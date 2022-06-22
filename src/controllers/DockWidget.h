/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief The DockWidget base-class that's shared between QtWidgets and QtQuick stack.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_CONTROLLERS_DOCKWIDGET_H
#define KD_CONTROLLERS_DOCKWIDGET_H
#pragma once

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"
#include "kddockwidgets/LayoutSaver.h"
#include "kddockwidgets/Controller.h"

#include <QVector>

#include <memory>

// clazy:excludeall=ctor-missing-parent-argument

class TestDocks;

namespace KDDockWidgets {

class DragController;
class DockRegistry;
class LayoutSaver;
class StateDragging;

namespace Controllers {

class MainWindow;
class FloatingWindow;
class Group;
class Layout;
class TitleBar;

/**
 * @brief The DockWidget base-class. DockWidget and Controllers::DockWidget are only
 * split in two so we can share some code with the QtQuick implementation,
 * which also derives from Controllers::DockWidget.
 *
 * Do not use instantiate directly in user code. Use DockWidget instead.
 */
class DOCKS_EXPORT DockWidget : public Controller
{
    Q_OBJECT
public:
    typedef QVector<DockWidget *> List;

    /**
     * @brief constructs a new DockWidget
     * @param uniqueName the name of the dockwidget, should be unique. Use title for user visible text.
     * @param options the options controlling certain behaviours
     * @param layoutSaverOptions the options to control save/restore
     *
     * There's no parent argument. The DockWidget is either parented to FloatingWindow or MainWindow
     * when visible, or stays without a parent when hidden.
     */
    explicit DockWidget(View *view, const QString &uniqueName,
                        DockWidgetOptions options = {},
                        LayoutSaverOptions layoutSaverOptions = LayoutSaverOptions());

    ///@brief destructor
    ~DockWidget() override;

    void init();

    /**
     * @brief docks @p other widget into this one. Tabs will be shown if not already.
     * @param other The other dock widget to dock into this one.
     * @param initialOption Allows to specify an InitialOption. Which is useful to add the dock widget
     * as hidden, recording only a placeholder in the tab. So it's restored to tabbed when eventually
     * shown.
     * @sa MainWindow::addDockWidget(), DockWidget::addDockWidgetToContainingWindow()
     */
    void addDockWidgetAsTab(KDDockWidgets::Controllers::DockWidget *other,
                            KDDockWidgets::InitialOption initialOption = {});

    /**
     * @brief docks @p other widget into the window that contains this one.
     *        Equivalent to MainWindow::addDockWidget() with the difference
     *        that it also supports the case where the top-level window is a
     *        FloatingWindow instead of MainWindow.
     *
     * @param other The other dock widget to dock into the window.
     * @param location The location to dock.
     * @param relativeTo The dock widget that the @p location is relative to. If null then the window is considered
     * @param initialOption Allows to specify some extra options that are used while docking.
     * @sa MainWindow::addDockWidget(), DockWidget::addDockWidgetAsTab()
     */
    void
    addDockWidgetToContainingWindow(KDDockWidgets::Controllers::DockWidget *other,
                                    KDDockWidgets::Location location,
                                    KDDockWidgets::Controllers::DockWidget *relativeTo = nullptr,
                                    KDDockWidgets::InitialOption initialOption = {});

    /**
     * @brief sets the widget which this dock widget hosts.
     * @param widget the widget to show inside this dock widget. Must not be null.
     *
     * Ownership for @p widget is transferred to Controllers::DockWidget.
     * Ownsership for any previously existing widget is transferred back to the user. Meaning if you
     * call setWidget(A) followed by setWidget(B) then A will have to be deleted by you, while B is
     * owned by the dock widget.
     */
    virtual void setGuestView(std::shared_ptr<ViewWrapper> guest);

    /// @brief Like widget() but returns a view
    std::shared_ptr<ViewWrapper> guestView() const;

    /**
     * @brief Returns whether the dock widget is floating.
     * Floating means it's not docked and has a window of its own.
     * Note that if you dock a floating dock widget into another floating one
     * then they don't count as floating anymore, as they are
     * side-by-side (or tabbed).
     */
    bool isFloating() const;

