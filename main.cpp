#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>

#include "databasehelper.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<DataBaseHelper>("com.databasehelper", 1, 0, "DBHelper");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/clinicTest/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
