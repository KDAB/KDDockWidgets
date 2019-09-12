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
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

#include "DockWidgetBase.h"
#include "MainWindow.h"
#include "FloatingWindow_p.h"
#include "DockRegistry_p.h"
#include "Frame_p.h"
#include "FrameWidget_p.h"
#include "DropArea_p.h"
#include "TitleBar_p.h"
#include "WindowBeingDragged_p.h"
#include "Utils_p.h"
#include "LayoutSaver.h"
#include "LayoutSaver_p.h"
#include "TabWidget_p.h"
#include "multisplitter/MultiSplitter_p.h"
#include "LastPosition_p.h"
#include "utils.h"
#include "FrameworkWidgetFactory.h"
#include "DropAreaWithCentralFrame_p.h"

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
#include <QToolButton>

#ifdef Q_OS_WIN
# include <Windows.h>
#endif

#define WAIT QTest::qWait(5000000);

using namespace KDDockWidgets;
using namespace KDDockWidgets::Tests;

extern quintptr Q_CORE_EXPORT qtHookData[];

static QString s_expectedWarning;

static int staticAnchorLength()
{
    return Config::self().separatorThickness(true);
}

static int anchorLength()
{
    return Config::self().separatorThickness(false);
}

struct SetExpectedWarning
{
    explicit SetExpectedWarning(const QString &s)
    {
        s_expectedWarning = s;
    }

    ~SetExpectedWarning()
    {
        s_expectedWarning.clear();
    }
    Q_DISABLE_COPY(SetExpectedWarning)
};

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

static int osWindowMinWidth()
{
#ifdef Q_OS_WIN
    return GetSystemMetrics(SM_CXMIN);
#else
    return 140; // Some random value for our windows. It's only important on Windows
#endif
}
/*
static int osWindowMinHeight()
{
#ifdef Q_OS_WIN
    return GetSystemMetrics(SM_CYMIN);
#else
    return 100; // Some random value for our windows. It's only important on Windows
#endif
}*/

namespace KDDockWidgets {

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
    EventFilter(QEvent::Type type) : m_type(type) {}
    bool eventFilter(QObject *, QEvent *e)
    {
        if (e->type() == m_type)
            m_got = true;

        return false;
    }

    const QEvent::Type m_type;
    bool m_got = false;
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
    if (shouldBlacklistWarning(msg, QLatin1String(context.category)))
        return;

    s_original(t, context, msg);
    if (t == QtWarningMsg) {

        if (!s_expectedWarning.isEmpty() && msg.contains(s_expectedWarning))
            return;

        if (!isGammaray() && !qEnvironmentVariableIsSet("NO_FATAL"))
            qFatal("Got a warning, category=%s", context.category);
    }
}

struct EnsureTopLevelsDeleted
{
    EnsureTopLevelsDeleted()
        : m_initialNumWindows(topLevels().size())
        , m_originalFlags(Config::self().flags())
        , m_originalStaticAnchorThickness(Config::self().separatorThickness(true))
        , m_originalAnchorThickness(Config::self().separatorThickness(false))
    {
    }

    ~EnsureTopLevelsDeleted()
    {
        if (topLevels().size() != m_initialNumWindows) {
            qWarning() << "There's still top-level widgets present!" << qApp->topLevelWidgets() << m_initialNumWindows;
        }

        // Other cleanup, since we use this class everywhere
        Config::self().setDockWidgetFactoryFunc(nullptr);
        Config::self().setFlags(m_originalFlags);
        Config::self().setSeparatorThickness(m_originalStaticAnchorThickness, true);
        Config::self().setSeparatorThickness(m_originalAnchorThickness, false);
    }

    QWidgetList topLevels() const
    {
        QWidgetList result;

        for (QWidget *w : qApp->topLevelWidgets()) {
            if (!qobject_cast<QToolButton*>(w))
                result << w;
        }

        return result;
    }

    const int m_initialNumWindows;
    const Config::Flags m_originalFlags;
    const int m_originalStaticAnchorThickness;
    const int m_originalAnchorThickness;
};

class TestDocks : public QObject
{
    Q_OBJECT
public Q_SLOTS:
    void initTestCase()
    {
        qputenv("KDDOCKWIDGETS_SHOW_DEBUG_WINDOW", "");
        qApp->setOrganizationName("KDAB");
        qApp->setApplicationName("dockwidgets-unit-tests");
        s_original = qInstallMessageHandler(fatalWarningsMessageHandler);
    }
public:
    static void nestDockWidget(DockWidgetBase *dock, DropArea *dropArea, Frame *relativeTo, KDDockWidgets::Location location);

private Q_SLOTS:
    void tst_simple1();
    void tst_simple2();
    void tst_shutdown();
    void tst_mainWindowAlwaysHasCentralWidget();
    void tst_createFloatingWindow();
    void tst_dock2FloatingWidgetsTabbed();
    void tst_close();
    void tst_preventClose();
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

    void tst_clear();
    void tst_constraintsAfterPlaceholder();
    void tst_rectForDrop_data();
    void tst_rectForDrop();
    void tst_rectForDropMath_data();
    void tst_rectForDropMath();
    void tst_crash(); // tests some crash I got
    void tst_crash2_data();
    void tst_crash2();
    void tst_setFloatingWhenWasTabbed();
    void tst_setFloatingWhenSideBySide();
    void tst_setFloatingAfterDraggedFromTabToSideBySide();
    void tst_setFloatingAFrameWithTabs();
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
    void tst_toggleMiddleDockCrash(); // tests some crash I got
    void tst_28NestedWidgets();
    void tst_28NestedWidgets_data();
    void tst_invalidPlaceholderPosition_data();
    void tst_invalidPlaceholderPosition();
    void tst_invalidAnchorGroup();
    void tst_resizeViaAnchorsAfterPlaceholderCreation();
    void tst_negativeAnchorPosition();
    void tst_negativeAnchorPosition2();
    void tst_negativeAnchorPosition3();
    void tst_negativeAnchorPosition4();
    void tst_negativeAnchorPosition5();
    void tst_negativeAnchorPosition6();
    void tst_negativeAnchorPosition7();
    void tst_negativeAnchorPositionWhenEmbedded_data();
    void tst_negativeAnchorPositionWhenEmbedded();
    void tst_availableSizeWithPlaceholders();
    void tst_stealFrame();
    void tst_addAsPlaceholder();
    void tst_removeItem();
    void tst_startHidden();
    void tst_startClosed();
    void tst_sizeConstraintWarning();
    void tst_invalidLayoutAfterRestore();
    void tst_samePositionAfterHideRestore();
    void tst_anchorFollowingItselfAssert();
    void tst_positionWhenShown();
    void tst_restoreEmpty();
    void tst_restoreSimple();
    void tst_restoreNestedAndTabbed();
    void tst_restoreCentralFrame();
    void tst_restoreCrash();
    void tst_restoreTwice();
    void tst_restoreSideBySide();
    void tst_restoreWithPlaceholder();
    void tst_restoreWithNonClosableWidget();
    void tst_restoreAfterResize();
    void tst_marginsAfterRestore();
    void tst_restoreEmbeddedMainWindow();
    void tst_restoreWithDockFactory();

    void tst_resizeWindow_data();
    void tst_resizeWindow();
    void tst_resizeWindow2();
    void tst_rectForDropCrash();

    void tst_tabBarWithHiddenTitleBar_data();
    void tst_tabBarWithHiddenTitleBar();
    void tst_dragByTabBar_data();
    void tst_dragByTabBar();

    void tst_addToHiddenMainWindow();
    void tst_minSizeChanges();
    void tst_complex();
    void tst_titlebar_getter();
    void tst_staticAnchorThickness_data();
    void tst_staticAnchorThickness();

private:
    std::unique_ptr<MultiSplitter> createMultiSplitterFromSetup(MultiSplitterSetup setup, QHash<QWidget *, Frame *> &frameMap) const;
};
}

static EmbeddedWindow *createEmbeddedMainWindow(QSize sz)
{
    static int count = 0;
    count++;
    // Tests a MainWindow which isn't a top-level window, but is embedded in another window
    auto mainwindow = new MainWindow(QString("MyMainWindow%1").arg(count));

    auto window = new EmbeddedWindow(mainwindow);
    auto lay = new QVBoxLayout(window);
    lay->setContentsMargins(100, 100, 100, 100);
    lay->addWidget(mainwindow);
    window->show();
    window->resize(sz);
    return window;
}

namespace {

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

    void setMinSize(QSize s)
    {
        m_minSz = s;
        updateGeometry();
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

bool waitForEvent(QWidget *w, QEvent::Type type, int timeout = 2000)
{
    EventFilter filter(type);
    w->installEventFilter(&filter);
    QTime time;
    time.start();

    while (!filter.m_got && time.elapsed() < timeout) {
        qApp->processEvents();
        QTest::qWait(50);
    }

    return filter.m_got;
}

bool waitForResize(QWidget *w, int timeout = 2000)
{
    return waitForEvent(w, QEvent::Resize, timeout);
}

Frame* createFrameWithWidget(const QString &name, MultiSplitter *parent, int minLength = -1)
{
    QWidget *w = createWidget(minLength, name);
    auto dw = new DockWidget(name);
    dw->setWidget(w);
    auto frame = Config::self().frameWorkWidgetFactory()->createFrame(parent);
    frame->addWidget(dw);
    return frame;
}

FloatingWindow *createFloatingWindow()
{
    static int count = 0;
    count++;
    auto dock = createDockWidget(QString("docfw %1").arg(count), Qt::green);
    return dock->morphIntoFloatingWindow();
}

void TestDocks::tst_createFloatingWindow()
{
    EnsureTopLevelsDeleted e;

    auto dock = createDockWidget("doc1", Qt::green);
    QVERIFY(dock);
    QVERIFY(dock->isFloating());

    QCOMPARE(dock->uniqueName(), QLatin1String("doc1")); // 1.0 objectName() is inherited

    QPointer<FloatingWindow> window = qobject_cast<FloatingWindow *>(dock->window());
    QVERIFY(window); // 1.1 DockWidget creates a FloatingWindow and is reparented
    QVERIFY(window->dropArea()->checkSanity());
    dock->deleteLater();
    QVERIFY(waitForDeleted(dock));
    QVERIFY(waitForDeleted(window)); // 1.2 Floating Window is destroyed when DockWidget is destroyed
    QVERIFY(!window);
}

void TestDocks::nestDockWidget(DockWidgetBase *dock, DropArea *dropArea, Frame *relativeTo, KDDockWidgets::Location location)
{
    auto frame = Config::self().frameWorkWidgetFactory()->createFrame();
    frame->addWidget(dock);
    dock->frame()->setObjectName(dock->objectName());

    qDebug() << "Adding widget" << frame
             << "; min width=" << widgetMinLength(frame, Qt::Vertical)
             << "; min height=" << widgetMinLength(frame, Qt::Horizontal);

    dropArea->multiSplitterLayout()->addWidget(frame, location, relativeTo);
    QVERIFY(dropArea->checkSanity());
    qDebug() << "Size after adding: " << frame->size();
}

DockWidgetBase *createAndNestDockWidget(DropArea *dropArea, Frame *relativeTo, KDDockWidgets::Location location)
{
    static int count = 0;
    count++;
    const QString name = QString("dock%1").arg(count);
    auto dock = createDockWidget(name, Qt::red);
    dock->setObjectName(name);
    TestDocks::nestDockWidget(dock, dropArea, relativeTo, location);
    dropArea->checkSanity();
    return dock;
}

std::unique_ptr<MainWindow> createSimpleNestedMainWindow(DockWidgetBase * *centralDock, DockWidgetBase * *leftDock, DockWidgetBase * *rightDock)
{
    auto window = createMainWindow({900, 500});
    *centralDock = createDockWidget("centralDock", Qt::green);
    window->addDockWidgetAsTab(*centralDock);
    auto dropArea = window->dropArea();

    *leftDock = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnLeft);
    *rightDock = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnRight);
    return window;
}

void TestDocks::tst_dock2FloatingWidgetsTabbed()
{
    EnsureTopLevelsDeleted e;

    if (KDDockWidgets::usesNativeTitleBar())
        return; // Unit-tests can't drag via tab, yet

    auto dock1 = createDockWidget("doc1", Qt::green);
    auto fw1 = dock1->floatingWindow();
    fw1->setGeometry(500, 500, 400, 400);
    QVERIFY(dock1);
    QPointer<Frame> frame1 = dock1->frame();

    auto titlebar1 = fw1->titleBar();
    auto dock2 = createDockWidget("doc2", Qt::red);

    QVERIFY(dock1->isFloating());
    QVERIFY(dock2->isFloating());

    drag(titlebar1, titlebar1->mapToGlobal(QPoint(5, 5)), dock2->window()->geometry().center(), ButtonAction_Press);

    // It morphed into a FloatingWindow
    QPointer<Frame> frame2 = dock2->frame();
    if (!dock2->floatingWindow()) {
        qWarning() << "dock2->floatingWindow()=" << dock2->floatingWindow();
        QVERIFY(false);
    }
    QVERIFY(frame2);
    QCOMPARE(frame2->dockWidgetCount(), 1);

    releaseOn(dock2->window()->geometry().center(), titlebar1);
    QCOMPARE(frame2->dockWidgetCount(), 2); // 2.2 Frame has 2 widgets when one is dropped

    QVERIFY(waitForDeleted(frame1));

    // 2.3 Detach tab1 to empty space
    QPoint globalPressPos = dragPointForWidget(frame2.data(), 0);
    QTabBar *tabBar = static_cast<FrameWidget*>(frame2.data())->tabBar();
    QVERIFY(tabBar);
    drag(tabBar, globalPressPos, frame2->window()->geometry().bottomRight() + QPoint(10, 10));

    QVERIFY(frame2->dockWidgetCount() == 1);
    QVERIFY(qobject_cast<FloatingWindow *>(dock1->window()));

    // 2.4 Drag the first dock over the second
    frame1 = dock1->frame();
    frame2 = dock2->frame();
    fw1 = dock1->floatingWindow();
    globalPressPos = fw1->titleBar()->mapToGlobal(QPoint(100,5));
    drag(fw1->titleBar(), globalPressPos, dock2->window()->geometry().center());

    QCOMPARE(frame2->dockWidgetCount(), 2);

    // 2.5 Detach and drop to the same place, should tab again
    globalPressPos = dragPointForWidget(frame2.data(), 0);
    tabBar = static_cast<FrameWidget*>(frame2.data())->tabBar();

    drag(tabBar, globalPressPos, dock2->window()->geometry().center());
    QCOMPARE(frame2->dockWidgetCount(), 2);

    // 2.6 Drag the tabbed group over a 3rd floating window
    auto dock3 = createDockWidget("doc3", Qt::black);
    QTest::qWait(1000); // Test is flaky otherwise

    auto fw2 = dock2->floatingWindow();
    drag(fw2->titleBar(), frame2->mapToGlobal(QPoint(10, 10)), dock3->window()->geometry().center());

    QVERIFY(waitForDeleted(frame1));
    QVERIFY(waitForDeleted(frame2));
    QVERIFY(dock3->frame());
    QCOMPARE(dock3->frame()->dockWidgetCount(), 3);

    auto fw3 = qobject_cast<FloatingWindow *>(dock3->window());
    QVERIFY(fw3);
    QVERIFY(fw3->dropArea()->checkSanity());

    // 2.7 Drop the window into a MainWindow
    {
        MainWindow m("MyMainWindow_tst_dock2FloatingWidgetsTabbed");
        m.show();
        m.setGeometry(500, 300, 300, 300);
        QVERIFY(!dock3->isFloating());
        auto fw3 = qobject_cast<FloatingWindow *>(dock3->window());
        drag(fw3->titleBar(), dock3->window()->mapToGlobal(QPoint(10, 10)), m.geometry().center());
        QVERIFY(!dock3->isFloating());
        QVERIFY(qobject_cast<MainWindow *>(dock3->window()) == &m);
        QCOMPARE(dock3->frame()->dockWidgetCount(), 3);
        QVERIFY(m.dropArea()->checkSanity());

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
    auto dock1 = createDockWidget("doc1", Qt::green);
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
    auto fw1 = dock1->floatingWindow();
    dock1->hide();
    QVERIFY(waitForDeleted(fw1));
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
    DockWidgetBase *centralDock;
    DockWidgetBase *leftDock;
    DockWidgetBase *rightDock;

    auto mainwindow = createSimpleNestedMainWindow(&centralDock, &leftDock, &rightDock);
    auto da = mainwindow->dropArea();

    QVERIFY(da->checkSanity());
    QCOMPARE(leftDock->frame()->x(), staticAnchorLength()); // 1 = static anchor thickness
    QCOMPARE(centralDock->frame()->x(), leftDock->frame()->geometry().right() + anchorLength() + 1);
    QCOMPARE(rightDock->frame()->x(), centralDock->frame()->geometry().right() + anchorLength() + 1);
    leftDock->close();
    QTest::qWait(250); // TODO: wait for some signal
    QCOMPARE(centralDock->frame()->x(), staticAnchorLength());
    QCOMPARE(rightDock->frame()->x(), centralDock->frame()->geometry().right() + anchorLength() + 1);

    rightDock->close();
    QTest::qWait(250); // TODO: wait for some signal
    auto lay = mainwindow->centralWidget()->layout();
    QMargins margins = lay->contentsMargins();
    QCOMPARE(centralDock->frame()->width(), mainwindow->width() - staticAnchorLength()*2 - margins.left() - margins.right());
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
        dock1 = createDockWidget("hello", Qt::green);
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
        dock1 = createDockWidget("hello", Qt::green);
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
        dock1 = createDockWidget("hello", Qt::green);
        m->addDockWidget(dock1, Location_OnLeft);

        // 2.2 Closing should not close the main window
        dock1->frame()->titleBar()->onCloseClicked();
        QVERIFY(mainWindowPtr.data());
        QVERIFY(mainWindowPtr->isVisible());
        delete dock1;
    }
}

