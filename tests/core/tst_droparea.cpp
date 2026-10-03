/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../utils.h"
#include "core/DropArea.h"
#include "core/Group.h"
#include "Config.h"
#include "core/DockWidget.h"
#include "core/ViewFactory.h"
#include "core/Platform.h"
#include "core/DropIndicatorOverlay.h"
#include "core/indicators/SegmentedDropIndicatorOverlay.h"
#include "core/View.h"
#include "core/MainWindow.h"
#include "core/FloatingWindow.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::Tests;

class TestDropArea : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_dropAreaCtor();
    void tst_addWidget();
    void tst_addWidgetHidden();
    void tst_segmentedIndicators();
    void tst_validateInputs();
};

void TestDropArea::tst_dropAreaCtor()
{
    // Tests that ctor runs and doesn't leak
    Core::DropArea da(nullptr, {});
}

void TestDropArea::tst_addWidget()
{
    auto group = new Core::Group();
    Core::DropArea da(nullptr, {});
    da.addWidget(group->view(), KDDockWidgets::Location_OnLeft);
}

void TestDropArea::tst_addWidgetHidden()
{
    // Test adding a widget that starts hidden

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    Core::DropArea da(nullptr, {});
    da.addDockWidget(dw, KDDockWidgets::Location_OnLeft, nullptr,
                     InitialVisibilityOption::StartHidden);

    QVERIFY(!dw->isOpen());
    QVERIFY(!dw->toggleAction()->isChecked());
    dw->open();
    QVERIFY(dw->isOpen());
    QVERIFY(dw->toggleAction()->isChecked());

    auto group = dw->dptr()->group();
    delete dw;
    WAIT_FOR_DELETED(group);
}

void TestDropArea::tst_segmentedIndicators()
{
    if (!Platform::instance()->isQtWidgets())
        QSKIP("Segmented indicators are only supported by QtWidgets");

    struct TypeRestorer
    {
        ~TypeRestorer()
        {
            ViewFactory::s_dropIndicatorType = DropIndicatorType::Classic;
        }
    } restorer;
    ViewFactory::s_dropIndicatorType = DropIndicatorType::Segmented;

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(1000, 1000), MainWindowOption_None);
    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget("dock1");
    auto dock2 = createDockWidget("dock2");
    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);

    auto overlay = dynamic_cast<Core::SegmentedDropIndicatorOverlay *>(dropArea->dropIndicatorOverlay());
    QVERIFY(overlay);

    auto fw = createFloatingWindow();
    auto draggable = draggableFor(fw->view());
    QVERIFY(draggable);

    // Hover over the center, the indicators appear
    auto groupView = dock1->dptr()->group()->view();
    const Point center = groupView->mapToGlobal(groupView->rect().center());
    drag(draggable, draggable->mapToGlobal(Point(10, 10)), center, ButtonAction_Press);
    QVERIFY(overlay->isVisible());
    QCOMPARE(overlay->currentDropLocation(), DropLocation_Center);
    QVERIFY(!overlay->segments().empty());
    QCOMPARE(overlay->dropLocationForPos(overlay->hoveredPt()), DropLocation_Center);

    // The outter segments hug the window border
    const Point nearLeftBorder = dropArea->view()->mapToGlobal(Point(3, dropArea->view()->height() / 2));
    drag(draggable, Point(), nearLeftBorder, ButtonAction_None);
    QCOMPARE(overlay->currentDropLocation(), DropLocation_OutterLeft);

    // Not over any segment
    const Point nowhere = dropArea->view()->mapToGlobal(Point(dropArea->view()->width() / 2, 100));
    drag(draggable, Point(), nowhere, ButtonAction_None);
    QCOMPARE(overlay->currentDropLocation(), DropLocation_None);

    // Drop it on the center, it becomes a tab
    drag(draggable, Point(), center, ButtonAction_Release);
    QVERIFY(!overlay->isVisible());
    QCOMPARE(dock1->dptr()->group()->dockWidgetCount(), 2);
}

void TestDropArea::tst_validateInputs()
{
    {
        EnsureTopLevelsDeleted e;
        auto dw1 = createDockWidget("dw1");
        auto dw2 = createDockWidget("dw2");
        auto dw3 = createDockWidget("dw3");
        Core::DropArea da(nullptr, {});
        Core::DropArea other(nullptr, {});
        other.addDockWidget(dw3, Location_OnLeft, nullptr);

        {
            SetExpectedWarning sew("Invalid parameters");
            da.addDockWidget(dw1, Location_None, nullptr);
            da.addDockWidget(nullptr, Location_OnLeft, nullptr);
            da.addDockWidget(dw1, Location_OnLeft, dw1);
            da._addDockWidget(nullptr, Location_OnLeft, nullptr, {});
            QVERIFY(!da.containsDockWidget(dw1));
        }

        {
            auto group = new Core::Group();
            SetExpectedWarning sew("not adding to location None");
            da.addWidget(group->view(), Location_None, nullptr);
            delete group;
        }

        {
            // A dock widget needs to start hidden, as it's the dock widget which creates the group
            SetExpectedWarning sew("Wrong parameters");
            da.addWidget(dw1->view(), Location_OnLeft, nullptr);
            QVERIFY(!da.containsDockWidget(dw1));
        }

        {
            SetExpectedWarning sew("Unknown widget type");
            auto view = Platform::instance()->tests_createView({ true });
            da.addWidget(view, Location_OnLeft, nullptr);
            delete view;
        }

        {
            // dw3 lives in another layout
            da.addDockWidget(dw1, Location_OnLeft, nullptr);
            SetExpectedWarning sew("Doesn't contain relativeTo");
            da.addDockWidget(dw2, Location_OnRight, dw3);
            QVERIFY(!da.containsDockWidget(dw2));
        }

        delete dw1;
        delete dw2;
        delete dw3;
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    QTest::qWait(1);
}

#define KDDW_TEST_NAME TestDropArea
#include "../test_main_qt.h"

#include "tst_droparea.moc"
