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
#include "views/GroupViewInterface.h"
#include "TitleBar_qtquick.h"

class QQuickItem;

namespace KDDockWidgets {

namespace Controllers {
class Group;
class DockWidget;
}

namespace Views {

class Stack_qtquick;

class DOCKS_EXPORT Group_qtquick : public View_qtquick, public GroupViewInterface
{
    Q_OBJECT
    Q_PROPERTY(QObject *tabWidget READ tabWidgetObj CONSTANT)
    Q_PROPERTY(KDDockWidgets::Views::TitleBar_qtquick *titleBar READ titleBar CONSTANT)
    Q_PROPERTY(int userType READ userType CONSTANT)
    Q_PROPERTY(KDDockWidgets::Views::TitleBar_qtquick *actualTitleBar READ actualTitleBar NOTIFY actualTitleBarChanged)
    Q_PROPERTY(int currentIndex READ currentIndex_impl NOTIFY currentDockWidgetChanged)
    Q_PROPERTY(bool isMDI READ isMDI NOTIFY isMDIChanged)

public:
    explicit Group_qtquick(Controllers::Group *controller, QQuickItem *parent = nullptr);
    ~Group_qtquick() override;

    /// @reimp
    QSize minSize() const override;

    /// @reimp
    QSize maximumSize() const override;

    /// @brief Returns the QQuickItem which represents this group on the screen
    QQuickItem *visualItem() const override;

    QRect dragRect() const override;

    // QML interface:
    KDDockWidgets::Views::TitleBar_qtquick *titleBar() const;
    KDDockWidgets::Views::TitleBar_qtquick *actualTitleBar() const;
    int userType() const;
    QObject *tabWidgetObj() const;


protected:
    bool event(QEvent *) override;
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
    void isMDIChanged();
    void currentDockWidgetChanged();
    void actualTitleBarChanged();

public Q_SLOTS:
    void updateConstriants();

private:
    void init() override;
    Stack_qtquick *stackView() const;

    QQuickItem *m_stackLayout = nullptr;
    QQuickItem *m_visualItem = nullptr;
    QHash<Controllers::DockWidget *, QMetaObject::Connection> m_connections; // To make it easy to disconnect from lambdas
};

}
}

#endif
