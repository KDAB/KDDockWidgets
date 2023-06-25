/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MDILayout.h"
#include "core/layouting/ItemFreeContainer_p.h"
#include "Config.h"
#include "core/ViewFactory.h"
#include "core/Group.h"
#include "core/DockWidget_p.h"
#include "core/Logging_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

MDILayout::MDILayout(View *parent)
    : Layout(ViewType::MDILayout, Config::self().viewFactory()->createMDILayout(this, parent))
    , m_rootItem(new Core::ItemFreeContainer(view()))
{
    setRootItem(m_rootItem);
}

MDILayout::~MDILayout()
{
}

void MDILayout::addDockWidget(Core::DockWidget *dw, QPoint localPt,
                              InitialOption addingOption)
{
    if (!dw) {
        spdlog::error("Refusing to add null dock widget");
        return;
    }

    auto group = qobject_cast<Core::Group *>(dw->d->group());
    if (itemForFrame(group) != nullptr) {
        // Item already exists, remove it. See also comment in MultiSplitter::addWidget().
        group->setParentView(nullptr);
        group->setLayoutItem(nullptr);
    }

    Core::Item *newItem = new Core::Item(view());
    if (group) {
        newItem->setGuestView(group->view());
    } else {
        group = new Core::Group();
        group->addTab(dw, addingOption);

        newItem->setGuestView(group->view());
    }

    Q_ASSERT(!newItem->geometry().isEmpty());
    m_rootItem->addDockWidget(newItem, localPt);

    if (addingOption.startsHidden()) {
        delete group;
    }
}

void MDILayout::setDockWidgetGeometry(Core::Group *group, QRect geometry)
{
    if (!group)
        return;

    Core::Item *item = itemForFrame(group);
    if (!item) {
        spdlog::error("Group not found in the layout {}", ( void * )group);
        return;
    }

    item->setGeometry(geometry);
}

void MDILayout::moveDockWidget(Core::DockWidget *dw, QPoint pos)
{
    moveDockWidget(dw->d->group(), pos);
}

void MDILayout::moveDockWidget(Core::Group *group, QPoint pos)
{
    if (!group)
        return;

    Core::Item *item = itemForFrame(group);
    if (!item) {
        spdlog::error("Group not found in the layout {}.", ( void * )group);
        return;
    }

    QRect geo = item->geometry();
    geo.moveTopLeft(pos);
    item->setGeometry(geo);
}

void MDILayout::resizeDockWidget(Core::DockWidget *dw, QSize size)
{
    resizeDockWidget(dw->d->group(), size);
}

void MDILayout::resizeDockWidget(Core::Group *group, QSize size)
{
    if (!group)
        return;

    Core::Item *item = itemForFrame(group);
    if (!item) {
        spdlog::error("Group not found in the layout {} isMDI={}, isMDIWrapper={}", ( void * )group, group->isMDI(), group->isMDIWrapper());
        return;
    }

    item->setSize(size.expandedTo(group->view()->minSize()));
}
