/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_WIDGET_RESIZE_HANDLER_P_H
#define KD_WIDGET_RESIZE_HANDLER_P_H

#include "QWidgetAdapter.h"
#include "Qt5Qt6Compat_p.h"
#include "kddockwidgets/KDDockWidgets.h"

#include <QPoint>
#include <QDebug>

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE

namespace KDDockWidgets {

class FloatingWindow;

class WidgetResizeHandler : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief CTOR
     * @param target The target widget that will be resized. Also acts as parent QObject.
     */
    explicit WidgetResizeHandler(bool filterIsGlobal, QWidgetOrQuick *target);
    ~WidgetResizeHandler() override;

    /**
     * @brief Sets the sides the user is allowed to resize with mouse.
     *
     * By default the user can resize all 4 sides.
     * However, when a dock widget is overlayed (popuped), only one side can be resized.
     */
    void setAllowedResizeSides(CursorPositions);


    /**
     * Sets the resize gap. By default 10.
     *
     * This is only used for non-top-level (child) widgets.
     * When resizing a child widget, it will be clipped by its parent, but we leave a little space so
     * we can resize it again.
     *
     * Meaning, if you're resizing 'bottom' of the child widget, it can never be bigger than parent.geometry().bottom() - gap.
     * The gap allows you to put your mouse there and resize again.
     */
    void setResizeGap(int);

    static int widgetResizeHandlerMargin();

#ifdef Q_OS_WIN
    static bool handleWindowsNativeEvent(FloatingWindow *w, const QByteArray &eventType, void *message, Qt5Qt6Compat::qintptr *result);
#endif
    static bool s_disableAllHandlers;
protected:
    bool eventFilter(QObject *o, QEvent *e) override;

private:
    void setTarget(QWidgetOrQuick *w);
    bool mouseMoveEvent(QMouseEvent *e);
    void updateCursor(CursorPosition m);
    void setMouseCursor(Qt::CursorShape cursor);
    void restoreMouseCursor();
    CursorPosition cursorPosition(QPoint) const;
    QWidgetOrQuick *mTarget = nullptr;
    CursorPosition mCursorPos = CursorPosition_Undefined;
    QPoint mNewPosition;
    bool mResizeWidget = false;
    const bool mFilterIsGlobal;
    int m_resizeGap = 10;
    CursorPositions mAllowedResizeSides = CursorPosition_All;
};

}

#endif
