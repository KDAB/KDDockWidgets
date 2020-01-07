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

#include "docks_export.h"
#include "QWidgetAdapter.h"

#include <QPointer>

namespace KDDockWidgets {
class Anchor;

class DOCKS_EXPORT Separator : public QWidgetAdapter
{
    Q_OBJECT
    Q_PROPERTY(bool isVertical READ isVertical CONSTANT)
    Q_PROPERTY(bool isStatic READ isStatic CONSTANT)
    //Q_PROPERTY(int position READ position NOTIFY positionChanged)
public:
    explicit Separator(Anchor *anchor, QWidgetAdapter *parent = nullptr);
    bool isVertical() const;
    bool isStatic() const;
    int position() const;
    void move(int p);
    const QPointer<Anchor> anchor() const { return m_anchor; }

protected:
    void onMousePress() override;
    void onMouseMove(QPoint globalPos) override;
    void onMouseRelease() override;

private:
    const QPointer<Anchor> m_anchor; // QPointer so we don't dereference invalid point in paintEvent() when Anchor is deleted.
};

}

#endif
