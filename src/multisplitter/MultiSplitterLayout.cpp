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

#include "MultiSplitterLayout_p.h"
#include "Logging_p.h"
#include "MultiSplitterWidget_p.h"
#include "Frame_p.h"
#include "FloatingWindow_p.h"
#include "DockWidget.h"
#include "LastPosition_p.h"
#include "SeparatorWidget_p.h"
#include "DockRegistry_p.h"

#include <QPushButton>
#include <QEvent>
#include <QtMath>

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

MultiSplitterLayout::MultiSplitterLayout(MultiSplitterWidget *parent)
    : QObject(parent)
    , m_multiSplitter(parent)
    , m_leftAnchor(new Anchor(Qt::Vertical, this, Anchor::Type_LeftStatic))
    , m_topAnchor(new Anchor(Qt::Horizontal, this, Anchor::Type_TopStatic))
    , m_rightAnchor(new Anchor(Qt::Vertical, this, Anchor::Type_RightStatic))
    , m_bottomAnchor(new Anchor(Qt::Horizontal, this, Anchor::Type_BottomStatic))
    , m_staticAnchorGroup(this)
{
    Q_ASSERT(parent);
    KDDockWidgets::setLoggingFilterRules();

    DockRegistry::self()->registerLayout(this);

    setContentsSize(parent->size());

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

MultiSplitterWidget *MultiSplitterLayout::multiSplitter() const
{
    return m_multiSplitter;
}

bool MultiSplitterLayout::validateInputs(QWidget *widget,
                                         Location location,
                                         const Frame *relativeToFrame, AddingOption option) const
{
    if (!widget) {
        qWarning() << Q_FUNC_INFO << "Widget is null";
        Q_ASSERT(false);
        return false;
    }

    const bool isDockWidget = qobject_cast<DockWidget*>(widget);
    const bool isStartHidden = option & AddingOption_StartHidden;

    if (!qobject_cast<Frame*>(widget) && !qobject_cast<MultiSplitterWidget*>(widget) && !isDockWidget) {
        qWarning() << "Unknown widget type" << widget;
        Q_ASSERT(false);
        return false;
    }

    if (isDockWidget != isStartHidden) {
        qWarning() << "Wrong parameters" << isDockWidget << isStartHidden;
        Q_ASSERT(false);
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
        Q_ASSERT(false);
        return false;
    }

    const bool relativeToThis = relativeToFrame == nullptr;

    Item *relativeToItem = itemForFrame(relativeToFrame);
    if (!relativeToThis && !contains(relativeToItem)) {
        qWarning() << "MultiSplitterLayout::addWidget: Doesn't contain relativeTo:" << relativeToItem;
        return false;
    }

    return true;
}

void MultiSplitterLayout::addWidget(QWidget *w, Location location, Frame *relativeToWidget, AddingOption option)
{
    auto frame = qobject_cast<Frame*>(w);
    qCDebug(addwidget) << Q_FUNC_INFO << w
                       << "; location=" << locationStr(location)
                       << "; relativeTo=" << relativeToWidget
                       << "; contentSize=" << contentsSize()
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

    if (option & AddingOption_StartHidden) {
        addAsPlaceholder(qobject_cast<DockWidget*>(w), location, relativeToItem);
        return;
    }

    const Length lfd = lengthForDrop(w, location, relativeToItem);
    if (lfd.isNull()) {
        Qt::Orientation orientation = anchorOrientationForLocation(location);
        const int required = widgetMinLength(w, orientation);
        const int totalRequired = required + length(orientation)
                + (isEmpty() ? 0 : Anchor::thickness(/*static*/ false))
                + extraUselessSpace(orientation);
        qCDebug(sizing) << "\n    m_contentSize=" << m_contentSize
                        << "\n    required=" << required
                        << "\n    this length=" << length(orientation)
                        << "\n    availableLengthForDrop()=" << availableLengthForDrop(location, relativeToItem).length();
        setContentLength(orientation, totalRequired);
        qCDebug(sizing) << "now=    m_contentSize=" << m_contentSize
                        << "\n      totalRequired=" << totalRequired
                        << "\n availableLengthForDrop()=" << availableLengthForDrop(location, relativeToItem).length();
    }

    Anchor *newAnchor = nullptr;
    const QRect dropRect = rectForDrop(w, location, relativeToItem);

    if (dropRect.size().isNull() || dropRect.x() < 0 || dropRect.y() < 0) {
        qWarning() << Q_FUNC_INFO << "Invalid drop rect" << dropRect
                   << "\n    size=" << m_multiSplitter->size() << "; contentsSize="<< m_contentSize
                   << "\n    location=" << location
                   << "\n    window=" << m_multiSplitter->window()
                   << "\n    this=" << this
                   << "\n    availableHeight=" << availableLengthForOrientation(Qt::Horizontal)
                   << "\n    availableWidth=" << availableLengthForOrientation(Qt::Vertical)
                   << "\n    widget.minSize=" << widgetMinLength(w, anchorOrientationForLocation(location));
        return;
    }

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
            delta1 = originalExistingAnchorPos - posForExistingAnchor;
            delta2 = posForNewAnchor - posForExistingAnchor;
            break;
        case Location_OnRight:
        case Location_OnBottom:
            direction1Anchor = newAnchor;
            direction2Anchor = existingAnchor;
            delta1 = posForExistingAnchor - posForNewAnchor;
            delta2 = posForExistingAnchor - originalExistingAnchorPos;
            break;
        case Location_None:
            qWarning() << Q_FUNC_INFO << "Location can't be none";
            Q_ASSERT(false);
            return;
        }

        qCDebug(sizing) << "posForNewAnchor=" << posForNewAnchor
                        << "; posForExistingAnchor=" << posForExistingAnchor
                        << "; delta1=" << delta1
                        << "; delta2=" << delta2;

        newAnchor->setPosition(posForNewAnchor);

        if (posForExistingAnchor != originalExistingAnchorPos) {
            if (existingAnchor->isStatic()) {
                qWarning() << "Trying to move static anchor from" << originalExistingAnchorPos << "to"
                         << posForExistingAnchor << "; location=" << location
                         << "; dropRect=" << dropRect
                         << "; existingAnchor=" << existingAnchor
                         << "; size=" << m_contentSize
                         << "; Qt::WA_PendingResizeEvent=" << m_multiSplitter->testAttribute(Qt::WA_PendingResizeEvent)
                         << "; Qt::WA_WState_Created=" << m_multiSplitter->testAttribute(Qt::WA_WState_Created);
                Q_ASSERT(false);
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

        /*qDebug() << "Delta1=" << delta1 << "; delta2=" << delta2
                 << "; posForNewAnchor=" << posForNewAnchor
                 << "; w=" << widget->width()
                 << "; direction1Anchor=" << direction1Anchor
                 << "; direction2Anchor=" << direction2Anchor;*/
    }

    auto sourceMultiSplitterWidget = qobject_cast<MultiSplitterWidget *>(w);
    auto sourceMultiSplitter = sourceMultiSplitterWidget ? sourceMultiSplitterWidget->multiSplitterLayout()
                                                         : nullptr;

    if (sourceMultiSplitter) {
        auto items = sourceMultiSplitter->items();
        targetAnchorGroup.addItem(sourceMultiSplitter);
        addItems_internal(items);
    } else {
        Q_ASSERT(frame);
        auto item = new Item(frame, this);
        targetAnchorGroup.addItem(item);
        addItems_internal(ItemList{ item });
    }

    updateAnchorFollowing();
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

void MultiSplitterLayout::addAsPlaceholder(DockWidget *dockWidget, Location location, Item *relativeTo)
{
    if (!dockWidget) {
        qWarning() << Q_FUNC_INFO << "null dockwidget";
        return;
    }

    dockWidget->setParent(nullptr);

    auto result = createTargetAnchorGroup(location, relativeTo);
    AnchorGroup targetAnchorGroup = result.first;

    auto frame = new Frame(m_multiSplitter);
    auto item = new Item(frame, this);

    targetAnchorGroup.addItem(item);
    addItems_internal(ItemList{ item }, false);

    dockWidget->addPlaceholderItem(item);
    delete frame;

    updateAnchorFollowing();
    Q_ASSERT(!dockWidget->isVisible());
}

void MultiSplitterLayout::setExtraUselessSpace(QSize sz)
{
    qCDebug(sizing) << Q_FUNC_INFO << sz;
    m_extraUselessSpace = sz;
}

int MultiSplitterLayout::extraUselessSpace(Qt::Orientation o) const
{
    return o == Qt::Vertical ? m_extraUselessSpace.width()
                             : m_extraUselessSpace.height();
}

static Anchor::List removeSmallestPath(QVector<Anchor::List> &paths)
{
    // Removes and returns the smallest list
    Anchor::List smallestPath;
    int indexOfSmallest = 0;
    for (int i = 0, end = paths.size(); i < end; ++i) {
        const Anchor::List path = paths.at(i);
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
    qCDebug(sizing) << Q_FUNC_INFO << " START delta=" << delta
                    << "; fromAnchor=" << fromAnchor
                    << "; isStatic?" << fromAnchor->isStatic()
                    << "; direction=" << direction
                    << "; pos=" << fromAnchor->position();

    Q_ASSERT(delta >= 0);
    if (delta == 0 || fromAnchor->isStatic())
        return;

    QVector<Anchor::List> paths;
    collectPaths(paths, fromAnchor, direction);

    qCDebug(sizing) << Q_FUNC_INFO << "Got" << paths.size() << "paths";
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

    qCDebug(sizing) << Q_FUNC_INFO << "END";
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

void MultiSplitterLayout::addMultiSplitter(MultiSplitterWidget *sourceMultiSplitter,
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

int MultiSplitterLayout::length(Qt::Orientation orientation) const
{
    return KDDockWidgets::widgetLength(m_multiSplitter, orientation);
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
            const int max = contentsLength(anchor->orientation()) - 1;
            return {max, max};
        }
    }

    const int minSide1Length = anchor->cumulativeMinLength(Anchor::Side1);
    const int minSide2Length = anchor->cumulativeMinLength(Anchor::Side2);
    const int length = anchor->isVertical() ? contentsWidth() : contentsHeight();

    return { minSide1Length - anchor->thickness(), length - minSide2Length };
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
        Q_ASSERT(false);
        return result;
    case KDDockWidgets::Location_OnLeft:
        anchor = anchors.left;
        thisLength = contentsWidth();
        break;
    case KDDockWidgets::Location_OnTop:
        anchor = anchors.top;
        thisLength = contentsHeight();
        break;
    case KDDockWidgets::Location_OnRight:
        anchor = anchors.right;
        thisLength = contentsWidth();
        break;
    case KDDockWidgets::Location_OnBottom:
        anchor = anchors.bottom;
        thisLength = contentsHeight();
        break;
    }

    const int minForAlreadyOccupied1 = anchor->cumulativeMinLength(Anchor::Side1) - anchor->thickness(); // TODO: Check if this is correct, we're discounting the anchor twice
    const int minForAlreadyOccupied2 = anchor->cumulativeMinLength(Anchor::Side2) - anchor->thickness();

    const int side1AvailableLength = anchor->position() - minForAlreadyOccupied1;
    const int side2AvailableLength = thisLength - (anchor->position() + anchor->thickness()) - minForAlreadyOccupied2;

    const bool needsNewAnchor = !isEmpty(); // If a new anchor is needed then we need space for the drag handle and such.
    const int newAnchorThickness = needsNewAnchor ? Anchor::thickness(/*static=*/false) : 0;

    // This useless space doesn't belong to side1 or side2 specifically. So account for it separately.
    const int unusableSpace = newAnchorThickness + extraUselessSpace(anchorOrientationForLocation(location));

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
                    << "; unusableSpace=" << unusableSpace
                    << "; extraUseless=" << m_extraUselessSpace;

    //Q_ASSERT(result.side1Length <= side1AvailableLength); // TODO, uncomment this, maybe
    //Q_ASSERT(result.side2Length <= side2AvailableLength);
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
MultiSplitterLayout::Length MultiSplitterLayout::lengthForDrop(const QWidget *widget, Location location,
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
                        << "; m_contentSize=" << m_contentSize;
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
                            contentsWidth() - widgetLength - staticAnchorThickness), relativeToRect.y(), widgetLength, relativeToRect.height());
        break;
    case Location_OnBottom:
        result = QRect(relativeToRect.x(), qMin(relativeToRect.bottom() + 1 - side1Length + newAnchorThickness,
                                                contentsHeight() - widgetLength - staticAnchorThickness),
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

QRect MultiSplitterLayout::rectForDrop(const QWidget *widgetBeingDropped, Location location,
                                       const Item *relativeTo) const
{
    Q_ASSERT(widgetBeingDropped);
    Length lfd = lengthForDrop(widgetBeingDropped, location, relativeTo);
    if (lfd.isNull())  {
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

    AnchorGroup group = relativeToThis ? staticAnchorGroup() : relativeTo->anchorGroup();

    // This function is split in two just so we can unit-test the math in the second one, which is more involved
    QRect result = rectForDrop(lfd, location, relativeToRect);

    // lfd has the length that the widget should have, and we're guaranteed to have +5 (Anchor::thicknes) pixels
    // For the new anchor, but in rectForDrop() we don't know if that extra 5px fits on the left side or on the right,
    // so now do an adjustment and put the rect within correct bounds, so all the min sizes to side1 and to side2 are respected
    const Qt::Orientation orientation = orientationForLocation(location);
    Anchor *anchor1 = group.anchorAtSide(Anchor::Side1, orientation);
    Anchor *anchor2 = group.anchorAtSide(Anchor::Side2, orientation);
    const int bound1 = boundPositionForAnchor(anchor1, Anchor::Side1);
    const int bound2 = boundPositionForAnchor(anchor2, Anchor::Side2);

    if (orientation == Qt::Vertical) {
        if (result.x() < bound1 + anchor1->thickness())
            result.moveLeft(bound1 + anchor1->thickness());
        if (result.right() >= bound2)
            result.moveRight(bound2 - 1);
        Q_ASSERT(result.x() >= bound1 + anchor1->thickness());
    } else {
        if (result.y() < bound1 + anchor1->thickness())
            result.moveTop(bound1 + anchor1->thickness());
        if (result.bottom() >= bound2)
            result.moveBottom(bound2 - 1);
        Q_ASSERT(result.y() >= bound1 + anchor1->thickness());
    }

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
    qDebug() << Q_FUNC_INFO << "m_contentsSize=" << m_contentSize
             << "; minimumSize=" << m_multiSplitter->minimumSize();

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
        qDebug() << "    " << anchor
                 << "; separatorWidget=" << anchor->separatorWidget()
                 << "; side1=" << side1Widgets << anchor->debug_side1ItemNames()
                 << "; side2=" << side2Widgets << anchor->debug_side2ItemNames()
                 << "; pos=" << anchor->position()
                 << "; sepWidget.pos=" << (anchor->isVertical() ? anchor->separatorWidget()->x()
                                                                : anchor->separatorWidget()->y())
                 << "; geo=" << anchor->geometry()
                 << "; sep.geo=" << anchor->separatorWidget()->geometry()
                 << "; bounds=" << bounds
                 << "; orientation=" << anchor->orientation()
                 << "; isFollowing=" << anchor->isFollowing()
                 << "; followee=" << anchor->followee()
                 << "; from=" << ((void*)anchor->from())
                 << "; to=" << ((void*)anchor->to());
    }

    qDebug() << "Num Frame:" << Frame::dbg_numFrames();
    qDebug() << "Num FloatingWindow:" << FloatingWindow::dbg_numFrames();
}

void MultiSplitterLayout::positionStaticAnchors()
{
    qCDebug(sizing) << Q_FUNC_INFO;
    m_leftAnchor->setPosition(0);
    m_topAnchor->setPosition(0);
    m_bottomAnchor->setPosition(contentsHeight() - 1);
    m_rightAnchor->setPosition(contentsWidth() - 1);
}

void MultiSplitterLayout::redistributeSpace(QSize oldSize, QSize newSize)
{
    positionStaticAnchors();
    if (oldSize == newSize || !oldSize.isValid() || !newSize.isValid())
        return;

    qCDebug(sizing) << "MultiSplitterLayout::redistributeSpace old=" << oldSize << "; new=" << newSize;

    redistributeSpace_recursive(m_leftAnchor, 0);
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
            const int newPosition = int(nextAnchor->positionPercentage() * contentsLength(nextAnchor->orientation()));

            // But don't let the anchor go out of bounds, it must respect its widgets min sizes
            auto bounds = boundPositionsForAnchor(nextAnchor);

            // For the bounding, use Anchor::minPosition, as we're not making the anchors on the left/top shift, which boundsPositionsForAnchor() assumes.
            const int newPositionBounded = qBound(minAnchorPos, newPosition, bounds.second);

            qCDebug(sizing) << Q_FUNC_INFO << nextAnchor << "FOO ; bounds.first=" << bounds.first
                            << "; newPosition=" << newPosition
                            << "; bounds.first=" << bounds.first
                            << "; bounds.second=" << bounds.second
                            << "; newPositionBounded=" << newPositionBounded
                            << "; oldPosition=" << nextAnchor->position()
                            << "; contentSize=" << m_contentSize
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

    setMinimumSize(QSize(minW, minH));
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
    Q_ASSERT(checkSanity(AnchorSanity_Normal));
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


    if (!checkSanity(AnchorSanity_Normal)) {
        qWarning() << "MultiSplitterLayout::newAnchor no sanity!";
        Q_ASSERT(false);
    }
    updateAnchorsFromTo(donor, newAnchor);

    qCDebug(::anchors()) << newAnchor->hasNonPlaceholderItems(Anchor::Side1)
                         << newAnchor->hasNonPlaceholderItems(Anchor::Side2)
                         << newAnchor->side1Items() << newAnchor->side2Items()
                         << "; donor" << donor
                         << "; follows=" << newAnchor->followee();
    return newAnchor;
}

void MultiSplitterLayout::setDoSanityChecks(bool doit)
{
    if (doit != m_doSanityChecks)
        m_doSanityChecks = doit;
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

Frame::List MultiSplitterLayout::framesFrom(QWidget *frameOrMultiSplitter) const
{
    if (auto frame = qobject_cast<Frame*>(frameOrMultiSplitter))
        return { frame };

    if (auto msw = qobject_cast<MultiSplitterWidget*>(frameOrMultiSplitter))
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

QVector<DockWidget *> MultiSplitterLayout::dockWidgets() const
{
    DockWidget::List result;
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
        Q_ASSERT(false);
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
    if (!m_doSanityChecks || m_inCtor)
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

        if (!anchor->isFollowing() &&  anchor->geometry() != anchor->separatorWidget()->geometry()) {
            qWarning() << Q_FUNC_INFO << anchor << anchor->separatorWidget()
                       << "Inconsistent anchor geometry" << anchor->geometry() << "; " << anchor->separatorWidget()->geometry();
            return false;
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
                               << "Intersects anchor" << a << "with rect" << a->geometry();
                    return false;
                }
            }
        }
    }

    if (options & AnchorSanity_WidgetGeometry) {
        for (Item *item: items()) {

            if (!item->anchorGroup().isValid()) {
                qWarning() << Q_FUNC_INFO << "Invalid item group for item" << item->anchorGroup();
                return false;
            }

            if (!item->isPlaceholder() && item->anchorGroup().itemSize() != item->size()) {
                qWarning() << Q_FUNC_INFO << "Invaild item size" << item->size() << item->anchorGroup().itemSize();
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
                dumpDebug();
                qWarning() << "MultiSplitterLayout::checkSanity: Widget has width=" << item->width()
                           << "but minimum is" << minWidth
                           << item;
                return false;
            }

            if (item->height() < minHeight) {
                dumpDebug();
                qWarning() << "MultiSplitterLayout::checkSanity: Widget has height=" << item->height()
                           << "but minimum is" << minHeight
                           << item;
                return false;
            }
        }
    }

/* TODO: uncomment when all tests pass
    if (m_topAnchor->position() != 0 || m_leftAnchor->position() != 0) {
        qWarning() << Q_FUNC_INFO << "Invalid top or left anchor position"
                   << m_topAnchor->position() << m_leftAnchor->position();
        return false;
    }

    if (m_rightAnchor->position() != m_contentSize.width() - 1 || m_bottomAnchor->position() != m_contentSize.height() - 1) {
        qWarning() << Q_FUNC_INFO << "Invalid right or bottom anchor position"
                   << m_rightAnchor->position() << m_bottomAnchor->position()
                   << "; m_contentsSize=" << m_contentSize;
        return false;
    }
*/
    return true;
}

void MultiSplitterLayout::ensureHasAvailableSize(QSize needed)
{
    const QSize availableSize = this->availableSize();

    qCDebug(placeholder) << Q_FUNC_INFO << "; needed=" << needed << availableSize;

    const int deltaWidth = needed.width() > availableSize.width() ? (needed.width() - availableSize.width())
                                                                  : 0;

    const int deltaHeight = needed.height() > availableSize.height() ? (needed.height() - availableSize.height())
                                                                     : 0;

    const QSize newSize = contentsSize() + QSize(deltaWidth, deltaHeight);
    setContentsSize(newSize);
}

void MultiSplitterLayout::restorePlaceholder(Item *item)
{
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
    updateSizeConstraints();

    Anchor::List anchorsFollowing = anchorGroup.anchorsFollowingInwards();
    if (anchorsFollowing.isEmpty()) {
        // There's no separator to move, it means it's a static anchor group (layout is empty, so the anchors
        // are the actual borders of the window
        // dumpDebug();
        Q_ASSERT(anchorGroup.isStaticOrFollowsStatic());
        anchorGroup.updateItemSizes();
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

    item->beginBlockPropagateGeo();
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
        /*if (!anchorGroup.hasAvailableSizeFor(newSize)) {
                qWarning() << "There's not enough space: bound2=" << boundPosition2
                           << "; bound1=" << boundPosition1 << "; side1Anchor.thickness=" << side1Anchor->thickness()
                           << "; newSize=" << newSize
                           << "; newspace=" << boundPosition2 - boundPosition1 - side1Anchor->thickness()
                           << "; available_old=" << availableSize
                           << "; available_new=" << this->availableSize()
                           << "; anchors=" << side1Anchor << side2Anchor
                           << "; oldPos1=" << oldPosition1
                           << "; oldPos2=" << oldPosition2
                           << "; static=" << side1Anchor->isStatic() << side2Anchor->isStatic()
                           << "; contentsSize=" << m_contentSize;
                Q_ASSERT(false);
                return;
            }*/

        const int newLength = anchorFollowingInwards->isVertical() ? newSize.width() : newSize.height();
        // Let's try that each anchor contributes 50%, so that the widget appears centered
        const int suggestedLength1 = qMin(newLength, qCeil(newLength / 2) + side1Anchor->thickness() + 1);
        const int maxPos1 = boundPosition2 - newLength - side1Anchor->thickness();
        const int newPosition1 = qMin(qMax(boundPosition1, oldPosition1 - suggestedLength1), maxPos1); // Honour the bound
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
                             << "; contentsSize=" << m_contentSize
                             << "; widgetMinSize=" << widgetMinSize
                             << "; available_old=" << availableSize
                             << "; available_new=" << availableLengthForOrientation(orientation)
                             << "; item.size=" << item->size();

        // We don't want item to resize the anchors while setting newPosition1, we already calculated it
        side1Anchor->setPosition(newPosition1);
        side2Anchor->setPosition(newPosition2);
    }
    item->endBlockPropagateGeo();

    updateAnchorFollowing();
}

void MultiSplitterLayout::unrefOldPlaceholders(const Frame::List &framesBeingAdded) const
{
    for (Frame *frame : framesBeingAdded) {
        for (DockWidget *dw : frame->dockWidgets()) {
            if (Item *existingItem = dw->lastPosition()->layoutItem()) {
                if (contains(existingItem)) { // We're only interested in placeholders from this layout
                    dw->lastPosition()->removePlaceholders(this);
                }
            }
        }
    }
}

void MultiSplitterLayout::setContentsSize(QSize size)
{
    if (size != m_contentSize) {
        QSize oldSize = m_contentSize;

        if (size.width() < m_minSize.width() || size.height() < m_minSize.height()) {
            qWarning() << Q_FUNC_INFO << "new size is smaller than min size" << size << m_minSize;
        }

#if defined(DOCKS_DEVELOPER_MODE)
        if (!m_inCtor && false) { // TODO Uncomment when it passes
            QSize minSizeCalculated = QSize(availableLengthForOrientation(Qt::Vertical), availableLengthForOrientation(Qt::Horizontal));
            if (size.width() < minSizeCalculated.width() || size.height() < minSizeCalculated.height()) {
                qWarning() << Q_FUNC_INFO << "new size is smaller than min size calculated" << size << minSizeCalculated;
            }
        }
#endif

        m_contentSize = size;
        Q_EMIT contentsSizeChanged(size);
        redistributeSpace(oldSize, size);
    }
}

void MultiSplitterLayout::setContentLength(Qt::Orientation o, int value)
{
    if (o == Qt::Vertical) {
        // Setting the width
        setContentsSize({value, m_contentSize.height()});
    } else {
        // Setting the height
        setContentsSize({m_contentSize.width(), value});
    }
}

int MultiSplitterLayout::contentsLength(Qt::Orientation o) const
{
    return o == Qt::Vertical ? contentsWidth()
                             : contentsHeight();
}

void MultiSplitterLayout::setMinimumSize(QSize sz)
{
    if (sz != m_minSize) {
        m_minSize = sz;
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

                Q_ASSERT(false);
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
                            toFollow->setPosition(toFollow->position() - halfDelta);
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
                            toFollow->setPosition(toFollow->position() + halfDelta);
                        }
                    }
                }

                anchor->setFollowee(toFollow);
            }
        }
    }
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

