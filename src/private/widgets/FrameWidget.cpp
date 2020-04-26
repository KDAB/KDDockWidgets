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
 * @brief The GUI counterpart of Frame. Inherits Frame and implements paintEvent().
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "FrameWidget_p.h"
#include "../TitleBar_p.h"
#include "../TabWidget_p.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QTableWidget>
#include <QTabBar>

using namespace KDDockWidgets;

///@brieg a QVBoxLayout that emits layoutInvalidated so that Item can detect minSize changes
class VBoxLayout : public QVBoxLayout
{
public:
    explicit VBoxLayout(FrameWidget *parent)
        : QVBoxLayout(parent)
        , m_frameWidget(parent) {}
    ~VBoxLayout() override;

    void invalidate() override
    {
        QVBoxLayout::invalidate();
        m_frameWidget->layoutInvalidated();
    }

    FrameWidget *const m_frameWidget;
};

VBoxLayout::~VBoxLayout() = default;

FrameWidget::FrameWidget(QWidget *parent, FrameOptions options)
    : Frame(parent, options)
{
    auto vlayout = new VBoxLayout(this);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setSpacing(0);
    vlayout->addWidget(titleBar());
    vlayout->addWidget(tabWidget()->asWidget());
}

void FrameWidget::paintEvent(QPaintEvent *)
{
    if (!isFloating()) {
        QPainter p(this);
        QPen pen(QColor(184, 184, 184, 184));
        p.setPen(pen);
        p.drawRoundedRect(rect().adjusted(0, 0, -1, -1), 2, 2);
    }
}

QTabBar *FrameWidget::tabBar() const
{
    auto tw = static_cast<QTabWidget*>(tabWidget()->asWidget());
    return tw->tabBar();
}
