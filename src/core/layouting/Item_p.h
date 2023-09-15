/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"

#include "kdbindings/signal.h"
#include "nlohmann/json.hpp"

#include <memory>
#include <unordered_map>

class TestMultiSplitter;

namespace KDDockWidgets {

namespace Core {

class Group;
class Separator;
class View;
class ItemContainer;
class ItemBoxContainer;
class Item;
struct LengthOnSide;

enum Side {
    Side1,
    Side2
};

enum class GrowthStrategy {
    BothSidesEqually,
    Side1Only,
    Side2Only
};

enum class SeparatorOption {
    None = 0,
    LazyResize
};
Q_DECLARE_FLAGS(SeparatorOptions, SeparatorOption)

enum class ChildrenResizeStrategy {
    Percentage, ///< Resizes the container in a way that all children will keep occupying the same
                ///< percentage
    Side1SeparatorMove, ///< When resizing a container, it takes/adds space from Side1 children
                        ///< first
    Side2SeparatorMove ///< When resizing a container, it takes/adds space from Side2 children first
};

enum class NeighbourSqueezeStrategy {
    AllNeighbours, ///< The squeeze is spread between all neighbours, not just immediate ones first
    ImmediateNeighboursFirst ///< The first neighbour takes as much squeeze as it can, only then the
                             ///< next neighbour is squezed, and so forth
};

enum LayoutBorderLocation {
    LayoutBorderLocation_None = 0,
    LayoutBorderLocation_North = 1,
    LayoutBorderLocation_East = 2,
    LayoutBorderLocation_West = 4,
    LayoutBorderLocation_South = 8,
    LayoutBorderLocation_All = LayoutBorderLocation_North | LayoutBorderLocation_East
        | LayoutBorderLocation_West | LayoutBorderLocation_South,
    LayoutBorderLocation_Verticals = LayoutBorderLocation_West | LayoutBorderLocation_East,
    LayoutBorderLocation_Horizontals = LayoutBorderLocation_North | LayoutBorderLocation_South,
};
Q_DECLARE_FLAGS(LayoutBorderLocations, LayoutBorderLocation)

inline int pos(Point p, Qt::Orientation o)
{
    return o == Qt::Vertical ? p.y() : p.x();
}

inline int length(Size sz, Qt::Orientation o)
{
    return o == Qt::Vertical ? sz.height() : sz.width();
}

struct DOCKS_EXPORT_FOR_UNIT_TESTS SizingInfo
{
    SizingInfo();

    Size size() const
    {
        return geometry.size();
    }

    void setSize(Size sz)
    {
        geometry.setSize(sz);
    }

    int length(Qt::Orientation o) const
    {
        return Core::length(size(), o);
    }

    int minLength(Qt::Orientation o) const
    {
        return Core::length(minSize, o);
    }

    int maxLengthHint(Qt::Orientation o) const;
    int availableLength(Qt::Orientation o) const;
    int missingLength(Qt::Orientation o) const;

    Point pos() const
    {
        return geometry.topLeft();
    }

    int position(Qt::Orientation o) const
    {
        return Core::pos(pos(), o);
    }

    int edge(Qt::Orientation o) const
    {
        return o == Qt::Vertical ? geometry.bottom() : geometry.right();
    }

    void setLength(int l, Qt::Orientation o)
    {
        if (o == Qt::Vertical) {
            geometry.setHeight(l);
        } else {
            geometry.setWidth(l);
        }
    }

    void incrementLength(int byAmount, Qt::Orientation o)
    {
        setLength(length(o) + byAmount, o);
    }

    void setOppositeLength(int l, Qt::Orientation o);

    void setPos(int p, Qt::Orientation o)
    {
        if (o == Qt::Vertical)
            geometry.moveTop(p);
        else
            geometry.moveLeft(p);
    }

    bool isNull() const
    {
        return geometry.isNull();
    }

    void setGeometry(Rect geo)
    {
        geometry = geo;
    }

    int availableToGrow(Qt::Orientation o) const
    {
        return maxLengthHint(o) - length(o);
    }

    int neededToShrink(Qt::Orientation o) const;

    bool isPastMax(Qt::Orientation o) const
    {
        return availableToGrow(o) >= 0;
    }

    typedef Vector<SizingInfo> List;
    Rect geometry;
    Size minSize;
    Size maxSizeHint;
    double percentageWithinParent = 0.0;
    bool isBeingInserted = false;
};

class DOCKS_EXPORT_FOR_UNIT_TESTS Item : public Core::Object
{
    Q_OBJECT
public:
    typedef Vector<Item *> List;

