/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "WaylandTestUtils.h"

#include "core/View.h"
#include "core/Window_p.h"
#include "qtcommon/Window_p.h"

#include <qpa/qplatformwindow_p.h>

#include <QEventLoop>
#include <QTest>
#include <QTimer>

#include <linux/input-event-codes.h>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Tests::Wayland;

namespace {

QWindow *qtWindowFor(Core::View *view)
{
    auto window = std::static_pointer_cast<QtCommon::Window>(view->window());
    return window ? window->qtWindow() : nullptr;
}

wl_fixed_t fixed(int value)
{
    return wl_fixed_from_int(value);
}

}

TestInput::TestInput()
    : QWaylandClientExtensionTemplate(/*version=*/1)
{
    initialize();
}

bool TestInput::waitForActive()
{
    return QTest::qWaitFor([this] { return isActive(); }, 5000);
}

bool TestInput::commitAndWait(int timeoutMs)
{
    const uint32_t serial = ++m_lastSerial;
    bool ok = false;

    QEventLoop loop;
    connect(this, &TestInput::done, &loop, [&](uint doneSerial, uint result, const QString &message) {
        if (doneSerial != serial)
            return;

        ok = result == result_ok;
        if (!ok)
            qWarning() << "TestInput::commitAndWait: " << message;
        loop.quit();
    });

    QTimer::singleShot(timeoutMs, &loop, [&loop, serial] {
        qWarning() << "TestInput::commitAndWait: Timed out waiting for batch" << serial;
        loop.quit();
    });

    commit(serial);
    loop.exec();

    return ok;
}

void TestInput::moveTo(Core::View *view, Point localPos)
{
    const Point pos = mapToSurface(view, localPos);
    pointer_move(surfaceFor(view), fixed(pos.x()), fixed(pos.y()));
}

void TestInput::press()
{
    pointer_button(BTN_LEFT, button_state_pressed);
}

void TestInput::release()
{
    pointer_button(BTN_LEFT, button_state_released);
}

void TestInput::doubleClick()
{
    for (int i = 0; i < 2; ++i) {
        press();
        release();
    }
}

void TestInput::drag(Core::View *source, Point sourcePos, Core::View *dest, Point destPos)
{
    moveTo(source, sourcePos);
    press();

    // Move past the drag threshold, in small steps like a real mouse would
    for (int i = 1; i <= 10; ++i)
        moveTo(source, sourcePos + Point(0, 4 * i));

    wait_for_drag_start(/*timeout_msecs=*/5000);

    // The pointer can't move smoothly between different windows, as we don't know where they
    // are. Within the same window it can.
    wl_surface *destSurface = surfaceFor(dest);
    const Point to = mapToSurface(dest, destPos);
    const Point from = destSurface == surfaceFor(source)
        ? mapToSurface(source, sourcePos + Point(0, 40))
        : to - Point(0, 10);

    constexpr int steps = 20;
    for (int i = 1; i <= steps; ++i) {
        const Point p = from + (to - from) * i / steps;
        pointer_move(destSurface, fixed(p.x()), fixed(p.y()));
    }

    release();
}

void TestInput::kddw_test_v1_done(uint32_t serial, uint32_t result, const QString &message)
{
    Q_EMIT done(serial, result, message);
}

wl_surface *KDDockWidgets::Tests::Wayland::surfaceFor(Core::View *view)
{
    QWindow *window = qtWindowFor(view);
    if (!window)
        return nullptr;

    auto waylandWindow = window->nativeInterface<QNativeInterface::Private::QWaylandWindow>();
    return waylandWindow ? waylandWindow->surface() : nullptr;
}

Point KDDockWidgets::Tests::Wayland::mapToSurface(Core::View *view, Point localPos)
{
    // Wayland doesn't tell clients where their windows are, but going through global coordinates
    // is still correct, as the same made up window position is used both ways
    return view->window()->mapFromGlobal(view->mapToGlobal(localPos));
}

bool KDDockWidgets::Tests::Wayland::waitForMapped(Core::View *view)
{
    QWindow *window = qtWindowFor(view);
    return window && QTest::qWaitForWindowExposed(window);
}
