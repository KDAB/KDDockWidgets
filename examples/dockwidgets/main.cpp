#include <kddockwidgets/DockWidget.h>
#include <kddockwidgets/KDDockWidgets.h>
#include <kddockwidgets/MainWindow.h>

#include <QApplication>
#include <QTextEdit>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    KDDockWidgets::MainWindow mainWindow(QString("Main"));

    auto dock1 = new KDDockWidgets::DockWidget(QStringLiteral("Dock1"));
    dock1->setWidget(new QTextEdit());
    mainWindow.addDockWidget(dock1, KDDockWidgets::Location_OnTop);

    auto dock2 = new KDDockWidgets::DockWidget(QStringLiteral("Dock2"));
    dock2->setWidget(new QTextEdit());
    mainWindow.addDockWidget(dock2, KDDockWidgets::Location_OnBottom);

    mainWindow.show();

    return app.exec();
}
