/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MDILayout.h"
#include "private/multisplitter/ItemFreeContainer_p.h"
#include "Config.h"
#include "kddockwidgets/ViewFactory.h"
#include "controllers/Group.h"
#include "controllers/DockWidget_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

MDILayout::MDILayout(View *parent)
    : Layout(Type::MDILayout, Config::self().viewFactory()->createMDILayout(this, parent))
    , m_rootItem(new Layouting::ItemFreeContainer(view()))
{
    setRootItem(m_rootItem);
}

MDILayout::~MDILayout()
{
}

void MDILayout::addDockWidget(Controllers::DockWidget *dw, QPoint localPt,
                              InitialOption addingOption)
{
    if (!dw) {
        qWarning() << Q_FUNC_INFO << "Refusing to add null dock widget";
        return;
    }

    auto group = qobject_cast<Controllers::Group *>(dw->d->group());
    if (itemForFrame(group) != nullptr) {
        // Item already exists, remove it. See also comment in MultiSplitter::addWidget().
        group->setParentView(nullptr);
        group->setLayoutItem(nullptr);
    }

    Layouting::Item *newItem = new Layouting::Item(view());
    if (group) {
        newItem->setGuestView(group->view());
    } else {
        group = new Controllers::Group();
        group->addTab(dw, addingOption);

        newItem->setGuestView(group->view());
    }

    Q_ASSERT(!newItem->geometry().isEmpty());
    m_rootItem->addDockWidget(newItem, localPt);

    if (addingOption.startsHidden()) {
        delete group;
    }
}

void MDILayout::setDockWidgetGeometry(Controllers::Group *group, QRect geometry)
{
    if (!group)
        return;

    Layouting::Item *item = itemForFrame(group);
    if (!item) {
        qWarning() << Q_FUNC_INFO << "Frame not found in the layout" << group;
        return;
    }

    item->setGeometry(geometry);
}

void MDILayout::moveDockWidget(Controllers::DockWidget *dw, QPoint pos)
{
    moveDockWidget(dw->d->group(), pos);
}

void MDILayout::moveDockWidget(Controllers::Group *group, QPoint pos)
{
    if (!group)
        return;

    Layouting::Item *item = itemForFrame(group);
    if (!item) {
        qWarning() << Q_FUNC_INFO << "Frame not found in the layout" << group;
        return;
    }

    QRect geo = item->geometry();
    geo.moveTopLeft(pos);
    item->setGeometry(geo);
}

void MDILayout::resizeDockWidget(Controllers::DockWidget *dw, QSize size)
{
    resizeDockWidget(dw->d->group(), size);
}

void MDILayout::resizeDockWidget(Controllers::Group *group, QSize size)
{
    if (!group)
        return;

    Layouting::Item *item = itemForFrame(group);
    if (!item) {
        qWarning() << Q_FUNC_INFO << "Group not found in the layout" << group << group->isMDI()
                   << group->isMDIWrapper();
        return;
    }

    item->setSize(size.expandedTo(group->view()->minSize()));
}
