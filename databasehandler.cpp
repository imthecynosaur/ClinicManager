#include "databasehandler.h"
#include "qdebug.h"

databaseHandler::databaseHandler(QObject *parent)
    : QObject{parent},
      db{QSqlDatabase::addDatabase("QSQLITE")}
{
    db.setDatabaseName("patients.db");
    if (!db.open()){
        qDebug() << "db didn't open";
    }
    query.exec("DROP TABLE patients");
    query.exec("PRAGMA table_info(patients)");
    if (query.exec()) {
        qDebug() << "The table exists";
    } else {
        qDebug() << "created table";
//        query.exec("CREATE TABLE patients (id INTEGER PRIMARY KEY, firstName TEXT, lastName TEXT, age INTEGER, image BLOB)");
        query.exec("CREATE TABLE patinets (id INTEGER PRIMARY KEY, data BLOB)");
    }
}

databaseHandler::~databaseHandler()
{
    db.close();
    qDebug() << "db closed";
}

QString databaseHandler::getImageUrl()
{
    return imageUrl;
}

void databaseHandler::setImageUrl(QUrl newImageUrl)
{
//    imageUrl = newImageUrl;
//    qDebug() << "image url changed to" << imageUrl;
    addImageDatatoDB(obtainImageData(convertToQImage(newImageUrl)), 48);
}

QImage databaseHandler::convertToQImage(QUrl imageUrl)
{

    qDebug() << imageUrl;
    QImage image;
    if (!image.load(imageUrl.toLocalFile())) {
        qWarning("Failed to load image");
    }

//    QImage image;
//    if (!image.load("C:/Users/Steve/Pictures/Screenshots/Screenshot (1).png")) {
//        qWarning("Failed to load image");
//        // Handle error
//    }
    qDebug() << image;
    return image;
}

QByteArray databaseHandler::obtainImageData(QImage image)
{
    QByteArray imageData;

    qDebug() << imageData;
    qWarning() << "before";
    qWarning() << "before";
    qWarning() << "before";
    qWarning() << "before";
    qWarning() << "before";
    qWarning() << "before";
    qWarning() << "before";
    qWarning() << "before";
    qWarning() << "before";
    qWarning() << "before";
    qWarning() << "before";
    qWarning() << "before";
    qWarning() << "before";
    qWarning() << "before";
    qWarning() << "before";
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    buffer.close();
    qDebug() << imageData;
    return imageData;
}

void databaseHandler::addImageDatatoDB(QByteArray imageData, int id)
{
    query.prepare("INSERT INTO patintes (id, data) VALUES (:id, :data)");
    query.bindValue(":id", id);
    query.bindValue(":data", imageData);
    if (!query.exec()) {
        qWarning("Failed to insert image into database");
    }
    qWarning("added");
}

void databaseHandler::intializeDatabase()
{

}
