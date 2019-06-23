/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "Item_p.h"
#include "MultiSplitterLayout_p.h"
#include "Logging_p.h"
#include "AnchorGroup_p.h"
#include "Frame_p.h"

#include <QEvent>

using namespace KDDockWidgets;

class Item::Private {
public:

    Private(Item *qq, Frame *widget, MultiSplitterLayout *parent)
        : q(qq)
        , m_anchorGroup(parent)
        , m_frame(widget)
        , m_geometry(m_frame->geometry())
    {
    }

    void updateObjectName();
    Item *const q;
    AnchorGroup m_anchorGroup;
    const QPointer<Frame> m_frame;
    QPointer<MultiSplitterLayout> m_layout;
    QRect m_geometry;
    bool m_destroying = false;
};

Item::Item(Frame *frame, MultiSplitterLayout *parent)
    : QObject(parent)
    , d(new Private(this, frame, parent))
{
    Q_ASSERT(parent);
    Q_ASSERT(d->m_frame);
    setLayout(parent);
    d->m_frame->installEventFilter(this);

    // auto destruction
    connect(d->m_frame, &QObject::destroyed, this, [this] {
        if (!d->m_destroying) {
            d->m_destroying = true;
            delete this;
        }
    });

    connect(d->m_frame, &QObject::objectNameChanged, this, [this] { d->updateObjectName(); });
    d->updateObjectName();
}

Item::~Item()
{
    if (!d->m_destroying) {
        d->m_destroying = true;
        delete d->m_frame;
    }

    if (d->m_layout) {
        d->m_layout->removeItem(this);
    }
    delete d;
}

int Item::x() const
{
    return d->m_geometry.x();
}

int Item::y() const
{
    return d->m_geometry.y();
}

QPoint Item::pos() const
{
    return d->m_geometry.topLeft();
}

int Item::position(Qt::Orientation orientation) const
{
    return orientation == Qt::Vertical ? x()
                                       : y();
}

QSize Item::size() const
{
    return d->m_geometry.size();
}

int Item::width() const
{
    return size().width();
}

int Item::height() const
{
    return size().height();
}

bool Item::isVisible() const
{
    Q_ASSERT(d->m_frame);
    return d->m_frame->isVisible();
}

void Item::setVisible(bool v)
{
    Q_ASSERT(d->m_frame);
    d->m_frame->setVisible(v);
}

void Item::setGeometry(QRect geo)
{
    Q_ASSERT(d->m_frame);
    if (geo != d->m_geometry) {

        GeometryDiff geoDiff(d->m_geometry, geo);

        /*qDebug() << "old=" << geo << "; new=" << d->m_geometry
                 << "; len=" << length(geoDiff.orientation())
                 << "; minLen=" << minLength(geoDiff.orientation())
                 << "; window=" << parentWidget()->window()
                 << "this=" << this;*/
        d->m_geometry = geo;
        d->m_frame->setGeometry(geo);

        if (d->m_anchorGroup.isValid() && geoDiff.onlyOneSideChanged) {
            const int lengthDelta = length(geoDiff.orientation()) - minLength(geoDiff.orientation());
            if (lengthDelta < 0) {
                Anchor *anchorThatMoved = anchor(geoDiff);
                Q_ASSERT(anchorThatMoved);
                Anchor *anchorToMove = d->m_anchorGroup.oppositeAnchor(anchorThatMoved);
                Q_ASSERT(anchorToMove);
                const int newPosition = anchorToMove->position() - (lengthDelta * geoDiff.signess());

                // Note: Position can be slightly negative if the main window isn't big enougn to host the new size.
                // In that case the window will be resized shortly after
                anchorToMove->setPosition(newPosition);
            }
        }
    }
}

QRect Item::geometry() const
{
    return d->m_geometry;
}

bool Item::eventFilter(QObject *o, QEvent *e)
{
    if (!d->m_layout)
        return false;

    if (e->type() == QEvent::ParentChange && !d->m_layout->m_beingMergedIntoAnotherMultiSplitter) {
        if (o->parent() != d->m_layout->parentWidget())
            d->m_layout->removeItem(this);
    } else if (e->type() == QEvent::Show || e->type() == QEvent::Hide) {
        d->m_layout->emitVisibleWidgetCountChanged();
    }
    return false;
}

Frame *Item::frame() const
{
    return d->m_frame;
}

QWidget *Item::parentWidget() const
{
    return d->m_frame ? d->m_frame->parentWidget()
                      : nullptr;
}

MultiSplitterLayout *Item::layout() const
{
    return d->m_layout;
}

void Item::setLayout(MultiSplitterLayout *m)
{
    Q_ASSERT(m);
    Q_ASSERT(d->m_frame);
    if (m != d->m_layout) {
        d->m_layout = m;
        d->m_anchorGroup.layout = m;
        setParent(m);
        d->m_frame->setParent(m->parentWidget());
    }
}

int Item::length(Qt::Orientation orientation) const
{
    return KDDockWidgets::widgetLength(this, orientation);
}

int Item::minLength(Qt::Orientation orientation) const
{
    return KDDockWidgets::widgetMinLength(this, orientation);
}

Anchor *Item::anchor(Anchor::Side side, Qt::Orientation orientation) const
{
    return d->m_anchorGroup.anchor(side, orientation);
}

Anchor *Item::anchor(const GeometryDiff &geoDiff) const
{
    if (!geoDiff.onlyOneSideChanged)
        return nullptr;
    if (geoDiff.leftDiff)
        return d->m_anchorGroup.left;
    if (geoDiff.topDiff)
        return d->m_anchorGroup.top;
    if (geoDiff.bottomDiff)
        return d->m_anchorGroup.bottom;
    if (geoDiff.rightDiff)
        return d->m_anchorGroup.right;

    Q_UNREACHABLE();
    return nullptr;
}

AnchorGroup& Item::anchorGroup()
{
    return d->m_anchorGroup;
}

const AnchorGroup &Item::anchorGroup() const
{
    return d->m_anchorGroup;
}

int Item::cumulativeMinLength(Anchor::Side side, Qt::Orientation orientation) const
{
    return minLength(orientation) + anchor(Anchor::oppositeSide(side), orientation)->cumulativeMinLength(side);
}

int Item::minimumWidth() const
{
    Q_ASSERT(d->m_frame);
    return d->m_frame->minimumWidth();
}

int Item::minimumHeight() const
{
    Q_ASSERT(d->m_frame);
    return d->m_frame->minimumHeight();
}

QSize Item::minimumSize() const
{
    Q_ASSERT(d->m_frame);
    return d->m_frame->minimumSize();
}

QSize Item::minimumSizeHint() const
{
    Q_ASSERT(d->m_frame);
    return d->m_frame->minimumSizeHint();
}

void Item::Private::updateObjectName()
{
    q->setObjectName(m_frame->objectName());
}
