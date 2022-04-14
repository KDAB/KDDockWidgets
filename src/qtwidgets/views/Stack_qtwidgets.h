/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#pragma once

#include "View_qtwidgets.h"
#include "views/Stack.h"

#include <QTabWidget>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QHBoxLayout;
QT_END_NAMESPACE

namespace KDDockWidgets::Controllers {
class Stack;
class Frame;
}

namespace KDDockWidgets {
namespace Views {

class DOCKS_EXPORT Stack_qtwidgets : public View_qtwidgets<QTabWidget>, public Stack
{
    Q_OBJECT
public:
    explicit Stack_qtwidgets(Controllers::Stack *controller,
                             Controllers::Frame *parent = nullptr);

    Controllers::Stack *stack() const;
    QTabBar *tabBar() const;

    int numDockWidgets() const override;
    void removeDockWidget(Controllers::DockWidget *) override;
    int indexOfDockWidget(const Controllers::DockWidget *) const override;

    bool isPositionDraggable(QPoint p) const override;
    void init() override;
    void setDocumentMode(bool) override;

public: // TODO: make protected
    void mouseDoubleClickEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void tabInserted(int index) override;
    void tabRemoved(int index) override;
    void setCurrentDockWidget(int index) override;
    bool insertDockWidget(int index, Controllers::DockWidget *, const QIcon &, const QString &title) override;
    void setTabBarAutoHide(bool) override;
    void renameTab(int index, const QString &) override;
    void changeTabIcon(int index, const QIcon &) override;
    Controllers::DockWidget *dockwidgetAt(int index) const override;
    int currentIndex() const override;

    /// @brief Shows the context menu. Override to implement your own context menu.
    /// By default it's used to honour Config::Flag_AllowSwitchingTabsViaMenu
    virtual void showContextMenu(QPoint pos);

private:
    void updateMargins();
    void setupTabBarButtons();

    QHBoxLayout *m_cornerWidgetLayout = nullptr;
    QAbstractButton *m_floatButton = nullptr;
    QAbstractButton *m_closeButton = nullptr;
    Controllers::Stack *const m_stack;

    Q_DISABLE_COPY(Stack_qtwidgets)
};

}
}
