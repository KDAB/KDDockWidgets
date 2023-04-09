/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidget.h"
#include "core/DockWidget.h"
#include "ViewWrapper.h"

#include <QCloseEvent>
#include <QVBoxLayout>

/**
 * @file
 * @brief Represents a dock widget.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

using namespace KDDockWidgets;
using namespace KDDockWidgets::qtwidgets;

class DockWidget::Private
{
public:
    Private(DockWidget *q)
        : layout(new QVBoxLayout(q))
    {
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);

        // propagate the max-size constraints from the guest widget to the DockWidget
        layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    }

    QVBoxLayout *const layout;
};

DockWidget::DockWidget(const QString &uniqueName, DockWidgetOptions options,
                       LayoutSaverOptions layoutSaverOptions,
                       Qt::WindowFlags windowFlags)
    : View_qtwidgets<QWidget>(new Core::DockWidget(this, uniqueName, options, layoutSaverOptions),
                              Core::ViewType::DockWidget, nullptr, windowFlags)
    , Views::DockWidgetViewInterface(asDockWidgetController())
    , d(new Private(this))
{
    init();
    m_dockWidget->init();
}

DockWidget::~DockWidget()
{
    delete d;
}

void DockWidget::init()
{
    connect(m_dockWidget, &Core::DockWidget::guestViewChanged, this, [this] {
        if (auto guest = dockWidget()->guestView()) {
            d->layout->addWidget(View_qt::asQWidget(guest.get()));
        }
    });
}

void DockWidget::setWidget(QWidget *widget)
{
    m_dockWidget->setGuestView(ViewWrapper_qtwidgets::create(widget));
}

bool DockWidget::event(QEvent *e)
{
    if (e->type() == QEvent::Show)
        m_dockWidget->open();

    return QWidget::event(e);
}

void DockWidget::resizeEvent(QResizeEvent *e)
{
    m_dockWidget->onResize(e->size());
    QWidget::resizeEvent(e);
}

QWidget *DockWidget::widget() const
{
    if (auto guest = m_dockWidget->guestView())
        return View_qt::asQWidget(guest.get());

    return nullptr;
}
