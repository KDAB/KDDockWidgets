/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "KDDockWidgets.h"
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

template<>
struct fmt::formatter<QRect>
{
    constexpr auto parse(format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(QRect r, FormatContext &ctx)
    {
        return fmt::format_to(ctx.out(), "Rect({},{} {}x{})", r.x(), r.y(), r.width(), r.height());
    }
};


template<>
struct fmt::formatter<QString>
{
    constexpr auto parse(format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const QString &str, FormatContext &ctx)
    {
        return fmt::format_to(ctx.out(), "{}", str.toStdString());
    }
};

template<>
struct fmt::formatter<QStringList>
{
    constexpr auto parse(format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const QStringList &strings, FormatContext &ctx)
    {
        return fmt::format_to(ctx.out(), "{}", strings.join(QLatin1Char(',')));
    }
};

template<typename T>
struct fmt::formatter<QVector<T>>
{
    constexpr auto parse(format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const QVector<T> &vec, FormatContext &ctx)
    {

        auto out = ctx.out();
        out = fmt::format_to(out, "{}", "{ ");
        for (const auto &element : vec)
            out = fmt::format_to(out, "{}, ", element);
        out = fmt::format_to(out, "{}", " }");

        return out;
    }
};


template<>
struct fmt::formatter<KDDockWidgets::DropLocation>
{
    constexpr auto parse(format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(KDDockWidgets::DropLocation loc, FormatContext &ctx)
    {

        switch (loc) {
        case KDDockWidgets::DropLocation_None:
            return fmt::format_to(ctx.out(), "DropLocation_None");
        case KDDockWidgets::DropLocation_Left:
            return fmt::format_to(ctx.out(), "DropLocation_Left");
        case KDDockWidgets::DropLocation_Top:
            return fmt::format_to(ctx.out(), "DropLocation_Top");
        case KDDockWidgets::DropLocation_Right:
            return fmt::format_to(ctx.out(), "DropLocation_Right");
        case KDDockWidgets::DropLocation_Bottom:
            return fmt::format_to(ctx.out(), "DropLocation_Bottom");
        case KDDockWidgets::DropLocation_Center:
            return fmt::format_to(ctx.out(), "DropLocation_Center");
        case KDDockWidgets::DropLocation_OutterLeft:
            return fmt::format_to(ctx.out(), "DropLocation_OutterLeft");
        case KDDockWidgets::DropLocation_OutterTop:
            return fmt::format_to(ctx.out(), "DropLocation_OutterTop");
        case KDDockWidgets::DropLocation_OutterRight:
            return fmt::format_to(ctx.out(), "DropLocation_OutterRight");
        case KDDockWidgets::DropLocation_OutterBottom:
            return fmt::format_to(ctx.out(), "DropLocation_OutterBottom");
        default:
            break;
        }

        return fmt::format_to(ctx.out(), "{}", ( int )loc);
    }
};

template<>
struct fmt::formatter<KDDockWidgets::InitialOption>
{
    constexpr auto parse(format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const KDDockWidgets::InitialOption &opt, FormatContext &ctx)
    {
        return fmt::format_to(ctx.out(), "[InitialOption: preferredSize={}, visibility={}]", opt.preferredSize, ( int )opt.visibility);
    }
};
