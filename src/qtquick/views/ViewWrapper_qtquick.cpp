/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewWrapper_qtquick.h"
#include "qtquick/views/RubberBand_qtquick.h"
#include "qtquick/views/View_qtquick.h"

#include "qtquick/views/DockWidget_qtquick.h"
#include "qtquick/views/FloatingWindow_qtquick.h"
#include "qtquick/views/Group_qtquick.h"
#include "kddockwidgets/views/MainWindow_qtquick.h"
#include "qtquick/views/Separator_qtquick.h"
#include "private/multisplitter/Item_p.h"
// #include "qtquick/views/SideBar_qtquick.h"
#include "qtquick/views/Stack_qtquick.h"
#include "qtquick/views/TabBar_qtquick.h"
#include "qtquick/views/TitleBar_qtquick.h"
#include "qtquick/views/MDILayout_qtquick.h"
#include "qtquick/views/DropArea_qtquick.h"

#include "../Window_qtquick.h"

#include "kddockwidgets/controllers/DropArea.h"
#include "kddockwidgets/controllers/MDILayout.h"
// #include "views/MDIArea_qtwidgets.h"

#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

namespace KDDockWidgets {
static Controller *controllerForItem(QQuickItem *item)
{
    // KDDW deals in views, but sometimes we might get a native type like QWidget, for example if you call
    // someview->window(). This function let's us retrieve the actual controller of the stray QWidget.

    for (int i = int(Type::FIRST); i <= int(::Type::LAST); i *= 2) {
        // Using a for+switch pattern so that compiler reminds us if new enumerators are added to enum
        switch (Type(i)) {
        case Type::Frame:
            if (auto view = qobject_cast<Group_qtquick *>(item))
                return view->controller();
            break;
        case Type::TitleBar:
            if (auto view = qobject_cast<TitleBar_qtquick *>(item))
                return view->controller();
            break;
        case Type::TabBar:
            if (auto view = qobject_cast<TabBar_qtquick *>(item))
                return view->controller();
            break;
        case Type::Stack:
            if (auto view = qobject_cast<Stack_qtquick *>(item))
                return view->controller();
            break;
        case Type::FloatingWindow:
            if (auto view = qobject_cast<FloatingWindow_qtquick *>(item))
                return view->controller();
            break;
        case Type::Separator:
            if (auto view = qobject_cast<Separator_qtquick *>(item))
                return view->controller();
            break;
        case Type::DockWidget:
            if (auto view = qobject_cast<DockWidget_qtquick *>(item))
                return view->controller();
            break;
        case Type::DropArea:
            if (auto view = qobject_cast<DropArea_qtquick *>(item))
                return view->controller();
            break;
        case Type::MDILayout:
            if (auto view = qobject_cast<MDILayout_qtquick *>(item))
                return view->controller();
            break;

        case Type::MDIArea:
        case Type::SideBar:
            // Not implemented for QtQuick yet
            break;
        case Type::MainWindow:
            if (auto view = qobject_cast<MainWindow_qtquick *>(item))
                return view->controller();
            break;
        case Type::RubberBand:
        case Type::LayoutItem:
        case Type::ViewWrapper:
        case Type::None:
            // skip internal types
            continue;
        }
    }

    return nullptr;
}
}

ViewWrapper_qtquick::ViewWrapper_qtquick(QObject *item)
    : ViewWrapper_qtquick(qobject_cast<QQuickItem *>(item))
{
}

ViewWrapper_qtquick::ViewWrapper_qtquick(QQuickItem *item)
    : ViewWrapper(controllerForItem(item), item)
    , m_item(item)
{
}

void ViewWrapper_qtquick::setObjectName(const QString &name)
{
    m_item->setObjectName(name);
}

QRect ViewWrapper_qtquick::geometry() const
{
    if (isRootView()) {
        if (QWindow *w = m_item->window()) {
            return w->geometry();
        }
    }

    return QRect(QPointF(m_item->x(), m_item->y()).toPoint(), m_item->size().toSize());
}

QPoint ViewWrapper_qtquick::mapToGlobal(QPoint localPt) const
{
    return m_item->mapToGlobal(localPt).toPoint();
}

QPoint ViewWrapper_qtquick::mapFromGlobal(QPoint globalPt) const
{
    return m_item->mapFromGlobal(globalPt).toPoint();
}

void ViewWrapper_qtquick::setGeometry(QRect rect)
{
    setSize(rect.width(), rect.height());
    ViewWrapper_qtquick::move(rect.topLeft().x(), rect.topLeft().y());
}

