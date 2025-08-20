/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "QmlConfig.h"
#include "Config.h"
#include "DockWidgetInstantiator.h"
#include "kddockwidgets/core/DockWidget.h"

#include <QDebug>
#include <QPointer>
#include <private/qglobal_p.h>

using namespace KDDockWidgets;

QPointer<QmlConfig> QmlConfig::s_qmlConfigInstance;

static KDDockWidgets::Core::DockWidget *dockWidgetFactoryCallback(const QString &name)
{
    if (!QmlConfig::instance() || !QmlConfig::instance()->dockWidgetFactoryFunc().isCallable())
        return nullptr;

    QJSValue result = QmlConfig::instance()->dockWidgetFactoryFunc().call(QJSValueList() << name);
    if (result.isError() || result.isNull() || result.isUndefined())
        return nullptr;

    auto dwInstantiator = qobject_cast<KDDockWidgets::DockWidgetInstantiator *>(result.toQObject());
    if (!dwInstantiator)
        qWarning() << "QmlConfig: Factory function did not return a valid DockWidgetInstantiator for" << name;

    auto dw = dwInstantiator->controller();
    if (!dw)
        qWarning() << "QmlConfig: Factory function did not return a valid DockWidget for" << name;

    return dw;
}

QmlConfig::QmlConfig()
{
    if (s_qmlConfigInstance) {
        // Shouldn't happen since singleton
        qFatal("QmlConfig: Another instance already exists. Only one supported");
    } else {
        s_qmlConfigInstance = this;
    }
}

QmlConfig::~QmlConfig()
{
    s_qmlConfigInstance = nullptr;
}

QJSValue QmlConfig::dockWidgetFactoryFunc() const
{
    return m_dockWidgetFactoryFunc;
}

void QmlConfig::setDockWidgetFactoryFunc(const QJSValue &func)
{
    if (m_dockWidgetFactoryFunc.equals(func))
        return;

    m_dockWidgetFactoryFunc = func;

    if (m_dockWidgetFactoryFunc.isCallable()) {
        Config::self().setDockWidgetFactoryFunc(&dockWidgetFactoryCallback);
    } else {
        Config::self().setDockWidgetFactoryFunc(nullptr);
    }

    Q_EMIT dockWidgetFactoryFuncChanged();
}
