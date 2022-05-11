/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

#include "tst_docks.h"
#include "Config.h"
#include "LayoutSaver_p.h"
#include "MDILayoutWidget_p.h"
#include "MainWindowMDI.h"
#include "Position_p.h"
#include "WindowBeingDragged_p.h"
#include "Platform.h"
#include "multisplitter/Item_p.h"

#include "controllers/DropArea.h"
#include "controllers/DockWidget.h"
#include "controllers/DockWidget_p.h"
#include "controllers/Separator.h"
#include "controllers/TabBar.h"
#include "controllers/Stack.h"
#include "controllers/SideBar.h"

#include <QAction>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;
using namespace Layouting;
using namespace KDDockWidgets::Tests;

static int osWindowMinWidth()
{
#ifdef Q_OS_WIN
    return GetSystemMetrics(SM_CXMIN);
#else
    return 140; // Some random value for our windows. It's only important on Windows
#endif
}

inline int lengthForSize(QSize sz, Qt::Orientation o)
{
    return o == Qt::Vertical ? sz.height() : sz.width();
}

inline int widgetMinLength(View *view, Qt::Orientation o)
{
    const QSize sz = view->minSize();
    return lengthForSize(sz, o);
}

inline int widgetMinLength(Controllers::Frame *frame, Qt::Orientation o)
{
    const QSize sz = frame->view()->minSize();
    return lengthForSize(sz, o);
}

static Controllers::DockWidget *createAndNestDockWidget(DropArea *dropArea, Controllers::Frame *relativeTo,
                                                        KDDockWidgets::Location location)
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

static std::unique_ptr<MainWindow> createSimpleNestedMainWindow(Controllers::DockWidget **centralDock,
                                                                Controllers::DockWidget **leftDock,
                                                                Controllers::DockWidget **rightDock)
{
    auto window = createMainWindow({ 900, 500 });
    *centralDock = createDockWidget("centralDock", Qt::green);
    window->addDockWidgetAsTab(*centralDock);
    auto dropArea = window->dropArea();

    *leftDock = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnLeft);
    *rightDock = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnRight);
    return window;
}

void TestDocks::tst_simple1()
{
    // Simply create a MainWindow
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    m->layoutWidget()->checkSanity();
}

void TestDocks::tst_simple2()
{
    // Simply create a MainWindow, and dock something on top
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dw = createDockWidget("dw", new MyWidget("dw", Qt::blue));
    auto fw = dw->floatingWindow();
    m->addDockWidget(dw, KDDockWidgets::Location_OnTop);
    m->layoutWidget()->checkSanity();
    delete fw;
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
    auto f1 = dock1->dptr()->frame();
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
    QVERIFY(fw2->view()->isRootView());
    QCOMPARE(fw2->pos(), dock2FloatingPoint);
    QVERIFY(m->view()->window()->equals(fw2->view()->window()->transientParent()));
    QVERIFY(dock2->isFloating());
    QVERIFY(dock2->isVisible());

    QVERIFY(!dock3->isVisible()); // Remains closed
    QVERIFY(dock3->view()->parentView() == nullptr);

    dock3->show();
    dock3->dptr()->morphIntoFloatingWindow(); // as it would take 1 event loop. Do it now so we can
                                              // compare already.

    QCOMPARE(dock3->window()->pos(), dock3FloatingPoint);
}

void TestDocks::tst_doesntHaveNativeTitleBar()
{
    // Tests that a floating window doesn't have a native title bar
    // This test is mostly to test a bug that was happening with QtQuick, where the native title bar
    // would appear on linux
    EnsureTopLevelsDeleted e;

    auto dw1 = createDockWidget("dock1");
    Controllers::FloatingWindow *fw = dw1->floatingWindow();
    QVERIFY(fw);
    QVERIFY(fw->view()->flags() & Qt::Tool);

#if defined(Q_OS_LINUX)
    QVERIFY(fw->view()->flags() & Qt::FramelessWindowHint);
#elif defined(Q_OS_WIN)
    QVERIFY(!(fw->windowFlags() & Qt::FramelessWindowHint));
#endif
}

void TestDocks::tst_resizeWindow2()
{
    // Tests that resizing the width of the main window will never move horizontal anchors

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    auto dock2 = createDockWidget("2");

    Controllers::FloatingWindow *fw1 = dock1->floatingWindow();
    Controllers::FloatingWindow *fw2 = dock2->floatingWindow();
    m->addDockWidget(dock1, Location_OnTop);
    m->addDockWidget(dock2, Location_OnBottom);

    auto layout = m->multiSplitter();
    Controllers::Separator *anchor = layout->separators().at(0);
    const int oldPosY = anchor->position();
    m->view()->resize(QSize(m->width() + 10, m->height()));
    QCOMPARE(anchor->position(), oldPosY);
    layout->checkSanity();

    delete fw1;
    delete fw2;
}

void TestDocks::tst_hasLastDockedLocation()
{
    // Tests Controllers::DockWidget::hasPreviousDockedLocation()

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    m->layoutWidget()->checkSanity();
    m->multiSplitter()->setObjectName("mainWindow-dropArea");
    dock1->floatingWindow()->layoutWidget()->view()->setObjectName("first-dropArea1");
    dock1->floatingWindow()->layoutWidget()->checkSanity();
    auto window1 = dock1->window();
    QVERIFY(dock1->isFloating());
    QVERIFY(!dock1->hasPreviousDockedLocation());
    QVERIFY(dock1->setFloating(true));
    QVERIFY(!dock1->setFloating(false)); // No docking location, so it's not docked
    QVERIFY(dock1->isFloating());
    QVERIFY(!dock1->hasPreviousDockedLocation());

    m->addDockWidget(dock1, Location_OnBottom);
    m->layoutWidget()->checkSanity();

    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->setFloating(true));

    auto ms1 = dock1->floatingWindow()->layoutWidget();
    ms1->view()->setObjectName("dropArea1");
    ms1->checkSanity();
    QVERIFY(dock1->hasPreviousDockedLocation());
    auto window11 = dock1->window();
    QVERIFY(dock1->setFloating(false));
}

void TestDocks::tst_ghostSeparator()
{
    // Tests a situation where a separator wouldn't be removed after a widget had been removed
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    auto dock2 = createDockWidget("2");
    auto dock3 = createDockWidget("3");

    QPointer<Controllers::FloatingWindow> fw1 = dock1->floatingWindow();
    QPointer<Controllers::FloatingWindow> fw2 = dock2->floatingWindow();
    QPointer<Controllers::FloatingWindow> fw3 = dock3->floatingWindow();

    dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);
    QCOMPARE(fw1->multiSplitter()->separators().size(), 1);
    QCOMPARE(Controllers::Separator::numSeparators(), 1);

    m->addDockWidget(dock3, Location_OnBottom);
    QCOMPARE(m->multiSplitter()->separators().size(), 0);
    QCOMPARE(Controllers::Separator::numSeparators(), 1);

    m->multiSplitter()->addMultiSplitter(fw1->multiSplitter(), Location_OnRight);
    QCOMPARE(m->multiSplitter()->separators().size(), 2);
    QCOMPARE(Controllers::Separator::numSeparators(), 2);

    delete fw1;
    delete fw2;
    delete fw3;
}

void TestDocks::tst_detachFromMainWindow()
{
    // Tests a situation where clicking the float button wouldn't work on QtQuick
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    auto fw1 = dock1->window();
    m->addDockWidget(dock1, Location_OnTop);

    QVERIFY(m->layoutWidget()->mainWindow() != nullptr);
    QVERIFY(!dock1->isFloating());
    Controllers::TitleBar *tb = dock1->titleBar();
    QVERIFY(tb == dock1->dptr()->frame()->titleBar());
    QVERIFY(tb->isVisible());
    QVERIFY(!tb->isFloating());
}

void TestDocks::tst_detachPos()
{
    // Tests a situation where detaching a dock widget would send it to a bogus position
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new MyWidget(QStringLiteral("1"), Qt::black), {}, {}, /** show = */ false); // we're creating the dock widgets without showing them as floating initially, so it doesn't record the previous floating position
    auto dock2 = createDockWidget("2", new MyWidget(QStringLiteral("2"), Qt::black), {}, {}, /** show = */ false);

    QVERIFY(!dock1->isVisible());
    QVERIFY(!dock2->isVisible());

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);

    QVERIFY(!dock1->dptr()->lastPosition()->lastFloatingGeometry().isValid());
    QVERIFY(!dock2->dptr()->lastPosition()->lastFloatingGeometry().isValid());

    const int previousWidth = dock1->width();
    dock1->setFloating(true);
    QTest::qWait(400); // Needed for QtQuick

    QVERIFY(qAbs(previousWidth - dock1->width()) < 15); // 15px of difference when floating is fine, due to margins and what not.
}

void TestDocks::tst_floatingWindowSize()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    auto fw1 = dock1->window();

    QTest::qWait(100);

    QVERIFY(!fw1->geometry().isNull());
    QCOMPARE(fw1->size(), fw1->window()->size());
}

void TestDocks::tst_tabbingWithAffinities()
{
    EnsureTopLevelsDeleted e;
    // Tests that dock widgets with different affinities should not tab together

    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None);
    m1->setAffinities({ "af1", "af2" });

    auto dw1 = new Controllers::DockWidget("1");
    dw1->setAffinities({ "af1" });
    dw1->show();

    auto dw2 = new Controllers::DockWidget("2");
    dw2->setAffinities({ "af2" });
    dw2->show();

    Controllers::FloatingWindow *fw1 = dw1->floatingWindow();
    Controllers::FloatingWindow *fw2 = dw2->floatingWindow();

    {
        SetExpectedWarning ignoreWarning("Refusing to dock widget with incompatible affinity");
        dw1->addDockWidgetAsTab(dw2);
        QVERIFY(!dw1->window()->equals(dw2->window()));
    }

    m1->addDockWidget(dw1, Location_OnBottom);
    QVERIFY(!dw1->isFloating());

    {
        SetExpectedWarning ignoreWarning("Refusing to dock widget with incompatible affinity");
        auto dropArea = m1->dropArea();
        WindowBeingDragged wbd(fw2, fw2);
        QVERIFY(!dropArea->drop(&wbd, dw1->dptr()->frame(),
                                DropLocation_Center));
        QVERIFY(!dw1->window()->equals(dw2->window()));
    }

    delete fw1;
    delete fw2;
}

void TestDocks::tst_sizeAfterRedock()
{
    EnsureTopLevelsDeleted e;
    auto dw1 = new Controllers::DockWidget(QStringLiteral("1"));
    auto dw2 = new Controllers::DockWidget(QStringLiteral("2"));
    dw2->setWidget(new MyWidget("2", Qt::red));

    dw1->addDockWidgetToContainingWindow(dw2, Location_OnBottom);
    const int height2 = dw2->dptr()->frame()->height();

    dw2->setFloating(true);
    QTest::qWait(100);

    QCOMPARE(height2, dw2->window()->height());
    auto oldFw2 = dw2->floatingWindow();

    // Redock
    Controllers::FloatingWindow *fw1 = dw1->floatingWindow();
    DropArea *dropArea = fw1->dropArea();

    Controllers::DropArea *ms1 = fw1->multiSplitter();
    {
        WindowBeingDragged wbd2(oldFw2);
        const QRect suggestedDropRect = ms1->rectForDrop(&wbd2, Location_OnBottom, nullptr);
        QCOMPARE(suggestedDropRect.height(), height2);
    }

    dropArea->drop(dw2->floatingWindow()->view(), Location_OnBottom, nullptr);

    QCOMPARE(dw2->dptr()->frame()->height(), height2);

    delete oldFw2;
}

void TestDocks::tst_honourUserGeometry()
{
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None);
    auto dw1 = new Controllers::DockWidget(QStringLiteral("1"));
    QVERIFY(!dw1->view()->testAttribute(Qt::WA_PendingMoveEvent));

    const QPoint pt(10, 10);
    dw1->view()->move(pt);
    dw1->show();
    Controllers::FloatingWindow *fw1 = dw1->floatingWindow();
    QCOMPARE(fw1->view()->window()->geometry().topLeft(), pt);
}

void TestDocks::tst_floatingWindowTitleBug()
{
    // Test for #74
    EnsureTopLevelsDeleted e;
    auto dw1 = new Controllers::DockWidget(QStringLiteral("1"));
    auto dw2 = new Controllers::DockWidget(QStringLiteral("2"));
    auto dw3 = new Controllers::DockWidget(QStringLiteral("3"));

    dw1->setObjectName(QStringLiteral("1"));
    dw2->setObjectName(QStringLiteral("2"));
    dw3->setObjectName(QStringLiteral("3"));

    dw1->show();
    dw1->addDockWidgetAsTab(dw2);
    dw1->addDockWidgetToContainingWindow(dw3, Location_OnBottom);

    dw1->titleBar()->onFloatClicked();

    QCOMPARE(dw3->titleBar()->title(), QLatin1String("3"));
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
    auto dock1 = createDockWidget("1", new MyWidget("1", Qt::red));
    auto dock2 = createDockWidget("2", new MyWidget("2", Qt::blue));
    QPointer<Controllers::FloatingWindow> fw1 = dock1->floatingWindow();
    QPointer<Controllers::FloatingWindow> fw2 = dock2->floatingWindow();
    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);

    auto layout = m->multiSplitter();

    layout->checkSanity();

    const int oldWidth1 = dock1->width();
    const int oldWidth2 = dock2->width();

    QVERIFY(oldWidth2 - oldWidth1 <= 1); // They're not equal if separator thickness if even

    if (doASaveRestore) {
        LayoutSaver saver;
        saver.restoreLayout(saver.serializeLayout());
    }

    m->view()->showMaximized();
    Platform::instance()->tests_waitForResize(m->view());

    const int maximizedWidth1 = dock1->width();
    const int maximizedWidth2 = dock2->width();

    const double relativeDifference = qAbs((maximizedWidth1 - maximizedWidth2) / (1.0 * layout->layoutWidth()));

    QVERIFY(relativeDifference <= 0.01);

    m->view()->showNormal();
    Platform::instance()->tests_waitForResize(m->view());

    const int newWidth1 = dock1->width();
    const int newWidth2 = dock2->width();

    QCOMPARE(oldWidth1, newWidth1);
    QCOMPARE(oldWidth2, newWidth2);
    layout->checkSanity();

    delete fw1;
    delete fw2;
}

void TestDocks::tst_restoreTwice()
{
    // Tests that restoring multiple times doesn't hide the floating windows for some reason
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralFrame, "tst_restoreTwice");
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidgetAsTab(dock1);

    auto dock2 = createDockWidget("2", new QPushButton("2"));
    auto dock3 = createDockWidget("3", new QPushButton("3"));

    dock2->dptr()->morphIntoFloatingWindow();
    dock3->dptr()->morphIntoFloatingWindow();

    {
        LayoutSaver saver;
        QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreTwice.json")));
        QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreTwice.json")));
        QVERIFY(dock2->isVisible());
        QVERIFY(dock3->isVisible());
    }

    {
        LayoutSaver saver;
        QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreTwice.json")));
        QVERIFY(dock2->isVisible());
        QVERIFY(dock3->isVisible());
        QVERIFY(dock2->window()->isVisible());
        QVERIFY(dock3->window()->isVisible());
        auto fw = dock2->floatingWindow();
        QVERIFY(fw);
    }
}

void TestDocks::tst_restoreEmpty()
{
    EnsureTopLevelsDeleted e;

    // Create an empty main window, save it to disk.
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto layout = m->multiSplitter();
    LayoutSaver saver;
    const QSize oldSize = m->size();
    QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreEmpty.json")));
    saver.restoreFromFile(QStringLiteral("layout_tst_restoreEmpty.json"));
    QVERIFY(m->layoutWidget()->checkSanity());
    QCOMPARE(layout->separators().size(), 0);
    QCOMPARE(layout->count(), 0);
    QCOMPARE(m->size(), oldSize);
    QVERIFY(layout->checkSanity());
}

void TestDocks::tst_restoreCentralFrame()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500));
    auto layout = m->multiSplitter();

    QCOMPARE(layout->count(), 1);
    Item *item = m->dropArea()->centralFrame();
    QVERIFY(item);
    auto frame = item->asFrameController();
    QCOMPARE(frame->options(), FrameOption_IsCentralFrame | FrameOption_AlwaysShowsTabs);
    QVERIFY(!frame->titleBar()->isVisible());

    LayoutSaver saver;
    QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreCentralFrame.json")));
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreCentralFrame.json")));

    QCOMPARE(layout->count(), 1);
    item = m->dropArea()->centralFrame();
    QVERIFY(item);
    frame = item->asFrameController();
    QCOMPARE(frame->options(), FrameOption_IsCentralFrame | FrameOption_AlwaysShowsTabs);
    QVERIFY(!frame->titleBar()->isVisible());
}

void TestDocks::tst_restoreMaximizedState()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();

    m->view()->showMaximized();

    QCOMPARE(m->view()->window()->windowState(), Qt::WindowMaximized);
    LayoutSaver saver;

    const QByteArray saved = saver.serializeLayout();
    m->view()->showNormal();
    QVERIFY(m->view()->window()->windowState() != Qt::WindowMaximized);

    saver.restoreLayout(saved);
    QCOMPARE(m->view()->window()->windowState(), Qt::WindowMaximized);
}

void TestDocks::tst_restoreFloatingMinimizedState()
{
    EnsureTopLevelsDeleted e;
    auto dock1 = createDockWidget("dock1", new MyWidget("one"));
    dock1->floatingWindow()->showMinimized();

    QCOMPARE(dock1->floatingWindow()->view()->window()->windowState(), Qt::WindowMinimized);

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    saver.restoreLayout(saved);
    QCOMPARE(dock1->floatingWindow()->view()->window()->windowState(), Qt::WindowMinimized);
}

void TestDocks::tst_restoreNonExistingDockWidget()
{
    // If the layout is old and doesn't know about some dock widget, then we need to float it
    // before restoring the MainWindow's layout

    QByteArray saved;
    const QSize defaultMainWindowSize = { 500, 500 };

    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(defaultMainWindowSize, MainWindowOption_None, "mainwindow1");
        LayoutSaver saver;
        saved = saver.serializeLayout();
    }

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(defaultMainWindowSize, MainWindowOption_None, "mainwindow1");
    auto dock2 = createDockWidget("dock2", new MyWidget("dock2"));
    m->addDockWidget(dock2, Location_OnBottom);
    LayoutSaver restorer;
    SetExpectedWarning sew("Couldn't find dock widget");
    QVERIFY(restorer.restoreLayout(saved));
    auto da = m->dropArea();
    QVERIFY(m->dropArea()->checkSanity());
    QCOMPARE(da->frames().size(), 0);

    QVERIFY(dock2->isOpen());
    QVERIFY(dock2->isFloating());
}

void TestDocks::tst_setFloatingSimple()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new MyWidget("one"));
    m->addDockWidget(dock1, Location_OnTop);
    auto l = m->multiSplitter();
    dock1->setFloating(true);
    QVERIFY(l->checkSanity());
    dock1->setFloating(false);
    QVERIFY(l->checkSanity());
    dock1->setFloating(true);
    QVERIFY(l->checkSanity());
    dock1->setFloating(false);
    QVERIFY(l->checkSanity());
}

void TestDocks::tst_nonDockable()
{
    { // First test without Option_NotDockable
        EnsureTopLevelsDeleted e;
        auto dock = new Controllers::DockWidget("1");
        dock->show();

        Controllers::TitleBar *tb = dock->titleBar();
        QVERIFY(tb->isVisible());
        QVERIFY(tb->isFloatButtonVisible());
    }

    {
        EnsureTopLevelsDeleted e;
        // Test that when using Option_NotDockable we don't get a dock/undock icon
        auto dock = new Controllers::DockWidget("1", Controllers::DockWidget::Option_NotDockable);
        dock->show();

        Controllers::TitleBar *tb = dock->titleBar();
        QVERIFY(tb->isVisible());
        QVERIFY(!tb->isFloatButtonVisible());
    }
}

void TestDocks::tst_closeDockWidgets()
{
    EnsureTopLevelsDeleted e;
    auto dock1 = createDockWidget("hello1", Qt::green);
    auto dock2 = createDockWidget("hello2", Qt::green);

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnBottom);

    QVERIFY(m->closeDockWidgets(true));
    QCOMPARE(m->layoutWidget()->visibleCount(), 0);
}

void TestDocks::tst_layoutEqually()
{
    EnsureTopLevelsDeleted e;

    const QString mainWindowId = "{7829427d-88e3-402e-9120-50c628dfd0bc}";
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None, mainWindowId);
    m->setAffinities({ mainWindowId });

    auto dock1 = createDockWidget("Favorite-481", new MyWidget2(QSize(536, 438)));
    auto dock2 = createDockWidget("Favorite-482", new MyWidget2(QSize(229, 118)));
    auto dock3 = createDockWidget("Favorite-483", new MyWidget2(QSize(356, 90)));
    m->setContentsMargins(10, 0, 10, 0);
    dock1->setAffinities({ mainWindowId });
    dock2->setAffinities({ mainWindowId });
    dock3->setAffinities({ mainWindowId });

    LayoutSaver restorer;
    restorer.restoreFromFile(":/layouts/layoutEquallyCrash.json");

    m->layoutEqually();
}

