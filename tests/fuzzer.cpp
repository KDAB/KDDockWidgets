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

#include "Testing.h"

#include <QApplication>
#include <QTimer>
#include <QDebug>

#include <random>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Testing;

#define OPERATIONS_PER_TEST 200

class Fuzzer : public QObject
{
    Q_OBJECT
public:

    struct FuzzerConfig
    {
        int numTests;
        int numOperationsPerTest;
        bool singleMainWindow;
    };

    Fuzzer(FuzzerConfig config, QObject *parent = nullptr)
        : QObject(parent)
        , m_randomEngine(m_randomDevice())
        , m_fuzzerConfig(config)
    {
    }

    Testing::Layout generateRandomLayout()
    {
        // for now we only support 1 main window
        Testing::Layout layout;
        Testing::MainWindowDescriptor mainWindow;
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

    Testing::DockWidgetDescriptor generateRandomDockWidget()
    {
        Testing::DockWidgetDescriptor dwd;

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

    Testing::DockWidgetDescriptor::List generateRandomDockWidgets(int num)
    {
        Testing::DockWidgetDescriptor::List dockWidgets;
        for (int i = 0; i < num; ++i) {
            dockWidgets << generateRandomDockWidget();
        }
        return dockWidgets;
    }

    bool getRandomBool(int truePercentage = 50)
    {
        std::uniform_int_distribution<> distrib(1, 100);
        return distrib(m_randomEngine) < truePercentage;
    }

    QPoint getRandomPos()
    {
        std::uniform_int_distribution<> posDistrib(0, 500);
        const int x = posDistrib(m_randomEngine);
        const int y = posDistrib(m_randomEngine);
        return {x, y};
    }

    Testing::Operation getRandomOperation()
    {
        Testing::Operation operation;
        operation.operationType = OperationType_CloseViaDockWidgetAPI; // TODO
        return operation;
    }

    Testing::Test generateRandomTest()
    {
        Testing::Test test;
        test.initialLayout = generateRandomLayout();

        const int numOperationsPerTest = OPERATIONS_PER_TEST;
        test.operations.reserve(numOperationsPerTest);
        for (int i = 0; i < numOperationsPerTest; ++i)
            test.operations << getRandomOperation();

        return test;
    }
    Testing::Test::List generateRandomTests(int num)
    {
        Testing::Test::List tests;

        for (int i = 0; i < num; ++i) {
            tests << generateRandomTest();
        }

        return tests;
    }

    void fuzz()
    {
        const Testing::Test::List tests = generateRandomTests(m_fuzzerConfig.numTests);
        for (const auto &test : tests)
            Testing::runTest(test);
    }

    QRect randomGeometry()
    {
        std::uniform_int_distribution<> posDistrib(0, 500);
        std::uniform_int_distribution<> sizeDistrib(700, 1500);
        const int width = posDistrib(m_randomEngine);
        const int height = sizeDistrib(m_randomEngine);

        QPoint pos = getRandomPos();

        return QRect(pos, QSize(width, height));
    }

    std::random_device m_randomDevice;
    std::mt19937 m_randomEngine;
    FuzzerConfig m_fuzzerConfig;
};


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Fuzzer fuzzer({ 1, 10, true });
    QTimer::singleShot(0, &fuzzer, &Fuzzer::fuzz);

    return app.exec();
}

#include <fuzzer.moc>
