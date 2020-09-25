/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "FloatingWindowWidget_p.h"
#include "Logging_p.h"
#include "Utils_p.h"
#include "DropArea_p.h"
#include "TitleBar_p.h"

#include <QApplication>
#include <QPainter>
#include <QVBoxLayout>
#include <QWindowStateChangeEvent>

using namespace KDDockWidgets;

FloatingWindowWidget::FloatingWindowWidget(MainWindowBase *parent)
    : FloatingWindow(parent)
    , m_vlayout(new QVBoxLayout(this))
{
    init();
}

FloatingWindowWidget::FloatingWindowWidget(Frame *frame, MainWindowBase *parent)
    : FloatingWindow(frame, parent)
    , m_vlayout(new QVBoxLayout(this))
{
    init();
}

void FloatingWindowWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(0x666666);
    p.drawRect(rect().adjusted(0, 0, -1, -1));
}

bool FloatingWindowWidget::event(QEvent *ev)
{
    if (ev->type() == QEvent::WindowStateChange)
        Q_EMIT windowStateChanged(static_cast<QWindowStateChangeEvent*>(ev));

    return FloatingWindow::event(ev);
}

void FloatingWindowWidget::init()
{
    m_vlayout->setSpacing(0);
    m_vlayout->setContentsMargins(4, 4, 4, 4);
    m_vlayout->addWidget(m_titleBar);
    m_vlayout->addWidget(m_dropArea);
}
