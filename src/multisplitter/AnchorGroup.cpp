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

#include "AnchorGroup_p.h"
#include "Anchor_p.h"
#include "MultiSplitterLayout_p.h"
#include "MultiSplitterWidget_p.h"
#include "Logging_p.h"


using namespace KDDockWidgets;

AnchorGroup::AnchorGroup(MultiSplitterLayout *l)
    : layout(l)
{
}

int AnchorGroup::width() const
{
    return right->position() - left->position();
}

int AnchorGroup::height() const
{
    return bottom->position() - top->position();
}

bool AnchorGroup::containsAnchor(Anchor *anchor) const
{
    return anchor == left || anchor == top || anchor == right || anchor == bottom;
}

QSize AnchorGroup::availableSize() const
{
    const int leftBound = left->isStatic() ? left->position()
                                           : layout->boundPositionForAnchor(left, Anchor::Side1);

    const int rightBound = right->isStatic() ? right->position()
                                             : layout->boundPositionForAnchor(right, Anchor::Side2);

    const int topBound = top->isStatic() ? top->position()
                                         : layout->boundPositionForAnchor(top, Anchor::Side1);

    const int bottomBound = bottom->isStatic() ? bottom->position()
                                               : layout->boundPositionForAnchor(bottom, Anchor::Side2);

    return QSize(rightBound - leftBound - left->thickness(),
                 bottomBound - topBound - top->thickness());
}

bool AnchorGroup::hasAvailableSizeFor(QSize needed) const
{
    const QSize available = availableSize();
    return available.width() >= needed.width() && available.height() >= needed.height();
}

Anchor *AnchorGroup::oppositeAnchor(Anchor *a) const
{
    if (a == left)
        return right;
    if (a == right)
        return left;
    if (a == top)
        return bottom;
    if (a == bottom)
        return top;

    return nullptr;
}

Anchor *AnchorGroup::createAnchorFrom(Location fromAnchorLocation, Item *relativeTo)
{
    Anchor *other = anchor(fromAnchorLocation);
    Q_ASSERT(other);

    auto anchor = new Anchor(other->orientation(), other->m_layout);
    if (anchor->isVertical()) {
        anchor->setFrom(top);
        anchor->setTo(bottom);
    } else {
        anchor->setFrom(left);
        anchor->setTo(right);
    }

    if (relativeTo) {
        if (other->containsItem(relativeTo, Anchor::Side1)) {
            other->removeItem(relativeTo);
            anchor->addItem(relativeTo, Anchor::Side1);
        } else if (other->containsItem(relativeTo, Anchor::Side2)) {
            other->removeItem(relativeTo);
            anchor->addItem(relativeTo, Anchor::Side2);
        } else {
            Q_ASSERT(false);
        }
    } else {
        auto other1 = other->m_side1Items;
        auto other2 = other->m_side2Items;
        other->removeAllItems();
        anchor->addItems(other1, Anchor::Side1);
        anchor->addItems(other2, Anchor::Side2);
    }

    return anchor;
}

Anchor *AnchorGroup::anchor(Location loc) const
{
    switch (loc) {
    case KDDockWidgets::Location_OnLeft:
        return left;
    case KDDockWidgets::Location_OnTop:
        return top;
    case KDDockWidgets::Location_OnRight:
        return right;
    case KDDockWidgets::Location_OnBottom:
        return bottom;
    default:
        Q_ASSERT(false);
        return nullptr;
    }
}

Anchor *AnchorGroup::anchorAtDirection(Anchor::Side side, Qt::Orientation orientation) const
{
    const bool isSide1 = side == Anchor::Side1;
    if (orientation == Qt::Vertical) {
        return isSide1 ? right : left;
    } else {
        return isSide1 ? bottom : top;
    }
}

