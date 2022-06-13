/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

#include "Frame_qtquick.h"
#include "views/Frame.h"

#include "kddockwidgets/controllers/Frame.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/DockWidget_p.h"

#include "qtquick/ViewFactory_qtquick.h"
#include "qtquick/Platform_qtquick.h"
#include "qtquick/views/DockWidget_qtquick.h"

#include "Stack_qtquick.h"

#include "Config.h"
#include "ViewFactory.h"
#include "Stack_qtquick.h"
#include "private/WidgetResizeHandler_p.h"

#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

Frame_qtquick::Frame_qtquick(Controllers::Frame *controller, QQuickItem *parent)
    : View_qtquick(controller, Type::Frame, parent)
    , m_controller(controller)
{
}

Frame_qtquick::~Frame_qtquick()
{
    // The QML item must be deleted with deleteLater(), as we might be currently with its mouse
    // handler in the stack. QML doesn't support it being deleted in that case.
    // So unparent it and deleteLater().
    m_visualItem->setParent(nullptr);
    m_visualItem->deleteLater();
}

void Frame_qtquick::init()
{
    connect(m_controller->tabWidget(), SIGNAL(countChanged()), /// clazy:exclude=old-style-connect
            this, SLOT(updateConstriants()));

    connect(this, &View_qtquick::geometryUpdated, this, [this] {
        layoutInvalidated.emit();
    });

    /// QML interface connect, since controllers won't be QObjects for much longer:
    connect(m_controller, &Controllers::Frame::isMDIChanged, this, &Frame_qtquick::isMDIChanged);
    connect(m_controller, &Controllers::Frame::currentDockWidgetChanged, this, &Frame_qtquick::currentDockWidgetChanged);
    connect(m_controller, &Controllers::Frame::actualTitleBarChanged, this, &Frame_qtquick::actualTitleBarChanged);

    connect(this, &View_qtquick::itemGeometryChanged, this, [this] {
        for (auto dw : m_controller->dockWidgets()) {
            auto dwView = static_cast<DockWidget_qtquick *>(asView_qtquick(dw->view()));
            dwView->frameGeometryChanged(geometry());
        }
    });

    QQmlComponent component(plat()->qmlEngine(),
                            plat()->viewFactory()->frameFilename());

    m_visualItem = static_cast<QQuickItem *>(component.create());

    if (!m_visualItem) {
        qWarning() << Q_FUNC_INFO << "Failed to create item" << component.errorString();
        return;
    }

    m_visualItem->setProperty("frameCpp", QVariant::fromValue(this));
    m_visualItem->setParentItem(this);
    m_visualItem->setParent(this);
}

void Frame_qtquick::updateConstriants()
{
    m_controller->onDockWidgetCountChanged();

    // QtQuick doesn't have layouts, so we need to do constraint propagation manually

    setProperty("kddockwidgets_min_size", minSize());
    setProperty("kddockwidgets_max_size", maximumSize());

    layoutInvalidated.emit();
}

void Frame_qtquick::removeWidget_impl(Controllers::DockWidget *dw)
{
    stackView()->removeDockWidget(dw);
    disconnect(m_connections.take(dw));
}

int Frame_qtquick::indexOfDockWidget_impl(const Controllers::DockWidget *dw)
{
    return stackView()->indexOfDockWidget(dw);
}

int Frame_qtquick::currentIndex_impl() const
{
    return stackView()->currentIndex();
}

void Frame_qtquick::setCurrentTabIndex_impl(int index)
{
    setCurrentDockWidget_impl(m_controller->dockWidgetAt(index));
}

void Frame_qtquick::setCurrentDockWidget_impl(Controllers::DockWidget *dw)
{
    m_controller->tabWidget()->setCurrentDockWidget(dw);
}

