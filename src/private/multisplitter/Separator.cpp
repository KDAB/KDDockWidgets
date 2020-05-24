/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Widget_qwidget.h"
#include "Separator_p.h"
#include "Logging_p.h"
#include "Item_p.h"
#include "Config.h"

#include <QGuiApplication>

#ifdef Q_OS_WIN
# include <windows.h>
#endif

using namespace Layouting;

Separator* Separator::s_separatorBeingDragged = nullptr;

struct Separator::Private
{
    // Only set when anchor is moved through mouse. Side1 if going towards left or top, Side2 otherwise.

    Private(Widget *host)
        : m_hostWidget(host) {}

    Qt::Orientation orientation;
    QRect geometry;
    int lazyPosition = 0;
    // SeparatorOptions m_options; TODO: Have a Layouting::Config
    Widget *lazyResizeRubberBand = nullptr;
    ItemContainer *parentContainer = nullptr;
    Layouting::Side lastMoveDirection = Side1;
    const bool usesLazyResize = Config::self().flags() & Config::Flag::LazyResize;
    Widget *const m_hostWidget;
};

Separator::Separator(Widget *hostWidget)
    : QWidget(hostWidget->asWidget())
    , d(new Private(hostWidget))
{
}

Separator::~Separator()
{
    delete d;
    if (isBeingDragged())
        s_separatorBeingDragged = nullptr;
}

bool Separator::isVertical() const
{
    return d->orientation == Qt::Vertical;
}

void Separator::move(int p)
{
    if (isVertical()) {
        QWidget::move(x(), p);
    } else {
        QWidget::move(p, y());
    }
}

Qt::Orientation Separator::orientation() const
{
    return d->orientation;
}

void Separator::onMousePress()
{
    s_separatorBeingDragged = this;

    qCDebug(separators) << "Drag started";

    if (d->lazyResizeRubberBand) {
        setLazyPosition(position());
        d->lazyResizeRubberBand->show();
    }
}

void Separator::onMouseDoubleClick()
{
    // a double click means we'll resize the left and right neighbour so that they occupy
    // the same size (or top/bottom, depending on orientation).
    d->parentContainer->requestEqualSize(this);
}

void Separator::onMouseMove(QPoint pos)
{
    if (!isBeingDragged())
        return;

    if (!(qApp->mouseButtons() & Qt::LeftButton)) {
        qCDebug(separators) << Q_FUNC_INFO << "Ignoring spurious mouse event. Someone ate our ReleaseEvent";
        onMouseReleased();
        return;
    }

#ifdef Q_OS_WIN
    // Try harder, Qt can be wrong, if mixed with MFC
    const bool mouseButtonIsReallyDown = (GetKeyState(VK_LBUTTON) & 0x8000) || (GetKeyState(VK_RBUTTON) & 0x8000);
    if (!mouseButtonIsReallyDown) {
        qCDebug(separators) << Q_FUNC_INFO << "Ignoring spurious mouse event. Someone ate our ReleaseEvent";
        onMouseReleased();
        return;
    }
#endif

    const int positionToGoTo = Layouting::pos(mapToParent(pos), d->orientation);
    const int minPos = d->parentContainer->minPosForSeparator_global(this);
    const int maxPos = d->parentContainer->maxPosForSeparator_global(this);

    if (positionToGoTo < minPos || positionToGoTo > maxPos)
        return;

    d->lastMoveDirection = positionToGoTo < position() ? Side1
                                                       : (positionToGoTo > position() ? Side2
                                                                                      : Side2); // Last case shouldn't happen though.

    if (d->lazyResizeRubberBand)
        setLazyPosition(positionToGoTo);
    else
        d->parentContainer->requestSeparatorMove(this, positionToGoTo - position());
}

void Separator::onMouseReleased()
{
    if (d->lazyResizeRubberBand) {
        d->lazyResizeRubberBand->hide();
        d->parentContainer->requestSeparatorMove(this, d->lazyPosition - position());
    }

    s_separatorBeingDragged = nullptr;
}

void Separator::setGeometry(QRect r)
{
    if (r != d->geometry) {
        d->geometry = r;
        QWidget::setGeometry(r);
        setVisible(true);
    }
}

int Separator::position() const
{
    const QPoint topLeft = d->geometry.topLeft();
    return isVertical() ? topLeft.y() : topLeft.x();
}

QObject *Separator::host() const
{
    return d->m_hostWidget ? d->m_hostWidget->asQObject() : nullptr;
}

void Separator::init(ItemContainer *parentContainer, Qt::Orientation orientation)
{
    if (!parentContainer) {
        qWarning() << Q_FUNC_INFO << "null parentContainer";
        return;
    }

    d->parentContainer = parentContainer;
    d->orientation = orientation;
    d->lazyResizeRubberBand = d->usesLazyResize ? createRubberBand(d->m_hostWidget)
                                                : nullptr;
    setVisible(true);
}

ItemContainer *Separator::parentContainer() const
{
    return d->parentContainer;
}

void Separator::setGeometry(int pos, int pos2, int length)
{
    QRect newGeo = d->geometry;
    if (isVertical()) {
        // The separator itself is horizontal
        newGeo.setSize(QSize(length, Item::separatorThickness));
        newGeo.moveTo(pos2, pos);
    } else {
        // The separator itself is vertical
        newGeo.setSize(QSize(Item::separatorThickness, length));
        newGeo.moveTo(pos, pos2);
    }

    setGeometry(newGeo);
}

bool Separator::isResizing()
{
    return s_separatorBeingDragged != nullptr;
}

void Separator::setLazyPosition(int pos)
{
    if (d->lazyPosition != pos) {
        d->lazyPosition = pos;

        QRect geo = geometry();
        if (isVertical()) {
            geo.moveTop(pos);
        } else {
            geo.moveLeft(pos);
        }

        d->lazyResizeRubberBand->setGeometry(geo);
    }
}

bool Separator::isBeingDragged() const
{
    return s_separatorBeingDragged == this;
}
