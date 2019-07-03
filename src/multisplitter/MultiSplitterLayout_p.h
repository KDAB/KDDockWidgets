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

/**
 * @file
 * @brief A class to layout widgets in any place relative to another widget.
 *
 * Widgets can be inserted to the left,right,top,bottom in relation to another widget or in relation
 * to the window. Each two neighbour widgets have a separator in between, which the user can use
 * to resize.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_MULTISPLITTER_LAYOUT_P_H
#define KD_MULTISPLITTER_LAYOUT_P_H

#include "Anchor_p.h"
#include "AnchorGroup_p.h"
#include "docks_export.h"
#include "KDDockWidgets.h"
#include "Item_p.h"
#include "Frame_p.h"

#include <QLoggingCategory>
#include <QPointer>

namespace KDDockWidgets {

class MultiSplitterWidget;

/**
 * Returns the width of the widget if orientation is Vertical, the height otherwise.
 */
template <typename T>
inline int widgetLength(const T *w, Qt::Orientation orientation)
{
    return (orientation == Qt::Vertical) ? w->width() : w->height();
}

/**
 * Returns the widget's min-width if orientation is Vertical, the min-height otherwise.
 */
template <typename T>
inline int widgetMinLength(const T *w, Qt::Orientation orientation)
{
    int min = 0;
    if (orientation == Qt::Vertical) {
        if (w->minimumWidth() > 0)
            min = w->minimumWidth();
        else
            min = w->minimumSizeHint().width();
    } else {
        if (w->minimumHeight() > 0)
            min = w->minimumHeight();
        else
            min = w->minimumSizeHint().height();
    }

    return qMax(min, 0);
}

/**
 * A MultiSplitter is like a QSplitter but supports mixing vertical and horizontal splitters in
 * any combination.
 *
 * It supports adding a widget to the left/top/bottom/right of the whole MultiSplitter or adding
 * relative to a single widget.
 *
 * A MultiSplitter is simply a list of Anchors, each one of them handling the resizing of widgets.
 * See the documentation for Anchor.
 */
class DOCKS_EXPORT_FOR_UNIT_TESTS MultiSplitterLayout : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY widgetCountChanged)
    Q_PROPERTY(int visibleCount READ visibleCount NOTIFY widgetCountChanged) // This notify isn't ogood enough, but it's just for debug, we're calling QMetaProperty::read to debug
    Q_PROPERTY(int placeholderCount READ placeholderCount NOTIFY widgetCountChanged) // This notify isn't ogood enough, but it's just for debug, we're calling QMetaProperty::read to debug
    Q_PROPERTY(QSize contentsSize READ contentsSize NOTIFY contentsSizeChanged)
    Q_PROPERTY(QSize minimumSize READ minimumSize NOTIFY minimumSizeChanged)
