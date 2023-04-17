/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewFactory.h"
#include "Config.h"

#include "core/Utils_p.h"

#include "kddockwidgets/core/TabBar.h"
#include "kddockwidgets/core/Stack.h"
#include "kddockwidgets/core/FloatingWindow.h"
#include "kddockwidgets/core/indicators/ClassicIndicators.h"
#include "kddockwidgets/core/indicators/NullIndicators.h"
#include "kddockwidgets/core/indicators/SegmentedIndicators.h"
#include "kddockwidgets/core/MainWindow.h"
#include "kddockwidgets/core/views/ClassicIndicatorWindowViewInterface.h"

#include "qtwidgets/views/ClassicIndicatorsWindow.h"
#include "qtwidgets/views/SegmentedIndicatorsOverlay.h"
#include "qtwidgets/views/FloatingWindow.h"
#include "qtwidgets/views/DockWidget.h"
#include "qtwidgets/views/DropArea.h"
#include "qtwidgets/views/Group.h"
#include "qtwidgets/views/View.h"
#include "qtwidgets/views/Separator.h"
#include "qtwidgets/views/TitleBar.h"
#include "qtwidgets/views/TabBar.h"
#include "qtwidgets/views/SideBar.h"
#include "qtwidgets/views/Stack.h"
#include "qtwidgets/views/MainWindow.h"
#include "qtwidgets/views/MDILayout.h"
#include "qtwidgets/views/RubberBand.h"

#include <QToolButton>


// clazy:excludeall=ctor-missing-parent-argument

using namespace KDDockWidgets;
using namespace KDDockWidgets::qtwidgets;


ViewFactory::~ViewFactory()
{
}

Core::View *ViewFactory::createDockWidget(const QString &uniqueName, DockWidgetOptions options,
                                          LayoutSaverOptions layoutSaverOptions,
                                          Qt::WindowFlags windowFlags) const
{
    return new qtwidgets::DockWidget(uniqueName, options, layoutSaverOptions, windowFlags);
}


Core::View *ViewFactory::createGroup(Core::Group *controller,
                                     Core::View *parent = nullptr) const
{
    return new qtwidgets::Group(controller, qtcommon::View_qt::asQWidget(parent));
}

Core::View *ViewFactory::createTitleBar(Core::TitleBar *titleBar, Core::View *parent) const
{
    return new qtwidgets::TitleBar(titleBar, parent);
}

Core::View *ViewFactory::createTabBar(Core::TabBar *tabBar, Core::View *parent) const
{
    return new qtwidgets::TabBar(tabBar, qtcommon::View_qt::asQWidget(parent));
}

Core::View *ViewFactory::createStack(Core::Stack *controller, Core::View *parent) const
{
    return new qtwidgets::Stack(controller, qtcommon::View_qt::asQWidget(parent));
}

Core::View *ViewFactory::createSeparator(Core::Separator *controller, Core::View *parent) const
{
    return new qtwidgets::Separator(controller, parent);
}

Core::View *ViewFactory::createFloatingWindow(Core::FloatingWindow *controller,
                                              Core::MainWindow *parent,
                                              Qt::WindowFlags windowFlags) const
{
    auto mainwindow =
        qobject_cast<QMainWindow *>(qtcommon::View_qt::asQWidget(parent ? parent->view() : nullptr));
    return new qtwidgets::FloatingWindow(controller, mainwindow, windowFlags);
}

Core::View *ViewFactory::createRubberBand(Core::View *parent) const
{
    return new qtwidgets::RubberBand(qtcommon::View_qt::asQWidget(parent));
}

Core::View *ViewFactory::createSideBar(Core::SideBar *controller, Core::View *parent) const
{
    return new qtwidgets::SideBar(controller, qtcommon::View_qt::asQWidget(parent));
}

QAbstractButton *ViewFactory::createTitleBarButton(QWidget *parent,
                                                   TitleBarButtonType type) const
{
    if (!parent) {
        qWarning() << Q_FUNC_INFO << "Parent not provided";
        return nullptr;
    }

    auto button = new qtwidgets::Button(parent);
    button->setIcon(iconForButtonType(type, parent->devicePixelRatioF()));

    return button;
}

// iconForButtonType impl is the same for QtQuick and QtWidgets
QIcon ViewFactory::iconForButtonType(TitleBarButtonType type, qreal dpr) const
{
    auto key = std::make_pair(type, dpr);
    auto it = m_cachedIcons.constFind(key);
    if (it != m_cachedIcons.cend())
        return *it;

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
    if (!scalingFactorIsSupported(dpr)) {
        m_cachedIcons.insert(key, icon);
        return icon;
    }

    // Not using Qt's sugar syntax, which doesn't support 1.5x anyway when we need it.
    // Simply add the high-res files and Qt will pick them when needed

    if (scalingFactorIsSupported(1.5))
        icon.addFile(QStringLiteral(":/img/%1-1.5x.png").arg(iconName));

    icon.addFile(QStringLiteral(":/img/%1-2x.png").arg(iconName));
    m_cachedIcons.insert(key, icon);

    return icon;
}

Core::View *ViewFactory::createDropArea(Core::DropArea *controller, Core::View *parent) const
{
    return new qtwidgets::DropArea(controller, parent);
}

Core::View *ViewFactory::createMDILayout(Core::MDILayout *controller, Core::View *parent) const
{
    return new qtwidgets::MDILayout(controller, parent);
}

Core::View *ViewFactory::createSegmentedDropIndicatorOverlayView(
    Core::SegmentedIndicators *controller, Core::View *parent) const
{
    return new qtwidgets::SegmentedIndicatorsOverlay(controller,
                                                     qtcommon::View_qt::asQWidget(parent));
}

Core::ClassicIndicatorWindowViewInterface *ViewFactory::createClassicIndicatorWindow(
    Core::ClassicIndicators *classicIndicators) const
{
    return new qtwidgets::IndicatorWindow(classicIndicators);
}

void ViewFactory::clearIconCache()
{
    m_cachedIcons.clear();
}
