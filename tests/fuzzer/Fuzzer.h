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

#ifndef KDDOCKWIDGETS_FUZZER_H
#define KDDOCKWIDGETS_FUZZER_H

#include "../Testing.h"
#include "MainWindowBase.h"
#include "Operations.h"

#include <QJsonDocument>
#include <QVector>
#include <random>

namespace KDDockWidgets {
namespace Testing {

static QVariantMap sizeToVariantMap(QSize sz)
{
    QVariantMap map;
    map["width"] = sz.width();
    map["height"] = sz.height();
    return map;
}

static QVariantMap rectToVariantMap(QRect r)
{
    QVariantMap map;
    map["size"] = sizeToVariantMap(r.size());
    map["x"] = r.x();
    map["y"] = r.y();
    return map;
}

static QSize sizeFromVariantMap(const QVariantMap &map)
{
    return { map["x"].toInt(), map["y"].toInt() };
}

static QRect rectFromVariantMap(const QVariantMap &map)
{
    const QSize sz = sizeFromVariantMap(map["size"].toMap());
    return { map["x"].toInt(), map["y"].toInt(), sz.width(), sz.height() };
}

class Fuzzer : public QObject
             , WarningObserver
{
    Q_OBJECT
public:

    struct FuzzerConfig
    {
        int numTests;
        int numOperationsPerTest;
        bool singleMainWindow;
    };

    struct DockWidgetDescriptor {
        typedef QVector<DockWidgetDescriptor> List;
        QSize minSize; // the minSize of the hosted widget
        QRect geometry;
        bool isFloating;
        bool isVisible;

        QVariantMap toVariantMap() const
        {
            QVariantMap map;
            map[QStringLiteral("minSize")] = sizeToVariantMap(minSize);
            map[QStringLiteral("geometry")] = rectToVariantMap(geometry);
            map[QStringLiteral("isFloating")] = isFloating;
            map[QStringLiteral("isVisible")] = isVisible;

            return map;
        }

        static DockWidgetDescriptor fromVariantMap(const QVariantMap &map)
        {
            DockWidgetDescriptor dock;

            dock.minSize = sizeFromVariantMap(map["minSize"].toMap());
            dock.geometry = rectFromVariantMap(map["geometry"].toMap());
            dock.isFloating = map["isFloating"].toBool();
            dock.isVisible = map["isVisible"].toBool();

            return dock;
        }

    };

    struct MainWindowDescriptor {
        typedef QVector<MainWindowDescriptor> List;
        QRect geometry;
        MainWindowOption mainWindowOption;

        QVariantMap toVariantMap() const
        {
            QVariantMap map;
            map[QStringLiteral("geometry")] = rectToVariantMap(geometry);
            map[QStringLiteral("mainWindowOption")] = mainWindowOption;
            return map;
        }

        static MainWindowDescriptor fromVariantMap(const QVariantMap &map)
        {
            MainWindowDescriptor mainWindow;

            mainWindow.mainWindowOption = MainWindowOption(map["mainWindowOption"].toInt());
            mainWindow.geometry = rectFromVariantMap(map["geometry"].toMap());

            return mainWindow;
        }
    };

    struct Layout {
        typedef QVector<Layout> List;
        MainWindowDescriptor::List mainWindows;
        DockWidgetDescriptor::List dockWidgets;

        QVariantMap toVariantMap() const
        {
            QVariantList mainWindowsVariant;
            mainWindowsVariant.reserve(mainWindows.size());
            for (const auto &mw : mainWindows) {
                mainWindowsVariant << mw.toVariantMap();
            }

            QVariantList dockWidgetsVariant;
            dockWidgetsVariant.reserve(dockWidgets.size());
            for (const auto &dw : dockWidgets) {
                dockWidgetsVariant << dw.toVariantMap();
            }

            QVariantMap map;
            map[QStringLiteral("mainWindows")] = mainWindowsVariant;
            map[QStringLiteral("dockWidgets")] = dockWidgetsVariant;
            return map;
        }


        static Layout fromVariantMap(const QVariantMap &map)
        {
            Layout l;

            const QVariantList mainWindows = map["mainWindows"].toList();
            const QVariantList dockWidgets = map["dockWidgets"].toList();

            l.mainWindows.reserve(mainWindows.size());
            for (const QVariant &mainwindow : mainWindows)
                l.mainWindows.push_back(MainWindowDescriptor::fromVariantMap(mainwindow.toMap()));

            l.dockWidgets.reserve(dockWidgets.size());
            for (const QVariant &dockWidget : dockWidgets)
                l.dockWidgets.push_back(DockWidgetDescriptor::fromVariantMap(dockWidget.toMap()));

            return l;
        }
    };

    struct Test {
        typedef QVector<Test> List;
        Layout initialLayout;
        Operations::OperationBase::List operations;
        QVariantMap toVariantMap() const
        {
            QVariantMap map;
            map[QStringLiteral("initialLayout")] = initialLayout.toVariantMap();

            QVariantList operationsVariant;
            operationsVariant.reserve(operations.size());
            int i = 0;
            for (const auto &o : operations) {
                QVariantMap operationVariant = o->toVariantMap();
                if (operationVariant.isEmpty())
                    break;

                operationVariant["index"] = i;
                ++i;
                operationsVariant << operationVariant;
            }

            map[QStringLiteral("operations")] = operationsVariant;
            return map;
        }

        static Test fromVariantMap(Fuzzer *fuzzer, const QVariantMap &map)
        {
            Test t;
            t.initialLayout = Layout::fromVariantMap(map["initialLayout"].toMap());

            const QVariantList operations = map["operations"].toList();
            t.operations.reserve(operations.size());
            for (const QVariant &operation : operations)
                t.operations.push_back(Operations::OperationBase::fromVariantMap(fuzzer, operation.toMap()));

            return t;
        }
    };

    void runTest(const Test &);

    explicit Fuzzer(bool dumpJsonOnFailure, QObject *parent = nullptr);

    Fuzzer::Layout generateRandomLayout();

    Fuzzer::DockWidgetDescriptor generateRandomDockWidget();

    Fuzzer::DockWidgetDescriptor::List generateRandomDockWidgets(int num);

    bool getRandomBool(int truePercentage = 50);

    Testing::AddDockWidgetParams getRandomAddDockWidgetParams();

    KDDockWidgets::MainWindowBase* getRandomMainWindow();
    KDDockWidgets::DockWidgetBase* getRandomDockWidget(DockWidgetBase *excluding = nullptr);
    KDDockWidgets::DockWidgetBase* getRandomRelativeTo(MainWindowBase *mainWindow,
                                                       DockWidgetBase *excluding);

    KDDockWidgets::Location getRandomLocation();

    QPoint getRandomPos();

    Operations::OperationBase::Ptr getRandomOperation();

    Fuzzer::Test generateRandomTest();
    Fuzzer::Test::List generateRandomTests(int num);

    void fuzz(FuzzerConfig config);
    void fuzz(const QStringList &jsonFiles);
    void fuzz(const QString &json);

    QRect randomGeometry();

    void onFatal() override;

private:
    std::random_device m_randomDevice;
    std::mt19937 m_randomEngine;
    Fuzzer::Test m_currentTest;
    const bool m_dumpJsonOnFailure;
};

}
}

#endif
