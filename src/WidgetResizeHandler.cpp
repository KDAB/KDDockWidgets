/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "WidgetResizeHandler_p.h"
#include <QEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QDebug>
namespace  {
int widgetResizeHandlerMargin = 4; //4 pixel
}
bool WidgetResizeHandler::s_disableAllHandlers = false;
WidgetResizeHandler::WidgetResizeHandler(QWidget *target)
    : QObject(target)
{
    setTarget(target);
}

WidgetResizeHandler::~WidgetResizeHandler()
{
}

bool WidgetResizeHandler::eventFilter(QObject *o, QEvent *e)
{
    if (s_disableAllHandlers || (o != mTarget)) {
        return false;
    }
    switch (e->type()) {
    case QEvent::MouseButtonPress: {
        if (mCursorPos == CursorPosition::Undefined)
            return false;
        QMouseEvent *mouveEvent = static_cast<QMouseEvent *>(e);
        if (mTarget->isMaximized())
            break;
        const QRect widgetRect = mTarget->rect().marginsAdded(QMargins(widgetResizeHandlerMargin, widgetResizeHandlerMargin, widgetResizeHandlerMargin, widgetResizeHandlerMargin));
        const QPoint cursorPoint = mTarget->mapFromGlobal(mouveEvent->globalPos());
        if (!widgetRect.contains(cursorPoint))
            return false;
        if (mouveEvent->button() == Qt::LeftButton) {
            mResizeWidget = true;
        }
        mNewPosition = cursorPoint;
        return true;
    }
    case QEvent::MouseButtonRelease: {
        if (mTarget->isMaximized())
            break;
        QMouseEvent *mouveEvent = static_cast<QMouseEvent *>(e);
        if (mouveEvent->button() == Qt::LeftButton) {
            mResizeWidget = false;
            mTarget->releaseMouse();
            mTarget->releaseKeyboard();
            return true;
        }
        break;
    }
    case QEvent::MouseMove: {
        if (mTarget->isMaximized())
            break;
        QMouseEvent *mouveEvent = static_cast<QMouseEvent *>(e);
        mResizeWidget = mResizeWidget && (mouveEvent->buttons() & Qt::LeftButton);
        const bool state = mResizeWidget;
        mResizeWidget = ((o == mTarget) && mResizeWidget);
        mouseMoveEvent(mouveEvent);
        mResizeWidget = state;
        return true;
    }
    default:
        break;
    }
    return false;
}

