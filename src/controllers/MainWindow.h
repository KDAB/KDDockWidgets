/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


/**
 * @file
 * @brief The MainWindow base-class that's shared between QtWidgets and QtQuick stack.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_MAINWINDOW_BASE_H
#define KD_MAINWINDOW_BASE_H

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"
#include "kddockwidgets/LayoutSaver.h"
#include "kddockwidgets/Controller.h"

#include <QVector>
#include <QMargins>

class TestDocks;

namespace KDDockWidgets {


namespace Controllers {

class MDILayout;
class DropArea;
class Frame;
class Layout;
class SideBar;
class DockWidget;

/**
 * @brief The MainWindow base-class. MainWindow and MainWindowBase are only
 * split in two so we can share some code with the QtQuick implementation,
 * which also derives from MainWindowBase.
 *
 * Do not use instantiate directly in user code. Use MainWindow instead.
 */
class DOCKS_EXPORT MainWindow : public Controller
{
    Q_OBJECT
    Q_PROPERTY(QStringList affinities READ affinities CONSTANT)
    Q_PROPERTY(QString uniqueName READ uniqueName CONSTANT)
    Q_PROPERTY(KDDockWidgets::MainWindowOptions options READ options CONSTANT)
    Q_PROPERTY(bool isMDI READ isMDI CONSTANT)
public:
    typedef QVector<MainWindow *> List;

    explicit MainWindow(View *view, const QString &uniqueName, MainWindowOptions options);

    ~MainWindow() override;
    void init(const QString &name);

    /**
     * @brief Docks a DockWidget into the central frame, tabbed.
     * @warning Requires that the MainWindow was constructed with MainWindowOption_HasCentralFrame option.
     * @param dockwidget The dockwidget to dock.
     *
     * @sa Controllers::DockWidget::addDockWidgetAsTab()
     */
    Q_INVOKABLE void addDockWidgetAsTab(KDDockWidgets::Controllers::DockWidget *dockwidget);

    /**
     * @brief Docks a DockWidget into this main window.
     * @param dockWidget The dock widget to add into this MainWindow
     * @param location the location where to dock
     * @param relativeTo In case we're docking in relation to another dock widget
     * @param initialOption Allows to specify an InitialOption. Which is useful to add the dock widget
     * as hidden, recording only a placeholder in the tab. So it's restored to tabbed when eventually
     * shown.
     */
    Q_INVOKABLE void addDockWidget(KDDockWidgets::Controllers::DockWidget *dockWidget,
                                   KDDockWidgets::Location location,
                                   KDDockWidgets::Controllers::DockWidget *relativeTo = nullptr,
                                   KDDockWidgets::InitialOption initialOption = {});

    /**
     * @brief Sets a persistent central widget. It can't be detached.
     *
     * Requires passing MainWindowOption_HasCentralWidget in the CTOR.
     * This is similar to the central frame concept of MainWindowOption_HasCentralFrame,
     * with the difference that it won't show a tabs.
     *
     * @param widget The QWidget (or QQuickItem if built with QtQuick support) that you
     * want to set.
     *
     * Example: examples/qtwidgets_dockwidgets --central-widget
     */
    Q_INVOKABLE void setPersistentCentralWidget(std::shared_ptr<ViewWrapper> widget);
    std::shared_ptr<ViewWrapper> persistentCentralWidget() const;

    /**
     * @brief Returns the unique name that was passed via constructor.
     *        Used internally by the save/restore mechanism.
     * @internal
     */
    QString uniqueName() const;


    /// @brief Returns the main window options that were passed via constructor.
    MainWindowOptions options() const;

    ///@internal
    ///@brief returns the drop area.
    DropArea *dropArea() const;

    ///@internal
    ///@brief returns the MultiSplitter.
    DropArea *multiSplitter() const;

    ///@internal
    ///@brief returns the MultiSplitter.
    Layout *layout() const;

    ///@internal
    ///@brief Returns the MDI layout. Or nullptr if this isn't a MDI main window
    MDILayout *mdiLayoutWidget() const;

    /**
     * @brief Sets the affinities names. Dock widgets can only dock into main windows of the same affinity.
     *
     * By default the affinity is empty and a dock widget can dock into any main window. Usually you
     * won't ever need to call this function, unless you have requirements where certain dock widgets
     * can only dock into certain main windows. @sa Controllers::DockWidget::setAffinities().
     *
     * Note: Call this function right after creating your main window, before docking any dock widgets
     * into a main window and before restoring any layout.
     *
     * Note: Currently you can only call this function once, to keep the code simple and avoid
     * edge cases. This will only be changed if a good use case comes up that requires changing
     * affinities multiple times.
     *
     * @p name The affinity names.
     */
    void setAffinities(const QStringList &names);

