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

#include "Widget_qwidget.h"
#include "Config.h"
#include "Item_p.h"
#include "Separator_p.h"

#ifdef KDMULTISPLITTER_QTQUICK
# include <QQmlEngine>
#endif

namespace Layouting
{

Config::Config()
{
    registerQmlTypes();
}

Separator *Config::createSeparator(Widget *parent) const
{
    if (m_separatorFactoryFunc)
        return m_separatorFactoryFunc(parent);

    return nullptr;
}

void Config::registerQmlTypes()
{
#ifdef KDMULTISPLITTER_QTQUICK
    qmlRegisterUncreatableType<Item>("com.kdab.kddockwidgets.multisplitter", 1, 0,
                                     "KDMultiSplitter", QStringLiteral("enum access"));
#endif
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
    if (m_separatorFactoryFunc && !func) {
        qWarning() << Q_FUNC_INFO << "Refusing to store nullptr separator func";
        return;
    }

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

}
