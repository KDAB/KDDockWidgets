/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_MULTISPLITTER_RUBBERBAND_QUICK_H
#define KD_MULTISPLITTER_RUBBERBAND_QUICK_H

#include "kddockwidgets/docks_export.h"
#include "View_qtquick.h"

#include <QQuickItem>

namespace KDDockWidgets::Views {

class DOCKS_EXPORT RubberBand_qtquick
    : public View_qtquick
{
    Q_OBJECT
public:
    explicit RubberBand_qtquick(QQuickItem *parent);
};

}

#endif
