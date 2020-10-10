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

#include <QtTest/QtTest>
#include <QObject>
#include <QApplication>

#ifdef KDDOCKWIDGETS_QTQUICK
# include "quick/DockWidgetQuick.h"

# include <QQmlEngine>
# include <QQuickStyle>
# else
# include "DockWidget.h"
#endif

using namespace KDDockWidgets;
using namespace Layouting;
using namespace KDDockWidgets::Tests;

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
        QQuickStyle::setStyle("Material"); // so we don't load KDE pluginss
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
    void tst_doesntHaveNativeTitleBar();
    void tst_resizeWindow2();
    void tst_hasLastDockedLocation();
    void tst_ghostSeparator();
    void tst_detachFromMainWindow();
    void tst_detachPos();
    void tst_floatingWindowSize();
    void tst_tabbingWithAffinities();
};

void TestCommon::tst_simple1()
{
    // Simply create a MainWindow
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    m->multiSplitter()->checkSanity();
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
        QVERIFY(!dropArea->drop(fw2, dw1->frame(), DropIndicatorOverlayInterface::DropLocation_Center));
        QVERIFY(dw1->window() != dw2->window());
    }

    delete fw1;
    delete fw2;
}

int main(int argc, char *argv[])
{
    if (!qpaPassedAsArgument(argc, argv)) {
        // Use offscreen by default as it's less annoying, doesn't create visible windows
        qputenv("QT_QPA_PLATFORM", "offscreen");
    }

    QApplication app(argc, argv);
    TestCommon test;

    return QTest::qExec(&test, argc, argv);
}

#include "tst_common.moc"
