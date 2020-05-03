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

//#include "docks_export.h" TODO

#include <QWidget>
#include <QPointer>

namespace Layouting {
class Anchor;

class /*DOCKS_EXPORT*/ Separator : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool isVertical READ isVertical CONSTANT)
public:
    explicit Separator(Layouting::Anchor *anchor, QWidget *hostWidget);
    bool isVertical() const;
    void move(int p);

protected:
    const QPointer<Layouting::Anchor> anchor() const { return m_anchor; }
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private:
    const QPointer<Layouting::Anchor> m_anchor; // QPointer so we don't dereference invalid point in paintEvent() when Anchor is deleted.
};

}

#endif
