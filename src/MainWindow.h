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
 * @brief QMainWindow wrapper to enable KDDockWidgets support.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_MAINWINDOW_H
#define KD_MAINWINDOW_H

#include "docks_export.h"
#include "KDDockWidgets.h"

#include <QMainWindow>
#include <QVector>

class QDataStream;

namespace KDDockWidgets {

class DockWidget;
class Frame;
class DropArea;
class MultiSplitterLayout;

class DOCKS_EXPORT MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    typedef QVector<MainWindow*> List;
    explicit MainWindow(const QString &name, MainWindowOptions options = MainWindowOption_HasCentralFrame,
                        QWidget *parent = nullptr, Qt::WindowFlags flags = {});
    ~MainWindow() override;
    void addDockWidgetAsTab(DockWidget *);
    void addDockWidget(DockWidget *, KDDockWidgets::Location, DockWidget *relativeTo = nullptr, AddingOption = {});

    QString name() const;
    MainWindowOptions options() const;

    ///@internal
    ///@brief returns the drop area.
    DropArea *dropArea() const;

    ///@internal
    ///@brief returns the MultiSplitterLayout.
    MultiSplitterLayout* multiSplitterLayout() const;

protected:
    bool eventFilter(QObject *, QEvent *) override;

private:
    friend QDataStream &operator<<(QDataStream &ds, MainWindow *);
    friend class LayoutSaver;
    bool fillFromDataStream(QDataStream &ds);

    class Private;
    Private *const d;
};

QDataStream &operator<<(QDataStream &ds, MainWindow *);

}

#endif
