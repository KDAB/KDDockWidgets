/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"

#include <qglobal.h>

namespace KDDockWidgets {
class View;

namespace Controllers {
class Separator;
}

}

namespace Layouting {

typedef KDDockWidgets::View *(*SeparatorFactoryFunc)(KDDockWidgets::Controllers::Separator *controller, KDDockWidgets::View *parent);

class DOCKS_EXPORT_FOR_UNIT_TESTS Config
{
public:
    enum class Flag
    {
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
    /// Note: Only use this function at startup before creating any Item
    void setSeparatorThickness(int value);

    ///@brief sets the function used internally to create the separators
    void setSeparatorFactoryFunc(SeparatorFactoryFunc);

    ///@brief Returns the function used to create separators, null by default
    SeparatorFactoryFunc separatorFactoryFunc() const;

    ///@brief returns the flags;
    Config::Flags flags() const;

    ///@brief sets the flags. Set only before creating any Item
    void setFlags(Layouting::Config::Flags);

    Config();
    KDDockWidgets::View *createSeparator(KDDockWidgets::Controllers::Separator *, KDDockWidgets::View *) const;

private:
    friend class Item;
    friend class ItemBoxContainer;

    void registerQmlTypes();

    SeparatorFactoryFunc m_separatorFactoryFunc = nullptr;
    Flags m_flags = Flag::None;

    Q_DISABLE_COPY(Config);
};

}
