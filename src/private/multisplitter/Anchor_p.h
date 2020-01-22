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

#ifndef KD_MULTISPLITTER_ANCHOR_P_H
#define KD_MULTISPLITTER_ANCHOR_P_H

#include "docks_export.h"
#include "LayoutSaver_p.h"

#include <QObject>
#include <QPointer>
#include <QRect>
#include <QVector>

QT_BEGIN_NAMESPACE
class QRubberBand;
QT_END_NAMESPACE

namespace KDDockWidgets {

class Item;
class MultiSplitterLayout;
class Separator;

typedef QVector<Item*> ItemList;

/**
 * @brief An anchor is the vertical or horizontal (@ref orientation()) line that has an handle
 * so you can resize widgets with your mouse.
 *
 * A MultiSplitter comes with 4 static anchors (@ref isStatic()), that represent the top, left, right
 * and bottom borders. A static anchor means it can't change position, doesn't display the handle and
 * will have the same lifetime has the MultiSplitter.
 *
 * Each anchor has two properties indicating in which anchor it starts and where it ends, @ref from(), to().
 * For example, the top static horizontal anchor starts at the left anchor and ends at the right static anchor.
 * If this anchor is vertical, then from()/to() return horizontal anchors, and vice-versa.
 *
 * An anchor has a length, which is to()->pos() - from()->pos(). The length of a vertical anchor is,
 * thus, its vertical extent (Likewise for horizontal anchors).
 *
 * An anchor controls two groups of widgets: side1 and side2 widgets. When an anchor is dragged with mouse
 * it will resize those widgets. The widgets always start or end at the position where the anchor lives.
 * For vertical anchors, side1 means "the widgets at its left" and side2 means "the widgets at its right",
 * Same principle for horizontal anchors, but for top/bottom instead.
 * Static anchors only have 1 side with widgets. For example the left static anchor only has widgets at its
 * right, so side1Widgets is empty.
 * Non-static anchors, always have side1 and side2 widgets. If not then they are considered unneeded
 * and are deleted.
 *
 * Example:
 *
 * +--------------------+
 * |          |         |
 * |          |         |
 * |          |         |
 * | Foo      |   Bar   |
 * |          |         |
 * |          |         |
 * +--------------------+
 *
 * In the above example we have 5 anchors. 4 of them are static (left, right, top, bottom) and there's
 * a non-static one, in the middle. It's vertical, and can be dragged left and right, resizing its
 * side1Widgets (Foo) and side2Widgets (Bar). This non-static anchors has from=top anchor, and to=bottom anchor.
 *
 */
class DOCKS_EXPORT_FOR_UNIT_TESTS Anchor : public QObject // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT

    // properties for GammaRay
    Q_PROPERTY(KDDockWidgets::ItemList side1Items READ side1Items NOTIFY itemsChanged)
    Q_PROPERTY(KDDockWidgets::ItemList side2Items READ side2Items NOTIFY itemsChanged)

    Q_PROPERTY(QString debug_side1ItemNames READ debug_side1ItemNames NOTIFY debug_itemNamesChanged)
    Q_PROPERTY(QString debug_side2ItemNames READ debug_side2ItemNames NOTIFY debug_itemNamesChanged)

