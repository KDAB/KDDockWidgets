/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidget_qtquick.h"
#include "kddockwidgets/ViewFactory.h"

#include "kddockwidgets/controllers/TitleBar.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/DockWidget_p.h"
#include "kddockwidgets/controllers/Group.h"
#include "qtquick/Platform_qtquick.h"
#include "qtquick/views/TitleBar_qtquick.h"
#include "qtquick/views/Group_qtquick.h"
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
    Private(DockWidget_qtquick *view, QQmlEngine *qmlengine)
        : q(view)
        , m_visualItem(
              q->createItem(qmlengine, plat()->viewFactory()->dockwidgetFilename().toString()))
        , m_qmlEngine(qmlengine)
    {
        Q_ASSERT(m_visualItem);
        m_visualItem->setParent(view);
        m_visualItem->setParentItem(view);
    }

    DockWidget_qtquick *const q;
    QQuickItem *const m_visualItem;
    QQmlEngine *const m_qmlEngine;
};

DockWidget_qtquick::DockWidget_qtquick(const QString &uniqueName, DockWidgetOptions options,
                                       LayoutSaverOptions layoutSaverOptions,
                                       Qt::WindowFlags windowFlags, QQmlEngine *engine)
    : View_qtquick(new DockWidget(this, uniqueName, options, layoutSaverOptions), Type::DockWidget,
                   nullptr, windowFlags)
    , Views::DockWidgetViewInterface(asDockWidgetController())
    , d(new Private(this, engine ? engine : plat()->qmlEngine()))
{
    init();
    m_dockWidget->init();

    connect(m_dockWidget, &Controllers::DockWidget::isFloatingChanged, this,
            &DockWidget_qtquick::isFloatingChanged);
    connect(m_dockWidget, &Controllers::DockWidget::isFocusedChanged, this,
            &DockWidget_qtquick::isFocusedChanged);
    connect(m_dockWidget, &Controllers::DockWidget::titleChanged, this,
            &DockWidget_qtquick::titleChanged);
    connect(m_dockWidget, &Controllers::DockWidget::optionsChanged, this,
            &DockWidget_qtquick::optionsChanged);
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
    connect(dw, &Controllers::DockWidget::actualTitleBarChanged, this,
            &DockWidget_qtquick::actualTitleBarChanged);

    connect(dw, &Controllers::DockWidget::guestViewChanged, this, [this, dw] {
        if (auto guest = dw->guestView()) {
            // TODOm3: Move this logic to the controller
            guest->setParent(this);
            guest->controller()->setVisible(true);

            Q_EMIT guestItemChanged();
        }
    });
}

void DockWidget_qtquick::setGuestItem(const QString &qmlFilename)
{
    QQuickItem *guest = createItem(d->m_qmlEngine, qmlFilename);
    if (!guest)
        return;

    setGuestItem(guest);
}

void DockWidget_qtquick::setGuestItem(QQuickItem *item)
{
    auto wrapper = asQQuickWrapper(item);
    wrapper->setParent(this);
    makeItemFillParent(item);
    dockWidget()->setGuestView(wrapper);
}

QQuickItem *DockWidget_qtquick::guestItem() const
{
    if (auto guest = m_dockWidget->guestView())
        return dynamic_cast<QQuickItem *>(guest.get());

    return nullptr;
}

bool DockWidget_qtquick::event(QEvent *e)
{
    if (dockWidget()->d->m_isSettingCurrent)
        return View_qtquick::event(e);

    if (e->type() == QEvent::Show) {
        dockWidget()->onShown();
    } else if (e->type() == QEvent::Hide) {
        dockWidget()->onHidden();
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

QSize DockWidget_qtquick::maxSizeHint() const
{
    if (auto guestWidget = dockWidget()->guestView()) {
        // The guests max-size is the same as the widget's, there's no spacing or margins.
        return guestWidget->maxSizeHint();
    }

    return View_qtquick::maxSizeHint();
}

QObject *DockWidget_qtquick::actualTitleBarView() const
{
    if (auto tb = actualTitleBar()) {
        return static_cast<Views::TitleBar_qtquick *>(tb->view());
    }

    return nullptr;
}

QQuickItem *DockWidget_qtquick::groupVisualItem() const
{
    if (Controllers::Group *group = this->group()) {
        if (auto view = asView_qtquick(group->view()))
            return view->visualItem();
    }

    return nullptr;
}

void DockWidget_qtquick::onGeometryUpdated()
{
    if (auto group = this->group()) {
        if (auto view = group->view()) {
            auto groupView = static_cast<Group_qtquick *>(asView_qtquick(view));
            groupView->updateConstriants();
            groupView->updateGeometry();
        }
    }
}
