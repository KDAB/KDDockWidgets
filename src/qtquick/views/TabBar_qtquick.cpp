/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief Implements a QTabWidget derived class with support for docking and undocking
 * KDockWidget::DockWidget as tabs .
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "TabBar_qtquick.h"
#include "kddockwidgets/controllers/TabBar.h"
#include "kddockwidgets/controllers/Stack.h"

#include <QMetaObject>
#include <QMouseEvent>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

TabBar_qtquick::TabBar_qtquick(Controllers::TabBar *controller, QQuickItem *parent)
    : View_qtquick(controller, Type::TabBar, parent)
    , TabBarViewInterface(controller)
{
}

void TabBar_qtquick::init()
{
    m_tabBarAutoHideChanged = m_tabBar->stack()->tabBarAutoHideChanged.connect([this] {
        Q_EMIT tabBarAutoHideChanged();
    });
}

QHash<int, QQuickItem *> TabBar_qtquick::qmlTabs() const
{
    if (!m_tabBarQmlItem) {
        qWarning() << Q_FUNC_INFO << "No visual tab bar item yet" << this;
        return {};
    }

    /// Returns the list of QtQuickControls tabs in our tab bar
    QHash<int, QQuickItem *> tabs;

    if (QQuickItem *internalListView = listView()) {
        const auto childItems = internalListView->childItems();
        if (!childItems.isEmpty()) {
            for (QQuickItem *item : childItems.first()->childItems()) {
                bool ok = false;
                const int index = item->property("tabIndex").toInt(&ok);
                if (ok)
                    tabs.insert(index, item);
            }
        }
    } else {
        qWarning() << Q_FUNC_INFO << "Couldn't find the internal ListView";
    }

    return tabs;
}

int TabBar_qtquick::tabAt(QPoint localPt) const
{
    // QtQuick's TabBar doesn't provide any API for this.
    // Also note that the ListView's flickable has bogus contentX, so instead just iterate through the tabs

    if (!m_tabBarQmlItem) {
        qWarning() << Q_FUNC_INFO << "No visual tab bar item yet";
        return -1;
    }

    const QPointF globalPos = m_tabBarQmlItem->mapToGlobal(localPt);

    const QHash<int, QQuickItem *> tabs = qmlTabs();
    for (auto it = tabs.keyValueBegin(); it != tabs.keyValueEnd(); ++it) {
        QQuickItem *tab = it->second;
        if (tab->contains(tab->mapFromGlobal(globalPos))) {
            const int index = it->first;
            return index;
        }
    }

    return -1;
}

QQuickItem *TabBar_qtquick::tabBarQmlItem() const
{
    return m_tabBarQmlItem;
}

void TabBar_qtquick::setTabBarQmlItem(QQuickItem *item)
{
    m_tabBarQmlItem = item;
}

QString TabBar_qtquick::text(int index) const
{
    if (QQuickItem *item = tabAt(index))
        return item->property("text").toString();

    return {};
}

QRect TabBar_qtquick::rectForTab(int index) const
{
    if (QQuickItem *item = tabAt(index))
        return item->boundingRect().toRect();

    return {};
}

bool TabBar_qtquick::event(QEvent *ev)
{
    switch (ev->type()) {
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonPress: {
        if (m_tabBarQmlItem) {
            auto me = static_cast<QMouseEvent *>(ev);
            m_tabBarQmlItem->setProperty("currentIndex", tabAt(me->pos()));
            if (ev->type() == QEvent::MouseButtonPress)
                m_tabBar->onMousePress(me->pos());
            else
                m_tabBar->onMouseDoubleClick(me->pos());
        }

        break;
    }
    default:
        break;
    }

    return View_qtquick::event(ev);
}

QQuickItem *TabBar_qtquick::tabAt(int index) const
{
    const QHash<int, QQuickItem *> tabs = qmlTabs();
    return tabs.value(index, nullptr);
}

QQuickItem *TabBar_qtquick::listView() const
{
    // Returns the internal ListView of the TabBar
    if (!m_tabBarQmlItem) {
        qWarning() << Q_FUNC_INFO << "No visual tab bar item yet";
        return nullptr;
    }

    const QList<QQuickItem *> children = m_tabBarQmlItem->childItems();
    for (QQuickItem *child : children) {
        if (qstrcmp(child->metaObject()->className(), "QQuickListView") == 0)
            return child;
    }

    return nullptr;
}

void TabBar_qtquick::moveTabTo(int from, int to)
{
    Q_UNUSED(from);
    Q_UNUSED(to);
    // Not implemented yet
}

Controllers::DockWidget *TabBar_qtquick::currentDockWidget() const
{
    return nullptr;
}

bool TabBar_qtquick::tabsAreMovable() const
{
    return false;
}

bool TabBar_qtquick::tabBarAutoHide() const
{
    return m_tabBar->stack()->tabBarAutoHide();
}
