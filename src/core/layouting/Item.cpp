/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Item_p.h"
#include "kddockwidgets/core/Separator.h"
#include "kddockwidgets/core/Group.h"
#include "ItemFreeContainer_p.h"
#include "kdbindings/signal.h"
#include "core/Window_p.h"
#include "core/View_p.h"
#include "core/Utils_p.h"
#include "core/Controller_p.h"
#include "core/Platform_p.h"
#include "core/Logging_p.h"
#include "core/ScopedValueRollback_p.h"
#include "core/nlohmann_helpers_p.h"

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <utility>

#ifdef KDDW_FRONTEND_QT
#include <QTimer>
#endif

#define LAYOUT_DUMP_INDENT 6

#ifdef Q_CC_MSVC
#pragma warning(push)
#pragma warning(disable : 4138)
#pragma warning(disable : 4244)
#pragma warning(disable : 4457)
#pragma warning(disable : 4702)
#endif

// clazy:excludeall=missing-typeinfo,old-style-connect

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

int Core::Item::separatorThickness = 5;
bool Core::Item::s_silenceSanityChecks = false;

// There are the defaults. They can be changed by the user via Config.h API.
Size Core::Item::hardcodedMinimumSize = Size(80, 90);
Size Core::Item::hardcodedMaximumSize = Size(16777215, 16777215);

bool Core::ItemBoxContainer::s_inhibitSimplify = false;

inline bool locationIsVertical(Location loc)
{
    return loc == Location_OnTop || loc == Location_OnBottom;
}

inline bool locationIsSide1(Location loc)
{
    return loc == Location_OnLeft || loc == Location_OnTop;
}

inline Qt::Orientation orientationForLocation(Location loc)
{
    switch (loc) {
    case Location_OnLeft:
    case Location_OnRight:
        return Qt::Horizontal;
    case Location_None:
    case Location_OnTop:
    case Location_OnBottom:
        return Qt::Vertical;
    }

    return Qt::Vertical;
}

inline Qt::Orientation oppositeOrientation(Qt::Orientation o)
{
    return o == Qt::Vertical ? Qt::Horizontal : Qt::Vertical;
}

inline Rect adjustedRect(Rect r, Qt::Orientation o, int p1, int p2)
{
    if (o == Qt::Vertical) {
        r.adjust(0, p1, 0, p2);
    } else {
        r.adjust(p1, 0, p2, 0);
    }

    return r;
}

namespace KDDockWidgets::Core {
struct LengthOnSide
{
    int length = 0;
    int minLength = 0;

    int available() const
    {
        return std::max(0, length - minLength);
    }

    int missing() const
    {
        return std::max(0, minLength - length);
    }
};

}

ItemBoxContainer *Item::root() const
{
    return m_parent ? m_parent->root()
                    : const_cast<ItemBoxContainer *>(object_cast<const ItemBoxContainer *>(this));
}

Rect Item::mapToRoot(Rect r) const
{
    const Point topLeft = mapToRoot(r.topLeft());
    r.moveTopLeft(topLeft);
    return r;
}

Point Item::mapToRoot(Point p) const
{
    if (isRoot())
        return p;

    return p + parentContainer()->mapToRoot(pos());
}

int Item::mapToRoot(int p, Qt::Orientation o) const
{
    if (o == Qt::Vertical)
        return mapToRoot(Point(0, p)).y();
    return mapToRoot(Point(p, 0)).x();
}

Point Item::mapFromRoot(Point p) const
{
    const Item *it = this;
    while (it) {
        p = p - it->pos();
        it = it->parentContainer();
    }

    return p;
}

Rect Item::mapFromRoot(Rect r) const
{
    const Point topLeft = mapFromRoot(r.topLeft());
    r.moveTopLeft(topLeft);
    return r;
}

Point Item::mapFromParent(Point p) const
{
    if (isRoot())
        return p;

    return p - pos();
}

int Item::mapFromRoot(int p, Qt::Orientation o) const
{
    if (o == Qt::Vertical)
        return mapFromRoot(Point(0, p)).y();
    return mapFromRoot(Point(p, 0)).x();
}


void Item::setGuestView(View *guest)
{
    assert(!guest || !m_guest);

    m_guest = guest;
    m_parentChangedConnection.disconnect();
    m_guestDebugNameChangedConnection->disconnect();
    m_guestDestroyedConnection->disconnect();
    m_layoutInvalidatedConnection->disconnect();

    if (m_guest) {
        m_guest->controller()->setParentView(m_hostWidget);
        if (Core::Group *group = asGroupController())
            group->setLayoutItem(this);

        m_parentChangedConnection = m_guest->controller()->dptr()->parentViewChanged.connect([this](View *parent) {
            if (!View::equals(parent, hostView())) {
                // Group was detached into floating window. Turn into placeholder
                assert(isVisible());
                turnIntoPlaceholder();
            }
        });

        {
            ScopedValueRollback guard(m_isSettingGuest, true);
            setMinSize(guest->minSize());
            setMaxSizeHint(guest->maxSizeHint());
        }

        m_guestDebugNameChangedConnection =
            m_guest->d->debugNameChanged.connect(&Item::updateObjectName, this);
        m_guestDestroyedConnection =
            m_guest->d->beingDestroyed.connect(&Item::onWidgetDestroyed, this);

        m_layoutInvalidatedConnection =
            guest->d->layoutInvalidated.connect(&Item::onWidgetLayoutRequested, this);

        if (m_sizingInfo.geometry.isEmpty()) {
            // Use the widgets geometry, but ensure it's at least hardcodedMinimumSize
            Rect widgetGeo = m_guest->geometry();
            widgetGeo.setSize(
                widgetGeo.size().expandedTo(minSize()).expandedTo(Item::hardcodedMinimumSize));
            setGeometry(mapFromRoot(widgetGeo));
        } else {
            updateWidgetGeometries();
        }
    }

    updateObjectName();
}

KDDockWidgets::Core::Group *Item::asGroupController() const
{
    return m_guest ? m_guest->asGroupController() : nullptr;
}

void Item::updateWidgetGeometries()
{
    if (m_guest) {
        m_guest->setGeometry(mapToRoot(rect()));
    }
}

void Item::to_json(nlohmann::json &json) const
{
    json["sizingInfo"] = m_sizingInfo;
    json["isVisible"] = m_isVisible;
    json["isContainer"] = isContainer();
    json["objectName"] = objectName();
    if (m_guest)
        json["guestId"] = m_guest->d->id(); // just for coorelation purposes when restoring
}

void Item::fillFromJson(const nlohmann::json &j,
                        const std::unordered_map<QString, KDDockWidgets::Core::View *> &widgets)
{
    m_sizingInfo = j.value("sizingInfo", SizingInfo());
    m_isVisible = j.value("isVisible", false);
    setObjectName(j.value("objectName", QString()));
    const QString guestId = j.value("guestId", QString());
    if (!guestId.isEmpty()) {
        auto it = widgets.find(guestId);
        if (it != widgets.cend()) {
            setGuestView(it->second);
            m_guest->controller()->setParentView(hostView());
        } else if (hostView()) {
            KDDW_ERROR("Couldn't find group to restore for item={}", ( void * )this);
            assert(false);
        }
    }
}

Item *Item::createFromJson(View *hostWidget, ItemContainer *parent, const nlohmann::json &json,
                           const std::unordered_map<QString, View *> &widgets)
{
    auto item = new Item(hostWidget, parent);
    item->fillFromJson(json, widgets);
    return item;
}

void Item::ref()
{
    m_refCount++;
}

void Item::unref()
{
    assert(m_refCount > 0);
    m_refCount--;
    if (m_refCount == 0) {
        assert(!isRoot());
        parentContainer()->removeItem(this);
    }
}

int Item::refCount() const
{
    return m_refCount;
}

View *Item::hostView() const
{
    return m_hostWidget;
}

void Item::restore(View *guest)
{
    if (isVisible() || m_guest) {
        KDDW_ERROR("Hitting assert. visible={}, guest={}", isVisible(), ( void * )this);
        assert(false);
    }

    if (isContainer()) {
        KDDW_ERROR("Containers can't be restored");
    } else {
        setGuestView(guest);
        parentContainer()->restore(this);

        // When we restore to previous positions, we only still from the immediate neighbours.
        // It's consistent with closing an item, it also only grows the immediate neighbours
        // By passing ImmediateNeighboursFirst we can hide/show an item multiple times and it
        // uses the same place
    }
}

Vector<int> Item::pathFromRoot() const
{
    // Returns the list of indexes to get to this item, starting from the root container
    // Example [0, 1, 3] would mean that the item is the 4th child of the 2nd child of the 1st child
    // of root
    // [] would mean 'this' is the root item
    // [0] would mean the 1st child of root

    Vector<int> path;
    path.reserve(10); // random big number, good to bootstrap it

    const Item *it = this;
    while (it) {
        if (auto p = it->parentContainer()) {
            const auto index = p->childItems().indexOf(const_cast<Item *>(it));
            path.prepend(index);
            it = p;
        } else {
            break;
        }
    }

    return path;
}

void Item::setHostView(View *host)
{
    if (m_hostWidget != host) {
        m_hostWidget = host;
        if (m_guest) {
            m_guest->controller()->setParentView(host);
            m_guest->setVisible(true);
            updateWidgetGeometries();
        }
    }
}

void Item::setSize_recursive(Size newSize, ChildrenResizeStrategy)
{
    setSize(newSize);
}

Size Item::missingSize() const
{
    Size missing = minSize() - this->size();
    missing.setWidth(std::max(missing.width(), 0));
    missing.setHeight(std::max(missing.height(), 0));

    return missing;
}

bool Item::isBeingInserted() const
{
    return m_sizingInfo.isBeingInserted;
}

void Item::setBeingInserted(bool is)
{
    m_sizingInfo.isBeingInserted = is;

    // Trickle up the hierarchy too, as the parent might be hidden due to not having visible
    // children
    if (auto parent = parentContainer()) {
        if (is) {
            if (!parent->hasVisibleChildren())
                parent->setBeingInserted(true);
        } else {
            parent->setBeingInserted(false);
        }
    }
}

void Item::setParentContainer(ItemContainer *parent)
{
    if (parent == m_parent)
        return;

    if (m_parent) {
        m_minSizeChangedHandle.disconnect();
        m_visibleChangedHandle.disconnect();
        visibleChanged.emit(this, false);
    }

    if (auto c = asContainer()) {
        const bool ceasingToBeRoot = !m_parent && parent;
        if (ceasingToBeRoot && !c->hasVisibleChildren()) {
            // Was root but is not root anymore. So, if empty, then it has an empty rect too.
            // Only root can have a non-empty rect without having children
            c->setGeometry({});
        }
    }

    m_parent = parent;
    connectParent(parent); // Reused by the ctor too

    setParent(parent);
}

void Item::connectParent(ItemContainer *parent)
{
    if (parent) {
        m_minSizeChangedHandle =
            minSizeChanged.connect(&ItemContainer::onChildMinSizeChanged, parent);
        m_visibleChangedHandle =
            visibleChanged.connect(&ItemContainer::onChildVisibleChanged, parent);

        setHostView(parent->hostView());
        updateWidgetGeometries();

        visibleChanged.emit(this, isVisible());
    }
}

ItemContainer *Item::parentContainer() const
{
    return m_parent;
}

ItemBoxContainer *Item::parentBoxContainer() const
{
    return object_cast<ItemBoxContainer *>(m_parent);
}

int Item::indexInAncestor(ItemContainer *ancestor) const
{
    auto it = this;
    while (auto p = it->parentBoxContainer()) {
        if (p == ancestor) {
            // We found the ancestor
            const auto children = ancestor->visibleChildren();
            return children.indexOf(const_cast<Item *>(it));
        }
        it = p;
    }

    return -1;
}

ItemBoxContainer *Item::ancestorBoxContainerWithOrientation(Qt::Orientation o) const
{
    auto p = parentBoxContainer();
    while (p) {
        if (p->orientation() == o)
            return p;
        p = p->parentBoxContainer();
    }

    return nullptr;
}

const ItemContainer *Item::asContainer() const
{
    return object_cast<const ItemContainer *>(this);
}

ItemContainer *Item::asContainer()
{
    return object_cast<ItemContainer *>(this);
}

ItemBoxContainer *Item::asBoxContainer()
{
    return object_cast<ItemBoxContainer *>(this);
}

void Item::setMinSize(Size sz)
{
    if (sz != m_sizingInfo.minSize) {
        m_sizingInfo.minSize = sz;
        minSizeChanged.emit(this);
        if (!m_isSettingGuest)
            setSize_recursive(size().expandedTo(sz));
    }
}

void Item::setMaxSizeHint(Size sz)
{
    if (sz != m_sizingInfo.maxSizeHint) {
        m_sizingInfo.maxSizeHint = sz;
        maxSizeChanged.emit(this);
    }
}

Size Item::minSize() const
{
    return m_sizingInfo.minSize;
}

Size Item::maxSizeHint() const
{
    return m_sizingInfo.maxSizeHint.boundedTo(hardcodedMaximumSize);
}

void Item::setPos(Point pos)
{
    Rect geo = m_sizingInfo.geometry;
    geo.moveTopLeft(pos);
    setGeometry(geo);
}

void Item::setPos(int pos, Qt::Orientation o)
{
    if (o == Qt::Vertical) {
        setPos({ x(), pos });
    } else {
        setPos({ pos, y() });
    }
}

int Item::pos(Qt::Orientation o) const
{
    return o == Qt::Vertical ? y() : x();
}

int Item::x() const
{
    return m_sizingInfo.geometry.x();
}

int Item::y() const
{
    return m_sizingInfo.geometry.y();
}

int Item::width() const
{
    return m_sizingInfo.geometry.width();
}

int Item::height() const
{
    return m_sizingInfo.geometry.height();
}

Size Item::size() const
{
    return m_sizingInfo.geometry.size();
}

void Item::setSize(Size sz)
{
    Rect newGeo = m_sizingInfo.geometry;
    newGeo.setSize(sz);
    setGeometry(newGeo);
}

void Item::requestResize(int left, int top, int right, int bottom)
{
    if (left == 0 && right == 0 && top == 0 && bottom == 0)
        return;

    ItemBoxContainer *parent = parentBoxContainer();
    if (!parent) {
        // Can't happen
        KDDW_ERROR("Item::requestResize: Could not find parent container");
        return;
    }

    auto moveSeparators = [](int side1Delta, int side2Delta, Separator *separator1, Separator *separator2) {
        if (side1Delta != 0 && separator1) {
            const auto ancestor = separator1->parentContainer();
            const int min = ancestor->minPosForSeparator_global(separator1);
            const int pos = separator1->position();
            const int max = ancestor->maxPosForSeparator_global(separator1);
            int newPos = pos - side1Delta;
            newPos = bound(min, newPos, max);
            const int delta = newPos - pos;

            ancestor->requestSeparatorMove(separator1, delta);
        }

        if (side2Delta != 0 && separator2) {
            const auto ancestor = separator2->parentContainer();
            const int min = ancestor->minPosForSeparator_global(separator2);
            const int pos = separator2->position();
            const int max = ancestor->maxPosForSeparator_global(separator2);
            int newPos = pos + side2Delta;
            newPos = bound(min, newPos, max);
            const int delta = newPos - pos;

            ancestor->requestSeparatorMove(separator2, delta);
        }
    };

    {
        // Here we handle resize along the orientation of the container
        const int side1Delta = parent->isHorizontal() ? left : top;
        const int side2Delta = parent->isHorizontal() ? right : bottom;
        auto separator1 = parent->separatorForChild(this, Side1);
        auto separator2 = parent->separatorForChild(this, Side2);
        moveSeparators(side1Delta, side2Delta, separator1, separator2);
    }

    {
        // Here we handle resize against the orientation of the container
        const int side1Delta = parent->isHorizontal() ? top : left;
        const int side2Delta = parent->isHorizontal() ? bottom : right;
        auto separator1 = parent->adjacentSeparatorForChild(this, Side1);
        auto separator2 = parent->adjacentSeparatorForChild(this, Side2);

        if (separator2)
            KDDW_WARN("SEP {} {}", separator2->position(), separator2->orientation());
        moveSeparators(side1Delta, side2Delta, separator1, separator2);
    }
}

