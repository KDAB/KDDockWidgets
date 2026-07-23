// main.cpp

#include <kddockwidgets/MainWindow.h>
#include <kddockwidgets/DockWidget.h>
#include <kddockwidgets/LayoutSaver.h>

#include <QApplication>
#include <QToolBar>


using namespace KDDockWidgets;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtWidgets);

    KDDockWidgets::QtWidgets::MainWindow mainWindow(QStringLiteral("MyMainWindow"));
    mainWindow.setAffinities({ "Main-Window-Affinity" });
    mainWindow.resize(300, 300);

    auto dock1 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock1"));
    dock1->setAffinities({ "Main-Window-Affinity", dock1->uniqueName() });

    auto dock2 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock2"));
    dock2->setAffinities({ "Main-Window-Affinity", dock2->uniqueName() });

    mainWindow.show();
    mainWindow.addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    mainWindow.addDockWidget(dock2, KDDockWidgets::Location_OnTop);

    auto toolbar = new QToolBar();
    mainWindow.addToolBar(toolbar);
    auto action = toolbar->addAction("Close all except Dock 1");
    action->setCheckable(true);


    QObject::connect(action, &QAction::toggled, [&](bool checked) {
        if (!checked) // restore
        {
            printf("restore\n");
            auto layoutSaver = LayoutSaver(RestoreOption::RestoreOption_RelativeToMainWindow);
            layoutSaver.restoreFromFile("maximize_using_layout_saver.json");
            action->setText("Close all except Dock 1");
        } else // maximize
        {
            printf("maximize\n");
            auto layoutSaver = LayoutSaver();
            layoutSaver.setAffinityNames({ dock1->uniqueName(), dock2->uniqueName() });
            layoutSaver.saveToFile("maximize_using_layout_saver.json");

            dock2->close();
            action->setText("Restore");
        }
    });
    return app.exec();
}
