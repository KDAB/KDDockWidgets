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

#include "MyMainWindow.h"
#include "MyWidget.h"

#include <kddockwidgets/LayoutSaver.h>
#include <kddockwidgets/DockWidget.h>

#include <QMenu>
#include <QMenuBar>
#include <QEvent>
#include <QDebug>
#include <QString>
#include <QTextEdit>

#include <stdlib.h>
#include <time.h>

static MyWidget *newMyWidget()
{
    const int randomNumber = rand() % 100 + 1;

    if (randomNumber < 66) {
        if (randomNumber < 33) {
            return new MyWidget1();
        } else {
            return new MyWidget2();
        }
    } else {
        return new MyWidget3();
    }
}

MyMainWindow::MyMainWindow(KDDockWidgets::MainWindowOptions options, QWidget *parent)
    : MainWindow(QStringLiteral("MyMainWindow"), options, parent)
{
    // qApp->installEventFilter(this);

    srand(time(nullptr));

    auto menubar = menuBar();
    auto fileMenu = new QMenu(QStringLiteral("File"));
    m_toggleMenu = new QMenu(QStringLiteral("Toggle"));
    menubar->addMenu(fileMenu);
    menubar->addMenu(m_toggleMenu);

    QAction *newAction = fileMenu->addAction(QStringLiteral("New DockWidget"));

    connect(newAction, &QAction::triggered, this, [] {
        static int count = 0;
        count++;
        auto w = newMyWidget();
        w->setGeometry(100, 100, 400, 400);
        auto dock = new KDDockWidgets::DockWidget(QStringLiteral("new dock %1").arg(count));
        dock->setWidget(w);
        dock->resize(400, 400);
        dock->show();
    });

    auto saveLayoutAction = fileMenu->addAction(QStringLiteral("Save Layout"));
    connect(saveLayoutAction, &QAction::triggered, this, [] {
        KDDockWidgets::LayoutSaver saver;
        const bool result = saver.saveToDisk();
        qDebug() << "Saving layout to disk. Result=" << result;
    });

    auto restoreLayoutAction = fileMenu->addAction(QStringLiteral("Restore Layout"));
    connect(restoreLayoutAction, &QAction::triggered, this, [] {
        KDDockWidgets::LayoutSaver saver;
        saver.restoreFromDisk();
    });

    struct Descriptor {
        KDDockWidgets::Location location;
        int relativeTo;
    };

    const QVector<Descriptor> docksToCreate = {
        { KDDockWidgets::Location_OnTop, -1 },
        { KDDockWidgets::Location_OnRight, 0 },
        { KDDockWidgets::Location_OnLeft, -1 },
        { KDDockWidgets::Location_OnBottom, -1 },
    };

    int count = 0;
    KDDockWidgets::DockWidget::List createdDockWidgets;
    for (Descriptor desc : docksToCreate) {
        count++;
        auto dock = new KDDockWidgets::DockWidget(QStringLiteral("DockWidget #%1").arg(count));
        createdDockWidgets << dock;

        if (count == 1)
            dock->setIcon(QIcon::fromTheme(QStringLiteral("mail-message")));
        auto myWidget = newMyWidget();
        dock->setWidget(myWidget);
        dock->setTitle(QStringLiteral("DockWidget #%1").arg(count));
        dock->resize(400, 400);
        dock->show();
        m_toggleMenu->addAction(dock->toggleAction());

        KDDockWidgets::DockWidgetBase *relativeTo = desc.relativeTo == -1 ? nullptr
                                                                          : createdDockWidgets.at(desc.relativeTo);

        addDockWidget(dock, desc.location, relativeTo);
    }
}