    /**
     * @brief setter to make the dock widget float or dock.
     * @param floats If true makes the dock widget float, otherwise docks it.
     *
     * Returns true if the request was accomplished
     */
    bool setFloating(bool floats);

    /// @brief returns the FloatingWindow this widget is in, otherwise nullptr
    FloatingWindow *floatingWindow() const;

    /**
     * @brief Returns the QAction that allows to hide/show the dock widget
     * Useful to put in menus.
     */
    QAction *toggleAction() const;

    /**
     * @brief Returns the QAction that allows to dock/undock the dock widget
     * Useful to put in menus.
     */
    QAction *floatAction() const;

    /**
     * @brief the dock widget's unique name.
     * @internal
     */
    QString uniqueName() const;

    /**
     * @brief Returns the dock widget's title.
     *        This title is visible in title bars and tab bars.
     * @sa setTitle
     */
    QString title() const;

    /**
     * @brief setter for the dock widget's title
     * @param title the dock widget's new title
     * @sa setTitle
     */
    void setTitle(const QString &title);

    /**
     * @brief Returns the size of the dock widget's parent group.
     *
     * This will always be bigger than the DockWidget's size, as there's margins and a title bar.
     * Also, a group can contain more than 1 dock widget (tabbed), meaning the geometry will account
     * for the tab bar and title bar.
     *
     * The position of the rect is in layout coordinates. 0,0 is the top-left of the layout
     * holding the widgets.
     */
    QRect frameGeometry() const;

    /**
     * @brief Returns the dock widget's options which control behaviour.
     * @sa setOptions(), optionsChanged()
     */
    DockWidgetOptions options() const;

    /// @brief returns the per-dockwidget options which will affect LayoutSaver
    /// These are the options which were passed to the constructor
    KDDockWidgets::LayoutSaverOptions layoutSaverOptions() const;

    /**
     * @brief Setter for the options.
     * Only DockWidetOption_NotClosable is allowed to change after construction. For the other options use
     * the constructor only.
     *
     * @sa options(), optionsChanged()
     */
    void setOptions(DockWidgetOptions);

    /**
     * @brief returns if this dock widget is tabbed into another
     *
     * Technically a docked DockWidget always lives in a tab widget, but from the user's perspective
     * it's not tabbed when there's only 1 dock widget, as there are no tabs displayed. Unless
     * the group is using Option_AlwaysShowsTabs, in which case this method will return true regardless
     * if being the single one.
     */
    bool isTabbed() const;

    /**
     * @brief Returns true if this dock widget is the current one in the tab
     *        widget that contains it. If the dock widget is alone then true is
     *        returned, as in this case there will also be a tab widget even
     *        though it's invisible.
     */
    bool isCurrentTab() const;

    /**
     * @brief Makes this dock widget current in its tab group.
     */
    void setAsCurrentTab();

    /**
     * @brief Returns the tab index this dock widget occupies
     * Note that dock widgets are almost always tabbed, even if you don't see the tab bar.
     * A single floating dock widget is still tabbed on a tab widget with a single tab.
     */
    int tabIndex() const;

    /**
     * @brief Returns the index of the current tab of the tab group this dock widget is in.
     */
    int currentTabIndex() const;

    /**
     * @brief Sets an icon to show on title bars and tab bars.
     * @param places Specifies where the icon will be shown (TitleBar, TabBar, ToggleAction, or All)
     *
     * By default there's no icon set.
     *
     * @sa icon()
     */
    void setIcon(const QIcon &icon, IconPlaces places = IconPlace::All);

    /**
     * @brief Returns the dock widget's titlebar, tabbar, or toggle action icon (depending on the passed @p place)
     *
     * By default it's null.
     *
     * @sa setIcon()
     */
    QIcon icon(IconPlace place = IconPlace::TitleBar) const;

    /**
     * @brief Like QWidget::close() but the hosted widget won't be asked if we
     * should close.
     */
    void forceClose();

    /**
     * @brief Returns this dock widget's title bar.
     *
     * Note that several dock widgets can have the same title bar, in case they are tabbed together.
     * Hidden dock widgets have no associated title bar.
     */
    Controllers::TitleBar *titleBar() const;

