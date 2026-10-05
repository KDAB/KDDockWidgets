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

#include <QTest>
#include <QTemporaryDir>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

class TestLayoutSaver : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_fileErrors();
    void tst_invalidData();
    void tst_unknownMainWindow();
    void tst_scopeArguments();
    void tst_dockWidgetsInLayout();
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void tst_userData();
#endif
};

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

    dw1->setUserData({ });
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
