/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief A MultiSplitter with support for drop indicators when hovering over.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#pragma once

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"

#include "qtwidgets/views/View_qtwidgets.h"

namespace KDDockWidgets {

namespace Controllers {
class DropArea;
}

namespace Views {

class DOCKS_EXPORT DropArea_qtwidgets : public Views::View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit DropArea_qtwidgets(Controllers::DropArea *, View *parent);
    ~DropArea_qtwidgets();

    /// TODOm3
    bool onResize(QSize newSize) override;

private:
    Controllers::DropArea *const m_dropArea;
};

}
}