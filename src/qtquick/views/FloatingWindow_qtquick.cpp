/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "FloatingWindow_qtquick.h"
#include "controllers/FloatingWindow.h"
#include "controllers/Frame.h"
#include "controllers/TitleBar.h"
#include "controllers/MainWindow.h"

#include "private/DockRegistry_p.h"
#include "controllers/DropArea.h"
#include "private/Logging_p.h"
#include "private/Utils_p.h"

#include "TitleBar_qtquick.h"

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QVBoxLayout>
#include <QWindow>
#include <QWindowStateChangeEvent>


using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

FloatingWindow_qtquick::FloatingWindow_qtquick(Controllers::FloatingWindow *controller,
                                               QMainWindow *parent, Qt::WindowFlags windowFlags)
    : View_qtquick<QWidget>(controller, Type::FloatingWindow, parent, windowFlags)
    , m_controller(controller)
    , m_vlayout(new QVBoxLayout(this))
{
}

void FloatingWindow_qtquick::paintEvent(QPaintEvent *ev)
{
    if (Config::self().disabledPaintEvents() & Config::CustomizableWidget_FloatingWindow) {
        QWidget::paintEvent(ev);
        return;
    }

    QPainter p(this);
    QPen pen(0x666666);
    pen.setWidth(1);
    pen.setJoinStyle(Qt::MiterJoin);
    p.setPen(pen);
    const qreal halfPenWidth = p.pen().widthF() / 2;
    const QRectF rectf = rect();
    p.drawRect(rectf.adjusted(halfPenWidth, halfPenWidth, -halfPenWidth, -halfPenWidth));
}

bool FloatingWindow_qtquick::event(QEvent *ev)
{
    if (ev->type() == QEvent::WindowStateChange) {
        Q_EMIT m_controller->windowStateChanged(static_cast<QWindowStateChangeEvent *>(ev));
    } else if (ev->type() == QEvent::NonClientAreaMouseButtonDblClick && (Config::self().flags() & Config::Flag_NativeTitleBar)) {
        if ((windowFlags() & Qt::Tool) == Qt::Tool) {
            if (Config::self().flags() & Config::Flag_DoubleClickMaximizes) {
                // Let's refuse to maximize Qt::Tool. It's not natural.
                // Just avoid this combination: Flag_NativeTitleBar + Qt::Tool + Flag_DoubleClickMaximizes
            } else {
                // Double clicking a Qt::Tool title-bar. Triggers a redocking.
                if (m_controller->titleBar()->isFloating()) { // redocking nested floating windows aren't supported
                    m_controller->titleBar()->onFloatClicked();
                    return true;
                }
            }
        } else {
            // A normal Qt::Window window. The OS handles the double click.
            // In general this will maximize the window, that's the native behaviour.
        }
    } else if (ev->type() == QEvent::Show && !m_screenChangedConnection) {
        // We connect after QEvent::Show, so we have a QWindow. Qt doesn't offer much API to
        // intercept screen events
        m_screenChangedConnection =
            connect(window(), &QWindow::screenChanged, DockRegistry::self(),
                    [this] { Q_EMIT DockRegistry::self()->windowChangedScreen(window()); });
    } else if (ev->type() == QEvent::ActivationChange) {
        // Since QWidget is missing a signal for window activation
        Q_EMIT m_controller->activatedChanged();
    } else if (ev->type() == QEvent::StatusTip && QWidget::parent()) {
        // show status tips in the main window
        return QWidget::parent()->event(ev); // TODO: Move to base class
    } else if (ev->type() == QEvent::LayoutRequest) {
        m_controller->updateSizeConstraints(); // TODO: Move to base class
    }

    return View_qtquick<QWidget>::event(ev);
}

void FloatingWindow_qtquick::init()
{
    m_vlayout->setSpacing(0);
    updateMargins();
    m_vlayout->addWidget(m_controller->titleBar()->view()->asQWidget());
    m_vlayout->addWidget(m_controller->dropArea());

    connect(DockRegistry::self(), &DockRegistry::windowChangedScreen, this, [this](QWindow *w) {
        if (w == window()->window())
            updateMargins();
    });
}

void FloatingWindow_qtquick::updateMargins()
{
    m_vlayout->setContentsMargins(QMargins(4, 4, 4, 4) * logicalDpiFactor(this));
}

Controllers::FloatingWindow *FloatingWindow_qtquick::floatingWindow() const
{
    return m_controller;
}

void FloatingWindow_qtquick::closeEvent(QCloseEvent *ev)
{
    m_controller->onCloseEvent(ev);
}
