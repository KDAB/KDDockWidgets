/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief Application-wide config to tune certain behaviours of the framework.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_DOCKWIDGETS_CONFIG_H
#define KD_DOCKWIDGETS_CONFIG_H

#include "docks_export.h"

QT_BEGIN_NAMESPACE
class QQmlEngine;
QT_END_NAMESPACE

namespace KDDockWidgets
{

class DockWidgetBase;
class MainWindowBase;
class FrameworkWidgetFactory;

typedef KDDockWidgets::DockWidgetBase* (*DockWidgetFactoryFunc)(const QString &name);
typedef KDDockWidgets::MainWindowBase* (*MainWindowFactoryFunc)(const QString &name);

/**
 * @brief Singleton to allow to choose certain behaviours of the framework.
 *
 * The setters should only be used before creating any DockWidget or MainWindow,
 * preferably right after creating the QApplication.
 */
class DOCKS_EXPORT Config
{
public:

    ///@brief returns the singleton Config instance
    static Config &self();

    ///@brief destructor, called at shutdown
    ~Config();

    ///@brief Flag enum to tune certain behaviours, the defaults are Flag_Default
    enum Flag {
        Flag_None = 0, ///> No option set
        Flag_NativeTitleBar = 1, ///> Enables the Native OS title bar on OSes that support it (Windows 10, macOS), ignored otherwise. This is mutually exclusive with Flag_AeroSnap
        Flag_AeroSnapWithClientDecos = 2, ///> Enables AeroSnap even if we're not using the native title bar. Only supported on Windows 10.
        Flag_AlwaysTitleBarWhenFloating = 4, ///> Floating windows will have a title bar even if Flag_HideTitleBarWhenTabsVisible is specified. Unneeded if Flag_HideTitleBarWhenTabsVisible isn't specified, as that's the default already.
        Flag_HideTitleBarWhenTabsVisible = 8, ///> Hides the title bar if there's tabs visible. The empty space in the tab bar becomes draggable.
        Flag_AlwaysShowTabs = 16, ///> Always show tabs, even if there's only one,
        Flag_AllowReorderTabs = 32, /// Allows user to re-order tabs by dragging them
        Flag_TabsHaveCloseButton = 64, /// Tabs will have a close button. Equivalent to QTabWidget::setTabsClosable(true).
        Flag_DoubleClickMaximizes = 128, /// Double clicking the titlebar will maximize a floating window instead of re-docking it
        Flag_TitleBarHasMaximizeButton = 256, /// The title bar will have a maximize/restore button when floating. This is mutually-exclusive with the floating button (since many apps behave that way).
        Flag_TitleBarIsFocusable = 512, /// You can click the title bar and it will focus the last focused widget in the focus scope. If no previously focused widget then it focuses the user's dock widget guest, which should accept focus or use a focus proxy.
        Flag_LazyResize = 1024, /// The dock widgets are resized in a lazy manner. The actual resize only happens when you release the mouse button.

        // These two are internal, for testing purposes across platforms. Use Flag_DontUseUtilityFloatingWindows instead.
        Flag_internal_DontUseQtToolWindowsForFloatingWindows = 0x800, ///> FloatingWindows will use Qt::Window instead of Qt::Tool. Internal, use Flag_DontUseUtilityFloatingWindows instead.
        Flag_internal_DontUseParentForFloatingWindows = 0x1000, ///> FloatingWindows won't have a parent top-level. Internal, use Flag_DontUseUtilityFloatingWindows instead.

        Flag_DontUseUtilityFloatingWindows = Flag_internal_DontUseQtToolWindowsForFloatingWindows | Flag_internal_DontUseParentForFloatingWindows,
        Flag_TitleBarHasMinimizeButton = 0x2000 | Flag_DontUseUtilityFloatingWindows, ///> The title bar will have a minimize button when floating. This implies Flag_DontUseUtilityFloatingWindows too, otherwise they wouldn't appear in the task bar.
        Flag_Default = Flag_AeroSnapWithClientDecos ///> The defaults
    };
    Q_DECLARE_FLAGS(Flags, Flag)

    ///@brief returns the chosen flags
    Flags flags() const;

    ///@brief setter for the flags
    ///@param flags the flags to set
    ///Not all flags are guaranteed to be set, as the OS might not supported them
    ///Call @ref flags() after the setter if you need to know what was really set
    void setFlags(Flags flags);

    /**
     * @brief Registers a DockWidgetFactoryFunc.
     *
     * This is optional, the default is nullptr.
     *
     * A DockWidgetFactoryFunc is a function that receives a dock widget name
     * and returns a DockWidget instance.
     *
     * While restoring, @ref LayoutSaver requires all dock widgets to exist.
     * If a DockWidget doesn't exist then a DockWidgetFactoryFunc function is
     * required, so the layout saver can ask to create the DockWidget and then
     * restore it.
     */
    void setDockWidgetFactoryFunc(DockWidgetFactoryFunc);

    ///@brief Returns the DockWidgetFactoryFunc.
    ///nullptr by default
    DockWidgetFactoryFunc dockWidgetFactoryFunc() const;

    ///@brief counter-part of DockWidgetFactoryFunc but for the main window.
    /// Should be rarely used. It's good practice to have the main window before restoring a layout.
    /// It's here so we can use it in the linter executable
    void setMainWindowFactoryFunc(MainWindowFactoryFunc);

    ///@brief Returns the MainWindowFactoryFunc.
    ///nullptr by default
    MainWindowFactoryFunc mainWindowFactoryFunc() const;

    /**
     * @brief Sets the WidgetFactory.
     *
     * By default DefaultWidgetFactory is used, which gives you FrameWidget, TitleBarWidget,
     * TabBarWidget, TabWidgetWidget etc. You can set your own factory, to supply your own variants
     * of those classes, for the purposes of changing GUI appearance and such.
     *
     * Also potentially useful to return QtQuick classes instead of the QtWidget based ones.
     * Ownership is taken.
     */
    void setFrameworkWidgetFactory(FrameworkWidgetFactory *);

    ///@brief getter for the framework widget factory
    FrameworkWidgetFactory *frameworkWidgetFactory() const;

    /**
     * @brief Returns the thickness of the separator.
     *
     * Default is 5px.
     */
    int separatorThickness() const;

    ///@brief setter for @ref separatorThickness
    ///Note: Only use this function at startup before creating any DockWidget or MainWindow.
    void setSeparatorThickness(int value);

    ///@brief sets the dragged window opacity
    ///1.0 is fully opaque while 0.0 is fully transparent
    void setDraggedWindowOpacity(qreal opacity);

    ///@brief returns the opacity to use when dragging dock widgets
    ///By default it's 1.0, fully opaque
    qreal draggedWindowOpacity() const;

    ///@brief Sets the QQmlEngine to use. Applicable only when using QtQuick.
    void setQmlEngine(QQmlEngine *);
    QQmlEngine* qmlEngine() const;

private:
    Q_DISABLE_COPY(Config)
    Config();
    class Private;
    Private *const d;
};

}

Q_DECLARE_OPERATORS_FOR_FLAGS(KDDockWidgets::Config::Flags)

#endif
