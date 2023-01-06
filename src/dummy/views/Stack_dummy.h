/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#pragma once

#include "View_dummy.h"
#include "views/StackViewInterface.h"

namespace KDDockWidgets {
namespace Views {

class DOCKS_EXPORT Stack_dummy : public View_dummy, public StackViewInterface
{
public:
    explicit Stack_dummy(Controllers::Stack *controller, QWidget *parent = nullptr);
    void init() override;

private:
    Q_DISABLE_COPY(Stack_dummy)
};

}
}