void TestDocks::tst_doubleClose()
{
    {
        // Via close()
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("hello", Qt::green);
        dock1->close();
        dock1->close();
    }
    {
        // Via the button
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("hello", Qt::green);
        auto fw1 = dock1->floatingWindow();

        auto t = dock1->dptr()->frame()->titleBar();
        t->onCloseClicked();
        t->onCloseClicked();

        delete dock1;
        delete fw1;
    }
    {
        // Test for #141, double delete would ruin lastPositions()
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow();
        auto dock1 = createDockWidget("1", new QPushButton("1"));
        m->addDockWidget(dock1, Location_OnBottom);

        QVERIFY(!dock1->dptr()->lastPosition()->wasFloating());
        dock1->close();
        QVERIFY(!dock1->dptr()->lastPosition()->wasFloating());
        dock1->close();
        QVERIFY(!dock1->dptr()->lastPosition()->wasFloating());
    }
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

    auto centralFrame = dropArea->items()[0]->asFrameController();
    nestDockWidget(dock1, dropArea, centralFrame, KDDockWidgets::Location_OnRight);

    QVERIFY(dock1->width() < dropArea->layoutWidth() - centralFrame->width());
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

    m->view()->showMaximized();
    Platform::instance()->tests_waitForResize(m->view());

    QVERIFY(dropArea->checkSanity());
    m->view()->showNormal();
    Platform::instance()->tests_waitForResize(m->view());

    QVERIFY(dropArea->checkSanity());
}

void TestDocks::tst_propagateResize2()
{
    // |5|1|2|
    // | |3|4|

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

void TestDocks::tst_shutdown()
{
    EnsureTopLevelsDeleted e;
    createDockWidget("doc1", Qt::green);

    auto m = createMainWindow();
    m->show();
    QVERIFY(Platform::instance()->tests_waitForWindowActive(m->view()->window()));
}

#ifndef KDDOCKWIDGETS_QTWIDGETS
// TODOv2: Move to tst_qtquick.cpp
void TestDocks::tst_hoverShowsDropIndicators()
{
    // For QtQuick on Windows, there was a bug where drop indicators wouldn't be shown if MainWindowBase
    // wasn't the root item.

    EnsureTopLevelsDeleted e;
    QQmlApplicationEngine engine(":/main2.qml");

    const MainWindowBase::List mainWindows = DockRegistry::self()->mainwindows();
    QCOMPARE(mainWindows.size(), 1);
    MainWindowBase *m = mainWindows.first();

    m->window()->window()->setPosition(500, 800);

    auto dock0 = createDockWidget("dock0", new MyWidget2(QSize(400, 400)));

    auto floatingDockWidget = createDockWidget("floatingDockWidget", new MyWidget2(QSize(400, 400)));

    m->addDockWidget(dock0, Location_OnLeft);

    const QPoint mainWindowCenterPos = m->mapToGlobal(m->geometry().center());

    QTest::qWait(100);

    auto fw = floatingDockWidget->floatingWindow();
    dragFloatingWindowTo(fw, mainWindowCenterPos);

    QCOMPARE(dock0->dptr()->frame()->dockWidgetCount(), 2);
}
#endif

void TestDocks::tst_28NestedWidgets_data()
{
    QTest::addColumn<QVector<DockDescriptor>>("docksToCreate");
    QTest::addColumn<QVector<int>>("docksToHide");

    QVector<DockDescriptor> docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible }
    };
#ifdef KDDOCKWIDGETS_QTWIDGETS
    QTest::newRow("28") << docks << QVector<int> { 11, 0 };
#endif
    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },

    };

    QVector<int> docksToHide;
    for (int i = 0; i < docks.size(); ++i) {
        docksToHide << i;
    }

    QTest::newRow("anchor_intersection") << docks << docksToHide;

    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
    };
#ifdef KDDOCKWIDGETS_QTWIDGETS
    // 2. Produced valgrind invalid reads while adding
    QTest::newRow("valgrind") << docks << QVector<int> {};
#endif
    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
    };
#ifdef KDDOCKWIDGETS_QTWIDGETS
    QTest::newRow("bug_when_closing") << docks << QVector<int> {}; // Q_ASSERT(!isSquashed())
#endif
    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
    };
#ifdef KDDOCKWIDGETS_QTWIDGETS
    QTest::newRow("bug_when_closing2") << docks << QVector<int> {}; // Tests for void KDDockWidgets::Anchor::setPosition(int, KDDockWidgets::Anchor::SetPositionOptions) Negative position -69
#endif
    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible }
    };

    docksToHide.clear();
    for (int i = 0; i < 28; ++i) {
        if (i != 16 && i != 17 && i != 18 && i != 27)
            docksToHide << i;
    }
#ifdef KDDOCKWIDGETS_QTWIDGETS
    QTest::newRow("bug_with_holes") << docks << docksToHide;
#endif
    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnLeft, 17, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible }
    };

    docksToHide.clear();
    QTest::newRow("add_as_placeholder") << docks << docksToHide;

    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden }
    };

    QTest::newRow("add_as_placeholder_simple") << docks << docksToHide;


    docks = {
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden }
    };

    docksToHide.clear();
    QTest::newRow("isSquashed_assert") << docks << docksToHide;

    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden }
    };

    docksToHide.clear();
    QTest::newRow("negative_pos_warning") << docks << docksToHide;

    docks = {
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible }
    };

    docksToHide.clear();
    QTest::newRow("bug") << docks << docksToHide;

    docks = {
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible }
    };

    docksToHide.clear();
    QTest::newRow("bug2") << docks << docksToHide;

    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible }
    };

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
    Controllers::DropArea *layout = dropArea;

    int i = 0;
    for (DockDescriptor &desc : docksToCreate) {
        desc.createdDock = createDockWidget(QString("%1").arg(i), new QPushButton(QString("%1").arg(i).toLatin1()), {}, {}, false);

        Controllers::DockWidget *relativeTo = nullptr;
        if (desc.relativeToIndex != -1)
            relativeTo = docksToCreate.at(desc.relativeToIndex).createdDock;
        m->addDockWidget(desc.createdDock, desc.loc, relativeTo, desc.option);
        QVERIFY(layout->checkSanity());
        ++i;
    }

    layout->checkSanity();

    // Run the saver in these complex scenarios:
    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    QVERIFY(!saved.isEmpty());
    QVERIFY(saver.restoreLayout(saved));

    layout->checkSanity();

    for (int i : docksToHide) {
        docksToCreate.at(i).createdDock->close();
        layout->checkSanity();
        QTest::qWait(200);
    }

    layout->checkSanity();

    for (int i : docksToHide) {
        docksToCreate.at(i).createdDock->deleteLater();
        QVERIFY(Testing::waitForDeleted(docksToCreate.at(i).createdDock));
    }

    layout->checkSanity();

    // And hide the remaining ones
    i = 0;
    for (auto dock : docksToCreate) {
        if (dock.createdDock && dock.createdDock->isVisible()) {
            dock.createdDock->close();
            QTest::qWait(200); // Wait for the docks to be closed. TODO Replace with a global event filter and wait for any resize ?
        }
        ++i;
    }

    layout->checkSanity();

    // Cleanup
    for (auto dock : DockRegistry::self()->dockwidgets()) {
        dock->deleteLater();
        QVERIFY(Testing::waitForDeleted(dock));
    }
}

void TestDocks::tst_closeReparentsToNull()
{
    EnsureTopLevelsDeleted e;
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto fw1 = dock1->window();
    QVERIFY(dock1->view()->parent() != nullptr);
    dock1->close();
    QVERIFY(dock1->view()->parent() == nullptr);
    delete dock1;
}

void TestDocks::tst_startHidden()
{
    // A really simple test for InitialVisibilityOption::StartHidden

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"), {}, {}, /*show=*/false);
    m->addDockWidget(dock1, Location_OnRight, nullptr, InitialVisibilityOption::StartHidden);
    delete dock1;
}

void TestDocks::tst_startHidden2()
{
    EnsureTopLevelsDeleted e;
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"), {}, {}, false);
        auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, {}, false);

        auto dropArea = m->dropArea();
        Controllers::DropArea *layout = dropArea;

        m->addDockWidget(dock1, Location_OnTop, nullptr, InitialVisibilityOption::StartHidden);
        QVERIFY(layout->checkSanity());

        QCOMPARE(layout->count(), 1);
        QCOMPARE(layout->placeholderCount(), 1);

        m->addDockWidget(dock2, Location_OnTop);
        QVERIFY(layout->checkSanity());

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 1);

        qDebug() << dock1->isVisible();
        dock1->show();

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);

        Platform::instance()->tests_waitForResize(dock2->view());
    }

    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"), {}, {}, false);
        auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, {}, false);
        auto dock3 = createDockWidget("dock3", new QPushButton("three"), {}, {}, false);

        auto dropArea = m->dropArea();
        Controllers::DropArea *layout = dropArea;
        m->addDockWidget(dock1, Location_OnLeft, nullptr, InitialVisibilityOption::StartHidden);

        m->addDockWidget(dock2, Location_OnBottom, nullptr, InitialVisibilityOption::StartHidden);
        m->addDockWidget(dock3, Location_OnRight, nullptr, InitialVisibilityOption::StartHidden);

        dock1->show();

        QCOMPARE(layout->count(), 3);
        QCOMPARE(layout->placeholderCount(), 2);

        dock2->show();
        dock3->show();
        Platform::instance()->tests_waitForResize(dock2->view());
        layout->checkSanity();
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

    Controllers::DropArea *layout = m->multiSplitter();

    auto d1 = createDockWidget("1", w1);
    auto d2 = createDockWidget("2", w2);
    auto d3 = createDockWidget("3", w3);

    m->addDockWidgetAsTab(d1);

    m->addDockWidget(d2, Location_OnTop);
    m->addDockWidget(d3, Location_OnTop);

    d2->close();

    Platform::instance()->tests_waitForResize(d3->view());
    d2->show(); // Should not result in negative anchor positions (Test will fail due to a qWarning)
    Platform::instance()->tests_waitForResize(d3->view());
    layout->checkSanity();

    d2->close();
    Platform::instance()->tests_waitForResize(d3->view());
    layout->checkSanity();

    // Now resize the Window, after removing middle one
    const int availableToShrink = layout->layoutSize().height() - layout->view()->minSize().height();
    const QSize newSize = { layout->layoutWidth(), layout->layoutHeight() - availableToShrink };
    if (layout->layoutMinimumSize().expandedTo(newSize) != newSize) {
        qDebug() << "Size to set is too small=" << newSize
                 << "; min=" << layout->layoutMinimumSize();
        QFAIL("");
    }

    layout->setLayoutSize(newSize);

    d2->deleteLater();
    Testing::waitForDeleted(d2);
    layout->checkSanity();
}

void TestDocks::tst_negativeAnchorPosition2()
{
    // Tests that the "Out of bounds position" warning doesn't appear. Test will abort if yes.
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dropArea = m->dropArea();
    Controllers::DropArea *layout = dropArea;

    auto dock1 = createDockWidget("1", new QPushButton("1"), {}, {}, /*show=*/false);
    auto dock2 = createDockWidget("2", new QPushButton("2"), {}, {}, /*show=*/false);
    auto dock3 = createDockWidget("3", new QPushButton("3"), {}, {}, /*show=*/false);

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight, nullptr, InitialVisibilityOption::StartHidden);
    m->addDockWidget(dock3, Location_OnRight);
    QCOMPARE(layout->placeholderCount(), 1);
    QCOMPARE(layout->count(), 3);

    dock1->setFloating(true);
    dock1->setFloating(false);
    dock2->deleteLater();
    layout->checkSanity();
    QVERIFY(Testing::waitForDeleted(dock2));
}

void TestDocks::tst_negativeAnchorPosition3()
{
    // 1. Another case, when floating a dock:
    EnsureTopLevelsDeleted e;
    QVector<DockDescriptor> docks = { { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
                                      { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
                                      { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
                                      { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
                                      { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible } };
    auto m = createMainWindow(docks);
    auto dropArea = m->dropArea();
    Controllers::DropArea *layout = dropArea;
    layout->checkSanity();

    auto dock1 = docks.at(1).createdDock;
    auto dock3 = docks.at(3).createdDock;

    dock1->setFloating(true);
    layout->checkSanity();
}

void TestDocks::tst_negativeAnchorPosition4()
{
    // 1. Tests that we don't get a warning
    // Out of bounds position= -5 ; oldPosition= 0 KDDockWidgets::Anchor(0x55e726be9090, name = "left") KDDockWidgets::Views::MainWindow(0x55e726beb8d0)
    EnsureTopLevelsDeleted e;
    QVector<DockDescriptor> docks = { { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
                                      { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
                                      { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
                                      { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
                                      { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible } };

    auto m = createMainWindow(docks);
    auto dropArea = m->dropArea();
    Controllers::DropArea *layout = dropArea;
    layout->checkSanity();

    auto dock1 = docks.at(1).createdDock;
    auto dock2 = docks.at(2).createdDock;
    dock2->setFloating(true);
    auto fw2 = dock2->floatingWindow();
    dropArea->addWidget(fw2->dropArea()->view(), Location_OnLeft, dock1->dptr()->frame());
    dock2->setFloating(true);
    fw2 = dock2->floatingWindow();

    dropArea->addWidget(fw2->dropArea()->view(), Location_OnRight, dock1->dptr()->frame());

    layout->checkSanity();
    docks.at(0).createdDock->deleteLater();
    docks.at(4).createdDock->deleteLater();
    Testing::waitForDeleted(docks.at(4).createdDock);
}

void TestDocks::tst_negativeAnchorPosition5()
{
    EnsureTopLevelsDeleted e;
    QVector<DockDescriptor> docks = {
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
    };

    auto m = createMainWindow(docks);
    auto dropArea = m->dropArea();
    Controllers::DropArea *layout = dropArea;
    layout->checkSanity();

    auto dock0 = docks.at(0).createdDock;
    auto dock1 = docks.at(1).createdDock;

    dock1->show();
    QVERIFY(layout->checkSanity());
    dock0->show();
    QVERIFY(layout->checkSanity());

    // Cleanup
    for (auto dock : DockRegistry::self()->dockwidgets())
        dock->deleteLater();

    QVERIFY(Testing::waitForDeleted(dock0));
}

void TestDocks::tst_negativeAnchorPosition6()
{
    // Tests a case when we add a widget to left/right but the layout doesn't have enough height (or vice-versa)
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    m->view()->resize(QSize(100, 100));
    m->show();

    auto layout = m->multiSplitter();

    auto w1 = new MyWidget2(QSize(400, 100));
    auto w2 = new MyWidget2(QSize(400, 100));
    auto w3 = new MyWidget2(QSize(400, 100));
    auto w4 = new MyWidget2(QSize(400, 900));
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
    layout->rectForDrop(nullptr, Location_OnTop, centralItem);
    layout->checkSanity();
}

void TestDocks::tst_negativeAnchorPosition7()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    m->show();
    auto w1 = new MyWidget2(QSize(400, 400));
    auto w2 = new MyWidget2(QSize(400, 400));

    auto d1 = new Controllers::DockWidget("1");
    d1->setWidget(w1);
    auto d2 = new Controllers::DockWidget("2");
    d2->setWidget(w2);

    auto w3 = new MyWidget2(QSize(100, 100));
    auto d3 = new Controllers::DockWidget("3");
    d3->setWidget(w3);

    // Stack 1, 2
    m->addDockWidget(d2, Location_OnTop);
    m->addDockWidget(d1, Location_OnTop);

    // add a small one to the middle

    // Stack: 1, 3, 2
    m->addDockWidget(d3, Location_OnTop, d2);
    m->layoutWidget()->checkSanity();
}

void TestDocks::tst_invalidAnchorGroup()
{
    // Tests a bug I got. Should not warn.
    EnsureTopLevelsDeleted e;

    {
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));

        QPointer<Controllers::FloatingWindow> fw = dock2->dptr()->morphIntoFloatingWindow();
        nestDockWidget(dock1, fw->dropArea(), nullptr, KDDockWidgets::Location_OnTop);

        dock1->close();
        Platform::instance()->tests_waitForResize(dock2->view());
        auto layout = fw->dropArea();
        layout->checkSanity();

        dock2->close();
        dock1->deleteLater();
        dock2->deleteLater();
        Testing::waitForDeleted(dock1);
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
        Testing::waitForDeleted(dock1);
    }
}

void TestDocks::tst_addAsPlaceholder()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new QPushButton("one"), {}, {}, false);
    auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, {}, false);

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnTop, nullptr, InitialVisibilityOption::StartHidden);

    auto dropArea = m->dropArea();
    Controllers::DropArea *layout = dropArea;

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    QVERIFY(!dock2->isVisible());

    dock2->show();
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 0);

    layout->checkSanity();

    // Cleanup
    dock2->deleteLater();
    Testing::waitForDeleted(dock2);
}

void TestDocks::tst_removeItem()
{
    // Tests that MultiSplitterLayout::removeItem() works
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, {}, false);
    auto dock3 = createDockWidget("dock3", new QPushButton("three"));

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnTop, nullptr, InitialVisibilityOption::StartHidden);
    Item *item2 = dock2->dptr()->lastPosition()->lastItem();

    auto dropArea = m->dropArea();
    Controllers::DropArea *layout = dropArea;

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);

    // 1. Remove an item that's a placeholder

    layout->removeItem(item2);

    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // 2. Remove an item that has an actual widget
    Item *item1 = dock1->dptr()->lastPosition()->lastItem();
    layout->removeItem(item1);
    QCOMPARE(layout->count(), 0);
    QCOMPARE(layout->placeholderCount(), 0);

    // 3. Remove an item that has anchors following one of its other anchors (Tests that anchors stop following)
    // Stack 1, 2, 3
    m->addDockWidget(dock3, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnBottom);
    m->addDockWidget(dock1, Location_OnBottom);
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 0);

    dock2->close();
    auto frame1 = dock1->dptr()->frame();
    dock1->close();
    QVERIFY(Testing::waitForDeleted(frame1));

    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 2);

    // Now remove the items
    layout->removeItem(dock2->dptr()->lastPosition()->lastItem());
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    layout->checkSanity();
    layout->removeItem(dock1->dptr()->lastPosition()->lastItem());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // Add again
    m->addDockWidget(dock2, Location_OnBottom);
    m->addDockWidget(dock1, Location_OnBottom);
    dock2->close();
    frame1 = dock1->dptr()->frame();
    dock1->close();
    QVERIFY(Testing::waitForDeleted(frame1));

    // Now remove the items, but first dock1
    layout->removeItem(dock1->dptr()->lastPosition()->lastItem());
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    layout->checkSanity();
    layout->removeItem(dock2->dptr()->lastPosition()->lastItem());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();

    // Add again, stacked as 1, 2, 3, then close 2 and 3.
    m->addDockWidget(dock2, Location_OnTop);
    m->addDockWidget(dock1, Location_OnTop);

    auto frame2 = dock2->dptr()->frame();
    dock2->close();
    Testing::waitForDeleted(frame2);

    auto frame3 = dock3->dptr()->frame();
    dock3->close();
    Testing::waitForDeleted(frame3);

    // The second anchor is now following the 3rd, while the 3rd is following 'bottom'
    layout->removeItem(dock3->dptr()->lastPosition()->lastItem()); // will trigger the 3rd anchor to
                                                                   // be removed
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    layout->checkSanity();

    dock1->deleteLater();
    dock2->deleteLater();
    dock3->deleteLater();
    Testing::waitForDeleted(dock3);
}

void TestDocks::tst_clear()
{
    // Tests MultiSplitterLayout::clear()
    EnsureTopLevelsDeleted e;
    QCOMPARE(Controllers::Frame::dbg_numFrames(), 0);

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    auto dock3 = createDockWidget("3", new QPushButton("3"));
    auto fw3 = dock3->floatingWindow();

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);
    QVERIFY(Testing::waitForDeleted(fw3));
    dock3->close();

    QCOMPARE(Controllers::Frame::dbg_numFrames(), 3);

    auto layout = m->multiSplitter();
    layout->clearLayout();

    QCOMPARE(layout->count(), 0);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();

    // Cleanup
    dock3->deleteLater();
    QVERIFY(Testing::waitForDeleted(dock3));
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
    QRect geo2 = dock2->dptr()->frame()->view()->geometry();
    dock2->setFloating(true);

    auto fw2 = dock2->floatingWindow();
    dock2->setFloating(false);
    QVERIFY(Testing::waitForDeleted(fw2));
    QCOMPARE(geo2, dock2->dptr()->frame()->view()->geometry());
    m->layoutWidget()->checkSanity();
}

void TestDocks::tst_startClosed()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));

    auto dropArea = m->dropArea();
    Controllers::DropArea *layout = dropArea;

    m->addDockWidget(dock1, Location_OnTop);
    Controllers::Frame *frame1 = dock1->dptr()->frame();
    dock1->close();
    Testing::waitForDeleted(frame1);

    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 1);

    m->addDockWidget(dock2, Location_OnTop);

    layout->checkSanity();

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);

    dock1->show();
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 0);
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

