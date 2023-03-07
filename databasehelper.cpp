#include "databasehelper.h"


DataBaseHelper::DataBaseHelper(QObject *parent)
    : QObject{parent}
{
    intializeDb();
    query = new QSqlQuery;

    if (!checkForTable("names")){
        query->exec("CREATE TABLE names (id INTEGER PRIMARY KEY, name TEXT)");
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
