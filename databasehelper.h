#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QObject>
//#include <QSql>
#include <QtSql>

class DataBaseHelper : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseHelper(QObject *parent = nullptr);
    ~DataBaseHelper();

signals:

public slots:
    void insertIntoTable(int, QString);
    void showPatients();

private:
    QSqlDatabase db;
    QSqlQuery* query;
    bool intializeDb();

    bool checkForTable(QString);
};

#endif // DATABASEHELPER_H