    explicit Item(KDDockWidgets::Core::View *hostWidget, ItemContainer *parent = nullptr);
    ~Item() override;

    /// @brief returns whether this item is a root container
    bool isRoot() const;

    ///@brief Returns whether the item is touching the layout's borders.
    /// Returns Location_None if it's not touching a border.
    LayoutBorderLocations adjacentLayoutBorders() const;

    virtual int visibleCount_recursive() const;

    /**
     * @brief No widget can have a minimum size smaller than this, regardless of their minimum size.
     */
    static Size hardcodedMinimumSize;
    static Size hardcodedMaximumSize;
    static int separatorThickness;

    int x() const;
    int y() const;
    int width() const;
    int height() const;
    Size size() const;
    void setSize(Size);

    /// Unlike setSize(), which just stores data, requestResize() asks the parent container
    /// to resize this item and all its neighbours. This is convenience API for users wanting
    /// to programmatically resize a dock widget. Not really used by the usual layouting.
    /// API semantics work like QRect::adjust(), positive values always increase size.
    void requestResize(int left, int top, int right, int bottom);

    Point pos() const;
    int pos(Qt::Orientation) const;
    Rect geometry() const;
    Rect rect() const;
    bool isContainer() const;
    ItemContainer *parentContainer() const;

    /// Returns the parent container, but casted to ItemBoxContainer
    ItemBoxContainer *parentBoxContainer() const;

    int indexInAncestor(ItemContainer *) const;

    /// Returns the 1st ancestor container that has the desired orientation
    /// Example:
    /// - ItemBoxContainer(Vertical)
    /// -- ItemBoxContainer(Horizontal)
    /// --- Item // Passing this item to ancestorBoxContainerWithOrientation(Qt::Vertical) would
    /// skip the direct parent and return the verticl one.
    ItemBoxContainer *ancestorBoxContainerWithOrientation(Qt::Orientation) const;

    void setMinSize(Size);
    void setMaxSizeHint(Size);
    bool isPlaceholder() const;
    void setGeometry(Rect rect);
    ItemBoxContainer *root() const;
    Rect mapToRoot(Rect) const;
    Point mapToRoot(Point) const;
    int mapToRoot(int p, Qt::Orientation) const;
    Point mapFromRoot(Point) const;
    Rect mapFromRoot(Rect) const;
    Point mapFromParent(Point) const;
    int mapFromRoot(int p, Qt::Orientation) const;

    KDDockWidgets::Core::Group *asGroupController() const;
    KDDockWidgets::Core::View *guestView() const
    {
        return m_guest;
    }
    void setGuestView(KDDockWidgets::Core::View *);

    void ref();
    void unref();
    int refCount() const;
    void turnIntoPlaceholder();

    int minLength(Qt::Orientation) const;
    int maxLengthHint(Qt::Orientation) const;

    KDDockWidgets::Core::View *hostView() const;
    void restore(KDDockWidgets::Core::View *guestView);

    Vector<int> pathFromRoot() const;

    Q_REQUIRED_RESULT virtual bool checkSanity();
    bool isMDI() const;

    static bool s_silenceSanityChecks;

    virtual Size minSize() const;
    virtual Size maxSizeHint() const;
    virtual void
    setSize_recursive(Size newSize,
                      ChildrenResizeStrategy strategy = ChildrenResizeStrategy::Percentage);
    virtual bool isVisible(bool excludeBeingInserted = false) const;
    virtual void setGeometry_recursive(Rect rect);
    virtual void dumpLayout(int level = 0, bool printSeparators = true);
    virtual void setHostView(KDDockWidgets::Core::View *);
    virtual void to_json(nlohmann::json &) const;

    virtual void fillFromJson(const nlohmann::json &,
                              const std::unordered_map<QString, KDDockWidgets::Core::View *> &);

    static Item *createFromJson(KDDockWidgets::Core::View *hostWidget, ItemContainer *parent,
                                const nlohmann::json &,
                                const std::unordered_map<QString, KDDockWidgets::Core::View *> &);