    Q_PROPERTY(Anchor* from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(Anchor* to READ to WRITE setTo NOTIFY toChanged)
    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(Qt::Orientation orientation READ orientation CONSTANT)
    Q_PROPERTY(Anchor *followee READ followee NOTIFY followeeChanged)
public:
    ///@brief represents the Anchor type
    ///An anchor can be of 2 types:
    /// - Normal: Anchor that can be resized via mouse
    /// - static: this is the top, left, right, bottom borders of the main window. They are called static because they don't move.
    enum Type {
        Type_None = 0, ///< The anchor is normal, and can be resized.
        Type_LeftStatic = 1,   ///< The anchor is static and represents the left mainwindow margin
        Type_RightStatic = 2,  ///< The anchor is static and represents the right mainwindow margin
        Type_TopStatic = 4,    ///< The anchor is static and represents the top mainwindow margin
        Type_BottomStatic = 8, ///< The anchor is static and represents the bottom mainwindow margin
        Type_Static = Type_TopStatic | Type_LeftStatic | Type_RightStatic | Type_BottomStatic ///< The anchor is static, one of the 4 previous ones
    };
    Q_ENUM(Type)

    enum Side {
        Side_None = 0,
        Side1,
        Side2
    };
    Q_ENUM(Side)

    enum SetPositionOption {
        SetPositionOption_None = 0,
        SetPositionOption_DontRecalculatePercentage = 1
    };
    Q_DECLARE_FLAGS(SetPositionOptions, SetPositionOption)

    typedef QVector<Anchor *> List;
    explicit Anchor(Qt::Orientation orientation, MultiSplitterLayout *multiSplitter, Type = Type_None);
    ~Anchor() override;
    static Anchor* deserialize(const LayoutSaver::Anchor &, MultiSplitterLayout *layout);
    LayoutSaver::Anchor serialize() const;

    void setFrom(Anchor *);
    Anchor *from() const { return m_from; }
    Anchor *to() const { return m_to; }
    void setTo(Anchor *);
    Qt::Orientation orientation() const;
    void addItem(Item *, Side);
    void addItems(const ItemList &list, Side);
    void removeItem(Item *w);
    void removeItems(Side);
    bool isVertical() const { return m_orientation == Qt::Vertical; }
    void setPosition(int p, SetPositionOptions = SetPositionOption_None);
    void updatePositionPercentage();
    int position() const;

    void setVisible(bool);
    qreal positionPercentage() const { return m_positionPercentage; }

    void ensureBounded();

    /**
     * @brief Sets the new layout. Called when we're dropping a source layout into a target one.
     * The target one will steal the separators of the source one.
     */
    void setLayout(MultiSplitterLayout *);

    ///@brief returns the separator widget
    Separator* separatorWidget() const;

    /**
     * Returns how far left or top an anchor can go and still respecting it's Side1 widgets min-size.
     * This function doesn't count with shifting other anchors, for that use MultiSplitterLayout::boundPositionsForAnchor()
     * which is is recursive and returns the bounds after simulating that intermediary anchors to the left/top were
     * also resized (each still respecting widgets min sizes though).
     */
    int minPosition() const;

    /**
     * A squeeze is a widget's width (or height for horizontal anchors) minus its minimum width.
     * This function iterates through all widgets of the specified side and returns the minimum
     * available squeeze.
     */
    int smallestAvailableItemSqueeze(Anchor::Side) const;

    /**
     * @brief The length of this anchor. The distance between @ref from and @ref to.
     * @return the anchor's length
     */
    int length() const;

    /**
     * @brief Checks if this anchor is valid. It's valid if @ref from and @ref to are non-null, and not the same.
     * @return true if this anchor is valid.
     */
    bool isValid() const;

    /**
     * @brief The width of a vertical anchor, or height of an horizontal anchor.
     */
    int thickness() const;

    /**
     * @brief Checks if this Anchor is static.
     * @return true if this Anchor is static.
     */
    bool isStatic() const { return m_type & Type_Static; }

    bool isUnneeded() const { return !isStatic() && (!hasItems(Side1) || !hasItems(Side2)); }
    bool isEmpty() const { return !hasItems(Side1) && !hasItems(Side2); }
    bool hasItems(Side) const;
    bool hasNonPlaceholderItems(Side) const;
    bool onlyHasPlaceholderItems(Anchor::Side side) const;

    /**
     * @brief Returns whether this Anchor should follow another one. That happens if one of it's side is empty or only has placeholders
     * Also, it can't be a static anchor.
     */
    bool shouldFollow() const { return !isStatic() && (onlyHasPlaceholderItems(Side1) || onlyHasPlaceholderItems(Side2)); }

    bool containsItem(const Item *w, Side side) const;
    bool isStaticOrFollowsStatic() const;

    const ItemList items(Side side) const;
    const ItemList side1Items() const { return m_side1Items; }
    const ItemList side2Items() const { return m_side2Items; }

    void consume(Anchor *other);
    void consume(Anchor *other, Side);
    void swapItems(Anchor *other);
    void removeAllItems();

    static Anchor *createFrom(Anchor *other, Item *relativeTo = nullptr);
    void setPositionOffset(int);
    bool isBeingDragged() const;

    Type type() const { return m_type; }

    int cumulativeMinLength(Anchor::Side side) const;

    /**
     * @brief Makes this separator follow another one. This one will be made invisible.
     * Used when the item in the layout is just a placeholder remembering a previous dock widget position.
     * Pass nullptr do make it not follow and visible again.
     */
    void setFollowee(Anchor *);

    /**
     * @brief getter for the followee
     */
    Anchor *followee() const { return m_followee; }

    /**
     * @brief Returns the list of anchors following this one.
     */
    const List followers() const;

    /**
     * @brief Returns the last followee in the chain.
     */
    Anchor *endFollowee() const;

    /**
     * @brief Recursively looks for an anchor in the whole layout but only looking at side @p side
     *
     * This allows us to know if there's an anchor on the top or left of us (side1) or right or bottom
     * (side2), in the whole layout.
     *
     * Returns false if @p anchor is nullptr
     */
    bool findAnchor(Anchor *anchor, Side side) const;

    /**
     * @brief Returns the nearest Anchor with non-placeholder items on side @p side
     * If nothing is found then returns the static anchor on that side
     */
    Anchor *findNearestAnchorWithItems(Side side) const;

    ///@brief removes the side1 and side2 items. Doesn't delete them
    void clear();

    static int thickness(bool staticAnchor);
    static Anchor::Side oppositeSide(Side side);
    void onFolloweePositionChanged(int pos);
    bool isFollowing() const { return m_followee != nullptr; }

    void onMousePress();
    void onMouseReleased();
    void onMouseMoved(QPoint pt);
    void onWidgetMoved(int p);


    ///@brief Returns whether we're dragging a separator. Can be useful for the app to stop other work while we're not in the final size
    static bool isResizing();

private:
    struct CumulativeMin {
        int minLength = 0;
        int numItems = 0;
        CumulativeMin& operator+=(CumulativeMin other) {
            minLength += other.minLength;
            numItems += other.numItems;
            return *this;
        }
    };
    CumulativeMin cumulativeMinLength_recursive(Anchor::Side side) const;

    void setThickness();
    void setLazyPosition(int);

Q_SIGNALS:
    void positionChanged(int pos);
    void itemsChanged(Anchor::Side);
    void fromChanged();
    void toChanged();
    void debug_itemNamesChanged();
    void followeeChanged();
    void thicknessChanged();

public:
    int position(QPoint) const;
    void updateSize();
    void updateItemSizes();
    void debug_updateItemNames();
    QString debug_side1ItemNames() const;
    QString debug_side2ItemNames() const;
    void setGeometry(QRect);
    QRect geometry() const { return m_geometry; }

    const Qt::Orientation m_orientation;
    ItemList m_side1Items;
    ItemList m_side2Items;
    QPointer<Anchor> m_from;// QPointer just so we can assert. They should never be null.
    QPointer<Anchor> m_to;
    const Type m_type;
    qreal m_positionPercentage = 0.0;

    // Only set when anchor is moved through mouse. Side1 if going towards left or top, Side2 otherwise.
    Side m_lastMoveDirection = Side_None;

    MultiSplitterLayout *m_layout = nullptr;
    bool m_showingSide1Rubberband = false;
    bool m_showingSide2Rubberband = false;
    bool m_initialized = false;
    static bool s_isResizing;
    static const QString s_magicMarker; // Just to validate serialize is symmetric to deserialize

    // For when being animated. They are not displayed at their pos, but with an offset.
    int m_positionOffset = 0;

    QString m_debug_side1ItemNames;
    QString m_debug_side2ItemNames;
    Separator *const m_separatorWidget;
    QRect m_geometry;
    Anchor *m_followee = nullptr;
    QMetaObject::Connection m_followeeDestroyedConnection;
    const bool m_lazyResize;
    int m_lazyPosition = 0;
    QRubberBand *const m_lazyResizeRubberBand;
};

}

Q_DECLARE_METATYPE(KDDockWidgets::ItemList)
Q_DECLARE_METATYPE(KDDockWidgets::Item*)

#endif
