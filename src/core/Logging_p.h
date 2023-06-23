/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_DOCK_LOGGING_P_H
#define KD_DOCK_LOGGING_P_H
#pragma once

#ifdef KDDW_HAS_SPDLOG

#include "NonQtCompat_p.h"
#include <spdlog/spdlog.h>

template<>
struct fmt::formatter<QSize>
{
    constexpr auto parse(format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(QSize size, FormatContext &ctx)
    {
        return fmt::format_to(ctx.out(), "{}x{}", size.width(), size.height());
    }
};

template<>
struct fmt::formatter<QPoint>
{
    constexpr auto parse(format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(QPoint point, FormatContext &ctx)
    {
        return fmt::format_to(ctx.out(), "{}x{}", point.x(), point.y());
    }
};


#else

// KDDW is built without logging support.
// Declare some stubs, so caller code doesn't get littered with #ifdefs

namespace KDDockWidgets::spdlog {

template<typename... Args>
void warn(const char *, const Args &...)
{
}

template<typename... Args>
void error(const char *, const Args &...)
{
}

template<typename... Args>
void info(const char *, const Args &...)
{
}

template<typename... Args>
void debug(const char *, const Args &...)
{
}

template<typename... Args>
void trace(const char *, const Args &...)
{
}


}

#endif

#endif
