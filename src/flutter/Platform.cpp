/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform.h"
#include "kddockwidgets/KDDockWidgets.h"

#include "Window.h"
#include "views/View.h"
#include "core/Platform_p.h"
#include "ViewFactory.h"
#include "Platform.h"
#include "kddockwidgets/core/MainWindow.h"

#include <QMutexLocker>
#include <QMutex>

#include <memory.h>

using namespace KDDockWidgets;
using namespace KDDockWidgets::flutter;

Platform::Platform()
{
    init();
}

void Platform::init()
{
}

std::shared_ptr<Core::View> Platform::focusedView() const
{
    return m_focusedView;
}

QVector<std::shared_ptr<Core::Window>> Platform::windows() const
{
    return {};
}

void Platform::sendEvent(Core::View *, Event *) const
{
}

Platform::~Platform()
{
}

const char *Platform::name() const
{
    return nullptr;
}

bool Platform::hasActivePopup() const
{
    return false;
}

Core::ViewFactory *Platform::createDefaultViewFactory()
{
    return new ViewFactory();
}

Core::Window::Ptr Platform::windowAt(QPoint) const
{
    return {};
}

int Platform::screenNumberFor(Core::View *) const
{
    return -1;
}

int Platform::screenNumberFor(std::shared_ptr<Core::Window>) const
{
    return {};
}

bool Platform::isProcessingAppQuitEvent() const
{
    return {};
}

QString Platform::applicationName() const
{
    return {};
}

QString Platform::organizationName() const
{
    return {};
}

void Platform::setMouseCursor(Qt::CursorShape)
{
}

void Platform::restoreMouseCursor()
{
}

Core::Platform::DisplayType Platform::displayType() const
{
    return {};
}

bool Platform::isLeftMouseButtonPressed() const
{
    return {};
}

QSize Platform::screenSizeFor(Core::View *) const
{
    return {};
}

Core::View *Platform::createView(Core::Controller *, Core::View *) const
{
    return nullptr;
}

bool Platform::usesFallbackMouseGrabber() const
{
    return false;
}

bool Platform::inDisallowedDragView(QPoint) const
{
    return false;
}

void Platform::ungrabMouse()
{
}

Core::Screen::List Platform::screens() const
{
    return {};
}

Core::Screen::Ptr Platform::primaryScreen() const
{
    return {};
}


void Platform::onFloatingWindowCreated(Core::FloatingWindow *)
{
}

void Platform::onFloatingWindowDestroyed(Core::FloatingWindow *)
{
}

void Platform::onMainWindowCreated(Core::MainWindow *)
{
}

void Platform::onMainWindowDestroyed(Core::MainWindow *)
{
}

void Platform::runDelayed(int, Core::DelayedCall *)
{
    Q_UNREACHABLE(); // Platform.dart gets called instead
}

QPoint Platform::cursorPos() const
{
    return {};
}

void Platform::setCursorPos(QPoint)
{
}


#ifdef DOCKS_DEVELOPER_MODE

void Platform::installMessageHandler()
{
}

void Platform::uninstallMessageHandler()
{
}

void Platform::pauseForDebugger()
{
    pauseForDartDebugger();
}

Platform::RunTestsFunc Platform::s_runTestsFunc = nullptr;

namespace KDDockWidgets::flutter {

class TestView_flutter : public flutter::View
{
public:
    explicit TestView_flutter(Core::CreateViewOptions opts, QWidget *)
        : flutter::View(nullptr, Core::ViewType::None, nullptr /* TODO parent*/)
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

class FocusableTestView_flutter : public flutter::View
{
public:
    explicit FocusableTestView_flutter(Core::CreateViewOptions opts, QWidget *)
        : flutter::View(nullptr, Core::ViewType::None, nullptr /* TODO parent*/)
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

class NonClosableTestView_flutter : public flutter::View
{
public:
    explicit NonClosableTestView_flutter(QWidget *)
        : flutter::View(nullptr, Core::ViewType::None, nullptr /* TODO parent*/)
    {
    }