void TestDocks::tst_preventClose()
{
    EnsureTopLevelsDeleted e;

    auto nonClosableWidget = new NonClosableWidget();
    auto dock1 = new DockWidget("1");
    dock1->setWidget(nonClosableWidget);

    // 1. Test a floating dock widget
    dock1->resize(100, 100);
    dock1->show();
    QVERIFY(dock1->isVisible());
    dock1->close();
    QVERIFY(dock1->isVisible());

    // 2. Morph it into a FlatingWindow
    dock1->morphIntoFloatingWindow();
    dock1->close();
    QVERIFY(dock1->isVisible());
    dock1->frame()->titleBar()->onCloseClicked();
    QVERIFY(dock1->isVisible());
    auto fw = dock1->floatingWindow();
    fw->close();
    QVERIFY(dock1->isVisible());

    dock1->deleteLater();
    QVERIFY(waitForDeleted(dock1));
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

    DockWidgetBase *centralDock;
    DockWidgetBase *leftDock;
    DockWidgetBase *rightDock;
    auto mainwindow = createSimpleNestedMainWindow(&centralDock, &leftDock, &rightDock);
    auto dropArea = mainwindow->dropArea();
    QVERIFY(dropArea->checkSanity());

    auto nonStaticAnchors = dropArea->nonStaticAnchors();
    AnchorGroup staticAnchors = dropArea->multiSplitterLayout()->staticAnchorGroup();

    QVERIFY(staticAnchors.isValid());
    QCOMPARE(nonStaticAnchors.size(), 2);

    for (Anchor *anchor : nonStaticAnchors) {
        QCOMPARE(anchor->orientation(), Qt::Vertical);
        QCOMPARE(anchor->from(), staticAnchors.top);
        QCOMPARE(anchor->to(), staticAnchors.bottom);
    }

    qDebug() << "Adding the bottom one";
    QVERIFY(dropArea->checkSanity());
    DockWidgetBase *bottom = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnBottom);
    QVERIFY(dropArea->checkSanity());
    nonStaticAnchors = dropArea->nonStaticAnchors();
    auto horizAnchors = dropArea->multiSplitterLayout()->anchors(Qt::Horizontal);
    auto vertAnchors = dropArea->multiSplitterLayout()->anchors(Qt::Vertical);
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
    QVERIFY(qobject_cast<FloatingWindow *>(window->floatingWindow()));
    QVERIFY(follower->isFollowing());

    nonStaticAnchors = dropArea->nonStaticAnchors();
    horizAnchors = dropArea->multiSplitterLayout()->anchors(Qt::Horizontal, false, false);
    vertAnchors = dropArea->multiSplitterLayout()->anchors(Qt::Vertical, false, false);
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
    delete window->floatingWindow();

    {
        // Test a case where the to wasn't correct
        auto m = createMainWindow({400, 400});
        DropArea *dropArea = m->dropArea();

        auto dock = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnRight);
        createAndNestDockWidget(dropArea, dock->frame(), KDDockWidgets::Location_OnBottom);

        const auto anchors = dropArea->nonStaticAnchors();
        QCOMPARE(anchors.size(), 2);
        QCOMPARE(anchors[1]->orientation(), Qt::Horizontal);
        QCOMPARE(anchors[1]->to()->objectName(), QString("right"));
        QCOMPARE(anchors[1]->from(), anchors[0]);
    }
}

void TestDocks::tst_dockWindowWithTwoSideBySideFramesIntoCenter()
{
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();
    auto fw = createFloatingWindow();
    auto dock2 = createDockWidget("doc2", Qt::red);
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
    fw->setObjectName("fw1");
    auto dock2 = createDockWidget("doc2", Qt::red);
    nestDockWidget(dock2, fw->dropArea(), nullptr, KDDockWidgets::Location_OnLeft);
    QCOMPARE(fw->frames().size(), 2);

    auto fw2 = createFloatingWindow();
    fw2->setObjectName("fw2");
    fw2->move(fw->x() + fw->width() + 100, fw->y());

    QVERIFY(fw2->dropArea()->checkSanity());
    dragFloatingWindowTo(fw, fw2->dropArea(), DropIndicatorOverlayInterface::DropLocation_Left);
    QCOMPARE(fw2->frames().size(), 3);

    auto anchors = fw2->dropArea()->nonStaticAnchors();
    QCOMPARE(anchors.size(), 2);
    QCOMPARE(anchors[0]->orientation(), Qt::Vertical);
    QCOMPARE(anchors[1]->orientation(), Qt::Vertical);

    QCOMPARE(anchors[0]->from()->objectName(), QString("top"));
    QCOMPARE(anchors[0]->to()->objectName(), QString("bottom"));
    QCOMPARE(anchors[1]->from()->objectName(), QString("top"));
    QCOMPARE(anchors[1]->to()->objectName(), QString("bottom"));

    QVERIFY(anchors[1]->position() < anchors[0]->position());
    fw2->dropArea()->debug_updateItemNamesForGammaray();
    QVERIFY(fw2->dropArea()->checkSanity());

    ///Cleanup
    fw2->deleteLater();
    waitForDeleted(fw2);
}

void TestDocks::tst_dockWindowWithTwoSideBySideFramesIntoRight()
{
    EnsureTopLevelsDeleted e;

    auto fw = createFloatingWindow();
    auto dock2 = createDockWidget("doc2", Qt::red);
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

    QCOMPARE(anchors[0]->from()->objectName(), QString("top"));
    QCOMPARE(anchors[0]->to()->objectName(), QString("bottom"));
    QCOMPARE(anchors[1]->from(), anchors[0]);
    QCOMPARE(anchors[1]->to()->objectName(), QString("right"));

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
        auto dock2 = createDockWidget("doc2", Qt::red);
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
        auto dock2 = createDockWidget("doc2", Qt::red);
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
    auto dock = createDockWidget("doc1", Qt::green);

    auto m = createMainWindow();
    m->show();
    QVERIFY(QTest::qWaitForWindowActive(m->windowHandle()));
    dock->deleteLater();
    QVERIFY(waitForDeleted(dock));
}

void TestDocks::tst_mainWindowAlwaysHasCentralWidget()
{
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();
    QWidget *central = m->centralWidget();
    auto dropArea = m->dropArea();
    QVERIFY(dropArea);

    QPointer<Frame> centralFrame = static_cast<Frame*>(dropArea->centralFrame()->frame());
    QVERIFY(central);
    QVERIFY(dropArea);
    QCOMPARE(dropArea->count(), 1);
    QVERIFY(centralFrame);
    QCOMPARE(centralFrame->dockWidgetCount(), 0);

    // Add a tab
    auto dock = createDockWidget("doc1", Qt::green);
    m->addDockWidgetAsTab(dock);
    QCOMPARE(dropArea->count(), 1);
    QCOMPARE(centralFrame->dockWidgetCount(), 1);

    qDebug() << "Central widget width=" << central->size() << "; mainwindow="
             << m->size();

    // Detach tab
    QPoint globalPressPos = dragPointForWidget(centralFrame.data(), 0);
    QTabBar *tabBar = static_cast<FrameWidget*>(centralFrame.data())->tabBar();
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
    auto dropArea = m->dropArea();

    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
    auto dock3 = createDockWidget("dock3", new QPushButton("three"));

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
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dropArea = m->dropArea();

    Frame *centralWidget = dropArea->multiSplitterLayout()->items()[0]->frame();
    nestDockWidget(dock1, dropArea, centralWidget, KDDockWidgets::Location_OnRight);

    QVERIFY(dock1->width() < dropArea->width() - centralWidget->width());
}

void TestDocks::tst_closeAllDockWidgets()
{
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();
    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("one"));
    auto dock3 = createDockWidget("dock3", new QPushButton("one"));
    auto dock4 = createDockWidget("dock4", new QPushButton("one"));
    auto dock5 = createDockWidget("dock5", new QPushButton("one"));
    auto dock6 = createDockWidget("dock6", new QPushButton("one"));

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

    QCOMPARE(dock3->window(), fw.data());
    QCOMPARE(dock4->window(), m.get());
    QCOMPARE(dock5->window(), m.get());
    QCOMPARE(dock6->window(), fw.data());

    qDebug() << "closeAllDockWidgets";
    DockRegistry::self()->clear();
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
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
    auto dropArea = m->dropArea();
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

    dock1 = createDockWidget("one", new QTextEdit());
    m->addDockWidgetAsTab(dock1);
    auto dock3 = createDockWidget("three", new QTextEdit());
    m->addDockWidget(dock3, Location_OnTop);
    QVERIFY(m->dropArea()->checkSanity());

    min1 = widgetMinLength(dock1, Qt::Horizontal);
    QVERIFY(dock1->height() >= min1);
}

void TestDocks::tst_restoreEmpty()
{
    EnsureTopLevelsDeleted e;

    // Create a main window, with a left dock, save it to disk.
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto layout = m->multiSplitterLayout();
    auto oldRight = layout->m_rightAnchor;
    const int oldRightPos = oldRight->position();
    LayoutSaver saver;
    QVERIFY(saver.saveToDisk());
    saver.restoreFromDisk();
    QVERIFY(m->multiSplitterLayout()->checkSanity());
    QVERIFY(oldRight != layout->m_rightAnchor); // It got new static-anchors
    QVERIFY(oldRightPos == layout->m_rightAnchor->position());
    QCOMPARE(layout->anchors().size(), 4);
    QCOMPARE(layout->count(), 0);
}

void TestDocks::tst_restoreSimple()
{
    EnsureTopLevelsDeleted e;
    // Tests restoring a very simple layout, composed of just 1 docked widget

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto layout = m->multiSplitterLayout();
    auto dock1 = createDockWidget("one", new QTextEdit());
    auto dock2 = createDockWidget("two", new QTextEdit());
    auto dock3 = createDockWidget("three", new QTextEdit());
    m->addDockWidget(dock1, Location_OnTop);

    // Dock2 floats at 150,150
    const QPoint dock2FloatingPoint = QPoint(150, 150);
    dock2->window()->move(dock2FloatingPoint);
    QVERIFY(dock2->isVisible());

    const QPoint dock3FloatingPoint = QPoint(200, 200);
    dock3->window()->move(dock3FloatingPoint);
    dock3->close();

    LayoutSaver saver;
    QVERIFY(saver.saveToDisk());
    auto f1 = dock1->frame();
    dock2->window()->move(QPoint(0, 0)); // Move *after* we saved.
    dock3->window()->move(QPoint(0, 0)); // Move *after* we saved.
    dock1->close();
    dock2->close();
    QVERIFY(!dock2->isVisible());
    QCOMPARE(layout->count(), 1);
    QVERIFY(waitForDeleted(f1));
    QCOMPARE(layout->placeholderCount(), 1);

    QCOMPARE(DockRegistry::self()->nestedwindows().size(), 0);
    QVERIFY(saver.restoreFromDisk());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    QVERIFY(dock1->isVisible());
    layout->checkSanity();
    QCOMPARE(saver.restoredDockWidgets().size(), 3);

    // Test a crash I got:
    dock1->setFloating(true);
    dock1->setFloating(false);

    auto fw2 = dock2->floatingWindow();
    QVERIFY(fw2);
    QVERIFY(fw2->isVisible());
    QVERIFY(fw2->isTopLevel());
    QCOMPARE(fw2->pos(), dock2FloatingPoint);
    QCOMPARE(fw2->parent(), m.get());
    QVERIFY(dock2->isFloating());
    QVERIFY(dock2->isVisible());

    QVERIFY(!dock3->isVisible()); // Remains closed
    QVERIFY(dock3->parentWidget() == nullptr);

    dock3->show();
    dock3->morphIntoFloatingWindow(); // as it would take 1 event loop. Do it now so we can compare already.

    QCOMPARE(dock3->window()->pos(), dock3FloatingPoint);

    // Cleanup
    dock3->deleteLater();
    QVERIFY(waitForDeleted(dock3));
}

void TestDocks::tst_restoreNestedAndTabbed()
{
    // Just a more involved test

    EnsureTopLevelsDeleted e;
    QPoint oldFW4Pos;
    QRect oldGeo;
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None, "tst_restoreNestedAndTabbed");
        m->move(500, 500);
        oldGeo = m->geometry();
        auto layout = m->multiSplitterLayout();
        auto dock1 = createDockWidget("1", new QTextEdit());
        auto dock2 = createDockWidget("2", new QTextEdit());
        auto dock3 = createDockWidget("3", new QTextEdit());

        auto dock4 = createDockWidget("4", new QTextEdit());
        auto dock5 = createDockWidget("5", new QTextEdit());
        dock4->addDockWidgetAsTab(dock5);
        oldFW4Pos = dock4->window()->pos();

        m->addDockWidget(dock1, Location_OnLeft);
        m->addDockWidget(dock2, Location_OnRight);
        dock2->addDockWidgetAsTab(dock3);
        dock2->setAsCurrentTab();
        QCOMPARE(dock2->frame()->currentTabIndex(), 0);
        QCOMPARE(dock4->frame()->currentTabIndex(), 1);

        LayoutSaver saver;
        QVERIFY(saver.saveToDisk());
        QVERIFY(layout->checkSanity());
        // Let it be destroyed, we'll restore a new one
    }

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None, "tst_restoreNestedAndTabbed");
    auto layout = m->multiSplitterLayout();
    auto dock1 = createDockWidget("1", new QTextEdit());
    auto dock2 = createDockWidget("2", new QTextEdit());
    auto dock3 = createDockWidget("3", new QTextEdit());
    auto dock4 = createDockWidget("4", new QTextEdit());
    auto dock5 = createDockWidget("5", new QTextEdit());

    LayoutSaver saver;
    QVERIFY(saver.restoreFromDisk());
    QVERIFY(layout->checkSanity());

    auto fw4 = dock4->floatingWindow();
    QVERIFY(fw4);
    QCOMPARE(dock4->window(), dock5->window());
    QCOMPARE(fw4->pos(), oldFW4Pos);

    QCOMPARE(dock1->window(), m.get());
    QCOMPARE(dock2->window(), m.get());
    QCOMPARE(dock3->window(), m.get());

    QCOMPARE(dock2->frame()->currentTabIndex(), 0);
    QCOMPARE(dock4->frame()->currentTabIndex(), 1);

    qDebug() << m->frameGeometry() << m->geometry();
    QCOMPARE(m->geometry(), oldGeo);
}

void TestDocks::tst_restoreCentralFrame()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500));
    auto layout = m->multiSplitterLayout();

    QCOMPARE(layout->count(), 1);
    Item *item = m->dropArea()->centralFrame();
    QVERIFY(item);
    QCOMPARE(item->frame()->options(), Frame::Option_IsCentralFrame | Frame::Option_AlwaysShowsTabs);
    QVERIFY(!item->frame()->titleBar()->isVisible());

    LayoutSaver saver;
    QVERIFY(saver.saveToDisk());
    QVERIFY(saver.restoreFromDisk());

    QCOMPARE(layout->count(), 1);
    item = m->dropArea()->centralFrame();
    QVERIFY(item);
    QCOMPARE(item->frame()->options(), Frame::Option_IsCentralFrame | Frame::Option_AlwaysShowsTabs);
    QVERIFY(!item->frame()->titleBar()->isVisible());
}

void TestDocks::tst_restoreCrash()
{
    EnsureTopLevelsDeleted e;

    {
        // Create a main window, with a left dock, save it to disk.
        auto m = createMainWindow({}, {}, "tst_restoreCrash");
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        m->addDockWidget(dock1, Location_OnLeft);
        LayoutSaver saver;
        QVERIFY(saver.saveToDisk());
    }

    // Restore
    qDebug() << Q_FUNC_INFO << "Restoring";
    auto m = createMainWindow({}, {}, "tst_restoreCrash");
    auto layout = m->multiSplitterLayout();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    QVERIFY(dock1->isFloating());
    QVERIFY(layout->checkSanity());

    LayoutSaver saver;
    QVERIFY(saver.restoreFromDisk());
    QVERIFY(layout->checkSanity());
    QVERIFY(!dock1->isFloating());
}

void TestDocks::tst_restoreTwice()
{
    // Tests that restoring multiple times doesn't hide the floating windows for some reason

    auto m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralFrame, "tst_restoreTwice");
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidgetAsTab(dock1);

    auto dock2 = createDockWidget("2", new QPushButton("2"));
    auto dock3 = createDockWidget("3", new QPushButton("3"));

    dock2->morphIntoFloatingWindow();
    dock3->morphIntoFloatingWindow();

    {
        LayoutSaver saver;
        QVERIFY(saver.saveToDisk());
        QVERIFY(saver.restoreFromDisk());
        QVERIFY(dock2->isVisible());
        QVERIFY(dock3->isVisible());
    }

    {
        LayoutSaver saver;
        QVERIFY(saver.restoreFromDisk());
        QVERIFY(dock2->isVisible());
        QVERIFY(dock3->isVisible());
        QVERIFY(dock2->window()->isVisible());
        QVERIFY(dock3->window()->isVisible());
        auto fw = dock2->floatingWindow();
        QVERIFY(fw);
    }
}

