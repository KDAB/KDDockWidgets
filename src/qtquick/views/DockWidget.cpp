/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidget.h"
#include "kddockwidgets/ViewFactory.h"

#include "kddockwidgets/core/TitleBar.h"
#include "kddockwidgets/core/DockWidget.h"
#include "kddockwidgets/core/DockWidget_p.h"
#include "kddockwidgets/core/Group.h"
#include "qtquick/Platform.h"
#include "qtquick/views/TitleBar.h"
#include "qtquick/views/Group.h"
#include "qtquick/ViewFactory.h"

#include <Config.h>
#include <QQuickItem>

/**
 * @file
 * @brief Represents a dock widget.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

using namespace KDDockWidgets;
using namespace KDDockWidgets::qtquick;

class qtquick::DockWidget::Private
{
public:
    Private(DockWidget *view, QQmlEngine *qmlengine)
        : q(view)
        , m_visualItem(
              q->createItem(qmlengine, plat()->viewFactory()->dockwidgetFilename().toString()))
        , m_qmlEngine(qmlengine)
    {
        Q_ASSERT(m_visualItem);
        m_visualItem->setParent(view);
        m_visualItem->setParentItem(view);
    }

    DockWidget *const q;
    QQuickItem *const m_visualItem;
    QQmlEngine *const m_qmlEngine;
};

DockWidget::DockWidget(const QString &uniqueName, DockWidgetOptions options,
                       LayoutSaverOptions layoutSaverOptions,
                       Qt::WindowFlags windowFlags, QQmlEngine *engine)
    : View(new Core::DockWidget(this, uniqueName, options, layoutSaverOptions), Core::ViewType::DockWidget,
           nullptr, windowFlags)
    , Core::DockWidgetViewInterface(asDockWidgetController())
    , d(new Private(this, engine ? engine : plat()->qmlEngine()))
{
    init();
    m_dockWidget->init();

    connect(m_dockWidget, &Core::DockWidget::isFloatingChanged, this,
            &DockWidget::isFloatingChanged);
    connect(m_dockWidget, &Core::DockWidget::isFocusedChanged, this,
            &DockWidget::isFocusedChanged);
    connect(m_dockWidget, &Core::DockWidget::titleChanged, this,
            &DockWidget::titleChanged);
    connect(m_dockWidget, &Core::DockWidget::optionsChanged, this,
            &DockWidget::optionsChanged);
}

DockWidget::~DockWidget()
{
    delete d;
}

void DockWidget::init()
{
    // To mimic what QtWidgets does when creating a new QWidget.
    setVisible(false);

    auto dw = this->dockWidget();
    connect(dw, &Core::DockWidget::actualTitleBarChanged, this,
            &DockWidget::actualTitleBarChanged);

    connect(dw, &Core::DockWidget::guestViewChanged, this, [this, dw] {
        if (auto guest = dw->guestView()) {
            guest->setVisible(true);
            Q_EMIT guestItemChanged();
        }
    });
}

void DockWidget::setGuestItem(const QString &qmlFilename)
{
    QQuickItem *guest = createItem(d->m_qmlEngine, qmlFilename);
    if (!guest)
        return;

    setGuestItem(guest);
}

void DockWidget::setGuestItem(QQuickItem *item)
{
    auto wrapper = asQQuickWrapper(item);
    wrapper->setParent(this);
    makeItemFillParent(item);
    dockWidget()->setGuestView(wrapper);
}

QQuickItem *DockWidget::guestItem() const
{
    if (auto guest = m_dockWidget->guestView())
        return dynamic_cast<QQuickItem *>(guest.get());

    return nullptr;
}

bool DockWidget::event(QEvent *e)
{
    if (dockWidget()->d->m_isSettingCurrent)
        return View::event(e);

    if (e->type() == QEvent::Show) {
        dockWidget()->open();
    }

    return View::event(e);
}

QSize DockWidget::minSize() const
{
    if (auto guestWidget = dockWidget()->guestView()) {
        // The guests min-size is the same as the widget's, there's no spacing or margins.
        return guestWidget->minSize();
    }

    return View::minSize();
}

QSize DockWidget::maxSizeHint() const
{
    if (auto guestWidget = dockWidget()->guestView()) {
        // The guests max-size is the same as the widget's, there's no spacing or margins.
        return guestWidget->maxSizeHint();
    }

    return View::maxSizeHint();
}

QObject *DockWidget::actualTitleBarView() const
{
    if (auto tb = actualTitleBar()) {
        return static_cast<qtquick::TitleBar *>(tb->view());
    }

    return nullptr;
}

QQuickItem *DockWidget::groupVisualItem() const
{
    if (Core::Group *group = this->group()) {
        if (auto view = qtquick::asView_qtquick(group->view()))
            return view->visualItem();
    }

    return nullptr;
}

void DockWidget::onGeometryUpdated()
{
    if (auto group = this->group()) {
        if (auto view = group->view()) {
            auto groupView = static_cast<Group *>(qtquick::asView_qtquick(view));
            groupView->updateConstriants();
            groupView->updateGeometry();
        }
    }
}
