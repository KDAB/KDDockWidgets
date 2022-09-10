/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief The QQuickItem counter part of TabWidgetQuick. Handles GUI while TabWidget handles state.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDTABWIDGETQUICK_P_H
#define KDTABWIDGETQUICK_P_H
#pragma once

#include "View_qtquick.h"
#include "views/StackViewInterface.h"

#include <QVector>

#include "kdbindings/signal.h"

namespace KDDockWidgets {
namespace Controllers {
class DockWidget;
class Group;
class TabBar;
}

namespace Views {

class DOCKS_EXPORT Stack_qtquick : public View_qtquick, public StackViewInterface
{
    Q_OBJECT
public:
    explicit Stack_qtquick(Controllers::Stack *controller, QQuickItem *parent = nullptr);


    /// @brief Returns the stack controller associated with this view
    Controllers::Stack *stack() const;

    /// Returns whether the tab bar should hide when there's only 1 tab visible
    /// Default true, unless Flag_HideTitleBarWhenTabsVisible
    bool tabBarAutoHide() const;

Q_SIGNALS:
    void tabBarChanged();
    void tabBarAutoHideChanged();

protected:
    void init() override;

private:
    Q_DISABLE_COPY(Stack_qtquick)
    KDBindings::ScopedConnection m_tabBarAutoHideChanged;
};

}
}

#endif
