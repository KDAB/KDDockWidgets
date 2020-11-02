/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

#include "DockWidgetBase.h"
#include "MainWindow.h"
#include "FloatingWindow_p.h"
#include "DockRegistry_p.h"
#include "Frame_p.h"
#include "private/widgets/FrameWidget_p.h"
#include "private/widgets/TabWidgetWidget_p.h"
#include "private/widgets/TabWidget_p.h"
#include "DropArea_p.h"
#include "TitleBar_p.h"
#include "WindowBeingDragged_p.h"
#include "Utils_p.h"
#include "LayoutSaver.h"
#include "LayoutSaver_p.h"
#include "MultiSplitter_p.h"
#include "Position_p.h"
#include "utils.h"
#include "FrameworkWidgetFactory.h"
#include "DropAreaWithCentralFrame_p.h"
#include "Testing.h"
#include "DockWidget.h"
#include "SideBar_p.h"

#include <QtTest/QtTest>
#include <QPainter>
#include <QApplication>
#include <QTabBar>
#include <QAction>
#include <QTime>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QToolButton>
#include <QMenuBar>
#include <QStyleFactory>
#include <QCursor>
#include <QLineEdit>

#ifdef Q_OS_WIN
# include <Windows.h>
#endif

#ifdef KDDOCKWIDGETS_QTWIDGETS
# include <QPushButton>
#endif

#define WAIT QTest::qWait(5000000);

using namespace KDDockWidgets;
using namespace KDDockWidgets::Tests;
using namespace Layouting;

static QPoint dragPointForWidget(Frame *frame, int index)
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

inline int widgetMinLength(const QWidget *w, Qt::Orientation o)
{
    const QSize sz = Widget_qwidget::widgetMinSize(w);
    return o == Qt::Vertical ? sz.height() : sz.width();
}

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

namespace KDDockWidgets {

namespace {

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

class TestDocks : public QObject
{
    Q_OBJECT
public Q_SLOTS:
    void initTestCase()
    {
        qputenv("KDDOCKWIDGETS_SHOW_DEBUG_WINDOW", "");
        qApp->setOrganizationName("KDAB");
        qApp->setApplicationName("dockwidgets-unit-tests");

        qApp->setStyle(QStyleFactory::create("fusion"));

        Testing::installFatalMessageHandler();

        auto m = createMainWindow();
        QTest::qWait(10); // the DND state machine needs the event loop to start, otherwise activeState() is nullptr. (for offscreen QPA)
    }

private Q_SLOTS:
    void tst_mainWindowAlwaysHasCentralWidget();
    void tst_dock2FloatingWidgetsTabbed();
    void tst_close();
    void tst_propagateSizeHonoursMinSize();

    void tst_addDockWidgetAsTabToDockWidget();
    void tst_addToSmallMainWindow6();

    void tst_constraintsAfterPlaceholder();
    void tst_negativeAnchorPositionWhenEmbedded_data();
    void tst_negativeAnchorPositionWhenEmbedded();
    void tst_sizeConstraintWarning();
    void tst_restoreSimple();
    void tst_invalidLayoutAfterRestore();

    void tst_dragByTabBar_data();
    void tst_dragByTabBar();
    void tst_dragBySingleTab();

    void tst_addToHiddenMainWindow();
    void tst_minSizeChanges();
    void tst_complex();
    void tst_titlebar_getter();
    void tst_dockNotFillingSpace();
    void tst_addingOptionHiddenTabbed();
    void tst_flagDoubleClick();
    void tst_floatingWindowDeleted();
    void tst_raise();
    void tst_floatingAction();
    void tst_dockableMainWindows();
    void tst_lastFloatingPositionIsRestored();
    void tst_maxSizeHonouredWhenAnotherDropped();
    void tst_maxSizedHonouredAfterRemoved();
    void tst_maximumSizePolicy();
    void tst_tabsNotClickable();
    void tst_stuckSeparator();
    void tst_titleBarFocusedWhenTabsChange();

private:
    std::unique_ptr<MultiSplitter> createMultiSplitterFromSetup(MultiSplitterSetup setup, QHash<QWidget *, Frame *> &frameMap) const;
};
}

Frame* createFrameWithWidget(const QString &name, MultiSplitter *parent, int minLength = -1)
{
    QWidget *w = createWidget(minLength, name);
    auto dw = new DockWidgetType(name);
    dw->setWidget(w);
    auto frame =KDDockWidgets::Config::self().frameworkWidgetFactory()->createFrame(parent);
    frame->addWidget(dw);
    return frame;
}

DockWidgetBase *createAndNestDockWidget(DropArea *dropArea, Frame *relativeTo, KDDockWidgets::Location location)
{
    static int count = 0;
    count++;
    const QString name = QString("dock%1").arg(count);
    auto dock = createDockWidget(name, Qt::red);
    dock->setObjectName(name);
    nestDockWidget(dock, dropArea, relativeTo, location);
    dropArea->checkSanity();
    return dock;
}

std::unique_ptr<MainWindowBase> createSimpleNestedMainWindow(DockWidgetBase * *centralDock, DockWidgetBase * *leftDock, DockWidgetBase * *rightDock)
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

    QVERIFY(Testing::waitForDeleted(frame1));

    // 2.3 Detach tab1 to empty space
    QPoint globalPressPos = dragPointForWidget(frame2.data(), 0);
    QTabBar *tabBar = static_cast<FrameWidget*>(frame2.data())->tabBar();
    QVERIFY(tabBar);
    drag(tabBar, globalPressPos, frame2->window()->geometry().bottomRight() + QPoint(10, 10));

    QVERIFY(frame2->dockWidgetCount() == 1);
    QVERIFY(dock1->floatingWindow());

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

    QVERIFY(Testing::waitForDeleted(frame1));
    QVERIFY(Testing::waitForDeleted(frame2));
    QVERIFY(dock3->frame());
    QCOMPARE(dock3->frame()->dockWidgetCount(), 3);

    auto fw3 = dock3->floatingWindow();
    QVERIFY(fw3);
    QVERIFY(fw3->dropArea()->checkSanity());

