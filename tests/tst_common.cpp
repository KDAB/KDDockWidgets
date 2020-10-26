/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

#include "Testing.h"
#include "utils.h"
#include "DockWidgetBase.h"
#include "multisplitter/Separator_p.h"
#include "private/MultiSplitter_p.h"
#include "TitleBar_p.h"
#include "Position_p.h"
#include "DropAreaWithCentralFrame_p.h"
#include "WindowBeingDragged_p.h"
#include "Config.h"
#include "SideBar_p.h"

#include <QtTest/QtTest>
#include <QObject>
#include <QApplication>

#ifdef KDDOCKWIDGETS_QTQUICK
# include "quick/DockWidgetQuick.h"
# include "quick/MainWindowQuick_p.h"

# include <QQmlEngine>
# include <QQuickStyle>
# else
# include "DockWidget.h"
# include "MainWindow.h"

# include <QPushButton>
# include <QLineEdit>
# include <QTextEdit>
#endif

#ifdef Q_OS_WIN
# include <Windows.h>
#endif

using namespace KDDockWidgets;
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

class TestCommon : public QObject
{
    Q_OBJECT
public Q_SLOTS:
    void initTestCase()
    {
        qputenv("KDDOCKWIDGETS_SHOW_DEBUG_WINDOW", "");
        qApp->setOrganizationName("KDAB");
        qApp->setApplicationName("dockwidgets-unit-tests");

        Testing::installFatalMessageHandler();

#ifdef KDDOCKWIDGETS_QTQUICK
        QQuickStyle::setStyle("Material"); // so we don't load KDE plugins
        KDDockWidgets::Config::self().setQmlEngine(new QQmlEngine(this));
#endif
        QTest::qWait(10); // the DND state machine needs the event loop to start, otherwise activeState() is nullptr. (for offscreen QPA)
    }

    void cleanupTestCase()
    {
#ifdef KDDOCKWIDGETS_QTQUICK
        delete KDDockWidgets::Config::Config::self().qmlEngine();
#endif
    }

private Q_SLOTS:
    void tst_simple1();
    void tst_simple2();
    void tst_doesntHaveNativeTitleBar();
    void tst_resizeWindow2();
    void tst_hasLastDockedLocation();
    void tst_ghostSeparator();
    void tst_detachFromMainWindow();
    void tst_detachPos();
    void tst_floatingWindowSize();
    void tst_sizeAfterRedock();
    void tst_tabbingWithAffinities();
    void tst_honourUserGeometry();
    void tst_floatingWindowTitleBug();
    void tst_setFloatingSimple();

    void tst_resizeWindow_data();
    void tst_resizeWindow();
    void tst_restoreEmpty();
    void tst_restoreCentralFrame();
    void tst_shutdown();
    void tst_doubleClose();
    void tst_dockInternal();
    void tst_maximizeAndRestore();
    void tst_propagateResize2();
    void tst_28NestedWidgets();
    void tst_28NestedWidgets_data();
    void tst_negativeAnchorPosition();
    void tst_negativeAnchorPosition2();
    void tst_negativeAnchorPosition3();
    void tst_negativeAnchorPosition4();
    void tst_negativeAnchorPosition5();
    void tst_negativeAnchorPosition6();
    void tst_negativeAnchorPosition7();
    void tst_startHidden();
    void tst_startHidden2();
    void tst_startClosed();
    void tst_closeReparentsToNull();
    void tst_invalidAnchorGroup();
    void tst_addAsPlaceholder();
    void tst_removeItem();
    void tst_clear();
    void tst_samePositionAfterHideRestore();
    void tst_dockDockWidgetNested();
    void tst_dockFloatingWindowNested();
    void tst_crash();
    void tst_refUnrefItem();
    void tst_placeholderCount();
    void tst_availableLengthForOrientation();
    void tst_closeShowWhenNoCentralFrame();
    void tst_setAstCurrentTab();
    void tst_placeholderDisappearsOnReadd();
    void tst_placeholdersAreRemovedProperly();

    void tst_crash2_data();
    void tst_crash2();
    void tst_closeAllDockWidgets();
    void tst_toggleMiddleDockCrash();
    void tst_stealFrame();
    void tst_setFloatingWhenWasTabbed();
    void tst_setFloatingWhenSideBySide();
    void tst_dockWindowWithTwoSideBySideFramesIntoCenter();
    void tst_closeRemovesFromSideBar();
    void tst_tabTitleChanges();
    void tst_dockWidgetGetsFocusWhenDocked();
    void tst_setWidget();
    void tst_isFocused();
    void tst_floatingLastPosAfterDoubleClose();
    void tst_registry();
    void tst_honourGeometryOfHiddenWindow();
    void tst_0_data();
    void tst_0();
    void tst_dockWindowWithTwoSideBySideFramesIntoRight();
    void tst_dockWindowWithTwoSideBySideFramesIntoLeft();
    void tst_posAfterLeftDetach();
    void tst_preventClose();
    void tst_propagateMinSize();
    void tst_createFloatingWindow();
    void tst_addAndReadd();
    void tst_addToSmallMainWindow1();
    void tst_addToSmallMainWindow2();
    void tst_addToSmallMainWindow3();
    void tst_addToSmallMainWindow4();
    void tst_addToSmallMainWindow5();
    void tst_fairResizeAfterRemoveWidget();
    void tst_invalidJSON_data();
    void tst_invalidJSON();

    void tst_invalidPlaceholderPosition_data();
    void tst_invalidPlaceholderPosition();
    void tst_setVisibleFalseWhenSideBySide();
    void tst_embeddedMainWindow();
    void tst_restoreSimplest();
};

void TestCommon::tst_simple1()
{
    // Simply create a MainWindow
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    m->multiSplitter()->checkSanity();
}

void TestCommon::tst_simple2()
{
    // Simply create a MainWindow, and dock something on top
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dw = createDockWidget("dw", new MyWidget("dw", Qt::blue));
    auto fw = dw->floatingWindow();
    m->addDockWidget(dw, KDDockWidgets::Location_OnTop);
    m->multiSplitter()->checkSanity();
    delete fw;
}


void TestCommon::tst_doesntHaveNativeTitleBar()
{
    // Tests that a floating window doesn't have a native title bar
    // This test is mostly to test a bug that was happening with QtQuick, where the native title bar
    // would appear on linux
    EnsureTopLevelsDeleted e;

    auto dw1 = createDockWidget("dock1");
    FloatingWindow *fw = dw1->floatingWindow();
    QVERIFY(fw);
    QVERIFY(fw->windowFlags() & Qt::Tool);

#if defined(Q_OS_LINUX)
    QVERIFY(fw->windowFlags() & Qt::FramelessWindowHint);
#elif defined(Q_OS_WIN)
    QVERIFY(!(fw->windowFlags() & Qt::FramelessWindowHint));
#endif

    delete dw1->window();
}

void TestCommon::tst_resizeWindow2()
{
    // Tests that resizing the width of the main window will never move horizontal anchors

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    auto dock2 = createDockWidget("2");

    FloatingWindow *fw1 = dock1->floatingWindow();
    FloatingWindow *fw2 = dock2->floatingWindow();
    m->addDockWidget(dock1, Location_OnTop);
    m->addDockWidget(dock2, Location_OnBottom);

    auto layout = m->multiSplitter();
    Separator *anchor = layout->separators().at(0);
    const int oldPosY = anchor->position();
    m->resize(QSize(m->width() + 10, m->height()));
    QCOMPARE(anchor->position(), oldPosY);
    layout->checkSanity();

    delete fw1;
    delete fw2;
}