Point Item::pos() const
{
    return m_sizingInfo.geometry.topLeft();
}

Rect Item::geometry() const
{
    return isBeingInserted() ? Rect() : m_sizingInfo.geometry;
}

Rect Item::rect() const
{
    return Rect(0, 0, width(), height());
}

bool Item::isContainer() const
{
    return m_isContainer;
}

int Item::minLength(Qt::Orientation o) const
{
    return Core::length(minSize(), o);
}

int Item::maxLengthHint(Qt::Orientation o) const
{
    return Core::length(maxSizeHint(), o);
}

void Item::setLength(int length, Qt::Orientation o)
{
    assert(length > 0);
    if (o == Qt::Vertical) {
        const int w = std::max(width(), hardcodedMinimumSize.width());
        setSize(Size(w, length));
    } else {
        const int h = std::max(height(), hardcodedMinimumSize.height());
        setSize(Size(length, h));
    }
}

void Item::setLength_recursive(int length, Qt::Orientation o)
{
    setLength(length, o);
}

int Item::length(Qt::Orientation o) const
{
    return Core::length(size(), o);
}

int Item::availableLength(Qt::Orientation o) const
{
    return length(o) - minLength(o);
}

bool Item::isPlaceholder() const
{
    return !isVisible();
}

bool Item::isVisible(bool excludeBeingInserted) const
{
    return m_isVisible && !(excludeBeingInserted && isBeingInserted());
}

void Item::setIsVisible(bool is)
{
    if (is != m_isVisible) {
        m_isVisible = is;
        visibleChanged.emit(this, is);
    }

    if (is && m_guest) {
        m_guest->setGeometry(mapToRoot(rect()));
        m_guest->setVisible(true); // Only set visible when apply*() ?
    }

    updateObjectName();
}

void Item::setGeometry_recursive(Rect rect)
{
    // Recursiveness doesn't apply for non-container items
    setGeometry(rect);
}

bool Item::checkSanity()
{
    if (!root())
        return true;

    if (minSize().width() > width() || minSize().height() > height()) {
        root()->dumpLayout();
        KDDW_ERROR("Size constraints not honoured this={}, min={}, size={}", ( void * )this, minSize(), size());
        return false;
    }

    if (m_guest) {
        if (m_guest->parentView() && !m_guest->parentView()->equals(hostView())) {
            if (root())
                root()->dumpLayout();
            KDDW_ERROR("Unexpected parent for our guest. this={}, item.parentContainer={}, item.root.parent={}",
                       ( void * )this, ( void * )parentContainer(), ( void * )(root() ? root()->parent() : nullptr));
            return false;
        }

#if 0 // if guest is explicitly hidden we're not hiding the item yet. And probably won't
        if (!m_guest->isVisible() && (!m_guest->parent() || m_guest->parentWidget()->isVisible())) {

            KDDW_ERROR("Guest widget isn't visible {}", this);
            return false;
        }
#endif
        if (m_guest->geometry() != mapToRoot(rect())) {
            root()->dumpLayout();
            KDDW_ERROR("Guest widget doesn't have correct geometry. has={}, guest.global={}, item.local={}, item.global={}", m_guest->geometry(), geometry(), mapToRoot(rect()), ( void * )this);
            return false;
        }
    }

    return true;
}

bool Item::isMDI() const
{
    return object_cast<ItemFreeContainer *>(parentContainer()) != nullptr;
}

void Item::setGeometry(Rect rect)
{
    Rect &m_geometry = m_sizingInfo.geometry;

    if (rect != m_geometry) {
        const Rect oldGeo = m_geometry;

        m_geometry = rect;

        if (rect.isEmpty()) {
            // Just a sanity check...
            ItemContainer *c = asContainer();
            if (c) {
                if (c->hasVisibleChildren()) {
                    if (auto r = root())
                        r->dumpLayout();
                    assert(false);
                }
            } else {
                KDDW_ERROR("Empty rect");
            }
        }

        const Size minSz = minSize();
        if (!s_silenceSanityChecks
            && (rect.width() < minSz.width() || rect.height() < minSz.height())) {
            if (auto r = root())
                r->dumpLayout();
            KDDW_ERROR("Constraints not honoured. this={}, sz={}, min={}, parent={}", ( void * )this, rect.size(), minSz, ( void * )parentContainer());
        }

        geometryChanged.emit();

        if (oldGeo.x() != x())
            xChanged.emit();
        if (oldGeo.y() != y())
            yChanged.emit();
        if (oldGeo.width() != width())
            widthChanged.emit();
        if (oldGeo.height() != height())
            heightChanged.emit();

        updateWidgetGeometries();
    }
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &os, const Size &size)
{
    os << "Size(" << size.width() << ", " << size.height() << ")";
    return os;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &os, const Rect &rect)
{
    os << "Rect(" << rect.x() << "," << rect.y() << " " << rect.width() << "x" << rect.height() << ")";
    return os;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &os, const Vector<double> &vec)
{
    os << "{ ";
    for (double v : vec) {
        os << v << ", ";
    }
    os << " }";
    return os;
}


void Item::dumpLayout(int level, bool)
{
    std::string indent(LAYOUT_DUMP_INDENT * size_t(level), ' ');

    std::cerr << indent << "- Widget: " << m_sizingInfo.geometry // << "r=" << m_geometry.right() << "b=" << m_geometry.bottom()
              << "; min=" << minSize();

    if (maxSizeHint() != hardcodedMaximumSize)
        std::cerr << "; max=" << maxSizeHint() << "; ";

    if (!isVisible())
        std::cerr << ";hidden;";

    if (m_guest && geometry() != m_guest->geometry()) {
        std::cerr << "; guest geometry=" << m_guest->geometry();
    }

    if (m_sizingInfo.isBeingInserted)
        std::cerr << ";beingInserted;";

    std::cerr << "; guest=" << this << "; name=" << objectName().toStdString() << "\n";
}

Item::Item(View *hostWidget, ItemContainer *parent)
    : Core::Object(parent)
    , m_isContainer(false)
    , m_parent(parent)
    , m_hostWidget(hostWidget)
{
    connectParent(parent);
}

Item::Item(bool isContainer, View *hostWidget, ItemContainer *parent)
    : Core::Object(parent)
    , m_isContainer(isContainer)
    , m_parent(parent)
    , m_hostWidget(hostWidget)
{
    connectParent(parent);
}

Item::~Item()
{
    m_inDtor = true;
    aboutToBeDeleted.emit();

    m_minSizeChangedHandle.disconnect();
    m_visibleChangedHandle.disconnect();
    m_parentChangedConnection.disconnect();

    deleted.emit();
}

void Item::turnIntoPlaceholder()
{
    assert(!isContainer());

    // Turning into placeholder just means hiding it. So we can show it again in its original
    // position. Call removeItem() so we share the code for making the neighbours grow into the
    // space that becomes available after hiding this one
    parentContainer()->removeItem(this, /*hardDelete=*/false);
}

void Item::updateObjectName()
{
    if (isContainer())
        return;

    if (auto w = guestView()) {
        setObjectName(w->viewName().isEmpty() ? QStringLiteral("widget") : w->viewName());
    } else if (!isVisible()) {
        setObjectName(QStringLiteral("hidden"));
    } else if (!m_guest) {
        setObjectName(QStringLiteral("null"));
    } else {
        setObjectName(QStringLiteral("empty"));
    }
}

void Item::onWidgetDestroyed()
{
    m_guest = nullptr;
    m_parentChangedConnection.disconnect();
    m_guestDebugNameChangedConnection->disconnect();
    m_guestDestroyedConnection->disconnect();

    if (m_refCount) {
        turnIntoPlaceholder();
    } else if (!isRoot()) {
        parentContainer()->removeItem(this);
    }
}

void Item::onWidgetLayoutRequested()
{
    if (View *w = guestView()) {
        if (w->size() != size() && !isMDI()) { // for MDI we allow user/manual arbitrary resize with
                                               // mouse
            std::cerr << "Item::onWidgetLayoutRequested"
                      << "TODO: Not implemented yet. Widget can't just decide to resize yet"
                      << "View.size=" << w->size() << "Item.size=" << size() << m_sizingInfo.geometry
                      << m_sizingInfo.isBeingInserted << "\n";
        }

        if (w->minSize() != minSize()) {
            setMinSize(m_guest->minSize());
        }

        setMaxSizeHint(w->maxSizeHint());
    }
}

bool Item::isRoot() const
{
    return m_parent == nullptr;
}

LayoutBorderLocations Item::adjacentLayoutBorders() const
{
    if (isRoot()) {
        return LayoutBorderLocation_All;
    }

    ItemBoxContainer *c = parentBoxContainer();
    if (!c)
        return LayoutBorderLocation_None;

    const int indexInParent = c->indexOfVisibleChild(this);
    const int numVisibleChildren = c->numVisibleChildren();
    const bool isFirst = indexInParent == 0;
    const bool isLast = indexInParent == numVisibleChildren - 1;
    if (indexInParent == -1)
        return LayoutBorderLocation_None;

    LayoutBorderLocations locations = LayoutBorderLocation_None;
    if (c->isRoot()) {
        if (c->isVertical()) {
            locations |= LayoutBorderLocation_West;
            locations |= LayoutBorderLocation_East;

            if (isFirst)
                locations |= LayoutBorderLocation_North;
            if (isLast)
                locations |= LayoutBorderLocation_South;
        } else {
            locations |= LayoutBorderLocation_North;
            locations |= LayoutBorderLocation_South;

            if (isFirst)
                locations |= LayoutBorderLocation_West;
            if (isLast)
                locations |= LayoutBorderLocation_East;
        }
    } else {
        const LayoutBorderLocations parentBorders = c->adjacentLayoutBorders();
        if (c->isVertical()) {
            if (parentBorders & LayoutBorderLocation_West)
                locations |= LayoutBorderLocation_West;

            if (parentBorders & LayoutBorderLocation_East)
                locations |= LayoutBorderLocation_East;

            if (isFirst && (parentBorders & LayoutBorderLocation_North))
                locations |= LayoutBorderLocation_North;

            if (isLast && (parentBorders & LayoutBorderLocation_South))
                locations |= LayoutBorderLocation_South;

        } else {
            if (parentBorders & LayoutBorderLocation_North)
                locations |= LayoutBorderLocation_North;

            if (parentBorders & LayoutBorderLocation_South)
                locations |= LayoutBorderLocation_South;

            if (isFirst && (parentBorders & LayoutBorderLocation_West))
                locations |= LayoutBorderLocation_West;

            if (isLast && (parentBorders & LayoutBorderLocation_East))
                locations |= LayoutBorderLocation_East;
        }
    }

    return locations;
}

int Item::visibleCount_recursive() const
{
    return isVisible() ? 1 : 0;
}

struct ItemBoxContainer::Private
{
    explicit Private(ItemBoxContainer *qq)
        : q(qq)
    {
    }

    ~Private()
    {
        deleteAll(m_separators);
        m_separators.clear();
    }

    int defaultLengthFor(Item *item, InitialOption option) const;
    void relayoutIfNeeded();
    const Item *itemFromPath(const Vector<int> &path) const;
    void resizeChildren(Size oldSize, Size newSize, SizingInfo::List &sizes,
                        ChildrenResizeStrategy);
    void honourMaxSizes(SizingInfo::List &sizes);
    void scheduleCheckSanity() const;
    KDDockWidgets::Core::Separator *neighbourSeparator(const Item *item, Side,
                                                       Qt::Orientation) const;
    KDDockWidgets::Core::Separator *neighbourSeparator_recursive(const Item *item, Side,
                                                                 Qt::Orientation) const;
    void updateWidgets_recursive();
    /// Returns the positions that each separator should have (x position if Qt::Horizontal, y
    /// otherwise)
    Vector<int> requiredSeparatorPositions() const;
    void updateSeparators();
    void deleteSeparators();
    KDDockWidgets::Core::Separator *separatorAt(int p) const;
    Vector<double> childPercentages() const;
    bool isDummy() const;
    void deleteSeparators_recursive();
    void updateSeparators_recursive();
    Size minSize(const Item::List &items) const;
    int excessLength() const;

    mutable bool m_checkSanityScheduled = false;
    Vector<KDDockWidgets::Core::Separator *> m_separators;
    bool m_convertingItemToContainer = false;
    bool m_blockUpdatePercentages = false;
    bool m_isDeserializing = false;
    bool m_isSimplifying = false;
    Qt::Orientation m_orientation = Qt::Vertical;
    ItemBoxContainer *const q;
};

ItemBoxContainer::ItemBoxContainer(View *hostWidget, ItemContainer *parent)
    : ItemContainer(hostWidget, parent)
    , d(new Private(this))
{
    assert(parent);
}

ItemBoxContainer::ItemBoxContainer(View *hostWidget)
    : ItemContainer(hostWidget, /*parentContainer=*/nullptr)
    , d(new Private(this))
{
}

ItemBoxContainer::~ItemBoxContainer()
{
    delete d;
}

int ItemBoxContainer::numSideBySide_recursive(Qt::Orientation o) const
{
    int num = 0;
    if (d->m_orientation == o) {
        // Example: Container is horizontal and we want to know how many layouted horizontally
        for (Item *child : m_children) {
            if (ItemBoxContainer *container = child->asBoxContainer()) {
                num += container->numSideBySide_recursive(o);
            } else if (!child->isPlaceholder()) {
                num++;
            }
        }
    } else {
        // Example: Container is vertical and we want to know how many layouted horizontally
        for (Item *child : m_children) {
            if (ItemBoxContainer *container = child->asBoxContainer()) {
                num = std::max(num, container->numSideBySide_recursive(o));
            } else if (!child->isPlaceholder()) {
                num = std::max(num, 1);
            }
        }
    }

    return num;
}

