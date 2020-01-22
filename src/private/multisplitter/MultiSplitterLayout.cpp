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

#include "MultiSplitterLayout_p.h"
#include "Logging_p.h"
#include "MultiSplitter_p.h"
#include "Frame_p.h"
#include "FloatingWindow_p.h"
#include "DockWidgetBase.h"
#include "LastPosition_p.h"
#include "DockRegistry_p.h"
#include "Config.h"
#include "Separator_p.h"
#include "FrameworkWidgetFactory.h"
#include "LayoutSaver.h"

#include <QAction>
#include <QEvent>
#include <QtMath>
#include <QScopedValueRollback>

#define INDICATOR_MINIMUM_LENGTH 100
#define KDDOCKWIDGETS_MIN_WIDTH 80
#define KDDOCKWIDGETS_MIN_HEIGHT 90

using namespace KDDockWidgets;

const QString MultiSplitterLayout::s_magicMarker = QStringLiteral("bac9948e-5f1b-4271-acc5-07f1708e2611");

static Qt::Orientation anchorOrientationForLocation(Location l)
{
    return (l == Location_OnLeft || l == Location_OnRight) ? Qt::Vertical
                                                           : Qt::Horizontal;
}

MultiSplitterLayout::MultiSplitterLayout(MultiSplitter *parent)
    : QObject(parent)
    , m_multiSplitter(parent)
    , m_leftAnchor(new Anchor(Qt::Vertical, this, Anchor::Type_LeftStatic))
    , m_topAnchor(new Anchor(Qt::Horizontal, this, Anchor::Type_TopStatic))
    , m_rightAnchor(new Anchor(Qt::Vertical, this, Anchor::Type_RightStatic))
    , m_bottomAnchor(new Anchor(Qt::Horizontal, this, Anchor::Type_BottomStatic))
    , m_staticAnchorGroup(this)
{
    Q_ASSERT(parent);

    DockRegistry::self()->registerLayout(this);

    setSize(parent->size());

    qCDebug(multisplittercreation()) << "MultiSplitter";
    connect(this, &MultiSplitterLayout::widgetCountChanged, this, [this] {
        Q_EMIT visibleWidgetCountChanged(visibleCount());
    });

    m_leftAnchor->setObjectName(QStringLiteral("left"));
    m_rightAnchor->setObjectName(QStringLiteral("right"));
    m_bottomAnchor->setObjectName(QStringLiteral("bottom"));
    m_topAnchor->setObjectName(QStringLiteral("top"));

    m_leftAnchor->setFrom(m_topAnchor);
    m_leftAnchor->setTo(m_bottomAnchor);
    m_rightAnchor->setFrom(m_topAnchor);
    m_rightAnchor->setTo(m_bottomAnchor);

    m_topAnchor->setFrom(m_leftAnchor);
    m_topAnchor->setTo(m_rightAnchor);
    m_bottomAnchor->setFrom(m_leftAnchor);
    m_bottomAnchor->setTo(m_rightAnchor);

    m_staticAnchorGroup.left = m_leftAnchor;
    m_staticAnchorGroup.right = m_rightAnchor;
    m_staticAnchorGroup.top = m_topAnchor;
    m_staticAnchorGroup.bottom = m_bottomAnchor;

    clear();

    positionStaticAnchors();

    // Initialize min size
    updateSizeConstraints();
    m_inCtor = false;
}

MultiSplitterLayout::~MultiSplitterLayout()
{
    qCDebug(multisplittercreation) << "~MultiSplitter" << this;
    m_inDestructor = true;
    const auto anchors = m_anchors;
    qDeleteAll(anchors);
    DockRegistry::self()->unregisterLayout(this);
}

/**static*/
QSize MultiSplitterLayout::hardcodedMinimumSize()
{
    return QSize(KDDOCKWIDGETS_MIN_WIDTH, KDDOCKWIDGETS_MIN_HEIGHT);
}

MultiSplitter *MultiSplitterLayout::multiSplitter() const
{
    return m_multiSplitter;
}

bool MultiSplitterLayout::validateInputs(QWidgetOrQuick *widget,
                                         Location location,
                                         const Frame *relativeToFrame, AddingOption option) const
{
    if (!widget) {
        qWarning() << Q_FUNC_INFO << "Widget is null";
        return false;
    }

    const bool isDockWidget = qobject_cast<DockWidgetBase*>(widget);
    const bool isStartHidden = option & AddingOption_StartHidden;

    if (!qobject_cast<Frame*>(widget) && !qobject_cast<MultiSplitter*>(widget) && !isDockWidget) {
        qWarning() << "Unknown widget type" << widget;
        return false;
    }

    if (isDockWidget != isStartHidden) {
        qWarning() << "Wrong parameters" << isDockWidget << isStartHidden;
        return false;
    }

    if (relativeToFrame && relativeToFrame == widget) {
        qWarning() << "widget can't be relative to itself";
        return false;
    }

    Item *item = itemForFrame(qobject_cast<Frame*>(widget));

    if (contains(item)) {
        qWarning() << "MultiSplitterLayout::addWidget: Already contains" << widget;
        return false;
    }// TODO: check for widget changing parent

    if (location == Location_None) {
        qWarning() << "MultiSplitterLayout::addWidget: not adding to location None";
        return false;
    }

    const bool relativeToThis = relativeToFrame == nullptr;

    Item *relativeToItem = itemForFrame(relativeToFrame);
    if (!relativeToThis && !contains(relativeToItem)) {
        qWarning() << "MultiSplitterLayout::addWidget: Doesn't contain relativeTo:"
                   << relativeToFrame
                   << "; options=" << option;
        return false;
    }

    return true;
}

std::pair<int,int> MultiSplitterLayout::boundInterval(int newPos1, Anchor* anchor1, int newPos2, Anchor *anchor2) const
{
    const int bound1 = boundPositionForAnchor(anchor1, Anchor::Side1);
    const int bound2 = boundPositionForAnchor(anchor2, Anchor::Side2);

    if (newPos1 >= bound1 && newPos2 <= bound2) {
        // Simplest case, it's bounded.
        return { newPos1, newPos2 };
    }

    if (newPos1 < bound1) {
        // the anchor1 is out of bounds

        const int bythismuch = bound1 - newPos1;
        newPos1 = bound1;
        newPos2 = newPos2 + bythismuch;

        if (newPos2 > bound2) {
            qWarning() << "Adjusted interval still out of bounds. Not enough space. #1";
        }

        return { newPos1, newPos2 };
    } else if (newPos2 > bound2) {
        // the anchor2 is out of bounds

        const int bythismuch = newPos2 - bound2;
        newPos2 = bound2;
        newPos1 = newPos1 - bythismuch;

        if (newPos1 < bound1) {
            qWarning() << "Adjusted interval still out of bounds. Not enough space. #1";
        }

        return { newPos1, newPos2 };
    }

    return { newPos1, newPos2 };
}

