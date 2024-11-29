#include <kddockwidgets/MainWindow.h>
#include <kddockwidgets/DockWidget.h>

#include "kddockwidgets/Config.h"
#include <kddockwidgets/LayoutSaver.h>

#include <QStyleFactory>
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>

using namespace KDDockWidgets;

struct SuperDock
{
    QtWidgets::DockWidget *dockwidget;
    QtWidgets::MainWindow *mainwindow;
};

QtWidgets::DockWidget *create_sub_dockwidget(int number, QString label, QColor color)
{
    auto set_color = [](QLabel *label, QColor color) {
        auto pal = label->palette();
        pal.setColor(QPalette::ColorRole::Window, color);
        label->setPalette(pal);
        label->setAutoFillBackground(true);
    };

    auto subdock = new QtWidgets::DockWidget(QStringLiteral("SubDock-%2 (%1)").arg(number).arg(label));
    subdock->setAffinityName(QStringLiteral("MainWindow%1").arg(number));
    auto subwidget = new QLabel(QStringLiteral("subwidget-%1 (%2)").arg(number).arg(label));
    subwidget->setAlignment(Qt::AlignCenter);
    set_color(subwidget, color);
    subdock->setWidget(subwidget);
    return subdock;
}

SuperDock create_super_dock(int number)
{
    auto mw = new QtWidgets::MainWindow(QStringLiteral("MainWindow%1").arg(number));
    mw->setAffinities({ QStringLiteral("MainWindow%1").arg(number) });
    mw->setWindowTitle(QStringLiteral("Main Window %1").arg(number));

    auto container = new QWidget();
    auto layout = new QVBoxLayout(container);
    auto label = new QLabel(QStringLiteral("Main Window %1").arg(number));
    label->setAlignment(Qt::AlignBottom);
    layout->addWidget(label);
    layout->addWidget(mw);

    auto superdock = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("SuperDock-%1").arg(number));
    superdock->setAttribute(Qt::WA_DeleteOnClose);
    superdock->setWidget(container);
    return { superdock, mw };
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtWidgets);

    // auto &config = Config::self();

    // Create application main window
    QtWidgets::MainWindow appMainWindow(QStringLiteral("Application MainWindow"));
    appMainWindow.setWindowTitle("Application Main Window");
    appMainWindow.resize(600, 200);
    appMainWindow.show();

    auto menu = new QMenu(QStringLiteral("File"));
    auto menubar = appMainWindow.menuBar();
    menubar->addMenu(menu);

    auto saveLayoutAction = menu->addAction("Save layout");
    QObject::connect(saveLayoutAction, &QAction::triggered, [] {
        KDDockWidgets::LayoutSaver saver;
        const bool result = saver.saveToFile(QStringLiteral("mylayout.json"));
        qDebug() << "Saving layout to disk. Result=" << result;
    });
    auto restoreLayoutAction = menu->addAction("Restore layout");
    QObject::connect(restoreLayoutAction, &QAction::triggered, [] {
        KDDockWidgets::RestoreOptions options = KDDockWidgets::RestoreOption_None;
        KDDockWidgets::LayoutSaver saver(options);
        saver.restoreFromFile(QStringLiteral("mylayout.json"));
    });

    /* Setup the specific layout*/

    // Super-dock 1 with one red sub-dock
    auto super_dock_1 = create_super_dock(1);
    auto sub_dock_a_1 = create_sub_dockwidget(1, "A", Qt::red);
    appMainWindow.addDockWidget(super_dock_1.dockwidget, KDDockWidgets::Location_OnRight);
    super_dock_1.mainwindow->addDockWidget(sub_dock_a_1, KDDockWidgets::Location_OnRight);

    // Super-dock 2 with one blue sub-dock
    auto super_dock_2 = create_super_dock(2);
    auto sub_dock_b_2 = create_sub_dockwidget(2, "B", Qt::blue);
    appMainWindow.addDockWidget(super_dock_2.dockwidget, KDDockWidgets::Location_OnRight);
    super_dock_2.mainwindow->addDockWidget(sub_dock_b_2, KDDockWidgets::Location_OnRight);

    /* Do the problematic actions for case 1 (visibility) */
    if (0) {
        super_dock_1.dockwidget->addDockWidgetAsTab(super_dock_2.dockwidget);
        super_dock_1.dockwidget->setAsCurrentTab();
        saveLayoutAction->trigger();
        restoreLayoutAction->trigger();
    }

    return app.exec();
}
