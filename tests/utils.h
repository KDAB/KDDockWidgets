/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_TESTS_UTILS_H
#define KDDOCKWIDGETS_TESTS_UTILS_H

#include "KDDockWidgets.h"
#include "DropIndicatorOverlayInterface_p.h"
#include "DockWidgetBase.h"
#include "Config.h"
#include "TitleBar_p.h"
#include "FloatingWindow_p.h"
#include "DropArea_p.h"
#include "Utils_p.h"

#ifdef KDDOCKWIDGETS_QTWIDGETS
# include "widgets/TabWidgetWidget_p.h"
# include "widgets/FrameWidget_p.h"
# include <QWidget>
# include <QToolButton>
#else
# include <QQuickView>
#endif

#include <QPointer>
#include <QVector>
#include <QtTest/QtTest>

#include <memory>

static bool s_pauseBeforePress = false; // for debugging
static bool s_pauseBeforeMove = false; // for debugging
#define DEBUGGING_PAUSE_DURATION 5000 // 5 seconds

// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates

namespace KDDockWidgets {

class FrameWidget;

namespace Tests {

template <typename T>
inline QPointer<T> make_qpointer(T *t)
{
    // To support both QWidget and QtQuick we need QPointer<auto>, so use a function instead.
    return QPointer<T>(t);
}

enum ButtonAction {
    ButtonAction_None,
    ButtonAction_Press = 1,
    ButtonAction_Release = 2
};
Q_DECLARE_FLAGS(ButtonActions, ButtonAction)

struct DockDescriptor {
    Location loc;
    int relativeToIndex;
    QPointer<DockWidgetBase> createdDock;
    KDDockWidgets::AddingOption option;
};

inline bool shouldSkipTests()
{
    // Skip mac+offscreen on Qt <= 5.15.0 due to a QPA crash, fixed in 5.15.1
#if defined(Q_OS_MACOS) && QT_VERSION <= QT_VERSION_CHECK(5, 15, 0)
    if (qApp->platformName() == QLatin1String("offscreen"))
        return true;
#endif

    return false;
}

struct EnsureTopLevelsDeleted
{
    EnsureTopLevelsDeleted()
        : m_originalFlags(Config::self().flags())
        , m_originalSeparatorThickness(Config::self().separatorThickness())
    {
    }

    ~EnsureTopLevelsDeleted()
    {
        if (topLevels().size() != 0) {
            qWarning() << "There's still top-level widgets present!" << topLevels();
        }

        // Other cleanup, since we use this class everywhere
        Config::self().setDockWidgetFactoryFunc(nullptr);
        Config::self().setFlags(m_originalFlags);
        Config::self().setSeparatorThickness(m_originalSeparatorThickness);
    }

    QWidgetList topLevels() const
    {
        QWidgetList result;
#ifdef KDDOCKWIDGETS_QTWIDGETS
        for (QWidget *w : qApp->topLevelWidgets()) {
            if (!qobject_cast<QToolButton*>(w))
                result << w;
        }
#endif
        return result;
    }

    const Config::Flags m_originalFlags;
    const int m_originalSeparatorThickness;
};

bool shouldBlacklistWarning(const QString &msg, const QString &category = {});

std::unique_ptr<MainWindowBase> createMainWindow(QSize sz = {600, 600},
                                                            KDDockWidgets::MainWindowOptions options = MainWindowOption_HasCentralFrame, const QString &name = {});



std::unique_ptr<KDDockWidgets::MainWindowBase> createMainWindow(QVector<DockDescriptor> &docks);

KDDockWidgets::DockWidgetBase *createDockWidget(const QString &name, QWidgetOrQuick *w,
                                                DockWidgetBase::Options options = {}, bool show = true,
                                                const QString &affinityName = {});
KDDockWidgets::DockWidgetBase *createDockWidget(const QString &name, QColor color = Qt::black);

void nestDockWidget(DockWidgetBase *dock, DropArea *dropArea, Frame *relativeTo,
                    KDDockWidgets::Location location);

class NonClosableWidget : public QWidget
{
public:
    Q_OBJECT
public:
    explicit NonClosableWidget(QWidget *parent = nullptr);
    ~NonClosableWidget() override;

protected:
    void closeEvent(QCloseEvent *event) override;
};

class MyWidget : public QWidgetOrQuick
{
public:
    explicit MyWidget(const QString &, QColor c = Qt::black);
    ~MyWidget() override;


    QSize minimumSizeHint() const override
    {
        return {100, 100};
    }

protected:
#ifdef KDDOCKWIDGETS_QTWIDGETS
    void paintEvent(QPaintEvent *) override;
#endif
private:
    QColor c;
};


#ifdef KDDOCKWIDGETS_QTQUICK
// Don't want to adapt dozens of locations so it compiles for QtQuick, so just typedef.
// the fact it's a button isn't important for the tests anyway

class QPushButton : public MyWidget
{
public:
    // use const char* to silence QtCreator static analizer warnings when using const char * in tst_docks.cpp
    // We don't have QT_NO_CAST_FROM_ASCII and still it complains, so use an indirection so I can read tst_docks while
    // porting to QtQuick without noise. Once the port is done feel free to change to QString.
    explicit QPushButton(const char *name)
        : MyWidget(QString::fromLatin1(name))
    {
    }
};

class QLineEdit : public QWidgetAdapter
{
public:
    explicit QLineEdit()
        : QWidgetAdapter()
    {
    }
};

class QTextEdit : public QWidgetAdapter
{
public:
    explicit QTextEdit()
        : QWidgetAdapter()
    {
    }
};

class MyWidget2 : public QWidgetAdapter
{
public:

    explicit MyWidget2(QSize minSz = QSize(1, 1))
    {
        setMinimumSize(minSz);
        setSizeHint(minSz);
    }

