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

#ifndef KD_FRAME_P_H
#define KD_FRAME_P_H

#include "docks_export.h"
#include "multisplitter/MultiSplitter_p.h"
#include "Draggable_p.h"

#include <QWidget>
#include <QVector>

namespace KDDockWidgets {

class TitleBar;
class TabWidget;
class DropArea;
class DragController;
class FloatingWindow;
class DockWidget;

/**
 * Represents a widget that's docked.
 * Shows a small titlebar so you can drag it out.
 * Also provides a QTabWidget so you can tab dock widgets together
 */
class DOCKS_EXPORT_FOR_UNIT_TESTS Frame : public QWidget
{
    Q_OBJECT
public:
    typedef int Options;
    enum Option {
        Option_None = 0,
        Option_AlwaysShowsTabs = 1,
        Option_IsCentralFrame = 2
    };
    Q_ENUM(Option)

    typedef QList<Frame *> List;
    explicit Frame(QWidget *parent = nullptr, Options = 0);
    ~Frame() override;

    void addWidget(DockWidget *);
    void addWidget(Frame *);
    void addWidget(Draggable *draggable);
    void updateTitleBarVisibility();
    bool containsMouse(QPoint globalPos) const;
    TitleBar *titleBar() const;
    QVector<DockWidget *> dockWidgets() const;
    DockWidget *dockWidgetAt(int index) const;
    void setDropArea(DropArea *);

    bool isTheOnlyFrame() const;

    bool isCentralFrame() const { return m_options & Option_IsCentralFrame; }
    bool alwaysShowsTabs() const { return m_options & Option_AlwaysShowsTabs; }
    int widgetCount() const;
    bool contains(DockWidget *) const;
    QPoint dragPointForWidget(int index) const; // for unit-tests
    void closeEvent(QCloseEvent *) override;
    int currentTabIndex() const;
    void setCurrentTabIndex(int);

    Options options() const { return m_options; }
    quint64 id() const;
    bool anyNonClosable() const;
Q_SIGNALS:
    void currentDockWidgetChanged(KDDockWidgets::DockWidget *);
    void numDockWidgetsChanged();

private:
    Q_DISABLE_COPY(Frame)
    void onDockWidgetCountChanged();
    bool event(QEvent *) override;
    TabWidget *const m_tabWidget;
    TitleBar *const m_titleBar;
    DropArea *m_dropArea = nullptr;
    const Options m_options;
    const quint64 m_id;
};
}

inline QDebug operator<< (QDebug d, KDDockWidgets::Frame *frame)
{
    d << static_cast<QObject*>(frame);
    d << "\n; window=" << frame->window();
    d << "\n; options=" << frame->options();
    d << "\n; dockwidgets=" << frame->dockWidgets();
    return d;
}

#endif
