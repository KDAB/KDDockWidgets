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

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref

#include "DockWidget.h"
#include "MainWindow.h"
#include "FloatingWindow_p.h"
#include "DockRegistry_p.h"
#include "Frame_p.h"
#include "DropArea_p.h"
#include "TitleBar_p.h"
#include "WindowBeingDragged_p.h"
#include "Utils_p.h"
#include "LayoutSaver.h"
#include "TabWidget_p.h"
#include "multisplitter/MultiSplitterWidget_p.h"
#include "LastPosition_p.h"
#include <QtTest/QtTest>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QTabBar>
#include <QAction>
#include <QTime>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

#ifdef Q_OS_WIN
# include <Windows.h>
#endif

#define STATIC_ANCHOR_LENGTH 1
#define ANCHOR_LENGTH 5
#define WAIT QTest::qWait(5000000);
using namespace KDDockWidgets;

static bool s_pauseBeforePress = false; // for debugging
static bool s_pauseBeforeMove = false; // for debugging
#define DEBUGGING_PAUSE_DURATION 5000 // 5 seconds


extern quintptr Q_CORE_EXPORT qtHookData[];

struct WidgetResize
{
    int length;
    Qt::Orientation orientation;
    QWidget *w;
};
typedef QVector<WidgetResize> WidgetResizes;
Q_DECLARE_METATYPE(WidgetResize)

struct MultiSplitterSetup
{
    QSize size;
    QWidgetList widgets;
    QWidgetList relativeTos;
    WidgetResizes widgetResizes;

    QVector<KDDockWidgets::Location> locations;
};
Q_DECLARE_METATYPE(MultiSplitterSetup)

class EmbeddedWindow : public QWidget
{
public:
    explicit EmbeddedWindow(MainWindow *m)
        : mainWindow(m)
    {
    }

    MainWindow *const mainWindow;
};

struct ExpectedAvailableSize // struct for testing MultiSplitterLayout::availableLengthForDrop()
{
    KDDockWidgets::Location location;
    QWidget *relativeTo;
    int side1ExpectedSize;
    int side2ExpectedSize;
    int totalAvailable;
};
typedef QVector<ExpectedAvailableSize> ExpectedAvailableSizes;
Q_DECLARE_METATYPE(ExpectedAvailableSize)


struct ExpectedRectForDrop // struct for testing MultiSplitterLayout::availableLengthForDrop()
{
    QWidget *widgetToDrop;
    KDDockWidgets::Location location;
    Frame *relativeTo;
    QRect expectedRect;
};
typedef QVector<ExpectedRectForDrop> ExpectedRectsForDrop;
Q_DECLARE_METATYPE(ExpectedRectForDrop)

int osWindowMinWidth()
{
#ifdef Q_OS_WIN
    return GetSystemMetrics(SM_CXMIN);
#else
    return 140; // Some random value for our windows. It's only important on Windows
#endif
}


namespace KDDockWidgets {

enum ButtonAction {
    ButtonAction_None,
    ButtonAction_Press = 1,
    ButtonAction_Release = 2
};
Q_DECLARE_FLAGS(ButtonActions, ButtonAction)

static QtMessageHandler s_original = nullptr;

static bool isGammaray()
{
    static bool is = qtHookData[3] != 0;
    return is;
}
namespace {
class EventFilter : public QObject
{
public:
    EventFilter() {}
    bool eventFilter(QObject *, QEvent *e)
    {
        if (e->type() == QEvent::Resize)
            m_gotResize = true;

        return false;
    }


    bool m_gotResize = false;
};


class WidgetWithMinSize : public QWidget
{
public:
    WidgetWithMinSize(QSize minSize)
    {
        m_minSize = minSize;
    }

    QSize minimumSizeHint() const override
    {
        return m_minSize;
    }

    QSize m_minSize;
};
}

static QWidget *createWidget(int minLength, const QString &objname = QString())
{
    auto w = new WidgetWithMinSize(QSize(minLength, minLength));
    w->setObjectName(objname);
    return w;
}

void fatalWarningsMessageHandler(QtMsgType t, const QMessageLogContext &context, const QString &msg)
{
    s_original(t, context, msg);
    if (t == QtWarningMsg) {

        if (QLatin1String(context.category) == QLatin1String("qt.qpa.xcb"))
            return;

        if (msg.contains(QLatin1String("QSocketNotifier: Invalid socket")) ||
            msg.contains(QLatin1String("QWindowsWindow::setGeometry")) ||
            msg.contains(QLatin1String("This plugin does not support")) ||
            msg.contains(QLatin1String("Note that Qt no longer ships fonts")))
            return;

        if (!isGammaray() && !qEnvironmentVariableIsSet("NO_FATAL"))
            qFatal("Got a warning, category=%s", context.category);
    }
}

struct EnsureTopLevelsDeleted
{
    EnsureTopLevelsDeleted()
        : m_initialNumWindows(qApp->topLevelWidgets().size())
    {
    }

    ~EnsureTopLevelsDeleted()
    {
        if (qApp->topLevelWidgets().size() != m_initialNumWindows) {
            qWarning() << "There's still top-level widgets present!" << qApp->topLevelWidgets() << m_initialNumWindows;
        }
    }

    const int m_initialNumWindows;
};

class TestDocks : public QObject
{
    Q_OBJECT
public Q_SLOTS:
    void initTestCase()
    {
        qApp->setOrganizationName(QStringLiteral("KDAB"));
        qApp->setApplicationName(QStringLiteral("dockwidgets-unit-tests"));
        s_original = qInstallMessageHandler(fatalWarningsMessageHandler);
    }
public:
    static void nestDockWidget(DockWidget *dock, DropArea *dropArea, Frame *relativeTo, KDDockWidgets::Location location);

private Q_SLOTS:
    void tst_simple1();
    void tst_simple2();
    void tst_shutdown();
    void tst_mainWindowAlwaysHasCentralWidget();
    void tst_createFloatingWindow();
    void tst_dock2FloatingWidgetsTabbed();
    void tst_close();
    void tst_closeAllDockWidgets();
    void tst_dockDockWidgetNested();
    void tst_dockFloatingWindowNested();
    void tst_anchorsFromTo();
    void tst_dockWindowWithTwoSideBySideFramesIntoCenter();
    void tst_dockWindowWithTwoSideBySideFramesIntoLeft();
    void tst_dockWindowWithTwoSideBySideFramesIntoRight();
    void tst_posAfterLeftDetach();
    void tst_propagateMinSize();
    void tst_dockInternal();
    void tst_propagateSizeHonoursMinSize();

    void tst_addDockWidgetAsTabToDockWidget();
    void tst_addDockWidgetToMainWindow(); // Tests MainWindow::addDockWidget();
    void tst_addDockWidgetToContainingWindow();
    void tst_addToSmallMainWindow();
    void tst_fairResizeAfterRemoveWidget();
    void tst_notClosable();
    void tst_maximizeAndRestore();
    void tst_propagateResize2();

    void tst_availableLengthForDrop_data();
    void tst_availableLengthForDrop();

    void tst_rectForDrop_data();
    void tst_rectForDrop();
    void tst_crash(); // tests some crash I got
    void tst_setFloatingWhenWasTabbed();
    void tst_setFloatingWhenSideBySide();
    void tst_setVisibleFalseWhenSideBySide();
    void tst_refUnrefItem();
    void tst_addAndReadd();
    void tst_placeholderCount();
    void tst_availableLengthForOrientation();
    void tst_setAstCurrentTab();
    void tst_closeShowWhenNoCentralFrame();
    void tst_placeholderDisappearsOnReadd();
    void tst_placeholdersAreRemovedPropertly();
    void tst_embeddedMainWindow();
private:
    void tst_restoreEmpty(); // TODO. Disabled for now, save/restore needs to support placeholders
    void tst_restoreCrash(); // TODO. Disabled for now, save/restore needs to support placeholders
    std::unique_ptr<MultiSplitterWidget> createMultiSplitterFromSetup(MultiSplitterSetup setup, QHash<QWidget *, Frame *> &frameMap) const;
};
}

static std::unique_ptr<MainWindow> createMainWindow(QSize sz = {600, 600}, MainWindowOptions options = MainWindowOption_HasCentralFrame)
{
    auto ptr = std::unique_ptr<MainWindow>(new MainWindow(QStringLiteral("MyMainWindow"), options));
    ptr->show();
    ptr->resize(sz);
    return ptr;
}

static EmbeddedWindow *createEmbeddedMainWindow(QSize sz)
{
    // Tests a MainWindow which isn't a top-level window, but is embedded in another window
    auto mainwindow = new MainWindow(QStringLiteral("MyMainWindow"));

    auto window = new EmbeddedWindow(mainwindow);
    auto lay = new QVBoxLayout(window);
    lay->setContentsMargins(100, 100, 100, 100);
    lay->addWidget(mainwindow);
    window->show();
    window->resize(sz);
    return window;
}

namespace {
class MyWidget : public QWidget
{
public:
    explicit MyWidget(const QString &, QColor c)
        : QWidget()
        , c(c)
    {
        qDebug() << "MyWidget" << this;
    }

    ~MyWidget() override
    {
        qDebug() << "~MyWidget" << this;
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.fillRect(rect(), c);
    }

    QColor c;
};

class MyWidget2 : public QWidget
{
public:

    explicit MyWidget2(QSize minSz = QSize(1,1))
        : m_minSz(minSz)
    {

    }

    QSize sizeHint() const override
    {
        return m_minSz;
    }

    QSize minimumSizeHint() const override
    {
        return m_minSz;
    }

    QSize m_minSz;
};
}

bool waitForDeleted(QObject *o, int timeout = 2000)
{
    if (!o)
        return true;

    QPointer<QObject> ptr = o;
    QTime time;
    time.start();

    while (ptr && time.elapsed() < timeout) {
        qApp->processEvents();
        QTest::qWait(50);
    }

    const bool wasDeleted = !ptr;
    return wasDeleted;
}

bool waitForResize(QWidget *w, int timeout = 2000)
{
    EventFilter filter;
    w->installEventFilter(&filter);
    QTime time;
    time.start();

    while (!filter.m_gotResize && time.elapsed() < timeout) {
        qApp->processEvents();
        QTest::qWait(50);
    }

    return filter.m_gotResize;
}

static QTabBar *tabBarForFrame(Frame *f)
{
    return f->findChild<QTabBar *>(QString(), Qt::FindChildrenRecursively);
}

void moveMouseTo(QPoint globalDest, QWidget *receiver)
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

