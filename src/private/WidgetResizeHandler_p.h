/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_WIDGET_RESIZE_HANDLER_P_H
#define KD_WIDGET_RESIZE_HANDLER_P_H

#include <QWidget>
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
    explicit WidgetResizeHandler(QWidget *target = nullptr);
    ~WidgetResizeHandler() override;

    void setTarget(QWidget *w);

#ifdef Q_OS_WIN
    static bool handleWindowsNativeEvent(FloatingWindow *w, const QByteArray &eventType, void *message, long *result);
#endif
    static bool s_disableAllHandlers;
protected:
    bool eventFilter(QObject *o, QEvent *e) override;

private:
    enum class CursorPosition {
        Left,
        Right,
        TopLeft,
        TopRight,
        BottomRight,
        BottomLeft,
        Top,
        Bottom,
        Undefined
    };
    void mouseMoveEvent(QMouseEvent *e);
    void updateCursor(CursorPosition m);
    CursorPosition cursorPosition(QPoint) const;
    QWidget *mTarget = nullptr;
    CursorPosition mCursorPos = CursorPosition::Undefined;
    QPoint mNewPosition;
    bool mResizeWidget = false;
};

}

#endif
