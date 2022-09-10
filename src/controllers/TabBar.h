/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "../Controller.h"
#include "Group.h"
#include "../private/Draggable_p.h"
#include "DockWidget.h"

#include <QPointer>

namespace KDDockWidgets::Controllers {

class Stack;
class Group;

class DOCKS_EXPORT TabBar : public Controller, public Draggable
{
    Q_OBJECT
public:
    explicit TabBar(Stack *tabWidget = nullptr);
    virtual ~TabBar() override;

    /**
     * @brief returns the dock widgets at tab number @p index
     * @param index the tab number from which we want the dock widget
     * @return the dock widget at tab number @p index
     */
    DockWidget *dockWidgetAt(int index) const;

    ///@overload
    DockWidget *dockWidgetAt(QPoint localPos) const;

    /// @brief Returns the current dock widget
    DockWidget *currentDockWidget() const;
    void setCurrentDockWidget(DockWidget *dw);

    /// @brief Returns the index of the current tab
    int currentIndex() const;
    void setCurrentIndex(int index);

    /// @brief Returns the tab index of the specified dock widget
    int indexOfDockWidget(const Controllers::DockWidget *dw) const;
    void removeDockWidget(Controllers::DockWidget *dw);
    void insertDockWidget(int index, Controllers::DockWidget *dw, const QIcon &icon,
                          const QString &title);

    // Draggable
    bool dragCanStart(QPoint pressPos, QPoint pos) const override;
    std::unique_ptr<WindowBeingDragged> makeWindow() override;
    bool isWindow() const override;

    void onMousePress(QPoint localPos);
    void onMouseDoubleClick(QPoint localPos);

    ///@brief returns whether there's only 1 tab
    bool hasSingleDockWidget() const;

    int numDockWidgets() const;

    bool tabsAreMovable() const;

    DockWidget *singleDockWidget() const override;

    /// @reimp
    bool isMDI() const override;

    Group *group() const;
    Stack *stack() const;

    void moveTabTo(int from, int to);
    QString text(int index) const;
    QRect rectForTab(int index) const;
    ///@brief rename's the tab's text
    void renameTab(int index, const QString &);

    ///@brief change the tab's icon
    void changeTabIcon(int index, const QIcon &);
Q_SIGNALS:
    void currentDockWidgetChanged(KDDockWidgets::Controllers::DockWidget *);
    void countChanged();

private:
    Controllers::Stack *const m_stack;
    QPointer<DockWidget> m_lastPressedDockWidget = nullptr;
    DockWidget *m_currentDockWidget = nullptr;
    QVector<const DockWidget *> m_dockWidgets;
    bool m_removeGuard = false;
};

}
