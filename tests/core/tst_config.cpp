/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../utils.h"
#include "core/DockWidget.h"
#include "core/ViewFactory.h"
#include "Config.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

namespace {

bool dropIndicatorAllowed(DropLocation, const Vector<Core::DockWidget *> &, const Vector<Core::DockWidget *> &,
                          Core::DropArea *)
{
    return false;
}

bool dragAboutToStart(Core::Draggable *)
{
    return false;
}

void dragEnded()
{
}

int tabIndexOverride(Core::DockWidget *, Core::Group *, int tabIndex)
{
    return tabIndex;
}

}

class TestConfig : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_layoutSpacing();
    void tst_separatorThickness();
    void tst_invalidSpacingIsRejected();
    void tst_startupOnlySettersAreRejectedWhenDockWidgetsExist();
    void tst_absoluteSizes();
    void tst_draggedWindowOpacity();
    void tst_transparencyOnlyOverDropIndicator();
    void tst_tabsAtBottom();
    void tst_disabledPaintEvents();
    void tst_mdiPopupThreshold();
    void tst_startDragDistance();
    void tst_dropIndicatorsInhibited();
    void tst_callbacks();
    void tst_printDebug();
};

void TestConfig::tst_layoutSpacing()
{
    auto &config = Config::self();
    const int originalSpacing = config.layoutSpacing();
    const int originalThickness = config.separatorThickness();

    config.setLayoutSpacing(7);
    QCOMPARE(config.layoutSpacing(), 7);
    QCOMPARE(config.separatorThickness(), originalThickness); // Only the spacing changed

    config.setLayoutSpacing(originalSpacing);
    QCOMPARE(config.layoutSpacing(), originalSpacing);
}

void TestConfig::tst_separatorThickness()
{
    auto &config = Config::self();
    const int originalSpacing = config.layoutSpacing();
    const int originalThickness = config.separatorThickness();

    // The thickness also sets the spacing
    config.setSeparatorThickness(9);
    QCOMPARE(config.separatorThickness(), 9);
    QCOMPARE(config.layoutSpacing(), 9);

    config.setSeparatorThickness(originalThickness);
    config.setLayoutSpacing(originalSpacing);
    QCOMPARE(config.separatorThickness(), originalThickness);
    QCOMPARE(config.layoutSpacing(), originalSpacing);
}

void TestConfig::tst_invalidSpacingIsRejected()
{
    auto &config = Config::self();
    const int originalSpacing = config.layoutSpacing();
    const int originalThickness = config.separatorThickness();

    config.setLayoutSpacing(-1);
    config.setLayoutSpacing(100);
    QCOMPARE(config.layoutSpacing(), originalSpacing);

    config.setSeparatorThickness(-1);
    config.setSeparatorThickness(100);
    QCOMPARE(config.separatorThickness(), originalThickness);
    QCOMPARE(config.layoutSpacing(), originalSpacing);
}

void TestConfig::tst_startupOnlySettersAreRejectedWhenDockWidgetsExist()
{
    Tests::EnsureTopLevelsDeleted e;

    auto &config = Config::self();
    const int originalSpacing = config.layoutSpacing();
    const int originalThickness = config.separatorThickness();
    const Size originalMin = config.absoluteWidgetMinSize();
    const Size originalMax = config.absoluteWidgetMaxSize();

    auto dw = config.viewFactory()->createDockWidget("dw1")->asDockWidgetController();

    config.setLayoutSpacing(originalSpacing + 1);
    config.setSeparatorThickness(originalThickness + 1);
    config.setAbsoluteWidgetMinSize(Size(originalMin.width() + 1, originalMin.height() + 1));
    config.setAbsoluteWidgetMaxSize(Size(originalMax.width() - 1, originalMax.height() - 1));

    QCOMPARE(config.layoutSpacing(), originalSpacing);
    QCOMPARE(config.separatorThickness(), originalThickness);
    QCOMPARE(config.absoluteWidgetMinSize(), originalMin);
    QCOMPARE(config.absoluteWidgetMaxSize(), originalMax);

    delete dw;
}

void TestConfig::tst_absoluteSizes()
{
    auto &config = Config::self();
    const Size originalMin = config.absoluteWidgetMinSize();
    const Size originalMax = config.absoluteWidgetMaxSize();

    config.setAbsoluteWidgetMinSize(Size(123, 45));
    config.setAbsoluteWidgetMaxSize(Size(6789, 1011));
    QCOMPARE(config.absoluteWidgetMinSize(), Size(123, 45));
    QCOMPARE(config.absoluteWidgetMaxSize(), Size(6789, 1011));

    config.setAbsoluteWidgetMinSize(originalMin);
    config.setAbsoluteWidgetMaxSize(originalMax);
    QCOMPARE(config.absoluteWidgetMinSize(), originalMin);
    QCOMPARE(config.absoluteWidgetMaxSize(), originalMax);
}

