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

/**
 * @file
 * @brief Application wide config to tune certain beahviours of the framework.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "Config.h"
#include <QApplication>
#include <QDebug>

using namespace KDDockWidgets;

class Config::Private
{
public:
    Private()
    {
    }

    Flags m_flags = Flag_Default;

};


Config::Config()
    : d(new Private())
{
}

Config& Config::instance()
{
    static Config config;
    return config;
}

Config::~Config()
{
    delete d;
}

Config::Flags Config::flags() const
{
    return d->m_flags;
}

void Config::setFlags(Flags f)
{
    if (!qApp) {
        qWarning() << Q_FUNC_INFO << "Only use this function before creating the QApplication";
        return;
    }

    if ((f & Flag_AeroSnapWithClientDecos) && (f & Flag_NativeTitleBar)) {
        // We're either using native or client decorations
        f = f & ~Flag_AeroSnapWithClientDecos;
    }

    d->m_flags = f;
}
