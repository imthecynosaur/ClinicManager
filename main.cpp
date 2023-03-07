#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>

#include "databasehelper.h"


//#include "databasehandler.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    qmlRegisterType<databaseHandler>("com.databasehandler", 1, 0, "DBHandler");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/clinicTest/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);



    DataBaseHelper db;

    db.insertIntoTable(1, "ali");
    db.insertIntoTable(5, "naghi");

    db.showPatients();


    return app.exec();
}