    // 2.7 Drop the window into a MainWindow
    {
        MainWindow m("MyMainWindow_tst_dock2FloatingWidgetsTabbed", MainWindowOption_HasCentralFrame);
        m.show();
        m.setGeometry(500, 300, 300, 300);
        QVERIFY(!dock3->isFloating());
        auto fw3 = dock3->floatingWindow();
        drag(fw3->titleBar(), dock3->window()->mapToGlobal(QPoint(10, 10)), m.geometry().center());
        QVERIFY(!dock3->isFloating());
        QVERIFY(qobject_cast<MainWindow *>(dock3->window()) == &m);
        QCOMPARE(dock3->frame()->dockWidgetCount(), 3);
        QVERIFY(m.dropArea()->checkSanity());

        delete dock1;
        delete dock2;
        delete dock3;
        QVERIFY(Testing::waitForDeleted(frame2));
        QVERIFY(Testing::waitForDeleted(fw3));
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
    auto fw = dock1->floatingWindow();
    QVERIFY(fw);
    QVERIFY(toggleAction->isChecked());
    QVERIFY(dock1->isVisible());
    QCOMPARE(dock1->window(), fw);
    QVERIFY(toggleAction->isChecked());

    // 1.2 Reshow with toggleAction instead
    QVERIFY(dock1->close());
    QVERIFY(!toggleAction->isChecked());
    QVERIFY(!dock1->isVisible());
    toggleAction->setChecked(true);
    QVERIFY(dock1->isVisible());

    // 1.3 Use hide() instead
    auto fw1 = dock1->floatingWindow();
    QVERIFY(fw1);

    dock1->close(); // TODO: Hide doesn't delete the FloatingWindow

    QVERIFY(Testing::waitForDeleted(fw1));
    QVERIFY(!dock1->isVisible());
    QVERIFY(!dock1->window()->isVisible());
    QCOMPARE(dock1->window(), dock1);
    QVERIFY(!toggleAction->isChecked());

    // 1.4 close a FloatingWindow, via DockWidget::close
    QPointer<FloatingWindow> window = dock1->morphIntoFloatingWindow();
    QPointer<Frame> frame1 = dock1->frame();
    QVERIFY(dock1->isVisible());
    QVERIFY(dock1->window()->isVisible());
    QVERIFY(frame1->QWidgetAdapter::isVisible());
    QCOMPARE(dock1->window(), window.data());

    QVERIFY(dock1->close());
    QVERIFY(!dock1->frame());
    QVERIFY(Testing::waitForDeleted(frame1));
    QVERIFY(Testing::waitForDeleted(window));

    // 1.5 close a FloatingWindow, via FloatingWindow::close
    dock1->show();

    window = dock1->morphIntoFloatingWindow();
    frame1 = dock1->frame();
    QVERIFY(dock1->isVisible());
    QVERIFY(dock1->window()->isVisible());
    QVERIFY(frame1->QWidgetAdapter::isVisible());
    QCOMPARE(dock1->window(), window.data());

    QVERIFY(window->close());

    QVERIFY(!dock1->frame());
    QVERIFY(Testing::waitForDeleted(frame1));
    QVERIFY(Testing::waitForDeleted(window));

    // TODO: 1.6 Test FloatingWindow with two frames
    // TODO: 1.7 Test Frame with two tabs

    // 1.8 Check if space is reclaimed after closing left dock
    DockWidgetBase *centralDock;
    DockWidgetBase *leftDock;
    DockWidgetBase *rightDock;

    auto mainwindow = createSimpleNestedMainWindow(&centralDock, &leftDock, &rightDock);
    auto da = mainwindow->dropArea();

    QVERIFY(da->checkSanity());
    QCOMPARE(leftDock->frame()->QWidgetAdapter::x(), 0);

    QCOMPARE(centralDock->frame()->QWidgetAdapter::x(), leftDock->frame()->QWidgetAdapter::geometry().right() + Item::separatorThickness + 1);
    QCOMPARE(rightDock->frame()->QWidgetAdapter::x(), centralDock->frame()->QWidgetAdapter::geometry().right() + Item::separatorThickness + 1);
    leftDock->close();
    QTest::qWait(250); // TODO: wait for some signal
    QCOMPARE(centralDock->frame()->QWidgetAdapter::x(), 0);
    QCOMPARE(rightDock->frame()->QWidgetAdapter::x(), centralDock->frame()->QWidgetAdapter::geometry().right() + Item::separatorThickness + 1);

    rightDock->close();
    QTest::qWait(250); // TODO: wait for some signal
    auto lay = mainwindow->centralWidget()->layout();
    QMargins margins = lay->contentsMargins();
    QCOMPARE(centralDock->frame()->width(), mainwindow->width() - 0*2 - margins.left() - margins.right());
    delete leftDock; delete rightDock; delete centralDock;

    // 1.9 Close tabbed dock, side docks will maintain their position
    mainwindow = createSimpleNestedMainWindow(&centralDock, &leftDock, &rightDock);
    const int leftX = leftDock->frame()->QWidgetAdapter::x();
    const int rightX = rightDock->frame()->QWidgetAdapter::x();

    centralDock->close();

    QCOMPARE(leftDock->frame()->QWidgetAdapter::x(), leftX);
    QCOMPARE(rightDock->frame()->QWidgetAdapter::x(), rightX);
    delete leftDock; delete rightDock; delete centralDock;
    delete dock1;


    // 2. Test that closing the single frame of a main window doesn't close the main window itself
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
        QPointer<MainWindowBase> mainWindowPtr = m.get();
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
        QPointer<MainWindowBase> mainWindowPtr = m.get();
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
        QPointer<MainWindowBase> mainWindowPtr = m.get();
        dock1 = createDockWidget("hello", Qt::green);
        m->addDockWidget(dock1, Location_OnLeft);

        // 2.2 Closing should not close the main window
        dock1->frame()->titleBar()->onCloseClicked();
        QVERIFY(mainWindowPtr.data());
        QVERIFY(mainWindowPtr->isVisible());
        delete dock1;
    }
}

