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

#include "multisplitter_export.h"

#include <QObject>
#include <QPoint>

namespace Layouting {

class Config;
class ItemContainer;
class Separator;
class Widget;

class MULTISPLITTER_EXPORT Separator
{
public:
    typedef QVector<Separator*> List;

    virtual ~Separator();

    bool isVertical() const;
    void move(int p);
    Qt::Orientation orientation() const;
    void setGeometry(int pos, int pos2, int length);
    void setGeometry(QRect r);
    int position() const;
    QObject *host() const;

    void init(Layouting::ItemContainer*, Qt::Orientation orientation);

    ItemContainer *parentContainer() const;

    ///@brief Returns whether we're dragging a separator. Can be useful for the app to stop other work while we're not in the final size
    static bool isResizing();
    virtual Widget* asWidget() = 0;

protected:
    explicit Separator(Widget *hostWidget);
    virtual Widget* createRubberBand(Widget *parent) { Q_UNUSED(parent); return nullptr; }
    void onMousePress();
    void onMouseReleased();
    void onMouseDoubleClick();
    void onMouseMove(QPoint pos);
private:
    friend class Config;

    void setLazyPosition(int);
    bool isBeingDragged() const;
    bool usesLazyResize() const;
    static bool s_isResizing;
    static Separator* s_separatorBeingDragged;
    struct Private;
    Private *const d;
};

}

#endif