public:

    /**
     * @brief Constructor. MultiSplitterLayout is created by MultiSplitterWidget only.
     */
    explicit MultiSplitterLayout(MultiSplitterWidget *parent);
    ~MultiSplitterLayout() override;

    /**
     * @brief returns the widget that this layout manages
     */
    MultiSplitterWidget *parentWidget() const;

    /**
     * @brief Adds a widget to this MultiSplitter.
     */
    void addWidget(QWidget *widget, KDDockWidgets::Location location, Frame *relativeTo = nullptr);

    /**
     * Adds an entire MultiSplitterWidget into this layout. The donor MultiSplitterWidget will be deleted
     * after all its Frames are stolen. All added Frames will preserve their original layout, so,
     * if widgetFoo was at the left of widgetBar when in the donor splitter, then it will still be at left
     * of widgetBar when the whole splitter is dropped into this one.
     */
    void addMultiSplitter(MultiSplitterWidget *splitter, KDDockWidgets::Location location,
                          Frame *relativeTo = nullptr);

    /**
     * @brief Removes an item from this MultiSplitter.
     */
    void removeItem(Item *item);

    /**
     * @brief Returns true if this layout contains the specified item.
     */
    bool contains(const Item *) const;

    /**
     * @brief Returns the visible Item at pos @p p.
     */
    Item *itemAt(QPoint p) const;

    /**
     *  @brief Removes all items.
     */
    void clear();

    /**
     * @brief Returns the number of Item objects in this layout.
     * This includes non-visible (placeholder) Items too.
     * @sa visibleCount
     */
    int count() const { return m_items.size(); }

    /**
     * @brief Returns the number of visible Items in this layout.
     * Which is @ref count minus @ref placeholderCount
     * @sa count
     */
    int visibleCount() const;

    /**
     * @brief Returns the number of placeholder items in this layout.
     * This is the same as @ref count minus @ref visibleCount
     * @sa count, visibleCount
     */
    int placeholderCount() const;

    /**
     * @brief Returns true if count is 0.
     */
    bool isEmpty() const { return m_items.isEmpty(); }

    /**
     * @brief If @p orientation is Qt::Horizontal, returns the height, otherwise the width.
     */
    int length(Qt::Orientation orientation) const;

    /**
     * @brief The list of items in this layout.
     */
    const ItemList items() const;

    /**
     * Called by the indicators, so they draw the drop rubber band at the correct place.
     * The rect for the rubberband when dropping a widget at the specified location.
     * Excludes the Anchor thickness, result is actually smaller than what needed. In other words,
     * the result will be exactly the same as the geometry the widget will get.
     */
    QRect rectForDrop(const QWidget *widget, KDDockWidgets::Location location, const Item *relativeTo) const;

    void setAnchorBeingDragged(Anchor *);
    Anchor *anchorBeingDragged() const { return m_anchorBeingDragged; }
    bool anchorIsBeingDragged() const { return m_anchorBeingDragged != nullptr; }

    ///@brief returns list of separators
    const Anchor::List anchors() const { return m_anchors; }

    ///@brief returns either the left, top, right or bottom separator, depending on the @p type
    Anchor *staticAnchor(Anchor::Type type) const;

    ///@brief a function that all code paths adding Items will call.
    ///It's mostly for code reuse, so we don't duplicate what's done here. But it's also nice to
    ///have a central place that we know will be called
    void addItems_internal(const ItemList &, bool updateConstraints = true);

    /**
     * @brief returns the extra useless space
     * FloatingWindow for example must make space for its title bar, so that space isn't available
     * for adding widgets.
     * If @p orientation is Qt::Horizontal, returns the useless height, otherwise width.
     */
    int extraUselessSpace(Qt::Orientation orientation) const;

    /**
     * @brief setter for the @ref extraUselessSpace
     * @sa extraUselessSpace
     */
    void setExtraUselessSpace(QSize);

    /**
     * @brief Updates the min size of this layout.
     */
    void updateSizeConstraints();

    /**
     * @brief setter for the contents size
     * The "contents size" is just the size() of this layout. However, since resizing
     * QWidgets is async and we need it to be sync. As sometimes adding widgets will increase
     * the MultiSplitterLayout size (due to widget's min-size constraints).
     */
    void setContentsSize(QSize);

    /**
     * @brief sets either the contents height if @p o is Qt::Horizontal, otherwise sets the contents width
     */
    void setContentLength(Qt::Orientation o, int value);

    /**
     * @brief returns the contents width.
     * Usually it's the same width as the respective parent MultiSplitterWidget.
     */
    int contentsWidth() const { return m_contentSize.width(); }

    /**
     * @brief returns the contents height.
     * Usually it's the same height as the respective parent MultiSplitterWidget.
     */
    int contentsHeight() const { return m_contentSize.height(); }

    /**
     * @brief returns the layout's minimum size
     * @ref setMinimumSize
     */
    QSize minimumSize() const { return m_minSize; }

    /**
     * @brief getter for the contents size
     */
    QSize contentsSize() const { return m_contentSize; }

    // For debug/hardening
    bool validateInputs(QWidget *widget, KDDockWidgets::Location location, const Item *relativeToItem) const;
    // For debug/hardening

    enum AnchorSanityOption {
        AnchorSanity_Normal = 0,
        AnchorSanity_Intersections = 1,
        AnchorSanity_WidgetMinSizes = 2,
        AnchorSanity_WidgetInvalidSizes = 4,
        AnchorSanity_All = AnchorSanity_Intersections | AnchorSanity_WidgetMinSizes | AnchorSanity_WidgetInvalidSizes,
    };
    Q_ENUM(AnchorSanityOption)

    bool checkSanity(AnchorSanityOption o = AnchorSanity_All) const;

    void restorePlaceholder(Item *item);

    /**
     * @brief Removes unneeded placeholder items when adding new frames.
     *
     * A floating frame A might have a placeholder in the main window (for example to remember it's position on the Left),
     * but then the user might attach it to the right, so the left placeholder is no longer need.
     * Right before adding the frame to the right we remove the left placeholder, otherwise it's unrefed while we're adding
     * causing a segfault. So what this does is making the unrefing happen a bit earlier.
     */
    void unrefOldPlaceholders(const Frame::List &framesBeingAdded) const;

    // For debug
    void dumpDebug() const;
    /**
     * @brief returns the Item that holds @p frame in this layout
     */
    Item *itemForFrame(const Frame *frame) const;

    /**
     * @brief returns the frames contained in @p frameOrMultiSplitter
     * If frameOrMultiSplitter is a Frame, it returns a list of 1 element, with that frame
     * If frameOrMultiSplitter is a MultiSplitterLayout then it returns a list of all frames it contains
     */
    Frame::List framesFrom(QWidget *frameOrMultiSplitter) const;

    /**
     * @brief Returns a list of Frame objects contained in this layout
     */
    Frame::List frames() const;

    /**
     * @brief Returns a list of DockWidget objects contained in this layout
     */
    QVector<DockWidget*> dockWidgets() const;

