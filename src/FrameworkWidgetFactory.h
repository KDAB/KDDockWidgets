/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_FRAMEWORKWIDGETFACTORY_H
#define KDDOCKWIDGETS_FRAMEWORKWIDGETFACTORY_H

#include "docks_export.h"
#include "KDDockWidgets.h"
#include "View.h" // TODO
#include "controllers/Stack.h"
#include "controllers/TitleBar.h"

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

class MainWindowBase;
class DropIndicatorOverlayInterface;
class TabWidget;
class DropArea;
class TabBar;
class TabWidgetQuick;

namespace Views {
class Separator;
class TitleBar;
class TabBar;
}

namespace Controllers {
class Separator;
class TabBar;
class SideBar;
class FloatingWindow;
}

/**
 * @brief A factory class for allowing the user to customize some internal widgets.
 * This is optional, and if not provided, a default one will be used, @ref DefaultWidgetFactory.
 *
 * Deriving from @ref DefaultWidgetFactory is recommended, unless you need to override
 * all methods.
 *
 * Sub-classing FrameworkWidgetFactory allows for fine-grained customization and
 * styling of some non-public widgets, such as titlebars, dock widget frame and
 * tab widgets.
 *
 * To set your own factory see Config::setFrameworkWidgetFactory()
 *
 * Will also be useful to provide a QtQuickWidget factory in the future.
 *
 * @sa Config::setFrameworkWidgetFactory()
 */
class DOCKS_EXPORT FrameworkWidgetFactory : public QObject
{
    Q_OBJECT
public:
    FrameworkWidgetFactory() = default;

    ///@brief Destructor.Don't delete FrameworkWidgetFactory directly, it's owned
    /// by the framework.
    virtual ~FrameworkWidgetFactory();

    ///@brief Called internally by the framework to create a Frame class
    ///       Override to provide your own Frame sub-class. A frame is the
    ///       widget that holds the titlebar and tab-widget which holds the
    ///       DockWidgets.
    ///@param parent just forward to Frame's constructor
    ///@param options just forward to Frame's constructor
    virtual View *createFrame(Controllers::Frame *, View *parent = nullptr,
                              FrameOptions options = FrameOption_None) const = 0;

    ///@brief Called internally by the framework to create a TitleBar
    ///       Override to provide your own TitleBar sub-class. If overridden then
    ///       you also need to override the overload below.
    ///@param frame Just forward to TitleBar's constructor.
    virtual View *createTitleBar(Controllers::TitleBar *, Controllers::Frame *frame) const = 0;

    ///@brief Called internally by the framework to create a TitleBar
    ///       Override to provide your own TitleBar sub-class. If overridden then
    ///       you also need to override the overload above.
    ///@param floatingWindow Just forward to TitleBar's constructor.
    virtual View *createTitleBar(Controllers::TitleBar *, Controllers::FloatingWindow *) const = 0;

    ///@brief Called internally by the framework to create a TabWidget
    ///       Override to provide your own TabWidget sub-class.
    ///@param parent Just forward to TabWidget's constructor.
    virtual View *createTabWidget(Controllers::Stack *stack, Controllers::Frame *parent) const = 0;

    ///@brief Called internally by the framework to create a TabBar
    ///       Override to provide your own TabBar sub-class.
    ///@param parent Just forward to TabBar's's constructor.
    virtual View *createTabBar(Controllers::TabBar *tabBar, View *parent = nullptr) const = 0;

    ///@brief Called internally by the framework to create a Separator
    ///       Override to provide your own Separator sub-class. The Separator allows
    ///       the user to resize nested dock widgets.
    ///@param parent Just forward to Separator's constructor.
    virtual View *createSeparator(Controllers::Separator *, View *parent = nullptr) const = 0;

