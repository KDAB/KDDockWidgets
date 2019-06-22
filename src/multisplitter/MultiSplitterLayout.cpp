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

#include <QPushButton>
#include <QEvent>
#include <QResizeEvent>

#define INDICATOR_MINIMUM_LENGTH 100

using namespace KDDockWidgets;

static Qt::Orientation anchorOrientationForLocation(Location l)
{
    return (l == Location_OnLeft || l == Location_OnRight) ? Qt::Vertical
                                                           : Qt::Horizontal;
}

MultiSplitterLayout::MultiSplitterLayout(QWidget *parent)
    : QObject(parent)
    , m_leftAnchor(new Anchor(Qt::Vertical, this, Anchor::Type_LeftStatic))
    , m_topAnchor(new Anchor(Qt::Horizontal, this, Anchor::Type_TopStatic))
    , m_rightAnchor(new Anchor(Qt::Vertical, this, Anchor::Type_RightStatic))
    , m_bottomAnchor(new Anchor(Qt::Horizontal, this, Anchor::Type_BottomStatic))
    , m_staticAnchorGroup(this)
{
    Q_ASSERT(parent);
    KDDockWidgets::setLoggingFilterRules();
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
}

MultiSplitterLayout::~MultiSplitterLayout()
{
    qCDebug(multisplittercreation()) << "~MultiSplitter";
    m_inDestructor = true;
    const auto anchors = m_anchors;
    qDeleteAll(anchors);
}

QWidget *MultiSplitterLayout::parentWidget() const
{
    auto pw = qobject_cast<QWidget*>(parent());
    Q_ASSERT(!(!pw && parent())); // it's either null or a QWidget
    return pw;
}

bool MultiSplitterLayout::validateInputs(QWidget *widget,
                                         Location location,
                                         Item *relativeTo) const
{
    if (!widget) {
        qWarning() << Q_FUNC_INFO << "Widget is null";
        Q_ASSERT(false);
        return false;
    }

    if (!qobject_cast<Frame*>(widget) && !qobject_cast<MultiSplitterWidget*>(widget)) {
        Q_ASSERT(false);
        return false;
    }

    if (relativeTo && relativeTo->frame() == widget) {
        qWarning() << "widget can't be relative to itself";
        return false;
    }

    Item *item = itemForWidget(widget);

    if (contains(item)) {
        qWarning() << "MultiSplitterLayout::addWidget: Already contains" << widget;
        return false;
    }// TODO: check for widget changing parent

    if (location == Location_None) {
        qWarning() << "MultiSplitterLayout::addWidget: not adding to location None";
        Q_ASSERT(false);
        return false;
    }

    const bool relativeToThis = relativeTo == nullptr;
    if (!relativeToThis && !contains(relativeTo)) {
        qWarning() << "MultiSplitterLayout::addWidget: Doesn't contain relativeTo:" << relativeTo;
        return false;
    }

    return true;
}

