/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidget_qtquick.h"
#include "FrameworkWidgetFactory.h"

#include "controllers/TitleBar.h"
#include "controllers/DockWidget.h"
#include "controllers/Frame.h"

#include <Config.h>
#include <QQuickItem>
#include <QCloseEvent>

/**
 * @file
 * @brief Represents a dock widget.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

class DockWidget_qtquick::Private
{
public:
    Private(DockWidget_qtquick *view, QQmlEngine *qmlengine)
        : q(view->m_controller)
        , m_visualItem(q->createItem(qmlengine,
                                     Config::self().frameworkWidgetFactory()->dockwidgetFilename().toString()))
        , m_qmlEngine(qmlengine)
    {
        Q_ASSERT(m_visualItem);
        m_visualItem->setParent(view);
        m_visualItem->setParentItem(view);
    }

    Controllers::DockWidget *const q;
    QQuickItem *const m_visualItem;
    QQmlEngine *const m_qmlEngine;
};

DockWidget_qtquick::DockWidget_qtquick(Controllers::DockWidget *controller,
                                       Qt::WindowFlags windowFlags, QQmlEngine *engine)
    : View_qtquick(controller, Type::DockWidget, nullptr, windowFlags)
    , d(new Private(this, engine ? engine : Config::self().qmlEngine()))
{
    // To mimic what QtWidgets does when creating a new QWidget.
    setVisible(false);
}

DockWidget_qtquick::~DockWidget_qtquick()
{
    delete d;
}

void DockWidget_qtquick::setWidget(const QString &qmlFilename)
{
    QQuickItem *guest = createItem(d->m_qmlEngine, qmlFilename);
    if (!guest)
        return;

    setWidget(guest);
}

void DockWidget_qtquick::setWidget(QWidgetAdapter *widget)
{
    widget->QWidgetAdapter::setParent(this);
    makeItemFillParent(widget);
    DockWidget::setWidget(widget);
}

void DockWidget_qtquick::setWidget(QQuickItem *guest)
{
    auto adapter = new View_qtquick(nullptr, Type::None, this);
    adapter->setIsWrapper();

    // In case the user app needs to use them:
    adapter->setProperty("originalParent", QVariant::fromValue(guest->parent()));
    adapter->setProperty("originalParentItem", QVariant::fromValue(guest->parentItem()));

    guest->setParentItem(adapter);
    guest->setParent(adapter);
    makeItemFillParent(guest);

    setWidget(adapter);
}

bool DockWidget_qtquick::event(QEvent *e)
{
    if (e->type() == QEvent::ParentChange) {
        d->q->onParentChanged();
        Q_EMIT d->q->actualTitleBarChanged();
    } else if (e->type() == QEvent::Show) {
        d->q->onShown(e->spontaneous());
    } else if (e->type() == QEvent::Hide) {
        d->q->onHidden(e->spontaneous());
    } else if (e->type() == QEvent::Close) {
        d->q->onCloseEvent(static_cast<QCloseEvent *>(e));
    }

    return DockWidget_qtquick::event(e);
}

QSize DockWidget_qtquick::minSize() const
{
    if (auto guestWidget = widget()) {
        // The guests min-size is the same as the widget's, there's no spacing or margins.
        return guestWidget->minimumSize();
    }

    return View_qtquick::minSize();
}

QSize DockWidget_qtquick::maximumSize() const
{
    if (auto guestWidget = widget()) {
        // The guests max-size is the same as the widget's, there's no spacing or margins.
        return guestWidget->maximumSize();
    }

    return View_qtquick::maximumSize();
}

QObject *DockWidget_qtquick::actualTitleBar() const
{
    if (Controllers::Frame *frame = d->q->d->frame())
        return frame->actualTitleBar();
    return nullptr;
}

QObject *DockWidget_qtquick::actualTitleBarObj() const
{
    return actualTitleBar();
}

QQuickItem *DockWidget_qtquick::frameVisualItem() const
{
    if (Controllers::Frame *frame = d->q->d->frame()) {
        return frame->visualItem();
    }


    return nullptr;
}

void DockWidget_qtquick::onGeometryUpdated()
{
    if (auto frame = qobject_cast<FrameQuick *>(DockWidgetBase::d->frame())) {
        frame->updateConstriants();
        frame->updateGeometry();
    }
}

Frame *DockWidget_qtquick::frame() const
{
    return qobject_cast<FrameQuick *>(DockWidgetBase::d->frame());
}
