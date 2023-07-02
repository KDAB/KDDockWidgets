/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "FloatingWindow.h"
#include "Config.h"

#include <kdbindings/signal.h>

#include <QPointer>

#pragma once


namespace KDDockWidgets {

namespace Core {

class FloatingWindow::Private
{
public:
    explicit Private(FloatingWindowFlags requestedFlags, FloatingWindow *q);

    KDBindings::Signal<> activatedChanged;
    KDBindings::Signal<> numFramesChanged;
    KDBindings::Signal<> numDockWidgetsChanged;
    KDBindings::Signal<> windowStateChanged;

    KDBindings::ScopedConnection m_visibleWidgetCountConnection;
    KDBindings::ScopedConnection m_currentStateChangedConnection;

    const FloatingWindowFlags m_flags;
    QPointer<DropArea> m_dropArea;
};

}

}
