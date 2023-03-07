#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QSql>
#include <QtSql>
#include <QImage>

class databaseHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imageUrl READ getImageUrl WRITE setImageUrl NOTIFY imageUrlChanged)
public:
    explicit databaseHandler(QObject *parent = nullptr);
    ~databaseHandler();



signals:
    void imageUrlChanged();

public slots:
    QString getImageUrl();
    void setImageUrl(QUrl);

private:
    QSqlDatabase db;
    QSqlQuery query;

    QImage convertToQImage(QUrl);
    QByteArray obtainImageData(QImage);
    void addImageDatatoDB(QByteArray, int);

    int counter{};

    QString imageUrl;
    void intializeDatabase();

};

#endif // DATABASEHANDLER_H
