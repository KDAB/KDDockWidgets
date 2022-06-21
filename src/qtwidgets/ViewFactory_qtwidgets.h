/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_ViewFactory_QTWIDGETS_H
#define KDDOCKWIDGETS_ViewFactory_QTWIDGETS_H

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
 * @brief The default ViewFactory for QtWidgets frontend.
 */
class DOCKS_EXPORT ViewFactory_qtwidgets : public ViewFactory
{
    Q_OBJECT
public:
    ViewFactory_qtwidgets() = default;
    ~ViewFactory_qtwidgets() override;

    View *createDockWidget(const QString &uniqueName,
                           DockWidgetOptions = {},
                           LayoutSaverOptions = {},
                           Qt::WindowFlags = {}) const override;

    View *createFrame(Controllers::Group *, View *parent) const override;
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
    QIcon iconForButtonType(TitleBarButtonType type, qreal dpr) const override;
    QAbstractButton *createTitleBarButton(QWidget *parent, TitleBarButtonType) const;

    View *createClassicDropIndicatorOverlayView(Controllers::ClassicIndicators *controller, View *parent = nullptr) const override;
    Views::ClassicIndicatorWindowViewInterface *createClassicIndicatorWindow(Controllers::ClassicIndicators *) const override;

    View *createSegmentedDropIndicatorOverlayView(Controllers::SegmentedIndicators *controller, View *parent = nullptr) const override;

private:
    Q_DISABLE_COPY(ViewFactory_qtwidgets)
};

}

#endif
