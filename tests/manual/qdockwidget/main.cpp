/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include <kddockwidgets/MainWindow.h>

#include <QDockWidget>
#include <QApplication>
#include <QMainWindow>
#include <QStyleFactory>
#include <QPainter>

class Widget : public QWidget
{
public:
    explicit Widget(QColor c)
        : color(c)
    {
        setMinimumSize(300, 300);
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.fillRect(rect(), color);
    }

    QColor color;
};

int main(int argc, char **argv)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    QApplication app(argc, argv);
    qApp->setStyle(QStyleFactory::create(QStringLiteral("Fusion")));
    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtWidgets);

    KDDockWidgets::QtWidgets::MainWindow mainWindow("mainwindow1", KDDockWidgets::MainWindowOption_QDockWidgets);
    mainWindow.resize(1000, 1000);

    auto dock1 = new QDockWidget("d1", &mainWindow);
    auto dock2 = new QDockWidget("d2", &mainWindow);
    auto dock3 = new QDockWidget("d3", &mainWindow);

    dock1->setWidget(new Widget(QColor("#9CAFB7")));
    dock2->setWidget(new Widget(QColor("#F6CA83")));
    dock3->setWidget(new Widget(QColor("#ADB993")));

    mainWindow.addDockWidget_legacy(Qt::LeftDockWidgetArea, dock1);
    mainWindow.addDockWidget_legacy(Qt::RightDockWidgetArea, dock2);
    mainWindow.addDockWidget_legacy(Qt::BottomDockWidgetArea, dock3);
    mainWindow.setCentralWidget_legacy(new Widget(Qt::black));

    mainWindow.show();

    return app.exec();
}
