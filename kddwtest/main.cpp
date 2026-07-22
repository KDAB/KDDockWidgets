#include <kddockwidgets/Config.h>
#include <kddockwidgets/qtquick/Platform.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Fusion");

    // Bug 2 repro: uncomment the next line, then rebuild and run the "Maximize Button" tab.
    // KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::self().flags() | KDDockWidgets::Config::Flag_TitleBarHasMaximizeButton);
    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtQuick);
    // Keep MDI windows inside the MDI area.
    KDDockWidgets::Config::self().setMDIPopupThreshold(-1);

    QQmlApplicationEngine engine;
    KDDockWidgets::QtQuick::Platform::instance()->setQmlEngine(&engine);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("kddwtest", "Main");

    return QGuiApplication::exec();
}