static void pressOn(QPoint globalPos, QWidget *receiver)
{
    QCursor::setPos(globalPos);
    QMouseEvent ev(QEvent::MouseButtonPress, receiver->mapFromGlobal(globalPos), receiver->window()->mapFromGlobal(globalPos), globalPos,
                   Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    qApp->sendEvent(receiver, &ev);
}

void releaseOn(QPoint globalPos, QWidget *receiver)
{
    QMouseEvent ev(QEvent::MouseButtonRelease, receiver->mapFromGlobal(globalPos), receiver->window()->mapFromGlobal(globalPos), globalPos,
                   Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    qApp->sendEvent(receiver, &ev);
}

static void drag(QWidget *sourceWidget, QPoint pressGlobalPos, QPoint globalDest, ButtonActions buttonActions = ButtonActions(ButtonAction_Press) | ButtonAction_Release)
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
             << "; sourceWidget->size=" << sourceWidget->size();
    moveMouseTo(globalDest, sourceWidget);
    qDebug() << "Arrived at" << QCursor::pos();
    pressGlobalPos = sourceWidget->mapToGlobal(QPoint(10, 10));
    if (buttonActions & ButtonAction_Release)
        releaseOn(globalDest, sourceWidget);
}

static void drag(QWidget *sourceWidget, QPoint globalDest, ButtonActions buttonActions = ButtonActions(ButtonAction_Press) | ButtonAction_Release)
{
    Q_ASSERT(sourceWidget && sourceWidget->isVisible());

    TitleBar *titleBar = nullptr;
    if (auto dock = qobject_cast<DockWidget *>(sourceWidget)) {
        titleBar = dock->titleBar();

        if (!titleBar->isVisible()) {
            if (auto frame = dock->frame()) {
                titleBar = frame->titleBar();
            }
        }
    } else if (auto fw = qobject_cast<FloatingWindow *>(sourceWidget)) {
        titleBar = fw->titleBar();
    }

    Q_ASSERT(titleBar && titleBar->isVisible());
    const QPoint pressGlobalPos = titleBar->mapToGlobal(QPoint(6, 6));

    drag(titleBar, pressGlobalPos, globalDest, buttonActions);
}

static void dragFloatingWindowTo(FloatingWindow *fw, QPoint globalDest, ButtonActions buttonActions = ButtonActions(ButtonAction_Press) | ButtonAction_Release)
{
    auto sourceTitleBar = fw->actualTitleBar();
    Q_ASSERT(sourceTitleBar && sourceTitleBar->isVisible());
    drag(sourceTitleBar, sourceTitleBar->mapToGlobal(QPoint(10, 10)), globalDest, buttonActions);
}

static void dragFloatingWindowTo(FloatingWindow *fw, DropArea *target, DropIndicatorOverlayInterface::DropLocation dropLocation)
{
    auto sourceTitleBar = fw->actualTitleBar();

    // First we drag over it, so the drop indicators appear:
    drag(sourceTitleBar, sourceTitleBar->mapToGlobal(QPoint(10, 10)), target->window()->mapToGlobal(QPoint(50, 50)), ButtonAction_Press);

    // Now we drag over the drop indicator and only then release mouse:
    DropIndicatorOverlayInterface *dropIndicatorOverlay = target->dropIndicatorOverlay();
    const QPoint dropPoint = dropIndicatorOverlay->posForIndicator(dropLocation);

    drag(sourceTitleBar, QPoint(), dropPoint, ButtonAction_Release);
}

DockWidget *createDockWidget(const QString &name, QWidget *w, DockWidget::Options options = {})
{
    auto dock = new DockWidget(name, options);
    dock->setWidget(w);
    dock->setObjectName(name);
    dock->setGeometry(0, 0, 400, 400);
    dock->show();
    dock->activateWindow();
    Q_ASSERT(dock->window());
    Q_ASSERT(dock->windowHandle());
    if (QTest::qWaitForWindowActive(dock->window()->windowHandle(), 200)) {
        qDebug() << dock->window();
        return dock;
    }
    return nullptr;
};

Frame* createFrameWithWidget(const QString &name, MultiSplitterWidget *parent, int minLength = -1)
{
    QWidget *w = createWidget(minLength, name);
    auto dw = new DockWidget(name);
    dw->setWidget(w);
    auto frame = new Frame(parent);
    frame->addWidget(dw);
    return frame;
}

DockWidget *createDockWidget(const QString &name, QColor color)
{
    return createDockWidget(name, new MyWidget(name, color));
};

FloatingWindow *createFloatingWindow()
{
    static int count = 0;
    count++;
    auto dock = createDockWidget(QStringLiteral("docfw %1").arg(count), Qt::green);
    return dock->morphIntoFloatingWindow();
}

void TestDocks::tst_createFloatingWindow()
{
    EnsureTopLevelsDeleted e;

    auto dock = createDockWidget(QStringLiteral("doc1"), Qt::green);
    QVERIFY(dock);
    QVERIFY(dock->isFloating());

    QVERIFY(dock->name() == QLatin1String("doc1")); // 1.0 objectName() is inherited
    QCOMPARE(dock->window(), dock);

    dock->morphIntoFloatingWindow();

    QPointer<FloatingWindow> window = qobject_cast<FloatingWindow *>(dock->window());
    QVERIFY(window); // 1.1 DockWidget creates a FloatingWindow and is reparented
    QVERIFY(window->dropArea()->checkSanity());
    delete dock;

    QVERIFY(waitForDeleted(window)); // 1.2 Floating Window is destroyed when DockWidget is destroyed
    QVERIFY(!window);
}

void TestDocks::nestDockWidget(DockWidget *dock, DropArea *dropArea, Frame *relativeTo, KDDockWidgets::Location location)
{
    auto frame = new Frame();
    frame->addWidget(dock);
    dock->frame()->setObjectName(dock->objectName());

    qDebug() << "Adding widget" << frame
             << "; min width=" << widgetMinLength(frame, Qt::Vertical)
             << "; min height=" << widgetMinLength(frame, Qt::Horizontal);

    dropArea->multiSplitter()->addWidget(frame, location, relativeTo);
    QVERIFY(dropArea->checkSanity());
    qDebug() << "Size after adding: " << frame->size();
}

DockWidget *createAndNestDockWidget(DropArea *dropArea, Frame *relativeTo, KDDockWidgets::Location location)
{
    static int count = 0;
    count++;
    const QString name = QStringLiteral("dock%1").arg(count);
    auto dock = createDockWidget(name, Qt::red);
    dock->setObjectName(name);
    TestDocks::nestDockWidget(dock, dropArea, relativeTo, location);
    dropArea->checkSanity();
    return dock;
}

std::unique_ptr<MainWindow> createSimpleNestedMainWindow(DockWidget * *centralDock, DockWidget * *leftDock, DockWidget * *rightDock)
{
    auto window = createMainWindow({900, 500});
    *centralDock = createDockWidget(QStringLiteral("centralDock"), Qt::green);
    window->addDockWidgetAsTab(*centralDock);
    QWidget *central = window->centralWidget();
    auto dropArea = qobject_cast<DropArea *>(central);

    *leftDock = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnLeft);
    *rightDock = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnRight);
    return window;
}

void TestDocks::tst_dock2FloatingWidgetsTabbed()
{
    EnsureTopLevelsDeleted e;

    if (KDDockWidgets::supportsNativeTitleBar())
        return; // Unit-tests can't drag via tab, yet

    auto dock1 = createDockWidget(QStringLiteral("doc1"), Qt::green);
    dock1->window()->setGeometry(500, 500, 400, 400);
    QVERIFY(dock1);
    QPointer<Frame> frame1 = dock1->frame();
    QVERIFY(!frame1); // Doesn't have frame yet

    auto titlebar1 = dock1->titleBar();
    auto dock2 = createDockWidget(QStringLiteral("doc2"), Qt::red);

    QVERIFY(dock1->isFloating());
    QVERIFY(dock2->isFloating());

    drag(titlebar1, titlebar1->mapToGlobal(QPoint(5, 5)), dock2->window()->geometry().center(), ButtonAction_Press);

    // It morphed into a FloatingWindow
    QPointer<Frame> frame2 = dock2->frame();
    if (!qobject_cast<FloatingWindow *>(dock2->window())) {
        qWarning() << "dock2->window()=" << dock2->window();
        QVERIFY(false);
    }
    QVERIFY(frame2);
    QCOMPARE(frame2->dockWidgetCount(), 1);

    releaseOn(dock2->window()->geometry().center(), titlebar1);
    QCOMPARE(frame2->dockWidgetCount(), 2); // 2.2 Frame has 2 widgets when one is dropped

    QVERIFY(waitForDeleted(frame1));

    // 2.3 Detach tab1 to empty space
    QPoint globalPressPos = frame2->dragPointForWidget(0);
    QTabBar *tabBar = tabBarForFrame(frame2);
    QVERIFY(tabBar);
    drag(tabBar, globalPressPos, frame2->window()->geometry().bottomRight() + QPoint(10, 10));

    QVERIFY(frame2->dockWidgetCount() == 1);
    QVERIFY(qobject_cast<FloatingWindow *>(dock1->window()));

    // 2.4 Drag the first dock over the second
    frame1 = dock1->frame();
    frame2 = dock2->frame();
    drag(dock1, frame1->mapToGlobal(QPoint(10, 10)), dock2->window()->geometry().center());
    QCOMPARE(frame2->dockWidgetCount(), 2);

    // 2.5 Detach and drop to the same place, should tab again
    globalPressPos = frame2->dragPointForWidget(0);
    tabBar = tabBarForFrame(frame2);
    drag(tabBar, globalPressPos, dock2->window()->geometry().center());
    QCOMPARE(frame2->dockWidgetCount(), 2);

    // 2.6 Drag the tabbed group over a 3rd floating window
    auto dock3 = createDockWidget(QStringLiteral("doc3"), Qt::black);
    QTest::qWait(1000); // Test is flaky otherwise
    drag(frame2->window(), frame2->mapToGlobal(QPoint(10, 10)), dock3->window()->geometry().center());

    QVERIFY(waitForDeleted(frame1));
    QVERIFY(waitForDeleted(frame2));
    QVERIFY(dock3->frame());
    QCOMPARE(dock3->frame()->dockWidgetCount(), 3);

    auto fw3 = qobject_cast<FloatingWindow *>(dock3->window());
    QVERIFY(fw3);
    QVERIFY(fw3->dropArea()->checkSanity());

    // 2.7 Drop the window into a MainWindow
    {
        MainWindow m(QStringLiteral("MyMainWindow"));
        m.show();
        m.setGeometry(500, 300, 300, 300);
        QVERIFY(!dock3->isFloating());
        drag(dock3->window(), dock3->window()->mapToGlobal(QPoint(10, 10)), m.geometry().center());
        QVERIFY(!dock3->isFloating());
        QVERIFY(qobject_cast<MainWindow *>(dock3->window()) == &m);
        QCOMPARE(dock3->frame()->dockWidgetCount(), 3);
        QVERIFY(qobject_cast<DropArea*>(m.centralWidget())->checkSanity());

        delete dock1;
        delete dock2;
        delete dock3;
        QVERIFY(waitForDeleted(frame2));
        QVERIFY(waitForDeleted(fw3));
    }
}

