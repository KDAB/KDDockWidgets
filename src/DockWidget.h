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

#ifndef KD_DOCKWIDGET_H
#define KD_DOCKWIDGET_H

#include "docks_export.h"
#include "KDDockWidgets.h"
#include "Draggable_p.h"

#include <QVector>
#include <QWidget>

class QAction;

namespace KDDockWidgets {

class Frame;
class TitleBar;
class FloatingWindow;
class DragController;
class TitleBar;

/**
 * @brief Represents a dock widget.
 */
class DOCKS_EXPORT DockWidget : public QWidget
    , public Draggable
{
    Q_OBJECT
public:
    typedef QVector<DockWidget *> List;

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
     * @param flags optional Qt::WindowFlags to apply to the window
     */
    explicit DockWidget(const QString &name, Options options = {},
                        QWidget *parent = nullptr, Qt::WindowFlags flags = {});

    ///@brief destructor
    ~DockWidget() override;

    /**
     * @brief docks @p other widget into this one. Tabs will be shown.
     * @param other The other dock widget to dock into this one.
     */
    void addDockWidgetAsTab(DockWidget *other);

    /**
     * @brief docks @p other widget into the window that contains this one.
     * @param other The other dock widget to dock into the window.
     * @param location The location to dock.
     * @param relativeTo The dock widget that the @p location is relative to. If null then the window is considered.
     */
    void addDockWidgetToContainingWindow(DockWidget *other, KDDockWidgets::Location location,
                                         DockWidget *relativeTo = nullptr);

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
     * @brief checks if the dock widget is floating. By floating it means it's not docked into the main window.
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
    QString name() const;

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
     * @brief checks if this dock widget is tabbed into another
     * @return true if this dock widget is tabbed into another
     */
    bool isTabbed() const;

Q_SIGNALS:
    ///@brief signal emitted when the parent changed
    void parentChanged();

    ///@brief signal emitted when the DockWidget was shown
    void shown();

    ///@brief signal emitted when the DockWidget was hidden
    void hidden();

protected:
    bool event(QEvent *) override;
    void closeEvent(QCloseEvent *) override;
    std::unique_ptr<WindowBeingDragged> makeWindow() override;
    void paintEvent(QPaintEvent *) override;

#if defined(DOCKS_DEVELOPER_MODE)
public Q_SLOTS:
#else
private Q_SLOTS:
#endif
    KDDockWidgets::FloatingWindow *morphIntoFloatingWindow();

#if defined(DOCKS_DEVELOPER_MODE)
public:
#else
private:
#endif
    Q_DISABLE_COPY(DockWidget)
    friend class DropArea;
    friend class TestDocks;
    friend class KDDockWidgets::DragController;
    friend class KDDockWidgets::TitleBar;
    friend struct KDDockWidgets::WindowBeingDragged;
    TitleBar *titleBar() const;
    Frame *frame() const;
    class Private;
    Private *const d;
};

}

#endif