void TestDocks::tst_crash()
{
    // tests some crash I got

    EnsureTopLevelsDeleted e;

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
    auto layout = m->multiSplitter();

    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    Item *item1 = layout->itemForFrame(dock1->dptr()->frame());
    dock1->addDockWidgetAsTab(dock2);

    QVERIFY(!dock1->isFloating());
    dock1->setFloating(true);
    QVERIFY(dock1->isFloating());
    QVERIFY(!dock1->isInMainWindow());

    Item *layoutItem = dock1->dptr()->lastPosition()->lastItem();
    QVERIFY(layoutItem && DockRegistry::self()->itemIsInMainWindow(layoutItem));
    QCOMPARE(layoutItem, item1);

    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->count(), 1);

    // Move from tab to bottom
    m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
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
    auto layout = dropArea;
    QPointer<Controllers::Frame> frame1 = dock1->dptr()->frame();
    QPointer<Controllers::Frame> frame2 = dock2->dptr()->frame();
    QPointer<Item> item1 = layout->itemForFrame(frame1);
    QPointer<Item> item2 = layout->itemForFrame(frame2);
    QVERIFY(item1.data());
    QVERIFY(item2.data());
    QCOMPARE(item1->refCount(), 2); // 2 - the item and its frame, which can be persistent
    QCOMPARE(item2->refCount(), 2);

    // 1. Delete a dock widget directly. It should delete its frame and also the Item
    delete dock1;
    Testing::waitForDeleted(frame1);
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
    Testing::waitForDeleted(frame2);
    QVERIFY(dock2);
    QVERIFY(item2.data());
    QCOMPARE(item2->refCount(), 1);
    QCOMPARE(dock2->dptr()->lastPosition()->lastItem(), item2.data());
    delete dock2;

    QVERIFY(!item2.data());
    QCOMPARE(layout->count(), 1);

    // 4. Move a closed dock widget from one mainwindow to another
    // It should delete its old placeholder
    auto dock4 = createDockWidget("dock4", new QPushButton("4"));
    m->addDockWidget(dock4, KDDockWidgets::Location_OnLeft);

    QPointer<Controllers::Frame> frame4 = dock4->dptr()->frame();
    QPointer<Item> item4 = layout->itemForFrame(frame4);
    dock4->close();
    Testing::waitForDeleted(frame4);
    QCOMPARE(item4->refCount(), 1);
    QVERIFY(item4->isPlaceholder());
    layout->checkSanity();

    auto m2 = createMainWindow();
    m2->addDockWidget(dock4, KDDockWidgets::Location_OnLeft);
    m2->layoutWidget()->checkSanity();
    QVERIFY(!item4.data());
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
    auto layout = dropArea;

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

    Testing::waitForDeleted(fw);
}

void TestDocks::tst_availableLengthForOrientation()
{
    EnsureTopLevelsDeleted e;

    // 1. Test a completely empty window, it's available space is its size minus the static separators thickness
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    auto dropArea = m->dropArea();
    Controllers::DropArea *layout = dropArea;

    int availableWidth = layout->availableLengthForOrientation(Qt::Horizontal);
    int availableHeight = layout->availableLengthForOrientation(Qt::Vertical);
    QCOMPARE(availableWidth, layout->layoutWidth());
    QCOMPARE(availableHeight, layout->layoutHeight());

    // 2. Now do the same, but we have some widget docked

    auto dock1 = createDockWidget("dock1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);

    const int dock1MinWidth =
        layout->itemForFrame(dock1->dptr()->frame())->minLength(Qt::Horizontal);
    const int dock1MinHeight =
        layout->itemForFrame(dock1->dptr()->frame())->minLength(Qt::Vertical);

    availableWidth = layout->availableLengthForOrientation(Qt::Horizontal);
    availableHeight = layout->availableLengthForOrientation(Qt::Vertical);
    QCOMPARE(availableWidth, layout->layoutWidth() - dock1MinWidth);
    QCOMPARE(availableHeight, layout->layoutHeight() - dock1MinHeight);
    m->layoutWidget()->checkSanity();
}

void TestDocks::tst_closeShowWhenNoCentralFrame()
{
    EnsureTopLevelsDeleted e;
    // Tests a crash I got when hiding and showing and no central frame

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    QPointer<Controllers::DockWidget> dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->close();
    m->layoutWidget()->checkSanity();

    QVERIFY(!dock1->dptr()->frame());
    QVERIFY(!Testing::waitForDeleted(dock1)); // It was being deleted due to a bug
    QVERIFY(dock1);
    dock1->show();
    m->layoutWidget()->checkSanity();
}

void TestDocks::tst_setAsCurrentTab()
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
    fw->layoutWidget()->checkSanity();

    delete dock1;
    delete dock2;
    Testing::waitForDeleted(fw);
}

void TestDocks::tst_placeholderDisappearsOnReadd()
{
    // This tests that addMultiSplitter also updates refcount of placeholders

    // 1. Detach a widget and dock it on the opposite side. Placeholder
    // should have been deleted and anchors properly positioned

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    Controllers::DropArea *layout = m->multiSplitter();

    QPointer<Controllers::DockWidget> dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    dock1->setFloating(true);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 1);

    dock1->dptr()->morphIntoFloatingWindow();
    auto fw = dock1->floatingWindow();
    layout->addMultiSplitter(fw->dropArea(), Location_OnRight);

    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->count(), 1);

    layout->checkSanity();
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // The dock1 should occupy the entire width
    QCOMPARE(dock1->dptr()->frame()->width(), layout->layoutWidth());

    QVERIFY(Testing::waitForDeleted(fw));
}

void TestDocks::tst_placeholdersAreRemovedProperly()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    Controllers::DropArea *layout = m->multiSplitter();
    QPointer<Controllers::DockWidget> dock1 = createDockWidget("1", new QPushButton("1"));
    QPointer<Controllers::DockWidget> dock2 = createDockWidget("2", new QPushButton("2"));
    m->addDockWidget(dock1, Location_OnLeft);
    Item *item = layout->items().constFirst();
    m->addDockWidget(dock2, Location_OnRight);
    QVERIFY(!item->isPlaceholder());
    dock1->setFloating(true);
    QVERIFY(item->isPlaceholder());

    QCOMPARE(layout->separators().size(), 0);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    layout->removeItem(item);
    QCOMPARE(layout->separators().size(), 0);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // 2. Recreate the placeholder. This time delete the dock widget to see if placeholder is deleted too.
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->setFloating(true);
    delete dock1;
    QCOMPARE(layout->separators().size(), 0);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();
}

void TestDocks::tst_floatMaintainsSize()
{
    // Tests that when we make a window float by pressing the float button, it will popup with
    // the same size it had when docked

    EnsureTopLevelsDeleted e;
    auto dw1 = new Controllers::DockWidget("1");
    auto dw2 = new Controllers::DockWidget("2");

    dw1->addDockWidgetToContainingWindow(dw2, Location_OnRight);
    const int oldWidth2 = dw2->width();
    dw1->show();

    dw2->setFloating(true);
    QTest::qWait(100);

    QVERIFY(qAbs(dw2->width() - oldWidth2) < 16); // 15px for margins
}

void TestDocks::tst_preferredInitialSize()
{
    EnsureTopLevelsDeleted e;
    auto dw1 = new Controllers::DockWidget("1");
    auto dw2 = new Controllers::DockWidget("2");
    auto m = createMainWindow(QSize(1200, 1200), MainWindowOption_None);

    m->addDockWidget(dw1, Location_OnTop);
    m->addDockWidget(dw2, Location_OnBottom, nullptr, QSize(0, 200));

    QCOMPARE(dw2->dptr()->frame()->height(), 200);
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
        auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
        auto layout = m->multiSplitter();
        m->setVisible(show);

        Controllers::DockWidget::List docks;
        const int num = 4;
        for (int i = 0; i < num; ++i)
            docks << new Controllers::DockWidget(QString::number(i));

        QVector<KDDockWidgets::Location> locations = { Location_OnLeft,
                                                       Location_OnRight, Location_OnRight, Location_OnRight };

        QVector<KDDockWidgets::InitialVisibilityOption> options = { InitialVisibilityOption::StartHidden,
                                                                    InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartVisible, InitialVisibilityOption::StartHidden };

        QVector<bool> floatings = { true, false, false, false };

        for (int i = 0; i < num; ++i) {

            m->addDockWidget(docks[i], locations[i], nullptr, options[i]);
            layout->checkSanity();
            docks[i]->setFloating(floatings[i]);
        }

        qDeleteAll(docks);
        qDeleteAll(DockRegistry::self()->frames());
    }

    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
        auto layout = m->multiSplitter();
        m->show();

        const int num = 3;
        Controllers::DockWidget::List docks;
        for (int i = 0; i < num; ++i)
            docks << new Controllers::DockWidget(QString::number(i));

        QVector<KDDockWidgets::Location> locations = { Location_OnLeft, Location_OnLeft,
                                                       Location_OnRight };

        QVector<KDDockWidgets::InitialVisibilityOption> options = { InitialVisibilityOption::StartVisible, InitialVisibilityOption::StartVisible,
                                                                    InitialVisibilityOption::StartHidden };

        QVector<bool> floatings = { true, false, false };

        for (int i = 0; i < num; ++i) {
            m->addDockWidget(docks[i], locations[i], nullptr, options[i]);
            layout->checkSanity();
            if (i == 2) {
                // Wait for the resizes. This used to make the app crash.
                QTest::qWait(1000);
            }

            docks[i]->setFloating(floatings[i]);
        }
        layout->checkSanity();

        qDeleteAll(docks);
        qDeleteAll(DockRegistry::self()->frames());
    }
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

    QPointer<Controllers::FloatingWindow> fw = dock3->dptr()->morphIntoFloatingWindow();

    nestDockWidget(dock4, dropArea, nullptr, KDDockWidgets::Location_OnRight);
    nestDockWidget(dock5, dropArea, nullptr, KDDockWidgets::Location_OnTop);

    const int oldFWHeight = fw->height();
    nestDockWidget(dock6, fw->dropArea(), nullptr, KDDockWidgets::Location_OnTop);

    QVERIFY(oldFWHeight <= fw->height());
    QCOMPARE(fw->frames().size(), 2);

    QVERIFY(dock3->window()->equals(fw->view()));
    QVERIFY(dock4->window()->equals(m->view()));
    QVERIFY(dock5->window()->equals(m->view()));
    QVERIFY(dock6->window()->equals(fw->view()));
    auto layout = m->multiSplitter();
    layout->checkSanity();
    DockRegistry::self()->clear();
    layout->checkSanity();

    Testing::waitForDeleted(fw);
    QVERIFY(!fw);

    QVERIFY(dock1->window()->equals(dock1->view()));
    QVERIFY(dock2->window()->equals(dock2->view()));
    QVERIFY(dock3->window()->equals(dock3->view()));
    QVERIFY(dock4->window()->equals(dock4->view()));
    QVERIFY(dock5->window()->equals(dock5->view()));
    QVERIFY(dock6->window()->equals(dock6->view()));

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

void TestDocks::tst_toggleMiddleDockCrash()
{
    // tests some crash I got

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    Controllers::DropArea *layout = m->multiSplitter();
    QPointer<Controllers::DockWidget> dock1 = createDockWidget("1", new QPushButton("1"));
    QPointer<Controllers::DockWidget> dock2 = createDockWidget("2", new QPushButton("2"));
    QPointer<Controllers::DockWidget> dock3 = createDockWidget("3", new QPushButton("3"));

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);

    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 0);

    auto frame = dock2->dptr()->frame();
    dock2->close();
    QVERIFY(Testing::waitForDeleted(frame));

    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 1);
    QVERIFY(layout->checkSanity());

    dock2->show();
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
    auto dropArea2 = m2->dropArea();

    m1->addDockWidget(dock1, Location_OnRight);
    m1->addDockWidget(dock2, Location_OnRight);
    m2->addDockWidget(dock3, Location_OnRight);
    m2->addDockWidget(dock4, Location_OnRight);

    // 1. MainWindow #1 steals a widget from MainWindow2 and vice-versa
    m1->addDockWidget(dock3, Location_OnRight);
    m1->addDockWidget(dock4, Location_OnRight);
    m2->addDockWidget(dock1, Location_OnRight);
    QPointer<Item> item2 = dropArea1->itemForFrame(dock2->dptr()->frame());
    m2->addDockWidget(dock2, Location_OnRight);
    QVERIFY(!item2.data());

    QCOMPARE(dropArea1->count(), 2);
    QCOMPARE(dropArea2->count(), 2);
    QCOMPARE(dropArea1->placeholderCount(), 0);
    QCOMPARE(dropArea2->placeholderCount(), 0);

    // 2. MainWindow #1 steals a widget from MainWindow2 and vice-versa, but adds as tabs
    dock1->addDockWidgetAsTab(dock3);
    QPointer<Controllers::Frame> f2 = dock2->dptr()->frame();
    dock4->addDockWidgetAsTab(dock2);
    QVERIFY(Testing::waitForDeleted(f2.data()));
    QVERIFY(!f2.data());

    QCOMPARE(dropArea1->count(), 1);
    QCOMPARE(dropArea2->count(), 1);
    QCOMPARE(dropArea1->placeholderCount(), 0);
    QCOMPARE(dropArea2->placeholderCount(), 0);

    // 3. Test stealing a tab from the same tab-widget we're in. Nothing happens
    {
        SetExpectedWarning sew("Already contains KDDockWidgets::Controllers::DockWidget"); // Suppress the qFatal this time
        dock1->addDockWidgetAsTab(dock3);
        QCOMPARE(dock1->dptr()->frame()->dockWidgetCount(), 2);
    }

    // 4. Steal from another tab which resides in another Frame, which resides in the same main window
    m1->addDockWidget(dock1, Location_OnTop);
    f2 = dock2->dptr()->frame();
    dock1->addDockWidgetAsTab(dock2);
    QCOMPARE(dock1->dptr()->frame()->dockWidgetCount(), 2);
    QCOMPARE(dock4->dptr()->frame()->dockWidgetCount(), 1);

    QCOMPARE(dropArea1->count(), 2);
    QCOMPARE(dropArea1->placeholderCount(), 0);

    // 5. And also steal a side-by-side one into the tab
    QPointer<Controllers::Frame> f4 = dock4->dptr()->frame();
    dock1->addDockWidgetAsTab(dock4);
    QVERIFY(Testing::waitForDeleted(f4.data()));
    QCOMPARE(dropArea1->count(), 1);
    QCOMPARE(dropArea1->placeholderCount(), 0);

    // 6. Steal from tab to side-by-side within the same MainWindow
    m1->addDockWidget(dock1, Location_OnLeft);
    QCOMPARE(dropArea1->count(), 2);
    QCOMPARE(dropArea1->placeholderCount(), 0);

    // 6. side-by-side to side-by-side within same MainWindow
    m2->addDockWidget(dock1, Location_OnRight);
    QCOMPARE(dropArea2->count(), 2);
    QCOMPARE(dropArea2->placeholderCount(), 0);

    {
        SetExpectedWarning sew("Invalid parameters KDDockWidgets::Controllers::DockWidget"); // Suppress the qFatal this time
        m2->addDockWidget(dock1, Location_OnLeft, dock1);
        QCOMPARE(dropArea2->count(), 2); // Nothing happened
        QCOMPARE(dropArea2->placeholderCount(), 0);
        QVERIFY(dock1->isVisible());
    }

    QVERIFY(dock1->isVisible());
    m2->addDockWidget(dock1, Location_OnLeft, nullptr); // Should not warn

    QVERIFY(dock1->isVisible());
    QCOMPARE(dropArea2->count(), 2); // Nothing happened
    QCOMPARE(dropArea2->placeholderCount(), 0);

    m2->addDockWidget(dock1, Location_OnLeft, nullptr);
    QVERIFY(dock1->isVisible());
    QCOMPARE(dropArea2->count(), 2); // Nothing happened
    QCOMPARE(dropArea2->placeholderCount(), 0);
    dropArea1->checkSanity();
    dropArea2->checkSanity();
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
    QCOMPARE(dock2->dptr()->frame()->dockWidgetCount(), 2);
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

    dock2->setFloating(true);
    QVERIFY(dock1->isTabbed());
    QVERIFY(!dock2->isTabbed());
    QVERIFY(!dock1->isFloating());
    QVERIFY(dock2->isFloating());

    QCOMPARE(dock2->dptr()->lastPosition()->lastTabIndex(), 1);
    QVERIFY(dock2->dptr()->lastPosition()->isValid());
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
    QCOMPARE(dock2->dptr()->frame()->indexOfDockWidget(dock2), 1);

    // 10. Float dock1, and dock it to main window as tab. This tests Option_AlwaysShowsTabs.
    dock1->setFloating(true);
    dock2->setFloating(true);
    dock3->setFloating(true);

    m->addDockWidgetAsTab(dock1);
    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->isTabbed());
    dock1->setFloating(true);
    dock1->setFloating(false);
    QCOMPARE(dock1->dptr()->frame()->dockWidgetCount(), 1);
    // Cleanup
    m->addDockWidgetAsTab(dock2);
    m->addDockWidgetAsTab(dock3);
    m->deleteLater();
    auto window = m.release();
    Testing::waitForDeleted(window);
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

        QPointer<Controllers::Frame> frame1 = dock1->dptr()->frame();
        dock1->setFloating(true);
        QVERIFY(dock1->isFloating());
        auto fw = dock1->floatingWindow();
        QVERIFY(fw);

        // 2. Put it back, via setFloating(). It should return to its place.
        dock1->setFloating(false);

        QVERIFY(!dock1->isFloating());
        QVERIFY(!dock1->isTabbed());

        Testing::waitForDeleted(fw);
    }

    {
        // 2. Tests a case where restoring a dock widget wouldn't make it use all its available space
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        auto dock3 = createDockWidget("dock3", new QPushButton("three"));
        auto dropArea = m->dropArea();
        Controllers::DropArea *layout = dropArea;
        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);
        m->addDockWidget(dock3, KDDockWidgets::Location_OnRight);
        auto f2 = dock2->dptr()->frame();
        Item *item2 = layout->itemForFrame(f2);
        QVERIFY(item2);
        dock2->close();
        dock3->close();
        Testing::waitForDeleted(f2);
        dock2->show();
        Platform::instance()->tests_waitForResize(dock2->view());

        QCOMPARE(item2->geometry(), dock2->dptr()->frame()->view()->geometry());
        layout->checkSanity();

        // Cleanup
        dock3->deleteLater();
        Testing::waitForDeleted(dock3);
    }
}

void TestDocks::tst_dockWindowWithTwoSideBySideFramesIntoCenter()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setInternalFlags(KDDockWidgets::Config::InternalFlag_NoAeroSnap);
    KDDockWidgets::Config::self().setFlags({});

    auto m = createMainWindow();
    auto fw = createFloatingWindow();
    auto dock2 = createDockWidget("doc2", Qt::red);
    nestDockWidget(dock2, fw->dropArea(), nullptr, KDDockWidgets::Location_OnLeft);
    QCOMPARE(fw->frames().size(), 2);
    QVERIFY(fw->dropArea()->checkSanity());

    auto fw2 = createFloatingWindow();
    fw2->view()->move(fw->x() + fw->width() + 100, fw->y());

    // QtQuick is a bit more async than QWidgets. Wait for the move.
    Platform::instance()->tests_waitForEvent(fw2->view()->window(), QEvent::Move);

    auto da2 = fw2->dropArea();
    const QPoint dragDestPos = da2->mapToGlobal(da2->rect().center());

    dragFloatingWindowTo(fw, dragDestPos);
    QVERIFY(fw2->dropArea()->checkSanity());

    QCOMPARE(fw2->frames().size(), 1);
    auto f2 = fw2->frames().constFirst();
    QCOMPARE(f2->dockWidgetCount(), 3);
    QVERIFY(Testing::waitForDeleted(fw));
    delete fw2;
}

void TestDocks::tst_tabTitleChanges()
{
    // Tests that the tab's title changes if the dock widget's title changes
    EnsureTopLevelsDeleted e;
    auto dw1 = new Controllers::DockWidget(QStringLiteral("1"));
    auto dw2 = new Controllers::DockWidget(QStringLiteral("2"));

    dw1->addDockWidgetAsTab(dw2);

    Controllers::TabBar *tb = dw1->dptr()->frame()->tabWidget()->tabBar();
    QCOMPARE(tb->text(0), QStringLiteral("1"));
    dw1->setTitle(QStringLiteral("other"));
    QCOMPARE(tb->text(0), QStringLiteral("other"));
}

void TestDocks::tst_dockWidgetGetsFocusWhenDocked()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_TitleBarIsFocusable);

    // We drag dw2 onto dw2 and drop it

    auto dw1 = new Controllers::DockWidget(QStringLiteral("1"));
    auto dw2 = new Controllers::DockWidget(QStringLiteral("2"));
    auto le1 = new FocusableWidget();
    auto le2 = new FocusableWidget();
    dw1->setWidget(le1);
    dw2->setWidget(le2);
    dw2->show();
    dw1->show();
    QTest::qWait(200);

    auto fw1 = dw1->floatingWindow();
    QPointer<Controllers::FloatingWindow> fw2 = dw2->floatingWindow();

    // Focus dock widget 1 first
    QVERIFY(!dw1->isFocused());
    dw1->window()->activateWindow();
    le1->setFocus(Qt::MouseFocusReason);
    QTest::qWait(200);
    QVERIFY(dw1->isFocused());

    QVERIFY(fw1->view()->isActiveWindow());
    dragFloatingWindowTo(fw2, fw1->dropArea(), DropLocation_Left);
    Platform::instance()->tests_waitForEvent(fw1, QEvent::WindowActivate);

    /// We dropped into floating window 1, it should still be active
    QVERIFY(fw1->view()->isActiveWindow());

    // DockWidget 2 was dropped, it should now be focused
    QVERIFY(!dw1->isFocused());
    QVERIFY(dw2->isFocused());

    delete fw1;
    delete fw2;
}

