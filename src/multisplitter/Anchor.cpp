/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, Author: Sérgio Martins <sergio.martins@kdab.com>

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
#include "MultiSplitter_p.h"
#include "Logging_p.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QStyleOption>

using namespace KDDockWidgets;

Anchor::Anchor(Qt::Orientation orientation, MultiSplitter *multiSplitter, Options options)
    : QWidget(multiSplitter)
    , m_orientation(orientation)
    , m_options(options)
    , m_multiSplitter(multiSplitter)
{
    if (isVertical())
        setFixedWidth(thickness(isStatic()));
    else
        setFixedHeight(thickness(isStatic()));

    setVisible(true);
    setMouseTracking(true);
    multiSplitter->insertAnchor(this);
}

Anchor::~Anchor()
{
    qCDebug(multisplittercreation) << "~Anchor; this=" << this << "; m_to=" << m_to << "; m_from=" << m_from;
    m_multiSplitter->removeAnchor(this);
    for (Item *item : items(Side1))
        item->anchorGroup().setAnchor(nullptr, m_orientation, Side1);
    for (Item *item : items(Side2))
        item->anchorGroup().setAnchor(nullptr, m_orientation, Side2);
}

int Anchor::pos() const
{
    return m_orientation == Qt::Horizontal ? y() : x();
}

void Anchor::setFrom(Anchor *from)
{
    if (from->orientation() == orientation() || from == this) {
        qWarning() << "Anchor::setFrom: Invalid from" << from->orientation() << m_orientation
                   << from << this;
        return;
    }

    if (m_from)
        disconnect(m_from, &Anchor::positionChanged, this, &Anchor::updateSize);
    m_from = from;
    connect(from, &Anchor::positionChanged, this, &Anchor::updateSize);
    updateSize();

    emit fromChanged();
}

void Anchor::setTo(Anchor *to)
{
    Q_ASSERT(to);
    if (to->orientation() == orientation() || to == this) {
        qWarning() << "Anchor::setFrom: Invalid to" << to->orientation() << m_orientation
                   << to << this;
        return;
    }

    if (m_to)
        disconnect(m_to, &Anchor::positionChanged, this, &Anchor::updateSize);
    m_to = to;
    connect(to, &Anchor::positionChanged, this, &Anchor::updateSize);
    updateSize();

    emit toChanged();
}

void Anchor::updateSize()
{
    if (isValid()) {
        if (isVertical()) {
            setGeometry(position(), m_from->geometry().bottom(), width(), length());
        } else {
            setGeometry(m_from->geometry().right(), position(), length(), height());
        }
    }
    qCDebug(anchors) << "Anchor::updateSize" << this << geometry();
}

void Anchor::updateItemSizes()
{
    if (!m_initialized) {
        // setPosition() hasn't been called yet, don't bother
        return;
    }

    qCDebug(anchors) << Q_FUNC_INFO << this << "; o=" << orientation();

    int position = this->position() + m_positionOffset;
    for (Item *item : qAsConst(m_side2Items)) {
        QRect geo = item->geometry();

        const QPoint topLeft = isVertical() ? QPoint(position + thickness(), item->y())
                                            : QPoint(item->x(), position + thickness());

        geo.setTopLeft(topLeft);
        item->setGeometry(geo);
    }

    position = this->position() - m_positionOffset;

    for (Item *item : qAsConst(m_side1Items)) {
        QRect geo = item->geometry();

        // -1 as the widget is right next to the anchor, and not on top
        const QPoint bottomRight = isVertical() ? QPoint(position - 1, geo.bottom())
                                                : QPoint(geo.right(), position - 1);
        geo.setBottomRight(bottomRight);
        item->setGeometry(geo);
    }
}

void Anchor::debug_updateItemNames()
{
    // I call this in the unit-tests, when running them on gammaray

    m_debug_side1ItemNames.clear();
    m_debug_side2ItemNames.clear();

    for (Item *item : m_side1Items)
        m_debug_side1ItemNames += item->objectName() + QStringLiteral("; ");

    for (Item *item : m_side2Items)
        m_debug_side2ItemNames += item->objectName() + QStringLiteral("; ");

    emit debug_itemNamesChanged();
}

QString Anchor::debug_side1ItemNames() const
{
    return m_debug_side1ItemNames;
}

QString Anchor::debug_side2ItemNames() const
{
    return m_debug_side2ItemNames;
}

Qt::Orientation Anchor::orientation() const
{
    return m_orientation;
}

