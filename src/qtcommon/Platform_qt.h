/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "docks_export.h"
#include "Platform.h"

namespace KDDockWidgets {

/// @brief Baseclass platform for Qt based platform
/// Useful since QtWidgets and QtQuick share some similarities
class DOCKS_EXPORT Platform_qt : public Platform
{
public:
    Platform_qt();
    ~Platform_qt() override;

    std::shared_ptr<ViewWrapper> focusedView() const override;
    QVector<std::shared_ptr<Window>> windows() const override;
    std::shared_ptr<Window> qobjectAsWindow(QObject *) const override;
    virtual std::shared_ptr<Window> windowFromQWindow(QWindow *) const = 0;
};

}
