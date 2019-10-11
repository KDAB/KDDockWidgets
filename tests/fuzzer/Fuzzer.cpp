/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

#include "Fuzzer.h"
#include "DockRegistry_p.h"
#include "DockWidget.h"
#include "MainWindow.h"

#include <QJsonDocument>

#include <QString>
#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Testing;
using namespace KDDockWidgets::Testing::Operations;

#define OPERATIONS_PER_TEST 200

static MainWindow* createMainWindow(const Fuzzer::MainWindowDescriptor &mwd)
{
    static int count = 0;
    count++;
    auto mainWindow = new MainWindow(QStringLiteral("MainWindow-%1").arg(count), mwd.mainWindowOption);

    mainWindow->setGeometry(mwd.geometry);

    mainWindow->show();
    return mainWindow;
}

static DockWidget* createDockWidget(const Fuzzer::DockWidgetDescriptor &dwd)
{
    static int count = 0;
    count++;
    auto dockWidget = new DockWidget(QStringLiteral("DockWidget-%1").arg(count));

    dockWidget->setWidget(new Testing::HostedWidget(dwd.minSize));

    if (dwd.isFloating)
        dockWidget->setGeometry(dwd.geometry);

    if (dwd.isVisible)
        dockWidget->show();

    return dockWidget;
}

static void createLayout(const Fuzzer::Layout &layout)
{
    for (const Fuzzer::MainWindowDescriptor &mwd : layout.mainWindows) {
        createMainWindow(mwd);
    }

    for (const Fuzzer::DockWidgetDescriptor &dwd : layout.dockWidgets) {
        createDockWidget(dwd);
    }
}

void Fuzzer::runTest(const Test &test)
{
    m_currentTest = test;

    if (!DockRegistry::self()->isEmpty())
        qFatal("There's dock widgets and the start runTest");

    createLayout(test.initialLayout);
    for (const auto &op : test.operations) {
        op->execute();
        //QTest::qWait(1000);
    }

    for (MainWindowBase *mw : DockRegistry::self()->mainwindows())
        delete mw;

    for (FloatingWindow *fw : DockRegistry::self()->nestedwindows())
        delete fw;

    for (DockWidgetBase *dw : DockRegistry::self()->dockwidgets())
        delete dw;

    if (!DockRegistry::self()->isEmpty())
        qFatal("There's still dock widgets and the end of runTest");
}

Fuzzer::Fuzzer(Fuzzer::FuzzerConfig config, QObject *parent)
    : QObject(parent)
    , m_randomEngine(m_randomDevice())
    , m_fuzzerConfig(config)
{
    Testing::installFatalMessageHandler();
    Testing::setWarningObserver(this);
}

Fuzzer::Layout Fuzzer::generateRandomLayout()
{
    // for now we only support 1 main window
    Fuzzer::Layout layout;
    Fuzzer::MainWindowDescriptor mainWindow;
    mainWindow.geometry = randomGeometry();
    mainWindow.mainWindowOption = MainWindowOption_None; // TODO: Maybe test other options
    layout.mainWindows << mainWindow;

    std::uniform_int_distribution<> numDocksDistrib(1, 10); // TODO: Increase
    const int numDockWidgets = numDocksDistrib(m_randomEngine);
    for (int i = 0; i < numDockWidgets; ++i) {
        layout.dockWidgets << generateRandomDockWidget();
    }

    return layout;
}

Fuzzer::DockWidgetDescriptor Fuzzer::generateRandomDockWidget()
{
    Fuzzer::DockWidgetDescriptor dwd;

    dwd.isFloating = getRandomBool(35);
    dwd.isVisible = getRandomBool(70);

    std::uniform_int_distribution<> minSizeDistriv(150, 600);

    dwd.minSize.setWidth(minSizeDistriv(m_randomEngine));
    dwd.minSize.setHeight(minSizeDistriv(m_randomEngine));

    QPoint pos = getRandomPos();
    std::uniform_int_distribution<> widthDistrib(dwd.minSize.width() + 50, dwd.minSize.width() + 600);
    std::uniform_int_distribution<> heightDistrib(dwd.minSize.height() + 50, dwd.minSize.height() + 600);
    dwd.geometry = QRect(pos, QSize(widthDistrib(m_randomEngine), heightDistrib(m_randomEngine)));

    return dwd;
}

Fuzzer::DockWidgetDescriptor::List Fuzzer::generateRandomDockWidgets(int num)
{
    Fuzzer::DockWidgetDescriptor::List dockWidgets;
    for (int i = 0; i < num; ++i) {
        dockWidgets << generateRandomDockWidget();
    }
    return dockWidgets;
}

bool Fuzzer::getRandomBool(int truePercentage)
{
    std::uniform_int_distribution<> distrib(1, 100);
    return distrib(m_randomEngine) < truePercentage;
}

