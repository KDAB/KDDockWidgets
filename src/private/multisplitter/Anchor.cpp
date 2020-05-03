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

#include "Anchor_p.h"
#include "Logging_p.h"
#include "Separator_p.h"

#include <QRubberBand>
#include <QApplication>
#include <QDebug>

#ifdef Q_OS_WIN
# include <Windows.h>
#endif

using namespace KDDockWidgets;
using namespace Layouting;

bool Anchor::s_isResizing = false;
Anchor* Anchor::s_separatorBeingDragged = nullptr;

static SeparatorFactoryFunc s_separatorFactoryFunc = nullptr;

static Separator* createSeparator(Anchor *a, QWidget *parent)
{
    if (s_separatorFactoryFunc)
        return s_separatorFactoryFunc(a, parent);

    return new Separator(a, parent);
}

Anchor::Anchor(ItemContainer *parentContainer, Qt::Orientation orientation,
               Options options, QWidget *hostWidget)
    : QObject(hostWidget)
    , m_orientation(orientation)
    , m_hostWidget(hostWidget)
    , m_separatorWidget(createSeparator(this, m_hostWidget))
    , m_options(options)
    , m_lazyResizeRubberBand((options & Option::LazyResize) ? new QRubberBand(QRubberBand::Line, hostWidget) : nullptr)
    , m_parentContainer(parentContainer)
{
    connect(this, &QObject::objectNameChanged, m_separatorWidget, &QObject::setObjectName);
}

Anchor::~Anchor()
{
    delete m_separatorWidget;
    if (s_separatorBeingDragged == this)
        s_separatorBeingDragged = nullptr;
}

QWidget *Anchor::hostWidget() const
{
    return m_hostWidget;
}

void Anchor::setGeometry(QRect r)
{
    if (r != m_geometry) {
        if (position() < 0) {
            qCDebug(separators) << Q_FUNC_INFO << "Old position was negative" << position() << "; new=" << r;
        }

        m_geometry = r;
        m_separatorWidget->setGeometry(r);
        m_separatorWidget->setVisible(true);
        Q_EMIT geometryChanged(r);
    }
}

bool Anchor::isVertical() const
{
    return m_orientation == Qt::Vertical;
}

Qt::Orientation Anchor::orientation() const
{
    return m_orientation;
}

void Anchor::setGeometry(int pos, int pos2, int length)
{
    QRect newGeo = m_geometry;
    if (isVertical()) {
        // The separator itself is horizontal
        newGeo.setSize(QSize(length, Item::separatorThickness()));
        newGeo.moveTo(pos2, pos);
    } else {
        // The separator itself is vertical
        newGeo.setSize(QSize(Item::separatorThickness(), length));
        newGeo.moveTo(pos, pos2);
    }

    setGeometry(newGeo);
}

int Anchor::position() const
{
    const QPoint topLeft = m_geometry.topLeft();
    return isVertical() ? topLeft.y() : topLeft.x();
}

bool Anchor::isBeingDragged() const
{
    return s_separatorBeingDragged == this;
}

bool Anchor::lazyResizeEnabled() const
{
    return m_options & Option::LazyResize;
}

Separator *Anchor::separatorWidget() const
{
    return m_separatorWidget;
}

void Anchor::setLazyPosition(int pos)
{
    if (m_lazyPosition != pos) {
        m_lazyPosition = pos;

        QRect geo = m_separatorWidget->geometry();
        if (isVertical()) {
            geo.moveLeft(pos);
        } else {
            geo.moveTop(pos);
        }

        m_lazyResizeRubberBand->setGeometry(geo);
    }
}

int Anchor::position(QPoint p) const
{
    return isVertical() ? p.y() : p.x();
}

void Anchor::setPosition(int p)
{
    QRect geo = m_geometry;
    QPoint pt = geo.topLeft();
    if (isVertical())
        pt.setY(p);
    else
        pt.setX(p);

    geo.moveTopLeft(pt);
    setGeometry(geo);
}

void Anchor::onMousePress()
{
    s_separatorBeingDragged = this;

    qCDebug(separators) << "Drag started";

    if (lazyResizeEnabled()) {
        setLazyPosition(position());
        m_lazyResizeRubberBand->show();
    }
}

void Anchor::onMouseReleased()
{
    if (m_lazyResizeRubberBand) {
        m_lazyResizeRubberBand->hide();
        setPosition(m_lazyPosition);
    }

    s_separatorBeingDragged = nullptr;
}

void Anchor::onMouseMoved(QPoint pt)
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
        qCDebug(mouseevents) << Q_FUNC_INFO << "Ignoring spurious mouse event. Someone ate our ReleaseEvent";
        onMouseReleased();
        return;
    }
#endif

    const int positionToGoTo = position(pt);
    const int minPos = m_parentContainer->minPosForSeparator_global(this);
    const int maxPos = m_parentContainer->maxPosForSeparator_global(this);

    qDebug() << "foo" << minPos << positionToGoTo << maxPos;

    if (positionToGoTo < minPos || positionToGoTo > maxPos)
        return;

    m_lastMoveDirection = positionToGoTo < position() ? Side1
                                                      : (positionToGoTo > position() ? Side2
                                                                                     : Side2); // Last case shouldn't happen though.

    if (/*m_lazyResize*/ false) // TODO
        setLazyPosition(positionToGoTo);
    else
        setPosition(positionToGoTo);
}

void Anchor::onWidgetMoved(int p)
{
   if (!isResizing()) // We only care if it's being dragged by mouse
       return;

   setPosition(p);
}

QRect Anchor::geometry() const
{
    return m_geometry;
}

bool Anchor::isResizing()
{
    return s_isResizing;
}

void Anchor::setSeparatorFactoryFunc(SeparatorFactoryFunc func)
{
    s_separatorFactoryFunc = func;
}
