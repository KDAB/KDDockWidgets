/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "FrameworkWidgetFactory_qtquick.h"
#include "Config.h"

#include "private/indicators/ClassicIndicators_p.h"
#include "private/indicators/NullIndicators_p.h"
#include "private/Utils_p.h"

#include "controllers/TabBar.h"
#include "controllers/Stack.h"
#include "controllers/FloatingWindow.h"

#include "private/indicators/SegmentedIndicators_p.h"

// #include "qtquick/views/FloatingWindow_qtquick.h"
#include "qtquick/views/DockWidget_qtquick.h"
#include "qtquick/views/DropArea_qtquick.h"
#include "qtquick/views/Frame_qtquick.h"
#include "qtquick/views/View_qtquick.h"
#include "qtquick/views/Separator_qtquick.h"
#include "qtquick/views/TitleBar_qtquick.h"
#include "qtquick/views/TabBar_qtquick.h"
// #include "qtquick/views/SideBar_qtquick.h"
#include "qtquick/views/Stack_qtquick.h"
// #include "qtquick/views/MainWindow_qtquick.h"
#include "qtquick/views/MDILayout_qtquick.h"



// clazy:excludeall=ctor-missing-parent-argument

using namespace KDDockWidgets;


DefaultWidgetFactory_qtquick::~DefaultWidgetFactory_qtquick()
{
}

View *DefaultWidgetFactory_qtquick::createMainWindow(Controllers::MainWindow *, View *, Qt::WindowFlags) const
{
    return {};
    // return new Views::MainWindow_qtquick(mainWindow, parent ? static_cast<Views::View_qtwidgets<QMainWindow> *>(parent) : nullptr, flags);
}

View *DefaultWidgetFactory_qtquick::createDockWidget(Controllers::DockWidget *, Qt::WindowFlags) const
{
    return {};
    // return new Views::DockWidget_qtquick(dw, flags);
}

View *DefaultWidgetFactory_qtquick::createFrame(Controllers::Frame *, View *,
                                                FrameOptions) const
{
    // TODOv2: Remove options
    return {};
    // return new Views::Frame_qtquick(controller, Views::View_qtwidgets<QWidget>::asQWidget(parent));
}

View *DefaultWidgetFactory_qtquick::createTitleBar(Controllers::TitleBar *, Controllers::Frame *) const
{
    return {};
    // return new Views::TitleBar_qtquick(titleBar, Views::View_qtwidgets<QWidget>::asQWidget(frame));
}

View *DefaultWidgetFactory_qtquick::createTitleBar(Controllers::TitleBar *, Controllers::FloatingWindow *) const
{
    return {};
    // return new Views::TitleBar_qtquick(titleBar, Views::View_qtwidgets<QWidget>::asQWidget(fw));
}

View *DefaultWidgetFactory_qtquick::createTabBar(Controllers::TabBar *, View *) const
{
    return {};
    // return new Views::TabBar_qtquick(tabBar, Views::View_qtwidgets<QWidget>::asQWidget(parent));
}

View *DefaultWidgetFactory_qtquick::createTabWidget(Controllers::Stack *, Controllers::Frame *) const
{
    return {};
    // return new Views::Stack_qtquick(controller, parent);
}

View *DefaultWidgetFactory_qtquick::createSeparator(Controllers::Separator *controller, View *parent) const
{
    return new Views::Separator_qtquick(controller, parent ? static_cast<Views::View_qtquick *>(parent) : nullptr);
}

View *DefaultWidgetFactory_qtquick::createFloatingWindow(Controllers::FloatingWindow *,
                                                         Controllers::MainWindow *, Qt::WindowFlags) const
{
    return {};
    // auto mainwindow = qobject_cast<QMainWindow *>(Views::View_qtwidgets<QWidget>::asQWidget(parent));
    // return new Views::FloatingWindow_qtquick(controller, mainwindow, windowFlags);
}

DropIndicatorOverlayInterface *DefaultWidgetFactory_qtquick::createDropIndicatorOverlay(Controllers::DropArea *dropArea) const
{
#ifdef Q_OS_WASM
    // On WASM windows don't support translucency, which is required for the classic indicators.
    return new SegmentedIndicators(dropArea);
#endif

    switch (s_dropIndicatorType) {
    case DropIndicatorType::Classic:
        return new ClassicIndicators(dropArea);
    case DropIndicatorType::Segmented:
        return new SegmentedIndicators(dropArea);
    case DropIndicatorType::None:
        return new NullIndicators(dropArea);
    }

    return new ClassicIndicators(dropArea);
}

View *DefaultWidgetFactory_qtquick::createRubberBand(View *) const
{
    return {};
    // return new QRubberBand(QRubberBand::Rectangle, parent ? qobject_cast<QWidget *>(parent->asQObject()) : nullptr);
}

View *DefaultWidgetFactory_qtquick::createSideBar(Controllers::SideBar *,
                                                  Controllers::MainWindow *) const
{
    return {};
    // return new Views::SideBar_qtquick(controller, Views::View_qtwidgets<QWidget>::asQWidget(parent));
}

// iconForButtonType impl is the same for QtQuick and QtWidgets
QIcon DefaultWidgetFactory_qtquick::iconForButtonType(TitleBarButtonType type, qreal dpr) const
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
    if (!scalingFactorIsSupported(dpr))
        return icon;

    // Not using Qt's sugar syntax, which doesn't support 1.5x anyway when we need it.
    // Simply add the high-res files and Qt will pick them when needed

    if (scalingFactorIsSupported(1.5))
        icon.addFile(QStringLiteral(":/img/%1-1.5x.png").arg(iconName));

    icon.addFile(QStringLiteral(":/img/%1-2x.png").arg(iconName));

    return icon;
}

View *DefaultWidgetFactory_qtquick::createDropArea(Controllers::DropArea *controller, View *parent) const
{
    return new Views::DropArea_qtquick(controller, parent);
}

View *DefaultWidgetFactory_qtquick::createMDILayout(MDILayoutWidget *controller, View *parent) const
{
    return new Views::MDILayout_qtquick(controller, parent);
}

Q_INVOKABLE QUrl DefaultWidgetFactory_qtquick::titleBarFilename() const
{
    return {};
}

QUrl DefaultWidgetFactory_qtquick::dockwidgetFilename() const
{
    return {};
}

QUrl DefaultWidgetFactory_qtquick::frameFilename() const
{
    return {};
}

QUrl DefaultWidgetFactory_qtquick::floatingWindowFilename() const
{
    return {};
}
