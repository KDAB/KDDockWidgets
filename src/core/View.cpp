/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "View.h"
#include "core/View_p.h"
#include "core/Utils_p.h"
#include "core/layouting/Item_p.h"
#include "core/EventFilterInterface.h"
#include "core/FloatingWindow.h"
#include "core/Group.h"
#include "core/Stack.h"
#include "core/TitleBar.h"
#include "core/TabBar.h"
#include "core/MainWindow.h"
#include "core/DropArea.h"
#include "core/MDILayout.h"

#include "core/Platform.h"
#include "core/Window.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

namespace KDDockWidgets {
static qint64 s_nextId = 1;

Controller *maybeCreateController(Controller *controller, ViewType type, View *view)
{
    if (controller)
        return controller;

    if (type == ViewType::ViewWrapper)
        return new Controller(ViewType::ViewWrapper, view);

    return new Controller(ViewType::None, view);
}

}

View::View(Controller *controller, ViewType type)
    : d(new Private(this, QString::number(KDDockWidgets::s_nextId++), type))
    , m_controller(maybeCreateController(controller, type, this))
{
}

View::~View()
{
    m_inDtor = true;
    d->beingDestroyed.emit();

    if (!freed() && !is(ViewType::ViewWrapper) && !is(ViewType::DropAreaIndicatorOverlay)) {
        // TODOm3
        // Views should be deleted via View::free()!
        // However some of our deletes are coming from widgets parent destroying their children
        // But we want the controllers to drive things instead. For now detect the view destruction
        // and destroy its controller, which was the old behaviour.
        delete m_controller;
    }

#ifdef KDDW_FRONTEND_FLUTTER
    const auto children = m_childViews;
    for (auto child : children)
        delete child;

    m_childViews.clear();
#endif

    delete d;
}

QString View::Private::id() const
{
    return m_id;
}

ViewType View::Private::type() const
{
    return m_type;
}

void View::free()
{
    if (d->m_freed) {
        qWarning() << Q_FUNC_INFO << "Free already called";
        return;
    }

    d->m_freed = true;
    delete this;
}

void View::init()
{
}

bool View::freed() const
{
    return d->m_freed;
}

bool View::inDtor() const
{
    return m_inDtor;
}

void View::setZOrder(int)
{
}

QSize View::size() const
{
    return geometry().size();
}

QPoint View::pos() const
{
    return geometry().topLeft();
}

QRect View::rect() const
{
    return QRect(QPoint(0, 0), size());
}

int View::x() const
{
    return geometry().x();
}

int View::y() const
{
    return geometry().y();
}

int View::height() const
{
    return geometry().height();
}

int View::width() const
{
    return geometry().width();
}

void View::move(QPoint pt)
{
    move(pt.x(), pt.y());
}

void View::resize(QSize sz)
{
    setSize(sz.width(), sz.height());
}

void View::setSize(QSize sz)
{
    setSize(sz.width(), sz.height());
}

void View::resize(int w, int h)
{
    setSize(w, h);
}

Controller *View::controller() const
{
    return m_controller;
}

/** static */
QSize View::hardcodedMinimumSize()
{
    return Core::Item::hardcodedMinimumSize;
}

bool View::is(ViewType t) const
{
    return int(d->m_type) & int(t);
}

Core::FloatingWindow *View::asFloatingWindowController() const
{
    if (m_controller && m_controller->is(ViewType::FloatingWindow))
        return qobject_cast<Core::FloatingWindow *>(m_controller);

    return nullptr;
}

Core::Group *View::asGroupController() const
{
    if (m_controller && m_controller->is(ViewType::Frame))
        return qobject_cast<Core::Group *>(m_controller);

    return nullptr;
}

Core::TitleBar *View::asTitleBarController() const
{
    if (m_controller && m_controller->is(ViewType::TitleBar))
        return qobject_cast<Core::TitleBar *>(m_controller);

    return nullptr;
}

Core::TabBar *View::asTabBarController() const
{
    if (m_controller && m_controller->is(ViewType::TabBar))
        return qobject_cast<Core::TabBar *>(m_controller);

    return nullptr;
}

Core::Stack *View::asStackController() const
{
    if (m_controller && m_controller->is(ViewType::Stack))
        return qobject_cast<Core::Stack *>(m_controller);

    return nullptr;
}

Core::DockWidget *View::asDockWidgetController() const
{
    if (m_controller && m_controller->is(ViewType::DockWidget))
        return qobject_cast<Core::DockWidget *>(m_controller);

    return nullptr;
}

Core::MainWindow *View::asMainWindowController() const
{
    if (m_controller && m_controller->is(ViewType::MainWindow))
        return qobject_cast<Core::MainWindow *>(m_controller);

    return nullptr;
}