    /**
     * @brief Returns whether this dock widget is open.
     * Equivalent to calling toggleAction().isChecked() or isVisible()
     */
    bool isOpen() const;

    /**
     * @brief Sets the affinity names. Dock widgets can only dock into dock widgets of the same affinity.
     *
     * By default the affinity is empty and a dock widget can dock into any main window and into any
     * floating window. Usually you won't ever need to call
     * this function, unless you have requirements where certain dock widgets can only dock into
     * certain other dock widgets and main windows. @sa MainWindowBase::setAffinities().
     *
     * Note: Call this function right after creating your dock widget, before adding to a main window and
     * before restoring any layout.
     *
     * Note: Currently you can only call this function once, to keep the code simple and avoid
     * edge cases. This will only be changed if a good use case comes up that requires changing
     * affinities multiple times.
     *
     * @p names the affinity names
     */
    void setAffinities(const QStringList &);

    /// @deprecated @overload
    /// @param name the affinity name
    void setAffinityName(const QString &name);

    /**
     * @brief Returns the affinity name. Empty by default.
     */
    QStringList affinities() const;

    /// @brief Equivalent to QWidget::show(), but it's optimized to reduce flickering on some platforms
    void show();

    /// @brief Brings the dock widget to the front.
    ///
    /// This means:
    /// - If the dock widget is tabbed with other dock widgets but its tab is not current, it's made current.
    /// - If the dock widget is floating, QWindow::raise() is called.
    ///
    /// This only applies if the dock widget is already open. If closed, does nothing.
    void raise();

    /**
     * @brief Returns whether widget() is a KDDockWidget::MainWindow
     *
     * This function doesn't have anything to do with this dock widget being inside a main window or
     * not, but rather the inverse concept. It's not a very popular usage, but some applications
     * want to dock a main window into another main window. This is done by putting it into a
     * dock widget first.
     *
     * See also examples/qtwidgets_dockwidgets -j
     */
    bool isMainWindow() const;

    /**
     * @brief Returns whether this dock widget is docked into a main window (as opposed to floating)
     *
     * Note that isFloating() returning false might either mean the dock widget is docked into a
     * main window or into a floating window (groupped/nested with other dock widgets. Use this function
     * then if you need to disambiguate
     */
    bool isInMainWindow() const;

    /// @brief Returns the main window this dock widget is in. nullptr if it's not inside a main window
    /// Also returns nullptr if it's minimized to a sidebar
    MainWindow *mainWindow() const;

    ///@brief Returns whether This or any child of this dock widget is focused
    /// Not to be confused with QWidget::hasFocus(), which just refers to 1 widget. This includes
    /// variant includes children.
    ///@sa isFocusedChanged()
    bool isFocused() const;

    /**
     * @brief Minimizes this dock widget to the MainWindow's side-bar.
     *
     * It will be undocked from current layout. It's previous docked position will be remembered.
     *
     * This action is only available if the dock widget is docked into a MainWindow.
     * The dockwidget will initially be visible and overlayed on top of the current layout (this is
     * the auto-hide feature).
     */
    void moveToSideBar();

    /// @brief Returns whether this dock widget is overlayed from the side-bar.
    ///
    /// This is only relevant when using the auto-hide and side-bar feature.
    /// Not to be confused with "floating", which means top-level window.
    bool isOverlayed() const;

    ///@brief Returns whether this dock widget is in a side bar, and which.
    /// SideBarLocation::None is returned if it's not in a sidebar.
    /// This is only relevant when using the auto-hide and side-bar feature.
    /// @sa isInSideBar
    SideBarLocation sideBarLocation() const;

    /// @brief Returns where this dockwidget is in a sidebar
    /// Similar to sideBarLocation(), but returns a bool
    bool isInSideBar() const;

    /// @brief Returns whether this floating dock widget knows its previous docked location
    /// Result only makes sense if it's floating.
    ///
    /// When you call dockWidget->setFloating(false) it will only dock if it knows where to.
    bool hasPreviousDockedLocation() const;

    /// @brief returns the last size the widget has when overlayed
    /// Empty otherwise
    QSize lastOverlayedSize() const;


