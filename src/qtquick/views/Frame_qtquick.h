/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#ifndef KD_FRAME_QUICK_P_H
#define KD_FRAME_QUICK_P_H
#pragma once

#include "View_qtquick.h"
#include "views/Frame.h"

class QQuickItem;

namespace KDDockWidgets {

namespace Controllers {
class Frame;
class DockWidget;
}

namespace Views {

class Stack_qtquick;

class DOCKS_EXPORT Frame_qtquick : public View_qtquick, public Frame
{
    Q_OBJECT
    Q_PROPERTY(QObject *tabWidget READ tabWidgetObj CONSTANT)
    Q_PROPERTY(bool isMDI READ isMDI CONSTANT)
public:
    explicit Frame_qtquick(Controllers::Frame *controller, QQuickItem *parent = nullptr);
    ~Frame_qtquick() override;

    /// @reimp
    QSize minSize() const override;

    /// @reimp
    QSize maximumSize() const override;

    /// @brief returns the tab widget as QObject for usage in QML.
    /// We can't return TabWidget directly as it's not a QObject
    QObject *tabWidgetObj() const;

    /// @brief Returns the QQuickItem which represents this frame on the screen
    QQuickItem *visualItem() const;

    QRect dragRect() const override;


    // QML interface:
    bool isMDI() const;

protected:
    void removeWidget_impl(Controllers::DockWidget *) override;
    int indexOfDockWidget_impl(const Controllers::DockWidget *) override;
    int currentIndex_impl() const override;
    void setCurrentTabIndex_impl(int index) override;
    void setCurrentDockWidget_impl(Controllers::DockWidget *) override;
    void insertDockWidget_impl(Controllers::DockWidget *, int index) override;
    Controllers::DockWidget *dockWidgetAt_impl(int index) const override;
    Controllers::DockWidget *currentDockWidget_impl() const override;
    void renameTab(int index, const QString &) override;
    void changeTabIcon(int index, const QIcon &) override;

    Q_INVOKABLE void setStackLayout(QQuickItem *);

    int nonContentsHeight() const override;

Q_SIGNALS:
    void tabTitlesChanged();

public Q_SLOTS:
    void updateConstriants();

private:
    void init() override;
    Stack_qtquick *stackView() const;

    QQuickItem *m_stackLayout = nullptr;
    QQuickItem *m_visualItem = nullptr;
    Controllers::Frame *const m_controller;
    QHash<Controllers::DockWidget *, QMetaObject::Connection> m_connections; // To make it easy to disconnect from lambdas
};

}
}

#endif
