/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "utils.h"
#include "DropArea_p.h"
#include "Config.h"
#include "private/widgets/TabWidgetWidget_p.h"
#include "private/widgets/FrameWidget_p.h"
#include "TitleBar_p.h"
#include "FloatingWindow_p.h"

#include <QCloseEvent>
#include <QDebug>
#include <QPainter>
#include <QPushButton>
#include <QtTest/QtTest>

static bool s_pauseBeforePress = false; // for debugging
static bool s_pauseBeforeMove = false; // for debugging
#define DEBUGGING_PAUSE_DURATION 5000 // 5 seconds

using namespace KDDockWidgets;
using namespace KDDockWidgets::Tests;

// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates

QPoint KDDockWidgets::Tests::dragPointForWidget(Frame *frame, int index)
{
    auto frameW = static_cast<FrameWidget*>(frame);

    if (frameW->hasSingleDockWidget()) {
        Q_ASSERT(index == 0);
        return frameW->titleBar()->mapToGlobal(QPoint(5, 5));
    } else {
        QRect rect = frameW->tabBar()->tabRect(index);
        return frameW->tabBar()->mapToGlobal(rect.center());
    }
}

NonClosableWidget::NonClosableWidget(QWidget *parent)
    : QWidget(parent)
{
}

NonClosableWidget::~NonClosableWidget()
{
}

void NonClosableWidget::closeEvent(QCloseEvent *ev)
{
    ev->ignore(); // don't allow to close
}

std::unique_ptr<KDDockWidgets::MainWindow> KDDockWidgets::Tests::createMainWindow(QSize sz, KDDockWidgets::MainWindowOptions options, const QString &name)
{
    static int count = 0;
    count++;

    const QString mainWindowName = name.isEmpty() ? QStringLiteral("MyMainWindow%1").arg(count)
                                                  : name;

    auto ptr = std::unique_ptr<MainWindow>(new MainWindow(mainWindowName, options));
    ptr->show();
    ptr->resize(sz);
    return ptr;
}

DockWidgetBase *KDDockWidgets::Tests::createDockWidget(const QString &name, QWidget *w, DockWidgetBase::Options options, bool show)
{
    auto dock = new DockWidget(name, options);
    dock->setWidget(w);
    dock->setObjectName(name);
    dock->setGeometry(0, 0, 400, 400);
    if (show) {
        dock->show();
        dock->morphIntoFloatingWindow();
        dock->activateWindow();
        Q_ASSERT(dock->window());
        if (QTest::qWaitForWindowActive(dock->window()->windowHandle(), 200)) {
            qDebug() << dock->window();
            return dock;
        }
        return nullptr;
    } else {
        return dock;
    }
};

DockWidgetBase *KDDockWidgets::Tests::createDockWidget(const QString &name, QColor color)
{
    return createDockWidget(name, new MyWidget(name, color));
};


std::unique_ptr<MainWindow> KDDockWidgets::Tests::createMainWindow(QVector<DockDescriptor> &docks)
{
    static int count = 0;
    count++;
    auto m = std::unique_ptr<MainWindow>(new MainWindow(QStringLiteral("MyMainWindow%1").arg(count), MainWindowOption_None));
    auto layout = m->multiSplitterLayout();
    m->show();
    m->resize(QSize(700, 700));

    int i = 0;
    for (DockDescriptor &desc : docks) {
        desc.createdDock = createDockWidget(QStringLiteral("%1-%2").arg(i).arg(count), new QPushButton(QStringLiteral("%1").arg(i)), {}, false);

        DockWidgetBase *relativeTo = nullptr;
        if (desc.relativeToIndex != -1)
            relativeTo = docks.at(desc.relativeToIndex).createdDock;

        m->addDockWidget(desc.createdDock, desc.loc, relativeTo, desc.option);
        qDebug() << "Added" <<i;
        layout->checkSanity();
        ++i;
    }

    return m;
}

MyWidget::MyWidget(const QString &, QColor c)
    : QWidget()
    , c(c)
{
    qDebug() << "MyWidget" << this;
}

MyWidget::~MyWidget()
{
    qDebug() << "~MyWidget" << this;
}

void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), c);
}

bool KDDockWidgets::Tests::shouldBlacklistWarning(const QString &msg, const QString &category)
{
    if (category == QLatin1String("qt.qpa.xcb"))
        return true;

    return msg.contains(QLatin1String("QSocketNotifier: Invalid socket")) ||
           msg.contains(QLatin1String("QWindowsWindow::setGeometry")) ||
           msg.contains(QLatin1String("This plugin does not support")) ||
           msg.contains(QLatin1String("Note that Qt no longer ships fonts")) ||
           msg.contains(QLatin1String("Another dock KDDockWidgets::DockWidget")) ||
           msg.contains(QLatin1String("There's multiple MainWindows, not sure what to do about parenting"));
}