void TestDocks::tst_mainWindowAlwaysHasCentralWidget()
{
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();
    QTest::qWait(10); // the DND state machine needs the event loop to start, otherwise activeState() is nullptr. (for offscreen QPA)

    QWidget *central = m->centralWidget();
    auto dropArea = m->dropArea();
    QVERIFY(dropArea);

    QPointer<Frame> centralFrame = static_cast<Frame*>(dropArea->centralFrame()->guestAsQObject());
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
    qDebug() << "Detaching tab from dropArea->size=" << dropArea->QWidget::size() << "; dropArea=" << dropArea;
    drag(tabBar, globalPressPos, m->geometry().bottomRight() + QPoint(30, 30));

    QVERIFY(centralFrame);
    QCOMPARE(dropArea->count(), 1);
    QCOMPARE(centralFrame->dockWidgetCount(), 0);
    QVERIFY(dropArea->checkSanity());

    delete dock->window();
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
    int min1 = widgetMinLength(dock1, Qt::Horizontal);
    int min2 = widgetMinLength(dock2, Qt::Horizontal);

    QVERIFY(dock1->width() >= min1);
    QVERIFY(dock2->width() >= min2);

    nestDockWidget(dock1, dropArea, nullptr, KDDockWidgets::Location_OnRight);
    nestDockWidget(dock2, dropArea, nullptr, KDDockWidgets::Location_OnLeft);

    // Calculate again, as the window frame has disappeared
    min1 = widgetMinLength(dock1, Qt::Horizontal);
    min2 = widgetMinLength(dock2, Qt::Horizontal);

    auto l = m->dropArea();
    l->checkSanity();

    if (dock1->width() < min1) {
        qDebug() << "\ndock1->width()=" << dock1->width() << "\nmin1=" << min1
                 << "\ndock min sizes=" << dock1->minimumWidth() << dock1->minimumSizeHint().width()
                 << "\nframe1->width()=" << dock1->frame()->width()
                 << "\nframe1->min=" << widgetMinLength(dock1->frame(), Qt::Horizontal);
        l->dumpLayout();
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

    min1 = widgetMinLength(dock1, Qt::Vertical);
    QVERIFY(dock1->height() >= min1);
}

void TestDocks::tst_restoreSimple()
{
    EnsureTopLevelsDeleted e;
    // Tests restoring a very simple layout, composed of just 1 docked widget

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto layout = m->multiSplitter();
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
    QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreSimple.json")));
    auto f1 = dock1->frame();
    dock2->window()->move(QPoint(0, 0)); // Move *after* we saved.
    dock3->window()->move(QPoint(0, 0)); // Move *after* we saved.
    dock1->close();
    dock2->close();
    QVERIFY(!dock2->isVisible());
    QCOMPARE(layout->count(), 1);
    QVERIFY(Testing::waitForDeleted(f1));
    QCOMPARE(layout->placeholderCount(), 1);

    QCOMPARE(DockRegistry::self()->floatingWindows().size(), 0);
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreSimple.json")));
    QVERIFY(layout->checkSanity());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    QVERIFY(dock1->isVisible());
    QCOMPARE(saver.restoredDockWidgets().size(), 3);

    // Test a crash I got:
    dock1->setFloating(true);
    QVERIFY(layout->checkSanity());
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
    QVERIFY(Testing::waitForDeleted(dock3));
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
        Testing::waitForDeleted(dock2);
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
        Testing::waitForDeleted(dock2);
    }
    {
        // Dock a morphed dock widget into a morphed dock widget
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        dock1->morphIntoFloatingWindow();
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        dock2->morphIntoFloatingWindow();
        auto originalWindow2 = Tests::make_qpointer(dock2->window());

        dock1->addDockWidgetAsTab(dock2);

        QWidget *window1 = dock1->window();
        QWidget *window2 = dock2->window();
        QCOMPARE(window1, window2);
        QCOMPARE(dock1->frame(), dock2->frame());
        QCOMPARE(dock1->frame()->dockWidgetCount(), 2);
        Testing::waitForDeleted(originalWindow2);
        QVERIFY(!originalWindow2);
        dock1->deleteLater();
        dock2->deleteLater();
        Testing::waitForDeleted(dock2);
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

void TestDocks::tst_addToSmallMainWindow6()
{
    EnsureTopLevelsDeleted e;
    // Test test shouldn't spit any warnings

    QWidget container;
    auto lay = new QVBoxLayout(&container);
    MainWindow m("MyMainWindow_tst_addToSmallMainWindow8", MainWindowOption_None);
    lay->addWidget(&m);
    container.resize(100, 100);
    Testing::waitForResize(&container);
    container.show();
    Testing::waitForResize(&m);
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(50, 240)));
    auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(50, 240)));
    m.addDockWidget(dock1, KDDockWidgets::Location_OnBottom);
    m.addDockWidget(dock2, KDDockWidgets::Location_OnBottom);
    Testing::waitForResize(&m);
    QVERIFY(m.dropArea()->checkSanity());
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
    MultiSplitter *layout = dropArea;

    // Stack 3, 2, 1
    m->addDockWidget(dock1, Location_OnTop);
    m->addDockWidget(dock2, Location_OnTop);
    m->addDockWidget(dock3, Location_OnTop);

    QVERIFY(Testing::waitForResize(m.get()));

    QVERIFY(widgetMinLength(m.get(), Qt::Vertical) > minHeight * 3); // > since some vertical space is occupied by the separators

    // Now close dock1 and check again
    dock1->close();
    Testing::waitForResize(dock2);

    Item *item2 = layout->itemForFrame(dock2->frame());
    Item *item3 = layout->itemForFrame(dock3->frame());

    QMargins margins = m->centralWidget()->layout()->contentsMargins();
    const int expectedMinHeight = item2->minLength(Qt::Vertical) +
                                  item3->minLength(Qt::Vertical) +
                                  1 * Item::separatorThickness
                                  + margins.top() + margins.bottom();

    qDebug() << layout->rootItem()->minSize() << margins;

    QCOMPARE(m->minimumSizeHint().height(), expectedMinHeight);

    dock1->deleteLater();
    Testing::waitForDeleted(dock1);
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

    MainWindowBase *m;

    if (embedded) {
        auto em = createEmbeddedMainWindow(QSize(500, 500));
        m = em->mainWindow;
    } else {
        m = new MainWindow("m1", MainWindowOption_HasCentralFrame);
        m->resize(QSize(500, 500));
        m->show();
    }
    auto layout = m->multiSplitter();

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

void TestDocks::tst_dragByTabBar_data()
{
    QTest::addColumn<bool>("documentMode");
    QTest::addColumn<bool>("tabsAlwaysVisible");

    QTest::newRow("false-false") << false << false;
    QTest::newRow("true-false") << true << false;
    QTest::newRow("false-true") << false << true;
    QTest::newRow("true-true") << true << true;
}

void TestDocks::tst_dragByTabBar()
{
    QFETCH(bool, documentMode);
    QFETCH(bool, tabsAlwaysVisible);

    EnsureTopLevelsDeleted e;
    auto flags = Config::self().flags() | Config::Flag_HideTitleBarWhenTabsVisible;
    if (tabsAlwaysVisible)
        flags |= Config::Flag_AlwaysShowTabs;

    Config::self().setFlags(flags);

    auto m = createMainWindow();
    QTest::qWait(10); // the DND state machine needs the event loop to start, otherwise activeState() is nullptr. (for offscreen QPA)

    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(400, 400)));

    auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(400, 400)));
    auto dock3 = createDockWidget("dock3", new MyWidget2(QSize(400, 400)));
    m->addDockWidgetAsTab(dock1);
    m->resize(osWindowMinWidth(), 200);

    dock2->addDockWidgetAsTab(dock3);
    if (documentMode)
        static_cast<QTabWidget*>(static_cast<FrameWidget*>(dock2->frame())->tabWidget()->asWidget())->setDocumentMode(true);

    auto fw = dock2->floatingWindow();
    fw->move(m->pos() + QPoint(500, 500));
    QVERIFY(fw->isVisible());
    QVERIFY(!fw->titleBar()->isVisible());

    dragFloatingWindowTo(fw, dropArea, DropIndicatorOverlayInterface::DropLocation_Right);
}

void TestDocks::tst_dragBySingleTab()
{
    // Tests dragging via a tab when there's only 1 tab, and we're using Flag_AlwaysShowTabs
    EnsureTopLevelsDeleted e;
    Config::self().setFlags(Config::Flag_AlwaysShowTabs);
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(400, 400)));
    dock1->show();

    auto frame1 = dock1->frame();

    QPoint globalPressPos = dragPointForWidget(frame1, 0);
    QTabBar *tabBar = static_cast<FrameWidget*>(frame1)->tabBar();
    QVERIFY(tabBar);
    SetExpectedWarning sew("No window being dragged for"); // because dragging by tab does nothing in this case
    drag(tabBar, globalPressPos, QPoint(0, 0));

    delete dock1;
    Testing::waitForDeleted(frame1);
}

