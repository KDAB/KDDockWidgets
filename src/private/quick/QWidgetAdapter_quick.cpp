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
#include <QWindow>

using namespace KDDockWidgets;

QWidgetAdapter::QWidgetAdapter(QQuickItem *parent, Qt::WindowFlags)
    : QQuickItem(parent)
{
    this->setParent(parent); // also set parentItem

    connect(this, &QQuickItem::widthChanged, this, [this] {
        onResize(size());
    });

    connect(this, &QQuickItem::heightChanged, this, [this] {
        onResize(size());
    });
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


void QWidgetAdapter::raise() {}

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
    qDebug() << Q_FUNC_INFO << height << this;
    setHeight(height);
}

void QWidgetAdapter::setFixedWidth(int width)
{
    qDebug() << Q_FUNC_INFO << width << this;
    setWidth(width);
}

void QWidgetAdapter::setGeometry(QRect rect)
{
    qDebug() << Q_FUNC_INFO << rect << this;
    setWidth(rect.width());
    setHeight(rect.height());
    setX(rect.x());
    setY(rect.y());
}

void QWidgetAdapter::grabMouse() {}
void QWidgetAdapter::releaseMouse() {}
void QWidgetAdapter::setMinimumSize(QSize sz)
{
    m_minimumSize = sz;
}

void QWidgetAdapter::resize(QSize sz)
{
    qDebug() << Q_FUNC_INFO << sz << this;
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

QWindow *QWidgetAdapter::windowHandle() const { return nullptr; }

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

void QWidgetAdapter::setFlag(Qt::WindowType f, bool on)
{
    if (auto w = windowHandle()) {
        w->setFlag(f, on);
    } else {
        qWarning() << Q_FUNC_INFO << "Implement me";
    }
}

