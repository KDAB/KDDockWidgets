/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file
 * @brief Represents a dock widget.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_DOCKWIDGET_BASE_H
#define KD_DOCKWIDGET_BASE_H

#include "docks_export.h"
#include "KDDockWidgets.h"
#include "QWidgetAdapter.h"

#include <QVector>
#include <QWidget>

class QAction;

namespace KDDockWidgets {

class Frame;
class FloatingWindow;
class DragController;
class Item;
class LastPosition;
class DockRegistry;
class LayoutSaver;
class TabWidget;
class TitleBar;

/**
 * @brief Represents a dock widget.
 */
class DOCKS_EXPORT DockWidgetBase : public QWidgetOrQuick
{
    Q_OBJECT
public:
    typedef QVector<DockWidgetBase *> List;

    enum Option {
        Option_None = 0,
        Option_NotClosable = 1 /// The DockWidget can't be closed on the [x], only programatically
    };
    Q_DECLARE_FLAGS(Options, Option)

    /**
     * @brief constructs a new DockWidgets
     * @param name the name of the dockwidget, should be unique. Use title for user visible text.
     * @param options optional options controlling behaviour
     * @param parent optional QWidget parent, for ownership purposes
     *
     * There's no parent argument. The DockWidget is either parented to FloatingWindow or MainWindow
     * when visible, or stays without a parent when hidden.
     */
    explicit DockWidgetBase(const QString &uniqueName, Options options = {});

    ///@brief destructor
    ~DockWidgetBase() override;

    static DockWidgetBase *createFromDataStream(QDataStream &ds);

    /**
     * @brief docks @p other widget into this one. Tabs will be shown.
     * @param other The other dock widget to dock into this one.
     */
    void addDockWidgetAsTab(DockWidgetBase *other);

    /**
     * @brief docks @p other widget into the window that contains this one.
     * @param other The other dock widget to dock into the window.
     * @param location The location to dock.
     * @param relativeTo The dock widget that the @p location is relative to. If null then the window is considered.
     */
    void addDockWidgetToContainingWindow(DockWidgetBase *other, KDDockWidgets::Location location,
                                         DockWidgetBase *relativeTo = nullptr);

    /**
     * @brief sets the widget which this dock widget contains
     * @param widget to show inside this dock widget
     */
    void setWidget(QWidget *widget);

    /**
     * @brief the widget which this dock widget contains
     * @returns the widget shown inside this dock widget
     */
    QWidget *widget() const;

    /**
     * @brief checks if the dock widget is floating. Floating means it's not docked and has a window of it's own.
     * Note that if you dock a floating dock widget into another floating one then they don't count
     * as floating anymore, as they are side by side (or tabbed).
     * @returns true if the dock widget is floating.
     */
    bool isFloating() const;

    /**
     * @brief setter to make the dock widget float or dock.
     * @param floats Makes the dock widget float or docks it.
     */
    void setFloating(bool floats);

    /**
     * @brief allows to to hide/show the dock widget via a QAction
     * @return a QAction to toggle the visibility
     */
    QAction *toggleAction() const;

    /**
     * @brief the dock widget's unique name.
     * @return the dock widget's unique name.
     * @sa title
     */
    QString uniqueName() const;

    /**
     * @brief the dock widget's title.
     * @return the dock widget's title.
     * @sa name, setTitle
     */
    QString title() const;

    /**
     * @brief setter for the dock widget's title
     * @param title the dock widget's new title
     * @sa name, setTitle
     */
    void setTitle(const QString &title);

    /**
     * @brief the dock widget's options which control behaviour
     * @return the dock widget's options
     */
    Options options() const;

    /**
     * @brief returns if this dock widget is tabbed into another
     *
     * Technically a docked DockWidget always lives in a tab widget, but from the user's prespective
     * it's not tabbed when there's only 1 dock widget, as there are no tabs displayed. Unless
     * the frame is using Option_AlwaysShowsTabs, in which case this method will return true regardless
     * if being the single one.
     *
     * @return true if this dock widget is tabbed into another
     */
    bool isTabbed() const;

    /**
     * @brief Returns true if this dock widget is the current one in the tab widget that contains it.
     *
     * If the dock widget is alone then true is returned, as in this case there will also be a tab widget even though it's invisible.
     */
    bool isCurrentTab() const;

    /**
     * @brief Makes this dock widget current in its tab group.
     */
    void setAsCurrentTab();

    /**
     * @brief Add an icon on titlebar.
     */
    void setIcon(const QIcon &icon);

    /**
     * @return the dock widget's icon.
     */
    QIcon icon() const;

    /**
     * @brief Like QWidget::close() but the hosted widget won't be asked if we should close
     */
    void forceClose();


    /**
     * @brief Returns this dock widget's title bar.
     *
     * Note that several dock widgets can have the same title bar, in case they are tabbed.
     * Hidden dock widgets have no title bar.
     */
    TitleBar *titleBar() const;

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

    ///@brief emitted when the widget changes,
    void widgetChanged(QWidget*);

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
    friend class MultiSplitterLayout;
    friend class Frame;
    friend class DropArea;
    friend class TestDocks;
    friend class Item;
    friend class KDDockWidgets::TabWidget;
    friend class KDDockWidgets::TitleBar;
    friend class KDDockWidgets::DragController;
    friend class KDDockWidgets::Item;
    friend class KDDockWidgets::DockRegistry;
    friend class KDDockWidgets::LayoutSaver;

    friend QDataStream &operator<<(QDataStream &ds, DockWidgetBase *);

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
    void addPlaceholderItem(Item*);

    ///@brief returns the last position, just for tests. TODO Make tests just use the d-pointer.
    LastPosition *lastPosition() const;

    class Private;
    Private *const d;
};

QDataStream &operator<<(QDataStream &ds, DockWidgetBase *);

}

#endif
