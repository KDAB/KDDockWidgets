/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidget_qtwidgets.h"
#include "controllers/DockWidget.h"
#include "ViewWrapper_qtwidgets.h"

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
    Private(DockWidget_qtwidgets *q)
        : layout(new QVBoxLayout(q))
    {
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);

        // propagate the max-size constraints from the guest widget to the DockWidget
        layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    }

    QVBoxLayout *const layout;
};

DockWidget_qtwidgets::DockWidget_qtwidgets(const QString &uniqueName,
                                           DockWidgetOptions options,
                                           LayoutSaverOptions layoutSaverOptions,
                                           Qt::WindowFlags windowFlags)
    : View_qtwidgets<QWidget>(new DockWidget(this, uniqueName, options, layoutSaverOptions), Type::DockWidget, nullptr, windowFlags)
    , Views::DockWidgetViewInterface(asDockWidgetController())
    , d(new Private(this))
{
    init();
    m_dockWidget->init();
}

DockWidget_qtwidgets::~DockWidget_qtwidgets()
{
    delete d;
}

void DockWidget_qtwidgets::init()
{
    connect(m_dockWidget, &Controllers::DockWidget::guestViewChanged, this, [this] {
        if (auto guest = dockWidget()->guestView()) {
            d->layout->addWidget(View_qt::asQWidget(guest.get()));
        }
    });
}

void DockWidget_qtwidgets::setWidget(QWidget *widget)
{
    auto wrapper = widget ? new ViewWrapper_qtwidgets(widget) : nullptr;
    m_dockWidget->setGuestView(std::shared_ptr<View>(wrapper));
}

bool DockWidget_qtwidgets::event(QEvent *e)
{
    if (e->type() == QEvent::ParentChange) {
        m_dockWidget->onParentChanged();
    } else if (e->type() == QEvent::Show) {
        m_dockWidget->onShown(e->spontaneous());
    } else if (e->type() == QEvent::Hide) {
        m_dockWidget->onHidden(e->spontaneous());
    }

    return QWidget::event(e);
}

void DockWidget_qtwidgets::resizeEvent(QResizeEvent *e)
{
    m_dockWidget->onResize(e->size());
    return QWidget::resizeEvent(e);
}

QWidget *DockWidget_qtwidgets::widget() const
{
    if (auto guest = m_dockWidget->guestView())
        return View_qt::asQWidget(guest.get());

    return nullptr;
}
