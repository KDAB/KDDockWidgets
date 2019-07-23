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
 * @brief A DockWidget wrapper that adds a QTabWidget and a TitleBar.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_FRAME_P_H
#define KD_FRAME_P_H

#include "docks_export.h"
#include "Draggable_p.h"
#include "multisplitter/Item_p.h"

#include <QWidget>
#include <QVector>
#include <QDebug>

namespace KDDockWidgets {

class TitleBar;
class TabWidget;
class DropArea;
class DockWidget;
class Item;

/**
 * @brief A DockWidget wrapper that adds a QTabWidget and a TitleBar
 *
 * Frame is the actual widget that goes into the MultiSplitter. It provides a TitleBar which you
 * can use to detach, and also a QTabWidget so you can tab dock widgets together.
 *
 * This class doesn't actually add window frames and it's never a top-level widget. A Frame is always
 * inside a MultiSplitter (DropArea). Be it a MultiSplitter belonging to a MainWindow or belonging
 * to a FloatingWindow.
 */
class DOCKS_EXPORT_FOR_UNIT_TESTS Frame : public QWidget
{
    Q_OBJECT
public:
    typedef QList<Frame *> List;
    typedef int Options;
    enum Option {
        Option_None = 0,
        Option_AlwaysShowsTabs = 1,
        Option_IsCentralFrame = 2
    };
    Q_ENUM(Option)

    explicit Frame(QWidget *parent = nullptr, Options = Option_None);
    ~Frame() override;

    static Frame *createFromDataStream(QDataStream &ds, MultiSplitterLayout *layout);

    ///@brief Adds a widget into the Frame's TabWidget
    void addWidget(DockWidget *);
    ///@overload
    void addWidget(Frame *);
    ///@overload
    void addWidget(Draggable *draggable);

    ///@brief Inserts a widget into the Frame's TabWidget at @p index
    void insertWidget(DockWidget *, int index);

    ///@brief removes a dockwidget from the frame
    void removeWidget(DockWidget *);

    void updateTitleBarVisibility();
    bool containsMouse(QPoint globalPos) const;
    TitleBar *titleBar() const;
    const QVector<DockWidget *> dockWidgets() const;
    DockWidget *dockWidgetAt(int index) const;
    void setDropArea(DropArea *);

    bool isTheOnlyFrame() const;

    /**
     * @brief Returns whether this frame is floating. A floating frame isn't attached to any other MainWindow,
     * and if it's attached to a FloatingWindow then it's considered floating if it's the only frame in that Window.
     * A floating frame can have multiple dock widgets (tabbed), in which case each DockWidget::isFloating() returns false.
     */
    bool isFloating() const;

    /**
     * @brief Returns whether this frame is docked inside a MainWindow.
     */
    bool isInMainWindow() const;

    /**
     * @brief returns if this widget is the central frame
     * MainWindow supports a mode where the middle frame is persistent even if no dock widget is there.
     *
     * @return whether this widget is the central frame in a main window
     */
    bool isCentralFrame() const { return m_options & Option_IsCentralFrame; }

    /**
     * @brief whether the tab widget will always show tabs, even if there's only 1 dock widget
     *
     * While technically a non-floating dock widget is always tabbed, the user won't see the tabs
     * as in most cases there's only 1 widget tabbed. But for the main window central frame it's
     * often wanted to see tabs even if there's only 1 widget, where each widget represents a "document".
     *
     * @return whether the tab widget will always show tabs, even if there's only 1 dock widget
     */
    bool alwaysShowsTabs() const { return m_options & Option_AlwaysShowsTabs; }


    /// @brief returns the number of dock widgets inside the frame
    int dockWidgetCount() const;

    /// @brief returns whether the dockwidget @p w is inside this frame
    bool contains(DockWidget *w) const;


    /**
     * @brief Puts the Frame back in its previous main window position
     *
     * Usually DockWidget::Private::restoreToPreviousPosition() is used, but
     * when we have a floating frame with tabs we just reuse the frame instead of
     * moving the tabbed dock widgets one by one.
     */
    void restoreToPreviousPosition();

    QPoint dragPointForWidget(int index) const; // for unit-tests
    void closeEvent(QCloseEvent *) override;
    int currentTabIndex() const;
    void setCurrentTabIndex(int);

    Options options() const { return m_options; }
    bool anyNonClosable() const;


    ///@brief returns whether there's 0 dock widgets. If not persistent then the Frame will delete itself.
    bool isEmpty() const { return dockWidgetCount() == 0; }

    ///@brief returns whether there's only 1 dock widget.
    bool hasSingleDockWidget() const { return dockWidgetCount() == 1; }

    ///@brief Called when a dock widget child @p w is shown
    void onDockWidgetShown(DockWidget *w);

    ///@brief Called when a dock widget child @p w is hidden
    void onDockWidgetHidden(DockWidget *w);

    ///@brief sets the layout item that either contains this Frame in the layout or is a placeholder
    void setLayoutItem(Item *item);

    ///@brief returns the layout item that either contains this Frame in the layout or is a placeholder
    Item *layoutItem() const;

    ///@brief For tests-only. Returns the number of Frame instances in the whole application.
    static int dbg_numFrames();

    ///@brief for debug only, prints some debug information
    void dumpDebug();

    void paintEvent(QPaintEvent *) override;

    /**
     * @brief Returns whether a deleteLater has already been issued
     */
    bool beingDeletedLater() const;

Q_SIGNALS:
    void currentDockWidgetChanged(KDDockWidgets::DockWidget *);
    void numDockWidgetsChanged();

private:
    Q_DISABLE_COPY(Frame)
    friend class TestDocks;
    void scheduleDeleteLater();
    void onDockWidgetCountChanged();
    bool event(QEvent *) override;
    TabWidget *const m_tabWidget;
    TitleBar *const m_titleBar;
    DropArea *m_dropArea = nullptr;
    const Options m_options;
    QPointer<Item> m_layoutItem;
    bool m_beingDeleted = false;
};

QDataStream &operator<<(QDataStream &ds, Frame *);

}

inline QDebug operator<< (QDebug d, KDDockWidgets::Frame *frame)
{
    if (frame) {
        d << static_cast<QObject*>(frame);
        d << "; window=" << frame->window();
        d << "; options=" << frame->options();
        d << "; dockwidgets=" << frame->dockWidgets();
    } else {
        d << "nullptr";
    }

    return d;
}

#endif
