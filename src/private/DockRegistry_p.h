/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_DOCKREGISTRY_P_H
#define KD_DOCKREGISTRY_P_H

#include "controllers/DockWidget.h"
#include "controllers/Frame.h"
#include "controllers/MainWindow.h"
#include "Window.h"

#include <QVector>
#include <QObject>
#include <QPointer>

#include "kdbindings/signal.h"

/**
 * DockRegistry is a singleton that knows about all DockWidgets.
 * It's used so we can restore layouts.
 * It's a private implementation detail.
 */
namespace KDDockWidgets {

namespace Controllers {
class FloatingWindow;
class SideBar;
}

class Layout;
class MainWindowMDI;
struct WindowBeingDragged;

class DOCKS_EXPORT DockRegistry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(
        Controllers::Frame *frameInMDIResize READ frameInMDIResize NOTIFY frameInMDIResizeChanged)
public:
    enum class DockByNameFlag
    {
        None = 0,
        ConsultRemapping = 1,
        CreateIfNotFound = 2 ///< Creates the dock widget via the user's widget factory in case it doesn't exist
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

    void registerLayout(Layout *);
    void unregisterLayout(Layout *);

    void registerFrame(Controllers::Frame *);
    void unregisterFrame(Controllers::Frame *);

    Q_INVOKABLE KDDockWidgets::Controllers::DockWidget *focusedDockWidget() const;

    Q_INVOKABLE bool containsDockWidget(const QString &uniqueName) const;
    Q_INVOKABLE bool containsMainWindow(const QString &uniqueName) const;

    Q_INVOKABLE KDDockWidgets::Controllers::DockWidget *dockByName(const QString &,
                                                                   KDDockWidgets::DockRegistry::DockByNameFlags = {}) const;
    Q_INVOKABLE KDDockWidgets::Controllers::MainWindow *mainWindowByName(const QString &) const;
    Q_INVOKABLE KDDockWidgets::MainWindowMDI *mdiMainWindowByName(const QString &) const;

    /// @brief returns the dock widget that hosts @p guest widget. Nullptr if there's none.
    Controllers::DockWidget *dockWidgetForGuest(View *guest) const;

    bool isSane() const;

    ///@brief returns all DockWidget instances
    const Controllers::DockWidget::List dockwidgets() const;

    ///@brief overload returning only the ones with the specified names
    const Controllers::DockWidget::List dockWidgets(const QStringList &names);

    ///@brief returns all closed DockWidget instances
    const Controllers::DockWidget::List closedDockwidgets() const;

    ///@brief returns all MainWindow instances
    const Controllers::MainWindow::List mainwindows() const;

    ///@brief overload returning only the ones with the specified names
    const Controllers::MainWindow::List mainWindows(const QStringList &names);

    ///@brief returns the list of Layout instances
    const QVector<Layout *> layouts() const;

    ///@brief returns a list of all Frame instances
    const QList<Controllers::Frame *> frames() const;

    ///@brief returns all FloatingWindow instances. Not necessarily all floating dock widgets,
    /// As there might be DockWidgets which weren't morphed yet.
    const QVector<Controllers::FloatingWindow *> floatingWindows(bool includeBeingDeleted = false) const;

    ///@brief overload that returns list of QWindow. This is more friendly for supporting both QtWidgets and QtQuick
    const Window::List floatingQWindows() const;

    ///@brief returns whether if there's at least one floating window
    Q_INVOKABLE bool hasFloatingWindows() const;

    ///@brief Returns the window with the specified id
    Window::Ptr windowForHandle(WId id) const;

    ///@brief returns the FloatingWindow with handle @p windowHandle
    Controllers::FloatingWindow *floatingWindowForHandle(Window::Ptr windowHandle) const;

    ///@brief returns the FloatingWindow with handle @p hwnd
    Controllers::FloatingWindow *floatingWindowForHandle(WId hwnd) const;

    ///@brief returns the MainWindow with handle @p windowHandle
    Controllers::MainWindow *mainWindowForHandle(Window::Ptr windowHandle) const;

    ///@brief Returns the list with all visiblye top-level parents of our FloatingWindow and MainWindow instances.
    ///
    /// Typically these are the FloatingWindows and MainWindows themselves. However, since a
    /// MainWindow can be embedded into another widget (for whatever reason, like a QWinWidget),
    /// it means that a top-level can be something else.
    ///
    /// Every returned widget is either a FloatingWindow, MainWindow, or something that contains a MainWindow.
    ///
    /// If @p excludeFloatingDocks is true then FloatingWindow won't be returned
    Window::List topLevels(bool excludeFloatingDocks = false) const;

    /**
     * @brief Closes all dock widgets, and destroys all FloatingWindows
     * This is called before restoring a layout.
     * @param affinities if specified only closes dock widgets and main windows with the specified affinities
     */
    Q_INVOKABLE void clear(const QStringList &affinities = {});

    /**
     * @brief clear Overload that only clears the specified dockWidgets and main windows.
     */
    void clear(const Controllers::DockWidget::List &dockWidgets,
               const Controllers::MainWindow::List &mainWindows,
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
     * @brief Returns whether we're processing a QEvent::Quit
     *
     * Used internally to know if we should let Qt close a NonClosable dock widget at shutdown time.
     */
    bool isProcessingAppQuitEvent() const;

    /**
     * @brief Returns all main windows which match at least one of the @p affinities
     */
    Controllers::MainWindow::List mainWindowsWithAffinity(const QStringList &affinities) const;

    /// @brief Returns the Layout where the specified item is in
    Layout *layoutForItem(const Layouting::Item *) const;

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
    bool isProbablyObscured(Window::Ptr target, Controllers::FloatingWindow *exclude) const;

    /// @overload
    bool isProbablyObscured(Window::Ptr target, WindowBeingDragged *exclude) const;

    ///@brief Returns whether the specified dock widget is in a side bar, and which.
    /// SideBarLocation::None is returned if it's not in a sidebar.
    /// This is only relevant when using the auto-hide and side-bar feature.
    SideBarLocation sideBarLocationForDockWidget(const Controllers::DockWidget *) const;

    ///@brief Overload that returns the SideBar itself
    Controllers::SideBar *sideBarForDockWidget(const Controllers::DockWidget *) const;

    ///@brief Returns the Frame which is being resized in a MDI layout. nullptr if none
    Controllers::Frame *frameInMDIResize() const;

Q_SIGNALS:
    /// @brief emitted when a main window or a floating window change screen
    void windowChangedScreen(Window::Ptr);

    /// @brief emitted when the MDI frame that's being resized changed
    void frameInMDIResizeChanged();

    /// @brief emitted whenever Config::dropIndicatorsInhibited changes
    void dropIndicatorsInhibitedChanged(bool inhibited);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    friend class FocusScope;
    explicit DockRegistry(QObject *parent = nullptr);
    bool onDockWidgetPressed(Controllers::DockWidget *dw, QMouseEvent *);
    void onFocusedViewChanged(std::shared_ptr<ViewWrapper> view);
    void maybeDelete();
    void setFocusedDockWidget(Controllers::DockWidget *);

    bool m_isProcessingAppQuitEvent = false;
    Controllers::DockWidget::List m_dockWidgets;
    Controllers::MainWindow::List m_mainWindows;
    QList<Controllers::Frame *> m_frames;
    QVector<Controllers::FloatingWindow *> m_floatingWindows;
    QVector<Layout *> m_layouts;
    QPointer<Controllers::DockWidget> m_focusedDockWidget;
    KDBindings::ConnectionHandle m_connection;

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
