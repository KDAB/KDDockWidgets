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

#ifndef KD_MULTISPLITTER_MULTISPLITTERWIDGET_P_H
#define KD_MULTISPLITTER_MULTISPLITTERWIDGET_P_H

#include "docks_export.h"
#include <QWidget>

namespace KDDockWidgets {

class MultiSplitterLayout;

/**
 * @brief A widget that supports an arbitrary number of splitters (called Separators) in any
 * combination of vertical/horizontal.
 *
 * The actual layouting is done by @ref MultiSplitterLayout.
 */
class DOCKS_EXPORT_FOR_UNIT_TESTS MultiSplitterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MultiSplitterWidget(QWidget *parent = nullptr);
    ~MultiSplitterWidget() override;
    MultiSplitterLayout *multiSplitter() const { return m_layout; }
    int count() const;
protected:
    bool event(QEvent *e) override;
    void resizeEvent(QResizeEvent *) override;
    MultiSplitterLayout *const m_layout;
private:
    friend class MultiSplitterLayout;
    bool m_inResizeEvent = false;
};


}

#endif
