#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QObject>
#include <QtSql>
#include <QPixmap>
#include <QImageReader>
#include <QStandardPaths>


class DataBaseHelper : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseHelper(QObject *parent = nullptr);
    ~DataBaseHelper();

signals:
public slots:
    bool insertIntoTable(int, QString, QString, QUrl);
    QUrl creatImageFromData(int);
    QString getFirstName(int);
    QString getLastName(int);


private:
    QSqlDatabase db;
    QSqlQuery* query;
    bool intializeDb();

    bool checkForTable(QString);

    QImage convertToQImage(QUrl);
    QByteArray obtainImageData(QImage);
    bool addImageDatatoDB(QByteArray, int);
    QByteArray fetchImageData(int);
};

#endif // DATABASEHELPER_H