void TestCommon::tst_hasLastDockedLocation()
{
    // Tests DockWidgetBase::hasPreviousDockedLocation()

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    m->multiSplitter()->checkSanity();
    m->multiSplitter()->setObjectName("mainWindow-dropArea");
    dock1->floatingWindow()->multiSplitter()->setObjectName("first-dropArea1");
    dock1->floatingWindow()->multiSplitter()->checkSanity();
    auto window1 = dock1->window();
    QVERIFY(dock1->isFloating());
    QVERIFY(!dock1->hasPreviousDockedLocation());
    QVERIFY(dock1->setFloating(true));
    QVERIFY(!dock1->setFloating(false)); // No docking location, so it's not docked
    QVERIFY(dock1->isFloating());
    QVERIFY(!dock1->hasPreviousDockedLocation());

    m->addDockWidget(dock1, Location_OnBottom);
    m->multiSplitter()->checkSanity();

    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->setFloating(true));

    auto ms1 = dock1->floatingWindow()->multiSplitter();
    ms1->setObjectName("dropArea1");
    ms1->checkSanity();
    QVERIFY(dock1->hasPreviousDockedLocation());
    auto window11 = dock1->window();
    QVERIFY(dock1->setFloating(false));

    delete window1;
    delete window11;
}

void TestCommon::tst_ghostSeparator()
{
    // Tests a situation where a separator wouldn't be removed after a widget had been removed
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    auto dock2 = createDockWidget("2");
    auto dock3 = createDockWidget("3");

    QPointer<FloatingWindow> fw1 = dock1->floatingWindow();
    QPointer<FloatingWindow> fw2 = dock2->floatingWindow();
    QPointer<FloatingWindow> fw3 = dock3->floatingWindow();

    dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);
    QCOMPARE(fw1->multiSplitter()->separators().size(), 1);
    QCOMPARE(Layouting::Separator::numSeparators(), 1);

    m->addDockWidget(dock3, Location_OnBottom);
    QCOMPARE(m->multiSplitter()->separators().size(), 0);
    QCOMPARE(Layouting::Separator::numSeparators(), 1);

    m->multiSplitter()->addMultiSplitter(fw1->multiSplitter(), Location_OnRight);
    QCOMPARE(m->multiSplitter()->separators().size(), 2);
    QCOMPARE(Layouting::Separator::numSeparators(), 2);

    delete fw1;
    delete fw2;
    delete fw3;
}

void TestCommon::tst_detachFromMainWindow()
{
    // Tests a situation where clicking the float button wouldn't work on QtQuick
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    auto fw1 = dock1->window();
    m->addDockWidget(dock1, Location_OnTop);

    QVERIFY(m->multiSplitter()->mainWindow() != nullptr);
    QVERIFY(!dock1->isFloating());
    TitleBar *tb = dock1->titleBar();
    QVERIFY(tb == dock1->frame()->titleBar());
    QVERIFY(tb->isVisible());
    QVERIFY(!tb->isFloating());

    delete fw1;
}

void TestCommon::tst_detachPos()
{
    // Tests a situation where detaching a dock widget would send it to a bogus position
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new MyWidget(QStringLiteral("1"), Qt::black), {}, /** show = */false); // we're creating the dock widgets without showing them as floating initially, so it doesn't record the previous floating position
    auto dock2 = createDockWidget("2", new MyWidget(QStringLiteral("2"), Qt::black), {}, /** show = */false);

    QVERIFY(!dock1->isVisible());
    QVERIFY(!dock2->isVisible());

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);

    QVERIFY(!dock1->lastPositions().lastFloatingGeometry().isValid());
    QVERIFY(!dock2->lastPositions().lastFloatingGeometry().isValid());

    const int previousWidth = dock1->width();
    dock1->setFloating(true);
    QTest::qWait(400); // Needed for QtQuick

    QVERIFY(qAbs(previousWidth - dock1->width()) < 15); // 15px of difference when floating is fine, due to margins and what not.
    delete dock1->window();
}

void TestCommon::tst_floatingWindowSize()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    auto fw1 = dock1->window();


    QTest::qWait(2000);

    QVERIFY(!fw1->geometry().isNull());
    QCOMPARE(fw1->size(), fw1->windowHandle()->size());

    delete fw1;
}

void TestCommon::tst_tabbingWithAffinities()
{
    EnsureTopLevelsDeleted e;
    // Tests that dock widgets with different affinities should not tab together

    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None);
    m1->setAffinities({ "af1", "af2" });

    auto dw1 = new DockWidgetType("1");
    dw1->setAffinities({ "af1" });
    dw1->show();

    auto dw2 = new DockWidgetType("2");
    dw2->setAffinities({ "af2" });
    dw2->show();

    FloatingWindow *fw1 = dw1->floatingWindow();
    FloatingWindow *fw2 = dw2->floatingWindow();

    {
        SetExpectedWarning ignoreWarning("Refusing to dock widget with incompatible affinity");
        dw1->addDockWidgetAsTab(dw2);
        QVERIFY(dw1->window() != dw2->window());
    }

    m1->addDockWidget(dw1, Location_OnBottom);
    QVERIFY(!dw1->isFloating());

    {
        SetExpectedWarning ignoreWarning("Refusing to dock widget with incompatible affinity");
        auto dropArea = m1->dropArea();
        WindowBeingDragged wbd(fw2, fw2);
        QVERIFY(!dropArea->drop(&wbd, dw1->frame(), DropIndicatorOverlayInterface::DropLocation_Center));
        QVERIFY(dw1->window() != dw2->window());
    }

    delete fw1;
    delete fw2;
}

void TestCommon::tst_sizeAfterRedock()
{
    EnsureTopLevelsDeleted e;
    auto dw1 = new DockWidgetType(QStringLiteral("1"));
    auto dw2 = new DockWidgetType(QStringLiteral("2"));
    dw2->setWidget(new MyWidget("2", Qt::red));

    dw1->addDockWidgetToContainingWindow(dw2, Location_OnBottom);
    const int height2 = dw2->frame()->height();

    dw2->setFloating(true);
    QCOMPARE(height2, dw2->window()->height());
    auto oldFw2 = dw2->floatingWindow();

    // Redock
    FloatingWindow *fw1 = dw1->floatingWindow();
    DropArea *dropArea = fw1->dropArea();

    MultiSplitter *ms1 = fw1->multiSplitter();
    {
        WindowBeingDragged wbd2(oldFw2);
        const QRect suggestedDropRect = ms1->rectForDrop(&wbd2, Location_OnBottom, nullptr);
        QCOMPARE(suggestedDropRect.height(), height2);
    }

    dropArea->drop(dw2->floatingWindow(), Location_OnBottom, nullptr);

    QCOMPARE(dw2->frame()->height(), height2);

    delete dw1->window();
    delete oldFw2;
}

void TestCommon::tst_honourUserGeometry()
{
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None);
    auto dw1 = new DockWidgetType(QStringLiteral("1"));
    QVERIFY(!dw1->testAttribute(Qt::WA_PendingMoveEvent));

    const QPoint pt(10, 10);
    dw1->move(pt);
    dw1->show();
    FloatingWindow *fw1 = dw1->floatingWindow();
    QCOMPARE(fw1->windowHandle()->geometry().topLeft(), pt);

    delete dw1->window();
}

void TestCommon::tst_floatingWindowTitleBug()
{
    // Test for #74
    EnsureTopLevelsDeleted e;
    auto dw1 = new DockWidgetType(QStringLiteral("1"));
    auto dw2 = new DockWidgetType(QStringLiteral("2"));
    auto dw3 = new DockWidgetType(QStringLiteral("3"));

    dw1->setObjectName(QStringLiteral("1"));
    dw2->setObjectName(QStringLiteral("2"));
    dw3->setObjectName(QStringLiteral("3"));

    dw1->show();
    dw1->addDockWidgetAsTab(dw2);
    dw1->addDockWidgetToContainingWindow(dw3, Location_OnBottom);

    dw1->titleBar()->onFloatClicked();

    QCOMPARE(dw3->titleBar()->title(), QLatin1String("3"));

    delete dw1->window();
    delete dw3->window();
}

