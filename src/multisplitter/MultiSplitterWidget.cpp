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

#include "MultiSplitterWidget_p.h"
#include "MultiSplitter_p.h"
#include "Logging_p.h"

#include <QResizeEvent>

using namespace KDDockWidgets;

MultiSplitterWidget::MultiSplitterWidget(QWidget *parent)
    : QWidget(parent)
    , m_layout(new MultiSplitter(this))
{
}

MultiSplitterWidget::~MultiSplitterWidget()
{

}

int MultiSplitterWidget::count() const
{
    return m_layout->count();
}

void MultiSplitterWidget::resizeEvent(QResizeEvent *ev)
{
    qCDebug(sizing) << Q_FUNC_INFO << "; new=" << ev->size() << "; old=" << ev->oldSize();

    m_layout->setContentsSize(ev->size());
    QWidget::resizeEvent(ev);
}

bool MultiSplitterWidget::event(QEvent *e)
{
    if (e->type() == QEvent::LayoutRequest)
        m_layout->updateSizeConstraints();

    return QWidget::event(e);
}
