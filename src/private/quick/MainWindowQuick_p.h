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

#ifndef KD_MAIN_WINDOW_QUICK_P_H
#define KD_MAIN_WINDOW_QUICK_P_H

#include "MainWindowBase.h"

namespace KDDockWidgets {

class MainWindowQuick : public MainWindowBase
{
    Q_OBJECT
    Q_PROPERTY(QString uniqueName READ uniqueName WRITE setUniqueName NOTIFY uniqueNameChanged)
    Q_PROPERTY(KDDockWidgets::DropAreaWithCentralFrame* dropArea READ dropArea WRITE setDropArea NOTIFY dropAreaChanged)
public:
    MainWindowQuick();
protected:
    DropAreaWithCentralFrame *dropArea() const override;
    void setDropArea(DropAreaWithCentralFrame*);
Q_SIGNALS:
    void dropAreaChanged();
private:
    DropAreaWithCentralFrame *m_dropArea = nullptr;
};

}

#endif