void TestDocks::tst_isFocused()
{
    EnsureTopLevelsDeleted e;

    // 1. Create 2 floating windows
    auto dock1 = createDockWidget(QStringLiteral("dock1"), new FocusableWidget());
    auto dock2 = createDockWidget(QStringLiteral("dock2"), new FocusableWidget());

    QTest::qWait(200); // macOS is flaky here, needs dock2 to be shown first before focusing dock1, otherwise dock1 looses again

    dock1->window()->move(400, 200);

    // 2. Raise dock1 and focus its line edit
    dock1->raise();
    dock1->guestView()->setFocus(Qt::OtherFocusReason);
    Platform::instance()->tests_waitForEvent(dock1->guestView().get(), QEvent::FocusIn);

    QVERIFY(dock1->isFocused());
    QVERIFY(!dock2->isFocused());

    // 3. Raise dock2 and focus its line edit
    dock2->view()->raiseAndActivate();
    if (!dock2->window()->window()->isActive())
        Platform::instance()->tests_waitForEvent(dock2->view()->window(), QEvent::WindowActivate);

    dock2->guestView()->setFocus(Qt::OtherFocusReason);
    Platform::instance()->tests_waitForEvent(dock1->guestView().get(), QEvent::FocusIn);

    QVERIFY(!dock1->isFocused());
    QVERIFY(dock2->guestView()->hasFocus());
    QVERIFY(dock2->isFocused());

    // 4. Tab dock1, it's current tab now
    auto oldFw1 = dock1->window();
    dock2->addDockWidgetAsTab(dock1);
    QVERIFY(dock1->isFocused());
    QVERIFY(!dock2->isFocused());

    // 5. Set dock2 as current tab again
    dock2->raise();
    QVERIFY(!dock1->isFocused());
    QVERIFY(dock2->isFocused());

    // 6. Create dock3, focus it
    auto dock3 = createDockWidget(QStringLiteral("dock3"), new FocusableWidget());
    auto oldFw3 = dock3->window();
    dock3->raise();
    dock3->guestView()->setFocus(Qt::OtherFocusReason);
    Platform::instance()->tests_waitForEvent(dock1->guestView().get(), QEvent::FocusIn);
    QVERIFY(!dock1->isFocused());
    QVERIFY(!dock2->isFocused());
    QVERIFY(dock3->isFocused());

    // 4. Add dock3 to the 1st window, nested, focus 2 again
    dock2->addDockWidgetToContainingWindow(dock3, Location_OnLeft);
    dock2->raise();
    dock2->guestView()->setFocus(Qt::OtherFocusReason);
    Platform::instance()->tests_waitForEvent(dock2->guestView().get(), QEvent::FocusIn);
    QVERIFY(!dock1->isFocused());
    QVERIFY(dock2->isFocused());
    QVERIFY(!dock3->isFocused());
}

void TestDocks::tst_setWidget()
{
    EnsureTopLevelsDeleted e;
    auto dw = new Controllers::DockWidget(QStringLiteral("FOO"));
    auto button1 = new QPushButton("button1");
    auto button2 = new QPushButton("button2");
    dw->setWidget(button1);
    dw->setWidget(button2);
    delete button1;
    delete dw;
}

void TestDocks::tst_floatingLastPosAfterDoubleClose()
{
    EnsureTopLevelsDeleted e;
    auto d1 = new Controllers::DockWidget(QStringLiteral("a"));
    QVERIFY(d1->dptr()->lastPosition()->lastFloatingGeometry().isNull());
    QVERIFY(!d1->isVisible());
    d1->close();
    QVERIFY(d1->dptr()->lastPosition()->lastFloatingGeometry().isNull());
    delete d1;
}

void TestDocks::tst_0_data()
{
    QTest::addColumn<int>("thickness");
    QTest::newRow("2") << 2;
    QTest::newRow("1") << 1;
    QTest::newRow("0") << 0;
}

void TestDocks::tst_0()
{
    QFETCH(int, thickness);
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setSeparatorThickness(thickness);

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    m->view()->resize(QSize(502, 500));
    m->show();

    auto d1 = createDockWidget("1", new QTextEdit());
    auto d2 = createDockWidget("2", new QTextEdit());

    m->addDockWidget(d1, Location_OnLeft);
    m->addDockWidget(d2, Location_OnRight);
}

void TestDocks::tst_honourGeometryOfHiddenWindow()
{
    EnsureTopLevelsDeleted e;

    auto d1 = new Controllers::DockWidget("1");
    d1->setWidget(new QTextEdit());

    QVERIFY(!d1->isVisible());

    // Clear had a bug where it saved the position of all dock widgets being closed
    DockRegistry::self()->clear();

    const QRect suggestedGeo(150, 150, 250, 250);
    d1->view()->setGeometry(suggestedGeo);

    d1->show();
    Platform::instance()->tests_waitForEvent(d1, QEvent::Show);

    QCOMPARE(d1->window()->window()->geometry(), suggestedGeo);
}

void TestDocks::tst_registry()
{
    EnsureTopLevelsDeleted e;
    auto dr = DockRegistry::self();

    QCOMPARE(dr->dockwidgets().size(), 0);
    auto dw = new Controllers::DockWidget(QStringLiteral("dw1"));
    auto guest = new QWidgetOrQuick();
    auto wrapper = std::shared_ptr<ViewWrapper>(new Views::ViewWrapper_qtwidgets(guest)); // TODOv2 port

    dw->setWidget(guest);
    QCOMPARE(dr->dockWidgetForGuest(nullptr), nullptr);
    QCOMPARE(dr->dockWidgetForGuest(wrapper.get()), dw);
    delete dw;
}

void TestDocks::tst_dockWindowWithTwoSideBySideFramesIntoRight()
{
    EnsureTopLevelsDeleted e;

    auto fw = createFloatingWindow();
    auto dock2 = createDockWidget("doc2", Qt::red);
    nestDockWidget(dock2, fw->dropArea(), nullptr, KDDockWidgets::Location_OnTop); // No we stack on top, unlike in previous test
    QCOMPARE(fw->frames().size(), 2);

    auto fw2 = createFloatingWindow();
    fw2->view()->move(fw->x() + fw->width() + 100, fw->y());

    dragFloatingWindowTo(fw, fw2->dropArea(), DropLocation_Right); // Outer right instead of Left
    QCOMPARE(fw2->frames().size(), 3);
    QVERIFY(fw2->dropArea()->checkSanity());

    fw2->deleteLater();
    Testing::waitForDeleted(fw2);
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
    fw2->view()->move(fw->x() + fw->width() + 100, fw->y());

    QVERIFY(fw2->dropArea()->checkSanity());
    dragFloatingWindowTo(fw, fw2->dropArea(), DropLocation_Left);
    QCOMPARE(fw2->frames().size(), 3);

    QVERIFY(fw2->dropArea()->checkSanity());

    /// Cleanup
    fw2->deleteLater();
    Testing::waitForDeleted(fw2);
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
        QVERIFY(dock2->isVisible());
        drag(dock2->view(), globalDest);
        QVERIFY(fw->dropArea()->checkSanity());
        const QPoint actualEndPos = dock2->mapToGlobal(QPoint(0, 0));
        QVERIFY(actualEndPos.x() - globalSrc.x() < offset + 5); // 5px so we have margin for window system fluctuations. The actual bug was a very big jump like 50px, so a 5 margin is fine to test that the bug doesn't happen

        delete dock2;
        fw->deleteLater();
        Testing::waitForDeleted(fw);
    }

    {
        EnsureTopLevelsDeleted e;
        auto fw = createFloatingWindow();
        auto dock2 = createDockWidget("doc2", Qt::red);
        nestDockWidget(dock2, fw->dropArea(), nullptr, KDDockWidgets::Location_OnRight);
        QVERIFY(fw->dropArea()->checkSanity());

        const int originalX = dock2->mapToGlobal(QPoint(0, 0)).x();
        dock2->dptr()->frame()->titleBar()->makeWindow();
        const int finalX = dock2->mapToGlobal(QPoint(0, 0)).x();

        QVERIFY(finalX - originalX < 10); // 10 or some other small number that is less than say 200

        delete dock2;
        fw->deleteLater();
        Testing::waitForDeleted(fw);
    }
}

void TestDocks::tst_preventClose()
{
    EnsureTopLevelsDeleted e;

    auto nonClosableWidget = new NonClosableWidget();
    auto dock1 = new Controllers::DockWidget("1");
    dock1->setWidget(nonClosableWidget);

    // 1. Test a floating dock widget
    dock1->view()->resize(QSize(200, 200));
    dock1->show();
    QVERIFY(dock1->isVisible());
    dock1->close();
    QVERIFY(dock1->isVisible());

    // 2. Morph it into a FlatingWindow
    dock1->dptr()->morphIntoFloatingWindow();
    dock1->close();
    QVERIFY(dock1->isVisible());
    dock1->dptr()->frame()->titleBar()->onCloseClicked();
    QVERIFY(dock1->isVisible());
    auto fw = dock1->floatingWindow();
    fw->view()->close();
    QVERIFY(dock1->isVisible());

    dock1->deleteLater();
    QVERIFY(Testing::waitForDeleted(dock1));
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
    // QTest::qWait(50000);
}

void TestDocks::tst_createFloatingWindow()
{
    EnsureTopLevelsDeleted e;

    auto dock = createDockWidget("doc1", Qt::green);
    QVERIFY(dock);
    QVERIFY(dock->isFloating());

    QCOMPARE(dock->uniqueName(), QLatin1String("doc1")); // 1.0 objectName() is inherited

    QPointer<Controllers::FloatingWindow> window = dock->floatingWindow();
    QVERIFY(window); // 1.1 DockWidget creates a FloatingWindow and is reparented
    QVERIFY(window->dropArea()->checkSanity());
    dock->deleteLater();
    QVERIFY(Testing::waitForDeleted(dock));
    QVERIFY(Testing::waitForDeleted(window)); // 1.2 Floating Window is destroyed when DockWidget is destroyed
    QVERIFY(!window);
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
    m->layoutWidget()->checkSanity();
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->dptr()->frame()->titleBar()->makeWindow();
    m->layoutWidget()->checkSanity();
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->dptr()->frame()->titleBar()->makeWindow();
    m->layoutWidget()->checkSanity();

    auto fw = dock1->floatingWindow();
    QVERIFY(fw);
    auto dropArea = m->dropArea();
    dragFloatingWindowTo(fw, dropArea, DropLocation_Right);
    QVERIFY(dock1->dptr()->frame()->titleBar()->isVisible());
    fw->titleBar()->makeWindow();
    m->layoutWidget()->checkSanity();

    // Cleanup
    delete dock1;
    Testing::waitForDeleted(fw);
}

void TestDocks::tst_addToSmallMainWindow1()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new MyWidget2());
    auto dock2 = createDockWidget("dock2", new MyWidget2());
    auto dock3 = createDockWidget("dock3", new MyWidget2());
    auto dock4 = createDockWidget("dock4", new MyWidget2());

    const int mainWindowLength = 400;

    m->view()->window()->resize(mainWindowLength, mainWindowLength);
    QTest::qWait(100);

    dock1->view()->resize(QSize(800, 800));
    dock2->view()->resize(QSize(800, 800));
    dock3->view()->resize(QSize(800, 800));

    // Add as tabbed:
    m->addDockWidgetAsTab(dock1);

    QCOMPARE(m->height(), mainWindowLength);

    QTest::qWait(300);
    if (dock1->height() > mainWindowLength) {
        qDebug() << "dock1->height=" << dock1->height()
                 << "; mainWindowLength=" << mainWindowLength;
        QVERIFY(false);
    }

    QVERIFY(dock1->width() <= mainWindowLength);

    // Add in area:
    m->addDockWidget(dock2, Location_OnLeft);
    m->addDockWidget(dock3, Location_OnTop, dock2);
    m->addDockWidget(dock4, Location_OnBottom);

    auto dropArea = m->dropArea();

    QVERIFY(dropArea->checkSanity());
    QVERIFY(dock2->width() < mainWindowLength);
    QVERIFY(dock3->height() < m->height());
    QVERIFY(dock4->height() < m->height());
}

void TestDocks::tst_addToSmallMainWindow2()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(100, 100)));
    auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(100, 100)));
    m->addDockWidgetAsTab(dock1);
    m->view()->window()->resize(osWindowMinWidth(), 200);

    Platform::instance()->tests_waitForResize(m->view());

    QVERIFY(qAbs(m->width() - osWindowMinWidth()) < 15); // Not very important verification. Anyway, using 15 to account for margins and what not.
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);
#ifdef KDDOCKWIDGETS_QTWIDGETS
    QVERIFY(Platform::instance()->tests_waitForResize(m.get()));
#else
    QTest::qWait(100);
#endif

    QVERIFY(dropArea->layoutWidth() > osWindowMinWidth());
    QMargins margins = m->centerWidgetMargins();
    QCOMPARE(dropArea->layoutWidth(), m->width() - margins.left() - margins.right());
    QVERIFY(m->dropArea()->checkSanity());
}

void TestDocks::tst_addToSmallMainWindow3()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget("dock1", new MyWidget2());
    auto dock2 = createDockWidget("dock2", new MyWidget2());
    m->addDockWidgetAsTab(dock1);
    m->view()->window()->resize(osWindowMinWidth(), 200);
    QTest::qWait(200);
    QVERIFY(qAbs(m->width() - osWindowMinWidth()) < 15); // Not very important verification. Anyway, using 15 to account for margins and what not.

    auto fw = dock2->dptr()->morphIntoFloatingWindow();
    QVERIFY(fw->isVisible());
    QVERIFY(dropArea->checkSanity());
    dragFloatingWindowTo(fw, dropArea, DropLocation_Right);
    QVERIFY(m->dropArea()->checkSanity());
    delete fw;
}

void TestDocks::tst_addToSmallMainWindow4()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(100, 100), MainWindowOption_None);

    QTest::qWait(100);
    QCOMPARE(m->height(), 100);

    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(50, 50)));
    auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(50, 50)));
    Controllers::DropArea *layout = dropArea;
    m->addDockWidget(dock1, KDDockWidgets::Location_OnBottom);
    Platform::instance()->tests_waitForResize(m->view());

    m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);
    Platform::instance()->tests_waitForResize(m->view());
    QVERIFY(m->dropArea()->checkSanity());

    const int item2MinHeight =
        layout->itemForFrame(dock2->dptr()->frame())->minLength(Qt::Vertical);
    QCOMPARE(dropArea->layoutHeight(),
             dock1->dptr()->frame()->height() + item2MinHeight + Item::separatorThickness);
}

void TestDocks::tst_addToSmallMainWindow5()
{
    EnsureTopLevelsDeleted e;
    // Test test shouldn't spit any warnings

    auto m = createMainWindow(QSize(100, 100), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(50, 240)));
    auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(50, 240)));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnBottom);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);
    QVERIFY(m->dropArea()->checkSanity());
}

void TestDocks::tst_fairResizeAfterRemoveWidget()
{
    // 1. Add 3 dock widgets horizontally, remove the middle one, make sure
    // both left and right widgets get a share of the new available space

    EnsureTopLevelsDeleted e;

    Controllers::DockWidget *dock1 = createDockWidget("dock1", new QPushButton("one"));
    Controllers::DockWidget *dock2 = createDockWidget("dock2", new QPushButton("two"));
    Controllers::DockWidget *dock3 = createDockWidget("dock3", new QPushButton("three"));

    dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);
    dock1->addDockWidgetToContainingWindow(dock3, Location_OnRight, dock2);

    auto fw = dock1->floatingWindow();

    QPointer<Controllers::Frame> frame2 = dock2->dptr()->frame();

    const int oldWidth1 = dock1->dptr()->frame()->width();
    const int oldWidth2 = dock2->dptr()->frame()->width();
    const int oldWidth3 = dock3->dptr()->frame()->width();
    Controllers::DropArea *layout = fw->dropArea();
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->visibleCount(), 3);
    QCOMPARE(layout->placeholderCount(), 0);

    delete dock2;
    QVERIFY(Platform::instance()->tests_waitForResize(dock1->view()));
    QVERIFY(!frame2);

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 2);
    QCOMPARE(layout->placeholderCount(), 0);

    const int delta1 = (dock1->dptr()->frame()->width() - oldWidth1);
    const int delta3 = (dock3->dptr()->frame()->width() - oldWidth3);

    qDebug() << "old1=" << oldWidth1
             << "; old3=" << oldWidth3
             << "; to spread=" << oldWidth2
             << "; Delta1=" << delta1
             << "; Delta3=" << delta3;

    QVERIFY(delta1 > 0);
    QVERIFY(delta3 > 0);
    QVERIFY(qAbs(delta3 - delta1) <= 1); // Both dock1 and dock3 should have increased by the same amount
}

void TestDocks::tst_invalidJSON_data()
{
    // Be sure that the main windows in the json are called "MyMainWindow1" and the dock widgets
    // dock-x where x starts at 0
    QTest::addColumn<QString>("layoutFileName");
    QTest::addColumn<int>("numDockWidgets");
    QTest::addColumn<QString>("expectedWarning");
    QTest::addColumn<bool>("expectedResult");
    QTest::newRow("unsupported-serialization-version") << "unsupported-serialization-version.json"
                                                       << 10
                                                       << "Serialization format is too old"
                                                       << false;
    QTest::newRow("invalid") << "invalid.json" << 29 << "" << false;
    QTest::newRow("overlapping-item") << "overlapping-item.json" << 2 << "Unexpected pos" << true;
}

void TestDocks::tst_invalidJSON()
{
    QFETCH(QString, layoutFileName);
    QFETCH(int, numDockWidgets);
    QFETCH(QString, expectedWarning);
    QFETCH(bool, expectedResult);

    const QString absoluteLayoutFileName = QStringLiteral(":/layouts/%1").arg(layoutFileName);

    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(800, 500), MainWindowOption_None, "MyMainWindow1");
    for (int i = 0; i < numDockWidgets; ++i) {
        createDockWidget(QStringLiteral("dock-%1").arg(i), new QPushButton("one"));
    }

    SetExpectedWarning sew(expectedWarning);

    LayoutSaver restorer;
    QCOMPARE(restorer.restoreFromFile(absoluteLayoutFileName), expectedResult);
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

    Controllers::DropArea *layout = m->multiSplitter();

    // Stack: 1, 2, 3 vertically
    m->addDockWidget(dock3, Location_OnTop);
    m->addDockWidget(dock2, Location_OnTop);
    m->addDockWidget(dock1, Location_OnTop);

    auto frame1 = dock1->dptr()->frame();
    auto frame2 = dock2->dptr()->frame();
    auto frame3 = dock3->dptr()->frame();
    QCOMPARE(frame1->view()->y(), 0);

    // Close 1
    dock1->close();
    Platform::instance()->tests_waitForResize(frame2->view());

    // Check that frame2 moved up to y=1
    QCOMPARE(frame2->view()->y(), 0);

    // Close 2
    dock2->close();
    Platform::instance()->tests_waitForResize(dock3->view());

    QVERIFY(layout->checkSanity());
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 2);

    // Check that frame3 moved up to y=1
    QCOMPARE(frame3->view()->y(), 0);

    // Now restore:
    auto toRestore1 = restore1First ? dock1 : dock2;
    auto toRestore2 = restore1First ? dock2 : dock1;

    toRestore1->show();
    QCOMPARE(layout->placeholderCount(), 1);
    QVERIFY(dock3->isVisible());
    QVERIFY(!dock3->size().isNull());

    toRestore2->show();

    Platform::instance()->tests_waitForResize(frame3->view());
    QVERIFY(layout->checkSanity());
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();

    dock1->deleteLater();
    dock2->deleteLater();
    QVERIFY(Testing::waitForDeleted(dock2));
}

void TestDocks::tst_setVisibleFalseWhenSideBySide_data()
{
    QTest::addColumn<bool>("useSetVisible");
    QTest::newRow("false") << false;
    // QTest::newRow("true") << true; // We don't support closing dock widgets via setVisible(false). (Yet ? Maybe never).
}

void TestDocks::tst_setVisibleFalseWhenSideBySide()
{
    QFETCH(bool, useSetVisible);

    auto setVisible = [useSetVisible](Controllers::DockWidget *dw, bool visible) {
        if (useSetVisible)
            dw->setVisible(visible);
        else if (visible)
            dw->show();
        else
            dw->close();
    };

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

    const QRect oldGeo = dock1->geometry();
    auto oldParent = dock1->view()->parentView();

    // 1. Just toggle visibility and check that stuff remained sane
    QVERIFY(dock1->titleBar()->isVisible());
    setVisible(dock1, false);

    QVERIFY(!dock1->titleBar());
    QVERIFY(!dock1->isTabbed());
    QVERIFY(dock1->isFloating());

    setVisible(dock1, true);
    QVERIFY(dock1->titleBar()->isVisible());
    QVERIFY(!dock1->isTabbed());
    QVERIFY(!dock1->isFloating());
    QCOMPARE(dock1->geometry(), oldGeo);
    QVERIFY(dock1->view()->parentView()->equals(oldParent));

    // 2. Check that the parent frame also is hidden now
    // auto fw1 = dock1->window();
    setVisible(dock1, false);
    QVERIFY(!dock1->dptr()->frame());
    delete dock1;
}

void TestDocks::tst_restoreSimplest()
{
    EnsureTopLevelsDeleted e;
    // Tests restoring a very simple layout, composed of just 1 docked widget
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto layout = m->multiSplitter();
    auto dock1 = createDockWidget("one", new QTextEdit());
    m->addDockWidget(dock1, Location_OnTop);

    LayoutSaver saver;
    QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreSimplest.json")));
    QTest::qWait(200);
    QVERIFY(layout->checkSanity());
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreSimplest.json")));
    QVERIFY(layout->checkSanity());
}

void TestDocks::tst_restoreNonClosable()
{
    // Tests that restoring state also restores the Option_NotClosable option

    {
        // Basic case:

        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("one", new QTextEdit(), Controllers::DockWidget::Option_NotClosable);
        QCOMPARE(dock1->options(), Controllers::DockWidget::Option_NotClosable);

        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();
        QVERIFY(saver.restoreLayout(saved));
        QCOMPARE(dock1->options(), Controllers::DockWidget::Option_NotClosable);
    }

    {
        // Case from issue #137
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);

        auto dock1 = createDockWidget("1", new QTextEdit());
        auto dock2 = createDockWidget("2", new QTextEdit(), Controllers::DockWidget::Option_NotClosable);
        auto dock3 = createDockWidget("3", new QTextEdit());

        m->addDockWidget(dock1, Location_OnLeft);
        m->addDockWidget(dock2, Location_OnLeft);
        m->addDockWidget(dock3, Location_OnLeft);

        QCOMPARE(dock2->options(), Controllers::DockWidget::Option_NotClosable);
        dock2->setFloating(true);
        QCOMPARE(dock2->options(), Controllers::DockWidget::Option_NotClosable);

        Controllers::TitleBar *tb = dock2->dptr()->frame()->actualTitleBar();
        QVERIFY(tb->isVisible());
        QVERIFY(!tb->closeButtonEnabled());

        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();

        QVERIFY(saver.restoreLayout(saved));
        QCOMPARE(dock2->options(), Controllers::DockWidget::Option_NotClosable);

        tb = dock2->dptr()->frame()->actualTitleBar();
        QVERIFY(tb->isVisible());

        QVERIFY(!tb->closeButtonEnabled());
    }
}

