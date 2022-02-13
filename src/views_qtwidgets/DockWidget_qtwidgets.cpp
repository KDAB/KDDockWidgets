/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidget_qtwidgets.h"

#include <QCloseEvent>
#include <QVBoxLayout>

/**
 * @file
 * @brief Represents a dock widget.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;
using namespace KDDockWidgets::Views;

class DockWidget_qtwidgets::Private
{
public:
    Private(DockWidget_qtwidgets *q, Controllers::DockWidgetBase *controller)
        : layout(new QVBoxLayout(q))
        , m_controller(controller)
    {
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);

        // propagate the max-size constraints from the guest widget to the DockWidget
        layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    }

    QVBoxLayout *const layout;
    Controllers::DockWidgetBase *const m_controller;
};

DockWidget_qtwidgets::DockWidget_qtwidgets(Controllers::DockWidgetBase *controller,
                                           Qt::WindowFlags windowFlags)
    : View_qtwidgets<QWidget>(controller, Type::DockWidget, nullptr, windowFlags)
    , d(new Private(this, controller))
{
}

DockWidget_qtwidgets::~DockWidget_qtwidgets()
{
    delete d;
}

void DockWidget_qtwidgets::init()
{
    connect(d->m_controller, &DockWidgetBase::widgetChanged, this, [this](QWidget *w) {
        d->layout->addWidget(w);
    });
}

Controllers::DockWidgetBase *DockWidget_qtwidgets::dockWidget() const
{
    return d->m_controller;
}

bool DockWidget_qtwidgets::event(QEvent *e)
{
    if (e->type() == QEvent::ParentChange) {
        d->m_controller->onParentChanged();
    } else if (e->type() == QEvent::Show) {
        d->m_controller->onShown(e->spontaneous());
    } else if (e->type() == QEvent::Hide) {
        d->m_controller->onHidden(e->spontaneous());
    }

    return QWidget::event(e);
}

void DockWidget_qtwidgets::closeEvent(QCloseEvent *e)
{
    d->m_controller->onCloseEvent(e);
}

void DockWidget_qtwidgets::resizeEvent(QResizeEvent *e)
{
    d->m_controller->onResize(e->size());
    return QWidget::resizeEvent(e);
}
