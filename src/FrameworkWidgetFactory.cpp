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
#include "Utils_p.h"

#ifdef KDDOCKWIDGETS_QTWIDGETS
# include "indicators/ClassicIndicators_p.h"
# include "widgets/TabWidget_p.h"
# include "widgets/FrameWidget_p.h"
# include "widgets/TitleBarWidget_p.h"
# include "widgets/TabBarWidget_p.h"
# include "widgets/SideBarWidget_p.h"
# include "widgets/TabWidgetWidget_p.h"
# include "multisplitter/Separator_qwidget.h"
# include "widgets/FloatingWindowWidget_p.h"
# include "indicators/SegmentedIndicators_p.h"

# include <QRubberBand>
# include <QToolButton>
#else
# include "DockWidgetQuick.h"
# include "quick/FrameQuick_p.h"
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

SideBar *DefaultWidgetFactory::createSideBar(SideBarLocation loc, MainWindowBase *parent) const
{
    return new SideBarWidget(loc, parent);
}

QAbstractButton* DefaultWidgetFactory::createTitleBarButton(QWidget *parent, TitleBarButtonType type) const
{
    if (!parent) {
        qWarning() << Q_FUNC_INFO << "Parent not provided";
        return nullptr;
    }

    auto button = new Button(parent);
    button->setIcon(iconForButtonType(type, parent->devicePixelRatioF()));

    return button;
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

SideBar *DefaultWidgetFactory::createSideBar(SideBarLocation loc, MainWindowBase *parent) const
{
    Q_UNUSED(loc);
    Q_UNUSED(parent);

    qWarning() << Q_FUNC_INFO << "Not implemented yet";
    return nullptr;
}

#endif // QtQuick

// iconForButtonType impl is the same for QtQuick and QtWidgets
QIcon DefaultWidgetFactory::iconForButtonType(TitleBarButtonType type, qreal dpr) const
{
    QString iconName;
    switch (type) {
    case TitleBarButtonType::AutoHide:
        iconName = QStringLiteral("auto-hide");
        break;
    case TitleBarButtonType::UnautoHide:
        iconName = QStringLiteral("unauto-hide");
        break;
    case TitleBarButtonType::Close:
        iconName = QStringLiteral("close");
        break;
    case TitleBarButtonType::Minimize:
        iconName = QStringLiteral("min");
        break;
    case TitleBarButtonType::Maximize:
        iconName = QStringLiteral("max");
        break;
    case TitleBarButtonType::Normal:
        // We're using the same icon as dock/float
        iconName = QStringLiteral("dock-float");
        break;
    case TitleBarButtonType::Float:
        iconName = QStringLiteral("dock-float");
        break;
    }

    if (iconName.isEmpty())
        return {};

    QIcon icon(QStringLiteral(":/img/%1.png").arg(iconName));

#if QT_VERSION < QT_VERSION_CHECK(5, 15, 2)
    const bool isFractional = int(dpr) != dpr;
    if (isFractional) {
        // We don't support 1.5x yet.
        // Problem with Linux is that rendering is off due to a rounding bug only fixed in 5.15.2
        // Will enable for fractional later.
        // QTBUG-86170
        // Mostly affects Linux. Unless you're using Qt::HighDpiScaleFactorRoundingPolicy::PassThrough, in which case it will
        // affect other OSes too.
        return icon;
    }
#else
    // Not using Qt's sugar syntax, which doesn't support 1.5x anyway when we need it.
    // Simply add the high-res files and Qt will pick them when needed

    icon.addFile(QStringLiteral(":/img/%1-1.5x.png").arg(iconName));
    Q_UNUSED(dpr);
#endif
    icon.addFile(QStringLiteral(":/img/%1-2x.png").arg(iconName));

    return icon;
}
