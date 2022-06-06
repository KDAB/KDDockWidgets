/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#define DOCTEST_CONFIG_IMPLEMENT

#include "Platform.h"
#include "Window.h"

#include <QRect>
#include <QSize>
#include <QPoint>

#include <doctest/doctest.h>
#include <iostream>

std::ostream &operator<<(std::ostream &os, QSize size)
{
    os << QStringLiteral("QSize(%1x%2)").arg(size.width()).arg(size.height()).toStdString();
    return os;
}

std::ostream &operator<<(std::ostream &os, QPoint pt)
{
    os << QStringLiteral("QPoint(%1,%2)").arg(pt.x()).arg(pt.y()).toStdString();
    return os;
}

std::ostream &operator<<(std::ostream &os, QRect r)
{
    os << QStringLiteral("QRect(%1,%2 %3x%4)").arg(r.x()).arg(r.y()).arg(r.width()).arg(r.height()).toStdString();
    return os;
}

using namespace KDDockWidgets;

inline View *createViewAndWindow(Platform::CreateViewOptions opts, View *parent = nullptr)
{
    opts.createWindow = true;
    return Platform::instance()->tests_createView(opts, parent);
}

int main(int argc, char **argv)
{
    int exitCode = 0;

    doctest::Context ctx;
    ctx.setOption("abort-after", 4);
    ctx.applyCommandLine(argc, argv);
    ctx.setOption("no-breaks", true);

    for (FrontendType type : Platform::frontendTypes()) {

        Platform::tests_initPlatform(argc, argv, type);

        std::cout << "\nStarting tests for Platform" << Platform::instance()->name() << "\n";

        int code = ctx.run();

        if (Platform::instance()->m_numWarningsEmitted > 0) {
            std::cout << "ABORTING! Test caused a warning.\n";
            code = 1;
        }

        if (code != 0)
            exitCode = code;

        Platform::tests_deinitPlatform();
    }

    return exitCode;
}
