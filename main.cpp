#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>

#include "databasehelper.h"


//#include "databasehandler.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    qmlRegisterType<databaseHandler>("com.databasehandler", 1, 0, "DBHandler");
    qmlRegisterType<DataBaseHelper>("com.databasehelper", 1, 0, "DBHelper");
    qmlRegisterType<QByteArray>("MyTypes", 1, 0, "QByteArray");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/clinicTest/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);



//    DataBaseHelper db;
//    QUrl address{"file:///C:/Users/Steve/Pictures/Screenshots/Screenshot (1).png"};
//    db.InsertImage(address);


    return app.exec();
}