Anchor *AnchorGroup::anchorAtSide(Anchor::Side side, Qt::Orientation orientation) const
{
    const bool isSide1 = side == Anchor::Side1;
    if (orientation == Qt::Vertical) {
        return isSide1 ? left: right;
    } else {
        return isSide1 ? top : bottom;
    }
}

void AnchorGroup::setAnchor(Anchor *anchor, Location loc)
{
    switch (loc) {

    case KDDockWidgets::Location_OnLeft:
        left = anchor;
        break;
    case KDDockWidgets::Location_OnTop:
        top = anchor;
        break;
    case KDDockWidgets::Location_OnRight:
        right = anchor;
        break;
    case KDDockWidgets::Location_OnBottom:
        bottom = anchor;
        break;
    default:
        Q_ASSERT(false);
    }
}

bool AnchorGroup::anchorIsFollowingInwards(Anchor *anchor) const
{
    if (anchor == left && left->findAnchor(left->endFollowee(), Anchor::Side2))
        return true;

    if (anchor == top && top->findAnchor(top->endFollowee(), Anchor::Side2))
        return true;

    if (anchor == right && right->findAnchor(right->endFollowee(), Anchor::Side1))
        return true;

    if (anchor == bottom && bottom->findAnchor(bottom->endFollowee(), Anchor::Side1))
        return true;

    return false;
}

QDebug AnchorGroup::debug(QDebug d) const
{
    d << "AnchorGroup: this=" << ((void*)this) << "\n;  top=" << top << "; left=" << left
      << "\n  ; right=" << right << "; bottom=" << bottom
      << "\n  ; valid=" << isValid()
      << "\n  ; layoutWindow=" << (layout ? layout->parentWidget()->window() : nullptr)
      << "; isSquashed=" << isSquashed() << "; "
      << anchorIsFollowingInwards(left) << anchorIsFollowingInwards(top)
      << anchorIsFollowingInwards(right) << anchorIsFollowingInwards(bottom)
      << left->followee()
      << "\n";
    return d;
}

const Anchor::List AnchorGroup::anchorsFollowingInwards() const
{
    Anchor::List result;
    if (anchorIsFollowingInwards(left))
        result.push_back(left);

    if (anchorIsFollowingInwards(top))
        result.push_back(top);

    if (anchorIsFollowingInwards(right)) {
        result.push_back(right);
        Q_ASSERT(!result.contains(left));
    }

    if (anchorIsFollowingInwards(bottom)) {
        result.push_back(bottom);
        Q_ASSERT(!result.contains(top));
    }

    Q_ASSERT(result.size() <= 2);
    return result;
}

const Anchor::List AnchorGroup::anchorsNotFollowingInwards() const
{
    Anchor::List result = anchors();
    for (Anchor *a : anchorsFollowingInwards())
        result.removeOne(a);

    return result;
}

const Anchor::List AnchorGroup::anchors() const
{
    return { left, top, right, bottom };
}

Anchor::Side AnchorGroup::sideForAnchor(Anchor *a) const
{
    if (a == left || a == top)
        return Anchor::Side1;
    return Anchor::Side2;
}

bool AnchorGroup::isStatic() const
{
    return top->isStatic() && bottom->isStatic() && left->isStatic() && right->isStatic();
}

bool AnchorGroup::isStaticOrFollowsStatic() const
{
    return top->isStaticOrFollowsStatic() && bottom->isStaticOrFollowsStatic()
            && left->isStaticOrFollowsStatic() && right->isStaticOrFollowsStatic();
}

void AnchorGroup::updateItemSizes()
{
    // Sets the geometry of the items that are inside this group
    left->updateItemSizes();
    top->updateItemSizes();
    right->updateItemSizes();
    bottom->updateItemSizes();
}

