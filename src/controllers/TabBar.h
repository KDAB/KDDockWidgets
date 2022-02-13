/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "../Controller.h"
#include "Frame.h"
#include "../private/Draggable_p.h"
#include "DockWidget.h"

#include <QPointer>

namespace KDDockWidgets::Controllers {

class Stack;
class Frame;

class DOCKS_EXPORT TabBar : public Controller, public Draggable
{
public:
    explicit TabBar(Stack *tabWidget = nullptr);
    virtual ~TabBar() override;

    /**
     * @brief returns the dock widgets at tab number @p index
     * @param index the tab number from which we want the dock widget
     * @return the dock widget at tab number @p index
     */
    DockWidgetBase *dockWidgetAt(int index) const;

    ///@overload
    DockWidgetBase *dockWidgetAt(QPoint localPos) const;

    // Draggable
    bool dragCanStart(QPoint pressPos, QPoint pos) const override;
    std::unique_ptr<WindowBeingDragged> makeWindow() override;
    bool isWindow() const override;

    void onMousePress(QPoint localPos);
    void onMouseDoubleClick(QPoint localPos);

    ///@brief returns whether there's only 1 tab
    bool hasSingleDockWidget() const;

    int numDockWidgets() const;

    /**
     * @brief Returns this class as a QWidget (if using QtWidgets) or QQuickItem
     */
    // QWidgetOrQuick *asWidget() const;

    DockWidgetBase *singleDockWidget() const override;

    /// @reimp
    bool isMDI() const override;

    Frame *frame() const;

    void moveTabTo(int from, int to);
    QString text(int index) const;
    QRect rectForTab(int index) const;

private:
    Controllers::Stack *const m_tabWidget;
    QPointer<DockWidgetBase> m_lastPressedDockWidget = nullptr;
};

}