Q_SIGNALS:
    ///@brief emitted when the number of widgets changes
    ///@param count the new widget count
    void widgetCountChanged(int count);

    void visibleWidgetCountChanged(int count);

    ///@brief emitted when a widget is added
    ///@param item the item containing the new widget
    void widgetAdded(KDDockWidgets::Item *item);

    ///@brief emitted when a widget is removed
    ///@param item the item containing the removed widget
    void widgetRemoved(KDDockWidgets::Item *item);

    ///@brief emitted right before dumping debug
    ///@sa dumpDebug
    void aboutToDumpDebug() const; // clazy:exclude=const-signal-or-slot

    ///@brief emitted when the contentsSize changes
    ///@sa contentsSize
    void contentsSizeChanged();

    ///@brief emitted when the minimumSize changes
    ///@sa minimumSize
    void minimumSizeChanged();

public:
    bool eventFilter(QObject *o, QEvent *e) override;
    AnchorGroup anchorsForPos(QPoint pos) const;
    AnchorGroup staticAnchorGroup() const;
    Anchor::List anchors(Qt::Orientation, bool includeStatic = false, bool includePlaceholders = true) const;
    Anchor *newAnchor(AnchorGroup &group, KDDockWidgets::Location location);
    friend QDebug operator<<(QDebug d, const AnchorGroup &group);

    void setDoSanityChecks(bool);

