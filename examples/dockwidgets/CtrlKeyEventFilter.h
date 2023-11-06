/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <kddockwidgets/Config.h>

#include <QObject>
#include <QKeyEvent>

// This event filter is just for examplify how to use the KDDW API to show/hide
// the drag indicators when ctrl is pressed
class CtrlKeyEventFilter : public QObject
{
public:
    using QObject::QObject;

    ~CtrlKeyEventFilter() override;

    bool eventFilter(QObject *, QEvent *ev) override
    {
        if (ev->type() != QEvent::KeyPress && ev->type() != QEvent::KeyRelease)
            return false;

        auto me = static_cast<QKeyEvent *>(ev);
        if (me->key() != Qt::Key_Control)
            return false;

        KDDockWidgets::Config::self().setDropIndicatorsInhibited(ev->type() == QEvent::KeyRelease);

        return false;
    }
};
