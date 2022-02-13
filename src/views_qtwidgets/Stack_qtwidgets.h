/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#pragma once

#include "View_qtwidgets.h"

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

class DOCKS_EXPORT Stack_qtwidgets : public View_qtwidgets<QTabWidget>
{
    Q_OBJECT
public:
    explicit Stack_qtwidgets(Controllers::Stack *controller,
                             Controllers::Frame *parent = nullptr);

    Controllers::Stack *stack() const;
    QTabBar *tabBar() const;

    int numDockWidgets() const;
    void removeDockWidget(Controllers::DockWidgetBase *);
    int indexOfDockWidget(const Controllers::DockWidgetBase *) const;

public: // TODO: make protected
    void mouseDoubleClickEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void tabInserted(int index) override;
    void tabRemoved(int index) override;
    void setCurrentDockWidget(int index);
    bool insertDockWidget(int index, Controllers::DockWidgetBase *, const QIcon &, const QString &title);
    void setTabBarAutoHide(bool);
    void renameTab(int index, const QString &);
    void changeTabIcon(int index, const QIcon &);
    void init() override;

    Controllers::DockWidgetBase *dockwidgetAt(int index) const;
    int currentIndex() const;

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