void TestDocks::tst_restoreSideBySide()
{
    // Save a layout that has a floating window with nesting

    EnsureTopLevelsDeleted e;

    QSize item2MinSize;
    {
        EnsureTopLevelsDeleted e1;
        // MainWindow:
        auto m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralFrame, "tst_restoreTwice");
        auto dock1 = createDockWidget("1", new QPushButton("1"));
        m->addDockWidgetAsTab(dock1);
        auto layout = m->multiSplitterLayout();

        // FloatingWindow:
        auto dock2 = createDockWidget("2", new QPushButton("2"));
        auto dock3 = createDockWidget("3", new QPushButton("3"));
        dock2->addDockWidgetToContainingWindow(dock3, Location_OnRight);
        auto fw2 = dock2->floatingWindow();
        item2MinSize = fw2->multiSplitterLayout()->itemForFrame(dock2->frame())->minimumSize();
        LayoutSaver saver;
        QVERIFY(saver.saveToDisk());
        QVERIFY(layout->checkSanity());
    }

    {
        auto m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralFrame, "tst_restoreTwice");
        auto dock1 = createDockWidget("1", new QPushButton("1"));
        auto dock2 = createDockWidget("2", new QPushButton("2"));
        auto dock3 = createDockWidget("3", new QPushButton("3"));

        LayoutSaver restorer;
        QVERIFY(restorer.restoreFromDisk());

        auto fw2 = dock2->floatingWindow();
        QCOMPARE(item2MinSize, fw2->multiSplitterLayout()->itemForFrame(dock2->frame())->minimumSize());

        QCOMPARE(dock1->window(), m.get());
        QCOMPARE(dock2->window(), dock3->window());
    }
}

void TestDocks::tst_restoreWithPlaceholder()
{
    // Float dock1, save and restore, then unfloat and see if dock2 goes back to where it was

    EnsureTopLevelsDeleted e;
    {
        auto m = createMainWindow(QSize(500, 500), {}, "tst_restoreWithPlaceholder");

        auto dock1 = createDockWidget("1", new QPushButton("1"));
        m->addDockWidget(dock1, Location_OnLeft);
        auto layout = m->multiSplitterLayout();
        dock1->setFloating(true);

        LayoutSaver saver;
        QVERIFY(saver.saveToDisk());

        dock1->close();

        QVERIFY(saver.restoreFromDisk());
        QVERIFY(layout->checkSanity());

        QVERIFY(dock1->isFloating());
        QVERIFY(dock1->isVisible());
        QCOMPARE(layout->count(), 1);
        QCOMPARE(layout->placeholderCount(), 1);

        dock1->setFloating(false); // Put it back. Should go back because the placeholder was restored.

        QVERIFY(!dock1->isFloating());
        QVERIFY(dock1->isVisible());
        QCOMPARE(layout->count(), 1);
        QCOMPARE(layout->placeholderCount(), 0);

    }

    // Try again, but on a different main window
    auto m = createMainWindow(QSize(500, 500), {}, "tst_restoreWithPlaceholder");
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto layout = m->multiSplitterLayout();

    LayoutSaver saver;
    QVERIFY(saver.restoreFromDisk());
    QVERIFY(layout->checkSanity());

    QVERIFY(dock1->isFloating());
    QVERIFY(dock1->isVisible());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 1);

    dock1->setFloating(false); // Put it back. Should go back because the placeholder was restored.

    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->isVisible());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
}

void TestDocks::tst_restoreWithNonClosableWidget()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(500, 500), {}, "tst_marginsAfterRestore");
    auto dock1 = createDockWidget("1", new NonClosableWidget(), DockWidgetBase::Option_NotClosable);
    m->addDockWidget(dock1, Location_OnLeft);
    auto layout = m->multiSplitterLayout();

    LayoutSaver saver;
    QVERIFY(saver.saveToDisk());
    QVERIFY(saver.restoreFromDisk());
    QVERIFY(layout->checkSanity());
}

void TestDocks::tst_restoreAfterResize()
{
    // Tests a crash I got when the layout received a resize event *while* restoring

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(500, 500), {}, "tst_restoreAfterResize");
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);
    auto layout = m->multiSplitterLayout();
    const QSize oldContentsSize = layout->size();
    const QSize oldWindowSize = m->size();
    LayoutSaver saver;
    QVERIFY(saver.saveToDisk());
    m->resize(1000, 1000);
    QVERIFY(saver.restoreFromDisk());
    QCOMPARE(oldContentsSize, layout->size());
    QCOMPARE(oldWindowSize, m->size());
}

void TestDocks::tst_marginsAfterRestore()
{
    EnsureTopLevelsDeleted e;
    {
        EnsureTopLevelsDeleted e1;
        // MainWindow:
        auto m = createMainWindow(QSize(500, 500), {}, "tst_marginsAfterRestore");
        auto dock1 = createDockWidget("1", new QPushButton("1"));
        m->addDockWidget(dock1, Location_OnLeft);
        auto layout = m->multiSplitterLayout();

        LayoutSaver saver;
        QVERIFY(saver.saveToDisk());
        QVERIFY(saver.restoreFromDisk());
        QVERIFY(layout->checkSanity());

        dock1->setFloating(true);

        auto fw = dock1->floatingWindow();
        QVERIFY(fw);
        layout->addWidget(fw->dropArea(), Location_OnRight);

        m->dropArea()->debug_updateItemNamesForGammaray();
        layout->checkSanity();
    }
}

void TestDocks::tst_addDockWidgetAsTabToDockWidget()
{
    EnsureTopLevelsDeleted e;
    {
        // Dock into a non-morphed floating dock widget
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));

        dock1->addDockWidgetAsTab(dock2);

        QWidget *window1 = dock1->window();
        QWidget *window2 = dock2->window();
        QCOMPARE(window1, window2);
        QCOMPARE(dock1->frame(), dock2->frame());
        QCOMPARE(dock1->frame()->dockWidgetCount(), 2);
        dock1->deleteLater();
        dock2->deleteLater();
        waitForDeleted(dock2);
    }
    {
        // Dock into a morphed dock widget
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        dock1->morphIntoFloatingWindow();
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));

        dock1->addDockWidgetAsTab(dock2);

        QWidget *window1 = dock1->window();
        QWidget *window2 = dock2->window();
        QCOMPARE(window1, window2);
        QCOMPARE(dock1->frame(), dock2->frame());
        QCOMPARE(dock1->frame()->dockWidgetCount(), 2);
        dock1->deleteLater();
        dock2->deleteLater();
        waitForDeleted(dock2);
    }
    {
        // Dock a morphed dock widget into a morphed dock widget
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        dock1->morphIntoFloatingWindow();
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
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
        dock1->deleteLater();
        dock2->deleteLater();
        waitForDeleted(dock2);
    }
    {
        // Dock to an already docked widget
        auto m = createMainWindow();
        auto dropArea = m->dropArea();
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        nestDockWidget(dock1, dropArea, nullptr, KDDockWidgets::Location_OnLeft);

        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
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
     auto dock1 = createDockWidget("dock1", new QPushButton("one"));
     auto dock2 = createDockWidget("dock2", new QPushButton("two"));

     m->addDockWidget(dock1, Location_OnRight, nullptr);
     m->addDockWidget(dock2, Location_OnTop, dock1);
     QVERIFY(m->dropArea()->checkSanity());

     QCOMPARE(dock1->window(), m.get());
     QCOMPARE(dock2->window(), m.get());
     QVERIFY(dock1->frame()->y() > dock2->frame()->y());
     QCOMPARE(dock1->frame()->x(), dock2->frame()->x());
}

void TestDocks::tst_addDockWidgetToContainingWindow()
{
    EnsureTopLevelsDeleted e;

    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
    auto dock3 = createDockWidget("dock3", new QPushButton("three"));

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
        auto dock1 = createDockWidget("dock1", new MyWidget2());
        auto dock2 = createDockWidget("dock2", new MyWidget2());
        auto dock3 = createDockWidget("dock3", new MyWidget2());
        auto dock4 = createDockWidget("dock4", new MyWidget2());

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

        auto dropArea = m->dropArea();

        dropArea->debug_updateItemNamesForGammaray();

        QVERIFY(dropArea->checkSanity());
        QVERIFY(dock2->width() < mainWindowLength);
        QVERIFY(dock3->height() < m->height());
        QVERIFY(dock4->height() < m->height());
    }

    qDebug() << "Test 2";

    {
        auto m = createMainWindow();
        auto dropArea = m->dropArea();
        auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(100, 100)));
        auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(100, 100)));
        m->addDockWidgetAsTab(dock1);
        m->resize(osWindowMinWidth(), 200);

        waitForResize(m.get());

        qDebug() << "Adding dock2 to Right. window size=" << m->size();
        QVERIFY(m->width() == osWindowMinWidth());
        m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);
        qDebug() << "Waiting for resize. window size2=" << m->size();
        QVERIFY(waitForResize(m.get()));
        qDebug() << "window size3=" << m->size();

        QVERIFY(dropArea->multiSplitterLayout()->width() > osWindowMinWidth());
        QMargins margins = m->centralWidget()->layout()->contentsMargins();
        QCOMPARE(dropArea->multiSplitterLayout()->width(), m->width() - margins.left() - margins.right());
        qDebug() << "New size: " << m->width() << dropArea->multiSplitterLayout()->width()
                 << dropArea->minimumSize();
        QVERIFY(m->dropArea()->checkSanity());
    }

    qDebug() << "Test 3";
    {
        auto m = createMainWindow();
        auto dropArea = m->dropArea();
        auto dock1 = createDockWidget("dock1", new MyWidget2());
        auto dock2 = createDockWidget("dock2", new MyWidget2());
        m->addDockWidgetAsTab(dock1);
        m->resize(osWindowMinWidth(), 200);
        QTest::qWait(200);
        QVERIFY(m->width() == osWindowMinWidth());

        auto fw = dock2->morphIntoFloatingWindow();
        QVERIFY(fw->isVisible());
        QVERIFY(dropArea->checkSanity(MultiSplitterLayout::AnchorSanity_Intersections));

        dragFloatingWindowTo(fw, dropArea, DropIndicatorOverlayInterface::DropLocation_Right);
        QVERIFY(m->dropArea()->checkSanity());
        delete fw;
    }

    qDebug() << "Test 4";
    {
        auto m = createMainWindow(QSize(100, 100), MainWindowOption_None);
        auto dropArea = m->dropArea();
        auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(50, 50)));
        auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(50, 50)));
        MultiSplitterLayout *layout = dropArea->multiSplitterLayout();
        m->addDockWidget(dock1, KDDockWidgets::Location_OnBottom);
        waitForResize(m.get());
        qDebug() << "Size=" << m->size();

        m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);
        waitForResize(m.get());

        const int item2MinHeight =  layout->itemForFrame(dock2->frame())->minLength(Qt::Horizontal);
        QCOMPARE(dropArea->height(), dock1->frame()->height() + item2MinHeight + Anchor::thickness(true)*2 + Anchor::thickness(false));
    }

    qDebug() << "Test 5";
    {
        // Test test shouldn't spit any warnings

        MainWindow m("MyMainWindow_tst_addToSmallMainWindow5", MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(50, 240)));
        auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(50, 240)));
        m.addDockWidget(dock1, KDDockWidgets::Location_OnBottom);
        m.addDockWidget(dock2, KDDockWidgets::Location_OnBottom);

        waitForResize(&m);
        qDebug() << m.size();
    }

    qDebug() << "Test 8";
    {
        // Test test shouldn't spit any warnings

        QWidget container;
        auto lay = new QVBoxLayout(&container);
        MainWindow m("MyMainWindow_tst_addToSmallMainWindow8", MainWindowOption_None);
        lay->addWidget(&m);
        container.resize(100, 100);
        waitForResize(&container);
        container.show();
        waitForResize(&m);
        auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(50, 240)));
        auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(50, 240)));
        m.addDockWidget(dock1, KDDockWidgets::Location_OnBottom);
        m.addDockWidget(dock2, KDDockWidgets::Location_OnBottom);
        waitForResize(&m);
    }
}

void TestDocks::tst_fairResizeAfterRemoveWidget()
{
    // 1. Add 3 dock widgets horizontally, remove the middle one, make sure
    // both left and right widgets get a share of the new available space

    EnsureTopLevelsDeleted e;

    DockWidgetBase *dock1 = createDockWidget("dock1", new QPushButton("one"));
    DockWidgetBase *dock2 = createDockWidget("dock2", new QPushButton("two"));
    DockWidgetBase *dock3 = createDockWidget("dock3", new QPushButton("three"));

    dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);
    dock1->addDockWidgetToContainingWindow(dock3, Location_OnRight, dock2);

    auto fw = dock1->floatingWindow();

    QPointer<Frame> frame2= dock2->frame();

    const int oldWidth1 = dock1->frame()->width();
    const int oldWidth2 = dock2->frame()->width();
    const int oldWidth3 = dock3->frame()->width();
    MultiSplitterLayout *layout = fw->dropArea()->multiSplitterLayout();
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
        auto dock1 = createDockWidget("dock1", new QPushButton("one"), DockWidgetBase::Option_NotClosable);
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        dock1->addDockWidgetAsTab(dock2);

        auto fw = dock1->floatingWindow();
        QVERIFY(fw);
        TitleBar *titlebarFW = fw->titleBar();
        TitleBar *titleBarFrame = fw->frames().at(0)->titleBar();
        QVERIFY(titlebarFW->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonEnabled());

        auto window = dock1->window();
        window->deleteLater();
        waitForDeleted(window);
    }

    {
        // Now dock dock1 into dock1 instead

        auto dock1 = createDockWidget("dock1", new QPushButton("one"), DockWidgetBase::Option_NotClosable);
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));

        dock2->morphIntoFloatingWindow();
        dock2->addDockWidgetAsTab(dock1);

        auto fw = dock1->floatingWindow();
        QVERIFY(fw);
        TitleBar *titlebarFW = fw->titleBar();
        TitleBar *titleBarFrame = fw->frames().at(0)->titleBar();

        QVERIFY(titlebarFW->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonEnabled());

        auto window = dock2->window();
        window->deleteLater();
        waitForDeleted(window);
    }
}

void TestDocks::tst_maximizeAndRestore()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));

    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

    auto dropArea = m->dropArea();
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
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnTop);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight, dock1);

    auto dock3 = createDockWidget("dock3", new QPushButton("three"));
    auto dock4 = createDockWidget("dock4", new QPushButton("four"));

    m->addDockWidget(dock3, KDDockWidgets::Location_OnBottom);
    m->addDockWidget(dock4, KDDockWidgets::Location_OnRight, dock3);

    auto dock5 = createDockWidget("dock5", new QPushButton("five"));
    m->addDockWidget(dock5, KDDockWidgets::Location_OnLeft);

    auto dropArea = m->dropArea();
    dropArea->checkSanity();
}

std::unique_ptr<MultiSplitter> TestDocks::createMultiSplitterFromSetup(MultiSplitterSetup setup, QHash<QWidget*, Frame*> &frameMap) const
{
    auto widget = std::unique_ptr<MultiSplitter>(new MultiSplitter());
    auto layout = widget->multiSplitterLayout();
    widget->show();
    layout->setSize(setup.size);

    const int count = setup.widgets.size();
    for (int i = 0; i < count; ++i) {
        auto frame = Config::self().frameWorkWidgetFactory()->createFrame(widget.get());
        auto dock = new DockWidget(QString("foo_createMultiSplitterFromSetup%1").arg(i));
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

        auto frame = Config::self().frameWorkWidgetFactory()->createFrame();
        const int w1MinLength = 100;
        QWidget *w1 = createWidget(w1MinLength);
        auto dock = new DockWidget("foo");
        dock->setWidget(w1);
        frame->addWidget(dock);
        minFrameSize = frame->minimumSizeHint();
        delete frame;
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

        QWidget *w1 = createWidget(w1MinLength, "w1");
        QWidget *w2 = createWidget(w1MinLength, "w2");
        QWidget *w3 = createWidget(w1MinLength, "w3");

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
    auto layout = multisplitterWidget->multiSplitterLayout();

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

void TestDocks::tst_constraintsAfterPlaceholder()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(500, 500), MainWindowOption_None);
    const int minHeight = 400;
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(400, minHeight)));
    auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(400, minHeight)));
    auto dock3 = createDockWidget("dock3", new MyWidget2(QSize(400, minHeight)));
    auto dropArea = m->dropArea();
    MultiSplitterLayout *layout = dropArea->multiSplitterLayout();

    // Stack 3, 2, 1
    m->addDockWidget(dock1, Location_OnTop);
    m->addDockWidget(dock2, Location_OnTop);
    m->addDockWidget(dock3, Location_OnTop);

    QVERIFY(waitForResize(m.get()));

    QVERIFY(widgetMinLength(m.get(), Qt::Horizontal) > minHeight * 3); // > since some vertical space is occupied by the separators

    // Now close dock1 and check again
    dock1->close();
    waitForResize(dock2);

    Item *item2 = layout->itemForFrame(dock2->frame());
    Item *item3 = layout->itemForFrame(dock3->frame());

    QMargins margins = m->centralWidget()->layout()->contentsMargins();
    const int expectedMinHeight = item2->minLength(Qt::Horizontal) +
                                  item3->minLength(Qt::Horizontal) +
                                  2 * Anchor::thickness(true) +
                                  1 * Anchor::thickness(false)
                                  + margins.top() + margins.bottom();

    QCOMPARE(m->minimumSizeHint().height(), expectedMinHeight);

    dock1->deleteLater();
    waitForDeleted(dock1);
}

