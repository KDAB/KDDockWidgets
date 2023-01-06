/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MyViewFactory.h"
#include "MyTitleBar_CSS.h"

#include <kddockwidgets/views/TitleBar_qtwidgets.h>
#include <kddockwidgets/views/Separator_qtwidgets.h>

#include <QApplication>
#include <QPainter>

// clazy:excludeall=missing-qobject-macro,ctor-missing-parent-argument

class MyTitleBar : public KDDockWidgets::Views::TitleBar_qtwidgets
{
public:
    explicit MyTitleBar(KDDockWidgets::Controllers::TitleBar *controller, View *parent = nullptr)
        : KDDockWidgets::Views::TitleBar_qtwidgets(controller, parent)
        , m_controller(controller)
    {
        setFixedHeight(60);
    }

    ~MyTitleBar() override;

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        QPen pen(Qt::black);
        const QColor focusedBackgroundColor = Qt::yellow;
        const QColor backgroundColor = focusedBackgroundColor.darker(115);
        QBrush brush(m_controller->isFocused() ? focusedBackgroundColor : backgroundColor);
        pen.setWidth(4);
        p.setPen(pen);
        p.setBrush(brush);
        p.drawRect(rect().adjusted(4, 4, -4, -4));
        QFont f = qGuiApp->font();
        f.setPixelSize(30);
        f.setBold(true);
        p.setFont(f);
        p.drawText(QPoint(10, 40), m_controller->title());
    }

private:
    KDDockWidgets::Controllers::TitleBar *const m_controller;
};

MyTitleBar::~MyTitleBar() = default;

// Inheriting from SeparatorWidget instead of Separator as it handles moving and mouse cursor
// changing
class MySeparator : public KDDockWidgets::Views::Separator_qtwidgets
{
public:
    explicit MySeparator(KDDockWidgets::Controllers::Separator *controller, View *parent)
        : KDDockWidgets::Views::Separator_qtwidgets(controller, parent)
    {
    }

    ~MySeparator() override;

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.fillRect(QWidget::rect(), Qt::cyan);
    }
};

MySeparator::~MySeparator() = default;

KDDockWidgets::View *
CustomWidgetFactory::createTitleBar(KDDockWidgets::Controllers::TitleBar *controller,
                                    KDDockWidgets::View *parent) const
{
    // Feel free to return MyTitleBar_CSS here instead, but just for education purposes!
    return new MyTitleBar(controller, parent);
}

KDDockWidgets::View *
CustomWidgetFactory::createSeparator(KDDockWidgets::Controllers::Separator *controller,
                                     KDDockWidgets::View *parent) const
{
    return new MySeparator(controller, parent);
}
