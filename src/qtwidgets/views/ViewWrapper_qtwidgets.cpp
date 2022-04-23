/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewWrapper_qtwidgets.h"
#include "qtwidgets/views/DockWidget_qtwidgets.h"
#include "qtwidgets/views/FloatingWindow_qtwidgets.h"
#include "qtwidgets/views/Frame_qtwidgets.h"
#include "qtwidgets/views/MainWindow_qtwidgets.h"
#include "qtwidgets/views/Separator_qtwidgets.h"
#include "qtwidgets/views/SideBar_qtwidgets.h"
#include "qtwidgets/views/Stack_qtwidgets.h"
#include "qtwidgets/views/TabBar_qtwidgets.h"
#include "qtwidgets/views/TitleBar_qtwidgets.h"
#include "qtwidgets/Window_qtwidgets.h"

#include "private/MultiSplitter_p.h"
#include "private/MDILayoutWidget_p.h"
#include "MDIArea.h"
#include "controllers/DropArea.h"

#include <QWindow>
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
        case Type::MultiSplitter:
        case Type::MDILayout:
        case Type::Layout:
            if (auto view = qobject_cast<LayoutWidget *>(widget))
                return view->controller();
            break;
        case Type::MDIArea:
            if (auto view = qobject_cast<MDIArea *>(widget))
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

std::shared_ptr<Window> ViewWrapper_qtwidgets::windowHandle() const
{
    if (QWindow *w = m_widget->window()->windowHandle())
        return std::shared_ptr<Window>(new Window_qtwidgets(w));

    return nullptr;
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

bool ViewWrapper_qtwidgets::isMinimized() const
{
    return m_widget->isMinimized();
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
    case Type::MultiSplitter:
        return qobject_cast<MultiSplitter *>(m_widget);
    case Type::MDILayout:
        return qobject_cast<MDILayoutWidget *>(m_widget);
    case Type::MDIArea:
        return qobject_cast<MDIArea *>(m_widget);
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

std::shared_ptr<ViewWrapper> ViewWrapper_qtwidgets::window() const
{
    if (auto w = m_widget->window())
        return std::shared_ptr<ViewWrapper>(new ViewWrapper_qtwidgets(w));

    return {};
}

std::shared_ptr<ViewWrapper> ViewWrapper_qtwidgets::parentView() const
{
    if (auto p = m_widget->parentWidget())
        return std::shared_ptr<ViewWrapper>(new ViewWrapper_qtwidgets(p));

    return {};
}

std::shared_ptr<ViewWrapper> ViewWrapper_qtwidgets::childViewAt(QPoint localPos) const
{
    if (QWidget *child = m_widget->childAt(localPos))
        return std::shared_ptr<ViewWrapper>(new ViewWrapper_qtwidgets(child));

    return {};
}

HANDLE ViewWrapper_qtwidgets::handle() const
{
    return reinterpret_cast<HANDLE>(m_widget.data());
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

QString ViewWrapper_qtwidgets::objectName() const
{
    return m_widget->QWidget::objectName();
}

QVariant ViewWrapper_qtwidgets::property(const char *name) const
{
    return m_widget->property(name);
}

bool ViewWrapper_qtwidgets::isNull() const
{
    return m_widget.data() == nullptr;
}

DropArea *ViewWrapper_qtwidgets::asDropArea() const
{
    return qobject_cast<DropArea *>(m_widget);
}

QWidget *ViewWrapper_qtwidgets::widget() const
{
    return m_widget;
}

void ViewWrapper_qtwidgets::setWindowTitle(const QString &title)
{
    m_widget->setWindowTitle(title);
}

QPoint ViewWrapper_qtwidgets::mapTo(View *someAncestor, QPoint pos) const
{
    return m_widget->mapTo(qobject_cast<QWidget *>(someAncestor->asQObject()), pos);
}