void TestCommon::tst_resizeWindow_data()
{
    QTest::addColumn<bool>("doASaveRestore");
    QTest::newRow("false") << false;
    QTest::newRow("true") << true;
}

void TestCommon::tst_resizeWindow()
{
    QFETCH(bool, doASaveRestore);

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new MyWidget("1", Qt::red));
    auto dock2 = createDockWidget("2", new MyWidget("2", Qt::blue));
    QPointer<FloatingWindow> fw1 = dock1->floatingWindow();
    QPointer<FloatingWindow> fw2 = dock2->floatingWindow();
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

    m->showMaximized();
    Testing::waitForResize(m.get());

    const int maximizedWidth1 = dock1->width();
    const int maximizedWidth2 = dock2->width();

    const double relativeDifference = qAbs((maximizedWidth1 - maximizedWidth2) / (1.0 * layout->width()));

    qDebug() << oldWidth1 << oldWidth2 << maximizedWidth1 << maximizedWidth2 << relativeDifference;
    QVERIFY(relativeDifference <= 0.01);

    m->showNormal();
    Testing::waitForResize(m.get());

    const int newWidth1 = dock1->width();
    const int newWidth2 = dock2->width();

    QCOMPARE(oldWidth1, newWidth1);
    QCOMPARE(oldWidth2, newWidth2);
    layout->checkSanity();

    delete fw1;
    delete fw2;
}

void TestCommon::tst_restoreEmpty()
{
    EnsureTopLevelsDeleted e;

    // Create an empty main window, save it to disk.
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto layout = m->multiSplitter();
    LayoutSaver saver;
    const QSize oldSize = m->size();
    QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreEmpty.json")));
    saver.restoreFromFile(QStringLiteral("layout_tst_restoreEmpty.json"));
    QVERIFY(m->multiSplitter()->checkSanity());
    QCOMPARE(layout->separators().size(), 0);
    QCOMPARE(layout->count(), 0);
    QCOMPARE(m->size(), oldSize);
    QVERIFY(layout->checkSanity());
}

void TestCommon::tst_restoreCentralFrame()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500));
    auto layout = m->multiSplitter();

    QCOMPARE(layout->count(), 1);
    Item *item = m->dropArea()->centralFrame();
    QVERIFY(item);
    auto frame = static_cast<Frame *>(item->guestAsQObject());
    QCOMPARE(frame->options(), FrameOption_IsCentralFrame | FrameOption_AlwaysShowsTabs);
    QVERIFY(!frame->titleBar()->isVisible());

    LayoutSaver saver;
    QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreCentralFrame.json")));
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreCentralFrame.json")));

    QCOMPARE(layout->count(), 1);
    item = m->dropArea()->centralFrame();
    QVERIFY(item);
    frame = static_cast<Frame *>(item->guestAsQObject());
    QCOMPARE(frame->options(), FrameOption_IsCentralFrame | FrameOption_AlwaysShowsTabs);
    QVERIFY(!frame->titleBar()->isVisible());
}

void TestCommon::tst_setFloatingSimple()
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

int main(int argc, char *argv[])
{
    if (!qpaPassedAsArgument(argc, argv)) {
        // Use offscreen by default as it's less annoying, doesn't create visible windows
        qputenv("QT_QPA_PLATFORM", "offscreen");
    }

    QApplication app(argc, argv);
    if (shouldSkipTests())
        return 0;

    TestCommon test;
    return QTest::qExec(&test, argc, argv);
}

void TestCommon::tst_doubleClose()
{
    EnsureTopLevelsDeleted e;
    {
        // Via close()
        auto dock1 = createDockWidget("hello", Qt::green);
        dock1->close();
        dock1->close();

        delete dock1->window();
    }
    {
        // Via the button
        auto dock1 = createDockWidget("hello", Qt::green);
        auto fw1 = dock1->floatingWindow();

        auto t = dock1->frame()->titleBar();
        t->onCloseClicked();
        t->onCloseClicked();

        delete dock1;
        delete fw1;
    }
}

void TestCommon::tst_dockInternal()
{
    /**
     * Here we dock relative to an existing widget, and not to the drop-area.
     */
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dropArea = m->dropArea();

    auto centralWidget = static_cast<Frame*>(dropArea->items()[0]->guestAsQObject());
    nestDockWidget(dock1, dropArea, centralWidget, KDDockWidgets::Location_OnRight);

    QVERIFY(dock1->width() < dropArea->width() - centralWidget->width());
}

void TestCommon::tst_maximizeAndRestore()
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
    Testing::waitForResize(m.get());

    QVERIFY(dropArea->checkSanity());
    qDebug() << "About to show normal";
    m->showNormal();
    Testing::waitForResize(m.get());

    QVERIFY(dropArea->checkSanity());
}

void TestCommon::tst_propagateResize2()
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

void TestCommon::tst_shutdown()
{
    EnsureTopLevelsDeleted e;
    auto dock = createDockWidget("doc1", Qt::green);

    auto m = createMainWindow();
    m->show();
    QVERIFY(QTest::qWaitForWindowActive(m->windowHandle()));
    delete dock->window();
}

void TestCommon::tst_28NestedWidgets_data()
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

void TestCommon::tst_28NestedWidgets()
{
    QFETCH(QVector<DockDescriptor>, docksToCreate);
    QFETCH(QVector<int>, docksToHide);

    // Tests a case that used to cause negative anchor position when turning into placeholder
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dropArea = m->dropArea();
    MultiSplitter *layout = dropArea;

    int i = 0;
    for (DockDescriptor &desc : docksToCreate) {
        desc.createdDock = createDockWidget(QString("%1").arg(i), new QPushButton(QString("%1").arg(i).toLatin1()), {}, false);

        DockWidgetBase *relativeTo = nullptr;
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

void TestCommon::tst_closeReparentsToNull()
{
    EnsureTopLevelsDeleted e;
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto fw1 = dock1->window();
    QVERIFY(dock1->parent() != nullptr);
    dock1->close();
    QVERIFY(dock1->parent() == nullptr);
    delete fw1;
    delete dock1;
}

void TestCommon::tst_startHidden()
{
    // A really simple test for AddingOption_StartHidden

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"), {}, /*show=*/false);
    m->addDockWidget(dock1, Location_OnRight, nullptr, AddingOption_StartHidden);
    delete dock1;
}

void TestCommon::tst_startHidden2()
{
    EnsureTopLevelsDeleted e;
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"), {}, false);
        auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, false);

        auto dropArea = m->dropArea();
        MultiSplitter *layout = dropArea;

        m->addDockWidget(dock1, Location_OnTop, nullptr, AddingOption_StartHidden);
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

        Testing::waitForResize(dock2);
    }

    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"), {}, false);
        auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, false);
        auto dock3 = createDockWidget("dock3", new QPushButton("three"), {}, false);

        auto dropArea = m->dropArea();
        MultiSplitter *layout = dropArea;
        m->addDockWidget(dock1, Location_OnLeft, nullptr, AddingOption_StartHidden);

        m->addDockWidget(dock2, Location_OnBottom, nullptr, AddingOption_StartHidden);
        m->addDockWidget(dock3, Location_OnRight, nullptr, AddingOption_StartHidden);

        dock1->show();

        QCOMPARE(layout->count(), 3);
        QCOMPARE(layout->placeholderCount(), 2);

        dock2->show();
        dock3->show();
        Testing::waitForResize(dock2);
        layout->checkSanity();
    }
}

