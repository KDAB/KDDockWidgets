/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "docks_export.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

/// An spdlog logger that terminates the application if an error is printed
/// This is only used by the tests. KDDW should be error free.

namespace KDDockWidgets {

class DOCKS_EXPORT FatalLogger : public spdlog::sinks::stdout_color_sink_mt
{
public:
    ~FatalLogger() override;
    static std::shared_ptr<spdlog::logger> create();
    void log(const spdlog::details::log_msg &msg) override;
};

}
