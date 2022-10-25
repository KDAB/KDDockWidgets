/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"
#include "views/TitleBarViewInterface.h"
#include "View_dummy.h"

namespace KDDockWidgets {


namespace Controllers {
class TitleBar;
}

namespace Views {

class DOCKS_EXPORT TitleBar_dummy : public View_dummy, public Views::TitleBarViewInterface
{
public:
    explicit TitleBar_dummy(Controllers::TitleBar *controller, View *parent = nullptr);
    ~TitleBar_dummy() override;

protected:
#ifdef DOCKS_DEVELOPER_MODE
    // These 3 just for unit-tests
    bool isCloseButtonEnabled() const override;
    bool isCloseButtonVisible() const override;
    bool isFloatButtonVisible() const override;
#endif

protected:
    void init() override;
};

}

}
