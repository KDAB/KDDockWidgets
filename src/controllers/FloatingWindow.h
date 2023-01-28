/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "../Controller.h"

#include "KDDockWidgets_p.h"
#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/LayoutSaver.h"
#include "kddockwidgets/Qt5Qt6Compat_p.h"
#include "Group.h"
#include "private/Draggable_p.h"

QT_BEGIN_NAMESPACE
class QAbstractNativeEventFilter;
QT_END_NAMESPACE

namespace KDDockWidgets::Controllers {

class DropArea;
class Group;
class Layout;
class MainWindow;
class TitleBar;

class DOCKS_EXPORT FloatingWindow : public Controller, public Draggable
{
    Q_OBJECT
public:
    explicit FloatingWindow(
        QRect suggestedGeometry, MainWindow *parent = nullptr,
        FloatingWindowFlags requestedFlags = FloatingWindowFlag::FromGlobalConfig);
    explicit FloatingWindow(Controllers::Group *group, QRect suggestedGeometry,
                            MainWindow *parent = nullptr);
    virtual ~FloatingWindow() override;

    bool deserialize(const LayoutSaver::FloatingWindow &);
    LayoutSaver::FloatingWindow serialize() const;

    // Draggable:
    std::unique_ptr<WindowBeingDragged> makeWindow() override;
    Controllers::DockWidget *singleDockWidget() const override;
    bool isWindow() const override;

    const QVector<DockWidget *> dockWidgets() const;
    const Controllers::Group::List groups() const;
    DropArea *dropArea() const;

    int userType() const;

    /// @brief Returns whether this window is a tool window
    /// Tool windows don't usually appear in the task bar
    bool isUtilityWindow() const;

    static void ensureRectIsOnScreen(QRect &geometry);

#ifdef Q_OS_WIN
    void setLastHitTest(int hitTest)
    {
        m_lastHitTest = hitTest;
    }
#endif
    /**
     * @brief Returns the title bar.
     *
     * This TitleBar is hidden if we're using a native title bar.
     */
    Controllers::TitleBar *titleBar() const
    {
        return m_titleBar;
    }

    /**
     * @brief Equivalent to setGeometry(), but the value might be adjusted.
     *
     * For example, if the suggestedRect is bigger than max size, we'll make it smaller.
     *
     * @param preserveCenter, if true, then the center is preserved
     *
     */
    void setSuggestedGeometry(QRect suggestedRect,
                              SuggestedGeometryHints = SuggestedGeometryHint_None);

    bool anyNonClosable() const;
    bool anyNonDockable() const;

    /**
     * @brief checks if this FloatingWindow only has one group.
     * If true it means there's no side-by-side dock widgets here. There's only 1 group.
     * Note that despite having only 1 group it can still have multiple DockWidgets,
     * as they can be tabbed into the single group.
     * @return true if this FloatingWindow has a single group.
     */
    bool hasSingleFrame() const;

    /**
     * @brief checks if this FloatingWindow only has one dockwidget.
     * This is a more specific case than hasSingleFrame(), it implies not only a single group,
     * but that group must only have 1 dock widget.
     * @return true if this FloatingWindow only has one dockwidget.
     */
    bool hasSingleDockWidget() const;

    /// @brief If this floating window has only one Frame, it's returned, otherwise nullptr
    Controllers::Group *singleFrame() const;

    /**
     * @brief Returns whether a deleteLater has already been issued
     */
    bool beingDeleted() const;

    /**
     * @brief Equivalent to deleteLater() but sets beingDeleted() to true
     */
    void scheduleDeleteLater();

    /**
     * @brief Returns the MultiSplitter
     */
    Controllers::DropArea *multiSplitter() const;

    /**
     * @brief Returns the Layout
     */
    Layout *layout() const;

    /**
     * @brief Returns whether @p globalPoint is inside the title bar (or, when there's no title-bar,
     * the draggable empty area of a tab bar)
     */
    bool isInDragArea(QPoint globalPoint) const;

    bool isMDI() const override;

    ///@brief updates the title and the icon
    void updateTitleAndIcon();
    void updateTitleBarVisibility();

    QStringList affinities() const;

    /**
     * Returns the drag rect in global coordinates. This is usually the title bar rect.
     * However, when using Config::Flag_HideTitleBarWhenTabsVisible it will be the tab bar
     * background. Returns global coordinates.
     */
    QRect dragRect() const;

    ///@brief Returns whether all dock widgets have the specified option set
    bool allDockWidgetsHave(DockWidgetOption) const;

    ///@brief Returns whether at least one dock widget has the specified option set
    bool anyDockWidgetsHas(DockWidgetOption) const;

    ///@brief Returns whether all dock widgets have the specified  layout saver option set
    bool allDockWidgetsHave(LayoutSaverOption) const;

    ///@brief Returns whether at least one dock widget has the specified layout saver option set
    bool anyDockWidgetsHas(LayoutSaverOption) const;

    /// @brief Adds the dock widget to the specified location
    void addDockWidget(DockWidget *, KDDockWidgets::Location location, DockWidget *relativeTo,
                       InitialOption = {});

    /// @brief Returns the MainWindow which is the transient parent of this FloatingWindow
    /// Can be nullptr if you create dock widgets before the main window. Can also be some
    /// arbitrary value if you have more than one main window.
    MainWindow *mainWindow() const;

    ///@brief Returns the contents margins
    QMargins contentMargins() const;

    // The state reported by QWidget is not always the same as what the
    // window manager thinks, due to the async nature. This method
    // returns the last state reported by the window manager itself.
    WindowState lastWindowManagerState() const;
    void setLastWindowManagerState(WindowState);

    ///@brief Allows the user app to specify which window flags to use, instead of KDDWs default
    /// ones
    /// Bugs caused by this won't be supported, as the amount of combinations that could go wrong
    /// can be open ended
    static Qt::WindowFlags s_windowFlagsOverride;

    /// @brief Returns whether this floating window supports showing a minimize button
    bool supportsMinimizeButton() const;

    /// @brief Returns whether this floating window supports showing a maximize button
    bool supportsMaximizeButton() const;

    void maybeCreateResizeHandler();

Q_SIGNALS:
    void activatedChanged();
    void numFramesChanged();
    void numDockWidgetsChanged();
    void windowStateChanged();

private:
    class Private;
    Private *const d;

protected:
    QPointer<DropArea> m_dropArea;
    Controllers::TitleBar *const m_titleBar;
    WindowState m_lastWindowManagerState = WindowState::None;

private:
    Q_DISABLE_COPY(FloatingWindow)
    QSize maxSizeHint() const;
    void onFrameCountChanged(int count);
    void onVisibleFrameCountChanged(int count);
    void onCloseEvent(QCloseEvent *);
    void updateSizeConstraints();

    bool m_disableSetVisible = false;
    bool m_deleteScheduled = false;
    bool m_inDtor = false;
    bool m_updatingTitleBarVisibility = false;
    QMetaObject::Connection m_layoutDestroyedConnection;
    QAbstractNativeEventFilter *m_nchittestFilter = nullptr;
    WindowState windowStateOverride() const;
#ifdef Q_OS_WIN
    int m_lastHitTest = 0;
#endif
};

}
