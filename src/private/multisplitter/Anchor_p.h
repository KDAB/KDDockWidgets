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

#include "Item_p.h"

#include <QObject>
#include <QPointer>
#include <QRect>
#include <QVector>

QT_BEGIN_NAMESPACE
class QRubberBand;
QT_END_NAMESPACE

namespace KDDockWidgets {
class MultiSplitterLayout;
}

namespace Layouting {

class Anchor : public QObject // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT

    Q_PROPERTY(QRect geometry READ geometry NOTIFY geometryChanged)
    Q_PROPERTY(Qt::Orientation orientation READ orientation CONSTANT)
public:

    enum class Option {
        None = 0,
        LazyResize
    };
    Q_DECLARE_FLAGS(Options, Option);

    typedef QVector<Anchor *> List;
    explicit Anchor(ItemContainer *parentContainer, Qt::Orientation orientation,
                    Options options, QWidget *hostWidget);

    ~Anchor() override;

    QWidget *hostWidget() const;

    Qt::Orientation orientation() const;
    void setGeometry(int pos, int pos2, int length);
    int position() const;

    ///@brief returns the separator widget
    Separator* separatorWidget() const;

    void setPositionOffset(int);
    bool isBeingDragged() const;

    bool lazyResizeEnabled() const;

    void onMousePress();
    void onMouseReleased();
    void onMouseMoved(QPoint pt);
    void onWidgetMoved(int p);

    QRect geometry() const;
    bool isVertical() const;

    ///@brief Returns whether we're dragging a separator. Can be useful for the app to stop other work while we're not in the final size
    static bool isResizing();
    static void setSeparatorFactoryFunc(SeparatorFactoryFunc);

Q_SIGNALS:
    void geometryChanged(QRect);

private:
    void setLazyPosition(int);
    void setGeometry(QRect);
    int position(QPoint) const;
    void setPosition(int p);

    const Qt::Orientation m_orientation;

    // Only set when anchor is moved through mouse. Side1 if going towards left or top, Side2 otherwise.
    Layouting::Side m_lastMoveDirection = Side1;

    QWidget *const m_hostWidget;
    static bool s_isResizing;
    static Anchor* s_separatorBeingDragged;

    Separator *const m_separatorWidget;
    QRect m_geometry;
    int m_lazyPosition = 0;
    const Options m_options;
    QRubberBand *const m_lazyResizeRubberBand;
    ItemContainer *const m_parentContainer;
};

}

#endif