void MultiSplitterLayout::addWidget(QWidgetOrQuick *w, Location location, Frame *relativeToWidget, AddingOption option)
{
    auto frame = qobject_cast<Frame*>(w);
    qCDebug(addwidget) << Q_FUNC_INFO << w
                       << "; location=" << locationStr(location)
                       << "; relativeTo=" << relativeToWidget
                       << "; size=" << size()
                       << "; w.size=" << w->size()
                       << "; w.min=" << KDDockWidgets::widgetMinLength(w, anchorOrientationForLocation(location))
                       << "; frame=" << frame
                       << "; option=" << option;

    if (itemForFrame(frame) != nullptr) {
        // Item already exists, remove it.
        // Changing the frame parent will make the item clean itself up. It turns into a placeholder and is removed by unrefOldPlaceholders
        frame->setParent(nullptr); // so ~Item doesn't delete it
        frame->setLayoutItem(nullptr); // so Item is destroyed, as there's no refs to it
    }

    // Make some sanity checks:
    if (!validateInputs(w, location, relativeToWidget, option))
        return;

    unrefOldPlaceholders(framesFrom(w));

    Item *relativeToItem = itemForFrame(relativeToWidget);

    ensureEnoughSize(w, location, relativeToItem);

    if (option & AddingOption_StartHidden) {
        addAsPlaceholder(qobject_cast<DockWidgetBase*>(w), location, relativeToItem);
        return;
    }

    Anchor *newAnchor = nullptr;
    const QRect dropRect = rectForDrop(w, location, relativeToItem);

    if (dropRect.size().isNull() || dropRect.x() < 0 || dropRect.y() < 0) {
        qWarning() << Q_FUNC_INFO << "Invalid drop rect" << dropRect
                   << "\n    size=" << m_multiSplitter->size() << "; size="<< m_size
                   << "\n    location=" << location
                   << "\n    window=" << m_multiSplitter->window()
                   << "\n    this=" << this
                   << "\n    availableHeight=" << availableLengthForOrientation(Qt::Horizontal)
                   << "\n    availableWidth=" << availableLengthForOrientation(Qt::Vertical)
                   << "\n    widget.minSize=" << widgetMinLength(w, anchorOrientationForLocation(location));
        return;
    }

    m_addingItem = true;

    auto result = this->createTargetAnchorGroup(location, relativeToItem);
    AnchorGroup targetAnchorGroup = result.first;
    newAnchor = result.second;

    if (newAnchor && !newAnchor->isFollowing()) {
        const int anchorThickness = Anchor::thickness(/*static=*/false);
        qCDebug(sizing) << "Drop rect" << dropRect;

        int posForExistingAnchor = 0;
        int posForNewAnchor = 0;
        Anchor *existingAnchor = targetAnchorGroup.anchor(location);
        Anchor *direction1Anchor = nullptr;
        Anchor *direction2Anchor = nullptr;

        switch (location) {
        case Location_OnLeft:
            posForExistingAnchor = dropRect.left() - existingAnchor->thickness();
            posForNewAnchor = dropRect.right() + 1;
            break;
        case Location_OnTop:
            posForExistingAnchor = dropRect.top() - existingAnchor->thickness();
            posForNewAnchor = dropRect.bottom() + 1;
            break;
        case Location_OnBottom:
            posForExistingAnchor = dropRect.bottom() + 1;
            posForNewAnchor = dropRect.top() - anchorThickness;
            break;
        case Location_OnRight:
            posForExistingAnchor = dropRect.right() + 1;
            posForNewAnchor = dropRect.left() - anchorThickness;
            break;
        case Location_None:
            Q_ASSERT(false);
            break;
        }

        int delta1 = 0;
        int delta2 = 0;
        const int originalExistingAnchorPos = existingAnchor->position();

        switch (location) {
        case Location_OnLeft:
        case Location_OnTop:
            direction1Anchor = existingAnchor;
            direction2Anchor = newAnchor;
            std::tie(posForExistingAnchor, posForNewAnchor) = boundInterval(posForExistingAnchor, existingAnchor, posForNewAnchor, newAnchor);
            delta1 = originalExistingAnchorPos - posForExistingAnchor;
            delta2 = posForNewAnchor - posForExistingAnchor;
            break;
        case Location_OnRight:
        case Location_OnBottom:
            direction1Anchor = newAnchor;
            direction2Anchor = existingAnchor;
            std::tie(posForNewAnchor, posForExistingAnchor) = boundInterval(posForNewAnchor, newAnchor, posForExistingAnchor, existingAnchor);
            delta1 = posForExistingAnchor - posForNewAnchor;
            delta2 = posForExistingAnchor - originalExistingAnchorPos;
            break;
        case Location_None:
            qWarning() << Q_FUNC_INFO << "Location can't be none";
            return;
        }

        newAnchor->setPosition(posForNewAnchor);

        if (posForExistingAnchor != originalExistingAnchorPos) {
            if (existingAnchor->isStatic()) {
                qWarning() << "Trying to move static anchor from" << originalExistingAnchorPos << "to"
                         << posForExistingAnchor << "; location=" << location
                         << "; dropRect=" << dropRect
                         << "; existingAnchor=" << existingAnchor
                         << "; size=" << m_size
                         << "; Qt::WA_PendingResizeEvent=" << m_multiSplitter->testAttribute(Qt::WA_PendingResizeEvent)
                         << "; Qt::WA_WState_Created=" << m_multiSplitter->testAttribute(Qt::WA_WState_Created);
            }
            existingAnchor->setPosition(posForExistingAnchor);
        }

        // If you drop a 100px in the middle of a layout, it will steal some space from the left widgets
        // and still some space from the right ones. delta1 is the space stolen at the left
        // delta2 is the space stolen at the right. The sum of delta1+delta2 is the size of the widget
        // (plus the splitter). Then we propagate the resize, so that all widgets chip in and get smaller
        // to make room for ours.
        propagateResize(delta1, direction1Anchor, /*direction*/ Anchor::Side1);
        propagateResize(delta2, direction2Anchor, /*direction*/ Anchor::Side2);
    }

    if (newAnchor) {
        // Also ensure the widget has a minimum size in the other direction. So, when adding to
        // left/right, it will still have its minimum height honoured, and vice-versa.
        QPair<Anchor*, Anchor*> adjacentAnchors = targetAnchorGroup.adjacentAnchors(newAnchor);

        const int bound1 = boundPositionForAnchor(adjacentAnchors.first, Anchor::Side1);
        const int bound2 = boundPositionForAnchor(adjacentAnchors.second, Anchor::Side2);

        const Qt::Orientation otherOrientation = adjacentAnchors.first->orientation();
        const int min = widgetMinLength(w, otherOrientation);
        const int has = targetAnchorGroup.itemSize(otherOrientation);
        const int needs = min - has;
        if (needs > 0) {
            const int pos1 = qMax(bound1, adjacentAnchors.first->position() - needs);
            const int pos2 = pos1 + adjacentAnchors.first->thickness() + min;
            Q_ASSERT(pos2 <= bound2);
            adjacentAnchors.first->setPosition(pos1);
            adjacentAnchors.second->setPosition(pos2);
        }
    }

    auto sourceMultiSplitter = qobject_cast<MultiSplitter *>(w);
    auto sourceMultiSplitterLayout = sourceMultiSplitter ? sourceMultiSplitter->multiSplitterLayout()
                                                         : nullptr;

    if (sourceMultiSplitterLayout) {
        auto items = sourceMultiSplitterLayout->items();
        targetAnchorGroup.addItem(sourceMultiSplitterLayout);
        addItems_internal(items);
    } else {
        Q_ASSERT(frame);
        auto item = new Item(frame, this);
        targetAnchorGroup.addItem(item);
        addItems_internal(ItemList{ item });
    }

    updateAnchorFollowing();
    m_addingItem = false;

    maybeCheckSanity();
}

void MultiSplitterLayout::addItems_internal(const ItemList &items, bool updateConstraints, bool emitSignal)
{
    m_items << items;
    if (updateConstraints)
        updateSizeConstraints();

    for (auto item : items) {
        item->setLayout(this);
        if (item->frame()) {
            item->setVisible(true);
            item->frame()->installEventFilter(this);
            Q_EMIT widgetAdded(item);
        }
    }

    if (emitSignal)
        Q_EMIT widgetCountChanged(m_items.size());
}

void MultiSplitterLayout::addAsPlaceholder(DockWidgetBase *dockWidget, Location location, Item *relativeTo)
{
    if (!dockWidget) {
        qWarning() << Q_FUNC_INFO << "null dockwidget";
        return;
    }

    dockWidget->setParent(nullptr);

    auto result = createTargetAnchorGroup(location, relativeTo);
    AnchorGroup targetAnchorGroup = result.first;

    auto frame = Config::self().frameworkWidgetFactory()->createFrame(m_multiSplitter);
    auto item = new Item(frame, this);

    targetAnchorGroup.addItem(item);
    addItems_internal(ItemList{ item }, false);

    dockWidget->addPlaceholderItem(item);
    delete frame;

    updateAnchorFollowing();
    Q_ASSERT(!dockWidget->isVisible());
    maybeCheckSanity();
}

void MultiSplitterLayout::ensureEnoughSize(const QWidgetOrQuick *widget,
                                                   Location location, const Item *relativeToItem)
{
    const int neededAnchorThickness = isEmpty() ? 0 : Anchor::thickness(/*static=*/ false);
    const QSize available = availableSize();
    const QSize widgetMin = { widgetMinLength(widget, Qt::Vertical), widgetMinLength(widget, Qt::Horizontal) };
    const QSize oldSize = m_size;
    const int neededWidth = widgetMin.width() - available.width() + neededAnchorThickness;
    const int neededHeight = widgetMin.height() - available.height() + neededAnchorThickness;

    QSize newSize = m_size;
    if (neededWidth > 0)
        newSize.setWidth(newSize.width() + neededWidth);
    if (neededHeight > 0)
        newSize.setHeight(newSize.height() + neededHeight);

    if (newSize != m_size)
        setSize(newSize);

    // Just to make sure:
    if (lengthForDrop(widget, location, relativeToItem).isNull()) {
        qWarning() << Q_FUNC_INFO << "failed! Please report a bug."
                   << "; oldAvailable=" << available
                   << "; newAvailable=" << availableSize()
                   << "; newSize=" << newSize
                   << "; m_size=" << m_size
                   << "; oldSize=" << oldSize
                   << "; widgetMin=" << widgetMin
                   << "; isEmpty=" << isEmpty();
    }
}

void MultiSplitterLayout::ensureAnchorsBounded()
{
    //Ensures all separators are within their bounds, meaning all items obey their min size
    positionStaticAnchors();
    ensureItemsMinSize();
}

static Anchor::List removeSmallestPath(QVector<Anchor::List> &paths)
{
    // Removes and returns the smallest list
    Anchor::List smallestPath;
    int indexOfSmallest = 0;
    for (int i = 0, end = paths.size(); i < end; ++i) {
        const Anchor::List &path = paths.at(i);
        if (path.size() <= smallestPath.size() || smallestPath.isEmpty()) {
            smallestPath = path;
            indexOfSmallest = i;
        }
    }

    paths.removeAt(indexOfSmallest);
    return smallestPath;
}