    ~NonClosableTestView_flutter();
};

TestView_flutter::~TestView_flutter() = default;
NonClosableTestView_flutter::~NonClosableTestView_flutter() = default;
FocusableTestView_flutter::~FocusableTestView_flutter() = default;

}

static QMutex m_mutex;
void Platform::runTests()
{
    // Called from Flutter, so C++ tests run in the ui thread
    Q_ASSERT(s_runTestsFunc);

    // The tests run in a co-routine, meaning they can be interrupted (due to a C++ wait or deleteLater)
    // and the Flutter event loop keeps running. When they are actually finished, the "then()" block is run.
    s_runTestsFunc().then([this](auto result) {
        QMutexLocker locker(&m_mutex);
        Q_ASSERT(!m_testsResult.has_value());
        m_testsResult = result ? 0 : 1;
    });
}

void Platform::maybeResumeCoRoutines()
{
    m_coRoutines.maybeResume();
}

std::optional<int> Platform::testsResult() const
{
    QMutexLocker locker(&m_mutex);
    return m_testsResult;
}

void Platform::tests_initPlatform_impl()
{
}

void Platform::tests_deinitPlatform_impl()
{
}

Core::View *Platform::tests_createView(Core::CreateViewOptions, Core::View *)
{
    Q_UNREACHABLE(); // Platform.dart gets called instead
    return {};
}

Core::View *Platform::tests_createFocusableView(Core::CreateViewOptions, Core::View *)
{
    return {};
}

Core::View *Platform::tests_createNonClosableView(Core::View *)
{
    return {};
}

Core::MainWindow *Platform::createMainWindow(const QString &, Core::CreateViewOptions,
                                             MainWindowOptions, Core::View *,
                                             Qt::WindowFlags) const
{
    Q_UNREACHABLE(); // Platform.dart gets called instead
    return {};
}


bool Platform::tests_waitForWindowActive(std::shared_ptr<Core::Window>, int timeout) const
{
    ( void )timeout;
    return true;
}

bool Platform::tests_waitForResize(Core::View *, int timeout) const
{
    ( void )timeout;
    return true;
}

bool Platform::tests_waitForResize(Core::Controller *, int timeout) const
{
    ( void )timeout;
    return true;
}

bool Platform::tests_waitForEvent(QObject *w, Event::Type type, int timeout) const
{
    ( void )w;
    ( void )type;
    ( void )timeout;
    return true;
}

bool Platform::tests_waitForEvent(Core::View *, Event::Type type, int timeout) const
{
    ( void )type;
    ( void )timeout;
    return true;
}

bool Platform::tests_waitForEvent(std::shared_ptr<Core::Window>, Event::Type type,
                                  int timeout) const
{
    ( void )type;
    ( void )timeout;
    return true;
}

bool Platform::tests_waitForDeleted(Core::View *, int timeout) const
{
    ( void )timeout;
    return true;
}

bool Platform::tests_waitForDeleted(QObject *, int timeout) const
{
    ( void )timeout;
    return true;
}

void Platform::tests_sendEvent(std::shared_ptr<Core::Window> window, Event *ev) const
{
    ( void )window;
    ( void )ev;
}

KDDW_QCORO_TASK Platform::tests_wait(int ms) const
{
    co_await m_coRoutines.wait(ms);
    co_return true;
}

KDDW_QCORO_TASK Platform::tests_waitForResize2(Core::View *, int) const
{
    co_await m_coRoutines.wait(1000);
    co_return true;
}

KDDW_QCORO_TASK Platform::tests_waitForResize2(Core::Controller *, int) const
{
    co_await m_coRoutines.wait(1000);
    co_return true;
}

KDDW_QCORO_TASK Platform::tests_waitForDeleted2(QObject *, int) const
{
    co_await m_coRoutines.wait(1000);
    co_return true;
}

KDDW_QCORO_TASK Platform::tests_waitForDeleted2(Core::View *, int) const
{
    co_await m_coRoutines.wait(1000);
    co_return true;
}

std::shared_ptr<Core::Window> Platform::tests_createWindow()
{
    auto window = new flutter::Window(tests_createView({}, nullptr)->asWrapper());
    return std::shared_ptr<Core::Window>(window);
}

#endif


void Platform::setFocusedView(std::shared_ptr<Core::View> view)
{
    m_focusedView = view;
}
