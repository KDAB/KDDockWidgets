/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform.h"

#include "qtwidgets/Platform_qtwidgets.h"
#include "qtquick/Platform_qtquick.h"
#include "Config.h"

#include <qglobal.h>
#include <QDebug>

using namespace KDDockWidgets;

static Platform *s_platform = nullptr;

Platform::Platform()
{
    Q_ASSERT(!s_platform);
    s_platform = this;
}

Platform::~Platform()
{
    s_platform = nullptr;
}

Platform *Platform::instance()
{
    return s_platform;
}

bool Platform::hasActivePopup() const
{
    return false;
}


#ifdef DOCKS_DEVELOPER_MODE

/*static*/
void Platform::tests_initPlatform(int argc, char *argv[], KDDockWidgets::FrontendType type)
{
    if (Platform::instance())
        return;

    switch (type) {
    case FrontendType::QtWidgets:
        new Platform_qtwidgets(argc, argv);
        break;
    case FrontendType::QtQuick:
        new Platform_qtquick(argc, argv);
        break;
    }

    /// Any additional setup
    Platform::instance()->tests_initPlatform_impl();

    /// Reset the default framework factory, so we can test several frontends in the same test run
    Config::self().setFrameworkWidgetFactory(Platform::instance()->createDefaultFrameworkWidgetFactory());
}

/*static */
void Platform::tests_deinitPlatform()
{
    auto plat = Platform::instance();

    plat->tests_deinitPlatform_impl();
    delete plat;
}

/**static*/
std::vector<KDDockWidgets::FrontendType> Platform::frontendTypes()
{
    std::vector<KDDockWidgets::FrontendType> types;
    types.reserve(int(FrontendType::LAST));
    for (int i = int(FrontendType::FIRST); i <= int(FrontendType::LAST); ++i) {
        types.push_back(FrontendType(i));
    }

    return types;
}

#endif