void MultiSplitterLayout::propagateResize(int delta, Anchor *fromAnchor, Anchor::Side direction)
{
    if (delta < 0)
        qWarning() << Q_FUNC_INFO << "Invalid delta" << delta << fromAnchor << direction;

    if (delta <= 0 || fromAnchor->isStatic())
        return;

    QVector<Anchor::List> paths;
    collectPaths(paths, fromAnchor, direction);

    for (const Anchor::List &path : qAsConst(paths)) {
        qCDebug(sizing) << Q_FUNC_INFO << path;
    }

    Anchor::List anchorsThatAlreadyContributed;
    anchorsThatAlreadyContributed.push_back(fromAnchor);

    while (!paths.isEmpty()) {
        // Get smallest path:
        Anchor::List smallestPath = removeSmallestPath(/*by-ref*/paths);
        if (smallestPath.size() <= 1) {
            // Nothing to do, it has a single anchor, which was already adjusted in addWidget()
            continue;
        }

        const bool towardsSide1 = direction == Anchor::Side1;
        const bool towardsSide2 = !towardsSide1;

        const int sign = towardsSide1 ? -1 : 1;
        const int contributionPerAnchor = (delta / (smallestPath.size() - 1)) * sign; // n-1 because the initial anchor already contributed
        if (qAbs(contributionPerAnchor) < 5) {
            // Too small, don't bother
            continue;
        }

        // Now make those anchors contribute, skipping the first
        for (int i = 1, end = smallestPath.size(); i < end; ++i) {
            Anchor *a = smallestPath.at(i);
            if (!anchorsThatAlreadyContributed.contains(a)) {
                // When moving anchors don't allow widgets to go bellow their min size
                const int bound = boundPositionForAnchor(a, direction);
                int newPosition = a->position() + contributionPerAnchor;
                if ((towardsSide1 && newPosition < bound) ||
                    (towardsSide2 && newPosition > bound)) {
                    newPosition = bound;
                }

                if (a->position() != newPosition) {
                    a->setPosition(newPosition);
                    anchorsThatAlreadyContributed.push_back(a);
                }
            }
        }
    }
}

void MultiSplitterLayout::collectPaths(QVector<Anchor::List> &paths, Anchor *fromAnchor, Anchor::Side direction)
{
    if (fromAnchor->isStatic()) {
        // We've finally reached a border anchor, we can stop now.
        return;
    }

    if (paths.isEmpty())
        paths.push_back({});

    int currentPathIndex = paths.size() - 1; // Store the index instead of using "Anchor::List &currentPath = paths.last();" as the references are stable, as the paths vector reallocates

    paths[currentPathIndex].push_back(fromAnchor);

    const ItemList items = fromAnchor->items(direction);
    for (int i = 0, end = items.size(); i < end; ++i) {
        Anchor *nextAnchor = items[i]->anchorAtSide(direction, fromAnchor->orientation());
        if (i > 0) {
            Anchor::List newPath = paths[currentPathIndex];
            paths.push_back(newPath);
        }
        collectPaths(paths, nextAnchor, direction);
    }
}

void MultiSplitterLayout::resizeItem(Frame *frame, int newSize, Qt::Orientation orientation)
{
    // Used for unit-tests only
    Item *item = itemForFrame(frame);
    Q_ASSERT(item);
    Anchor *a = item->anchorAtSide(Anchor::Side2, orientation);
    Q_ASSERT(!a->isStatic());
    const int widgLength = item->length(orientation);
    const int delta = newSize - widgLength;
    qCDebug(::anchors) << Q_FUNC_INFO << "Old position:" << a->position() << "; old w.geo=" << item->geometry();
    a->setPosition(a->position() + delta);
    qCDebug(::anchors) << Q_FUNC_INFO << "New position:" << a->position() << "; new w.geo=" << item->geometry();
}

void MultiSplitterLayout::ensureItemsMinSize()
{
    for (Item *item : qAsConst(m_items)) {
        item->ensureMinSize(Qt::Vertical);
        item->ensureMinSize(Qt::Horizontal);
    }
}

void MultiSplitterLayout::addMultiSplitter(MultiSplitter *sourceMultiSplitter,
                                           Location location,
                                           Frame *relativeTo)
{
    qCDebug(addwidget) << Q_FUNC_INFO << sourceMultiSplitter << location << relativeTo;
    addWidget(sourceMultiSplitter, location, relativeTo);
}

void MultiSplitterLayout::removeItem(Item *item)
{
    if (!item || m_inDestructor || !m_items.contains(item))
        return;

    maybeCheckSanity();

    if (!item->isPlaceholder())
        item->frame()->removeEventFilter(this);
    AnchorGroup anchorGroup = item->anchorGroup();
    anchorGroup.removeItem(item);
    m_items.removeOne(item);

    updateAnchorFollowing();

    Q_EMIT widgetRemoved(item);
    Q_EMIT widgetCountChanged(m_items.size());
}

bool MultiSplitterLayout::contains(const Item *item) const
{
    return m_items.contains(const_cast<Item*>(item));
}

bool MultiSplitterLayout::contains(const Frame *frame) const
{
    return itemForFrame(frame) != nullptr;
}

Item *MultiSplitterLayout::itemAt(QPoint p) const
{
    for (Item *item : m_items) {
        if (!item->isPlaceholder() && item->geometry().contains(p))
            return item;
    }

    return nullptr;
}

void MultiSplitterLayout::clear(bool alsoDeleteStaticAnchors)
{
    const int oldCount = count();
    const int oldVisibleCount = visibleCount();
    const auto items = m_items;
    m_items.clear(); // Clear the item list first, do avoid ~Item() triggering a removal from the list
    qDeleteAll(items);

    const auto anchors = m_anchors;
    m_anchors.clear();

    for (Anchor *anchor : qAsConst(anchors)) {
        anchor->clear();
        if (!anchor->isStatic() || alsoDeleteStaticAnchors) {
            delete anchor;
        }
    }

    if (alsoDeleteStaticAnchors) {
        m_anchors.clear();
        m_topAnchor = nullptr;
        m_bottomAnchor = nullptr;
        m_leftAnchor = nullptr;
        m_rightAnchor = nullptr;
        m_staticAnchorGroup.left = nullptr;
        m_staticAnchorGroup.top = nullptr;
        m_staticAnchorGroup.right = nullptr;
        m_staticAnchorGroup.bottom = nullptr;
    } else {
        m_anchors = { m_topAnchor, m_bottomAnchor, m_leftAnchor, m_rightAnchor };
    }

    if (oldCount > 0)
        Q_EMIT widgetCountChanged(0);
    if (oldVisibleCount > 0)
        Q_EMIT visibleWidgetCountChanged(0);

}

int MultiSplitterLayout::visibleCount() const
{
    int count = 0;
    for (auto item : m_items)
        if (!item->isPlaceholder())
            count++;
    return count;
}

int MultiSplitterLayout::placeholderCount() const
{
    return count() - visibleCount();
}

void MultiSplitterLayout::removeAnchor(Anchor *anchor)
{
    if (!m_inDestructor)
        m_anchors.removeOne(anchor);
}

QPair<int, int> MultiSplitterLayout::boundPositionsForAnchor(Anchor *anchor) const
{
    if (anchor->isStatic()) {
        if (anchor == m_leftAnchor || anchor == m_topAnchor) {
            return {0, 0};
        } else if (anchor == m_rightAnchor || anchor == m_bottomAnchor) {
            const int max = length(anchor->orientation()) - Anchor::thickness(true);
            return {max, max};
        }
    }

    if (anchor->isFollowing())
        anchor = anchor->endFollowee();

    const int minSide1Length = anchor->cumulativeMinLength(Anchor::Side1);
    const int minSide2Length = anchor->cumulativeMinLength(Anchor::Side2);
    const int length = anchor->isVertical() ? width() : height();

    const int bound1 = qMax(0, minSide1Length - anchor->thickness());
    const int bound2 = qMax(0, length - minSide2Length);

    if (bound2 < bound1) {
        qWarning() << Q_FUNC_INFO << "Invalid bounds"
                   << "; bound1=" << bound1
                   << "; bound2=" << bound2
                   << "; layout.size=" << size()
                   << "; layout.min=" << minimumSize()
                   << "; anchor=" << anchor
                   << "; orientation=" << anchor->orientation()
                   << "; minSide1Length=" << minSide1Length
                   << "; minSide2Length=" << minSide2Length
                   << "; side1=" << anchor->side1Items()
                   << "; side2=" << anchor->side2Items()
                   << "; followee=" << anchor->followee()
                   << "; thickness=" << anchor->thickness();
    }

    return { bound1, bound2 };
}

QHash<Anchor *, QPair<int, int> > MultiSplitterLayout::boundPositionsForAllAnchors() const
{
    QHash<Anchor *, QPair<int, int> > result;
    for (Anchor *anchor : m_anchors)
        result.insert(anchor, boundPositionsForAnchor(anchor));

    return result;
}

int MultiSplitterLayout::boundPositionForAnchor(Anchor *anchor, Anchor::Side direction) const
{
    auto bounds = boundPositionsForAnchor(anchor);
    return direction == Anchor::Side1 ? bounds.first
                                      : bounds.second;
}

