/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018 Sérgio Martins <sergio.martins@kdab.com>

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

#include "MainWindow.h"
#include "DropArea_p.h"
#include "Frame_p.h"
#include "Logging_p.h"
#include "DockRegistry_p.h"
#include "multisplitter/MultiSplitter_p.h"

#include <QPainter>
#include <QApplication>

using namespace KDDockWidgets;

namespace KDDockWidgets {
class DropAreaWithCentralFrame : public DropArea
{
public:
    explicit DropAreaWithCentralFrame(QMainWindow *parent, MainWindowOptions options)
        : DropArea(parent)
        , m_centralFrame(createCentralFrame(options))
    {
        if (m_centralFrame)
            addWidget(m_centralFrame, KDDockWidgets::Location_OnTop, {});
    }

    static Frame* createCentralFrame(MainWindowOptions options)
    {
        return (options & MainWindowOption_HasCentralFrame) ? new Frame(nullptr, Frame::Option_IsCentralFrame | Frame::Option_AlwaysShowsTabs)
                                                            : nullptr;
    }

    ~DropAreaWithCentralFrame();

    Frame *const m_centralFrame = nullptr;
};

DropAreaWithCentralFrame::~DropAreaWithCentralFrame() {}

}

class MainWindow::Private
{
public:
    explicit Private(const QString &mainWindowName, MainWindowOptions options, MainWindow *mainWindow)
        : m_dropArea(new DropAreaWithCentralFrame(mainWindow, options))
        , name(mainWindowName)
        , m_options(options)
    {
    }

    bool supportsCentralFrame() const
    {
        return m_options & MainWindowOption_HasCentralFrame;
    }

    DropAreaWithCentralFrame *const m_dropArea;
    const QString name;
    const MainWindowOptions m_options;
};

MainWindow::MainWindow(const QString &name, MainWindowOptions options,
                       QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
    , d(new Private(name, options, this))
{
    DockRegistry::self()->registerMainWindow(this);
    setCentralWidget(d->m_dropArea);
    // qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    DockRegistry::self()->unregisterMainWindow(this);
    delete d;
}

void MainWindow::addDockWidgetAsTab(DockWidget *widget)
{
    Q_ASSERT(widget);

    if (d->supportsCentralFrame()) {
        d->m_dropArea->m_centralFrame->addWidget(widget);
    } else {
        qWarning() << Q_FUNC_INFO << "Not supported without MainWindowOption_HasCentralFrame";
    }
}

void MainWindow::addDockWidget(DockWidget *dw, Location location, DockWidget *relativeTo)
{
    d->m_dropArea->addDockWidget(dw, location, relativeTo);
}

QString MainWindow::name() const
{
    return d->name;
}

MainWindowOptions MainWindow::options() const
{
    return d->m_options;
}

bool MainWindow::eventFilter(QObject *o, QEvent *e)
{
    qCDebug(globalevents) << "event: " << e->type() << ";receiver=" << o;
    return QMainWindow::eventFilter(o, e);
}