void TestDocks::tst_addToHiddenMainWindow()
{
    EnsureTopLevelsDeleted e;
    auto m = new MainWindow("m1", MainWindowOption_HasCentralFrame);
    auto w1 = new MyWidget2(QSize(400,400));
    auto w2 = new MyWidget2(QSize(400,400));
    auto d1 = createDockWidget("1", w1);
    auto d2 = createDockWidget("2", w2);

    m->addDockWidget(d1, Location_OnTop);
    m->addDockWidget(d2, Location_OnTop);

    QVERIFY(!m->isVisible());
    d1->setFloating(true);
    d2->setFloating(false);
    m->multiSplitter()->checkSanity();

    delete m;
}

void TestDocks::tst_minSizeChanges()
{
    EnsureTopLevelsDeleted e;
    auto m = new MainWindow("m1", MainWindowOption_None);
    m->show();
    auto w1 = new MyWidget2(QSize(400,400));
    auto w2 = new MyWidget2(QSize(400,400));

    auto d1 = new DockWidgetType("1");
    d1->setWidget(w1);
    auto d2 = new DockWidgetType("2");
    d2->setWidget(w2);

    m->addDockWidget(d1, Location_OnTop);
    m->addDockWidget(d2, Location_OnTop, nullptr, AddingOption_StartHidden);
    auto layout = m->multiSplitter();

    // 1. d2 is a placeholder, let's change its min size before showing it
    w2->setMinSize(QSize(800, 800));
    d2->show();

    Item *item1 = layout->itemForFrame(d1->frame());
    Item *item2 = layout->itemForFrame(d2->frame());

    QVERIFY(layout->checkSanity());

    Testing::waitForResize(m);

    qDebug() << item2->width();
    QVERIFY(item2->width() >= 800);
    QVERIFY(item2->height() >= 800);
    QVERIFY(m->height() >= 1200);

    // 2. d1 is visible, let's change its min size
    qDebug() << item1->minSize() << item1->size();
    w1->setMinSize(QSize(800, 800));

    Testing::waitForResize(m);
    layout->checkSanity();
    QVERIFY(m->height() >= 1600);

    // add a small one to the middle
    auto w3 = new MyWidget2(QSize(100,100));
    auto d3 = new DockWidgetType("3");
    d3->setWidget(w3);
    m->addDockWidget(d3, Location_OnTop, d1);

    delete m;
}

void TestDocks::tst_complex()
{
    // Tests some anchors out of bounds I got

    EnsureTopLevelsDeleted e;
    auto m = new MainWindow("m1", MainWindowOption_None);
    auto layout = m->multiSplitter();
    m->resize(3266, 2239);
    m->show(); // TODO: Remove and see if it crashes

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
        auto dw = new DockWidgetType(QString::number(i));
        dw->setWidget(widget);
        docks << dw;
    }

    for (int i = 0; i < num; ++i) {
        m->addDockWidget(docks[i], locations[i], nullptr, options[i]);
        layout->checkSanity();
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
    auto m = new MainWindow("m1", MainWindowOption_HasCentralFrame);
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

void TestDocks::tst_dockNotFillingSpace()
{
     EnsureTopLevelsDeleted e;
     auto m = new MainWindow("m1");
     m->resize(QSize(500, 500));
     m->show();

     auto d1 = createDockWidget("1", new QTextEdit());
     auto d2 = createDockWidget("2", new QTextEdit());
     auto d3 = createDockWidget("3", new QTextEdit());

     m->addDockWidget(d1, Location_OnTop);
     m->addDockWidget(d2, Location_OnBottom);
     m->addDockWidget(d3, Location_OnBottom);

     Frame *frame2 = d2->frame();
     d1->close();
     d2->close();
     Testing::waitForDeleted(frame2);

     auto layout = m->multiSplitter();
     QVERIFY(layout->checkSanity());

     delete d1;
     delete d2;
     delete m;
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
       auto dock = new DockWidgetType("foo-0");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-1");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-2");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-3");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-4");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-5");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-6");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-7");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-8");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-9");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-10");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-11");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-12");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-13");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-14");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-15");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-16");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-17");
       dock->setWidget(new QTextEdit(dock));
       listDockWidget.append(dock);
    }
    {
       auto dock = new DockWidgetType("foo-18");
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

    Testing::waitForDeleted(lastDock);
}

void TestDocks::tst_invalidLayoutAfterRestore()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
    auto dock3 = createDockWidget("dock3", new QPushButton("three"));
    auto dropArea = m->dropArea();
    MultiSplitter *layout = dropArea;
    // Stack 1, 2, 3
    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);

    const int oldContentsWidth = layout->width();

    auto f1 = dock1->frame();
    dock3->close();
    dock2->close();
    dock1->close();
    QVERIFY(Testing::waitForDeleted(f1));

    dock3->show();
    dock2->show();
    dock1->show();
    Testing::waitForEvent(m.get(), QEvent::LayoutRequest); // So MainWindow min size is updated

    Item *item1 = layout->itemForFrame(dock1->frame());
    Item *item3 = layout->itemForFrame(dock3->frame());
    Item *item4 = dropArea->centralFrame();

    QCOMPARE(layout->count(), 4);
    QCOMPARE(layout->placeholderCount(), 0);

    // Detach dock2
    QPointer<Frame> f2 = dock2->frame();
    f2->detachTab(dock2);
    QVERIFY(!f2.data());
    QTest::qWait(200); // Not sure why. Some event we're waiting for. TODO: Investigate
    auto fw2 = dock2->floatingWindow();
    QCOMPARE(layout->minimumSize().width(), 2*Item::separatorThickness + item1->minSize().width() + item3->minSize().width() + item4->minSize().width());

    // Drop left of dock3
    layout->addWidget(fw2->dropArea(), Location_OnLeft, dock3->frame());

    QVERIFY(Testing::waitForDeleted(fw2));
    QCOMPARE(layout->width(), oldContentsWidth);
    layout->checkSanity();
}

void TestDocks::tst_addingOptionHiddenTabbed()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    m->addDockWidget(dock1, Location_OnTop);

    QCOMPARE(dock1->frame()->dockWidgetCount(), 1);
    dock1->addDockWidgetAsTab(dock2, AddingOption_StartHidden);
    QCOMPARE(dock1->frame()->dockWidgetCount(), 1);
    dock2->show();
    QCOMPARE(dock1->frame()->dockWidgetCount(), 2);

    QVERIFY(dock1->frame() == dock2->frame());
}

