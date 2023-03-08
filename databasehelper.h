#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QObject>
//#include <QSql>
#include <QtSql>
#include <QPixmap>
#include <QImageReader>
#include <QStandardPaths>

//#include "imageprovider.h"


class DataBaseHelper : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QUrl imageUrl READ getImageUrl WRITE setImageUrl NOTIFY imageUrlChanged)
public:
    explicit DataBaseHelper(QObject *parent = nullptr);
    ~DataBaseHelper();

signals:
//    void imageUrlChanged();
//    void sendImage(QImage);
public slots:
    void insertIntoTable(int, QString);
    void showPatients();
//    void InsertImage(QUrl);
//    QUrl getImageUrl();
//    void setImageUrl(QUrl);
    bool addImagetoDatabase(QUrl);
    QByteArray getImageData();
    void setImageData(QByteArray);
    QPixmap creatImageFromData();
//    void recieveImageRequest();


private:
    QSqlDatabase db;
    QSqlQuery* query;
    bool intializeDb();

//    QUrl imageUrl;

    bool checkForTable(QString);


    QImage convertToQImage(QUrl);
    QByteArray obtainImageData(QImage);
    bool addImageDatatoDB(QByteArray, int);

    QImage image;

    QByteArray imageData;
};

#endif // DATABASEHELPER_H
