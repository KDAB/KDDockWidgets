/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Separator.h"
#include "layouting/Item_p.h"
#include "View.h"
#include "core/Logging_p.h"
#include "Config.h"
#include "Platform.h"
#include "Controller.h"
#include "core/ViewFactory.h"


#ifdef Q_OS_WIN
#include <Windows.h>
#endif

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

Separator *Separator::s_separatorBeingDragged = nullptr;

/// @brief internal counter just for unit-tests
static int s_numSeparators = 0;

namespace {

bool rubberBandIsTopLevel()
{
    return KDDockWidgets::Config::self().internalFlags()
        & KDDockWidgets::Config::InternalFlag_TopLevelIndicatorRubberBand;
}

}

struct Separator::Private
{
    // Only set when anchor is moved through mouse. Side1 if going towards left or top, Side2
    // otherwise.

    explicit Private(View *host)
        : m_hostView(host)
    {
        s_numSeparators++;
    }

    ~Private()
    {
        s_numSeparators--;
    }

    Qt::Orientation orientation = Qt::Horizontal;
    Rect geometry;
    int lazyPosition = 0;
    View *lazyResizeRubberBand = nullptr;
    Core::ItemBoxContainer *parentContainer = nullptr;
    Core::Side lastMoveDirection = Core::Side1;
    const bool usesLazyResize = Config::self().flags() & Config::Flag_LazyResize;

    View *const m_hostView;
};

Separator::Separator(View *host)
    : Controller(ViewType::Separator, Config::self().viewFactory()->createSeparator(this, host))
    , d(new Private(host))
{
    assert(view());
    view()->show();
}

Separator::~Separator()
{
    delete d;
}

void Separator::init(Core::ItemBoxContainer *parentContainer, Qt::Orientation orientation)
{
    if (!parentContainer) {
        KDDW_ERROR("null parentContainer");
        return;
    }

    d->parentContainer = parentContainer;
    d->orientation = orientation;
    view()->init();
    d->lazyResizeRubberBand = d->usesLazyResize ? Config::self().viewFactory()->createRubberBand(
                                  rubberBandIsTopLevel() ? nullptr : d->m_hostView)
                                                : nullptr;
    setVisible(true);
}

bool Separator::isVertical() const
{
    return d->orientation == Qt::Vertical;
}

void Separator::move(int p)
{
    if (p == position())
        return;

    Rect geo = d->geometry;
    if (isVertical()) {
        geo.moveTop(p);
    } else {
        geo.moveLeft(p);
    }
    setGeometry(geo);

    if (View *v = view()) {
        if (isVertical()) {
            v->move(v->x(), p);
        } else {
            v->move(p, v->y());
        }
    }
}

int Separator::position() const
{
    const Point topLeft = d->geometry.topLeft();
    return isVertical() ? topLeft.y() : topLeft.x();
}

void Separator::setGeometry(Rect r)
{
    if (r == d->geometry)
        return;

    d->geometry = r;

    if (View *v = view()) {
        v->setGeometry(r);
    }

    setVisible(true);
}

void Separator::setGeometry(int pos, int pos2, int length)
{
    Rect newGeo = d->geometry;
    if (isVertical()) {
        // The separator itself is horizontal
        newGeo.setSize(Size(length, Core::Item::separatorThickness));
        newGeo.moveTo(pos2, pos);
    } else {
        // The separator itself is vertical
        newGeo.setSize(Size(Core::Item::separatorThickness, length));
        newGeo.moveTo(pos, pos2);
    }

    setGeometry(newGeo);
}

Qt::Orientation Separator::orientation() const
{
    return d->orientation;
}

void Separator::setLazyPosition(int pos)
{
    if (pos == d->lazyPosition)
        return;

    View *v = view();

    d->lazyPosition = pos;

    Rect geo = v->geometry();
    if (isVertical()) {
        geo.moveTop(pos);
    } else {
        geo.moveLeft(pos);
    }

    if (rubberBandIsTopLevel() && Platform::instance()->isQtWidgets())
        geo.translate(d->m_hostView->mapToGlobal(Point(0, 0)));
    d->lazyResizeRubberBand->setGeometry(geo);
}

bool Separator::isBeingDragged() const
{
    return s_separatorBeingDragged == this;
}

bool Separator::usesLazyResize() const
{
    return d->usesLazyResize;
}

void Separator::onMousePress()
{
    s_separatorBeingDragged = this;

    KDDW_DEBUG("Drag started");

    if (d->lazyResizeRubberBand) {
        setLazyPosition(position());
        d->lazyResizeRubberBand->show();
        if (rubberBandIsTopLevel() && Platform::instance()->isQtWidgets())
            d->lazyResizeRubberBand->raise();
    }
}

void Separator::onMouseReleased()
{
    if (d->lazyResizeRubberBand) {
        d->lazyResizeRubberBand->hide();
        d->parentContainer->requestSeparatorMove(this, d->lazyPosition - position());
    }

    s_separatorBeingDragged = nullptr;
}

void Separator::onMouseDoubleClick()
{
    // a double click means we'll resize the left and right neighbour so that they occupy
    // the same size (or top/bottom, depending on orientation).
    d->parentContainer->requestEqualSize(this);
}

void Separator::onMouseMove(Point pos)
{
    if (!isBeingDragged())
        return;

    if (Platform::instance()->isQt()) {
        // Workaround a bug in Qt where we're getting mouse moves without without the button being
        // pressed
        if (!Platform::instance()->isLeftMouseButtonPressed()) {
            KDDW_DEBUG(
                "Separator::onMouseMove: Ignoring spurious mouse event. Someone ate our ReleaseEvent");
            onMouseReleased();
            return;
        }

#ifdef KDDW_FRONTEND_QT_WINDOWS
        // Try harder, Qt can be wrong, if mixed with MFC
        const bool mouseButtonIsReallyDown =
            (GetKeyState(VK_LBUTTON) & 0x8000) || (GetKeyState(VK_RBUTTON) & 0x8000);
        if (!mouseButtonIsReallyDown) {
            KDDW_DEBUG(
                "Separator::onMouseMove: Ignoring spurious mouse event. Someone ate our ReleaseEvent");
            onMouseReleased();
            return;
        }
#endif
    }

    const int positionToGoTo = Core::pos(pos, d->orientation);
    const int minPos = d->parentContainer->minPosForSeparator_global(this);
    const int maxPos = d->parentContainer->maxPosForSeparator_global(this);

    if ((positionToGoTo > maxPos && position() <= positionToGoTo)
        || (positionToGoTo < minPos && position() >= positionToGoTo)) {
        // if current pos is 100, and max is 80, we do allow going to 90.
        // Would continue to violate, but only by 10, so allow.

        // On the other hand, if we're already past max-pos, don't make it worse and just
        // return if positionToGoTo is further away from maxPos.

        // Same reasoning for minPos
        return;
    }

    d->lastMoveDirection = positionToGoTo < position()
        ? Core::Side1
        : (positionToGoTo > position() ? Core::Side2
                                       : Core::Side1); // Last case shouldn't happen though.

    if (d->lazyResizeRubberBand)
        setLazyPosition(positionToGoTo);
    else
        d->parentContainer->requestSeparatorMove(this, positionToGoTo - position());
}

Core::ItemBoxContainer *Separator::parentContainer() const
{
    return d->parentContainer;
}

/** static */
bool Separator::isResizing()
{
    return s_separatorBeingDragged != nullptr;
}

/** static */
int Separator::numSeparators()
{
    return s_numSeparators;
}
