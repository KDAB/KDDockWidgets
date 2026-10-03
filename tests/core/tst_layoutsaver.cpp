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

#define KDDW_TEST_NAME TestLayoutSaver
#include "../test_main_qt.h"

#include "tst_layoutsaver.moc"