bool ItemBoxContainer::checkSanity()
{
    d->m_checkSanityScheduled = false;

    auto plat = Platform::instance();
    if (!plat || plat->d->inDestruction()) {
        // checkSanity() can be called with deleteLater(), so check if we still
        // have a platform
        return true;
    }

    if (!hostView()) {
        /// This is a dummy ItemBoxContainer, just return true
        return true;
    }

    if (!Item::checkSanity())
        return false;

    if (numChildren() == 0 && !isRoot()) {
        KDDW_ERROR("Container is empty. Should be deleted");
        return false;
    }

    if (d->m_orientation != Qt::Vertical && d->m_orientation != Qt::Horizontal) {
        KDDW_ERROR("Invalid orientation={}, this={}", d->m_orientation, ( void * )this);
        return false;
    }

    // Check that the geometries don't overlap
    int expectedPos = 0;
    const auto children = childItems();
    for (Item *item : children) {
        if (!item->isVisible())
            continue;
        const int pos = Core::pos(item->pos(), d->m_orientation);
        if (expectedPos != pos) {
            root()->dumpLayout();
            KDDW_ERROR("Unexpected pos={}, expected={}, item={}, isContainer={}", pos, expectedPos, ( void * )item,
                       item->isContainer());
            return false;
        }

        expectedPos = pos + Core::length(item->size(), d->m_orientation) + separatorThickness;
    }

    const int h1 = Core::length(size(), oppositeOrientation(d->m_orientation));
    for (Item *item : children) {
        if (item->parentContainer() != this) {
            KDDW_ERROR("Invalid parent container for item={}, is={}, expected={}", ( void * )item, ( void * )item->parentContainer(), ( void * )this);
            return false;
        }

        if (item->parent() != this) {
            KDDW_ERROR("Invalid Object parent for item={}, is={}, expected={}", ( void * )item, ( void * )item->parent(), ( void * )this);
            return false;
        }

        if (item->isVisible()) {
            // Check the children height (if horizontal, and vice-versa)
            const int h2 = Core::length(item->size(), oppositeOrientation(d->m_orientation));
            if (h1 != h2) {
                root()->dumpLayout();
                KDDW_ERROR("Invalid size for item {}, Container.length={}, item.length={}", ( void * )item, h1, h2);
                return false;
            }

            if (!rect().contains(item->geometry())) {
                root()->dumpLayout();
                KDDW_ERROR("Item geo is out of bounds. item={}, geo={}, parent.rect={}", ( void * )item, item->geometry(), rect());
                return false;
            }
        }

        if (!item->checkSanity())
            return false;
    }

    const Item::List visibleChildren = this->visibleChildren();
    const bool isEmptyRoot = isRoot() && visibleChildren.isEmpty();
    if (!isEmptyRoot) {
        auto occupied = std::max(0, Item::separatorThickness * (int(visibleChildren.size()) - 1));
        for (Item *item : visibleChildren) {
            occupied += item->length(d->m_orientation);
        }

        if (occupied != length()) {
            root()->dumpLayout();
            KDDW_ERROR("Unexpected length. Expected={}, got={}, this={}", occupied, length(), ( void * )this);
            return false;
        }

        const Vector<double> percentages = d->childPercentages();
        const double totalPercentage = std::accumulate(percentages.begin(), percentages.end(), 0.0);
        const double expectedPercentage = visibleChildren.isEmpty() ? 0.0 : 1.0;
        if (!fuzzyCompare(totalPercentage, expectedPercentage)) {
            root()->dumpLayout();
            KDDW_ERROR("Percentages don't add up", totalPercentage, percentages, ( void * )this);
            const_cast<ItemBoxContainer *>(this)->d->updateSeparators_recursive();
            KDDW_ERROR("percentages={}", d->childPercentages());
            return false;
        }
    }

    const auto numVisibleChildren = int(visibleChildren.size());
    if (d->m_separators.size() != std::max(0, numVisibleChildren - 1)) {
        root()->dumpLayout();
        KDDW_ERROR("Unexpected number of separators sz={}, numVisibleChildren={}", d->m_separators.size(), numVisibleChildren);
        return false;
    }

    const Size expectedSeparatorSize = isVertical() ? Size(width(), Item::separatorThickness)
                                                    : Size(Item::separatorThickness, height());

    const int pos2 = Core::pos(mapToRoot(Point(0, 0)), oppositeOrientation(d->m_orientation));

    for (int i = 0; i < d->m_separators.size(); ++i) {
        KDDockWidgets::Core::Separator *separator = d->m_separators.at(i);
        Item *item = visibleChildren.at(i);
        const int expectedSeparatorPos =
            mapToRoot(item->m_sizingInfo.edge(d->m_orientation) + 1, d->m_orientation);

        if (!View::equals(separator->view()->parentView().get(), hostView())) {
            KDDW_ERROR("Invalid host widget for separator this={}", ( void * )this);
            return false;
        }

        if (separator->parentContainer() != this) {
            KDDW_ERROR("Invalid parent container for separator parent={}, separator={}, this={}", ( void * )separator->parentContainer(), ( void * )separator, ( void * )this);
            return false;
        }

        if (separator->position() != expectedSeparatorPos) {
            root()->dumpLayout();
            KDDW_ERROR("Unexpected separator position, expected={}, separator={}, this={}", separator->position(), expectedSeparatorPos, ( void * )separator, ( void * )this);
            return false;
        }

        View *separatorWidget = separator->view();
        if (separatorWidget->geometry().size() != expectedSeparatorSize) {
            KDDW_ERROR("Unexpected separator size={}, expected={}, separator={}, this={}", separatorWidget->geometry().size(), expectedSeparatorSize, ( void * )separator, ( void * )this);
            return false;
        }

        const int separatorPos2 = Core::pos(separatorWidget->geometry().topLeft(),
                                            oppositeOrientation(d->m_orientation));
        if (Core::pos(separatorWidget->geometry().topLeft(),
                      oppositeOrientation(d->m_orientation))
            != pos2) {
            root()->dumpLayout();
            KDDW_ERROR("Unexpected position pos2={}, expected={}, separator={}, this={}", separatorPos2, pos2, ( void * )separator, ( void * )this);
            return false;
        }

        if (separator->view()->parentView()
            && !separator->view()->parentView()->equals(hostView())) {
            KDDW_ERROR("Unexpected host widget in separator");
            return false;
        }

        // Check that the separator bounds are correct. We can't always honour widget's max-size
        // constraints, so only honour min-size
        const int separatorMinPos = minPosForSeparator_global(separator, /*honourMax=*/false);
        const int separatorMaxPos = maxPosForSeparator_global(separator, /*honourMax=*/false);
        const int separatorPos = separator->position();
        if (separatorPos < separatorMinPos || separatorPos > separatorMaxPos || separatorMinPos < 0
            || separatorMaxPos <= 0) {
            root()->dumpLayout();
            KDDW_ERROR("Invalid bounds for separator, pos={}, min={}, max={}, separator={}", separatorPos, separatorMinPos, separatorMaxPos, ( void * )separator);
            return false;
        }
    }

#ifdef DOCKS_DEVELOPER_MODE
    // Can cause slowdown, so just use it in developer mode.
    if (isRoot()) {
        if (!asBoxContainer()->test_suggestedRect())
            return false;
    }
#endif

    return true;
}

void ItemBoxContainer::Private::scheduleCheckSanity() const
{
#ifdef KDDW_FRONTEND_QT
    if (!m_checkSanityScheduled) {
        m_checkSanityScheduled = true;
        QTimer::singleShot(0, q->root(), &ItemBoxContainer::checkSanity);
    }
#endif
}

bool ItemBoxContainer::hasOrientation() const
{
    return isVertical() || isHorizontal();
}

int ItemBoxContainer::indexOfVisibleChild(const Item *item) const
{
    const Item::List items = visibleChildren();
    return items.indexOf(const_cast<Item *>(item));
}

void ItemBoxContainer::restore(Item *child)
{
    restoreChild(child, NeighbourSqueezeStrategy::ImmediateNeighboursFirst);
}

void ItemBoxContainer::removeItem(Item *item, bool hardRemove)
{
    assert(!item->isRoot());

    if (!contains(item)) {
        // Not ours, ask parent
        item->parentContainer()->removeItem(item, hardRemove);
        return;
    }

    Item *side1Item = visibleNeighbourFor(item, Side1);
    Item *side2Item = visibleNeighbourFor(item, Side2);

    const bool isContainer = item->isContainer();
    const bool wasVisible = !isContainer && item->isVisible();

    if (hardRemove) {
        m_children.removeOne(item);
        delete item;
        if (!isContainer)
            root()->numItemsChanged.emit();
    } else {
        item->setIsVisible(false);
        item->setGuestView(nullptr);

        if (!wasVisible && !isContainer) {
            // Was already hidden
            return;
        }
    }

    if (wasVisible) {
        root()->numVisibleItemsChanged.emit(root()->numVisibleChildren());
    }

    if (isEmpty()) {
        // Empty container is useless, delete it
        if (auto p = parentContainer())
            p->removeItem(this, /*hardDelete=*/true);
    } else if (!hasVisibleChildren()) {
        if (auto p = parentContainer()) {
            p->removeItem(this, /*hardDelete=*/false);
            setGeometry(Rect());
        }
    } else {
        // Neighbours will occupy the space of the deleted item
        growNeighbours(side1Item, side2Item);
        itemsChanged.emit();

        updateSizeConstraints();
        d->updateSeparators_recursive();
    }
}

void ItemBoxContainer::setGeometry_recursive(Rect rect)
{
    setPos(rect.topLeft());

    // Call resize, which is recursive and will resize the children too
    setSize_recursive(rect.size());
}

ItemBoxContainer *ItemBoxContainer::convertChildToContainer(Item *leaf)
{
    ScopedValueRollback converting(d->m_convertingItemToContainer, true);

    const auto index = m_children.indexOf(leaf);
    assert(index != -1);
    auto container = new ItemBoxContainer(hostView(), this);
    container->setParentContainer(nullptr);
    container->setParentContainer(this);

    insertItem(container, index, DefaultSizeMode::NoDefaultSizeMode);
    m_children.removeOne(leaf);
    container->setGeometry(leaf->geometry());
    container->insertItem(leaf, Location_OnTop, DefaultSizeMode::NoDefaultSizeMode);
    itemsChanged.emit();
    d->updateSeparators_recursive();

    return container;
}

/** static */
void ItemBoxContainer::insertItemRelativeTo(Item *item, Item *relativeTo, Location loc,
                                            KDDockWidgets::InitialOption option)
{
    assert(item != relativeTo);

    if (auto asContainer = relativeTo->asBoxContainer()) {
        asContainer->insertItem(item, loc, option);
        return;
    }

    item->setIsVisible(!option.startsHidden());
    assert(!(option.startsHidden() && item->isContainer()));

    ItemBoxContainer *parent = relativeTo->parentBoxContainer();
    if (!parent) {
        KDDW_ERROR("This method should only be called for box containers parent={}", ( void * )item->parent());
        return;
    }

    if (parent->hasOrientationFor(loc)) {
        const bool locIsSide1 = locationIsSide1(loc);
        auto indexInParent = parent->childItems().indexOf(relativeTo);
        if (!locIsSide1)
            indexInParent++;

        const Qt::Orientation orientation = orientationForLocation(loc);
        if (orientation != parent->orientation()) {
            assert(parent->visibleChildren().size() == 1);
            // This is the case where the container only has one item, so it's both vertical and
            // horizontal Now its orientation gets defined
            parent->setOrientation(orientation);
        }

        parent->insertItem(item, indexInParent, option);
    } else {
        ItemBoxContainer *container = parent->convertChildToContainer(relativeTo);
        container->insertItem(item, loc, option);
    }
}

void ItemBoxContainer::insertItem(Item *item, Location loc,
                                  KDDockWidgets::InitialOption initialOption)
{
    assert(item != this);
    if (contains(item)) {
        KDDW_ERROR("Item already exists");
        return;
    }

    item->setIsVisible(!initialOption.startsHidden());
    assert(!(initialOption.startsHidden() && item->isContainer()));

    const Qt::Orientation locOrientation = orientationForLocation(loc);

    if (hasOrientationFor(loc)) {
        if (m_children.size() == 1) {
            // 2 items is the minimum to know which orientation we're layedout
            d->m_orientation = locOrientation;
        }

        const auto index = locationIsSide1(loc) ? 0 : m_children.size();
        insertItem(item, index, initialOption);
    } else {
        // Inserting directly in a container ? Only if it's root.
        assert(isRoot());
        auto container = new ItemBoxContainer(hostView(), this);
        container->setGeometry(rect());
        container->setChildren(m_children, d->m_orientation);
        m_children.clear();
        setOrientation(oppositeOrientation(d->m_orientation));
        insertItem(container, 0, DefaultSizeMode::NoDefaultSizeMode);

        // Now we have the correct orientation, we can insert
        insertItem(item, loc, initialOption);

        if (!container->hasVisibleChildren())
            container->setGeometry(Rect());
    }

    d->updateSeparators_recursive();
    d->scheduleCheckSanity();
}

void ItemBoxContainer::onChildMinSizeChanged(Item *child)
{
    if (d->m_convertingItemToContainer || d->m_isDeserializing || !child->isVisible()) {
        // Don't bother our parents, we're converting
        return;
    }

    updateSizeConstraints();

    if (child->isBeingInserted())
        return;

    if (numVisibleChildren() == 1 && child->isVisible()) {
        // The easy case. Child is alone in the layout, occupies everything.
        child->setGeometry(rect());
        updateChildPercentages();
        return;
    }

    const Size missingForChild = child->missingSize();
    if (!missingForChild.isNull()) {
        // Child has some growing to do. It will grow left and right equally, (and top-bottom), as
        // needed.
        growItem(child, Core::length(missingForChild, d->m_orientation),
                 GrowthStrategy::BothSidesEqually, NeighbourSqueezeStrategy::AllNeighbours);
    }

    updateChildPercentages();
}

void ItemBoxContainer::updateSizeConstraints()
{
    const Size missingSize = this->missingSize();
    if (!missingSize.isNull()) {
        if (isRoot()) {
            // Resize the whole layout
            setSize_recursive(size() + missingSize);
        }
    }

    // Our min-size changed, notify our parent, and so on until it reaches root()
    minSizeChanged.emit(this);
}

void ItemBoxContainer::onChildVisibleChanged(Item *, bool visible)
{
    if (d->m_isDeserializing || isInSimplify())
        return;

    const int numVisible = numVisibleChildren();
    if (visible && numVisible == 1) {
        // Child became visible and there's only 1 visible child. Meaning there were 0 visible
        // before.
        visibleChanged.emit(this, true);
    } else if (!visible && numVisible == 0) {
        visibleChanged.emit(this, false);
    }
}

