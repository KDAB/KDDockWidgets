/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_FLOATING_WINDOWQUICK_P_H
#define KD_FLOATING_WINDOWQUICK_P_H

#include "FloatingWindow_p.h"

namespace KDDockWidgets {

class DOCKS_EXPORT FloatingWindowQuick : public FloatingWindow
{
    Q_OBJECT
public:
    explicit FloatingWindowQuick(QWidgetOrQuick *parent = nullptr);
    explicit FloatingWindowQuick(Frame *frame, QWidgetOrQuick *parent = nullptr);

private:
    void init();
    Q_DISABLE_COPY(FloatingWindowQuick)
};

}

#endif
