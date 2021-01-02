/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "controller.h"
#include "Item_p.h"

#include <QDebug>

Controller::Controller(Layouting::MultiSplitter *multisplitter)
    : m_multiSplitter(multisplitter)
{

}

void Controller::addItem(int loc, QQuickItem *relativeTo)
{
    auto location = Layouting::Item::Location(loc);
    m_multiSplitter->addItem(":/MyItem.qml", location, relativeTo);
}