Core::DropArea *View::asDropAreaController() const
{
    if (!m_inDtor && m_controller && m_controller->is(ViewType::DropArea)) {
        return qobject_cast<Core::DropArea *>(m_controller);
    }
    return nullptr;
}

Core::MDILayout *View::asMDILayoutController() const
{
    if (!m_inDtor && m_controller && m_controller->is(ViewType::MDILayout))
        return qobject_cast<Core::MDILayout *>(m_controller);

    return nullptr;
}

Core::Layout *View::asLayout() const
{
    if (Core::DropArea *da = asDropAreaController()) {
        return da;
    } else if (Core::MDILayout *mdi = asMDILayoutController()) {
        return mdi;
    }

    return nullptr;
}

bool View::equals(const View *other) const
{
    return other && handle() == other->handle();
}

bool View::equals(const std::shared_ptr<View> &other) const
{
    if (isNull() || !other || other->isNull()) {
        // We don't care about nullity for identity
        return false;
    }

    return handle() == other->handle();
}

bool View::isNull() const
{
    return false;
}

bool View::isInWindow(std::shared_ptr<Core::Window> window) const
{
    if (!window)
        return false;

    if (auto ourWindow = this->window())
        return ourWindow->equals(window);

    return false;
}

QSize View::parentSize() const
{
    if (auto p = parentView())
        return p->size();
    return {};
}

QRect View::windowGeometry() const
{
    if (Core::Window::Ptr window = this->window())
        return window->geometry();

    return {};
}

void View::closeRootView()
{
    if (auto view = rootView())
        view->close();
}

Screen::Ptr View::Private::screen() const
{
    if (Core::Window::Ptr window = q->window())
        return window->screen();

    return nullptr;
}

void View::Private::setAboutToBeDestroyed()
{
    m_aboutToBeDestroyed = true;
}

bool View::Private::aboutToBeDestroyed() const
{
    return m_aboutToBeDestroyed;
}

void View::dumpDebug()
{
    qDebug() << "View::dumpDebug:" << m_controller << int(d->type()) << "root=" << rootView()->controller();
}

/** static */
Controller *View::firstParentOfType(View *view, ViewType type)
{
    auto p = view->asWrapper();
    while (p) {
        if (p->is(type))
            return p->controller();

        // Ignore QObject hierarchies spanning though multiple windows
        if (p->isRootView())
            return nullptr;

        p = p->parentView();
    }

    return nullptr;
}

Controller *View::Private::firstParentOfType(ViewType type) const
{
    return View::firstParentOfType(const_cast<View *>(q), type);
}

void View::Private::requestClose(CloseEvent *e)
{
    closeRequested.emit(e);
}

QRect View::Private::globalGeometry() const
{
    QRect geo = q->geometry();
    if (!q->isRootView())
        geo.moveTopLeft(q->mapToGlobal(QPoint(0, 0)));
    return geo;
}

void View::createPlatformWindow()
{
    // Only qtwidgets need this
    qFatal("Shouldn't be called on this platform");
}

std::shared_ptr<Core::Window> View::Private::transientWindow() const
{
    if (auto w = q->window())
        return w->transientParent();

    return {};
}

bool View::onResize(int w, int h)
{
    d->resized.emit(QSize(w, h));
    return false;
}

bool View::onResize(QSize sz)
{
    return onResize(sz.width(), sz.height());
}

/** static */
bool View::equals(const View *one, const View *two)
{
    if ((one && !two) || (!one && two))
        return false;

    if (!one && !two)
        return true;

    return one->equals(two);
}

void View::installViewEventFilter(EventFilterInterface *filter)
{
    d->m_viewEventFilters.push_back(filter);
}

void View::removeViewEventFilter(EventFilterInterface *filter)
{
    d->m_viewEventFilters.erase(
        std::remove(d->m_viewEventFilters.begin(), d->m_viewEventFilters.end(), filter),
        d->m_viewEventFilters.end());
}

bool View::deliverViewEventToFilters(Event *ev)
{
    for (Core::EventFilterInterface *filter : qAsConst(d->m_viewEventFilters)) {
        if (ev->type() == Event::Move) {
            if (filter->onMoveEvent(this))
                return true;
        } else if (auto me = mouseEvent(ev)) {
            if (filter->onMouseEvent(this, me))
                return true;

            switch (ev->type()) {
            case Event::MouseButtonPress:
                if (filter->onMouseButtonPress(this, me))
                    return true;
                break;
            case Event::MouseButtonRelease:
                if (filter->onMouseButtonRelease(this, me))
                    return true;
                break;
            case Event::MouseMove:
                if (filter->onMouseButtonMove(this, me))
                    return true;
                break;
            case Event::MouseButtonDblClick:
                if (filter->onMouseDoubleClick(this, me))
                    return true;
                break;
            default:
                break;
            }
        }
    }

    return false;
}
