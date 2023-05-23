/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#pragma once

#include "View.h"
#include <kddockwidgets/core/views/StackViewInterface.h>

#include <QTabWidget>

namespace KDDockWidgets {
namespace QtWidgets {

class DOCKS_EXPORT Stack : public View<QTabWidget>, public Core::StackViewInterface
{
    Q_OBJECT
public:
    explicit Stack(Core::Stack *controller, QWidget *parent = nullptr);
    ~Stack();

    /// @brief Returns the QTabBar associated with this QTabWidget
    QTabBar *tabBar() const;

    bool isPositionDraggable(QPoint p) const override;
    void init() override;
    void setDocumentMode(bool) override;

    /// @brief Returns the controller
    Core::Stack *stack() const;

public: // TODOm3: make protected
    void mouseDoubleClickEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;

    /// @brief Shows the context menu. Override to implement your own context menu.
    /// By default it's used to honour Config::Flag_AllowSwitchingTabsViaMenu
    virtual void showContextMenu(QPoint pos);

private:
    void updateMargins();
    void setupTabBarButtons();

    class Private;
    Private *const d;

    Q_DISABLE_COPY(Stack)
};

}
}
