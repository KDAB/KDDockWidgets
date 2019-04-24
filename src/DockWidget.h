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

#ifndef KD_DOCKWIDGET_H
#define KD_DOCKWIDGET_H

#include "docks_export.h"
#include "KDDockWidgets.h"
#include "Draggable_p.h"

#include <QVector>
#include <QWidget>
#include <QPointer>

class QAction;

namespace KDDockWidgets {

class Frame;
class TitleBar;
class FloatingWindow;
class DragController;
class TitleBar;

/**
 * Represents something that can be docked.
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

    explicit DockWidget(const QString &name, Options options = {},
                        QWidget *parent = nullptr, Qt::WindowFlags flags = {});
    ~DockWidget() override;

    void addDockWidgetAsTab(DockWidget *other);
    void addDockWidgetToContainingWindow(DockWidget *other, KDDockWidgets::Location,
                                         DockWidget *relativeTo = nullptr);

    void setWidget(QWidget *);
    QWidget *widget() const;
    bool isFloating() const;
    void setFloating(bool);

    QAction *toggleAction() const;
    QString name() const;
    QString title() const;
    void setTitle(const QString &);

    Options options() const;

Q_SIGNALS:
    void parentChanged();
    void shown();
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
