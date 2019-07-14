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
#include "MultiSplitterWidget_p.h"
#include "Logging_p.h"
#include "AnchorGroup_p.h"
#include "Frame_p.h"
#include "MainWindow.h"
#include "DockWidget.h"

#include <QEvent>

using namespace KDDockWidgets;

class Item::Private {
public:

    Private(Item *qq, Frame *frame, MultiSplitterLayout *parent)
        : q(qq)
        , m_anchorGroup(parent)
        , m_frame(frame)
        , m_geometry(m_frame->geometry())
    {
        m_minSize = QSize(widgetMinLength(m_frame, Qt::Vertical),
                          widgetMinLength(m_frame, Qt::Horizontal));
    }

    void setFrame(Frame *frame);
    void turnIntoPlaceholder();
    void setIsPlaceholder(bool);

    void updateObjectName();
    Item *const q;
    AnchorGroup m_anchorGroup;
    Frame *m_frame = nullptr;
    bool m_isPlaceholder = false;
    QPointer<MultiSplitterLayout> m_layout;
    QRect m_geometry;
    QSize m_minSize;
    bool m_destroying = false;
    int m_refCount = 0;
    bool m_blockPropagateGeo = false;
    QMetaObject::Connection m_onFrameDestroyed_connection;
    QMetaObject::Connection m_onFrameObjectNameChanged_connection;
};

Item::Item(Frame *frame, MultiSplitterLayout *parent)
    : QObject(parent)
    , d(new Private(this, frame, parent))
{    

    Q_ASSERT(frame);
    setLayout(parent);

    // Minor hack: Set to nullptr so setFrame doesn't bail out. There's a catch-22: setLayout needs to have an m_frame and setFrame needs to have a layout.
    d->m_frame = nullptr;
    d->setFrame(frame);
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
    Q_ASSERT(d->m_frame || isPlaceholder());

    if (geo != d->m_geometry) {
        GeometryDiff geoDiff(d->m_geometry, geo);

        /*qDebug() << "old=" << geo << "; new=" << d->m_geometry
                 << "; len=" << length(geoDiff.orientation())
                 << "; minLen=" << minLength(geoDiff.orientation())
                 << "; window=" << parentWidget()->window()
                 << "this=" << this;*/
        d->m_geometry = geo;
        Q_EMIT geometryChanged();

        if (!isPlaceholder())
            d->m_frame->setGeometry(geo);

        if (!d->m_blockPropagateGeo && d->m_anchorGroup.isValid() && geoDiff.onlyOneSideChanged) {
            // If we're being squeezed to the point where it reaches less then our min size, then we drag the opposite separator, to preserve size
            const int lengthDelta = length(geoDiff.orientation()) - minLength(geoDiff.orientation());
            if (lengthDelta < 0) {
                Anchor *anchorThatMoved = anchor(geoDiff);
                Q_ASSERT(anchorThatMoved);
                Anchor *anchorToMove = d->m_anchorGroup.oppositeAnchor(anchorThatMoved);
                if (anchorToMove->isFollowing())
                    anchorToMove = anchorToMove->endFollowee();

                Q_ASSERT(anchorToMove);
                const int newPosition = anchorToMove->position() - (lengthDelta * geoDiff.signess());

                // Note: Position can be slightly negative if the main window isn't big enougn to host the new size.
                // In that case the window will be resized shortly after
                Q_ASSERT(!anchorToMove->isFollowing());
                anchorToMove->setPosition(newPosition);
            }
        }
    }
}

void Item::beginBlockPropagateGeo()
{
    Q_ASSERT(!d->m_blockPropagateGeo);
    d->m_blockPropagateGeo = true;
}

void Item::endBlockPropagateGeo()
{
    Q_ASSERT(d->m_blockPropagateGeo);
    d->m_blockPropagateGeo = false;
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
        if (o->parent() != d->m_layout->parentWidget()) {
            // Frame was detached into a floating window
            Q_ASSERT(!isPlaceholder());
            d->turnIntoPlaceholder();
        }
    } else if (e->type() == QEvent::Show || e->type() == QEvent::Hide) {
        //d->m_layout->emitVisibleWidgetCountChanged(); REMOVE
    }
    return false;
}

Frame *Item::frame() const
{
    return d->m_frame;
}

QWidget *Item::window() const
{
    Q_ASSERT(d->m_layout);
    Q_ASSERT(d->m_layout->parentWidget());
    return d->m_layout->parentWidget()->window();
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
    if (m != d->m_layout) {
        d->m_layout = m;
        d->m_anchorGroup.layout = m;
        setParent(m);
        if (d->m_frame)
            d->m_frame->setParent(m->parentWidget());
    }
}

int Item::length(Qt::Orientation orientation) const
{
    return KDDockWidgets::widgetLength(this, orientation);
}

int Item::minLength(Qt::Orientation orientation) const
{
    return lengthFromSize(minimumSize(), orientation);
}

