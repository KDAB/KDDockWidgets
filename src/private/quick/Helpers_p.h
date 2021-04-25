/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_QTQUICK_HELPERS_P_H
#define KD_QTQUICK_HELPERS_P_H

#include <QObject>

namespace KDDockWidgets {
class QtQuickHelpers : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;
};
}

#endif
