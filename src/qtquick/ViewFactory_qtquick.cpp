/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewFactory_qtquick.h"
#include "Config.h"

#include "controllers/indicators/ClassicIndicators.h"
#include "controllers/indicators/NullIndicators.h"
#include "controllers/indicators/SegmentedIndicators.h"
#include "private/Utils_p.h"

#include "controllers/MainWindow.h"
#include "controllers/TabBar.h"
#include "controllers/Stack.h"
#include "controllers/FloatingWindow.h"

#include "qtquick/views/FloatingWindow_qtquick.h"
#include "qtquick/views/DockWidget_qtquick.h"
#include "qtquick/views/DropArea_qtquick.h"
#include "qtquick/views/Frame_qtquick.h"
#include "qtquick/views/View_qtquick.h"
#include "qtquick/views/RubberBand_qtquick.h"
#include "qtquick/views/Separator_qtquick.h"
#include "qtquick/views/TitleBar_qtquick.h"
#include "qtquick/views/TabBar_qtquick.h"
// #include "qtquick/views/SideBar_qtquick.h"
#include "qtquick/views/Stack_qtquick.h"
#include "qtquick/views/MainWindow_qtquick.h"
#include "qtquick/views/MDILayout_qtquick.h"



// clazy:excludeall=ctor-missing-parent-argument

using namespace KDDockWidgets;


ViewFactory_qtquick::~ViewFactory_qtquick()
{
}

View *ViewFactory_qtquick::createMainWindow(Controllers::MainWindow *mainWindow,
                                            View *parent, Qt::WindowFlags flags) const
{
    Q_UNUSED(mainWindow);
    Q_UNUSED(parent);
    Q_UNUSED(flags);

    return {};
    // return new Views::MainWindow_qtquick(mainWindow, Views::asQQuickItem(parent), flags);
}

View *ViewFactory_qtquick::createDockWidget(Controllers::DockWidget *dw, Qt::WindowFlags flags) const
{
    return new Views::DockWidget_qtquick(dw, flags);
}

View *ViewFactory_qtquick::createFrame(Controllers::Frame *controller, View *parent,
                                       FrameOptions) const
{
    return new Views::Frame_qtquick(controller, Views::asQQuickItem(parent));
}

View *ViewFactory_qtquick::createTitleBar(Controllers::TitleBar *titleBar,
                                          Controllers::Frame *parent) const
{
    return new Views::TitleBar_qtquick(titleBar, Views::asQQuickItem(parent));
}

View *ViewFactory_qtquick::createTitleBar(Controllers::TitleBar *titleBar,
                                          Controllers::FloatingWindow *fw) const
{
    return new Views::TitleBar_qtquick(titleBar, Views::asQQuickItem(fw));
}

View *ViewFactory_qtquick::createTabBar(Controllers::TabBar *controller, View *parent) const
{
    return new Views::TabBar_qtquick(controller, Views::asQQuickItem(parent));
}

View *ViewFactory_qtquick::createTabWidget(Controllers::Stack *controller, Controllers::Frame *parent) const
{
    return new Views::Stack_qtquick(controller, parent);
}

View *ViewFactory_qtquick::createSeparator(Controllers::Separator *controller, View *parent) const
{
    return new Views::Separator_qtquick(controller, parent ? static_cast<Views::View_qtquick *>(parent) : nullptr);
}

View *ViewFactory_qtquick::createFloatingWindow(Controllers::FloatingWindow *controller,
                                                Controllers::MainWindow *parent, Qt::WindowFlags flags) const
{

    auto mainwindow = parent ? qobject_cast<Views::MainWindow_qtquick *>(Views::asQQuickItem(parent->view()))
                             : nullptr;
    return new Views::FloatingWindow_qtquick(controller, mainwindow, flags);
}

View *ViewFactory_qtquick::createRubberBand(View *parent) const
{
    return new Views::RubberBand_qtquick(Views::asQQuickItem(parent));
}

View *ViewFactory_qtquick::createSideBar(Controllers::SideBar *,
                                         Controllers::MainWindow *) const
{
    return {};
    // return new Views::SideBar_qtquick(controller, Views::View_qtwidgets<QWidget>::asQWidget(parent));
}

// iconForButtonType impl is the same for QtQuick and QtWidgets
QIcon ViewFactory_qtquick::iconForButtonType(TitleBarButtonType type, qreal dpr) const
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

View *ViewFactory_qtquick::createDropArea(Controllers::DropArea *controller, View *parent) const
{
    return new Views::DropArea_qtquick(controller, parent);
}

View *ViewFactory_qtquick::createMDILayout(Controllers::MDILayout *controller, View *parent) const
{
    return new Views::MDILayout_qtquick(controller, parent);
}

Q_INVOKABLE QUrl ViewFactory_qtquick::titleBarFilename() const
{
    return {};
}

QUrl ViewFactory_qtquick::dockwidgetFilename() const
{
    return {};
}

QUrl ViewFactory_qtquick::frameFilename() const
{
    return {};
}

QUrl ViewFactory_qtquick::floatingWindowFilename() const
{
    return {};
}

View *ViewFactory_qtquick::createClassicDropIndicatorOverlayView(Controllers::ClassicIndicators *, View *) const
{
    return nullptr;
}

View *ViewFactory_qtquick::createSegmentedDropIndicatorOverlayView(Controllers::SegmentedIndicators *, View *) const
{
    return nullptr;
}
