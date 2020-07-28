/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "FloatingWindowQuick_p.h"
#include "Logging_p.h"
#include "Utils_p.h"
#include "DropArea_p.h"
#include "TitleBar_p.h"

#include <QDebug>

using namespace KDDockWidgets;

FloatingWindowQuick::FloatingWindowQuick(MainWindowBase *parent)
    : FloatingWindow(parent)
{
    init();
}

FloatingWindowQuick::FloatingWindowQuick(Frame *frame, MainWindowBase *parent)
    : FloatingWindow(frame, parent)
{
    init();
}


void FloatingWindowQuick::init()
{
    qDebug() << "FLoatingWindow!!";
}
