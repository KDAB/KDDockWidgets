/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

#ifndef KDDOCKWIDGETS_QWIDGETADAPTERQUICK_P_H
#define KDDOCKWIDGETS_QWIDGETADAPTERQUICK_P_H

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/Qt5Qt6Compat_p.h"

#include <QQuickItem>
#include <QObject>
#include <QCloseEvent>
#include <QQuickWindow>
#include <QScreen>

QT_BEGIN_NAMESPACE
class QWindow;
class QQmlEngine;
class QQuickView;
QT_END_NAMESPACE

namespace KDDockWidgets {

class MouseEventRedirector;

namespace Private {

DOCKS_EXPORT QQuickItem *widgetForWindow(QWindow *window);

/// @brief Helper since QQuickItem::parentItem() has a different name than QWidget::parentWidget()
inline QQuickItem *parentWidget(QQuickItem *item)
{
    return item ? item->parentItem() : nullptr;
}

inline bool isMinimized(const QQuickItem *item)
{
    QWindow *window = item ? item->window() : nullptr;
    return KDDockWidgets::Private::isMinimized(window);
}

inline QRect geometry(const QQuickItem *item)
{
    QRect r(QPoint(0, 0), item->size().toSize());
    r.moveTopLeft(QPointF(item->x(), item->y()).toPoint());
    return r;
}

inline QRect parentGeometry(const QQuickItem *item)
{
    if (!item || !item->parentItem())
        return QRect();


    return geometry(item->parentItem());
}

inline QWindow *windowForWidget(const QQuickItem *item)
{
    return item ? item->window() : nullptr;
}

/// @brief sets the geometry on the QWindow containing the specified item
inline void setTopLevelGeometry(QRect geometry, const QQuickItem *item)
{
    if (!item)
        return;

    if (QWindow *window = item->window())
        window->setGeometry(geometry);
}

} // namespace Private

class FloatingWindow;
class DOCKS_EXPORT QWidgetAdapter : public QQuickItem
{
    Q_OBJECT
public:
    Q_INVOKABLE void showMaximized();
    Q_INVOKABLE void showMinimized();
    Q_INVOKABLE void showNormal();
    Q_INVOKABLE void redirectMouseEvents(QObject *from);


Q_SIGNALS:
    void geometryUpdated(); // similar to QLayout stuff, when size constraints change
    void itemGeometryChanged(); // emitted when the geometry changes. QQuickItem::geometryChanged()
                                // isn't a signal, so prefixed item

protected:
    void itemChange(QQuickItem::ItemChange, const QQuickItem::ItemChangeData &) override;

private:
    MouseEventRedirector *m_mouseEventRedirector = nullptr;
};

inline qreal logicalDpiFactor(const QQuickItem *item)
{
#ifndef Q_OS_MACOS
    if (QQuickWindow *window = item->window()) {
        if (QScreen *s = window->screen()) {
            return s->logicalDotsPerInch() / 96.0;
        }
    }
#endif

    // It's always 72 on mac
    Q_UNUSED(item);
    return 1;
}

}

#endif
