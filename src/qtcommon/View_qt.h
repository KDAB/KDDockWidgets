/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/View.h"

namespace KDDockWidgets::Views {

class DOCKS_EXPORT View_qt : public View
{
public:
    explicit View_qt(Controller *controller, Type type, QObject *thisObj);
    ~View_qt() override;

    QObject *thisObject() const;

protected:
    QObject *const m_thisObj;
};

}
