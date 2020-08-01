
#include "private/quick/DockWidgetQuick.h"
#include "Config.h"

#include <QQuickView>
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setSource(QUrl("qrc:/main.qml"));
    view.resize(1000, 800);
    view.show();
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    KDDockWidgets::Config::self().setQmlEngine(view.engine());

    auto dw = new KDDockWidgets::DockWidgetQuick("Dock #1");
    dw->setWidget(QStringLiteral("qrc:/Guest1.qml"));
    dw->resize(QSize(800, 800));
    dw->show();

    auto dw2 = new KDDockWidgets::DockWidgetQuick("Dock #2");
    dw2->setWidget(QStringLiteral("qrc:/Guest2.qml"));
    dw2->resize(QSize(800, 800));
    dw2->show();

    auto dw3 = new KDDockWidgets::DockWidgetQuick("Dock #2");
    dw3->setWidget(QStringLiteral("qrc:/Guest2.qml"));
    dw3->resize(QSize(800, 800));
    dw3->show();

    dw->addDockWidgetAsTab(dw2);
    dw->addDockWidgetToContainingWindow(dw3, KDDockWidgets::Location_OnRight);

    return app.exec();
}
