/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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
#include "Config.h"
#include "TitleBar_p.h"
#include "DockWidget.h"
#include "SeparatorWidget_p.h"
#include "FrameworkWidgetFactory.h"

#include <QTextEdit>
#include <QApplication>
#include <QStyleFactory>
#include <QPainter>

using namespace KDDockWidgets;

class MyTitleBar : public TitleBar
{
public:
    explicit MyTitleBar(Frame *frame) : TitleBar(frame) {
        init();
    }
    explicit MyTitleBar(FloatingWindow *fw) : TitleBar(fw) {
        init();
    }

    void init()
    {
        setFixedHeight(60);
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        QPen pen(Qt::black);
        QBrush brush(Qt::yellow);
        pen.setWidth(4);
        p.setPen(pen);
        p.setBrush(brush);
        p.drawRect(rect().adjusted(4, 4, -4, -4));
        QFont f = qApp->font();
        f.setPixelSize(30);
        f.setBold(true);
        p.setFont(f);
        p.drawText(QPoint(10,40), title());
    }
};

// Inheriting from SeparatorWidget instead of Separator as it handles moving and mouse cursor changing
class MySeparator : public SeparatorWidget
{
public:
    explicit MySeparator(Anchor *anchor, QWidgetAdapter *parent = nullptr)
        : SeparatorWidget(anchor, parent)
    {
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.fillRect(rect(), isStatic() ? Qt::black : Qt::cyan);
    }
};

class CustomWidgetFactory : public DefaultWidgetFactory
{
public:
    TitleBar * createTitleBar(Frame *frame) const override
    {
        return new MyTitleBar(frame);
    }

    TitleBar * createTitleBar(FloatingWindow *fw) const override
    {
        return new MyTitleBar(fw);
    }

    Separator * createSeparator(Anchor *anchor, QWidgetAdapter *parent = nullptr) const override
    {
        return new MySeparator(anchor, parent);
    }
};

DockWidgetBase *createDockWidget(const QString &name)
{
    auto dock = new DockWidget(name);
    dock->setWidget(new QTextEdit());
    dock->setTitle(name);
    dock->resize(400, 400);
    dock->show();
    return dock;
}

int main(int argc, char **argv)
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);

    Config::self().setFrameworkWidgetFactory(new CustomWidgetFactory()); // Sets our custom factory
    Config::self().setSeparatorThickness(10, /*static=*/ false);

    app.setOrganizationName(QStringLiteral("KDAB"));
    app.setApplicationName(QStringLiteral("Test app"));


    MainWindow mainWindow(QStringLiteral("myMainWindow"), MainWindowOption_None);
    mainWindow.resize(1000, 800);
    mainWindow.show();

    DockWidgetBase *dock1 = createDockWidget(QStringLiteral("one"));
    createDockWidget(QStringLiteral("two"));
    createDockWidget(QStringLiteral("three"));
    mainWindow.addDockWidget(dock1, Location_OnTop);

    return app.exec();
}

