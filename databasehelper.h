#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QObject>
//#include <QSql>
#include <QtSql>
#include <QPixmap>
#include <QImageReader>

class DataBaseHelper : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QUrl imageUrl READ getImageUrl WRITE setImageUrl NOTIFY imageUrlChanged)
public:
    explicit DataBaseHelper(QObject *parent = nullptr);
    ~DataBaseHelper();

signals:
//    void imageUrlChanged();
public slots:
    void insertIntoTable(int, QString);
    void showPatients();
//    void InsertImage(QUrl);
//    QUrl getImageUrl();
//    void setImageUrl(QUrl);
    bool addImagetoDatabase(QUrl);
    QByteArray getImageData();
    void setImageData(QByteArray);
    QImage creatImageFromData();

private:
    QSqlDatabase db;
    QSqlQuery* query;
    bool intializeDb();

//    QUrl imageUrl;

    bool checkForTable(QString);


    QImage convertToQImage(QUrl);
    QByteArray obtainImageData(QImage);
    bool addImageDatatoDB(QByteArray, int);

    QByteArray imageData;
};

#endif // DATABASEHELPER_H