void TestDocks::tst_restoreRestoresMainWindowPosition()
{
    // Tests that MainWindow position is restored by LayoutSaver
    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        const QPoint originalPos = m->pos();

        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();

        m->view()->move(originalPos + QPoint(100, 100));

        saver.restoreLayout(saved);
        QCOMPARE(originalPos, m->pos());
    }
#ifdef KDDOCKWIDGETS_QTQUICK
    // Tests the ApplicationWindow {} case
    {
        QQmlApplicationEngine engine(":/main2.qml");

        const MainWindowBase::List mainWindows = DockRegistry::self()->mainwindows();
        QCOMPARE(mainWindows.size(), 1);
        MainWindowBase *mainWindow = mainWindows.first();
        QVERIFY(mainWindow->isVisible());

        QCOMPARE(mainWindow->pos(), QPoint(0, 0));

        QWindow *window = mainWindow->window();

        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();

        const QPoint originalPos = window->position();
        window->setPosition(originalPos + QPoint(200, 200));
        QCOMPARE(window->position(), originalPos + QPoint(200, 200));

        QVERIFY(saver.restoreLayout(saved));

        QCOMPARE(window->position(), originalPos);

        delete mainWindow;
    }
#endif
}

void TestDocks::tst_resizeViaAnchorsAfterPlaceholderCreation()
{
    EnsureTopLevelsDeleted e;

    // Stack 1, 2, 3, close 2, close 2
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        Controllers::DropArea *layout = m->multiSplitter();
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        auto dock3 = createDockWidget("dock3", new QPushButton("three"));
        m->addDockWidget(dock3, Location_OnTop);
        m->addDockWidget(dock2, Location_OnTop);
        m->addDockWidget(dock1, Location_OnTop);
        QCOMPARE(layout->separators().size(), 2);
        dock2->close();
        Platform::instance()->tests_waitForResize(dock3->view());
        QCOMPARE(layout->separators().size(), 1);
        layout->checkSanity();

        // Cleanup:
        dock2->deleteLater();
        Testing::waitForDeleted(dock2);
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

        Controllers::DropArea *layout = m->multiSplitter();

        Item *item1 = layout->itemForFrame(dock1->dptr()->frame());
        Item *item2 = layout->itemForFrame(dock2->dptr()->frame());
        Item *item3 = layout->itemForFrame(dock3->dptr()->frame());
        Item *item4 = layout->itemForFrame(dock4->dptr()->frame());

        const auto separators = layout->separators();
        QCOMPARE(separators.size(), 3);

        Controllers::Separator *anchor1 = separators[0];
        int boundToTheRight = layout->rootItem()->maxPosForSeparator(anchor1);
        int expectedBoundToTheRight = layout->layoutWidth() - 3 * Item::separatorThickness - item2->minLength(Qt::Horizontal) - item3->minLength(Qt::Horizontal) - item4->minLength(Qt::Horizontal);

        QCOMPARE(boundToTheRight, expectedBoundToTheRight);

        dock3->close();
        Platform::instance()->tests_waitForResize(dock2->view());

        QVERIFY(!item1->isPlaceholder());
        QVERIFY(!item2->isPlaceholder());
        QVERIFY(item3->isPlaceholder());
        QVERIFY(!item4->isPlaceholder());

        boundToTheRight = layout->rootItem()->maxPosForSeparator(anchor1);
        expectedBoundToTheRight = layout->layoutWidth() - 2 * Item::separatorThickness - item2->minLength(Qt::Horizontal) - item4->minLength(Qt::Horizontal);

        QCOMPARE(boundToTheRight, expectedBoundToTheRight);
        dock3->deleteLater();
        Testing::waitForDeleted(dock3);
    }
}

void TestDocks::tst_rectForDropCrash()
{
    // Tests a crash I got in MultiSplitterLayout::rectForDrop() (asserts being hit)
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();
    m->view()->resize(QSize(500, 500));
    m->show();

    auto layout = m->multiSplitter();

    auto w1 = new MyWidget2(QSize(400, 400));
    auto w2 = new MyWidget2(QSize(400, 400));

    auto d1 = createDockWidget("1", w1);
    auto d2 = createDockWidget("2", w2);

    m->addDockWidget(d1, Location_OnTop);
    Item *centralItem = m->dropArea()->centralFrame();
    {
        WindowBeingDragged wbd2(d2->floatingWindow());
        layout->rectForDrop(&wbd2, Location_OnTop, centralItem);
    }
    layout->checkSanity();
}

void TestDocks::tst_restoreAfterResize()
{
    // Tests a crash I got when the layout received a resize event *while* restoring

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(500, 500), {}, "tst_restoreAfterResize");
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);
    auto layout = m->multiSplitter();
    const QSize oldContentsSize = layout->layoutSize();
    const QSize oldWindowSize = m->size();
    LayoutSaver saver;
    QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreAfterResize.json")));
    m->view()->resize(QSize(1000, 1000));
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreAfterResize.json")));
    QCOMPARE(oldContentsSize, layout->layoutSize());
    QCOMPARE(oldWindowSize, m->size());
}

void TestDocks::tst_restoreWithNonClosableWidget()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(500, 500), {}, "tst_restoreWithNonClosableWidget");
    auto dock1 = createDockWidget("1", new NonClosableWidget(), Controllers::DockWidget::Option_NotClosable);
    m->addDockWidget(dock1, Location_OnLeft);
    auto layout = m->multiSplitter();

    LayoutSaver saver;
    QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreWithNonClosableWidget.json")));
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreWithNonClosableWidget.json")));
    QVERIFY(layout->checkSanity());
}

void TestDocks::tst_restoreNestedAndTabbed()
{
    // Just a more involved test

    QPoint oldFW4Pos;
    QRect oldGeo;
    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None, "tst_restoreNestedAndTabbed");
        m->view()->move(500, 500);
        oldGeo = m->geometry();
        auto layout = m->multiSplitter();
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
        QCOMPARE(dock2->dptr()->frame()->currentTabIndex(), 0);
        QCOMPARE(dock4->dptr()->frame()->currentTabIndex(), 1);

        LayoutSaver saver;
        QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreNestedAndTabbed.json")));
        QVERIFY(layout->checkSanity());

        // Let it be destroyed, we'll restore a new one
    }

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None, "tst_restoreNestedAndTabbed");
    auto layout = m->multiSplitter();
    auto dock1 = createDockWidget("1", new QTextEdit());
    auto dock2 = createDockWidget("2", new QTextEdit());
    auto dock3 = createDockWidget("3", new QTextEdit());
    auto dock4 = createDockWidget("4", new QTextEdit());
    auto dock5 = createDockWidget("5", new QTextEdit());

    LayoutSaver saver;
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreNestedAndTabbed.json")));
    QVERIFY(layout->checkSanity());

    auto fw4 = dock4->floatingWindow();
    QVERIFY(fw4);
    QCOMPARE(dock4->window()->window(), dock5->window()->window());
    QCOMPARE(fw4->pos(), oldFW4Pos);

    QVERIFY(dock1->window()->equals(m->view()));
    QVERIFY(dock2->window()->equals(m->view()));
    QVERIFY(dock3->window()->equals(m->view()));

    QCOMPARE(dock2->dptr()->frame()->currentTabIndex(), 0);
    QCOMPARE(dock4->dptr()->frame()->currentTabIndex(), 1);

    QCOMPARE(m->geometry(), oldGeo);
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
        QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreCrash.json")));
    }

    // Restore
    auto m = createMainWindow({}, {}, "tst_restoreCrash");
    auto layout = m->multiSplitter();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    QVERIFY(dock1->isFloating());
    QVERIFY(layout->checkSanity());

    LayoutSaver saver;
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreCrash.json")));
    QVERIFY(layout->checkSanity());
    QVERIFY(!dock1->isFloating());
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
        auto layout = m->multiSplitter();

        // FloatingWindow:
        auto dock2 = createDockWidget("2", new QPushButton("2"));
        auto dock3 = createDockWidget("3", new QPushButton("3"));
        dock2->addDockWidgetToContainingWindow(dock3, Location_OnRight);
        auto fw2 = dock2->floatingWindow();
        item2MinSize = fw2->layoutWidget()->itemForFrame(dock2->dptr()->frame())->minSize();
        LayoutSaver saver;
        QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreSideBySide.json")));
        QVERIFY(layout->checkSanity());
    }

    {
        auto m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralFrame, "tst_restoreTwice");
        auto dock1 = createDockWidget("1", new QPushButton("1"));
        auto dock2 = createDockWidget("2", new QPushButton("2"));
        auto dock3 = createDockWidget("3", new QPushButton("3"));

        LayoutSaver restorer;
        QVERIFY(restorer.restoreFromFile(QStringLiteral("layout_tst_restoreSideBySide.json")));

        DockRegistry::self()->checkSanityAll();

        QVERIFY(dock1->window()->equals(m->view()));
        QVERIFY(dock2->window()->equals(dock3->window()));
    }
}

void TestDocks::tst_restoreWithCentralFrameWithTabs()
{
    auto m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralFrame, "tst_restoreTwice");
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    m->addDockWidgetAsTab(dock1);
    m->addDockWidgetAsTab(dock2);

    QCOMPARE(DockRegistry::self()->frames().size(), 1);

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    QVERIFY(saver.restoreLayout(saved));

    QCOMPARE(DockRegistry::self()->frames().size(), 1);
}

void TestDocks::tst_restoreWithPlaceholder()
{
    // Float dock1, save and restore, then unfloat and see if dock2 goes back to where it was

    EnsureTopLevelsDeleted e;
    {
        auto m = createMainWindow(QSize(500, 500), {}, "tst_restoreWithPlaceholder");

        auto dock1 = createDockWidget("1", new QPushButton("1"));
        m->addDockWidget(dock1, Location_OnLeft);
        auto layout = m->multiSplitter();
        dock1->setFloating(true);

        LayoutSaver saver;
        QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreWithPlaceholder.json")));

        dock1->close();

        QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreWithPlaceholder.json")));
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
    auto layout = m->multiSplitter();

    LayoutSaver saver;
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreWithPlaceholder.json")));
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

void TestDocks::tst_restoreWithAffinity()
{
    EnsureTopLevelsDeleted e;

    auto m1 = createMainWindow(QSize(500, 500));
    m1->setAffinities({ "a1" });
    auto m2 = createMainWindow(QSize(500, 500));
    m2->setAffinities({ "a2" });

    auto dock1 = createDockWidget("1", new QPushButton("1"), {}, {}, true, "a1");
    m1->addDockWidget(dock1, Location_OnLeft);

    auto dock2 = createDockWidget("2", new QPushButton("2"), {}, {}, true, "a2");
    dock2->setFloating(true);
    dock2->show();

    LayoutSaver saver;
    saver.setAffinityNames({ "a1" });
    const QByteArray saved1 = saver.serializeLayout();

    QPointer<Controllers::FloatingWindow> fw2 = dock2->floatingWindow();
    saver.restoreLayout(saved1);

    // Restoring affinity 1 shouldn't close affinity 2
    QVERIFY(!fw2.isNull());
    QVERIFY(dock2->isVisible());

    // Close all and restore again
    DockRegistry::self()->clear();
    saver.restoreLayout(saved1);

    // dock2 continues closed
    QVERIFY(!dock2->isVisible());

    // dock1 was restored
    QVERIFY(dock1->isVisible());
    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->window()->equals(m1->view()));
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
        auto layout = m->multiSplitter();

        LayoutSaver saver;
        QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_marginsAfterRestore.json")));
        QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_marginsAfterRestore.json")));
        QVERIFY(layout->checkSanity());

        dock1->setFloating(true);

        auto fw = dock1->floatingWindow();
        QVERIFY(fw);
        layout->addWidget(fw->dropArea()->view(), Location_OnRight);

        layout->checkSanity();
    }
}

void TestDocks::tst_restoreWithNewDockWidgets()
{
    // Tests that if the LayoutSaver doesn't know about some dock widget
    // when it saves the layout, then it won't close it when restoring layout
    // it will just be ignored.
    EnsureTopLevelsDeleted e;
    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    QVERIFY(!saved.isEmpty());

    auto dock1 = createDockWidget("dock1", new QPushButton("dock1"));
    dock1->show();

    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(dock1->isVisible());
}

void TestDocks::tst_restoreWithDockFactory()
{
    // Tests that restore the layout with a missing dock widget will recreate the dock widget using a factory

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);
    auto layout = m->multiSplitter();

    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->visibleCount(), 1);

    LayoutSaver saver;
    QByteArray saved = saver.serializeLayout();
    QVERIFY(!saved.isEmpty());
    QPointer<Controllers::Frame> f1 = dock1->dptr()->frame();
    delete dock1;
    Testing::waitForDeleted(f1);
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
    DockWidgetFactoryFunc func = [](const QString &) {
        return createDockWidget("1", new QPushButton("1"), {}, {}, /*show=*/false);
    };

    KDDockWidgets::Config::self().setDockWidgetFactoryFunc(func);
    QVERIFY(saver.restoreLayout(saved));
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->visibleCount(), 1);
    layout->checkSanity();
}

void TestDocks::tst_restoreWithDockFactory2()
{
    // Teste that the factory function can do id remapping.
    // For example, if id "foo" is missing, the factory can return a
    // dock widget with id "bar" if it feels like it

    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);

    auto dock1 = createDockWidget("dw1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->setFloating(true);

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    delete dock1;

    DockWidgetFactoryFunc func = [](const QString &) {
        // A factory func which does id remapping
        return createDockWidget("dw2", new QPushButton("w"), {}, {}, /*show=*/false);
    };

    KDDockWidgets::Config::self().setDockWidgetFactoryFunc(func);
    saver.restoreLayout(saved);
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

    QVERIFY(dock1->window()->equals(m->view()));
    QVERIFY(dock2->window()->equals(m->view()));

    QVERIFY(dock1->dptr()->frame()->view()->y()
            > dock2->dptr()->frame()->view()->y());
    QCOMPARE(dock1->dptr()->frame()->view()->x(),
             dock2->dptr()->frame()->view()->x());
}

void TestDocks::tst_addDockWidgetToContainingWindow()
{
    { // Test with a floating window
        EnsureTopLevelsDeleted e;

        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        auto dock3 = createDockWidget("dock3", new QPushButton("three"));

        dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);
        dock1->addDockWidgetToContainingWindow(dock3, Location_OnTop, dock2);

        QVERIFY(dock1->window()->equals(dock2->window()));
        QVERIFY(dock2->window()->equals(dock3->window()));

        QVERIFY(dock3->dptr()->frame()->view()->y()
                < dock2->dptr()->frame()->view()->y());
        QVERIFY(dock1->dptr()->frame()->view()->x()
                < dock2->dptr()->frame()->view()->x());
        QCOMPARE(dock2->dptr()->frame()->view()->x(),
                 dock3->dptr()->frame()->view()->x());
    }

    { // Also test with a main window
        EnsureTopLevelsDeleted e;

        auto m = createMainWindow();
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));

        m->addDockWidget(dock1, Location_OnRight, nullptr);
        dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);

        QCOMPARE(dock1->window()->window(), dock2->window()->window());
        QVERIFY(m->view()->equals(dock2->window()));
    }
}

void TestDocks::tst_notClosable()
{
    {
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("dock1", new QPushButton("one"), Controllers::DockWidget::Option_NotClosable);
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        dock1->addDockWidgetAsTab(dock2);

        auto fw = dock1->floatingWindow();
        QVERIFY(fw);
        Controllers::TitleBar *titlebarFW = fw->titleBar();
        Controllers::TitleBar *titleBarFrame = fw->frames().at(0)->titleBar();
        QVERIFY(titlebarFW->isCloseButtonVisible());
        QVERIFY(!titlebarFW->isCloseButtonEnabled());
        QVERIFY(!titleBarFrame->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonEnabled());

        dock1->setOptions(Controllers::DockWidget::Option_None);
        QVERIFY(titlebarFW->isCloseButtonVisible());
        QVERIFY(titlebarFW->isCloseButtonEnabled());
        QVERIFY(!titleBarFrame->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonEnabled());

        dock1->setOptions(Controllers::DockWidget::Option_NotClosable);
        QVERIFY(titlebarFW->isCloseButtonVisible());
        QVERIFY(!titlebarFW->isCloseButtonEnabled());
        QVERIFY(!titleBarFrame->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonEnabled());
    }

    {
        // Now dock dock1 into dock1 instead
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("dock1", new QPushButton("one"), Controllers::DockWidget::Option_NotClosable);
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));

        dock2->dptr()->morphIntoFloatingWindow();
        dock2->addDockWidgetAsTab(dock1);

        auto fw = dock1->floatingWindow();
        QVERIFY(fw);
        Controllers::TitleBar *titlebarFW = fw->titleBar();
        Controllers::TitleBar *titleBarFrame = fw->frames().at(0)->titleBar();

        QVERIFY(titlebarFW->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonEnabled());
    }
}

void TestDocks::tst_dragOverTitleBar()
{
    // Tests that dragging over the title bar is returning DropLocation_None

    EnsureTopLevelsDeleted e;
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("Two"));

    DropArea *da = dock1->floatingWindow()->dropArea();
    Controllers::FloatingWindow *fw1 = dock1->floatingWindow();
    Controllers::FloatingWindow *fw2 = dock2->floatingWindow();
    {
        WindowBeingDragged wbd(fw2, fw2);

        const QPoint titleBarPoint = fw1->titleBar()->mapToGlobal(QPoint(5, 5));

        auto loc = da->hover(&wbd, titleBarPoint);
        QCOMPARE(loc, DropLocation_None);
    }

    delete fw1;
    delete fw2;
}

void TestDocks::tst_setFloatingGeometry()
{
    EnsureTopLevelsDeleted e;
    auto dock1 = createDockWidget("dock1", new MyWidget("one"));

    QVERIFY(dock1->isVisible());
    const QRect requestedGeo = QRect(70, 70, 400, 400);
    dock1->setFloatingGeometry(requestedGeo);
    QCOMPARE(dock1->window()->geometry(), requestedGeo);

    dock1->close();
    QVERIFY(!dock1->isVisible());

    const QRect requestedGeo2 = QRect(80, 80, 400, 400);
    dock1->setFloatingGeometry(requestedGeo2);
    dock1->show();

    QCOMPARE(dock1->window()->geometry(), requestedGeo2);
}

void TestDocks::tst_setFloatingAfterDraggedFromTabToSideBySide()
{
    EnsureTopLevelsDeleted e;
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        auto dropArea = m->dropArea();
        auto layout = dropArea;

        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        dock1->addDockWidgetAsTab(dock2);

        // Move from tab to bottom
        m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);

        dock2->setFloating(true);
        dock2->setFloating(false);
        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);
        QVERIFY(!dock2->isFloating());
    }

    {
        // 2. Try again, but now detach from tab before putting it on the bottom. What was happening was that MultiSplitterLayout::addWidget()
        // called with a MultiSplitter as widget wasn't setting the layout items for the dock widgets
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        auto dropArea = m->dropArea();
        auto layout = dropArea;

        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        dock1->addDockWidgetAsTab(dock2);
        Item *oldItem2 = dock2->dptr()->lastPosition()->lastItem();
        QCOMPARE(oldItem2, layout->itemForFrame(dock2->dptr()->frame()));


        // Detach tab
        dock1->dptr()->frame()->detachTab(dock2);
        QVERIFY(layout->checkSanity());
        auto fw2 = dock2->floatingWindow();
        QVERIFY(fw2);
        QCOMPARE(dock2->dptr()->lastPosition()->lastItem(), oldItem2);
        Item *item2 = fw2->dropArea()->itemForFrame(dock2->dptr()->frame());
        QVERIFY(item2);
        QVERIFY(item2->hostWidget()->equals(fw2->dropArea()->view()));
        QVERIFY(!layout->itemForFrame(dock2->dptr()->frame()));

        // Move from tab to bottom
        layout->addWidget(fw2->dropArea()->view(), KDDockWidgets::Location_OnRight, nullptr);
        QVERIFY(layout->checkSanity());
        QVERIFY(dock2->dptr()->lastPosition()->lastItem());
        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);

        dock2->setFloating(true);
        QVERIFY(layout->checkSanity());

        dock2->setFloating(false);

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);
        QVERIFY(!dock2->isFloating());
        QVERIFY(layout->checkSanity());

        Testing::waitForDeleted(fw2);
    }
}

