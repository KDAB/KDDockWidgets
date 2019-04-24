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

#ifndef KD_DOCK_LOGGING_P_H
#define KD_DOCK_LOGGING_P_H

#include <QLoggingCategory>

namespace KDDockWidgets {
void setLoggingFilterRules();
}


Q_DECLARE_LOGGING_CATEGORY(hovering)
Q_DECLARE_LOGGING_CATEGORY(creation)
Q_DECLARE_LOGGING_CATEGORY(mouseevents)
Q_DECLARE_LOGGING_CATEGORY(state)
Q_DECLARE_LOGGING_CATEGORY(docking)
Q_DECLARE_LOGGING_CATEGORY(globalevents)
Q_DECLARE_LOGGING_CATEGORY(hiding)
Q_DECLARE_LOGGING_CATEGORY(closing)
Q_DECLARE_LOGGING_CATEGORY(overlay)
Q_DECLARE_LOGGING_CATEGORY(dropping)
Q_DECLARE_LOGGING_CATEGORY(restoring)
Q_DECLARE_LOGGING_CATEGORY(title)
Q_DECLARE_LOGGING_CATEGORY(closebutton)
Q_DECLARE_LOGGING_CATEGORY(sizing)
Q_DECLARE_LOGGING_CATEGORY(multisplittercreation)
Q_DECLARE_LOGGING_CATEGORY(addwidget)
Q_DECLARE_LOGGING_CATEGORY(anchors)
Q_DECLARE_LOGGING_CATEGORY(item)

#endif
