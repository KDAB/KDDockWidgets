/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#ifndef KD_FRAME_QUICK_P_H
#define KD_FRAME_QUICK_P_H

#include "Frame_p.h"

namespace KDDockWidgets {

/**
 * @brief The GUI counterpart of Frame.
 */
class DOCKS_EXPORT FrameQuick : public Frame
{
    Q_OBJECT
public:
    explicit FrameQuick(QWidgetAdapter *parent = nullptr, Options = Option_None);

};

}

#endif
