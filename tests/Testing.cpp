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

#include "Testing.h"
#include "MainWindow.h"
#include "DockWidget.h"
#include "DockRegistry_p.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Testing;


class HostedWidget : public QWidget
{
public:

    explicit HostedWidget(QSize minSz = QSize(1,1))
        : m_minSz(minSz)
    {

    }

    QSize sizeHint() const override
    {
        return m_minSz;
    }

    QSize minimumSizeHint() const override
    {
        return m_minSz;
    }

    void setMinSize(QSize s)
    {
        m_minSz = s;
        updateGeometry();
    }

    QSize m_minSz;
};

static MainWindow* createMainWindow(const Testing::MainWindowDescriptor &mwd)
{
    static int count = 0;
    count++;
    auto mainWindow = new MainWindow(QStringLiteral("MainWindow-%1").arg(count), mwd.mainWindowOption);

    mainWindow->setGeometry(mwd.geometry);

    mainWindow->show();
    return mainWindow;
}

static DockWidget* createDockWidget(const Testing::DockWidgetDescriptor &dwd)
{
    static int count = 0;
    count++;
    auto dockWidget = new DockWidget(QStringLiteral("DockWidget-%1").arg(count));

    dockWidget->setWidget(new HostedWidget(dwd.minSize));

    if (dwd.isFloating)
        dockWidget->setGeometry(dwd.geometry);

    if (dwd.isVisible)
        dockWidget->show();

    return dockWidget;
}

static void createLayout(const Layout &layout)
{
    for (const Testing::MainWindowDescriptor &mwd : layout.mainWindows) {
        createMainWindow(mwd);
    }

    for (const Testing::DockWidgetDescriptor &dwd : layout.dockWidgets) {
        createDockWidget(dwd);
    }

}

static void runOperation(const Operation &)
{
}

void Testing::runTest(const Test &test)
{
    if (!DockRegistry::self()->isEmpty())
        qFatal("There's dock widgets and the start runTest");

    createLayout(test.initialLayout);
    for (const auto &op : test.operations) {
        runOperation(op);
    }

    for (MainWindowBase *mw : DockRegistry::self()->mainwindows())
        delete mw;

    for (FloatingWindow *fw : DockRegistry::self()->nestedwindows())
        delete fw;

    for (DockWidgetBase *dw : DockRegistry::self()->dockwidgets())
        delete dw;

    if (!DockRegistry::self()->isEmpty())
        qFatal("There's still dock widgets and the end of runTest");
}
