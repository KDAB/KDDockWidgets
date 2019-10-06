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

KDDockWidgets::DockWidget::Options s_dockWidgetOptions = KDDockWidgets::DockWidget::Option_None;

static MyWidget *newMyWidget()
{
    static int count = 0;
    count++;
    return new MyWidget();
}

MyMainWindow::MyMainWindow(KDDockWidgets::MainWindowOptions options, QWidget *parent)
    : MainWindow(QStringLiteral("MyMainWindow"), options, parent)
{
    // qApp->installEventFilter(this);

    auto menubar = menuBar();
    auto fileMenu = new QMenu(QStringLiteral("File"));
    m_toggleMenu = new QMenu(QStringLiteral("Toggle"));
    menubar->addMenu(fileMenu);
    menubar->addMenu(m_toggleMenu);

    QAction *newAction = fileMenu->addAction(QStringLiteral("New DockWidget"));
    static int count = 0;
    count++;
    connect(newAction, &QAction::triggered, this, [] {
        auto w = newMyWidget();
        w->setGeometry(100, 100, 400, 400);
        auto dock = new KDDockWidgets::DockWidget(QStringLiteral("dock %1").arg(count));
        dock->setWidget(w);
        dock->resize(400, 400);
        dock->show();
    });

    // newAction = fileMenu->addAction("Change MainWindow indicator style");

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

    auto example = newMyWidget();
    auto dock = new KDDockWidgets::DockWidget(QStringLiteral("foo"), s_dockWidgetOptions);
    dock->setIcon(QIcon::fromTheme(QStringLiteral("mail-message")));
    dock->setWidget(example);
    dock->setTitle(QStringLiteral("foo"));
    example->winId(); // for testing native widgets too
    dock->resize(400, 400);
    dock->show();
    m_toggleMenu->addAction(dock->toggleAction());

    example = newMyWidget();
    example->setGeometry(100, 100, 400, 400);
    dock = new KDDockWidgets::DockWidget(QStringLiteral("bar"), s_dockWidgetOptions);
    dock->setWidget(example);
    dock->resize(400, 400);
    dock->show();
    m_toggleMenu->addAction(dock->toggleAction());

    auto textEdit = new QTextEdit();
    textEdit->setText(QStringLiteral("Hello, this is the central document."));
    dock = new KDDockWidgets::DockWidget(QStringLiteral("doc 0"), s_dockWidgetOptions);
    dock->setWidget(textEdit);
    m_toggleMenu->addAction(dock->toggleAction());
    if (options & KDDockWidgets::MainWindowOption_HasCentralFrame)
        addDockWidgetAsTab(dock);
}
