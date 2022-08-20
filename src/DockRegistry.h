/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_DOCKREGISTRY_P_H
#define KD_DOCKREGISTRY_P_H

#include "kddockwidgets/KDDockWidgets.h"
#include "kddockwidgets/View.h"
#include "kddockwidgets/private/EventFilterInterface.h"

#include <QVector>
#include <QObject>
#include <QPointer>

#include <memory>

/**
 * DockRegistry is a singleton that knows about all DockWidgets.
 * It's used so we can restore layouts.
 * It's a private implementation detail.
 */
namespace KDDockWidgets {

namespace Controllers {
class FloatingWindow;
class Layout;
class SideBar;
class MainWindow;
class DockWidget;
class Group;
}

namespace Views {
class MainWindowMDIViewInterface;
class MainWindowViewInterface;
}

class MainWindowMDI;
struct WindowBeingDragged;

class DOCKS_EXPORT DockRegistry : public QObject, public EventFilterInterface
{
    Q_OBJECT

public:
    enum class DockByNameFlag {
        None = 0,
        ConsultRemapping = 1,
        CreateIfNotFound =
            2 ///< Creates the dock widget via the user's widget factory in case it doesn't exist
    };
    Q_DECLARE_FLAGS(DockByNameFlags, DockByNameFlag)

    static DockRegistry *self();
    ~DockRegistry();
    void registerDockWidget(Controllers::DockWidget *);
    void unregisterDockWidget(Controllers::DockWidget *);

    void registerMainWindow(Controllers::MainWindow *);
    void unregisterMainWindow(Controllers::MainWindow *);

    void registerFloatingWindow(Controllers::FloatingWindow *);
    void unregisterFloatingWindow(Controllers::FloatingWindow *);

    void registerLayout(Controllers::Layout *);
    void unregisterLayout(Controllers::Layout *);

    void registerGroup(Controllers::Group *);
    void unregisterGroup(Controllers::Group *);

    Q_INVOKABLE KDDockWidgets::Controllers::DockWidget *focusedDockWidget() const;

    Q_INVOKABLE bool containsDockWidget(const QString &uniqueName) const;
    Q_INVOKABLE bool containsMainWindow(const QString &uniqueName) const;

    Q_INVOKABLE KDDockWidgets::Controllers::DockWidget *
    dockByName(const QString &, KDDockWidgets::DockRegistry::DockByNameFlags = {}) const;
    Q_INVOKABLE KDDockWidgets::Controllers::MainWindow *mainWindowByName(const QString &) const;

    bool isSane() const;

    ///@brief returns all DockWidget instances
    const QVector<Controllers::DockWidget *> dockwidgets() const;

    ///@brief overload returning only the ones with the specified names
    const QVector<Controllers::DockWidget *> dockWidgets(const QStringList &names);

    ///@brief returns all closed DockWidget instances
    const QVector<Controllers::DockWidget *> closedDockwidgets() const;

    ///@brief returns all MainWindow instances
    const QVector<Controllers::MainWindow *> mainwindows() const;

    /// @brief returns all MainWindow instances
    /// Like mainwindows(), but with better suited for QtQuick and better terminology
    /// as we're phasing out the "MainWindow" name there
    const QList<Views::MainWindowViewInterface *> mainDockingAreas() const;

    ///@brief overload returning only the ones with the specified names
    const QVector<Controllers::MainWindow *> mainWindows(const QStringList &names);

    ///@brief returns the list of Layout instances
    const QVector<Controllers::Layout *> layouts() const;

    ///@brief returns a list of all Frame instances
    const QList<Controllers::Group *> groups() const;

    ///@brief returns all FloatingWindow instances. Not necessarily all floating dock widgets,
    /// As there might be DockWidgets which weren't morphed yet.
    const QVector<Controllers::FloatingWindow *>
    floatingWindows(bool includeBeingDeleted = false) const;

    ///@brief overload that returns list of QWindow. This is more friendly for supporting both
    /// QtWidgets and QtQuick
    const QVector<std::shared_ptr<Window>> floatingQWindows() const;

    ///@brief returns whether if there's at least one floating window
    Q_INVOKABLE bool hasFloatingWindows() const;

    ///@brief returns the FloatingWindow with handle @p windowHandle
    Controllers::FloatingWindow *
    floatingWindowForHandle(std::shared_ptr<Window> windowHandle) const;

    ///@brief returns the FloatingWindow with handle @p hwnd
    Controllers::FloatingWindow *floatingWindowForHandle(WId hwnd) const;

    ///@brief returns the MainWindow with handle @p windowHandle
    Controllers::MainWindow *mainWindowForHandle(std::shared_ptr<Window> windowHandle) const;

    ///@brief Returns the list with all visiblye top-level parents of our FloatingWindow and
    /// MainWindow instances.
    ///
    /// Typically these are the FloatingWindows and MainWindows themselves. However, since a
    /// MainWindow can be embedded into another widget (for whatever reason, like a QWinWidget),
    /// it means that a top-level can be something else.
    ///
    /// Every returned widget is either a FloatingWindow, MainWindow, or something that contains a
    /// MainWindow.
    ///
    /// If @p excludeFloatingDocks is true then FloatingWindow won't be returned
    QVector<std::shared_ptr<Window>> topLevels(bool excludeFloatingDocks = false) const;

