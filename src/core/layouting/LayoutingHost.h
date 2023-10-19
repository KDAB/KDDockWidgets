/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"

namespace KDDockWidgets {

namespace Core {


/// The interface graphical components need to implement in order to host a layout
/// The layout engine doesn't know about any GUI, only about LayoutingHost.
/// This allows to keep the layouting engine separate from the rest of KDDW and even
/// reused by non-KDDW projects

class DOCKS_EXPORT LayoutingHost
{
public:
    virtual ~LayoutingHost();

    /// Weather this layout host supports min size constraints or not
    virtual bool supportsHonouringLayoutMinSize() const = 0;
};

}

}