void MultiSplitterLayout::addWidget(QWidget *w, Location location, QWidget *relativeToWidget)
{
    Item *item = itemForWidget(w);
    if (item) {
        qWarning() << "Item already exists;";
        return;
    }

    auto relativeTo = itemForWidget(relativeToWidget);

    // Make some sanity checks:
    if (!validateInputs(w, location, relativeTo))
        return;

    const Length lfd = lengthForDrop(w, location, relativeTo);
    if (lfd.isNull()) {
        Qt::Orientation orientation = anchorOrientationForLocation(location);
        const int required = widgetMinLength(w, orientation);
        const int totalRequired = required + length(orientation)
                + (isEmpty() ? 0 : Anchor::thickness(/*static*/ false))
                + extraUselessSpace(orientation);
        qCDebug(sizing) << "had size=" << parentWidget()->size()
                        << "\n    m_contentSize=" << m_contentSize
                        << "\n    required=" << required
                        << "\n    this length=" << length(orientation)
                        << "\n    availableLengthForDrop()=" << availableLengthForDrop(location, relativeTo).length();
        setContentLength(orientation, totalRequired);
        qCDebug(sizing) << "now has size= " << parentWidget()->size()
                        << "\n    m_contentSize=" << m_contentSize
                        << "\n    totalRequired=" << totalRequired
                        << "\n availableLengthForDrop()=" << availableLengthForDrop(location, relativeTo).length();
    }

    auto sourceMultiSplitterWidget = qobject_cast<MultiSplitterWidget *>(w);
    auto sourceMultiSplitter = sourceMultiSplitterWidget ? sourceMultiSplitterWidget->multiSplitter()
                                                         : nullptr;
    const bool sourceIsAMultiSplitter = sourceMultiSplitter != nullptr;
    const bool relativeToThis = relativeTo == nullptr;


    AnchorGroup targetAnchorGroup = relativeToThis ? staticAnchorGroup()
                                                   : anchorsForPos(relativeTo->geometry().center());
    Q_ASSERT(targetAnchorGroup.isValid());

    Anchor *newAnchor = nullptr;
    QRect dropRect = rectForDrop(w, location, relativeTo);

    if (dropRect.size().isNull() || dropRect.x() < 0 || dropRect.y() < 0) {
        qWarning() << Q_FUNC_INFO << "Invalid drop rect" << dropRect
                   << "\n    size=" << parentWidget()->size() << m_contentSize
                   << "\n    location=" << location
                   << "\n    window=" << parentWidget()->window()
                   << "\n    this=" << this
                   << "\n    widget.minSize" << widgetMinLength(w, anchorOrientationForLocation(location));
        return;
    }

    if (!sourceIsAMultiSplitter) {
        auto frame = qobject_cast<Frame*>(w);
        Q_ASSERT(frame);
        item = new Item(frame, this);
    }

    if (relativeToThis) {
        if (!isEmpty())
            newAnchor = this->newAnchor(targetAnchorGroup, location);
    } else {
        newAnchor = targetAnchorGroup.createAnchorFrom(location, relativeTo);
        targetAnchorGroup.setAnchor(newAnchor, KDDockWidgets::oppositeLocation(location));
    }

    if (newAnchor) {
        const int anchorThickness = Anchor::thickness(/*static=*/false);
        qCDebug(sizing) << "Drop rect" << dropRect;

        int posForExistingAnchor = 0;
        int posForNewAnchor = 0;
        Anchor *existingAnchor = targetAnchorGroup.anchor(location);
        Anchor *direction1Anchor = nullptr;
        Anchor *direction2Anchor = nullptr;

        switch (location) {
        case Location_OnLeft:
            posForExistingAnchor = dropRect.left() - 1;
            posForNewAnchor = dropRect.right();
            break;
        case Location_OnTop:
            posForExistingAnchor = dropRect.top() - 1;
            posForNewAnchor = dropRect.bottom();
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
                         << "; size=" << parentWidget()->size() << m_contentSize
                         << "; Qt::WA_PendingResizeEvent=" << parentWidget()->testAttribute(Qt::WA_PendingResizeEvent)
                         << "; Qt::WA_WState_Created=" << parentWidget()->testAttribute(Qt::WA_WState_Created);
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

    if (sourceMultiSplitter) {
        auto items = sourceMultiSplitter->items();
        targetAnchorGroup.addItem(sourceMultiSplitter);
        addItems_internal(items);
    } else {
        targetAnchorGroup.addItem(item);
        addItems_internal(ItemList{ item });
    }
}

void MultiSplitterLayout::addItems_internal(const ItemList &items, bool updateConstraints)
{
    m_items << items;
    if (updateConstraints)
        updateSizeConstraints();

    for (auto item : items) {
        item->setLayout(this);
        item->setVisible(true);
        item->frame()->installEventFilter(this);
        Q_EMIT widgetAdded(item);
    }
    Q_EMIT widgetCountChanged(m_items.size());
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

    Anchor::List &currentPath = paths.last();
    currentPath.push_back(fromAnchor);

    const ItemList items = fromAnchor->items(direction);
    for (int i = 0, end = items.size(); i < end; ++i) {
        Anchor *nextAnchor = items[i]->anchor(Anchor::oppositeSide(direction), fromAnchor->orientation());
        if (i > 0) {
            Anchor::List newPath = currentPath;
            paths.push_back(newPath);
        }
        collectPaths(paths, nextAnchor, direction);
    }
}

void MultiSplitterLayout::resizeItem(QWidget *widget, int newSize, Qt::Orientation orientation)
{
    // Used for unit-tests only
    Item *item = itemForWidget(widget);
    Anchor *a = item->anchor(Anchor::Side1, orientation);
    Q_ASSERT(!a->isStatic());
    const int widgLength = item->length(orientation);
    const int delta = newSize - widgLength;
    qCDebug(::anchors) << Q_FUNC_INFO << "Old position:" << a->pos() << "; old w.geo=" << item->geometry();
    a->setPosition(a->position() + delta);
    qCDebug(::anchors) << Q_FUNC_INFO << "New position:" << a->pos() << "; new w.geo=" << item->geometry();
}

void MultiSplitterLayout::addMultiSplitter(MultiSplitterWidget *sourceMultiSplitter,
                                     Location location,
                                     QWidget *relativeTo)
{
    addWidget(sourceMultiSplitter, location, relativeTo);
}

void MultiSplitterLayout::removeItem(Item *item)
{
    if (!item || m_inDestructor || !m_items.contains(item))
        return;

    item->frame()->removeEventFilter(this);
    AnchorGroup anchorGroup = item->anchorGroup();
    anchorGroup.removeItem(item);
    m_items.removeOne(item);

    Q_EMIT widgetRemoved(item);
    Q_EMIT widgetCountChanged(m_items.size());
}

bool MultiSplitterLayout::contains(Item *item) const
{
    return m_items.contains(item);
}

Item *MultiSplitterLayout::itemAt(QPoint p) const
{
    for (Item *item : m_items) {
        if (item->geometry().contains(p))
            return item;
    }

    return nullptr;
}

void MultiSplitterLayout::clear()
{
    qDeleteAll(m_items);
    m_items.clear();
    Q_EMIT widgetCountChanged(0);

    for (Anchor *anchor : qAsConst(m_anchors)) {
        if (!anchor->isStatic())
            anchor->deleteLater();
    }

    m_anchors.clear();
    m_anchors << m_topAnchor << m_bottomAnchor << m_leftAnchor << m_rightAnchor;
}

int MultiSplitterLayout::visibleCount() const
{
    int count = 0;
    for (auto w : m_items)
        if (w->isVisible())
            count++;
    return count;
}

int MultiSplitterLayout::length(Qt::Orientation orientation) const
{
    return KDDockWidgets::widgetLength(parentWidget(), orientation);
}

void MultiSplitterLayout::removeAnchor(Anchor *anchor)
{
    if (!m_inDestructor)
        m_anchors.removeOne(anchor);
}

QPair<int, int> MultiSplitterLayout::boundPositionsForAnchor(Anchor *anchor) const
{
    if (anchor->isStatic()) {
        // Doesn't happen
        qWarning() << "MultiSplitterLayout::boundsForAnchor Can't be called with static anchors";
        Q_ASSERT(false);
        return {};
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

QRect MultiSplitterLayout::rectForDrop(const QWidget *widgetBeingDropped, Location location, Item *relativeTo) const
{
    Q_ASSERT(widgetBeingDropped);
    Length lfd = lengthForDrop(widgetBeingDropped, location, relativeTo);
    if (lfd.isNull())  {
        // This is the case with the drop indicators. If there's not enough space let's still
        // draw some indicator drop. The window will resize to accommodate the drop.
        lfd.side1Length = INDICATOR_MINIMUM_LENGTH / 2;
        lfd.side2Length = INDICATOR_MINIMUM_LENGTH - lfd.side1Length;
    }

    QRect result;
    const int newAnchorThickness = isEmpty() ? 0 : Anchor::thickness(/*static=*/false);
    const int lengthForDrop = lfd.length();
    const int side1Length = lfd.side1Length;
    const int staticAnchorThickness = Anchor::thickness(/**static=*/true);
    const bool relativeToThis = relativeTo == nullptr;
    const QRect relativeToRect = relativeToThis ? parentWidget()->rect().adjusted(staticAnchorThickness, staticAnchorThickness,
                                                                                  -staticAnchorThickness, -staticAnchorThickness)
                                                : relativeTo->geometry();


    switch (location) {
    case Location_OnLeft:
        result = QRect(qMax(0, relativeToRect.x() - side1Length), relativeToRect.y(),
                       lengthForDrop, relativeToRect.height());
        break;
    case Location_OnTop:
        result = QRect(relativeToRect.x(), qMax(0, relativeToRect.y() - side1Length),
                       relativeToRect.width(), lengthForDrop);
        break;
    case Location_OnRight:
        result = QRect(qMin(relativeToRect.right() + 1 - side1Length + newAnchorThickness,
                            contentsWidth() - lengthForDrop - staticAnchorThickness), relativeToRect.y(), lengthForDrop, relativeToRect.height());
        break;
    case Location_OnBottom:
        result = QRect(relativeToRect.x(), qMin(relativeToRect.bottom() + 1 - side1Length + newAnchorThickness,
                                                contentsHeight() - lengthForDrop - staticAnchorThickness),
                       relativeToRect.width(), lengthForDrop);
        break;
    default:
        break;
    }

    qCDebug(sizing) << "MultiSplitterLayout::rectForDrop rect=" << result
                    << "; location=" << location
                    << "; s1=" << side1Length
                    << "; bottom=" << relativeToRect.bottom();
    return result;
}

void MultiSplitterLayout::setAnchorBeingDragged(Anchor *anchor)
{
    m_anchorBeingDragged = anchor;
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
             << "; minimumSize=" << parentWidget()->minimumSize();

    qDebug() << "Widgets:";
    for (auto item : items()) {
        qDebug() <<"    " << item << item->geometry()
                 << "; min.width=" << item->minLength(Qt::Vertical)
                 << "; min.height=" << item->minLength(Qt::Horizontal);
    }

    qDebug() << "Anchors:";
    for (Anchor *anchor : m_anchors) {
        auto side1Widgets = anchor->items(Anchor::Side1);
        auto side2Widgets = anchor->items(Anchor::Side2);
        auto bounds = anchor->isStatic() ? QPair<int, int>() : boundPositionsForAnchor(anchor);
        qDebug() << "    " << anchor
                 << "; side1=" << side1Widgets << anchor->debug_side1ItemNames()
                 << "; side2=" << side2Widgets << anchor->debug_side2ItemNames()
                 << "; pos=" << anchor->pos()
                 << "; bounds=" << bounds
                 << "; orientation=" << anchor->orientation();
    }
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

    redistributeSpace_recursive(m_leftAnchor);
    redistributeSpace_recursive(m_topAnchor);
}

void MultiSplitterLayout::redistributeSpace_recursive(Anchor *fromAnchor)
{
    for (auto w : fromAnchor->items(Anchor::Side2)) {
        Anchor *nextAnchor = w->anchor(Anchor::Side1, fromAnchor->orientation());
        if (nextAnchor->isStatic())
            continue;

        const int newPosition = int(nextAnchor->positionPercentage() * (nextAnchor->isVertical() ? m_contentSize.width()
                                                                                                 : m_contentSize.height()));

        // But don't let the anchor go out of bounds, it must respect its widgets min sizes
        auto bounds = boundPositionsForAnchor(nextAnchor);

        // For the bounding, use Anchor::minPosition, as we're not making the anchors on the left/top shift, which boundsPositionsForAnchor() assumes.
        const int newPositionBounded = qBound(nextAnchor->minPosition(), newPosition, bounds.second);

        qCDebug(sizing) << Q_FUNC_INFO << nextAnchor << "; bounds.first=" << bounds.first
                        << "; newPosition=" << newPosition
                        << "; bounds.second=" << bounds.second
                        << "; newPositionBounded=" << newPositionBounded
                        << "; m_contentSize=" << m_contentSize
                        << "; nextAnchor.minPosition=" << nextAnchor->minPosition();

        nextAnchor->setPosition(newPositionBounded, Anchor::SetPositionOption_DontRecalculatePercentage);
        redistributeSpace_recursive(nextAnchor);
    }
}

void MultiSplitterLayout::updateSizeConstraints()
{
    m_minHeight = m_topAnchor->cumulativeMinLength(Anchor::Side2);
    m_minWidth = m_leftAnchor->cumulativeMinLength(Anchor::Side2);

    parentWidget()->setMinimumSize(m_minWidth, m_minHeight);
    qCDebug(sizing) << Q_FUNC_INFO << "minSize = " << m_minWidth << m_minHeight;
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

Anchor::List MultiSplitterLayout::anchors(Qt::Orientation orientation, bool includeStatic) const
{
    Anchor::List result;
    for (Anchor *anchor : m_anchors) {
        if ((includeStatic || !anchor->isStatic()) && anchor->orientation() == orientation)
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

Item *MultiSplitterLayout::itemForWidget(const QWidget *w) const
{
    for (Item *item : m_items) {
        if (item->frame() == w)
            return item;
    }
    return nullptr;
}

bool MultiSplitterLayout::checkSanity(AnchorSanityOption options) const
{
    if (!m_doSanityChecks)
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

        if (options & AnchorSanity_WidgetInvalidSizes) {
            if (item->width() <= 0 || item->height() <= 0) {
                dumpDebug();
                qWarning() << "Invalid size for widget" << item->size();
                return false;
            }
        }

        return true;
    };


    for (Item *item : qAsConst(m_items)) {
        if (!check(item, Qt::Vertical))
            return false;

        if (!check(item, Qt::Horizontal))
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
    }

    // Check that no widget intersects with an anchor
    if (options & AnchorSanity_Intersections) {
        for (Item *item: items()) {
            for (Anchor *a : anchors()) {
                if (item->geometry().intersects(a->geometry())) {
                    dumpDebug();
                    qWarning() << "MultiSplitterLayout::checkSanity: Widget" << item << "with rect" << item->geometry()
                               << "Intersects anchor" << a << "with rect" << a->geometry();
                    return false;
                }
            }
        }
    }

    if (options & AnchorSanity_WidgetMinSizes) {
        for (Item *item : items()) {
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

    return true;
}

void MultiSplitterLayout::setContentsSize(QSize size)
{
    if (size != m_contentSize) {
        QSize oldSize = m_contentSize;
        m_contentSize = size;
        parentWidget()->resize(size);
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
    if (m_inDestructor || e->spontaneous())
        return false;

    if (!parentWidget()->isVisible()) {
        // The whole MultiSplitter isn't visible, don't bother. It probably even is being hidden by ~QMainWindow().
        return false;
    }

    QWidget *w = qobject_cast<QWidget*>(o);
    if (!w || !w->testAttribute(Qt::WA_WState_ExplicitShowHide)) {
        // We only care about explicit show/hide by the developer
        return false;
    }

    if (e->type() == QEvent::Show) {
        //qDebug() << "MultiSplitterLayout::eventFilter show for " << w << w->testAttribute(Qt::WA_WState_ExplicitShowHide);
        // TODO
    } else if (e->type() == QEvent::Hide) {
        //qDebug() << "MultiSplitterLayout::eventFilter hide for " << w << w->testAttribute(Qt::WA_WState_ExplicitShowHide);
        // TODO
    }

    return false;
}
