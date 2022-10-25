/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidgetViewInterface.h"
#include "kddockwidgets/controllers/Group.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/DockWidget_p.h"

namespace KDDockWidgets::Views {

DockWidgetViewInterface::DockWidgetViewInterface(Controllers::DockWidget *controller)
    : m_dockWidget(controller)
{
}

Controllers::Group *DockWidgetViewInterface::group() const
{
    return m_dockWidget->dptr()->group();
}

Controllers::DockWidget *DockWidgetViewInterface::dockWidget() const
{
    return m_dockWidget;
}

Controllers::TitleBar *DockWidgetViewInterface::actualTitleBar() const
{
    if (Controllers::Group *group = this->group())
        return group->actualTitleBar();
    return nullptr;
}

DockWidgetViewInterface::~DockWidgetViewInterface() = default;

bool DockWidgetViewInterface::isFocused() const
{
    return m_dockWidget->isFocused();
}

bool DockWidgetViewInterface::isFloating() const
{
    return m_dockWidget->isFloating();
}

QString DockWidgetViewInterface::uniqueName() const
{
    return m_dockWidget->uniqueName();
}

QString DockWidgetViewInterface::title() const
{
    return m_dockWidget->title();
}

void DockWidgetViewInterface::setTitle(const QString &title)
{
    m_dockWidget->setTitle(title);
}

void DockWidgetViewInterface::setFloating(bool is)
{
    m_dockWidget->setFloating(is);
}

QAction *DockWidgetViewInterface::toggleAction() const
{
    return m_dockWidget->toggleAction();
}

QAction *DockWidgetViewInterface::floatAction() const
{
    return m_dockWidget->floatAction();
}

void DockWidgetViewInterface::setAsCurrentTab()
{
    m_dockWidget->setAsCurrentTab();
}

bool DockWidgetViewInterface::isOpen() const
{
    return m_dockWidget->isOpen();
}

void DockWidgetViewInterface::forceClose()
{
    m_dockWidget->forceClose();
}

void DockWidgetViewInterface::open()
{
    m_dockWidget->open();
}

void DockWidgetViewInterface::show()
{
    open();
}

void DockWidgetViewInterface::raise()
{
    m_dockWidget->raise();
}

void DockWidgetViewInterface::moveToSideBar()
{
    m_dockWidget->moveToSideBar();
}

void DockWidgetViewInterface::addDockWidgetAsTab(DockWidgetViewInterface *other,
                                                 KDDockWidgets::InitialOption initialOption)
{
    Controllers::DockWidget *dw = other ? other->dockWidget() : nullptr;
    m_dockWidget->addDockWidgetAsTab(dw, initialOption);
}

void DockWidgetViewInterface::addDockWidgetToContainingWindow(
    DockWidgetViewInterface *other, KDDockWidgets::Location location,
    DockWidgetViewInterface *relativeTo, KDDockWidgets::InitialOption initialOption)
{
    Controllers::DockWidget *dw = other ? other->dockWidget() : nullptr;
    Controllers::DockWidget *relativeToDw = relativeTo ? relativeTo->dockWidget() : nullptr;
    m_dockWidget->addDockWidgetToContainingWindow(dw, location, relativeToDw, initialOption);
}

DockWidgetOptions DockWidgetViewInterface::options() const
{
    return m_dockWidget->options();
}

void DockWidgetViewInterface::setOptions(DockWidgetOptions opts)
{
    m_dockWidget->setOptions(opts);
}

void DockWidgetViewInterface::setIcon(const QIcon &icon, IconPlaces places)
{
    m_dockWidget->setIcon(icon, places);
}

QIcon DockWidgetViewInterface::icon(IconPlace place) const
{
    return m_dockWidget->icon(place);
}

void DockWidgetViewInterface::setAffinities(const QStringList &affinities)
{
    m_dockWidget->setAffinities(affinities);
}

void DockWidgetViewInterface::setAffinityName(const QString &name)
{
    m_dockWidget->setAffinityName(name);
}

QStringList DockWidgetViewInterface::affinities() const
{
    return m_dockWidget->affinities();
}

} // namespace
