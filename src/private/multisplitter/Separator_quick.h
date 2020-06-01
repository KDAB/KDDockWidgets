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

#ifndef KD_MULTISPLITTER_SEPARATOR_QUICK_H
#define KD_MULTISPLITTER_SEPARATOR_QUICK_H

#include "multisplitter_export.h"
#include "Separator_p.h"
#include "Widget_quick.h"

#include <QQuickItem>

namespace Layouting {

class MULTISPLITTER_EXPORT SeparatorQuick
        : public QQuickItem
        , public Layouting::Separator
        , public Layouting::Widget_quick
{
    Q_OBJECT
    Q_PROPERTY(bool isVertical READ isVertical NOTIFY isVerticalChanged)
public:
    explicit SeparatorQuick(Layouting::Widget *parent = nullptr);

    bool isVertical() const;

protected:
    Widget* createRubberBand(Widget *parent) override;
    Widget *asWidget() override;

public:
    // Interface with QML:
    Q_INVOKABLE void onMousePressed();
    Q_INVOKABLE void onMouseMoved(QPointF localPos);
    Q_INVOKABLE void onMouseReleased();
    Q_INVOKABLE void onMouseDoubleClicked();
Q_SIGNALS:
    // constant but it's only set after Separator::init
    void isVerticalChanged();
};

}

#endif