private:
    friend struct AnchorGroup;
    friend class Item;
    friend class Anchor;
    friend class TestDocks;

    struct AnchorBounds {
        Anchor *side1;
        Anchor *side2;
    };

    struct Length {
        int side1Length = 0;
        int side2Length = 0;
        int length() const { return side1Length + side2Length; }

        void setLength(int newLength)
        {
            // Sets the new length, preserving proportion
            side1Length = int(side1Factor() * newLength);
            side2Length = newLength - side1Length;
        }

        bool isNull() const
        {
            return length() <= 0;
        }

    private:
        qreal side1Factor() const
        {
            return (1.0 * side1Length) / length();
        }
    };

    /**
     * @brief setter for the minimum size
     * @ref minimumSize
     */
    void setMinimumSize(QSize);

    void emitVisibleWidgetCountChanged();

    /**
     * Returns the size that the widget will get when dropped at this specific location.
     * When location is Left or Right then the length represents a width, otherwise an height.
     * This function is also called to know the size of the rubberband when hovering over a location.
     */
    MultiSplitterLayout::Length lengthForDrop(const QWidget *widget, KDDockWidgets::Location location,
                                              const Item *relativeTo) const;
    void insertAnchor(Anchor *);
    void removeAnchor(Anchor *);

    /**
     * Returns the min or max position that an anchor can go to (due to minimum size restriction on the widgets).
     * For example, if the anchor is vertical and direction is Side1 then it returns the minimum x
     * that the anchor can have. If direction is Side2 then it returns the maximum width. If horizontal
     * then the height.
     */
    int boundPositionForAnchor(Anchor *, Anchor::Side direction) const;

    /**
     * Similar to boundPositionForAnchor, but returns both the min and the max width (or height)
     */
    QPair<int, int> boundPositionsForAnchor(Anchor *) const;

    /** Returns how much is available for the new drop. It already counts with the space for new anchor that will be created.
     * So it returns the contentWidth (or height), minus the minimum-sizes of all widgets, minus the thickness of all anchors
     * minus the thickness of the anchor that would be created.
     **/
    Length availableLengthForDrop(KDDockWidgets::Location location, const Item *relativeTo) const;

    /**
     * @brief Like @ref availableLengthForDrop but just returns the total available width or height (depending on @p orientation)
     * So no need to receive any location.
     * @param orientation If Qt::Vertical then returns the available width. Height otherwise.
     */
    int availableLengthForOrientation(Qt::Orientation orientation) const;

    /**
     * Removes the widgets associated with oldAnchor and gives them to newAnchor.
     * Called when removing a widget results in unneeded anchors.
     */
    void updateAnchorsFromTo(Anchor *oldAnchor, Anchor *newAnchor);

    /**
     * Positions the static anchors at their correct places. Called when the MultiSplitter is resized.
     * left and top anchor are at position 0, while right/bottom are at position= width/height.
     * (Approx, due to styling margins and whatnot)
     */
    void positionStaticAnchors();

    /**
     * When this MultiSplitter is resized, it gives or steals the less/extra space evenly through
     * all widgets.
     **/
    void redistributeSpace(QSize oldSize, QSize newSize);
    void redistributeSpace_recursive(Anchor *fromAnchor);

    /**
     * Returns the width (if orientation = Horizontal), or height that is occupied by anchors.
     * For example, an horizontal anchor has 2 or 3 px of width, so that's space that can't be
     * occupied by child widgets.
     */
    int wastedSpacing(Qt::Orientation) const;

    /**
     * Called by addWidget().
     * If you drop a 100px in the middle of a layout, it will steal some space from the left widgets
     * and still some space from the right ones. delta1 is the space stolen at the left
     * delta2 is the space stolen at the right. The sum of delta1+delta2 is the size of the widget
     * (plus the splitter). Then we propagate the resize, so that all widgets chip in and get smaller
     * to make room for ours.
     */
    void propagateResize(int delta, Anchor *fromAnchor, Anchor::Side direction);

    // Helper function for propagateResize()
    void collectPaths(QVector<Anchor::List> &paths, Anchor *fromAnchor, Anchor::Side direction);


    // convenience for the unit-tests
    // Moves the widget's bottom or right anchor, to resize it.
    void resizeItem(Frame *frame, int newSize, Qt::Orientation);

    Anchor::List m_anchors;

    Anchor *const m_leftAnchor;
    Anchor *const m_topAnchor;
    Anchor *const m_rightAnchor;
    Anchor *const m_bottomAnchor;

    ItemList m_items;
    bool m_inDestructor = false;
    bool m_beingMergedIntoAnotherMultiSplitter = false;
    bool m_doSanityChecks = true;

    QSize m_minSize = QSize(0, 0);
    AnchorGroup m_staticAnchorGroup;

    QPointer<Anchor> m_anchorBeingDragged;
    QSize m_contentSize;
    QSize m_extraUselessSpace = {0, 0};
};

inline QDebug operator<<(QDebug d, const AnchorGroup &group) {
    d << "AnchorGroup: top=" << group.top << "; left=" << group.left
      << "; right=" << group.right << "; bottom=" << group.bottom;
    return d;
}
}

#endif
