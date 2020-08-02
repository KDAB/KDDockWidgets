/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief A class that is QWidget when building for QtWidgets, and QObject when building for QtQuick.
 *
 * Allows to have the same code base supporting both stacks.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "QWidgetAdapter_quick_p.h"
#include "FloatingWindow_p.h"

#include <QResizeEvent>
#include <QMouseEvent>
#include <QQuickWindow>
#include <QQmlComponent>
#include <QQuickItem>
#include <QQmlEngine>

using namespace KDDockWidgets;

QWidgetAdapter::QWidgetAdapter(QQuickItem *parent, Qt::WindowFlags flags)
    : QQuickItem(parent)
    , m_requestedWindowFlags(flags)
{
    this->setParent(parent); // also set parentItem

    connect(this, &QQuickItem::widthChanged, this, [this] {
        onResize(size());
    });

    connect(this, &QQuickItem::heightChanged, this, [this] {
        onResize(size());
    });

    setSize(QSize(800, 800));
}

QWidgetAdapter::~QWidgetAdapter()
{
}

void QWidgetAdapter::raiseAndActivate()
{
}

bool QWidgetAdapter::onResize(QSize) { return false; }
void QWidgetAdapter::onLayoutRequest() {}
void QWidgetAdapter::onMousePress() {}
void QWidgetAdapter::onMouseMove(QPoint) {}
void QWidgetAdapter::onMouseRelease() {}
void QWidgetAdapter::onCloseEvent(QCloseEvent *) {}

void QWidgetAdapter::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &data)
{
    QQuickItem::itemChange(change, data);

    // Emulate the QWidget behaviour as QQuickItem doesn't receive some QEvents.
    switch (change) {
    case QQuickItem::ItemVisibleHasChanged: {
        QEvent ev(QEvent::ParentChange);
        event(&ev);
        Q_EMIT parentChanged();
        break;
    }
    case QQuickItem::ItemParentHasChanged: {
        QEvent ev(isVisible() ? QEvent::Show : QEvent::Hide);
        event(&ev);
        break;
    }
    default:
        break;
    }
}

void QWidgetAdapter::raise() {}

WId QWidgetAdapter::winId() const
{
    if (QWindow *w = windowHandle())
        return w->winId();

    return -1;
}

FloatingWindow * QWidgetAdapter::floatingWindow() const
{
    return nullptr;
}

QRect QWidgetAdapter::geometry() const
{
    QRect r = rect();
    r.moveTopLeft(QPointF(x(), y()).toPoint());
    return r;
}

QRect QWidgetAdapter::rect() const
{
    return QRectF(0, 0, width(), height()).toRect();
}

void QWidgetAdapter::show()
{
    setVisible(true);
}

void QWidgetAdapter::setFixedHeight(int height)
{
    setHeight(height);
}

void QWidgetAdapter::setFixedWidth(int width)
{
    setWidth(width);
}

void QWidgetAdapter::setGeometry(QRect rect)
{
    setWidth(rect.width());
    setHeight(rect.height());
    setX(rect.x());
    setY(rect.y());
}

void QWidgetAdapter::grabMouse()
{
    QQuickItem::grabMouse();
}

void QWidgetAdapter::releaseMouse()
{
    QQuickItem::ungrabMouse();
}

void QWidgetAdapter::setMinimumSize(QSize sz)
{
    m_minimumSize = sz;
}

void QWidgetAdapter::resize(QSize sz)
{
    setWidth(sz.width());
    setHeight(sz.height());
}

bool QWidgetAdapter::isMaximized() const
{
    qWarning() << Q_FUNC_INFO << "Implement me";
    return false;
}

void QWidgetAdapter::showMaximized()
{
    qWarning() << Q_FUNC_INFO << "Implement me";
}

void QWidgetAdapter::showNormal()
{
    qWarning() << Q_FUNC_INFO << "Implement me";
}

QWindow *QWidgetAdapter::windowHandle() const
{
    return QQuickItem::window();
}

QWidgetAdapter *QWidgetAdapter::window() const
{
    // We return the top-most QWidgetAdapter

    if (QWidgetAdapter *w = parentWidget()) {
        return w->window();
    }

    return const_cast<QWidgetAdapter *>(this);
}

QWidgetAdapter *QWidgetAdapter::parentWidget() const
{
    QQuickItem *p = parentItem();
    while (p) {
        if (auto qa = qobject_cast<QWidgetAdapter*>(p))
            return qa;

        p = p->parentItem();
    }

    return nullptr;
}

void QWidgetAdapter::close()
{
    if (QWindow *w = windowHandle())
        w->close();
}

void QWidgetAdapter::move(int x, int y)
{
    qDebug() << Q_FUNC_INFO << x << y << this;
    setX(x);
    setY(y);
}

void QWidgetAdapter::setParent(QQuickItem *p)
{
    QQuickItem::setParent(p);
    QQuickItem::setParentItem(p);
}

void QWidgetAdapter::activateWindow()
{
    qWarning() << Q_FUNC_INFO << "Implement me";
}

void QWidgetAdapter::setSizePolicy(QSizePolicy)
{
    qWarning() << Q_FUNC_INFO << "Implement me";
}

QSizePolicy QWidgetAdapter::sizePolicy() const
{
    qWarning() << Q_FUNC_INFO << "Implement me";
    return {};
}

QSize QWidgetAdapter::sizeHint() const
{
    qWarning() << Q_FUNC_INFO << "Implement me";
    return {};
}

Qt::WindowFlags QWidgetAdapter::windowFlags() const
{
    if (QWindow *w = windowHandle())
        return w->flags();

    return m_requestedWindowFlags;
}

QQuickItem *QWidgetAdapter::createItem(QQmlEngine *engine, const QString &filename) const
{
    QQmlComponent component(engine, filename);
    QObject *obj = component.create();
    if (!obj) {
        qWarning() << Q_FUNC_INFO << component.errorString();
        return nullptr;
    }

    return qobject_cast<QQuickItem*>(obj);
}

void QWidgetAdapter::setFlag(Qt::WindowType f, bool on)
{
    if (QWindow *w = windowHandle()) {
        w->setFlag(f, on);
    } else {
        // When we create a QWindow we'll set these
        if (on) {
            m_requestedWindowFlags |= f;
        } else {
            m_requestedWindowFlags &= ~f;
        }
    }
}