void AnchorGroup::assertIsSquashed()
{
    if (!isStaticOrFollowsStatic() && !isSquashed()) {
        layout->dumpDebug();
        qWarning() << "The group should be squashed"
                   << "; shouldFollow=" << left->shouldFollow() << top->shouldFollow() << right->shouldFollow() << bottom->shouldFollow()
                   << "\n; isStatic=" << left->isStatic() << top->isStatic() << right->isStatic() << bottom->isStatic()
                   << "\n; isFollowing=" << left->isFollowing() << top->isFollowing() << right->isFollowing() << bottom->isFollowing()
                   << "\n; followee=" << left->followee() << top->followee() << right->followee() << bottom->followee()
                   << "; right.onlyHasPlaceholderItems=" << right->onlyHasPlaceholderItems(Anchor::Side1);

        Q_ASSERT(false);
    }
}

void AnchorGroup::setAnchor(Anchor *a, Qt::Orientation orientation, Anchor::Side side)
{
    const bool isSide1 = side == Anchor::Side1;
    if (orientation == Qt::Vertical) {
        if (isSide1)
            right = a;
        else
            left = a;
    } else {
        if (isSide1)
            bottom = a;
        else
            top = a;
    }
}

Anchor *AnchorGroup::adjacentAnchor(Anchor *other) const
{
    if (other == top)
        return right;
    if (other == right)
        return bottom;
    if (other == bottom)
        return left;
    if (other == left)
        return top;

    return nullptr;
}

void AnchorGroup::addItem(Item *item)
{
    // Dropping a single dockwidget, without any nesting
    left->addItem(item, Anchor::Side2);
    top->addItem(item, Anchor::Side2);
    right->addItem(item, Anchor::Side1);
    bottom->addItem(item, Anchor::Side1);
}

void AnchorGroup::addItem(MultiSplitterLayout *sourceMultiSplitter)
{
    // Here we rip all the widgets and anchors from the source multisplitter into the receiving multisplitter
    // preserving the layout between source widgets. Then we delete the source splitter, as all its
    // content has bene integrated into ours

    // To prevent the source splitter from deleting the anchors once the widgets are reparented
    sourceMultiSplitter->m_beingMergedIntoAnotherMultiSplitter = true;

    // Reparent the widgets:
    for (Item *sourceItem : sourceMultiSplitter->items()) {
        sourceItem->setLayout(layout);
        sourceItem->setVisible(true);
    }

    // Reparent the inner anchors, they're ours now
    for (Anchor *anchor : sourceMultiSplitter->anchors()) {
        if (!anchor->isStatic()) {
            const qreal positionPercentage = anchor->positionPercentage();
            anchor->setLayout(layout);
            anchor->setVisible(true);

            if (anchor->from()->isStatic()) {
                if (anchor->isVertical()) {
                    anchor->setFrom(top);
                } else {
                    anchor->setFrom(left);
                }
            }

            if (anchor->to()->isStatic()) {
                if (anchor->isVertical()) {
                    anchor->setTo(bottom);
                } else {
                    anchor->setTo(right);
                }
            }

            // And update their position

            qreal newPos = 0;
            if (anchor->isVertical()) {
                newPos = left->position() + (width() * positionPercentage);
            } else {
                newPos = top->position() + (height() * positionPercentage);
            }
            anchor->setPosition(static_cast<int>(newPos));
        }
    }

    AnchorGroup sourceAnchorGroup = sourceMultiSplitter->staticAnchorGroup();

    Q_ASSERT(sourceAnchorGroup.isValid());
    top->consume(sourceAnchorGroup.top);
    bottom->consume(sourceAnchorGroup.bottom);
    left->consume(sourceAnchorGroup.left);
    right->consume(sourceAnchorGroup.right);

    delete sourceMultiSplitter->parentWidget(); // Delete MultiSplitterWidget and MultiSplitterLayout
}