MultiSplitterLayout::Length MultiSplitterLayout::availableLengthForDrop(Location location, const Item *relativeTo) const
{
    Length result;

    const bool relativeToThis = relativeTo == nullptr;

    AnchorGroup anchors = relativeToThis ? staticAnchorGroup()
                                         : relativeTo->anchorGroup();

    Anchor *anchor = nullptr;

    int thisLength = 0;

    switch (location) {
    case KDDockWidgets::Location_None:
        qWarning() << "MultiSplitterLayout::availableLengthForDrop invalid location for dropping";
        return result;
    case KDDockWidgets::Location_OnLeft:
        anchor = anchors.left;
        thisLength = width();
        break;
    case KDDockWidgets::Location_OnTop:
        anchor = anchors.top;
        thisLength = height();
        break;
    case KDDockWidgets::Location_OnRight:
        anchor = anchors.right;
        thisLength = width();
        break;
    case KDDockWidgets::Location_OnBottom:
        anchor = anchors.bottom;
        thisLength = height();
        break;
    }

    const int minForAlreadyOccupied1 = anchor->cumulativeMinLength(Anchor::Side1) - anchor->thickness(); // TODO: Check if this is correct, we're discounting the anchor twice
    const int minForAlreadyOccupied2 = anchor->cumulativeMinLength(Anchor::Side2) - anchor->thickness();

    const int side1AvailableLength = anchor->position() - minForAlreadyOccupied1;
    const int side2AvailableLength = thisLength - (anchor->position() + anchor->thickness()) - minForAlreadyOccupied2;

    const bool needsNewAnchor = hasVisibleItems(); // If a new anchor is needed then we need space for the drag handle and such.
    const int newAnchorThickness = needsNewAnchor ? Anchor::thickness(/*static=*/false) : 0;

    // This useless space doesn't belong to side1 or side2 specifically. So account for it separately.
    const int unusableSpace = newAnchorThickness;

    const int usableLength = qMax(0, side1AvailableLength + side2AvailableLength - unusableSpace);
    if (usableLength > 0) {
        qreal factor = (side1AvailableLength * 1.0) / (side1AvailableLength + side2AvailableLength);
        result.side1Length = int(qRound(usableLength * factor)); // rounding not really needed, but makes things more fair probably
        result.side2Length = usableLength - result.side1Length;
    }

    qCDebug(sizing) << Q_FUNC_INFO
                    << "; available=" << result.length() << result.side1Length << result.side2Length
                    << "; side1AvailableLength=" << side1AvailableLength
                    << "; side2AvailableLength=" << side2AvailableLength
                    << "; minForAlreadyOccupied1=" << minForAlreadyOccupied1
                    << "; minForAlreadyOccupied2=" << minForAlreadyOccupied2
                    << "; thisLength=" << thisLength
                    << "; anchorPos=" << anchor->position()
                    << "; unusableSpace=" << unusableSpace;

    return result;
}

int MultiSplitterLayout::availableLengthForOrientation(Qt::Orientation orientation) const
{
    Length l = availableLengthForDrop(orientation == Qt::Vertical ? Location_OnLeft
                                                                  : Location_OnTop, nullptr);

    return l.length();
}

QSize MultiSplitterLayout::availableSize() const
{
    return { availableLengthForOrientation(Qt::Vertical), availableLengthForOrientation(Qt::Horizontal) };
}

/*
 * Returns the width or height the widget will get when dropped.
 */
MultiSplitterLayout::Length MultiSplitterLayout::lengthForDrop(const QWidgetOrQuick *widget, Location location,
                                                               const Item *relativeTo) const
{
    Q_ASSERT(location != Location_None);

    const Qt::Orientation anchorOrientation = anchorOrientationForLocation(location);
    const int widgetCurrentLength = widgetLength(widget, anchorOrientation);
    Length available = availableLengthForDrop(location, relativeTo);

    const int requiredAtLeast = widgetMinLength(widget, anchorOrientation);
    if (available.length() < requiredAtLeast) {
        qCDebug(sizing) << Q_FUNC_INFO
                        << "\n    Not enough space. available=" << available.length()
                        << "; required=" << requiredAtLeast
                        << "; m_size=" << m_size;
        return {};
    }

    const int suggestedLength = qMin(widgetCurrentLength, int(0.4 * length(anchorOrientation)));
    available.setLength(qBound(requiredAtLeast, suggestedLength, available.length()));

    qCDebug(sizing) << "MultiSplitterLayout::lengthForDrop length=" << available.length()
                    << "; s1=" << available.side1Length << "; s2="<< available.side2Length
                    << "; relativeTo=" << relativeTo
                    << "; relativeTo.geo=" << (relativeTo ? relativeTo->geometry() : QRect())
                    << "; widgetCurrentLength=" << widgetCurrentLength;
    return available;
}

QRect MultiSplitterLayout::rectForDrop(MultiSplitterLayout::Length lfd, Location location, QRect relativeToRect) const
{
    QRect result;
    const int widgetLength = lfd.length();
    const int newAnchorThickness = isEmpty() ? 0 : Anchor::thickness(/*static=*/false);
    const int side1Length = lfd.side1Length;
    const int staticAnchorThickness = Anchor::thickness(/**static=*/true);

    switch (location) {
    case Location_OnLeft:
        result = QRect(qMax(0, relativeToRect.x() - side1Length), relativeToRect.y(),
                       widgetLength, relativeToRect.height());
        break;
    case Location_OnTop:
        result = QRect(relativeToRect.x(), qMax(0, relativeToRect.y() - side1Length),
                       relativeToRect.width(), widgetLength);
        break;
    case Location_OnRight:
        result = QRect(qMin(relativeToRect.right() + 1 - side1Length + newAnchorThickness,
                            width() - widgetLength - staticAnchorThickness), relativeToRect.y(), widgetLength, relativeToRect.height());
        break;
    case Location_OnBottom:
        result = QRect(relativeToRect.x(), qMin(relativeToRect.bottom() + 1 - side1Length + newAnchorThickness,
                                                height() - widgetLength - staticAnchorThickness),
                       relativeToRect.width(), widgetLength);
        break;
    default:
        break;
    }

    qCDebug(sizing) << "MultiSplitterLayout::rectForDrop rect=" << result
                    << "; result.bottomRight=" << result.bottomRight()
                    << "; location=" << location
                    << "; s1=" << side1Length
                    << "; relativeToRect.bottomRight=" << relativeToRect.bottomRight();
    return result;
}

QRect MultiSplitterLayout::rectForDrop(const QWidgetOrQuick *widgetBeingDropped, Location location,
                                       const Item *relativeTo) const
{
    Q_ASSERT(widgetBeingDropped);
    Length lfd = lengthForDrop(widgetBeingDropped, location, relativeTo);
    const bool needsMoreSpace = lfd.isNull();
    if (needsMoreSpace)  {
        // This is the case with the drop indicators. If there's not enough space let's still
        // draw some indicator drop. The window will resize to accommodate the drop.
        lfd.side1Length = INDICATOR_MINIMUM_LENGTH / 2;
        lfd.side2Length = INDICATOR_MINIMUM_LENGTH - lfd.side1Length;
    }

    const int staticAnchorThickness = Anchor::thickness(/**static=*/true);
    const bool relativeToThis = relativeTo == nullptr;
    const QRect relativeToRect = relativeToThis ? m_multiSplitter->rect().adjusted(staticAnchorThickness, staticAnchorThickness,
                                                                                  -staticAnchorThickness, -staticAnchorThickness)
                                                : relativeTo->geometry();

    // This function is split in two just so we can unit-test the math in the second one, which is more involved
    QRect result = rectForDrop(lfd, location, relativeToRect);

    return result;
}

void MultiSplitterLayout::setAnchorBeingDragged(Anchor *anchor)
{
    m_anchorBeingDragged = anchor;
}

Anchor::List MultiSplitterLayout::anchorsFollowing(Anchor *followee) const
{
    if (!followee)
        return {};

    Anchor::List followers;

    for (Anchor *a : m_anchors) {
        if (a->followee() == followee)
            followers.push_back(a);
    }

    return followers;
}

int MultiSplitterLayout::numAchorsFollowing() const
{
    int count = 0;
    for (Anchor *a : m_anchors) {
        if (a->isFollowing())
            count++;
    }

    return count;
}

int MultiSplitterLayout::numVisibleAnchors() const
{
    int count = 0;
    for (Anchor *a : m_anchors) {
        if (a->separatorWidget()->isVisible())
            count++;
    }

    return count;
}

Anchor *MultiSplitterLayout::staticAnchor(Anchor::Type type) const
{
    if (type == Anchor::Type_TopStatic)
        return m_topAnchor;

    if (type == Anchor::Type_BottomStatic)
        return m_bottomAnchor;

    if (type == Anchor::Type_LeftStatic)
        return m_leftAnchor;

    if (type == Anchor::Type_RightStatic)
        return m_rightAnchor;

    return nullptr;
}

Anchor *MultiSplitterLayout::staticAnchor(Anchor::Side side, Qt::Orientation orientation) const
{
    if (orientation == Qt::Vertical) {
        return side == Anchor::Side1 ? m_leftAnchor : m_rightAnchor;
    } else {
        return side == Anchor::Side1 ? m_topAnchor : m_bottomAnchor;
    }
}

AnchorGroup MultiSplitterLayout::anchorsForPos(QPoint pos) const
{
    Item *item = itemAt(pos);
    if (!item)
        return AnchorGroup(const_cast<MultiSplitterLayout *>(this));

    return item->anchorGroup();
}