    ///@brief Called internally by the framework to create a FloatingWindow
    ///       Override to provide your own FloatingWindow sub-class. If overridden then
    ///       you also need to override the overloads below.
    ///@param parent Just forward to FloatingWindow's constructor.
    virtual View *createFloatingWindow(Controllers::FloatingWindow *controller,
                                       MainWindowBase *parent = nullptr,
                                       Qt::WindowFlags windowFlags = {}) const = 0;

    ///@brief Called internally by the framework to create a DropIndicatorOverlayInterface
    ///       Override to provide your own DropIndicatorOverlayInterface sub-class.
    ///@param dropArea Just forward to DropIndicatorOverlayInterface's constructor.
    virtual DropIndicatorOverlayInterface *createDropIndicatorOverlay(DropArea *dropArea) const = 0;

    ///@brief Called internally by the framework to create a RubberBand to show as drop zone
    /// Returns a rubber band
    virtual QWidgetOrQuick *createRubberBand(QWidgetOrQuick *parent) const = 0;

    ///@brief Called internally by the framework to create a SideBar
    ///@param loc The side-bar location without the main window. Just forward into your SideBar sub-class ctor.
    ///@param parent The MainWindow. Just forward into your SideBar sub-class ctor.
    virtual View *createSideBar(Controllers::SideBar *, MainWindowBase *parent) const = 0;

#ifdef KDDOCKWIDGETS_QTWIDGETS
    ///@brief Called internally by the framework to create a title bar button
    ///@p parent the button's parent
    virtual QAbstractButton *createTitleBarButton(QWidget *parent, TitleBarButtonType) const = 0;
#else
    virtual QUrl titleBarFilename() const = 0;
    virtual QUrl dockwidgetFilename() const = 0;
    virtual QUrl frameFilename() const = 0;
    virtual QUrl floatingWindowFilename() const = 0;
#endif

    /// @brief Returns the icon to be used with the specified @p type
    /// @param dpr the device pixel ratio of the button
    virtual QIcon iconForButtonType(TitleBarButtonType type, qreal dpr) const = 0;

private:
    Q_DISABLE_COPY(FrameworkWidgetFactory)
};

/**
 * @brief The FrameworkWidgetFactory that's used if none is specified.
 */
class DOCKS_EXPORT DefaultWidgetFactory : public FrameworkWidgetFactory
{
    Q_OBJECT
public:
    DefaultWidgetFactory() = default;
    View *createFrame(Controllers::Frame *, View *parent, FrameOptions options = FrameOption_None) const override;
    View *createTitleBar(Controllers::TitleBar *, Controllers::Frame *) const override;
    View *createTitleBar(Controllers::TitleBar *, Controllers::FloatingWindow *) const override;
    View *createTabWidget(Controllers::Stack *, Controllers::Frame *parent) const override;
    View *createTabBar(Controllers::TabBar *tabBar, View *parent) const override;
    View *createSeparator(Controllers::Separator *, View *parent = nullptr) const override;
    View *createFloatingWindow(Controllers::FloatingWindow *,
                               MainWindowBase *parent = nullptr,
                               Qt::WindowFlags windowFlags = {}) const override;
    DropIndicatorOverlayInterface *createDropIndicatorOverlay(DropArea *) const override;
    QWidgetOrQuick *createRubberBand(QWidgetOrQuick *parent) const override;
    View *createSideBar(Controllers::SideBar *, MainWindowBase *parent) const override;

#ifdef KDDOCKWIDGETS_QTWIDGETS
    QAbstractButton *createTitleBarButton(QWidget *parent, TitleBarButtonType) const override;
#else
    Q_INVOKABLE QUrl titleBarFilename() const override;
    QUrl dockwidgetFilename() const override;
    QUrl frameFilename() const override;
    QUrl floatingWindowFilename() const override;
#endif

    QIcon iconForButtonType(TitleBarButtonType type, qreal dpr) const override;

    static DropIndicatorType s_dropIndicatorType;

private:
    Q_DISABLE_COPY(DefaultWidgetFactory)
};

}

#endif
