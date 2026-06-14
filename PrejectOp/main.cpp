#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "scripts/UsbBridge.h"
#include <QQmlContext>
#include <QThread>
#include <QIcon>
#include "scripts/enrollbridge.h"
#include "scripts/removebridge.h"
#include "scripts/integration.h"
#include "scripts/removal.h"



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/Images/icon.png"));

    QQmlApplicationEngine engine;


    qmlRegisterType<FileInt>("MyUtils", 1, 0, "FileInt");
    qmlRegisterType<Removal>("MyUtils", 1, 0, "Removal");



    UsbBridge bridge;
    engine.rootContext()->setContextProperty("usbBridge", &bridge);

    EnrollBridge bridge1;
    engine.rootContext()->setContextProperty("enrollBridge", &bridge1);

    RemoveBridge bridge2;
    engine.rootContext()->setContextProperty("removeBridge", &bridge2);

    FileInt bridge3;
    engine.rootContext()->setContextProperty("fileInt", &bridge3);

    Removal bridge4;
    engine.rootContext()->setContextProperty("removalHeHe", &bridge4);



    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("PrejectOp", "Main");

    return QGuiApplication::exec();
}
