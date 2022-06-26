/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "FloatingWindow_qtwidgets.h"
#include "kddockwidgets/controllers/FloatingWindow.h"
#include "kddockwidgets/controllers/Group.h"
#include "kddockwidgets/controllers/TitleBar.h"
#include "kddockwidgets/controllers/MainWindow.h"

#include "DockRegistry.h"
#include "kddockwidgets/controllers/DropArea.h"
#include "private/Logging_p.h"
#include "private/Utils_p.h"
#include "private/DragController_p.h"
#include "private/WidgetResizeHandler_p.h"

#include "TitleBar_qtwidgets.h"

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QVBoxLayout>
#include <QWindow>
#include <QWindowStateChangeEvent>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

class FloatingWindow_qtwidgets::Private
{
public:
    Private(FloatingWindow_qtwidgets *q, Controllers::FloatingWindow *controller)
        : m_vlayout(new QVBoxLayout(q))
        , m_controller(controller)
    {
    }

    QVBoxLayout *const m_vlayout;
    Controllers::FloatingWindow *const m_controller;
    KDBindings::ConnectionHandle m_screenChangedConnection;
};

FloatingWindow_qtwidgets::FloatingWindow_qtwidgets(Controllers::FloatingWindow *controller,
                                                   QMainWindow *parent, Qt::WindowFlags windowFlags)
    : View_qtwidgets<QWidget>(controller, Type::FloatingWindow, parent, windowFlags)
    , d(new Private(this, controller))
{
}

FloatingWindow_qtwidgets::~FloatingWindow_qtwidgets()
{
    d->m_screenChangedConnection.disconnect();
    delete d;
}

void FloatingWindow_qtwidgets::paintEvent(QPaintEvent *ev)
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

bool FloatingWindow_qtwidgets::event(QEvent *ev)
{
    if (ev->type() == QEvent::NonClientAreaMouseButtonDblClick && (Config::self().flags() & Config::Flag_NativeTitleBar)) {
        if ((windowFlags() & Qt::Tool) == Qt::Tool) {
            if (Config::self().flags() & Config::Flag_DoubleClickMaximizes) {
                // Let's refuse to maximize Qt::Tool. It's not natural.
                // Just avoid this combination: Flag_NativeTitleBar + Qt::Tool + Flag_DoubleClickMaximizes
            } else {
                // Double clicking a Qt::Tool title-bar. Triggers a redocking.
                if (d->m_controller->titleBar()->isFloating()) { // redocking nested floating windows aren't supported
                    d->m_controller->titleBar()->onFloatClicked();
                    return true;
                }
            }
        } else {
            // A normal Qt::Window window. The OS handles the double click.
            // In general this will maximize the window, that's the native behaviour.
        }
    } else if (ev->type() == QEvent::Show && !d->m_screenChangedConnection.isActive()) {
        // We connect after QEvent::Show, so we have a QWindow. Qt doesn't offer much API to
        // intercept screen events
        d->m_screenChangedConnection = window()->screenChanged.connect([this] {
            Q_EMIT DockRegistry::self()->windowChangedScreen(window());
        });

        QWidget::windowHandle()->installEventFilter(this);
    } else if (ev->type() == QEvent::ActivationChange) {
        // Since QWidget is missing a signal for window activation
        Q_EMIT d->m_controller->activatedChanged();
    } else if (ev->type() == QEvent::StatusTip && QWidget::parent()) {
        // show status tips in the main window
        return QWidget::parent()->event(ev); // TODOm3: Move to base class
    }

    return View_qtwidgets<QWidget>::event(ev);
}

void FloatingWindow_qtwidgets::init()
{
    d->m_vlayout->setSpacing(0);
    updateMargins();
    d->m_vlayout->addWidget(View_qtwidgets::asQWidget(d->m_controller->titleBar()));
    d->m_vlayout->addWidget(View_qtwidgets::asQWidget(d->m_controller->dropArea()));

    connect(DockRegistry::self(), &DockRegistry::windowChangedScreen, this, [this](Window::Ptr w) {
        if (isInWindow(w))
            updateMargins();
    });
}

void FloatingWindow_qtwidgets::updateMargins()
{
    d->m_vlayout->setContentsMargins(QMargins(4, 4, 4, 4) * logicalDpiFactor(this));
}

Controllers::FloatingWindow *FloatingWindow_qtwidgets::floatingWindow() const
{
    return d->m_controller;
}

bool FloatingWindow_qtwidgets::eventFilter(QObject *, QEvent *ev)
{
    if (ev->type() == QEvent::WindowStateChange) {

        // QWidget::windowState() is not reliable as it's emitted both for the spontaneous (async) event and non-spontaneous (sync)
        // The sync one being useless, as the window manager can still have the old state.
        // Only emit windowStateChanged once the window manager tells us the state has actually changed
        // See also QTBUG-102430
        if (ev->spontaneous()) {
            d->m_controller->setLastWindowManagerState(WindowState(windowHandle()->windowState()));
            Q_EMIT d->m_controller->windowStateChanged();
        }
    }

    return false;
}

#if defined(Q_OS_WIN)
bool FloatingWindow_qtwidgets::nativeEvent(const QByteArray &eventType, void *message, Qt5Qt6Compat::qintptr *result)
{
    auto fw = floatingWindow();
    if (fw->beingDeleted())
        return QWidget::nativeEvent(eventType, message, result);

    if (KDDockWidgets::usesAeroSnapWithCustomDecos()) {
        // To enable aero snap we need to tell Windows where's our custom title bar
        if (WidgetResizeHandler::handleWindowsNativeEvent(fw, eventType, message, result))
            return true;
    } else if (KDDockWidgets::usesNativeTitleBar()) {
        auto msg = static_cast<MSG *>(message);
        if (msg->message == WM_SIZING) {
            // Cancel any drag if we're resizing
            Q_EMIT DragController::instance()->dragCanceled();
        }
    }

    return QWidget::nativeEvent(eventType, message, result);
}
#endif