void TestDocks::tst_setFloatingAFrameWithTabs()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dropArea = m->dropArea();
    auto layout = dropArea;
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->addDockWidgetAsTab(dock2);

    // Make it float
    dock1->dptr()->frame()->titleBar()->onFloatClicked();

    auto fw = dock1->floatingWindow();
    QVERIFY(fw);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);

    auto frame1 = dock1->dptr()->frame();
    QVERIFY(frame1->layoutItem());

    // Attach it again
    dock1->dptr()->frame()->titleBar()->onFloatClicked();

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 0);
    QVERIFY(dock1->window()->equals(m->view()));

    Testing::waitForDeleted(fw);
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

    const auto originalFlags = KDDockWidgets::Config::self().flags();

    auto newFlags = originalFlags;

    if (hiddenTitleBar)
        newFlags = newFlags | KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible;

    if (tabsAlwaysVisible)
        newFlags = newFlags | KDDockWidgets::Config::Flag_AlwaysShowTabs;

    KDDockWidgets::Config::self().setFlags(newFlags);

    auto m = createMainWindow();

    auto d1 = createDockWidget("1", new QTextEdit());
    auto d2 = createDockWidget("2", new QTextEdit());
    m->addDockWidget(d1, Location_OnTop);

    if (tabsAlwaysVisible) {
        if (hiddenTitleBar)
            QVERIFY(!d1->dptr()->frame()->titleBar()->isVisible());
        else
            QVERIFY(d1->dptr()->frame()->titleBar()->isVisible());
    } else {
        QVERIFY(d1->dptr()->frame()->titleBar()->isVisible());
    }

    d1->addDockWidgetAsTab(d2);

    QVERIFY(d2->dptr()->frame()->titleBar()->isVisible() ^ hiddenTitleBar);

    d2->close();
    m->layoutWidget()->checkSanity();
    delete d2;
    if (tabsAlwaysVisible) {
        if (hiddenTitleBar)
            QVERIFY(!d1->dptr()->frame()->titleBar()->isVisible());
        else
            QVERIFY(d1->dptr()->frame()->titleBar()->isVisible());
    } else {
        QVERIFY(d1->dptr()->frame()->titleBar()->isVisible());
    }
}

void TestDocks::tst_toggleDockWidgetWithHiddenTitleBar()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible | KDDockWidgets::Config::Flag_AlwaysShowTabs);
    auto m = createMainWindow();

    auto d1 = createDockWidget("1", new QTextEdit());
    m->addDockWidget(d1, Location_OnTop);

    QVERIFY(!d1->dptr()->frame()->titleBar()->isVisible());

    d1->toggleAction()->setChecked(false);
    auto f1 = d1->dptr()->frame();
    Testing::waitForDeleted(f1);
    d1->toggleAction()->setChecked(true);
    QVERIFY(d1->dptr()->frame());
    QVERIFY(!d1->dptr()->frame()->titleBar()->isVisible());
}

void TestDocks::tst_availableSizeWithPlaceholders()
{
    // Tests MultiSplitterLayout::available() with and without placeholders. The result should be the same.

    EnsureTopLevelsDeleted e;
    QVector<DockDescriptor> docks1 = {
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
    };

    QVector<DockDescriptor> docks2 = {
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
    };

    QVector<DockDescriptor> empty;

    auto m1 = createMainWindow(docks1);
    auto m2 = createMainWindow(docks2);
    auto m3 = createMainWindow(empty);

    auto layout1 = m1->multiSplitter();
    auto layout2 = m2->multiSplitter();
    auto layout3 = m3->multiSplitter();

    auto f20 = docks2.at(0).createdDock->dptr()->frame();

    docks2.at(0).createdDock->close();
    docks2.at(1).createdDock->close();
    docks2.at(2).createdDock->close();
    QVERIFY(Testing::waitForDeleted(f20));

    QCOMPARE(layout1->layoutSize(), layout2->layoutSize());
    QCOMPARE(layout1->layoutSize(), layout3->layoutSize());

    QCOMPARE(layout1->availableSize(), layout2->availableSize());
    QCOMPARE(layout1->availableSize(), layout3->availableSize());

    // Now show 1 widget in m1 and m3
    docks1.at(0).createdDock->show();
    m3->addDockWidget(docks2.at(0).createdDock, Location_OnBottom); // just steal from m2

    QCOMPARE(layout1->layoutSize(), layout3->layoutSize());

    Controllers::Frame *f10 = docks1.at(0).createdDock->dptr()->frame();
    Item *item10 = layout1->itemForFrame(f10);
    Item *item30 = layout3->itemForFrame(docks2.at(0).createdDock->dptr()->frame());

    QCOMPARE(item10->geometry(), item30->geometry());
    QCOMPARE(item10->guestView()->minSize(), item10->guestView()->minSize());
    QCOMPARE(item10->minSize(), item30->minSize());
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
    QVERIFY(Testing::waitForDeleted(docks2.at(2).createdDock));
}

void TestDocks::tst_anchorFollowingItselfAssert()
{
    // 1. Tests that we don't assert in Anchor::setFollowee()
    //  ASSERT: "this != m_followee" in file ../src/multisplitter/Anchor.cpp
    EnsureTopLevelsDeleted e;
    QVector<DockDescriptor> docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible }
    };

    auto m = createMainWindow(docks);
    auto dropArea = m->dropArea();
    Controllers::DropArea *layout = dropArea;
    layout->checkSanity();

    auto dock1 = docks.at(1).createdDock;
    auto dock2 = docks.at(2).createdDock;
    dock2->setFloating(true);
    auto fw2 = dock2->floatingWindow();
    dropArea->addWidget(fw2->dropArea()->view(), Location_OnLeft, dock1->dptr()->frame());
    dock2->setFloating(true);
    fw2 = dock2->floatingWindow();
    dropArea->addWidget(fw2->dropArea()->view(), Location_OnRight, dock1->dptr()->frame());

    docks.at(0).createdDock->deleteLater();
    docks.at(4).createdDock->deleteLater();
    Testing::waitForDeleted(docks.at(4).createdDock);
}

void TestDocks::tst_positionWhenShown()
{
    // Tests that when showing a dockwidget it shows in the same position as before
    EnsureTopLevelsDeleted e;
    auto window = createMainWindow();
    auto dock1 = new Controllers::DockWidget("1");
    dock1->show();
    dock1->window()->window()->setPosition(QPoint(100, 100));
    QTest::qWait(1000);
    QCOMPARE(dock1->window()->window()->geometry().topLeft(), QPoint(100, 100));

    dock1->close();
    dock1->show();
    QCOMPARE(dock1->window()->window()->geometry().topLeft(), QPoint(100, 100));

    // Cleanup
    window->layoutWidget()->checkSanity();
    dock1->deleteLater();
    QVERIFY(Testing::waitForDeleted(dock1));
}

void TestDocks::tst_moreTitleBarCornerCases()
{
    {
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("dock1", new QPushButton("foo1"));
        auto dock2 = createDockWidget("dock2", new QPushButton("foo2"));
        dock1->show();
        dock2->show();
        auto fw2 = dock2->window();
        dock1->addDockWidgetToContainingWindow(dock2, Location_OnLeft);
        QVERIFY(dock1->dptr()->frame()->titleBar()->isVisible());
        QVERIFY(dock2->dptr()->frame()->titleBar()->isVisible());
        QVERIFY(dock1->dptr()->frame()->titleBar() != dock2->dptr()->frame()->titleBar());
        auto fw = dock1->floatingWindow();
        QVERIFY(fw->titleBar()->isVisible());
        QVERIFY(fw->titleBar() != dock1->dptr()->frame()->titleBar());
        QVERIFY(fw->titleBar() != dock2->dptr()->frame()->titleBar());
    }

    {
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("dock1", new QPushButton("foo1"));
        auto dock2 = createDockWidget("dock2", new QPushButton("foo2"));
        dock1->show();
        dock2->show();
        auto fw1 = dock1->floatingWindow();
        auto fw2 = dock2->floatingWindow();
        fw1->dropArea()->drop(fw2->view(), Location_OnRight, nullptr);
        QVERIFY(fw1->titleBar()->isVisible());
        QVERIFY(dock1->dptr()->frame()->titleBar()->isVisible());
        QVERIFY(dock2->dptr()->frame()->titleBar()->isVisible());
        QVERIFY(dock1->dptr()->frame()->titleBar() != dock2->dptr()->frame()->titleBar());
        QVERIFY(fw1->titleBar() != dock1->dptr()->frame()->titleBar());
        QVERIFY(fw1->titleBar() != dock2->dptr()->frame()->titleBar());
    }

    {
        // Tests that restoring a single floating dock widget doesn't make it show two title-bars
        // As reproduced myself... and fixed in this commit

        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("dock1", new QPushButton("foo1"));
        dock1->show();

        auto fw1 = dock1->floatingWindow();
        QVERIFY(!dock1->dptr()->frame()->titleBar()->isVisible());
        QVERIFY(fw1->titleBar()->isVisible());

        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();
        saver.restoreLayout(saved);

        delete fw1; // the old window

        fw1 = dock1->floatingWindow();
        QVERIFY(dock1->isVisible());
        QVERIFY(!dock1->dptr()->frame()->titleBar()->isVisible());
        QVERIFY(fw1->titleBar()->isVisible());
    }
}

void TestDocks::tst_isInMainWindow()
{
    EnsureTopLevelsDeleted e;
    auto dw = new Controllers::DockWidget(QStringLiteral("FOO"));
    dw->show();
    auto fw = dw->window();
    QVERIFY(!dw->isInMainWindow());
    auto m1 = createMainWindow(QSize(2560, 809), MainWindowOption_None, "MainWindow1");
    m1->addDockWidget(dw, KDDockWidgets::Location_OnLeft);
    QVERIFY(dw->isInMainWindow());

    // Also test after creating the MainWindow, as the FloatingWindow will get parented to it
    auto dw2 = new Controllers::DockWidget(QStringLiteral("2"));
    dw2->show();
    QVERIFY(!dw2->isInMainWindow());
}

void TestDocks::tst_sizeConstraintWarning()
{
    // Tests that we don't get the warning: MultiSplitterLayout::checkSanity: Widget has height= 122 but minimum is 144 KDDockWidgets::Item
    // Code autogenerated by the fuzzer:
    EnsureTopLevelsDeleted e;
    SetExpectedWarning sew("Dock widget already exists in the layout");

    auto window = createMainWindow();
    QList<Controllers::DockWidget *> listDockWidget;
    {
        auto dock = new Controllers::DockWidget("foo-0");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-1");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-2");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-3");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-4");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-5");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-6");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-7");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-8");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-9");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-10");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-11");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-12");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-13");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-14");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-15");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-16");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-17");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }
    {
        auto dock = new Controllers::DockWidget("foo-18");
        dock->setWidget(new QTextEdit());
        listDockWidget.append(dock);
    }

    auto dropArea = window->dropArea();
    window->addDockWidget(listDockWidget.at(0), static_cast<Location>(2));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(1), static_cast<Location>(1));
    dropArea->checkSanity();

    listDockWidget.at(2 - 1)->addDockWidgetAsTab(listDockWidget.at(2));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(3 - 1), static_cast<Location>(2), listDockWidget.at(3), static_cast<InitialVisibilityOption>(1));
    dropArea->checkSanity();

    listDockWidget.at(4 - 1)->addDockWidgetAsTab(listDockWidget.at(4));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(5), static_cast<Location>(1));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(6), static_cast<Location>(1));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(7), static_cast<Location>(4));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(8 - 1), static_cast<Location>(1), listDockWidget.at(8), static_cast<InitialVisibilityOption>(1));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(9), static_cast<Location>(2));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(10 - 1), static_cast<Location>(2), listDockWidget.at(10), static_cast<InitialVisibilityOption>(1));
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
    for (auto dock : docks)
        dock->deleteLater();

    Testing::waitForDeleted(lastDock);
}

void TestDocks::tst_stuckSeparator()
{
    const QString absoluteLayoutFileName = QStringLiteral(":/layouts/stuck-separator.json");

    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(2560, 809), MainWindowOption_None, "MainWindow1");
    const int numDockWidgets = 26;
    Controllers::DockWidget *dw25 = nullptr;
    for (int i = 0; i < numDockWidgets; ++i) {
        auto createdDw = createDockWidget(QStringLiteral("dock-%1").arg(i));
        if (i == 25)
            dw25 = createdDw;
    }

    LayoutSaver restorer;
    QVERIFY(restorer.restoreFromFile(absoluteLayoutFileName));

    Controllers::Frame *frame25 = dw25->dptr()->frame();
    ItemBoxContainer *root = m1->multiSplitter()->rootItem();
    Item *item25 = root->itemForWidget(frame25->view());
    ItemBoxContainer *container25 = item25->parentBoxContainer();
    QVector<Controllers::Separator *> separators = container25->separators();
    QCOMPARE(separators.size(), 1);

    Controllers::Separator *separator25 = separators.constFirst();
    const int sepMin = container25->minPosForSeparator_global(separator25);
    const int sepMax = container25->maxPosForSeparator_global(separator25);

    QVERIFY(sepMin <= sepMax);

    for (auto dw : DockRegistry::self()->dockwidgets()) {
        delete dw;
    }
}

void TestDocks::tst_titlebar_getter()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(1000, 1000), MainWindowOption_HasCentralFrame);
    m->view()->resize(QSize(500, 500));
    m->show();

    auto w1 = new MyWidget2(QSize(400, 400));
    auto d1 = createDockWidget("1", w1);

    m->addDockWidget(d1, Location_OnTop);

    QVERIFY(d1->titleBar()->isVisible());
    d1->setFloating(true);
    QVERIFY(d1->floatingWindow());
    QVERIFY(d1->floatingWindow()->isVisible());
    QVERIFY(d1->titleBar()->isVisible());
}

void TestDocks::tst_dockNotFillingSpace()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(1000, 1000));
    m->view()->resize(QSize(500, 500));
    m->show();

    auto d1 = createDockWidget("1", new QTextEdit());
    auto d2 = createDockWidget("2", new QTextEdit());
    auto d3 = createDockWidget("3", new QTextEdit());

    m->addDockWidget(d1, Location_OnTop);
    m->addDockWidget(d2, Location_OnBottom);
    m->addDockWidget(d3, Location_OnBottom);

    Controllers::Frame *frame2 = d2->dptr()->frame();
    d1->close();
    d2->close();
    Testing::waitForDeleted(frame2);

    auto layout = m->multiSplitter();
    QVERIFY(layout->checkSanity());

    delete d1;
    delete d2;
}

void TestDocks::tst_lastFloatingPositionIsRestored()
{
    EnsureTopLevelsDeleted e;

    auto m1 = createMainWindow();
    auto dock1 = createDockWidget("dock1");
    dock1->show();
    QPoint targetPos = QPoint(340, 340);
    dock1->window()->window()->setFramePosition(targetPos);
    QCOMPARE(dock1->window()->window()->frameGeometry().topLeft(), targetPos);
    auto oldFw = dock1->window();
    Platform::instance()->tests_waitForEvent(dock1->window().get(), QEvent::Move);

    LayoutSaver saver;
    QByteArray saved = saver.serializeLayout();

    dock1->window()->move(0, 0);
    dock1->close();

    saver.restoreLayout(saved);
    QCOMPARE(dock1->window()->window()->frameGeometry().topLeft(), targetPos);

    // Adjsut to what we got without the frame
    targetPos = dock1->window()->geometry().topLeft();

    // Now dock it:
    m1->addDockWidget(dock1, Location_OnTop);
    QCOMPARE(dock1->dptr()->lastPosition()->lastFloatingGeometry().topLeft(), targetPos);

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
}

void TestDocks::tst_titleBarFocusedWhenTabsChange()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_TitleBarIsFocusable);

    auto le1 = new FocusableWidget();
    le1->setObjectName("le1");
    auto dock1 = createDockWidget(QStringLiteral("dock1"), le1);
    auto dock2 = createDockWidget(QStringLiteral("dock2"), new FocusableWidget());
    auto dock3 = createDockWidget(QStringLiteral("dock3"), new FocusableWidget());
    auto oldFw1 = dock1->window();
    auto oldFw2 = dock2->window();
    auto oldFw3 = dock3->window();

    auto m1 = createMainWindow(QSize(2560, 809), MainWindowOption_None, "MainWindow1");

    m1->addDockWidget(dock1, Location_OnLeft);
    m1->addDockWidget(dock2, Location_OnRight);
    dock2->addDockWidgetAsTab(dock3);

    Controllers::TitleBar *titleBar1 = dock1->titleBar();
    dock1->guestView()->setFocus(Qt::MouseFocusReason);

    QVERIFY(dock1->isFocused() || Platform::instance()->tests_waitForEvent(dock1->guestView().get(), QEvent::FocusIn));
    QVERIFY(titleBar1->isFocused());

    auto frame2 = dock2->dptr()->frame();

    Controllers::Stack *tb2 = frame2->tabWidget();
    QCOMPARE(tb2->currentIndex(), 1); // Was the last to be added

    auto tabBar2 = tb2->tabBar();
    const QRect rect0 = tabBar2->rectForTab(0);
    const QPoint globalPos = tabBar2->view()->mapToGlobal(rect0.topLeft()) + QPoint(5, 5);
    Tests::clickOn(globalPos, tabBar2->view());

    QVERIFY(!titleBar1->isFocused());
    QVERIFY(dock2->titleBar()->isFocused());

    // Test that clicking on a tab that is already current will also set focus
    dock1->view()->setFocus(Qt::MouseFocusReason);
    QVERIFY(dock1->titleBar()->isFocused());
    QVERIFY(!dock2->titleBar()->isFocused());

#ifdef KDDOCKWIDGETS_QTWIDGETS
    // TODO: Not yet ready for QtQuick. The TitleBar.qml is clicked, but we check the C++ TitleBar for focus
    Tests::clickOn(globalPos, tabBar2->view());
    QVERIFY(!dock1->titleBar()->isFocused());
    QVERIFY(dock2->titleBar()->isFocused());
#endif
}

void TestDocks::tst_floatingAction()
{
    // Tests DockWidget::floatAction()

    {
        EnsureTopLevelsDeleted e;
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

        // 2. Put it back, via setFloating(). It should return to its place.
        action->toggle();

        QVERIFY(!dock1->isFloating());
        QVERIFY(!action->isChecked());
        QVERIFY(action->isEnabled());
        QVERIFY(!dock1->isTabbed());
        QCOMPARE(action->toolTip(), tr("Detach"));

        Testing::waitForDeleted(fw);
    }

    {
        EnsureTopLevelsDeleted e;
        // 1. Create a MainWindow with one docked dock-widgets, and one floating.
        auto m = createMainWindow();
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);

        // The floating window action should be disabled as it has no previous place
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

        // 2. Put it back, via setFloating(). It should return to its place.
        action->toggle();

        QVERIFY(!dock1->isFloating());
        QVERIFY(!action->isChecked());
        QVERIFY(action->isEnabled());
        QVERIFY(!dock1->isTabbed());
        QCOMPARE(action->toolTip(), tr("Detach"));

        Testing::waitForDeleted(fw);
    }
    {
        EnsureTopLevelsDeleted e;
        // 3. A floating window with two tabs
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));

        bool dock1IsFloating = dock1->floatAction()->isChecked();
        bool dock2IsFloating = dock2->floatAction()->isChecked();

        auto conn1 = connect(dock1->floatAction(), &QAction::toggled, [&dock1IsFloating](bool t) {
            Q_ASSERT(dock1IsFloating != t);
            dock1IsFloating = t;
        });

        auto conn2 = connect(dock2->floatAction(), &QAction::toggled, [&dock2IsFloating](bool t) {
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

        disconnect(conn1);
        disconnect(conn2);
        delete fw2;
    }

    {
        EnsureTopLevelsDeleted e;
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

        QSignalSpy spy11(dock1, &Controllers::DockWidget::isFloatingChanged);
        QSignalSpy spy21(dock2, &Controllers::DockWidget::isFloatingChanged);

        dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);

        QCOMPARE(spy1.count(), 1);
        QCOMPARE(spy2.count(), 1);
        QCOMPARE(spy11.count(), 1);
        QCOMPARE(spy21.count(), 1);

        QVERIFY(!dock1->isFloating());
        QVERIFY(!dock2->isFloating());

        QVERIFY(!dock2->floatAction()->isChecked());
        QVERIFY(!dock1->floatAction()->isChecked());
    }

    {
        EnsureTopLevelsDeleted e;
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

        QSignalSpy spy11(dock1, &Controllers::DockWidget::isFloatingChanged);
        QSignalSpy spy21(dock2, &Controllers::DockWidget::isFloatingChanged);

        auto dropArea1 = dock1->floatingWindow()->dropArea();
        dropArea1->drop(oldFw2->view(), Location_OnRight, nullptr);

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
    }

    {
        EnsureTopLevelsDeleted e;
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
        QSignalSpy spy11(dock1, &Controllers::DockWidget::isFloatingChanged);
        QSignalSpy spy21(dock2, &Controllers::DockWidget::isFloatingChanged);
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
    }
}

void TestDocks::tst_raise()
{
    // Tests DockWidget::raise();
    EnsureTopLevelsDeleted e;

    auto dock1 = createDockWidget("1");
    auto dock2 = createDockWidget("2");

    dock1->addDockWidgetAsTab(dock2);
    dock1->setAsCurrentTab();
    QVERIFY(dock1->isCurrentTab());
    QVERIFY(!dock2->isCurrentTab());
    dock2->raise();
    QVERIFY(!dock1->isCurrentTab());
    QVERIFY(dock2->isCurrentTab());

    if (qApp->platformName() != QLatin1String("offscreen")) { // offscreen qpa doesn't seem to keep Window Z.
        auto dock3 = createDockWidget("3");
        dock3->window()->setGeometry(dock1->window()->geometry());
        dock3->window()->setObjectName("3");
        dock1->window()->setObjectName("1");
        dock3->raise();
        QTest::qWait(200);

        if (!Platform::instance()->windowAt(dock3->window()->geometry().topLeft() + QPoint(50, 50))->equals(dock3->view()->window())) {
            qDebug() << "Failing before raise" << qApp->widgetAt(dock3->window()->geometry().topLeft() + QPoint(50, 50))->window() << dock3->window().get()
                     << dock1->window()->geometry() << dock3->window()->geometry();
            QVERIFY(false);
        }

        dock1->raise();
        QTest::qWait(200);
        QVERIFY(dock1->isCurrentTab());

        if (Platform::instance()->windowAt(dock3->window()->geometry().topLeft() + QPoint(50, 50))->equals(dock1->view()->window())) {
            qDebug() << "Failing after raise" << qApp->widgetAt(dock3->window()->geometry().topLeft() + QPoint(50, 50))->window() << dock1->window().get()
                     << dock1->window()->geometry() << dock3->window()->geometry();
            QVERIFY(false);
        }
    }
}