Rect ItemBoxContainer::suggestedDropRect(const Item *item, const Item *relativeTo,
                                         Location loc) const
{
    // Returns the drop rect. This is the geometry used by the rubber band when you hover over an
    // indicator. It's calculated by copying the layout and inserting the item into the
    // dummy/invisible copy The we see which geometry the item got. This way the returned geometry
    // is always what the item will get if you drop it. One exception is if the window doesn't have
    // enough space and it would grow. In this case we fall back to something reasonable


    if (relativeTo && !relativeTo->parentContainer()) {
        KDDW_ERROR("No parent container");
        return {};
    }

    if (relativeTo && relativeTo->parentContainer() != this) {
        KDDW_ERROR("Called on the wrong container");
        return {};
    }

    if (relativeTo && !relativeTo->isVisible()) {
        KDDW_ERROR("relative to isn't visible");
        return {};
    }

    if (loc == Location_None) {
        KDDW_ERROR("Invalid location");
        return {};
    }

    const Size availableSize = root()->availableSize();
    const Size minSize = item->minSize();
    const bool isEmpty = !root()->hasVisibleChildren();
    const int extraWidth = (isEmpty || locationIsVertical(loc)) ? 0 : Item::separatorThickness;
    const int extraHeight = (isEmpty || !locationIsVertical(loc)) ? 0 : Item::separatorThickness;
    const bool windowNeedsGrowing = availableSize.width() < minSize.width() + extraWidth
        || availableSize.height() < minSize.height() + extraHeight;

    if (windowNeedsGrowing)
        return suggestedDropRectFallback(item, relativeTo, loc);

    nlohmann::json rootSerialized;
    root()->to_json(rootSerialized);

    ItemBoxContainer rootCopy(nullptr);
    rootCopy.fillFromJson(rootSerialized, {});

    if (relativeTo)
        relativeTo = rootCopy.d->itemFromPath(relativeTo->pathFromRoot());

    nlohmann::json itemSerialized;
    item->to_json(itemSerialized);
    auto itemCopy = new Item(nullptr);
    itemCopy->fillFromJson(itemSerialized, {});

    if (relativeTo) {
        auto r = const_cast<Item *>(relativeTo);
        ItemBoxContainer::insertItemRelativeTo(itemCopy, r, loc, DefaultSizeMode::FairButFloor);
    } else {
        rootCopy.insertItem(itemCopy, loc, DefaultSizeMode::FairButFloor);
    }

    if (rootCopy.size() != root()->size()) {
        // Doesn't happen
        KDDW_ERROR("The root copy grew ?! copy={}, sz={}, loc={}", rootCopy.size(), root()->size(), loc);
        return suggestedDropRectFallback(item, relativeTo, loc);
    }

    return itemCopy->mapToRoot(itemCopy->rect());
}

Rect ItemBoxContainer::suggestedDropRectFallback(const Item *item, const Item *relativeTo,
                                                 Location loc) const
{
    const Size minSize = item->minSize();
    const int itemMin = Core::length(minSize, d->m_orientation);
    const int available = availableLength() - Item::separatorThickness;
    if (relativeTo) {
        int suggestedPos = 0;
        const Rect relativeToGeo = relativeTo->geometry();
        const int suggestedLength = relativeTo->length(orientationForLocation(loc)) / 2;
        switch (loc) {
        case Location_OnLeft:
            suggestedPos = relativeToGeo.x();
            break;
        case Location_OnTop:
            suggestedPos = relativeToGeo.y();
            break;
        case Location_OnRight:
            suggestedPos = relativeToGeo.right() - suggestedLength + 1;
            break;
        case Location_OnBottom:
            suggestedPos = relativeToGeo.bottom() - suggestedLength + 1;
            break;
        default:
            assert(false);
        }

        Rect rect;
        if (orientationForLocation(loc) == Qt::Vertical) {
            rect.setTopLeft(Point(relativeTo->x(), suggestedPos));
            rect.setSize(Size(relativeTo->width(), suggestedLength));
        } else {
            rect.setTopLeft(Point(suggestedPos, relativeTo->y()));
            rect.setSize(Size(suggestedLength, relativeTo->height()));
        }

        return mapToRoot(rect);
    } else if (isRoot()) {
        // Relative to the window itself
        Rect rect = this->rect();
        const int oneThird = length() / 3;
        const int suggestedLength = std::max(std::min(available, oneThird), itemMin);

        switch (loc) {
        case Location_OnLeft:
            rect.setWidth(suggestedLength);
            break;
        case Location_OnTop:
            rect.setHeight(suggestedLength);
            break;
        case Location_OnRight:
            rect.adjust(rect.width() - suggestedLength, 0, 0, 0);
            break;
        case Location_OnBottom:
            rect.adjust(0, rect.bottom() - suggestedLength, 0, 0);
            break;
        case Location_None:
            return {};
        }

        return rect;

    } else {
        KDDW_ERROR("Shouldn't happen");
    }

    return {};
}

void ItemBoxContainer::positionItems()
{
    SizingInfo::List sizes = this->sizes();
    positionItems(/*by-ref=*/sizes);
    applyPositions(sizes);

    d->updateSeparators_recursive();
}

void ItemBoxContainer::positionItems_recursive()
{
    positionItems();
    for (Item *item : std::as_const(m_children)) {
        if (item->isVisible()) {
            if (auto c = item->asBoxContainer())
                c->positionItems_recursive();
        }
    }
}

void ItemBoxContainer::applyPositions(const SizingInfo::List &sizes)
{
    const Item::List items = visibleChildren();
    const auto count = items.size();
    assert(count == sizes.size());
    for (int i = 0; i < count; ++i) {
        Item *item = items.at(i);
        const SizingInfo &sizing = sizes[i];
        if (sizing.isBeingInserted) {
            continue;
        }

        const Qt::Orientation oppositeOrientation = ::oppositeOrientation(d->m_orientation);
        // If the layout is horizontal, the item will have the height of the container. And
        // vice-versa
        item->setLength_recursive(sizing.length(oppositeOrientation), oppositeOrientation);

        item->setPos(sizing.geometry.topLeft());
    }
}

Qt::Orientation ItemBoxContainer::orientation() const
{
    return d->m_orientation;
}

void ItemBoxContainer::positionItems(SizingInfo::List &sizes)
{
    int nextPos = 0;
    const auto count = sizes.count();
    const Qt::Orientation oppositeOrientation = ::oppositeOrientation(d->m_orientation);
    for (auto i = 0; i < count; ++i) {
        SizingInfo &sizing = sizes[i];
        if (sizing.isBeingInserted) {
            nextPos += Item::separatorThickness;
            continue;
        }

        // If the layout is horizontal, the item will have the height of the container. And
        // vice-versa
        const int oppositeLength = Core::length(size(), oppositeOrientation);
        sizing.setLength(oppositeLength, oppositeOrientation);
        sizing.setPos(0, oppositeOrientation);

        sizing.setPos(nextPos, d->m_orientation);
        nextPos += sizing.length(d->m_orientation) + Item::separatorThickness;
    }
}

void ItemBoxContainer::clear()
{
    for (Item *item : std::as_const(m_children)) {
        if (ItemBoxContainer *container = item->asBoxContainer())
            container->clear();

        delete item;
    }
    m_children.clear();
    d->deleteSeparators();
}

Item *ItemBoxContainer::itemAt(Point p) const
{
    for (Item *item : std::as_const(m_children)) {
        if (item->isVisible() && item->geometry().contains(p))
            return item;
    }

    return nullptr;
}

Item *ItemBoxContainer::itemAt_recursive(Point p) const
{
    if (Item *item = itemAt(p)) {
        if (auto c = item->asBoxContainer()) {
            return c->itemAt_recursive(c->mapFromParent(p));
        } else {
            return item;
        }
    }

    return nullptr;
}

void ItemBoxContainer::setHostView(View *host)
{
    Item::setHostView(host);
    d->deleteSeparators_recursive();
    for (Item *item : std::as_const(m_children)) {
        item->setHostView(host);
    }

    d->updateSeparators_recursive();
}

void ItemBoxContainer::setIsVisible(bool)
{
    // no-op for containers, visibility is calculated
}

bool ItemBoxContainer::isVisible(bool excludeBeingInserted) const
{
    return hasVisibleChildren(excludeBeingInserted);
}

void ItemBoxContainer::setLength_recursive(int length, Qt::Orientation o)
{
    Size sz = size();
    if (o == Qt::Vertical) {
        sz.setHeight(length);
    } else {
        sz.setWidth(length);
    }

    setSize_recursive(sz);
}

void ItemBoxContainer::insertItem(Item *item, int index, InitialOption option)
{
    if (option.sizeMode != DefaultSizeMode::NoDefaultSizeMode) {
        /// Choose a nice size for the item we're adding
        const int suggestedLength = d->defaultLengthFor(item, option);
        item->setLength_recursive(suggestedLength, d->m_orientation);
    }

    m_children.insert(index, item);
    item->setParentContainer(this);

    itemsChanged.emit();

    if (!d->m_convertingItemToContainer && item->isVisible())
        restoreChild(item);

    const bool shouldEmitVisibleChanged = item->isVisible();

    if (!d->m_convertingItemToContainer && !s_inhibitSimplify)
        simplify();

    if (shouldEmitVisibleChanged)
        root()->numVisibleItemsChanged.emit(root()->numVisibleChildren());
    root()->numItemsChanged.emit();
}

bool ItemBoxContainer::hasOrientationFor(Location loc) const
{
    if (m_children.size() <= 1)
        return true;

    return d->m_orientation == orientationForLocation(loc);
}

int ItemBoxContainer::usableLength() const
{
    const Item::List children = visibleChildren();
    const auto numVisibleChildren = children.size();

    if (children.size() <= 1)
        return Core::length(size(), d->m_orientation);

    const int separatorWaste = separatorThickness * (numVisibleChildren - 1);
    return length() - separatorWaste;
}

void ItemBoxContainer::setChildren(const List &children, Qt::Orientation o)
{
    m_children = children;
    for (Item *item : children)
        item->setParentContainer(this);

    setOrientation(o);
}

void ItemBoxContainer::setOrientation(Qt::Orientation o)
{
    if (o != d->m_orientation) {
        d->m_orientation = o;
        d->updateSeparators_recursive();
    }
}

Size ItemBoxContainer::Private::minSize(const Item::List &items) const
{
    int minW = 0;
    int minH = 0;
    int numVisible = 0;
    if (!q->m_children.isEmpty()) {
        for (Item *item : items) {
            if (!(item->isVisible() || item->isBeingInserted()))
                continue;
            numVisible++;
            if (q->isVertical()) {
                minW = std::max(minW, item->minSize().width());
                minH += item->minSize().height();
            } else {
                minH = std::max(minH, item->minSize().height());
                minW += item->minSize().width();
            }
        }

        const int separatorWaste = std::max(0, (numVisible - 1) * separatorThickness);
        if (q->isVertical())
            minH += separatorWaste;
        else
            minW += separatorWaste;
    }

    return Size(minW, minH);
}

Size ItemBoxContainer::minSize() const
{
    return d->minSize(m_children);
}

Size ItemBoxContainer::maxSizeHint() const
{
    int maxW = isVertical() ? hardcodedMaximumSize.width() : 0;
    int maxH = isVertical() ? 0 : hardcodedMaximumSize.height();

    const Item::List visibleChildren = this->visibleChildren(/*includeBeingInserted=*/false);
    if (!visibleChildren.isEmpty()) {
        for (Item *item : visibleChildren) {
            if (item->isBeingInserted())
                continue;
            const Size itemMaxSz = item->maxSizeHint();
            const int itemMaxWidth = itemMaxSz.width();
            const int itemMaxHeight = itemMaxSz.height();
            if (isVertical()) {
                maxW = std::min(maxW, itemMaxWidth);
                maxH = std::min(maxH + itemMaxHeight, hardcodedMaximumSize.height());
            } else {
                maxH = std::min(maxH, itemMaxHeight);
                maxW = std::min(maxW + itemMaxWidth, hardcodedMaximumSize.width());
            }
        }

        const auto separatorWaste = (int(visibleChildren.size()) - 1) * separatorThickness;
        if (isVertical()) {
            maxH = std::min(maxH + separatorWaste, hardcodedMaximumSize.height());
        } else {
            maxW = std::min(maxW + separatorWaste, hardcodedMaximumSize.width());
        }
    }

    if (maxW == 0)
        maxW = hardcodedMaximumSize.width();

    if (maxH == 0)
        maxH = hardcodedMaximumSize.height();

    return Size(maxW, maxH).expandedTo(d->minSize(visibleChildren));
}

void ItemBoxContainer::Private::resizeChildren(Size oldSize, Size newSize,
                                               SizingInfo::List &childSizes,
                                               ChildrenResizeStrategy strategy)
{
    // This container is being resized to @p newSize, so we must resize our children too, based
    // on @p strategy.
    // The new sizes are applied to @p childSizes, which will be applied to the widgets when we're
    // done

    const Vector<double> childPercentages = this->childPercentages();
    const auto count = childSizes.count();
    const bool widthChanged = oldSize.width() != newSize.width();
    const bool heightChanged = oldSize.height() != newSize.height();
    const bool lengthChanged =
        (q->isVertical() && heightChanged) || (q->isHorizontal() && widthChanged);
    const int totalNewLength = q->usableLength();

    if (strategy == ChildrenResizeStrategy::Percentage) {
        // In this strategy mode, each children will preserve its current relative size. So, if a
        // child is occupying 50% of this container, then it will still occupy that after the
        // container resize

        int remaining = totalNewLength;
        for (int i = 0; i < count; ++i) {
            const bool isLast = i == count - 1;

            SizingInfo &itemSize = childSizes[i];

            const double childPercentage = childPercentages.at(i);
            const int newItemLength = lengthChanged
                ? (isLast ? remaining : int(childPercentage * totalNewLength))
                : itemSize.length(m_orientation);

            if (newItemLength <= 0) {
                q->root()->dumpLayout();
                KDDW_ERROR("Invalid resize newItemLength={}", newItemLength);
                assert(false);
                return;
            }

            remaining = remaining - newItemLength;

            if (q->isVertical()) {
                itemSize.geometry.setSize({ q->width(), newItemLength });
            } else {
                itemSize.geometry.setSize({ newItemLength, q->height() });
            }
        }
    } else if (strategy == ChildrenResizeStrategy::Side1SeparatorMove
               || strategy == ChildrenResizeStrategy::Side2SeparatorMove) {
        int remaining = Core::length(
            newSize - oldSize,
            m_orientation); // This is how much we need to give to children (when growing the
                            // container), or to take from them when shrinking the container
        const bool isGrowing = remaining > 0;
        remaining = std::abs(remaining); // Easier to deal in positive numbers

        // We're resizing the container, and need to decide if we start resizing the 1st children or
        // in reverse order. If the separator is being dragged left or top, then
        // isSide1SeparatorMove is true. If isSide1SeparatorMove is true and we're growing, then it
        // means this container is on the right/bottom of the separator, so should resize its first
        // children first. Same logic for the other 3 cases

        const bool isSide1SeparatorMove = strategy == ChildrenResizeStrategy::Side1SeparatorMove;
        bool resizeHeadFirst = false;
        if (isGrowing && isSide1SeparatorMove) {
            resizeHeadFirst = true;
        } else if (isGrowing && !isSide1SeparatorMove) {
            resizeHeadFirst = false;
        } else if (!isGrowing && isSide1SeparatorMove) {
            resizeHeadFirst = false;
        } else if (!isGrowing && !isSide1SeparatorMove) {
            resizeHeadFirst = true;
        }

        for (int i = 0; i < count; i++) {
            const auto index = resizeHeadFirst ? i : count - 1 - i;

            SizingInfo &size = childSizes[index];

            if (isGrowing) {
                // Since we don't honour item max-size yet, it can just grow all it wants
                size.incrementLength(remaining, m_orientation);
                remaining = 0; // and we're done, the first one got everything
            } else {
                const int availableToGive = size.availableLength(m_orientation);
                const int took = std::min(availableToGive, remaining);
                size.incrementLength(-took, m_orientation);
                remaining -= took;
            }

            if (remaining == 0)
                break;
        }
    }
    honourMaxSizes(childSizes);
}

