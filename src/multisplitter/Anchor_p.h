/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, Author: Sérgio Martins <sergio.martins@kdab.com>

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

#include <QWidget>
#include <QLoggingCategory>
#include <QPointer>

namespace KDDockWidgets {

class Item;
class MultiSplitter;

typedef QVector<Item*> ItemList;

/**
 * An anchor is the vertical or horizontal (@ref orientation()) line that has an handle
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
class DOCKS_EXPORT_FOR_UNIT_TESTS Anchor : public QWidget
{
    Q_OBJECT

    // properties for GammaRay
    Q_PROPERTY(ItemList side1Items READ side1Items NOTIFY itemsChanged)
    Q_PROPERTY(ItemList side2Items READ side2Items NOTIFY itemsChanged)

    Q_PROPERTY(QString debug_side1ItemNames READ debug_side1ItemNames NOTIFY debug_itemNamesChanged)
    Q_PROPERTY(QString debug_side2ItemNames READ debug_side2ItemNames NOTIFY debug_itemNamesChanged)

    Q_PROPERTY(Anchor* from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(Anchor* to READ to WRITE setTo NOTIFY toChanged)
    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)
public:
    enum Option {
        Option_None = 0,
        Option_LeftStatic = 1,
        Option_RightStatic = 2,
        Option_TopStatic = 4,
        Option_BottomStatic = 8,
        Option_Static = Option_TopStatic | Option_LeftStatic | Option_RightStatic | Option_BottomStatic
    };
    Q_ENUM(Option)

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
    typedef int Options;
    explicit Anchor(Qt::Orientation orientation, MultiSplitter *multiSplitter, Options = Option_None);
    ~Anchor() override;
    int pos() const;

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
    int position() const;
    qreal positionPercentage() const { return m_positionPercentage; }

    /**
     * Returns how far left or top an anchor can go and still respecting it's Side1 widgets min-size.
     * This function doesn't count with shifting other anchors, for that use MultiSplitter::boundPositionsForAnchor()
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


    int length() const;
    bool isValid() const;

    /**
     * @brief The width of a vertical anchor, or height of an horizontal anchor.
     */
    int thickness() const;

    bool isStatic() const { return m_options & Option_Static; }

    bool isUnneeded() const { return !isStatic() && (!hasItems(Side1) || !hasItems(Side2)); }
    bool isEmpty() const { return !hasItems(Side1) && !hasItems(Side2); }
    bool hasItems(Side) const;

    bool containsItem(const Item *w, Side side) const;

    ItemList items(Side side) const;
    ItemList side1Items() const { return m_side1Items; }
    ItemList side2Items() const { return m_side2Items; }

    void consume(Anchor *other);
    void consume(Anchor *other, Side);
    void swapItems(Anchor *other);
    void removeAllItems();

    static Anchor *createFrom(Anchor *other, Item *relativeTo = nullptr);
    void setPositionOffset(int);
    bool isBeingDragged() const;

    Options options() const { return m_options; }

    int cumulativeMinLength(Anchor::Side side) const;

    static int thickness(bool staticAnchor);
    static Anchor::Side oppositeSide(Side side);
protected:
    void paintEvent(QPaintEvent *) override;
    void moveEvent(QMoveEvent *) override;
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
    bool event(QEvent *) override;

    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

Q_SIGNALS:
    void positionChanged(int pos);
    void itemsChanged(Anchor::Side);
    void fromChanged();
    void toChanged();
    void debug_itemNamesChanged();

public:
    void move(int);
    int position(QPoint) const;
    void updateSize();
    void updateRubberBandGeometries();
    void updateItemSizes();
    void debug_updateItemNames();
    QString debug_side1ItemNames() const;
    QString debug_side2ItemNames() const;

    const Qt::Orientation m_orientation;
    ItemList m_side1Items;
    ItemList m_side2Items;
    QPointer<Anchor> m_from;// QPointer just so we can assert. They should never be null.
    QPointer<Anchor> m_to;
    const Options m_options;
    int m_position = 0;
    qreal m_positionPercentage = 0.0;

    // Only set when anchor is moved through mouse. Side1 if going towards left or top, Side2 otherwise.
    Side m_lastMoveDirection = Side_None;

    MultiSplitter *m_multiSplitter = nullptr;
    bool m_showingSide1Rubberband = false;
    bool m_showingSide2Rubberband = false;
    bool m_initialized = false;

    // For when being animated. They are not displayed at their pos, but with an offset.
    int m_positionOffset = 0;

    QString m_debug_side1ItemNames;
    QString m_debug_side2ItemNames;
};
}

#endif