QWidget *KDDockWidgets::Tests::draggableFor(QWidget *w)
{
    QWidget *draggable = nullptr;
    if (auto dock = qobject_cast<DockWidgetBase *>(w)) {
        if (auto frame = dock->frame())
            draggable = frame->titleBar();
    } else if (auto fw = qobject_cast<FloatingWindow *>(w)) {
        draggable = ((Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible) && fw->hasSingleFrame() && fw->frames().first()->hasTabsVisible()) ? static_cast<QWidget*>(fw->frames().first()->tabWidget()->asWidget())
                                                                                                                                                            : static_cast<QWidget*>(fw->titleBar());

    } else if (qobject_cast<TabWidgetWidget *>(w) || qobject_cast<TitleBar *>(w)) {
        draggable = w;
    }

    qDebug() << "Draggable is" << draggable;
    return draggable;
}

void KDDockWidgets::Tests::pressOn(QPoint globalPos, QWidget *receiver)
{
    QCursor::setPos(globalPos);
    QMouseEvent ev(QEvent::MouseButtonPress, receiver->mapFromGlobal(globalPos), receiver->window()->mapFromGlobal(globalPos), globalPos,
                   Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    qApp->sendEvent(receiver, &ev);
}

void KDDockWidgets::Tests::releaseOn(QPoint globalPos, QWidget *receiver)
{
    QMouseEvent ev(QEvent::MouseButtonRelease, receiver->mapFromGlobal(globalPos), receiver->window()->mapFromGlobal(globalPos), globalPos,
                   Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    qApp->sendEvent(receiver, &ev);
}

void KDDockWidgets::Tests::moveMouseTo(QPoint globalDest, QWidget *receiver)
{
    QPoint globalSrc(receiver->mapToGlobal(QPoint(5, 5)));

    QPointer<QWidget> receiverP = receiver;

    while (globalSrc != globalDest) {
        if (globalSrc.x() < globalDest.x()) {
            globalSrc.setX(globalSrc.x() + 1);
        } else if (globalSrc.x() > globalDest.x()) {
            globalSrc.setX(globalSrc.x() - 1);
        }
        if (globalSrc.y() < globalDest.y()) {
            globalSrc.setY(globalSrc.y() + 1);
        } else if (globalSrc.y() > globalDest.y()) {
            globalSrc.setY(globalSrc.y() - 1);
        }

        QCursor::setPos(globalSrc); // Since some code uses QCursor::pos()
        QMouseEvent ev(QEvent::MouseMove, receiver->mapFromGlobal(globalSrc), receiver->window()->mapFromGlobal(globalSrc), globalSrc,
                       Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);

        if (!receiverP) {
            qWarning() << "Receiver was deleted";
            return;
        }

        qApp->sendEvent(receiver, &ev);
        QTest::qWait(2);
    }
}

void KDDockWidgets::Tests::drag(QWidget *sourceWidget, QPoint pressGlobalPos, QPoint globalDest, ButtonActions buttonActions)
{
    if (buttonActions & ButtonAction_Press) {
        if (s_pauseBeforePress)
            QTest::qWait(DEBUGGING_PAUSE_DURATION);

        pressOn(pressGlobalPos, sourceWidget);
    }

    sourceWidget->window()->activateWindow();

    if (s_pauseBeforeMove)
        QTest::qWait(DEBUGGING_PAUSE_DURATION);

    qDebug() << "Moving sourceWidget to" << globalDest
             << "; sourceWidget->size=" << sourceWidget->size()
             << "; from=" << QCursor::pos();
    moveMouseTo(globalDest, sourceWidget);
    qDebug() << "Arrived at" << QCursor::pos();
    pressGlobalPos = sourceWidget->mapToGlobal(QPoint(10, 10));
    if (buttonActions & ButtonAction_Release)
        releaseOn(globalDest, sourceWidget);
}

void KDDockWidgets::Tests::drag(QWidget *sourceWidget, QPoint globalDest, ButtonActions buttonActions)
{
    Q_ASSERT(sourceWidget && sourceWidget->isVisible());

    QWidget *draggable = draggableFor(sourceWidget);

    Q_ASSERT(draggable && draggable->isVisible());
    const QPoint pressGlobalPos = draggable->mapToGlobal(QPoint(6, 6));

    drag(draggable, pressGlobalPos, globalDest, buttonActions);
}

void KDDockWidgets::Tests::dragFloatingWindowTo(FloatingWindow *fw, QPoint globalDest, ButtonActions buttonActions)
{
    auto draggable = draggableFor(fw);
    Q_ASSERT(draggable && draggable->isVisible());
    drag(draggable, draggable->mapToGlobal(QPoint(10, 10)), globalDest, buttonActions);
}

void KDDockWidgets::Tests::dragFloatingWindowTo(FloatingWindow *fw, DropArea *target, DropIndicatorOverlayInterface::DropLocation dropLocation)
{
    auto draggable = draggableFor(fw);

    // First we drag over it, so the drop indicators appear:
    drag(draggable, draggable->mapToGlobal(QPoint(10, 10)), target->window()->mapToGlobal(QPoint(50, 50)), ButtonAction_Press);

    // Now we drag over the drop indicator and only then release mouse:
    DropIndicatorOverlayInterface *dropIndicatorOverlay = target->dropIndicatorOverlay();
    const QPoint dropPoint = dropIndicatorOverlay->posForIndicator(dropLocation);

    drag(draggable, QPoint(), dropPoint, ButtonAction_Release);
}