void MultiSplitterLayout::dumpDebug() const
{
    Q_EMIT aboutToDumpDebug();
    qDebug() << Q_FUNC_INFO << "m_size=" << m_size
             << "; minimumSize=" << minimumSize();

    qDebug() << "Items:";
    for (auto item : items()) {
        qDebug() <<"    " << item
                 << "; min.width=" << item->minLength(Qt::Vertical)
                 << "; min.height=" << item->minLength(Qt::Horizontal)
                 << "; geometry=" << item->geometry()
                 << "; isPlaceholder=" << item->isPlaceholder()
                 << "; refCount=" << item->refCount();

        if (Frame *frame = item->frame())
            frame->dumpDebug();
     }

    qDebug() << "Anchors:";
    for (Anchor *anchor : m_anchors) {
        auto side1Widgets = anchor->items(Anchor::Side1);
        auto side2Widgets = anchor->items(Anchor::Side2);
        auto bounds = anchor->isStatic() ? QPair<int, int>() : boundPositionsForAnchor(anchor);
        qDebug() << "\n    " << anchor
                 << "; side1=" << side1Widgets
                 << "; side2=" << side2Widgets
                 << "; pos=" << anchor->position()
                 << "; sepWidget.pos=" << (anchor->isVertical() ? anchor->separatorWidget()->x()
                                                                : anchor->separatorWidget()->y())
                 << "; sepWidget.visible=" << anchor->separatorWidget()->isVisible()
                 << "; geo=" << anchor->geometry()
                 << "; sep.geo=" << anchor->separatorWidget()->geometry()
                 << "; bounds=" << bounds
                 << "; orientation=" << anchor->orientation()
                 << "; isFollowing=" << anchor->isFollowing()
                 << "; followee=" << anchor->followee()
                 << "; from=" << ((void*)anchor->from())
                 << "; to=" << ((void*)anchor->to())
                 << "; positionPercentage=" << anchor->positionPercentage();
    }

    qDebug() << "Num Frame:" << Frame::dbg_numFrames();
    qDebug() << "Num FloatingWindow:" << FloatingWindow::dbg_numFrames();
}

void MultiSplitterLayout::positionStaticAnchors()
{
    qCDebug(sizing) << Q_FUNC_INFO;
    m_leftAnchor->setPosition(0);
    m_topAnchor->setPosition(0);
    m_bottomAnchor->setPosition(height() - m_bottomAnchor->thickness());
    m_rightAnchor->setPosition(width() - m_rightAnchor->thickness());
}

void MultiSplitterLayout::redistributeSpace(QSize oldSize, QSize newSize)
{
    positionStaticAnchors();
    if (oldSize == newSize || !oldSize.isValid() || !newSize.isValid())
        return;

    qCDebug(sizing) << Q_FUNC_INFO << "old=" << oldSize << "; new=" << newSize;

    const bool widthChanged = oldSize.width() != newSize.width();
    const bool heightChanged = oldSize.height() != newSize.height();

    if (widthChanged)
        redistributeSpace_recursive(m_leftAnchor, 0);
    if (heightChanged)
        redistributeSpace_recursive(m_topAnchor, 0);
}

void MultiSplitterLayout::redistributeSpace_recursive(Anchor *fromAnchor, int minAnchorPos)
{
    for (Item *item : fromAnchor->items(Anchor::Side2)) {
        Anchor *nextAnchor = item->anchorAtSide(Anchor::Side2, fromAnchor->orientation());
        if (nextAnchor->isStatic())
            continue;

        // We use the minPos of the Anchor that had non-placeholder items on its side1.
        if (nextAnchor->hasNonPlaceholderItems(Anchor::Side1))
            minAnchorPos = nextAnchor->minPosition();

        if (nextAnchor->hasNonPlaceholderItems(Anchor::Side2) && !nextAnchor->isFollowing()) {
            const int newPosition = int(nextAnchor->positionPercentage() * length(nextAnchor->orientation()));

            // But don't let the anchor go out of bounds, it must respect its widgets min sizes
            auto bounds = boundPositionsForAnchor(nextAnchor);

            // For the bounding, use Anchor::minPosition, as we're not making the anchors on the left/top shift, which boundsPositionsForAnchor() assumes.
            const int newPositionBounded = qMax(bounds.first, qBound(minAnchorPos, newPosition, bounds.second));

            qCDebug(sizing) << Q_FUNC_INFO << nextAnchor << "bounds.first=" << bounds.first
                            << "; newPosition=" << newPosition
                            << "; bounds.first=" << bounds.first
                            << "; bounds.second=" << bounds.second
                            << "; newPositionBounded=" << newPositionBounded
                            << "; oldPosition=" << nextAnchor->position()
                            << "; size=" << m_size
                            << "; nextAnchor.minPosition=" << minAnchorPos;

            nextAnchor->setPosition(newPositionBounded, Anchor::SetPositionOption_DontRecalculatePercentage);
        }

        redistributeSpace_recursive(nextAnchor, minAnchorPos);
    }
}

void MultiSplitterLayout::updateSizeConstraints()
{
    const int minH = m_topAnchor->cumulativeMinLength(Anchor::Side2);
    const int minW = m_leftAnchor->cumulativeMinLength(Anchor::Side2);

    const QSize newMinSize = QSize(minW, minH);
    qCDebug(sizing) << Q_FUNC_INFO << "Updating size constraints from" << m_minSize
                    << "to" << newMinSize;

    setMinimumSize(newMinSize);
}

int MultiSplitterLayout::wastedSpacing(Qt::Orientation orientation) const
{
    // Wasted spacing due to using splitters:
    int numAnchors = 0;
    for (Anchor *anchor : m_anchors) {
        if (anchor->orientation() == orientation)
            numAnchors++;
    }

    return (2 * Anchor::thickness(/*static=*/ true)) +
           ((numAnchors - 2) * Anchor::thickness(/*static=*/ false));  // 2 of the anchors are always static
}

AnchorGroup MultiSplitterLayout::staticAnchorGroup() const
{
    return m_staticAnchorGroup;
}

Anchor::List MultiSplitterLayout::anchors(Qt::Orientation orientation, bool includeStatic,
                                          bool includePlaceholders) const
{
    Anchor::List result;
    for (Anchor *anchor : m_anchors) {
        if ((includeStatic || !anchor->isStatic()) && (includePlaceholders || !anchor->isFollowing()) && anchor->orientation() == orientation)
            result << anchor;
    }

    return result;
}

Anchor *MultiSplitterLayout::newAnchor(AnchorGroup &group, Location location)
{
    qCDebug(::anchors) << "MultiSplitterLayout::newAnchor" << location;
    Anchor *newAnchor = nullptr;
    Anchor *donor = nullptr;
    switch (location) {
    case Location_OnLeft:
        donor = group.left;
        newAnchor = Anchor::createFrom(donor);
        group.right = newAnchor;
        break;
    case Location_OnTop:
        donor = group.top;
        newAnchor = Anchor::createFrom(donor);
        group.bottom = newAnchor;
        break;
    case Location_OnRight:
        donor = group.right;
        newAnchor = Anchor::createFrom(donor);
        group.left = newAnchor;
        break;
    case Location_OnBottom:
        donor = group.bottom;
        newAnchor = Anchor::createFrom(donor);
        group.top = newAnchor;
        break;
    default:
        qWarning() << "MultiSplitterLayout::newAnchor invalid location!";
        return nullptr;
    }

    Q_ASSERT(newAnchor);
    Q_ASSERT(donor);
    Q_ASSERT(donor != newAnchor);

    updateAnchorsFromTo(donor, newAnchor);

    qCDebug(::anchors()) << newAnchor->hasNonPlaceholderItems(Anchor::Side1)
                         << newAnchor->hasNonPlaceholderItems(Anchor::Side2)
                         << newAnchor->side1Items() << newAnchor->side2Items()
                         << "; donor" << donor
                         << "; follows=" << newAnchor->followee();
    return newAnchor;
}

void MultiSplitterLayout::blockItemPropagateGeo(bool block)
{
    for (Item *item : m_items) {
        if (block)
            item->beginBlockPropagateGeo();
        else
            item->endBlockPropagateGeo();
    }
}

void MultiSplitterLayout::emitVisibleWidgetCountChanged()
{
    if (!m_inDestructor)
        Q_EMIT visibleWidgetCountChanged(visibleCount());
}

Item *MultiSplitterLayout::itemForFrame(const Frame *frame) const
{
    if (!frame)
        return nullptr;

    for (Item *item : m_items) {
        if (item->frame() == frame)
            return item;
    }
    return nullptr;
}

Frame::List MultiSplitterLayout::framesFrom(QWidgetOrQuick *frameOrMultiSplitter) const
{
    if (auto frame = qobject_cast<Frame*>(frameOrMultiSplitter))
        return { frame };

    if (auto msw = qobject_cast<MultiSplitter*>(frameOrMultiSplitter))
        return msw->multiSplitterLayout()->frames();

    return {};
}

Frame::List MultiSplitterLayout::frames() const
{
    Frame::List result;

    for (Item *item : m_items) {
        if (Frame *f = item->frame())
            result.push_back(f);
    }

    return result;
}

QVector<DockWidgetBase *> MultiSplitterLayout::dockWidgets() const
{
    DockWidgetBase::List result;
    const Frame::List frames = this->frames();

    for (Frame *frame : frames)
        result << frame->dockWidgets();

    return result;
}

QPair<AnchorGroup,Anchor*> MultiSplitterLayout::createTargetAnchorGroup(KDDockWidgets::Location location, Item *relativeToItem)
{
    const bool relativeToThis = relativeToItem == nullptr;
    AnchorGroup group = relativeToThis ? staticAnchorGroup()
                                       : anchorsForPos(relativeToItem->geometry().center());

    if (!group.isValid()) {
        qWarning() << Q_FUNC_INFO << "Invalid anchor group:" << group
                   << "; staticAnchorGroup=" << staticAnchorGroup()
                   << "; relativeTo=" << relativeToItem;

        dumpDebug();
    }

    Anchor *newAnchor = nullptr;
    if (relativeToThis) {
        if (!isEmpty())
            newAnchor = this->newAnchor(group, location);
    } else {
        newAnchor = group.createAnchorFrom(location, relativeToItem);
        group.setAnchor(newAnchor, KDDockWidgets::oppositeLocation(location));
    }

    return { group, newAnchor };
}

