/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

#ifndef KD_DOCKWIDGET_BASE_H
#define KD_DOCKWIDGET_BASE_H

#include "docks_export.h"
#include "KDDockWidgets.h"
#include "QWidgetAdapter.h"
#include "LayoutSaver_p.h"

#include <QVector>

QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE

namespace Layouting {
class Item;
}

namespace KDDockWidgets {

struct LastPositions;
class Frame;
class FloatingWindow;
class DragController;
class DockRegistry;
class LayoutSaver;
class TabWidget;
class TitleBar;
class MainWindowBase;
class StateDragging;

/**
 * @brief The DockWidget base-class. DockWidget and DockWidgetBase are only
 * split in two so we can share some code with the QtQuick implementation,
 * which also derives from DockWidgetBase.
 *
 * Do not use instantiate directly in user code. Use DockWidget instead.
 */
#ifndef PYTHON_BINDINGS //Pyside bug: https://bugreports.qt.io/projects/PYSIDE/issues/PYSIDE-1327
class DOCKS_EXPORT DockWidgetBase : public QWidgetAdapter
#else
class DOCKS_EXPORT DockWidgetBase : public QWidget
#endif
{
    Q_OBJECT
public:
    typedef QVector<DockWidgetBase *> List;

    ///@brief DockWidget options to pass at construction time
    enum Option {
        Option_None = 0, ///< No option, the default
        Option_NotClosable = 1, /// The DockWidget can't be closed on the [x], only programatically
        Option_NotDockable = 2 ///< The DockWidget can't be docked, it's always floating
    };
    Q_DECLARE_FLAGS(Options, Option)

    enum class IconPlace {
        TitleBar = 1,
        TabBar = 2,
        All = TitleBar | TabBar
    };
    Q_ENUM(IconPlace)
    Q_DECLARE_FLAGS(IconPlaces, IconPlace)

    /**
     * @brief constructs a new DockWidget
     * @param uniqueName the name of the dockwidget, should be unique. Use title for user visible text.
     * @param options optional options controlling behaviour
     *
     * There's no parent argument. The DockWidget is either parented to FloatingWindow or MainWindow
     * when visible, or stays without a parent when hidden.
     */
    explicit DockWidgetBase(const QString &uniqueName, Options options = DockWidgetBase::Options());

    ///@brief destructor
    ~DockWidgetBase() override;

    /**
     * @brief Constructs a dock widget from its serialized form.
     * @internal
     */
    static DockWidgetBase *deserialize(const LayoutSaver::DockWidget::Ptr &);

    /**
     * @brief Serializes this dock widget into an intermediate form
     */
    LayoutSaver::DockWidget::Ptr serialize() const;

    /**
     * @brief docks @p other widget into this one. Tabs will be shown if not already.
     * @param other The other dock widget to dock into this one.
     * @param addingOption Allows to specify an AddingOption. Which is useful to add the dock widget
     * as hidden, recording only a placeholder in the tab. So it's restored to tabbed when eventually
     * shown.
     * @sa MainWindow::addDockWidget(), DockWidget::addDockWidgetToContainingWindow()
     */
    void addDockWidgetAsTab(DockWidgetBase *other, AddingOption addingOption = AddingOption_None);

    /**
     * @brief docks @p other widget into the window that contains this one.
     *        Equivalent to MainWindow::addDockWidget() with the difference
     *        that it also supports the case where the top-level window is a
     *        FloatingWindow instead of MainWindow.
     *
     * @param other The other dock widget to dock into the window.
     * @param location The location to dock.
     * @param relativeTo The dock widget that the @p location is relative to. If null then the window is considered.
     * @sa MainWindow::addDockWidget(), DockWidget::addDockWidgetAsTab()
     */
    void addDockWidgetToContainingWindow(DockWidgetBase *other, KDDockWidgets::Location location,
                                         DockWidgetBase *relativeTo = nullptr);

    /**
     * @brief sets the widget which this dock widget hosts.
     * @param widget the widget to show inside this dock widget. Must not be null.
     *
     * Ownership for @p widget is transferred to DockWidgetBase.
     * Ownsership for any previously existing widget is transferred back to the user. Meaning if you
     * call setWidget(A) followed by setWidget(B) then A will have to be deleted by you, while B is
     * owned by the dock widget.
     */
    void setWidget(QWidgetOrQuick *widget);

    /**
     * @brief returns the widget which this dock widget hosts
     */
    QWidgetOrQuick *widget() const;

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
     */
    void setFloating(bool floats);

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
     * @brief Returns the dock widget's options which control behaviour.
     * @sa setOptions(), optionsChanged()
     */
    Options options() const;

    /**
     * @brief Setter for the options.
     * Only Option_NotClosable is allowed to change after construction. For the other options use
     * the constructor only.
     *
     * @sa options(), optionsChanged()
     */
    void setOptions(Options);

    /**
     * @brief returns if this dock widget is tabbed into another
     *
     * Technically a docked DockWidget always lives in a tab widget, but from the user's prespective
     * it's not tabbed when there's only 1 dock widget, as there are no tabs displayed. Unless
     * the frame is using Option_AlwaysShowsTabs, in which case this method will return true regardless
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
     * @brief Sets an icon to show on title bars and tab bars.
     * @param places Specifies where the icon will be shown (TitleBar, TabBar or both)
     *
     * By default there's no icon set.
     *
     * @sa icon()
     */
    void setIcon(const QIcon &icon, IconPlaces places = IconPlace::All);

    /**
     * @brief Returns the dock widget's titlebar or tabbar icon (depending on the passed @p place)
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
    TitleBar *titleBar() const;

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
     * See also kddockwidgets_example -j
     */
    bool isMainWindow() const;

    ///@brief Returns whether This or any child of this dock widget is focused
    ///Not to be confused with QWidget::hasFocus(), which just refers to 1 widget. This includes
    ///variant includes children.
    ///@sa isFocusedChanged()
    bool isFocused() const;

Q_SIGNALS:
    ///@brief signal emitted when the parent changed
    void parentChanged();

    ///@brief signal emitted when the DockWidget is shown. As in QEvent::Show.
    void shown();

    ///@brief signal emitted when the DockWidget is hidden. As in QEvent::Hide.
    void hidden();

    ///@brief signal emitted when the icon changed
    void iconChanged();

    ///@brief signal emitted when the title changed
    void titleChanged();

    ///@brief emitted when the hosted widget changed
    void widgetChanged(KDDockWidgets::QWidgetOrQuick *);

    ///@brief emitted when the options change
    ///@sa setOptions(), options()
    void optionsChanged(KDDockWidgets::DockWidgetBase::Options);

    ///@brief emitted when isFocused changes
    ///@sa isFocused
    void isFocusedChanged(bool);

protected:
    void onParentChanged();
    void onShown(bool spontaneous);
    void onHidden(bool spontaneous);
    void onClosed(QCloseEvent *e);

#if defined(DOCKS_DEVELOPER_MODE)
public Q_SLOTS:
#else
private Q_SLOTS:
#endif
    /**
     * @brief Creates a FloatingWindow and adds itself into it
     * @return the created FloatingWindow
     */
    KDDockWidgets::FloatingWindow *morphIntoFloatingWindow();

    /// @brief calls morphIntoFloatingWindow() if the dock widget is visible and is a top-level
    /// This is called delayed whenever we show a floating dock widget, so we get a FloatingWindow
    void maybeMorphIntoFloatingWindow();

#if defined(DOCKS_DEVELOPER_MODE)
public:
#else
private:
#endif
    Q_DISABLE_COPY(DockWidgetBase)
    friend class MultiSplitter;
    friend class Frame;
    friend class DropArea;
    friend class TestDocks;
    friend class StateDragging;
    friend class KDDockWidgets::TabWidget;
    friend class KDDockWidgets::TitleBar;
    friend class KDDockWidgets::DragController;
    friend class KDDockWidgets::DockRegistry;
    friend class KDDockWidgets::LayoutSaver;

    /**
     * @brief the Frame which contains this dock widgets.
     *
     * A frame wraps a docked DockWidget, giving it a TabWidget so it can accept other dock widgets.
     * Frame is also the actual class that goes into a MultiSplitter.
     *
     * It's nullptr immediately after creation.
     */
    Frame *frame() const;

    /**
     * @brief returns the FloatingWindow this dock widget is in. If nullptr then it's in a MainWindow.
     *
     * Note: Being in a FloatingWindow doesn't necessarily mean @ref isFloating() returns true, as
     * the dock widget might be in a floating window with other dock widgets side by side.
     */
    FloatingWindow *floatingWindow() const;

    ///@brief adds the current layout item containing this dock widget
    void addPlaceholderItem(Layouting::Item*);

    ///@brief returns the last position, just for tests. TODO Make tests just use the d-pointer.
    LastPositions &lastPositions() const;

    ///@brief If this dock widget is floating, then it saves its geometry
    void saveLastFloatingGeometry();

    ///@brief Updates the floatAction state
    void updateFloatAction();

    class Private;
    Private *const d;
};

}
Q_DECLARE_METATYPE(KDDockWidgets::Location)

#endif