void WidgetResizeHandler::mouseMoveEvent(QMouseEvent *e)
{
    QPoint pos = mTarget->mapFromGlobal(e->globalPos());
    if (!mResizeWidget) {
        if (pos.y() <= widgetResizeHandlerMargin && pos.x() <= widgetResizeHandlerMargin)
            mCursorPos = CursorPosition::TopLeft;
        else if (pos.y() >= mTarget->height() - widgetResizeHandlerMargin && pos.x() >= mTarget->width() - widgetResizeHandlerMargin)
            mCursorPos = CursorPosition::BottomRight;
        else if (pos.y() >= mTarget->height() - widgetResizeHandlerMargin && pos.x() <= widgetResizeHandlerMargin)
            mCursorPos = CursorPosition::BottomLeft;
        else if (pos.y() <= widgetResizeHandlerMargin && pos.x() >= mTarget->width() - widgetResizeHandlerMargin)
            mCursorPos = CursorPosition::TopRight;
        else if (pos.y() <= widgetResizeHandlerMargin)
            mCursorPos = CursorPosition::Top;
        else if (pos.y() >= mTarget->height() - widgetResizeHandlerMargin)
            mCursorPos = CursorPosition::Bottom;
        else if (pos.x() <= widgetResizeHandlerMargin)
            mCursorPos = CursorPosition::Left;
        else if ( pos.x() >= mTarget->width() - widgetResizeHandlerMargin)
            mCursorPos = CursorPosition::Right;
        else {
            mCursorPos = CursorPosition::Undefined;
        }
        updateCursor(mCursorPos);
        return;
    }

    const QPoint globalPos = e->globalPos();

    const QPoint newPos = globalPos - mNewPosition;

    QRect targetGeometry = mTarget->geometry();
    const QSize newSize(targetGeometry.right() - newPos.x() + 1,
                  targetGeometry.bottom() - newPos.y() + 1);
    const QPoint mp(targetGeometry.right() - newSize.width() + 1,
               targetGeometry.bottom() - newSize.height() + 1);

    switch (mCursorPos) {
    case CursorPosition::TopLeft:
        targetGeometry = QRect(mp, targetGeometry.bottomRight()) ;
        break;
    case CursorPosition::BottomRight:
        targetGeometry = QRect(targetGeometry.topLeft(), globalPos) ;
        break;
    case CursorPosition::BottomLeft:
        targetGeometry = QRect(QPoint(mp.x(), targetGeometry.y()), QPoint(targetGeometry.right(), globalPos.y())) ;
        break;
    case CursorPosition::TopRight:
        targetGeometry = QRect(QPoint(targetGeometry.x(), mp.y()), QPoint(globalPos.x(), targetGeometry.bottom())) ;
        break;
    case CursorPosition::Top:
        targetGeometry = QRect(QPoint(targetGeometry.left(), mp.y()), targetGeometry.bottomRight()) ;
        break;
    case CursorPosition::Bottom:
        targetGeometry = QRect(targetGeometry.topLeft(), QPoint(targetGeometry.right(), globalPos.y())) ;
        break;
    case CursorPosition::Left:
        targetGeometry = QRect(QPoint(mp.x(), targetGeometry.top()), targetGeometry.bottomRight()) ;
        break;
    case CursorPosition::Right:
        targetGeometry = QRect(targetGeometry.topLeft(), QPoint(globalPos.x(), targetGeometry.bottom())) ;
        break;
    case CursorPosition::Undefined:
        targetGeometry.moveTopLeft(newPos);
        break;
    }

    //Be sure that we can't resize more than maximumsize
    targetGeometry = QRect(targetGeometry.topLeft(),
                  targetGeometry.size().expandedTo(mTarget->minimumSize())
                             .boundedTo(mTarget->maximumSize()));
    if (targetGeometry != mTarget->geometry() &&
        (mTarget->isWindow() || mTarget->parentWidget()->rect().intersects(targetGeometry))) {
        if (mCursorPos == CursorPosition::Undefined)
            mTarget->move(targetGeometry.topLeft());
        else
            mTarget->setGeometry(targetGeometry);
    }
}

void WidgetResizeHandler::setTarget(QWidget *w)
{
    if (w) {
        mTarget = w;
        mTarget->setMouseTracking(true);
        mTarget->installEventFilter(this);
    } else {
        qWarning() << "Target widget is null!";
    }
}

void WidgetResizeHandler::setActive(bool b)
{
    if (!b) {
        mCursorPos = CursorPosition::Undefined;
    }
}

void WidgetResizeHandler::updateCursor(CursorPosition m)
{
    //Need for updating cursor when we change child widget
    const QObjectList children = mTarget->children();
    for (int i = 0, total = children.size(); i < total; ++i) {
        if (QWidget *child = qobject_cast<QWidget*>(children.at(i))) {
            if (!child->testAttribute(Qt::WA_SetCursor)) {
                child->setCursor(Qt::ArrowCursor);
            }
        }
    }
    switch (m) {
    case CursorPosition::TopLeft:
    case CursorPosition::BottomRight:
        mTarget->setCursor(Qt::SizeFDiagCursor);
        break;
    case CursorPosition::BottomLeft:
    case CursorPosition::TopRight:
        mTarget->setCursor(Qt::SizeBDiagCursor);
        break;
    case CursorPosition::Top:
    case CursorPosition::Bottom:
        mTarget->setCursor(Qt::SizeVerCursor);
        break;
    case CursorPosition::Left:
    case CursorPosition::Right:
        mTarget->setCursor(Qt::SizeHorCursor);
        break;
    case CursorPosition::Undefined:
        mTarget->setCursor(Qt::ArrowCursor);
        break;
    }
}
