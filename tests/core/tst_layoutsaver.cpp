/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../utils.h"
#include "core/DockWidget.h"
#include "../utils.h"
#include "LayoutSaver.h"
#include "Config.h"
#include "core/DockWidget.h"
#include "core/FloatingWindow.h"
#include "core/MainWindow.h"
#include "core/Platform.h"

#include <QDir>
#include <QTest>
#include <QTemporaryDir>

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

class TestLayoutSaver : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void tst_fileErrors();
    void tst_invalidData();
    void tst_unknownMainWindow();
    void tst_scopeArguments();
    void tst_dockWidgetsInLayout();
    void tst_malformedLayouts_data();
    void tst_malformedLayouts();
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void tst_userData();
#endif
};

void TestLayoutSaver::initTestCase()
{
    // So qWarning()s are recorded in m_toleratedWarnings too, which is how errors are reported
    // when built without spdlog
    Platform::instance()->installMessageHandler();
}

void TestLayoutSaver::cleanupTestCase()
{
    Platform::instance()->uninstallMessageHandler();
}

void TestLayoutSaver::tst_fileErrors()
{
    Tests::EnsureTopLevelsDeleted e;
    auto m = Tests::createMainWindow(Size(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");
    auto dw1 = Tests::createDockWidget("dw1");
    m->addDockWidget(dw1, Location_OnLeft);

    LayoutSaver saver;
    {
        SetExpectedWarning sew("Failed to open");
        QVERIFY(!saver.saveToFile("/this/folder/doesnt/exist/layout.json"));
    }

    {
        SetExpectedWarning sew("Failed to open");
        QVERIFY(!saver.restoreFromFile("/this/file/doesnt/exist.json"));
    }

    {
        SetExpectedWarning sew("Failed to open");
        QVERIFY(LayoutSaver::openedDockWidgetsInLayout(QString("/this/file/doesnt/exist.json")).isEmpty());
    }

    {
        SetExpectedWarning sew("Failed to open");
        QVERIFY(LayoutSaver::sideBarDockWidgetsInLayout(QString("/this/file/doesnt/exist.json")).isEmpty());
    }

    // And the happy path
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString fileName = dir.filePath("layout.json");
    QVERIFY(saver.saveToFile(fileName));
    QVERIFY(saver.restoreFromFile(fileName));
    QCOMPARE(LayoutSaver::openedDockWidgetsInLayout(fileName), Vector<QString>({ "dw1" }));
    QVERIFY(LayoutSaver::sideBarDockWidgetsInLayout(fileName).isEmpty());

    delete dw1;
}

void TestLayoutSaver::tst_invalidData()
{
    Tests::EnsureTopLevelsDeleted e;
    LayoutSaver saver;

    // Empty data is a no-op
    QVERIFY(saver.restoreLayout(QByteArray()));

    {
        SetExpectedWarning sew("Failed to parse json data");
        QVERIFY(!saver.restoreLayout("this is not json"));
    }

    QVERIFY(LayoutSaver::openedDockWidgetsInLayout(QByteArray("this is not json")).isEmpty());
    QVERIFY(LayoutSaver::sideBarDockWidgetsInLayout(QByteArray("this is not json")).isEmpty());
}

void TestLayoutSaver::tst_unknownMainWindow()
{
    Tests::EnsureTopLevelsDeleted e;

    QByteArray serialized;
    {
        auto m = Tests::createMainWindow(Size(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");
        auto dw1 = Tests::createDockWidget("dw1");
        m->addDockWidget(dw1, Location_OnLeft);
        serialized = LayoutSaver().serializeLayout();
        QVERIFY(!serialized.isEmpty());
        delete dw1;
    }

    // The main window doesn't exist anymore and there's no factory to create it
    SetExpectedWarning sew("Failed to restore layout create MainWindow");
    QVERIFY(!LayoutSaver().restoreLayout(serialized));
}

void TestLayoutSaver::tst_scopeArguments()
{
    Tests::EnsureTopLevelsDeleted e;
    auto m = Tests::createMainWindow(Size(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");
    auto dw1 = Tests::createDockWidget("dw1");
    auto dw2 = Tests::createDockWidget("dw2");
    auto dw3 = Tests::createDockWidget("dw3");
    m->addDockWidget(dw1, Location_OnLeft);
    dw2->open();
    QVERIFY(dw2->floatingWindow());

    LayoutSaver saver;
    {
        SetExpectedWarning sew("null main window");
        saver.addWindowToSave(static_cast<Core::MainWindow *>(nullptr));
    }
    {
        SetExpectedWarning sew("empty name");
        saver.addMainWindowToSave(QString());
    }
    {
        SetExpectedWarning sew("null floating window");
        saver.addWindowToSave(static_cast<Core::FloatingWindow *>(nullptr));
    }
    {
        SetExpectedWarning sew("null dock widget");
        saver.addWindowToSave(static_cast<Core::DockWidget *>(nullptr));
    }
    {
        // dw3 was never opened, it's in no window
        SetExpectedWarning sew("is in no window");
        saver.addWindowToSave(dw3);
    }

    // Save only the main window
    saver.addWindowToSave(dw1);
    saver.addMainWindowToSave("mw1");
    const QByteArray onlyMainWindow = saver.serializeLayout();
    QVERIFY(!onlyMainWindow.isEmpty());

    // Save only the floating window
    saver.clearWindowsToSave();
    saver.addWindowToSave(dw2);
    saver.addWindowToSave(dw2->floatingWindow());
    const QByteArray onlyFloating = saver.serializeLayout();
    QVERIFY(!onlyFloating.isEmpty());
    QVERIFY(onlyFloating != onlyMainWindow);

    QVERIFY(saver.restoreLayout(onlyFloating));
    QVERIFY(saver.restoreLayout(onlyMainWindow));

    saver.clearWindowsToSave();
    QVERIFY(saver.restoreLayout(saver.serializeLayout()));

    delete dw1;
    delete dw2;
    delete dw3;
}

void TestLayoutSaver::tst_dockWidgetsInLayout()
{
    Tests::EnsureTopLevelsDeleted e;
    auto m = Tests::createMainWindow(Size(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");
    auto dw1 = Tests::createDockWidget("dw1");
    auto dw2 = Tests::createDockWidget("dw2");
    m->addDockWidget(dw1, Location_OnLeft);
    m->addDockWidget(dw2, Location_OnRight);

    // Closing leaves a placeholder behind, which is saved too
    dw2->close();

    LayoutSaver saver;
    const QByteArray serialized = saver.serializeLayout();
    QCOMPARE(LayoutSaver::openedDockWidgetsInLayout(serialized), Vector<QString>({ "dw1" }));
    QVERIFY(LayoutSaver::sideBarDockWidgetsInLayout(serialized).isEmpty());

    dw2->open();
    QVERIFY(saver.restoreLayout(serialized));
    QVERIFY(!dw2->isOpen());
    QVERIFY(dw1->isOpen());

    delete dw1;
    delete dw2;
}

void TestLayoutSaver::tst_malformedLayouts_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QString>("expectedError"); // Empty if it's expected to restore

    // The layout tst_malformedLayouts() creates. All the malformed ones are corrupted versions of it.
    QTest::newRow("valid") << QStringLiteral(KDDW_SRC_DIR "/tests/layouts/malformedLayoutsBase.json") << QString();

    // What each malformed file is expected to complain about, so we know it's rejected for the
    // right reason
    const std::map<QString, QString> expectedErrors = {
        { QStringLiteral("binary_garbage.json"), QStringLiteral("Failed to parse json data") },
        { QStringLiteral("central_group_in_floating_window.json"), QStringLiteral("Unexpected central group for main window mw2") },
        { QStringLiteral("central_group_of_other_main_window.json"), QStringLiteral("Unexpected central group for main window mw2") },
        { QStringLiteral("container_children_overflow.json"), QStringLiteral("Invalid layout: Children don't fit in their container") },
        { QStringLiteral("container_empty.json"), QStringLiteral("Invalid layout: Empty container") },
        { QStringLiteral("container_invalid_orientation.json"), QStringLiteral("Invalid layout: Invalid orientation") },
        { QStringLiteral("container_marked_as_leaf.json"), QStringLiteral("Invalid layout: Some groups aren't in the layout") },
        { QStringLiteral("container_with_guest.json"), QStringLiteral("Invalid layout: Container with guest") },
        { QStringLiteral("container_without_size.json"), QStringLiteral("Invalid layout: Visible container without size") },
        { QStringLiteral("deep_nesting_json.json"), QStringLiteral("JSON is too deep") },
        { QStringLiteral("deep_nesting_layout.json"), QStringLiteral("Invalid layout: Too much nesting") },
        { QStringLiteral("dockwidget_in_main_and_floating_window.json"), QStringLiteral("Dock widget dw1 appears more than once") },
        { QStringLiteral("dockwidget_in_sidebar_and_group.json"), QStringLiteral("Dock widget dw1 appears more than once") },
        { QStringLiteral("dockwidget_in_two_groups.json"), QStringLiteral("Dock widget dw1 appears more than once") },
        { QStringLiteral("dockwidget_twice_in_group.json"), QStringLiteral("Dock widget dw1 appears more than once") },
        { QStringLiteral("dockwidget_twice_in_sidebar.json"), QStringLiteral("Dock widget dw3 appears more than once") },
        { QStringLiteral("floatingwindow_flags_huge_double.json"), QStringLiteral("Number out of range") },
        { QStringLiteral("floatingwindow_geometry_int_max.json"), QStringLiteral("Integer out of range") },
        { QStringLiteral("frames_not_an_object.json"), QStringLiteral("Expected frames to be an object") },
        { QStringLiteral("frames_null.json"), QStringLiteral("Invalid layout: Unknown group") },
        { QStringLiteral("group_duplicate_id.json"), QStringLiteral("Invalid layout: Duplicate group id") },
        { QStringLiteral("group_id_differs_from_key.json"), QStringLiteral("Invalid layout: Unknown group") },
        { QStringLiteral("group_not_in_layout.json"), QStringLiteral("Invalid layout: Some groups aren't in the layout") },
        { QStringLiteral("group_referenced_twice.json"), QStringLiteral("is referenced more than once") },
        { QStringLiteral("group_unknown.json"), QStringLiteral("Invalid layout: Unknown group") },
        { QStringLiteral("group_without_geometry.json"), QStringLiteral("Invalid geometry") },
        { QStringLiteral("item_children_not_an_array.json"), QStringLiteral("Invalid layout: Expected children to be an array") },
        { QStringLiteral("item_geometry_int_max.json"), QStringLiteral("Invalid layout: Invalid sizingInfo") },
        { QStringLiteral("item_geometry_width_huge_double.json"), QStringLiteral("Invalid layout: Invalid sizingInfo") },
        { QStringLiteral("item_geometry_width_not_a_number.json"), QStringLiteral("Invalid layout: Invalid sizingInfo") },
        { QStringLiteral("item_guestId_not_a_string.json"), QStringLiteral("Invalid layout: Expected guestId to be a string") },
        { QStringLiteral("item_guest_on_invisible_item.json"), QStringLiteral("Invalid layout: Only visible items have a guest") },
        { QStringLiteral("item_isContainer_not_a_bool.json"), QStringLiteral("Invalid layout: Expected a boolean") },
        { QStringLiteral("item_isVisible_null.json"), QStringLiteral("Invalid layout: Expected a boolean") },
        { QStringLiteral("item_leaf_with_guest_marked_as_container.json"), QStringLiteral("Invalid layout: Container with guest") },
        { QStringLiteral("item_maxSizeHint_not_a_number.json"), QStringLiteral("Invalid layout: Invalid sizingInfo") },
        { QStringLiteral("item_minSize_not_a_number.json"), QStringLiteral("Invalid layout: Invalid sizingInfo") },
        { QStringLiteral("item_not_an_object.json"), QStringLiteral("Invalid layout: Item is not an object") },
        { QStringLiteral("item_percentage_not_a_number.json"), QStringLiteral("Invalid layout: Invalid sizingInfo") },
        { QStringLiteral("item_sizingInfo_not_an_object.json"), QStringLiteral("Invalid layout: Invalid sizingInfo") },
        { QStringLiteral("item_visible_placeholder.json"), QStringLiteral("Invalid layout: Only visible items have a guest") },
        { QStringLiteral("lastCloseReason_huge_double.json"), QStringLiteral("Number out of range") },
        { QStringLiteral("lastOverlayedGeometries_location_huge_double.json"), QStringLiteral("Number out of range") },
        { QStringLiteral("layout_not_a_layout.json"), QStringLiteral("Invalid layout: Container without orientation") },
        { QStringLiteral("mainWindows_not_an_array.json"), QStringLiteral("type must be array") },
        { QStringLiteral("mainwindow_geometry_huge_double.json"), QStringLiteral("Number out of range") },
        { QStringLiteral("mainwindow_geometry_int_max.json"), QStringLiteral("Integer out of range") },
        { QStringLiteral("mainwindow_screenIndex_huge_double.json"), QStringLiteral("Number out of range") },
        { QStringLiteral("mainwindow_twice.json"), QStringLiteral("Main window mw1 appears more than once") },
        { QStringLiteral("mainwindow_unknown.json"), QStringLiteral("Failed to restore layout create MainWindow") },
        { QStringLiteral("persistent_central_name_in_normal_groups.json"), QStringLiteral("Dock widget -persistentCentralDockWidget appears more than once") },
        { QStringLiteral("placeholder_itemIndex_huge_double.json"), QStringLiteral("Number out of range") },
        { QStringLiteral("position_tabIndex_huge_double.json"), QStringLiteral("Number out of range") },
        { QStringLiteral("root_is_an_array.json"), QStringLiteral("cannot use value() with array") },
        { QStringLiteral("root_with_guest.json"), QStringLiteral("Invalid layout: Container with guest") },
        { QStringLiteral("serializationVersion_not_a_number.json"), QStringLiteral("type must be number") },
        { QStringLiteral("truncated.json"), QStringLiteral("Failed to parse json data") },
    };

    const QDir dir(QStringLiteral(KDDW_SRC_DIR "/tests/layouts/malformed/"));
    const QStringList files = dir.entryList({ QStringLiteral("*.json") }, QDir::Files, QDir::Name);
    QCOMPARE(size_t(files.size()), expectedErrors.size());

    for (const QString &file : files) {
        const auto it = expectedErrors.find(file);
        QVERIFY2(it != expectedErrors.cend(), qPrintable(QStringLiteral("No expected error for ") + file));
        QTest::newRow(qPrintable(file)) << dir.filePath(file) << it->second;
    }
}

void TestLayoutSaver::tst_malformedLayouts()
{
    QFETCH(QString, fileName);
    QFETCH(QString, expectedError);

    Tests::EnsureTopLevelsDeleted e;
    auto m1 = Tests::createMainWindow(Size(1000, 1000), MainWindowOption_None, "mw1");
    auto m2 = Tests::createMainWindow(Size(800, 800), MainWindowOption_HasCentralGroup, "mw2");

    // Deleted even if we fail half-way, so the next row starts clean
    std::vector<std::unique_ptr<Core::DockWidget>> docks;
    for (int i = 1; i <= 7; ++i)
        docks.emplace_back(Tests::createDockWidget(QStringLiteral("dw%1").arg(i)));
    auto dw = [&docks](int i) { return docks[i - 1].get(); };

    m1->addDockWidget(dw(1), Location_OnLeft);
    dw(1)->addDockWidgetAsTab(dw(2));
    m1->addDockWidget(dw(3), Location_OnRight);
    m1->addDockWidget(dw(4), Location_OnBottom);
    dw(4)->close(); // leaves a placeholder behind
    dw(5)->open();
    dw(5)->addDockWidgetAsTab(dw(6));
    m2->addDockWidgetAsTab(dw(7)); // into the persistent central group

    if (qEnvironmentVariableIsSet("KDDW_DUMP_LAYOUT")) {
        // To create more malformed files, dump the layout with this and corrupt it
        QVERIFY(LayoutSaver().saveToFile(qEnvironmentVariable("KDDW_DUMP_LAYOUT")));
        return;
    }

    for (RestoreOptions options : { RestoreOptions(RestoreOption_None), RestoreOptions(RestoreOption_RelativeToMainWindow) }) {
        if (expectedError.isEmpty()) {
            QVERIFY(LayoutSaver(options).restoreFromFile(fileName));
            continue;
        }

        // Besides the expected error, it might complain about other things too
        SetExpectedWarning sew(Core::Platform::AnyWarning);
        QVERIFY(!LayoutSaver(options).restoreFromFile(fileName));

        const std::vector<std::string> &warnings = Platform::instance()->m_toleratedWarnings;
#ifdef KDDW_HAS_SPDLOG
        const bool found = std::any_of(warnings.cbegin(), warnings.cend(), [&expectedError](const std::string &w) {
            return QString::fromStdString(w).contains(expectedError);
        });
#else
        // Without spdlog the errors are printed unformatted ("{}" isn't replaced), so just check there was one
        const bool found = !warnings.empty();
#endif

        QString allWarnings;
        for (const std::string &w : warnings)
            allWarnings += QString::fromStdString(w) + QLatin1Char('\n');
        QVERIFY2(found, qPrintable(QStringLiteral("Expected \"%1\", got:\n%2").arg(expectedError, allWarnings)));
    }

    {
        SetExpectedWarning sew(Core::Platform::AnyWarning);
        LayoutSaver::openedDockWidgetsInLayout(fileName);
        LayoutSaver::sideBarDockWidgetsInLayout(fileName);
    }

    // Nothing was left in a bad state
    LayoutSaver saver;
    QVERIFY(saver.restoreLayout(saver.serializeLayout()));
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
void TestLayoutSaver::tst_userData()
{
    Tests::EnsureTopLevelsDeleted e;
    auto m = Tests::createMainWindow(Size(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");
    auto dw1 = Tests::createDockWidget("dw1");
    auto dw2 = Tests::createDockWidget("dw2");
    m->addDockWidget(dw1, Location_OnLeft);
    m->addDockWidget(dw2, Location_OnRight);

    QVariantMap userData;
    userData["string"] = QStringLiteral("hello");
    userData["bool"] = true;
    userData["int"] = 42;
    userData["double"] = 3.5;
    userData["stringList"] = QStringList({ "a", "b" });
    userData["map"] = QVariantMap({ { "nested", 1 }, { "nestedString", "x" } });
    userData["list"] = QVariantList({ 1, "two", false });
    userData["null"] = QVariant();
    dw1->setUserData(userData);

    LayoutSaver saver;
    const QByteArray serialized = saver.serializeLayout();

    dw1->setUserData({});
    QVERIFY(dw1->userData().isEmpty());
    QVERIFY(saver.restoreLayout(serialized));

    const QVariantMap restored = dw1->userData();
    QCOMPARE(restored.size(), userData.size());
    QCOMPARE(restored["string"].toString(), QString("hello"));
    QCOMPARE(restored["bool"].typeId(), QMetaType::Bool);
    QVERIFY(restored["bool"].toBool());
    QCOMPARE(restored["int"].typeId(), QMetaType::Int);
    QCOMPARE(restored["int"].toInt(), 42);
    QCOMPARE(restored["double"].typeId(), QMetaType::Double);
    QCOMPARE(restored["double"].toDouble(), 3.5);
    // A QStringList is saved as a JSON array, so it comes back as a QVariantList
    QCOMPARE(restored["stringList"].toStringList(), QStringList({ "a", "b" }));
    QCOMPARE(restored["map"].toMap().size(), 2);
    QCOMPARE(restored["map"].toMap()["nested"].toInt(), 1);
    QCOMPARE(restored["map"].toMap()["nestedString"].toString(), QString("x"));
    const QVariantList list = restored["list"].toList();
    QCOMPARE(list.size(), 3);
    QCOMPARE(list[0].toInt(), 1);
    QCOMPARE(list[1].toString(), QString("two"));
    QCOMPARE(list[2].typeId(), QMetaType::Bool);
    QVERIFY(restored.contains("null"));
    QVERIFY(restored["null"].isNull());

    // No user data means nothing is saved, and nothing is restored
    QVERIFY(dw2->userData().isEmpty());

    delete dw1;
    delete dw2;
}
#endif

#define KDDW_TEST_NAME TestLayoutSaver
#include "../test_main_qt.h"

#include "tst_layoutsaver.moc"