std::shared_ptr<ViewWrapper> ViewWrapper_qtquick::childViewAt(QPoint p) const
{
    auto child = m_item->childAt(p.x(), p.y());
    return child ? asQQuickWrapper(child) : nullptr;
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

void ViewWrapper_qtquick::setVisible(bool is)
{
    if (isRootView()) {
        if (QWindow *w = m_item->window()) {
            if (!w->isVisible()) {
                w->show();
            }
        }
    }

    m_item->setVisible(is);
}

bool ViewWrapper_qtquick::isVisible() const
{
    if (QWindow *w = m_item->window()) {
        if (!w->isVisible())
            return false;
    }

    return m_item->isVisible();
}

void ViewWrapper_qtquick::move(int x, int y)
{
    if (isRootView()) {
        if (QWindow *w = m_item->window()) {
            w->setPosition(x, y);
            return;
        }
    }

    m_item->setX(x);
    m_item->setY(y);
    setAttribute(Qt::WA_Moved);
}

void ViewWrapper_qtquick::activateWindow()
{
    if (QWindow *w = m_item->window())
        w->requestActivate();
}

bool ViewWrapper_qtquick::isMaximized() const
{
    if (QWindow *w = m_item->window())
        return w->windowStates() & Qt::WindowMaximized;

    return false;
}

bool ViewWrapper_qtquick::isMinimized() const
{
    if (QWindow *w = m_item->window())
        return w->windowStates() & Qt::WindowMinimized;

    return false;
}

QSize ViewWrapper_qtquick::maximumSize() const
{
    if (auto view = unwrap()) {
        return view->maximumSize();
    } else {
        const QSize max = m_item->property("kddockwidgets_max_size").toSize();
        return max.isEmpty() ? Layouting::Item::hardcodedMaximumSize
                             : max.boundedTo(Layouting::Item::hardcodedMaximumSize);
    }
}

void ViewWrapper_qtquick::setSize(int w, int h)
{
    if (isRootView()) {
        if (QWindow *window = m_item->window()) {
            QRect windowGeo = window->geometry();
            windowGeo.setSize(QSize(w, h));
            window->setGeometry(windowGeo);
        }
    }

    m_item->setSize(QSizeF(w, h));
}

bool ViewWrapper_qtquick::is(Type t) const
{
    if (t == Type::ViewWrapper)
        return true;

    switch (t) {

    case Type::Frame:
        return qobject_cast<Views::Group_qtquick *>(m_item);
    case Type::TitleBar:
        return qobject_cast<Views::TitleBar_qtquick *>(m_item);
    case Type::TabBar:
        return qobject_cast<Views::TabBar_qtquick *>(m_item);
    case Type::Stack:
        return qobject_cast<Views::Stack_qtquick *>(m_item);
    case Type::FloatingWindow:
        return qobject_cast<Views::FloatingWindow_qtquick *>(m_item);
    case Type::Separator:
        return qobject_cast<Views::Separator_qtquick *>(m_item);
    case Type::DockWidget:
        return qobject_cast<Views::DockWidget_qtquick *>(m_item);
    case Type::SideBar:
        return false; // QtQuick doesn't support sidebar yet
        // return qobject_cast<Views::SideBar_qtquick *>(m_item);
    case Type::MainWindow:
        return qobject_cast<Views::MainWindow_qtquick *>(m_item);
    case Type::DropArea:
        return qobject_cast<Views::DropArea_qtquick *>(m_item);
    case Type::MDILayout:
        return qobject_cast<Views::MDILayout_qtquick *>(m_item);
    case Type::RubberBand:
        return qobject_cast<Views::RubberBand_qtquick *>(m_item);
    case Type::MDIArea:
        return false; // Not support by qtquick
    case Type::LayoutItem:
    case Type::None:
        qWarning() << Q_FUNC_INFO << "These are framework internals that are not wrapped";
        return false;
    case Type::ViewWrapper:
        return true;
    }

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

void ViewWrapper_qtquick::setFocusPolicy(Qt::FocusPolicy policy)
{
    if (auto view = unwrap()) {
        view->setFocusPolicy(policy);
    } else {
        qFatal("not implemented");
    }
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

void ViewWrapper_qtquick::setWindowTitle(const QString &title)
{
    if (QWindow *w = m_item->window())
        w->setTitle(title);
}

QPoint ViewWrapper_qtquick::mapTo(View *parent, QPoint pos) const
{
    if (!parent)
        return {};

    auto parentItem = asQQuickItem(parent);
    return parentItem->mapFromGlobal(m_item->mapToGlobal(pos)).toPoint();
}

bool ViewWrapper_qtquick::testAttribute(Qt::WidgetAttribute attr) const
{
    if (auto view = unwrap()) {
        // Only real views have min size
        return view->testAttribute(attr);
    } else {
        qFatal("not implemented");
        return false;
    }
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
        const QSize min = m_item->property("kddockwidgets_min_size").toSize();
        return min.expandedTo(Layouting::Item::hardcodedMinimumSize);
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

SizePolicy ViewWrapper_qtquick::verticalSizePolicy() const
{
    if (auto view = unwrap()) {
        return view->verticalSizePolicy();
    }
    return {};
}

SizePolicy ViewWrapper_qtquick::horizontalSizePolicy() const
{
    if (auto view = unwrap()) {
        return view->horizontalSizePolicy();
    }
    return {};
}