void Frame_qtquick::insertDockWidget_impl(Controllers::DockWidget *dw, int index)
{
    QPointer<Controllers::Frame> oldFrame = dw->d->frame();
    if (stackView()->insertDockWidget(index, dw, {}, {})) {

        asView_qtquick(dw->view())->setParent(m_stackLayout);

        QMetaObject::Connection conn = connect(dw, &Controllers::DockWidget::parentViewChanged, this, [dw, this] {
            if (dw->parent() != m_stackLayout)
                removeWidget_impl(dw);
        });

        m_connections[dw] = conn;
        setCurrentDockWidget_impl(dw);

        if (oldFrame && oldFrame->beingDeletedLater()) {
            // give it a push and delete it immediately.
            // Having too many deleteLater() puts us in an inconsistent state. For example if LayoutSaver::saveState()
            // would to be called while the Frame hadn't been deleted yet it would count with that frame unless hacks.
            // Also the unit-tests are full of waitForDeleted() due to deleteLater.

            // Ideally we would just remove the deleteLater from frame.cpp, but QTabWidget::insertTab()
            // would crash, as it accesses the old tab-widget we're stealing from

            delete oldFrame;
        }
    }
}

Controllers::DockWidget *Frame_qtquick::dockWidgetAt_impl(int index) const
{
    return stackView()->dockwidgetAt(index);
}

Controllers::DockWidget *Frame_qtquick::currentDockWidget_impl() const
{
    return stackView()->currentDockWidget();
}

void Frame_qtquick::renameTab(int, const QString &)
{
    // Not needed for QtQuick. Our model reacts to titleChanged()
}

void Frame_qtquick::changeTabIcon(int index, const QIcon &)
{
    Q_UNUSED(index);
    qDebug() << Q_FUNC_INFO << "Not implemented";
}

void Frame_qtquick::setStackLayout(QQuickItem *stackLayout)
{
    if (m_stackLayout || !stackLayout) {
        qWarning() << Q_FUNC_INFO << "Shouldn't happen";
        return;
    }

    m_stackLayout = stackLayout;
}

QSize Frame_qtquick::minSize() const
{
    const QSize contentsSize = m_controller->dockWidgetsMinSize();
    return contentsSize + QSize(0, nonContentsHeight());
}

QSize Frame_qtquick::maximumSize() const
{
    return View_qtquick::maximumSize();
}

QObject *Frame_qtquick::tabWidgetObj() const
{
    return stackView();
}

QQuickItem *Frame_qtquick::visualItem() const
{
    return m_visualItem;
}

int Frame_qtquick::nonContentsHeight() const
{
    return m_visualItem->property("nonContentsHeight").toInt();
}

Stack_qtquick *Frame_qtquick::stackView() const
{
    if (auto stack = m_controller->tabWidget())
        return qobject_cast<Stack_qtquick *>(asQQuickItem(stack->view()));

    return nullptr;
}

QRect Frame_qtquick::dragRect() const
{
    qFatal("Not implemented");
    return {};
}

bool Frame_qtquick::isMDI() const
{
    return m_controller->isMDI();
}

KDDockWidgets::Views::TitleBar_qtquick *Frame_qtquick::titleBar() const
{
    if (auto tb = m_controller->titleBar()) {
        return dynamic_cast<KDDockWidgets::Views::TitleBar_qtquick *>(tb->view());
    }

    return nullptr;
}

KDDockWidgets::Views::TitleBar_qtquick *Frame_qtquick::actualTitleBar() const
{
    if (auto tb = m_controller->actualTitleBar()) {
        return dynamic_cast<KDDockWidgets::Views::TitleBar_qtquick *>(tb->view());
    }

    return nullptr;
}

int Frame_qtquick::userType() const
{
    /// TODOm3
    return 0;
}

bool Frame_qtquick::event(QEvent *e)
{
    // TODOm3: Move to controller. Too much logic to be here, and it's duplicated
    // with QtWidgets
    if (freed())
        return View_qtquick::event(e);

    if (e->type() == QEvent::ParentChange) {
        auto p = parentView();
        m_controller->setLayout(p ? p->asLayout() : nullptr);
    }

    return View_qtquick::event(e);
}
