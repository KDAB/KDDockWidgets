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

#ifndef KD_MULTISPLITTER_SEPARATOR_P_H
#define KD_MULTISPLITTER_SEPARATOR_P_H


#include "Item_p.h"

#include <QWidget>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QRubberBand;
QT_END_NAMESPACE

namespace Layouting {

typedef Separator* (*SeparatorFactoryFunc)(QWidget *parent);

class Separator : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool isVertical READ isVertical CONSTANT)
public:
    typedef QVector<Separator*> List;

    ~Separator();

    bool isVertical() const;
    void move(int p);
    Qt::Orientation orientation() const;
    bool lazyResizeEnabled() const;
    void setGeometry(int pos, int pos2, int length);
    void setGeometry(QRect r);
    int position() const;
    QWidget *hostWidget() const;

    void init(Layouting::ItemContainer*, Qt::Orientation orientation, SeparatorOptions options);

    ItemContainer *parentContainer() const;

    ///@brief Returns whether we're dragging a separator. Can be useful for the app to stop other work while we're not in the final size
    static bool isResizing();
    static void setSeparatorFactoryFunc(SeparatorFactoryFunc);
    static Separator* createSeparator(QWidget *host);

protected:
    explicit Separator(QWidget *hostWidget);
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
private:
    static bool s_isResizing;
    static Separator* s_separatorBeingDragged;
    void onMouseReleased();
    void setLazyPosition(int);
    bool isBeingDragged() const;
    Qt::Orientation m_orientation;
    QRect m_geometry;
    int m_lazyPosition = 0;
    SeparatorOptions m_options;
    bool m_lazyResize = false; // TODO
    QRubberBand *m_lazyResizeRubberBand = nullptr;
    ItemContainer *m_parentContainer = nullptr;
    // Only set when anchor is moved through mouse. Side1 if going towards left or top, Side2 otherwise.
    Layouting::Side m_lastMoveDirection = Side1;
};

}

#endif