void TestDocks::tst_close()
{
    EnsureTopLevelsDeleted e;

    // 1.0 Call QWidget::close() on QDockWidget
    auto dock1 = createDockWidget(QStringLiteral("doc1"), Qt::green);
    QAction *toggleAction = dock1->toggleAction();
    QVERIFY(toggleAction->isChecked());

    QVERIFY(dock1->close());

    QVERIFY(!dock1->isVisible());
    QVERIFY(!dock1->window()->isVisible());
    QCOMPARE(dock1->window(), dock1);
    QVERIFY(!toggleAction->isChecked());

    // 1.1 Reshow with show()
    dock1->show();
    QVERIFY(toggleAction->isChecked());
    QVERIFY(dock1->isVisible());
    QCOMPARE(dock1->window(), dock1);
    QVERIFY(toggleAction->isChecked());

    // 1.2 Reshow with toggleAction instead
    QVERIFY(dock1->close());
    QVERIFY(!toggleAction->isChecked());
    QVERIFY(!dock1->isVisible());
    toggleAction->setChecked(true);
    QVERIFY(dock1->isVisible());

    // 1.3 Use hide() instead
    dock1->hide();
    QVERIFY(!dock1->isVisible());
    QVERIFY(!dock1->window()->isVisible());
    QCOMPARE(dock1->window(), dock1);
    QVERIFY(!toggleAction->isChecked());

    // 1.4 close a FloatingWindow, via DockWidget::close
    QPointer<FloatingWindow> window = dock1->morphIntoFloatingWindow();
    QPointer<Frame> frame1 = dock1->frame();
    QVERIFY(dock1->isVisible());
    QVERIFY(dock1->window()->isVisible());
    QVERIFY(frame1->isVisible());
    QCOMPARE(dock1->window(), window.data());

    QVERIFY(dock1->close());
    QVERIFY(!dock1->frame());
    QVERIFY(waitForDeleted(frame1));
    QVERIFY(waitForDeleted(window));

    // 1.5 close a FloatingWindow, via FloatingWindow::close
    dock1->show();
    QCOMPARE(dock1->window(), dock1);

    window = dock1->morphIntoFloatingWindow();
    frame1 = dock1->frame();
    QVERIFY(dock1->isVisible());
    QVERIFY(dock1->window()->isVisible());
    QVERIFY(frame1->isVisible());
    QCOMPARE(dock1->window(), window.data());

    QVERIFY(window->close());

    QVERIFY(!dock1->frame());
    QVERIFY(waitForDeleted(frame1));
    QVERIFY(waitForDeleted(window));

    // TODO: 1.6 Test FloatingWindow with two frames
    // TODO: 1.7 Test Frame with two tabs

    // 1.8 Check if space is reclaimed after closing left dock
    DockWidget *centralDock;
    DockWidget *leftDock;
    DockWidget *rightDock;

    auto mainwindow = createSimpleNestedMainWindow(&centralDock, &leftDock, &rightDock);
    auto da = qobject_cast<DropArea*>(mainwindow->centralWidget());

    QVERIFY(da->checkSanity());
    QCOMPARE(leftDock->frame()->x(), STATIC_ANCHOR_LENGTH); // 1 = static anchor thickness
    QCOMPARE(centralDock->frame()->x(), leftDock->frame()->geometry().right() + ANCHOR_LENGTH + 1);
    QCOMPARE(rightDock->frame()->x(), centralDock->frame()->geometry().right() + ANCHOR_LENGTH + 1);
    leftDock->close();
    QTest::qWait(250); // TODO: wait for some signal
    QCOMPARE(centralDock->frame()->x(), STATIC_ANCHOR_LENGTH);
    QCOMPARE(rightDock->frame()->x(), centralDock->frame()->geometry().right() + ANCHOR_LENGTH + 1);

    rightDock->close();
    QTest::qWait(250); // TODO: wait for some signal
    QCOMPARE(centralDock->frame()->width(), mainwindow->width() - STATIC_ANCHOR_LENGTH*2);
    delete leftDock; delete rightDock; delete centralDock;

    // 1.9 Close tabbed dock, side docks will maintain their position
    mainwindow = createSimpleNestedMainWindow(&centralDock, &leftDock, &rightDock);
    const int leftX = leftDock->frame()->x();
    const int rightX = rightDock->frame()->x();

    centralDock->close();

    QCOMPARE(leftDock->frame()->x(), leftX);
    QCOMPARE(rightDock->frame()->x(), rightX);
    delete leftDock; delete rightDock; delete centralDock;
    delete dock1;


    // 2. Test that closing the single frame of a main window doesn't close the main window itself
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
        QPointer<MainWindow> mainWindowPtr = m.get();
        dock1 = createDockWidget(QStringLiteral("hello"), Qt::green);
        m->addDockWidget(dock1, Location_OnLeft);

        // 2.2 Closing should not close the main window
        dock1->close();
        QVERIFY(mainWindowPtr.data());
        delete dock1;
    }

    // 2.1 Test closing the frame instead
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
        QPointer<MainWindow> mainWindowPtr = m.get();
        dock1 = createDockWidget(QStringLiteral("hello"), Qt::green);
        m->addDockWidget(dock1, Location_OnLeft);

        // 2.2 Closing should not close the main window
        dock1->frame()->titleBar()->onCloseClicked();
        QVERIFY(mainWindowPtr.data());
        QVERIFY(mainWindowPtr->isVisible());
        delete dock1;
    }

    // 2.2 Repeat, but with a central frame
    {
        auto m = createMainWindow(QSize(800, 500));
        QPointer<MainWindow> mainWindowPtr = m.get();
        dock1 = createDockWidget(QStringLiteral("hello"), Qt::green);
        m->addDockWidget(dock1, Location_OnLeft);

        // 2.2 Closing should not close the main window
        dock1->frame()->titleBar()->onCloseClicked();
        QVERIFY(mainWindowPtr.data());
        QVERIFY(mainWindowPtr->isVisible());
        delete dock1;
    }
}

void TestDocks::tst_dockDockWidgetNested()
{
    EnsureTopLevelsDeleted e;
    // Test detaching too, and check if the window size is correct


    // TODO
}

void TestDocks::tst_dockFloatingWindowNested()
{
    EnsureTopLevelsDeleted e;
    // TODO
}

void TestDocks::tst_anchorsFromTo()
{
    EnsureTopLevelsDeleted e;

    DockWidget *centralDock;
    DockWidget *leftDock;
    DockWidget *rightDock;
    auto mainwindow = createSimpleNestedMainWindow(&centralDock, &leftDock, &rightDock);
    auto dropArea = qobject_cast<DropArea *>(mainwindow->centralWidget());
    QVERIFY(dropArea->checkSanity());

    auto nonStaticAnchors = dropArea->nonStaticAnchors();
    AnchorGroup staticAnchors = dropArea->multiSplitter()->staticAnchorGroup();

    QVERIFY(staticAnchors.isValid());
    QCOMPARE(nonStaticAnchors.size(), 2);

    for (Anchor *anchor : nonStaticAnchors) {
        QCOMPARE(anchor->orientation(), Qt::Vertical);
        QCOMPARE(anchor->from(), staticAnchors.top);
        QCOMPARE(anchor->to(), staticAnchors.bottom);
    }

    qDebug() << "Adding the bottom one";
    QVERIFY(dropArea->checkSanity());
    DockWidget *bottom = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnBottom);
    QVERIFY(dropArea->checkSanity());
    nonStaticAnchors = dropArea->nonStaticAnchors();
    auto horizAnchors = dropArea->multiSplitter()->anchors(Qt::Horizontal);
    auto vertAnchors = dropArea->multiSplitter()->anchors(Qt::Vertical);
    QCOMPARE(nonStaticAnchors.size(), 3);
    QCOMPARE(horizAnchors.size(), 1);
    QCOMPARE(vertAnchors.size(), 2);

    for (Anchor *anchor : horizAnchors) {
        QCOMPARE(anchor->orientation(), Qt::Horizontal);
        QCOMPARE(anchor->from(), staticAnchors.left);
        QCOMPARE(anchor->to(), staticAnchors.right);
    }

    for (Anchor *anchor : vertAnchors) {
        QCOMPARE(anchor->orientation(), Qt::Vertical);
        QCOMPARE(anchor->from(), staticAnchors.top);
        QCOMPARE(anchor->to(), horizAnchors.at(0));
    }

    // Float bottom, check if horizontal anchor is deleted, and from/to updated
    Anchor *follower = horizAnchors.at(0);
    auto window = bottom->frame()->titleBar()->makeWindow();
    QVERIFY(dropArea->checkSanity());
    QVERIFY(qobject_cast<FloatingWindow *>(window->window()));
    QVERIFY(follower->isFollowing());

    nonStaticAnchors = dropArea->nonStaticAnchors();
    horizAnchors = dropArea->multiSplitter()->anchors(Qt::Horizontal, false, false);
    vertAnchors = dropArea->multiSplitter()->anchors(Qt::Vertical, false, false);
    QCOMPARE(nonStaticAnchors.size(), 2);
    QCOMPARE(horizAnchors.size(), 0);
    QCOMPARE(vertAnchors.size(), 2);
    for (Anchor *anchor : qAsConst(vertAnchors)) {
        QCOMPARE(anchor->orientation(), Qt::Vertical);
        if (!anchor->isValid()) {
            qDebug() << "anchors:" << anchor->to() << anchor->from();
            QVERIFY(false);
        }

        QCOMPARE(anchor->from(), staticAnchors.top);
        QCOMPARE(anchor->to(), follower);
    }

    mainwindow.reset();
    delete window->window();

    {
        // Test a case where the to wasn't correct
        auto m = createMainWindow({400, 400});
        DropArea *dropArea = qobject_cast<DropArea *>(m->centralWidget());

        auto dock = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnRight);
        createAndNestDockWidget(dropArea, dock->frame(), KDDockWidgets::Location_OnBottom);

        const auto anchors = dropArea->nonStaticAnchors();
        QCOMPARE(anchors.size(), 2);
        QCOMPARE(anchors[1]->orientation(), Qt::Horizontal);
        QCOMPARE(anchors[1]->to()->objectName(), QStringLiteral("right"));
        QCOMPARE(anchors[1]->from(), anchors[0]);
    }
}

void TestDocks::tst_dockWindowWithTwoSideBySideFramesIntoCenter()
{
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();
    auto fw = createFloatingWindow();
    auto dock2 = createDockWidget(QStringLiteral("doc2"), Qt::red);
    nestDockWidget(dock2, fw->dropArea(), nullptr, KDDockWidgets::Location_OnLeft);
    QCOMPARE(fw->frames().size(), 2);
    QVERIFY(fw->dropArea()->checkSanity());

    auto fw2 = createFloatingWindow();
    fw2->move(fw->x() + fw->width() + 100, fw->y());

    dragFloatingWindowTo(fw, fw2->geometry().center());
    QVERIFY(fw2->dropArea()->checkSanity());

    QCOMPARE(fw2->frames().size(), 1);
    auto f2 = fw2->frames().constFirst();
    QCOMPARE(f2->dockWidgetCount(), 3);
    QVERIFY(waitForDeleted(fw));
    delete fw2;
}

