/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_ViewFactory_QTQUICK_H
#define KDDOCKWIDGETS_ViewFactory_QTQUICK_H

#include "ViewFactory.h"

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

namespace Layouting {
class Widget;
}

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
    View *createMainWindow(Controllers::MainWindow *, View *, Qt::WindowFlags) const override;
    View *createDockWidget(Controllers::DockWidget *, Qt::WindowFlags) const override;
    View *createFrame(Controllers::Frame *, View *parent, FrameOptions options = FrameOption_None) const override;
    View *createTitleBar(Controllers::TitleBar *, Controllers::Frame *) const override;
    View *createTitleBar(Controllers::TitleBar *, Controllers::FloatingWindow *) const override;
    View *createTabWidget(Controllers::Stack *, Controllers::Frame *parent) const override;
    View *createTabBar(Controllers::TabBar *tabBar, View *parent) const override;
    View *createSeparator(Controllers::Separator *, View *parent = nullptr) const override;
    View *createFloatingWindow(Controllers::FloatingWindow *,
                               Controllers::MainWindow *parent = nullptr,
                               Qt::WindowFlags windowFlags = {}) const override;
    View *createRubberBand(View *parent) const override;
    View *createSideBar(Controllers::SideBar *, Controllers::MainWindow *parent) const override;
    View *createDropArea(Controllers::DropArea *, View *parent) const override;
    View *createMDILayout(Controllers::MDILayout *, View *parent) const override;

    Q_INVOKABLE QUrl titleBarFilename() const;
    QUrl dockwidgetFilename() const;
    QUrl frameFilename() const;
    QUrl floatingWindowFilename() const;

    QIcon iconForButtonType(TitleBarButtonType type, qreal dpr) const override;
    View *createClassicDropIndicatorOverlayView(Controllers::ClassicIndicators *controller, View *parent = nullptr) const override;
    Views::ClassicIndicatorWindow *createClassicIndicatorWindow(Controllers::ClassicIndicators *) const override;
    View *createSegmentedDropIndicatorOverlayView(Controllers::SegmentedIndicators *controller, View *parent = nullptr) const override;

private:
    Q_DISABLE_COPY(ViewFactory_qtquick)
};

}

#endif
