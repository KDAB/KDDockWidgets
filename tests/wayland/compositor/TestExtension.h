/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "qwayland-server-kddw-test-v1.h"

#include <QWaylandCompositorExtensionTemplate>
#include <QHash>
#include <QList>
#include <QPointF>
#include <QPointer>

#include <functional>

QT_BEGIN_NAMESPACE
class QQuickWindow;
class QWaylandCompositor;
class QWaylandQuickItem;
class QWaylandSurface;
QT_END_NAMESPACE

/// Server side of kddw-test-v1. Queues the actions a test client requests and plays them back
/// on commit, as input events to the compositor's window.
class TestExtension : public QWaylandCompositorExtensionTemplate<TestExtension>,
                      public QtWaylandServer::kddw_test_v1
{
    Q_OBJECT
public:
    TestExtension(QWaylandCompositor *compositor, QQuickWindow *window);
    void initialize() override;

    /// Delay between two consecutive actions, so the client gets to process each one
    void setStepDelay(int msecs);

protected:
    void kddw_test_v1_destroy_resource(Resource *resource) override;
    void kddw_test_v1_destroy(Resource *resource) override;
    void kddw_test_v1_pointer_move(Resource *resource, struct ::wl_resource *surface, wl_fixed_t x,
                                   wl_fixed_t y) override;
    void kddw_test_v1_pointer_move_absolute(Resource *resource, wl_fixed_t x, wl_fixed_t y) override;
    void kddw_test_v1_pointer_button(Resource *resource, uint32_t button, uint32_t state) override;
    void kddw_test_v1_key(Resource *resource, uint32_t key, uint32_t state) override;
    void kddw_test_v1_set_window_position(Resource *resource, struct ::wl_resource *surface,
                                          int32_t x, int32_t y) override;
    void kddw_test_v1_wait(Resource *resource, uint32_t msecs) override;
    void kddw_test_v1_wait_for_drag_start(Resource *resource, uint32_t timeout_msecs) override;
    void kddw_test_v1_cancel_drag(Resource *resource) override;
    void kddw_test_v1_screenshot(Resource *resource, const QString &filename) override;
    void kddw_test_v1_commit(Resource *resource, uint32_t serial) override;

private:
    /// An action reports completion by calling the callback, with an empty string on success
    using Done = std::function<void(const QString &error)>;
    using Action = std::function<void(const Done &)>;

    struct Batch
    {
        Resource *resource = nullptr;
        uint32_t serial = 0;
        QList<Action> actions;
    };

    void enqueue(Resource *resource, Action action);
    void runNextBatch();
    void runNextAction();
    void finishBatch(const QString &error);

    QWaylandQuickItem *itemForSurface(QWaylandSurface *surface) const;
    void movePointerTo(QPointF scenePos);

    QWaylandCompositor *const m_compositor;
    QQuickWindow *const m_window;
    int m_stepDelay = 5;

    QHash<Resource *, QList<Action>> m_pendingActions;
    QList<Batch> m_batches;
    Batch m_currentBatch;
    bool m_running = false;

    QPointF m_pointerPos;
    Qt::KeyboardModifiers m_keyboardModifiers;

    // Counts drags started by clients. wait_for_drag_start only accepts drags newer than the
    // last button press.
    int m_dragsStarted = 0;
    int m_dragsStartedAtLastPress = 0;
    bool m_dragInProgress = false;
};
