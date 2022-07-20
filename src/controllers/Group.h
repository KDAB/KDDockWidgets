/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/Controller.h"
#include "kddockwidgets/KDDockWidgets.h"
#include "kddockwidgets/FocusScope.h"
#include "DockWidget.h"
#include "kddockwidgets/LayoutSaver.h"

#include "kddockwidgets/docks_export.h"

#include <QVector>
#include <QDebug>
#include <QPointer>

class TestDocks;

namespace KDDockWidgets {
class WidgetResizeHandler;
}

namespace KDDockWidgets::Controllers {

class MDILayout;
class DockWidget;
class FloatingWindow;
class MainWindow;
class Stack;
class TabBar;
class TitleBar;

class DOCKS_EXPORT Group : public Controller, public FocusScope
{
    Q_OBJECT
public:
    typedef QList<Group *> List;

    explicit Group(View *parent = nullptr, FrameOptions = FrameOption_None, int userType = 0);
    virtual ~Group() override;

    static Group *deserialize(const LayoutSaver::Group &);
    LayoutSaver::Group serialize() const;

    ///@brief Adds a widget into the Group's TabWidget
    void addWidget(DockWidget *, InitialOption = {});
    ///@overload
    void addWidget(Group *, InitialOption = {});
    ///@overload
    void addWidget(FloatingWindow *floatingWindow, InitialOption = {});

    ///@brief Inserts a widget into the Group's TabWidget at @p index
    void insertWidget(DockWidget *, int index, InitialOption = {});

    ///@brief removes a dockwidget from the group
    void removeWidget(DockWidget *);

    ///@brief detaches this dock widget
    FloatingWindow *detachTab(DockWidget *);

    ///@brief returns the index of the specified dock widget
    int indexOfDockWidget(const DockWidget *);

    ///@brief returns the index of the current tab
    int currentIndex() const;

    ///@brief sets the current tab index
    void setCurrentTabIndex(int index);

    ///@brief Sets the specified dock widget to be the current tab
    void setCurrentDockWidget(DockWidget *);

    ///@brief Inserts a dock widget into the specified index
    void insertDockWidget(DockWidget *, int index);

    /// @brief Returns the dock widget at @p index
    DockWidget *dockWidgetAt(int index) const;

    ///@brief Returns the current dock widget
    DockWidget *currentDockWidget() const;

    /// @brief returns the number of dock widgets inside the group
    int dockWidgetCount() const;

    /// @brief returns the tab widget
    Controllers::Stack *stack() const;
    Controllers::TabBar *tabBar() const;

    void updateTitleAndIcon();
    void onDockWidgetTitleChanged();
    void updateTitleBarVisibility();
    void updateFloatingActions();
    bool containsMouse(QPoint globalPos) const;
    Controllers::TitleBar *titleBar() const;
    Controllers::TitleBar *actualTitleBar() const;
    QString title() const;
    QIcon icon() const;
    const QVector<DockWidget *> dockWidgets() const;

    bool isTheOnlyFrame() const;

    ///@brief Returns whether this group is overlayed on top of the MainWindow (auto-hide feature);
    bool isOverlayed() const;

    ///@brief clears the FrameOption_IsOverlayed flag.
    /// For example, if you drag a side-bar overlay, then it becomes a normal floating window
    void unoverlay();

    /**
     * @brief Returns whether this group is floating. A floating group isn't attached to any other MainWindow,
     * and if it's attached to a FloatingWindow then it's considered floating if it's the only group in that Window.
     * A floating group can have multiple dock widgets (tabbed), in which case each DockWidget::isFloating() returns false,
     * in which case you can use isInFloatingWindow() which would still return true
     */
    bool isFloating() const;

    /**
     * @brief Returns whether this group is in a FloatingWindow, as opposed to MainWindow.
     *
     * After setup it's equivalent to !isInMainWindow().
     */
    bool isInFloatingWindow() const;

    /**
     * @brief Returns whether this group is docked inside a MainWindow.
     */
    bool isInMainWindow() const;

