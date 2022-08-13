/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TabBar_qtwidgets.h"
#include "Stack_qtwidgets.h"
#include "DockWidget_qtwidgets.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/TabBar.h"
#include "kddockwidgets/controllers/Stack.h"
#include "private/Utils_p.h"
#include "private/Logging_p.h"
#include "Config.h"
#include "kddockwidgets/ViewFactory.h"
#include "kddockwidgets/private/DockRegistry.h"

#include <QMouseEvent>
#include <QApplication>
#include <QProxyStyle>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

namespace KDDockWidgets {
namespace { // anonymous namespace to silence -Wweak-vtables
class MyProxy : public QProxyStyle
{
public:
    MyProxy()
        : QProxyStyle(qApp->style())
    {
        setParent(qApp);
    }

    int styleHint(QStyle::StyleHint hint, const QStyleOption *option = nullptr,
                  const QWidget *widget = nullptr,
                  QStyleHintReturn *returnData = nullptr) const override
    {
        if (hint == QStyle::SH_Widget_Animation_Duration) {
            // QTabBar has a bug which causes the paint event to dereference a tab which was already
            // removed. Because, after the tab being removed, the d->pressedIndex is only reset
            // after the animation ends. So disable the animation. Crash can be repro by enabling
            // movable tabs, and detaching a tab quickly from a floating window containing two dock
            // widgets. Reproduced on Windows
            return 0;
        }
        return baseStyle()->styleHint(hint, option, widget, returnData);
    }
};
}
}


TabBar_qtwidgets::TabBar_qtwidgets(Controllers::TabBar *controller, QWidget *parent)
    : View_qtwidgets(controller, Type::TabBar, parent)
    , TabBarViewInterface(controller)
    , m_controller(controller)
{
}

int TabBar_qtwidgets::tabAt(QPoint localPos) const
{
    return QTabBar::tabAt(localPos);
}

Controllers::DockWidget *TabBar_qtwidgets::currentDockWidget() const
{
    const int index = currentIndex();
    return index == -1 ? nullptr : m_controller->dockWidgetAt(index);
}

void TabBar_qtwidgets::mousePressEvent(QMouseEvent *e)
{
    m_controller->onMousePress(e->pos());
    QTabBar::mousePressEvent(e);
}

void TabBar_qtwidgets::mouseMoveEvent(QMouseEvent *e)
{
    if (count() > 1) {
        // Only allow to re-order tabs if we have more than 1 tab, otherwise it's just weird.
        QTabBar::mouseMoveEvent(e);
    }
}

void TabBar_qtwidgets::mouseDoubleClickEvent(QMouseEvent *e)
{
    m_controller->onMouseDoubleClick(e->pos());
}

bool TabBar_qtwidgets::event(QEvent *ev)
{
    // Qt has a bug in QWidgetPrivate::deepestFocusProxy(), it doesn't honour visibility
    // of the focus scope. Once an hidden widget is focused the chain is broken and tab
    // stops working (#180)

    auto parent = parentWidget();
    if (!parent)
        return QTabBar::event(ev);

    const bool result = QTabBar::event(ev);

    if (ev->type() == QEvent::Show) {
        parent->setFocusProxy(this);
    } else if (ev->type() == QEvent::Hide) {
        parent->setFocusProxy(nullptr);
    }

    return result;
}

QString TabBar_qtwidgets::text(int index) const
{
    return tabText(index);
}

QRect TabBar_qtwidgets::rectForTab(int index) const
{
    return QTabBar::tabRect(index);
}

void TabBar_qtwidgets::moveTabTo(int from, int to)
{
    moveTab(from, to);
}

bool TabBar_qtwidgets::tabsAreMovable() const
{
    return isMovable();
}

void TabBar_qtwidgets::tabInserted(int index)
{
    QTabBar::tabInserted(index);
    Q_EMIT dockWidgetInserted(index);
}

void TabBar_qtwidgets::tabRemoved(int index)
{
    QTabBar::tabRemoved(index);
    Q_EMIT dockWidgetRemoved(index);
}

int TabBar_qtwidgets::currentIndex() const
{
    return QTabBar::currentIndex();
}

void TabBar_qtwidgets::setCurrentIndex(int index)
{
    QTabBar::setCurrentIndex(index);
}

int TabBar_qtwidgets::numDockWidgets() const
{
    return QTabBar::count();
}

QTabWidget *TabBar_qtwidgets::tabWidget() const
{
    if (auto tw = dynamic_cast<Stack_qtwidgets *>(m_controller->stack()->view()))
        return tw;

    qWarning() << Q_FUNC_INFO << "Unexpected null QTabWidget";
    return nullptr;
}

Controllers::DockWidget *TabBar_qtwidgets::dockWidgetAt(int index) const
{
    auto view = qobject_cast<DockWidget_qtwidgets *>(tabWidget()->widget(index));
    return view ? view->dockWidget() : nullptr;
}

int TabBar_qtwidgets::indexOfDockWidget(const Controllers::DockWidget *dw) const
{
    return tabWidget()->indexOf(View_qt::asQWidget(dw->view()));
}

void TabBar_qtwidgets::renameTab(int index, const QString &text)
{
    setTabText(index, text);
}

void TabBar_qtwidgets::changeTabIcon(int index, const QIcon &icon)
{
    setTabIcon(index, icon);
}

void TabBar_qtwidgets::removeDockWidget(Controllers::DockWidget *dw)
{
    auto tabWidget = static_cast<QTabWidget *>(View_qt::asQWidget(m_tabBar->stack()));
    tabWidget->removeTab(indexOfDockWidget(dw));
}

bool TabBar_qtwidgets::insertDockWidget(int index, Controllers::DockWidget *dw, const QIcon &icon,
                                        const QString &title)
{
    auto tabWidget = static_cast<QTabWidget *>(View_qt::asQWidget(m_tabBar->stack()));
    tabWidget->insertTab(index, View_qt::asQWidget(dw), icon, title);
    return true;
}
