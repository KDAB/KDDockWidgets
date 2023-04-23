/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/qtcommon/Window_qt.h"

namespace KDDockWidgets::qtquick {

class DOCKS_EXPORT Window : public qtcommon::Window_qt
{
public:
    using qtcommon::Window_qt::Window_qt;
    ~Window();
    std::shared_ptr<Core::View> rootView() const override;
    Window::Ptr transientParent() const override;
    void setVisible(bool) override;
    bool supportsHonouringLayoutMinSize() const override;
};

}
