/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TestExtension.h"

#include <QElapsedTimer>
#include <QImage>
#include <QKeyEvent>
#include <QLoggingCategory>
#include <QQuickWindow>
#include <QTest>
#include <QTimer>
#include <QWaylandCompositor>
#include <QWaylandDrag>
#include <QWaylandQuickItem>
#include <QWaylandQuickOutput>
#include <QWaylandQuickShellSurfaceItem>
#include <QWaylandSeat>
#include <QWaylandSurface>
#include <QWaylandView>

#include <linux/input-event-codes.h>

Q_LOGGING_CATEGORY(lcTestCompositor, "kddw.testcompositor")

namespace {

Qt::MouseButton qtButton(uint32_t button)
{
    switch (button) {
    case BTN_LEFT:
        return Qt::LeftButton;
    case BTN_RIGHT:
        return Qt::RightButton;
    case BTN_MIDDLE:
        return Qt::MiddleButton;
    default:
        return Qt::NoButton;
    }
}

// QWaylandKeyboard expects XKB keycodes as native scan codes, which are evdev codes + 8
constexpr uint32_t XkbKeycodeOffset = 8;

struct ModifierKey
{
    Qt::Key key;
    Qt::KeyboardModifier modifier;
};

ModifierKey modifierKey(uint32_t key)
{
    switch (key) {
    case KEY_LEFTSHIFT:
    case KEY_RIGHTSHIFT:
        return { Qt::Key_Shift, Qt::ShiftModifier };
    case KEY_LEFTCTRL:
    case KEY_RIGHTCTRL:
        return { Qt::Key_Control, Qt::ControlModifier };
    case KEY_LEFTALT:
        return { Qt::Key_Alt, Qt::AltModifier };
    case KEY_LEFTMETA:
    case KEY_RIGHTMETA:
        return { Qt::Key_Meta, Qt::MetaModifier };
    default:
        return { Qt::Key_unknown, Qt::NoModifier };
    }
}

}

TestExtension::TestExtension(QWaylandCompositor *compositor, QQuickWindow *window)
    : QWaylandCompositorExtensionTemplate(compositor)
    , m_compositor(compositor)
    , m_window(window)
{
    connect(compositor->defaultSeat()->drag(), &QWaylandDrag::dragStarted, this, [this] {
        qCDebug(lcTestCompositor) << "Drag started";
        ++m_dragsStarted;
        m_dragInProgress = true;
    });
}

void TestExtension::initialize()
{
    QWaylandCompositorExtensionTemplate::initialize();
    init(m_compositor->display(), 1);
}

void TestExtension::setStepDelay(int msecs)
{
    m_stepDelay = msecs;
}

void TestExtension::kddw_test_v1_destroy_resource(Resource *resource)
{
    m_pendingActions.remove(resource);

    m_batches.removeIf([resource](const Batch &batch) { return batch.resource == resource; });

    // Let a running batch finish, there's just nobody to tell
    if (m_currentBatch.resource == resource)
        m_currentBatch.resource = nullptr;
}

void TestExtension::kddw_test_v1_destroy(Resource *resource)
{
    wl_resource_destroy(resource->handle);
}

void TestExtension::kddw_test_v1_pointer_move(Resource *resource, struct ::wl_resource *surface,
                                              wl_fixed_t x, wl_fixed_t y)
{
    const QPointer<QWaylandSurface> waylandSurface = QWaylandSurface::fromResource(surface);
    const QPointF localPos(wl_fixed_to_double(x), wl_fixed_to_double(y));

    enqueue(resource, [this, waylandSurface, localPos](const Done &done) {
        QWaylandQuickItem *item = itemForSurface(waylandSurface);
        if (!item) {
            done(QStringLiteral("pointer_move: surface is not mapped"));
            return;
        }

        movePointerTo(item->mapToScene(item->mapFromSurface(localPos)));
        done({});
    });
}

void TestExtension::kddw_test_v1_pointer_move_absolute(Resource *resource, wl_fixed_t x, wl_fixed_t y)
{
    const QPointF pos(wl_fixed_to_double(x), wl_fixed_to_double(y));
    enqueue(resource, [this, pos](const Done &done) {
        movePointerTo(pos);
        done({});
    });
}

void TestExtension::kddw_test_v1_pointer_button(Resource *resource, uint32_t button, uint32_t state)
{
    enqueue(resource, [this, button, state](const Done &done) {
        const Qt::MouseButton qtbutton = qtButton(button);
        if (qtbutton == Qt::NoButton) {
            done(QStringLiteral("pointer_button: unsupported button %1").arg(button));
            return;
        }

        const QPoint pos = m_pointerPos.toPoint();
        if (state == button_state_pressed) {
            qCDebug(lcTestCompositor) << "Press" << qtbutton << "at" << pos;
            m_dragsStartedAtLastPress = m_dragsStarted;
            QTest::mousePress(m_window, qtbutton, {}, pos);
        } else {
            qCDebug(lcTestCompositor) << "Release" << qtbutton << "at" << pos;
            QTest::mouseRelease(m_window, qtbutton, {}, pos);
            m_dragInProgress = false; // Releasing drops or cancels it
        }

        done({});
    });
}