void TestCommon::tst_negativeAnchorPosition()
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

    MultiSplitter *layout = m->multiSplitter();

    auto d1 = createDockWidget("1", w1);
    auto d2 = createDockWidget("2", w2);
    auto d3 = createDockWidget("3", w3);

    m->addDockWidgetAsTab(d1);

    m->addDockWidget(d2, Location_OnTop);
    m->addDockWidget(d3, Location_OnTop);

    d2->close();

    Testing::waitForResize(d3);
    d2->show(); // Should not result in negative anchor positions (Test will fail due to a qWarning)
    Testing::waitForResize(d3);
    layout->checkSanity();

    d2->close();
    Testing::waitForResize(d3);
    layout->checkSanity();

    // Now resize the Window, after removing middle one
    const int availableToShrink = layout->size().height() - layout->minimumSize().height();
    layout->setLayoutSize({layout->width(), layout->width() - availableToShrink});

    d2->deleteLater();
    Testing::waitForDeleted(d2);
    layout->checkSanity();
}

void TestCommon::tst_negativeAnchorPosition2()
{
    // Tests that the "Out of bounds position" warning doesn't appear. Test will abort if yes.
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dropArea = m->dropArea();
    MultiSplitter *layout = dropArea;

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
    QVERIFY(Testing::waitForDeleted(dock2));
}

void TestCommon::tst_negativeAnchorPosition3()
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
    MultiSplitter *layout = dropArea;
    layout->checkSanity();

    auto dock1 = docks.at(1).createdDock;
    auto dock3 = docks.at(3).createdDock;

    dock1->setFloating(true);
    delete dock1->window();
    delete dock3->window();

    layout->checkSanity();
}

void TestCommon::tst_negativeAnchorPosition4()
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
    MultiSplitter *layout = dropArea;
    layout->checkSanity();

    auto dock1 = docks.at(1).createdDock;
    auto dock2 = docks.at(2).createdDock;
    dock2->setFloating(true);
    auto fw2 = dock2->floatingWindow();
    dropArea->addWidget(fw2->dropArea(), Location_OnLeft, dock1->frame());
    dock2->setFloating(true);
    fw2 = dock2->floatingWindow();

    dropArea->addWidget(fw2->dropArea(), Location_OnRight, dock1->frame());

    layout->checkSanity();
    docks.at(0).createdDock->deleteLater();
    docks.at(4).createdDock->deleteLater();
    Testing::waitForDeleted(docks.at(4).createdDock);
}

void TestCommon::tst_negativeAnchorPosition5()
{
    EnsureTopLevelsDeleted e;
    QVector<DockDescriptor> docks = {
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        {Location_OnBottom, -1, nullptr, AddingOption_StartHidden },
        };

    auto m = createMainWindow(docks);
    auto dropArea = m->dropArea();
    MultiSplitter *layout = dropArea;
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

void TestCommon::tst_negativeAnchorPosition6()
{
    // Tests a case when we add a widget to left/right but the layout doesn't have enough height (or vice-versa)
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    m->resize(QSize(100, 100));
    m->show();

    auto layout = m->multiSplitter();

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
    layout->rectForDrop(nullptr, Location_OnTop, centralItem);
    layout->checkSanity();
}

void TestCommon::tst_negativeAnchorPosition7()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
    m->show();
    auto w1 = new MyWidget2(QSize(400,400));
    auto w2 = new MyWidget2(QSize(400,400));

    auto d1 = new DockWidgetType("1");
    d1->setWidget(w1);
    auto d2 = new DockWidgetType("2");
    d2->setWidget(w2);

    auto w3 = new MyWidget2(QSize(100,100));
    auto d3 = new DockWidgetType("3");
    d3->setWidget(w3);

    // Stack 1, 2
    m->addDockWidget(d2, Location_OnTop);
    m->addDockWidget(d1, Location_OnTop);

    // add a small one to the middle

    // Stack: 1, 3, 2
    m->addDockWidget(d3, Location_OnTop, d2);
    m->multiSplitter()->checkSanity();
}

void TestCommon::tst_invalidAnchorGroup()
{
    // Tests a bug I got. Should not warn.
    EnsureTopLevelsDeleted e;

    {
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));

        QPointer<FloatingWindow> fw = dock2->morphIntoFloatingWindow();
        nestDockWidget(dock1, fw->dropArea(), nullptr, KDDockWidgets::Location_OnTop);

        dock1->close();
        Testing::waitForResize(dock2);
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

void TestCommon::tst_addAsPlaceholder()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new QPushButton("one"), {}, false);
    auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, false);

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnTop, nullptr, AddingOption_StartHidden);

    auto dropArea = m->dropArea();
    MultiSplitter *layout = dropArea;

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

void TestCommon::tst_removeItem()
{
    // Tests that MultiSplitterLayout::removeItem() works
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"), {}, false);
    auto dock3 = createDockWidget("dock3", new QPushButton("three"));

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnTop, nullptr, AddingOption_StartHidden);
    Item *item2 = dock2->lastPositions().lastItem();

    auto dropArea = m->dropArea();
    MultiSplitter *layout = dropArea;

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);

    // 1. Remove an item that's a placeholder

    layout->removeItem(item2);

    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // 2. Remove an item that has an actual widget
    Item *item1 = dock1->lastPositions().lastItem();
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
    auto frame1 = dock1->frame();
    dock1->close();
    QVERIFY(Testing::waitForDeleted(frame1));

    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 2);

    // Now remove the items
    layout->removeItem(dock2->lastPositions().lastItem());
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    layout->checkSanity();
    layout->removeItem(dock1->lastPositions().lastItem());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // Add again
    m->addDockWidget(dock2, Location_OnBottom);
    m->addDockWidget(dock1, Location_OnBottom);
    dock2->close();
    frame1 = dock1->frame();
    dock1->close();
    QVERIFY(Testing::waitForDeleted(frame1));

    // Now remove the items, but first dock1
    layout->removeItem(dock1->lastPositions().lastItem());
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    layout->checkSanity();
    layout->removeItem(dock2->lastPositions().lastItem());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();

    // Add again, stacked as 1, 2, 3, then close 2 and 3.
    m->addDockWidget(dock2, Location_OnTop);
    m->addDockWidget(dock1, Location_OnTop);

    auto frame2 = dock2->frame();
    dock2->close();
    Testing::waitForDeleted(frame2);

    auto frame3 = dock3->frame();
    dock3->close();
    Testing::waitForDeleted(frame3);

    // The second anchor is now following the 3rd, while the 3rd is following 'bottom'
    layout->removeItem(dock3->lastPositions().lastItem()); // will trigger the 3rd anchor to be removed
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    layout->checkSanity();

    dock1->deleteLater();
    dock2->deleteLater();
    dock3->deleteLater();
    Testing::waitForDeleted(dock3);
}

void TestCommon::tst_clear()
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
    QVERIFY(Testing::waitForDeleted(fw3));
    dock3->close();

    QCOMPARE(Frame::dbg_numFrames(), 3);

    auto layout = m->multiSplitter();
    layout->rootItem()->clear();

    QCOMPARE(layout->count(), 0);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();

    // Cleanup
    dock3->deleteLater();
    QVERIFY(Testing::waitForDeleted(dock3));
}

void TestCommon::tst_samePositionAfterHideRestore()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    auto dock3 = createDockWidget("3", new QPushButton("3"));

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);
    QRect geo2 = dock2->frame()->QWidgetAdapter::geometry();
    dock2->setFloating(true);

    auto fw2 = dock2->floatingWindow();
    dock2->setFloating(false);
    QVERIFY(Testing::waitForDeleted(fw2));
    QCOMPARE(geo2, dock2->frame()->QWidgetAdapter::geometry());
    m->multiSplitter()->checkSanity();
}

void TestCommon::tst_startClosed()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));

    auto dropArea = m->dropArea();
    MultiSplitter *layout = dropArea;

    m->addDockWidget(dock1, Location_OnTop);
    Frame *frame1 = dock1->frame();
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

