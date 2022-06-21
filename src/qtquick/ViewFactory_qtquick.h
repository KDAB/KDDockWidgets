/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_ViewFactory_QTQUICK_H
#define KDDOCKWIDGETS_ViewFactory_QTQUICK_H

#include "kddockwidgets/ViewFactory.h"

// clazy:excludeall=ctor-missing-parent-argument

/**
 * @file
 * @brief A factory class for allowing the user to customize some internal widgets.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QQmlEngine;
QT_END_NAMESPACE

namespace KDDockWidgets {

class DropIndicatorOverlay;

namespace Controllers {
class MDILayoutWidget;
class DropArea;
class Separator;
class TabBar;
class SideBar;
class FloatingWindow;
class MainWindow;
}

/**
 * @brief The default ViewFactory for QtQuick frontend.
 */
class DOCKS_EXPORT ViewFactory_qtquick : public ViewFactory
{
    Q_OBJECT
public:
    ViewFactory_qtquick() = default;
    ~ViewFactory_qtquick() override;
    View *createDockWidget(const QString &uniqueName,
                           DockWidgetOptions options = {},
                           LayoutSaverOptions layoutSaverOptions = {},
                           Qt::WindowFlags windowFlags = {}) const override;
    virtual View *createDockWidget(const QString &uniqueName,
                                   QQmlEngine *, DockWidgetOptions options = {},
                                   LayoutSaverOptions layoutSaverOptions = {},
                                   Qt::WindowFlags windowFlags = {}) const;
    View *createGroup(Controllers::Group *, View *parent) const override;
    View *createTitleBar(Controllers::TitleBar *, View *parent) const override;
    View *createStack(Controllers::Stack *, View *parent) const override;
    View *createTabBar(Controllers::TabBar *tabBar, View *parent) const override;
    View *createSeparator(Controllers::Separator *, View *parent = nullptr) const override;
    View *createFloatingWindow(Controllers::FloatingWindow *,
                               Controllers::MainWindow *parent = nullptr,
                               Qt::WindowFlags windowFlags = {}) const override;
    View *createRubberBand(View *parent) const override;
    View *createSideBar(Controllers::SideBar *, View *parent) const override;
    View *createDropArea(Controllers::DropArea *, View *parent) const override;
    View *createMDILayout(Controllers::MDILayout *, View *parent) const override;

    Q_INVOKABLE virtual QUrl titleBarFilename() const;
    virtual QUrl dockwidgetFilename() const;
    virtual QUrl frameFilename() const;
    virtual QUrl floatingWindowFilename() const;

    QIcon iconForButtonType(TitleBarButtonType type, qreal dpr) const override;
    View *createClassicDropIndicatorOverlayView(Controllers::ClassicIndicators *controller, View *parent = nullptr) const override;
    Views::ClassicIndicatorWindowViewInterface *createClassicIndicatorWindow(Controllers::ClassicIndicators *) const override;
    View *createSegmentedDropIndicatorOverlayView(Controllers::SegmentedIndicators *controller, View *parent = nullptr) const override;

    static ViewFactory_qtquick *self();

private:
    Q_DISABLE_COPY(ViewFactory_qtquick)
};

}

#endif
