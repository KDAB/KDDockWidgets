/*
  This file is part of KDDockWidgets.

  Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <qmath.h>

/// @file
/// @brief Indirection to run tst_docks.exe. tst_docks is very big (140 tests), so instead we invoke
/// this launcher N times on a smaller subset, so we can use threads

static QStringList availableTests()
{
    QProcess p;
    p.setProgram(QString("%1/tst_docks").arg(qApp->applicationDirPath()));
    p.setArguments({ "-datatags" });
    p.start();
    const bool started = p.waitForStarted();
    if (!started) {
        qWarning() << "Failed to start process" << p.program();
        return {};
    }

    p.waitForFinished();

    const QString output = p.readAllStandardOutput();
    QStringList functions = output.split('\n');

    QStringList result;

    for (QString &function : functions) {
        function = function.replace("()", "").trimmed();
        function = function.replace(" ", ":"); // datatags
        function = function.replace("KDDockWidgets::TestDocks:", "");
        if (!function.isEmpty())
            result << function;
    }

    return result;
}

static QStringList calculateSubset(int subsetNumber, int subsetPercentage, const QStringList &allFunctions)
{
    if (allFunctions.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "No tests to run";
        return {};
    }

    const int blockSize = (subsetPercentage / 100.0) * allFunctions.size();
    const int numBlocks = qCeil(allFunctions.size() / (blockSize * 1.0));

    if (subsetNumber >= numBlocks)
        return {};

    QVector<QStringList> subsets;
    subsets.resize(numBlocks);

    int i = 0;
    // Interleave, since the first tst_docks functions take more time, due to mouse dragging
    for (const QString &func : allFunctions) {
        QStringList &subset = subsets[i % numBlocks];
        subset << func;
        i++;
    }

    return subsets.at(subsetNumber);
}

static int run_tests(const QStringList &subset)
{
    if (subset.isEmpty())
        return 0;

    QProcess p;
    p.setProgram(QString("%1/tst_docks").arg(qApp->applicationDirPath()));
    p.setArguments(subset);
    p.setProcessChannelMode(QProcess::ForwardedChannels);
    p.start();
    const bool started = p.waitForStarted();
    if (!started) {
        qWarning() << "Failed to start process" << p.program();
        return {};
    }

    p.waitForFinished();

    return p.exitCode();
}

int main(int argv, char**argc)
{
    QCoreApplication app(argv, argc);

    if (app.arguments().size() != 3) {
        qWarning() << "Usage:" << app.arguments().constFirst() << "<subsetNumber>" << "<subsetPercentage>";
        return -1;
    }

    bool ok = false;
    const int subsetNumber = app.arguments()[1].toInt(&ok);
    if (!ok) {
        qWarning() << "Invalid number" << app.arguments()[1];
        return -1;
    }

    const int subsetPercentage = app.arguments()[2].toInt(&ok);
    if (!ok) {
        qWarning() << "Invalid number" << app.arguments()[2];
        return -1;
    }

    if (subsetPercentage > 100 || subsetPercentage <= 0) {
        qWarning() << "Invalid percentage" << app.arguments()[2];
        return -1;
    }

    return run_tests(calculateSubset(subsetNumber, subsetPercentage, availableTests()));
}
