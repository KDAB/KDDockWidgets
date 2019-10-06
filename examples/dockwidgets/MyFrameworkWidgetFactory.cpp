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

#include "MyFrameworkWidgetFactory.h"
#include <kddockwidgets/FrameworkWidgetFactory.h>
#include <kddockwidgets/widgets/SeparatorWidget_p.h>
#include <QApplication>

class MyTitleBar : public KDDockWidgets::TitleBar
{
public:
    explicit MyTitleBar(KDDockWidgets::Frame *frame)
        : KDDockWidgets::TitleBar(frame)
    {
        init();
    }

    explicit MyTitleBar(KDDockWidgets::FloatingWindow *fw)
        : KDDockWidgets::TitleBar(fw)
    {
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
class MySeparator : public KDDockWidgets::SeparatorWidget
{
public:
    explicit MySeparator(KDDockWidgets::Anchor *anchor,
                         KDDockWidgets::QWidgetAdapter *parent = nullptr)
        : KDDockWidgets::SeparatorWidget(anchor, parent)
    {
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.fillRect(rect(), isStatic() ? Qt::black : Qt::cyan);
    }
};

KDDockWidgets::TitleBar * CustomWidgetFactory::createTitleBar(KDDockWidgets::Frame *frame) const
{
    return new MyTitleBar(frame);
}

KDDockWidgets::TitleBar * CustomWidgetFactory::createTitleBar(KDDockWidgets::FloatingWindow *fw) const
{
    return new MyTitleBar(fw);
}

KDDockWidgets::Separator * CustomWidgetFactory::createSeparator(KDDockWidgets::Anchor *anchor,
                                                                KDDockWidgets::QWidgetAdapter *parent) const
{
    return new MySeparator(anchor, parent);
}
