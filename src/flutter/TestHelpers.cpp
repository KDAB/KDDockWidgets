/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "kddockwidgets/KDDockWidgets.h"
#include "Platform.h"
#include "views/View.h"
#include "kddockwidgets/core/MainWindow.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::flutter;

#ifdef DOCKS_DEVELOPER_MODE

namespace KDDockWidgets::flutter {

class TestView_flutter : public flutter::View_flutter
{
public:
    explicit TestView_flutter(Core::CreateViewOptions opts, QWidget *)
        : flutter::View_flutter(nullptr, Core::ViewType::None, nullptr /* TODO parent*/)
        , m_opts(opts)
    {
    }

    ~TestView_flutter();

    QSize sizeHint() const override
    {
        return m_opts.sizeHint;
    }

    QSize maxSizeHint() const override
    {
        return {};
    }

private:
    Core::CreateViewOptions m_opts;
};

class FocusableTestView_flutter : public flutter::View_flutter
{
public:
    explicit FocusableTestView_flutter(Core::CreateViewOptions opts, QWidget *)
        : flutter::View_flutter(nullptr, Core::ViewType::None, nullptr /* TODO parent*/)
        , m_opts(opts)
    {
    }

    ~FocusableTestView_flutter();

    QSize sizeHint() const override
    {
        return m_opts.sizeHint;
    }

    QSize maxSizeHint() const override
    {
        return {};
    }

private:
    Core::CreateViewOptions m_opts;
};

class NonClosableTestView_flutter : public flutter::View_flutter
{
public:
    explicit NonClosableTestView_flutter(QWidget *)
        : flutter::View_flutter(nullptr, Core::ViewType::None, nullptr /* TODO parent*/)
    {
    }

    ~NonClosableTestView_flutter();
};

TestView_flutter::~TestView_flutter() = default;
NonClosableTestView_flutter::~NonClosableTestView_flutter() = default;
FocusableTestView_flutter::~FocusableTestView_flutter() = default;

}

Platform_flutter::Platform_flutter(int &, char **)
    : Platform()
{
    init();
}

void Platform_flutter::tests_initPlatform_impl()
{
}

void Platform_flutter::tests_deinitPlatform_impl()
{
}

Core::View *Platform_flutter::tests_createView(Core::CreateViewOptions, Core::View *)
{
    return {};
}

Core::View *Platform_flutter::tests_createFocusableView(Core::CreateViewOptions, Core::View *)
{
    return {};
}

Core::View *Platform_flutter::tests_createNonClosableView(Core::View *)
{
    return {};
}

Core::MainWindow *Platform_flutter::createMainWindow(const QString &, Core::CreateViewOptions,
                                                     MainWindowOptions, Core::View *,
                                                     Qt::WindowFlags) const
{
    return {};
}


bool Platform_flutter::tests_waitForWindowActive(std::shared_ptr<Core::Window>, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForResize(Core::View *, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForResize(Core::Controller *, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForEvent(QObject *w, Event::Type type, int timeout) const
{
    ( void )w;
    ( void )type;
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForEvent(Core::View *, Event::Type type, int timeout) const
{
    ( void )type;
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForEvent(std::shared_ptr<Core::Window>, Event::Type type,
                                          int timeout) const
{
    ( void )type;
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForDeleted(Core::View *, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForDeleted(QObject *, int timeout) const
{
    ( void )timeout;
    return false;
}

void Platform_flutter::tests_sendEvent(std::shared_ptr<Core::Window> window, Event *ev) const
{
    ( void )window;
    ( void )ev;
}

void Platform_flutter::tests_wait(int ms)
{
    ( void )ms;
}

std::shared_ptr<Core::Window> Platform_flutter::tests_createWindow()
{
    return {};
}

#endif