    /**
     * @brief returns if this widget is the central group
     * MainWindow supports a mode where the middle group is persistent even if no dock widget is there.
     *
     * @return whether this widget is the central group in a main window
     */
    bool isCentralFrame() const
    {
        return m_options & FrameOption_IsCentralFrame;
    }

    /// @brief Returns whether you can DND dock widgets over this group and tab into it
    bool isDockable() const
    {
        return !(m_options & FrameOption_NonDockable);
    }

    /**
     * @brief whether the tab widget will always show tabs, even if there's only 1 dock widget
     *
     * While technically a non-floating dock widget is always tabbed, the user won't see the tabs
     * as in most cases there's only 1 widget tabbed. But for the main window central group it's
     * often wanted to see tabs even if there's only 1 widget, where each widget represents a "document".
     *
     * @return whether the tab widget will always show tabs, even if there's only 1 dock widget
     */
    bool alwaysShowsTabs() const
    {
        return m_options & FrameOption_AlwaysShowsTabs;
    }

    /// @brief returns whether the dockwidget @p w is inside this group
    bool containsDockWidget(DockWidget *w) const;

    ///@brief returns the FloatingWindow this group is in, if any
    FloatingWindow *floatingWindow() const;

    /**
     * @brief Returns the main window this group is in.
     * nullptr if not inside a main window.
     */
    MainWindow *mainWindow() const;

    /**
     * @brief Puts the Group back in its previous main window position
     *
     * Usually DockWidget::Private::restoreToPreviousPosition() is used, but
     * when we have a floating group with tabs we just reuse the group instead of
     * moving the tabbed dock widgets one by one.
     */
    void restoreToPreviousPosition();

    int currentTabIndex() const;

    FrameOptions options() const
    {
        return m_options;
    }
    bool anyNonClosable() const;
    bool anyNonDockable() const;

    ///@brief returns whether there's 0 dock widgets. If not persistent then the Frame will delete itself.
    bool isEmpty() const
    {
        return dockWidgetCount() == 0;
    }

    ///@brief returns whether there's only 1 dock widget.
    bool hasSingleDockWidget() const
    {
        return dockWidgetCount() == 1;
    }

    ///@brief Called when a dock widget child @p w is shown
    void onDockWidgetShown(DockWidget *w);

    ///@brief Called when a dock widget child @p w is hidden
    void onDockWidgetHidden(DockWidget *w);

    ///@brief returns the layout item that either contains this Frame in the layout or is a placeholder
    Layouting::Item *layoutItem() const;

    ///@brief For tests-only. Returns the number of Frame instances in the whole application.
    static int dbg_numFrames();

    /**
     * @brief Returns whether a deleteLater has already been issued
     */
    bool beingDeletedLater() const;

    /**
     * @brief returns true if tabs are visible
     *
     * @sa hasTabsVisibleChanged()
     **/
    bool hasTabsVisible() const;

    QStringList affinities() const;

    ///@brief sets the layout item that either contains this Frame in the layout or is a placeholder
    void setLayoutItem(Layouting::Item *item);

    /**
     * Returns the drag rect in global coordinates. This is usually the title bar rect.
     * However, when using Config::Flag_HideTitleBarWhenTabsVisible it will be the tab bar background.
     * Returns global coordinates.
     */
    virtual QRect dragRect() const;

    ///@brief Returns whether all dock widgets have the specified option set
    bool allDockWidgetsHave(DockWidgetOption) const;

    ///@brief Returns whether at least one dock widget has the specified option set
    bool anyDockWidgetsHas(DockWidgetOption) const;

    ///@brief Returns whether all dock widgets have the specified  layout saver option set
    bool allDockWidgetsHave(LayoutSaverOption) const;

    ///@brief Returns whether at least one dock widget has the specified layout saver option set
    bool anyDockWidgetsHas(LayoutSaverOption) const;

    /// @brief Usually we do resize via the native window manager, but if a widget is docked like
    /// in MDI mode, or in overlayed mode then we allow the user to resize with mouse
    void setAllowedResizeSides(CursorPositions sides);

