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

#include "Window_qtquick.h"
#include "views/View_qtquick.h"
#include "qtquick/Window_qtquick.h"

#include <QQmlEngine>
#include <QQuickStyle>
#include <QQuickWindow>
#include <QGuiApplication>
#include <QWindow>
#include <QScreen>

using namespace KDDockWidgets;


Platform_qtquick::Platform_qtquick()
{
    // KDDockWidgets::registerQmlTypes(); // TODOv2
    QQuickWindow::setDefaultAlphaBuffer(true);

    qApp->connect(qApp, &QGuiApplication::focusObjectChanged, qApp, [this](QObject *obj) {
        ViewWrapper *wrapper = obj ? new Views::ViewWrapper_qtquick(obj) : nullptr;
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

std::shared_ptr<ViewWrapper> Platform_qtquick::qobjectAsView(QObject *obj) const
{
    if (auto w = qobject_cast<QQuickItem *>(obj)) {
        ViewWrapper *wrapper = new Views::ViewWrapper_qtquick(w);
        return std::shared_ptr<ViewWrapper>(wrapper);
    }

    return nullptr;
}

std::shared_ptr<Window> Platform_qtquick::windowFromQWindow(QWindow *qwindow) const
{
    return std::shared_ptr<Window>(new Window_qtquick(qwindow));
}

FrameworkWidgetFactory *Platform_qtquick::createDefaultFrameworkWidgetFactory()
{
    return {};
}

Window::Ptr Platform_qtquick::windowAt(QPoint globalPos) const
{
    if (auto qwindow = qApp->QGuiApplication::topLevelAt(globalPos)) {
        auto window = new Window_qtquick(qwindow);
        return Window::Ptr(window);
    }

    return {};
}

int Platform_qtquick::screenNumberFor(View *view) const
{
    if (auto item = qobject_cast<QQuickItem *>(view->asQObject())) {
        if (QWindow *qtwindow = item->window())
            return screenNumberForQWindow(qtwindow);
    }

    return -1;
}

QSize Platform_qtquick::screenSizeFor(View *view) const
{
    if (auto item = qobject_cast<QQuickItem *>(view->asQObject())) {
        if (QWindow *qtwindow = item->window())
            if (QScreen *screen = qtwindow->screen())
                return screen->size();
    }


    return {};
}

#ifdef DOCKS_DEVELOPER_MODE

void Platform_qtquick::tests_initTests() const
{
    Platform_qt::tests_initTests();

    QQuickStyle::setStyle("Material"); // so we don't load KDE plugins
    KDDockWidgets::Config::self().setQmlEngine(new QQmlEngine(this));
}

void Platform_qtquick::tests_cleanupTests() const
{
    delete KDDockWidgets::Config::self().qmlEngine();
}

#endif
