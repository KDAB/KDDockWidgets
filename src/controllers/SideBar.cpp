/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "SideBar.h"
#include "DockWidget.h"
#include "MainWindow.h"
#include "kddockwidgets/FrameworkWidgetFactory.h"
#include "views/SideBar.h"
#include "Config.h"

#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

SideBar::SideBar(SideBarLocation location, MainWindow *parent)
    : Controller(Type::SideBar, Config::self().frameworkWidgetFactory()->createSideBar(this, parent))
    , m_mainWindow(parent)
    , m_location(location)
    , m_orientation((location == SideBarLocation::North || location == SideBarLocation::South) ? Qt::Horizontal
                                                                                               : Qt::Vertical)
{
    updateSize();
    view()->init();
}

void SideBar::addDockWidget(DockWidget *dw)
{
    if (!dw)
        return;

    if (m_dockWidgets.contains(dw)) {
        qWarning() << Q_FUNC_INFO << "Already contains dock widget" << dw->title();
        return;
    }

    connect(dw, &QObject::destroyed, this, &SideBar::onDockWidgetDestroyed);

    m_dockWidgets << dw;
    dynamic_cast<Views::SideBar *>(view())->addDockWidget_Impl(dw);
    updateSize();
}

void SideBar::removeDockWidget(DockWidget *dw)
{
    if (!m_dockWidgets.contains(dw)) {
        qWarning() << Q_FUNC_INFO << "Doesn't contain dock widget" << dw->title();
        return;
    }

    disconnect(dw, &QObject::destroyed, this, &SideBar::onDockWidgetDestroyed);
    m_dockWidgets.removeOne(dw);
    dynamic_cast<Views::SideBar *>(view())->removeDockWidget_Impl(dw);
    Q_EMIT dw->removedFromSideBar();
    updateSize();
}

bool SideBar::containsDockWidget(DockWidget *dw) const
{
    return m_dockWidgets.contains(dw);
}

void SideBar::onButtonClicked(DockWidget *dw)
{
    toggleOverlay(dw);
}

void SideBar::onDockWidgetDestroyed(QObject *dw)
{
    removeDockWidget(static_cast<DockWidget *>(dw));
}

void SideBar::updateSize()
{
    const int thickness = isEmpty() ? 0 : 30;
    if (isVertical()) {
        view()->setFixedWidth(thickness);
    } else {
        view()->setFixedHeight(thickness);
    }
}

Qt::Orientation SideBar::orientation() const
{
    return m_orientation;
}

bool SideBar::isEmpty() const
{
    return m_dockWidgets.isEmpty();
}

SideBarLocation SideBar::location() const
{
    return m_location;
}

MainWindow *SideBar::mainWindow() const
{
    return m_mainWindow;
}

void SideBar::toggleOverlay(DockWidget *dw)
{
    m_mainWindow->toggleOverlayOnSideBar(dw);
}

QStringList SideBar::serialize() const
{
    QStringList ids;
    ids.reserve(m_dockWidgets.size());
    for (DockWidget *dw : m_dockWidgets)
        ids << dw->uniqueName();

    return ids;
}

void SideBar::clear()
{
    for (DockWidget *dw : qAsConst(m_dockWidgets))
        removeDockWidget(dw);
}
