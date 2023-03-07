#include "databasehelper.h"
#include "qimage.h"


DataBaseHelper::DataBaseHelper(QObject *parent)
    : QObject{parent}
{
    intializeDb();
    query = new QSqlQuery;

    if (!checkForTable("names")){
        query->exec("CREATE TABLE names (id INTEGER PRIMARY KEY, name TEXT)");
        qDebug() << "table created";
    }
    if (!checkForTable("images")){
        query->exec("CREATE TABLE images (id INTEGER PRIMARY KEY, imageData BLOB)");
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

void DataBaseHelper::insertIntoTable(int id, QString name)
{
//    query->exec("SELECT ")
    query->prepare("INSERT INTO names (id, name) VALUES (:id, :name)");
    query->bindValue(":id", id);
    query->bindValue(":name", name);
    if (!query->exec()){
        qWarning() << "something went wrong";
    }
}

void DataBaseHelper::showPatients()
{
    query->exec("SELECT * FROM names");
    while (query->next()) {
        int id = query->value(0).toInt();
        QString name = query->value(1).toString();
        qDebug() << "ID" << id << "Name:" << name;
    }
}

//void DataBaseHelper::InsertImage(QUrl imageUrl)
//{
//    addImageDatatoDB(obtainImageData(convertToQImage(imageUrl)), 48);
//}

//QUrl DataBaseHelper::getImageUrl()
//{
//    return imageUrl;
//}

//void DataBaseHelper::setImageUrl(QUrl url)
//{
//    imageUrl = url;
//    InsertImage(url);
//}

bool DataBaseHelper::addImagetoDatabase(QUrl imageUrl)
{
    if (addImageDatatoDB(obtainImageData(convertToQImage(imageUrl)), 87)){
        return true;
    }
    return false;
}

QByteArray DataBaseHelper::getImageData()
{
    return imageData;
}

void DataBaseHelper::setImageData(QByteArray imageData)
{
    this->imageData = imageData;
}

QImage DataBaseHelper::creatImageFromData()
{
    QImage image;
    image.loadFromData(imageData);
    return image;
}


QImage DataBaseHelper::convertToQImage(QUrl imageUrl)
{
    QImage image;
    if (!image.load(imageUrl.toLocalFile())) {
        qWarning("Failed to load image");
    }
    qDebug() << image;
    return image;
}

QByteArray DataBaseHelper::obtainImageData(QImage image)
{
    QPixmap inPixmap = QPixmap::fromImage(image);
    QByteArray inByteArray;
    QBuffer inBuffer( &inByteArray );
    inBuffer.open( QIODevice::WriteOnly );
    inPixmap.save( &inBuffer, "PNG" );
    setImageData(inByteArray);
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