Fuzzer::AddDockWidgetParams Fuzzer::getRandomAddDockWidgetParams()
{
    AddDockWidgetParams params;

    params.dockWidget = getRandomDockWidget();
    if (!params.dockWidget) {
        qWarning() << Q_FUNC_INFO << "No dock widgets exist yet!";
        return {};
    }

    params.mainWindow = getRandomMainWindow();
    params.relativeTo = getRandomBool() ? getRandomRelativeTo(params.mainWindow, params.dockWidget)
                                        : nullptr;
    params.location = getRandomLocation();
    params.addingOption = AddingOption_None; // TODO: Test the other ones

    return params;
}

MainWindowBase *Fuzzer::getRandomMainWindow()
{
    auto windows = DockRegistry::self()->mainwindows();
    if (windows.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "No MainWindows exist yet!";
        return nullptr;
    }

    return windows.first();
}

DockWidgetBase *Fuzzer::getRandomDockWidget(DockWidgetBase *excluding)
{
    auto docks = DockRegistry::self()->dockwidgets();

    if (excluding)
        docks.removeOne(excluding);

    if (docks.isEmpty())
        return nullptr;

    std::uniform_int_distribution<> locationDistrib(0, docks.size() - 1);
    return docks[locationDistrib(m_randomEngine)];
}

DockWidgetBase *Fuzzer::getRandomRelativeTo(MainWindowBase *mainWindow, DockWidgetBase *excluding)
{
    auto docks = DockRegistry::self()->dockwidgets();

    DockWidgetBase::List candidates;

    for (DockWidgetBase *dw : docks)  {
        if (dw != excluding && dw->window() == mainWindow)
            candidates << dw;
    }

    if (candidates.isEmpty())
        return nullptr;

    std::uniform_int_distribution<> locationDistrib(0, candidates.size() - 1);
    return candidates[locationDistrib(m_randomEngine)];
}

Location Fuzzer::getRandomLocation()
{
    std::uniform_int_distribution<> locationDistrib(1, 4);
    return Location(locationDistrib(m_randomEngine));
}

QPoint Fuzzer::getRandomPos()
{
    std::uniform_int_distribution<> posDistrib(0, 500);
    const int x = posDistrib(m_randomEngine);
    const int y = posDistrib(m_randomEngine);
    return {x, y};
}

OperationBase::Ptr Fuzzer::getRandomOperation()
{
    Testing::Operations::OperationBase::Ptr operation;

    std::uniform_int_distribution<> operationDistrib(OperationType_None + 1, OperationType_Count - 1);
    auto operationType = OperationType(operationDistrib(m_randomEngine));

    switch (operationType) {
    case OperationType_CloseViaDockWidgetAPI:
        operation = OperationBase::Ptr(new CloseViaDockWidgetAPI(this));
        break;
    case OperationType_HideViaDockWidgetAPI:
        operation = OperationBase::Ptr(new HideViaDockWidgetAPI(this));
        break;
    case OperationType_ShowViaDockWidgetAPI:
        operation = OperationBase::Ptr(new ShowViaDockWidgetAPI(this));
        break;
    case OperationType_AddDockWidget:
        operation = OperationBase::Ptr(new AddDockWidget(this));
        break;
    default:
        qFatal("Doesn't happen");
    }

    return operation;
}

Fuzzer::Test Fuzzer::generateRandomTest()
{
    Fuzzer::Test test;
    test.initialLayout = generateRandomLayout();

    const int numOperationsPerTest = OPERATIONS_PER_TEST;
    test.operations.reserve(numOperationsPerTest);
    for (int i = 0; i < numOperationsPerTest; ++i)
        test.operations << getRandomOperation();

    return test;
}

Fuzzer::Test::List Fuzzer::generateRandomTests(int num)
{
    Fuzzer::Test::List tests;

    for (int i = 0; i < num; ++i) {
        tests << generateRandomTest();
    }

    return tests;
}

void Fuzzer::fuzz()
{
    const Fuzzer::Test::List tests = generateRandomTests(m_fuzzerConfig.numTests);
    qDebug().noquote() << "Running" << QString("%1 tests...").arg(tests.size());

    for (const auto &test : tests) {
        runTest(test);
    }
}

QRect Fuzzer::randomGeometry()
{
    std::uniform_int_distribution<> posDistrib(0, 500);
    std::uniform_int_distribution<> sizeDistrib(700, 1500);
    const int width = posDistrib(m_randomEngine);
    const int height = sizeDistrib(m_randomEngine);

    QPoint pos = getRandomPos();

    return QRect(pos, QSize(width, height));
}

void Fuzzer::onFatal()
{
    // Tests failed! Let's dump
    QVariantMap map = m_currentTest.toVariantMap();
    QJsonDocument jsonDoc = QJsonDocument::fromVariant(map);
    QFile file("fuzzer_dump.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDoc.toJson());
    }
    file.close();
}
