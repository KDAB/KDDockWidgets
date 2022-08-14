/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Stack_qtquick.h"
#include "Config.h"
#include "kddockwidgets/ViewFactory.h"

#include "kddockwidgets/controllers/Stack.h"
#include "kddockwidgets/controllers/Group.h"
#include "kddockwidgets/controllers/TabBar.h"

#include <QDebug>
#include <QScopedValueRollback>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

Stack_qtquick::Stack_qtquick(Controllers::Stack *controller, QQuickItem *parent)
    : View_qtquick(controller, Type::Stack, parent)
    , StackViewInterface(controller)
    , m_dockWidgetModel(new DockWidgetModel(this))
{
    connect(m_dockWidgetModel, &DockWidgetModel::countChanged, this,
            [this] { Q_EMIT m_stack->tabBar()->countChanged(); });
}

void Stack_qtquick::init()
{
    m_dockWidgetModel->m_tabBar = m_stack->tabBar();
    m_tabBarAutoHideChanged =
        m_stack->tabBarAutoHideChanged.connect([this] { Q_EMIT tabBarAutoHideChanged(); });

    Q_EMIT tabBarChanged();
}

Controllers::Stack *Stack_qtquick::stack() const
{
    return m_stack;
}

QObject *Stack_qtquick::tabBarViewObj() const
{
    return View_qt::asQObject(m_stack->tabBar()->view());
}

Controllers::DockWidget *Stack_qtquick::currentDockWidget() const
{
    return m_dockWidgetModel->currentDockWidget();
}

bool Stack_qtquick::tabBarAutoHide() const
{
    return m_stack->tabBarAutoHide();
}

DockWidgetModel *Stack_qtquick::dockWidgetModel() const
{
    return m_dockWidgetModel;
}

DockWidgetModel::DockWidgetModel(QObject *parent)
    : QAbstractListModel(parent)
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
    m_currentDockWidget = dw;
    setCurrentIndex(indexOf(dw));
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
    const bool wasCurrent = dw == m_currentDockWidget;

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

        if (wasCurrent) {
            const bool isLast = row == count() - 1;
            const int newCurrentIndex = isLast ? row - 1 : row + 1;
            if (newCurrentIndex >= 0)
                setCurrentIndex(newCurrentIndex);
        }

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
