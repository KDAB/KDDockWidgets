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


#include <QWidget>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QRubberBand;
QT_END_NAMESPACE

namespace Layouting {

class Config;
class ItemContainer;
class Separator;

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
    void setGeometry(int pos, int pos2, int length);
    void setGeometry(QRect r);
    int position() const;
    QWidget *hostWidget() const;

    void init(Layouting::ItemContainer*, Qt::Orientation orientation);

    ItemContainer *parentContainer() const;

    ///@brief Returns whether we're dragging a separator. Can be useful for the app to stop other work while we're not in the final size
    static bool isResizing();

protected:
    explicit Separator(QWidget *hostWidget);
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
private:
    friend class Config;

    void onMouseReleased();
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
