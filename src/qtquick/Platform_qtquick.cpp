/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_qtquick.h"
#include "KDDockWidgets.h"
// #include "QmlTypes.h" // TODOv2

#include "views/View_qtquick.h"
#include <QQuickWindow>
#include <QGuiApplication>

static KDDockWidgets::Platform_qtquick s_platformQtQuick;

using namespace KDDockWidgets;



Platform_qtquick::Platform_qtquick()
{
    // KDDockWidgets::registerQmlTypes(); // TODOv2
    QQuickWindow::setDefaultAlphaBuffer(true);

    qApp->connect(qApp, &QGuiApplication::focusObjectChanged, qApp, [this](QObject *obj) {
        ViewWrapper *wrapper = new Views::ViewWrapper_qtquick(obj);
        focusedViewChanged.emit(std::shared_ptr<ViewWrapper>(wrapper));
    });
}

Platform_qtquick::~Platform_qtquick()
{
}

const char *Platform_qtquick::name() const
{
    return "qtquick";
}

std::shared_ptr<ViewWrapper> Platform_qtquick::focusedView() const
{
    if (auto item = qobject_cast<QQuickItem *>(qApp->focusObject())) {
        ViewWrapper *wrapper = new Views::ViewWrapper_qtquick(item);
        return std::shared_ptr<ViewWrapper>(wrapper);
    }

    return {};
}
