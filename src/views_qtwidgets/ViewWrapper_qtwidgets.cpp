/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewWrapper_qtwidgets.h"

#include <QDebug>

using namespace KDDockWidgets::Views;

ViewWrapper_qtwidgets::ViewWrapper_qtwidgets(QWidget *widget)
    : ViewWrapper()
    , m_widget(widget)
{
}
