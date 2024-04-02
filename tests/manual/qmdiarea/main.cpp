/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include <QMdiArea>
#include <QApplication>
#include <QMainWindow>
#include <QTabBar>
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QMainWindow mainWindow;

    auto area = new QMdiArea();
    area->setDocumentMode(true);
    area->setAutoFillBackground(true);
    area->setViewMode(QMdiArea::TabbedView);
    mainWindow.setCentralWidget(area);

    area->addSubWindow(new QPushButton("click1"));
    area->addSubWindow(new QPushButton("click2"));

    mainWindow.show();

    return app.exec();
}
