/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewWrapper.h"
#include "core/View_p.h"
#include "qtwidgets/views/DockWidget.h"
#include "qtwidgets/views/DropArea.h"
#include "qtwidgets/views/FloatingWindow.h"
#include "qtwidgets/views/Group.h"
#include "qtwidgets/views/MainWindow.h"
#include "qtwidgets/views/MDILayout.h"
#include "qtwidgets/views/Separator.h"
#include "qtwidgets/views/SideBar.h"
#include "qtwidgets/views/Stack.h"
#include "qtwidgets/views/TabBar.h"
#include "qtwidgets/views/TitleBar.h"
#include "qtwidgets/views/RubberBand.h"
#include "qtwidgets/Window.h"
#include "qtwidgets/views/MDIArea.h"

#include "kddockwidgets/core/MDILayout.h"
#include "kddockwidgets/core/DropArea.h"
#include "kddockwidgets/core/SideBar.h"

#include <QWindow>
#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::qtwidgets;

static Core::Controller *controllerForWidget(QWidget *widget)
{
    // KDDW deals in views, but sometimes we might get a native type like QWidget, for example if
    // you call someview->window(). This function let's us retrieve the actual controller of the
    // stray QWidget.

    for (int i = int(Core::ViewType::FIRST); i <= int(Core::ViewType::LAST); i *= 2) {
        // Using a for+switch pattern so that compiler reminds us if new enumerators are added to
        // enum
        switch (Core::ViewType(i)) {
        case Core::ViewType::Frame:
            if (auto view = qobject_cast<Group *>(widget))
                return view->controller();
            break;
        case Core::ViewType::TitleBar:
            if (auto view = qobject_cast<TitleBar *>(widget))
                return view->controller();
            break;
        case Core::ViewType::TabBar:
            if (auto view = qobject_cast<TabBar *>(widget))
                return view->controller();
            break;
        case Core::ViewType::Stack:
            if (auto view = qobject_cast<Stack *>(widget))
                return view->controller();
            break;
        case Core::ViewType::FloatingWindow:
            if (auto view = qobject_cast<FloatingWindow *>(widget))
                return view->controller();
            break;
        case Core::ViewType::Separator:
            if (auto view = qobject_cast<Separator *>(widget))
                return view->controller();
            break;
        case Core::ViewType::DockWidget:
            if (auto view = qobject_cast<DockWidget *>(widget))
                return view->controller();
            break;
        case Core::ViewType::DropArea:
            if (auto view = qobject_cast<DropArea *>(widget))
                return view->controller();
            break;
        case Core::ViewType::MDILayout:
            if (auto view = qobject_cast<MDILayout *>(widget))
                return view->controller();
            break;

        case Core::ViewType::MDIArea:
            if (auto view = qobject_cast<MDIArea *>(widget))
                return view->controller();
            break;
        case Core::ViewType::SideBar:
            if (auto view = qobject_cast<SideBar *>(widget))
                return view->controller();
            break;
        case Core::ViewType::MainWindow:
            if (auto view = qobject_cast<MainWindow *>(widget))
                return view->controller();
            break;
        case Core::ViewType::RubberBand:
        case Core::ViewType::LayoutItem:
        case Core::ViewType::ViewWrapper:
        case Core::ViewType::DropAreaIndicatorOverlay:
        case Core::ViewType::None:
            // skip internal types
            continue;
            break;
        }
    }

    return nullptr;
}

/*static*/
std::shared_ptr<Core::View> ViewWrapper_qtwidgets::create(QObject *widget)
{
    return create(qobject_cast<QWidget *>(widget));
}

/*static*/
std::shared_ptr<Core::View> ViewWrapper_qtwidgets::create(QWidget *widget)
{
    if (!widget)
        return {};

    auto wrapper = new ViewWrapper_qtwidgets(widget);
    auto sharedptr = std::shared_ptr<View>(wrapper);
    wrapper->d->m_thisWeakPtr = sharedptr;

    return sharedptr;
}

ViewWrapper_qtwidgets::ViewWrapper_qtwidgets(QObject *widget)
    : ViewWrapper_qtwidgets(qobject_cast<QWidget *>(widget))
{
}

