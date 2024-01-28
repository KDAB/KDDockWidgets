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
#include <QMenuBar>
#include <QMenu>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>

class Widget : public QWidget
{
public:
    explicit Widget(QColor c, bool showButtons = false)
        : color(c)
    {
        setMinimumSize(300, 300);
        if (showButtons) {
            auto lay = new QVBoxLayout(this);
            auto button1 = new QPushButton("close()");
            auto button2 = new QPushButton("setVisible(false)");
            auto button3 = new QPushButton("hide()");
            lay->addStretch();
            lay->addWidget(button1);
            lay->addWidget(button2);
            lay->addWidget(button3);

            connect(button1, &QPushButton::clicked, this, [this] {
                dockWidget()->close();
            });

            connect(button2, &QPushButton::clicked, this, [this] {
                dockWidget()->setVisible(false);
            });

            connect(button3, &QPushButton::clicked, this, [this] {
                dockWidget()->hide();
            });
        }
    }

    QDockWidget *dockWidget() const
    {
        return qobject_cast<QDockWidget *>(parentWidget());
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.fillRect(rect(), color);
    }

    QColor color;
};

class CustomDockWidget : public QDockWidget
{
public:
    using QDockWidget::QDockWidget;
    void closeEvent(QCloseEvent *ev) override
    {
        QDockWidget::closeEvent(ev);
        qDebug() << "CustomDockWidget::closeEvent";
    }
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

    auto dock1 = new CustomDockWidget("d1", &mainWindow);
    auto dock2 = new QDockWidget("d2", &mainWindow);
    auto dock3 = new QDockWidget("d3", &mainWindow);
    auto hiddenDock = new QDockWidget("hiddenDock", &mainWindow);
    hiddenDock->setVisible(false);

    dock1->setWidget(new Widget(QColor("#9CAFB7"), true));
    dock2->setWidget(new Widget(QColor("#F6CA83")));
    dock3->setWidget(new Widget(QColor("#ADB993")));

    mainWindow.addDockWidget_legacy(Qt::LeftDockWidgetArea, dock1);
    mainWindow.addDockWidget_legacy(Qt::RightDockWidgetArea, dock2);
    mainWindow.addDockWidget_legacy(Qt::BottomDockWidgetArea, dock3);
    mainWindow.addDockWidget_legacy(Qt::BottomDockWidgetArea, hiddenDock);
    mainWindow.setCentralWidget_legacy(new Widget(Qt::black));

    QMenuBar *menuBar = mainWindow.menuBar();
    QMenu *toggleMenu = menuBar->addMenu("Toggle");
    toggleMenu->addAction(dock1->toggleViewAction());
    toggleMenu->addAction(dock2->toggleViewAction());
    toggleMenu->addAction(dock3->toggleViewAction());
    toggleMenu->addAction(hiddenDock->toggleViewAction());

    mainWindow.show();

    return app.exec();
}