void TestDocks::tst_flagDoubleClick()
{
    {
        EnsureTopLevelsDeleted e;
        Config::self().setFlags(Config::Flag_DoubleClickMaximizes);
        auto m = createMainWindow(QSize(500, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("1", new QPushButton("1"));
        auto dock2 = createDockWidget("2", new QPushButton("2"));
        m->addDockWidget(dock1, Location_OnTop);

        FloatingWindow *fw2 = dock2->floatingWindow();
        QVERIFY(!fw2->isMaximized());
        TitleBar *t2 = dock2->titleBar();
        QPoint pos = t2->mapToGlobal(QPoint(5, 5));
        Tests::doubleClickOn(pos, t2);
        QVERIFY(fw2->isMaximized());
        delete fw2;

        TitleBar *t1 = dock1->titleBar();
        QVERIFY(!t1->isFloating());
        pos = t1->mapToGlobal(QPoint(5, 5));
        Tests::doubleClickOn(pos, t1);
        QVERIFY(t1->isFloating());
        QVERIFY(!dock1->window()->isMaximized());
        delete dock1->window();
    }

    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(QSize(500, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("1", new QPushButton("1"));

        m->addDockWidget(dock1, Location_OnTop);

        TitleBar *t1 = dock1->titleBar();
        QVERIFY(!t1->isFloating());
        QPoint pos = t1->mapToGlobal(QPoint(5, 5));
        Tests::doubleClickOn(pos, t1);
        QVERIFY(t1->isFloating());
        QVERIFY(dock1->isFloating());
        QVERIFY(!dock1->window()->isMaximized());

        pos = t1->mapToGlobal(QPoint(5, 5));
        Tests::doubleClickOn(pos, t1);
        QVERIFY(!dock1->isFloating());
    }
}

void TestDocks::tst_floatingWindowDeleted()
{
    // Tests a case where the empty floating dock widget wouldn't be deleted
    // Doesn't repro QTBUG-83030 unfortunately, as we already have an event loop running
    // but let's leave this here nontheless
    class MyMainWindow : public KDDockWidgets::MainWindow {
    public:

        MyMainWindow()
            : KDDockWidgets::MainWindow("tst_floatingWindowDeleted", MainWindowOption_None)
        {
            auto dock1 = new KDDockWidgets::DockWidget(QStringLiteral("DockWidget #1"));
            auto myWidget = new QWidget();
            dock1->setWidget(myWidget);
            dock1->resize(600, 600);
            dock1->show();

            auto dock2 = new KDDockWidgets::DockWidget(QStringLiteral("DockWidget #2"));
            myWidget = new QWidget();
            dock2->setWidget(myWidget);
            dock2->resize(600, 600);
            dock2->show();

            dock1->addDockWidgetAsTab(dock2);
        }
    };

    MyMainWindow m;
}

void TestDocks::tst_raise()
{
    // Tests DockWidget::raise();
    EnsureTopLevelsDeleted e;

    auto dock1 = createDockWidget("1", new QWidget());
    auto dock2 = createDockWidget("2", new QWidget());
    auto fw2 = Tests::make_qpointer(dock2->window());
    dock1->addDockWidgetAsTab(dock2);
    dock1->setAsCurrentTab();
    QVERIFY(dock1->isCurrentTab());
    QVERIFY(!dock2->isCurrentTab());
    dock2->raise();
    QVERIFY(!dock1->isCurrentTab());
    QVERIFY(dock2->isCurrentTab());

    if (qApp->platformName() != QLatin1String("offscreen")) { // offscreen qpa doesn't seem to keep Window Z.
        auto dock3 = createDockWidget("3", new QWidget());
        dock3->window()->setGeometry(dock1->window()->geometry());
        dock3->window()->setObjectName("3");
        dock1->window()->setObjectName("1");
        dock3->raise();
        QTest::qWait(200);

        if (qApp->widgetAt(dock3->window()->geometry().topLeft() + QPoint(50, 50))->window() != dock3->window()) {
            qDebug() << "Failing before raise" << qApp->widgetAt(dock3->window()->geometry().topLeft() + QPoint(50, 50))->window() << dock3->window()
                     << dock1->window()->geometry() << dock3->window()->geometry();
            QVERIFY(false);
        }

        dock1->raise();
        QTest::qWait(200);
        QVERIFY(dock1->isCurrentTab());

        if (qApp->widgetAt(dock3->window()->geometry().topLeft() + QPoint(50, 50))->window() != dock1->window()) {
            qDebug() << "Failing after raise" << qApp->widgetAt(dock3->window()->geometry().topLeft() + QPoint(50, 50))->window() << dock1->window()
                     << dock1->window()->geometry() << dock3->window()->geometry();
            QVERIFY(false);
        }

        delete dock3->window();
    }

    delete fw2;
    delete dock1->window();
}

void TestDocks::tst_floatingAction()
{
    // Tests DockWidget::floatAction()
    EnsureTopLevelsDeleted e;

    {
        // 1. Create a MainWindow with two docked dock-widgets, then float the first one.
        auto m = createMainWindow();
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

        auto action = dock1->floatAction();
        QVERIFY(!dock1->isFloating());
        QVERIFY(!action->isChecked());
        QVERIFY(action->isEnabled());
        QCOMPARE(action->toolTip(), tr("Detach"));

        action->toggle();
        QVERIFY(dock1->isFloating());
        QVERIFY(action->isChecked());
        QVERIFY(action->isEnabled());
        QCOMPARE(action->toolTip(), tr("Dock"));

        auto fw = dock1->floatingWindow();
        QVERIFY(fw);

        //2. Put it back, via setFloating(). It should return to its place.
        action->toggle();

        QVERIFY(!dock1->isFloating());
        QVERIFY(!action->isChecked());
        QVERIFY(action->isEnabled());
        QVERIFY(!dock1->isTabbed());
        QCOMPARE(action->toolTip(), tr("Detach"));;

        Testing::waitForDeleted(fw);
    }

    {
        // 1. Create a MainWindow with one docked dock-widgets, and one floating.
        auto m = createMainWindow();
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);

        //The floating window action should be disabled as it has no previous place
        auto action = dock2->floatAction();
        QVERIFY(dock2->isFloating());
        QVERIFY(action->isChecked());
        QVERIFY(!action->isEnabled());
        QCOMPARE(action->toolTip(), tr("Dock"));

        m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

        QVERIFY(!dock2->isFloating());
        QVERIFY(!action->isChecked());
        QVERIFY(action->isEnabled());
        QCOMPARE(action->toolTip(), tr("Detach"));

        action->toggle();
        QVERIFY(dock2->isFloating());
        QVERIFY(action->isChecked());
        QVERIFY(action->isEnabled());
        QCOMPARE(action->toolTip(), tr("Dock"));

        auto fw = dock2->floatingWindow();
        QVERIFY(fw);

        //2. Put it back, via setFloating(). It should return to its place.
        action->toggle();

        QVERIFY(!dock1->isFloating());
        QVERIFY(!action->isChecked());
        QVERIFY(action->isEnabled());
        QVERIFY(!dock1->isTabbed());
        QCOMPARE(action->toolTip(), tr("Detach"));

        Testing::waitForDeleted(fw);
    }
    {
        // 3. A floating window with two tabs
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));

        bool dock1IsFloating = dock1->floatAction()->isChecked();
        bool dock2IsFloating = dock2->floatAction()->isChecked();

        connect(dock1->floatAction(), &QAction::toggled, [&dock1IsFloating] (bool t) {
            Q_ASSERT(dock1IsFloating != t);
            dock1IsFloating = t;
        });

        connect(dock2->floatAction(), &QAction::toggled, [&dock2IsFloating] (bool t) {
            Q_ASSERT(dock2IsFloating != t);
            dock2IsFloating = t;
        });

        auto fw2 = dock2->floatingWindow();
        QVERIFY(dock1->isFloating());
        QVERIFY(dock2->isFloating());
        QVERIFY(dock1->floatAction()->isChecked());
        QVERIFY(dock2->floatAction()->isChecked());

        dock1->addDockWidgetAsTab(dock2);
        QVERIFY(!dock1->isFloating());
        QVERIFY(!dock2->isFloating());
        QVERIFY(!dock1->floatAction()->isChecked());
        QVERIFY(!dock2->floatAction()->isChecked());

        dock2->setFloating(true);

        QVERIFY(dock1->isFloating());
        QVERIFY(dock1->floatAction()->isChecked());
        QVERIFY(dock2->isFloating());
        QVERIFY(dock2->floatAction()->isChecked());

        QVERIFY(dock1IsFloating);
        QVERIFY(dock2IsFloating);

        delete fw2;
        delete dock1->window();
        delete dock2->window();
    }

    {
        // If the dock widget is alone then it's floating, but we suddenly dock a widget side-by-side
        // to it, then both aren't floating anymore. This test tests if the signal was emitted

        auto dock1 = createDockWidget("one", new QPushButton("one"));
        auto dock2 = createDockWidget("two", new QPushButton("two"));

        QVERIFY(dock1->isFloating());
        QVERIFY(dock2->isFloating());
        QVERIFY(dock1->floatAction()->isChecked());
        QVERIFY(dock2->floatAction()->isChecked());
        auto oldFw2 = dock2->window();

        QSignalSpy spy1(dock1->floatAction(), &QAction::toggled);
        QSignalSpy spy2(dock2->floatAction(), &QAction::toggled);

        QSignalSpy spy11(dock1, &DockWidgetBase::isFloatingChanged);
        QSignalSpy spy21(dock2, &DockWidgetBase::isFloatingChanged);

        dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);

        QCOMPARE(spy1.count(), 1);
        QCOMPARE(spy2.count(), 1);
        QCOMPARE(spy11.count(), 1);
        QCOMPARE(spy21.count(), 1);

        QVERIFY(!dock1->isFloating());
        QVERIFY(!dock2->isFloating());

        QVERIFY(!dock2->floatAction()->isChecked());
        QVERIFY(!dock1->floatAction()->isChecked());

        delete dock1->window();
        delete oldFw2->window();
    }

    {
        // Like before, but now we use addMultiSplitter()

        auto dock1 = createDockWidget("one", new QPushButton("one"));
        auto dock2 = createDockWidget("two", new QPushButton("two"));

        QVERIFY(dock1->isFloating());
        QVERIFY(dock2->isFloating());
        QVERIFY(dock1->floatAction()->isChecked());
        QVERIFY(dock2->floatAction()->isChecked());
        auto oldFw2 = dock2->floatingWindow();

        QSignalSpy spy1(dock1->floatAction(), &QAction::toggled);
        QSignalSpy spy2(dock2->floatAction(), &QAction::toggled);

        QSignalSpy spy11(dock1, &DockWidgetBase::isFloatingChanged);
        QSignalSpy spy21(dock2, &DockWidgetBase::isFloatingChanged);

        auto dropArea1 = dock1->floatingWindow()->dropArea();
        dropArea1->drop(oldFw2, Location_OnRight, nullptr);

        QCOMPARE(spy1.count(), 1);
        QCOMPARE(spy2.count(), 1);
        QCOMPARE(spy11.count(), 1);
        QCOMPARE(spy21.count(), 1);

        QVERIFY(!dock1->isFloating());
        QVERIFY(!dock2->isFloating());
        QVERIFY(!dock2->floatAction()->isChecked());
        QVERIFY(!dock1->floatAction()->isChecked());

        // Let's now remove dock1, dock2 should be floating
        dock1->setFloating(true);
        QVERIFY(dock1->isFloating());
        QVERIFY(dock2->isFloating());
        QVERIFY(dock2->floatAction()->isChecked());
        QVERIFY(dock1->floatAction()->isChecked());

        delete dock1->window();
        delete dock2->window();
        delete oldFw2->window();
    }

    {
        // Same test as before, but now tab instead of side-by-side
        auto dock1 = createDockWidget("one", new QPushButton("one"));
        auto dock2 = createDockWidget("two", new QPushButton("two"));

        QVERIFY(dock1->isFloating());
        QVERIFY(dock2->isFloating());
        QVERIFY(dock1->floatAction()->isChecked());
        QVERIFY(dock2->floatAction()->isChecked());
        auto oldFw2 = dock2->window();

        QSignalSpy spy1(dock1->floatAction(), &QAction::toggled);
        QSignalSpy spy2(dock2->floatAction(), &QAction::toggled);
        QSignalSpy spy11(dock1, &DockWidgetBase::isFloatingChanged);
        QSignalSpy spy21(dock2, &DockWidgetBase::isFloatingChanged);
        dock1->addDockWidgetAsTab(dock2);

        QCOMPARE(spy1.count(), 1);

        // On earlier Qt versions this is flaky, but technically correct.
        // Windows can get hidden while being reparented and floating changes momentarily.
        QVERIFY(spy2.count() == 1 || spy2.count() == 3);
        QVERIFY(spy21.count() == 1 || spy21.count() == 3);
        QCOMPARE(spy11.count(), 1);

        QVERIFY(!dock1->isFloating());
        QVERIFY(!dock2->isFloating());

        QVERIFY(!dock2->floatAction()->isChecked());
        QVERIFY(!dock1->floatAction()->isChecked());

        delete dock1->window();
        delete oldFw2->window();
    }
}