void TestExtension::kddw_test_v1_key(Resource *resource, uint32_t key, uint32_t state)
{
    enqueue(resource, [this, key, state](const Done &done) {
        QWaylandSeat *seat = m_compositor->defaultSeat();
        if (!seat->keyboardFocus()) {
            done(QStringLiteral("key: no surface has keyboard focus"));
            return;
        }

        // QWaylandSeat overwrites the client's modifier state with the event's modifiers, so
        // they must reflect the modifier keys being held
        const bool pressed = state == key_state_pressed;
        const ModifierKey modifier = modifierKey(key);
        m_keyboardModifiers.setFlag(modifier.modifier, pressed);

        QKeyEvent ev(pressed ? QEvent::KeyPress : QEvent::KeyRelease, modifier.key,
                     m_keyboardModifiers, key + XkbKeycodeOffset, 0, 0);
        seat->sendFullKeyEvent(&ev);
        done({});
    });
}

void TestExtension::kddw_test_v1_set_window_position(Resource *resource, struct ::wl_resource *surface,
                                                     int32_t x, int32_t y)
{
    const QPointer<QWaylandSurface> waylandSurface = QWaylandSurface::fromResource(surface);

    enqueue(resource, [this, waylandSurface, x, y](const Done &done) {
        auto item = qobject_cast<QWaylandQuickShellSurfaceItem *>(itemForSurface(waylandSurface));
        if (!item) {
            done(QStringLiteral("set_window_position: surface is not a mapped toplevel"));
            return;
        }

        item->moveItem()->setPosition(QPointF(x, y));
        done({});
    });
}

void TestExtension::kddw_test_v1_wait(Resource *resource, uint32_t msecs)
{
    enqueue(resource, [this, msecs](const Done &done) {
        QTimer::singleShot(int(msecs), this, [done] { done({}); });
    });
}

void TestExtension::kddw_test_v1_wait_for_drag_start(Resource *resource, uint32_t timeout_msecs)
{
    enqueue(resource, [this, timeout_msecs](const Done &done) {
        auto elapsed = std::make_shared<QElapsedTimer>();
        elapsed->start();

        auto poll = std::make_shared<std::function<void()>>();
        *poll = [this, timeout_msecs, done, elapsed, poll] {
            if (m_dragsStarted > m_dragsStartedAtLastPress) {
                m_dragsStartedAtLastPress = m_dragsStarted;
                done({});
                *poll = nullptr; // break the reference cycle
            } else if (elapsed->elapsed() > timeout_msecs) {
                done(QStringLiteral("wait_for_drag_start: no drag started within %1ms").arg(timeout_msecs));
                *poll = nullptr;
            } else {
                QTimer::singleShot(10, this, *poll);
            }
        };
        (*poll)();
    });
}

void TestExtension::kddw_test_v1_cancel_drag(Resource *resource)
{
    enqueue(resource, [this](const Done &done) {
        m_compositor->defaultSeat()->drag()->cancelDrag();
        done({});
    });
}

void TestExtension::kddw_test_v1_screenshot(Resource *resource, const QString &filename)
{
    enqueue(resource, [this, filename](const Done &done) {
        if (m_window->grabWindow().save(filename))
            done({});
        else
            done(QStringLiteral("screenshot: failed to save %1").arg(filename));
    });
}

void TestExtension::kddw_test_v1_commit(Resource *resource, uint32_t serial)
{
    m_batches.append({ resource, serial, m_pendingActions.take(resource) });
    if (!m_running)
        runNextBatch();
}

void TestExtension::enqueue(Resource *resource, Action action)
{
    m_pendingActions[resource].append(std::move(action));
}

void TestExtension::runNextBatch()
{
    if (m_batches.isEmpty()) {
        m_running = false;
        return;
    }

    m_running = true;
    m_currentBatch = m_batches.takeFirst();
    runNextAction();
}

void TestExtension::runNextAction()
{
    if (m_currentBatch.actions.isEmpty()) {
        finishBatch({});
        return;
    }

    const Action action = m_currentBatch.actions.takeFirst();
    action([this](const QString &error) {
        if (error.isEmpty()) {
            QTimer::singleShot(m_stepDelay, this, &TestExtension::runNextAction);
        } else {
            finishBatch(error);
        }
    });
}

void TestExtension::finishBatch(const QString &error)
{
    if (!error.isEmpty())
        qCWarning(lcTestCompositor) << "Batch" << m_currentBatch.serial << "failed:" << error;

    if (m_currentBatch.resource)
        send_done(m_currentBatch.resource->handle, m_currentBatch.serial,
                  error.isEmpty() ? result_ok : result_error, error);

    m_currentBatch = {};

    // Don't recurse, the next batch might be queued by a client reacting to this done event
    QTimer::singleShot(0, this, &TestExtension::runNextBatch);
}

QWaylandQuickItem *TestExtension::itemForSurface(QWaylandSurface *surface) const
{
    if (!surface)
        return nullptr;

    const auto views = surface->views();
    for (QWaylandView *view : views) {
        auto item = qobject_cast<QWaylandQuickItem *>(view->renderObject());
        if (item && item->window() == m_window && item->isVisible())
            return item;
    }

    return nullptr;
}

void TestExtension::movePointerTo(QPointF scenePos)
{
    // Note: QTest treats QPoint(0, 0) as "center of the window"
    m_pointerPos = scenePos;
    QTest::mouseMove(m_window, scenePos.toPoint());

    if (!m_dragInProgress)
        return;

    // During a drag, QWaylandQuickItem only updates the drag's target while over a surface. Like
    // desktop compositors, leave the last one when over none, so a release there cancels the drag
    // instead of dropping onto that surface.
    auto output = static_cast<QWaylandQuickOutput *>(m_compositor->defaultOutput());
    auto item = qobject_cast<QWaylandQuickItem *>(output->pickClickableItem(scenePos));
    if (!item || !item->surface())
        m_compositor->defaultSeat()->drag()->dragMove(nullptr, {});
}
