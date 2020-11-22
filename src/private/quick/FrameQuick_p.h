/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#ifndef KD_FRAME_QUICK_P_H
#define KD_FRAME_QUICK_P_H

#include "Frame_p.h"
#include "DockWidgetBase.h"

#include <QAbstractListModel>

class QQuickItem;

namespace KDDockWidgets {

class DockWidgetModel;

/**
 * @brief The GUI counterpart of Frame.
 */
class DOCKS_EXPORT FrameQuick : public Frame
{
    Q_OBJECT
    Q_PROPERTY(DockWidgetModel* dockWidgetModel READ dockWidgetModel CONSTANT)
public:
    explicit FrameQuick(QWidgetAdapter *parent = nullptr, FrameOptions = FrameOption::FrameOption_None);
    ~FrameQuick() override;
    DockWidgetModel *dockWidgetModel() const;

    /// @reimp
    QSize minimumSize() const override;

    /// @reimp
    QSize maximumSize() const override;

protected:
    void removeWidget_impl(DockWidgetBase *) override;
    int indexOfDockWidget_impl(DockWidgetBase *) override;
    int currentIndex_impl() const override;
    void setCurrentTabIndex_impl(int index) override;
    void setCurrentDockWidget_impl(DockWidgetBase *) override;
    void insertDockWidget_impl(DockWidgetBase *, int index) override;
    DockWidgetBase *dockWidgetAt_impl(int index) const override;
    DockWidgetBase *currentDockWidget_impl() const override;
    int dockWidgetCount_impl() const override;
    void renameTab(int index, const QString &) override;
    Q_INVOKABLE void setStackLayout(QQuickItem *);

Q_SIGNALS:
    void tabTitlesChanged();
private:
    int nonContentsHeight() const;
    QQuickItem *m_stackLayout = nullptr;
    QQuickItem *m_visualItem = nullptr;
    DockWidgetBase *m_currentDockWidget = nullptr;
    DockWidgetModel *const m_dockWidgetModel;
    QHash<DockWidgetBase *, QMetaObject::Connection> m_connections; // To make it easy to disconnect from lambdas
};

class DockWidgetModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role {
        Role_Title = Qt::UserRole
    };

    explicit DockWidgetModel(QObject *parent);
    int count() const;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    DockWidgetBase *dockWidgetAt(int index) const;
    void remove(DockWidgetBase *);
    int indexOf(DockWidgetBase *);
    bool insert(DockWidgetBase *dw, int index);
    bool contains(DockWidgetBase *dw) const;
protected:
    QHash<int, QByteArray> roleNames() const override;
Q_SIGNALS:
    void countChanged();
private:
    void emitDataChangedFor(DockWidgetBase *);
    DockWidgetBase::List m_dockWidgets;
    QHash<DockWidgetBase *, QVector<QMetaObject::Connection> > m_connections; // To make it easy to disconnect from lambdas
};

}

#endif
