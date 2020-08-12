/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "utils.h"
#include "DropArea_p.h"
#include "Config.h"
#include "TitleBar_p.h"
#include "FloatingWindow_p.h"

#include <QCloseEvent>
#include <QDebug>
#include <QPainter>
#include <QPushButton>
#include <QtTest/QtTest>

#ifdef KDDOCKWIDGETS_QTQUICK
# include "private/quick/DockWidgetQuick.h"
# include "private/quick/MainWindowQuick_p.h"
#else
# include "DockWidget.h"
#endif

using namespace KDDockWidgets;
using namespace KDDockWidgets::Tests;

// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates

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

std::unique_ptr<KDDockWidgets::MainWindowBase> KDDockWidgets::Tests::createMainWindow(QSize sz, KDDockWidgets::MainWindowOptions options, const QString &name)
{
    static int count = 0;
    count++;

    const QString mainWindowName = name.isEmpty() ? QStringLiteral("MyMainWindow%1").arg(count)
                                                  : name;

    auto ptr = std::unique_ptr<MainWindowType>(new MainWindowType(mainWindowName, options));
    ptr->show();
    ptr->resize(sz);
    return ptr;
}

DockWidgetBase *KDDockWidgets::Tests::createDockWidget(const QString &name, QWidgetOrQuick *w,
                                                       DockWidgetBase::Options options, bool show,
                                                       const QString &affinityName)
{
    auto dock = new DockWidgetType(name, options);
    dock->setAffinityName(affinityName);
    dock->DockWidgetBase::setWidget(w);
    dock->setObjectName(name);
    dock->setGeometry(QRect(0, 0, 400, 400));
    if (show) {
        dock->show();
        dock->morphIntoFloatingWindow();
        dock->activateWindow();
        Q_ASSERT(dock->window());
        if (QTest::qWaitForWindowActive(dock->window()->windowHandle(), 200)) {
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

static QWidgetOrQuick *createGuestWidget(int i)
{
#ifdef KDDOCKWIDGETS_QTWIDGETS
    return new QPushButton(QStringLiteral("%1").arg(i));
#else
    Q_UNUSED(i);
    return new QWidgetAdapter();
#endif
}

std::unique_ptr<MainWindowBase> KDDockWidgets::Tests::createMainWindow(QVector<DockDescriptor> &docks)
{
    static int count = 0;
    count++;
    auto m = std::unique_ptr<MainWindowType>(new MainWindowType(QStringLiteral("MyMainWindow%1").arg(count), MainWindowOption_None));
    auto layout = m->multiSplitter();
    m->show();
    m->resize(QSize(700, 700));

    int i = 0;
    for (DockDescriptor &desc : docks) {
        desc.createdDock = createDockWidget(QStringLiteral("%1-%2").arg(i).arg(count), createGuestWidget(i), {}, false);
        DockWidgetBase *relativeTo = nullptr;
        if (desc.relativeToIndex != -1)
            relativeTo = docks.at(desc.relativeToIndex).createdDock;

        m->addDockWidget(desc.createdDock, desc.loc, relativeTo, desc.option);

        layout->checkSanity();
        ++i;
    }

    return m;
}

MyWidget::MyWidget(const QString &, QColor c)
    : QWidgetOrQuick()
    , c(c)
{
}

MyWidget::~MyWidget()
{
}

#ifdef KDDOCKWIDGETS_QTWIDGETS
void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), c);
}
#endif

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

void KDDockWidgets::Tests::doubleClickOn(QPoint globalPos, QWidget *receiver)
{
    QCursor::setPos(globalPos);
    QMouseEvent ev(QEvent::MouseButtonDblClick, receiver->mapFromGlobal(globalPos), receiver->window()->mapFromGlobal(globalPos), globalPos,
                   Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    qApp->sendEvent(receiver, &ev);
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