void TestConfig::tst_draggedWindowOpacity()
{
    auto &config = Config::self();
    const double original = config.draggedWindowOpacity();

    config.setDraggedWindowOpacity(0.25);
    QCOMPARE(config.draggedWindowOpacity(), 0.25);

    config.setDraggedWindowOpacity(original);
}

void TestConfig::tst_transparencyOnlyOverDropIndicator()
{
    auto &config = Config::self();
    const bool original = config.transparencyOnlyOverDropIndicator();

    config.setTransparencyOnlyOverDropIndicator(!original);
    QCOMPARE(config.transparencyOnlyOverDropIndicator(), !original);

    config.setTransparencyOnlyOverDropIndicator(original);
    QCOMPARE(config.transparencyOnlyOverDropIndicator(), original);
}

void TestConfig::tst_tabsAtBottom()
{
    auto &config = Config::self();
    const bool original = config.tabsAtBottom();

    config.setTabsAtBottom(!original);
    QCOMPARE(config.tabsAtBottom(), !original);

    config.setTabsAtBottom(original);
    QCOMPARE(config.tabsAtBottom(), original);
}

void TestConfig::tst_disabledPaintEvents()
{
    auto &config = Config::self();
    const auto original = config.disabledPaintEvents();

    const Config::CustomizableWidgets widgets = Config::CustomizableWidgets(Config::CustomizableWidget_TitleBar)
        | Config::CustomizableWidget_Separator;
    config.setDisabledPaintEvents(widgets);
    QCOMPARE(config.disabledPaintEvents(), widgets);

    config.setDisabledPaintEvents(original);
    QCOMPARE(config.disabledPaintEvents(), original);
}

void TestConfig::tst_mdiPopupThreshold()
{
    auto &config = Config::self();
    const int original = config.mdiPopupThreshold();

    config.setMDIPopupThreshold(original + 10);
    QCOMPARE(config.mdiPopupThreshold(), original + 10);

    config.setMDIPopupThreshold(original);
    QCOMPARE(config.mdiPopupThreshold(), original);
}

void TestConfig::tst_startDragDistance()
{
    auto &config = Config::self();
    const int original = config.startDragDistance();

    config.setStartDragDistance(original + 3);
    QCOMPARE(config.startDragDistance(), original + 3);

    config.setStartDragDistance(original);
    QCOMPARE(config.startDragDistance(), original);
}

void TestConfig::tst_dropIndicatorsInhibited()
{
    auto &config = Config::self();
    const bool original = config.dropIndicatorsInhibited();

    config.setDropIndicatorsInhibited(!original);
    QCOMPARE(config.dropIndicatorsInhibited(), !original);

    // Setting the same value again is a no-op
    config.setDropIndicatorsInhibited(!original);
    QCOMPARE(config.dropIndicatorsInhibited(), !original);

    config.setDropIndicatorsInhibited(original);
    QCOMPARE(config.dropIndicatorsInhibited(), original);
}

void TestConfig::tst_callbacks()
{
    auto &config = Config::self();
    const auto originalAllowed = config.dropIndicatorAllowedFunc();
    const auto originalAboutToStart = config.dragAboutToStartFunc();
    const auto originalEnded = config.dragEndedFunc();
    const auto originalTabIndex = config.dockWidgetTabIndexOverrideFunc();

    config.setDropIndicatorAllowedFunc(dropIndicatorAllowed);
    config.setDragAboutToStartFunc(dragAboutToStart);
    config.setDragEndedFunc(dragEnded);
    config.setDockWidgetTabIndexOverrideFunc(tabIndexOverride);

    QVERIFY(config.dropIndicatorAllowedFunc() == &dropIndicatorAllowed);
    QVERIFY(config.dragAboutToStartFunc() == &dragAboutToStart);
    QVERIFY(config.dragEndedFunc() == &dragEnded);
    QVERIFY(config.dockWidgetTabIndexOverrideFunc() == &tabIndexOverride);

    config.setDropIndicatorAllowedFunc(originalAllowed);
    config.setDragAboutToStartFunc(originalAboutToStart);
    config.setDragEndedFunc(originalEnded);
    config.setDockWidgetTabIndexOverrideFunc(originalTabIndex);
}

void TestConfig::tst_printDebug()
{
    // Just a smoke test, it prints the flags to stderr
    Config::self().printDebug();
}

#define KDDW_TEST_NAME TestConfig
#include "../test_main_qt.h"

#include "tst_config.moc"
