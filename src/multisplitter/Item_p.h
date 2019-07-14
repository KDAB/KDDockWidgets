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

#ifndef KD_MULTISPLITTER_ITEM_P_H
#define KD_MULTISPLITTER_ITEM_P_H

#include "docks_export.h"
#include "Anchor_p.h"

#include <QRect>
#include <QObject>

/**
 * @brief Implements an item that you put into a multi-splitter.
 * For now it just wraps a KDDockWidgets::Frame, but could eventually be used in QML.
 */
namespace KDDockWidgets {

struct AnchorGroup;
class MultiSplitterLayout;
class Frame;
class DockWidget;

struct GeometryDiff
{
    explicit GeometryDiff(QRect oldGeo, QRect newGeo)
        : leftDiff(newGeo.left() - oldGeo.left())
        , topDiff(newGeo.top() - oldGeo.top())
        , rightDiff(newGeo.right() - oldGeo.right())
        , bottomDiff(newGeo.bottom() - oldGeo.bottom())
        , onlyOneSideChanged([this]{
                int numChanged = 0;
                if (leftDiff != 0)
                    numChanged++;
                if (topDiff != 0)
                    numChanged++;
                if (rightDiff != 0)
                    numChanged++;
                if (bottomDiff != 0)
                    numChanged++;
                return numChanged == 1;
           }()) // Lambda just so we can have onlyOneChanged as const
    {
    }

    // Orientation of the Anchor that provoked the geometry diff
    Qt::Orientation orientation() const
    {
        if (leftDiff || rightDiff)
            return Qt::Vertical;

        return Qt::Horizontal;
    }

    int delta() const
    {
        // Since we only use GeometryDiff when only 1 side changed, just sum them all
        return leftDiff + rightDiff + topDiff + bottomDiff;
    }

    int signess() const
    {
        return delta() > 0 ? 1: -1;
    }

    const int leftDiff;
    const int topDiff;
    const int rightDiff;
    const int bottomDiff;
    const bool onlyOneSideChanged;
};

class DOCKS_EXPORT_FOR_UNIT_TESTS Item : public QObject // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_PROPERTY(bool isPlaceholder READ isPlaceholder NOTIFY isPlaceholderChanged)
    Q_PROPERTY(QRect geometry READ geometry NOTIFY geometryChanged)
    Q_PROPERTY(QSize minimumSize READ minimumSize NOTIFY minimumSizeChanged)
public:
    explicit Item(Frame *frame, MultiSplitterLayout *parent);
    ~Item() override;

    int x() const;
    int y() const;
    QPoint pos() const;
    int position(Qt::Orientation) const;
    QSize size() const;
    int width() const;
    int height() const;
    bool isVisible() const;
    void setVisible(bool);

    void setGeometry(QRect);

    void beginBlockPropagateGeo();
    void endBlockPropagateGeo();

    QRect geometry() const;
    bool eventFilter(QObject *, QEvent *) override;

    Frame* frame() const;
    QWidget *window() const;
    QWidget *parentWidget() const;

    MultiSplitterLayout *layout() const;
    void setLayout(MultiSplitterLayout *w); // TODO: Make the widget children of this one?

    /**
     * Returns the width of the widget if orientation is Vertical, the height otherwise.
     */
    int length(Qt::Orientation) const;
    int minLength(Qt::Orientation orientation) const;

    Anchor *anchorAtSide(Anchor::Side side, Qt::Orientation orientation) const;
    Anchor *anchor(const GeometryDiff &) const;
    AnchorGroup& anchorGroup();
    const AnchorGroup& anchorGroup() const;

    int cumulativeMinLength(Anchor::Side, Qt::Orientation orientation) const;

    QSize minimumSize() const;

    bool isPlaceholder() const;
    void setIsPlaceholder(bool);
    /**
     * @brief Returns whether this item lives in a @ref MainWindow, as opposed to a @ref FloatingWindow
     */
    bool isInMainWindow() const;

    ///@brief turns the placeholder into a normal Item again showing @p dockWidget
    void restorePlaceholder(DockWidget *dockWidget, int tabIndex);

    void ref();
    void unref();
    int refCount() const; // for tests
Q_SIGNALS:
    void frameChanged();
    void geometryChanged();
    void isPlaceholderChanged();
    void minimumSizeChanged();
private:
    class Private;
    Private *const d;
};

}

#endif