void ItemBoxContainer::Private::honourMaxSizes(SizingInfo::List &sizes)
{
    // Reduces the size of all children that are bigger than max-size.
    // Assuming there's widgets that are willing to grow to occupy that space.

    int amountNeededToShrink = 0;
    int amountAvailableToGrow = 0;
    Vector<int> indexesOfShrinkers;
    Vector<int> indexesOfGrowers;

    for (int i = 0; i < sizes.count(); ++i) {
        SizingInfo &info = sizes[i];
        const int neededToShrink = info.neededToShrink(m_orientation);
        const int availableToGrow = info.availableToGrow(m_orientation);

        if (neededToShrink > 0) {
            amountNeededToShrink += neededToShrink;
            indexesOfShrinkers.push_back(i); // clazy:exclude=reserve-candidates
        } else if (availableToGrow > 0) {
            amountAvailableToGrow = std::min(amountAvailableToGrow + availableToGrow, q->length());
            indexesOfGrowers.push_back(i); // clazy:exclude=reserve-candidates
        }
    }

    // Don't grow more than what's needed
    amountAvailableToGrow = std::min(amountNeededToShrink, amountAvailableToGrow);

    // Don't shrink more than what's available to grow
    amountNeededToShrink = std::min(amountAvailableToGrow, amountNeededToShrink);

    if (amountNeededToShrink == 0 || amountAvailableToGrow == 0)
        return;

    // We gathered who needs to shrink and who can grow, now try to do it evenly so that all
    // growers participate, and not just one giving everything.

    // Do the growing:
    while (amountAvailableToGrow > 0) {
        // Each grower will grow a bit (round-robin)
        auto toGrow = std::max(1, amountAvailableToGrow / int(indexesOfGrowers.size()));

        for (auto it = indexesOfGrowers.begin(); it != indexesOfGrowers.end();) {
            const int index = *it;
            SizingInfo &sizing = sizes[index];
            const auto grew = std::min(sizing.availableToGrow(m_orientation), toGrow);
            sizing.incrementLength(grew, m_orientation);
            amountAvailableToGrow -= grew;

            if (amountAvailableToGrow == 0) {
                // We're done growing
                break;
            }

            if (sizing.availableToGrow(m_orientation) == 0) {
                // It's no longer a grower
                it = indexesOfGrowers.erase(it);
            } else {
                it++;
            }
        }
    }

    // Do the shrinking:
    while (amountNeededToShrink > 0) {
        // Each shrinker will shrink a bit (round-robin)
        auto toShrink = std::max(1, amountNeededToShrink / int(indexesOfShrinkers.size()));

        for (auto it = indexesOfShrinkers.begin(); it != indexesOfShrinkers.end();) {
            const int index = *it;
            SizingInfo &sizing = sizes[index];
            const auto shrunk = std::min(sizing.neededToShrink(m_orientation), toShrink);
            sizing.incrementLength(-shrunk, m_orientation);
            amountNeededToShrink -= shrunk;

            if (amountNeededToShrink == 0) {
                // We're done shrinking
                break;
            }

            if (sizing.neededToShrink(m_orientation) == 0) {
                // It's no longer a shrinker
                it = indexesOfShrinkers.erase(it);
            } else {
                it++;
            }
        }
    }
}

bool ItemBoxContainer::hostSupportsHonouringLayoutMinSize() const
{
    if (!m_hostWidget) {
        // Corner case. No reason not to honour min-size
        return true;
    }

    if (auto window = m_hostWidget->window()) {
        return window->supportsHonouringLayoutMinSize();
    } else {
        // Corner case. No reason not to honour min-size
        return true;
    }
}

void ItemBoxContainer::setSize_recursive(Size newSize, ChildrenResizeStrategy strategy)
{
    ScopedValueRollback block(d->m_blockUpdatePercentages, true);

    const Size minSize = this->minSize();
    if (newSize.width() < minSize.width() || newSize.height() < minSize.height()) {
        if (!s_silenceSanityChecks && hostSupportsHonouringLayoutMinSize()) {
            root()->dumpLayout();
            KDDW_ERROR("New size doesn't respect size constraints new={}, min={}, this={}", newSize, minSize, ( void * )this);
        }
        return;
    }

    if (newSize == size())
        return;

    const Size oldSize = size();
    setSize(newSize);

    const Item::List children = visibleChildren();
    const auto count = children.size();
    SizingInfo::List childSizes = sizes();

    // #1 Since we changed size, also resize out children.
    // But apply them to our SizingInfo::List first before setting actual Item/QWidget geometries
    // Because we need step #2 where we ensure min sizes for each item are respected. We could
    // calculate and do everything in a single-step, but we already have the code for #2 in
    // growItem() so doing it in 2 steps will reuse much logic.


    // the sizes:
    d->resizeChildren(oldSize, newSize, /*by-ref*/ childSizes, strategy);

    // the positions:
    positionItems(/*by-ref*/ childSizes);

    // #2 Adjust sizes so that each item has at least Item::minSize.
    for (int i = 0; i < count; ++i) {
        SizingInfo &size = childSizes[i];
        const int missing = size.missingLength(d->m_orientation);
        if (missing > 0)
            growItem(i, childSizes, missing, GrowthStrategy::BothSidesEqually,
                     NeighbourSqueezeStrategy::AllNeighbours);
    }

    // #3 Sizes are now correct and honour min/max sizes. So apply them to our Items
    applyGeometries(childSizes, strategy);
}

int ItemBoxContainer::length() const
{
    return isVertical() ? height() : width();
}

void ItemBoxContainer::dumpLayout(int level, bool printSeparators)
{
    if (level == 0 && hostView()) {
        const auto screens = Platform::instance()->screens();
        for (const auto &screen : screens) {
            std::cerr << "Screen: " << screen->geometry() << "; " << screen->availableGeometry()
                      << "; drp=" << screen->devicePixelRatio() << "\n";
        }
    }

    std::string indent(LAYOUT_DUMP_INDENT * size_t(level), ' ');
    const std::string beingInserted =
        m_sizingInfo.isBeingInserted ? "; beingInserted;" : "";
    const std::string visible = !isVisible() ? ";hidden;" : "";
    const bool isOverflow = isOverflowing();
    const Size missingSize_ = missingSize();
    const std::string isOverflowStr = isOverflow ? "; overflowing ;" : "";
    const std::string missingSizeStr = missingSize_.isNull() ? "" : (std::string("; missingSize=") + std::to_string(missingSize_.width()) + "x" + std::to_string(missingSize_.height()));

    const std::string typeStr = isRoot() ? "- Root: " : "- Layout: ";

    {
        std::cerr << indent << typeStr << "; isVertical=" << (d->m_orientation == Qt::Vertical) << "; "
                  << m_sizingInfo.geometry /*<< "r=" << m_geometry.right() << "b=" <<
                                              m_geometry.bottom()*/
                  << "; min=" << minSize() << "; this=" << this << beingInserted << visible
                  << "; %=" << d->childPercentages();

        if (maxSizeHint() != Item::hardcodedMaximumSize)
            std::cerr << "; max=" << maxSizeHint();

        std::cerr << missingSizeStr << isOverflowStr << "\n";
    }

    int i = 0;
    for (Item *item : std::as_const(m_children)) {
        item->dumpLayout(level + 1, printSeparators);
        if (printSeparators && item->isVisible()) {
            if (i < d->m_separators.size()) {
                auto separator = d->m_separators.at(i);
                std::cerr << std::string(LAYOUT_DUMP_INDENT * size_t(level + 1), ' ') << "- Separator: "
                          << "local.geo=" << mapFromRoot(separator->view()->geometry())
                          << " ; global.geo=" << separator->view()->geometry() << "; separator=" << separator << "\n";
            }
            ++i;
        }
    }
}

void ItemBoxContainer::updateChildPercentages()
{
    if (root()->d->m_blockUpdatePercentages)
        return;

    const int usable = usableLength();
    for (Item *item : std::as_const(m_children)) {
        if (item->isVisible() && !item->isBeingInserted()) {
            item->m_sizingInfo.percentageWithinParent =
                (1.0 * item->length(d->m_orientation)) / usable;
        } else {
            item->m_sizingInfo.percentageWithinParent = 0.0;
        }
    }
}

void ItemBoxContainer::updateChildPercentages_recursive()
{
    updateChildPercentages();
    for (Item *item : std::as_const(m_children)) {
        if (auto c = item->asBoxContainer())
            c->updateChildPercentages_recursive();
    }
}

Vector<double> ItemBoxContainer::Private::childPercentages() const
{
    Vector<double> percentages;
    percentages.reserve(q->m_children.size());

    for (Item *item : std::as_const(q->m_children)) {
        if (item->isVisible() && !item->isBeingInserted())
            percentages.push_back(item->m_sizingInfo.percentageWithinParent);
    }

    return percentages;
}

void ItemBoxContainer::restoreChild(Item *item, NeighbourSqueezeStrategy neighbourSqueezeStrategy)
{
    assert(contains(item));

    const bool hadVisibleChildren = hasVisibleChildren(/*excludeBeingInserted=*/true);

    item->setIsVisible(true);
    item->setBeingInserted(true);

    const int excessLength = d->excessLength();

    if (!hadVisibleChildren) {
        // This container was hidden and will now be restored too, since a child was restored
        if (auto c = parentBoxContainer()) {
            setSize(item->size()); // give it a decent size. Same size as the item being restored
                                   // makes sense
            c->restoreChild(this, neighbourSqueezeStrategy);
        }
    }

    // Make sure root() is big enough to respect all item's min-sizes
    updateSizeConstraints();

    item->setBeingInserted(false);

    if (numVisibleChildren() == 1) {
        // The easy case. Child is alone in the layout, occupies everything.
        item->setGeometry_recursive(rect());
        d->updateSeparators_recursive();
        return;
    }

    const int available = availableToSqueezeOnSide(item, Side1)
        + availableToSqueezeOnSide(item, Side2) - Item::separatorThickness;

    const int max = std::min(available, item->maxLengthHint(d->m_orientation));
    const int min = item->minLength(d->m_orientation);

    /*
     * Regarding the excessLength:
     * The layout bigger than its own max-size. The new item will get more (if it can), to counter
     * that excess. There's just 1 case where we have excess length: A layout with items with
     * max-size, but the layout can't be smaller due to min-size constraints of the higher level
     * layouts, in the nesting hierarchy. The excess goes away when inserting a widget that can grow
     * indefinitely, it eats all the current excess.
     */
    const int proposed = std::max(Core::length(item->size(), d->m_orientation),
                                  excessLength - Item::separatorThickness);
    const int newLength = bound(min, proposed, max);

    assert(item->isVisible());

    // growItem() will make it grow by the same amount it steals from the neighbours, so we can't
    // start the growing without zeroing it
    if (isVertical()) {
        item->m_sizingInfo.geometry.setHeight(0);
    } else {
        item->m_sizingInfo.geometry.setWidth(0);
    }

    growItem(item, newLength, GrowthStrategy::BothSidesEqually, neighbourSqueezeStrategy,
             /*accountForNewSeparator=*/true);
    d->updateSeparators_recursive();
}

void ItemBoxContainer::updateWidgetGeometries()
{
    for (Item *item : std::as_const(m_children))
        item->updateWidgetGeometries();
}

int ItemBoxContainer::oppositeLength() const
{
    return isVertical() ? width() : height();
}

void ItemBoxContainer::requestSeparatorMove(KDDockWidgets::Core::Separator *separator,
                                            int delta)
{
    const auto separatorIndex = d->m_separators.indexOf(separator);
    if (separatorIndex == -1) {
        // Doesn't happen
        KDDW_ERROR("Unknown separator {}, this={}", ( void * )separator, ( void * )this);
        root()->dumpLayout();
        return;
    }

    if (delta == 0)
        return;

    const int min = minPosForSeparator_global(separator);
    const int pos = separator->position();
    const int max = maxPosForSeparator_global(separator);

    if ((pos + delta < min && delta < 0) || // pos can be smaller than min, as long as we're making
                                            // the distane to minPos smaller, same for max.
        (pos + delta > max && delta > 0)) { // pos can be bigger than max already and going left/up
                                            // (negative delta, which is fine), just don't increase
                                            // if further
        root()->dumpLayout();
        KDDW_ERROR("Separator would have gone out of bounds, separator={}, min={}, pos={}, max={}, deleta={}", ( void * )separator,
                   min, pos, max, delta);
        return;
    }

    const Side moveDirection = delta < 0 ? Side1 : Side2;
    const Item::List children = visibleChildren();
    if (children.size() <= separatorIndex) {
        // Doesn't happen
        KDDW_ERROR("Not enough children for separator index", ( void * )separator, ( void * )this, separatorIndex);
        root()->dumpLayout();
        return;
    }

    int remainingToTake = std::abs(delta);
    int tookLocally = 0;

    Item *side1Neighbour = children[separatorIndex];
    Item *side2Neighbour = children[separatorIndex + 1];

    Side nextSeparatorDirection = moveDirection;

    if (moveDirection == Side1) {
        // Separator is moving left (or top if horizontal)
        const int availableSqueeze1 = availableToSqueezeOnSide(side2Neighbour, Side1);
        const int availableGrow2 = availableToGrowOnSide(side1Neighbour, Side2);

        // This is the available within our container, which we can use without bothering other
        // separators
        tookLocally = std::min(availableSqueeze1, remainingToTake);
        tookLocally = std::min(tookLocally, availableGrow2);

        if (tookLocally != 0) {
            growItem(side2Neighbour, tookLocally, GrowthStrategy::Side1Only,
                     NeighbourSqueezeStrategy::ImmediateNeighboursFirst, false,
                     ChildrenResizeStrategy::Side1SeparatorMove);
        }

        if (availableGrow2 == tookLocally)
            nextSeparatorDirection = Side2;

    } else {

        const int availableSqueeze2 = availableToSqueezeOnSide(side1Neighbour, Side2);
        const int availableGrow1 = availableToGrowOnSide(side2Neighbour, Side1);

        // Separator is moving right (or bottom if horizontal)
        tookLocally = std::min(availableSqueeze2, remainingToTake);
        tookLocally = std::min(tookLocally, availableGrow1);

        if (tookLocally != 0) {
            growItem(side1Neighbour, tookLocally, GrowthStrategy::Side2Only,
                     NeighbourSqueezeStrategy::ImmediateNeighboursFirst, false,
                     ChildrenResizeStrategy::Side2SeparatorMove);
        }

        if (availableGrow1 == tookLocally)
            nextSeparatorDirection = Side1;
    }

    remainingToTake -= tookLocally;

    if (remainingToTake > 0) {
        // Go up the hierarchy and move the next separator on the left
        if (isRoot()) {
            // Doesn't happen
            KDDW_ERROR("Not enough space to move separator {}", ( void * )this);
        } else {
            KDDockWidgets::Core::Separator *nextSeparator =
                parentBoxContainer()->d->neighbourSeparator_recursive(this, nextSeparatorDirection,
                                                                      d->m_orientation);
            if (!nextSeparator) {
                // Doesn't happen
                KDDW_ERROR("nextSeparator is null, report a bug");
                return;
            }

            // nextSeparator might not belong to parentContainer(), due to different orientation
            const int remainingDelta = moveDirection == Side1 ? -remainingToTake : remainingToTake;
            nextSeparator->parentContainer()->requestSeparatorMove(nextSeparator, remainingDelta);
        }
    }
}

