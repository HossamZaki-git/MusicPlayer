#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include "PlayerController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    /*
        Setting the window icon
        using qrc:/qt/qml before the path, makes the icon a part of the exe file not just an external asset
        this is mandatory because main.cpp isn't part of the QML module (can't see what's inside the CMakeList.txt file)
    */
    app.setWindowIcon(QIcon(":/qt/qml/MusicPlayer/assets/icons/app_icon.ico"));

    QQmlApplicationEngine engine;

    PlayerController* playerController = new PlayerController(&app);
    //           The name that will be used for the import, major version, minor version, object name in QML, pointer to the object
    qmlRegisterSingletonInstance("com.company.PlayerController", 1, 0, "PlayerController", playerController);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    // The starting point of the QML engine
    engine.loadFromModule("MusicPlayer", "Main");

    return QCoreApplication::exec();
}
