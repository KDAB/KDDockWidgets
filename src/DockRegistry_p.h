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

#ifndef KD_DOCKREGISTRY_P_H
#define KD_DOCKREGISTRY_P_H

#include "DockWidgetBase.h"
#include "MainWindowBase.h"
#include "FloatingWindow_p.h"

#include <QVector>
#include <QObject>

/**
 * DockRegistry is a singleton that knows about all DockWidgets.
 * It's used so we can restore layouts.
 * It's a private implementation detail.
 */
namespace KDDockWidgets
{

class DOCKS_EXPORT DockRegistry : public QObject
{
    Q_OBJECT
public:
    static DockRegistry *self();
    ~DockRegistry();
    void registerDockWidget(DockWidgetBase *);
    void unregisterDockWidget(DockWidgetBase *);

    void registerMainWindow(MainWindowBase *);
    void unregisterMainWindow(MainWindowBase *);

    void registerNestedWindow(FloatingWindow *);
    void unregisterNestedWindow(FloatingWindow *);

    void registerLayout(MultiSplitterLayout *);
    void unregisterLayout(MultiSplitterLayout *);

    void registerFrame(Frame *);
    void unregisterFrame(Frame *);

    DockWidgetBase *dockByName(const QString &) const;
    MainWindowBase *mainWindowByName(const QString &) const;
    bool isSane() const;

    ///@brief returns all DockWidget instances
    const DockWidgetBase::List dockwidgets() const;

    ///@brief returns all closed DockWidget instances
    const DockWidgetBase::List closedDockwidgets() const;

    ///@brief returns all MainWindow instances
    const MainWindowBase::List mainwindows() const;

    ///@brief returns the list of MultiSplitterLayout instances
    const QVector<MultiSplitterLayout*> layouts() const;

    ///@brief returns a list of all Frame instances
    const Frame::List frames() const;

    ///@brief returns all FloatingWindow instances. Not necessarily all floating dock widgets,
    /// As there might be DockWidgets which weren't morphed yet.
    const QVector<FloatingWindow*> nestedwindows() const;

    ///@brief returns the FloatingWindow with handle @p windowHandle
    FloatingWindow *floatingWindowForHandle(QWindow *windowHandle) const;

    /**
     * @brief Closes all dock widgets, destroys all FloatingWindow, Item and Anchors.
     * This is called before restoring a layout.
     */
    void clear(bool deleteStaticAnchors = false);

    /**
     * @brief Ensures that all floating DockWidgets have a FloatingWindow as a window.
     *
     * This is to simplify things before saving a layout. So we don't have to care about the case
     * where the window is a DockWidget.
     */
    void ensureAllFloatingWidgetsAreMorphed();

    /**
     * @brief returns true if there's 0 dockwidgets, 0 main windows
     */
    bool isEmpty() const;
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
private:
    explicit DockRegistry(QObject *parent = nullptr);
    void maybeDelete();
    DockWidgetBase::List m_dockWidgets;
    MainWindowBase::List m_mainWindows;
    Frame::List m_frames;
    QVector<FloatingWindow*> m_nestedWindows;
    QVector<MultiSplitterLayout*> m_layouts;
};

}

#endif