bool MultiSplitterLayout::checkSanity(AnchorSanityOption options) const
{
    if (m_inCtor || LayoutSaver::restoreInProgress())
        return true;

    auto check = [this, options] (Item *item, Qt::Orientation orientation) {
        int numSide1 = 0;
        int numSide2 = 0;
        const auto &anchors = this->anchors(orientation, /*includeStatic=*/ true);
        for (Anchor *anchor : anchors) {
            if (anchor->containsItem(item, Anchor::Side1))
                numSide1++;
            if (anchor->containsItem(item, Anchor::Side2))
                numSide2++;
        }

        if (numSide1 != 1 || numSide2 != 1) {
            dumpDebug();
            qWarning() << "MultiSplitterLayout::checkSanity:" << "Problem detected! while processing"
                       << orientation << "anchors"
                       << "; numSide1=" << numSide1
                       << "; numSide2=" << numSide2;
            for (Anchor *anchor : anchors) {
                if (anchor->containsItem(item, Anchor::Side1))
                    qDebug() << "Anchor" << anchor << "contains said widget on side1";
                if (anchor->containsItem(item, Anchor::Side2))
                    qDebug() << "Anchor" << anchor << "contains said widget on side2";
            }
            qWarning() << "MultiSplitterLayout::checkSanity:" << numSide1 << numSide2 << item
                       << "\n" << m_topAnchor->items(Anchor::Side2)
                       << "\n" << m_bottomAnchor->items(Anchor::Side1)
                       << "\n" << m_leftAnchor->items(Anchor::Side2)
                       << "\n" << m_rightAnchor->items(Anchor::Side1);
            return false;
        }

        if ((options & AnchorSanity_WidgetInvalidSizes) && !item->isPlaceholder()) {
            if (item->width() <= 0 || item->height() <= 0) {
                dumpDebug();
                qWarning() << "Invalid size for widget" << item << item->size() << "; isPlaceholder=" << item->isPlaceholder();
                return false;
            }
        }

        return true;
    };

    if (!m_topAnchor || !m_leftAnchor || !m_rightAnchor || !m_bottomAnchor) {
        qWarning() << Q_FUNC_INFO << "Invalid static anchors"
                   << m_leftAnchor << m_topAnchor << m_rightAnchor << m_bottomAnchor;
        return false;
    }

    if (m_topAnchor->position() != 0 || m_leftAnchor->position() != 0 ||
            m_rightAnchor->position() != width() - m_rightAnchor->thickness() ||
            m_bottomAnchor->position() != height() - m_bottomAnchor->thickness()) {
        qWarning() << Q_FUNC_INFO << "Invalid anchor position"
                    << " left=" << m_leftAnchor->position()
                    << " top=" << m_topAnchor->position()
                    << " right=" << m_rightAnchor->position()
                    << " bottom=" << m_bottomAnchor->position()
                    << "; size=" << m_size
                    << "; min=" << m_minSize;
        return false;
    }


    for (Anchor *anchor : qAsConst(m_anchors)) {
        if (!anchor->isValid()) {
            dumpDebug();
            qWarning() << "invalid anchor" << anchor;
            return false;
        }

        auto checkSides = [this, anchor] (Anchor::Side side) {
            for (Item *item : anchor->items(side)) {
                if (!contains(item)) {
                    dumpDebug();
                    qWarning() << "MultiSplitterLayout::checkSanity: Anchor has" << item << "but multi splitter does not";
                    return false;
                }
            }
            return true;
        };

        if (!checkSides(Anchor::Side1) || !checkSides(Anchor::Side2))
            return false;

        if (anchor->isFollowing() && !qobject_cast<Anchor*>(anchor->followee())) {
            qWarning() << "Anchor is following but followee was deleted already";
            return false;
        }

        if (options & AnchorSanity_Followers) {
            const bool hasItemsOnBothSides = anchor->hasNonPlaceholderItems(Anchor::Side1) && anchor->hasNonPlaceholderItems(Anchor::Side2);
            if (!anchor->isStatic() && !anchor->isFollowing() && !hasItemsOnBothSides && anchorsFollowing(anchor).isEmpty()) {
                qWarning() << "Non static anchor should have items on both sides unless it's following or being followed" << anchor;
            }
        }

        if (!anchor->isFollowing() &&anchor->geometry() != anchor->separatorWidget()->geometry()) {
            qWarning() << Q_FUNC_INFO << anchor << anchor->separatorWidget()
                       << "Inconsistent anchor geometry" << anchor->geometry() << "; " << anchor->separatorWidget()->geometry();
            return false;
        }

        if (options & AnchorSanity_Visibility) {
            if (multiSplitter()->isVisible() && !anchor->isFollowing() && !anchor->separatorWidget()->isVisible()) {
                qWarning() << Q_FUNC_INFO << "Anchor should be visible" << anchor;
                return false;
            }
        }
    }

    for (Item *item : qAsConst(m_items)) {
        if (!check(item, Qt::Vertical))
            return false;

        if (!check(item, Qt::Horizontal))
            return false;
    }

    // Check that no widget intersects with an anchor
    if (options & AnchorSanity_Intersections) {
        for (Item *item: items()) {
            for (Anchor *a : anchors()) {
                if (!item->isPlaceholder() && item->geometry().intersects(a->geometry())) {
                    dumpDebug();
                    qWarning() << "MultiSplitterLayout::checkSanity: Widget" << item << "with rect" << item->geometry()
                               << "Intersects anchor" << a << "with rect" << a->geometry()
                               << "; a.visible|following|valid|unneeded=" << a->separatorWidget()->isVisible()<< a->isFollowing() << a->isValid() << a->isUnneeded();
                    return false;
                }
            }
        }
    }

    if (options & AnchorSanity_WidgetGeometry) {
        for (Item *item: items()) {

            if (!item->isPlaceholder() && item->geometry() != item->frame()->geometry()) {
                qWarning() << Q_FUNC_INFO << "Invalid geometry for item" << item << item->geometry() << item->frame()->geometry();
                return false;
            }

            if (!item->anchorGroup().isValid()) {
                qWarning() << Q_FUNC_INFO << "Invalid item group for item" << item->anchorGroup();
                return false;
            }

            if (!item->isPlaceholder() && item->anchorGroup().itemSize() != item->size()) {
                qWarning() << Q_FUNC_INFO << "Invaild item size="
                           << item->size()
                           << "group size="
                           << item->anchorGroup().itemSize();
                return false;
            }
        }
    }

    if (options & AnchorSanity_WidgetMinSizes) {
        for (Item *item : items()) {

            if (item->isPlaceholder())
                continue;

            const int minWidth = item->minLength(Qt::Vertical);
            const int minHeight = item->minLength(Qt::Horizontal);

            if (item->width() < minWidth) {
                qWarning() << "MultiSplitterLayout::checkSanity: Widget has width=" << item->width()
                           << "but minimum is" << minWidth
                           << item;
                return false;
            }

            if (item->height() < minHeight) {
                qWarning() << "MultiSplitterLayout::checkSanity: Widget has height=" << item->height()
                           << "but minimum is" << minHeight
                           << item;
                return false;
            }
        }
    }

    for (DockWidgetBase *dw : DockRegistry::self()->dockwidgets()) {
        Frame *frame = dw->frame();
        auto tabWidgetParent = frame ? frame->tabWidget() : nullptr;
        const bool shouldBeChecked = dw->isVisible() || tabWidgetParent;

        if (shouldBeChecked != dw->toggleAction()->isChecked()) {
            qWarning() << Q_FUNC_INFO << "Invalid state for DockWidgetBase::toggleAction()"
                       << dw->toggleAction()->isChecked();
            return false;
        }
    }

/* TODO: uncomment when all tests pass
    if (m_topAnchor->position() != 0 || m_leftAnchor->position() != 0) {
        qWarning() << Q_FUNC_INFO << "Invalid top or left anchor position"
                   << m_topAnchor->position() << m_leftAnchor->position();
        return false;
    }

    if (m_rightAnchor->position() != m_size.width() - 1 || m_bottomAnchor->position() != m_size.height() - 1) {
        qWarning() << Q_FUNC_INFO << "Invalid right or bottom anchor position"
                   << m_rightAnchor->position() << m_bottomAnchor->position()
                   << "; m_size=" << m_size;
        return false;
    }
*/
    return true;
}

void MultiSplitterLayout::maybeCheckSanity()
{
#if defined(DOCKS_DEVELOPER_MODE)
    if (!isRestoringPlaceholder() && !checkSanity(AnchorSanityOption(AnchorSanity_All & ~AnchorSanity_Visibility)))
        qWarning() << Q_FUNC_INFO << "Sanity check failed";
#endif
}

void MultiSplitterLayout::ensureHasAvailableSize(QSize needed)
{
    const QSize availableSize = this->availableSize();

    qCDebug(placeholder) << Q_FUNC_INFO << "; needed=" << needed << availableSize;

    const int deltaWidth = needed.width() > availableSize.width() ? (needed.width() - availableSize.width())
                                                                  : 0;

    const int deltaHeight = needed.height() > availableSize.height() ? (needed.height() - availableSize.height())
                                                                     : 0;

    const QSize newSize = size() + QSize(deltaWidth, deltaHeight);
    setSize(newSize);
}

