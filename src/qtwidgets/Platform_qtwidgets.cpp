/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_qtwidgets.h"
#include "KDDockWidgets.h"

#include "qtwidgets/DebugWindow_p.h"
#include "qtwidgets/views/ViewWrapper_qtwidgets.h"

#include <QApplication>
#include <QTimer>

#include <memory.h>

static KDDockWidgets::Platform_qtwidgets s_platformQtWidgets;

using namespace KDDockWidgets;

Platform_qtwidgets::Platform_qtwidgets()
{
#ifdef DOCKS_DEVELOPER_MODE
    if (qEnvironmentVariableIntValue("KDDOCKWIDGETS_SHOW_DEBUG_WINDOW") == 1) {
        auto dv = new Debug::DebugWindow();
        dv->show();
    }
#endif

    // Delay call to init(), so we have a QApplication
    QTimer::singleShot(0, [this] {
        init();
    });
}

Platform_qtwidgets::~Platform_qtwidgets()
{
}

void Platform_qtwidgets::init()
{
    qApp->connect(qApp, &QGuiApplication::focusObjectChanged, qApp, [this](QObject *obj) {
        ViewWrapper *wrapper = obj ? new Views::ViewWrapper_qtwidgets(obj) : nullptr;
        focusedViewChanged.emit(std::shared_ptr<ViewWrapper>(wrapper));
    });
}

const char *Platform_qtwidgets::name() const
{
    return "qtwidgets";
}

bool Platform_qtwidgets::hasActivePopup() const
{
    return qApp->activePopupWidget() != nullptr;
}

std::shared_ptr<ViewWrapper> Platform_qtwidgets::focusedView() const
{
    if (auto w = qobject_cast<QWidget *>(qApp->focusObject())) {
        ViewWrapper *wrapper = new Views::ViewWrapper_qtwidgets(w);
        return std::shared_ptr<ViewWrapper>(wrapper);
    }

    return {};
}
