/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "SideBarWidget_p.h"
#include "DockWidgetBase.h"

#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QAbstractButton>

using namespace KDDockWidgets;

SideBarWidget::SideBarWidget(SideBarLocation location, QWidget *parent)
    : SideBar(location, parent)
    , m_layout(isVertical() ? static_cast<QBoxLayout*>(new QVBoxLayout(this))
                            : static_cast<QBoxLayout*>(new QHBoxLayout(this))) // ternary operator requires static_cast
{
    m_layout->setSpacing(1);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addStretch();
}

void SideBarWidget::addDockWidget_Impl(DockWidgetBase *dw)
{
    auto button = createButton();
    button->setText(dw->title());
    connect(dw, &DockWidgetBase::titleChanged, button, &QToolButton::setText);
    connect(dw, &QObject::destroyed, button, &QObject::deleteLater);
    connect(button, &QAbstractButton::clicked, this, [this, button, dw] {
        onButtonClicked(dw);
        button->deleteLater();
    });

    const int count = m_layout->count();
    m_layout->insertWidget(count - 1, button);
}

void SideBarWidget::removeDockWidget_Impl(DockWidgetBase *)
{
    // Nothing is needed. Button is removed automatically.
}

QAbstractButton *SideBarWidget::createButton()
{
    return new QToolButton(this);
}
