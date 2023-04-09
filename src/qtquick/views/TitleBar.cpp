/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TitleBar.h"

#include "private/DragController_p.h"

#include "kddockwidgets/core/Group.h"
#include "kddockwidgets/core/FloatingWindow.h"
#include "kddockwidgets/core/TitleBar.h"

#include "private/Logging_p.h"
#include "private/WindowBeingDragged_p.h"
#include "private/Utils_p.h"


using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;
using namespace KDDockWidgets::qtquick;


TitleBar::TitleBar(Core::TitleBar *controller, QQuickItem *parent)
    : View_qtquick(controller, Core::ViewType::TitleBar, parent)
    , Views::TitleBarViewInterface(controller)
{
    setFixedHeight(30);
}

TitleBar::~TitleBar()
{
}

void TitleBar::init()
{
    // QML interface signals
    connect(m_titleBar, &Core::TitleBar::titleChanged, this,
            &TitleBar::titleChanged);
    connect(m_titleBar, &Core::TitleBar::iconChanged, this, &TitleBar::iconChanged);
    connect(m_titleBar, &Core::TitleBar::isFocusedChanged, this,
            &TitleBar::isFocusedChanged);
    connect(m_titleBar, &Core::TitleBar::closeButtonEnabledChanged, this,
            &TitleBar::closeButtonEnabledChanged);
    connect(m_titleBar, &Core::TitleBar::floatButtonVisibleChanged, this,
            &TitleBar::floatButtonVisibleChanged);
    connect(m_titleBar, &Core::TitleBar::floatButtonToolTipChanged, this,
            &TitleBar::floatButtonToolTipChanged);
    connect(m_titleBar, &Core::TitleBar::numDockWidgetsChanged, this,
            &TitleBar::numDockWidgetsChanged);
    connect(m_titleBar, &Core::TitleBar::maximizeButtonChanged, this,
            &TitleBar::maximizeButtonVisibleChanged);
    connect(m_titleBar, &Core::TitleBar::minimizeButtonChanged, this,
            &TitleBar::minimizeButtonVisibleChanged);
}

#ifdef DOCKS_DEVELOPER_MODE

bool TitleBar::isCloseButtonEnabled() const
{
    if (QQuickItem *button = closeButton())
        return button->isEnabled();
    return false;
}

bool TitleBar::isCloseButtonVisible() const
{
    if (QQuickItem *button = closeButton())
        return button->isVisible();

    return true;
}

bool TitleBar::isFloatButtonVisible() const
{
    if (QQuickItem *button = floatButton())
        return button->isVisible();

    return true;
}

#endif

QQuickItem *TitleBar::titleBarQmlItem() const
{
    return m_titleBarQmlItem;
}

QQuickItem *TitleBar::titleBarMouseArea() const
{
    if (m_titleBarQmlItem)
        return m_titleBarQmlItem->property("mouseAreaForTests").value<QQuickItem *>();

    return nullptr;
}

void TitleBar::setTitleBarQmlItem(QQuickItem *item)
{
    if (item != m_titleBarQmlItem) {
        m_titleBarQmlItem = item;
        Q_EMIT titleBarQmlItemChanged();
    }
}

QQuickItem *TitleBar::floatButton() const
{
    return m_titleBarQmlItem ? m_titleBarQmlItem->property("floatButton").value<QQuickItem *>()
                             : nullptr;
}

QQuickItem *TitleBar::closeButton() const
{
    return m_titleBarQmlItem ? m_titleBarQmlItem->property("closeButton").value<QQuickItem *>()
                             : nullptr;
}

bool TitleBar::isFocused() const
{
    return m_titleBar->isFocused();
}

bool TitleBar::floatButtonVisible() const
{
    return m_titleBar->floatButtonVisible();
}

bool TitleBar::minimizeButtonVisible() const
{
    return m_titleBar->supportsMinimizeButton();
}

bool TitleBar::maximizeButtonVisible() const
{
    return m_titleBar->maximizeButtonVisible();
}

bool TitleBar::maximizeUsesRestoreIcon() const
{
    return m_titleBar->maximizeButtonType() == TitleBarButtonType::Normal;
}

bool TitleBar::closeButtonEnabled() const
{
    return m_titleBar->closeButtonEnabled();
}

QString TitleBar::floatButtonToolTip() const
{
    return m_titleBar->floatButtonToolTip();
}

bool TitleBar::hasIcon() const
{
    return m_titleBar->hasIcon();
}

QString TitleBar::title() const
{
    return m_titleBar->title();
}

void TitleBar::setCloseButtonEnabled(bool is)
{
    m_titleBar->setCloseButtonEnabled(is);
}

void TitleBar::setFloatButtonVisible(bool is)
{
    m_titleBar->setFloatButtonVisible(is);
}

bool TitleBar::onDoubleClicked()
{
    return m_titleBar->onDoubleClicked();
}

void TitleBar::onCloseClicked()
{
    m_titleBar->onCloseClicked();
}

void TitleBar::onFloatClicked()
{
    m_titleBar->onFloatClicked();
}

void TitleBar::onMaximizeClicked()
{
    m_titleBar->onMaximizeClicked();
}

void TitleBar::onMinimizeClicked()
{
    m_titleBar->onMinimizeClicked();
}

void TitleBar::onAutoHideClicked()
{
    m_titleBar->onAutoHideClicked();
}

void TitleBar::toggleMaximized()
{
    m_titleBar->toggleMaximized();
}
