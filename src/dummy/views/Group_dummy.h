/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_dummy.h"
#include "views/GroupViewInterface.h"
#include "TitleBar_dummy.h"

namespace KDDockWidgets {

namespace Controllers {
class Group;
class DockWidget;
}

namespace Views {

class Stack_dummy;

class DOCKS_EXPORT Group_dummy : public View_dummy, public GroupViewInterface
{
public:
    explicit Group_dummy(Controllers::Group *controller, View *parent = nullptr);
    ~Group_dummy() override;

    QSize minSize() const override;
    QSize maxSizeHint() const override;
    QRect dragRect() const override;

protected:
    int nonContentsHeight() const override;

private:
    void init() override;
};

}
}
