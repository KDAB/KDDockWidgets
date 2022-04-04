/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewWrapper_qtquick.h"
// #include "qtwidgets/views/DockWidget_qtquick.h"
// #include "qtwidgets/views/FloatingWindow_qtquick.h"
// #include "qtwidgets/views/Frame_qtquick.h"
// #include "qtwidgets/views/MainWindow_qtquick.h"
// #include "qtwidgets/views/Separator_qtquick.h"
// #include "qtwidgets/views/SideBar_qtquick.h"
// #include "qtwidgets/views/Stack_qtquick.h"
// #include "qtwidgets/views/TabBar_qtquick.h"
// #include "qtwidgets/views/TitleBar_qtquick.h"

#include "private/MultiSplitter_p.h"
#include "private/MDILayoutWidget_p.h"
#include "MDIArea.h"

#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

ViewWrapper_qtquick::ViewWrapper_qtquick(QObject *item)
    : ViewWrapper_qtquick(qobject_cast<QQuickItem *>(item))
{
}

ViewWrapper_qtquick::ViewWrapper_qtquick(QQuickItem *item)
    : ViewWrapper(nullptr /*controllerForWidget(widget)*/, item)
    , m_item(item)
{
}

void ViewWrapper_qtquick::setObjectName(const QString &name)
{
    m_item->setObjectName(name);
}

QRect ViewWrapper_qtquick::geometry() const
{
    return {};
}

QPoint ViewWrapper_qtquick::mapToGlobal(QPoint localPt) const
{
    return {};
}

QPoint ViewWrapper_qtquick::mapFromGlobal(QPoint globalPt) const
{
    return {};
}

void ViewWrapper_qtquick::setGeometry(QRect)
{
}

QWindow *ViewWrapper_qtquick::windowHandle() const
{
    return {};
}

bool ViewWrapper_qtquick::isTopLevel() const
{
    return {};
}

void ViewWrapper_qtquick::setVisible(bool)
{
}

bool ViewWrapper_qtquick::isVisible() const
{
    return {};
}

void ViewWrapper_qtquick::move(int, int)
{
}

void ViewWrapper_qtquick::move(QPoint)
{
}

void ViewWrapper_qtquick::activateWindow()
{
}

bool ViewWrapper_qtquick::isMaximized() const
{
    return {};
}

QSize ViewWrapper_qtquick::maximumSize() const
{
    return {};
}

void ViewWrapper_qtquick::setSize(int, int)
{
}

bool ViewWrapper_qtquick::is(Type t) const
{
    if (t == Type::ViewWrapper)
        return true;

    // switch (t) {

    // case Type::Frame:
    //     return qobject_cast<Views::Frame_qtquick *>(m_item);
    // case Type::TitleBar:
    //     return qobject_cast<Views::TitleBar_qtquick *>(m_item);
    // case Type::TabBar:
    //     return qobject_cast<Views::TabBar_qtquick *>(m_item);
    // case Type::Stack:
    //     return qobject_cast<Views::Stack_qtquick *>(m_item);
    // case Type::FloatingWindow:
    //     return qobject_cast<Views::FloatingWindow_qtquick *>(m_item);
    // case Type::Separator:
    //     return qobject_cast<Views::Separator_qtquick *>(m_item);
    // case Type::DockWidget:
    //     return qobject_cast<Views::DockWidget_qtquick *>(m_item);
    // case Type::SideBar:
    //     return qobject_cast<Views::SideBar_qtquick *>(m_item);
    // case Type::MainWindow:
    //     return qobject_cast<Views::MainWindow_qtquick *>(m_item);
    // case Type::Layout:
    //     return qobject_cast<LayoutWidget *>(m_item);
    // case Type::MultiSplitter:
    //     return qobject_cast<MultiSplitter *>(m_item);
    // case Type::MDILayout:
    //     return qobject_cast<MDILayoutWidget *>(m_item);
    // case Type::MDIArea:
    //     return qobject_cast<MDIArea *>(m_item);
    // case Type::LayoutItem:
    // case Type::DropIndicatorOverlayInterface:
    //     qWarning() << Q_FUNC_INFO << "These are framework internals that are not wrapped";
    //     return false;
    // case Type::ViewWrapper:
    //     return true;
    // }

    qWarning() << Q_FUNC_INFO << "Unknown type" << static_cast<int>(t);
    return false;
}

std::shared_ptr<ViewWrapper> ViewWrapper_qtquick::window() const
{
    // return std::shared_ptr<ViewWrapper>(new ViewWrapper_qtquick(m_item->window()));
    return {};
}

std::shared_ptr<ViewWrapper> ViewWrapper_qtquick::parentView() const
{
    // return std::shared_ptr<ViewWrapper>(new ViewWrapper_qtquick(m_item->parentWidget()));
    return {};
}

HANDLE ViewWrapper_qtquick::handle() const
{
    return reinterpret_cast<HANDLE>(m_item);
}

void ViewWrapper_qtquick::grabMouse()
{
}

void ViewWrapper_qtquick::releaseMouse()
{
}

QScreen *ViewWrapper_qtquick::screen() const
{
    return {};
}

void ViewWrapper_qtquick::setFocus(Qt::FocusReason)
{
}

QString ViewWrapper_qtquick::objectName() const
{
    return {};
}