    QSize sizeHint() const
    {
        return m_sizeHint;
    }

    void setSizeHint(QSize s)
    {
        m_sizeHint = s;
    }

    QSize m_sizeHint;
};

#else

namespace {

class MyWidget2 : public QWidget
{
public:

    explicit MyWidget2(QSize minSz = QSize(1,1))
        : m_minSz(minSz)
        , m_sizeHint(minSz)
    {

    }

    QSize sizeHint() const override
    {
        return m_sizeHint;
    }

    QSize minimumSizeHint() const override
    {
        return m_minSz;
    }

    void setMinSize(QSize s)
    {
        m_minSz = s;
        updateGeometry();
    }

    void setSizeHint(QSize s)
    {
        m_sizeHint = s;
    }

    QSize m_minSz;
    QSize m_sizeHint;
};
}

#endif

void doubleClickOn(QPoint globalPos, WidgetType *receiver);
void pressOn(QPoint globalPos, WidgetType *receiver);
void releaseOn(QPoint globalPos, WidgetType *receiver);
void clickOn(QPoint globalPos, WidgetType *receiver);
void moveMouseTo(QPoint globalDest, WidgetType *receiver);

inline FloatingWindow *createFloatingWindow()
{
    static int count = 0;
    count++;
    auto dock = createDockWidget(QString("dock %1").arg(count), Qt::green);
    return dock->morphIntoFloatingWindow();
}

inline WidgetType *draggableFor(WidgetType *w)
{
    WidgetType *draggable = nullptr;
    if (auto dock = qobject_cast<DockWidgetBase *>(w)) {
        if (auto frame = dock->frame())
            draggable = frame->titleBar();
    } else if (auto fw = qobject_cast<FloatingWindow *>(w)) {
#ifdef KDDOCKWIDGETS_QTWIDGETS
        auto frame = fw->hasSingleFrame() ? static_cast<FrameWidget*>(fw->frames().first())
                                          : nullptr;
        draggable = ((KDDockWidgets::Config::self().flags() & KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible) && frame && frame->hasTabsVisible()) ? static_cast<QWidget*>(frame->tabWidget()->asWidget())
                                                                                                                                                            : static_cast<QWidget*>(fw->titleBar());
    } else if (qobject_cast<TabWidgetWidget *>(w)) {
        draggable = w;
#else
        Q_UNUSED(fw);
#endif
    } else if (qobject_cast<TitleBar *>(w)) {
        draggable = w;
    }

    qDebug() << "Draggable is" << draggable;
    return draggable;
}

inline void drag(WidgetType *sourceWidget, QPoint pressGlobalPos, QPoint globalDest,
                 ButtonActions buttonActions = ButtonActions(ButtonAction_Press) | ButtonAction_Release)
{
    if (buttonActions & ButtonAction_Press) {
        if (s_pauseBeforePress)
            QTest::qWait(DEBUGGING_PAUSE_DURATION);

        pressOn(pressGlobalPos, sourceWidget);
    }

    activateWindow(sourceWidget->window());

    if (s_pauseBeforeMove)
        QTest::qWait(DEBUGGING_PAUSE_DURATION);

    qDebug() << "Moving sourceWidget to" << globalDest
             << "; sourceWidget->size=" << sourceWidget->size()
             << "; from=" << QCursor::pos();
    moveMouseTo(globalDest, sourceWidget);
    qDebug() << "Arrived at" << QCursor::pos();
    pressGlobalPos = KDDockWidgets::mapToGlobal(sourceWidget, QPoint(10, 10));
    if (buttonActions & ButtonAction_Release)
        releaseOn(globalDest, sourceWidget);
}

inline void drag(WidgetType *sourceWidget, QPoint globalDest,
                 ButtonActions buttonActions = ButtonActions(ButtonAction_Press) | ButtonAction_Release)
{
    Q_ASSERT(sourceWidget && sourceWidget->isVisible());

    WidgetType *draggable = draggableFor(sourceWidget);

    Q_ASSERT(draggable && draggable->isVisible());
    const QPoint pressGlobalPos = KDDockWidgets::mapToGlobal(draggable, QPoint(6, 6));

    drag(draggable, pressGlobalPos, globalDest, buttonActions);
}

inline void dragFloatingWindowTo(FloatingWindow *fw, QPoint globalDest,
                                 ButtonActions buttonActions = ButtonActions(ButtonAction_Press) | ButtonAction_Release)
{
    auto draggable = draggableFor(fw);
    Q_ASSERT(draggable && draggable->isVisible());
    drag(draggable, KDDockWidgets::mapToGlobal(draggable, QPoint(10, 10)), globalDest, buttonActions);
}

inline void dragFloatingWindowTo(FloatingWindow *fw, DropArea *target, DropIndicatorOverlayInterface::DropLocation dropLocation)
{
    auto draggable = draggableFor(fw);

    // First we drag over it, so the drop indicators appear:
    drag(draggable, KDDockWidgets::mapToGlobal(draggable, QPoint(10, 10)), target->window()->mapToGlobal(target->window()->rect().center()), ButtonAction_Press);

    // Now we drag over the drop indicator and only then release mouse:
    DropIndicatorOverlayInterface *dropIndicatorOverlay = target->dropIndicatorOverlay();
    const QPoint dropPoint = dropIndicatorOverlay->posForIndicator(dropLocation);

    drag(draggable, QPoint(), dropPoint, ButtonAction_Release);
}

}

inline bool qpaPassedAsArgument(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        if (qstrcmp(argv[i], "-platform") == 0) {
            return true;
        }
    }

    return false;
}

}

Q_DECLARE_METATYPE(KDDockWidgets::Tests::DockDescriptor)


#endif