void AnchorGroup::removeItem(Item *item)
{
    left->removeItem(item);
    right->removeItem(item);
    bottom->removeItem(item);
    top->removeItem(item);

    if (left->isUnneeded()) {
        layout->updateAnchorsFromTo(left, right);
        const int leftPosition = left->position();
        right->consume(left, Anchor::Side1);

        if (!right->isUnneeded() && !right->isStatic()) {
            // Make use of the extra space, so it's fair
            right->setPosition(right->position() - ((right->position() - leftPosition) / 2));
        }
    }

    if (right->isUnneeded()) {
        layout->updateAnchorsFromTo(right, left);
        left->consume(right, Anchor::Side2);
    }

    if (top->isUnneeded()) {
        layout->updateAnchorsFromTo(top, bottom);
        const int topPosition = top->position();
        bottom->consume(top, Anchor::Side1);

        if (!bottom->isUnneeded() && !bottom->isStatic()) {
            // Make use of the extra space, so it's fair
            bottom->setPosition(bottom->position() - ((bottom->position() - topPosition) / 2));
        }
    }

    if (bottom->isUnneeded()) {
        layout->updateAnchorsFromTo(bottom, top);
        top->consume(bottom, Anchor::Side2);
    }
}

void AnchorGroup::turnIntoPlaceholder()
{
    qCDebug(placeholder) << Q_FUNC_INFO << *this;

    struct RAIIScopeGuard
    {
        AnchorGroup &m_group;

        RAIIScopeGuard(AnchorGroup &group)
            : m_group(group)
        {
        }

        ~RAIIScopeGuard()
        {
            m_group.assertIsSquashed();
            m_group.layout->emitVisibleWidgetCountChanged();
        }
    private:
        Q_DISABLE_COPY(RAIIScopeGuard)
    } guard(*this);

    if (isSquashed()) {
        return; // Nothing to do
    }

    if (left->shouldFollow()) {
        if (Anchor *followee = left->endFollowee()) {
            // Left is already following something else
            if (!followee->isStatic() && followee->onlyHasPlaceholderItems(Anchor::Side2)) {
                followee->setFollowee(right);
                return;
            }
        } else {
            // Make use of the extra space, so it's fair. When a dock widget in the middle is closed, both left/right widgets can use the space.
            if (!right->isStatic() && right->onlyHasPlaceholderItems(Anchor::Side1) && !right->isFollowing())
                right->setPosition(right->position() - ((right->position() - left->position()) / 2));
            left->setFollowee(right);
            return;
        }
    }

    if (top->shouldFollow()) {
        if (Anchor *followee = top->endFollowee()) {
            // Top is already following something else
            if (!followee->isStatic() && followee->onlyHasPlaceholderItems(Anchor::Side2)) {
                followee->setFollowee(bottom);
                return;
            }
        } else {
            // Make use of the extra space, so it's fair. When a dock widget in the middle is closed, both left/right widgets can use the space.
            if (!bottom->isStatic() && bottom->onlyHasPlaceholderItems(Anchor::Side1) && !bottom->isFollowing())
                bottom->setPosition(bottom->position() - ((bottom->position() - top->position()) / 2));
            top->setFollowee(bottom);
            return;
        }
    }

    if (bottom->shouldFollow()) {
        if (Anchor *followee = bottom->endFollowee()) {
            // Bottom is already following something else (outwards), that something else will follow up
            if (!followee->isStatic() && followee->onlyHasPlaceholderItems(Anchor::Side1)) {
                followee->setFollowee(top);
                return;
            }
        } else {
            bottom->setFollowee(top);
            return;
        }
    }

    if (right->shouldFollow()) {
        if (Anchor *followee = right->endFollowee()) {
            // Right is already following something else (outwards), that something else will follow left
            if (!followee->isStatic() && followee->onlyHasPlaceholderItems(Anchor::Side1)) {
                followee->setFollowee(left);
                return;
            }
        } else {
            right->setFollowee(left);
            return;
        }
    }
}

bool AnchorGroup::isSquashed() const
{
    // If left or top are following to Side2 that's inwards, so our group is squashed. Because it's holding a placeholder
    // Side1 is inwards for right and bottom.

    return !anchorsFollowingInwards().isEmpty();
}
