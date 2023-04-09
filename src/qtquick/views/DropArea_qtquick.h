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

namespace Core {
class DropArea;
}

namespace qtquick {

class DOCKS_EXPORT DropArea : public Views::View_qtquick
{
    Q_OBJECT
public:
    explicit DropArea(Core::DropArea *, View *parent);
    ~DropArea();

private:
    Core::DropArea *const m_dropArea;
};

}
}
