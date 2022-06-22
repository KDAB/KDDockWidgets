/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "kddockwidgets/KDDockWidgets.h"
#include "Platform_gtk.h"
#include "views/View_gtk.h"
// #include "views/MainWindow_gtk.h"
#include "kddockwidgets/controllers/MainWindow.h"

#include <gtkmm/window.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/button.h>
#include <gtkmm/main.h>

#include <chrono>

using namespace KDDockWidgets;

#ifdef DOCKS_DEVELOPER_MODE

namespace KDDockWidgets {

class TestView_gtk : public Views::View_gtk
{
public:
    explicit TestView_gtk(Platform::CreateViewOptions opts, QWidget *)
        : Views::View_gtk(nullptr, Type::None, nullptr /* TODO parent*/)
        , m_opts(opts)
    {
    }

    ~TestView_gtk();

    QSize sizeHint() const override
    {
        return m_opts.sizeHint;
    }

    QSize maxSizeHint() const override
    {
        return {};
    }

private:
    Platform::CreateViewOptions m_opts;
};

class FocusableTestView_gtk : public Views::View_gtk
{
public:
    explicit FocusableTestView_gtk(Platform::CreateViewOptions opts, QWidget *)
        : Views::View_gtk(nullptr, Type::None, nullptr /* TODO parent*/)
        , m_opts(opts)
    {
    }

    ~FocusableTestView_gtk();

    QSize sizeHint() const override
    {
        return m_opts.sizeHint;
    }

    QSize maxSizeHint() const override
    {
        return {};
    }

private:
    Platform::CreateViewOptions m_opts;
};

class NonClosableTestView_gtk : public Views::View_gtk
{
public:
    explicit NonClosableTestView_gtk(QWidget *)
        : Views::View_gtk(nullptr, Type::None, nullptr /* TODO parent*/)
    {
    }

    ~NonClosableTestView_gtk();
};

TestView_gtk::~TestView_gtk() = default;
NonClosableTestView_gtk::~NonClosableTestView_gtk() = default;
FocusableTestView_gtk::~FocusableTestView_gtk() = default;

}

Platform_gtk::Platform_gtk(int &argc, char **argv)
    : Platform()
{
    m_application = Gtk::Application::create(argc, argv, "com.kdab.kddockwidgets.tests");
    init();
}

void Platform_gtk::tests_initPlatform_impl()
{
}

void Platform_gtk::tests_deinitPlatform_impl()
{
}

View *Platform_gtk::tests_createView(CreateViewOptions, View *)
{

    // GtkWidget *root = gtk_button_new_with_label("button1");

    return {};
}

View *Platform_gtk::tests_createFocusableView(CreateViewOptions, View *)
{
    return {};
}

View *Platform_gtk::tests_createNonClosableView(View *)
{
    return {};
}

Controllers::MainWindow *Platform_gtk::createMainWindow(const QString &,
                                                        CreateViewOptions, MainWindowOptions,
                                                        View *, Qt::WindowFlags) const
{
    return {};
}


bool Platform_gtk::tests_waitForWindowActive(std::shared_ptr<Window>, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_gtk::tests_waitForResize(View *, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_gtk::tests_waitForResize(Controller *, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_gtk::tests_waitForEvent(QObject *w, QEvent::Type type, int timeout) const
{
    ( void )w;
    ( void )type;
    ( void )timeout;
    return false;
}

bool Platform_gtk::tests_waitForEvent(View *, QEvent::Type type, int timeout) const
{
    ( void )type;
    ( void )timeout;
    return false;
}

bool Platform_gtk::tests_waitForEvent(std::shared_ptr<Window>, QEvent::Type type, int timeout) const
{
    ( void )type;
    ( void )timeout;
    return false;
}

bool Platform_gtk::tests_waitForDeleted(View *, int timeout) const
{
    ( void )timeout;
    return false;
}

bool Platform_gtk::tests_waitForDeleted(QObject *, int timeout) const
{
    ( void )timeout;
    return false;
}

void Platform_gtk::tests_sendEvent(std::shared_ptr<Window> window, QEvent *ev) const
{
    ( void )window;
    ( void )ev;
}

void Platform_gtk::tests_wait(int ms)
{
    auto start = std::chrono::steady_clock::now();
    long elapsed = 0;

    while (elapsed < ms) {
        Gtk::Main::iteration();

        const auto end = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
}

bool Platform_gtk::isProcessingAppQuitEvent() const
{
    return {};
}

QString Platform_gtk::applicationName() const
{
    return {};
}

QString Platform_gtk::organizationName() const
{
    return {};
}

void Platform_gtk::setMouseCursor(Qt::CursorShape)
{
}

void Platform_gtk::restoreMouseCursor()
{
}

Platform::DisplayType Platform_gtk::displayType() const
{
    return {};
}

bool Platform_gtk::isLeftMouseButtonPressed() const
{
    return {};
}

#endif
