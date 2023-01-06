/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief The QQuickItem counter part of TabWidgetQuick. Handles GUI while TabWidget handles state.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDTABWIDGETQUICK_P_H
#define KDTABWIDGETQUICK_P_H
#pragma once

#include "View_qtquick.h"
#include "views/StackViewInterface.h"

#include <QVector>

namespace KDDockWidgets {

namespace Controllers {
class Stack;
}

namespace Views {

class DOCKS_EXPORT Stack_qtquick : public View_qtquick, public StackViewInterface
{
    Q_OBJECT
public:
    explicit Stack_qtquick(Controllers::Stack *controller, QQuickItem *parent = nullptr);

private:
    Q_DISABLE_COPY(Stack_qtquick)
};

}
}

#endif
