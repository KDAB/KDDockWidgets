/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <kddockwidgets/docks_export.h>

#include <QQuickItem>

namespace KDDockWidgets {

class DOCKS_EXPORT QmlConfig : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(Config)
    QML_SINGLETON
    Q_PROPERTY(QJSValue dockWidgetFactoryFunc READ dockWidgetFactoryFunc WRITE setDockWidgetFactoryFunc NOTIFY dockWidgetFactoryFuncChanged)
public:
    QmlConfig();
    ~QmlConfig() override;

    QJSValue dockWidgetFactoryFunc() const;
    void setDockWidgetFactoryFunc(const QJSValue &func);

    static QmlConfig *instance()
    {
        return s_qmlConfigInstance;
    }

Q_SIGNALS:
    void dockWidgetFactoryFuncChanged();

private:
    QJSValue m_dockWidgetFactoryFunc;
    static QPointer<QmlConfig> s_qmlConfigInstance;
};

}
