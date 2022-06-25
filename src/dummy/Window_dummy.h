/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/Window.h"

namespace KDDockWidgets {
class DOCKS_EXPORT Window_dummy : public Window
{
public:
    Window_dummy();
    ~Window_dummy() override;
    std::shared_ptr<View> rootView() const override;
    Window::Ptr transientParent() const override;
    void setGeometry(QRect) const override;
    void setVisible(bool) override;
    bool supportsHonouringLayoutMinSize() const override;
};

}
