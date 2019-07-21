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

#include "DockWidget.h"
#include "MainWindow.h"
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
    void registerDockWidget(DockWidget *);
    void unregisterDockWidget(DockWidget *);

    void registerMainWindow(MainWindow *);
    void unregisterMainWindow(MainWindow *);

    void registerNestedWindow(FloatingWindow *);
    void unregisterNestedWindow(FloatingWindow *);

    DockWidget *dockByName(const QString &) const;
    MainWindow *mainWindowByName(const QString &) const;
    bool isSane() const;

    DockWidget::List dockwidgets() const;
    MainWindow::List mainwindows() const;
    QVector<FloatingWindow*> nestedwindows() const;

    /**
     * Closes all dock widgets, destroys all FloatingWindow, Item and Anchors.
     * This is called before restoring a layout.
     */
    void clear();

private:
    explicit DockRegistry(QObject *parent = nullptr);
    void maybeDelete();
    bool isEmpty() const;
    DockWidget::List m_dockWidgets;
    MainWindow::List m_mainWindows;
    QVector<FloatingWindow*> m_nestedWindows;
};

}

#endif
