/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief The GUI counterpart of Frame.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "FrameQuick_p.h"
#include "Config.h"

#include <QDebug>

using namespace KDDockWidgets;

FrameQuick::FrameQuick(QWidgetAdapter *parent, FrameOptions options)
    : Frame(parent, options)
    , m_dockWidgetModel(new DockWidgetModel(this))
{
    connect(m_dockWidgetModel, &DockWidgetModel::countChanged,
            this, &FrameQuick::onDockWidgetCountChanged);

    connect(this, &QWidgetAdapter::geometryUpdated, this, &Frame::layoutInvalidated);

    QQmlComponent component(Config::self().qmlEngine(),
                            QUrl(QStringLiteral("qrc:/kddockwidgets/private/quick/qml/Frame.qml")));

    auto visualItem = static_cast<QQuickItem*>(component.create());

    if (!visualItem) {
        qWarning() << Q_FUNC_INFO << "Failed to create item" << component.errorString();
        return;
    }

    visualItem->setProperty("frameCpp", QVariant::fromValue(this));
    visualItem->setParentItem(this);
    visualItem->setParent(this);
}

DockWidgetModel *FrameQuick::dockWidgetModel() const
{
    return m_dockWidgetModel;
}

void FrameQuick::removeWidget_impl(DockWidgetBase *dw)
{
    m_dockWidgetModel->remove(dw);
    disconnect(m_connections.take(dw));
}

int FrameQuick::indexOfDockWidget_impl(DockWidgetBase *dw)
{
    return m_dockWidgetModel->indexOf(dw);
}

int FrameQuick::currentIndex_impl() const
{
    if (!m_currentDockWidget)
        return -1;

    return m_dockWidgetModel->indexOf(m_currentDockWidget);
}

void FrameQuick::setCurrentTabIndex_impl(int index)
{
    m_currentDockWidget = dockWidgetAt(index);
}

void FrameQuick::setCurrentDockWidget_impl(DockWidgetBase *dw)
{
    if (dw && !m_dockWidgetModel->contains(dw)) {
        qWarning() << Q_FUNC_INFO << "Shouldn't happen";
        return;
    }

    m_currentDockWidget = dw;
}

void FrameQuick::insertDockWidget_impl(DockWidgetBase *dw, int index)
{
    QPointer<Frame> oldFrame = dw->frame();
    if (m_dockWidgetModel->insert(dw, index)) {
        dw->setParent(m_stackLayout);

        QMetaObject::Connection conn = connect(dw, &DockWidgetBase::parentChanged, this, [dw, this] {
            if (dw->parent() != m_stackLayout)
                removeWidget_impl(dw);
        });

        m_connections[dw] = conn;

        if (!m_currentDockWidget)
            m_currentDockWidget = dw;

        if (oldFrame && oldFrame->beingDeletedLater()) {
            // give it a push and delete it immediately.
            // Having too many deleteLater() puts us in an inconsistent state. For example if LayoutSaver::saveState()
            // would to be called while the Frame hadn't been deleted yet it would count with that frame unless hacks.
            // Also the unit-tests are full of waitForDeleted() due to deleteLater.

            // Ideally we would just remove the deleteLater from frame.cpp, but QTabWidget::insertTab()
            // would crash, as it accesses the old tab-widget we're stealing from

            delete oldFrame;
        }
    }
}

DockWidgetBase *FrameQuick::dockWidgetAt_impl(int index) const
{
    return m_dockWidgetModel->dockWidgetAt(index);
}

DockWidgetBase *FrameQuick::currentDockWidget_impl() const
{
    return m_currentDockWidget;
}

int FrameQuick::dockWidgetCount_impl() const
{
    return m_dockWidgetModel->count();
}

void FrameQuick::renameTab(int, const QString &)
{
    // Not needed for QtQuick. Our model reacts to titleChanged()
}

void FrameQuick::setStackLayout(QQuickItem *stackLayout)
{
    if (m_stackLayout || !stackLayout) {
        qWarning() << Q_FUNC_INFO << "Shouldn't happen";
        return;
    }

    m_stackLayout = stackLayout;
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

    DockWidgetBase *dw = m_dockWidgets.at(row);

    switch (role) {
    case Role_Title:
        return dw->title();
    }

    return {};
}

DockWidgetBase *DockWidgetModel::dockWidgetAt(int index) const
{
    if (index < 0 || index >= m_dockWidgets.size()) {
        // Can happen. Benign.
        return nullptr;
    }

    return m_dockWidgets[index];
}

bool DockWidgetModel::contains(DockWidgetBase *dw) const
{
    return m_dockWidgets.contains(dw);
}

QHash<int, QByteArray> DockWidgetModel::roleNames() const
{
    return { {Role_Title, "title"} };
}

void DockWidgetModel::emitDataChangedFor(DockWidgetBase *dw)
{
    const int row = indexOf(dw);
    if (row == -1) {
        qWarning() << Q_FUNC_INFO << "Couldn't find" << dw;
    } else {
        QModelIndex index = this->index(row, 0);
        Q_EMIT dataChanged(index, index);
    }
}

void DockWidgetModel::remove(DockWidgetBase *dw)
{
    const int row = indexOf(dw);
    if (row == -1) {
        qWarning() << Q_FUNC_INFO << "Nothing to remove" << dw;
    } else {
        const auto connections = m_connections.take(dw);
        for (QMetaObject::Connection conn : connections)
            disconnect(conn);

        beginRemoveRows(QModelIndex(), row, row);
        m_dockWidgets.removeOne(dw);
        endRemoveRows();

        Q_EMIT countChanged();
    }
}

int DockWidgetModel::indexOf(DockWidgetBase *dw)
{
    return m_dockWidgets.indexOf(dw);
}

bool DockWidgetModel::insert(DockWidgetBase *dw, int index)
{
    if (m_dockWidgets.contains(dw)) {
        qWarning() << Q_FUNC_INFO << "Shouldn't happen";
        return false;
    }

    QMetaObject::Connection conn = connect(dw, &DockWidgetBase::titleChanged, this, [dw, this] {
        emitDataChangedFor(dw);
    });

    m_connections[dw] = { conn };

    beginInsertRows(QModelIndex(), index, index);
    m_dockWidgets.insert(index, dw);
    endInsertRows();

    Q_EMIT countChanged();
    return true;
}