void TestDocks::tst_rectForDropMath_data()
{
    QTest::addColumn<QSize>("layoutContentsSize");
    QTest::addColumn<MultiSplitterLayout::Length>("length");
    QTest::addColumn<Location>("location");
    QTest::addColumn<QRect>("relativeToRect");
    QTest::addColumn<QRect>("expectedRect");

    const QRect layoutRect(0, 0, 1000, 1000);
    const QSize contentsSize = layoutRect.size();
    const int staticAnchorThickness = Anchor::thickness(true);
    const int anchorThickness = Anchor::thickness(false);
    const QRect relativeToWindowRect = layoutRect.adjusted(staticAnchorThickness, staticAnchorThickness, -staticAnchorThickness, -staticAnchorThickness);

    MultiSplitterLayout::Length length = { 0, 100 };
    QRect expectedRect(staticAnchorThickness, staticAnchorThickness, 100, 1000 - staticAnchorThickness*2);

    // 1. Relative to the whole window
    QTest::newRow("left-of-window") << contentsSize
                                    << length
                                    << Location_OnLeft
                                    << relativeToWindowRect
                                    << expectedRect;

    expectedRect = QRect(staticAnchorThickness, staticAnchorThickness, 1000 - staticAnchorThickness*2, 100);
    QTest::newRow("top-of-window") << contentsSize
                                   << length
                                   << Location_OnTop
                                   << relativeToWindowRect
                                   << expectedRect;


    expectedRect = QRect(1000 - 100 - staticAnchorThickness, staticAnchorThickness, 100, 1000 - staticAnchorThickness*2);
    QTest::newRow("right-of-window") << contentsSize
                                     << length
                                     << Location_OnRight
                                     << relativeToWindowRect
                                     << expectedRect;

    expectedRect = QRect(staticAnchorThickness, 1000 - 100 - staticAnchorThickness, 1000 - staticAnchorThickness*2, 100);
    QTest::newRow("bottom-of-window") << contentsSize
                                      << length
                                      << Location_OnBottom
                                      << relativeToWindowRect
                                      << expectedRect;

    // 2. Relative to the item, left of leftmost, right of rightmost, etc.
    QRect item1Geometry = QRect(staticAnchorThickness, staticAnchorThickness, 1000 - 2*staticAnchorThickness, 1000 - 2*staticAnchorThickness);
    length = { 0, 100 };
    expectedRect = QRect(staticAnchorThickness, staticAnchorThickness, 100, 1000 - staticAnchorThickness*2);
    QTest::newRow("left-of-leftmost-item") << contentsSize
                                           << length
                                           << Location_OnLeft
                                           << item1Geometry
                                           << expectedRect;

    expectedRect = QRect(staticAnchorThickness, staticAnchorThickness, 1000 - staticAnchorThickness*2, 100);
    QTest::newRow("top-of-topmost-item") << contentsSize
                                         << length
                                         << Location_OnTop
                                         << item1Geometry
                                         << expectedRect;

    expectedRect = QRect(1000 - 100 - staticAnchorThickness, staticAnchorThickness, 100, 1000 - staticAnchorThickness*2);
    QTest::newRow("right-of-rightmost-item") << contentsSize
                                             << length
                                             << Location_OnRight
                                             << item1Geometry
                                             << expectedRect;

    expectedRect = QRect(staticAnchorThickness, 1000 - 100 - staticAnchorThickness, 1000 - staticAnchorThickness*2, 100);
    QTest::newRow("bottom-of-bottommost-item") << contentsSize
                                               << length
                                               << Location_OnBottom
                                               << item1Geometry
                                               << expectedRect;
    // 3. Now we have two items already in the layout, side-by side, item1 on the left, item2 on the right

    const int availableWidth = 1000 - 2*staticAnchorThickness - anchorThickness;
    const int width1 = availableWidth / 2;
    const int width2 = availableWidth - width1;
    const int height1 = width1;
    const int height2 = width2;
    const int h = 1000 - 2*staticAnchorThickness;
    const int w = 1000 - 2*staticAnchorThickness;
    const QRect item1GeometryH = QRect(staticAnchorThickness, staticAnchorThickness, width1, h);
    const QRect item2GeometryH = QRect(item1GeometryH.right() + anchorThickness + 1, staticAnchorThickness, width2, h);

    const QRect item1GeometryV = QRect(staticAnchorThickness, staticAnchorThickness, w, height1);
    const QRect item2GeometryV = QRect(staticAnchorThickness, item1GeometryV.bottom() + anchorThickness + 1, w, height2);

    qDebug() <<"item1H=" << item1GeometryH << "; item2H=" << item2GeometryH;
    qDebug() <<"item1V=" << item1GeometryV << "; item2V=" << item2GeometryV;

    const int spaceBetweenItems = item2GeometryH.left() - item1GeometryH.right() - 1;
    Q_ASSERT(spaceBetweenItems == anchorThickness);

    length = { 100, 0 };
    int x = 1000 - staticAnchorThickness - item2GeometryH.width() - 100;
    expectedRect = QRect(x, staticAnchorThickness, 100, h);
    qDebug() << "expected=" << expectedRect;
    QTest::newRow("left-of-right-item") << contentsSize
                                        << length
                                        << Location_OnLeft
                                        << item2GeometryH
                                        << expectedRect;

    length = { 0, 100 };
    x = item1GeometryH.width() + anchorThickness + staticAnchorThickness;
    expectedRect = QRect(x, staticAnchorThickness, 100, h);
    qDebug() << "expected=" << expectedRect;
    QTest::newRow("left-of-right-item2") << contentsSize
                                         << length
                                         << Location_OnLeft
                                         << item2GeometryH
                                         << expectedRect;

    int side1 = 2;
    length = { side1, 98 };
    x = item1GeometryH.width() + anchorThickness - side1 + staticAnchorThickness;
    expectedRect = QRect(x, staticAnchorThickness, 100, h);
    qDebug() << "expected=" << expectedRect;
    QTest::newRow("left-of-right-item3") << contentsSize
                                         << length
                                         << Location_OnLeft
                                         << item2GeometryH
                                         << expectedRect;


    length = { 100, 0 };
    int y = 1000 - staticAnchorThickness - item2GeometryV.height() - 100;
    expectedRect = QRect(staticAnchorThickness, y, w, 100);
    qDebug() << "expected=" << expectedRect;
    QTest::newRow("top-of-bottom-item") << contentsSize
                                        << length
                                        << Location_OnTop
                                        << item2GeometryV
                                        << expectedRect;

    length = { 0, 100 };
    x = item1GeometryH.right() + 1;
    expectedRect = QRect(x, staticAnchorThickness, 100, h);
    QTest::newRow("right-of-left-item") << contentsSize
                                        << length
                                        << Location_OnRight
                                        << item1GeometryH
                                        << expectedRect;


}

void TestDocks::tst_rectForDropMath()
{
    QFETCH(QSize, layoutContentsSize);
    QFETCH(MultiSplitterLayout::Length, length);
    QFETCH(Location, location);
    QFETCH(QRect, relativeToRect);
    QFETCH(QRect, expectedRect);

    MultiSplitter widget;
    MultiSplitterLayout layout(&widget);
    layout.setSize(layoutContentsSize);

    const QRect result = layout.rectForDrop(length, location, relativeToRect);
    qDebug() << "Result=" << result;
    QCOMPARE(result, expectedRect);
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

        QWidget * widgetToDrop = createWidget(100, "w1");
        widgetToDrop->resize(200, 200);
        const int expectedLength = 200; // this 200 will change when the initial length algoritm changes; Maybe just call MultiSplitterLayout::LengthForDrop() directly here
        rects << ExpectedRectForDrop {widgetToDrop, KDDockWidgets::Location_OnLeft, nullptr, QRect(staticAnchorThickness, staticAnchorThickness, expectedLength,  multispitterlength - staticAnchorThickness*2) };
        rects << ExpectedRectForDrop {widgetToDrop, KDDockWidgets::Location_OnTop, nullptr, QRect(staticAnchorThickness, staticAnchorThickness, multispitterlength - staticAnchorThickness*2, expectedLength) };
        rects << ExpectedRectForDrop {widgetToDrop, KDDockWidgets::Location_OnRight, nullptr, QRect(300 - staticAnchorThickness, staticAnchorThickness, expectedLength, multispitterlength - staticAnchorThickness*2) };
        rects << ExpectedRectForDrop {widgetToDrop, KDDockWidgets::Location_OnBottom, nullptr, QRect(staticAnchorThickness, 300 - staticAnchorThickness, multispitterlength - staticAnchorThickness*2, expectedLength) };

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
    auto layout = multisplitterWidget->multiSplitterLayout();
    qDebug() << "Created with contentsSize=" << layout->width() << layout->height()<< multisplitterSetup.size;
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
    {
        // 1. Teste an assert I got
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        auto layout = m->multiSplitterLayout();

        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        Item *item1 = layout->itemForFrame(dock1->frame());
        dock1->addDockWidgetAsTab(dock2);

        dock1->setFloating(true);
        Item *layoutItem = dock1->lastPosition()->layoutItem();
        QVERIFY(layoutItem && layoutItem->isInMainWindow());
        QCOMPARE(layoutItem, item1);

        QCOMPARE(layout->placeholderCount(), 0);
        QCOMPARE(layout->count(), 1);
        QCOMPARE(layout->numAchorsFollowing(), 0);

        // Move from tab to bottom
        m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 1);
        QCOMPARE(layout->numAchorsFollowing(), 1);

        dock1->deleteLater();
        waitForDeleted(dock1);
    }
}

void TestDocks::tst_crash2_data()
{
    QTest::addColumn<bool>("show");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

void TestDocks::tst_crash2()
{
    QFETCH(bool, show);

    {
        EnsureTopLevelsDeleted e;
        auto m = new MainWindow("m1", MainWindowOption_None);
        auto layout = m->multiSplitterLayout();
        m->setVisible(show);

        DockWidget::List docks;
        const int num = 4;
        for (int i = 0; i < num; ++i)
            docks << new DockWidget(QString::number(i));

        QVector<KDDockWidgets::Location> locations = {Location_OnLeft,
                                                      Location_OnRight, Location_OnRight, Location_OnRight};

        QVector<KDDockWidgets::AddingOption> options = { AddingOption_StartHidden,
                                                        AddingOption_StartHidden, AddingOption_None, AddingOption_StartHidden};

        QVector<bool> floatings =  {true, false, false, false};

        for (int i = 0; i < num; ++i) {

            m->addDockWidget(docks[i], locations[i], nullptr, options[i]);
            layout->checkSanity();

            QCOMPARE(layout->m_leftAnchor->cumulativeMinLength(Anchor::Side2), layout->minimumSize().width());
            QCOMPARE(layout->m_topAnchor->cumulativeMinLength(Anchor::Side2), layout->minimumSize().height());

            docks[i]->setFloating(floatings[i]);
        }

        qDeleteAll(docks);
        qDeleteAll(DockRegistry::self()->frames());
        delete m;
    }

    {
        EnsureTopLevelsDeleted e;
        auto m = new MainWindow("m1");
        auto layout = m->multiSplitterLayout();
        m->show();

        const int num = 3;
        DockWidget::List docks;
        for (int i = 0; i < num; ++i)
            docks << new DockWidget(QString::number(i));

        QVector<KDDockWidgets::Location> locations = {Location_OnLeft, Location_OnLeft,
                                                      Location_OnRight};

        QVector<KDDockWidgets::AddingOption> options = { AddingOption_None, AddingOption_None,
                                                        AddingOption_StartHidden};

        QVector<bool> floatings =  {true, false, false};

        for (int i = 0; i < num; ++i) {

            m->addDockWidget(docks[i], locations[i], nullptr, options[i]);
            layout->checkSanity();

            QCOMPARE(layout->m_leftAnchor->cumulativeMinLength(Anchor::Side2), layout->minimumSize().width());
            QCOMPARE(layout->m_topAnchor->cumulativeMinLength(Anchor::Side2), layout->minimumSize().height());

            docks[i]->setFloating(floatings[i]);
        }

        qDeleteAll(docks);
        qDeleteAll(DockRegistry::self()->frames());
        delete m;
    }

}

void TestDocks::tst_setFloatingWhenWasTabbed()
{
    // Tests DockWidget::isTabbed() and DockWidget::setFloating(false|true) when tabbed (it should redock)
    // setFloating(false) for side-by-side is tested in another function

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));

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
    QCOMPARE(dock2->frame()->m_tabWidget->numDockWidgets(), 2);

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
    auto dock3 = createDockWidget("dock3", new QPushButton("three"));
    dock3->setFloating(true);
    dock3->setFloating(true);

    // 8. Tab 3 together, detach the middle one, reattach the middle one, it should go to the middle.
    m->addDockWidgetAsTab(dock3);
    dock2->setFloating(true);
    QVERIFY(dock2->isFloating());
    dock2->setFloating(false);
    QVERIFY(!dock2->isFloating());
    QVERIFY(dock2->isTabbed());
    QCOMPARE(dock2->frame()->m_tabWidget->indexOfDockWidget(dock2), 1);


    // 10. Float dock1, and dock it to main window as tab. This tests Option_AlwaysShowsTabs.
    dock1->setFloating(true);
    dock2->setFloating(true);
    dock3->setFloating(true);

    m->addDockWidgetAsTab(dock1);
    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->isTabbed());
    dock1->setFloating(true);
    dock1->setFloating(false);
    QCOMPARE(dock1->frame()->m_tabWidget->numDockWidgets(), 1);

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

    {
        // 1. Create a MainWindow with two docked dock-widgets, then float the first one.
        auto m = createMainWindow();
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

        QPointer<Frame> frame1 = dock1->frame();
        dock1->setFloating(true);
        QVERIFY(dock1->isFloating());
        auto fw = dock1->floatingWindow();
        QVERIFY(fw);

        //2. Put it back, via setFloating(). It should return to its place.
        dock1->setFloating(false);

        QVERIFY(!dock1->isFloating());
        QVERIFY(!dock1->isTabbed());

        waitForDeleted(fw);
    }

    {
        // 2. Tests a case where restoring a dock widget wouldn't make it use all its available space
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        auto dock3 = createDockWidget("dock3", new QPushButton("three"));
        auto dropArea = m->dropArea();
        MultiSplitterLayout *layout = dropArea->multiSplitterLayout();
        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);
        m->addDockWidget(dock3, KDDockWidgets::Location_OnRight);
        auto f2 = dock2->frame();
        Item *item2 = layout->itemForFrame(f2);
        QVERIFY(item2);
        dock2->close();
        dock3->close();
        waitForDeleted(f2);
        dock2->show();

        waitForResize(dock2);

        AnchorGroup group = item2->anchorGroup();
        AnchorGroup staticGroup = layout->staticAnchorGroup();
        QCOMPARE(group.right->followee(), staticGroup.right);
        QCOMPARE(group.right->position(), staticGroup.right->position());
        QCOMPARE(item2->geometry(), dock2->frame()->geometry());
        layout->checkSanity();
        QCOMPARE(item2->size(), group.itemSize());

        // Cleanup
        dock3->deleteLater();
        waitForDeleted(dock3);
    }
}

void TestDocks::tst_setFloatingAfterDraggedFromTabToSideBySide()
{
    EnsureTopLevelsDeleted e;
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        auto dropArea = m->dropArea();
        auto layout = dropArea->multiSplitterLayout();

        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        dock1->addDockWidgetAsTab(dock2);

        // Move from tab to bottom
        m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);
        QCOMPARE(layout->numAchorsFollowing(), 0);

        dock2->setFloating(true);
        dock2->setFloating(false);
        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);
        QCOMPARE(layout->numAchorsFollowing(), 0);
        QVERIFY(!dock2->isFloating());
    }

    {
        // 2. Try again, but now detach from tab before putting it on the bottom. What was happening was that MultiSplitterLayout::addWidget()
        // called with a MultiSplitter as widget wasn't setting the layout items for the dock widgets
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        auto dropArea = m->dropArea();
        auto layout = dropArea->multiSplitterLayout();

        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        dock1->addDockWidgetAsTab(dock2);
        Item *oldItem2 = dock2->lastPosition()->layoutItem();
        QCOMPARE(oldItem2, layout->itemForFrame(dock2->frame()));


        // Detach tab
        dock1->frame()->m_tabWidget->detachTab(dock2);
        auto fw2 = dock2->floatingWindow();
        QVERIFY(fw2);
        QCOMPARE(dock2->lastPosition()->layoutItem(), oldItem2);
        Item *item2 = fw2->dropArea()->multiSplitterLayout()->itemForFrame(dock2->frame());
        QVERIFY(item2);
        QCOMPARE(item2->parentWidget(), fw2->dropArea());
        QVERIFY(!layout->itemForFrame(dock2->frame()));

        // Move from tab to bottom
        layout->addWidget(fw2->dropArea(), KDDockWidgets::Location_OnRight, nullptr);
        QVERIFY(dock2->lastPosition()->layoutItem());
        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);
        QCOMPARE(layout->numAchorsFollowing(), 0);

        dock2->setFloating(true);
        dock2->setFloating(false);

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);
        QCOMPARE(layout->numAchorsFollowing(), 0);
        QVERIFY(!dock2->isFloating());
        waitForDeleted(fw2);
    }
}

