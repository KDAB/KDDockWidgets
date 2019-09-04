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
 * @brief The MainWindow base class that's shared between QtWidgets and QtQuick stack
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "MainWindowBase.h"
#include "DockRegistry_p.h"
#include "DropArea_p.h"
#include "Frame_p.h"
#include "Logging_p.h"
#include "DropAreaWithCentralFrame_p.h"
#include "multisplitter/MultiSplitterLayout_p.h"
#include "multisplitter/MultiSplitter_p.h"

#include <QDataStream>

using namespace KDDockWidgets;

class MainWindowBase::Private
{
public:
    explicit Private(const QString &mainWindowName, MainWindowOptions options, MainWindowBase *mainWindow)
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

MainWindowBase::MainWindowBase(const QString &uniqueName, KDDockWidgets::MainWindowOptions options,
                               QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
    , d(new Private(uniqueName, options, this))
{
    DockRegistry::self()->registerMainWindow(this);
}

MainWindowBase::~MainWindowBase()
{
    DockRegistry::self()->unregisterMainWindow(this);
    delete d;
}

void MainWindowBase::addDockWidgetAsTab(DockWidgetBase *widget)
{
    Q_ASSERT(widget);
    qCDebug(addwidget) << Q_FUNC_INFO << widget;

    if (d->supportsCentralFrame()) {
        d->m_dropArea->m_centralFrame->addWidget(widget);
    } else {
        qWarning() << Q_FUNC_INFO << "Not supported without MainWindowOption_HasCentralFrame";
    }
}

void MainWindowBase::addDockWidget(DockWidgetBase *dw, Location location, DockWidgetBase *relativeTo, AddingOption option)
{
    d->m_dropArea->addDockWidget(dw, location, relativeTo, option);
}

QString MainWindowBase::uniqueName() const
{
    return d->name;
}

MainWindowOptions MainWindowBase::options() const
{
    return d->m_options;
}

DropArea *MainWindowBase::dropArea() const
{
    return d->m_dropArea;
}

MultiSplitterLayout *MainWindowBase::multiSplitterLayout() const
{
    return d->m_dropArea->multiSplitterLayout();
}


bool MainWindowBase::fillFromDataStream(QDataStream &ds)
{
    int options;
    ds >> options;

    if (options != int(this->options())) {
        qWarning() << Q_FUNC_INFO << "Refusing to restore MainWindow with different options"
                   << "; expected=" << options << "; has=" << this->options();
        return false;
    }

    return dropArea()->multiSplitterLayout()->fillFromDataStream(ds);
}

QDataStream &KDDockWidgets::operator<<(QDataStream &ds, MainWindowBase *mainWindow)
{
    ds << mainWindow->options();
    ds << mainWindow->dropArea()->multiSplitterLayout();

    return ds;
}
