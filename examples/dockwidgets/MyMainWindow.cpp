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
    const int randomNumber = qrand() % 100 + 1;

    if (randomNumber < 50) {
        if (randomNumber < 33) {
            return new MyWidget1();
        } else {
            return new MyWidget3();
        }
    } else {
        return new MyWidget2();
    }
}

MyMainWindow::MyMainWindow(KDDockWidgets::MainWindowOptions options, QWidget *parent)
    : MainWindow(QStringLiteral("MyMainWindow"), options, parent)
{
    // qApp->installEventFilter(this);

    qsrand(time(nullptr));

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
        dock->resize(600, 600);
        dock->show();
    });

    auto saveLayoutAction = fileMenu->addAction(QStringLiteral("Save Layout"));
   	connect(saveLayoutAction, &QAction::triggered, this, &MyMainWindow::slotSaveLayoutActionClicked);
    //connect(saveLayoutAction, &QAction::triggered, this, [] {
    //    KDDockWidgets::LayoutSaver saver;
    //    const bool result = saver.saveToDisk();
    //    qDebug() << "Saving layout to disk. Result=" << result;
    //});

    auto restoreLayoutAction = fileMenu->addAction(QStringLiteral("Restore Layout"));
   	connect(restoreLayoutAction, &QAction::triggered, this, &MyMainWindow::slotLoadLayoutActionClicked);
    //connect(restoreLayoutAction, &QAction::triggered, this, [] {
    //    KDDockWidgets::LayoutSaver saver;
    //    saver.restoreFromDisk();
    //});

    createDockWidgets();
	slotLoadLayoutActionClicked();
}

void MyMainWindow::slotLoadLayoutActionClicked()
{
	std::ifstream ifile("layout.config", std::ios::in | std::ios::binary);
	if (ifile.is_open())
	{
		std::string temp, s;
		while (std::getline(ifile, temp))
		{
			s += temp;
			s += "\n";
		}

		QByteArray arr = QByteArray::fromStdString(s);
		KDDockWidgets::LayoutSaver saver;
		saver.restoreLayout(arr);
	}
}

void MyMainWindow::slotSaveLayoutActionClicked()
{
	KDDockWidgets::LayoutSaver saver;
	if (true == saver.saveToDisk())
	{
		auto arr = saver.serializeLayout();
		std::string s = saver.serializeLayout().toStdString();
		std::ofstream ofile(".\\layout.config", std::ios::out | std::ios::binary);
		if (ofile.is_open())
		{
			ofile << s;
			ofile.close();
		}
		saver.restoreLayout(arr);
	}
}

void MyMainWindow::createDockWidgets()
{
    KDDockWidgets::DockWidget::List dockwidgets;
    // Create 9 KDDockWidget::DockWidget and the respective widgets they're hosting (MyWidget instances)
    for (int i = 0; i < 9; i++)
        dockwidgets << newDockWidget();


    // MainWindow::addDockWidget() attaches a dock widget to the main window:
#if defined(DOCKS_DEVELOPER_MODE) 
	addDockWidgetAsTab(dockwidgets[0]);
#else
	addDockWidget(dockwidgets[0], KDDockWidgets::Location_OnTop);
#endif

    // Here, for finer granularity we specify right of dockwidgets[0]:
    addDockWidget(dockwidgets[1], KDDockWidgets::Location_OnRight, dockwidgets[0]);

    addDockWidget(dockwidgets[2], KDDockWidgets::Location_OnLeft);
    addDockWidget(dockwidgets[3], KDDockWidgets::Location_OnBottom);
    addDockWidget(dockwidgets[4], KDDockWidgets::Location_OnBottom);

    // Tab two dock widgets toghether
    dockwidgets[3]->addDockWidgetAsTab(dockwidgets[5]);

    // 6 is floating, as it wasn't added to the main window via MainWindow::addDockWidget().
    // and we tab 7 with it.
    dockwidgets[6]->addDockWidgetAsTab(dockwidgets[7]);

    // Floating windows also support nesting, here we add 8 to the bottom of the group
    dockwidgets[6]->addDockWidgetToContainingWindow(dockwidgets[8], KDDockWidgets::Location_OnBottom);
}

KDDockWidgets::DockWidgetBase *MyMainWindow::newDockWidget()
{
    static int count = 0;
    auto dock = new KDDockWidgets::DockWidget(QStringLiteral("DockWidget #%1").arg(count));

    if (count == 1)
        dock->setIcon(QIcon::fromTheme(QStringLiteral("mail-message")));
    auto myWidget = newMyWidget();
    dock->setWidget(myWidget);
    dock->setTitle(QStringLiteral("DockWidget #%1").arg(count));
    dock->resize(600, 600);
    dock->show();
    m_toggleMenu->addAction(dock->toggleAction());

    count++;
    return dock;
}