void TestDocks::tst_setFloatingAFrameWithTabs()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dropArea = m->dropArea();
    auto layout = dropArea->multiSplitterLayout();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->addDockWidgetAsTab(dock2);

    // Make it float
    dock1->frame()->titleBar()->onFloatClicked();

    auto fw = dock1->floatingWindow();
    QVERIFY(fw);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);

    auto frame1 = dock1->frame();
    QVERIFY(frame1->layoutItem());

    // Attach it again
    dock1->frame()->titleBar()->onFloatClicked();

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(dock1->window(), m.get());

    waitForDeleted(fw);
}

void TestDocks::tst_setVisibleFalseWhenSideBySide()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
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
    m->multiSplitterLayout()->checkSanity();
}

void TestDocks::tst_simple2()
{
    // Simply create a MainWindow, and dock something on top
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dw = createDockWidget("dw", new QPushButton("dw"));
    m->addDockWidget(dw, KDDockWidgets::Location_OnTop);
    m->multiSplitterLayout()->checkSanity();
}

void TestDocks::tst_refUnrefItem()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("1"));
    auto dock2 = createDockWidget("dock2", new QPushButton("2"));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);
    auto dropArea = m->dropArea();
    auto layout = dropArea->multiSplitterLayout();
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
    auto dock3 = createDockWidget("dock3", new QPushButton("3"));
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
    auto dock4 = createDockWidget("dock4", new QPushButton("4"));
    m->addDockWidget(dock4, KDDockWidgets::Location_OnLeft);

    QPointer<Frame> frame4 = dock4->frame();
    QPointer<Item> item4 = layout->itemForFrame(frame4);
    dock4->close();
    waitForDeleted(frame4);
    QCOMPARE(item4->refCount(), 1);
    QVERIFY(item4->isPlaceholder());
    layout->checkSanity();

    auto m2 = createMainWindow();
    m2->addDockWidget(dock4, KDDockWidgets::Location_OnLeft);
    m2->multiSplitterLayout()->checkSanity();
    QVERIFY(!item4.data());
}

void TestDocks::tst_addAndReadd()
{
    EnsureTopLevelsDeleted e;

    // 1. This just tests some crash I got.
    // Make a dock widget float and immediately reattach it
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("1"));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->setFloating(true);
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->frame()->titleBar()->makeWindow();
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->frame()->titleBar()->makeWindow();

    auto fw = dock1->floatingWindow();
    QVERIFY(fw);
    auto dropArea = m->dropArea();
    dragFloatingWindowTo(fw, dropArea, DropIndicatorOverlayInterface::DropLocation_OutterRight);
    dock1->frame()->titleBar()->makeWindow();
    m->multiSplitterLayout()->checkSanity();

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
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    auto dropArea = m->dropArea();
    auto layout = dropArea->multiSplitterLayout();

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

    auto fw = dock1->floatingWindow();
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
    fw = dock1->floatingWindow();
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 2);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();

    waitForDeleted(fw);
}

void TestDocks::tst_availableLengthForOrientation()
{
    EnsureTopLevelsDeleted e;

    // 1. Test a completely empty window, it's available space is its size minus the static separators thickness
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    auto dropArea = m->dropArea();
    MultiSplitterLayout *layout = dropArea->multiSplitterLayout();

    int availableWidth = layout->availableLengthForOrientation(Qt::Vertical);
    int availableHeight = layout->availableLengthForOrientation(Qt::Horizontal);
    QCOMPARE(availableWidth, layout->width() - 2 * Anchor::thickness(true));
    QCOMPARE(availableHeight, layout->height() - 2 *Anchor::thickness(true));

    //2. Now do the same, but we have some widget docked

    auto dock1 = createDockWidget("dock1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);

    const int dock1MinWidth = layout->itemForFrame(dock1->frame())->minLength(Qt::Vertical);
    const int dock1MinHeight = layout->itemForFrame(dock1->frame())->minLength(Qt::Horizontal);

    availableWidth = layout->availableLengthForOrientation(Qt::Vertical);
    availableHeight = layout->availableLengthForOrientation(Qt::Horizontal);
    QCOMPARE(availableWidth, layout->width() - 2 * Anchor::thickness(true) - Anchor::thickness(false) - dock1MinWidth);
    QCOMPARE(availableHeight, layout->height() - 2 *Anchor::thickness(true) - Anchor::thickness(false) -  dock1MinHeight);
    m->multiSplitterLayout()->checkSanity();
}

void TestDocks::tst_setAstCurrentTab()
{
    EnsureTopLevelsDeleted e;

    // Tests DockWidget::setAsCurrentTab() and DockWidget::isCurrentTab()
    // 1. a single dock widget is current, by definition
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    QVERIFY(dock1->isCurrentTab());

    // 2. Tab dock2 to the group, dock2 is current now
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    dock1->addDockWidgetAsTab(dock2);
    QVERIFY(!dock1->isCurrentTab());
    QVERIFY(dock2->isCurrentTab());

    // 3. Set dock1 as current
    dock1->setAsCurrentTab();
    QVERIFY(dock1->isCurrentTab());
    QVERIFY(!dock2->isCurrentTab());

    auto fw = dock1->floatingWindow();
    QVERIFY(fw);
    fw->multiSplitterLayout()->checkSanity();

    delete dock1; delete dock2;
    waitForDeleted(fw);
}

void TestDocks::tst_closeShowWhenNoCentralFrame()
{
    EnsureTopLevelsDeleted e;
    // Tests a crash I got when hidding and showing and no central frame

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    QPointer<DockWidgetBase> dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->close();
    QVERIFY(!dock1->frame());
    QVERIFY(!waitForDeleted(dock1)); // It was being deleted due to a bug
    QVERIFY(dock1);
    dock1->show();
    m->multiSplitterLayout()->checkSanity();
}

void TestDocks::tst_placeholderDisappearsOnReadd()
{
    // This tests that addMultiSplitter also updates refcount of placeholders

    // 1. Detach a widget and dock it on the opposite side. Placeholder
    // should have been deleted and anchors properly positioned

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    MultiSplitterLayout *layout = m->multiSplitterLayout();

    QPointer<DockWidgetBase> dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->dumpDebug();
    dock1->setFloating(true);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 1);

    dock1->morphIntoFloatingWindow();
    auto fw = dock1->floatingWindow();
    layout->addMultiSplitter(fw->dropArea(), Location_OnRight );
    layout->dumpDebug();
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->count(), 1);

    layout->checkSanity();
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // The dock1 should occupy the entire width
    QCOMPARE(dock1->frame()->width(), layout->width() - 2 * Anchor::thickness(true));

    QVERIFY(waitForDeleted(fw));
}

void TestDocks::tst_placeholdersAreRemovedPropertly()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    MultiSplitterLayout *layout = m->multiSplitterLayout();
    QPointer<DockWidgetBase> dock1 = createDockWidget("1", new QPushButton("1"));
    QPointer<DockWidgetBase> dock2 = createDockWidget("2", new QPushButton("2"));
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
    layout->checkSanity();

    // Cleanup
    waitForDeleted(window1);
}

void TestDocks::tst_embeddedMainWindow()
{
    EnsureTopLevelsDeleted e;
    // Tests a MainWindow which isn't a top-level window, but is embedded in another window
    EmbeddedWindow *window = createEmbeddedMainWindow(QSize(800, 800));

    auto dock1 = createDockWidget("1", new QPushButton("1"));
    window->mainWindow->addDockWidget(dock1, Location_OnTop);
    dock1->setFloating(true);
    auto dropArea = window->mainWindow->dropArea();
    auto fw = dock1->floatingWindow();
    dragFloatingWindowTo(fw, dropArea, DropIndicatorOverlayInterface::DropLocation_OutterLeft);

    auto layout = dropArea->multiSplitterLayout();
    QVERIFY(waitForDeleted(fw));
    QCOMPARE(layout->count(), 2); // 2, as it has the central frame
    QCOMPARE(layout->visibleCount(), 2);
    layout->checkSanity();

    delete window;
}

void TestDocks::tst_toggleMiddleDockCrash()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    MultiSplitterLayout *layout = m->multiSplitterLayout();
    QPointer<DockWidgetBase> dock1 = createDockWidget("1", new QPushButton("1"));
    QPointer<DockWidgetBase> dock2 = createDockWidget("2", new QPushButton("2"));
    QPointer<DockWidgetBase> dock3 = createDockWidget("3", new QPushButton("3"));

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);

    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 0);

    auto frame = dock2->frame();
    dock2->close();
    QVERIFY(waitForDeleted(frame));

    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 1);
    QVERIFY(layout->checkSanity());
    QCOMPARE(layout->numAchorsFollowing(), 1);

    qDebug() << "Dock1.min=" << KDDockWidgets::widgetMinLength(dock1->frame(), Qt::Vertical);
    qDebug() << "Dock3.min=" << KDDockWidgets::widgetMinLength(dock3->frame(), Qt::Vertical);

    dock2->show();
    layout->checkSanity();
}

void TestDocks::tst_invalidPlaceholderPosition_data()
{
    QTest::addColumn<bool>("restore1First");
    QTest::newRow("restore1First") << true;
    QTest::newRow("restore2First") << false;
}

void TestDocks::tst_invalidPlaceholderPosition()
{
    QFETCH(bool, restore1First);

    // Tests a bug I saw: 3 widgets stacked, close the top one, then the second top one
    // result: the bottom most one didn't have it's top separator at y=0

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    auto dock3 = createDockWidget("3", new QPushButton("3"));

    MultiSplitterLayout *layout = m->multiSplitterLayout();

    // Stack: 1, 2, 3 vertically
    m->addDockWidget(dock3, Location_OnTop);
    m->addDockWidget(dock2, Location_OnTop);
    m->addDockWidget(dock1, Location_OnTop);

    QCOMPARE(layout->numAchorsFollowing(), 0);

    auto frame1 = dock1->frame();
    auto frame2 = dock2->frame();
    auto frame3 = dock3->frame();
    const int staticAnchorThickness = Anchor::thickness(true);
    QCOMPARE(frame1->y(), staticAnchorThickness);

    // Close 1
    dock1->close();
    waitForResize(frame2);

    // Check that frame2 moved up to y=1
    QCOMPARE(frame2->y(), staticAnchorThickness);
    QCOMPARE(layout->numAchorsFollowing(), 1);
    layout->dumpDebug();

    // Close 2
    dock2->close();
    waitForResize(dock3);

    QVERIFY(layout->checkSanity());
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 2);
    QCOMPARE(layout->numAchorsFollowing(), 2);

    // Check that frame3 moved up to y=1
    QCOMPARE(frame3->y(), staticAnchorThickness);

    // Now restore:
    auto toRestore1 = restore1First ? dock1 : dock2;
    auto toRestore2 = restore1First ? dock2 : dock1;


    qDebug() << "About to show dock1";
    toRestore1->show();
    QCOMPARE(layout->placeholderCount(), 1);
    QVERIFY(dock3->isVisible());
    QVERIFY(!dock3->size().isNull());


    QCOMPARE(layout->numAchorsFollowing(), 1);
    toRestore2->show();

    waitForResize(frame3);
    QVERIFY(layout->checkSanity());
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->numAchorsFollowing(), 0);
    layout->checkSanity();

    dock1->deleteLater();
    dock2->deleteLater();
    QVERIFY(waitForDeleted(dock2));
}

void TestDocks::tst_28NestedWidgets_data()
{
    QTest::addColumn<QVector<DockDescriptor>>("docksToCreate");
    QTest::addColumn<QVector<int>>("docksToHide");

    QVector<DockDescriptor> docks = {
        {Location_OnLeft, -1, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnTop, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnLeft, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnBottom, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None }
    };

    QTest::newRow("28") << docks << QVector<int>{11, 0};

    docks = {
        {Location_OnLeft, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnTop, -1, nullptr, AddingOption_None },
        {Location_OnLeft, -1, nullptr, AddingOption_None },

    };

    QVector<int> docksToHide;
    for (int i = 0; i < docks.size(); ++i) {
        docksToHide << i;
    }

    QTest::newRow("anchor_intersection") << docks << docksToHide;

    docks = {
        {Location_OnLeft, -1, nullptr, AddingOption_None },
        {Location_OnBottom, -1, nullptr, AddingOption_None },
        {Location_OnBottom, -1, nullptr, AddingOption_None },
        {Location_OnBottom, -1, nullptr, AddingOption_None },
        {Location_OnBottom, -1, nullptr, AddingOption_None },
        {Location_OnBottom, -1, nullptr, AddingOption_None },
        {Location_OnTop, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
    };

    // 2. Produced valgrind invalid reads while adding
    QTest::newRow("valgrind") << docks << QVector<int>{};

    docks = {
        {Location_OnLeft, -1, nullptr, AddingOption_None },
        {Location_OnBottom, -1, nullptr, AddingOption_None },
        {Location_OnTop, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
    };
    QTest::newRow("bug_when_closing") << docks << QVector<int>{}; // Q_ASSERT(!isSquashed())

    docks = {
        {Location_OnLeft, -1, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnBottom, -1, nullptr, AddingOption_None },
    };

    QTest::newRow("bug_when_closing2") << docks << QVector<int>{};    // Tests for void KDDockWidgets::Anchor::setPosition(int, KDDockWidgets::Anchor::SetPositionOptions) Negative position -69

    docks = {
        {Location_OnLeft, -1, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnBottom, 0, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnTop, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnLeft, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnBottom, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None }
    };

    docksToHide.clear();
    for (int i = 0; i < 28; ++i) {
        if (i != 16 && i != 17 && i != 18 && i != 27)
            docksToHide << i;
    }

    QTest::newRow("bug_with_holes") << docks << docksToHide;

    docks = {
        {Location_OnLeft, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnTop, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnLeft, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnLeft, 17, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None } };

    docksToHide.clear();
    QTest::newRow("add_as_placeholder") << docks << docksToHide;

    docks = {
        {Location_OnLeft, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden } };

    QTest::newRow("add_as_placeholder_simple") << docks << docksToHide;


    docks = {
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden } };

    docksToHide.clear();
    QTest::newRow("isSquashed_assert") << docks << docksToHide;

    docks = {
        {Location_OnLeft, -1, nullptr, AddingOption_StartHidden },
        {Location_OnTop, -1, nullptr, AddingOption_None },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden } };

    docksToHide.clear();
    QTest::newRow("negative_pos_warning") << docks << docksToHide;

    docks = {
        {Location_OnTop, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_None } };

    docksToHide.clear();
    QTest::newRow("bug") << docks << docksToHide;

    docks = {
        {Location_OnTop, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_None } };

    docksToHide.clear();
    QTest::newRow("bug2") << docks << docksToHide;

    docks = {
        {Location_OnLeft, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnTop, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnLeft, -1, nullptr, AddingOption_None },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_None } };

    docksToHide.clear();
    QTest::newRow("bug3") << docks << docksToHide;
}

void TestDocks::tst_28NestedWidgets()
{
    QFETCH(QVector<DockDescriptor>, docksToCreate);
    QFETCH(QVector<int>, docksToHide);

    // Tests a case that used to cause negative anchor position when turning into placeholder
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dropArea = m->dropArea();
    MultiSplitterLayout *layout = dropArea->multiSplitterLayout();

    int i = 0;
    for (DockDescriptor &desc : docksToCreate) {
        desc.createdDock = createDockWidget(QString("%1").arg(i), new QPushButton(QString("%1").arg(i)), {}, false);

        DockWidgetBase *relativeTo = nullptr;
        if (desc.relativeToIndex != -1)
            relativeTo = docksToCreate.at(desc.relativeToIndex).createdDock;

        m->addDockWidget(desc.createdDock, desc.loc, relativeTo, desc.option);
        qDebug() << "Added" <<i;
        layout->checkSanity();
        ++i;
    }

    layout->checkSanity();

    // Run the saver in these complex scenarios:
    LayoutSaver saver;
    QVERIFY(saver.saveToDisk());
    QVERIFY(saver.restoreFromDisk());

    layout->checkSanity();

    for (int i : docksToHide) {
        docksToCreate.at(i).createdDock->close();
        layout->checkSanity();
        QTest::qWait(200);
    }

    layout->checkSanity();

    for (int i : docksToHide) {
        docksToCreate.at(i).createdDock->deleteLater();
        QVERIFY(waitForDeleted(docksToCreate.at(i).createdDock));
    }

    layout->checkSanity();

    // And hide the remaining ones
    i = 0;
    for (auto dock : docksToCreate) {
        if (dock.createdDock && dock.createdDock->isVisible()) {
            qDebug() << "Closing" << i << dock.createdDock->title();
            dock.createdDock->close();
            QTest::qWait(200); // Wait for the docks to be closed. TODO Replace with a global event filter and wait for any resize ?
        }
        ++i;
    }

    layout->checkSanity();

    // Cleanup
    for (auto dock : DockRegistry::self()->dockwidgets()) {
        qDebug() << "Deleting" << dock->title();
        dock->deleteLater();
        QVERIFY(waitForDeleted(dock));
    }
}

