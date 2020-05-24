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

/**
 * @file
 * @brief A widget that supports an arbitrary number of splitters (called Separators) in any
 * combination of vertical/horizontal.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */


#include "MultiSplitter_p.h"
#include "MultiSplitterLayout_p.h"
#include "../Logging_p.h" // TODO
#include "MainWindowBase.h"
#include "FloatingWindow_p.h"
#include "LayoutSaver.h"

#include <QScopedValueRollback>

using namespace KDDockWidgets;

MultiSplitter::MultiSplitter(QWidgetOrQuick *parent)
    : QWidgetAdapter(parent)
    , Layouting::Widget_qwidget(this)
    , m_layout(new MultiSplitterLayout(this))
{
    connect(m_layout, &MultiSplitterLayout::minimumSizeChanged, this, [this] (QSize sz) {
        setMinimumSize(sz);
    });

    connect(m_layout, &MultiSplitterLayout::sizeChanged, this, [this] (QSize sz) {
        if (!m_inResizeEvent && !LayoutSaver::restoreInProgress())
            resize(sz);
    });

    setMinimumSize(m_layout->minimumSize());
}

MultiSplitter::~MultiSplitter()
{
}

void MultiSplitter::onLayoutRequest()
{
    m_layout->updateSizeConstraints();
}

bool MultiSplitter::onResize(QSize newSize)
{
    qCDebug(sizing) << Q_FUNC_INFO << "; new=" << newSize
                    << "; window=" << window();

    QScopedValueRollback<bool>(m_inResizeEvent, true); // to avoid re-entrancy

    if (!LayoutSaver::restoreInProgress()) {
        // don't resize anything while we're restoring the layout
        m_layout->setSize(newSize);
    }

    return false; // So QWidget::resizeEvent is called
}

bool MultiSplitter::isInMainWindow() const
{
    return mainWindow() != nullptr;
}

MainWindowBase *MultiSplitter::mainWindow() const
{
    if (auto pw = QWidget::parentWidget()) {
        // Note that if pw is a FloatingWindow then pw->parentWidget() can be a MainWindow too, as it's parented
        if (pw->objectName() == QLatin1String("MyCentralWidget"))
            return qobject_cast<MainWindowBase*>(pw->parentWidget());
    }

    return nullptr;
}

FloatingWindow *MultiSplitter::floatingWindow() const
{
    return qobject_cast<FloatingWindow*>(QWidget::parentWidget());
}
