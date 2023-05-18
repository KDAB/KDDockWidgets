/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief The GUI counterpart of Frame.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "Group.h"

#include "kddockwidgets/core/Group.h"
#include "kddockwidgets/core/Stack.h"
#include "kddockwidgets/core/TitleBar.h"
#include "kddockwidgets/core/DockWidget.h"
#include "kddockwidgets/core/DockWidget_p.h"

#include "qtquick/ViewFactory.h"
#include "qtquick/Platform.h"
#include "qtquick/views/TabBar.h"
#include "qtquick/views/DockWidget.h"
#include "qtquick/views/ViewWrapper.h"

#include "Stack.h"

#include "Config.h"
#include "core/WidgetResizeHandler_p.h"

#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::qtquick;

Group::Group(Core::Group *controller, QQuickItem *parent)
    : qtquick::View(controller, Core::ViewType::Frame, parent)
    , Core::GroupViewInterface(controller)
{
}

Group::~Group()
{
    disconnect(m_group, &Core::Group::isMDIChanged, this, &Group::isMDIChanged);

    // The QML item must be deleted with deleteLater(), as we might be currently with its mouse
    // handler in the stack. QML doesn't support it being deleted in that case.
    // So unparent it and deleteLater().
    m_visualItem->setParent(nullptr);
    m_visualItem->deleteLater();
}

void Group::init()
{
    connect(m_group->tabBar(), &Core::TabBar::countChanged, this,
            &Group::updateConstriants);

    connect(this, &View::geometryUpdated, this,
            [this] { Core::View::d->layoutInvalidated.emit(); });

    /// QML interface connect, since controllers won't be QObjects for much longer:
    connect(m_group, &Core::Group::isMDIChanged, this, &Group::isMDIChanged);
    connect(m_group->tabBar(), &Core::TabBar::currentDockWidgetChanged, this,
            &Group::currentDockWidgetChanged);

    // Minor hack: While the controllers keep track of "current widget",
    // the QML StackLayout deals in "current index", these can differ when removing a non-current
    // tab. The currentDockWidgetChanged() won't be emitted but the index did decrement.
    // As a workaround, always emit the signal, which is harmless if not needed.
    connect(m_group, &Core::Group::numDockWidgetsChanged, this,
            &Group::currentDockWidgetChanged);

    connect(m_group, &Core::Group::actualTitleBarChanged, this,
            &Group::actualTitleBarChanged);

    connect(this, &View::itemGeometryChanged, this, [this] {
        for (auto dw : m_group->dockWidgets()) {
            auto dwView = static_cast<DockWidget *>(qtquick::asView_qtquick(dw->view()));
            Q_EMIT dwView->groupGeometryChanged(geometry());
        }
    });

    QQmlComponent component(plat()->qmlEngine(), plat()->viewFactory()->groupFilename());

    m_visualItem = static_cast<QQuickItem *>(component.create());

    if (!m_visualItem) {
        qWarning() << Q_FUNC_INFO << "Failed to create item" << component.errorString();
        return;
    }

    m_visualItem->setProperty("groupCpp", QVariant::fromValue(this));
    m_visualItem->setParentItem(this);
    m_visualItem->setParent(this);
}

void Group::updateConstriants()
{
    m_group->onDockWidgetCountChanged();

    // QtQuick doesn't have layouts, so we need to do constraint propagation manually

    setProperty("kddockwidgets_min_size", minSize());
    setProperty("kddockwidgets_max_size", maxSizeHint());

    Core::View::d->layoutInvalidated.emit();
}

void Group::removeDockWidget(Core::DockWidget *dw)
{
    m_group->tabBar()->removeDockWidget(dw);
}

int Group::currentIndex() const
{
    return m_group->currentIndex();
}

void Group::insertDockWidget(Core::DockWidget *dw, int index)
{
    QPointer<Core::Group> oldFrame = dw->d->group();
    m_group->tabBar()->insertDockWidget(index, dw, {}, {});

    dw->setParentView(ViewWrapper::create(m_stackLayout).get());
    makeItemFillParent(View::asQQuickItem(dw->view()));
    m_group->setCurrentDockWidget(dw);

    if (oldFrame && oldFrame->beingDeletedLater()) {
        // give it a push and delete it immediately.
        // Having too many deleteLater() puts us in an inconsistent state. For example if
        // LayoutSaver::saveState() would to be called while the Frame hadn't been deleted yet
        // it would count with that group unless hacks. Also the unit-tests are full of
        // waitForDeleted() due to deleteLater.

        // Ideally we would just remove the deleteLater from Group.cpp, but
        // QTabWidget::insertTab() would crash, as it accesses the old tab-widget we're stealing
        // from

        delete oldFrame;
    }
}

void Group::setStackLayout(QQuickItem *stackLayout)
{
    if (m_stackLayout || !stackLayout) {
        qWarning() << Q_FUNC_INFO << "Shouldn't happen";
        return;
    }

    m_stackLayout = stackLayout;
}

QSize Group::minSize() const
{
    const QSize contentsSize = m_group->dockWidgetsMinSize();
    return contentsSize + QSize(0, nonContentsHeight());
}

QObject *Group::tabBarObj() const
{
    return tabBarView();
}

QQuickItem *Group::visualItem() const
{
    return m_visualItem;
}

int Group::nonContentsHeight() const
{
    return m_visualItem->property("nonContentsHeight").toInt();
}

Stack *Group::stackView() const
{
    if (auto stack = m_group->stack())
        return qobject_cast<Stack *>(asQQuickItem(stack->view()));

    return nullptr;
}

TabBar *Group::tabBarView() const
{
    if (auto tabBar = m_group->tabBar())
        return qobject_cast<TabBar *>(asQQuickItem(tabBar->view()));

    return nullptr;
}

KDDockWidgets::qtquick::TitleBar *Group::titleBar() const
{
    if (auto tb = m_group->titleBar()) {
        return dynamic_cast<KDDockWidgets::qtquick::TitleBar *>(tb->view());
    }

    return nullptr;
}

KDDockWidgets::qtquick::TitleBar *Group::actualTitleBar() const
{
    if (auto tb = m_group->actualTitleBar()) {
        return dynamic_cast<KDDockWidgets::qtquick::TitleBar *>(tb->view());
    }

    return nullptr;
}

int Group::userType() const
{
    /// TODOm3
    return 0;
}