    /// @brief Returns a dock widget by its name
    /// This is the same name you passed to DockWidget CTOR.
    /// nullptr is returned if the dock widget isn't found.
    static DockWidget *byName(const QString &uniqueName);

    /// @brief Returns whether this widget has the LayoutSaverOption::Skip flag
    bool skipsRestore() const;

    /// @brief If this dock widget is floating, then sets its geometry to @p geo.
    ///
    /// If this dock widget is hidden then it stores the geometry so it can be used the next
    /// time it becomes floating.
    ///
    /// This is just convenience, equivalent to calling window()->setGeometry(rect), with the
    /// added bonus of remembering the requested geometry in case it's still hidden.
    void setFloatingGeometry(QRect geo);

    ///@brief Allows the user to set a type on this dock widget
    /// The type is opaque and will not be interpreted by KDDockWidgets.
    /// This type is passed to ViewFactory::createTitleBar(), which the user can override
    /// and return different TitleBar subclasses, depending on the type.
    void setUserType(int userType);
    int userType() const;

    /// @brief Sets this dock widgets position to pos within the MDI layout
    /// This only applies if the main window is in MDI mode, which it is not by default
    void setMDIPosition(QPoint pos);
    /// @brief like setMDIPosition(), but for the size.
    void setMDISize(QSize size);
    /// @brief like setMDIPosition(), but for the Z
    /// only implemented for QtQuick
    void setMDIZ(int z);

    ///@brief Returns whether this dock widget is the main window persistent central widget
    /// This only applies when using MainWindowOption_HasCentralWidget
    bool isPersistentCentralDockWidget() const;

    void onResize(QSize newSize);

Q_SIGNALS:
    ///@brief signal emitted when the parent of the view changed
    void parentViewChanged();

    ///@brief signal emitted when the DockWidget is shown. As in QEvent::Show.
    void shown();

    ///@brief signal emitted when the DockWidget is hidden. As in QEvent::Hide.
    void hidden();

    ///@brief signal emitted when the icon changed
    void iconChanged();

    ///@brief signal emitted when the title changed
    ///@param title the new title
    void titleChanged(const QString &title);

    /// @brief emitted when the hosted guest widget changed
    void guestViewChanged();

    ///@brief emitted when the options change
    ///@sa setOptions(), options()
    void optionsChanged(KDDockWidgets::DockWidgetOptions);

    ///@brief emitted when isFocused changes
    ///@sa isFocused
    void isFocusedChanged(bool);

    ///@brief emitted when isOverlayed changes
    ///@sa isOverlayed
    void isOverlayedChanged(bool);

    ///@brief emitted when isFloating changes
    void isFloatingChanged(bool);

    ///@brief emitted when this dock widget is removed from a side-bar.
    /// Only relevant for the auto-hide/sidebar feature
    void removedFromSideBar();

    ///@brief Emitted when the top-level window this dock widget is in is activated or deactivated
    /// This is convenience to replace tracking dockWidget->window(), since the window changes when
    /// docking and undocking
    ///
    /// It's called 'aboutTo' because it's done in an event filter and the target window doesn't
    /// have it's 'activeWindow' property updated yet at this point.
    void windowActiveAboutToChange(bool activated);

    ///@brief Emitted when the title bar that serves this dock widget changes
    void actualTitleBarChanged();

    /// @brief Emitted when this dock widget is about to be deleted due to Option_DeleteOnClose
    void aboutToDeleteOnClose();

    /// @brief Emitted when this dock widget is about to be deleted
    void aboutToDelete(KDDockWidgets::Controllers::DockWidget *);

public: // TODOm3 make private
    void onParentChanged();
    void onShown(bool spontaneous);
    void onHidden(bool spontaneous);

public:
    /// @brief Returns the private impl d-pointer.
    /// Use at your own risk. Any issues reported involving its usage will be closed.
    class Private;
    Private *dptr() const;
    Private *const d;

    /**
     * @brief Constructs a dock widget from its serialized form.
     * @internal
     */
    static DockWidget *deserialize(const std::shared_ptr<LayoutSaver::DockWidget> &);

private:
    Q_DISABLE_COPY(DockWidget)
};
}
}
Q_DECLARE_METATYPE(KDDockWidgets::Location)

#endif
