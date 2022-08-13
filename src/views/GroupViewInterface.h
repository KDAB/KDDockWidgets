/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"


QT_BEGIN_NAMESPACE
class QRect;
QT_END_NAMESPACE

namespace KDDockWidgets {

namespace Controllers {
class DockWidget;
class Group;
}

namespace Views {

/// @brief The interface that Frame views should implement
class DOCKS_EXPORT GroupViewInterface
{
public:
    explicit GroupViewInterface(Controllers::Group *);
    virtual ~GroupViewInterface();
    virtual void removeDockWidget(Controllers::DockWidget *);
    virtual void insertDockWidget(Controllers::DockWidget *, int index);

    virtual int nonContentsHeight() const = 0;

    /// @brief the rect that should start a drag.
    /// Only relevant if the title bar isn't visible. For normal KDDW usage this method doesn't
    /// need to be reimplemented.
    virtual QRect dragRect() const;

    bool isMDI() const;
    Controllers::Group *group() const;

protected:
    Controllers::Group *const m_group;
};

}

}
