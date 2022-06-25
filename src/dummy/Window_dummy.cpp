/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "Window_dummy.h"

#include <QDebug>

using namespace KDDockWidgets;

Window_dummy::~Window_dummy() = default;

Window_dummy::Window_dummy()
    : Window()
{
}

std::shared_ptr<View> Window_dummy::rootView() const
{
    return nullptr;
}

Window::Ptr Window_dummy::transientParent() const
{
    return nullptr;
}

void Window_dummy::setGeometry(QRect geo) const
{
    Q_UNUSED(geo);
}

void Window_dummy::setVisible(bool)
{
}

bool Window_dummy::supportsHonouringLayoutMinSize() const
{
    // maybe...
    return false;
}
