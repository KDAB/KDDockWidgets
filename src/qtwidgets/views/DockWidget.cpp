/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidget.h"
#include "core/DockWidget_p.h"
#include "ViewWrapper_p.h"

#include <QCloseEvent>
#include <QVBoxLayout>
#include <QAction>

/**
 * @file
 * @brief Represents a dock widget.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

using namespace KDDockWidgets;
using namespace KDDockWidgets::QtWidgets;

class DockWidget::Private
{
public:
    explicit Private(DockWidget *q)
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
    : View<QWidget>(new Core::DockWidget(this, uniqueName, options, layoutSaverOptions),
                    Core::ViewType::DockWidget, nullptr, windowFlags)
    , Core::DockWidgetViewInterface(asDockWidgetController())
    , d(new Private(this))
{
    m_dockWidget->d->guestViewChanged.connect([this] {
        if (auto guest = widget()) {
            QWidget::setSizePolicy(guest->sizePolicy());
            d->layout->addWidget(guest);
        }
    });

    m_dockWidget->d->optionsChanged.connect([this](KDDockWidgets::DockWidgetOptions opts) {
        Q_EMIT optionsChanged(opts);
    });

    m_dockWidget->d->guestViewChanged.connect([this] {
        Q_EMIT guestViewChanged();
    });

    m_dockWidget->d->isFocusedChanged.connect([this](bool focused) {
        Q_EMIT isFocusedChanged(focused);
    });

    m_dockWidget->init();
}

DockWidget::~DockWidget()
{
    delete d;
}

void DockWidget::setWidget(QWidget *widget)
{
    m_dockWidget->setGuestView(ViewWrapper::create(widget));
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

QAction *DockWidget::toggleAction() const
{
    return dynamic_cast<QAction *>(m_dockWidget->toggleAction());
}

QAction *DockWidget::floatAction() const
{
    return dynamic_cast<QAction *>(m_dockWidget->floatAction());
}
