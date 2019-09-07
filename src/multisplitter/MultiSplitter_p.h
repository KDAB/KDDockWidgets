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

/**
 * @file
 * @brief A widget that supports an arbitrary number of splitters (called Separators) in any
 * combination of vertical/horizontal.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDDOCKWIDGETS_MULTISPLITTER_P_H
#define KDDOCKWIDGETS_MULTISPLITTER_P_H

#include "docks_export.h"
#include "QWidgetAdapter.h"

namespace KDDockWidgets {

class MultiSplitterLayout;
class MainWindowBase;
class FloatingWindow;

/**
 * @brief A widget that supports an arbitrary number of splitters (called Separators) in any
 * combination of vertical/horizontal.
 *
 * The actual layouting is done by @ref MultiSplitterLayout.
 */
class DOCKS_EXPORT_FOR_UNIT_TESTS MultiSplitter : public QWidgetAdapter
{
    Q_OBJECT
public:
    explicit MultiSplitter(QWidgetOrQuick *parent = nullptr);
    ~MultiSplitter() override;
    MultiSplitterLayout *multiSplitterLayout() const { return m_layout; }
    int count() const;
    bool isInMainWindow() const;
    MainWindowBase* mainWindow() const;
    FloatingWindow* floatingWindow() const;
protected:
    void onLayoutRequest() override;
    bool onResize(QSize newSize) override;
    MultiSplitterLayout *const m_layout;
private:
    bool m_inResizeEvent = false;
};

}

#endif
