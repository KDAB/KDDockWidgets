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
    void tst_close();
    void tst_propagateSizeHonoursMinSize();

    void tst_addDockWidgetAsTabToDockWidget();
    void tst_addToSmallMainWindow6();

    void tst_constraintsAfterPlaceholder();
    void tst_invalidLayoutAfterRestore();

    void tst_minSizeChanges();
    void tst_complex();
    void tst_addingOptionHiddenTabbed();
    void tst_flagDoubleClick();
    void tst_floatingWindowDeleted();
    void tst_maxSizedHonouredAfterRemoved();
    void tst_maximumSizePolicy();

private:
    std::unique_ptr<MultiSplitter> createMultiSplitterFromSetup(MultiSplitterSetup setup, QHash<QWidget *, Frame *> &frameMap) const;
};
}

Frame* createFrameWithWidget(const QString &name, MultiSplitter *parent, int minLength = -1)
{
    QWidget *w = createWidget(minLength, name);
    auto dw = new DockWidgetType(name);
    dw->setWidget(w);
    auto frame = KDDockWidgets::Config::self().frameworkWidgetFactory()->createFrame(parent);
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
        KDDockWidgets::Config::self().setFlags(Config::Flag_DoubleClickMaximizes);
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
