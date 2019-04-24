/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MainWindow.h"
#include "ExampleDockableWidget.h"
#include "DockWidget.h"
#include "LayoutSaver.h"

#include <QMouseEvent>
#include <QtWidgets>

using namespace KDDockWidgets;

DockWidget::Options s_dockWidgetOptions = DockWidget::Option_NotClosable;

static MyWidget *newMyWidget()
{
    static int count = 0;
    count++;
    return new MyWidget();
}


class MyMainWindow : public MainWindow
{
public:
    MyMainWindow(MainWindowOptions options)
        : MainWindow(QStringLiteral("MyMainWindow"), options)
    {
        auto menubar = menuBar();
        auto fileMenu = new QMenu(QStringLiteral("File"));
        toggleMenu = new QMenu(QStringLiteral("Toggle"));
        menubar->addMenu(fileMenu);
        menubar->addMenu(toggleMenu);

        QAction *newAction = fileMenu->addAction(QStringLiteral("New DockWidget"));
        static int count = 0;
        count++;
        connect(newAction, &QAction::triggered, this, [] {
            auto w = newMyWidget();
            w->setGeometry(100, 100, 400, 400);
            auto dock = new DockWidget(QStringLiteral("dock %1").arg(count));
            dock->setWidget(w);
            dock->resize(400, 400);
            dock->show();
        });

        // newAction = fileMenu->addAction("Change MainWindow indicator style");

        auto saveLayoutAction = fileMenu->addAction(QStringLiteral("Save Layout"));
        connect(saveLayoutAction, &QAction::triggered, this, [] {
            LayoutSaver saver;
            const bool result = saver.saveToDisk();
            qDebug() << "Saving layout to disk. Result=" << result;
        });

        auto restoreLayoutAction = fileMenu->addAction(QStringLiteral("Restore Layout"));
        connect(restoreLayoutAction, &QAction::triggered, this, [] {
            LayoutSaver saver;
            saver.restoreFromDisk();
        });

        /*connect(newAction, &QAction::triggered, this, [this] {
            auto dropArea = qobject_cast<DropArea*>(centralWidget());
            Q_ASSERT(dropArea);
            //if (dropArea->indicatorStyle() == DropIndicatorOverlayInterface::TypeAnimated)
                //dropArea->setIndicatorStyle(DropIndicatorOverlayInterface::TypeClassic);
            //else
                //dropArea->setIndicatorStyle(DropIndicatorOverlayInterface::TypeAnimated);
        });*/
    }


    QMenu *toggleMenu;
};

int main(int argc, char **argv)
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setOrganizationName(QStringLiteral("KDAB"));
    app.setApplicationName(QStringLiteral("Test app"));
    qApp->setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    const bool noCentralFrame = app.arguments().contains(QStringLiteral("--no-central"));
    MainWindowOptions options = noCentralFrame ? MainWindowOption_None
                                               : MainWindowOption_HasCentralFrame;

    MyMainWindow window(options);
    window.resize(1000, 800);
    window.show();

    auto example = newMyWidget();
    auto dock = new DockWidget(QStringLiteral("foo"), s_dockWidgetOptions);
    dock->setWidget(example);
    dock->resize(400, 400);
    dock->show();
    window.toggleMenu->addAction(dock->toggleAction());

    example = newMyWidget();
    example->setGeometry(100, 100, 400, 400);
    dock = new DockWidget(QStringLiteral("bar"), s_dockWidgetOptions);
    dock->setWidget(example);
    dock->resize(400, 400);
    dock->show();
    window.toggleMenu->addAction(dock->toggleAction());

    auto textEdit = new QTextEdit();
    textEdit->setText(QStringLiteral("Hello, this is the central document."));
    dock = new DockWidget(QStringLiteral("doc 0"), s_dockWidgetOptions);
    dock->setWidget(textEdit);
    window.toggleMenu->addAction(dock->toggleAction());
    if (!noCentralFrame)
        window.addDockWidgetAsTab(dock);

    return app.exec();
}