    KDBindings::Signal<> geometryChanged;
    KDBindings::Signal<> xChanged;
    KDBindings::Signal<> yChanged;
    KDBindings::Signal<> widthChanged;
    KDBindings::Signal<> heightChanged;
    KDBindings::Signal<Core::Item *, bool> visibleChanged;
    KDBindings::Signal<Core::Item *> minSizeChanged;
    KDBindings::Signal<Core::Item *> maxSizeChanged;
    /// signal emitted when ~Item starts
    KDBindings::Signal<> aboutToBeDeleted;
    KDBindings::Signal<> deleted;

public:
    friend class ::TestMultiSplitter;
    explicit Item(bool isContainer, KDDockWidgets::Core::View *hostWidget, ItemContainer *parent);
    void setParentContainer(ItemContainer *parent);
    void connectParent(ItemContainer *parent);
    void setPos(Point);
    void setPos(int pos, Qt::Orientation);
    const ItemContainer *asContainer() const;
    ItemContainer *asContainer();
    ItemBoxContainer *asBoxContainer();
    void setLength(int length, Qt::Orientation);
    virtual void setLength_recursive(int length, Qt::Orientation);
    int length(Qt::Orientation) const;
    int availableLength(Qt::Orientation) const;
    Size missingSize() const;
    virtual void updateWidgetGeometries();
    virtual void setIsVisible(bool);
    bool isBeingInserted() const;
    void setBeingInserted(bool);

    SizingInfo m_sizingInfo;
    const bool m_isContainer;
    ItemContainer *m_parent = nullptr;
    bool m_isSettingGuest = false;
    bool m_inDtor = false;
private Q_SLOTS:
    void onWidgetLayoutRequested();

private:
    friend class ItemContainer;
    friend class ItemBoxContainer;
    friend class ItemFreeContainer;
    int m_refCount = 0;
    void updateObjectName();
    void onWidgetDestroyed();
    bool m_isVisible = false;
    KDDockWidgets::Core::View *m_hostWidget = nullptr;
    KDDockWidgets::Core::View *m_guest = nullptr;

    KDBindings::ConnectionHandle m_parentChangedConnection;
    KDBindings::ConnectionHandle m_minSizeChangedHandle;
    KDBindings::ConnectionHandle m_visibleChangedHandle;
    KDBindings::ScopedConnection m_layoutInvalidatedConnection;
    KDBindings::ScopedConnection m_guestDebugNameChangedConnection;
    KDBindings::ScopedConnection m_guestDestroyedConnection;
};

/// @brief And Item which can contain other Items
class DOCKS_EXPORT_FOR_UNIT_TESTS ItemContainer : public Item
{
    Q_OBJECT
public:
    explicit ItemContainer(KDDockWidgets::Core::View *hostWidget, ItemContainer *parent);
    explicit ItemContainer(KDDockWidgets::Core::View *hostWidget);
    ~ItemContainer();

    virtual void removeItem(Item *, bool hardRemove = true) = 0;
    virtual void restore(Item *child) = 0;
    virtual void onChildMinSizeChanged(Item *child) = 0;
    virtual void onChildVisibleChanged(Item *child, bool visible) = 0;

    int numVisibleChildren() const;
    int numChildren() const;
    bool hasChildren() const;
    bool hasVisibleChildren(bool excludeBeingInserted = false) const;
    const List childItems() const;
    bool isEmpty() const;
    bool contains(const Item *item) const;
    Item *itemForView(const KDDockWidgets::Core::View *) const;
    Item::List visibleChildren(bool includeBeingInserted = false) const;
    Item::List items_recursive() const;
    bool contains_recursive(const Item *item) const;
    int visibleCount_recursive() const override;
    int count_recursive() const;
    virtual void clear() = 0;

public:
    KDBindings::Signal<> itemsChanged;
    KDBindings::Signal<> numItemsChanged;
    KDBindings::Signal<int> numVisibleItemsChanged;

protected:
    bool hasSingleVisibleItem() const;
    Item::List m_children;

private:
    struct Private;
    Private *const d;
};

/// @brief A container for items which can either be vertical or horizontal
///
/// Similar analogy to QBoxLayout
class DOCKS_EXPORT_FOR_UNIT_TESTS ItemBoxContainer : public ItemContainer
{
    Q_OBJECT
public:
    explicit ItemBoxContainer(KDDockWidgets::Core::View *hostWidget, ItemContainer *parent);
    explicit ItemBoxContainer(KDDockWidgets::Core::View *hostWidget);
    ~ItemBoxContainer();
    void insertItem(Item *item, int index,
                    KDDockWidgets::InitialOption option = KDDockWidgets::DefaultSizeMode::Fair);
    void insertItem(Item *item, KDDockWidgets::Location, KDDockWidgets::InitialOption = {});

    static void
    insertItemRelativeTo(Item *item, Item *relativeTo, KDDockWidgets::Location,
                         KDDockWidgets::InitialOption = KDDockWidgets::DefaultSizeMode::Fair);

