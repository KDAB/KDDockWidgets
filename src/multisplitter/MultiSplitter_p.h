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

#ifndef KD_MULTISPLITTER_MULTISPLITTER_P_H
#define KD_MULTISPLITTER_MULTISPLITTER_P_H

#include "Anchor_p.h"
#include "AnchorGroup_p.h"
#include "docks_export.h"
#include "KDDockWidgets.h"
#include "Item_p.h"

#include <QWidget>
#include <QLoggingCategory>
#include <QPointer>

namespace KDDockWidgets {

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
class DOCKS_EXPORT_FOR_UNIT_TESTS MultiSplitter : public QWidget
{
    Q_OBJECT
public:
    explicit MultiSplitter(QWidget *parent = nullptr);
    ~MultiSplitter() override;

    /**
     * Adds a widget to this MultiSplitter.
     */
    void addWidget(QWidget *widget, KDDockWidgets::Location location, QWidget *relativeTo = nullptr);

    /**
     * Adds an entire MultiSplitter into this MultiSplitter. The donor MultiSplitter will be deleted
     * after all its widgets are stolen. All added widgets will preserve their original layout, so,
     * if widgetFoo was at the left of widgetBar when in the donor splitter, then it will still be at left
     * of widgetBar when the whole splitter is dropped into this one.
     */
    void addMultiSplitter(MultiSplitter *splitter, KDDockWidgets::Location location,
                          QWidget *relativeTo = nullptr);

    /**
     * Removes a widget from this MultiSplitter.
     */
    void removeItem(Item *widget);

    /**
     * Returns true if this MultiSplitter contains the specified widget.
     * The widget must have been added with addWidget/addMultiSplitter.
     */
    bool contains(Item *) const;

    /**
     * Returns the child widget at pos p.
     * The widget must have been added with addWidget/addMultiSplitter.
     */
    Item *itemAt(QPoint p) const;

    /**
     * Removes all child widgets.
     */
    void clear();

    /**
     * Returns the number of child widgets.
     * Only the ones added through addWidget/addMultiSplitter. So any internal/helper widget
     * such as Anchors are ignored.
     */
    int count() const { return m_items.size(); }
    /**
     * Returns true if count is 0.
     */
    bool isEmpty() const { return m_items.isEmpty(); }
    int visibleCount() const;
    int length(Qt::Orientation) const;

    /**
     * The list of child widgets added through addWidget/addMultiSplitter.
     */
    const ItemList items() const;

    /**
     * Called by the indicators, so they draw the drop rubber band at the correct place.
     * The rect for the rubberband when dropping a widget at the specified location.
     * Excludes the Anchor thickness, result is actually smaller than what needed. In other words,
     * the result will be exactly the same as the geometry the widget will get.
     */
    QRect rectForDrop(const QWidget *widget, KDDockWidgets::Location location, Item *relativeTo) const;

    void setAnchorBeingDragged(Anchor *);
    Anchor *anchorBeingDragged() const { return m_anchorBeingDragged; }
    bool anchorIsBeingDragged() const { return m_anchorBeingDragged != nullptr; }
    const Anchor::List anchors() const { return m_anchors; }
    Anchor *staticAnchor(Anchor::Type) const;
    void addItems_internal(const ItemList &, bool updateConstraints = true);


    /**
     * FloatingWindow for example must make space for its title bar, so that space isn't available
     * for adding widgets.
     */
    void setExtraUselessSpace(QSize);
    int extraUselessSpace(Qt::Orientation) const;

    /**
     * Updates the min size of this MultiSplitter.
     */
    void updateSizeConstraints();

    /**
     * The "contents size" is just the size() of the MultiSplitter. However, since resizing
     * QWidgets is async and we need it to be sync. As sometimes adding widgets will increase
     * the MultiSplitter size (due to widget's min-size constraints).
     * Also, we might abstract multiSplitter and make it work for QML.
     */
    void setContentsSize(QSize);
    void setContentLength(Qt::Orientation o, int value);
    int contentsWidth() const { return m_contentSize.width(); }
    int contentsHeight() const { return m_contentSize.height(); }

    // For debug/hardening
    bool validateInputs(QWidget *widget, KDDockWidgets::Location location, Item *relativeTo) const;
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

    // For debug
    void dumpDebug() const;
    Item *itemForWidget(const QWidget *w) const;

Q_SIGNALS:
    void widgetCountChanged(int count);
    void visibleWidgetCountChanged(int count);
    void widgetAdded(KDDockWidgets::Item*);
    void aboutToDumpDebug() const; // clazy:exclude=const-signal-or-slot

protected:
    void resizeEvent(QResizeEvent *) override;
    bool event(QEvent *) override;
    AnchorGroup anchorsForPos(QPoint pos) const;
    AnchorGroup staticAnchorGroup() const;
    Anchor::List anchors(Qt::Orientation, bool includeStatic = false) const;
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

    void emitVisibleWidgetCountChanged();

    /**
     * Returns the size that the widget will get when dropped at this specific location.
     * When location is Left or Right then the length represents a width, otherwise an height.
     * This function is also called to know the size of the rubberband when hovering over a location.
     */
    MultiSplitter::Length lengthForDrop(const QWidget *widget, KDDockWidgets::Location location,
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
     * So ir returns the contentWidth (or height), minus the minimum-sizes of all widgets, minus the thickness of all anchors
     * minus the thickness of the anchor that would be created.
     **/
    Length availableLengthForDrop(KDDockWidgets::Location location, const Item *relativeTo) const;

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
    void resizeItem(QWidget *widget, int newSize, Qt::Orientation);

    Anchor::List m_anchors;

    Anchor *const m_leftAnchor;
    Anchor *const m_topAnchor;
    Anchor *const m_rightAnchor;
    Anchor *const m_bottomAnchor;

    ItemList m_items;
    bool m_inDestructor = false;
    bool m_beingMergedIntoAnotherMultiSplitter = false;
    bool m_doSanityChecks = true;

    int m_minHeight = 0;
    int m_minWidth = 0;
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
