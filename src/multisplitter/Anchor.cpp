/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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
#include "MultiSplitterLayout_p.h"
#include "MultiSplitter_p.h"
#include "Logging_p.h"
#include "LayoutSaver.h"
#include "Config.h"
#include "Separator_p.h"
#include "FrameworkWidgetFactory.h"

#include <QApplication>
#include <QDebug>

#ifdef Q_OS_WIN
# include <Windows.h>
#endif

using namespace KDDockWidgets;

bool Anchor::s_isResizing = false;
const QString Anchor::s_magicMarker = QStringLiteral("e520c60e-cf5d-4a30-b1a7-588d2c569851");

Anchor::Anchor(Qt::Orientation orientation, MultiSplitterLayout *multiSplitter, Type type)
    : QObject(multiSplitter->multiSplitter())
    , m_orientation(orientation)
    , m_type(type)
    , m_layout(multiSplitter)
    , m_separatorWidget(Config::self().frameWorkWidgetFactory()->createSeparator(this, multiSplitter->multiSplitter()))
{
    multiSplitter->insertAnchor(this);
    connect(this, &QObject::objectNameChanged, m_separatorWidget, &QObject::setObjectName);
}

Anchor::~Anchor()
{
    m_separatorWidget->setEnabled(false);
    m_separatorWidget->deleteLater();
    qCDebug(multisplittercreation) << "~Anchor; this=" << this << "; m_to=" << m_to << "; m_from=" << m_from;
    m_layout->removeAnchor(this);
    for (Item *item : items(Side1))
        item->anchorGroup().setAnchor(nullptr, m_orientation, Side1);
    for (Item *item : items(Side2))
        item->anchorGroup().setAnchor(nullptr, m_orientation, Side2);
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

    Q_EMIT fromChanged();
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

    Q_EMIT toChanged();
}

void Anchor::updateSize()
{
    if (isValid()) {
        if (isVertical()) {
            setGeometry(QRect(position(), m_from->geometry().bottom(), thickness(), length()));
        } else {
            setGeometry(QRect(m_from->geometry().right(), position(), length(), thickness()));
        }
    }
    qCDebug(anchors) << "Anchor::updateSize" << this << geometry();
}

void Anchor::setGeometry(QRect r)
{
    if (r != m_geometry) {

        if (position() < 0) {
            qCDebug(anchors) << Q_FUNC_INFO << "Old position was negative" << position() << "; new=" << r;
        }

        m_geometry = r;
        m_separatorWidget->setGeometry(r);
    }
}

void Anchor::updateItemSizes()
{
    if (!m_initialized) {
        // setPosition() hasn't been called yet, don't bother
        return;
    }

    if (LayoutSaver::restoreInProgress()) {
        // Nothing to do. The LayoutSaver is setting up the whole layout.
        return;
    }

    qCDebug(anchors) << Q_FUNC_INFO << this << "; o=" << orientation();

    int position = this->position() + m_positionOffset;
    for (Item *item : qAsConst(m_side2Items)) {
        QRect geo = item->geometry();

        const QPoint topLeft = isVertical() ? QPoint(position + thickness(), item->y())
                                            : QPoint(item->x(), position + thickness());

        geo.setTopLeft(topLeft);
        if (!item->isPlaceholder())
            item->setGeometry(geo);
    }

    position = this->position() - m_positionOffset;

    for (Item *item : qAsConst(m_side1Items)) {
        QRect geo = item->geometry();

        // -1 as the widget is right next to the anchor, and not on top
        const QPoint bottomRight = isVertical() ? QPoint(position - 1, geo.bottom())
                                                : QPoint(geo.right(), position - 1);
        geo.setBottomRight(bottomRight);
        if (!item->isPlaceholder()) {
            item->setGeometry(geo);
        }
    }
}