void TestDocks::tst_dockableMainWindows()
{
    EnsureTopLevelsDeleted e;

     auto m1 = createMainWindow();
     auto dock1 = createDockWidget("dock1", new QPushButton("foo"));
     m1->addDockWidget(dock1, Location_OnTop);

     auto m2 = new KDDockWidgets::MainWindow("mainwindow-dockable");
     auto m2Container = createDockWidget("mainwindow-dw", m2);
     auto menubar = m2->menuBar();
     menubar->addMenu("File");
     menubar->addMenu("View");
     menubar->addMenu("Help");
     m2Container->show();

     auto dock21 = createDockWidget("dock21", new QPushButton("foo"));
     auto dock22 = createDockWidget("dock22", new QPushButton("foo"));
     m2->addDockWidget(dock21, Location_OnLeft);
     m2->addDockWidget(dock22, Location_OnRight);

     auto fw = m2Container->floatingWindow();
     TitleBar *fwTitleBar = fw->titleBar();

     QVERIFY(fw->hasSingleFrame());
     QVERIFY(fw->hasSingleDockWidget());

     // Check that the inner-inner dock widgets have a visible title-bar
     QVERIFY(dock21->titleBar()->isVisible());
     QVERIFY(dock22->titleBar()->isVisible());
     QVERIFY(dock21->titleBar() != fwTitleBar);
     QVERIFY(dock22->titleBar() != fwTitleBar);

     QTest::qWait(10); // the DND state machine needs the event loop to start, otherwise activeState() is nullptr. (for offscreen QPA)
     const QPoint startPoint = fwTitleBar->mapToGlobal(QPoint(5, 5));
     const QPoint destination = startPoint + QPoint(20, 20);

     // Check that we don't get the "Refusing to itself" warning. not actually dropping anywhere
     drag(fwTitleBar, startPoint, destination);

     // The FloatingWindow has a single DockWidget, so it shows the title bar, while the Frame doesn't
     QVERIFY(fwTitleBar->isVisible());
     QVERIFY(!m2Container->frame()->titleBar()->isVisible());

     fw->dropArea()->addDockWidget(dock1, Location::Location_OnLeft, nullptr);
     // Now the FloatingWindow has two dock widgets, so our main window dock widget also shows the title bar
     QVERIFY(fwTitleBar->isVisible());
     QVERIFY(m2Container->frame()->titleBar()->isVisible());

     // Put it how it was, FloatingWindow is single dock again
     auto frame1 = dock1->frame();
     dock1->close();
     Testing::waitForDeleted(frame1);
     QVERIFY(fwTitleBar->isVisible());
     QVERIFY(!m2Container->frame()->titleBar()->isVisible());

     // Repeat, but instead of closing dock1, we float it
     fw->dropArea()->addDockWidget(dock1, Location::Location_OnLeft, nullptr);
     QVERIFY(fwTitleBar->isVisible());
     QVERIFY(m2Container->frame()->titleBar()->isVisible());
     frame1 = dock1->frame();
     frame1->titleBar()->onFloatClicked();
     QVERIFY(fwTitleBar->isVisible());

     QVERIFY(!m2Container->frame()->titleBar()->isVisible());

     fw->dropArea()->addDockWidget(dock1, Location::Location_OnLeft, nullptr);
}

