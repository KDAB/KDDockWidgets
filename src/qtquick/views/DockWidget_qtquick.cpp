/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidget_qtquick.h"
#include "ViewFactory.h"

#include "kddockwidgets/controllers/TitleBar.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/DockWidget_p.h"
#include "kddockwidgets/controllers/Frame.h"
#include "qtquick/Platform_qtquick.h"
#include "qtquick/views/TitleBar_qtquick.h"
#include "qtquick/views/Frame_qtquick.h"
#include "qtquick/ViewFactory_qtquick.h"

#include <Config.h>
#include <QQuickItem>

/**
 * @file
 * @brief Represents a dock widget.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;
using namespace KDDockWidgets::Views;

class DockWidget_qtquick::Private
{
public:
    Private(DockWidget_qtquick *view, Controllers::DockWidget *controller, QQmlEngine *qmlengine)
        : q(view)
        , dockWidget(controller)
        , m_visualItem(q->createItem(qmlengine,
                                     plat()->viewFactory()->dockwidgetFilename().toString()))
        , m_qmlEngine(qmlengine)
    {
        Q_ASSERT(m_visualItem);
        m_visualItem->setParent(view);
        m_visualItem->setParentItem(view);
    }

    DockWidget_qtquick *const q;
    Controllers::DockWidget *const dockWidget;
    QQuickItem *const m_visualItem;
    QQmlEngine *const m_qmlEngine;
};

DockWidget_qtquick::DockWidget_qtquick(const QString &uniqueName,
                                       Controllers::DockWidget::Options options,
                                       Controllers::DockWidget::LayoutSaverOptions layoutSaverOptions,
                                       Qt::WindowFlags windowFlags, QQmlEngine *engine)
    : View_qtquick(new DockWidget(this, uniqueName, options, layoutSaverOptions), Type::DockWidget, nullptr, windowFlags)
    , d(new Private(this, static_cast<DockWidget *>(controller()), engine ? engine : plat()->qmlEngine()))
{
    init();
    d->dockWidget->init();
}

DockWidget_qtquick::~DockWidget_qtquick()
{
    delete d;
}

void DockWidget_qtquick::init()
{
    // To mimic what QtWidgets does when creating a new QWidget.
    setVisible(false);

    auto dw = this->dockWidget();
    connect(dw, &Controllers::DockWidget::actualTitleBarChanged,
            this, &DockWidget_qtquick::actualTitleBarChanged);

    connect(dw, &Controllers::DockWidget::guestViewChanged, this, [this, dw] {
        if (auto guest = dw->guestView()) {
            // TODOm3: Move this logic to the controller
            guest->setParent(this);
            guest->setVisible(true);
        }
    });
}

void DockWidget_qtquick::setGuestView(const QString &qmlFilename)
{
    QQuickItem *guest = createItem(d->m_qmlEngine, qmlFilename);
    if (!guest)
        return;

    setGuestView(guest);
}

void DockWidget_qtquick::setGuestView(QQuickItem *widget)
{
    auto wrapper = asQQuickWrapper(widget);
    wrapper->setParent(this);
    makeItemFillParent(widget);
    dockWidget()->setGuestView(wrapper);
}

bool DockWidget_qtquick::event(QEvent *e)
{
    if (e->type() == QEvent::ParentChange) {
        dockWidget()->onParentChanged();
        Q_EMIT dockWidget()->actualTitleBarChanged();
    } else if (e->type() == QEvent::Show) {
        dockWidget()->onShown(e->spontaneous());
    } else if (e->type() == QEvent::Hide) {
        dockWidget()->onHidden(e->spontaneous());
    }

    return View_qtquick::event(e);
}

QSize DockWidget_qtquick::minSize() const
{
    if (auto guestWidget = dockWidget()->guestView()) {
        // The guests min-size is the same as the widget's, there's no spacing or margins.
        return guestWidget->minSize();
    }

    return View_qtquick::minSize();
}

QSize DockWidget_qtquick::maximumSize() const
{
    if (auto guestWidget = dockWidget()->guestView()) {
        // The guests max-size is the same as the widget's, there's no spacing or margins.
        return guestWidget->maximumSize();
    }

    return View_qtquick::maximumSize();
}

Controllers::TitleBar *DockWidget_qtquick::actualTitleBar() const
{
    if (Controllers::Frame *frame = this->frame())
        return frame->actualTitleBar();
    return nullptr;
}

QObject *DockWidget_qtquick::actualTitleBarView() const
{
    if (auto tb = actualTitleBar()) {
        return static_cast<Views::TitleBar_qtquick *>(tb->view());
    }

    return nullptr;
}

QQuickItem *DockWidget_qtquick::frameVisualItem() const
{
    if (Controllers::Frame *frame = this->frame()) {
        if (auto view = asView_qtquick(frame->view()))
            return view->visualItem();
    }

    return nullptr;
}

void DockWidget_qtquick::onGeometryUpdated()
{
    if (auto frame = this->frame()) {
        if (auto view = frame->view()) {
            auto frameView = static_cast<Frame_qtquick *>(asView_qtquick(view));
            frameView->updateConstriants();
            frameView->updateGeometry();
        }
    }
}

Controllers::Frame *DockWidget_qtquick::frame() const
{
    return dockWidget()->dptr()->frame();
}

Controllers::DockWidget *DockWidget_qtquick::dockWidget() const
{
    return d->dockWidget;
}