ViewWrapper_qtwidgets::ViewWrapper_qtwidgets(QWidget *widget)
    : qtcommon::ViewWrapper(controllerForWidget(widget), widget)
    , m_widget(widget)
{
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

std::shared_ptr<Core::Window> ViewWrapper_qtwidgets::window() const
{
    if (m_widget->window()->windowHandle())
        return std::shared_ptr<Core::Window>(new Window(m_widget->window()));

    return nullptr;
}

bool ViewWrapper_qtwidgets::isRootView() const
{
    return m_widget->isWindow();
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

void ViewWrapper_qtwidgets::setSize(int x, int y)
{
    m_widget->resize(x, y);
}

bool ViewWrapper_qtwidgets::is(Core::ViewType t) const
{
    if (t == Core::ViewType::ViewWrapper)
        return true;

    switch (t) {

    case Core::ViewType::Frame:
        return qobject_cast<qtwidgets::Group *>(m_widget);
    case Core::ViewType::TitleBar:
        return qobject_cast<qtwidgets::TitleBar *>(m_widget);
    case Core::ViewType::TabBar:
        return qobject_cast<qtwidgets::TabBar *>(m_widget);
    case Core::ViewType::Stack:
        return qobject_cast<qtwidgets::Stack *>(m_widget);
    case Core::ViewType::FloatingWindow:
        return qobject_cast<qtwidgets::FloatingWindow *>(m_widget);
    case Core::ViewType::Separator:
        return qobject_cast<qtwidgets::Separator *>(m_widget);
    case Core::ViewType::DockWidget:
        return qobject_cast<qtwidgets::DockWidget *>(m_widget);
    case Core::ViewType::SideBar:
        return qobject_cast<qtwidgets::SideBar *>(m_widget);
    case Core::ViewType::MainWindow:
        return qobject_cast<qtwidgets::MainWindow *>(m_widget);
    case Core::ViewType::DropArea:
        return qobject_cast<qtwidgets::DropArea *>(m_widget);
    case Core::ViewType::MDILayout:
        return qobject_cast<MDILayout *>(m_widget);
    case Core::ViewType::RubberBand:
        return qobject_cast<RubberBand *>(m_widget);
    case Core::ViewType::MDIArea:
        return qobject_cast<MDIArea *>(m_widget);
    case Core::ViewType::LayoutItem:
    case Core::ViewType::None:
    case Core::ViewType::DropAreaIndicatorOverlay:
        qWarning() << Q_FUNC_INFO << "These are framework internals that are not wrapped";
        return false;
    case Core::ViewType::ViewWrapper:
        return true;
    }

    qWarning() << Q_FUNC_INFO << "Unknown type" << static_cast<int>(t);
    return false;
}

std::shared_ptr<Core::View> ViewWrapper_qtwidgets::rootView() const
{
    if (auto w = m_widget->window())
        return std::shared_ptr<Core::View>(new ViewWrapper_qtwidgets(w));

    return {};
}

std::shared_ptr<Core::View> ViewWrapper_qtwidgets::parentView() const
{
    if (auto p = m_widget->parentWidget())
        return std::shared_ptr<Core::View>(new ViewWrapper_qtwidgets(p));

    return {};
}

std::shared_ptr<Core::View> ViewWrapper_qtwidgets::childViewAt(QPoint localPos) const
{
    if (QWidget *child = m_widget->childAt(localPos))
        return std::shared_ptr<Core::View>(new ViewWrapper_qtwidgets(child));

    return {};
}

void ViewWrapper_qtwidgets::grabMouse()
{
    m_widget->grabMouse();
}

void ViewWrapper_qtwidgets::releaseMouse()
{
    m_widget->releaseMouse();
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
    return m_widget->mapTo(View_qt::asQWidget(someAncestor), pos);
}

bool ViewWrapper_qtwidgets::testAttribute(Qt::WidgetAttribute attr) const
{
    return m_widget->testAttribute(attr);
}

void ViewWrapper_qtwidgets::setCursor(Qt::CursorShape cursor)
{
    m_widget->setCursor(cursor);
}

QSize ViewWrapper_qtwidgets::minSize() const
{
    const int minW = m_widget->minimumWidth() > 0 ? m_widget->minimumWidth()
                                                  : m_widget->minimumSizeHint().width();

    const int minH = m_widget->minimumHeight() > 0 ? m_widget->minimumHeight()
                                                   : m_widget->minimumSizeHint().height();

    return QSize(minW, minH).expandedTo(View::hardcodedMinimumSize());
}

QVector<std::shared_ptr<Core::View>> ViewWrapper_qtwidgets::childViews() const
{
    return qtwidgets::View_qtwidgets<QWidget>::childViewsFor(m_widget);
}

void ViewWrapper_qtwidgets::setParent(View *parent)
{
    qtwidgets::View_qtwidgets<QWidget>::setParentFor(m_widget, parent);
}

bool ViewWrapper_qtwidgets::close()
{
    return m_widget->close();
}

Qt::FocusPolicy ViewWrapper_qtwidgets::focusPolicy() const
{
    return m_widget->focusPolicy();
}

void ViewWrapper_qtwidgets::setFocusPolicy(Qt::FocusPolicy policy)
{
    m_widget->setFocusPolicy(policy);
}

bool ViewWrapper_qtwidgets::hasFocus() const
{
    return m_widget->hasFocus();
}

SizePolicy ViewWrapper_qtwidgets::horizontalSizePolicy() const
{
    return SizePolicy(m_widget->sizePolicy().horizontalPolicy());
}

SizePolicy ViewWrapper_qtwidgets::verticalSizePolicy() const
{
    return SizePolicy(m_widget->sizePolicy().verticalPolicy());
}

QSize ViewWrapper_qtwidgets::maxSizeHint() const
{
    return m_widget->maximumSize();
}
