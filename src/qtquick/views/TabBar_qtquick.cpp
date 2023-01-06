/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
#include "Stack_qtquick.h"
#include "kddockwidgets/controllers/DockWidget_p.h"
#include "kddockwidgets/controllers/TabBar.h"
#include "kddockwidgets/controllers/Stack.h"

#include <QMetaObject>
#include <QMouseEvent>
#include <QDebug>
#include <QScopedValueRollback>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

TabBar_qtquick::TabBar_qtquick(Controllers::TabBar *controller, QQuickItem *parent)
    : View_qtquick(controller, Type::TabBar, parent)
    , TabBarViewInterface(controller)
    , m_dockWidgetModel(new DockWidgetModel(controller, this))
{
    connect(m_dockWidgetModel, &DockWidgetModel::countChanged, this,
            [controller] { Q_EMIT controller->countChanged(); });
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
    if (m_tabBarQmlItem == item) {
        qWarning() << Q_FUNC_INFO << "Should be called only once";
        return;
    }

    m_tabBarQmlItem = item;
    Q_EMIT tabBarQmlItemChanged();
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

QRect TabBar_qtquick::globalRectForTab(int index) const
{
    if (QQuickItem *item = tabAt(index)) {
        QRect r = item->boundingRect().toRect();
        r.moveTopLeft(item->mapToGlobal(r.topLeft()).toPoint());
        return r;
    }

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

            // Don't call base class, it might have been deleted
            return true;
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
    m_dockWidgetModel->setCurrentIndex(index);
}

void TabBar_qtquick::renameTab(int index, const QString &)
{
    Q_UNUSED(index);
    qDebug() << Q_FUNC_INFO << "Not implemented";
}

void TabBar_qtquick::changeTabIcon(int index, const QIcon &)
{
    Q_UNUSED(index);
    qDebug() << Q_FUNC_INFO << "Not implemented";
}

void TabBar_qtquick::removeDockWidget(Controllers::DockWidget *dw)
{
    m_dockWidgetModel->remove(dw);
}

void TabBar_qtquick::insertDockWidget(int index, Controllers::DockWidget *dw, const QIcon &icon,
                                      const QString &title)
{
    Q_UNUSED(title); // TODO
    Q_UNUSED(icon); // TODO

    m_dockWidgetModel->insert(dw, index);
}

DockWidgetModel *TabBar_qtquick::dockWidgetModel() const
{
    return m_dockWidgetModel;
}

void TabBar_qtquick::onHoverEvent(QHoverEvent *ev, QPoint globalPos)
{
    if (ev->type() == QEvent::HoverLeave) {
        setHoveredTabIndex(-1);
    } else {
        setHoveredTabIndex(indexForTabPos(globalPos));
    }
}

int TabBar_qtquick::indexForTabPos(QPoint globalPt) const
{
    const int count = m_dockWidgetModel->count();
    for (int i = 0; i < count; i++) {
        const QRect tabRect = globalRectForTab(i);
        if (tabRect.contains(globalPt))
            return i;
    }

    return -1;
}

void TabBar_qtquick::setHoveredTabIndex(int idx)
{
    if (idx == m_hoveredTabIndex)
        return;

    m_hoveredTabIndex = idx;
    Q_EMIT hoveredTabIndexChanged(idx);
}

int TabBar_qtquick::hoveredTabIndex() const
{
    return m_hoveredTabIndex;
}

DockWidgetModel::DockWidgetModel(Controllers::TabBar *tabBar, QObject *parent)
    : QAbstractListModel(parent)
    , m_tabBar(tabBar)
{
}

int DockWidgetModel::count() const
{
    return m_dockWidgets.size();
}

int DockWidgetModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_dockWidgets.size();
}

QVariant DockWidgetModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (row < 0 || row >= m_dockWidgets.size())
        return {};

    Controllers::DockWidget *dw = m_dockWidgets.at(row);

    switch (role) {
    case Role_Title:
        return dw->title();
    }

    return {};
}

