/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TitleBar_qtquick.h"

#include "private/DragController_p.h"

#include "kddockwidgets/controllers/Group.h"
#include "kddockwidgets/controllers/FloatingWindow.h"
#include "kddockwidgets/controllers/TitleBar.h"

#include "private/Logging_p.h"
#include "private/WindowBeingDragged_p.h"
#include "private/Utils_p.h"


using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;


TitleBar_qtquick::TitleBar_qtquick(Controllers::TitleBar *controller, QQuickItem *parent)
    : View_qtquick(controller, Type::TitleBar, parent)
    , Views::TitleBarViewInterface(controller)
{
    setFixedHeight(30);
}

TitleBar_qtquick::~TitleBar_qtquick()
{
}

void TitleBar_qtquick::init()
{
    // QML interface signals
    connect(m_titleBar, &Controllers::TitleBar::titleChanged, this,
            &TitleBar_qtquick::titleChanged);
    connect(m_titleBar, &Controllers::TitleBar::iconChanged, this, &TitleBar_qtquick::iconChanged);
    connect(m_titleBar, &Controllers::TitleBar::isFocusedChanged, this,
            &TitleBar_qtquick::isFocusedChanged);
    connect(m_titleBar, &Controllers::TitleBar::closeButtonEnabledChanged, this,
            &TitleBar_qtquick::closeButtonEnabledChanged);
    connect(m_titleBar, &Controllers::TitleBar::floatButtonVisibleChanged, this,
            &TitleBar_qtquick::floatButtonVisibleChanged);
    connect(m_titleBar, &Controllers::TitleBar::floatButtonToolTipChanged, this,
            &TitleBar_qtquick::floatButtonToolTipChanged);
    connect(m_titleBar, &Controllers::TitleBar::numDockWidgetsChanged, this,
            &TitleBar_qtquick::numDockWidgetsChanged);
    connect(m_titleBar, &Controllers::TitleBar::maximizeButtonChanged, this,
            &TitleBar_qtquick::maximizeButtonVisibleChanged);
}

#ifdef DOCKS_DEVELOPER_MODE

bool TitleBar_qtquick::isCloseButtonEnabled() const
{
    if (QQuickItem *button = closeButton())
        return button->isEnabled();
    return false;
}

bool TitleBar_qtquick::isCloseButtonVisible() const
{
    if (QQuickItem *button = closeButton())
        return button->isVisible();

    return true;
}

bool TitleBar_qtquick::isFloatButtonVisible() const
{
    if (QQuickItem *button = floatButton())
        return button->isVisible();

    return true;
}

#endif

QQuickItem *TitleBar_qtquick::titleBarQmlItem() const
{
    return m_titleBarQmlItem;
}

QQuickItem *TitleBar_qtquick::titleBarMouseArea() const
{
    if (m_titleBarQmlItem)
        return m_titleBarQmlItem->property("mouseAreaForTests").value<QQuickItem *>();

    return nullptr;
}

void TitleBar_qtquick::setTitleBarQmlItem(QQuickItem *item)
{
    if (item != m_titleBarQmlItem) {
        m_titleBarQmlItem = item;
        Q_EMIT titleBarQmlItemChanged();
    }
}

QQuickItem *TitleBar_qtquick::floatButton() const
{
    return m_titleBarQmlItem ? m_titleBarQmlItem->property("floatButton").value<QQuickItem *>()
                             : nullptr;
}

QQuickItem *TitleBar_qtquick::closeButton() const
{
    return m_titleBarQmlItem ? m_titleBarQmlItem->property("closeButton").value<QQuickItem *>()
                             : nullptr;
}

bool TitleBar_qtquick::isFocused() const
{
    return m_titleBar->isFocused();
}

bool TitleBar_qtquick::floatButtonVisible() const
{
    return m_titleBar->floatButtonVisible();
}

bool TitleBar_qtquick::maximizeButtonVisible() const
{
    return m_titleBar->maximizeButtonVisible();
}

bool TitleBar_qtquick::maximizeUsesRestoreIcon() const
{
    return m_titleBar->maximizeButtonType() == TitleBarButtonType::Normal;
}

bool TitleBar_qtquick::closeButtonEnabled() const
{
    return m_titleBar->closeButtonEnabled();
}

QString TitleBar_qtquick::floatButtonToolTip() const
{
    return m_titleBar->floatButtonToolTip();
}

bool TitleBar_qtquick::hasIcon() const
{
    return m_titleBar->hasIcon();
}

QString TitleBar_qtquick::title() const
{
    return m_titleBar->title();
}

void TitleBar_qtquick::setCloseButtonEnabled(bool is)
{
    m_titleBar->setCloseButtonEnabled(is);
}

void TitleBar_qtquick::setFloatButtonVisible(bool is)
{
    m_titleBar->setFloatButtonVisible(is);
}

bool TitleBar_qtquick::onDoubleClicked()
{
    return m_titleBar->onDoubleClicked();
}

void TitleBar_qtquick::onCloseClicked()
{
    m_titleBar->onCloseClicked();
}

void TitleBar_qtquick::onFloatClicked()
{
    m_titleBar->onFloatClicked();
}

void TitleBar_qtquick::onMaximizeClicked()
{
    m_titleBar->onMaximizeClicked();
}

void TitleBar_qtquick::onMinimizeClicked()
{
    m_titleBar->onMinimizeClicked();
}

void TitleBar_qtquick::onAutoHideClicked()
{
    m_titleBar->onAutoHideClicked();
}

void TitleBar_qtquick::toggleMaximized()
{
    m_titleBar->toggleMaximized();
}
