/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

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
#include "Stack_qtquick.h"
#include "kddockwidgets/controllers/TabBar.h"
#include "kddockwidgets/controllers/Stack.h"
#include "Stack_qtquick.h"

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
    m_tabBarAutoHideChanged = m_tabBar->stack()->tabBarAutoHideChanged.connect(
        [this] { Q_EMIT tabBarAutoHideChanged(); });
}

int TabBar_qtquick::tabAt(QPoint localPt) const
{
    // QtQuick's TabBar doesn't provide any API for this.
    // Also note that the ListView's flickable has bogus contentX, so instead just iterate through
    // the tabs

    if (!m_tabBarQmlItem) {
        qWarning() << Q_FUNC_INFO << "No visual tab bar item yet";
        return -1;
    }

    const QPointF globalPos = m_tabBarQmlItem->mapToGlobal(localPt);

    QVariant index;
    const bool res =
        QMetaObject::invokeMethod(m_tabBarQmlItem, "getTabIndexAtPosition",
                                  Q_RETURN_ARG(QVariant, index), Q_ARG(QVariant, globalPos));

    if (res)
        return index.toInt();

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
            m_tabBarQmlItem->setProperty("currentTabIndex", tabAt(me->pos()));
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
    QVariant result;
    const bool res = QMetaObject::invokeMethod(
        m_tabBarQmlItem, "getTabAtIndex", Q_RETURN_ARG(QVariant, result), Q_ARG(QVariant, index));

    if (res)
        return result.value<QQuickItem *>();

    qWarning() << Q_FUNC_INFO << "Could not find tab for index" << index;
    return nullptr;
}

void TabBar_qtquick::moveTabTo(int from, int to)
{
    Q_UNUSED(from);
    Q_UNUSED(to);
    // Not implemented yet
}

bool TabBar_qtquick::tabsAreMovable() const
{
    return false;
}

bool TabBar_qtquick::tabBarAutoHide() const
{
    return m_tabBar->stack()->tabBarAutoHide();
}

Stack_qtquick *TabBar_qtquick::stackView() const
{
    if (auto tw = dynamic_cast<Stack_qtquick *>(m_tabBar->stack()->view()))
        return tw;

    qWarning() << Q_FUNC_INFO << "Unexpected null Stack_qtquick";
    return nullptr;
}

void TabBar_qtquick::setCurrentIndex(int index)
{
    stackView()->dockWidgetModel()->setCurrentIndex(index);
}

int TabBar_qtquick::numDockWidgets() const
{
    return stackView()->dockWidgetModel()->count();
}

Controllers::DockWidget *TabBar_qtquick::dockWidgetAt(int index) const
{
    return stackView()->dockWidgetModel()->dockWidgetAt(index);
}

int TabBar_qtquick::indexOfDockWidget(const Controllers::DockWidget *dw) const
{
    return stackView()->dockWidgetModel()->indexOf(dw);
}

void TabBar_qtquick::renameTab(int index, const QString &)
{
    Q_UNUSED(index);
    qWarning() << Q_FUNC_INFO << "Not implemented";
}

void TabBar_qtquick::changeTabIcon(int index, const QIcon &)
{
    Q_UNUSED(index);
    qWarning() << Q_FUNC_INFO << "Not implemented";
}

void TabBar_qtquick::removeDockWidget(Controllers::DockWidget *dw)
{
    stackView()->dockWidgetModel()->remove(dw);
}

bool TabBar_qtquick::insertDockWidget(int index, Controllers::DockWidget *dw, const QIcon &icon,
                                      const QString &title)
{
    Q_UNUSED(title); // TODO
    Q_UNUSED(icon); // TODO

    return stackView()->dockWidgetModel()->insert(dw, index);
}
