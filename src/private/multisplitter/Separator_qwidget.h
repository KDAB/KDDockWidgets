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

#ifndef KD_MULTISPLITTER_SEPARATORWIDGET_P_H
#define KD_MULTISPLITTER_SEPARATORWIDGET_P_H

#include "../../docks_export.h"
#include "Separator_p.h"

QT_BEGIN_NAMESPACE
class QPaintEvent;
QT_END_NAMESPACE

namespace Layouting {

class DOCKS_EXPORT SeparatorWidget : public Layouting::Separator
{
    Q_OBJECT
public:
    explicit SeparatorWidget(Layouting::Widget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *) override;
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
    Widget* createRubberBand(Widget *parent) override;
};

}

#endif
