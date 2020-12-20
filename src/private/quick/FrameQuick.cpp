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
#include "FrameworkWidgetFactory.h"
#include "TabWidgetQuick_p.h"

#include <QDebug>

using namespace KDDockWidgets;

FrameQuick::FrameQuick(QWidgetAdapter *parent, FrameOptions options)
    : Frame(parent, options)
    , m_tabWidget(static_cast<TabWidgetQuick*>(Config::self().frameworkWidgetFactory()->createTabWidget(this)))
{
    connect(m_tabWidget, &TabWidgetQuick::countChanged,
            this, &FrameQuick::onDockWidgetCountChanged);

    connect(m_tabWidget, &TabWidgetQuick::countChanged,
            this, &FrameQuick::updateConstriants);

    connect(m_tabWidget, &TabWidgetQuick::currentDockWidgetChanged,
            this, &FrameQuick::currentDockWidgetChanged);

    connect(this, &QWidgetAdapter::geometryUpdated, this, &Frame::layoutInvalidated);

    QQmlComponent component(Config::self().qmlEngine(),
                            QUrl(QStringLiteral("qrc:/kddockwidgets/private/quick/qml/Frame.qml")));

    m_visualItem = static_cast<QQuickItem*>(component.create());

    if (!m_visualItem) {
        qWarning() << Q_FUNC_INFO << "Failed to create item" << component.errorString();
        return;
    }

    m_visualItem->setProperty("frameCpp", QVariant::fromValue(this));
    m_visualItem->setParentItem(this);
    m_visualItem->setParent(this);
}

FrameQuick::~FrameQuick()
{
    {
        const DockWidgetBase::List docks = dockWidgets();

        // The QML item must be deleted with deleteLater(), has we might be currently with its mouse
        // handler in the stack. QML doesn't support it being deleted in that case.
        // So unparent it and deleteLater().
        m_visualItem->setParent(nullptr);
        m_visualItem->deleteLater();

        qDeleteAll(docks);
    }
}

void FrameQuick::updateConstriants()
{
    // QtQuick doesn't have layouts, so we need to do constraint propagation manually

    setProperty("kddockwidgets_min_size", minimumSize());
    setProperty("kddockwidgets_max_size", maximumSize());

    Q_EMIT layoutInvalidated();
}

DockWidgetModel *FrameQuick::dockWidgetModel() const
{
    return m_tabWidget->dockWidgetModel();
}

void FrameQuick::removeWidget_impl(DockWidgetBase *dw)
{
    m_tabWidget->removeDockWidget(dw);
    disconnect(m_connections.take(dw));
}

int FrameQuick::indexOfDockWidget_impl(DockWidgetBase *dw)
{
    return m_tabWidget->indexOfDockWidget(dw);
}

int FrameQuick::currentIndex_impl() const
{
    return m_tabWidget->currentIndex();
}

void FrameQuick::setCurrentTabIndex_impl(int index)
{
    setCurrentDockWidget_impl(dockWidgetAt(index));
}

void FrameQuick::setCurrentDockWidget_impl(DockWidgetBase *dw)
{
    m_tabWidget->setCurrentDockWidget(dw);
}

void FrameQuick::insertDockWidget_impl(DockWidgetBase *dw, int index)
{
    QPointer<Frame> oldFrame = dw->frame();
    if (m_tabWidget->insertDockWidget(index, dw, {}, {})) {
        dw->setParent(m_stackLayout);

        QMetaObject::Connection conn = connect(dw, &DockWidgetBase::parentChanged, this, [dw, this] {
            if (dw->parent() != m_stackLayout)
                removeWidget_impl(dw);
        });

        m_connections[dw] = conn;
        setCurrentDockWidget_impl(dw);

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
    return m_tabWidget->dockwidgetAt(index);
}

DockWidgetBase *FrameQuick::currentDockWidget_impl() const
{
    return m_tabWidget->currentDockWidget();
}

int FrameQuick::dockWidgetCount_impl() const
{
    return m_tabWidget->numDockWidgets();
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

QSize FrameQuick::minimumSize() const
{
    const QSize contentsSize = dockWidgetsMinSize();
    return contentsSize + QSize(0, nonContentsHeight());
}

QSize FrameQuick::maximumSize() const
{
    return Frame::maximumSize();
}

int FrameQuick::nonContentsHeight() const
{
    return m_visualItem->property("nonContentsHeight").toInt();
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
        qWarning() << Q_FUNC_INFO << "Nothing to remove"
                   << static_cast<void*>(dw); // Print address only, as it might be deleted already
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
