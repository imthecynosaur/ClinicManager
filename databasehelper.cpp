#include "databasehelper.h"
#include "qimage.h"


DataBaseHelper::DataBaseHelper(QObject *parent)
    : QObject{parent}
{
    intializeDb();
    query = new QSqlQuery;

    if (!checkForTable("images")){
        query->exec("CREATE TABLE images (id INTEGER PRIMARY KEY, imageData BLOB)");
        qDebug() << "table created";
    }
    if (!checkForTable("patients")){
        query->exec("CREATE TABLE patients (id INTEGER PRIMARY KEY, firstName TEXT, lastName TEXT)");
        qDebug() << "table created";
    }
}

DataBaseHelper::~DataBaseHelper()
{
    qDebug() << "db closed!";
    query = nullptr;
    delete query;
    db.close();
}

bool DataBaseHelper::intializeDb()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("patients.db");
    if (!db.open()){
        qWarning("db didn't open");
        return false;
    }
    qDebug() << "db connected";
    return true;
}

bool DataBaseHelper::checkForTable(QString tableName)
{
    query->prepare("SELECT name FROM sqlite_master WHERE type='table' AND name=:name");
    query->bindValue(":name", tableName);
    if (query->exec() && query->next()) {
        qDebug() << "Table" << tableName << "exists";
        return true;
    } else {
        qDebug() << "Table" << tableName << "does not exist";
        return false;
    }
}

QString DataBaseHelper::getFirstName(int id)
{
    query->prepare("SELECT firstName FROM patients WHERE id = :id");
    query->bindValue(":id", id);
    if(query->exec() && query->next()){
        QString firstName = query->value(0).toString();
        return firstName;
    }
}

QString DataBaseHelper::getLastName(int id)
{
    query->prepare("SELECT lastName FROM patients WHERE id = :id");
    query->bindValue(":id", id);
    if(query->exec() && query->next()){
        QString lastName = query->value(0).toString();
        return lastName;
    }
}


bool DataBaseHelper::insertIntoTable(int id, QString firstName, QString lastName, QUrl imageUrl)
{
    addImageDatatoDB(obtainImageData(convertToQImage(imageUrl)), id);
    query->prepare("INSERT INTO patients (id, firstName, lastName) VALUES (:id, :firstName, :lastName)");
    query->bindValue(":id", id);
    query->bindValue(":firstName", firstName);
    query->bindValue(":lastName", lastName);
    if (!query->exec()){
        qWarning() << "something went wrong";
        return false;
    }
    qDebug() << "patient" << id << "added to database";
    return true;
}



QByteArray DataBaseHelper::fetchImageData(int id)
{
    query->prepare("SELECT imageData FROM images WHERE id = :id");
    query->bindValue(":id", id);
    query->exec();

    if (query->next()) {
        QByteArray imageData = query->value(0).toByteArray();
        qDebug() << "imageData fetched";
        return imageData;
    }else{
        qWarning("failed to fectch imageData");
    }
}


QUrl DataBaseHelper::creatImageFromData(int id)
{
    QByteArray imageData{fetchImageData(id)};
    QImage image;
    image.loadFromData(imageData);
    QPixmap pixmap = QPixmap::fromImage(image);
    this->image = image;
    qDebug() << pixmap;
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filepath = desktopPath + "/random.png";
    qDebug() << filepath;
    if (!pixmap.save(filepath, "PNG")){
        qDebug() << "failed to save image on local disk";
    }
    QUrl url(filepath);

    qDebug() << url;
//     QByteArray bytes;
//     QBuffer buffer(&bytes);
//     buffer.open(QIODevice::WriteOnly);
//     pixmap.save(&buffer, "PNG");
    return url;
}



QImage DataBaseHelper::convertToQImage(QUrl imageUrl)
{
    QImage image;
    if (!image.load(imageUrl.toLocalFile())) {
        qWarning("Failed to load image");
    }
    return image;
}

QByteArray DataBaseHelper::obtainImageData(QImage image)
{
    QPixmap inPixmap = QPixmap::fromImage(image);
    QByteArray inByteArray;
    QBuffer inBuffer( &inByteArray );
    inBuffer.open( QIODevice::WriteOnly );
    inPixmap.save( &inBuffer, "PNG" );
    return inByteArray;
}


bool DataBaseHelper::addImageDatatoDB(QByteArray imageData, int id)
{
    query->prepare("INSERT INTO images (id, imageData) VALUES (:id, :data)");
    query->bindValue(":id", id);
    query->bindValue(":data", imageData);
    if (!query->exec()) {
        qWarning("Failed to insert image into database");
        return false;
    }
    qWarning("added");
    return true;
}
