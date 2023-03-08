#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>

#include "databasehelper.h"
//#include "imageprovider.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    ImageProvider IP;
//    QImage image;
//    IP.setQpixmap(image);


//    qmlRegisterType<databaseHandler>("com.databasehandler", 1, 0, "DBHandler");
    qmlRegisterType<DataBaseHelper>("com.databasehelper", 1, 0, "DBHelper");

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