Controllers::DockWidget *DockWidgetModel::dockWidgetAt(int index) const
{
    if (index < 0 || index >= m_dockWidgets.size()) {
        // Can happen. Benign.
        return nullptr;
    }

    return m_dockWidgets[index];
}

bool DockWidgetModel::contains(Controllers::DockWidget *dw) const
{
    return m_dockWidgets.contains(dw);
}

Controllers::DockWidget *DockWidgetModel::currentDockWidget() const
{
    return m_currentDockWidget;
}

void DockWidgetModel::setCurrentDockWidget(Controllers::DockWidget *dw)
{
    if (m_currentDockWidget)
        m_currentDockWidget->setVisible(false);

    m_currentDockWidget = dw;
    setCurrentIndex(indexOf(dw));
    if (m_currentDockWidget) {
        QScopedValueRollback<bool> guard(m_currentDockWidget->d->m_isSettingCurrent, true);
        m_currentDockWidget->setVisible(true);
    }
}

QHash<int, QByteArray> DockWidgetModel::roleNames() const
{
    return { { Role_Title, "title" } };
}

void DockWidgetModel::emitDataChangedFor(Controllers::DockWidget *dw)
{
    const int row = indexOf(dw);
    if (row == -1) {
        qWarning() << Q_FUNC_INFO << "Couldn't find" << dw;
    } else {
        QModelIndex index = this->index(row, 0);
        Q_EMIT dataChanged(index, index);
    }
}

void DockWidgetModel::remove(Controllers::DockWidget *dw)
{
    QScopedValueRollback<bool> guard(m_removeGuard, true);
    const int row = indexOf(dw);

    if (row == -1) {
        if (!m_removeGuard) {
            // can happen if there's reentrancy. Some user code reacting
            // to the signals and call remove for whatever reason.
            qWarning() << Q_FUNC_INFO << "Nothing to remove"
                       << static_cast<void *>(dw); // Print address only, as it might be deleted
                                                   // already
        }
    } else {
        const auto connections = m_connections.take(dw);
        for (const QMetaObject::Connection &conn : connections)
            disconnect(conn);

        beginRemoveRows(QModelIndex(), row, row);
        m_dockWidgets.removeOne(dw);
        endRemoveRows();

        Q_EMIT countChanged();
        Q_EMIT dockWidgetRemoved();
    }
}

int DockWidgetModel::indexOf(const Controllers::DockWidget *dw)
{
    return m_dockWidgets.indexOf(const_cast<Controllers::DockWidget *>(dw));
}

int DockWidgetModel::currentIndex() const
{
    if (!m_currentDockWidget)
        return -1;

    const int index = m_dockWidgets.indexOf(m_currentDockWidget);

    if (index == -1)
        qWarning() << Q_FUNC_INFO << "Unexpected null index for" << m_currentDockWidget << this
                   << "; count=" << count();

    return index;
}

void DockWidgetModel::setCurrentIndex(int index)
{
    Controllers::DockWidget *dw = dockWidgetAt(index);

    if (m_currentDockWidget != dw) {
        setCurrentDockWidget(dw);
        m_tabBar->setCurrentIndex(index);
    }
}

bool DockWidgetModel::insert(Controllers::DockWidget *dw, int index)
{
    if (m_dockWidgets.contains(dw)) {
        qWarning() << Q_FUNC_INFO << "Shouldn't happen";
        return false;
    }

    QMetaObject::Connection conn = connect(dw, &Controllers::DockWidget::titleChanged, this,
                                           [dw, this] { emitDataChangedFor(dw); });

    QMetaObject::Connection conn2 =
        connect(dw, &QObject::destroyed, this, [dw, this] { remove(dw); });

    m_connections[dw] = { conn, conn2 };

    beginInsertRows(QModelIndex(), index, index);
    m_dockWidgets.insert(index, dw);
    endInsertRows();

    Q_EMIT countChanged();
    return true;
}