    /**
     * @brief Closes all dock widgets, and destroys all FloatingWindows
     * This is called before restoring a layout.
     * @param affinities if specified only closes dock widgets and main windows with the specified
     * affinities
     */
    Q_INVOKABLE void clear(const QStringList &affinities = {});

    /**
     * @brief clear Overload that only clears the specified dockWidgets and main windows.
     */
    void clear(const QVector<Controllers::DockWidget *> &dockWidgets,
               const QVector<Controllers::MainWindow *> &mainWindows,
               const QStringList &affinities);

    /**
     * @brief Ensures that all floating DockWidgets have a FloatingWindow as a window.
     *
     * This is to simplify things before saving a layout. So we don't have to care about the case
     * where the window is a DockWidget.
     */
    void ensureAllFloatingWidgetsAreMorphed();

    /**
     * @brief returns true if there's 0 dockwidgets, 0 main windows
     *
     * @param excludeBeingDeleted if true, any window currently being deleted won't count
     */
    bool isEmpty(bool excludeBeingDeleted = false) const;

    /**
     * @brief Calls Layout::checkSanity() on all layouts.
     *
     * @param dumpDebug If true then each layout is dumped too
     *
     * This is called by the unit-tests or the fuzzer. If during this the framework spits a
     * qWarning() then the app will qFatal()
     */
    void checkSanityAll(bool dumpDebug = false);

    /**
     * @brief Returns all main windows which match at least one of the @p affinities
     */
    QVector<Controllers::MainWindow *> mainWindowsWithAffinity(const QStringList &affinities) const;

    /// @brief Returns the Layout where the specified item is in
    Controllers::Layout *layoutForItem(const Layouting::Item *) const;

    /// @brief Returns whether the item is in a main window.
    /// Nesting is honoured. (MDIArea inside DropArea inside MainWindow, for example)
    bool itemIsInMainWindow(const Layouting::Item *) const;

    bool affinitiesMatch(const QStringList &affinities1, const QStringList &affinities2) const;

    /// @brief Returns a list of all known main window unique names
    QStringList mainWindowsNames() const;

    /// @brief Returns a list of all known dock widget unique names
    QStringList dockWidgetNames() const;

    /// @brief returns if the specified window has some other window on top (with higher Z)
    /// This is an approximation, as we don't have ways to compare Z, so we mostly intersect
    /// geometries.
    /// @param target The window which we want to know if it's probably obscured
    /// @param exclude This window should not be counted as an obscurer. (It's being dragged).
    bool isProbablyObscured(std::shared_ptr<Window> target,
                            Controllers::FloatingWindow *exclude) const;

    /// @overload
    bool isProbablyObscured(std::shared_ptr<Window> target, WindowBeingDragged *exclude) const;

    ///@brief Returns whether the specified dock widget is in a side bar, and which.
    /// SideBarLocation::None is returned if it's not in a sidebar.
    /// This is only relevant when using the auto-hide and side-bar feature.
    SideBarLocation sideBarLocationForDockWidget(const Controllers::DockWidget *) const;

    ///@brief Overload that returns the SideBar itself
    Controllers::SideBar *sideBarForDockWidget(const Controllers::DockWidget *) const;

    ///@brief Returns the Group which is being resized in a MDI layout. nullptr if none
    Controllers::Group *groupInMDIResize() const;

Q_SIGNALS:
    /// @brief emitted when a main window or a floating window change screen
    void windowChangedScreen(std::shared_ptr<Window>);

    /// @brief emitted when the MDI group that's being resized changed
    void groupInMDIResizeChanged();

    /// @brief emitted whenever Config::dropIndicatorsInhibited changes
    void dropIndicatorsInhibitedChanged(bool inhibited);

private:
    friend class FocusScope;
    explicit DockRegistry(QObject *parent = nullptr);
    bool onDockWidgetPressed(Controllers::DockWidget *dw, QMouseEvent *);
    void onFocusedViewChanged(std::shared_ptr<View> view);
    void maybeDelete();
    void setFocusedDockWidget(Controllers::DockWidget *);

    // EventFilterInterface:
    bool onExposeEvent(std::shared_ptr<Window>) override;
    bool onMouseButtonPress(View *, QMouseEvent *) override;

    class Private;
    Private *const d;

    QVector<Controllers::DockWidget *> m_dockWidgets;
    QVector<Controllers::MainWindow *> m_mainWindows;
    QList<Controllers::Group *> m_groups;
    QVector<Controllers::FloatingWindow *> m_floatingWindows;
    QVector<Controllers::Layout *> m_layouts;
    QPointer<Controllers::DockWidget> m_focusedDockWidget;

    ///@brief Dock widget id remapping, used by LayoutSaver
    ///
    /// When LayoutSaver is trying to restore dock widget "foo", but it doesn't exist, it will
    /// attempt to call a user provided factory function. That function can however return a dock
    /// widget with another ID, such as "bar". When that happens this QHash gets a "foo" : "bar"
    /// entry
    mutable QHash<QString, QString> m_dockWidgetIdRemapping;
};

}

#endif