void Anchor::debug_updateItemNames()
{
    // I call this in the unit-tests, when running them on gammaray

    m_debug_side1ItemNames.clear();
    m_debug_side2ItemNames.clear();

    for (Item *item : qAsConst(m_side1Items))
        m_debug_side1ItemNames += item->objectName() + QStringLiteral("; ");

    for (Item *item : qAsConst(m_side2Items))
        m_debug_side2ItemNames += item->objectName() + QStringLiteral("; ");

    Q_EMIT debug_itemNamesChanged();
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
    qCDebug(anchors) << Q_FUNC_INFO << this << "; visible="
                     << m_separatorWidget->isVisible() << "; p=" << p;

    const int max = m_layout->length(orientation()) - 1;
    const bool outOfBounds = max != -1 && (p < 0  || p > max);

    if (outOfBounds) {
        if (isStatic() && m_layout->isRestoringPlaceholder()) {
            // Don't do anything here, it's restoring a placeholder and will call ensureAnchorsBounded() when finished
            return;
        } else {
            m_layout->dumpDebug();
            qWarning() << Q_FUNC_INFO << "Out of bounds position=" << p
                       << "; oldPosition=" << position()
                       << "; this=" << this
                       << "; size=" << m_layout->size()
                       << "; max=" << max
                       << m_layout->multiSplitter()->window();
        }

    }

    m_initialized = true;
    if (position() == p) {
        updateItemSizes();
        return;
    }

    if (isVertical()) {
        m_geometry.moveLeft(p);
    } else {
        m_geometry.moveTop(p);
    }

    /**
     * If we're in the middle of a resize then remember the relative positions, so we can do
     * a redistribution so that relatively all widgets occupy the same amount
     */
    const bool recalculatePercentage = !(options & SetPositionOption_DontRecalculatePercentage) && !m_layout->isResizing();

    m_separatorWidget->move(p);
    if (recalculatePercentage) {
        // We keep the percentage, so we don't constantly recalculate it during a resize, which introduces rounding errors
        updatePositionPercentage();
    }

    // Note: Position can be slightly negative if the main window isn't big enougn to host the new size.
    // In that case the window will be resized shortly after
    //Q_ASSERT(p >= 0); - commented out, as it's normal

    Q_EMIT positionChanged(position());
    updateItemSizes();
}

void Anchor::updatePositionPercentage()
{
    m_positionPercentage = (position() * 1.0) / m_layout->width();
}

int Anchor::position() const
{
    const QPoint topLeft = m_geometry.topLeft();
    return isVertical() ? topLeft.x() : topLeft.y();
}

void Anchor::setVisible(bool v)
{
    m_separatorWidget->setVisible(v);
    if (v) {
        m_separatorWidget->setGeometry(m_geometry);
    }
}

