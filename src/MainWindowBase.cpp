/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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
#include "Utils_p.h"
#include "Logging_p.h"
#include "DropAreaWithCentralFrame_p.h"
#include "widgets/MultiSplitterLayout_p.h"
#include "widgets/MultiSplitter_p.h"

using namespace KDDockWidgets;

class MainWindowBase::Private
{
public:
    explicit Private(MainWindowOptions options)
        : m_options(options)
    {
    }

    bool supportsCentralFrame() const
    {
        return m_options & MainWindowOption_HasCentralFrame;
    }

    QString name;
    QString affinityName;
    const MainWindowOptions m_options;
};

MainWindowBase::MainWindowBase(const QString &uniqueName, KDDockWidgets::MainWindowOptions options,
                               QWidgetOrQuick *parent, Qt::WindowFlags flags)
    : QMainWindowOrQuick(parent, flags)
    , d(new Private(options))
{
    setUniqueName(uniqueName);
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

    if (widget->affinityName() != affinityName()) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock widget with incompatible affinity."
                   << widget->affinityName() << affinityName();
        return;
    }

    if (widget->options() & DockWidgetBase::Option_NotDockable) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock non-dockable widget" << widget;
        return;
    }

    if (d->supportsCentralFrame()) {
        dropArea()->m_centralFrame->addWidget(widget);
    } else {
        qWarning() << Q_FUNC_INFO << "Not supported without MainWindowOption_HasCentralFrame";
    }
}

void MainWindowBase::addDockWidget(DockWidgetBase *dw, Location location, DockWidgetBase *relativeTo, AddingOption option)
{
    if (dw->options() & DockWidgetBase::Option_NotDockable) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock non-dockable widget" << dw;
        return;
    }

    dropArea()->addDockWidget(dw, location, relativeTo, option);
}

QString MainWindowBase::uniqueName() const
{
    return d->name;
}

MainWindowOptions MainWindowBase::options() const
{
    return d->m_options;
}

MultiSplitterLayout *MainWindowBase::multiSplitterLayout() const
{
    return dropArea()->multiSplitterLayout();
}

void MainWindowBase::setAffinityName(const QString &name)
{
    if (d->affinityName == name)
        return;

    if (!d->affinityName.isEmpty()) {
        qWarning() << Q_FUNC_INFO
                   << "Affinity is already set, refusing to change."
                   << "Submit a feature request with a good justification.";
        return;
    }

    d->affinityName = name;
}

QString MainWindowBase::affinityName() const
{
    return d->affinityName;
}

void MainWindowBase::layoutEqually()
{
    dropArea()->layoutEqually();
}

void MainWindowBase::layoutParentContainerEqually(DockWidgetBase *dockWidget)
{
    dropArea()->layoutParentContainerEqually(dockWidget);
}

void MainWindowBase::setUniqueName(const QString &uniqueName)
{
    if (uniqueName.isEmpty())
        return;

    if (d->name.isEmpty()) {
        d->name = uniqueName;
        Q_EMIT uniqueNameChanged();
        DockRegistry::self()->registerMainWindow(this);
    } else {
        qWarning() << Q_FUNC_INFO << "Already has a name." << this->uniqueName() << uniqueName;
    }
}

bool MainWindowBase::deserialize(const LayoutSaver::MainWindow &mw)
{
    if (mw.options != options()) {
        qWarning() << Q_FUNC_INFO << "Refusing to restore MainWindow with different options"
                   << "; expected=" << mw.options << "; has=" << options();
        return false;
    }

    if (d->affinityName != mw.affinityName) {
        qWarning() << Q_FUNC_INFO << "Affinty name changed from" << d->affinityName
                   << "; to" << mw.affinityName;

        d->affinityName = mw.affinityName;
    }

    return dropArea()->multiSplitterLayout()->deserialize(mw.multiSplitterLayout);
}

LayoutSaver::MainWindow MainWindowBase::serialize() const
{
    LayoutSaver::MainWindow m;

    m.options = options();
    m.geometry = window()->geometry(); // window() as the MainWindow can be embedded
    m.isVisible = isVisible();
    m.uniqueName = uniqueName();
    m.screenIndex = screenNumberForWidget(this);
    m.screenSize = screenSizeForWidget(this);
    m.multiSplitterLayout = dropArea()->multiSplitterLayout()->serialize();
    m.affinityName = d->affinityName;

    return m;
}