void TestDocks::tst_dockWindowWithTwoSideBySideFramesIntoLeft()
{
    EnsureTopLevelsDeleted e;

    auto fw = createFloatingWindow();
    fw->setObjectName(QStringLiteral("fw1"));
    auto dock2 = createDockWidget(QStringLiteral("doc2"), Qt::red);
    nestDockWidget(dock2, fw->dropArea(), nullptr, KDDockWidgets::Location_OnLeft);
    QCOMPARE(fw->frames().size(), 2);

    auto fw2 = createFloatingWindow();
    fw2->setObjectName(QStringLiteral("fw2"));
    fw2->move(fw->x() + fw->width() + 100, fw->y());

    QVERIFY(fw2->dropArea()->checkSanity());
    dragFloatingWindowTo(fw, fw2->dropArea(), DropIndicatorOverlayInterface::DropLocation_Left);
    QCOMPARE(fw2->frames().size(), 3);

    auto anchors = fw2->dropArea()->nonStaticAnchors();
    QCOMPARE(anchors.size(), 2);
    QCOMPARE(anchors[0]->orientation(), Qt::Vertical);
    QCOMPARE(anchors[1]->orientation(), Qt::Vertical);

    QCOMPARE(anchors[0]->from()->objectName(), QStringLiteral("top"));
    QCOMPARE(anchors[0]->to()->objectName(), QStringLiteral("bottom"));
    QCOMPARE(anchors[1]->from()->objectName(), QStringLiteral("top"));
    QCOMPARE(anchors[1]->to()->objectName(), QStringLiteral("bottom"));

    QVERIFY(anchors[1]->position() < anchors[0]->position());
    fw2->dropArea()->debug_updateItemNamesForGammaray();
    QVERIFY(fw2->dropArea()->checkSanity());

    fw2->deleteLater();
    waitForDeleted(fw2);
}

void TestDocks::tst_dockWindowWithTwoSideBySideFramesIntoRight()
{
    EnsureTopLevelsDeleted e;

    auto fw = createFloatingWindow();
    auto dock2 = createDockWidget(QStringLiteral("doc2"), Qt::red);
    nestDockWidget(dock2, fw->dropArea(), nullptr, KDDockWidgets::Location_OnTop); // No we stack on top, unlike in previous test
    QCOMPARE(fw->frames().size(), 2);

    auto fw2 = createFloatingWindow();
    fw2->move(fw->x() + fw->width() + 100, fw->y());

    dragFloatingWindowTo(fw, fw2->dropArea(), DropIndicatorOverlayInterface::DropLocation_Right); // Outter right instead of Left
    QCOMPARE(fw2->frames().size(), 3);

    auto anchors = fw2->dropArea()->nonStaticAnchors();
    QCOMPARE(anchors.size(), 2);
    QCOMPARE(anchors[0]->orientation(), Qt::Vertical);
    QCOMPARE(anchors[1]->orientation(), Qt::Horizontal);

    QCOMPARE(anchors[0]->from()->objectName(), QStringLiteral("top"));
    QCOMPARE(anchors[0]->to()->objectName(), QStringLiteral("bottom"));
    QCOMPARE(anchors[1]->from(), anchors[0]);
    QCOMPARE(anchors[1]->to()->objectName(), QStringLiteral("right"));

    QVERIFY(anchors[1]->position() > 0);
    QVERIFY(anchors[1]->position() < fw2->height());
    QVERIFY(fw2->dropArea()->checkSanity());

    fw2->deleteLater();
    waitForDeleted(fw2);
}

void TestDocks::tst_posAfterLeftDetach()
{
    {
        EnsureTopLevelsDeleted e;
        auto fw = createFloatingWindow();
        auto dock2 = createDockWidget(QStringLiteral("doc2"), Qt::red);
        nestDockWidget(dock2, fw->dropArea(), nullptr, KDDockWidgets::Location_OnRight);
        QVERIFY(fw->dropArea()->checkSanity());
        // When dragging the right one there was a bug where it jumped
        const QPoint globalSrc = dock2->mapToGlobal(QPoint(0, 0));
        const int offset = 10;
        const QPoint globalDest = globalSrc + QPoint(offset, 0);
        drag(dock2, globalDest);
        QVERIFY(fw->dropArea()->checkSanity());
        const QPoint actualEndPos = dock2->mapToGlobal(QPoint(0, 0));
        QVERIFY(actualEndPos.x() - globalSrc.x() < offset + 5); // 5px so we have margin for window system fluctuations. The actual bug was a very big jump like 50px, so a 5 margin is fine to test that the bug doesn't happen

        delete dock2;
        fw->deleteLater();
        waitForDeleted(fw);
    }

    {
        EnsureTopLevelsDeleted e;
        auto fw = createFloatingWindow();
        auto dock2 = createDockWidget(QStringLiteral("doc2"), Qt::red);
        nestDockWidget(dock2, fw->dropArea(), nullptr, KDDockWidgets::Location_OnRight);
        QVERIFY(fw->dropArea()->checkSanity());

        const int originalX = dock2->mapToGlobal(QPoint(0, 0)).x();
        dock2->frame()->titleBar()->makeWindow();
        const int finalX = dock2->mapToGlobal(QPoint(0, 0)).x();

        QVERIFY(finalX - originalX < 10); // 10 or some other small number that is less than say 200

        delete dock2;
        fw->deleteLater();
        waitForDeleted(fw);
    }
}

void TestDocks::tst_shutdown()
{
    EnsureTopLevelsDeleted e;
    auto dock = createDockWidget(QStringLiteral("doc1"), Qt::green);

    auto m = createMainWindow();
    m->show();
    QVERIFY(QTest::qWaitForWindowActive(m->windowHandle()));
    delete dock;
}

void TestDocks::tst_mainWindowAlwaysHasCentralWidget()
{
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();
    QWidget *central = m->centralWidget();
    auto dropArea = qobject_cast<DropArea *>(central);
    QVERIFY(dropArea);

    QPointer<Frame> centralFrame = static_cast<Frame*>(dropArea->centralFrame()->frame());
    QVERIFY(central);
    QVERIFY(dropArea);
    QCOMPARE(dropArea->count(), 1);
    QVERIFY(centralFrame);
    QCOMPARE(centralFrame->dockWidgetCount(), 0);

    // Add a tab
    auto dock = createDockWidget(QStringLiteral("doc1"), Qt::green);
    m->addDockWidgetAsTab(dock);
    QCOMPARE(dropArea->count(), 1);
    QCOMPARE(centralFrame->dockWidgetCount(), 1);

    qDebug() << "Central widget width=" << central->size() << "; mainwindow="
             << m->size();

    // Detach tab
    QPoint globalPressPos = centralFrame->dragPointForWidget(0);
    QTabBar *tabBar = tabBarForFrame(centralFrame);
    QVERIFY(tabBar);
    qDebug() << "Detaching tab from dropArea->size=" << dropArea->size() << "; dropArea=" << dropArea;
    drag(tabBar, globalPressPos, m->geometry().bottomRight() + QPoint(30, 30));

    QVERIFY(centralFrame);
    QCOMPARE(dropArea->count(), 1);
    QCOMPARE(centralFrame->dockWidgetCount(), 0);
    QVERIFY(dropArea->checkSanity());

    delete dock->window();
}

void TestDocks::tst_propagateMinSize()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    QWidget *central = m->centralWidget();
    auto dropArea = qobject_cast<DropArea *>(central);

    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
    auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));
    auto dock3 = createDockWidget(QStringLiteral("dock3"), new QPushButton(QStringLiteral("three")));

    nestDockWidget(dock1, dropArea, nullptr, KDDockWidgets::Location_OnRight);
    nestDockWidget(dock2, dropArea, nullptr, KDDockWidgets::Location_OnRight);
    nestDockWidget(dock3, dropArea, nullptr, KDDockWidgets::Location_OnRight);

    // TODO finish this when the 3 dock widgets have proper sizes
    //QTest::qWait(50000);

}

void TestDocks::tst_dockInternal()
{
    /**
     * Here we dock relative to an existing widget, and not to the drop-area.
     */
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
    QWidget *central = m->centralWidget();
    auto dropArea = qobject_cast<DropArea *>(central);

    Frame *centralWidget = dropArea->multiSplitter()->items()[0]->frame();
    nestDockWidget(dock1, dropArea, centralWidget, KDDockWidgets::Location_OnRight);

    QVERIFY(dock1->width() < dropArea->width() - centralWidget->width());
}

void TestDocks::tst_closeAllDockWidgets()
{
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();
    QWidget *central = m->centralWidget();
    auto dropArea = qobject_cast<DropArea *>(central);
    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
    auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("one")));
    auto dock3 = createDockWidget(QStringLiteral("dock3"), new QPushButton(QStringLiteral("one")));
    auto dock4 = createDockWidget(QStringLiteral("dock4"), new QPushButton(QStringLiteral("one")));
    auto dock5 = createDockWidget(QStringLiteral("dock5"), new QPushButton(QStringLiteral("one")));
    auto dock6 = createDockWidget(QStringLiteral("dock6"), new QPushButton(QStringLiteral("one")));

    QPointer<FloatingWindow> fw = dock3->morphIntoFloatingWindow();

    qDebug() << "Nesting1";

    nestDockWidget(dock4, dropArea, nullptr, KDDockWidgets::Location_OnRight);
    qDebug() << "Nesting2";
    nestDockWidget(dock5, dropArea, nullptr, KDDockWidgets::Location_OnTop);
    qDebug() << "Nesting3 fw size is" << fw->dropArea()->size();
    const int oldFWHeight = fw->height();
    nestDockWidget(dock6, fw->dropArea(), nullptr, KDDockWidgets::Location_OnTop);
    QVERIFY(oldFWHeight <= fw->height());
    qDebug() << "Nesting done";

    QCOMPARE(fw->frames().size(), 2);

    QCOMPARE(dock1->window(), dock1);
    QCOMPARE(dock2->window(), dock2);
    QCOMPARE(dock3->window(), fw.data());
    QCOMPARE(dock4->window(), m.get());
    QCOMPARE(dock5->window(), m.get());
    QCOMPARE(dock6->window(), fw.data());

    qDebug() << "closeAllDockWidgets";
    DockRegistry::self()->closeAllDockWidgets();
    qDebug() << "closeAllDockWidgets done";

    waitForDeleted(fw);
    QVERIFY(!fw);

    QCOMPARE(dock1->window(), dock1);
    QCOMPARE(dock2->window(), dock2);
    QCOMPARE(dock3->window(), dock3);
    QCOMPARE(dock4->window(), dock4);
    QCOMPARE(dock5->window(), dock5);
    QCOMPARE(dock6->window(), dock6);

    QVERIFY(!dock1->isVisible());
    QVERIFY(!dock2->isVisible());
    QVERIFY(!dock3->isVisible());
    QVERIFY(!dock4->isVisible());
    QVERIFY(!dock5->isVisible());
    QVERIFY(!dock6->isVisible());

    delete dock1;
    delete dock2;
    delete dock3;
    delete dock4;
    delete dock5;
    delete dock6;
}