void TestCommon::tst_dockDockWidgetNested()
{
    EnsureTopLevelsDeleted e;
    // Test detaching too, and check if the window size is correct
    // TODO
}

void TestCommon::tst_dockFloatingWindowNested()
{
    EnsureTopLevelsDeleted e;
    // TODO
}

void TestCommon::tst_crash()
{
     // tests some crash I got

    EnsureTopLevelsDeleted e;

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
    auto layout = m->multiSplitter();

    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    Item *item1 = layout->itemForFrame(dock1->frame());
    dock1->addDockWidgetAsTab(dock2);

    QVERIFY(!dock1->isFloating());
    dock1->setFloating(true);
    QVERIFY(dock1->isFloating());
    QVERIFY(!dock1->isInMainWindow());

    Item *layoutItem = dock1->lastPositions().lastItem();
    QVERIFY(layoutItem && DockRegistry::self()->itemIsInMainWindow(layoutItem));
    QCOMPARE(layoutItem, item1);

    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->count(), 1);

    // Move from tab to bottom
    m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);

    delete dock1->window();
}

void TestCommon::tst_refUnrefItem()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("1"));
    auto dock2 = createDockWidget("dock2", new QPushButton("2"));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);
    auto dropArea = m->dropArea();
    auto layout = dropArea;
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
    QCOMPARE(dock2->lastPositions().lastItem(), item2.data());
    delete dock2;

    QVERIFY(!item2.data());
    QCOMPARE(layout->count(), 1);

    // 4. Move a closed dock widget from one mainwindow to another
    // It should delete its old placeholder
    auto dock4 = createDockWidget("dock4", new QPushButton("4"));
    m->addDockWidget(dock4, KDDockWidgets::Location_OnLeft);

    QPointer<Frame> frame4 = dock4->frame();
    QPointer<Item> item4 = layout->itemForFrame(frame4);
    dock4->close();
    Testing::waitForDeleted(frame4);
    QCOMPARE(item4->refCount(), 1);
    QVERIFY(item4->isPlaceholder());
    layout->checkSanity();

    auto m2 = createMainWindow();
    m2->addDockWidget(dock4, KDDockWidgets::Location_OnLeft);
    m2->multiSplitter()->checkSanity();
    QVERIFY(!item4.data());
}

void TestCommon::tst_placeholderCount()
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

void TestCommon::tst_availableLengthForOrientation()
{
    EnsureTopLevelsDeleted e;

    // 1. Test a completely empty window, it's available space is its size minus the static separators thickness
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    auto dropArea = m->dropArea();
    MultiSplitter *layout = dropArea;

    int availableWidth = layout->availableLengthForOrientation(Qt::Horizontal);
    int availableHeight = layout->availableLengthForOrientation(Qt::Vertical);
    QCOMPARE(availableWidth, layout->width());
    QCOMPARE(availableHeight, layout->height());

    //2. Now do the same, but we have some widget docked

    auto dock1 = createDockWidget("dock1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);

    const int dock1MinWidth = layout->itemForFrame(dock1->frame())->minLength(Qt::Horizontal);
    const int dock1MinHeight = layout->itemForFrame(dock1->frame())->minLength(Qt::Vertical);

    availableWidth = layout->availableLengthForOrientation(Qt::Horizontal);
    availableHeight = layout->availableLengthForOrientation(Qt::Vertical);
    QCOMPARE(availableWidth, layout->width() - dock1MinWidth);
    QCOMPARE(availableHeight, layout->height() - dock1MinHeight);
    m->multiSplitter()->checkSanity();
}

void TestCommon::tst_closeShowWhenNoCentralFrame()
{
    EnsureTopLevelsDeleted e;
    // Tests a crash I got when hidding and showing and no central frame

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    QPointer<DockWidgetBase> dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->close();
    m->multiSplitter()->checkSanity();

    QVERIFY(!dock1->frame());
    QVERIFY(!Testing::waitForDeleted(dock1)); // It was being deleted due to a bug
    QVERIFY(dock1);
    dock1->show();
    m->multiSplitter()->checkSanity();
}

void TestCommon::tst_setAstCurrentTab()
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
    fw->multiSplitter()->checkSanity();

    delete dock1; delete dock2;
    Testing::waitForDeleted(fw);
}

void TestCommon::tst_placeholderDisappearsOnReadd()
{
    // This tests that addMultiSplitter also updates refcount of placeholders

    // 1. Detach a widget and dock it on the opposite side. Placeholder
    // should have been deleted and anchors properly positioned

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    MultiSplitter *layout = m->multiSplitter();

    QPointer<DockWidgetBase> dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    dock1->setFloating(true);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 1);

    dock1->morphIntoFloatingWindow();
    auto fw = dock1->floatingWindow();
    layout->addMultiSplitter(fw->dropArea(), Location_OnRight );

    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->count(), 1);

    layout->checkSanity();
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // The dock1 should occupy the entire width
    QCOMPARE(dock1->frame()->width(), layout->width());

    QVERIFY(Testing::waitForDeleted(fw));
}

void TestCommon::tst_placeholdersAreRemovedProperly()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    MultiSplitter *layout = m->multiSplitter();
    QPointer<DockWidgetBase> dock1 = createDockWidget("1", new QPushButton("1"));
    QPointer<DockWidgetBase> dock2 = createDockWidget("2", new QPushButton("2"));
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
    auto window1 = Tests::make_qpointer(dock1->window());
    delete dock1;
    QCOMPARE(layout->separators().size(), 0);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();

    delete window1;
}

