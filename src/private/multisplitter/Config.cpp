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

#include "Config.h"
#include "Item_p.h"
#include "Separator_p.h"

using namespace Layouting;

Config::Config()
{
}

Separator *Config::createSeparator(QWidget *parent) const
{
    if (m_separatorFactoryFunc)
        return m_separatorFactoryFunc(parent);

    // won't be visible, but still create it, so we don't have to look for nullptrs in the code
    // won't be a use case anyway, you'll want to provide a factory func
    return new Separator(parent);
}

Config &Config::self()
{
    static Config config;
    return config;
}

Config::~Config()
{
}

int Config::separatorThickness() const
{
    // TODO: Make Item call Config::separatorThickness instead ?
    return Item::separatorThickness;
}

void Config::setSeparatorThickness(int value)
{
    if (value < 0 || value >= 100) {
        qWarning() << Q_FUNC_INFO << "Invalid value" << value;
        return;
    }

    Layouting::Item::separatorThickness = value;
}

void Config::setSeparatorFactoryFunc(SeparatorFactoryFunc func)
{
    m_separatorFactoryFunc = func;
}

SeparatorFactoryFunc Config::separatorFactoryFunc() const
{
    return m_separatorFactoryFunc;
}

Config::Flags Config::flags() const
{
    return m_flags;
}

void Config::setFlags(Flags flags)
{
    if (m_flags == flags)
        return;

    // validations here, if any

    m_flags = flags;
}