void TestDocks::tst_propagateSizeHonoursMinSize()
{
    // Here we dock a widget on the left size, and on the right side.
    // When docking the second one, the 1st one shouldn't be squeezed too much, as it has a min size

    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();
    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
    auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));
    QWidget *central = m->centralWidget();
    auto dropArea = qobject_cast<DropArea *>(central);
    int min1 = widgetMinLength(dock1, Qt::Vertical);
    int min2 = widgetMinLength(dock2, Qt::Vertical);

    QVERIFY(dock1->width() >= min1);
    QVERIFY(dock2->width() >= min2);

    nestDockWidget(dock1, dropArea, nullptr, KDDockWidgets::Location_OnRight);
    nestDockWidget(dock2, dropArea, nullptr, KDDockWidgets::Location_OnLeft);

    // Calculate again, as the window frame has disappeared
    min1 = widgetMinLength(dock1, Qt::Vertical);
    min2 = widgetMinLength(dock2, Qt::Vertical);

    if (dock1->width() < min1) {
        qDebug() << "\ndock1->width()=" << dock1->width() << "\nmin1=" << min1
                 << "\ndock min sizes=" << dock1->minimumWidth() << dock1->minimumSizeHint().width()
                 << "\nframe1->width()=" << dock1->frame()->width()
                 << "\nframe1->min=" << widgetMinLength(dock1->frame(), Qt::Vertical);
        QVERIFY(false);
    }

    QVERIFY(dock2->width() >= min2);

    // Dock on top of center widget:
    m = createMainWindow();

    dock1 = createDockWidget(QStringLiteral("one"), new QTextEdit());
    m->addDockWidgetAsTab(dock1);
    auto dock3 = createDockWidget(QStringLiteral("three"), new QTextEdit());
    m->addDockWidget(dock3, Location_OnTop);
    QVERIFY(qobject_cast<DropArea*>(m->centralWidget())->checkSanity());

    min1 = widgetMinLength(dock1, Qt::Horizontal);
    QVERIFY(dock1->height() >= min1);
}

void TestDocks::tst_restoreEmpty()
{
    EnsureTopLevelsDeleted e;

    // Create a main window, with a left dock, save it to disk.
    auto m = createMainWindow();
    LayoutSaver saver;
    QVERIFY(saver.saveToDisk());
    saver.restoreFromDisk();
}

void TestDocks::tst_restoreCrash()
{
    EnsureTopLevelsDeleted e;

    {
        // Create a main window, with a left dock, save it to disk.
        auto m = createMainWindow();
        QWidget *central = m->centralWidget();
        auto dropArea = qobject_cast<DropArea *>(central);
        auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
        nestDockWidget(dock1, dropArea, nullptr, KDDockWidgets::Location_OnLeft);
        LayoutSaver saver;
        QVERIFY(saver.saveToDisk());
    }

    // Restore
    qDebug() << Q_FUNC_INFO << "Restoring";
    auto m = createMainWindow();
    QWidget *central = m->centralWidget();
    auto dropArea = qobject_cast<DropArea *>(central);
    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
    QVERIFY(dock1->isFloating());
    QVERIFY(dropArea->checkSanity());

    LayoutSaver saver;
    saver.restoreFromDisk();
    QVERIFY(dropArea->checkSanity());
    QVERIFY(!dock1->isFloating());
}

void TestDocks::tst_addDockWidgetAsTabToDockWidget()
{
    EnsureTopLevelsDeleted e;
    {
        // Dock into a non-morphed floating dock widget
        auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
        auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));

        dock1->addDockWidgetAsTab(dock2);

        QWidget *window1 = dock1->window();
        QWidget *window2 = dock2->window();
        QCOMPARE(window1, window2);
        QCOMPARE(dock1->frame(), dock2->frame());
        QCOMPARE(dock1->frame()->dockWidgetCount(), 2);
        delete dock1;
        delete dock2;
    }
    {
        // Dock into a morphed dock widget
        auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
        dock1->morphIntoFloatingWindow();
        auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));

        dock1->addDockWidgetAsTab(dock2);

        QWidget *window1 = dock1->window();
        QWidget *window2 = dock2->window();
        QCOMPARE(window1, window2);
        QCOMPARE(dock1->frame(), dock2->frame());
        QCOMPARE(dock1->frame()->dockWidgetCount(), 2);
        delete dock1;
        delete dock2;
    }
    {
        // Dock a morphed dock widget into a morphed dock widget
        auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
        dock1->morphIntoFloatingWindow();
        auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));
        dock2->morphIntoFloatingWindow();
        QPointer<QWidget> originalWindow2 = dock2->window();

        dock1->addDockWidgetAsTab(dock2);

        QWidget *window1 = dock1->window();
        QWidget *window2 = dock2->window();
        QCOMPARE(window1, window2);
        QCOMPARE(dock1->frame(), dock2->frame());
        QCOMPARE(dock1->frame()->dockWidgetCount(), 2);
        waitForDeleted(originalWindow2);
        QVERIFY(!originalWindow2);
        delete dock1;
        delete dock2;
    }
    {
        // Dock to an already docked widget
        auto m = createMainWindow();
        QWidget *central = m->centralWidget();
        auto dropArea = qobject_cast<DropArea *>(central);
        auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
        nestDockWidget(dock1, dropArea, nullptr, KDDockWidgets::Location_OnLeft);

        auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));
        dock1->addDockWidgetAsTab(dock2);
        QCOMPARE(dock1->window(), m.get());
        QCOMPARE(dock2->window(), m.get());
        QCOMPARE(dock1->frame(), dock2->frame());
        QCOMPARE(dock1->frame()->dockWidgetCount(), 2);
    }
}

void TestDocks::tst_addDockWidgetToMainWindow()
{
    EnsureTopLevelsDeleted e;
     auto m = createMainWindow();
     auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
     auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));

     m->addDockWidget(dock1, Location_OnRight, nullptr);
     m->addDockWidget(dock2, Location_OnTop, dock1);
     QVERIFY(qobject_cast<DropArea*>(m->centralWidget())->checkSanity());

     QCOMPARE(dock1->window(), m.get());
     QCOMPARE(dock2->window(), m.get());
     QVERIFY(dock1->frame()->y() > dock2->frame()->y());
     QCOMPARE(dock1->frame()->x(), dock2->frame()->x());
}

void TestDocks::tst_addDockWidgetToContainingWindow()
{
    EnsureTopLevelsDeleted e;

    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
    auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));
    auto dock3 = createDockWidget(QStringLiteral("dock3"), new QPushButton(QStringLiteral("three")));

    dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);
    dock1->addDockWidgetToContainingWindow(dock3, Location_OnTop, dock2);

    QCOMPARE(dock1->window(), dock2->window());
    QCOMPARE(dock2->window(), dock3->window());

    QVERIFY(dock3->frame()->y() < dock2->frame()->y());
    QVERIFY(dock1->frame()->x() < dock2->frame()->x());
    QCOMPARE(dock2->frame()->x(), dock3->frame()->x());

    QWidget *window = dock1->window();
    delete dock1;
    delete dock2;
    delete dock3;
    waitForDeleted(window);
}

void TestDocks::tst_addToSmallMainWindow()
{
    // Add a dock widget which is bigger than the main window.
    // Check that the dock widget gets smaller

    EnsureTopLevelsDeleted e;
    qDebug() << "Test 1";
    {
        auto m = createMainWindow();
        auto dock1 = createDockWidget(QStringLiteral("dock1"), new MyWidget2());
        auto dock2 = createDockWidget(QStringLiteral("dock2"), new MyWidget2());
        auto dock3 = createDockWidget(QStringLiteral("dock3"), new MyWidget2());
        auto dock4 = createDockWidget(QStringLiteral("dock4"), new MyWidget2());

        const int mainWindowLength = 400;

        m->resize(mainWindowLength, mainWindowLength);
        dock1->resize(800, 800);
        dock2->resize(800, 800);
        dock3->resize(800, 800);

        // Add as tabbed:
        m->addDockWidgetAsTab(dock1);

        QCOMPARE(m->height(), mainWindowLength);
        QVERIFY(dock1->height() < mainWindowLength);
        QVERIFY(dock1->width() < mainWindowLength);

        //Add in area:
        m->addDockWidget(dock2, Location_OnLeft);
        m->addDockWidget(dock3, Location_OnTop, dock2);
        qDebug() << "Adding bottom one";
        m->addDockWidget(dock4, Location_OnBottom);

        auto dropArea = qobject_cast<DropArea*>(m->centralWidget());

        dropArea->debug_updateItemNamesForGammaray();

        QVERIFY(dropArea->checkSanity());
        QVERIFY(dock2->width() < mainWindowLength);
        QVERIFY(dock3->height() < m->height());
        QVERIFY(dock4->height() < m->height());
    }

    qDebug() << "Test 2";

    {
        auto m = createMainWindow();
        QWidget *central = m->centralWidget();
        auto dropArea = qobject_cast<DropArea *>(central);
        auto dock1 = createDockWidget(QStringLiteral("dock1"), new MyWidget2(QSize(100, 100)));
        auto dock2 = createDockWidget(QStringLiteral("dock2"), new MyWidget2(QSize(100, 100)));
        m->addDockWidgetAsTab(dock1);
        m->resize(osWindowMinWidth(), 200);

        waitForResize(m.get());

        qDebug() << "Adding dock2 to Right. window size=" << m->size();
        QVERIFY(m->width() == osWindowMinWidth());
        m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);
        qDebug() << "Waiting for resize. window size2=" << m->size();
        QVERIFY(waitForResize(m.get()));
        qDebug() << "window size3=" << m->size();

        QVERIFY(dropArea->multiSplitter()->contentsWidth() > osWindowMinWidth());

        QCOMPARE(dropArea->multiSplitter()->contentsWidth(), m->width());
        qDebug() << "New size: " << m->width() << dropArea->multiSplitter()->contentsWidth()
                 << dropArea->minimumSize();
        QVERIFY(qobject_cast<DropArea*>(m->centralWidget())->checkSanity());
    }

    qDebug() << "Test 3";
    {
        auto m = createMainWindow();
        QWidget *central = m->centralWidget();
        auto dropArea = qobject_cast<DropArea *>(central);
        auto dock1 = createDockWidget(QStringLiteral("dock1"), new MyWidget2());
        auto dock2 = createDockWidget(QStringLiteral("dock2"), new MyWidget2());
        m->addDockWidgetAsTab(dock1);
        m->resize(osWindowMinWidth(), 200);
        QTest::qWait(200);
        QVERIFY(m->width() == osWindowMinWidth());

        auto fw = dock2->morphIntoFloatingWindow();
        QVERIFY(fw->isVisible());
        QVERIFY(dropArea->checkSanity(MultiSplitterLayout::AnchorSanity_Intersections));

        dragFloatingWindowTo(fw, dropArea, DropIndicatorOverlayInterface::DropLocation_Right);
        QVERIFY(qobject_cast<DropArea*>(m->centralWidget())->checkSanity());
        delete fw;
    }
}

void TestDocks::tst_fairResizeAfterRemoveWidget()
{
    // 1. Add 3 dock widgets horizontally, remove the middle one, make sure
    // both left and right widgets get a share of the new available space

    EnsureTopLevelsDeleted e;

    DockWidget *dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
    DockWidget *dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));
    DockWidget *dock3 = createDockWidget(QStringLiteral("dock3"), new QPushButton(QStringLiteral("three")));

    dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);
    dock1->addDockWidgetToContainingWindow(dock3, Location_OnRight, dock2);

    auto fw = qobject_cast<FloatingWindow*>(dock1->window());

    QPointer<Frame> frame2= dock2->frame();

    const int oldWidth1 = dock1->frame()->width();
    const int oldWidth2 = dock2->frame()->width();
    const int oldWidth3 = dock3->frame()->width();
    MultiSplitterLayout *layout = fw->dropArea()->multiSplitter();
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->visibleCount(), 3);
    QCOMPARE(layout->placeholderCount(), 0);

    delete dock2;
    QVERIFY(waitForResize(dock1));
    QVERIFY(!frame2);

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 2);
    QCOMPARE(layout->placeholderCount(), 0);

    const int delta1 = (dock1->frame()->width() - oldWidth1);
    const int delta3 = (dock3->frame()->width() - oldWidth3);

    qDebug() << "old1=" << oldWidth1
             << "; old3=" << oldWidth3
             << "; to spread=" << oldWidth2
             << "; Delta1=" << delta1
             << "; Delta3=" << delta3;

    QVERIFY(delta1 > 0);
    QVERIFY(delta3 > 0);
    QVERIFY(qAbs(delta3 - delta1) <= 1); // Both dock1 and dock3 should have increased by the same amount

    QWidget *window = dock1->window();
    window->deleteLater();
    waitForDeleted(window);
}

