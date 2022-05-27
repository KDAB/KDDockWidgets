/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_qtwidgets.h"
#include "KDDockWidgets.h"

#include "Window_qtwidgets.h"
#include "DebugWindow_p.h"
#include "views/ViewWrapper_qtwidgets.h"
#include "views/View_qtwidgets.h"

#include "ViewFactory_qtwidgets.h"
#include "controllers/MainWindow.h"
#include "qtwidgets/views/MainWindow_qtwidgets.h"

#include <QScreen>

#include <memory.h>


using namespace KDDockWidgets;

Platform_qtwidgets::Platform_qtwidgets()
{
    init();
}

void Platform_qtwidgets::init()
{
#if defined(KDDOCKWIDGETS_STATICLIB) || defined(QT_STATIC)
    Q_INIT_RESOURCE(kddockwidgets_resources);
#endif

#ifdef DOCKS_DEVELOPER_MODE
    if (qEnvironmentVariableIntValue("KDDOCKWIDGETS_SHOW_DEBUG_WINDOW") == 1) {
        auto dv = new Debug::DebugWindow();
        dv->show();
    }
#endif

    qApp->connect(qApp, &QGuiApplication::focusObjectChanged, qApp, [this](QObject *obj) {
        ViewWrapper *wrapper = obj ? new Views::ViewWrapper_qtwidgets(obj) : nullptr;
        focusedViewChanged.emit(std::shared_ptr<ViewWrapper>(wrapper));
    });
}

Platform_qtwidgets::~Platform_qtwidgets()
{
}

const char *Platform_qtwidgets::name() const
{
    return "qtwidgets";
}

bool Platform_qtwidgets::hasActivePopup() const
{
    return qApp->activePopupWidget() != nullptr;
}

std::shared_ptr<ViewWrapper> Platform_qtwidgets::qobjectAsView(QObject *obj) const
{
    if (auto w = qobject_cast<QWidget *>(obj)) {
        ViewWrapper *wrapper = new Views::ViewWrapper_qtwidgets(w);
        return std::shared_ptr<ViewWrapper>(wrapper);
    }

    return nullptr;
}

std::shared_ptr<Window> Platform_qtwidgets::windowFromQWindow(QWindow *qwindow) const
{
    return std::shared_ptr<Window>(new Window_qtwidgets(qwindow));
}

ViewFactory *Platform_qtwidgets::createDefaultViewFactory()
{
    return new ViewFactory_qtwidgets();
}

Window::Ptr Platform_qtwidgets::windowAt(QPoint globalPos) const
{
    if (auto qwindow = qApp->QGuiApplication::topLevelAt(globalPos)) {
        auto window = new Window_qtwidgets(qwindow);
        return Window::Ptr(window);
    }

    return {};
}

int Platform_qtwidgets::screenNumberFor(View *view) const
{
    if (auto widget = qobject_cast<QWidget *>(view->asQObject())) {
        if (QWindow *qtwindow = widget->window()->windowHandle())
            return screenNumberForQWindow(qtwindow);
    }

    return -1;
}

QSize Platform_qtwidgets::screenSizeFor(View *view) const
{
    if (auto widget = qobject_cast<QWidget *>(view->asQObject())) {
        if (QScreen *screen = widget->screen()) {
            return screen->size();
        }
    }

    return {};
}

int Platform_qtwidgets::startDragDistance() const
{
    return QApplication::startDragDistance();
}

View *Platform_qtwidgets::createView(View *parent) const
{
    return new Views::View_qtwidgets<QWidget>(nullptr, Type::None, Views::View_qtwidgets<QWidget>::asQWidget(parent));
}

Controllers::MainWindow *Platform_qtwidgets::createMainWindow(const QString &uniqueName,
                                                              CreateViewOptions, MainWindowOptions options,
                                                              View *parent, Qt::WindowFlags flags) const
{
    auto view = new Views::MainWindow_qtwidgets(uniqueName, options,
                                                parent ? static_cast<Views::View_qtwidgets<QMainWindow> *>(parent) : nullptr,
                                                flags);

    return view->mainWindow();
}
