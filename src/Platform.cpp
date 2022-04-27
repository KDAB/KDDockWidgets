/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform.h"

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
}

Platform *Platform::instance()
{
    return s_platform;
}

bool Platform::hasActivePopup() const
{
    return false;
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