    /// @brief Returns whether this group is in a MDI layout
    /// Usually no, unless you're using an MDI main window
    bool isMDI() const;

    /// @brief Returns whether this group was created automatically just for the purpose of supporting DockWidget::Option_MDINestable
    bool isMDIWrapper() const;

    /// @brief If this is an MDI wrapper group, return the DockWidget MDI wrapper
    /// @sa isMDIWrapper
    DockWidget *mdiDockWidgetWrapper() const;

    /// @brief If this is an MDI wrapper group, return the DropArea MDI wrapper
    /// @sa isMDIWrapper
    DropArea *mdiDropAreaWrapper() const;

    /// @brief If this group is an MDI wrapper, returns the MDI group. That is the group you actually drag inside the MDI area
    Group *mdiFrame() const;

    /// @brief Returns the MDI layout. Or nullptr if this group isn't in a MDI layout
    MDILayout *mdiLayout() const;

    /// @brief If this group is a MDI group (isMDI() == true), returns whether it contains nested dock widgets (DockWidget::Option_MDINestable)
    /// @sa isMDI()
    bool hasNestedMDIDockWidgets() const;

    /// @brief See Controllers::DockWidget::userType()
    int userType() const;

    /// @brief Returns the resize handler. Used mostly in MDI mode.
    WidgetResizeHandler *resizeHandler() const;

    void renameTab(int index, const QString &);
    void changeTabIcon(int index, const QIcon &);
    /// @brief Sets the Layout which this group is in
    void setLayout(Layout *);

    void setParentView(View *parent) override;

    void onDockWidgetCountChanged();

Q_SIGNALS:
    void numDockWidgetsChanged();
    void hasTabsVisibleChanged();
    void isInMainWindowChanged();
    void isFocusedChanged();
    void focusedWidgetChanged();
    void actualTitleBarChanged();
    void isMDIChanged();

protected:
    void isFocusedChangedCallback() final;
    void focusedWidgetChangedCallback() final;

protected Q_SLOTS:
    void onCurrentTabChanged(int index);

public:
    /**
     * @brief Returns the minimum size of the dock widgets.
     * This might be slightly smaller than Frame::minSize() due to the QTabWidget having some margins
     * and tab bar.
     */
    QSize dockWidgetsMinSize() const;

    /**
     * @brief Returns the biggest combined maxSize of all dock widgets.
     *
     * Example:
     *   dock 1, max=2000x1000
     *   dock 2, max=3000x400
     *   dock3, max=
     *   result=3000,1000
     *
     * Any widget having 16777215x16777215 is ignored (represents not having a max-size, QWIDGETSIZE_MAX)
     */
    QSize biggestDockWidgetMaxSize() const;

    void removeWidget_impl(DockWidget *);
    int indexOfDockWidget_impl(const DockWidget *);
    void setCurrentTabIndex_impl(int index);
    void setCurrentDockWidget_impl(DockWidget *);
    void insertDockWidget_impl(DockWidget *, int index);
    DockWidget *dockWidgetAt_impl(int index) const;
    DockWidget *currentDockWidget_impl() const;
    int nonContentsHeight() const;

private:
    class Private;
    Private *const d;
    bool m_inCtor = true; // Needs to be initialized early, as pointed out by UBSAN
protected:
    bool m_inDtor = false;

    Controllers::Stack *const m_stack;
    Controllers::TitleBar *const m_titleBar;

private:
    Q_DISABLE_COPY(Group)
    friend class ::TestDocks;
    friend class KDDockWidgets::Controllers::Stack;

    void scheduleDeleteLater();
    void onCloseEvent(QCloseEvent *);

    Layout *m_layout = nullptr;
    WidgetResizeHandler *m_resizeHandler = nullptr;
    FrameOptions m_options = FrameOption_None;
    QPointer<Layouting::Item> m_layoutItem;
    bool m_updatingTitleBar = false;
    bool m_beingDeleted = false;
    int m_userType = 0;
};

}