Anchor *Item::anchorAtSide(Anchor::Side side, Qt::Orientation orientation) const
{
    if (!d->m_anchorGroup.isValid())
        qWarning() << Q_FUNC_INFO << "Invalid anchor group" << &d->m_anchorGroup
                   << "in" << this << "; window=" << parentWidget()->window();

    return d->m_anchorGroup.anchorAtSide(side, orientation);
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

    Q_ASSERT(false);
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
    Anchor *oppositeAnchor = anchorAtSide(side, orientation);
    Q_ASSERT(oppositeAnchor);
    const int minLength = isPlaceholder() ? 0 : this->minLength(orientation);
    return minLength + oppositeAnchor->cumulativeMinLength(side);
}

QSize Item::minimumSize() const
{
    return isPlaceholder() ? QSize(0, 0)
                           : d->m_minSize;
}

bool Item::isPlaceholder() const
{
    return d->m_isPlaceholder;
}

void Item::setIsPlaceholder(bool is)
{
    d->setIsPlaceholder(is);
}

bool Item::isInMainWindow() const
{
    if (auto l = layout()) {
        if (auto p = l->parentWidget()) {
            return qobject_cast<MainWindow*>(p->parentWidget());
        }
    }

    return false;
}

void Item::restorePlaceholder(DockWidget *dockWidget, int tabIndex)
{
    qCDebug(placeholder) << Q_FUNC_INFO << "Restoring to window=" << window();
    if (d->m_isPlaceholder) {
        d->setFrame(new Frame(layout()->parentWidget()));
        d->m_frame->setGeometry(d->m_geometry);
    }

    if (tabIndex != -1 && d->m_frame->dockWidgetCount() >= tabIndex) {
        d->m_frame->insertWidget(dockWidget, tabIndex);
    } else {
        d->m_frame->addWidget(dockWidget);
    }

    if (d->m_isPlaceholder) {
        // Resize Anchors to their correct places.
        d->m_layout->restorePlaceholder(this);
        d->m_frame->setVisible(true);
        d->setIsPlaceholder(false);
    }
}

void Item::Private::setFrame(Frame *frame)
{
    Q_ASSERT((m_frame && !frame) || (!m_frame && frame));

    if (m_frame) {
        m_frame->removeEventFilter(q);
        QObject::disconnect(m_onFrameDestroyed_connection);
        QObject::disconnect(m_onFrameObjectNameChanged_connection);
    }

    m_frame = frame;
    Q_EMIT q->frameChanged();

    if (frame) {
        frame->setLayoutItem(q);
        frame->installEventFilter(q);
        // auto destruction
        m_onFrameDestroyed_connection = q->connect(frame, &QObject::destroyed, q, [this] {
            if (!m_layout) {
                // Our parent (MultiSplitterLayout) is being destructed, and will delete this Item
                // Nothing to do.
                return;
            }

            // Frame is being deleted, but perhaps the DockWidget was just made floating, so in this case
            // we turn the item into a placeholder, so it remembers its previous place if we want to redock it.
            if (m_refCount) {
                // There's still KDDockWidgets which are floating and were here previously
                turnIntoPlaceholder();
            } else {
                // Nope, nothing really needs this this Item, destroy it.
                if (!m_destroying) {
                    m_destroying = true;
                    delete this;
                }
            }
        });

        m_onFrameObjectNameChanged_connection = connect(frame, &QObject::objectNameChanged, q, [this] { updateObjectName(); });
    }
}

void Item::ref()
{
    d->m_refCount++;
    qCDebug(placeholder()) << Q_FUNC_INFO << "; new ref=" << d->m_refCount;
}

void Item::unref()
{
    if (d->m_refCount == 0) {
        qWarning() << Q_FUNC_INFO << "refcount can't be 0";
        return;
    }

    d->m_refCount--;
    qCDebug(placeholder()) << Q_FUNC_INFO << "; new ref=" << d->m_refCount;

    if (d->m_refCount == 0) {
        if (!d->m_destroying) {
            d->m_destroying = true;
            delete this;
        }
    }
}

int Item::refCount() const
{
    return d->m_refCount;
}

void Item::Private::turnIntoPlaceholder()
{
    if (q->isPlaceholder())
        return;

    setFrame(nullptr);
    setIsPlaceholder(true);

    qCDebug(placeholder) << Q_FUNC_INFO << this;
    AnchorGroup anchorGroup = q->anchorGroup();
    if (anchorGroup.isValid()) {
        m_layout->emitVisibleWidgetCountChanged();
    } else {
        // Auto-destruction, which removes it from the layout
        delete q;
    }


    m_layout->updateAnchorFollowing();
}

void Item::Private::setIsPlaceholder(bool is)
{
    if (is != m_isPlaceholder) {
        m_isPlaceholder = is;
        Q_EMIT q->isPlaceholderChanged();
    }
}

void Item::Private::updateObjectName()
{
    q->setObjectName(m_frame->objectName());
}
