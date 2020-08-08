/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MyFrameworkWidgetFactory.h"
#include <kddockwidgets/FrameworkWidgetFactory.h>
#include <kddockwidgets/private/widgets/TitleBarWidget_p.h>
#include <kddockwidgets/multisplitter/Separator_qwidget.h>
#include <QApplication>

class MyTitleBar : public KDDockWidgets::TitleBarWidget
{
public:
    explicit MyTitleBar(KDDockWidgets::Frame *frame)
        : KDDockWidgets::TitleBarWidget(frame)
    {
        init();
    }

    explicit MyTitleBar(KDDockWidgets::FloatingWindow *fw)
        : KDDockWidgets::TitleBarWidget(fw)
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
        //QBrush brush(isFocused() ? QColor(0xff, 0x80, 0) : Qt::yellow); // Uncomment to color differently if dock widget is focused
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
class MySeparator : public Layouting::SeparatorWidget
{
public:
    explicit MySeparator(Layouting::Widget *parent)
        : Layouting::SeparatorWidget(parent)
    {
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.fillRect(QWidget::rect(), Qt::cyan);
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

Layouting::Separator * CustomWidgetFactory::createSeparator(Layouting::Widget *parent) const
{
    return new MySeparator(parent);
}

