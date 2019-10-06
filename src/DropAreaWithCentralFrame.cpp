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

#include "DropAreaWithCentralFrame_p.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"

using namespace KDDockWidgets;

DropAreaWithCentralFrame::DropAreaWithCentralFrame(QWidgetOrQuick *parent, MainWindowOptions options)
    : DropArea(parent)
    , m_centralFrame(createCentralFrame(options))
{
    if (m_centralFrame)
        m_layout->addWidget(m_centralFrame, KDDockWidgets::Location_OnTop, {});
}

DropAreaWithCentralFrame::~DropAreaWithCentralFrame()
{
}

Frame* DropAreaWithCentralFrame::createCentralFrame(MainWindowOptions options)
{
    return (options & MainWindowOption_HasCentralFrame) ? Config::self().frameworkWidgetFactory()->createFrame(nullptr, Frame::Option_IsCentralFrame | Frame::Option_AlwaysShowsTabs)
                                                        : nullptr;
}