void TestDocks::tst_notClosable()
{
    EnsureTopLevelsDeleted e;
    {
        auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")), DockWidget::Option_NotClosable);
        auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));

        QVERIFY(dock1->titleBar()->isVisible());

        QWidget *close1 = dock1->titleBar()->closeButton();
        QWidget *close2 = dock2->titleBar()->closeButton();

        QVERIFY(!close1->isEnabled());
        QVERIFY(close2->isEnabled());

        dock1->addDockWidgetAsTab(dock2);


        auto fw = qobject_cast<FloatingWindow*>(dock1->window());
        QVERIFY(fw);
        QWidget *closeFW = fw->titleBar()->closeButton();
        QWidget *closeFrame = fw->frames().at(0)->titleBar()->closeButton();

        QVERIFY(!close1->isVisible());
        QVERIFY(!close2->isVisible());
        QVERIFY(!closeFW->isVisible());

        QVERIFY(closeFrame->isVisible());
        QVERIFY(!closeFrame->isEnabled());

        auto window = dock1->window();
        window->deleteLater();
        waitForDeleted(window);
    }

    {
        // Now dock dock1 into dock1 instead

        auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")), DockWidget::Option_NotClosable);
        auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));

        QVERIFY(dock1->titleBar()->isVisible());

        QWidget *close1 = dock1->titleBar()->closeButton();
        QWidget *close2 = dock2->titleBar()->closeButton();

        QVERIFY(!close1->isEnabled());
        QVERIFY(close2->isEnabled());

        dock2->morphIntoFloatingWindow();
        dock2->addDockWidgetAsTab(dock1);

        auto fw = qobject_cast<FloatingWindow*>(dock1->window());
        QVERIFY(fw);
        QWidget *closeFW = fw->titleBar()->closeButton();
        QWidget *closeFrame = fw->frames().at(0)->titleBar()->closeButton();

        QVERIFY(!close1->isVisible());
        QVERIFY(!close2->isVisible());
        QVERIFY(!closeFW->isVisible());

        QVERIFY(closeFrame->isVisible());
        QVERIFY(!closeFrame->isEnabled());

        auto window = dock2->window();
        window->deleteLater();
        waitForDeleted(window);
    }
}

void TestDocks::tst_maximizeAndRestore()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
    auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));

    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

    QWidget *central = m->centralWidget();
    auto dropArea = qobject_cast<DropArea *>(central);

    QVERIFY(dropArea->checkSanity());

    m->showMaximized();
    waitForResize(m.get());

    QVERIFY(dropArea->checkSanity());
    qDebug() << "About to show normal";
    m->showNormal();
    waitForResize(m.get());

    QVERIFY(dropArea->checkSanity());
}

void TestDocks::tst_propagateResize2()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
    auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnTop);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight, dock1);

    auto dock3 = createDockWidget(QStringLiteral("dock3"), new QPushButton(QStringLiteral("three")));
    auto dock4 = createDockWidget(QStringLiteral("dock4"), new QPushButton(QStringLiteral("four")));

    m->addDockWidget(dock3, KDDockWidgets::Location_OnBottom);
    m->addDockWidget(dock4, KDDockWidgets::Location_OnRight, dock3);

    auto dock5 = createDockWidget(QStringLiteral("dock5"), new QPushButton(QStringLiteral("five")));
    m->addDockWidget(dock5, KDDockWidgets::Location_OnLeft);

    QWidget *central = m->centralWidget();
    auto dropArea = qobject_cast<DropArea *>(central);

    dropArea->checkSanity();
}

std::unique_ptr<MultiSplitterWidget> TestDocks::createMultiSplitterFromSetup(MultiSplitterSetup setup, QHash<QWidget*, Frame*> &frameMap) const
{
    auto widget = std::unique_ptr<MultiSplitterWidget>(new MultiSplitterWidget());
    auto layout = widget->multiSplitter();
    widget->show();
    layout->setContentsSize(setup.size);

    const int count = setup.widgets.size();
    for (int i = 0; i < count; ++i) {
        auto frame = new Frame(widget.get());
        auto dock = new DockWidget(QStringLiteral("foo"));
        dock->setWidget(setup.widgets[i]);
        frame->addWidget(dock);
        frameMap.insert(setup.widgets[i], frame);
        qDebug() << "Min size=" << KDDockWidgets::widgetMinLength(frame, Qt::Horizontal)
                 << KDDockWidgets::widgetMinLength(dock, Qt::Horizontal);
        layout->addWidget(frame, setup.locations[i], frameMap.value(setup.relativeTos[i]));
    }

    for (WidgetResize wr : setup.widgetResizes) {
        qDebug() << "Resizing widget";
        Frame *frame = frameMap.value(wr.w);
        layout->resizeItem(frame, wr.length, wr.orientation);

        if (widgetLength(frame, wr.orientation) != wr.length) {
            qDebug() << widgetLength(wr.w, wr.orientation) <<  wr.length << widgetLength(frame, wr.orientation);
            Q_ASSERT(false);
        }
    }

    return widget;
}

void TestDocks::tst_availableLengthForDrop_data()
{
    QTest::addColumn<MultiSplitterSetup>("multisplitterSetup");
    QTest::addColumn<ExpectedAvailableSizes>("expectedAvailableSizes");

    const int staticAnchorThickness = Anchor::thickness(/*static=*/true);
    const int anchorThickness = Anchor::thickness(/*static=*/false);
    const int multispitterlength = 500;

    QSize minFrameSize;
    {
        // Frame has a bit bigger min size than the widget it hosts, since it has space for a tab bar and titlebar

        Frame frame;
        const int w1MinLength = 100;
        QWidget *w1 = createWidget(w1MinLength);
        auto dock = new DockWidget(QStringLiteral("foo"));
        dock->setWidget(w1);
        frame.addWidget(dock);
        minFrameSize = frame.minimumSizeHint();
    }

    {
        ExpectedAvailableSizes availableSizes;
        MultiSplitterSetup setup;
        setup.size = QSize(multispitterlength, multispitterlength);
        int totalAvailable = multispitterlength - 2*staticAnchorThickness;
        int expected2 = totalAvailable;
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnTop, nullptr, 0, expected2, totalAvailable };
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnLeft, nullptr, 0, expected2, totalAvailable };
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnRight, nullptr, expected2, 0, totalAvailable };
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnBottom, nullptr, expected2, 0, totalAvailable };

        QTest::newRow("empty") << setup << availableSizes;
    }

    {
        ExpectedAvailableSizes availableSizes;
        MultiSplitterSetup setup;
        setup.size = QSize(multispitterlength, multispitterlength);

        const int w1MinLength = 100;
        QWidget *w1 = createWidget(w1MinLength);
        setup.widgets << w1;
        setup.relativeTos << nullptr;
        setup.locations << KDDockWidgets::Location_OnLeft;
        const int totalAvailable_vert = multispitterlength - 2*staticAnchorThickness - anchorThickness - minFrameSize.height();
        const int expected2_vert = totalAvailable_vert;
        const int totalAvailable_horiz = multispitterlength - 2*staticAnchorThickness - anchorThickness - minFrameSize.width();
        const int expected2_horiz = totalAvailable_horiz;

        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnTop, nullptr, 0, expected2_vert, totalAvailable_vert };
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnLeft, nullptr, 0, expected2_horiz, totalAvailable_horiz };
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnRight, nullptr, expected2_horiz, 0, totalAvailable_horiz };
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnBottom, nullptr, expected2_vert, 0, totalAvailable_vert };

        QTest::newRow("one_existing-outter") << setup << availableSizes;
    }

    {
        ExpectedAvailableSizes availableSizes;
        MultiSplitterSetup setup;
        setup.size = QSize(multispitterlength, multispitterlength);

        const int w1MinLength = 100;
        QWidget *w1 = createWidget(w1MinLength);
        setup.widgets << w1;
        setup.relativeTos << nullptr;
        setup.locations << KDDockWidgets::Location_OnLeft;
        const int totalAvailable_vert = multispitterlength - 2*staticAnchorThickness - anchorThickness - minFrameSize.height();
        const int expected2_vert = totalAvailable_vert;
        const int totalAvailable_horiz = multispitterlength - 2*staticAnchorThickness - anchorThickness - minFrameSize.width();
        const int expected2_horiz = totalAvailable_horiz;
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnTop, w1, 0, expected2_vert, totalAvailable_vert };
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnLeft, w1, 0, expected2_horiz, totalAvailable_horiz };
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnRight, w1, expected2_horiz, 0, totalAvailable_horiz };
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnBottom, w1, expected2_vert, 0, totalAvailable_vert };

        QTest::newRow("one_existing-inner") << setup << availableSizes;
    }

    {
        ExpectedAvailableSizes availableSizes;
        MultiSplitterSetup setup;
        setup.size = QSize(multispitterlength, multispitterlength);

        const int w1MinLength = 100;

        QWidget *w1 = createWidget(w1MinLength, QStringLiteral("w1"));
        QWidget *w2 = createWidget(w1MinLength, QStringLiteral("w2"));
        QWidget *w3 = createWidget(w1MinLength, QStringLiteral("w3"));

        setup.widgets << w1 << w2 << w3;
        setup.relativeTos << nullptr << nullptr << nullptr;
        setup.locations << KDDockWidgets::Location_OnBottom << KDDockWidgets::Location_OnBottom << KDDockWidgets::Location_OnBottom;

        setup.widgetResizes << WidgetResize{ 150, Qt::Horizontal, w1 };
        setup.widgetResizes << WidgetResize{ 150, Qt::Horizontal, w2 };

        const int totalAvailable = multispitterlength - 2*staticAnchorThickness - 2*anchorThickness -3*minFrameSize.height() - anchorThickness;
        int expected2 = totalAvailable;
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnTop, nullptr, 0, expected2, totalAvailable };
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnBottom, w3, expected2, 0, totalAvailable };

        int expected1 = 15;
        expected2 = totalAvailable - expected1;
        availableSizes << ExpectedAvailableSize{ KDDockWidgets::Location_OnBottom, w1, expected1, expected2, totalAvailable };

        QTest::newRow("another") << setup << availableSizes;
    }
    //----------------------------------------------------------------------------------------------
}

