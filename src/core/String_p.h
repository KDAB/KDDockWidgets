/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <string>

namespace KDDockWidgets {

class QString
{
public:
    QString() = default;
    QString(const char *data)
        : m_str(data)
    {
    }

    bool isEmpty() const
    {
        return m_str.empty();
    }

    void clear()
    {
        m_str.clear();
    }

    bool operator==(const QString &other) const
    {
        return m_str == other.m_str;
    }

    // TODOm4: remove
    std::string toStdString() const
    {
        return m_str;
    }

private:
    std::string m_str;
};

using QStringLiteral = QString;
using QLatin1String = QString;

}