void TestDocks::tst_invalidAnchorGroup()
{
    // Tests a bug I got. Should not warn.
    EnsureTopLevelsDeleted e;

    {
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));

        QPointer<FloatingWindow> fw = dock2->morphIntoFloatingWindow();
        nestDockWidget(dock1, fw->dropArea(), nullptr, KDDockWidgets::Location_OnTop);

        dock1->close();
        waitForResize(dock2);
        auto layout = fw->dropArea()->multiSplitterLayout();
        layout->checkSanity();

        dock2->close();
        dock1->deleteLater();
        dock2->deleteLater();
        waitForDeleted(dock1);
    }

    {
        // Stack 1, 2, 3, close 2, close 1

        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        auto dock3 = createDockWidget("dock3", new QPushButton("three"));

        m->addDockWidget(dock3, Location_OnTop);
        m->addDockWidget(dock2, Location_OnTop);
        m->addDockWidget(dock1, Location_OnTop);

        dock2->close();
        dock1->close();

        dock1->deleteLater();
        dock2->deleteLater();
        waitForDeleted(dock1);
    }
}

void TestDocks::tst_resizeViaAnchorsAfterPlaceholderCreation()
{
    EnsureTopLevelsDeleted e;

    // Stack 1, 2, 3, close 2, close 2
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        auto dock3 = createDockWidget("dock3", new QPushButton("three"));
        m->addDockWidget(dock3, Location_OnTop);
        m->addDockWidget(dock2, Location_OnTop);
        m->addDockWidget(dock1, Location_OnTop);

        dock2->close();
        waitForResize(dock3);

        MultiSplitterLayout *layout = m->multiSplitterLayout();
        QCOMPARE(layout->numVisibleAnchors(), 5);
        layout->checkSanity();

        // Cleanup:
        dock2->deleteLater();
        waitForDeleted(dock2);
    }

    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        auto dock3 = createDockWidget("dock3", new QPushButton("three"));
        auto dock4 = createDockWidget("dock4", new QPushButton("four"));
        m->addDockWidget(dock1, Location_OnRight);
        m->addDockWidget(dock2, Location_OnRight);
        m->addDockWidget(dock3, Location_OnRight);
        m->addDockWidget(dock4, Location_OnRight);

        MultiSplitterLayout *layout = m->multiSplitterLayout();

        Item *item1 = layout->itemForFrame(dock1->frame());
        Item *item2 = layout->itemForFrame(dock2->frame());
        Item *item3 = layout->itemForFrame(dock3->frame());
        Item *item4 = layout->itemForFrame(dock4->frame());

        Anchor *anchor = item1->anchorGroup().right;
        int boundToTheRight = layout->boundPositionForAnchor(anchor, Anchor::Side2);
        int expectedBoundToTheRight = layout->size().width() -
                                      Anchor::thickness(true) -
                                      3*Anchor::thickness(false) -
                                      item2->minLength(Qt::Vertical) -
                                      item3->minLength(Qt::Vertical) -
                                      item4->minLength(Qt::Vertical);

        QCOMPARE(boundToTheRight, expectedBoundToTheRight);
        qDebug() << "boundToRight="<< boundToTheRight;

        dock3->close();
        waitForResize(dock2);

        QVERIFY(!item1->isPlaceholder());
        QVERIFY(!item2->isPlaceholder());
        QVERIFY(item3->isPlaceholder());
        QVERIFY(!item4->isPlaceholder());

        QCOMPARE(item1->anchorGroup().right, item2->anchorGroup().left);
        QCOMPARE(item2->anchorGroup().right, item3->anchorGroup().left);
        QCOMPARE(item3->anchorGroup().right, item4->anchorGroup().left);

        boundToTheRight = layout->boundPositionForAnchor(anchor, Anchor::Side2);
        expectedBoundToTheRight = layout->size().width() -
                                  Anchor::thickness(true) -
                                  2*Anchor::thickness(false) -
                                  item2->minLength(Qt::Vertical) -
                                  item4->minLength(Qt::Vertical) ;

        qDebug() << "after close boundToRight="<< boundToTheRight << "; anchor=" << anchor;
        QCOMPARE(boundToTheRight, expectedBoundToTheRight);
        anchor->setPosition(boundToTheRight);
        layout->checkSanity();

        dock3->deleteLater();
        waitForDeleted(dock3);
    }
}

void TestDocks::tst_negativeAnchorPosition()
{
    // Tests that we don't hit:
    // void KDDockWidgets::Anchor::setPosition(int, KDDockWidgets::Anchor::SetPositionOptions) Negative position

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(1002, 806));

    auto w1 = new MyWidget2(QSize(104, 104));
    w1->resize(994, 718);
    auto w2 = new MyWidget2(QSize(133, 343));
    w2->resize(392, 362);
    auto w3 = new MyWidget2(QSize(133, 343));
    w3->resize(392, 362);

    MultiSplitterLayout *layout = m->multiSplitterLayout();

    auto d1 = createDockWidget("1", w1);
    auto d2 = createDockWidget("2", w2);
    auto d3 = createDockWidget("3", w3);

    m->addDockWidgetAsTab(d1);

    m->addDockWidget(d2, Location_OnTop);
    m->addDockWidget(d3, Location_OnTop);

    const int minHeight = layout->minimumSize().height();
    const int min1 = KDDockWidgets::widgetMinLength(d1->frame(), Qt::Horizontal);
    const int min2 = KDDockWidgets::widgetMinLength(d2->frame(), Qt::Horizontal);
    const int min3 = KDDockWidgets::widgetMinLength(d3->frame(), Qt::Horizontal);

    qDebug() << "MinSizes=" << min1 << min2 << min3 << minHeight;

    d2->close();

    waitForResize(d3);
    d2->show(); // Should not result in negative anchor positions (Test will fail due to a qWarning)
    waitForResize(d3);
    layout->checkSanity();

    d2->close();
    waitForResize(d3);
    layout->checkSanity();

    // Now resize the Window, after removing middle one
    const int availableToShrink = layout->size().height() - layout->minimumSize().height();
    layout->setContentLength(layout->length(Qt::Horizontal) - availableToShrink, Qt::Horizontal); // Should not warn about negative sizes

    d2->deleteLater();
    waitForDeleted(d2);
    layout->checkSanity();
}

void TestDocks::tst_negativeAnchorPosition2()
{
    // Tests that the "Out of bounds position" warning doesn't appear. Test will abort if yes.
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dropArea = m->dropArea();
    MultiSplitterLayout *layout = dropArea->multiSplitterLayout();

    auto dock1 = createDockWidget("1", new QPushButton("1"), {}, /*show=*/false);
    auto dock2 = createDockWidget("2", new QPushButton("2"), {}, /*show=*/false);
    auto dock3 = createDockWidget("3", new QPushButton("3"), {}, /*show=*/false);

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight, nullptr, AddingOption_StartHidden);
    m->addDockWidget(dock3, Location_OnRight);
    QCOMPARE(layout->placeholderCount(), 1);
    QCOMPARE(layout->count(), 3);

    dock1->setFloating(true);
    dock1->setFloating(false);
    dock2->deleteLater();
    layout->checkSanity();
    QVERIFY(waitForDeleted(dock2));
}

void TestDocks::tst_negativeAnchorPosition3()
{
    // 1. Another case, when floating a dock:
    EnsureTopLevelsDeleted e;
    QVector<DockDescriptor> docks = { {Location_OnLeft, -1, nullptr, AddingOption_None },
                                     {Location_OnRight, -1, nullptr, AddingOption_None },
                                     {Location_OnLeft, -1, nullptr, AddingOption_None },
                                     {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
                                     {Location_OnRight, -1, nullptr, AddingOption_None } };
    auto m = createMainWindow(docks);
    auto dropArea = m->dropArea();
    MultiSplitterLayout *layout = dropArea->multiSplitterLayout();
    layout->checkSanity();

    auto dock1 = docks.at(1).createdDock;
    auto dock3 = docks.at(3).createdDock;

    dock1->setFloating(true);

    dock1->deleteLater();
    dock3->deleteLater();
    layout->checkSanity();
    waitForDeleted(dock3);
}

void TestDocks::tst_negativeAnchorPosition4()
{
    // 1. Tests that we don't get a warning
    // Out of bounds position= -5 ; oldPosition= 0 KDDockWidgets::Anchor(0x55e726be9090, name = "left") KDDockWidgets::MainWindow(0x55e726beb8d0)
    EnsureTopLevelsDeleted e;
    QVector<DockDescriptor> docks = { { Location_OnLeft, -1, nullptr, AddingOption_StartHidden },
                                      { Location_OnTop, -1, nullptr, AddingOption_None },
                                      { Location_OnRight, -1, nullptr, AddingOption_None },
                                      { Location_OnLeft, -1, nullptr, AddingOption_None },
                                      { Location_OnRight, -1, nullptr, AddingOption_None } };

    auto m = createMainWindow(docks);
    auto dropArea = m->dropArea();
    MultiSplitterLayout *layout = dropArea->multiSplitterLayout();
    layout->checkSanity();

    auto dock1 = docks.at(1).createdDock;
    auto dock2 = docks.at(2).createdDock;
    dock2->setFloating(true);
    auto fw2 = dock2->floatingWindow();
    dropArea->multiSplitterLayout()->addWidget(fw2->dropArea(), Location_OnLeft, dock1->frame());
    dock2->setFloating(true);
    fw2 = dock2->floatingWindow();

    dropArea->multiSplitterLayout()->addWidget(fw2->dropArea(), Location_OnRight, dock1->frame());

    layout->checkSanity();
    docks.at(0).createdDock->deleteLater();
    docks.at(4).createdDock->deleteLater();
    waitForDeleted(docks.at(4).createdDock);
}

void TestDocks::tst_negativeAnchorPosition5()
{
    EnsureTopLevelsDeleted e;
    QVector<DockDescriptor> docks = {
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        };

    auto m = createMainWindow(docks);
    auto dropArea = m->dropArea();
    MultiSplitterLayout *layout = dropArea->multiSplitterLayout();
    layout->checkSanity();

    auto dock0 = docks.at(0).createdDock;
    auto dock1 = docks.at(1).createdDock;

    dock1->show();

    Item *item1  = layout->itemForFrame(dock1->frame());

    qDebug() << "contents size" << layout->size()
             << "; available=" << layout->availableLengthForOrientation(Qt::Horizontal)
             << "; item1.min=" << item1->minimumSize();

    dock0->show();
    layout->checkSanity();

    // Cleanup
    for (auto dock : DockRegistry::self()->dockwidgets())
        dock->deleteLater();

    QVERIFY(waitForDeleted(dock0));
}

void TestDocks::tst_negativeAnchorPosition6()
{
    // Tests a case when we add a widget to left/right but the layout doesn't have enough height (or vice-versa)
    EnsureTopLevelsDeleted e;

    auto m = new MainWindow("m1", MainWindowOption_None);
    m->resize(QSize(100, 100));
    m->show();

    auto layout = m->multiSplitterLayout();

    auto w1 = new MyWidget2(QSize(400,100));
    auto w2 = new MyWidget2(QSize(400,100));
    auto w3 = new MyWidget2(QSize(400,100));
    auto w4 = new MyWidget2(QSize(400,900));
    auto d1 = createDockWidget("1", w1);
    auto d2 = createDockWidget("2", w2);
    auto d3 = createDockWidget("3", w3);
    auto d4 = createDockWidget("4", w4);

    m->addDockWidget(d1, Location_OnBottom);
    m->addDockWidget(d2, Location_OnBottom);
    m->addDockWidget(d3, Location_OnBottom);

    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 0);

    m->addDockWidget(d4, Location_OnRight, d3);

    layout->checkSanity();


    Item *centralItem = m->dropArea()->centralFrame();
    layout->rectForDrop(d2, Location_OnTop, centralItem);
    layout->checkSanity();

    delete m->window();
}

void TestDocks::tst_negativeAnchorPosition7()
{
    EnsureTopLevelsDeleted e;
    auto m = new MainWindow("m1", MainWindowOption_None);
    m->show();
    auto w1 = new MyWidget2(QSize(400,400));
    auto w2 = new MyWidget2(QSize(400,400));

    auto d1 = new DockWidget("1");
    d1->setWidget(w1);
    auto d2 = new DockWidget("2");
    d2->setWidget(w2);

    auto w3 = new MyWidget2(QSize(100,100));
    auto d3 = new DockWidget("3");
    d3->setWidget(w3);

    // Stack 1, 2
    m->addDockWidget(d2, Location_OnTop);
    m->addDockWidget(d1, Location_OnTop);

     //auto layout = m->multiSplitterLayout();
     //layout->dumpDebug();

    // add a small one to the middle

    // Stack: 1, 3, 2
    m->addDockWidget(d3, Location_OnTop, d2);
    m->multiSplitterLayout()->checkSanity();

    delete m;
}

void TestDocks::tst_negativeAnchorPositionWhenEmbedded_data()
{
    QTest::addColumn<bool>("embedded");

     QTest::newRow("false") << false;
     QTest::newRow("true") << true;
}

void TestDocks::tst_negativeAnchorPositionWhenEmbedded()
{
    QFETCH(bool, embedded);
    EnsureTopLevelsDeleted e;

    MainWindow *m;

    if (embedded) {
        auto em = createEmbeddedMainWindow(QSize(500, 500));
        m = em->mainWindow;
    } else {
        m =new MainWindow("m1");
        m->resize(QSize(500, 500));
        m->show();
    }
    auto layout = m->multiSplitterLayout();

    auto w1 = new MyWidget2(QSize(400,400));
    auto w2 = new MyWidget2(QSize(400,400));
    auto d1 = createDockWidget("1", w1);
    auto d2 = createDockWidget("2", w2);
    auto d3 = createDockWidget("3", w2);

    m->addDockWidget(d1, Location_OnLeft);
    m->addDockWidget(d2, Location_OnLeft);
    m->addDockWidget(d3, Location_OnLeft);

    layout->checkSanity();

    delete m->window();
}

void TestDocks::tst_tabBarWithHiddenTitleBar_data()
{
    QTest::addColumn<bool>("hiddenTitleBar");
    QTest::addColumn<bool>("tabsAlwaysVisible");

    QTest::newRow("false-false") << false << false;
    QTest::newRow("true-false") << true << false;

    QTest::newRow("false-true") << false << true;
    QTest::newRow("true-true") << true << true;

}

void TestDocks::tst_tabBarWithHiddenTitleBar()
{
    EnsureTopLevelsDeleted e;
    QFETCH(bool, hiddenTitleBar);
    QFETCH(bool, tabsAlwaysVisible);

    const auto originalFlags = Config::self().flags();

    auto newFlags = originalFlags;

    if (hiddenTitleBar)
        newFlags = newFlags | Config::Flag_HideTitleBarWhenTabsVisible;

    if (tabsAlwaysVisible)
        newFlags = newFlags | Config::Flag_AlwaysShowTabs;


    Config::self().setFlags(newFlags);

    auto m = createMainWindow();

    auto d1 = createDockWidget("1", new QTextEdit());
    auto d2 = createDockWidget("2", new QTextEdit());
    m->addDockWidget(d1, Location_OnTop);

    if (tabsAlwaysVisible) {
        if (hiddenTitleBar)
            QVERIFY(!d1->frame()->titleBar()->isVisible());
        else
            QVERIFY(d1->frame()->titleBar()->isVisible());
    } else {
        QVERIFY(d1->frame()->titleBar()->isVisible());
    }

    d1->addDockWidgetAsTab(d2);

    QVERIFY(d2->frame()->titleBar()->isVisible() ^ hiddenTitleBar);

    d2->close();
    m->multiSplitterLayout()->checkSanity();
    delete d2;
    if (tabsAlwaysVisible) {
        if (hiddenTitleBar)
            QVERIFY(!d1->frame()->titleBar()->isVisible());
        else
            QVERIFY(d1->frame()->titleBar()->isVisible());
    } else {
        QVERIFY(d1->frame()->titleBar()->isVisible());
    }
}

void TestDocks::tst_dragByTabBar_data()
{
    QTest::addColumn<bool>("documentMode");

    QTest::newRow("false") << false;
    QTest::newRow("true") << true;
}

void TestDocks::tst_dragByTabBar()
{
    QFETCH(bool, documentMode);

    EnsureTopLevelsDeleted e;
    Config::self().setFlags(Config::self().flags() | Config::Flag_HideTitleBarWhenTabsVisible);

    auto m = createMainWindow();

    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(400, 400)));

    auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(400, 400)));
    auto dock3 = createDockWidget("dock3", new MyWidget2(QSize(400, 400)));
    m->addDockWidgetAsTab(dock1);
    m->resize(osWindowMinWidth(), 200);

    dock2->addDockWidgetAsTab(dock3);
    if (documentMode)
        static_cast<QTabWidget*>(dock2->frame()->tabWidget()->asWidget())->setDocumentMode(true);

    auto fw = dock2->floatingWindow();
    fw->move(m->pos() + QPoint(500, 500));
    QVERIFY(fw->isVisible());
    QVERIFY(!fw->titleBar()->isVisible());

    dragFloatingWindowTo(fw, dropArea, DropIndicatorOverlayInterface::DropLocation_Right);
}

