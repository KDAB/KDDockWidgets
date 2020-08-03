/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_MAIN_WINDOW_QUICK_P_H
#define KD_MAIN_WINDOW_QUICK_P_H

#include "MainWindowBase.h"

namespace KDDockWidgets {

class DOCKS_EXPORT MainWindowQuick : public MainWindowBase
{
    Q_OBJECT
    Q_PROPERTY(QString uniqueName READ uniqueName WRITE setUniqueName NOTIFY uniqueNameChanged)
public:
    explicit MainWindowQuick(const QString &uniqueName = {});
};

}

#endif
