/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file
 * @brief Implements a QTabWidget derived class with support for docking and undocking
 * KDockWidget::DockWidget as tabs .
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "TabBarWidget_p.h"
#include "Config.h"

#include <QMouseEvent>
#include <QApplication>
#include <QProxyStyle>

namespace KDDockWidgets {
class MyProxy : public QProxyStyle
{
public:
    MyProxy() : QProxyStyle(qApp->style()) {}

    int styleHint(QStyle::StyleHint hint, const QStyleOption *option = nullptr,
                  const QWidget *widget = nullptr, QStyleHintReturn *returnData = nullptr) const override
    {

#if QT_VERSION < QT_VERSION_CHECK(5,10,0)
        auto durationHint = QStyle::SH_Widget_Animate; // deprecated in 5.10
#else
        auto durationHint = QStyle::SH_Widget_Animation_Duration;
#endif

        if (hint == durationHint) {
            // QTabBar has a bug which causes the paint event to dereference a tab which was already removed.
            // Because, after the tab being removed, the d->pressedIndex is only reset after the animation ends.
            // So disable the animation. Crash can be repro by enabling movable tabs, and detaching a tab quickly from
            // a floating window containing two dock widgets. Reproduced on Windows
            return 0;
        }
        return baseStyle()->styleHint(hint, option, widget, returnData);
    }
};
}

using namespace KDDockWidgets;

TabBarWidget::TabBarWidget(TabWidget *parent)
    : QTabBar(parent->asWidget())
    , TabBar(this, parent)
{
    setMovable(Config::self().flags() & Config::Flag_AllowReorderTabs);
    setStyle(new MyProxy());
}

int TabBarWidget::numDockWidgets() const
{
    return count();
}

int TabBarWidget::tabAt(QPoint localPos) const
{
    return QTabBar::tabAt(localPos);
}

void TabBarWidget::mousePressEvent(QMouseEvent *e)
{
    onMousePress(e->pos());
    QTabBar::mousePressEvent(e);
}

void TabBarWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (count() > 1) {
        // Only allow to re-order tabs if we have more than 1 tab, otherwise it's just weird.
        QTabBar::mouseMoveEvent(e);
    }
}

bool TabBarWidget::dragCanStart(QPoint pressPos, QPoint pos) const
{
    // Here we allow the user to re-order tabs instead of dragging them off.
    // To do that we just return false here, and QTabBar will handle the mouse event, assuming QTabBar::isMovable.

    const bool defaultResult = Draggable::dragCanStart(pressPos, pos);

    if (!defaultResult || !isMovable()) {
        // Nothing more to do. If the drag wouldn't start anyway, return false.
        // And if the tabs aren't movable, just return the default result, which just considers
        // QApplication::startDragDistances
        return defaultResult;
    }

    const int index = tabAt(mapFromGlobal(pos));
    if (index == -1)
        return defaultResult;

    const int deltaX = qAbs(pos.x() - pressPos.x());
    const int deltaY = qAbs(pos.y() - pressPos.y());

    if (deltaY > 5 * QApplication::startDragDistance()) {
        // Moving up or down too much results in a detach. No tab re-ordering allowed.
        return true;
    } else if (deltaY > QApplication::startDragDistance() && deltaX < QApplication::startDragDistance()) {
        // Moved a bit up or down, but not left/right, then detach too.
        // Only if it's going considerably left/right we allow to re-order tabs.
        return true;
    }

    return false;
}
