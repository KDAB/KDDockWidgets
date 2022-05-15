/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Stack_qtquick.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"

#include "controllers/Frame.h"

#include <QDebug>
#include <QScopedValueRollback>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

Stack_qtquick::Stack_qtquick(Controllers::Stack *controller,
                             Controllers::Frame *parent)
    : View_qtquick(controller, Type::Stack, Views::asQQuickItem(parent))
    , m_dockWidgetModel(new DockWidgetModel(this))
    // , m_tabBar(Config::self().frameworkWidgetFactory()->createTabBar(this))
    , m_stack(controller)
{
    connect(m_dockWidgetModel, &DockWidgetModel::countChanged, this,
            [this] {
                if (m_currentDockWidget && indexOfDockWidget(m_currentDockWidget) == -1) {
                    // The current dock widget was removed, set the first one as current
                    if (numDockWidgets() > 0)
                        setCurrentDockWidget(0);
                }

                Q_EMIT countChanged(); });
}

// TabBar *Stack_qtquick::tabBar() const
// {
//     return m_tabBar;
// }

void Stack_qtquick::setDocumentMode(bool)
{
    qDebug() << "Not implemented";
}

int Stack_qtquick::numDockWidgets() const
{
    return m_dockWidgetModel->count();
}

void Stack_qtquick::removeDockWidget(Controllers::DockWidget *dw)
{
    m_dockWidgetModel->remove(dw);
}

int Stack_qtquick::indexOfDockWidget(const Controllers::DockWidget *dw) const
{
    return m_dockWidgetModel->indexOf(dw);
}

bool Stack_qtquick::isPositionDraggable(QPoint p) const
{
    Q_UNUSED(p);
    return true;
}

void Stack_qtquick::setCurrentDockWidget(int index)
{
    Controllers::DockWidget *dw = dockwidgetAt(index);

    if (m_currentDockWidget != dw) {
        m_currentDockWidget = dw;
        Q_EMIT currentDockWidgetChanged(dw);
        Q_EMIT currentTabChanged(index);
    }
}

QObject *Stack_qtquick::tabBarObj() const
{
    // TODOv2
    return nullptr;
    // return m_tabBar->asWidget();
}

Controllers::DockWidget *Stack_qtquick::currentDockWidget() const
{
    return m_currentDockWidget;
}

bool Stack_qtquick::insertDockWidget(int index, Controllers::DockWidget *dw, const QIcon &, const QString &title)
{
    Q_UNUSED(title); // todo
    return m_dockWidgetModel->insert(dw, index);
}

void Stack_qtquick::setTabBarAutoHide(bool)
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
}

void Stack_qtquick::renameTab(int index, const QString &)
{
    Q_UNUSED(index);
    qWarning() << Q_FUNC_INFO << "Not implemented";
}

void Stack_qtquick::changeTabIcon(int index, const QIcon &)
{
    Q_UNUSED(index);
    qWarning() << Q_FUNC_INFO << "Not implemented";
}

Controllers::DockWidget *Stack_qtquick::dockwidgetAt(int index) const
{
    return m_dockWidgetModel->dockWidgetAt(index);
}

int Stack_qtquick::currentIndex() const
{
    if (!m_currentDockWidget)
        return -1;

    const int index = indexOfDockWidget(m_currentDockWidget);

    if (index == -1)
        qWarning() << Q_FUNC_INFO << "Unexpected null index for" << m_currentDockWidget << this
                   << "; count=" << m_dockWidgetModel->count();

    return index;
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
                       << static_cast<void *>(dw); // Print address only, as it might be deleted already
        }
    } else {
        const auto connections = m_connections.take(dw);
        for (const QMetaObject::Connection &conn : connections)
            disconnect(conn);

        beginRemoveRows(QModelIndex(), row, row);
        m_dockWidgets.removeOne(dw);
        endRemoveRows();

        Q_EMIT countChanged();
    }
}

int DockWidgetModel::indexOf(const Controllers::DockWidget *dw)
{
    return m_dockWidgets.indexOf(const_cast<Controllers::DockWidget *>(dw));
}

bool DockWidgetModel::insert(Controllers::DockWidget *dw, int index)
{
    if (m_dockWidgets.contains(dw)) {
        qWarning() << Q_FUNC_INFO << "Shouldn't happen";
        return false;
    }

    QMetaObject::Connection conn = connect(dw, &Controllers::DockWidget::titleChanged, this, [dw, this] {
        emitDataChangedFor(dw);
    });

    QMetaObject::Connection conn2 = connect(dw, &QObject::destroyed, this, [dw, this] {
        remove(dw);
    });

    m_connections[dw] = { conn, conn2 };

    beginInsertRows(QModelIndex(), index, index);
    m_dockWidgets.insert(index, dw);
    endInsertRows();

    Q_EMIT countChanged();
    return true;
}
