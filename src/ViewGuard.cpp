/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Waqar Ahmed <waqar.ahmed@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewGuard.h"
#include "View.h"

using namespace KDDockWidgets;

ViewGuard::ViewGuard(View *view)
    : v(view && view->inDtor() ? nullptr : view)
{
    if (v) {
        m_onDestroy = v->beingDestroyed.connect([this] {
            v = nullptr;
        });
    }
}

ViewGuard::operator bool() const
{
    return !isNull();
}

bool ViewGuard::isNull() const
{
    return v == nullptr;
}

View *ViewGuard::operator->()
{
    return v;
}

void ViewGuard::clear()
{
    v = nullptr;
    if (m_onDestroy.isActive())
        m_onDestroy.disconnect();
}

View *ViewGuard::view() const
{
    return v;
}

ViewGuard &ViewGuard::operator=(View *view)
{
    if (view == v)
        return *this;

    // Remove the previous connection
    clear();
    v = view;

    m_onDestroy = v->beingDestroyed.connect([this] {
        v = nullptr;
    });
    return *this;
}