void MultiSplitterLayout::restorePlaceholder(Item *item)
{
    QScopedValueRollback<bool> restoring(m_restoringPlaceholder, true);

    AnchorGroup anchorGroup = item->anchorGroup();

    const QSize availableSize = this->availableSize();
    const QSize hardcodedMinSize = MultiSplitterLayout::hardcodedMinimumSize();

    const QSize widgetMinSize = { qMax(hardcodedMinSize.width(), KDDockWidgets::widgetMinLength(item->frame(), Qt::Vertical)),
                                  qMax(hardcodedMinSize.height(), KDDockWidgets::widgetMinLength(item->frame(), Qt::Horizontal)) };

    const QSize newSize = {qMax(qMin(item->length(Qt::Vertical), availableSize.width()), widgetMinSize.width()),
                           qMax(qMin(item->length(Qt::Horizontal), availableSize.height()), widgetMinSize.height()) };

    // Our layout has enough size for the dock widget
    ensureHasAvailableSize(newSize);

    item->setIsPlaceholder(false);
    item->beginBlockPropagateGeo();
    updateSizeConstraints();

    Anchor::List anchorsFollowing = anchorGroup.anchorsFollowingInwards();
    if (anchorsFollowing.isEmpty()) {
        // There's no separator to move, it means it's a static anchor group (layout is empty, so the anchors
        // are the actual borders of the window
        // dumpDebug();
        Q_ASSERT(anchorGroup.isStaticOrFollowsStatic());
        anchorGroup.updateItemSizes();
        maybeCheckSanity();
        item->endBlockPropagateGeo();
        return;
    }

    clearAnchorsFollowing();
    QHash<Anchor*,Anchor*> anchorsThatWillFollowOthers = anchorsShouldFollow();

    if (!anchorsFollowing.contains(anchorGroup.top) && !anchorsFollowing.contains(anchorGroup.bottom)) {
        anchorGroup.top->updateItemSizes();
        anchorGroup.bottom->updateItemSizes();
    }
    if (!anchorsFollowing.contains(anchorGroup.left) && !anchorsFollowing.contains(anchorGroup.right)) {
        anchorGroup.left->updateItemSizes();
        anchorGroup.right->updateItemSizes();
    }


    for (Anchor *anchorFollowingInwards : anchorsFollowing) {
        const Qt::Orientation orientation = anchorFollowingInwards->orientation();
        Anchor *side1Anchor = anchorGroup.anchorAtSide(Anchor::Side1, orientation); // returns the left if vertical, otherwise top
        Anchor *side2Anchor = anchorGroup.anchorAtSide(Anchor::Side2, orientation); // returns the right if vertical, otherwise bottom

        if (anchorsThatWillFollowOthers.contains(side1Anchor)) {
            Anchor *followee = anchorsThatWillFollowOthers.value(side1Anchor);
            side1Anchor->setFollowee(followee);
            side1Anchor = followee;
        }

        if (anchorsThatWillFollowOthers.contains(side2Anchor)) {
            Anchor *followee = anchorsThatWillFollowOthers.value(side2Anchor);
            side2Anchor->setFollowee(followee);
            side2Anchor = followee;
        }

        const int oldPosition1 = side1Anchor->position();
        const int oldPosition2 = side2Anchor->position();
        const int boundPosition1 = side1Anchor->isStatic() ? side1Anchor->position()
                                                           : boundPositionForAnchor(side1Anchor, Anchor::Side1);

        const int boundPosition2 = side2Anchor->isStatic() ? side2Anchor->position()
                                                           : boundPositionForAnchor(side2Anchor, Anchor::Side2);

        // Double check the available space again, for sanity
        if (!anchorGroup.hasAvailableSizeFor(newSize, orientation)) {
            qWarning() << "There's not enough space: bound2=" << boundPosition2
                       << "; bound1=" << boundPosition1
                       << "; newSize=" << newSize
                       << "; anchorGroup.available" << anchorGroup.availableSize()
                       << "; widgetMinSize=" << widgetMinSize
                       << "; newspace=" << boundPosition2 - boundPosition1 - side1Anchor->thickness()
                       << "; available_old=" << availableSize
                       << "; available_new=" << this->availableSize()
                       << "; anchors=" << side1Anchor << side2Anchor
                       << "; oldPos1=" << oldPosition1
                       << "; oldPos2=" << oldPosition2
                       << "; thickness=" << side1Anchor->thickness() << side2Anchor->thickness()
                       << "; isFollowing=" << side1Anchor->isFollowing() << side2Anchor->isFollowing()
                       << "; static=" << side1Anchor->isStatic() << side2Anchor->isStatic()
                       << "; size=" << m_size
                       << "; m_minSize=" << m_minSize;
            item->endBlockPropagateGeo();
            return;
        }

        const int newLength = anchorFollowingInwards->isVertical() ? newSize.width() : newSize.height();
        // Let's try that each anchor contributes 50%, so that the widget appears centered
        const int suggestedLength1 = qMin(newLength, qCeil(newLength / 2) + side1Anchor->thickness() + 1);
        const int maxPos1 = boundPosition2 - newLength - side1Anchor->thickness();
        const int newPosition1 = qMax(qMin(maxPos1, oldPosition1 - suggestedLength1), boundPosition1); // Honour the bound
        const int newPosition2 = newPosition1 + side1Anchor->thickness() + newLength; // No need to check bound2, we have enough space afterall

        qCDebug(placeholder) << Q_FUNC_INFO
                             << "; oldPos1=" << oldPosition1
                             << "; oldPos2=" << oldPosition2
                             << "; newPosition1=" << newPosition1
                             << "; newPosition2=" << newPosition2
                             << "; bounds1=" << boundPosition1
                             << "; bounds2=" << boundPosition2
                             << "; item.geo=" << item->geometry()
                             << "; newSize=" << newSize
                             << "; side1Anchor=" << side1Anchor
                             << "; side2Anchor=" << side2Anchor
                             << side1Anchor->followee() << side2Anchor->followee()
                             << "; anchorFollowing=" << anchorFollowingInwards
                             << "; size=" << m_size
                             << "; minSize=" << m_minSize
                             << "; widgetMinSize=" << widgetMinSize
                             << "; available_old=" << availableSize
                             << "; available_new=" << availableLengthForOrientation(orientation)
                             << "; item.size=" << item->size();

        if (newPosition1 < boundPosition1 || newPosition2 > boundPosition2) {
            qWarning() << Q_FUNC_INFO << "Out of bounds"
                       // << "bounds.anchor1=" << boundPositionsForAnchor(side1Anchor)
                       << "bounds.anchor2=" << boundPositionsForAnchor(side2Anchor)
                       << "; side1Anchor.thickness" << side1Anchor->thickness()
                       << "; side2Anchor.thickness" << side2Anchor->thickness();
        }

        // We don't want item to resize the anchors while setting newPosition1, we already calculated it
        if (side1Anchor->isStatic()) {
            side1Anchor->updateItemSizes();
        } else {
            side1Anchor->setPosition(newPosition1);
        }

        if (side2Anchor->isStatic()) {
            side2Anchor->updateItemSizes();
        } else {
            side2Anchor->setPosition(newPosition2);
        }
    }
    item->endBlockPropagateGeo();

    updateAnchorFollowing();
    maybeCheckSanity();
}

void MultiSplitterLayout::unrefOldPlaceholders(const Frame::List &framesBeingAdded) const
{
    for (Frame *frame : framesBeingAdded) {
        for (DockWidgetBase *dw : frame->dockWidgets()) {
            if (Item *existingItem = dw->lastPosition()->layoutItem()) {
                if (contains(existingItem)) { // We're only interested in placeholders from this layout
                    dw->lastPosition()->removePlaceholders(this);
                }
            }
        }
    }
}

void MultiSplitterLayout::setSize(QSize size)
{
    if (size != m_size) {
        m_resizing = true;
        QSize oldSize = m_size;

        if (size.width() < m_minSize.width() || size.height() < m_minSize.height()) {
            qWarning() << Q_FUNC_INFO << "new size is smaller than min size. Size=" << size << "; min=" << m_minSize;
            return;
        }

#if defined(DOCKS_DEVELOPER_MODE)
        if (!m_inCtor && false) { // TODO Uncomment when it passes
            QSize minSizeCalculated = QSize(availableLengthForOrientation(Qt::Vertical), availableLengthForOrientation(Qt::Horizontal));
            if (size.width() < minSizeCalculated.width() || size.height() < minSizeCalculated.height()) {
                qWarning() << Q_FUNC_INFO << "new size is smaller than min size calculated" << size << minSizeCalculated;
            }
        }
#endif

        m_size = size;
        Q_EMIT sizeChanged(size);

        redistributeSpace(oldSize, size);
        m_resizing = false;

        if (!m_restoringPlaceholder) { // ensureAnchorsBounded() is run at the end of restorePlaceholder() already.
            ensureAnchorsBounded();
        }
    }
}

void MultiSplitterLayout::setContentLength(int value, Qt::Orientation o)
{
    if (o == Qt::Vertical) {
        // Setting the width
        setSize({value, m_size.height()});
    } else {
        // Setting the height
        setSize({m_size.width(), value});
    }
}

int MultiSplitterLayout::length(Qt::Orientation o) const
{
    return o == Qt::Vertical ? width()
                             : height();
}

void MultiSplitterLayout::setMinimumSize(QSize sz)
{
    if (sz != m_minSize) {
        m_minSize = sz;
        setSize(m_size.expandedTo(m_minSize)); // Increase size incase we need to
        Q_EMIT minimumSizeChanged(sz);
    }
    qCDebug(sizing) << Q_FUNC_INFO << "minSize = " << m_minSize;
}