bool MultiSplitterLayout::fillFromDataStream(QDataStream &ds)
{
    clear(true);

    QString marker;
    QSize minSize;
    QSize contentsSize;
    int numItems;
    int numAnchors;

    ds >> marker;
    if (marker != s_magicMarker) {
        qWarning() << Q_FUNC_INFO << "corrupted stream";
        return false;
    }

    ds >> contentsSize;
    ds >> minSize;
    ds >> numItems;
    ds >> numAnchors;

    ItemList items;
    Q_ASSERT(numItems >= 0);
    items.reserve(numItems);
    for (int i = 0; i < numItems; ++i) {
        Item *item = Item::createFromDataStream(ds, this);
        items.push_back(item);
    }

    m_items = items; // Set the items, so Anchor::createFromDataStream() can set the side1 and side2 items

    Q_ASSERT(numAnchors >= 0);
    for (int i = 0; i < numAnchors; ++i) {
        Anchor *anchor = Anchor::createFromDataStream(ds, this); // They auto-register into m_anchors
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

    m_contentSize = contentsSize;
    m_minSize = minSize;

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

    return true;
}

QDataStream &KDDockWidgets::operator<<(QDataStream &ds, MultiSplitterLayout *l)
{
    const ItemList items = l->items();
    const Anchor::List anchors = l->anchors();

    ds << MultiSplitterLayout::s_magicMarker;
    ds << l->contentsSize();
    ds << l->minimumSize();
    ds << items.size();
    ds << anchors.size();

    for (Item *item : items) {
        ds << item;
    }

    for (Anchor *anchor : anchors) {
        ds << anchor;
    }

    return ds;
}
