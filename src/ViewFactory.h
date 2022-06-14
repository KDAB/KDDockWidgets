/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_ViewFactory_H
#define KDDOCKWIDGETS_ViewFactory_H

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"
#include "View.h"
#include "controllers/Stack.h"
#include "controllers/TitleBar.h"


QT_BEGIN_NAMESPACE
class QAbstractButton;
QT_END_NAMESPACE

namespace KDDockWidgets {

namespace Controllers {
class DropIndicatorOverlay;
class DropArea;
class Separator;
class TabBar;
class SideBar;
class FloatingWindow;
class MainWindow;
class ClassicIndicators;
class SegmentedIndicators;
}

namespace Views {
class ClassicIndicatorWindow;
}

/**
 * @brief A factory class for allowing the user to customize some internal views.
 * This is optional, and if not provided, a default one will be used.
 *
 * You should however not derive directly from ViewFactory, and instead, derive from ViewFactory_qtwidgets (for QtWidgets),
 * or ViewFactory_qtquick (for QtQuick).
 *
 * Sub-classing ViewFactory allows for fine-grained customization and
 * styling of some non-public widgets, such as titlebars, dock widget frame and
 * tab widgets.
 *
 * To set your own factory see Config::setViewFactory()
 *
 * @sa Config::setViewFactory()
 */
class DOCKS_EXPORT ViewFactory : public QObject
{
    Q_OBJECT
public:
    ViewFactory() = default;

    ///@brief Destructor.
    /// Don't delete ViewFactory directly, it's owned by the framework.
    virtual ~ViewFactory();

    /// @brief Creates a dock widget. This is only used by MainWindow's persistent widget feature.
    /// In all other cases users will instantiate DockWidget directly
    virtual View *createDockWidget(const QString &uniqueName,
                                   Controllers::DockWidget::Options options = {},
                                   Controllers::DockWidget::LayoutSaverOptions layoutSaverOptions = {},
                                   Qt::WindowFlags windowFlags = {}) const = 0;


    ///@brief Called by the framework to create a Frame view
    ///       Override to provide your own Frame sub-class. A frame is the
    ///       widget that holds the titlebar and tab-widget which holds the
    ///       DockWidgets.
    ///@param parent just forward to Frame's constructor
    virtual View *createFrame(Controllers::Frame *, View *parent = nullptr) const = 0;

    ///@brief Called by the framework to create a TitleBar view
    ///       Override to provide your own TitleBar sub-class.
    ///       Just forward the @p controller and @p parent arguments to the TitleBar view ctor
    virtual View *createTitleBar(Controllers::TitleBar *controller, View *parent) const = 0;

    ///@brief Called by the framework to create a Stack view
    ///       Override to provide your own Stack sub-class.
    ///@param parent Just forward to Stack's constructor.
    virtual View *createStack(Controllers::Stack *stack, View *parent) const = 0;

    ///@brief Called by the framework to create a TabBar view
    ///       Override to provide your own TabBar sub-class.
    ///@param parent Just forward to TabBar's's constructor.
    virtual View *createTabBar(Controllers::TabBar *tabBar, View *parent = nullptr) const = 0;

    ///@brief Called by the framework to create a Separator view
    ///       Override to provide your own Separator sub-class. The Separator allows
    ///       the user to resize nested dock widgets.
    ///@param parent Just forward to Separator's constructor.
    virtual View *createSeparator(Controllers::Separator *, View *parent = nullptr) const = 0;

    ///@brief Called by the framework to create a FloatingWindow view
    ///       Override to provide your own FloatingWindow sub-class.
    ///@param parent Just forward to FloatingWindow's constructor.
    virtual View *createFloatingWindow(Controllers::FloatingWindow *controller,
                                       Controllers::MainWindow *parent = nullptr,
                                       Qt::WindowFlags windowFlags = {}) const = 0;

    /// @brief Creates the view that will parent the classic drop indicators rubber band overlay
    virtual View *createClassicDropIndicatorOverlayView(Controllers::ClassicIndicators *controller, View *parent = nullptr) const = 0;

    /// @brief Creates the window that will show the actual drop indicators. They need a higher z-order, so this
    /// is actually a separate window, not parented to the main window
    virtual Views::ClassicIndicatorWindow *createClassicIndicatorWindow(Controllers::ClassicIndicators *) const = 0;

    /// @brief Creates the view that will parent the segmented drop indicators
    virtual View *
    createSegmentedDropIndicatorOverlayView(Controllers::SegmentedIndicators *controller, View *parent = nullptr) const = 0;

    /// @brief Called by the framework to create a DropArea view
    virtual View *createDropArea(Controllers::DropArea *, View *parent) const = 0;

    /// @brief Called by the framework to create a MDI Layout view
    virtual View *createMDILayout(Controllers::MDILayout *, View *parent) const = 0;

    ///@brief Called by the framework to create a RubberBand view to show as drop zone
    virtual View *createRubberBand(View *parent) const = 0;

    ///@brief Called by the framework to create a SideBar view
    ///@param loc The side-bar location without the main window. Just forward into your SideBar sub-class ctor.
    ///@param parent The MainWindow. Just forward into your SideBar sub-class ctor.
    virtual View *createSideBar(Controllers::SideBar *, View *parent) const = 0;

    /// @brief Returns the icon to be used with the specified @p type
    /// @param dpr the device pixel ratio of the button
    virtual QIcon iconForButtonType(TitleBarButtonType type, qreal dpr) const = 0;

    /// @ The drop indicator type
    static DropIndicatorType s_dropIndicatorType;

private:
    Q_DISABLE_COPY(ViewFactory)
};

}

#endif