void ItemBoxContainer::requestEqualSize(KDDockWidgets::Core::Separator *separator)
{
    const auto separatorIndex = d->m_separators.indexOf(separator);
    if (separatorIndex == -1) {
        // Doesn't happen
        KDDW_ERROR("Separator not found {}", ( void * )separator);
        return;
    }

    const Item::List children = visibleChildren();
    Item *side1Item = children.at(separatorIndex);
    Item *side2Item = children.at(separatorIndex + 1);

    const int length1 = side1Item->length(d->m_orientation);
    const int length2 = side2Item->length(d->m_orientation);

    if (std::abs(length1 - length2) <= 1) {
        // items already have the same length, nothing to do.
        // We allow for a difference of 1px, since you can't split that.

        // But if at least 1 item is bigger than its max-size, don't bail out early, as then they
        // don't deserve equal sizes.
        if (!(side1Item->m_sizingInfo.isPastMax(d->m_orientation)
              || side2Item->m_sizingInfo.isPastMax(d->m_orientation))) {
            return;
        }
    }

    const int newLength = (length1 + length2) / 2;

    int delta = 0;
    if (length1 < newLength) {
        // Let's move separator to the right
        delta = newLength - length1;
    } else if (length2 < newLength) {
        // or left.
        delta = -(newLength - length2); // negative, since separator is going left
    }

    // Do some bounds checking, to respect min-size and max-size
    const int min = minPosForSeparator_global(separator, true);
    const int max = maxPosForSeparator_global(separator, true);
    const int newPos = bound(min, separator->position() + delta, max);

    // correct the delta
    delta = newPos - separator->position();

    if (delta != 0)
        requestSeparatorMove(separator, delta);
}

void ItemBoxContainer::layoutEqually()
{
    SizingInfo::List childSizes = sizes();
    if (!childSizes.isEmpty()) {
        layoutEqually(childSizes);
        applyGeometries(childSizes);
    }
}

void ItemBoxContainer::layoutEqually(SizingInfo::List &sizes)
{
    const auto numItems = sizes.count();
    Vector<int> satisfiedIndexes;
    satisfiedIndexes.reserve(numItems);

    int lengthToGive = length() - (d->m_separators.size() * Item::separatorThickness);

    // clear the sizes before we start distributing
    for (SizingInfo &size : sizes) {
        size.setLength(0, d->m_orientation);
    }

    while (satisfiedIndexes.count() < sizes.count()) {
        const int remainingItems = int(sizes.count() - satisfiedIndexes.count());
        const int suggestedToGive = std::max(1, lengthToGive / remainingItems);
        const auto oldLengthToGive = lengthToGive;

        for (int i = 0; i < numItems; ++i) {
            if (satisfiedIndexes.contains(i))
                continue;

            SizingInfo &size = sizes[i];
            if (size.availableToGrow(d->m_orientation) <= 0) {
                // Was already satisfied from the beginning
                satisfiedIndexes.push_back(i);
                continue;
            }

            // Bound the max length. Our max can't be bigger than the remaining space.
            // The layout's min length minus our own min length is the amount of space that we
            // need to guarantee. We can't go larger and overwrite that

            const auto othersMissing = // The size that the others are missing to satisfy their
                                       // minimum length
                std::accumulate(sizes.constBegin(), sizes.constEnd(), 0,
                                [this](size_t sum, const SizingInfo &sz) {
                                    return int(sum) + sz.missingLength(d->m_orientation);
                                })
                - size.missingLength(d->m_orientation);

            const auto maxLength =
                std::min(size.length(d->m_orientation) + lengthToGive - othersMissing,
                         size.maxLengthHint(d->m_orientation));

            const auto newItemLenght =
                bound(size.minLength(d->m_orientation),
                      size.length(d->m_orientation) + suggestedToGive, maxLength);
            const auto toGive = newItemLenght - size.length(d->m_orientation);

            if (toGive == 0) {
                assert(false);
                satisfiedIndexes.push_back(i);
            } else {
                lengthToGive -= toGive;
                size.incrementLength(toGive, d->m_orientation);
                if (size.availableToGrow(d->m_orientation) <= 0) {
                    satisfiedIndexes.push_back(i);
                }
                if (lengthToGive == 0)
                    return;

                if (lengthToGive < 0) {
                    KDDW_ERROR("Breaking infinite loop");
                    return;
                }
            }
        }

        if (oldLengthToGive == lengthToGive) {
            // Nothing happened, we can't satisfy more items, due to min/max constraints
            return;
        }
    }
}

void ItemBoxContainer::layoutEqually_recursive()
{
    layoutEqually();
    for (Item *item : std::as_const(m_children)) {
        if (item->isVisible()) {
            if (auto c = item->asBoxContainer())
                c->layoutEqually_recursive();
        }
    }
}

Item *ItemBoxContainer::visibleNeighbourFor(const Item *item, Side side) const
{
    // Item might not be visible, so use m_children instead of visibleChildren()
    const auto index = m_children.indexOf(const_cast<Item *>(item));

    if (side == Side1) {
        for (auto i = index - 1; i >= 0; --i) {
            Item *child = m_children.at(i);
            if (child->isVisible())
                return child;
        }
    } else {
        for (auto i = index + 1; i < m_children.size(); ++i) {
            Item *child = m_children.at(i);
            if (child->isVisible())
                return child;
        }
    }

    return nullptr;
}

Size ItemBoxContainer::availableSize() const
{
    return size() - this->minSize();
}

int ItemBoxContainer::availableLength() const
{
    return isVertical() ? availableSize().height() : availableSize().width();
}

LengthOnSide ItemBoxContainer::lengthOnSide(const SizingInfo::List &sizes, int fromIndex, Side side,
                                            Qt::Orientation o) const
{
    if (fromIndex < 0)
        return {};

    const auto count = sizes.count();
    if (fromIndex >= count)
        return {};

    int start = 0;
    int end = -1;
    if (side == Side1) {
        start = 0;
        end = fromIndex;
    } else {
        start = fromIndex;
        end = count - 1;
    }

    LengthOnSide result;
    for (int i = start; i <= end; ++i) {
        const SizingInfo &size = sizes.at(i);
        result.length += size.length(o);
        result.minLength += size.minLength(o);
    }

    return result;
}

int ItemBoxContainer::neighboursLengthFor(const Item *item, Side side, Qt::Orientation o) const
{
    const Item::List children = visibleChildren();
    const auto index = children.indexOf(const_cast<Item *>(item));
    if (index == -1) {
        KDDW_ERROR("Couldn't find item {}", ( void * )item);
        return 0;
    }

    if (o == d->m_orientation) {
        int neighbourLength = 0;
        int start = 0;
        int end = -1;
        if (side == Side1) {
            start = 0;
            end = index - 1;
        } else {
            start = index + 1;
            end = children.size() - 1;
        }

        for (int i = start; i <= end; ++i)
            neighbourLength += children.at(i)->length(d->m_orientation);

        return neighbourLength;
    } else {
        // No neighbours in the other orientation. Each container is bidimensional.
        return 0;
    }
}

int ItemBoxContainer::neighboursLengthFor_recursive(const Item *item, Side side,
                                                    Qt::Orientation o) const
{
    return neighboursLengthFor(item, side, o)
        + (isRoot() ? 0 : parentBoxContainer()->neighboursLengthFor_recursive(this, side, o));
}

int ItemBoxContainer::neighboursMinLengthFor(const Item *item, Side side, Qt::Orientation o) const
{
    const Item::List children = visibleChildren();
    const auto index = children.indexOf(const_cast<Item *>(item));
    if (index == -1) {
        KDDW_ERROR("Couldn't find item {}", ( void * )item);
        return 0;
    }

    if (o == d->m_orientation) {
        int neighbourMinLength = 0;
        int start = 0;
        int end = -1;
        if (side == Side1) {
            start = 0;
            end = index - 1;
        } else {
            start = index + 1;
            end = children.size() - 1;
        }

        for (int i = start; i <= end; ++i)
            neighbourMinLength += children.at(i)->minLength(d->m_orientation);

        return neighbourMinLength;
    } else {
        // No neighbours here
        return 0;
    }
}

int ItemBoxContainer::neighboursMaxLengthFor(const Item *item, Side side, Qt::Orientation o) const
{
    const Item::List children = visibleChildren();
    const auto index = children.indexOf(const_cast<Item *>(item));
    if (index == -1) {
        KDDW_ERROR("Couldn't find item {}", ( void * )item);
        return 0;
    }

    if (o == d->m_orientation) {
        int neighbourMaxLength = 0;
        int start = 0;
        int end = -1;
        if (side == Side1) {
            start = 0;
            end = index - 1;
        } else {
            start = index + 1;
            end = children.size() - 1;
        }

        for (int i = start; i <= end; ++i)
            neighbourMaxLength =
                std::min(Core::length(root()->size(), d->m_orientation),
                         neighbourMaxLength + children.at(i)->maxLengthHint(d->m_orientation));

        return neighbourMaxLength;
    } else {
        // No neighbours here
        return 0;
    }
}

int ItemBoxContainer::availableToSqueezeOnSide(const Item *child, Side side) const
{
    const int length = neighboursLengthFor(child, side, d->m_orientation);
    const int min = neighboursMinLengthFor(child, side, d->m_orientation);

    const int available = length - min;
    if (available < 0) {
        root()->dumpLayout();
        assert(false);
    }
    return available;
}

int ItemBoxContainer::availableToGrowOnSide(const Item *child, Side side) const
{
    const int length = neighboursLengthFor(child, side, d->m_orientation);
    const int max = neighboursMaxLengthFor(child, side, d->m_orientation);

    return max - length;
}

int ItemBoxContainer::availableToSqueezeOnSide_recursive(const Item *child, Side side,
                                                         Qt::Orientation orientation) const
{
    if (orientation == d->m_orientation) {
        const int available = availableToSqueezeOnSide(child, side);
        return isRoot()
            ? available
            : (available
               + parentBoxContainer()->availableToSqueezeOnSide_recursive(this, side, orientation));
    } else {
        return isRoot()
            ? 0
            : parentBoxContainer()->availableToSqueezeOnSide_recursive(this, side, orientation);
    }
}

int ItemBoxContainer::availableToGrowOnSide_recursive(const Item *child, Side side,
                                                      Qt::Orientation orientation) const
{
    if (orientation == d->m_orientation) {
        const int available = availableToGrowOnSide(child, side);
        return isRoot()
            ? available
            : (available
               + parentBoxContainer()->availableToGrowOnSide_recursive(this, side, orientation));
    } else {
        return isRoot()
            ? 0
            : parentBoxContainer()->availableToGrowOnSide_recursive(this, side, orientation);
    }
}

void ItemBoxContainer::growNeighbours(Item *side1Neighbour, Item *side2Neighbour)
{
    if (!side1Neighbour && !side2Neighbour)
        return;

    SizingInfo::List childSizes = sizes();

    if (side1Neighbour && side2Neighbour) {
        const int index1 = indexOfVisibleChild(side1Neighbour);
        const int index2 = indexOfVisibleChild(side2Neighbour);

        if (index1 == -1 || index2 == -1 || index1 >= childSizes.count()
            || index2 >= childSizes.count()) {
            // Doesn't happen
            KDDW_ERROR("Invalid indexes {} {} {}", index1, index2, childSizes.count());
            return;
        }

        // Give half/half to each neighbour
        Rect &geo1 = childSizes[index1].geometry;
        Rect &geo2 = childSizes[index2].geometry;

        if (isVertical()) {
            const int available = geo2.y() - geo1.bottom() - separatorThickness;
            geo1.setHeight(geo1.height() + available / 2);
            geo2.setTop(geo1.bottom() + separatorThickness + 1);
        } else {
            const int available = geo2.x() - geo1.right() - separatorThickness;
            geo1.setWidth(geo1.width() + available / 2);
            geo2.setLeft(geo1.right() + separatorThickness + 1);
        }

    } else if (side1Neighbour) {
        const int index1 = indexOfVisibleChild(side1Neighbour);
        if (index1 == -1 || index1 >= childSizes.count()) {
            // Doesn't happen
            KDDW_ERROR("Invalid indexes {} {}", index1, childSizes.count());
            return;
        }

        // Grow all the way to the right (or bottom if vertical)
        Rect &geo = childSizes[index1].geometry;
        if (isVertical()) {
            geo.setBottom(rect().bottom());
        } else {
            geo.setRight(rect().right());
        }
    } else if (side2Neighbour) {
        const int index2 = indexOfVisibleChild(side2Neighbour);
        if (index2 == -1 || index2 >= childSizes.count()) {
            // Doesn't happen
            KDDW_ERROR("Invalid indexes {} {}", index2, childSizes.count());
            return;
        }

        // Grow all the way to the left (or top if vertical)
        Rect &geo = childSizes[index2].geometry;
        if (isVertical()) {
            geo.setTop(0);
        } else {
            geo.setLeft(0);
        }
    }

    d->honourMaxSizes(childSizes);
    positionItems(/*by-ref*/ childSizes);
    applyGeometries(childSizes);
}

void ItemBoxContainer::growItem(int index, SizingInfo::List &sizes, int missing,
                                GrowthStrategy growthStrategy,
                                NeighbourSqueezeStrategy neighbourSqueezeStrategy,
                                bool accountForNewSeparator)
{
    int toSteal = missing; // The amount that neighbours of @p index will shrink
    if (accountForNewSeparator)
        toSteal += Item::separatorThickness;

    assert(index != -1);
    if (toSteal == 0)
        return;

    // #1. Grow our item
    SizingInfo &sizingInfo = sizes[index];
    sizingInfo.setOppositeLength(oppositeLength(), d->m_orientation);
    const bool isFirst = index == 0;
    const bool isLast = index == sizes.count() - 1;

    int side1Growth = 0;
    int side2Growth = 0;

    if (growthStrategy == GrowthStrategy::BothSidesEqually) {
        sizingInfo.setLength(sizingInfo.length(d->m_orientation) + missing, d->m_orientation);
        const auto count = sizes.count();
        if (count == 1) {
            // There's no neighbours to push, we're alone. Occupy the full container
            sizingInfo.incrementLength(missing, d->m_orientation);
            return;
        }

        // #2. Now shrink the neighbors by the same amount. Calculate how much to shrink from each
        // side
        const LengthOnSide side1Length = lengthOnSide(sizes, index - 1, Side1, d->m_orientation);
        const LengthOnSide side2Length = lengthOnSide(sizes, index + 1, Side2, d->m_orientation);

        int available1 = side1Length.available();
        int available2 = side2Length.available();

        if (toSteal > available1 + available2) {
            root()->dumpLayout();
            assert(false);
        }

        while (toSteal > 0) {
            if (available1 == 0) {
                assert(available2 >= toSteal);
                side2Growth += toSteal;
                break;
            } else if (available2 == 0) {
                assert(available1 >= toSteal);
                side1Growth += toSteal;
                break;
            }

            const int toTake = std::max(1, toSteal / 2);
            const int took1 = std::min(toTake, available1);
            toSteal -= took1;
            available1 -= took1;
            side1Growth += took1;
            if (toSteal == 0)
                break;

            const int took2 = std::min(toTake, available2);
            toSteal -= took2;
            side2Growth += took2;
            available2 -= took2;
        }
        shrinkNeighbours(index, sizes, side1Growth, side2Growth, neighbourSqueezeStrategy);
    } else if (growthStrategy == GrowthStrategy::Side1Only) {
        side1Growth = std::min(missing, sizingInfo.availableToGrow(d->m_orientation));
        sizingInfo.setLength(sizingInfo.length(d->m_orientation) + side1Growth, d->m_orientation);
        if (side1Growth > 0)
            shrinkNeighbours(index, sizes, side1Growth, /*side2Growth=*/0,
                             neighbourSqueezeStrategy);
        if (side1Growth < missing) {
            missing = missing - side1Growth;

            if (isLast) {
                // Doesn't happen
                KDDW_ERROR("No more items to grow");
            } else {
                growItem(index + 1, sizes, missing, growthStrategy, neighbourSqueezeStrategy,
                         accountForNewSeparator);
            }
        }

    } else if (growthStrategy == GrowthStrategy::Side2Only) {
        side2Growth = std::min(missing, sizingInfo.availableToGrow(d->m_orientation));
        sizingInfo.setLength(sizingInfo.length(d->m_orientation) + side2Growth, d->m_orientation);

        if (side2Growth > 0)
            shrinkNeighbours(index, sizes, /*side1Growth=*/0, side2Growth,
                             neighbourSqueezeStrategy);
        if (side2Growth < missing) {
            missing = missing - side2Growth;

            if (isFirst) {
                // Doesn't happen
                KDDW_ERROR("No more items to grow");
            } else {
                growItem(index - 1, sizes, missing, growthStrategy, neighbourSqueezeStrategy,
                         accountForNewSeparator);
            }
        }
    }
}

