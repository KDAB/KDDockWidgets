/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/KDDockWidgets.h"

#include "qwayland-kddw-test-v1.h"

#include <QtWaylandClient/QWaylandClientExtensionTemplate>

namespace KDDockWidgets::Core {
class View;
}

namespace KDDockWidgets::Tests::Wayland {

/// Client side of kddw-test-v1, see protocol/kddw-test-v1.xml.
/// Requests are queued by the compositor until commitAndWait() is called.
class TestInput : public QWaylandClientExtensionTemplate<TestInput>, public QtWayland::kddw_test_v1
{
    Q_OBJECT
public:
    TestInput();

    /// Waits until the compositor's kddw_test_v1 global is bound
    [[nodiscard]] bool waitForActive();

    /// Plays back the queued actions and waits until they're done, even if a drag's nested
    /// event loop runs meanwhile. Returns false if an action failed or on timeout.
    [[nodiscard]] bool commitAndWait(int timeoutMs = 10000);

    /// Moves the pointer to @p localPos, relative to @p view
    void moveTo(Core::View *view, Point localPos);

    void press();
    void release();
    void doubleClick();

    /// Drags @p source by @p sourcePos and drops it over @p dest at @p destPos.
    /// Positions are relative to each view. Only queues the actions, see commitAndWait().
    void drag(Core::View *source, Point sourcePos, Core::View *dest, Point destPos);

Q_SIGNALS:
    void done(uint serial, uint result, const QString &message);

protected:
    void kddw_test_v1_done(uint32_t serial, uint32_t result, const QString &message) override;

private:
    uint32_t m_lastSerial = 0;
};

/// Returns the wl_surface of the window that @p view is in
wl_surface *surfaceFor(Core::View *view);

/// Maps @p localPos from @p view to its window's coordinates, which are its surface's
Point mapToSurface(Core::View *view, Point localPos);

/// Waits until the window @p view is in has been shown by the compositor
[[nodiscard]] bool waitForMapped(Core::View *view);

}