void TestDocks::tst_invalidLayoutAfterRestore()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
    auto dock3 = createDockWidget("dock3", new QPushButton("three"));
    auto dropArea = m->dropArea();
    Controllers::DropArea *layout = dropArea;
    // Stack 1, 2, 3
    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);

    const int oldContentsWidth = layout->layoutWidth();

    auto f1 = dock1->dptr()->frame();
    dock3->close();
    dock2->close();
    dock1->close();
    QVERIFY(Testing::waitForDeleted(f1));

    dock3->show();
    dock2->show();
    dock1->show();
    Platform::instance()->tests_waitForEvent(m.get(), QEvent::LayoutRequest); // So MainWindow min size is updated

    Item *item1 = layout->itemForFrame(dock1->dptr()->frame());
    Item *item3 = layout->itemForFrame(dock3->dptr()->frame());
    Item *item4 = dropArea->centralFrame();

    QCOMPARE(layout->count(), 4);
    QCOMPARE(layout->placeholderCount(), 0);

    // Detach dock2
    QPointer<Controllers::Frame> f2 = dock2->dptr()->frame();
    f2->detachTab(dock2);
    QVERIFY(!f2.data());
    QTest::qWait(200); // Not sure why. Some event we're waiting for. TODO: Investigate
    auto fw2 = dock2->floatingWindow();
    QCOMPARE(layout->view()->minSize().width(), 2 * Item::separatorThickness + item1->minSize().width() + item3->minSize().width() + item4->minSize().width());

    // Drop left of dock3
    layout->addWidget(fw2->dropArea()->view(), Location_OnLeft, dock3->dptr()->frame());

    QVERIFY(Testing::waitForDeleted(fw2));
    QCOMPARE(layout->layoutWidth(), oldContentsWidth);
    layout->checkSanity();
}

void TestDocks::tst_dontCloseDockWidgetBeforeRestore()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, Controllers::DockWidget::LayoutSaverOption::Skip);
    auto dock3 = createDockWidget("dock3", new QPushButton("three"), {}, Controllers::DockWidget::LayoutSaverOption::Skip);
    auto dock4 = createDockWidget("4", new QPushButton("4"), {}, {}, /*show=*/false);

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnBottom);

    // Dock #3 floats, while #1 and #2 are docked.
    dock3->setFloating(true);
    QVERIFY(dock3->isOpen());
    QVERIFY(dock3->isFloating());
    QVERIFY(!dock3->isInMainWindow());

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    dock3->close();

    // Not open anymore
    QVERIFY(!dock3->isOpen());

    QVERIFY(saver.restoreLayout(saved));

    // #3 is still closed, the restore will skip it
    QVERIFY(!dock3->isOpen());
    QVERIFY(!dock3->isInMainWindow());

    auto dock5 = createDockWidget("5", new QPushButton("5"), {}, Controllers::DockWidget::LayoutSaverOption::Skip);

    dock4->show();
    dock5->show();

    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(!dock4->isOpen());
    QVERIFY(dock5->isOpen()); // #5 is still open, it ignored restore
}

void TestDocks::tst_dontCloseDockWidgetBeforeRestore2()
{
    // In this case we have a floating window with two dock widgets tabbed, both having LayoutSaverOption::Skip
    // Meaning the whole window should be skipped

    EnsureTopLevelsDeleted e;
    auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, Controllers::DockWidget::LayoutSaverOption::Skip);
    auto dock3 = createDockWidget("dock3", new QPushButton("three"), {}, Controllers::DockWidget::LayoutSaverOption::Skip);

    dock2->close();
    dock3->close();

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout(); // This layout has 0 docks visible

    dock2->show();
    dock3->show();
    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(dock2->isVisible()); // They're still visible
    QVERIFY(dock3->isVisible());

    // Now tab and restore again
    dock2->addDockWidgetAsTab(dock3);
    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(dock2->isOpen());
    QVERIFY(dock3->isOpen());
    QVERIFY(dock3->isVisible());
    QCOMPARE(dock3->dptr()->frame(), dock2->dptr()->frame());
}

void TestDocks::tst_dontCloseDockWidgetBeforeRestore3()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, Controllers::DockWidget::LayoutSaverOption::Skip);
    dock1->close();
    dock2->close();

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout(); // This layout has 0 docks visible

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnBottom);

    QVERIFY(saver.restoreLayout(saved));

    QVERIFY(!dock1->isOpen()); // Gets closed by the restore
    QVERIFY(dock2->isOpen()); // Dock2 remains open, it ignores restore
    QVERIFY(dock2->isFloating());
}

void TestDocks::tst_dontCloseDockWidgetBeforeRestore4()
{
    // Tests a case where the dock widget would get an invalid size.
    // Widgets which skip layout restore were be skipping LayoutSaver::onResize()

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow({ 1000, 1000 }, {});
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"), {},
                                  Controllers::DockWidget::LayoutSaverOption::Skip);

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnBottom);

    QTest::qWait(100);
    dock1->close();
    dock2->close();

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    QTest::qWait(100);
    dock2->show();

    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(dock2->isOpen());

    QTest::qWait(100);
    Controllers::FloatingWindow *fw = dock2->floatingWindow();
    DropArea *da = fw->dropArea();
    QVERIFY(da->checkSanity());
    QCOMPARE(da->layoutSize(), da->rootItem()->size());
    QVERIFY(qAbs(fw->width() - da->layoutWidth()) < 30);
}

void TestDocks::tst_closeOnlyCurrentTab()
{
    {
        // Case of a floating window with tabs
        EnsureTopLevelsDeleted e;
        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_CloseOnlyCurrentTab);

        auto dock1 = createDockWidget("1", new QPushButton("1"));
        auto dock2 = createDockWidget("2", new QPushButton("2"));
        auto dock3 = createDockWidget("3", new QPushButton("3"));

        /// Floating window with 3 tabs
        dock1->addDockWidgetAsTab(dock2);
        dock1->addDockWidgetAsTab(dock3);

        Controllers::TitleBar *tb = dock1->titleBar();
        QVERIFY(tb->isVisible());
        dock1->setAsCurrentTab();
        Controllers::Frame *frame = dock1->dptr()->frame();
        QCOMPARE(frame->currentIndex(), 0);

        tb->onCloseClicked();

        QVERIFY(!dock1->isOpen());
        QVERIFY(dock2->isOpen());
        QVERIFY(dock3->isOpen());
    }

    {
        // Case of a floating window with tabs
        EnsureTopLevelsDeleted e;
        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_CloseOnlyCurrentTab);

        auto m = createMainWindow();
        auto dock1 = createDockWidget("1", new QPushButton("1"));
        auto dock2 = createDockWidget("2", new QPushButton("2"));
        auto dock3 = createDockWidget("3", new QPushButton("3"));

        m->addDockWidget(dock1, Location_OnLeft);
        m->addDockWidget(dock2, Location_OnRight);

        dock2->addDockWidgetAsTab(dock3);
        Controllers::Frame *frame = dock2->dptr()->frame();
        QCOMPARE(frame->currentIndex(), 1);
        Controllers::TitleBar *tb = frame->titleBar();
        QVERIFY(tb->isVisible());
        tb->onCloseClicked();

        QVERIFY(!dock3->isOpen());
        QVERIFY(dock2->isOpen());
        QVERIFY(dock1->isOpen());
        QCOMPARE(frame->dockWidgetCount(), 1);
    }
}

void TestDocks::tst_tabWidgetCurrentIndex()
{
    EnsureTopLevelsDeleted e;

    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    auto dock3 = createDockWidget("3", new QPushButton("3"));
    auto fw2 = dock2->window();
    auto fw3 = dock3->window();

    Controllers::DockWidget *currentDw = nullptr;
    auto frame = dock1->dptr()->frame();
    connect(frame, &Controllers::Frame::currentDockWidgetChanged, this, [&currentDw](Controllers::DockWidget *dw) {
        currentDw = dw;
    });

    QCOMPARE(frame->tabWidget()->currentIndex(), 0);
    dock1->addDockWidgetAsTab(dock2);

    QCOMPARE(frame->tabWidget()->currentIndex(), 1);
    QCOMPARE(frame->currentDockWidget(), currentDw);
    QCOMPARE(dock2, currentDw);

    dock2->close();

    QCOMPARE(frame->tabWidget()->currentIndex(), 0);
    QCOMPARE(dock1, currentDw);
}

void TestDocks::tst_doubleClickTabToDetach()
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    // Tests::doubleClickOn(QWindow) doesn't work anymore on Qt6
    // which refactored mouse delivery.
    return;
#endif

    EnsureTopLevelsDeleted e;

    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));

    auto fw2 = dock2->window();

    dock1->addDockWidgetAsTab(dock2);

    auto frame = dock1->dptr()->frame();
    QCOMPARE(frame->currentIndex(), 1);

    auto tb = frame->tabWidget()->view();
    Tests::doubleClickOn(tb->mapToGlobal(QPoint(20, 20)), frame->view()->window());

    QVERIFY(dock1->isFloating());
    QVERIFY(dock2->isFloating());
    QVERIFY(dock1->floatingWindow() != dock2->floatingWindow());
}

void TestDocks::tst_addingOptionHiddenTabbed()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    m->addDockWidget(dock1, Location_OnTop);

    QCOMPARE(dock1->dptr()->frame()->dockWidgetCount(), 1);
    dock1->addDockWidgetAsTab(dock2, InitialVisibilityOption::StartHidden);
    QCOMPARE(dock1->dptr()->frame()->dockWidgetCount(), 1);
    dock2->show();
    QCOMPARE(dock1->dptr()->frame()->dockWidgetCount(), 2);

    QVERIFY(dock1->dptr()->frame() == dock2->dptr()->frame());
}

void TestDocks::tst_flagDoubleClick()
{
    {
        EnsureTopLevelsDeleted e;
        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_DoubleClickMaximizes);
        auto m = createMainWindow(QSize(500, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("1", new QPushButton("1"));
        auto dock2 = createDockWidget("2", new QPushButton("2"));
        m->addDockWidget(dock1, Location_OnTop);

        Controllers::FloatingWindow *fw2 = dock2->floatingWindow();
        QVERIFY(!fw2->view()->isMaximized());
        Controllers::TitleBar *t2 = dock2->titleBar();
        QPoint pos = t2->mapToGlobal(QPoint(5, 5));
        Tests::doubleClickOn(pos, t2->view());
        QVERIFY(fw2->view()->isMaximized());
        delete fw2;

        Controllers::TitleBar *t1 = dock1->titleBar();
        QVERIFY(!t1->isFloating());
        pos = t1->mapToGlobal(QPoint(5, 5));
        Tests::doubleClickOn(pos, t1->view());
        QVERIFY(t1->isFloating());
        QVERIFY(!dock1->window()->isMaximized());
    }

    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(QSize(500, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("1", new QPushButton("1"));

        m->addDockWidget(dock1, Location_OnTop);

        Controllers::TitleBar *t1 = dock1->titleBar();
        QVERIFY(!t1->isFloating());
        QPoint pos = t1->mapToGlobal(QPoint(5, 5));
        Tests::doubleClickOn(pos, t1->view());
        QVERIFY(t1->isFloating());
        QVERIFY(dock1->isFloating());
        QVERIFY(!dock1->window()->isMaximized());

        pos = t1->mapToGlobal(QPoint(5, 5));
        Tests::doubleClickOn(pos, t1->view());
        QVERIFY(!dock1->isFloating());
    }
}

void TestDocks::tst_maxSizedHonouredAfterRemoved()
{
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None);
    auto dock1 = new Controllers::DockWidget("dock1");
    dock1->show();

    auto w = new MyWidget("foo");
    w->setMinimumSize(120, 100);
    w->setMaximumSize(300, 150);
    dock1->setWidget(w);
    m1->dropArea()->addMultiSplitter(dock1->floatingWindow()->multiSplitter(), Location_OnLeft);

    auto dock2 = new Controllers::DockWidget("dock2");
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

    auto dock3 = new Controllers::DockWidget("dock3");
    dock3->show();
    m1->dropArea()->addMultiSplitter(dock3->floatingWindow()->multiSplitter(), Location_OnBottom);

    dock1->setFloating(true);
    m1->dropArea()->addMultiSplitter(dock1->floatingWindow()->multiSplitter(), Location_OnBottom,
                                     dock2->dptr()->frame());

    // Close dock2 and check if dock1's max-size is still honoured
    dock2->close();
    QTest::qWait(100); // wait for the resize, so dock1 gets taller"

    QVERIFY(dock1->dptr()->frame()->view()->height() <= dock1->dptr()->frame()->view()->maxSizeHint().height());
    delete dock2;
}

void TestDocks::tst_addDockWidgetAsTabToDockWidget()
{
    EnsureTopLevelsDeleted e;
    {
        // Dock into a non-morphed floating dock widget
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));

        dock1->addDockWidgetAsTab(dock2);

        auto window1 = dock1->window();
        auto window2 = dock2->window();
        QCOMPARE(window1->window(), window2->window());
        QCOMPARE(dock1->dptr()->frame(), dock2->dptr()->frame());
        QCOMPARE(dock1->dptr()->frame()->dockWidgetCount(), 2);
        dock1->deleteLater();
        dock2->deleteLater();
        Testing::waitForDeleted(dock2);
    }
    {
        // Dock into a morphed dock widget
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        dock1->dptr()->morphIntoFloatingWindow();
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));

        dock1->addDockWidgetAsTab(dock2);

        auto window1 = dock1->window();
        auto window2 = dock2->window();
        QCOMPARE(window1->window(), window2->window());
        QCOMPARE(dock1->dptr()->frame(), dock2->dptr()->frame());
        QCOMPARE(dock1->dptr()->frame()->dockWidgetCount(), 2);
        dock1->deleteLater();
        dock2->deleteLater();
        Testing::waitForDeleted(dock2);
    }
    {
        // Dock a morphed dock widget into a morphed dock widget
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        dock1->dptr()->morphIntoFloatingWindow();
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        dock2->dptr()->morphIntoFloatingWindow();
        auto originalWindow2 = dock2->window();

        dock1->addDockWidgetAsTab(dock2);

        auto window1 = dock1->window();
        auto window2 = dock2->window();
        QCOMPARE(window1->window(), window2->window());
        QCOMPARE(dock1->dptr()->frame(), dock2->dptr()->frame());
        QCOMPARE(dock1->dptr()->frame()->dockWidgetCount(), 2);
        Platform::instance()->tests_waitForDeleted(originalWindow2.get());

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
        QVERIFY(dock1->window()->equals(m->view()));
        QVERIFY(dock2->window()->equals(m->view()));
        QCOMPARE(dock1->dptr()->frame(), dock2->dptr()->frame());
        QCOMPARE(dock1->dptr()->frame()->dockWidgetCount(), 2);
    }
}

void TestDocks::tst_closeTabHidesDockWidget()
{
    // Tests that closing some tabbed dock widgets will hide them
    // QtQuick had a bug where they would still be visible
    {
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("doc1", Qt::green);
        auto dock2 = createDockWidget("doc2", Qt::green);
        auto dock3 = createDockWidget("doc3", Qt::green);

        dock1->addDockWidgetAsTab(dock2);
        dock1->addDockWidgetAsTab(dock3);

        dock1->forceClose();
        QVERIFY(!dock1->isOpen());
        QVERIFY(!dock1->isVisible());

        dock2->forceClose();
        QVERIFY(!dock2->isOpen());
        QVERIFY(!dock2->isVisible());

        dock3->forceClose();
        QVERIFY(!dock3->isOpen());
        QVERIFY(!dock3->isVisible());
    }

    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("doc1", Qt::green);
        auto dock2 = createDockWidget("doc2", Qt::green);
        auto dock3 = createDockWidget("doc3", Qt::green);
        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        m->addDockWidget(dock2, KDDockWidgets::Location_OnLeft);
        m->addDockWidget(dock3, KDDockWidgets::Location_OnLeft);

        dock2->addDockWidgetAsTab(dock1);
        dock2->addDockWidgetAsTab(dock3);

        dock1->close();
        QVERIFY(!dock1->isOpen());
        QVERIFY(!dock1->isVisible());
        QCOMPARE(dock1->parent(), nullptr);

        dock2->close();
        QVERIFY(!dock2->isOpen());
        QCOMPARE(dock2->parent(), nullptr);
        QVERIFY(!dock2->isVisible());

        dock3->close();
        QVERIFY(!dock3->isOpen());
        QVERIFY(!dock3->isVisible());
        QCOMPARE(dock3->parent(), nullptr);
        QVERIFY(!dock2->isVisible());
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
    QVERIFY(dock1->window()->equals(dock1->view()));
    QVERIFY(!toggleAction->isChecked());

    // 1.1 Reshow with show()
    dock1->show();
    auto fw = dock1->floatingWindow();
    QVERIFY(fw);
    QVERIFY(toggleAction->isChecked());
    QVERIFY(dock1->isVisible());
    QVERIFY(dock1->window()->equals(fw->view()));
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
    QVERIFY(dock1->window()->equals(dock1->view()));
    QVERIFY(!toggleAction->isChecked());

    // 1.4 close a FloatingWindow, via DockWidget::close
    QPointer<Controllers::FloatingWindow> window = dock1->dptr()->morphIntoFloatingWindow();
    QPointer<Controllers::Frame> frame1 = dock1->dptr()->frame();
    QVERIFY(dock1->isVisible());
    QVERIFY(dock1->window()->isVisible());
    QVERIFY(frame1->isVisible());
    QVERIFY(dock1->window()->equals(window->view()));

    QVERIFY(dock1->close());
    QVERIFY(!dock1->dptr()->frame());
    QVERIFY(Testing::waitForDeleted(frame1));
    QVERIFY(Testing::waitForDeleted(window));

    // 1.5 close a FloatingWindow, via FloatingWindow::close
    dock1->show();

    window = dock1->dptr()->morphIntoFloatingWindow();
    frame1 = dock1->dptr()->frame();
    QVERIFY(dock1->isVisible());
    QVERIFY(dock1->window()->isVisible());
    QVERIFY(frame1->isVisible());
    QVERIFY(dock1->window()->equals(window->view()));

    QVERIFY(window->view()->close());

    QVERIFY(!dock1->dptr()->frame());
    QVERIFY(Testing::waitForDeleted(frame1));
    QVERIFY(Testing::waitForDeleted(window));

    // TODO: 1.6 Test FloatingWindow with two frames
    // TODO: 1.7 Test Frame with two tabs

    // 1.8 Check if space is reclaimed after closing left dock
    Controllers::DockWidget *centralDock;
    Controllers::DockWidget *leftDock;
    Controllers::DockWidget *rightDock;

    auto mainwindow = createSimpleNestedMainWindow(&centralDock, &leftDock, &rightDock);
    auto da = mainwindow->dropArea();

    QVERIFY(da->checkSanity());
    QCOMPARE(leftDock->dptr()->frame()->view()->x(), 0);

    QCOMPARE(centralDock->dptr()->frame()->view()->x(),
             leftDock->dptr()->frame()->view()->geometry().right()
                 + Item::separatorThickness + 1);
    QCOMPARE(rightDock->dptr()->frame()->view()->x(),
             centralDock->dptr()->frame()->view()->geometry().right()
                 + Item::separatorThickness + 1);
    leftDock->close();
    QTest::qWait(250); // TODO: wait for some signal
    QCOMPARE(centralDock->dptr()->frame()->view()->x(), 0);
    QCOMPARE(rightDock->dptr()->frame()->view()->x(),
             centralDock->dptr()->frame()->view()->geometry().right()
                 + Item::separatorThickness + 1);

    rightDock->close();
    QTest::qWait(250); // TODO: wait for some signal
    QMargins margins = mainwindow->centerWidgetMargins();
    QCOMPARE(centralDock->dptr()->frame()->view()->width(),
             mainwindow->width() - 0 * 2 - margins.left() - margins.right());
    delete leftDock;
    delete rightDock;
    delete centralDock;

    // 1.9 Close tabbed dock, side docks will maintain their position
    mainwindow = createSimpleNestedMainWindow(&centralDock, &leftDock, &rightDock);
    const int leftX = leftDock->dptr()->frame()->view()->x();
    const int rightX = rightDock->dptr()->frame()->view()->x();

    centralDock->close();

    QCOMPARE(leftDock->dptr()->frame()->view()->x(), leftX);
    QCOMPARE(rightDock->dptr()->frame()->view()->x(), rightX);
    delete leftDock;
    delete rightDock;
    delete centralDock;
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
        dock1->dptr()->frame()->titleBar()->onCloseClicked();
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
        dock1->dptr()->frame()->titleBar()->onCloseClicked();
        QVERIFY(mainWindowPtr.data());
        QVERIFY(mainWindowPtr->isVisible());
        delete dock1;
    }
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
    int min1 = widgetMinLength(dock1->view(), Qt::Horizontal);
    int min2 = widgetMinLength(dock2->view(), Qt::Horizontal);

    QVERIFY(dock1->width() >= min1);
    QVERIFY(dock2->width() >= min2);

    nestDockWidget(dock1, dropArea, nullptr, KDDockWidgets::Location_OnRight);
    nestDockWidget(dock2, dropArea, nullptr, KDDockWidgets::Location_OnLeft);

    // Calculate again, as the window frame has disappeared
    min1 = widgetMinLength(dock1->view(), Qt::Horizontal);
    min2 = widgetMinLength(dock2->view(), Qt::Horizontal);

    auto l = m->dropArea();
    l->checkSanity();

    if (dock1->width() < min1) {
        qDebug() << "\ndock1->width()=" << dock1->width() << "\nmin1=" << min1
                 << "\ndock min sizes=" << dock1->view()->minimumWidth()
                 << "\nframe1->width()=" << dock1->dptr()->frame()->view()->width()
                 << "\nframe1->min=" << lengthForSize(dock1->dptr()->frame()->view()->minSize(), Qt::Horizontal);
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

    min1 = widgetMinLength(dock1->view(), Qt::Vertical);
    QVERIFY(dock1->height() >= min1);
}