void TestDocks::tst_availableLengthForDrop()
{
    QFETCH(MultiSplitterSetup, multisplitterSetup);
    QFETCH(ExpectedAvailableSizes, expectedAvailableSizes);
    QHash<QWidget*, Frame*> frameMap;
    auto multisplitterWidget = createMultiSplitterFromSetup(multisplitterSetup, frameMap);
    auto layout = multisplitterWidget->multiSplitter();

    int i = 0;
    for (ExpectedAvailableSize expectedSize : expectedAvailableSizes) {
        expectedSize.relativeTo = expectedSize.relativeTo == nullptr ? multisplitterWidget->parentWidget() : expectedSize.relativeTo;
        auto available = layout->availableLengthForDrop(expectedSize.location, layout->itemForFrame(frameMap.value(expectedSize.relativeTo)));
        // qDebug() << available.length() << "; i=" << i;

        QCOMPARE(available.length(), expectedSize.totalAvailable);
        if (available.side1Length != expectedSize.side1ExpectedSize) {
            layout->dumpDebug();
            qDebug() << "loc=" << expectedSize.location << "; relativeTo=" << expectedSize.relativeTo;
            QCOMPARE(available.side1Length, expectedSize.side1ExpectedSize);
        }

        QCOMPARE(available.side2Length, expectedSize.side2ExpectedSize);
        ++i;
    }
}

void TestDocks::tst_rectForDrop_data()
{
    QTest::addColumn<MultiSplitterSetup>("multisplitterSetup");
    QTest::addColumn<ExpectedRectsForDrop>("expectedRects");

    const int staticAnchorThickness = Anchor::thickness(/*static=*/true);
    const int multispitterlength = 500;

    {
        MultiSplitterSetup setup;
        ExpectedRectsForDrop rects;

        QWidget * widgetToDrop = createWidget(100, QStringLiteral("w1"));
        widgetToDrop->resize(200, 200);
        const int expectedLength = 200; // this 200 will change when the initial length algoritm changes; Maybe just call MultiSplitterLayout::LengthForDrop() directly here
        rects << ExpectedRectForDrop {widgetToDrop, KDDockWidgets::Location_OnLeft, nullptr, QRect(1, 1, expectedLength,  multispitterlength - staticAnchorThickness*2) };
        rects << ExpectedRectForDrop {widgetToDrop, KDDockWidgets::Location_OnTop, nullptr, QRect(1, 1, multispitterlength - staticAnchorThickness*2, expectedLength) };
        rects << ExpectedRectForDrop {widgetToDrop, KDDockWidgets::Location_OnRight, nullptr, QRect(299, 1, expectedLength, multispitterlength - staticAnchorThickness*2) };
        rects << ExpectedRectForDrop {widgetToDrop, KDDockWidgets::Location_OnBottom, nullptr, QRect(1, 299, multispitterlength - staticAnchorThickness*2, expectedLength) };

        setup.size = QSize(multispitterlength, multispitterlength);
        QTest::newRow("empty") << setup << rects;
    }
}

void TestDocks::tst_rectForDrop()
{
    QFETCH(MultiSplitterSetup, multisplitterSetup);
    QFETCH(ExpectedRectsForDrop, expectedRects);
    QHash<QWidget*, Frame*> frameMap;
    auto multisplitterWidget = createMultiSplitterFromSetup(multisplitterSetup, frameMap);
    auto layout = multisplitterWidget->multiSplitter();
    qDebug() << "Created with contentsSize=" << layout->contentsWidth() << layout->contentsHeight()<< multisplitterSetup.size;
    for (ExpectedRectForDrop expected : expectedRects) {
        QRect actualRect = layout->rectForDrop(expected.widgetToDrop, expected.location, layout->itemForFrame(expected.relativeTo));
        layout->dumpDebug();
        QCOMPARE(actualRect, expected.expectedRect);
        expected.widgetToDrop->deleteLater();
    }
}

void TestDocks::tst_crash()
{
    EnsureTopLevelsDeleted e;
    MultiSplitterWidget msw;
    auto layout = msw.multiSplitter();
    layout->setContentsSize(QSize(800, 316));
    layout->parentWidget()->show();

    auto f1 = createFrameWithWidget(QStringLiteral("w1"), &msw, 200);
    auto f2 = createFrameWithWidget(QStringLiteral("w2"), &msw, 100);
    auto f3 = createFrameWithWidget(QStringLiteral("w3"), &msw, 100);

    layout->addWidget(f3, KDDockWidgets::Location_OnBottom);
    layout->addWidget(f2, KDDockWidgets::Location_OnTop, f3);
    layout->addWidget(f1, KDDockWidgets::Location_OnTop, f2);
    layout->resizeItem(f1, 308, Qt::Horizontal);

    auto f4 = createFrameWithWidget(QStringLiteral("w4"), &msw, 105);  // side1 has 108pixels available, which doesn't fit the 5px for the new anchor, + 105 for the widget. Side2 must catter for the 5px.
    layout->addWidget(f4, KDDockWidgets::Location_OnBottom, f1);
}

void TestDocks::tst_setFloatingWhenWasTabbed()
{
    // Tests DockWidget::isTabbed() and DockWidget::setFloating(false|true) when tabbed (it should redock)
    // setFloating(false) for side-by-side is tested in another function

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
    auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));

    // 1. Two floating dock widgets. They are floating, not tabbed.
    QVERIFY(!dock1->isTabbed());
    QVERIFY(!dock2->isTabbed());
    QVERIFY(dock1->isFloating());
    QVERIFY(dock2->isFloating());

    // 2. Dock a floating dock into another floating dock. They're not floating anymore, just tabbed.
    dock1->addDockWidgetAsTab(dock2);
    QVERIFY(dock1->isTabbed());
    QVERIFY(dock2->isTabbed());
    QVERIFY(!dock1->isFloating());
    QVERIFY(!dock2->isFloating());

    // 2.1 Set one of them invisible. // Not much will happen, the tab will be still there, just showing an empty space.
    // Users should use close() instead. Tabwidgets control visibility, they hide the widget when it's not the current tab.
    dock2->setVisible(false);
    QVERIFY(dock2->isTabbed());
    QVERIFY(!dock1->isFloating());
    QCOMPARE(dock2->frame()->m_tabWidget->count(), 2);

    // 3. Set one floating. Now both cease to be tabbed, and both are floating.
    dock1->setFloating(true);
    QVERIFY(dock1->isFloating());
    QVERIFY(dock2->isFloating());
    QVERIFY(!dock1->isTabbed());
    QVERIFY(!dock2->isTabbed());

    // 4. Dock one floating dock into another, side-by-side. They're neither docking or tabbed now.
    dock1->addDockWidgetToContainingWindow(dock2, KDDockWidgets::Location_OnLeft);
    QVERIFY(!dock1->isFloating());
    QVERIFY(!dock2->isFloating());
    QVERIFY(!dock1->isTabbed());
    QVERIFY(!dock2->isTabbed());

    // 5. float one of them, now both are floating, not tabbed anymore.
    dock2->setFloating(true);
    QVERIFY(dock1->isFloating());
    QVERIFY(dock2->isFloating());
    QVERIFY(!dock1->isTabbed());
    QVERIFY(!dock2->isTabbed());

    // 6. With two dock widgets tabbed, detach 1, and reattach it, via DockWidget::setFloating(false)
    m->addDockWidgetAsTab(dock1);
    m->addDockWidgetAsTab(dock2);

    qDebug() << "6.";
    dock2->setFloating(true);
    QVERIFY(dock1->isTabbed());
    QVERIFY(!dock2->isTabbed());
    QVERIFY(!dock1->isFloating());
    QVERIFY(dock2->isFloating());

    LastPosition *pos2 = dock2->lastPosition();
    QCOMPARE(pos2->m_tabIndex, 1);
    QVERIFY(pos2->isValid());
    dock2->setFloating(false);

    QVERIFY(dock1->isTabbed());
    QVERIFY(dock2->isTabbed());
    QVERIFY(!dock1->isFloating());
    QVERIFY(!dock2->isFloating());

    // 7. Call setFloating(true) on an already docked widget
    auto dock3 = createDockWidget(QStringLiteral("dock3"), new QPushButton(QStringLiteral("three")));
    dock3->setFloating(true);
    dock3->setFloating(true);

    // 8. Tab 3 together, detach the middle one, reattach the middle one, it should go to the middle.
    m->addDockWidgetAsTab(dock3);
    dock2->setFloating(true);
    QVERIFY(dock2->isFloating());
    dock2->setFloating(false);
    QVERIFY(!dock2->isFloating());
    QVERIFY(dock2->isTabbed());
    QCOMPARE(dock2->frame()->m_tabWidget->indexOf(dock2), 1);


    // 10. Float dock1, and dock it to main window as tab. This tests Option_AlwaysShowsTabs.
    dock1->setFloating(true);
    dock2->setFloating(true);
    dock3->setFloating(true);

    m->addDockWidgetAsTab(dock1);
    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->isTabbed());
    dock1->setFloating(true);
    dock1->setFloating(false);
    QCOMPARE(dock1->frame()->m_tabWidget->count(), 1);

    // Cleanup
    m->addDockWidgetAsTab(dock2);
    m->addDockWidgetAsTab(dock3);
    m->deleteLater();
    auto window = m.release();
    waitForDeleted(window);
}

void TestDocks::tst_setFloatingWhenSideBySide()
{
    // Tests DockWidget::setFloating(false|true) when side-by-side (it should put it where it was)
    EnsureTopLevelsDeleted e;

    // 1. Create a MainWindow with two docked dock-widgets, then float the first one.
    auto m = createMainWindow();
    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
    auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

    QPointer<Frame> frame1 = dock1->frame();
    dock1->setFloating(true);
    QVERIFY(dock1->isFloating());
    auto fw = qobject_cast<FloatingWindow*>(dock1->window());
    QVERIFY(fw);

    //2. Put it back, via setFloating(). It should return to its place.
    dock1->setFloating(false);

    QVERIFY(!dock1->isFloating());
    QVERIFY(!dock1->isTabbed());

    waitForDeleted(fw);
}

void TestDocks::tst_setVisibleFalseWhenSideBySide()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("one")));
    auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("two")));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

    const QRect oldGeo = dock1->geometry();
    QWidget *oldParent = dock1->parentWidget();

    // 1. Just toggle visibility and check that stuff remained sane
    dock1->setVisible(false);

    QVERIFY(!dock1->isTabbed());
    QVERIFY(!dock1->isFloating());

    dock1->setVisible(true);
    QVERIFY(!dock1->isTabbed());
    QVERIFY(!dock1->isFloating());
    QCOMPARE(dock1->geometry(), oldGeo);
    QCOMPARE(dock1->parentWidget(), oldParent);

    // 2. Check that the parent frame also is hidden now
    dock1->setVisible(false);
    QVERIFY(!dock1->frame()->isVisible());

    // Cleanup
    m->deleteLater();
    auto window = m.release();
    waitForDeleted(window);
}

void TestDocks::tst_simple1()
{
    // Simply create a MainWindow
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
}

void TestDocks::tst_simple2()
{
    // Simply create a MainWindow, and dock something on top
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dw = createDockWidget(QStringLiteral("dw"), new QPushButton(QStringLiteral("dw")));
    m->addDockWidget(dw, KDDockWidgets::Location_OnTop);
}

