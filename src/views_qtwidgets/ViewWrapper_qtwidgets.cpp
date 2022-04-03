/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewWrapper_qtwidgets.h"
#include "views_qtwidgets/DockWidget_qtwidgets.h"
#include "views_qtwidgets/FloatingWindow_qtwidgets.h"
#include "views_qtwidgets/Frame_qtwidgets.h"
#include "views_qtwidgets/MainWindow_qtwidgets.h"
#include "views_qtwidgets/Separator_qtwidgets.h"
#include "views_qtwidgets/SideBar_qtwidgets.h"
#include "views_qtwidgets/Stack_qtwidgets.h"
#include "views_qtwidgets/TabBar_qtwidgets.h"
#include "views_qtwidgets/TitleBar_qtwidgets.h"

#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

static Controller *controllerForWidget(QWidget *widget)
{
    // KDDW deals in views, but sometimes we might get a native type like QWidget, for example if you call
    // someview->window(). This function let's us retrieve the actual controller of the stray QWidget.

    for (int i = int(Type::FIRST); i <= int(::Type::LAST); i *= 2) {
        // Using a for+switch pattern so that compiler reminds us if new enumerators are added to enum
        switch (Type(i)) {
        case Type::Frame:
            if (auto view = qobject_cast<Frame_qtwidgets *>(widget))
                return view->controller();
            break;
        case Type::TitleBar:
            if (auto view = qobject_cast<TitleBar_qtwidgets *>(widget))
                return view->controller();
            break;
        case Type::TabBar:
            if (auto view = qobject_cast<TabBar_qtwidgets *>(widget))
                return view->controller();
            break;
        case Type::Stack:
            if (auto view = qobject_cast<Stack_qtwidgets *>(widget))
                return view->controller();
            break;
        case Type::FloatingWindow:
            if (auto view = qobject_cast<FloatingWindow_qtwidgets *>(widget))
                return view->controller();
            break;
        case Type::Separator:
            if (auto view = qobject_cast<Separator_qtwidgets *>(widget))
                return view->controller();
            break;
        case Type::DockWidget:
            if (auto view = qobject_cast<DockWidget_qtwidgets *>(widget))
                return view->controller();
            break;
        case Type::Layout:
            if (auto view = qobject_cast<LayoutWidget *>(widget))
                return view->controller();
            break;
        case Type::SideBar:
            if (auto view = qobject_cast<SideBar_qtwidgets *>(widget))
                return view->controller();
            break;
        case Type::MainWindow:
            if (auto view = qobject_cast<MainWindow_qtwidgets *>(widget))
                return view->controller();
            break;
        case Type::LayoutItem:
        case Type::DropIndicatorOverlayInterface:
        case Type::ViewWrapper:
            // skip internal types
            continue;
        }
    }

    return nullptr;
}

ViewWrapper_qtwidgets::ViewWrapper_qtwidgets(QObject *widget)
    : ViewWrapper_qtwidgets(qobject_cast<QWidget *>(widget))
{
}

ViewWrapper_qtwidgets::ViewWrapper_qtwidgets(QWidget *widget)
    : ViewWrapper(controllerForWidget(widget), widget)
    , m_widget(widget)
{
}

void ViewWrapper_qtwidgets::setObjectName(const QString &name)
{
    m_widget->setObjectName(name);
}

QRect ViewWrapper_qtwidgets::geometry() const
{
    return m_widget->geometry();
}

QPoint ViewWrapper_qtwidgets::mapToGlobal(QPoint localPt) const
{
    return m_widget->mapToGlobal(localPt);
}

QPoint ViewWrapper_qtwidgets::mapFromGlobal(QPoint globalPt) const
{
    return m_widget->mapFromGlobal(globalPt);
}

void ViewWrapper_qtwidgets::setGeometry(QRect rect)
{
    m_widget->setGeometry(rect);
}

QWindow *ViewWrapper_qtwidgets::windowHandle() const
{
    return m_widget->windowHandle();
}

bool ViewWrapper_qtwidgets::isTopLevel() const
{
    return m_widget->isTopLevel();
}

void ViewWrapper_qtwidgets::setVisible(bool is)
{
    m_widget->setVisible(is);
}

bool ViewWrapper_qtwidgets::isVisible() const
{
    return m_widget->isVisible();
}

void ViewWrapper_qtwidgets::move(int x, int y)
{
    m_widget->move(x, y);
}

void ViewWrapper_qtwidgets::move(QPoint pt)
{
    m_widget->move(pt);
}

void ViewWrapper_qtwidgets::activateWindow()
{
    m_widget->activateWindow();
}

bool ViewWrapper_qtwidgets::isMaximized() const
{
    return m_widget->isMaximized();
}

QSize ViewWrapper_qtwidgets::maximumSize() const
{
    return m_widget->maximumSize();
}

void ViewWrapper_qtwidgets::setSize(int x, int y)
{
    m_widget->resize(x, y);
}

bool ViewWrapper_qtwidgets::is(Type t) const
{
    if (t == Type::ViewWrapper)
        return true;

    switch (t) {

    case Type::Frame:
        return qobject_cast<Views::Frame_qtwidgets *>(m_widget);
    case Type::TitleBar:
        return qobject_cast<Views::TitleBar_qtwidgets *>(m_widget);
    case Type::TabBar:
        return qobject_cast<Views::TabBar_qtwidgets *>(m_widget);
    case Type::Stack:
        return qobject_cast<Views::Stack_qtwidgets *>(m_widget);
    case Type::FloatingWindow:
        return qobject_cast<Views::FloatingWindow_qtwidgets *>(m_widget);
    case Type::Separator:
        return qobject_cast<Views::Separator_qtwidgets *>(m_widget);
    case Type::DockWidget:
        return qobject_cast<Views::DockWidget_qtwidgets *>(m_widget);
    case Type::SideBar:
        return qobject_cast<Views::SideBar_qtwidgets *>(m_widget);
    case Type::MainWindow:
        return qobject_cast<Views::MainWindow_qtwidgets *>(m_widget);
    case Type::Layout:
        return qobject_cast<LayoutWidget *>(m_widget);
    case Type::LayoutItem:
    case Type::DropIndicatorOverlayInterface:
        qWarning() << Q_FUNC_INFO << "These are framework internals that are not wrapped";
        return false;
    case Type::ViewWrapper:
        return true;
    }

    qWarning() << Q_FUNC_INFO << "Unknown type" << static_cast<int>(t);
    return false;
}

std::unique_ptr<ViewWrapper> ViewWrapper_qtwidgets::window() const
{
    return std::unique_ptr<ViewWrapper>(new ViewWrapper_qtwidgets(m_widget->window()));
}

std::unique_ptr<ViewWrapper> ViewWrapper_qtwidgets::parentView() const
{
    return std::unique_ptr<ViewWrapper>(new ViewWrapper_qtwidgets(m_widget->parentWidget()));
}

HANDLE ViewWrapper_qtwidgets::handle() const
{
    return reinterpret_cast<HANDLE>(m_widget);
}

void ViewWrapper_qtwidgets::grabMouse()
{
    m_widget->grabMouse();
}

void ViewWrapper_qtwidgets::releaseMouse()
{
    m_widget->releaseMouse();
}

QScreen *ViewWrapper_qtwidgets::screen() const
{
    return m_widget->screen();
}

void ViewWrapper_qtwidgets::setFocus(Qt::FocusReason reason)
{
    m_widget->setFocus(reason);
}