void TestDocks::tst_addToHiddenMainWindow()
{
    EnsureTopLevelsDeleted e;
    auto m = new MainWindow("m1");
    auto w1 = new MyWidget2(QSize(400,400));
    auto w2 = new MyWidget2(QSize(400,400));
    auto d1 = createDockWidget("1", w1);
    auto d2 = createDockWidget("2", w2);

    m->addDockWidget(d1, Location_OnTop);
    m->addDockWidget(d2, Location_OnTop);

    QVERIFY(!m->isVisible());
    d1->setFloating(true);
    d2->setFloating(false);
    m->multiSplitterLayout()->checkSanity();

    delete m;
}

void TestDocks::tst_minSizeChanges()
{
    EnsureTopLevelsDeleted e;
    auto m = new MainWindow("m1", MainWindowOption_None);
    m->show();
    auto w1 = new MyWidget2(QSize(400,400));
    auto w2 = new MyWidget2(QSize(400,400));

    auto d1 = new DockWidget("1");
    d1->setWidget(w1);
    auto d2 = new DockWidget("2");
    d2->setWidget(w2);

    m->addDockWidget(d1, Location_OnTop);
    m->addDockWidget(d2, Location_OnTop, nullptr, AddingOption_StartHidden);
    auto layout = m->multiSplitterLayout();

    // 1. d2 is a placeholder, let's change its min size before showing it
    w2->setMinSize(QSize(800, 800));
    d2->show();

    Item *item1 = layout->itemForFrame(d1->frame());
    Item *item2 = layout->itemForFrame(d2->frame());

    layout->checkSanity();

    waitForResize(m);

    QVERIFY(item2->width() >= 800);
    QVERIFY(item2->height() >= 800);
    QVERIFY(m->height() >= 1200);

    // 2. d1 is visible, let's change its min size
    qDebug() << item1->minimumSize() << item1->size();
    w1->setMinSize(QSize(800, 800));

    waitForResize(m);
    layout->checkSanity();
    QVERIFY(m->height() >= 1600);

    // add a small one to the middle
    auto w3 = new MyWidget2(QSize(100,100));
    auto d3 = new DockWidget("3");
    d3->setWidget(w3);
    m->addDockWidget(d3, Location_OnTop, d1);

    delete m;
}

void TestDocks::tst_complex()
{
    // Tests some anchors out of bounds I got

    EnsureTopLevelsDeleted e;
    auto m = new MainWindow("m1", MainWindowOption_None);
    auto layout = m->multiSplitterLayout();
    m->resize(3266, 2239);

    DockWidget::List docks;

    QVector<KDDockWidgets::Location> locations = {Location_OnLeft, Location_OnLeft, Location_OnLeft,
                                                  Location_OnRight, Location_OnRight, Location_OnRight, Location_OnRight,
                                                  Location_OnBottom, Location_OnBottom, Location_OnBottom, Location_OnBottom, Location_OnBottom,
                                                  Location_OnBottom, Location_OnBottom, Location_OnBottom, Location_OnBottom, Location_OnBottom,
                                                  Location_OnBottom, Location_OnBottom, Location_OnBottom, Location_OnBottom
                                                  };

    QVector<KDDockWidgets::AddingOption> options = { AddingOption_None, AddingOption_None,
                                                    AddingOption_StartHidden, AddingOption_StartHidden,
                                                    AddingOption_None,
                                                    AddingOption_StartHidden, AddingOption_StartHidden,AddingOption_StartHidden, AddingOption_StartHidden,AddingOption_StartHidden, AddingOption_StartHidden,
                                                    AddingOption_None, AddingOption_None,
                                                    AddingOption_StartHidden, AddingOption_StartHidden,AddingOption_StartHidden, AddingOption_StartHidden,AddingOption_StartHidden, AddingOption_StartHidden,AddingOption_StartHidden, AddingOption_StartHidden
    };

    QVector<bool> floatings =  {true, false, true, false, false, false, false, false, false, false, false, false,
                               true, false, false, true, true, true, true, true, false };

    QVector<QSize> minSizes= {
        QSize(316, 219),
        QSize(355, 237),
        QSize(293, 66),
        QSize(158, 72),
        QSize(30, 141),
        QSize(104, 143),
        QSize(104, 105),
        QSize(84, 341),
        QSize(130, 130),
        QSize(404, 205),
        QSize(296, 177),
        QSize(914, 474),
        QSize(355, 237),
        QSize(104, 104),
        QSize(104, 138),
        QSize(1061, 272),
        QSize(165, 196),
        QSize(296, 177),
        QSize(104, 104),
        QSize(355, 237),
        QSize(104, 138)
    };

    const int num = 21;
    for (int i = 0; i < num; ++i) {
        auto widget = new MyWidget2(minSizes.at(i));
        auto dw = new DockWidget(QString::number(i));
        dw->setWidget(widget);
        docks << dw;
    }

    for (int i = 0; i < num; ++i) {
        m->addDockWidget(docks[i], locations[i], nullptr, options[i]);
        layout->checkSanity();

        QCOMPARE(layout->m_leftAnchor->cumulativeMinLength(Anchor::Side2), layout->minimumSize().width());
        QCOMPARE(layout->m_topAnchor->cumulativeMinLength(Anchor::Side2), layout->minimumSize().height());

        docks[i]->setFloating(floatings[i]);
        layout->checkSanity();
    }

    m->show();

    // Cleanup
    qDeleteAll(docks);
    qDeleteAll(DockRegistry::self()->frames());
    delete m;
}

void TestDocks::tst_titlebar_getter()
{
    EnsureTopLevelsDeleted e;
    auto m = new MainWindow("m1");
    m->resize(QSize(500, 500));
    m->show();

    auto w1 = new MyWidget2(QSize(400, 400));
    auto d1 = createDockWidget("1", w1);

    m->addDockWidget(d1, Location_OnTop);

    QVERIFY(d1->titleBar()->isVisible());
    d1->setFloating(true);
    QVERIFY(d1->floatingWindow());
    QVERIFY(d1->floatingWindow()->isVisible());
    QVERIFY(d1->titleBar()->isVisible());

    delete m;
}

void TestDocks::tst_staticAnchorThickness_data()
{
    QTest::addColumn<int>("thickness");
    QTest::newRow("2") << 2;
    QTest::newRow("1") << 1;
    QTest::newRow("0") << 0;
}

void TestDocks::tst_staticAnchorThickness()
{
    QFETCH(int, thickness);
    Config::self().setSeparatorThickness(thickness, true);

    auto m = new MainWindow("m1", MainWindowOption_None);
    m->resize(QSize(502, 500));
    m->show();

    auto d1 = createDockWidget("1", new QTextEdit());
    auto d2 = createDockWidget("2", new QTextEdit());

    m->addDockWidget(d1, Location_OnLeft);
    m->addDockWidget(d2, Location_OnRight);

    delete m;
}

void TestDocks::tst_rectForDropCrash()
{
    // Tests a crash I got in MultiSplitterLayout::rectForDrop() (asserts being hit)
    EnsureTopLevelsDeleted e;

    auto m = new MainWindow("m1");
    m->resize(QSize(500, 500));
    m->show();

    auto layout = m->multiSplitterLayout();

    auto w1 = new MyWidget2(QSize(400,400));
    auto w2 = new MyWidget2(QSize(400,400));
    auto d1 = createDockWidget("1", w1);
    auto d2 = createDockWidget("2", w2);

    m->addDockWidget(d1, Location_OnTop);
    Item *centralItem = m->dropArea()->centralFrame();
    layout->rectForDrop(d2, Location_OnTop, centralItem);
    layout->checkSanity();

    delete m->window();
}

void TestDocks::tst_availableSizeWithPlaceholders()
{
    // Tests MultiSplitterLayout::available() with and without placeholders. The result should be the same.

    EnsureTopLevelsDeleted e;
    QVector<DockDescriptor> docks1 = {
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        };

    QVector<DockDescriptor> docks2 = {
        {Location_OnBottom, -1, nullptr, AddingOption_None },
        {Location_OnBottom, -1, nullptr, AddingOption_None },
        {Location_OnBottom, -1, nullptr, AddingOption_None },
        };

    QVector<DockDescriptor> empty;

    auto m1 = createMainWindow(docks1);
    auto m2 = createMainWindow(docks2);
    auto m3 = createMainWindow(empty);

    auto layout1 = m1->multiSplitterLayout();
    auto layout2 = m2->multiSplitterLayout();
    auto layout3 = m3->multiSplitterLayout();

    auto f20 = docks2.at(0).createdDock->frame();

    docks2.at(0).createdDock->close();
    docks2.at(1).createdDock->close();
    docks2.at(2).createdDock->close();
    QVERIFY(waitForDeleted(f20));

    QCOMPARE(layout1->size(), layout2->size());
    QCOMPARE(layout1->size(), layout3->size());

    qDebug() << "CONTENTS SIZE" << layout1->size();
    QCOMPARE(layout1->availableSize(), layout2->availableSize());
    QCOMPARE(layout1->availableSize(), layout3->availableSize());

    // Now show 1 widget in m1 and m3
    docks1.at(0).createdDock->show();
    m3->addDockWidget(docks2.at(0).createdDock, Location_OnBottom); // just steal from m2

    QCOMPARE(layout1->size(), layout3->size());

    Frame *f10 = docks1.at(0).createdDock->frame();
    Item *item10 = layout1->itemForFrame(f10);
    Item *item30 = layout3->itemForFrame(docks2.at(0).createdDock->frame());

    // HACK: The Frame's have different minimum size than the Items as they're geometry change later
    // and the item isn't updated, so for the purpose of this test (available) we force the items
    // to have the same properties. TODO: Remove the restoreSizes once the Frame propagates its min size
    // to the item.
    item10->restoreSizes(item30->minimumSize(), item30->geometry());

    QCOMPARE(item10->geometry(), item30->geometry());
    QCOMPARE(item10->frame()->minimumSizeHint(), item10->frame()->minimumSizeHint());
    QCOMPARE(item10->minimumSize(), item30->minimumSize());
    QCOMPARE(layout1->availableSize(), layout3->availableSize());

    layout1->checkSanity();
    layout2->checkSanity();
    layout3->checkSanity();

    // Cleanup
    docks1.at(0).createdDock->deleteLater();
    docks1.at(1).createdDock->deleteLater();
    docks1.at(2).createdDock->deleteLater();
    docks2.at(0).createdDock->deleteLater();
    docks2.at(1).createdDock->deleteLater();
    docks2.at(2).createdDock->deleteLater();
    QVERIFY(waitForDeleted(docks2.at(2).createdDock));
}

void TestDocks::tst_anchorFollowingItselfAssert()
{
    // 1. Tests that we don't assert in Anchor::setFollowee()
    //  ASSERT: "this != m_followee" in file ../src/multisplitter/Anchor.cpp
    EnsureTopLevelsDeleted e;
    QVector<DockDescriptor> docks = {
        {Location_OnLeft, -1, nullptr, AddingOption_StartHidden },
        {Location_OnTop, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_None },
        {Location_OnLeft, -1, nullptr, AddingOption_None },
        {Location_OnRight, -1, nullptr, AddingOption_StartHidden },
        {Location_OnRight, -1, nullptr, AddingOption_None } };

    auto m = createMainWindow(docks);
    auto dropArea = m->dropArea();
    MultiSplitterLayout *layout = dropArea->multiSplitterLayout();
    layout->checkSanity();

    auto dock1 = docks.at(1).createdDock;
    auto dock2 = docks.at(2).createdDock;
    dock2->setFloating(true);
    auto fw2 = dock2->floatingWindow();
    dropArea->multiSplitterLayout()->addWidget(fw2->dropArea(), Location_OnLeft, dock1->frame());
    dock2->setFloating(true);
    fw2 = dock2->floatingWindow();
    dropArea->multiSplitterLayout()->addWidget(fw2->dropArea(), Location_OnRight, dock1->frame());

    docks.at(0).createdDock->deleteLater();
    docks.at(4).createdDock->deleteLater();
    waitForDeleted(docks.at(4).createdDock);
}

void TestDocks::tst_positionWhenShown()
{
    // Tests that when showing a dockwidget it shows in the same position as before
    EnsureTopLevelsDeleted e;
    auto window = createMainWindow();
    auto dock1 = new DockWidget("1");
    dock1->show();
    dock1->window()->move(100, 100);
    QCOMPARE(dock1->window()->pos(), QPoint(100, 100));

    dock1->close();
    dock1->show();
    QCOMPARE(dock1->window()->pos(), QPoint(100, 100));

    window->multiSplitterLayout()->checkSanity();

    // Cleanup
    dock1->deleteLater();
    QVERIFY(waitForDeleted(dock1));
}

void TestDocks::tst_sizeConstraintWarning()
{
    // Tests that we don't get the warning: MultiSplitterLayout::checkSanity: Widget has height= 122 but minimum is 144 KDDockWidgets::Item
    // Code autogenerated by the fuzzer:
    EnsureTopLevelsDeleted e;
    SetExpectedWarning sew("Dock widget already exists in the layout");

    auto window = createMainWindow();
    QList<DockWidgetBase *> listDockWidget;
    {
       auto dock = new DockWidget("foo-0");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-1");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-2");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-3");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-4");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-5");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-6");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-7");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-8");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-9");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-10");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-11");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-12");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-13");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-14");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-15");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-16");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-17");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidget("foo-18");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }

    auto dropArea = window->dropArea();
    window->addDockWidget(listDockWidget.at(0), static_cast<Location>(2));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(1), static_cast<Location>(1));
    dropArea->checkSanity();

    listDockWidget.at(2 - 1)->addDockWidgetAsTab(listDockWidget.at(2));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(3-1), static_cast<Location>(2), listDockWidget.at(3), static_cast<AddingOption>(1));
    dropArea->checkSanity();

    listDockWidget.at(4 - 1)->addDockWidgetAsTab(listDockWidget.at(4));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(5), static_cast<Location>(1));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(6), static_cast<Location>(1));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(7), static_cast<Location>(4));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(8-1), static_cast<Location>(1), listDockWidget.at(8), static_cast<AddingOption>(1));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(9), static_cast<Location>(2));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(10-1), static_cast<Location>(2), listDockWidget.at(10), static_cast<AddingOption>(1));
    dropArea->checkSanity();

    listDockWidget.at(11 - 1)->addDockWidgetAsTab(listDockWidget.at(11));
    dropArea->checkSanity();

    listDockWidget.at(12 - 1)->addDockWidgetAsTab(listDockWidget.at(12));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(13), static_cast<Location>(4));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(14), static_cast<Location>(2));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(15), static_cast<Location>(3));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(16), static_cast<Location>(4));
    dropArea->checkSanity();

    listDockWidget.at(17 - 1)->addDockWidgetAsTab(listDockWidget.at(17));
    dropArea->checkSanity();
    listDockWidget.at(18 - 1)->addDockWidgetAsTab(listDockWidget.at(18));
    dropArea->checkSanity();

    auto docks = DockRegistry::self()->dockwidgets();
    auto lastDock = docks.last();
    for (auto dock: docks)
        dock->deleteLater();

    waitForDeleted(lastDock);
}

void TestDocks::tst_invalidLayoutAfterRestore()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
    auto dock3 = createDockWidget("dock3", new QPushButton("three"));
    auto dropArea = m->dropArea();
    MultiSplitterLayout *layout = dropArea->multiSplitterLayout();
    // Stack 1, 2, 3
    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);

    Anchor *rightAnchor = layout->staticAnchorGroup().right;
    const int oldRightAnchorPos = rightAnchor->position();
    const int oldContentsWidth = layout->width();

    auto f1 = dock1->frame();
    dock3->close();
    dock2->close();
    dock1->close();
    QVERIFY(waitForDeleted(f1));

    dock3->show();
    dock2->show();
    dock1->show();
    waitForEvent(m.get(), QEvent::LayoutRequest); // So MainWindow min size is updated

    Item *item1 = layout->itemForFrame(dock1->frame());
    Item *item2 = layout->itemForFrame(dock2->frame());
    Item *item3 = layout->itemForFrame(dock3->frame());
    Item *item4 = dropArea->centralFrame();
    const int oldAvailableWidth = layout->availableLengthForOrientation(Qt::Vertical);

    qDebug() << "; Item3 min=" << item3->minimumSize().width()
             << "; Item2 min=" << item2->minimumSize().width()
             << "; Item1 min=" << item1->minimumSize().width()
             << "; Item4 min=" << item4->minimumSize().width()
             << "; oldAvailableWidth=" << oldAvailableWidth
             << "; old window.minWidth=" << layout->minimumSize().width();

    qDebug() << "Item3 width=" << item3->width()
             << "Item2 width=" << item2->width();

    QCOMPARE(layout->count(), 4);
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->numAchorsFollowing(), 0);

    // Detach dock2
    QPointer<Frame> f2 = dock2->frame();
    f2->m_tabWidget->detachTab(dock2);
    QVERIFY(!f2.data());
    QTest::qWait(200); // Not sure why. Some event we're waiting for. TODO: Investigate
    auto fw2 = dock2->floatingWindow();
    const int newAvailableWidth = layout->availableLengthForOrientation(Qt::Vertical);
    QCOMPARE(layout->minimumSize().width(), 2*Anchor::thickness(true) + 2*Anchor::thickness(false) + item1->minimumSize().width() + item3->minimumSize().width() + item4->minimumSize().width());

    MultiSplitterLayout::Length availableForDock2 = layout->availableLengthForDrop(Location_OnLeft, item3);

    qDebug() << "Item3 width after=" << item3->width()
             << "; newAvailableWidth=" << newAvailableWidth
             << "; new window.minWidth=" << layout->minimumSize().width()
             << "; availableforDock2=" << availableForDock2.length()
             << availableForDock2.side1Length << availableForDock2.side2Length;

    const int item3AvailableSqueeze = item3->width() - item3->minimumSize().width();
    QVERIFY(availableForDock2.side2Length <= item3AvailableSqueeze);


    // Drop left of dock3
    layout->addWidget(fw2->dropArea(), Location_OnLeft, dock3->frame());

    QVERIFY(waitForDeleted(fw2));
    QCOMPARE(rightAnchor->position(), oldRightAnchorPos);
    QCOMPARE(layout->width(), oldContentsWidth);
    layout->checkSanity();
}