void TestCommon::tst_crash2_data()
{
    QTest::addColumn<bool>("show");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

void TestCommon::tst_crash2()
{
    QFETCH(bool, show);

    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(QSize(501, 500), MainWindowOption_None);
        auto layout = m->multiSplitter();
        m->setVisible(show);

        DockWidgetBase::List docks;
        const int num = 4;
        for (int i = 0; i < num; ++i)
            docks << new DockWidgetType(QString::number(i));

        QVector<KDDockWidgets::Location> locations = {Location_OnLeft,
                                                      Location_OnRight, Location_OnRight, Location_OnRight};

        QVector<KDDockWidgets::AddingOption> options = { AddingOption_StartHidden,
                                                        AddingOption_StartHidden, AddingOption_None, AddingOption_StartHidden};

        QVector<bool> floatings =  {true, false, false, false};

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
        DockWidgetBase::List docks;
        for (int i = 0; i < num; ++i)
            docks << new DockWidgetType(QString::number(i));

        QVector<KDDockWidgets::Location> locations = {Location_OnLeft, Location_OnLeft,
                                                      Location_OnRight};

        QVector<KDDockWidgets::AddingOption> options = { AddingOption_None, AddingOption_None,
                                                        AddingOption_StartHidden};

        QVector<bool> floatings =  {true, false, false};

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

void TestCommon::tst_closeAllDockWidgets()
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

    nestDockWidget(dock4, dropArea, nullptr, KDDockWidgets::Location_OnRight);
    nestDockWidget(dock5, dropArea, nullptr, KDDockWidgets::Location_OnTop);

    const int oldFWHeight = fw->height();
    nestDockWidget(dock6, fw->dropArea(), nullptr, KDDockWidgets::Location_OnTop);

    QVERIFY(oldFWHeight <= fw->height());
    QCOMPARE(fw->frames().size(), 2);

    QCOMPARE(dock3->window(), fw.data());
    QCOMPARE(dock4->window(), m.get());
    QCOMPARE(dock5->window(), m.get());
    QCOMPARE(dock6->window(), fw.data());
    auto layout = m->multiSplitter();
    layout->checkSanity();
    DockRegistry::self()->clear();
    layout->checkSanity();

    Testing::waitForDeleted(fw);
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

void TestCommon::tst_toggleMiddleDockCrash()
{
    // tests some crash I got

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central frame
    MultiSplitter *layout = m->multiSplitter();
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
    QVERIFY(Testing::waitForDeleted(frame));

    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 1);
    QVERIFY(layout->checkSanity());

    dock2->show();
    layout->checkSanity();
}

void TestCommon::tst_stealFrame()
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
    QPointer<Item> item2 = dropArea1->itemForFrame(dock2->frame());
    m2->addDockWidget(dock2, Location_OnRight);
    QVERIFY(!item2.data());

    QCOMPARE(dropArea1->count(), 2);
    QCOMPARE(dropArea2->count(), 2);
    QCOMPARE(dropArea1->placeholderCount(), 0);
    QCOMPARE(dropArea2->placeholderCount(), 0);

    // 2. MainWindow #1 steals a widget from MainWindow2 and vice-versa, but adds as tabs
    dock1->addDockWidgetAsTab(dock3);
    QPointer<Frame> f2 = dock2->frame();
    dock4->addDockWidgetAsTab(dock2);
    QVERIFY(Testing::waitForDeleted(f2.data()));
    QVERIFY(!f2.data());

    QCOMPARE(dropArea1->count(), 1);
    QCOMPARE(dropArea2->count(), 1);
    QCOMPARE(dropArea1->placeholderCount(), 0);
    QCOMPARE(dropArea2->placeholderCount(), 0);

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

    QCOMPARE(dropArea1->count(), 2);
    QCOMPARE(dropArea1->placeholderCount(), 0);

    // 5. And also steal a side-by-side one into the tab
    QPointer<Frame> f4 = dock4->frame();
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
        SetExpectedWarning sew("Invalid parameters KDDockWidgets::DockWidget"); // Suppress the qFatal this time
        m2->addDockWidget(dock1, Location_OnLeft, dock1);
        QCOMPARE(dropArea2->count(), 2);  // Nothing happened
        QCOMPARE(dropArea2->placeholderCount(), 0);
        QVERIFY(dock1->isVisible());
    }

    QVERIFY(dock1->isVisible());
    m2->addDockWidget(dock1, Location_OnLeft, nullptr); // Should not warn

    QVERIFY(dock1->isVisible());
    QCOMPARE(dropArea2->count(), 2);  // Nothing happened
    QCOMPARE(dropArea2->placeholderCount(), 0);

    m2->addDockWidget(dock1, Location_OnLeft, nullptr);
    QVERIFY(dock1->isVisible());
    QCOMPARE(dropArea2->count(), 2);  // Nothing happened
    QCOMPARE(dropArea2->placeholderCount(), 0);
    dropArea1->checkSanity();
    dropArea2->checkSanity();
}

void TestCommon::tst_setFloatingWhenWasTabbed()
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
    QCOMPARE(dock2->frame()->dockWidgetCount(), 2);
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

    QCOMPARE(dock2->lastPositions().lastTabIndex(), 1);
    QVERIFY(dock2->lastPositions().isValid());
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
    QCOMPARE(dock2->frame()->indexOfDockWidget(dock2), 1);

    // 10. Float dock1, and dock it to main window as tab. This tests Option_AlwaysShowsTabs.
    dock1->setFloating(true);
    dock2->setFloating(true);
    dock3->setFloating(true);

    m->addDockWidgetAsTab(dock1);
    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->isTabbed());
    dock1->setFloating(true);
    dock1->setFloating(false);
    QCOMPARE(dock1->frame()->dockWidgetCount(), 1);
    // Cleanup
    m->addDockWidgetAsTab(dock2);
    m->addDockWidgetAsTab(dock3);
    m->deleteLater();
    auto window = m.release();
    Testing::waitForDeleted(window);
}

void TestCommon::tst_setFloatingWhenSideBySide()
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

        Testing::waitForDeleted(fw);
    }

    {
        // 2. Tests a case where restoring a dock widget wouldn't make it use all its available space
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", new QPushButton("one"));
        auto dock2 = createDockWidget("dock2", new QPushButton("two"));
        auto dock3 = createDockWidget("dock3", new QPushButton("three"));
        auto dropArea = m->dropArea();
        MultiSplitter *layout = dropArea;
        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);
        m->addDockWidget(dock3, KDDockWidgets::Location_OnRight);
        auto f2 = dock2->frame();
        Item *item2 = layout->itemForFrame(f2);
        QVERIFY(item2);
        dock2->close();
        dock3->close();
        Testing::waitForDeleted(f2);
        dock2->show();
        Testing::waitForResize(dock2);

        QCOMPARE(item2->geometry(), dock2->frame()->QWidgetAdapter::geometry());
        layout->checkSanity();

        // Cleanup
        dock3->deleteLater();
        Testing::waitForDeleted(dock3);
    }
}

void TestCommon::tst_dockWindowWithTwoSideBySideFramesIntoCenter()
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
    QVERIFY(Testing::waitForDeleted(fw));
    delete fw2;
}

void TestCommon::tst_closeRemovesFromSideBar()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None);
    auto dw1 = new DockWidgetType(QStringLiteral("1"));
    auto fw1 = dw1->window();
    m1->addDockWidget(dw1, Location_OnBottom);
    m1->moveToSideBar(dw1);

    QVERIFY(!dw1->isOverlayed());
    QVERIFY(!dw1->isVisible());
    QVERIFY(dw1->sideBarLocation() != SideBarLocation::None);

    SideBar *sb = m1->sideBarForDockWidget(dw1);
    QVERIFY(sb);

    // Overlay it:
    sb->toggleOverlay(dw1);
    QVERIFY(dw1->isOverlayed());
    QVERIFY(dw1->isVisible());
    QCOMPARE(dw1->sideBarLocation(), sb->location());
    QVERIFY(dw1->isInMainWindow());
    QVERIFY(!dw1->isFloating());

    // Close it while it's overlayed:
    dw1->close();
    QVERIFY(!dw1->isInMainWindow());
    QVERIFY(!dw1->isOverlayed());
    QVERIFY(!dw1->isVisible());
    QCOMPARE(dw1->sideBarLocation(), SideBarLocation::None);

    delete fw1;
}

void TestCommon::tst_tabTitleChanges()
{
    // Tests that the tab's title changes if the dock widget's title changes
#ifdef KDDOCKWIDGETS_QTWIDGETS // TODO
    EnsureTopLevelsDeleted e;
    auto dw1 = new DockWidgetType(QStringLiteral("1"));
    auto dw2 = new DockWidgetType(QStringLiteral("2"));

    dw1->addDockWidgetAsTab(dw2);

    auto frame = qobject_cast<FrameWidget*>(dw1->frame());
    QTabBar *tb = frame->tabBar();
    QCOMPARE(tb->tabText(0), QStringLiteral("1"));
    dw1->setTitle(QStringLiteral("other"));
    QCOMPARE(tb->tabText(0), QStringLiteral("other"));

    delete dw1->window();
#endif
}
void TestCommon::tst_dockWidgetGetsFocusWhenDocked()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_TitleBarIsFocusable);

    auto dw1 = new DockWidgetType(QStringLiteral("1"));
    auto dw2 = new DockWidgetType(QStringLiteral("2"));
    auto le1 = new QLineEdit();
    auto le2 = new QLineEdit();
    dw1->setWidget(le1);
    dw2->setWidget(le2);
    dw1->show();
    dw2->show();

    auto fw1 = dw1->floatingWindow();
    QPointer<FloatingWindow> fw2 = dw2->floatingWindow();

    // Focus dock widget 1 first
    QVERIFY(!dw1->isFocused());
    dw1->window()->activateWindow();
    le1->setFocus(Qt::MouseFocusReason);
    QTest::qWait(200);
    QVERIFY(dw1->isFocused());

    QVERIFY(fw1->isActiveWindow());
    dragFloatingWindowTo(fw2, fw1->dropArea(), DropIndicatorOverlayInterface::DropLocation_Left);
    Testing::waitForEvent(fw1, QEvent::WindowActivate);

    /// We dropped into floating window 1, it should still be active
    QVERIFY(fw1->isActiveWindow());

    // DockWidget 2 was dropped, it should now be focused
    QVERIFY(!dw1->isFocused());
    QVERIFY(dw2->isFocused());

    delete fw1;
    delete fw2;
}

