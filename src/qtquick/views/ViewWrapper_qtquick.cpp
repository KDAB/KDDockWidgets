/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewWrapper_qtquick.h"
#include "qtquick/views/View_qtquick.h"

// #include "qtwidgets/views/DockWidget_qtquick.h"
// #include "qtwidgets/views/FloatingWindow_qtquick.h"
// #include "qtwidgets/views/Frame_qtquick.h"
// #include "qtwidgets/views/MainWindow_qtquick.h"
// #include "qtwidgets/views/Separator_qtquick.h"
// #include "qtwidgets/views/SideBar_qtquick.h"
// #include "qtwidgets/views/Stack_qtquick.h"
// #include "qtwidgets/views/TabBar_qtquick.h"
// #include "qtwidgets/views/TitleBar_qtquick.h"

#include "controllers/DropArea.h"
#include "private/MDILayoutWidget_p.h"
// #include "MDIArea.h"

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
    qFatal("not implemented");
    return {};
}

QPoint ViewWrapper_qtquick::mapToGlobal(QPoint /*localPt*/) const
{
    qFatal("not implemented");
    return {};
}

QPoint ViewWrapper_qtquick::mapFromGlobal(QPoint /*globalPt*/) const
{
    qFatal("not implemented");
    return {};
}

void ViewWrapper_qtquick::setGeometry(QRect)
{
    qFatal("not implemented");
}

std::shared_ptr<ViewWrapper> ViewWrapper_qtquick::childViewAt(QPoint) const
{
    return {};
}

std::shared_ptr<Window> ViewWrapper_qtquick::window() const
{
    if (QWindow *w = m_item->window()) {
        auto windowqtquick = new Window_qtquick(w);
        return std::shared_ptr<Window>(windowqtquick);
    }

    return {};
}

bool ViewWrapper_qtquick::isRootView() const
{
    return View_qtquick::isRootView(m_item);
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

void ViewWrapper_qtquick::activateWindow()
{
}

bool ViewWrapper_qtquick::isMaximized() const
{
    return {};
}

bool ViewWrapper_qtquick::isMinimized() const
{
    return {};
}

QSize ViewWrapper_qtquick::maximumSize() const
{
    qFatal("not implemented");
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
    //     return qobject_cast<Views::DropArea *>(m_item);
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

std::shared_ptr<ViewWrapper> ViewWrapper_qtquick::rootView() const
{
    if (Window::Ptr window = this->window())
        return window->rootView();

    qWarning() << Q_FUNC_INFO << "No window present";
    return {};
}

std::shared_ptr<ViewWrapper> ViewWrapper_qtquick::parentView() const
{
    return View_qtquick::parentViewFor(m_item);
}

HANDLE ViewWrapper_qtquick::handle() const
{
    return reinterpret_cast<HANDLE>(m_item.data());
}

void ViewWrapper_qtquick::grabMouse()
{
    m_item->grabMouse();
}

void ViewWrapper_qtquick::releaseMouse()
{
    m_item->ungrabMouse();
}

Qt::FocusPolicy ViewWrapper_qtquick::focusPolicy() const
{
    if (auto view = unwrap()) {
        return view->focusPolicy();
    } else {
        qFatal("not implemented");
        return {};
    }
}

void ViewWrapper_qtquick::setFocus(Qt::FocusReason reason)
{
    m_item->QQuickItem::setFocus(true, reason);
    m_item->forceActiveFocus(reason);
}

void ViewWrapper_qtquick::setFocusPolicy(Qt::FocusPolicy)
{
    qFatal("not implemented");
}

bool ViewWrapper_qtquick::hasFocus() const
{
    return m_item->hasActiveFocus();
}

QString ViewWrapper_qtquick::objectName() const
{
    return m_item->objectName();
}

QVariant ViewWrapper_qtquick::property(const char *name) const
{
    return m_item->property(name);
}

bool ViewWrapper_qtquick::isNull() const
{
    return m_item.data() == nullptr;
}

void ViewWrapper_qtquick::setWindowTitle(const QString &)
{
}

QPoint ViewWrapper_qtquick::mapTo(View *, QPoint) const
{
    return {};
}

bool ViewWrapper_qtquick::testAttribute(Qt::WidgetAttribute) const
{
    return {};
}

void ViewWrapper_qtquick::setCursor(Qt::CursorShape shape)
{
    m_item->QQuickItem::setCursor(shape);
}

QSize ViewWrapper_qtquick::minSize() const
{
    if (auto view = unwrap()) {
        // Only real views have min size
        return view->minSize();
    } else {
        qFatal("not implemented");
        return {};
    }
}

QVector<std::shared_ptr<View>> ViewWrapper_qtquick::childViews() const
{
    QVector<std::shared_ptr<View>> result;
    const auto childItems = m_item->childItems();
    for (QQuickItem *child : childItems) {
        result << asQQuickWrapper(child);
    }

    return result;
}

void ViewWrapper_qtquick::setParent(View *parent)
{
    if (auto view = unwrap()) {
        view->setParent(parent);
    } else {
        auto parentItem = Views::asQQuickItem(parent);
        m_item->QQuickItem::setParent(parentItem);
        m_item->QQuickItem::setParentItem(parentItem);
    }

    m_item->setVisible(false);
}

bool ViewWrapper_qtquick::close()
{
    return View_qtquick::close(m_item);
}

View *ViewWrapper_qtquick::unwrap()
{
    return qobject_cast<View_qtquick *>(m_item);
}

const View *ViewWrapper_qtquick::unwrap() const
{
    return qobject_cast<const View_qtquick *>(m_item);
}

QSizePolicy ViewWrapper_qtquick::sizePolicy() const
{
    if (auto view = unwrap()) {
        return view->sizePolicy();
    }
    return {};
}
