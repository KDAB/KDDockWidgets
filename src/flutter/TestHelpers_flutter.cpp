/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "kddockwidgets/KDDockWidgets.h"
#include "Platform_flutter.h"
#include "views/View_flutter.h"
#include "kddockwidgets/controllers/MainWindow.h"

using namespace KDDockWidgets;

#ifdef DOCKS_DEVELOPER_MODE

namespace KDDockWidgets {
class TestView_flutter : public Views::View_flutter
{
public:
    explicit TestView_flutter(CreateViewOptions opts, QWidget *)
        : Views::View_flutter(nullptr, Type::None, nullptr /* TODO parent*/)
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
    CreateViewOptions m_opts;
};

class FocusableTestView_flutter : public Views::View_flutter
{
public:
    explicit FocusableTestView_flutter(CreateViewOptions opts, QWidget *)
        : Views::View_flutter(nullptr, Type::None, nullptr /* TODO parent*/)
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
    CreateViewOptions m_opts;
};

class NonClosableTestView_flutter : public Views::View_flutter
{
public:
    explicit NonClosableTestView_flutter(QWidget *)
        : Views::View_flutter(nullptr, Type::None, nullptr /* TODO parent*/)
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

View *Platform_flutter::tests_createView(CreateViewOptions, View *)
{
    return {};
}

View *Platform_flutter::tests_createFocusableView(CreateViewOptions, View *)
{
    return {};
}

View *Platform_flutter::tests_createNonClosableView(View *)
{
    return {};
}

Controllers::MainWindow *Platform_flutter::createMainWindow(const QString &,
                                                            CreateViewOptions, MainWindowOptions,
                                                            View *, Qt::WindowFlags) const
{
    return {};
}


bool Platform_flutter::tests_waitForWindowActive(std::shared_ptr<Window>, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForResize(View *, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForResize(Controller *, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForEvent(QObject *w, QEvent::Type type, int timeout) const
{
    ( void )w;
    ( void )type;
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForEvent(View *, QEvent::Type type, int timeout) const
{
    ( void )type;
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForEvent(std::shared_ptr<Window>, QEvent::Type type, int timeout) const
{
    ( void )type;
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForDeleted(View *, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_flutter::tests_waitForDeleted(QObject *, int timeout) const
{
    ( void )timeout;
    return false;
}

void Platform_flutter::tests_sendEvent(std::shared_ptr<Window> window, QEvent *ev) const
{
    ( void )window;
    ( void )ev;
}

void Platform_flutter::tests_wait(int ms)
{
    ( void )ms;
}

std::shared_ptr<Window> Platform_flutter::tests_createWindow()
{
    return {};
}

#endif
