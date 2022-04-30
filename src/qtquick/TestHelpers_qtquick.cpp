/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "KDDockWidgets.h"
#include "Platform_qtquick.h"

#include "views/View_qtquick.h"
#include <QApplication> // TODO: Make it QGuiApplication
#include <QQmlEngine>
#include <QQuickStyle>
#include <QQuickItem>

using namespace KDDockWidgets;

#ifdef DOCKS_DEVELOPER_MODE

Platform_qtquick::Platform_qtquick(int argc, char *argv[])
    : Platform_qt(argc, argv)
{
    new QApplication(argc, argv);
    init();
}

void Platform_qtquick::tests_initPlatform_impl()
{
    Platform_qt::tests_initPlatform_impl();

    QQuickStyle::setStyle(QStringLiteral("Material")); // so we don't load KDE plugins
    m_qmlEngine = new QQmlEngine();
}

void Platform_qtquick::tests_deinitPlatform_impl()
{
    delete m_qmlEngine;
    Platform_qt::tests_deinitPlatform_impl();
}

std::shared_ptr<ViewWrapper> Platform_qtquick::tests_createView(std::shared_ptr<ViewWrapper> parent)
{
    auto parentItem = parent ? Views::asQQuickItem(parent.get()) : nullptr;
    auto newItem = new QQuickItem(parentItem);

    auto wrapper = new Views::ViewWrapper_qtquick(newItem);
    return std::shared_ptr<ViewWrapper>(wrapper);
}

#endif
