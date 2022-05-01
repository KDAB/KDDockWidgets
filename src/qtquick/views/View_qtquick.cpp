/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "View_qtquick.h"
#include "private/Utils_p.h"

#include <QGuiApplication>

using namespace KDDockWidgets::Views;

namespace KDDockWidgets::Views {

/**
 * @brief Event filter which redirects mouse events from one QObject to another.
 * Needed for QtQuick to redirect the events from MouseArea to our KDDW classes which derive from Draggable.
 * For QtWidgets it's not needed, as the Draggables are QWidgets themselves.
 */
class MouseEventRedirector : public QObject
{
    Q_OBJECT
public:
    explicit MouseEventRedirector(QObject *eventSource, QObject *eventTarget)
        : QObject(eventTarget)
        , m_eventSource(eventSource)
        , m_eventTarget(eventTarget)
    {
        eventSource->installEventFilter(this);

        // Each source can only have one MouseEventRedirector
        auto oldRedirector = s_mouseEventRedirectors.take(eventSource);
        if (oldRedirector) {
            eventSource->removeEventFilter(oldRedirector);
            oldRedirector->deleteLater();
        }

        s_mouseEventRedirectors.insert(eventSource, this);
    }

    static MouseEventRedirector *redirectorForSource(QObject *eventSource)
    {
        return s_mouseEventRedirectors.value(eventSource);
    }

    ~MouseEventRedirector() override;

    bool eventFilter(QObject *source, QEvent *ev) override
    {
        QMouseEvent *me = mouseEvent(ev);
        if (!me)
            return false;

        // MouseArea.enable is different from Item.enabled. The former still lets the events
        // go through event loops. So query MouseArea.enable here and bail out if false.
        const QVariant v = source->property("enabled");
        if (v.isValid() && !v.toBool())
            return false;

        // Finally send the event
        m_eventTarget->setProperty("cursorPosition", m_eventSource->property("cursorPosition"));
        qApp->sendEvent(m_eventTarget, me);
        m_eventTarget->setProperty("cursorPosition", CursorPosition_Undefined);

        return false;
    }

    QObject *const m_eventSource;
    QObject *const m_eventTarget;
    static QHash<QObject *, MouseEventRedirector *> s_mouseEventRedirectors;
};

QHash<QObject *, MouseEventRedirector *> MouseEventRedirector::s_mouseEventRedirectors = {};

MouseEventRedirector::~MouseEventRedirector()
{
    s_mouseEventRedirectors.remove(m_eventSource);
}

}

static bool flagsAreTopLevelFlags(Qt::WindowFlags flags)
{
    return flags & (Qt::Window | Qt::Tool);
}

static QQuickItem *actualParentItem(QQuickItem *candidateParentItem, Qt::WindowFlags flags)
{
    // When we have a top-level, such as FloatingWindow, we only want to set QObject parentship
    // and not parentItem.
    return flagsAreTopLevelFlags(flags) ? nullptr
                                        : candidateParentItem;
}

View_qtquick::View_qtquick(KDDockWidgets::Controller *controller, Type type,
                           QQuickItem *parent,
                           Qt::WindowFlags flags)
    : QQuickItem(actualParentItem(parent, flags))
    , View(controller, type, this)
    , m_windowFlags(flags)
{
    if (parent && flagsAreTopLevelFlags(flags)) {
        // See comment in actualParentItem(). We set only the QObject parent. Mimics QWidget behaviour
        QObject::setParent(parent);
    }

    connect(this, &QQuickItem::widthChanged, this, [this] {
        onResize(View::size());
        updateGeometry();
    });

    connect(this, &QQuickItem::heightChanged, this, [this] {
        if (!m_windowIsBeingDestroyed) { // If Window is being destroyed we don't bother
            onResize(View::size());
            updateGeometry();
        }
    });

    qApp->installEventFilter(this);
    setSize(800, 800);
}

void View_qtquick::setGeometry(QRect rect)
{
    setSize(rect.width(), rect.height());
    View::move(rect.topLeft());
}

QQuickItem *View_qtquick::createItem(QQmlEngine *engine, const QString &filename)
{
    QQmlComponent component(engine, filename);
    QObject *obj = component.create();
    if (!obj) {
        qWarning() << Q_FUNC_INFO << component.errorString();
        return nullptr;
    }

    return qobject_cast<QQuickItem *>(obj);
}

void View_qtquick::redirectMouseEvents(QObject *source)
{
    if (auto existingRedirector = MouseEventRedirector::redirectorForSource(source)) {
        if (existingRedirector->m_eventTarget == this) {
            // Nothing to do. The specified event source is already redirecting to this instance
            return;
        }
    }

    new MouseEventRedirector(source, this);
}

