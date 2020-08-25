/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "FrameworkWidgetFactory.h"
#include "Frame_p.h"
#include "TitleBar_p.h"
#include "multisplitter/Separator_p.h"
#include "FloatingWindow_p.h"
#include "Config.h"
#include "indicators/ClassicIndicators_p.h"

#ifdef KDDOCKWIDGETS_QTWIDGETS
# include "indicators/ClassicIndicators_p.h"
# include "widgets/TabWidget_p.h"
# include "widgets/FrameWidget_p.h"
# include "widgets/TitleBarWidget_p.h"
# include "widgets/TabBarWidget_p.h"
# include "widgets/TabWidgetWidget_p.h"
# include "multisplitter/Separator_qwidget.h"
# include "widgets/FloatingWindowWidget_p.h"
# include "indicators/SegmentedIndicators_p.h"
# include <QRubberBand>
#else
# include "quick/FrameQuick_p.h"
# include "quick/DockWidgetQuick.h"
# include "quick/TitleBarQuick_p.h"
# include "quick/FloatingWindowQuick_p.h"
# include "multisplitter/Separator_quick.h"
#endif

using namespace KDDockWidgets;

DropIndicatorType DefaultWidgetFactory::s_dropIndicatorType = DropIndicatorType::Classic;

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
    return new Layouting::SeparatorWidget(parent);
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
    switch (s_dropIndicatorType) {
    case DropIndicatorType::Classic:
        return new ClassicIndicators(dropArea);
    case DropIndicatorType::Segmented:
        return new SegmentedIndicators(dropArea);
    }

    return new ClassicIndicators(dropArea);
}

QWidgetOrQuick *DefaultWidgetFactory::createRubberBand(QWidgetOrQuick *parent) const
{
    return new QRubberBand(QRubberBand::Rectangle, parent);
}

#else

Frame *DefaultWidgetFactory::createFrame(QWidgetOrQuick *parent, FrameOptions options) const
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

/*Separator *DefaultWidgetFactory::createSeparator(QWidgetAdapter *parent) const
{
    return new SeparatorQuick(parent);
}*/

FloatingWindow *DefaultWidgetFactory::createFloatingWindow(MainWindowBase *parent) const
{
    return new FloatingWindowQuick(parent);
}

FloatingWindow *DefaultWidgetFactory::createFloatingWindow(Frame *frame, MainWindowBase *parent) const
{
    return new FloatingWindowQuick(frame, parent);
}

DropIndicatorOverlayInterface *DefaultWidgetFactory::createDropIndicatorOverlay(DropArea *dropArea) const
{
    return new ClassicIndicators(dropArea);
}

TabBar *DefaultWidgetFactory::createTabBar(TabWidget *parent) const
{
    Q_UNUSED(parent)
    Q_ASSERT(false);
    return nullptr;
}

TabWidget *DefaultWidgetFactory::createTabWidget(Frame *parent) const
{
    Q_UNUSED(parent)
    Q_ASSERT(false);
    return nullptr;
}

Layouting::Separator *DefaultWidgetFactory::createSeparator(Layouting::Widget *parent) const
{
    return new Layouting::SeparatorQuick(parent);
}

QWidgetOrQuick *DefaultWidgetFactory::createRubberBand(QWidgetOrQuick *parent) const
{
    return new QWidgetOrQuick(parent);
}

#endif