int Anchor::minPosition() const
{
    const int smallestSqueeze = smallestAvailableItemSqueeze(Side1);
    return position() - smallestSqueeze;
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

void Anchor::ensureBounded()
{
    if (!isStatic() && !isFollowing()) {
        const QPair<int,int> bounds = m_layout->boundPositionsForAnchor(this);

        if (position() < bounds.first) {
            setPosition(bounds.first);
        } else if (position() > bounds.second) {
            setPosition(bounds.second);
        }
    }

    for (Item *item : items(Side2)) {
        item->anchorAtSide(Side2, orientation())->ensureBounded();
    }
}

int Anchor::length() const
{
    Q_ASSERT(m_to);
    Q_ASSERT(m_from);
    return m_to->position() - m_from->position();
}

bool Anchor::isValid() const
{
    return m_to && m_from && m_to != m_from && m_to != this && m_from != this;
}

int Anchor::thickness() const
{
    return isVertical() ? m_separatorWidget->width()
                        : m_separatorWidget->height();
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

bool Anchor::onlyHasPlaceholderItems(Anchor::Side side) const
{
    auto &items = side == Side1 ? m_side1Items
                                : m_side2Items;

    for (Item *item : items) {
        if (!item->isPlaceholder())
            return false;
    }

    return true;
}

bool Anchor::hasNonPlaceholderItems(Anchor::Side side) const
{
    auto &items = side == Side1 ? m_side1Items
                                : m_side2Items;

    for (Item *item : items) {
        if (!item->isPlaceholder())
            return true;
    }

    return false;
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

bool Anchor::isStaticOrFollowsStatic() const
{
    if (isStatic())
        return true;

    return m_followee && m_followee->isStaticOrFollowsStatic();
}

const ItemList Anchor::items(Anchor::Side side) const
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
    QPointer<Anchor> otherp = other; // Just to check if it wasn't deleted meanwhile. Which doesn't happen, but we silence a clang-tidy warning this way.
    consume(other, Side1);
    if (otherp)
        consume(other, Side2);
}

void Anchor::consume(Anchor *other, Side side)
{
    auto items = other->items(side);
    other->removeItems(side);
    addItems(items, side);
    if (other->isUnneeded()) {
        // Before deleting an unneeded anchor, we must check if there's anchors following it, and make them follow us instead
        Anchor::List anchorsFollowingOther = m_layout->anchorsFollowing(other);
        for (Anchor *follower : anchorsFollowingOther) {
            if (follower != this)
                follower->setFollowee(this);
        }

        delete other;
    }
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
    auto anchor = new Anchor(other->orientation(), other->m_layout);
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
    return m_layout->anchorBeingDragged() == this;
}

int Anchor::cumulativeMinLength(Anchor::Side side) const
{
    if (isStatic() && isEmpty()) {
        // There's no widget, but minimum is the space occupied by left+right anchors (or top+bottom).
        const int staticAnchorThickness = Anchor::thickness(/*static=*/true);
        if ((side == Side2 && (m_type & (Type_LeftStatic | Type_TopStatic))) ||
            (side == Side1 && (m_type & (Type_RightStatic | Type_BottomStatic))))
            return 2 * staticAnchorThickness;
    }

    const auto items = this->items(side);
    int minLength = 0;
    for (auto item : items) {
        const int itemMin = item->cumulativeMinLength(side, orientation());
        minLength = qMax(itemMin, minLength);
    }

    // Dont' use isFollowing() here, because when restoring a placeholder we clear the followers first
    const int thickness = (isStatic() || hasNonPlaceholderItems(side)) ? this->thickness() : 0;

    return thickness + minLength;
}

void Anchor::setFollowee(Anchor *followee)
{
    Q_ASSERT(this != followee);
    if (m_followee == followee)
        return;

    qCDebug(placeholder) << Q_FUNC_INFO << "follower="
                         << this << "; followee=" << followee;

    if (m_followee) {
        disconnect(m_followee, &Anchor::positionChanged, this, &Anchor::onFolloweePositionChanged);
        disconnect(m_followee, &Anchor::thicknessChanged, this, &Anchor::setThickness);
    }

    m_followee = followee;
    setThickness();
    if (m_followee) {
        Q_ASSERT(orientation() == m_followee->orientation());
        setVisible(false);
        setPosition(m_followee->position());
        connect(m_followee, &Anchor::positionChanged, this, &Anchor::onFolloweePositionChanged);
        connect(m_followee, &Anchor::thicknessChanged, this, &Anchor::setThickness);
    } else {
        setVisible(true);
    }

    Q_EMIT followeeChanged();
}

Anchor *Anchor::endFollowee() const
{
    Anchor *a = m_followee;
    while (a) {
        if (!a->followee())
            return a;

        a = a->followee();
    }

    return nullptr;
}

bool Anchor::findAnchor(Anchor *anchor, Anchor::Side side) const
{
    if (!anchor)
        return false;

    Q_ASSERT(anchor != this);
    Q_ASSERT(anchor->orientation() == orientation());

    for (Item *item : items(side)) {
        Anchor *a = item->anchorAtSide(side, orientation());
        if (anchor == a)
            return true;

        if (a->findAnchor(anchor, side))
            return true;
    }

    return false;
}

Anchor *Anchor::findNearestAnchorWithItems(Anchor::Side side) const
{
    Anchor *candidate = nullptr;
    for (Item *item : items(side)) {
        Anchor *a = item->anchorAtSide(side, orientation());
        if (!a->hasNonPlaceholderItems(side))
            a = a->findNearestAnchorWithItems(side);

        if (!candidate || (side == Side1 && a->position() > candidate->position()) || (side == Side2 && a->position() < candidate->position()) ) {
            candidate = a;
        }
    }

    if (!candidate)
        candidate = m_layout->staticAnchor(side, orientation());

    Q_ASSERT(candidate->isStatic() || candidate->hasNonPlaceholderItems(side));
    return candidate;
}

void Anchor::clear()
{
    m_side1Items.clear();
    m_side2Items.clear();
}

void Anchor::onFolloweePositionChanged(int pos)
{
    Q_ASSERT(isFollowing());
    setPosition(pos);
}

int Anchor::thickness(bool staticAnchor)
{
    return Config::self().separatorThickness(staticAnchor);
}

void Anchor::setLayout(MultiSplitterLayout *layout)
{
    m_layout->removeAnchor(this);
    m_layout = layout;
    setParent(layout->multiSplitter());
    m_separatorWidget->setParent(layout->multiSplitter());
    m_layout->insertAnchor(this);
    m_layout->setAnchorBeingDragged(nullptr);
}

Separator *Anchor::separatorWidget() const
{
    return m_separatorWidget;
}

void Anchor::setThickness()
{
    const int value = isFollowing() ? m_followee->thickness()
                                    : thickness(isStatic());

    const int oldValue = thickness();

    if (value != oldValue) {
        if (isVertical()) {
            m_separatorWidget->setFixedWidth(value);
            m_geometry.setWidth(value);
        } else {
            m_separatorWidget->setFixedHeight(value);
            m_geometry.setHeight(value);
        }

        Q_EMIT thicknessChanged();
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
        Q_EMIT itemsChanged(side);
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
        Q_EMIT itemsChanged(Side1);
    } else {
        if (m_side2Items.removeOne(item)) {
            item->anchorGroup().setAnchor(nullptr, orientation(), Side2);
            Q_EMIT itemsChanged(Side2);
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

void Anchor::onMousePress()
{
    s_isResizing = true;
    m_layout->setAnchorBeingDragged(this);
    qCDebug(anchors) << "Drag started";
}

void Anchor::onMouseReleased()
{
    s_isResizing = false;
    m_layout->setAnchorBeingDragged(nullptr);
}

void Anchor::onMouseMoved(QPoint pt)
{
    if (!isBeingDragged() || isStatic())
        return;

    if (!(qApp->mouseButtons() & Qt::LeftButton)) {
        qCDebug(mouseevents) << Q_FUNC_INFO << "Ignoring spurious mouse event. Someone ate our ReleaseEvent";
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
    auto bounds = m_layout->boundPositionsForAnchor(this);

    if (positionToGoTo < bounds.first || positionToGoTo > bounds.second) {
        // qDebug() << "Out of bounds" << bounds.first << bounds.second << positionToGoTo << "; currentPos" << position() << "; window size" << window()->size();
        return;
    }

    m_lastMoveDirection = positionToGoTo < position() ? Side1
                                                      : (positionToGoTo > position() ? Side2
                                                                                     : Side_None); // Side_None shouldn't happen though.
    setPosition(positionToGoTo);
}

void Anchor::onWidgetMoved(int p)
{
    if (m_layout->anchorBeingDragged() != this) // We only care if it's being dragged by mouse
        return;


    setPosition(p);
}

bool Anchor::isResizing()
{
    return s_isResizing;
}

Anchor *Anchor::createFromDataStream(QDataStream &ds, MultiSplitterLayout *layout)
{
    QString marker;
    QString objectName;
    QRect geometry;
    int orientation;
    int type;

    int indexFrom;
    int indexTo;
    int indexFolowee;
    QVector<int> side1ItemIndexes;
    QVector<int> side2ItemIndexes;

    ds >> marker;
    if (marker != Anchor::s_magicMarker) {
        qWarning() << Q_FUNC_INFO << "Corrupted stream";
        return nullptr;
    }

    ds >> objectName;
    ds >> geometry;
    ds >> orientation;
    ds >> type;
    ds >> indexFrom;
    ds >> indexTo;
    ds >> indexFolowee;
    ds >> side1ItemIndexes;
    ds >> side2ItemIndexes;

    auto anchor = new Anchor(Qt::Orientation(orientation), layout, Anchor::Type(type));
    anchor->setObjectName(objectName);
    anchor->setGeometry(geometry);
    anchor->updatePositionPercentage();
    anchor->setProperty("indexFrom", indexFrom);
    anchor->setProperty("indexTo", indexTo);
    anchor->setProperty("indexFolowee", indexFolowee);

    ItemList side1Items;
    ItemList side2Items;
    const ItemList allItems = layout->items();
    side1Items.reserve(side1ItemIndexes.size());
    for (int index : qAsConst(side1ItemIndexes)) {
        side1Items.push_back(allItems.at(index));
    }
    side2Items.reserve(side2ItemIndexes.size());
    for (int index : qAsConst(side2ItemIndexes)) {
        side2Items.push_back(allItems.at(index));
    }

    anchor->m_side1Items = side1Items;
    anchor->m_side2Items = side2Items;
    anchor->m_initialized = true;

    return anchor;
}

QDataStream &KDDockWidgets::operator<<(QDataStream &ds, Anchor *a)
{
    const Anchor::List allAnchors = a->m_layout->anchors();
    const ItemList allItems = a->m_layout->items();

    ds << Anchor::s_magicMarker;
    ds << a->objectName();
    ds << a->geometry();
    ds << a->orientation();
    ds << a->type();
    ds << allAnchors.indexOf(a->from());
    ds << allAnchors.indexOf(a->to());
    ds << (a->followee() ? allAnchors.indexOf(a->followee()) : -1);

    QVector<int> side1Items;
    side1Items.reserve(a->side1Items().size());
    for (Item *item : a->side1Items())
        side1Items.push_back(allItems.indexOf(item));

    QVector<int> side2Items;
    side2Items.reserve(a->side2Items().size());
    for (Item *item : a->side2Items())
        side2Items.push_back(allItems.indexOf(item));

    ds << side1Items;
    ds << side2Items;

    return ds;
}