void TestDocks::tst_constraintsPropagateUp()
{
    // Mostly for QtQuick, which doesn't have any layouts, so we need to make the propagation
    // Manually in DockWidgetQuick::minimumSize(), in FrameQuick, etc.

    EnsureTopLevelsDeleted e;
    const int minWidth = 500;
    const int minHeight = 400;
    const QSize minSz = { minWidth, minHeight };
    auto guestWidget = new MyWidget2(QSize(minWidth, minHeight));
    auto dock1 = createDockWidget("dock1", guestWidget);
    auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(minWidth, minHeight)));

    // TODOv2: Remove
    Views::ViewWrapper_qtwidgets guestWrapper(guestWidget);

    QCOMPARE(widgetMinLength(&guestWrapper, Qt::Vertical), minHeight);
    QCOMPARE(widgetMinLength(&guestWrapper, Qt::Horizontal), minWidth);
    QCOMPARE(dock1->view()->minimumWidth(), minWidth);
    QCOMPARE(dock1->view()->minimumHeight(), minHeight);
    QCOMPARE(dock1->view()->minSize(), minSz);

    auto frame1 = dock1->dptr()->frame();

    QVERIFY(qAbs(widgetMinLength(frame1, Qt::Horizontal) - minWidth) < 10); // 10px for styling differences
    QVERIFY(qAbs(widgetMinLength(frame1, Qt::Vertical) - (minHeight + frame1->nonContentsHeight())) < 10); // 10px for styling differences

    // Add dock2 side-by side, so the Frame now has a title bar.
    auto oldFw2 = dock2->window();
    dock1->addDockWidgetToContainingWindow(dock2, Location_OnLeft);
    Controllers::TitleBar *tb = dock1->titleBar();
    QVERIFY(tb->isVisible());
    QVERIFY(qAbs(widgetMinLength(frame1, Qt::Vertical) - (minHeight + frame1->nonContentsHeight())) < 10);
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
    Controllers::DropArea *layout = dropArea;

    // Stack 3, 2, 1
    m->addDockWidget(dock1, Location_OnTop);
    m->addDockWidget(dock2, Location_OnTop);
    m->addDockWidget(dock3, Location_OnTop);

#ifdef KDDOCKWIDGETS_QTWIDGETS
    QVERIFY(Platform::instance()->tests_waitForResize(m.get()));
#endif

    QVERIFY(m->view()->minimumHeight() > minHeight * 3); // > since some vertical space is occupied by the separators

    // Now close dock1 and check again
    dock1->close();
    Platform::instance()->tests_waitForResize(dock2->view());

    Item *item2 = layout->itemForFrame(dock2->dptr()->frame());
    Item *item3 = layout->itemForFrame(dock3->dptr()->frame());

    QMargins margins = m->centerWidgetMargins();
    const int expectedMinHeight = item2->minLength(Qt::Vertical) + item3->minLength(Qt::Vertical) + 1 * Item::separatorThickness
        + margins.top() + margins.bottom();

    QCOMPARE(m->view()->minSize().height(), expectedMinHeight);

    dock1->deleteLater();
    Testing::waitForDeleted(dock1);
}

void TestDocks::tst_dragBySingleTab()
{
    // Tests dragging via a tab when there's only 1 tab, and we're using Flag_AlwaysShowTabs
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AlwaysShowTabs);
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(400, 400)));
    dock1->show();

    auto frame1 = dock1->dptr()->frame();

    QPoint globalPressPos = dragPointForWidget(frame1, 0);
    Controllers::TabBar *tabBar = frame1->tabWidget()->tabBar();
    QVERIFY(tabBar);
    SetExpectedWarning sew("No window being dragged for"); // because dragging by tab does nothing in this case
    drag(tabBar->view(), globalPressPos, QPoint(0, 0));

    delete dock1;
    Testing::waitForDeleted(frame1);
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
    auto flags = KDDockWidgets::Config::self().flags() | KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible;
    if (tabsAlwaysVisible)
        flags |= KDDockWidgets::Config::Flag_AlwaysShowTabs;

    KDDockWidgets::Config::self().setFlags(flags);

    auto m = createMainWindow();

    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(400, 400)));

    auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(400, 400)));
    auto dock3 = createDockWidget("dock3", new MyWidget2(QSize(400, 400)));
    m->addDockWidgetAsTab(dock1);
    m->view()->resize(QSize(osWindowMinWidth(), 200));

    dock2->addDockWidgetAsTab(dock3);
    if (documentMode)
        dock2->dptr()->frame()->tabWidget()->setDocumentMode(true);

    auto fw = dock2->floatingWindow();
    fw->view()->move(m->pos() + QPoint(500, 500));
    QVERIFY(fw->isVisible());
    QVERIFY(!fw->titleBar()->isVisible());

    dragFloatingWindowTo(fw, dropArea, DropLocation_Right);
}

void TestDocks::tst_dock2FloatingWidgetsTabbed()
{
    EnsureTopLevelsDeleted e;

    if (KDDockWidgets::usesNativeTitleBar())
        return; // Unit-tests can't drag via tab, yet

    auto dock1 = createDockWidget("doc1", Qt::green);
    auto fw1 = dock1->floatingWindow();
    fw1->view()->setGeometry(QRect(500, 500, 400, 400));
    QVERIFY(dock1);
    QPointer<Controllers::Frame> frame1 = dock1->dptr()->frame();

    auto titlebar1 = fw1->titleBar();
    auto dock2 = createDockWidget("doc2", Qt::red);

    QVERIFY(dock1->isFloating());
    QVERIFY(dock2->isFloating());

    QPoint finalPoint = dock2->window()->geometry().center() + QPoint(7, 7);
    drag(titlebar1->view(), titlebar1->mapToGlobal(QPoint(5, 5)), finalPoint, ButtonAction_Press);

    // It morphed into a FloatingWindow
    QPointer<Controllers::Frame> frame2 = dock2->dptr()->frame();
    if (!dock2->floatingWindow()) {
        qWarning() << "dock2->floatingWindow()=" << dock2->floatingWindow();
        QVERIFY(false);
    }
    QVERIFY(frame2);
    QCOMPARE(frame2->dockWidgetCount(), 1);

    releaseOn(finalPoint, titlebar1->view());
    QCOMPARE(frame2->dockWidgetCount(), 2); // 2.2 Frame has 2 widgets when one is dropped
    QVERIFY(Testing::waitForDeleted(frame1));

    // 2.3 Detach tab1 to empty space
    QPoint globalPressPos = dragPointForWidget(frame2.data(), 0);
    Controllers::TabBar *tabBar = frame2->tabWidget()->tabBar();
    QVERIFY(tabBar);
    drag(tabBar->view(), globalPressPos, frame2->view()->windowGeometry().bottomRight() + QPoint(10, 10));

    QVERIFY(frame2->dockWidgetCount() == 1);
    QVERIFY(dock1->floatingWindow());

    // 2.4 Drag the first dock over the second
    frame1 = dock1->dptr()->frame();
    frame2 = dock2->dptr()->frame();
    fw1 = dock1->floatingWindow();
    globalPressPos = fw1->titleBar()->mapToGlobal(QPoint(100, 5));
    finalPoint = dock2->window()->geometry().center() + QPoint(7, 7);
    drag(fw1->titleBar()->view(), globalPressPos, finalPoint);

    QCOMPARE(frame2->dockWidgetCount(), 2);

    // 2.5 Detach and drop to the same place, should tab again
    globalPressPos = dragPointForWidget(frame2.data(), 0);
    tabBar = frame2->tabWidget()->tabBar();

    finalPoint = dock2->window()->geometry().center() + QPoint(7, 7);
    drag(tabBar->view(), globalPressPos, finalPoint);
    QCOMPARE(frame2->dockWidgetCount(), 2);

    // 2.6 Drag the tabbed group over a 3rd floating window
    auto dock3 = createDockWidget("doc3", Qt::black);
    QTest::qWait(1000); // Test is flaky otherwise

    auto fw2 = dock2->floatingWindow();
    finalPoint = dock3->window()->geometry().center() + QPoint(7, 7);
    drag(fw2->titleBar()->view(), frame2->mapToGlobal(QPoint(10, 10)), finalPoint);

    QVERIFY(Testing::waitForDeleted(frame1));
    QVERIFY(Testing::waitForDeleted(frame2));
    QVERIFY(dock3->dptr()->frame());
    QCOMPARE(dock3->dptr()->frame()->dockWidgetCount(), 3);

    auto fw3 = dock3->floatingWindow();
    QVERIFY(fw3);
    QVERIFY(fw3->dropArea()->checkSanity());

    // 2.7 Drop the window into a MainWindow
    {
        auto m = createMainWindow();
        m->show();
        m->view()->setGeometry(QRect(500, 300, 300, 300));
        QVERIFY(!dock3->isFloating());
        auto fw3 = dock3->floatingWindow();
        drag(fw3->titleBar()->view(), dock3->window()->mapToGlobal(QPoint(10, 10)), m->geometry().center());
        QVERIFY(!dock3->isFloating());
        QVERIFY(dock3->window()->equals(m->view()));
        QCOMPARE(dock3->dptr()->frame()->dockWidgetCount(), 3);
        QVERIFY(m->dropArea()->checkSanity());

        delete dock1;
        delete dock2;
        delete dock3;
        QVERIFY(Testing::waitForDeleted(frame2));
        QVERIFY(Testing::waitForDeleted(fw3));
    }
}

void TestDocks::tst_deleteOnClose()
{
    {
        EnsureTopLevelsDeleted e;
        // Tests that DockWidget::close() deletes itself if Option_DeleteOnClose is set
        QPointer<Controllers::DockWidget> dock1 = createDockWidget("1", new MyWidget2(QSize(400, 400)), Controllers::DockWidget::Option_DeleteOnClose);
        dock1->show();
        dock1->close();

        QVERIFY(Testing::waitForDeleted(dock1));
    }

    {
        // Tests that if it's closed via LayoutSaver it's also destroyed when having Option_DeleteOnClose
        EnsureTopLevelsDeleted e;

        QPointer<Controllers::DockWidget> dock1 = createDockWidget("1", new MyWidget2(QSize(400, 400)), Controllers::DockWidget::Option_DeleteOnClose, {}, /*show=*/false);
        QPointer<Controllers::DockWidget> dock2 = createDockWidget("2", new MyWidget2(QSize(400, 400)), {}, {}, /*show=*/false);
        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();
        dock1->show();
        dock2->show();
        QVERIFY(dock1->isVisible());
        QVERIFY(dock2->isVisible());

        QVERIFY(saver.restoreLayout(saved));
        QVERIFY(!dock1->isVisible());
        QVERIFY(!dock2->isVisible());

        QVERIFY(Testing::waitForDeleted(dock1));
        QVERIFY(dock2.data());
        delete dock2;
    }
#ifdef KDDOCKWIDGETS_QTWIDGETS // QtQuick doesn't support autohide/pin/sidebar yet
    {
        // Tests that restoring the side-bar-overlay will call the users dock widget factory in case
        // the dock widget was deleted already
        EnsureTopLevelsDeleted e;
        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
        KDDockWidgets::Config::self().setDockWidgetFactoryFunc([](const QString &name) {
            return createDockWidget(name, new MyWidget2(QSize(400, 400)), Controllers::DockWidget::Option_DeleteOnClose);
        });

        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        QPointer<Controllers::DockWidget> dock1 = createDockWidget("1", new MyWidget2(QSize(400, 400)), Controllers::DockWidget::Option_DeleteOnClose);
        m->addDockWidget(dock1, Location_OnLeft);
        m->moveToSideBar(dock1);
        m->overlayOnSideBar(dock1);
        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();

        QVERIFY(dock1->isVisible());
        dock1->close();
        QVERIFY(Testing::waitForDeleted(dock1));
        QVERIFY(!dock1.data());

        saver.restoreLayout(saved);
    }
#endif
}

void TestDocks::tst_toggleAction()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(400, 400)));
    auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(400, 400)));
    auto dock3 = createDockWidget("dock3", new MyWidget2(QSize(400, 400)));

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);

    auto root = m->multiSplitter()->rootItem();
    QCOMPARE(root->visibleCount_recursive(), 3);
    QVERIFY(dock2->toggleAction()->isChecked());
    QPointer<Controllers::Frame> frame2 = dock2->dptr()->frame();
    dock2->toggleAction()->toggle();
    QVERIFY(!dock2->toggleAction()->isChecked());

    QVERIFY(!dock2->isVisible());
    QVERIFY(!dock2->isOpen());
    QVERIFY(Testing::waitForDeleted(frame2));

    QCOMPARE(root->visibleCount_recursive(), 2);
}

void TestDocks::tst_redocksToPreviousTabIndex()
{
    // Checks that when reordering tabs with mouse, floating and redocking, they go back to their previous index

    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AllowReorderTabs);

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock0 = createDockWidget("dock0", new MyWidget2(QSize(400, 400)));
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(400, 400)));
    m->addDockWidget(dock0, Location_OnLeft);
    dock0->addDockWidgetAsTab(dock1);

    QCOMPARE(dock0->tabIndex(), 0);
    QCOMPARE(dock1->tabIndex(), 1);

    dock0->setFloating(true);
    QCOMPARE(dock1->tabIndex(), 0);

    dock0->setFloating(false);
    QCOMPARE(dock0->tabIndex(), 0);
    QCOMPARE(dock1->tabIndex(), 1);

    Controllers::Frame *frame = dock0->dptr()->frame();
    auto tb = dock0->dptr()->frame()->tabWidget()->tabBar();
    tb->moveTabTo(0, 1);

#ifdef KDDOCKWIDGETS_QTWIDGETS
    QCOMPARE(dock0->tabIndex(), 1);
    QCOMPARE(dock1->tabIndex(), 0);

    // Also detach via detachTab(), which is what is called when the user detaches with mouse
    frame->detachTab(dock0);
    dock0->setFloating(false);

    QCOMPARE(dock0->tabIndex(), 1);
    QCOMPARE(dock1->tabIndex(), 0);
#else
    // An XFAIL so we remember to implement this
    QEXPECT_FAIL("", "TabBar::moveTabTo not implemented for QtQuick yet", Continue);
    QVERIFY(false);
    Q_UNUSED(frame);
#endif
}

void TestDocks::tst_toggleTabbed()
{
    // Testing the weird bugs reported in #211

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock0 = createDockWidget("dock0", new MyWidget2(QSize(400, 400)));
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(400, 400)));

    m->addDockWidget(dock0, Location_OnBottom);
    dock0->addDockWidgetAsTab(dock1);

    QVERIFY(dock1->isCurrentTab());
    QVERIFY(dock0->toggleAction()->isChecked());
    QVERIFY(dock1->toggleAction()->isChecked());
    QVERIFY(dock0->isOpen());
    QVERIFY(dock1->isOpen());

    dock0->close();
    QVERIFY(!dock0->isOpen());
    QVERIFY(dock1->isOpen());
    QVERIFY(dock1->toggleAction()->isChecked());
    QVERIFY(dock1->isCurrentTab());
    Controllers::Frame *frame = dock1->dptr()->frame();
    Controllers::Stack *tw = frame->tabWidget();
    QCOMPARE(tw->currentIndex(), 0);
    QCOMPARE(tw->numDockWidgets(), 1);
    QCOMPARE(tw->currentDockWidget(), dock1);
    QVERIFY(!dock0->isVisible());
    QVERIFY(frame->isVisible());

    QVERIFY(dock1->isVisible());
}

void TestDocks::tst_toggleTabbed2()
{
    // Testing the weird bugs reported in #215
    EnsureTopLevelsDeleted e;
    auto dock0 = createDockWidget("dock0", new MyWidget2(QSize(400, 400)));
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(400, 400)));
    dock0->addDockWidgetAsTab(dock1);

    dock0->setAsCurrentTab();

    Controllers::Frame *frame1 = dock1->dptr()->frame();
    QCOMPARE(frame1->currentDockWidget(), dock0);
    QCOMPARE(frame1->currentIndex(), 0);

    dock0->setFloating(true);
    Controllers::Frame *frame0 = dock0->dptr()->frame();

    QCOMPARE(frame0->currentIndex(), 0);
    QCOMPARE(frame1->currentIndex(), 0);

    QCOMPARE(frame0->title(), "dock0");
    QCOMPARE(frame1->title(), "dock1");
}

void TestDocks::tst_resizePropagatesEvenly()
{
    // For github issue #186
    // Usually resizing main window will resize dock widgets evenly, but if you resize multiple
    // times then one dock widget is getting too small. Not repro with all layouts, but the following
    // one reproduced it:

    auto m = createMainWindow(QSize(1000, 1000), MainWindowOption_None);
    auto dock0 = createDockWidget("dock0", new MyWidget2());
    auto dock1 = createDockWidget("dock1", new MyWidget2());
    auto dock2 = createDockWidget("dock2", new MyWidget2());

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnTop, dock1);
    m->addDockWidget(dock0, Location_OnRight);

    QVERIFY(qAbs(dock2->height() - dock1->height()) < 2);

    m->view()->resize(m->size() + QSize(0, 500));
    for (int i = 1; i < 10; ++i)
        m->view()->resize(m->size() - QSize(0, i));

    QVERIFY(qAbs(dock2->height() - dock1->height()) < 3);
}

void TestDocks::tst_addMDIDockWidget()
{
    EnsureTopLevelsDeleted e;

    // Test that adding a MDI dock widget doesn't produce any warning
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_MDI);
    auto dock0 = createDockWidget("dock0", new MyWidget2(QSize(400, 400)));
    m->layoutWidget()->asMDILayout()->addDockWidget(dock0, QPoint(0, 0), {});
}

void TestDocks::tst_redockToMDIRestoresPosition()
{
    // Tests that setFloating(false) puts the dock widget where it was before floating

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_MDI);
    auto dock0 = createDockWidget("dock0", new MyWidget2(QSize(400, 400)));

    auto layoutWidget = m->layoutWidget()->asMDILayout();
    const QPoint initialPoint = QPoint(500, 500);
    layoutWidget->addDockWidget(dock0, initialPoint, {});

    Controllers::Frame *frame = dock0->DockWidget::d->frame();
    QCOMPARE(frame->view()->pos(), initialPoint);

    const QSize initialSize = frame->size();

    dock0->setFloating(true);
    dock0->setFloating(false);
    frame = dock0->DockWidget::d->frame();
    QCOMPARE(frame->view()->pos(), initialPoint);

    const QPoint anotherPos = QPoint(250, 250);
    dock0->setMDIPosition(anotherPos);

    dock0->setFloating(true);
    dock0->setFloating(false);
    frame = dock0->DockWidget::d->frame();

    Item *item = layoutWidget->itemForFrame(frame);
    QCOMPARE(item->pos(), anotherPos);
    QCOMPARE(item->geometry(), frame->geometry());
    QCOMPARE(frame->view()->pos(), anotherPos);
    QCOMPARE(frame->size(), initialSize);

    const QSize anotherSize = QSize(500, 500);
    dock0->setMDISize(anotherSize);
    QCOMPARE(frame->size(), anotherSize);
    item = layoutWidget->itemForFrame(frame);
    QCOMPARE(item->geometry(), frame->geometry());
}

void TestDocks::tst_restoreWithNativeTitleBar()
{
#ifdef Q_OS_WIN // Other OS don't support this
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_NativeTitleBar);

    auto dock0 = createDockWidget("dock0", new MyWidget2(QSize(400, 400)));
    dock0->window()->move(100, 100);

    QVERIFY(!dock0->titleBar()->isVisible());
    QVERIFY(!dock0->floatingWindow()->titleBar()->isVisible());
    QVERIFY(!dock0->d->frame()->titleBar()->isVisible());

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    saver.restoreLayout(saved);
    QVERIFY(!dock0->titleBar()->isVisible());
    QVERIFY(!dock0->floatingWindow()->titleBar()->isVisible());
    QVERIFY(!dock0->d->frame()->titleBar()->isVisible());
#endif
}

void TestDocks::tst_closeTabOfCentralFrame()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralFrame, "tst_closeTabOfCentralFrame");
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidgetAsTab(dock1);
    Controllers::Frame *frame = dock1->dptr()->frame();
    QVERIFY(frame->options() & FrameOption_IsCentralFrame);
    QVERIFY(frame->isVisible());
    dock1->close();
    QVERIFY(frame->isVisible());
}

void TestDocks::tst_centralFrame245()
{
    /*

    Build: -DKDDockWidgets_DEVELOPER_MODE=ON
    Run: ./bin/tst_docks tst_centralFrame245 -platform xcb

    auto m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralFrame, "tst_centralFrame245");
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));

    m->addDockWidgetAsTab(dock1);
    m->addDockWidgetAsTab(dock2);

    QTest::qWait(100000);

*/
}

void TestDocks::tst_persistentCentralWidget()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralWidget);
    auto dockwidgets = m->dropArea()->dockWidgets();
    QCOMPARE(dockwidgets.size(), 1);

    auto dw = dockwidgets.constFirst();
    dw->close();
    QVERIFY(dw->isOpen());
    QVERIFY(dw->isPersistentCentralDockWidget());
    dw->setFloating(true);
    QVERIFY(!dw->isFloating());


    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    QVERIFY(!saved.isEmpty());

    QVERIFY(saver.restoreLayout(saved));
}

int main(int argc, char *argv[])
{
    KDDockWidgets::Platform::tests_initPlatform(argc, argv, KDDockWidgets::FrontendType::QtWidgets);
    if (shouldSkipTests())
        return 0;

    TestDocks test;

    const int exitCode = QTest::qExec(&test, argc, argv);
    KDDockWidgets::Platform::tests_deinitPlatform();

    return exitCode;
}