    void requestSeparatorMove(KDDockWidgets::Core::Separator *separator, int delta);
    int minPosForSeparator(KDDockWidgets::Core::Separator *, bool honourMax = true) const;
    int maxPosForSeparator(KDDockWidgets::Core::Separator *, bool honourMax = true) const;
    int minPosForSeparator_global(KDDockWidgets::Core::Separator *,
                                  bool honourMax = true) const;
    int maxPosForSeparator_global(KDDockWidgets::Core::Separator *,
                                  bool honourMax = true) const;
    void requestEqualSize(KDDockWidgets::Core::Separator *separator);
    void layoutEqually();
    void layoutEqually_recursive();
    void removeItem(Item *, bool hardRemove = true) override;
    Size minSize() const override;
    Size maxSizeHint() const override;
    Size availableSize() const;
    Q_REQUIRED_RESULT bool checkSanity() override;
    void dumpLayout(int level = 0, bool printSeparators = true) override;
    void setSize_recursive(
        Size newSize,
        ChildrenResizeStrategy strategy = ChildrenResizeStrategy::Percentage) override;
    bool hostSupportsHonouringLayoutMinSize() const;
    Rect suggestedDropRect(const Item *item, const Item *relativeTo,
                           KDDockWidgets::Location) const;
    void to_json(nlohmann::json &) const override;
    void fillFromJson(const nlohmann::json &,
                      const std::unordered_map<QString, KDDockWidgets::Core::View *> &) override;
    void clear() override;
    Qt::Orientation orientation() const;
    bool isVertical() const;
    bool isHorizontal() const;
    int length() const;
    bool hasOrientation() const;
    bool isOverflowing() const;

    /// @brief Returns the number of visible items layed-out horizontally or vertically
    /// But honours nesting
    int numSideBySide_recursive(Qt::Orientation) const;

    int availableLength() const;
    LengthOnSide lengthOnSide(const SizingInfo::List &sizes, int fromIndex, Side,
                              Qt::Orientation) const;
    int neighboursLengthFor(const Item *item, Side, Qt::Orientation) const;
    int neighboursLengthFor_recursive(const Item *item, Side, Qt::Orientation) const;
    int neighboursMinLengthFor(const Item *item, Side, Qt::Orientation) const;
    int neighboursMaxLengthFor(const Item *item, Side, Qt::Orientation) const;
    int availableToSqueezeOnSide(const Item *child, Side) const;
    int availableToGrowOnSide(const Item *child, Side) const;
    int availableToSqueezeOnSide_recursive(const Item *child, Side, Qt::Orientation) const;
    int availableToGrowOnSide_recursive(const Item *child, Side, Qt::Orientation) const;

private:
    int indexOfVisibleChild(const Item *) const;
    void restore(Item *) override;
    void restoreChild(Item *,
                      NeighbourSqueezeStrategy neighbourSqueezeStrategy =
                          NeighbourSqueezeStrategy::AllNeighbours);

    void setGeometry_recursive(Rect rect) override;

    ItemBoxContainer *convertChildToContainer(Item *leaf);
    bool hasOrientationFor(KDDockWidgets::Location) const;
    int usableLength() const;
    void setChildren(const Item::List &children, Qt::Orientation o);
    void setOrientation(Qt::Orientation);
    void updateChildPercentages();
    void updateChildPercentages_recursive();
    void updateWidgetGeometries() override;
    int oppositeLength() const;

    void layoutEqually(SizingInfo::List &sizes);

    ///@brief Grows the side1Neighbour to the right and the side2Neighbour to the left
    /// So they occupy the empty space that's between them (or bottom/top if Qt::Vertical).
    /// This is useful when an Item is removed. Its neighbours will occupy its space.
    /// side1Neighbour or side2Neighbour are allowed to be null, in which case the non-null one
    /// will occupy the entire space.
    void growNeighbours(Item *side1Neighbour, Item *side2Neighbour);

    ///@brief grows an item by @p amount. It calculates how much to grow on side1 and on side2
    /// Then calls growItem(item, side1Growth, side2Growth) which will effectively grow it,
    /// and shrink the neighbours which are donating the size.
    void growItem(Item *, int amount, GrowthStrategy,
                  NeighbourSqueezeStrategy neighbourSqueezeStrategy,
                  bool accountForNewSeparator = false,
                  ChildrenResizeStrategy = ChildrenResizeStrategy::Percentage);
    void growItem(int index, SizingInfo::List &sizes, int missing, GrowthStrategy,
                  NeighbourSqueezeStrategy neighbourSqueezeStrategy,
                  bool accountForNewSeparator = false);

