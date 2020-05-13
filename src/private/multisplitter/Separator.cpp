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

#include "Separator_p.h"
#include "Logging_p.h" // TODO: Have our own
#include "Item_p.h"

#include <QMouseEvent>
#include <QRubberBand>
#include <QApplication>

#ifdef Q_OS_WIN
# include <windows.h>
#endif

using namespace Layouting;

Separator* Separator::s_separatorBeingDragged = nullptr;

static SeparatorFactoryFunc s_separatorFactoryFunc = nullptr;
bool Separator::usesLazyResize = false;

struct Separator::Private {
    // Only set when anchor is moved through mouse. Side1 if going towards left or top, Side2 otherwise.

    Qt::Orientation orientation;
    QRect geometry;
    int lazyPosition = 0;
    // SeparatorOptions m_options; TODO: Have a Layouting::Config
    QRubberBand *lazyResizeRubberBand = nullptr;
    ItemContainer *parentContainer = nullptr;
    Layouting::Side lastMoveDirection = Side1;
};

Separator::Separator(QWidget *hostWidget)
    : QWidget(hostWidget)
    , d(new Private())
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

void Separator::mousePressEvent(QMouseEvent *)
{
    s_separatorBeingDragged = this;

    qCDebug(separators) << "Drag started";

    if (d->lazyResizeRubberBand) {
        setLazyPosition(position());
        d->lazyResizeRubberBand->show();
    }
}

void Separator::mouseMoveEvent(QMouseEvent *ev)
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

    const int positionToGoTo = Layouting::pos(mapToParent(ev->pos()), d->orientation);
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

void Separator::mouseReleaseEvent(QMouseEvent *)
{
    onMouseReleased();
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

QWidget *Separator::hostWidget() const
{
    return parentWidget();
}

void Separator::init(ItemContainer *parentContainer, Qt::Orientation orientation)
{
    d->parentContainer = parentContainer;
    d->orientation = orientation;
    d->lazyResizeRubberBand = usesLazyResize ? new QRubberBand(QRubberBand::Line, hostWidget())
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

void Separator::setSeparatorFactoryFunc(SeparatorFactoryFunc func)
{
    s_separatorFactoryFunc = func;
}

Separator* Separator::createSeparator(QWidget *host)
{
    if (s_separatorFactoryFunc)
        return s_separatorFactoryFunc(host);

    return new Separator(host);
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