void ItemBoxContainer::growItem(Item *item, int amount, GrowthStrategy growthStrategy,
                                NeighbourSqueezeStrategy neighbourSqueezeStrategy,
                                bool accountForNewSeparator,
                                ChildrenResizeStrategy childResizeStrategy)
{
    const Item::List items = visibleChildren();
    const auto index = items.indexOf(item);
    SizingInfo::List sizes = this->sizes();

    growItem(index, /*by-ref=*/sizes, amount, growthStrategy, neighbourSqueezeStrategy,
             accountForNewSeparator);

    applyGeometries(sizes, childResizeStrategy);
}

void ItemBoxContainer::applyGeometries(const SizingInfo::List &sizes,
                                       ChildrenResizeStrategy strategy)
{
    const Item::List items = visibleChildren();
    const auto count = items.size();
    assert(count == sizes.size());

    for (int i = 0; i < count; ++i) {
        Item *item = items.at(i);
        item->setSize_recursive(sizes[i].geometry.size(), strategy);
    }

    positionItems();
}

SizingInfo::List ItemBoxContainer::sizes(bool ignoreBeingInserted) const
{
    const Item::List children = visibleChildren(ignoreBeingInserted);
    SizingInfo::List result;
    result.reserve(children.count());
    for (Item *item : children) {
        if (item->isContainer()) {
            // Containers have virtual min/maxSize methods, and don't really fill in these
            // properties So fill them here
            item->m_sizingInfo.minSize = item->minSize();
            item->m_sizingInfo.maxSizeHint = item->maxSizeHint();
        }
        result.push_back(item->m_sizingInfo);
    }

    return result;
}

Vector<int> ItemBoxContainer::calculateSqueezes(
    SizingInfo::List::const_iterator begin, // clazy:exclude=function-args-by-ref
    SizingInfo::List::const_iterator end, int needed, // clazy:exclude=function-args-by-ref
    NeighbourSqueezeStrategy strategy, bool reversed) const
{
    Vector<int> availabilities;
    for (auto it = begin; it < end; ++it) {
        availabilities.push_back(it->availableLength(d->m_orientation));
    }

    const auto count = availabilities.count();

    Vector<int> squeezes;
    squeezes.resize(count);
    std::fill(squeezes.begin(), squeezes.end(), 0);

    int missing = needed;

    if (strategy == NeighbourSqueezeStrategy::AllNeighbours) {
        while (missing > 0) {
            const int numDonors = std::count_if(availabilities.cbegin(), availabilities.cend(),
                                                [](int num) { return num > 0; });

            if (numDonors == 0) {
                root()->dumpLayout();
                assert(false);
                return {};
            }

            int toTake = missing / numDonors;
            if (toTake == 0)
                toTake = missing;

            for (int i = 0; i < count; ++i) {
                const int available = availabilities.at(i);
                if (available == 0)
                    continue;
                const int took = std::min(missing, std::min(toTake, available));
                availabilities[i] -= took;
                missing -= took;
                squeezes[i] += took;
                if (missing == 0)
                    break;
            }
        }
    } else if (strategy == NeighbourSqueezeStrategy::ImmediateNeighboursFirst) {
        for (int i = 0; i < count; i++) {
            const auto index = reversed ? count - 1 - i : i;

            const int available = availabilities.at(index);
            if (available > 0) {
                const int took = std::min(missing, available);
                missing -= took;
                squeezes[index] += took;
            }

            if (missing == 0)
                break;
        }
    }

    if (missing < 0) {
        // Doesn't really happen
        KDDW_ERROR("Missing is negative. missing={}, squeezes={}", missing, squeezes);
    }

    return squeezes;
}

void ItemBoxContainer::shrinkNeighbours(int index, SizingInfo::List &sizes, int side1Amount,
                                        int side2Amount, NeighbourSqueezeStrategy strategy)
{
    assert(side1Amount > 0 || side2Amount > 0);
    assert(side1Amount >= 0 && side2Amount >= 0); // never negative

    if (side1Amount > 0) {
        auto begin = sizes.cbegin();
        auto end = sizes.cbegin() + index;
        const bool reversed = strategy == NeighbourSqueezeStrategy::ImmediateNeighboursFirst;
        const Vector<int> squeezes =
            calculateSqueezes(begin, end, side1Amount, strategy, reversed);
        for (int i = 0; i < squeezes.size(); ++i) {
            const int squeeze = squeezes.at(i);
            SizingInfo &sizing = sizes[i];
            // setSize() or setGeometry() have the same effect here, we don't care about the
            // position yet. That's done in positionItems()
            sizing.setSize(adjustedRect(sizing.geometry, d->m_orientation, 0, -squeeze).size());
        }
    }

    if (side2Amount > 0) {
        auto begin = sizes.cbegin() + index + 1;
        auto end = sizes.cend();

        const Vector<int> squeezes = calculateSqueezes(begin, end, side2Amount, strategy);
        for (int i = 0; i < squeezes.size(); ++i) {
            const int squeeze = squeezes.at(i);
            SizingInfo &sizing = sizes[i + index + 1];
            sizing.setSize(adjustedRect(sizing.geometry, d->m_orientation, squeeze, 0).size());
        }
    }
}

Vector<int> ItemBoxContainer::Private::requiredSeparatorPositions() const
{
    const int numSeparators = std::max(0, q->numVisibleChildren() - 1);
    Vector<int> positions;
    positions.reserve(numSeparators);

    for (Item *item : std::as_const(q->m_children)) {
        if (positions.size() == numSeparators)
            break;

        if (item->isVisible()) {
            const int localPos = item->m_sizingInfo.edge(m_orientation) + 1;
            positions.push_back(q->mapToRoot(localPos, m_orientation));
        }
    }

    return positions;
}

void ItemBoxContainer::Private::updateSeparators()
{
    if (!q->hostView())
        return;

    const Vector<int> positions = requiredSeparatorPositions();
    const auto requiredNumSeparators = positions.size();

    const bool numSeparatorsChanged = requiredNumSeparators != m_separators.size();
    if (numSeparatorsChanged) {
        // Instead of just creating N missing ones at the end of the list, let's minimize separators
        // having their position changed, to minimize flicker
        KDDockWidgets::Core::Separator::List newSeparators;
        newSeparators.reserve(requiredNumSeparators);

        for (int position : positions) {
            KDDockWidgets::Core::Separator *separator = separatorAt(position);
            if (separator) {
                // Already existing, reuse
                newSeparators.push_back(separator);
                m_separators.removeOne(separator);
            } else {
                separator = new Core::Separator(q->hostView());
                separator->init(q, m_orientation);
                newSeparators.push_back(separator);
            }
        }

        // delete what remained, which is unused
        deleteSeparators();

        m_separators = newSeparators;
    }

    // Update their positions:
    const int pos2 =
        q->isVertical() ? q->mapToRoot(Point(0, 0)).x() : q->mapToRoot(Point(0, 0)).y();

    int i = 0;
    for (int position : positions) {
        m_separators.at(i)->setGeometry(position, pos2, q->oppositeLength());
        i++;
    }

    q->updateChildPercentages();
}

void ItemBoxContainer::Private::deleteSeparators()
{
    deleteAll(m_separators);
    m_separators.clear();
}

void ItemBoxContainer::Private::deleteSeparators_recursive()
{
    deleteSeparators();

    // recurse into the children:
    for (Item *item : std::as_const(q->m_children)) {
        if (auto c = item->asBoxContainer())
            c->d->deleteSeparators_recursive();
    }
}

void ItemBoxContainer::Private::updateSeparators_recursive()
{
    updateSeparators();

    // recurse into the children:
    const Item::List items = q->visibleChildren();
    for (Item *item : items) {
        if (auto c = item->asBoxContainer())
            c->d->updateSeparators_recursive();
    }
}

int ItemBoxContainer::Private::excessLength() const
{
    // Returns how much bigger this layout is than its max-size
    return std::max(0, Core::length(q->size(), m_orientation) - q->maxLengthHint(m_orientation));
}

void ItemBoxContainer::simplify()
{
    // Removes unneeded nesting. For example, a vertical layout doesn't need to have vertical
    // layouts inside. It can simply have the contents of said sub-layouts

    ScopedValueRollback isInSimplify(d->m_isSimplifying, true);

    Item::List newChildren;
    newChildren.reserve(m_children.size() + 20); // over-reserve a bit

    for (Item *child : std::as_const(m_children)) {
        if (ItemBoxContainer *childContainer = child->asBoxContainer()) {
            childContainer->simplify(); // recurse down the hierarchy

            if (childContainer->orientation() == d->m_orientation
                || childContainer->m_children.size() == 1) {
                // This sub-container is redundant, as it has the same orientation as its parent
                // Cannibalize it.
                for (Item *child2 : childContainer->childItems()) {
                    child2->setParentContainer(this);
                    newChildren.push_back(child2);
                }

                delete childContainer;
            } else {
                newChildren.push_back(child);
            }
        } else {
            newChildren.push_back(child);
        }
    }

    if (m_children != newChildren) {
        m_children = newChildren;
        positionItems();
        updateChildPercentages();
    }
}

KDDockWidgets::Core::Separator *ItemBoxContainer::Private::separatorAt(int p) const
{
    for (auto separator : m_separators) {
        if (separator->position() == p)
            return separator;
    }

    return nullptr;
}

bool ItemBoxContainer::isVertical() const
{
    return d->m_orientation == Qt::Vertical;
}

bool ItemBoxContainer::isHorizontal() const
{
    return d->m_orientation == Qt::Horizontal;
}

int ItemBoxContainer::indexOf(KDDockWidgets::Core::Separator *separator) const
{
    return d->m_separators.indexOf(separator);
}

bool ItemBoxContainer::isInSimplify() const
{
    if (d->m_isSimplifying)
        return true;

    auto p = parentBoxContainer();
    return p && p->isInSimplify();
}

int ItemBoxContainer::minPosForSeparator(KDDockWidgets::Core::Separator *separator,
                                         bool honourMax) const
{
    const int globalMin = minPosForSeparator_global(separator, honourMax);
    return mapFromRoot(globalMin, d->m_orientation);
}

int ItemBoxContainer::maxPosForSeparator(KDDockWidgets::Core::Separator *separator,
                                         bool honourMax) const
{
    const int globalMax = maxPosForSeparator_global(separator, honourMax);
    return mapFromRoot(globalMax, d->m_orientation);
}

int ItemBoxContainer::minPosForSeparator_global(KDDockWidgets::Core::Separator *separator,
                                                bool honourMax) const
{
    const int separatorIndex = indexOf(separator);
    assert(separatorIndex != -1);

    const Item::List children = visibleChildren();
    assert(separatorIndex + 1 < children.size());
    Item *item2 = children.at(separatorIndex + 1);

    const int availableToSqueeze =
        availableToSqueezeOnSide_recursive(item2, Side1, d->m_orientation);

    if (honourMax) {
        // We can drag the separator left just as much as it doesn't violate max-size constraints of
        // Side2
        Item *item1 = children.at(separatorIndex);
        const int availabletoGrow = availableToGrowOnSide_recursive(item1, Side2, d->m_orientation);
        return separator->position() - std::min(availabletoGrow, availableToSqueeze);
    }

    return separator->position() - availableToSqueeze;
}

int ItemBoxContainer::maxPosForSeparator_global(KDDockWidgets::Core::Separator *separator,
                                                bool honourMax) const
{
    const int separatorIndex = indexOf(separator);
    assert(separatorIndex != -1);

    const Item::List children = visibleChildren();
    Item *item1 = children.at(separatorIndex);

    const int availableToSqueeze =
        availableToSqueezeOnSide_recursive(item1, Side2, d->m_orientation);

    if (honourMax) {
        // We can drag the separator right just as much as it doesn't violate max-size constraints
        // of Side1
        Item *item2 = children.at(separatorIndex + 1);
        const int availabletoGrow = availableToGrowOnSide_recursive(item2, Side1, d->m_orientation);
        return separator->position() + std::min(availabletoGrow, availableToSqueeze);
    }

    return separator->position() + availableToSqueeze;
}

void ItemBoxContainer::to_json(nlohmann::json &j) const
{
    Item::to_json(j);

    j["children"] = m_children;
    j["orientation"] = d->m_orientation;
}

void ItemBoxContainer::fillFromJson(const nlohmann::json &j,
                                    const std::unordered_map<QString, KDDockWidgets::Core::View *> &widgets)
{
    if (!j.is_object()) {
        KDDW_ERROR("Expected a JSON object");
        return;
    }

    ScopedValueRollback deserializing(d->m_isDeserializing, true);
    Item::fillFromJson(j, widgets);

    d->m_orientation = Qt::Orientation(j.value<Qt::Orientation>("orientation", {}));

    for (const auto &child : j.value("children", nlohmann::json::array())) {
        const bool isContainer = child.value<bool>("isContainer", {});
        Item *childItem =
            isContainer ? new ItemBoxContainer(hostView(), this) : new Item(hostView(), this);
        childItem->fillFromJson(child, widgets);
        m_children.push_back(childItem);
    }

    if (isRoot()) {
        updateChildPercentages_recursive();
        if (hostView()) {
            d->updateSeparators_recursive();
            d->updateWidgets_recursive();
        }

        d->relayoutIfNeeded();
        positionItems_recursive();

        minSizeChanged.emit(this);
#ifdef DOCKS_DEVELOPER_MODE
        if (!checkSanity())
            KDDW_ERROR("Resulting layout is invalid");
#endif
    }
}

bool ItemBoxContainer::Private::isDummy() const
{
    return q->hostView() == nullptr;
}

#ifdef DOCKS_DEVELOPER_MODE
void ItemBoxContainer::relayoutIfNeeded()
{
    d->relayoutIfNeeded();
}

