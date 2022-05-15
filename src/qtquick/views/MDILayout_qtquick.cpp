/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MDILayout_qtquick.h"
#include "controllers/MDILayout.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

MDILayout_qtquick::MDILayout_qtquick(Controllers::MDILayout *controller, View *parent)
    : Views::View_qtquick(controller, Type::MDILayout, asQQuickItem(parent))
    , m_controller(controller)
{
    Q_ASSERT(controller);
}

MDILayout_qtquick::~MDILayout_qtquick()
{
    if (!freed())
        m_controller->viewAboutToBeDeleted();
}

void MDILayout_qtquick::onLayoutRequest()
{
    m_controller->updateSizeConstraints();
}

bool MDILayout_qtquick::onResize(QSize newSize)
{
    return m_controller->onResize(newSize);
}