void TestDocks::tst_refUnrefItem()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("1")));
    auto dock2 = createDockWidget(QStringLiteral("dock2"), new QPushButton(QStringLiteral("2")));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);
    auto dropArea = qobject_cast<DropArea*>(m->centralWidget());
    auto layout = dropArea->multiSplitter();
    QPointer<Frame> frame1 = dock1->frame();
    QPointer<Frame> frame2 = dock2->frame();
    QPointer<Item> item1 = layout->itemForFrame(frame1);
    QPointer<Item> item2 = layout->itemForFrame(frame2);
    QVERIFY(item1.data());
    QVERIFY(item2.data());
    QCOMPARE(item1->refCount(), 2); // 2 - the item and its frame, which can be persistent
    QCOMPARE(item2->refCount(), 2);

    // 1. Delete a dock widget directly. It should delete its frame and also the Item
    delete dock1;
    waitForDeleted(frame1);
    QVERIFY(!frame1.data());
    QVERIFY(!item1.data());

    // 2. Delete dock3, but neither the frame or the item is deleted, since there were two tabs to begin with
    auto dock3 = createDockWidget(QStringLiteral("dock3"), new QPushButton(QStringLiteral("3")));
    QCOMPARE(item2->refCount(), 2);
    dock2->addDockWidgetAsTab(dock3);
    QCOMPARE(item2->refCount(), 3);
    delete dock3;
    QVERIFY(item2.data());
    QCOMPARE(frame2->dockWidgets().size(), 1);

    // 3. Close dock2. frame2 should be deleted, but item2 preserved.
    QCOMPARE(item2->refCount(), 2);
    dock2->close();
    waitForDeleted(frame2);
    QVERIFY(dock2);
    QVERIFY(item2.data());
    QCOMPARE(item2->refCount(), 1);
    QCOMPARE(dock2->lastPosition()->layoutItem(), item2.data());
    delete dock2;

    QVERIFY(!item2.data());
    QCOMPARE(layout->count(), 1);
    layout->dumpDebug();

    // 4. Move a closed dock widget from one mainwindow to another
    // It should delete its old placeholder
    auto dock4 = createDockWidget(QStringLiteral("dock4"), new QPushButton(QStringLiteral("4")));
    m->addDockWidget(dock4, KDDockWidgets::Location_OnLeft);

    QPointer<Frame> frame4 = dock4->frame();
    QPointer<Item> item4 = layout->itemForFrame(frame4);
    dock4->close();
    waitForDeleted(frame4);
    QCOMPARE(item4->refCount(), 1);
    QVERIFY(item4->isPlaceholder());

    auto m2 = createMainWindow();
    m2->addDockWidget(dock4, KDDockWidgets::Location_OnLeft);
    QVERIFY(!item4.data());

}

void TestDocks::tst_addAndReadd()
{
    EnsureTopLevelsDeleted e;

    // 1. This just tests some crash I got.
    // Make a dock widget float and immediately reattach it
    auto m = createMainWindow();
    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("1")));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->setFloating(true);
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->frame()->titleBar()->makeWindow();
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->frame()->titleBar()->makeWindow();

    auto fw = qobject_cast<FloatingWindow*>(dock1->window());
    QVERIFY(fw);
    auto dropArea = qobject_cast<DropArea*>(m->centralWidget());
    dragFloatingWindowTo(fw, dropArea, DropIndicatorOverlayInterface::DropLocation_OutterRight);
    dock1->frame()->titleBar()->makeWindow();

    //Cleanup
    delete dock1;
    waitForDeleted(fw);
}

void TestDocks::tst_placeholderCount()
{
    EnsureTopLevelsDeleted e;
    // Tests MultiSplitterLayout::count(),visibleCount() and placeholdercount()

    // 1. MainWindow with just the initial frame.
    auto m = createMainWindow();
    auto dock1 = createDockWidget(QStringLiteral("1"), new QPushButton(QStringLiteral("1")));
    auto dock2 = createDockWidget(QStringLiteral("2"), new QPushButton(QStringLiteral("2")));
    auto dropArea = qobject_cast<DropArea*>(m->centralWidget());
    auto layout = dropArea->multiSplitter();

    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->visibleCount(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // 2. MainWindow with central frame and left widget
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 2);
    QCOMPARE(layout->placeholderCount(), 0);

    // 3. Add another dockwidget, this time tabbed in the center. It won't increase count, as it reuses an existing frame.
    m->addDockWidgetAsTab(dock2);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 2);
    QCOMPARE(layout->placeholderCount(), 0);

    // 4. Float dock1. It should create a placeholder
    dock1->setFloating(true);

    auto fw = qobject_cast<FloatingWindow*>(dock1->window());
    layout->dumpDebug();

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 1);
    QCOMPARE(layout->placeholderCount(), 1);

    // 5. Re-dock dock1. It should reuse the placeholder
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 2);
    QCOMPARE(layout->placeholderCount(), 0);

    // 6. Again
    dock1->setFloating(true);
    fw = qobject_cast<FloatingWindow*>(dock1->window());
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 2);
    QCOMPARE(layout->placeholderCount(), 0);

    waitForDeleted(fw);
}

void TestDocks::tst_availableLengthForOrientation()
{
    EnsureTopLevelsDeleted e;

    // 1. Test a completely empty window, it's available space is its size minus the static separators thickness
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    auto dropArea = qobject_cast<DropArea*>(m->centralWidget());
    MultiSplitterLayout *layout = dropArea->multiSplitter();

    int availableWidth = layout->availableLengthForOrientation(Qt::Vertical);
    int availableHeight = layout->availableLengthForOrientation(Qt::Horizontal);
    QCOMPARE(availableWidth, layout->contentsWidth() - 2 * Anchor::thickness(true));
    QCOMPARE(availableHeight, layout->contentsHeight() - 2 *Anchor::thickness(true));

    //2. Now do the same, but we have some widget docked

    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QPushButton(QStringLiteral("1")));
    m->addDockWidget(dock1, Location_OnLeft);

    const int dock1MinWidth = widgetMinLength(dock1->frame(), Qt::Vertical);
    const int dock1MinHeight = widgetMinLength(dock1->frame(), Qt::Horizontal);

    availableWidth = layout->availableLengthForOrientation(Qt::Vertical);
    availableHeight = layout->availableLengthForOrientation(Qt::Horizontal);
    QCOMPARE(availableWidth, layout->contentsWidth() - 2 * Anchor::thickness(true) - Anchor::thickness(false) - dock1MinWidth);
    QCOMPARE(availableHeight, layout->contentsHeight() - 2 *Anchor::thickness(true) - Anchor::thickness(false) -  dock1MinHeight);
}

void TestDocks::tst_setAstCurrentTab()
{
    EnsureTopLevelsDeleted e;

    // Tests DockWidget::setAsCurrentTab() and DockWidget::isCurrentTab()
    // 1. a single dock widget is current, by definition
    auto dock1 = createDockWidget(QStringLiteral("1"), new QPushButton(QStringLiteral("1")));
    QVERIFY(dock1->isCurrentTab());

    // 2. Tab dock2 to the group, dock2 is current now
    auto dock2 = createDockWidget(QStringLiteral("2"), new QPushButton(QStringLiteral("2")));
    dock1->addDockWidgetAsTab(dock2);
    QVERIFY(!dock1->isCurrentTab());
    QVERIFY(dock2->isCurrentTab());

    // 3. Set dock1 as current
    dock1->setAsCurrentTab();
    QVERIFY(dock1->isCurrentTab());
    QVERIFY(!dock2->isCurrentTab());

    auto fw = qobject_cast<FloatingWindow*>(dock1->window());
    QVERIFY(fw);

    delete dock1; delete dock2;
    waitForDeleted(fw);
}

void TestDocks::tst_closeShowWhenNoCentralFrame()
{
    EnsureTopLevelsDeleted e;
    // Tests a crash I got when hidding and showing and no central frame

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    QPointer<DockWidget> dock1 = createDockWidget(QStringLiteral("1"), new QPushButton(QStringLiteral("1")));
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->close();
    QVERIFY(!dock1->frame());
    QVERIFY(!waitForDeleted(dock1)); // It was being deleted due to a bug
    QVERIFY(dock1);
    dock1->show();
}

void TestDocks::tst_placeholderDisappearsOnReadd()
{
    // This tests that addMultiSplitter also updates refcount of placeholders

    // 1. Detach a widget and dock it on the opposite side. Placeholder
    // should have been deleted and anchors properly positioned

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    auto dropArea = qobject_cast<DropArea*>(m->centralWidget());
    MultiSplitterLayout *layout = dropArea->multiSplitter();

    QPointer<DockWidget> dock1 = createDockWidget(QStringLiteral("1"), new QPushButton(QStringLiteral("1")));
    m->addDockWidget(dock1, Location_OnLeft);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->dumpDebug();
    dock1->setFloating(true);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 1);

    dock1->morphIntoFloatingWindow();
    auto fw = qobject_cast<FloatingWindow*>(dock1->window());
    layout->addMultiSplitter(fw->dropArea(), Location_OnRight );
    layout->dumpDebug();
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->count(), 1);

    layout->dumpDebug();
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // The dock1 should occupy the entire width
    QCOMPARE(dock1->frame()->width(), layout->contentsWidth() - 2 * Anchor::thickness(true));

    QVERIFY(waitForDeleted(fw));
}

void TestDocks::tst_placeholdersAreRemovedPropertly()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    auto dropArea = qobject_cast<DropArea*>(m->centralWidget());
    MultiSplitterLayout *layout = dropArea->multiSplitter();
    QPointer<DockWidget> dock1 = createDockWidget(QStringLiteral("1"), new QPushButton(QStringLiteral("1")));
    QPointer<DockWidget> dock2 = createDockWidget(QStringLiteral("1"), new QPushButton(QStringLiteral("1")));
    m->addDockWidget(dock1, Location_OnLeft);
    Item *item = layout->items().constFirst();
    m->addDockWidget(dock2, Location_OnRight);
    QVERIFY(!item->isPlaceholder());
    dock1->setFloating(true);
    QVERIFY(item->isPlaceholder());

    QCOMPARE(layout->anchors().size(), 5);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    layout->removeItem(item);

    QCOMPARE(layout->anchors().size(), 4);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // 2. Recreate the placeholder. This time delete the dock widget to see if placeholder is deleted too.
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->setFloating(true);
    QPointer<QWidget> window1 = dock1->window();
    delete dock1;
    QCOMPARE(layout->anchors().size(), 4);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // Cleanup
    waitForDeleted(window1);
}

void TestDocks::tst_embeddedMainWindow()
{
    // Tests a MainWindow which isn't a top-level window, but is embedded in another window
    EmbeddedWindow *window = createEmbeddedMainWindow(QSize(800, 800));

    auto dock1 = createDockWidget(QStringLiteral("1"), new QPushButton(QStringLiteral("1")));
    window->mainWindow->addDockWidget(dock1, Location_OnTop);
    dock1->setFloating(true);
    auto dropArea = qobject_cast<DropArea*>(window->mainWindow->centralWidget());
    auto fw = qobject_cast<FloatingWindow*>(dock1->window());
    dragFloatingWindowTo(fw, dropArea, DropIndicatorOverlayInterface::DropLocation_OutterLeft);

    auto layout = dropArea->multiSplitter();
    QVERIFY(waitForDeleted(fw));
    QCOMPARE(layout->count(), 2); // 2, as it has the central frame
    QCOMPARE(layout->visibleCount(), 2);

}

// QTest::qWait(50000)

QTEST_MAIN(KDDockWidgets::TestDocks)
#include "tst_docks.moc"


