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

#include <QCommandLineParser>
#include <QApplication>
#include <QTimer>
#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Testing;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Fuzzer Help");
    parser.addPositionalArgument("json", QCoreApplication::translate("main", "json file to load"));

    QCommandLineOption slowDownOption("s", QCoreApplication::translate("main", "Slowdown tests. Adds a 1 second delay between operations"));
    parser.addOption(slowDownOption);

    parser.addHelpOption();
    parser.process(app);

    const bool slowDown = parser.isSet(slowDownOption);

    const QStringList filesToLoad = parser.positionalArguments();

    const bool dumpToJsonOnFatal = filesToLoad.isEmpty();
    Fuzzer fuzzer(dumpToJsonOnFatal);
    if (slowDown)
        fuzzer.setDelayBetweenOperations(1000);

    QTimer::singleShot(0, &fuzzer, [&fuzzer, filesToLoad] {
        if (filesToLoad.isEmpty())
            fuzzer.fuzz({ 1, 10, true });
        else
            fuzzer.fuzz(filesToLoad);
    });

    return app.exec();
}