    ///@brief Shrinks the neighbours of the item at @p index
    ///
    /// The neighbours at the left/top of the item, will be shrunk by @p side1Amount, while the
    /// items at right/bottom will be shrunk by @p side2Amount. Squeezes all the neighbours (not
    /// just the immediate ones).
    void shrinkNeighbours(int index, SizingInfo::List &sizes, int side1Amount, int side2Amount,
                          NeighbourSqueezeStrategy = NeighbourSqueezeStrategy::AllNeighbours);

    Item *visibleNeighbourFor(const Item *item, Side side) const;

    void onChildMinSizeChanged(Item *child) override;
    void onChildVisibleChanged(Item *child, bool visible) override;
    void updateSizeConstraints();
    SizingInfo::List sizes(bool ignoreBeingInserted = false) const;
    Vector<int> calculateSqueezes(SizingInfo::List::const_iterator begin,
                                  SizingInfo::List::const_iterator end, int needed,
                                  NeighbourSqueezeStrategy, bool reversed = false) const;
    Rect suggestedDropRectFallback(const Item *item, const Item *relativeTo,
                                   KDDockWidgets::Location) const;
    Item *itemAt(Point p) const;
    Item *itemAt_recursive(Point p) const;
    void setHostView(KDDockWidgets::Core::View *) override;
    void setIsVisible(bool) override;
    bool isVisible(bool excludeBeingInserted = false) const override;
    void setLength_recursive(int length, Qt::Orientation) override;
    void applyGeometries(const SizingInfo::List &sizes,
                         ChildrenResizeStrategy = ChildrenResizeStrategy::Percentage);
    void applyPositions(const SizingInfo::List &sizes);

    int indexOf(KDDockWidgets::Core::Separator *) const;
    bool isInSimplify() const;

public:
    Vector<KDDockWidgets::Core::Separator *> separators_recursive() const;
    Vector<KDDockWidgets::Core::Separator *> separators() const;

    /// Returns the separator for the specified child on the specified child
    /// Example:
    /// - If this layout is horizontal, and side is Side1, then the left separator is returned.
    /// - If this layout is horizontal, and side is Side2, then the right separator is returned.
    /// - top, bottom if vertical layout.
    /// @sa adjacentSeparatorForChild
    Core::Separator *separatorForChild(Item *child, Side side) const;

    /// Returns the separator for the specified child on the specified child
    /// Example:
    /// - If this layout is horizontal, and side is Side1, then the top separator is returned.
    /// - If this layout is horizontal, and side is Side2, then the bottom separator is returned.
    /// - left, right if vertical layout.
    /// @sa separatorForChild
    Core::Separator *adjacentSeparatorForChild(Item *child, Side side) const;

#ifdef DOCKS_DEVELOPER_MODE
    bool
    test_suggestedRect();
    void relayoutIfNeeded();
#endif

#ifdef DOCKS_DEVELOPER_MODE
public:
#else
private:
#endif
    void simplify();

    /// Puts the items in their respective places. i.e. lays them sequentially, spaced by 5px (separator thickness)
    /// does not resize.
    void positionItems();
    void positionItems_recursive();
    void positionItems(SizingInfo::List &sizes);

    static bool s_inhibitSimplify;
    friend class Core::Item;
    friend class ::TestMultiSplitter;
    struct Private;
    Private *const d;
};

/// QtQuick triggers a lot of resizes due to bindings being updated individually
/// Only check sanity at the end of an operation, and not each time a binding gets evaluated
/// Tests will fail with a warning if anything is wrong.
struct AtomicSanityChecks
{
    AtomicSanityChecks(Item *root)
        : m_oldValue(Item::s_silenceSanityChecks)
        , m_root(root)
    {
        Item::s_silenceSanityChecks = true;
    }

    ~AtomicSanityChecks()
    {
        Item::s_silenceSanityChecks = m_oldValue;
#ifdef DOCKS_DEVELOPER_MODE
        if (m_root) {
            const bool result = m_root->checkSanity();
            KDDW_UNUSED(result);
        }
#endif
    }

    const bool m_oldValue;
    Item *const m_root;
    KDDW_DELETE_COPY_CTOR(AtomicSanityChecks)
};

DOCKS_EXPORT void from_json(const nlohmann::json &, SizingInfo &);
DOCKS_EXPORT void to_json(nlohmann::json &, const SizingInfo &);
DOCKS_EXPORT void to_json(nlohmann::json &, Item *);

} // Core

} // KDDockWidgets
