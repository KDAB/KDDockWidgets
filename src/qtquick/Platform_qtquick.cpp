/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_qtquick.h"
#include "kddockwidgets/KDDockWidgets.h"
#include "kddockwidgets/View_qt.h"
#include "Config.h"
#include "QmlTypes.h"

#include "Helpers_p.h"
#include "Window_qtquick.h"
#include "views/View_qtquick.h"
#include "qtquick/Window_qtquick.h"
#include "DockRegistry.h"
#include "private/DragController_p.h"
#include "private/Platform_p.h"
#include "ViewFactory_qtquick.h"
#include "views/ViewWrapper_qtquick.h"

#include "views/DockWidget_qtquick.h"
#include "DockWidgetInstantiator.h"

#include <QQmlEngine>
#include <QQuickStyle>
#include <QQuickWindow>
#include <QWindow>
#include <QScreen>
#include <QQuickItem>
#include <QGuiApplication>
#include <QQmlContext>

#if defined(KDDOCKWIDGETS_STATICLIB) || defined(QT_STATIC)
static void initResources()
{
    Q_INIT_RESOURCE(kddockwidgets_resources);
    Q_INIT_RESOURCE(kddockwidgets_qtquick);
}
#endif

using namespace KDDockWidgets;

inline QQuickItem *mouseAreaForPos(QQuickItem *item, QPointF globalPos)
{
    QRectF rect = item->boundingRect();
    rect.moveTopLeft(item->mapToGlobal(QPointF(0, 0)));

    // Assumes children are inside its parent. That's fine for KDDW's purposes.
    if (!rect.contains(globalPos)) {
        return nullptr;
    }

    const QList<QQuickItem *> children = item->childItems();

    for (auto it = children.rbegin(), end = children.rend(); it != end; ++it) {
        if (QQuickItem *receiver = mouseAreaForPos(*it, globalPos))
            return receiver;
    }

    if (QLatin1String(item->metaObject()->className()) == QLatin1String("QQuickMouseArea"))
        return item;

    return nullptr;
}

Platform_qtquick::Platform_qtquick()
    : m_qquickHelpers(new QtQuickHelpers())
{
    init();
}

void Platform_qtquick::init()
{
#if defined(KDDOCKWIDGETS_STATICLIB) || defined(QT_STATIC)
    initResources();
#endif

    KDDockWidgets::registerQmlTypes();
    QQuickWindow::setDefaultAlphaBuffer(true);

    qGuiApp->connect(qApp, &QGuiApplication::focusObjectChanged, qApp, [this](QObject *obj) {
        ViewWrapper *wrapper = obj ? new Views::ViewWrapper_qtquick(obj) : nullptr;
        d->focusedViewChanged.emit(std::shared_ptr<View>(wrapper));
    });
}

Platform_qtquick::~Platform_qtquick()
{
    delete m_qquickHelpers;
}

const char *Platform_qtquick::name() const
{
    return "qtquick";
}

std::shared_ptr<View> Platform_qtquick::qobjectAsView(QObject *obj) const
{
    if (auto w = qobject_cast<QQuickItem *>(obj)) {
        ViewWrapper *wrapper = new Views::ViewWrapper_qtquick(w);
        return std::shared_ptr<View>(wrapper);
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
    if (auto qwindow = qGuiApp->QGuiApplication::topLevelAt(globalPos)) {
        auto window = new Window_qtquick(qwindow);
        return Window::Ptr(window);
    }

    return {};
}

int Platform_qtquick::screenNumberFor(View *view) const
{
    if (auto item = qobject_cast<QQuickItem *>(Views::View_qt::asObject(view))) {
        if (QWindow *qtwindow = item->window())
            return screenNumberForQWindow(qtwindow);
    }

    return -1;
}

QSize Platform_qtquick::screenSizeFor(View *view) const
{
    if (auto item = qobject_cast<QQuickItem *>(Views::View_qt::asObject(view))) {
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
    context->setContextProperty(QStringLiteral("_kddwHelpers"), m_qquickHelpers);
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

/** static */
Platform_qtquick *Platform_qtquick::instance()
{
    auto p = Platform::instance();
    if (p->isQtQuick())
        return static_cast<Platform_qtquick *>(p);
    return nullptr;
}

bool Platform_qtquick::usesFallbackMouseGrabber() const
{
    // For QtQuick we use the global event filter as mouse delivery is flaky
    // For example, the same QQuickItem that receives the press isn't receiving the mouse moves
    // when the top-level window moves.
    return true;
}

bool Platform_qtquick::inDisallowedDragView(QPoint globalPos) const
{
    auto window = qobject_cast<QQuickWindow *>(qGuiApp->topLevelAt(globalPos));
    if (!window)
        return false;

    QQuickItem *item = mouseAreaForPos(window->contentItem(), globalPos);
    if (!item)
        return false;
    return item->objectName() != QLatin1String("draggableMouseArea");
}

void Platform_qtquick::ungrabMouse()
{
    const QWindowList windows = qGuiApp->topLevelWindows();
    for (QWindow *window : windows) {
        if (auto quickWindow = qobject_cast<QQuickWindow *>(window)) {
            if (QQuickItem *grabber = quickWindow->mouseGrabberItem())
                grabber->ungrabMouse();
        }
    }
}

Controllers::DockWidget *Platform_qtquick::dockWidgetForItem(QQuickItem *item)
{
    if (!item)
        return nullptr;

    if (auto dwView = qobject_cast<Views::DockWidget_qtquick *>(item))
        return dwView->dockWidget();

    if (auto dwi = qobject_cast<DockWidgetInstantiator *>(item))
        if (auto view = dwi->dockWidget())
            return view->dockWidget();

    return nullptr;
}
