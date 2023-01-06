/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "kddockwidgets/KDDockWidgets.h"
#include "Platform_dummy.h"
#include "views/View_dummy.h"
#include "kddockwidgets/controllers/MainWindow.h"

using namespace KDDockWidgets;

#ifdef DOCKS_DEVELOPER_MODE

namespace KDDockWidgets {
class TestView_dummy : public Views::View_dummy
{
public:
    explicit TestView_dummy(CreateViewOptions opts, QWidget *)
        : Views::View_dummy(nullptr, Type::None, nullptr /* TODO parent*/)
        , m_opts(opts)
    {
    }

    ~TestView_dummy();

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

class FocusableTestView_dummy : public Views::View_dummy
{
public:
    explicit FocusableTestView_dummy(CreateViewOptions opts, QWidget *)
        : Views::View_dummy(nullptr, Type::None, nullptr /* TODO parent*/)
        , m_opts(opts)
    {
    }

    ~FocusableTestView_dummy();

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

class NonClosableTestView_dummy : public Views::View_dummy
{
public:
    explicit NonClosableTestView_dummy(QWidget *)
        : Views::View_dummy(nullptr, Type::None, nullptr /* TODO parent*/)
    {
    }

    ~NonClosableTestView_dummy();
};

TestView_dummy::~TestView_dummy() = default;
NonClosableTestView_dummy::~NonClosableTestView_dummy() = default;
FocusableTestView_dummy::~FocusableTestView_dummy() = default;

}

Platform_dummy::Platform_dummy(int &, char **)
    : Platform()
{
    init();
}

void Platform_dummy::tests_initPlatform_impl()
{
}

void Platform_dummy::tests_deinitPlatform_impl()
{
}

View *Platform_dummy::tests_createView(CreateViewOptions, View *)
{
    return {};
}

View *Platform_dummy::tests_createFocusableView(CreateViewOptions, View *)
{
    return {};
}

View *Platform_dummy::tests_createNonClosableView(View *)
{
    return {};
}

Controllers::MainWindow *Platform_dummy::createMainWindow(const QString &, CreateViewOptions,
                                                          MainWindowOptions, View *,
                                                          Qt::WindowFlags) const
{
    return {};
}


bool Platform_dummy::tests_waitForWindowActive(std::shared_ptr<Window>, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_dummy::tests_waitForResize(View *, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_dummy::tests_waitForResize(Controller *, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_dummy::tests_waitForEvent(QObject *w, QEvent::Type type, int timeout) const
{
    ( void )w;
    ( void )type;
    ( void )timeout;
    return false;
}

bool Platform_dummy::tests_waitForEvent(View *, QEvent::Type type, int timeout) const
{
    ( void )type;
    ( void )timeout;
    return false;
}

bool Platform_dummy::tests_waitForEvent(std::shared_ptr<Window>, QEvent::Type type,
                                        int timeout) const
{
    ( void )type;
    ( void )timeout;
    return false;
}

bool Platform_dummy::tests_waitForDeleted(View *, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_dummy::tests_waitForDeleted(QObject *, int timeout) const
{
    ( void )timeout;
    return false;
}

void Platform_dummy::tests_sendEvent(std::shared_ptr<Window> window, QEvent *ev) const
{
    ( void )window;
    ( void )ev;
}

void Platform_dummy::tests_wait(int ms)
{
    ( void )ms;
}

std::shared_ptr<Window> Platform_dummy::tests_createWindow()
{
    return {};
}

#endif
