/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MyViewFactory.h"
#include "MyTitleBar_CSS.h"

#include <kddockwidgets/qtwidgets/views/TitleBar.h>
#include <kddockwidgets/qtwidgets/views/Separator.h>
#include <kddockwidgets/qtwidgets/views/Group.h>
#include <kddockwidgets/qtcommon/View.h>

#include <QApplication>
#include <QPainter>

// clazy:excludeall=missing-qobject-macro,ctor-missing-parent-argument

class MyTitleBar : public KDDockWidgets::QtWidgets::TitleBar
{
public:
    explicit MyTitleBar(KDDockWidgets::Core::TitleBar *controller, KDDockWidgets::Core::View *parent = nullptr)
        : KDDockWidgets::QtWidgets::TitleBar(controller, parent)
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

    // Not needed to override. Just here to illustrate setHideDisabledButtons()
    void init() override
    {
        // For demo purposes, we're hiding the close button if it's disabled (non-closable dock widget)
        // Affects dock #0 when running: ./bin/qtwidgets_dockwidgets -n -p
        m_controller->setHideDisabledButtons(KDDockWidgets::TitleBarButtonType::Close);

        // But if you do override init(), never forget to call the base method:
        KDDockWidgets::QtWidgets::TitleBar::init();
    }

private:
    KDDockWidgets::Core::TitleBar *const m_controller;
};

MyTitleBar::~MyTitleBar() = default;

// Inheriting from SeparatorWidget instead of Separator as it handles moving and mouse cursor
// changing
class MySeparator : public KDDockWidgets::QtWidgets::Separator
{
public:
    explicit MySeparator(KDDockWidgets::Core::Separator *controller, KDDockWidgets::Core::View *parent)
        : KDDockWidgets::QtWidgets::Separator(controller, parent)
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

KDDockWidgets::Core::View *
CustomWidgetFactory::createTitleBar(KDDockWidgets::Core::TitleBar *controller,
                                    KDDockWidgets::Core::View *parent) const
{
    // Feel free to return MyTitleBar_CSS here instead, but just for education purposes!
    return new MyTitleBar(controller, parent);
}

KDDockWidgets::Core::View *
CustomWidgetFactory::createSeparator(KDDockWidgets::Core::Separator *controller,
                                     KDDockWidgets::Core::View *parent) const
{
    return new MySeparator(controller, parent);
}


KDDockWidgets::Core::View *CustomWidgetFactory::createGroup(KDDockWidgets::Core::Group *controller, KDDockWidgets::Core::View *parent) const
{
    // If you want a different styling, just inherit from QtWidgets::Group() and return it here
    return new KDDockWidgets::QtWidgets::Group(controller, KDDockWidgets::QtCommon::View_qt::asQWidget(parent));
}