void TestDocks::tst_stealFrame()
{
    // Tests using addWidget() with dock widgets which are already in a layout
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));

    auto m2 = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock3 = createDockWidget("dock3", new QPushButton("three"));
    auto dock4 = createDockWidget("dock4", new QPushButton("four"));

    auto dropArea1 = m1->dropArea();
    MultiSplitterLayout *layout1 = dropArea1->multiSplitterLayout();

    auto dropArea2 = m2->dropArea();
    MultiSplitterLayout *layout2 = dropArea2->multiSplitterLayout();

    m1->addDockWidget(dock1, Location_OnRight);
    m1->addDockWidget(dock2, Location_OnRight);
    m2->addDockWidget(dock3, Location_OnRight);
    m2->addDockWidget(dock4, Location_OnRight);

    // 1. MainWindow #1 steals a widget from MainWindow2 and vice-versa
    m1->addDockWidget(dock3, Location_OnRight);
    m1->addDockWidget(dock4, Location_OnRight);
    m2->addDockWidget(dock1, Location_OnRight);
    QPointer<Item> item2 = layout1->itemForFrame(dock2->frame());
    m2->addDockWidget(dock2, Location_OnRight);
    QVERIFY(!item2.data());

    QCOMPARE(layout1->count(), 2);
    QCOMPARE(layout2->count(), 2);
    QCOMPARE(layout1->placeholderCount(), 0);
    QCOMPARE(layout2->placeholderCount(), 0);

    // 2. MainWindow #1 steals a widget from MainWindow2 and vice-versa, but adds as tabs
    dock1->addDockWidgetAsTab(dock3);
    QPointer<Frame> f2 = dock2->frame();
    dock4->addDockWidgetAsTab(dock2);
    QVERIFY(!f2.data());

    QCOMPARE(layout1->count(), 1);
    QCOMPARE(layout2->count(), 1);
    QCOMPARE(layout1->placeholderCount(), 0);
    QCOMPARE(layout2->placeholderCount(), 0);

    // 3. Test stealing a tab from the same tab-widget we're in. Nothing happens
    {
        SetExpectedWarning sew("Already contains KDDockWidgets::DockWidget"); // Suppress the qFatal this time
        dock1->addDockWidgetAsTab(dock3);
        QCOMPARE(dock1->frame()->dockWidgetCount(), 2);
    }

    // 4. Steal from another tab which resides in another Frame, which resides in the same main window
    m1->addDockWidget(dock1, Location_OnTop);
    f2 = dock2->frame();
    dock1->addDockWidgetAsTab(dock2);
    QCOMPARE(dock1->frame()->dockWidgetCount(), 2);
    QCOMPARE(dock4->frame()->dockWidgetCount(), 1);

    QCOMPARE(layout1->count(), 2);
    QCOMPARE(layout1->placeholderCount(), 0);

    // 5. And also steal a side-by-side one into the tab
    QPointer<Frame> f4 = dock4->frame();
    dock1->addDockWidgetAsTab(dock4);
    QVERIFY(!f4);
    QCOMPARE(layout1->count(), 1);
    QCOMPARE(layout1->placeholderCount(), 0);

    // 6. Steal from tab to side-by-side within the same MainWindow
    m1->addDockWidget(dock1, Location_OnLeft);
    QCOMPARE(layout1->count(), 2);
    QCOMPARE(layout1->placeholderCount(), 0);

    // 6. side-by-side to side-by-side within same MainWindow
    m2->addDockWidget(dock1, Location_OnRight);
    QCOMPARE(layout2->count(), 2);
    QCOMPARE(layout2->placeholderCount(), 0);

    {
        SetExpectedWarning sew("Invalid parameters KDDockWidgets::DockWidget"); // Suppress the qFatal this time
        m2->addDockWidget(dock1, Location_OnLeft, dock1);
        QCOMPARE(layout2->count(), 2);  // Nothing happened
        QCOMPARE(layout2->placeholderCount(), 0);
        QVERIFY(dock1->isVisible());
    }

    QVERIFY(dock1->isVisible());
    m2->addDockWidget(dock1, Location_OnLeft, nullptr); // Should not warn

    QVERIFY(dock1->isVisible());
    QCOMPARE(layout2->count(), 2);  // Nothing happened
    QCOMPARE(layout2->placeholderCount(), 0);

    m2->addDockWidget(dock1, Location_OnLeft, nullptr);
    QVERIFY(dock1->isVisible());
    QCOMPARE(layout2->count(), 2);  // Nothing happened
    QCOMPARE(layout2->placeholderCount(), 0);
    layout1->checkSanity();
    layout2->checkSanity();
}

void TestDocks::tst_addAsPlaceholder()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new QPushButton("one"), {}, false);
    auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, false);

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnTop, nullptr, AddingOption_StartHidden);

    auto dropArea = m->dropArea();
    MultiSplitterLayout *layout = dropArea->multiSplitterLayout();

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    QVERIFY(!dock2->isVisible());

    dock2->show();
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 0);

    layout->checkSanity();

    // Cleanup
    dock2->deleteLater();
    waitForDeleted(dock2);
}

void TestDocks::tst_removeItem()
{
    // Tests that MultiSplitterLayout::removeItem() works
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, false);
    auto dock3 = createDockWidget("dock3", new QPushButton("three"));

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnTop, nullptr, AddingOption_StartHidden);

    auto dropArea = m->dropArea();
    MultiSplitterLayout *layout = dropArea->multiSplitterLayout();

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    QCOMPARE(layout->numAchorsFollowing(), 1);

    // 1. Remove an item that's a placeholder
    Item *item2 = dock2->lastPosition()->layoutItem();
    layout->removeItem(item2);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->numAchorsFollowing(), 0);

    // 2. Remove an item that has an actual widget
    Item *item1 = dock1->lastPosition()->layoutItem();
    layout->removeItem(item1);
    QCOMPARE(layout->count(), 0);
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->numAchorsFollowing(), 0);


    // 3. Remove an item that has anchors following one of its other anchors (Tests that anchors stop following)
    // Stack 1, 2, 3
    m->addDockWidget(dock3, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnBottom);
    m->addDockWidget(dock1, Location_OnBottom);
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->numAchorsFollowing(), 0);

    qDebug() << "Closing... ";
    dock2->close();
    auto frame1 = dock1->frame();
    dock1->close();
    QVERIFY(waitForDeleted(frame1));

    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 2);
    QCOMPARE(layout->numAchorsFollowing(), 2);

    // Now remove the items
    layout->removeItem(dock2->lastPosition()->layoutItem());
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    QCOMPARE(layout->numAchorsFollowing(), 1);
    layout->checkSanity();
    layout->removeItem(dock1->lastPosition()->layoutItem());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->numAchorsFollowing(), 0);

    // Add again
    m->addDockWidget(dock2, Location_OnBottom);
    m->addDockWidget(dock1, Location_OnBottom);
    dock2->close();
    frame1 = dock1->frame();
    dock1->close();
    QVERIFY(waitForDeleted(frame1));

    // Now remove the items, but first dock1
    layout->removeItem(dock1->lastPosition()->layoutItem());
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    QCOMPARE(layout->numAchorsFollowing(), 1);
    layout->checkSanity();
    layout->removeItem(dock2->lastPosition()->layoutItem());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->numAchorsFollowing(), 0);
    layout->checkSanity();

    // Add again, stacked as 1, 2, 3, then close 2 and 3.
    m->addDockWidget(dock2, Location_OnTop);
    m->addDockWidget(dock1, Location_OnTop);

    auto frame2 = dock2->frame();
    dock2->close();
    waitForDeleted(frame2);

    auto frame3 = dock3->frame();
    dock3->close();
    waitForDeleted(frame3);

    // The second anchor is now following the 3rd, while the 3rd is following 'bottom'
    layout->removeItem(dock3->lastPosition()->layoutItem()); // will trigger the 3rd anchor to be removed
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    QCOMPARE(layout->numAchorsFollowing(), 1);
    layout->checkSanity();

    dock1->deleteLater();
    dock2->deleteLater();
    dock3->deleteLater();
    waitForDeleted(dock3);
}

void TestDocks::tst_startHidden()
{
    EnsureTopLevelsDeleted e;
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"), {}, false);
        auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, false);

        auto dropArea = m->dropArea();
        MultiSplitterLayout *layout = dropArea->multiSplitterLayout();

        m->addDockWidget(dock1, Location_OnTop, nullptr, AddingOption_StartHidden);

        QCOMPARE(layout->count(), 1);
        QCOMPARE(layout->placeholderCount(), 1);
        QCOMPARE(layout->numAchorsFollowing(), 0);

        m->addDockWidget(dock2, Location_OnTop);
        layout->checkSanity();

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 1);
        QCOMPARE(layout->numAchorsFollowing(), 1);

        dock1->show();

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);
        QCOMPARE(layout->numAchorsFollowing(), 0);

        waitForResize(dock2);
    }

    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"), {}, false);
        auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, false);
        auto dock3 = createDockWidget("dock3", new QPushButton("three"), {}, false);

        auto dropArea = m->dropArea();
        MultiSplitterLayout *layout = dropArea->multiSplitterLayout();
        m->addDockWidget(dock1, Location_OnLeft, nullptr, AddingOption_StartHidden);

        m->addDockWidget(dock2, Location_OnBottom, nullptr, AddingOption_StartHidden);
        m->addDockWidget(dock3, Location_OnRight, nullptr, AddingOption_StartHidden);


        Item *item1 = dock1->lastPosition()->layoutItem();
        Item *item2 = dock2->lastPosition()->layoutItem();
        Item *item3 = dock3->lastPosition()->layoutItem();

        qDebug() << item1 << item1->anchorGroup();
        qDebug() << item2 << item2->anchorGroup();
        qDebug() << item3 << item3->anchorGroup();
        QCOMPARE(layout->numAchorsFollowing(), 2);
        qDebug() << "About to show dock1";
        dock1->show();

        QCOMPARE(layout->count(), 3);
        QCOMPARE(layout->placeholderCount(), 2);
        QCOMPARE(layout->numAchorsFollowing(), 2);

        dock2->show();
        dock3->show();
        waitForResize(dock2);
        layout->checkSanity();
    }
}

void TestDocks::tst_startClosed()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));

    auto dropArea = m->dropArea();
    MultiSplitterLayout *layout = dropArea->multiSplitterLayout();

    m->addDockWidget(dock1, Location_OnTop);
    Frame *frame1 = dock1->frame();
    dock1->close();
    waitForDeleted(frame1);

    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 1);
    QCOMPARE(layout->numAchorsFollowing(), 0);

    m->addDockWidget(dock2, Location_OnTop);

    layout->checkSanity();

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    QCOMPARE(layout->numAchorsFollowing(), 1);

    dock1->show();
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->numAchorsFollowing(), 0);
}

void TestDocks::tst_samePositionAfterHideRestore()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    auto dock3 = createDockWidget("3", new QPushButton("3"));

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);
    QRect geo2 = dock2->frame()->geometry();
    dock2->setFloating(true);

    auto fw2 = dock2->floatingWindow();
    dock2->setFloating(false);
    QVERIFY(waitForDeleted(fw2));
    QCOMPARE(geo2, dock2->frame()->geometry());
    m->multiSplitterLayout()->checkSanity();
}

void TestDocks::tst_clear()
{
    // Tests MultiSplitterLayout::clear()
    EnsureTopLevelsDeleted e;
    QCOMPARE(Frame::dbg_numFrames(), 0);

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    auto dock3 = createDockWidget("3", new QPushButton("3"));
    auto fw3 = dock3->floatingWindow();

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);
    QVERIFY(waitForDeleted(fw3));
    dock3->close();

    QCOMPARE(Frame::dbg_numFrames(), 3);

    auto layout = m->multiSplitterLayout();
    layout->clear();

    QCOMPARE(layout->count(), 0);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();

    // Cleanup
    dock3->deleteLater();
    QVERIFY(waitForDeleted(dock3));
}

void TestDocks::tst_restoreEmbeddedMainWindow()
{
    EnsureTopLevelsDeleted e;
    // Tests a MainWindow which isn't a top-level window, but is embedded in another window
    EmbeddedWindow *window = createEmbeddedMainWindow(QSize(800, 800));

    auto dock1 = createDockWidget("1", new QPushButton("1"));
    window->mainWindow->addDockWidget(dock1, Location_OnTop);

    const QPoint originalPos(250, 250);
    const QSize originalSize = window->size();
    window->move(originalPos);

    LayoutSaver saver;
    QByteArray saved = saver.serializeLayout();
    QVERIFY(!saved.isEmpty());

    window->resize(555, 555);
    const QPoint newPos(500, 500);
    window->move(newPos);
    QVERIFY(saver.restoreLayout(saved));

    QCOMPARE(window->pos(), originalPos);
    QCOMPARE(window->size(), originalSize);
    window->mainWindow->multiSplitterLayout()->checkSanity();

    delete window;
}

void TestDocks::tst_restoreWithDockFactory()
{
    // Tests that restore the layout with a missing dock widget will recreate the dock widget using a factory

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);
    auto layout = m->multiSplitterLayout();

    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->visibleCount(), 1);

    LayoutSaver saver;
    QByteArray saved = saver.serializeLayout();
    QVERIFY(!saved.isEmpty());
    QPointer<Frame> f1 = dock1->frame();
    delete dock1;
    waitForDeleted(f1);
    QVERIFY(!f1);

    // Directly deleted don't leave placeolders. We could though.
    QCOMPARE(layout->count(), 0);

    {
        // We don't know how to create the dock widget
        SetExpectedWarning expectedWarning("Couldn't find dock widget");
        QVERIFY(saver.restoreLayout(saved));
        QCOMPARE(layout->count(), 0);
    }

    // Now try with a factory func
    DockWidgetFactoryFunc func = [] (const QString &) {
        return createDockWidget("1", new QPushButton("1"), {}, /*show=*/ false);
    };

    Config::self().setDockWidgetFactoryFunc(func);
    QVERIFY(saver.restoreLayout(saved));
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->visibleCount(), 1);
    layout->checkSanity();
}

void TestDocks::tst_resizeWindow_data()
{
    QTest::addColumn<bool>("doASaveRestore");
    QTest::newRow("false") << false;
    QTest::newRow("true") << true;
}

void TestDocks::tst_resizeWindow()
{
    QFETCH(bool, doASaveRestore);

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);

    auto layout = m->multiSplitterLayout();
    Item *item1 = layout->itemForFrame(dock1->frame());
    Anchor *anchor = item1->anchorGroup().right;

    // Move the separator so both dock widgets have the same space
    const int delta = dock1->width() - dock2->width();
    anchor->setPosition(anchor->position() - delta / 2);

    const int oldWidth1 = dock1->width();
    const int oldWidth2 = dock2->width();

    QVERIFY(oldWidth2 - oldWidth1 <= 1); // They're not equal if separator thickness if even

    if (doASaveRestore) {
        LayoutSaver saver;
        saver.restoreLayout(saver.serializeLayout());
    }

    m->showMaximized();
    QVERIFY(waitForResize(m.get()));

    const int maximizedWidth1 = dock1->width();
    const int maximizedWidth2 = dock2->width();

    const double relativeDifference = qAbs((maximizedWidth1 - maximizedWidth2) / (1.0 * layout->width()));

    qDebug() << oldWidth1 << oldWidth2 << maximizedWidth1 << maximizedWidth2 << relativeDifference;
    QVERIFY(relativeDifference <= 0.01);

    m->showNormal();
    QVERIFY(waitForResize(m.get()));

    const int newWidth1 = dock1->width();
    const int newWidth2 = dock2->width();

    QCOMPARE(oldWidth1, newWidth1);
    QCOMPARE(oldWidth2, newWidth2);
    layout->checkSanity();
}

void TestDocks::tst_resizeWindow2()
{
    // Tests that resizing the width of the main window will never move horizontal anchors

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    m->addDockWidget(dock1, Location_OnTop);
    m->addDockWidget(dock2, Location_OnBottom);

    auto layout = m->multiSplitterLayout();
    Item *item1 = layout->itemForFrame(dock1->frame());
    Anchor *anchor = item1->anchorGroup().bottom;

    m->resize(m->width() + 10, m->height());

    const int maxPos = layout->boundPositionForAnchor(anchor, Anchor::Side2);
    anchor->setPosition(maxPos);
    m->resize(m->width() + 10, m->height());

    QCOMPARE(anchor->position(), maxPos);
    layout->checkSanity();
}

// QTest::qWait(50000)

QTEST_MAIN(KDDockWidgets::TestDocks)
#include "tst_docks.moc"