void TestDocks::tst_lastFloatingPositionIsRestored()
{
    EnsureTopLevelsDeleted e;

    auto m1 = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QWidget());
    dock1->show();
    QPoint targetPos = QPoint(340, 340);
    dock1->window()->move(targetPos);
    auto oldFw = dock1->window();

    LayoutSaver saver;
    QByteArray saved = saver.serializeLayout();

    dock1->window()->move(0, 0);
    dock1->close();
    delete oldFw;

    saver.restoreLayout(saved);
    QCOMPARE(dock1->window()->pos(), targetPos);
    QCOMPARE(dock1->window()->frameGeometry().topLeft(), targetPos);

    // Adjsut to what we got without the frame
    targetPos = dock1->window()->geometry().topLeft();

    // Now dock it:
    m1->addDockWidget(dock1, Location_OnTop);
    QCOMPARE(dock1->lastPositions().lastFloatingGeometry().topLeft(), targetPos);

    dock1->setFloating(true);
    QCOMPARE(dock1->window()->geometry().topLeft(), targetPos);

    saver.restoreLayout(saved);
    QCOMPARE(dock1->window()->geometry().topLeft(), targetPos);

    // Dock again and save:
    m1->addDockWidget(dock1, Location_OnTop);
    saved = saver.serializeLayout();
    dock1->setFloating(true);
    dock1->window()->move(0, 0);
    saver.restoreLayout(saved);
    QVERIFY(!dock1->isFloating());
    dock1->setFloating(true);
    QCOMPARE(dock1->window()->geometry().topLeft(), targetPos);
    delete dock1->window();
}

void TestDocks::tst_maxSizeHonouredWhenAnotherDropped()
{
    // dock1 is docked, and has small max-height.
    // When dropping dock2, which is small too, dock2 should occupy all the height except dock1's max-height
    // i.e. dock2 should expand and eat all available space

    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None);
    auto dock1 = new DockWidgetType("dock1");

    auto w = new QWidget();
    w->setMinimumSize(120, 100);
    w->setMaximumSize(300, 150);
    dock1->setWidget(w);
    m1->addDockWidget(dock1, Location_OnLeft);

    auto dock2 = new DockWidgetType("dock2");
    m1->addDockWidget(dock2, Location_OnBottom);

    auto root = m1->multiSplitter()->rootItem();
    Separator *separator = root->separators().constFirst();
    const int min1 = root->minPosForSeparator_global(separator);
    const int max2 = root->maxPosForSeparator_global(separator);

    QVERIFY(separator->position() >= min1);
    QVERIFY(separator->position() <= max2);
    const int item1MaxHeight = dock1->frame()->maxSizeHint().height();
    QVERIFY(dock1->frame()->height() <= item1MaxHeight);
    root->dumpLayout();
    QCOMPARE(dock2->frame()->height(), root->height() - item1MaxHeight - Item::separatorThickness);
}

void TestDocks::tst_maxSizedHonouredAfterRemoved()
{
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None);
    auto dock1 = new DockWidgetType("dock1");
    dock1->show();

    auto w = new QWidget();
    w->setMinimumSize(120, 100);
    w->setMaximumSize(300, 150);
    dock1->setWidget(w);
    m1->dropArea()->addMultiSplitter(dock1->floatingWindow()->multiSplitter(), Location_OnLeft);

    auto dock2 = new DockWidgetType("dock2");
    dock2->show();
    m1->dropArea()->addMultiSplitter(dock2->floatingWindow()->multiSplitter(), Location_OnTop);

    auto root = m1->multiSplitter()->rootItem();

    // Wait 1 event loop so we get layout invalidated and get max-size constraints
    QTest::qWait(10);

    auto sep = root->separators().constFirst();
    root->requestEqualSize(sep); // Since we're not calling honourMaxSizes() after a widget changes its max size afterwards yet
    const int sepMin = root->minPosForSeparator_global(sep);
    const int sepMax = root->maxPosForSeparator_global(sep);

    QVERIFY(sep->position() >= sepMin);
    QVERIFY(sep->position() <= sepMax);

    auto dock3 = new DockWidgetType("dock3");
    dock3->show();
    m1->dropArea()->addMultiSplitter(dock3->floatingWindow()->multiSplitter(), Location_OnBottom);

    dock1->setFloating(true);
    m1->dropArea()->addMultiSplitter(dock1->floatingWindow()->multiSplitter(), Location_OnBottom, dock2->frame());

    // Close dock2 and check if dock1's max-size is still honoured
    dock2->close();
    QTest::qWait(100); // wait for the resize, so dock1 gets taller"

    QVERIFY(dock1->frame()->height() <= dock1->frame()->maxSizeHint().height());
    delete dock2;
}