bool ItemBoxContainer::test_suggestedRect()
{
    auto itemToDrop = new Item(hostView());

    const Item::List children = visibleChildren();
    for (Item *relativeTo : children) {
        if (auto c = relativeTo->asBoxContainer()) {
            c->test_suggestedRect();
        } else {
            std::unordered_map<Location, Rect> rects;
            for (Location loc :
                 { Location_OnTop, Location_OnLeft, Location_OnRight, Location_OnBottom }) {
                const Rect rect = suggestedDropRect(itemToDrop, relativeTo, loc);
                rects[loc] = rect;
                if (rect.isEmpty()) {
                    KDDW_ERROR("Empty rect");
                    return false;
                } else if (!root()->rect().contains(rect)) {
                    root()->dumpLayout();
                    KDDW_ERROR("Suggested rect is out of bounds rect={}, loc={}, relativeTo={}", rect, loc, ( void * )relativeTo);
                    return false;
                }
            }

            auto rectFor = [&rects](Location loc) -> Rect {
                auto it = rects.find(loc);
                return it == rects.cend() ? Rect() : it->second;
            };

            if (rectFor(Location_OnBottom).y() <= rectFor(Location_OnTop).y()
                || rectFor(Location_OnRight).x() <= rectFor(Location_OnLeft).x()) {
                root()->dumpLayout();
                KDDW_ERROR("Invalid suggested rects. this={}, relativeTo={}", ( void * )this, ( void * )relativeTo);
                return false;
            }
        }
    }

    delete itemToDrop;
    return true;
}
#endif

Vector<KDDockWidgets::Core::Separator *> ItemBoxContainer::separators_recursive() const
{
    KDDockWidgets::Core::Separator::List separators = d->m_separators;

    for (Item *item : std::as_const(m_children)) {
        if (auto c = item->asBoxContainer())
            separators.append(c->separators_recursive());
    }

    return separators;
}

Vector<KDDockWidgets::Core::Separator *> ItemBoxContainer::separators() const
{
    return d->m_separators;
}

KDDockWidgets::Core::Separator *ItemBoxContainer::separatorForChild(Item *child, Side side) const
{
    if (!child || !child->isVisible()) {
        KDDW_ERROR("ItemBoxContainer::separatorForChild: Unexpected nullptr or invisible child");
        return nullptr;
    }

    const Item::List children = visibleChildren();
    const int childIndex = children.indexOf(child);
    if (childIndex == -1) {
        KDDW_ERROR("ItemBoxContainer::separatorForChild: Could not find child");
        return nullptr;
    }

    int separatorIndex = -1;

    if (side == Side1) {
        // side1 is the separator on the left (or top)
        if (childIndex == 0) // No left separator for the 1st item
            return nullptr;

        separatorIndex = childIndex - 1;
    } else {
        // side2 is the separator on the right (or bottom)
        if (childIndex == children.size() - 1) // No right separator for the last item
            return nullptr;

        separatorIndex = childIndex;
    }

    if (separatorIndex < 0 || separatorIndex >= d->m_separators.size()) {
        KDDW_ERROR("ItemBoxContainer::separatorForChild: Not enough separators {} {} {}", d->m_separators.size(), children.size(), childIndex);
        return nullptr;
    }

    return d->m_separators[separatorIndex];
}

Core::Separator *ItemBoxContainer::adjacentSeparatorForChild(Item *child, Side side) const
{
    if (!child || !child->isVisible()) {
        KDDW_ERROR("ItemBoxContainer::adjacentSeparatorForChild: Unexpected nullptr or invisible child");
        return nullptr;
    }

    int separatorIndex = -1;

    // If this container is horizontal, we need to find the parent vertical one (or vice-versa):
    if (ItemBoxContainer *ancestor = ancestorBoxContainerWithOrientation(oppositeOrientation(orientation()))) {
        // Since it's not a direct ancestor, we need to use indexInAncestor().
        const int childIndex = indexInAncestor(ancestor);
        const auto children = ancestor->visibleChildren();
        const auto separators = ancestor->separators();

        if (childIndex == -1) {
            // Can't happen
            KDDW_ERROR("ItemBoxContainer::adjacentSeparatorForChild: Could not find index inside ancestor");
            return nullptr;
        }

        if (side == Side1) {
            if (childIndex == 0) // No top separator for the 1st item
                return nullptr;

            separatorIndex = childIndex - 1;
        } else {
            if (childIndex == children.size() - 1) // No bottom separator for the last item
                return nullptr;

            separatorIndex = childIndex;
        }

        if (separatorIndex < 0 || separatorIndex >= separators.size()) {
            KDDW_ERROR("ItemBoxContainer::adjacentSeparatorForChild: Not enough separators {} {} {}", separators.size(), children.size(), childIndex);
            return nullptr;
        }

        return separators[separatorIndex];
    }

    /// No grand parent, for example if we are root
    return nullptr;
}

bool ItemBoxContainer::isOverflowing() const
{
    // This never returns true, unless when loading a buggy layout
    // or if QWidgets now have bigger min-size

    int contentsLength = 0;
    int numVisible = 0;
    for (Item *item : std::as_const(m_children)) {
        if (item->isVisible()) {
            contentsLength += item->length(d->m_orientation);
            numVisible++;
        }
    }

    contentsLength += std::max(0, Item::separatorThickness * (numVisible - 1));
    return contentsLength > length();
}

void ItemBoxContainer::Private::relayoutIfNeeded()
{
    // Checks all the child containers if they have the correct min-size, recursively.
    // When loading a layout from disk the min-sizes for the host QWidgets might have changed, so we
    // need to adjust

    {
        // #1. First, we check if the current container has enough space
        const Size missing = q->missingSize();
        if (!missing.isNull())
            q->setSize_recursive(q->size() + missing);
    }

    // #2. Make sure there's no child that is missing space
    for (Item *child : q->m_children) {
        const int missingLength = ::length(child->missingSize(), m_orientation);
        if (!child->isVisible() || missingLength == 0)
            continue;

        q->growItem(child, missingLength, GrowthStrategy::BothSidesEqually, NeighbourSqueezeStrategy::AllNeighbours);
    }

    // #3. Contents is currently bigger. Not sure if this can still happen.
    if (q->isOverflowing()) {
        const Size size = q->size();
        q->m_sizingInfo.setSize(size + Size(1, 1)); // Just so setSize_recursive() doesn't bail out
        q->setSize_recursive(size);
        q->updateChildPercentages();
    }

    // Let's see our children too:
    for (Item *item : std::as_const(q->m_children)) {
        if (item->isVisible()) {
            if (auto c = item->asBoxContainer())
                c->d->relayoutIfNeeded();
        }
    }
}

const Item *ItemBoxContainer::Private::itemFromPath(const Vector<int> &path) const
{
    const ItemBoxContainer *container = q;

    for (int i = 0; i < path.size(); ++i) {
        const int index = path[i];
        const bool isLast = i == path.size() - 1;
        if (index < 0 || index >= container->m_children.size()) {
            // Doesn't happen
            q->root()->dumpLayout();
            KDDW_ERROR("Invalid index {}, this={}, path={}, isRoot={}", index, ( void * )this, path, q->isRoot());
            return nullptr;
        }

        if (isLast) {
            return container->m_children.at(index);
        } else {
            container = container->m_children.at(index)->asBoxContainer();
            if (!container) {
                KDDW_ERROR("Invalid index path={}", path);
                return nullptr;
            }
        }
    }

    return q;
}

Core::Separator *
ItemBoxContainer::Private::neighbourSeparator(const Item *item, Side side,
                                              Qt::Orientation orientation) const
{
    Item::List children = q->visibleChildren();
    const auto itemIndex = children.indexOf(const_cast<Item *>(item));
    if (itemIndex == -1) {
        KDDW_ERROR("Item not found item={}, this={}", ( void * )item, ( void * )this);
        q->root()->dumpLayout();
        return nullptr;
    }

    if (orientation != q->orientation()) {
        // Go up
        if (q->isRoot()) {
            return nullptr;
        } else {
            return q->parentBoxContainer()->d->neighbourSeparator(q, side, orientation);
        }
    }

    const auto separatorIndex = side == Side1 ? itemIndex - 1 : itemIndex;

    if (separatorIndex < 0 || separatorIndex >= m_separators.size())
        return nullptr;

    return m_separators[separatorIndex];
}

KDDockWidgets::Core::Separator *
ItemBoxContainer::Private::neighbourSeparator_recursive(const Item *item, Side side,
                                                        Qt::Orientation orientation) const
{
    KDDockWidgets::Core::Separator *separator = neighbourSeparator(item, side, orientation);
    if (separator)
        return separator;

    if (!q->parentContainer())
        return nullptr;

    return q->parentBoxContainer()->d->neighbourSeparator_recursive(q, side, orientation);
}

void ItemBoxContainer::Private::updateWidgets_recursive()
{
    for (Item *item : std::as_const(q->m_children)) {
        if (auto c = item->asBoxContainer()) {
            c->d->updateWidgets_recursive();
        } else {
            if (item->isVisible()) {
                if (View *widget = item->guestView()) {
                    widget->setGeometry(q->mapToRoot(item->geometry()));
                    widget->setVisible(true);
                } else {
                    KDDW_ERROR("visible item doesn't have a guest item=", ( void * )item);
                }
            }
        }
    }
}

SizingInfo::SizingInfo()
    : minSize(Core::Item::hardcodedMinimumSize)
    , maxSizeHint(Core::Item::hardcodedMaximumSize)
{
}

void SizingInfo::setOppositeLength(int l, Qt::Orientation o)
{
    setLength(l, oppositeOrientation(o));
}

int SizingInfo::maxLengthHint(Qt::Orientation o) const
{
    return std::max(minLength(o), Core::length(maxSizeHint, o));
}

int SizingInfo::availableLength(Qt::Orientation o) const
{
    return std::max(0, length(o) - minLength(o));
}

int SizingInfo::missingLength(Qt::Orientation o) const
{
    return std::max(0, minLength(o) - length(o));
}

int SizingInfo::neededToShrink(Qt::Orientation o) const
{
    return std::max(0, length(o) - maxLengthHint(o));
}

void Core::to_json(nlohmann::json &j, const SizingInfo &info)
{
    j["geometry"] = info.geometry;
    j["minSize"] = info.minSize;
    j["maxSizeHint"] = info.maxSizeHint;
    j["percentageWithinParent"] = info.percentageWithinParent;
    j["isBeingInserted"] = info.isBeingInserted;
}

void Core::from_json(const nlohmann::json &j, SizingInfo &info)
{
    info.geometry = j.value("geometry", Rect());
    info.minSize = j.value("minSize", Size());
    info.maxSizeHint = j.value("maxSizeHint", Size());
    info.percentageWithinParent = j.value<double>("percentageWithinParent", {});
    info.isBeingInserted = j.value<bool>("isBeingInserted", {});
}

void Core::to_json(nlohmann::json &j, Item *item)
{
    if (!item)
        return;

    // virtual dispatch
    item->to_json(j);
}

int ItemBoxContainer::Private::defaultLengthFor(Item *item, InitialOption option) const
{
    int result = 0;

    if (option.hasPreferredLength(m_orientation)
        && option.sizeMode != DefaultSizeMode::NoDefaultSizeMode) {
        result = option.preferredLength(m_orientation);
    } else {
        switch (option.sizeMode) {
        case DefaultSizeMode::NoDefaultSizeMode:
            break;
        case DefaultSizeMode::Fair: {
            const int numVisibleChildren =
                q->numVisibleChildren() + 1; // +1 so it counts with @p item too, which we're adding
            const int usableLength =
                q->length() - (Item::separatorThickness * (numVisibleChildren - 1));
            result = usableLength / numVisibleChildren;
            break;
        }
        case DefaultSizeMode::FairButFloor: {
            int length = defaultLengthFor(item, DefaultSizeMode::Fair);
            result = std::min(length, item->length(m_orientation));
            break;
        }
        case DefaultSizeMode::ItemSize:
            result = item->length(m_orientation);
            break;
        }
    }

    result = std::max(item->minLength(m_orientation), result); // bound with max-size too
    return result;
}

struct ItemContainer::Private
{
    explicit Private(ItemContainer *qq)
        : q(qq)
    {
    }

    ~Private()
    {
    }
    ItemContainer *const q;
};

ItemContainer::ItemContainer(View *hostWidget, ItemContainer *parent)
    : Item(true, hostWidget, parent)
    , d(new Private(this))
{
    xChanged.connect([this] {
        for (Item *item : std::as_const(m_children)) {
            item->xChanged.emit();
        }
    });

    yChanged.connect([this] {
        for (Item *item : std::as_const(m_children)) {
            item->yChanged.emit();
        }
    });
}

ItemContainer::ItemContainer(View *hostWidget)
    : Item(true, hostWidget, nullptr)
    , d(new Private(this))
{
}

ItemContainer::~ItemContainer()
{
    delete d;
}

const Item::List ItemContainer::childItems() const
{
    return m_children;
}

bool ItemContainer::hasChildren() const
{
    return !m_children.isEmpty();
}

bool ItemContainer::hasVisibleChildren(bool excludeBeingInserted) const
{
    for (Item *item : std::as_const(m_children)) {
        if (item->isVisible(excludeBeingInserted))
            return true;
    }

    return false;
}

int ItemContainer::numChildren() const
{
    return m_children.size();
}

int ItemContainer::numVisibleChildren() const
{
    int num = 0;
    for (Item *child : std::as_const(m_children)) {
        if (child->isVisible())
            num++;
    }
    return num;
}

bool ItemContainer::isEmpty() const
{
    return m_children.isEmpty();
}

bool ItemContainer::hasSingleVisibleItem() const
{
    return numVisibleChildren() == 1;
}

bool ItemContainer::contains(const Item *item) const
{
    return m_children.contains(const_cast<Item *>(item));
}

Item *ItemContainer::itemForView(const View *w) const
{
    for (Item *item : std::as_const(m_children)) {
        if (item->isContainer()) {
            if (Item *result = item->asContainer()->itemForView(w))
                return result;
        } else if (item->guestView() == w) {
            return item;
        }
    }

    return nullptr;
}

Item::List ItemContainer::visibleChildren(bool includeBeingInserted) const
{
    Item::List items;
    items.reserve(m_children.size());
    for (Item *item : std::as_const(m_children)) {
        if (includeBeingInserted) {
            if (item->isVisible() || item->isBeingInserted())
                items.push_back(item);
        } else {
            if (item->isVisible() && !item->isBeingInserted())
                items.push_back(item);
        }
    }

    return items;
}

Item::List ItemContainer::items_recursive() const
{
    Item::List items;
    items.reserve(30); // sounds like a good upper number to minimize allocations
    for (Item *item : std::as_const(m_children)) {
        if (auto c = item->asContainer()) {
            items.append(c->items_recursive());
        } else {
            items.push_back(item);
        }
    }

    return items;
}

bool ItemContainer::contains_recursive(const Item *item) const
{
    for (Item *it : std::as_const(m_children)) {
        if (it == item) {
            return true;
        } else if (it->isContainer()) {
            if (it->asContainer()->contains_recursive(item))
                return true;
        }
    }

    return false;
}


int ItemContainer::visibleCount_recursive() const
{
    int count = 0;
    for (Item *item : std::as_const(m_children)) {
        count += item->visibleCount_recursive();
    }

    return count;
}

int ItemContainer::count_recursive() const
{
    int count = 0;
    for (Item *item : std::as_const(m_children)) {
        if (auto c = item->asContainer()) {
            count += c->count_recursive();
        } else {
            count++;
        }
    }

    return count;
}

#ifdef Q_CC_MSVC
#pragma warning(pop)
#endif