void Anchor::setPosition(int p, SetPositionOptions options)
{
    qCDebug(anchors) << Q_FUNC_INFO << "; visible=" << isVisible();
    m_initialized = true;
    const bool recalculatePercentage = !(options & SetPositionOption_DontRecalculatePercentage);

    if (isVertical()) {
        QWidget::move(p, y());
        if (recalculatePercentage)
            m_positionPercentage = (p * 1.0) / m_multiSplitter->contentsWidth(); // We keep the percentage, so we don't constantly recalculate it during a resize, which introduces rounding errors
    } else {
        QWidget::move(x(), p);
        if (recalculatePercentage)
            m_positionPercentage = (p * 1.0) / m_multiSplitter->contentsHeight();
    }
}

int Anchor::position() const
{
    return isVertical() ? x() : y();
}

int Anchor::minPosition() const
{
    const int smallestSqueeze = smallestAvailableItemSqueeze(Side1);
    return m_position - smallestSqueeze;
}

int Anchor::smallestAvailableItemSqueeze(Anchor::Side side) const
{
    int smallest = 0;
    bool firstElement = true;
    for (Item *item : items(side)) {
        const int length = item->length(m_orientation);
        const int minLength = item->minLength(m_orientation);
        const int availableSqueeze = length - minLength;
        if (availableSqueeze < smallest || firstElement) {
            smallest = availableSqueeze;
            firstElement = false;
        }
    }
    return smallest;
}

int Anchor::length() const
{
    Q_ASSERT(m_to);
    Q_ASSERT(m_from);
    return m_to->pos() - m_from->pos();
}

bool Anchor::isValid() const
{
    return m_to && m_from && m_to != m_from;
}

int Anchor::thickness() const
{
    return isVertical() ? width() : height();
}

bool Anchor::hasItems(Anchor::Side side) const
{
    switch (side) {
    case Side1:
        return !m_side1Items.isEmpty();
    case Side2:
        return !m_side2Items.isEmpty();
    default:
        Q_ASSERT(false);
        return false;
    }
}

bool Anchor::containsItem(const Item *item, Anchor::Side side) const
{
    switch (side) {
    case Side1:
        return m_side1Items.contains(const_cast<Item *>(item));
    case Side2:
        return m_side2Items.contains(const_cast<Item *>(item));
    default:
        Q_ASSERT(false);
        return false;
    }
}

ItemList Anchor::items(Anchor::Side side) const
{
    switch (side) {
    case Side1:
        return m_side1Items;
    case Side2:
        return m_side2Items;
    default:
        Q_ASSERT(false);
        return {};
    }
}

void Anchor::consume(Anchor *other)
{
    consume(other, Side1);
    consume(other, Side2);
}

void Anchor::consume(Anchor *other, Side side)
{
    auto items = other->items(side);
    other->removeItems(side);
    addItems(items, side);
    if (other->isUnneeded())
        delete other;
}

void Anchor::swapItems(Anchor *other)
{
    auto other1 = other->m_side1Items;
    auto other2 = other->m_side2Items;
    auto my1 = m_side1Items;
    auto my2 = m_side2Items;

    removeAllItems();
    other->removeAllItems();

    other->addItems(my1, Side1);
    other->addItems(my2, Side2);
    addItems(other1, Side1);
    addItems(other2, Side1);
}

void Anchor::removeAllItems()
{
    removeItems(Side1);
    removeItems(Side2);
}

/** static */
Anchor *Anchor::createFrom(Anchor *other, Item *relativeTo)
{
    Q_ASSERT(other);
    auto anchor = new Anchor(other->orientation(), other->m_multiSplitter);
    anchor->setFrom(other->m_from);
    anchor->setTo(other->m_to);

    if (relativeTo) {
        if (other->containsItem(relativeTo, Side1)) {
            other->removeItem(relativeTo);
            anchor->addItem(relativeTo, Side1);
        } else if (other->containsItem(relativeTo, Side2)) {
            other->removeItem(relativeTo);
            anchor->addItem(relativeTo, Side2);
        } else {
            Q_ASSERT(false);
        }
    } else {
        auto other1 = other->m_side1Items;
        auto other2 = other->m_side2Items;
        other->removeAllItems();
        anchor->addItems(other1, Side1);
        anchor->addItems(other2, Side2);
    }

    return anchor;
}

void Anchor::setPositionOffset(int value)
{
    if (value != m_positionOffset) {
        m_positionOffset = value;
        updateItemSizes();
    }
}

bool Anchor::isBeingDragged() const
{
    return m_multiSplitter->anchorBeingDragged() == this;
}

