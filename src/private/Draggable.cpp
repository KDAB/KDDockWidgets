/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Draggable_p.h"
#include "DragController_p.h"
#include "WidgetResizeHandler_p.h"
#include "Utils_p.h"
#include "Platform.h"

#include "controllers/FloatingWindow.h"

using namespace KDDockWidgets;

class Draggable::Private
{
public:
    explicit Private(View *_thisView, bool _enabled)
        : thisView(_thisView)
        , enabled(_enabled)
    {
        Q_ASSERT(thisView);
    }

    QPointer<WidgetResizeHandler> widgetResizeHandler;
    View *const thisView;
    const bool enabled;
};

Draggable::Draggable(View *thisView, bool enabled)
    : d(new Private(thisView, enabled))
{
    if (thisView && d->enabled)
        DragController::instance()->registerDraggable(this);
}

Draggable::~Draggable()
{
    if (d->thisView && d->enabled)
        DragController::instance()->unregisterDraggable(this);
    delete d;
}

View *Draggable::asView() const
{
    return d->thisView;
}

bool Draggable::dragCanStart(QPoint pressPos, QPoint globalPos) const
{
    return (globalPos - pressPos).manhattanLength() > Platform::instance()->startDragDistance();
}

void Draggable::setWidgetResizeHandler(WidgetResizeHandler *w)
{
    Q_ASSERT(!d->widgetResizeHandler);
    Q_ASSERT(w);
    d->widgetResizeHandler = w;
}