void TestCommon::tst_isFocused()
{
    EnsureTopLevelsDeleted e;

    // 1. Create 2 floating windows
    auto dock1 = createDockWidget(QStringLiteral("dock1"), new QLineEdit());
    auto dock2 = createDockWidget(QStringLiteral("dock2"), new QLineEdit());

    QTest::qWait(200); // macOS is flaky here, needs dock2 to be shown first before focusing dock1, otherwise dock1 looses again

    dock1->window()->move(400, 200);

    // 2. Raise dock1 and focus its line edit
    dock1->raise();
    dock1->widget()->setFocus(Qt::OtherFocusReason);
    Testing::waitForEvent(dock1->widget(), QEvent::FocusIn);

    QVERIFY(dock1->isFocused());
    QVERIFY(!dock2->isFocused());

    // 3. Raise dock3 and focus its line edit
    dock2->raise();
    dock2->widget()->setFocus(Qt::OtherFocusReason);
    Testing::waitForEvent(dock2->widget(), QEvent::FocusIn);
    QVERIFY(!dock1->isFocused());
    QVERIFY(dock2->isFocused());

    // 4. Tab dock1, it's current tab now
    auto oldFw1 = dock1->window();
    dock2->addDockWidgetAsTab(dock1);
    delete oldFw1;
    QVERIFY(dock1->isFocused());
    QVERIFY(!dock2->isFocused());

    // 5. Set dock2 as current tab again
    dock2->raise();
    QVERIFY(!dock1->isFocused());
    QVERIFY(dock2->isFocused());

    // 6. Create dock3, focus it
    auto dock3 = createDockWidget(QStringLiteral("dock3"), new QLineEdit());
    auto oldFw3 = dock3->window();
    dock3->raise();
    dock3->widget()->setFocus(Qt::OtherFocusReason);
    Testing::waitForEvent(dock2->widget(), QEvent::FocusIn);
    QVERIFY(!dock1->isFocused());
    QVERIFY(!dock2->isFocused());
    QVERIFY(dock3->isFocused());

    // 4. Add dock3 to the 1st window, nested, focus 2 again
    dock2->addDockWidgetToContainingWindow(dock3, Location_OnLeft);
    delete oldFw3;
    dock2->raise();
    dock2->widget()->setFocus(Qt::OtherFocusReason);
    Testing::waitForEvent(dock2->widget(), QEvent::FocusIn);
    QVERIFY(!dock1->isFocused());
    QVERIFY(dock2->isFocused());
    QVERIFY(!dock3->isFocused());
    delete dock2->window();
}

void TestCommon::tst_setWidget()
{
    EnsureTopLevelsDeleted e;
    auto dw = new DockWidgetType(QStringLiteral("FOO"));
    auto button1 = new QPushButton("button1");
    auto button2 = new QPushButton("button2");
    dw->setWidget(button1);
    dw->setWidget(button2);
    delete button1;
    delete dw;
}

void TestCommon::tst_floatingLastPosAfterDoubleClose()
{
    EnsureTopLevelsDeleted e;
    auto d1 = new DockWidgetType(QStringLiteral("a"));
    QVERIFY(d1->lastPositions().lastFloatingGeometry().isNull());
    QVERIFY(!d1->isVisible());
    d1->close();
    QVERIFY(d1->lastPositions().lastFloatingGeometry().isNull());
    delete d1;
}

void TestCommon::tst_0_data()
{
    QTest::addColumn<int>("thickness");
    QTest::newRow("2") << 2;
    QTest::newRow("1") << 1;
    QTest::newRow("0") << 0;
}

void TestCommon::tst_0()
{
    QFETCH(int, thickness);
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setSeparatorThickness(thickness);

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    m->resize(QSize(502, 500));
    m->show();

    auto d1 = createDockWidget("1", new QTextEdit());
    auto d2 = createDockWidget("2", new QTextEdit());

    m->addDockWidget(d1, Location_OnLeft);
    m->addDockWidget(d2, Location_OnRight);
}

void TestCommon::tst_honourGeometryOfHiddenWindow()
{
    EnsureTopLevelsDeleted e;

    auto d1 = new DockWidgetType("1");
    d1->setWidget(new QTextEdit());

    QVERIFY(!d1->isVisible());

    // Clear had a bug where it saved the position of all dock widgets being closed
    DockRegistry::self()->clear();

    const QRect suggestedGeo(150, 150, 250, 250);
    d1->setGeometry(suggestedGeo);

    d1->show();
    Testing::waitForEvent(d1, QEvent::Show);

    QCOMPARE( d1->window()->geometry(), suggestedGeo);
    delete d1->window();
}

void TestCommon::tst_registry()
{
    EnsureTopLevelsDeleted e;
    auto dr = DockRegistry::self();

    QCOMPARE(dr->dockwidgets().size(), 0);
    auto dw = new DockWidgetType(QStringLiteral("dw1"));
    auto guest = new QWidgetOrQuick();
    dw->setWidget(guest);
    QCOMPARE(dr->dockWidgetForGuest(nullptr), nullptr);
    QCOMPARE(dr->dockWidgetForGuest(guest), dw);
    delete dw;
}

void TestCommon::tst_dockWindowWithTwoSideBySideFramesIntoRight()
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
    QVERIFY(fw2->dropArea()->checkSanity());

    fw2->deleteLater();
    Testing::waitForDeleted(fw2);
}

void TestCommon::tst_dockWindowWithTwoSideBySideFramesIntoLeft()
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

    QVERIFY(fw2->dropArea()->checkSanity());

    ///Cleanup
    fw2->deleteLater();
    Testing::waitForDeleted(fw2);
}

void TestCommon::tst_posAfterLeftDetach()
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
        Testing::waitForDeleted(fw);
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
        Testing::waitForDeleted(fw);
    }
}

void TestCommon::tst_preventClose()
{
    EnsureTopLevelsDeleted e;

    auto nonClosableWidget = new NonClosableWidget();
    auto dock1 = new DockWidgetType("1");
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
    QVERIFY(Testing::waitForDeleted(dock1));
}

void TestCommon::tst_propagateMinSize()
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

void TestCommon::tst_createFloatingWindow()
{
    EnsureTopLevelsDeleted e;

    auto dock = createDockWidget("doc1", Qt::green);
    QVERIFY(dock);
    QVERIFY(dock->isFloating());

    QCOMPARE(dock->uniqueName(), QLatin1String("doc1")); // 1.0 objectName() is inherited

    QPointer<FloatingWindow> window = dock->floatingWindow();
    QVERIFY(window); // 1.1 DockWidget creates a FloatingWindow and is reparented
    QVERIFY(window->dropArea()->checkSanity());
    dock->deleteLater();
    QVERIFY(Testing::waitForDeleted(dock));
    QVERIFY(Testing::waitForDeleted(window)); // 1.2 Floating Window is destroyed when DockWidget is destroyed
    QVERIFY(!window);
}

