/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidgetQuick.h"

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

class DockWidgetQuick::Private
{
public:
    Private(DockWidgetQuick *dw)
        : q(dw)
        , m_visualItem(q->createItem(Config::self().qmlEngine(), QStringLiteral("qrc:/kddockwidgets/private/quick/qml/DockWidget.qml")))
    {
        Q_ASSERT(m_visualItem);
        m_visualItem->setParent(q);
        m_visualItem->setParentItem(q);
    }

    DockWidgetBase *const q;
    QQuickItem *const m_visualItem;
};

DockWidgetQuick::DockWidgetQuick(const QString &name, Options options, LayoutSaverOptions layoutSaverOptions)
    : DockWidgetBase(name, options, layoutSaverOptions)
    , d(new Private(this))
{
    // To mimic what QtWidgets does when creating a new QWidget.
    setVisible(false);
}

DockWidgetQuick::~DockWidgetQuick()
{
    delete d;
}

void DockWidgetQuick::setWidget(const QString &qmlFilename)
{
    QQuickItem *guest = createItem(Config::self().qmlEngine(), qmlFilename);
    if (!guest)
        return;

    auto adapter = new QWidgetAdapter(this);
    guest->setParentItem(adapter);
    guest->setParent(adapter);

    setWidget(adapter);
}

void DockWidgetQuick::setWidget(QWidgetAdapter *widget)
{
    widget->QWidgetAdapter::setParent(this);
    QWidgetAdapter::makeItemFillParent(widget);
    DockWidgetBase::setWidget(widget);
}

bool DockWidgetQuick::event(QEvent *e)
{
    if (e->type() == QEvent::ParentChange) {
        onParentChanged();
    } else if (e->type() == QEvent::Show) {
        onShown(e->spontaneous());
    } else if (e->type() == QEvent::Hide) {
        onHidden(e->spontaneous());
    } else if (e->type() == QEvent::Close) {
        onCloseEvent(static_cast<QCloseEvent*>(e));
    }

    return DockWidgetBase::event(e);
}

QSize DockWidgetQuick::minimumSize() const
{
    if (QWidgetAdapter *guestWidget = widget()) {
        // The guests min-size is the same as the widget's, there's no spacing or margins.
        return guestWidget->minimumSize();
    }

    return DockWidgetBase::minimumSize();
}

QSize DockWidgetQuick::maximumSize() const
{
    if (QWidgetAdapter *guestWidget = widget()) {
        // The guests max-size is the same as the widget's, there's no spacing or margins.
        return guestWidget->maximumSize();
    }

    return DockWidgetBase::maximumSize();
}
