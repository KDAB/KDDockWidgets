/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewFactory_qtwidgets.h"
#include "Config.h"

#include "private/Utils_p.h"

#include "controllers/TabBar.h"
#include "controllers/Stack.h"
#include "controllers/FloatingWindow.h"
#include "controllers/indicators/ClassicIndicators.h"
#include "controllers/indicators/NullIndicators.h"
#include "controllers/indicators/SegmentedIndicators.h"

#include "qtwidgets/views/ClassicIndicatorsOverlay_qtwidgets.h"
#include "qtwidgets/views/SegmentedIndicatorsOverlay_qtwidgets.h"
#include "qtwidgets/views/FloatingWindow_qtwidgets.h"
#include "qtwidgets/views/DockWidget_qtwidgets.h"
#include "qtwidgets/views/DropArea_qtwidgets.h"
#include "qtwidgets/views/Frame_qtwidgets.h"
#include "qtwidgets/views/View_qtwidgets.h"
#include "qtwidgets/views/Separator_qtwidgets.h"
#include "qtwidgets/views/TitleBar_qtwidgets.h"
#include "qtwidgets/views/TabBar_qtwidgets.h"
#include "qtwidgets/views/SideBar_qtwidgets.h"
#include "qtwidgets/views/Stack_qtwidgets.h"
#include "qtwidgets/views/MainWindow_qtwidgets.h"
#include "qtwidgets/views/MDILayout_qtwidgets.h"
#include "qtwidgets/views/RubberBand_qtwidgets.h"

#include <QToolButton>


// clazy:excludeall=ctor-missing-parent-argument

using namespace KDDockWidgets;


ViewFactory_qtwidgets::~ViewFactory_qtwidgets()
{
}

View *ViewFactory_qtwidgets::createMainWindow(Controllers::MainWindow *mainWindow, View *parent, Qt::WindowFlags flags) const
{
    return new Views::MainWindow_qtwidgets(mainWindow, parent ? static_cast<Views::View_qtwidgets<QMainWindow> *>(parent) : nullptr, flags);
}

View *ViewFactory_qtwidgets::createDockWidget(Controllers::DockWidget *dw, Qt::WindowFlags flags) const
{
    return new Views::DockWidget_qtwidgets(dw, flags);
}

View *ViewFactory_qtwidgets::createFrame(Controllers::Frame *controller, View *parent = nullptr,
                                         FrameOptions) const
{
    // TODOv2: Remove options
    return new Views::Frame_qtwidgets(controller, Views::View_qtwidgets<QWidget>::asQWidget(parent));
}

View *ViewFactory_qtwidgets::createTitleBar(Controllers::TitleBar *titleBar, Controllers::Frame *frame) const
{
    return new Views::TitleBar_qtwidgets(titleBar, Views::View_qtwidgets<QWidget>::asQWidget(frame));
}

View *ViewFactory_qtwidgets::createTitleBar(Controllers::TitleBar *titleBar, Controllers::FloatingWindow *fw) const
{
    return new Views::TitleBar_qtwidgets(titleBar, Views::View_qtwidgets<QWidget>::asQWidget(fw));
}

View *ViewFactory_qtwidgets::createTabBar(Controllers::TabBar *tabBar, View *parent) const
{
    return new Views::TabBar_qtwidgets(tabBar, Views::View_qtwidgets<QWidget>::asQWidget(parent));
}

View *ViewFactory_qtwidgets::createTabWidget(Controllers::Stack *controller, Controllers::Frame *parent) const
{
    return new Views::Stack_qtwidgets(controller, parent);
}

View *ViewFactory_qtwidgets::createSeparator(Controllers::Separator *controller, View *parent) const
{
    return new Views::Separator_qtwidgets(controller, parent ? static_cast<Views::View_qtwidgets<QWidget> *>(parent) : nullptr);
}

View *ViewFactory_qtwidgets::createFloatingWindow(Controllers::FloatingWindow *controller,
                                                  Controllers::MainWindow *parent, Qt::WindowFlags windowFlags) const
{
    auto mainwindow = qobject_cast<QMainWindow *>(Views::View_qtwidgets<QWidget>::asQWidget(parent));
    return new Views::FloatingWindow_qtwidgets(controller, mainwindow, windowFlags);
}

View *ViewFactory_qtwidgets::createRubberBand(View *parent) const
{
    return new Views::RubberBand_qtwidgets(parent ? qobject_cast<QWidget *>(parent->asQObject()) : nullptr);
}

View *ViewFactory_qtwidgets::createSideBar(Controllers::SideBar *controller,
                                           Controllers::MainWindow *parent) const
{
    return new Views::SideBar_qtwidgets(controller, Views::View_qtwidgets<QWidget>::asQWidget(parent));
}

QAbstractButton *ViewFactory_qtwidgets::createTitleBarButton(QWidget *parent, TitleBarButtonType type) const
{
    if (!parent) {
        qWarning() << Q_FUNC_INFO << "Parent not provided";
        return nullptr;
    }

    auto button = new Views::Button(parent);
    button->setIcon(iconForButtonType(type, parent->devicePixelRatioF()));

    return button;
}

// iconForButtonType impl is the same for QtQuick and QtWidgets
QIcon ViewFactory_qtwidgets::iconForButtonType(TitleBarButtonType type, qreal dpr) const
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

View *ViewFactory_qtwidgets::createDropArea(Controllers::DropArea *controller, View *parent) const
{
    return new Views::DropArea_qtwidgets(controller, parent);
}

View *ViewFactory_qtwidgets::createMDILayout(Controllers::MDILayout *controller, View *parent) const
{
    return new Views::MDILayout_qtwidgets(controller, parent);
}

View *ViewFactory_qtwidgets::createClassicDropIndicatorOverlayView(Controllers::ClassicIndicators *controller, View *parent) const
{
    return new Views::ClassicIndicatorsOverlay_qtwidgets(controller, Views::View_qtwidgets<QWidget>::asQWidget(parent));
}

View *ViewFactory_qtwidgets::createSegmentedDropIndicatorOverlayView(Controllers::SegmentedIndicators *controller, View *parent) const
{
    return new Views::SegmentedIndicatorsOverlay_qtwidgets(controller, Views::View_qtwidgets<QWidget>::asQWidget(parent));
}
