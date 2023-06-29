/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TitleBar.h"

#include "core/DragController_p.h"

#include "kddockwidgets/core/Group.h"
#include "kddockwidgets/core/FloatingWindow.h"
#include "kddockwidgets/core/TitleBar.h"

#include "core/Logging_p.h"
#include "core/WindowBeingDragged_p.h"
#include "core/Utils_p.h"
#include "core/TitleBar_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::QtQuick;


TitleBar::TitleBar(Core::TitleBar *controller, QQuickItem *parent)
    : View(controller, Core::ViewType::TitleBar, parent)
    , Core::TitleBarViewInterface(controller)
{
    setFixedHeight(30);
}

TitleBar::~TitleBar()
{
}

void TitleBar::init()
{
    // QML interface signals
    m_titleBar->dptr()->titleChanged.connect([this] { titleChanged(); });
    m_titleBar->dptr()->iconChanged.connect([this] { iconChanged(); });
    m_titleBar->dptr()->isFocusedChanged.connect([this] { isFocusedChanged(); });
    m_titleBar->dptr()->closeButtonEnabledChanged.connect([this](bool enabled) { closeButtonEnabledChanged(enabled); });
    m_titleBar->dptr()->floatButtonVisibleChanged.connect([this](bool visible) { floatButtonVisibleChanged(visible); });
    m_titleBar->dptr()->floatButtonToolTipChanged.connect([this](const QString &text) { floatButtonToolTipChanged(text); });
    m_titleBar->dptr()->numDockWidgetsChanged.connect([this] { numDockWidgetsChanged(); });
    m_titleBar->dptr()->maximizeButtonChanged.connect([this](bool visible) { maximizeButtonVisibleChanged(visible); });
    m_titleBar->dptr()->minimizeButtonChanged.connect([this](bool visible) { minimizeButtonVisibleChanged(visible); });
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
