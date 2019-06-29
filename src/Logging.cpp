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

#include "Logging_p.h"

void KDDockWidgets::setLoggingFilterRules()
{
    static QStringList loggingCategories = {
        QStringLiteral("kdab.docks.mouseevents"),
        QStringLiteral("kdab.docks.hiding"),
        QStringLiteral("kdab.docks.hovering"),
        QStringLiteral("kdab.docks.creation"),
        QStringLiteral("kdab.docks.docking"),
        QStringLiteral("kdab.multisplitter.anchors"),
        QStringLiteral("kdab.multisplitter.sizing"),
        QStringLiteral("kdab.multisplitter.multisplittercreation"),
        QStringLiteral("kdab.multisplitter.placeholder"),
        QStringLiteral("kdab.multisplitter.addwidget"),
        QStringLiteral("kdab.docks.state"),
        QStringLiteral("kdab.docks.overlay"),
        QStringLiteral("kdab.docks.dropping"),
        QStringLiteral("kdab.docks.title"),
        QStringLiteral("kdab.docks.closebutton"),
        QStringLiteral("kdab.docks.restoring"),
        QStringLiteral("kdab.docks.closing")
    };

    static QString filterRules;
    if (filterRules.isEmpty()) {
        for (const QString &cat : loggingCategories) {
            filterRules += cat + QStringLiteral("=false\n");
        }
        QLoggingCategory::setFilterRules(filterRules);
    }
}

Q_LOGGING_CATEGORY(creation, "kdab.docks.creation")
Q_LOGGING_CATEGORY(hovering, "kdab.docks.hovering")
Q_LOGGING_CATEGORY(mouseevents, "kdab.docks.mouseevents")
Q_LOGGING_CATEGORY(state, "kdab.docks.state")
Q_LOGGING_CATEGORY(docking, "kdab.docks.docking")
Q_LOGGING_CATEGORY(globalevents, "kdab.docks.globalevents")
Q_LOGGING_CATEGORY(hiding, "kdab.docks.hiding")
Q_LOGGING_CATEGORY(closing, "kdab.docks.closing")
Q_LOGGING_CATEGORY(overlay, "kdab.docks.overlay")
Q_LOGGING_CATEGORY(dropping, "kdab.docks.dropping")
Q_LOGGING_CATEGORY(restoring, "kdab.docks.restoring")
Q_LOGGING_CATEGORY(title, "kdab.docks.title")
Q_LOGGING_CATEGORY(closebutton, "kdab.docks.closebutton")
Q_LOGGING_CATEGORY(sizing, "kdab.multisplitter.sizing")
Q_LOGGING_CATEGORY(multisplittercreation, "kdab.multisplitter.multisplittercreation")
Q_LOGGING_CATEGORY(addwidget, "kdab.multisplitter.addwidget")
Q_LOGGING_CATEGORY(anchors, "kdab.multisplitter.anchors")
Q_LOGGING_CATEGORY(item, "kdab.multisplitter.item")
Q_LOGGING_CATEGORY(placeholder, "kdab.multisplitter.placeholder")