    /**
     * @brief Returns the list of affinity names. Empty by default.
     */
    QStringList affinities() const;

    /// @brief layouts all the widgets so they have an equal size within their parent container
    ///
    /// Note that the layout is a tree of nested horizontal and vertical container layouts. The
    /// nodes closer to the root will have more space.
    ///
    /// min/max constraints will still be honoured.
    Q_INVOKABLE void layoutEqually();

    /// @brief like layoutEqually() but starts with the container that has @p dockWidget.
    /// While layoutEqually() starts from the root of the layout tree this function starts on a
    /// sub-tree.
    Q_INVOKABLE void layoutParentContainerEqually(KDDockWidgets::Controllers::DockWidget *dockWidget);

    ///@brief Moves the dock widget into one of the MainWindow's sidebar.
    /// Means the dock widget is removed from the layout, and the sidebar shows a button that if pressed
    /// will toggle the dock widget's visibility as an overlay over the layout. This is the auto-hide
    /// functionality.
    ///
    /// The chosen side bar will depend on some heuristics, mostly proximity.
    Q_INVOKABLE void moveToSideBar(KDDockWidgets::Controllers::DockWidget *);

    /// @brief overload that allows to specify which sidebar to use, instead of using heuristics.
    Q_INVOKABLE void moveToSideBar(KDDockWidgets::Controllers::DockWidget *, KDDockWidgets::SideBarLocation);

    /// @brief Removes the dock widget from the sidebar and docks it into the main window again
    Q_INVOKABLE void restoreFromSideBar(KDDockWidgets::Controllers::DockWidget *);

    ///@brief Shows the dock widget overlayed on top of the main window, placed next to the sidebar
    Q_INVOKABLE void overlayOnSideBar(KDDockWidgets::Controllers::DockWidget *);

    ///@brief Shows or hides an overlay. It's assumed the dock widget is already in a side-bar.
    Q_INVOKABLE void toggleOverlayOnSideBar(KDDockWidgets::Controllers::DockWidget *);

    /// @brief closes any overlayed dock widget. The sidebar still displays them as button.
    Q_INVOKABLE void clearSideBarOverlay(bool deleteFrame = true);

    /// @brief Returns the sidebar this dockwidget is in. nullptr if not in any.
    Q_INVOKABLE KDDockWidgets::Controllers::SideBar *
    sideBarForDockWidget(const KDDockWidgets::Controllers::DockWidget *) const;

    /// @brief Returns whether the specified sidebar is visible
    Q_INVOKABLE bool sideBarIsVisible(KDDockWidgets::SideBarLocation) const;

    /// @brief returns the dock widget which is currently overlayed. nullptr if none.
    /// This is only relevant when using the auto-hide and side-bar feature.
    Controllers::DockWidget *overlayedDockWidget() const;

    /// @brief Returns whether any side bar is visible
    bool anySideBarIsVisible() const;

    /// @brief Returns whether this main window is using an MDI layout.
    /// In other words, returns true if MainWindowOption_MDI was passed in the ctor.
    bool isMDI() const;

    /// @brief Closes all dock widgets which are docked into this main window
    /// This is convenience to calling DockWidget::close() individually
    /// If force is true, then the individual dock widgets can't stop the process
    /// Returns false if there's at least one dock widget which rejected closing. Returns true
    /// if all dock widgets were closed (0 or more)
    Q_INVOKABLE bool closeDockWidgets(bool force = false);

    /// @brief Sets the content's margins
    void setContentsMargins(int, int, int, int);

    /// @brief Returns the side bar at the specified location
    Controllers::SideBar *sideBar(SideBarLocation) const;

protected:
    void setUniqueName(const QString &uniqueName);
    QMargins centerWidgetMargins() const;
    QRect centralAreaGeometry() const;

Q_SIGNALS:
    void uniqueNameChanged();

    /// @brief emitted when the number of docked frames changes
    /// Note that we're using the "Frame" nomenculature instead of "DockWidget" here, as DockWidgets
    /// can be tabbed together, in which case this signal isn't emitted.
    void frameCountChanged(int);

private:
    class Private;
    Private *const d;

    friend class ::TestDocks;
    friend class KDDockWidgets::LayoutSaver;
    bool deserialize(const LayoutSaver::MainWindow &);
    LayoutSaver::MainWindow serialize() const;
};
}
}

#endif
