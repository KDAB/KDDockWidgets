/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewFactory_qtquick.h"
#include "Config.h"

#include "kddockwidgets/core/indicators/ClassicIndicators.h"
#include "kddockwidgets/core/indicators/NullIndicators.h"
#include "kddockwidgets/core/indicators/SegmentedIndicators.h"
#include "private/Utils_p.h"

#include "kddockwidgets/core/MainWindow.h"
#include "kddockwidgets/core/TabBar.h"
#include "kddockwidgets/core/Stack.h"
#include "kddockwidgets/core/FloatingWindow.h"

#include "qtquick/views/FloatingWindow_qtquick.h"
#include "qtquick/views/DockWidget_qtquick.h"
#include "qtquick/views/DropArea_qtquick.h"
#include "qtquick/views/Group_qtquick.h"
#include "qtquick/views/View_qtquick.h"
#include "qtquick/views/RubberBand_qtquick.h"
#include "qtquick/views/Separator_qtquick.h"
#include "qtquick/views/TitleBar_qtquick.h"
#include "qtquick/views/TabBar_qtquick.h"
// #include "qtquick/views/SideBar_qtquick.h"
#include "qtquick/views/Stack_qtquick.h"
#include "kddockwidgets/views/MainWindow_qtquick.h"
#include "qtquick/views/MDILayout_qtquick.h"
#include "qtquick/views/ClassicIndicatorsWindow_qtquick.h"

#include "views/ClassicIndicatorsWindow_qtquick.h"

// clazy:excludeall=ctor-missing-parent-argument

using namespace KDDockWidgets;
using namespace KDDockWidgets::qtquick;


ViewFactory::~ViewFactory()
{
}

View *ViewFactory::createDockWidget(const QString &uniqueName, DockWidgetOptions options,
                                    LayoutSaverOptions layoutSaverOptions,
                                    Qt::WindowFlags windowFlags) const
{
    return createDockWidget(uniqueName, /*engine=*/nullptr, options, layoutSaverOptions,
                            windowFlags);
}

View *ViewFactory::createDockWidget(const QString &uniqueName, QQmlEngine *qmlEngine,
                                    DockWidgetOptions options,
                                    LayoutSaverOptions layoutSaverOptions,
                                    Qt::WindowFlags windowFlags) const
{
    return new qtquick::DockWidget(uniqueName, options, layoutSaverOptions, windowFlags,
                                   qmlEngine);
}

View *ViewFactory::createGroup(Core::Group *controller, View *parent) const
{
    return new Group(controller, Views::asQQuickItem(parent));
}

View *ViewFactory::createTitleBar(Core::TitleBar *titleBar, View *parent) const
{
    return new TitleBar(titleBar, Views::asQQuickItem(parent));
}

View *ViewFactory::createTabBar(Core::TabBar *controller, View *parent) const
{
    return new TabBar(controller, Views::asQQuickItem(parent));
}

View *ViewFactory::createStack(Core::Stack *controller, View *parent) const
{
    return new Stack(controller, Views::asQQuickItem(parent));
}

View *ViewFactory::createSeparator(Core::Separator *controller, View *parent) const
{
    return new Separator(
        controller, parent ? static_cast<Views::View_qtquick *>(parent) : nullptr);
}

View *ViewFactory::createFloatingWindow(Core::FloatingWindow *controller,
                                        Core::MainWindow *parent,
                                        Qt::WindowFlags flags) const
{

    auto mainwindow = parent
        ? qobject_cast<qtquick::MainWindow *>(Views::asQQuickItem(parent->view()))
        : nullptr;
    return new FloatingWindow(controller, mainwindow, flags);
}

View *ViewFactory::createRubberBand(View *parent) const
{
    return new Views::RubberBand(Views::asQQuickItem(parent));
}

View *ViewFactory::createSideBar(Core::SideBar *, View *) const
{
    return {};
}

// iconForButtonType impl is the same for QtQuick and QtWidgets
QIcon ViewFactory::iconForButtonType(TitleBarButtonType type, qreal dpr) const
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

View *ViewFactory::createDropArea(Core::DropArea *controller, View *parent) const
{
    return new DropArea(controller, parent);
}

View *ViewFactory::createMDILayout(Core::MDILayout *controller, View *parent) const
{
    return new MDILayout(controller, parent);
}

QUrl ViewFactory::titleBarFilename() const
{
    return QUrl(QStringLiteral("qrc:/kddockwidgets/qtquick/views/qml/TitleBar.qml"));
}

QUrl ViewFactory::dockwidgetFilename() const
{
    return QUrl(QStringLiteral("qrc:/kddockwidgets/qtquick/views/qml/DockWidget.qml"));
}

QUrl ViewFactory::groupFilename() const
{
    return QUrl(QStringLiteral("qrc:/kddockwidgets/qtquick/views/qml/Group.qml"));
}

QUrl ViewFactory::floatingWindowFilename() const
{
    return QUrl(QStringLiteral("qrc:/kddockwidgets/qtquick/views/qml/FloatingWindow.qml"));
}

QUrl ViewFactory::tabbarFilename() const
{
    return QUrl(QStringLiteral("qrc:/kddockwidgets/qtquick/views/qml/TabBar.qml"));
}

View *
ViewFactory::createSegmentedDropIndicatorOverlayView(Core::SegmentedIndicators *,
                                                     View *) const
{
    return nullptr;
}

Views::ClassicIndicatorWindowViewInterface *ViewFactory::createClassicIndicatorWindow(
    Core::ClassicIndicators *classicIndicators) const
{
    return new IndicatorWindow(classicIndicators);
}

ViewFactory *ViewFactory::self()
{
    auto factory = qobject_cast<ViewFactory *>(Config::self().viewFactory());

    if (!factory)
        qWarning() << Q_FUNC_INFO << "Expected a ViewFactory_qtquick subclass, not"
                   << Config::self().viewFactory();

    return factory;
}