void MultiSplitterLayout::updateAnchorsFromTo(Anchor *oldAnchor, Anchor *newAnchor)
{
    // Update the from/to of other anchors
    for (Anchor *other : qAsConst(m_anchors)) {
        Q_ASSERT(other);
        Q_ASSERT(other->isValid());
        if (!other->isStatic() && other->orientation() != newAnchor->orientation()) {
            if (other->to() == oldAnchor) {
                other->setTo(newAnchor);
            } else if (other->from() == oldAnchor) {
                other->setFrom(newAnchor);
            }

            if (!other->isValid()) {
                qDebug() << "MultiSplitterLayout::updateAnchorsFromTo: anchor is now invalid."
                         << "\n    old=" << oldAnchor
                         << "\n    new=" << newAnchor
                         << "\n    from=" << other->from()
                         << "\n    to=" << other->to()
                         << "\n    other=" << other;
            }
        }
    }
}

void MultiSplitterLayout::clearAnchorsFollowing()
{
    for (Anchor *anchor : qAsConst(m_anchors))
        anchor->setFollowee(nullptr);
}

void MultiSplitterLayout::updateAnchorFollowing(const AnchorGroup &groupBeingRemoved)
{
    clearAnchorsFollowing();

    QHash<Anchor *, int> newPositionsWhenGroupRemoved;

    for (Anchor *anchor : qAsConst(m_anchors)) {
        if (anchor->isStatic())
            continue;

        if (anchor->onlyHasPlaceholderItems(Anchor::Side2)) {
            Anchor *toFollow = anchor->findNearestAnchorWithItems(Anchor::Side2);
            if (toFollow->followee() != anchor) {
                if (!toFollow->isStatic() && groupBeingRemoved.containsAnchor(anchor, Anchor::Side1)) {
                    // A group is being removed, instead of simply shifting the left/top anchor all the way, let's make it use half the space
                    if (toFollow->onlyHasPlaceholderItems(Anchor::Side1)) { // Means it can move!
                        const int delta = toFollow->position() - anchor->position() - anchor->thickness();
                        const int halfDelta = int(delta / 2.0);
                        if (halfDelta > 0) {
                            newPositionsWhenGroupRemoved.insert(toFollow, toFollow->position() - halfDelta);
                        }
                    }
                }

                anchor->setFollowee(toFollow);
            }
        } else if (anchor->onlyHasPlaceholderItems(Anchor::Side1)) {
            Anchor *toFollow = anchor->findNearestAnchorWithItems(Anchor::Side1);
            if (toFollow->followee() != anchor) {

                if (!toFollow->isStatic() && groupBeingRemoved.containsAnchor(anchor, Anchor::Side2)) {
                    // A group is being removed, instead of simply shifting the right/bottom anchor all the way, let's make it use half the space
                    if (toFollow->onlyHasPlaceholderItems(Anchor::Side2)) { // Means it can move!
                        const int delta = anchor->position() - toFollow->position() - toFollow->thickness();
                        const int halfDelta = int(delta / 2.0);
                        if (halfDelta > 0) {
                            newPositionsWhenGroupRemoved.insert(toFollow, toFollow->position() + halfDelta);
                        }
                    }
                }

                anchor->setFollowee(toFollow);
            }
        }
    }


    for (auto it = newPositionsWhenGroupRemoved.begin(), end = newPositionsWhenGroupRemoved.end(); it != end; ++it) {
        Anchor *anchorToShift = it.key();
        const int newPosition = it.value();
        const Anchor::Side sideToShiftTo = newPosition < anchorToShift->position() ? Anchor::Side1
                                                                                   : Anchor::Side2;
        bool doShift = true;
        for (Anchor *follower : anchorToShift->followers()) {
            if (follower->hasNonPlaceholderItems(sideToShiftTo) && !groupBeingRemoved.containsAnchor(follower, sideToShiftTo)) {
                doShift = false;
                break;
            }
        }

        if (doShift && !anchorToShift->isFollowing())
            anchorToShift->setPosition(newPosition);
    }

    updateSizeConstraints();
    ensureAnchorsBounded();
}

QHash<Anchor*, Anchor*> MultiSplitterLayout::anchorsShouldFollow() const
{
    QHash<Anchor*, Anchor*> followers;

    for (Anchor *anchor : m_anchors) {
        if (anchor->isStatic())
            continue;

        if (anchor->onlyHasPlaceholderItems(Anchor::Side2)) {
            Anchor *toFollow = anchor->findNearestAnchorWithItems(Anchor::Side2);
            if (followers.value(toFollow) != anchor)
                followers.insert(anchor, toFollow);
        } else if (anchor->onlyHasPlaceholderItems(Anchor::Side1)) {
            Anchor *toFollow = anchor->findNearestAnchorWithItems(Anchor::Side1);
            if (followers.value(toFollow) != anchor)
                followers.insert(anchor, toFollow);
        }
    }

    return followers;
}

void MultiSplitterLayout::insertAnchor(Anchor *anchor)
{
    m_anchors.append(anchor);
}

const ItemList MultiSplitterLayout::items() const
{
    return m_items;
}

bool MultiSplitterLayout::eventFilter(QObject *o, QEvent *e)
{
    if (m_inDestructor || e->spontaneous() || !m_multiSplitter)
        return false;

    if (!m_multiSplitter->isVisible()) {
        // The whole MultiSplitter isn't visible, don't bother. It probably even is being hidden by ~QMainWindow().
        return false;
    }

    QWidget *w = qobject_cast<QWidget*>(o);
    if (!w || !w->testAttribute(Qt::WA_WState_ExplicitShowHide)) {
        // We only care about explicit show/hide by the developer
        return false;
    }

    return false;
}

bool MultiSplitterLayout::deserialize(const LayoutSaver::MultiSplitterLayout &msl)
{
    clear(true);

    ItemList items;
    items.reserve(msl.items.size());
    for (const auto &i : qAsConst(msl.items)) {
        Item *item = Item::deserialize(i, this);
        items.push_back(item);
    }

    m_items = items; // Set the items, so Anchor::deserialize() can set the side1 and side2 items

    for (const auto &a : qAsConst(msl.anchors)) {
        Anchor *anchor = Anchor::deserialize(a, this); // They auto-register into m_anchors
        if (!anchor)
            return false;

        if (anchor->type() == Anchor::Type_LeftStatic) {
            Q_ASSERT(!m_leftAnchor);
            m_leftAnchor = anchor;
        } else if (anchor->type() == Anchor::Type_TopStatic) {
            Q_ASSERT(!m_topAnchor);
            m_topAnchor = anchor;
        } else if (anchor->type() == Anchor::Type_RightStatic) {
            Q_ASSERT(!m_rightAnchor);
            m_rightAnchor = anchor;
        } else if (anchor->type() == Anchor::Type_BottomStatic) {
            Q_ASSERT(!m_bottomAnchor);
            m_bottomAnchor = anchor;
        }
    }

    m_staticAnchorGroup.left = m_leftAnchor;
    m_staticAnchorGroup.top = m_topAnchor;
    m_staticAnchorGroup.right = m_rightAnchor;
    m_staticAnchorGroup.bottom = m_bottomAnchor;

    m_items.clear(); // Now properly set the items, which installs needed event filters, etc.
    addItems_internal(items, false, false); // Add the items only after we have the static anchors set

    for (Anchor *anchor : qAsConst(m_anchors)) {
        int indexFrom = anchor->property("indexFrom").toInt();
        int indexTo = anchor->property("indexTo").toInt();
        int indexFolowee = anchor->property("indexFolowee").toInt();
        anchor->setProperty("indexFrom", QVariant());
        anchor->setProperty("indexTo", QVariant());
        anchor->setProperty("indexFolowee", QVariant());

        anchor->setFrom(m_anchors.at(indexFrom));
        anchor->setTo(m_anchors.at(indexTo));
        if (indexFolowee != -1)
            anchor->setFollowee(m_anchors.at(indexFolowee));
    }

    m_size = msl.size;
    m_minSize = msl.minSize;

    // Now that the anchors were created we can add them to the items
    for (Item *item : qAsConst(m_items)) {
        const int leftIndex = item->property("leftIndex").toInt();
        const int topIndex = item->property("topIndex").toInt();
        const int rightIndex = item->property("rightIndex").toInt();
        const int bottomIndex = item->property("bottomIndex").toInt();

        AnchorGroup &group = item->anchorGroup();
        group.left = m_anchors.at(leftIndex);
        group.top = m_anchors.at(topIndex);
        group.right = m_anchors.at(rightIndex);
        group.bottom = m_anchors.at(bottomIndex);

        // Clear helper properties
        item->setProperty("leftIndex", QVariant());
        item->setProperty("topIndex", QVariant());
        item->setProperty("rightIndex", QVariant());
        item->setProperty("bottomIndex", QVariant());
    }

    if (!m_items.isEmpty())
        Q_EMIT widgetCountChanged(m_items.size());


    // The main window that we're restoring can have more stuff now (other-toolbars etc), so by
    // having restored its geometry it can mean our dockwidget layout is now different, so update
    // its content size if needed
    Q_EMIT minimumSizeChanged(m_minSize);

    if (m_size != multiSplitter()->size()) {
        setSize(multiSplitter()->size());
    }

    return true;
}

LayoutSaver::MultiSplitterLayout MultiSplitterLayout::serialize() const
{
    LayoutSaver::MultiSplitterLayout l;

    l.size = size();
    l.minSize = minimumSize();

    for (Item *item : m_items)
        l.items.push_back(item->serialize());

    for (Anchor *anchor : m_anchors)
        l.anchors.push_back(anchor->serialize());

    return l;
}
