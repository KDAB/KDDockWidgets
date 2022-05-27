/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_qtquick.h"
#include "KDDockWidgets.h"
#include "Config.h"
#include "QmlTypes.h"

#include "Window_qtquick.h"
#include "views/View_qtquick.h"
#include "qtquick/Window_qtquick.h"
#include "private/DockRegistry_p.h"
#include "private/DragController_p.h"
#include "ViewFactory_qtquick.h"

#include <QQmlEngine>
#include <QQuickStyle>
#include <QQuickWindow>
#include <QWindow>
#include <QScreen>
#include <QQuickItem>
#include <QGuiApplication>
#include <QQmlContext>

using namespace KDDockWidgets;

// QQmlEngine *Platform_qtquick::m_qmlEngine = nullptr;

Platform_qtquick::Platform_qtquick()
{
    init();
}

void Platform_qtquick::init()
{
#if defined(KDDOCKWIDGETS_STATICLIB) || defined(QT_STATIC)
    Q_INIT_RESOURCE(kddockwidgets_resources);
    Q_INIT_RESOURCE(kddockwidgets_qtquick);
#endif

    KDDockWidgets::registerQmlTypes();
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

ViewFactory *Platform_qtquick::createDefaultViewFactory()
{
    return new ViewFactory_qtquick();
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

QQmlEngine *Platform_qtquick::qmlEngine() const
{
    if (!m_qmlEngine)
        qWarning() << "Please call KDDockWidgets::Platform_qtquick::self()->setQmlEngine(engine)";

    return m_qmlEngine;
}

void Platform_qtquick::setQmlEngine(QQmlEngine *qmlEngine)
{
    if (m_qmlEngine) {
        qWarning() << Q_FUNC_INFO << "Already has QML engine";
        return;
    }

    if (!qmlEngine) {
        qWarning() << Q_FUNC_INFO << "Null QML engine";
        return;
    }

    m_qmlEngine = qmlEngine;

    auto dr = DockRegistry::self(); // make sure our QML types are registered
    QQmlContext *context = qmlEngine->rootContext();
    context->setContextProperty(QStringLiteral("_kddwHelpers"), &m_qquickHelpers);
    context->setContextProperty(QStringLiteral("_kddwDockRegistry"), dr);
    context->setContextProperty(QStringLiteral("_kddwDragController"), DragController::instance());
    context->setContextProperty(QStringLiteral("_kddw_widgetFactory"), Config::self().viewFactory());
}

ViewFactory_qtquick *Platform_qtquick::viewFactory() const
{
    return static_cast<ViewFactory_qtquick *>(Config::self().viewFactory());
}

View *Platform_qtquick::createView(View *parent) const
{
    return new Views::View_qtquick(nullptr, Type::None, Views::asQQuickItem(parent));
}