void TestCommon::tst_addAndReadd()
{
    EnsureTopLevelsDeleted e;

    // 1. This just tests some crash I got.
    // Make a dock widget float and immediately reattach it
    auto m = createMainWindow();
    QTest::qWait(10); // the DND state machine needs the event loop to start, otherwise activeState() is nullptr. (for offscreen QPA)

    auto dock1 = createDockWidget("dock1", new QPushButton("1"));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->setFloating(true);
    m->multiSplitter()->checkSanity();
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->frame()->titleBar()->makeWindow();
    m->multiSplitter()->checkSanity();
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->frame()->titleBar()->makeWindow();
    m->multiSplitter()->checkSanity();

    auto fw = dock1->floatingWindow();
    QVERIFY(fw);
    auto dropArea = m->dropArea();
    dragFloatingWindowTo(fw, dropArea, DropIndicatorOverlayInterface::DropLocation_OutterRight);
    QVERIFY(!dock1->frame()->titleBar()->isVisible());
    fw->titleBar()->makeWindow();
    m->multiSplitter()->checkSanity();

    //Cleanup
    delete dock1;
    Testing::waitForDeleted(fw);
}


void TestCommon::tst_addToSmallMainWindow1()
{
    EnsureTopLevelsDeleted e;
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
    m->addDockWidget(dock4, Location_OnBottom);

    auto dropArea = m->dropArea();

    QVERIFY(dropArea->checkSanity());
    QVERIFY(dock2->width() < mainWindowLength);
    QVERIFY(dock3->height() < m->height());
    QVERIFY(dock4->height() < m->height());
}

void TestCommon::tst_addToSmallMainWindow2()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(100, 100)));
    auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(100, 100)));
    m->addDockWidgetAsTab(dock1);
    m->resize(osWindowMinWidth(), 200);

    Testing::waitForResize(m.get());

    QVERIFY(qAbs(m->width() - osWindowMinWidth()) < 15); // Not very important verification. Anyway, using 15 to account for margins and what not.
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);
    QVERIFY(Testing::waitForResize(m.get()));

    QVERIFY(dropArea->width() > osWindowMinWidth());
    QMargins margins = m->centerWidgetMargins();
    QCOMPARE(dropArea->width(), m->width() - margins.left() - margins.right());
    QVERIFY(m->dropArea()->checkSanity());
}

void TestCommon::tst_addToSmallMainWindow3()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget("dock1", new MyWidget2());
    auto dock2 = createDockWidget("dock2", new MyWidget2());
    m->addDockWidgetAsTab(dock1);
    m->resize(osWindowMinWidth(), 200);
    QTest::qWait(200);
    QVERIFY(qAbs(m->width() - osWindowMinWidth()) < 15); // Not very important verification. Anyway, using 15 to account for margins and what not.

    auto fw = dock2->morphIntoFloatingWindow();
    QVERIFY(fw->isVisible());
    QVERIFY(dropArea->checkSanity());
    dragFloatingWindowTo(fw, dropArea, DropIndicatorOverlayInterface::DropLocation_Right);
    QVERIFY(m->dropArea()->checkSanity());
    delete fw;
}

void TestCommon::tst_addToSmallMainWindow4()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(100, 100), MainWindowOption_None);
    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget("dock1", new MyWidget2(QSize(50, 50)));
    auto dock2 = createDockWidget("dock2", new MyWidget2(QSize(50, 50)));
    MultiSplitter *layout = dropArea;
    m->addDockWidget(dock1, KDDockWidgets::Location_OnBottom);
    Testing::waitForResize(m.get());

    m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);
    Testing::waitForResize(m.get());
    QVERIFY(m->dropArea()->checkSanity());

    const int item2MinHeight = layout->itemForFrame(dock2->frame())->minLength(Qt::Vertical);
    QCOMPARE(dropArea->height(), dock1->frame()->height() + item2MinHeight + Item::separatorThickness);
}

void TestCommon::tst_addToSmallMainWindow5()
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

void TestCommon::tst_fairResizeAfterRemoveWidget()
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
    MultiSplitter *layout = fw->dropArea();
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->visibleCount(), 3);
    QCOMPARE(layout->placeholderCount(), 0);

    delete dock2;
    QVERIFY(Testing::waitForResize(dock1));
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

    delete dock1->window();
}

void TestCommon::tst_invalidJSON_data()
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

void TestCommon::tst_invalidJSON()
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

void TestCommon::tst_invalidPlaceholderPosition_data()
{
    QTest::addColumn<bool>("restore1First");
    QTest::newRow("restore1First") << true;
    QTest::newRow("restore2First") << false;
}

void TestCommon::tst_invalidPlaceholderPosition()
{
    QFETCH(bool, restore1First);

    // Tests a bug I saw: 3 widgets stacked, close the top one, then the second top one
    // result: the bottom most one didn't have it's top separator at y=0

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    auto dock3 = createDockWidget("3", new QPushButton("3"));

    MultiSplitter *layout = m->multiSplitter();

    // Stack: 1, 2, 3 vertically
    m->addDockWidget(dock3, Location_OnTop);
    m->addDockWidget(dock2, Location_OnTop);
    m->addDockWidget(dock1, Location_OnTop);

    auto frame1 = dock1->frame();
    auto frame2 = dock2->frame();
    auto frame3 = dock3->frame();
    QCOMPARE(frame1->QWidgetAdapter::y(), 0);

    // Close 1
    dock1->close();
    Testing::waitForResize(frame2);

    // Check that frame2 moved up to y=1
    QCOMPARE(frame2->QWidgetAdapter::y(), 0);

    // Close 2
    dock2->close();
    Testing::waitForResize(dock3);

    QVERIFY(layout->checkSanity());
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 2);

    // Check that frame3 moved up to y=1
    QCOMPARE(frame3->QWidgetAdapter::y(), 0);

    // Now restore:
    auto toRestore1 = restore1First ? dock1 : dock2;
    auto toRestore2 = restore1First ? dock2 : dock1;


    qDebug() << "About to show dock1";
    toRestore1->show();
    QCOMPARE(layout->placeholderCount(), 1);
    QVERIFY(dock3->isVisible());
    QVERIFY(!dock3->size().isNull());

    toRestore2->show();

    Testing::waitForResize(frame3);
    QVERIFY(layout->checkSanity());
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();

    dock1->deleteLater();
    dock2->deleteLater();
    QVERIFY(Testing::waitForDeleted(dock2));
}

void TestCommon::tst_setVisibleFalseWhenSideBySide()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("one"));
    auto dock2 = createDockWidget("dock2", new QPushButton("two"));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

    const QRect oldGeo = dock1->geometry();
    auto oldParent = dock1->parentWidget();

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
    QVERIFY(!dock1->frame()->QWidgetAdapter::isVisible());

    // Cleanup
    m->deleteLater();
    auto window = m.release();
    Testing::waitForDeleted(window);
}

void TestCommon::tst_embeddedMainWindow()
{
    EnsureTopLevelsDeleted e;
    // Tests a MainWindow which isn't a top-level window, but is embedded in another window
    EmbeddedWindow *window = createEmbeddedMainWindow(QSize(800, 800));

    QTest::qWait(10); // the DND state machine needs the event loop to start, otherwise activeState() is nullptr. (for offscreen QPA)

    auto dock1 = createDockWidget("1", new QPushButton("1"));
    window->mainWindow->addDockWidget(dock1, Location_OnTop);
    dock1->setFloating(true);
    auto dropArea = window->mainWindow->dropArea();
    auto fw = dock1->floatingWindow();

    dragFloatingWindowTo(fw, dropArea, DropIndicatorOverlayInterface::DropLocation_Left);

    auto layout = dropArea;
    QVERIFY(Testing::waitForDeleted(fw));
    QCOMPARE(layout->count(), 2); // 2, as it has the central frame
    QCOMPARE(layout->visibleCount(), 2);
    layout->checkSanity();

    delete window;
}

void TestCommon::tst_restoreSimplest()
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

#include "tst_common.moc"