int Anchor::cumulativeMinLength(Anchor::Side side) const
{
    if (isStatic() && isEmpty()) {
        // There's no widget, but minimum is the space occupied by left+right anchors (or top+bottom).
        const int staticAnchorThickness = Anchor::thickness(/*static=*/true);
        if ((side == Side2 && (m_options & (Option_LeftStatic | Option_TopStatic))) ||
            (side == Side1 && (m_options & (Option_RightStatic | Option_BottomStatic))))
            return 2 * staticAnchorThickness;
    }

    const auto items = this->items(side);
    int minLength = 0;
    for (auto item : items) {
        const int itemMin = item->cumulativeMinLength(side, orientation());
        minLength = qMax(itemMin, minLength);
    }

    return thickness() + minLength;
}

int Anchor::thickness(bool staticAnchor)
{
    return staticAnchor ? 1 : 5;
}

void Anchor::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    QStyleOption opt;
    opt.palette = palette();
    opt.rect = rect();
    opt.state = QStyle::State_None;
    if (isVertical())
        opt.state |= QStyle::State_Horizontal;

    if (isEnabled())
        opt.state |= QStyle::State_Enabled;

    parentWidget()->style()->drawControl(QStyle::CE_Splitter, &opt, &p, this);
}

void Anchor::moveEvent(QMoveEvent *)
{
    qCDebug(anchors) << Q_FUNC_INFO;
    if (m_position == position())
        return;

    m_position = position();
    emit positionChanged(m_position);
    updateItemSizes();
}

void Anchor::enterEvent(QEvent *)
{
    if (!isStatic()) {
        if (isVertical())
            setCursor(Qt::SizeHorCursor);
        else
            setCursor(Qt::SizeVerCursor);
    }
}

void Anchor::leaveEvent(QEvent *)
{
    setCursor(Qt::ArrowCursor);
}

bool Anchor::event(QEvent *e)
{
    if (e->type() == QEvent::ParentChange) {
        m_multiSplitter->removeAnchor(this);
        m_multiSplitter = qobject_cast<MultiSplitter *>(parent());
        Q_ASSERT(m_multiSplitter);
        m_multiSplitter->insertAnchor(this);
    }

    return QWidget::event(e);
}

void Anchor::mousePressEvent(QMouseEvent *)
{
    m_multiSplitter->setAnchorBeingDragged(this);
    qCDebug(anchors) << "Drag started";
}

void Anchor::mouseMoveEvent(QMouseEvent *e)
{
    if (!isBeingDragged() || isStatic())
        return;

    const int positionToGoTo = position(mapToParent(e->pos()));
    auto bounds = m_multiSplitter->boundPositionsForAnchor(this);

    if (positionToGoTo < bounds.first || positionToGoTo > bounds.second) {
        // qDebug() << "Out of bounds" << bounds.first << bounds.second << positionToGoTo << "; currentPos" << position() << "; window size" << window()->size();
        return;
    }

    m_lastMoveDirection = positionToGoTo < position() ? Side1
                                                      : (positionToGoTo > position() ? Side2
                                                                                     : Side_None); // Side_None shouldn't happen though.
    move(positionToGoTo);
}

void Anchor::mouseReleaseEvent(QMouseEvent *)
{
    m_multiSplitter->setAnchorBeingDragged(nullptr);
}

void Anchor::move(int p)
{
    if (isVertical()) {
        QWidget::move(p, y());
    } else {
        QWidget::move(x(), p);
    }
}

int Anchor::position(QPoint p) const
{
    return isVertical() ? p.x() : p.y();
}

void Anchor::addItem(Item *item, Anchor::Side side)
{
    Q_ASSERT(side != Side_None);
    auto &items = (side == Side1) ? m_side1Items : m_side2Items;
    if (!items.contains(item)) {
        items << item;
        item->anchorGroup().setAnchor(this, orientation(), side);
        emit itemsChanged(side);
        updateItemSizes();
    }
}

void Anchor::addItems(const ItemList &list, Side side)
{
    for (Item *item : list)
        addItem(item, side);
}

void Anchor::removeItem(Item *item)
{
    if (m_side1Items.removeOne(item)) {
        item->anchorGroup().setAnchor(nullptr, orientation(), Side1);
        emit itemsChanged(Side1);
    } else {
        if (m_side2Items.removeOne(item)) {
            item->anchorGroup().setAnchor(nullptr, orientation(), Side2);
            emit itemsChanged(Side2);
        }
    }
}

void Anchor::removeItems(Side side)
{
    const auto &items = this->items(side);
    for (Item *item : items)
        removeItem(item);
}

Anchor::Side Anchor::oppositeSide(Side side)
{
    switch (side) {
    case Side1:
        return Side2;
    case Side2:
        return Side1;
    default:
        Q_ASSERT(false);
        return Side_None;
    }
}