void View_qtquick::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &data)
{
    QQuickItem::itemChange(change, data);

    // Emulate the QWidget behaviour as QQuickItem doesn't receive some QEvents.
    switch (change) {
    case QQuickItem::ItemParentHasChanged: {
        QEvent ev(QEvent::ParentChange);
        qApp->sendEvent(this, &ev); // Not calling event() directly, otherwise it would skip event filters
        Q_EMIT parentChanged(this);
        break;
    }
    case QQuickItem::ItemVisibleHasChanged: {
        if (m_inSetParent) {
            // Setting parent to nullptr will emit visible true in QtQuick
            // which we don't want, as we're going to hide it (as we do with QtWidgets)
            break;
        }

        QEvent ev(isVisible() ? QEvent::Show : QEvent::Hide);
        event(&ev);
        break;
    }
    default:
        break;
    }
}

void View_qtquick::onResizeEvent(QResizeEvent *event)
{
    QWindow *window = QQuickItem::window();
    if (!window) {
        return;
    }

    if (isNormalWindowState(m_oldWindowState)) {
        QRect geo = normalGeometry();

        auto curState = window->windowState();
        if (isNormalWindowState(curState)) {
            geo.setSize(event->size());
        } else {
            geo.setSize(event->oldSize());
        }

        setNormalGeometry(geo);
    }
}
void View_qtquick::onMoveEvent(QMoveEvent *event)
{
    QWindow *window = QQuickItem::window();
    if (!window) {
        return;
    }

    if (isNormalWindowState(m_oldWindowState)) {
        QRect geo = normalGeometry();

        auto windowCurrentState = window->windowState();
        if (isNormalWindowState(windowCurrentState)) {
            geo.moveTopLeft(event->pos());
        } else {
            geo.moveTopLeft(event->oldPos());
        }

        setNormalGeometry(geo);
    }
}

void View_qtquick::move(int x, int y)
{
    if (isRootView()) {
        if (QWindow *w = QQuickItem::window()) {
            w->setPosition(x, y);
            return;
        }
    }

    QQuickItem::setX(x);
    QQuickItem::setY(y);
    setAttribute(Qt::WA_Moved);
}

bool View_qtquick::event(QEvent *ev)
{
    if (ev->type() == QEvent::Close)
        onCloseEvent(static_cast<QCloseEvent *>(ev));

    return QQuickItem::event(ev);
}

bool View_qtquick::eventFilter(QObject *watched, QEvent *ev)
{
    if (qobject_cast<QWindow *>(watched)) {
        if (m_mouseTrackingEnabled) {
            switch (ev->type()) {
            case QEvent::MouseMove:
            case QEvent::MouseButtonPress:
            case QEvent::MouseButtonRelease:
                ev->ignore();
                qApp->sendEvent(this, ev);
                // qDebug() << "Mouse event" << ev;
                if (ev->isAccepted())
                    return true;
                break;
            default:
                break;
            }
        }

        if (ev->type() == QEvent::Resize) {
            onResizeEvent(static_cast<QResizeEvent *>(ev));
        } else if (ev->type() == QEvent::Move) {
            onMoveEvent(static_cast<QMoveEvent *>(ev));
        } else if (ev->type() == QEvent::WindowStateChange) {
            onWindowStateChangeEvent(static_cast<QWindowStateChangeEvent *>(ev));
        }
    }

    return QQuickItem::eventFilter(watched, ev);
}

bool View_qtquick::close()
{
    QCloseEvent ev;
    onCloseEvent(&ev);

    if (ev.isAccepted()) {
        setVisible(false);
        return true;
    }

    return false;
}

void View_qtquick::QQUICKITEMgeometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    // Send a few events manually, since QQuickItem doesn't do it for us.
    QQuickItem::QQUICKITEMgeometryChanged(newGeometry, oldGeometry);

    // Not calling event() directly, otherwise it would skip event filters

    if (newGeometry.size() != oldGeometry.size()) {
        QEvent ev(QEvent::Resize);
        qApp->sendEvent(this, &ev);
    }

    if (newGeometry.topLeft() != oldGeometry.topLeft()) {
        QEvent ev(QEvent::Move);
        qApp->sendEvent(this, &ev);
    }

    Q_EMIT itemGeometryChanged();
}

bool View_qtquick::isVisible() const
{
    if (QWindow *w = QQuickItem::window()) {
        if (!w->isVisible())
            return false;
    }

    return QQuickItem::isVisible();
}

void View_qtquick::setVisible(bool is)
{
    if (isRootView()) {
        if (QWindow *w = QQuickItem::window()) {
            if (!w->isVisible()) {
                w->show();
            }
        }
    }

    QQuickItem::setVisible(is);
}

void View_qtquick::setSize(int w, int h)
{
    if (isRootView()) {
        if (QWindow *window = QQuickItem::window()) {
            QRect windowGeo = window->geometry();
            windowGeo.setSize(QSize(w, h));
            window->setGeometry(windowGeo);
        }
    }

    QQuickItem::setSize(QSizeF(w, h));
}


#include "View_qtquick.moc"
