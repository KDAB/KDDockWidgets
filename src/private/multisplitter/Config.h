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

#pragma once

#include "multisplitter_export.h"

#include <qglobal.h>

namespace Layouting {

class Separator;
class Widget;

typedef Separator* (*SeparatorFactoryFunc)(Layouting::Widget *parent);

class MULTISPLITTER_EXPORT Config {
public:

    enum class Flag {
        None = 0,
        LazyResize = 1
    };
    Q_DECLARE_FLAGS(Flags, Flag);

    ///@brief returns the singleton Config instance
    static Config &self();

    ///@brief destructor, called at shutdown
    ~Config();

    /**
     * @brief Returns the thickness of the separator.
     *
     * Default is 5px.
     */
    int separatorThickness() const;

    ///@brief setter for @ref separatorThickness
    ///Note: Only use this function at startup before creating any Item
    void setSeparatorThickness(int value);

    ///@brief sets the function used internally to create the separators
    void setSeparatorFactoryFunc(SeparatorFactoryFunc);

    ///@brief Returns the function used to create separators, null by default
    SeparatorFactoryFunc separatorFactoryFunc() const;

    ///@brief returns the flags;
    Config::Flags flags() const;

    ///@brief sets the flags. Set only before creating any Item
    void setFlags(Flags);

private:
    friend class Item;
    friend class ItemContainer;

    Config();
    Separator* createSeparator(Layouting::Widget *) const;

    void registerQmlTypes();

    SeparatorFactoryFunc m_separatorFactoryFunc = nullptr;
    Flags m_flags = Flag::None;

    Q_DISABLE_COPY(Config);
};

}
