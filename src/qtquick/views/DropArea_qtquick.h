/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_qtquick.h"

namespace KDDockWidgets {

namespace Controllers {
class DropArea;
}

namespace Views {

class DOCKS_EXPORT DropArea_qtquick : public Views::View_qtquick
{
    Q_OBJECT
public:
    explicit DropArea_qtquick(Controllers::DropArea *, View *parent);
    ~DropArea_qtquick();

private:
    Controllers::DropArea *const m_dropArea;
};

}
}
