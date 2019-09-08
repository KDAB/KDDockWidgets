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

#ifndef KD_TITLEBARQUICK_P_H
#define KD_TITLEBARQUICK_P_H

#include "../docks_export.h"
#include "../TitleBar_p.h"



namespace KDDockWidgets {

class DockWidget;
class Frame;

class DOCKS_EXPORT TitleBarQuick : public TitleBar
{
    Q_OBJECT
public:
    explicit TitleBarQuick(Frame *parent);
    explicit TitleBarQuick(FloatingWindow *parent);
    ~TitleBarQuick() override;

    ///@brief getter for the close button
    //QWidget* closeButton() const;

protected:
    /*void paintEvent(QPaintEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
    void updateFloatButton() override;
    void updateCloseButton() override;*/
//
};



}

#endif
