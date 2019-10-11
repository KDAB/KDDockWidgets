/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

#include "KDDockWidgets.h"
#include "Operations.h"

#include <QSize>
#include <QRect>
#include <QVector>
#include <QEvent>

/**
 * @file
 * @brief Namespace for tests related enums and classes
 */

namespace KDDockWidgets {
namespace Testing {

    void installFatalMessageHandler();
    void setExpectedWarning(const QString &);

    bool waitForEvent(QWidget *w, QEvent::Type type, int timeout = 2000);
    bool waitForDeleted(QObject *o, int timeout = 2000);
    bool waitForResize(QWidget *w, int timeout = 2000);

    ///@brief Describes a dock widget.
    struct DockWidgetDescriptor {
        typedef QVector<DockWidgetDescriptor> List;
        QSize minSize; // the minSize of the hosted widget
        QRect geometry;
        bool isFloating;
        bool isVisible;
    };

    struct MainWindowDescriptor {
        typedef QVector<MainWindowDescriptor> List;
        QRect geometry;
        MainWindowOption mainWindowOption;
    };

    ///@brief Describes our initial window layout, which will be subject to a test.
    struct Layout {
        typedef QVector<Layout> List;
        MainWindowDescriptor::List mainWindows;
        DockWidgetDescriptor::List dockWidgets;
    };

    /// @brief a test is an initial layout and the list of operations to run on it
    struct Test {
        typedef QVector<Test> List;
        Layout initialLayout;
        Operations::OperationBase::List operations;
    };

    void runTest(const Testing::Test &);
}
}
