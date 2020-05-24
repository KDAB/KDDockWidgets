/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "FrameworkWidgetFactory.h"
#include "Frame_p.h"
#include "TitleBar_p.h"
#include "TabWidget_p.h"
#include "multisplitter/Separator_p.h"
#include "FloatingWindow_p.h"
#include "Config.h"

#ifdef KDDOCKWIDGETS_QTWIDGETS
# include "indicators/ClassicIndicators_p.h"
# include "widgets/FrameWidget_p.h"
# include "widgets/TitleBarWidget_p.h"
# include "widgets/TabBarWidget_p.h"
# include "widgets/TabWidgetWidget_p.h"
# include "widgets/SeparatorWidget_p.h"
# include "widgets/FloatingWindowWidget_p.h"
#else
# include "quick/FrameQuick_p.h"
# include "quick/DockWidgetQuick.h"
# include "quick/TitleBarQuick_p.h"
# include "quick/TabBarQuick_p.h"
# include "quick/TabWidgetQuick_p.h"
# include "quick/FloatingWindowQuick_p.h"
# include "quick/SeparatorQuick_p.h"
#endif

using namespace KDDockWidgets;

FrameworkWidgetFactory::~FrameworkWidgetFactory()
{
}

#ifdef KDDOCKWIDGETS_QTWIDGETS
Frame *DefaultWidgetFactory::createFrame(QWidgetOrQuick *parent, FrameOptions options) const
{
    return new FrameWidget(parent, options);
}

TitleBar *DefaultWidgetFactory::createTitleBar(Frame *frame) const
{
    return new TitleBarWidget(frame);
}

TitleBar *DefaultWidgetFactory::createTitleBar(FloatingWindow *fw) const
{
    return new TitleBarWidget(fw);
}

TabBar *DefaultWidgetFactory::createTabBar(TabWidget *parent) const
{
    return new TabBarWidget(parent);
}

TabWidget *DefaultWidgetFactory::createTabWidget(Frame *parent) const
{
    return new TabWidgetWidget(parent);
}

Layouting::Separator *DefaultWidgetFactory::createSeparator(Layouting::Widget *parent) const
{
    return new SeparatorWidget(parent);
}

FloatingWindow *DefaultWidgetFactory::createFloatingWindow(MainWindowBase *parent) const
{
    return new FloatingWindowWidget(parent);
}

FloatingWindow *DefaultWidgetFactory::createFloatingWindow(Frame *frame, MainWindowBase *parent) const
{
    return new FloatingWindowWidget(frame, parent);
}

DropIndicatorOverlayInterface *DefaultWidgetFactory::createDropIndicatorOverlay(DropArea *dropArea) const
{
    return new ClassicIndicators(dropArea);
}
#else

Frame *DefaultWidgetFactory::createFrame(QWidgetOrQuick *parent, Frame::Options options) const
{
    return new FrameQuick(parent, options);
}

TitleBar *DefaultWidgetFactory::createTitleBar(Frame *frame) const
{
    return new TitleBarQuick(frame);
}

TitleBar *DefaultWidgetFactory::createTitleBar(FloatingWindow *fw) const
{
    return new TitleBarQuick(fw);
}

TabBar *DefaultWidgetFactory::createTabBar(TabWidget *tb) const
{
    return new TabBarQuick(tb);
}

TabWidget *DefaultWidgetFactory::createTabWidget(Frame *frame) const
{
    return new TabWidgetQuick(frame);
}

Separator *DefaultWidgetFactory::createSeparator(QWidgetAdapter *parent) const
{
    return new SeparatorQuick(parent);
}

FloatingWindow *DefaultWidgetFactory::createFloatingWindow(QWidgetOrQuick *parent) const
{
    return new FloatingWindowQuick(parent);
}

FloatingWindow *DefaultWidgetFactory::createFloatingWindow(Frame *frame, QWidgetOrQuick *parent) const
{
    return new FloatingWindowQuick(frame, parent);
}

DropIndicatorOverlayInterface *DefaultWidgetFactory::createDropIndicatorOverlay(DropArea *) const
{
    return nullptr;
}
#endif