void TestDocks::tst_maximumSizePolicy()
{
    EnsureTopLevelsDeleted e;

    auto widget = new MyWidget2();
    const int maxHeight = 250;
    widget->setMinSize(QSize(200, 200));
    widget->setSizeHint(QSize(250, maxHeight));
    widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    auto dock1 = createDockWidget("dock1", widget);
    dock1->show();
    dock1->window()->resize(QSize(500, 500));
    auto oldFw = Tests::make_qpointer(dock1->window());
    dock1->close();
    dock1->show();
    auto oldFw2 = dock1->window();


    const int tollerance = 50;
    QVERIFY(dock1->window()->height() <= maxHeight + tollerance); // +tollerance as the floating window is a bit bigger, due to margins etc.
    QVERIFY(dock1->height() <= maxHeight);

    auto m1 = createMainWindow();
    auto dock2 = createDockWidget("dock2", new QWidget());
    m1->addDockWidget(dock2, Location_OnTop);
    m1->resize(2000, 3000);

    // Make the floating window big, and see if the suggested highlight is still small
    dock1->window()->resize(QSize(dock1->width(), 800));

    {
        WindowBeingDragged wbd1(dock1->floatingWindow());
        const QRect highlightRect = m1->multiSplitter()->rectForDrop(&wbd1, Location_OnBottom, nullptr);
        QVERIFY(highlightRect.height() <= maxHeight + tollerance);
    }

    // Now drop it, and check too
    m1->addDockWidget(dock1, Location_OnBottom);
    QVERIFY(dock1->height() <= maxHeight);

    delete oldFw.data();
    delete oldFw2;
}

void TestDocks::tst_tabsNotClickable()
{
    // Well, not a great unit-test, as it's only repro when it's Windows sending the native event
    // Can't repro with fabricated events. Uncomment the WAIT and test different configs manually

    EnsureTopLevelsDeleted e;
    Config::self().setFlags(Config::Flag_Default  | Config::Flag_HideTitleBarWhenTabsVisible);
    //Config::self().setFlags(Config::Flag_Default  | Config::Flag_HideTitleBarWhenTabsVisible | Config::Flag_AlwaysShowTabs);
    //Config::self().setFlags(Config::Flag_HideTitleBarWhenTabsVisible | Config::Flag_AlwaysShowTabs);

    auto dock1 = createDockWidget("dock1", new QWidget());
    auto dock2 = createDockWidget("dock2", new QWidget());
    dock1->addDockWidgetAsTab(dock2);

    auto frame = qobject_cast<FrameWidget*>(dock1->frame());
    QCOMPARE(frame->currentIndex(), 1);

    QTest::qWait(500); // wait for window to get proper geometry

    const QPoint clickPoint = frame->tabBar()->mapToGlobal(frame->tabBar()->tabRect(0).center());
    QCursor::setPos(clickPoint); // Just for visual debug when needed

    pressOn(clickPoint, frame->tabBar());
    releaseOn(clickPoint, frame->tabBar());

   // WAIT // Uncomment for MANUAL test. Also test by adding Flag_AlwaysShowTabs

    QCOMPARE(frame->currentIndex(), 0);

    delete frame->window();
}

void TestDocks::tst_stuckSeparator()
{
    const QString absoluteLayoutFileName = QStringLiteral(":/layouts/stuck-separator.json");

    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(2560, 809), MainWindowOption_None, "MainWindow1");
    const int numDockWidgets = 26;
    DockWidgetBase *dw25 = nullptr;
    for (int i = 0; i < numDockWidgets; ++i) {
        auto createdDw = createDockWidget(QStringLiteral("dock-%1").arg(i), new QWidget());
        if (i == 25)
            dw25 = createdDw;
    }

    LayoutSaver restorer;
    QVERIFY(restorer.restoreFromFile(absoluteLayoutFileName));

    Frame *frame25 = dw25->frame();
    ItemContainer *root = m1->multiSplitter()->rootItem();
    Item *item25 = root->itemForWidget(frame25);
    ItemContainer *container25 = item25->parentContainer();
    Separator::List separators = container25->separators();
    QCOMPARE(separators.size(), 1);

    Separator *separator25 = separators.constFirst();
    const int sepMin = container25->minPosForSeparator_global(separator25);
    const int sepMax = container25->maxPosForSeparator_global(separator25);

    QVERIFY(sepMin <= sepMax);

    for (auto dw : DockRegistry::self()->dockwidgets()) {
        delete dw;
    }
}

void TestDocks::tst_titleBarFocusedWhenTabsChange()
{
     EnsureTopLevelsDeleted e;
     Config::self().setFlags(Config::Flag_TitleBarIsFocusable);

     auto le1 = new QLineEdit();
     le1->setObjectName("le1");
     auto dock1 = createDockWidget(QStringLiteral("dock1"), le1);
     auto dock2 = createDockWidget(QStringLiteral("dock2"), new QLineEdit());
     auto dock3 = createDockWidget(QStringLiteral("dock3"), new QLineEdit());

     auto m1 = createMainWindow(QSize(2560, 809), MainWindowOption_None, "MainWindow1");

     m1->addDockWidget(dock1, Location_OnLeft);
     m1->addDockWidget(dock2, Location_OnRight);
     dock2->addDockWidgetAsTab(dock3);

     TitleBar *titleBar1 = dock1->titleBar();
     dock1->widget()->setFocus(Qt::MouseFocusReason);

     QVERIFY(Testing::waitForEvent(dock1->widget(), QEvent::FocusIn));
     QVERIFY(titleBar1->isFocused());

     auto frame2 = qobject_cast<FrameWidget*>(dock2->frame());

     TabWidget *tb = frame2->tabWidget();
     QCOMPARE(tb->currentIndex(), 1); // Was the last to be added

     auto tabBar = dynamic_cast<QTabBar*>(tb->tabBar());
     const QRect rect0 = tabBar->tabRect(0);
     const QPoint globalPos = tabBar->mapToGlobal(rect0.topLeft()) + QPoint(5, 5);
     Tests::clickOn(globalPos, tabBar);
     QVERIFY(!titleBar1->isFocused());
     QVERIFY(dock2->titleBar()->isFocused());

     // Test that clicking on a tab that is already current will also set focus
     dock1->setFocus(Qt::MouseFocusReason);
     QVERIFY(dock1->titleBar()->isFocused());
     QVERIFY(!dock2->titleBar()->isFocused());

     Tests::clickOn(globalPos, tabBar);
     QVERIFY(!dock1->titleBar()->isFocused());
     QVERIFY(dock2->titleBar()->isFocused());
}

int main(int argc, char *argv[])
{
    if (!qpaPassedAsArgument(argc, argv)) {
        // Use offscreen by default as it's less annoying, doesn't create visible windows
        qputenv("QT_QPA_PLATFORM", "offscreen");
    }

    QApplication app(argc, argv);
    if (shouldSkipTests())
        return 0;

    KDDockWidgets::TestDocks test;
    return QTest::qExec(&test, argc, argv);
}


#include "tst_docks.moc"
