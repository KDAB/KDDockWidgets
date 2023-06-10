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
#include "Screen.h"
#include "views/View.h"
#include "core/Platform_p.h"
#include "core/ViewGuard.h"
#include "ViewFactory.h"
#include "Platform.h"
#include "kddockwidgets/core/MainWindow.h"

#include <QMutexLocker>
#include <QMutex>

#include <memory.h>

using namespace KDDockWidgets;
using namespace KDDockWidgets::flutter;

QPoint Platform::s_lastCursorPosition = { -1, -1 };

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
    qWarning() << Q_FUNC_INFO << "Not implemented";
    return {};
}

void Platform::sendEvent(Core::View *, Event *) const
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
}

Platform::~Platform()
{
}

const char *Platform::name() const
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
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
    qWarning() << Q_FUNC_INFO << "Not implemented";
    return {};
}

int Platform::screenNumberFor(Core::View *) const
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
    return -1;
}

int Platform::screenNumberFor(std::shared_ptr<Core::Window>) const
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
    return {};
}

bool Platform::isProcessingAppQuitEvent() const
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
    return {};
}

QString Platform::applicationName() const
{
    // TODOm3
    // qWarning() << Q_FUNC_INFO << "Not implemented";
    return {};
}

void Platform::setMouseCursor(Qt::CursorShape)
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
}

void Platform::restoreMouseCursor()
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
}

Core::Platform::DisplayType Platform::displayType() const
{
    /// TODOm4: Improve this
    return DisplayType::Other;
}

bool Platform::isLeftMouseButtonPressed() const
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
    return {};
}

QSize Platform::screenSizeFor(Core::View *) const
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
    return {};
}

Core::View *Platform::createView(Core::Controller *, Core::View *) const
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
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
    qWarning() << Q_FUNC_INFO << "Not implemented";
}

Core::Screen::List Platform::screens() const
{
    /// TODOm4, find the actual screens
    return { primaryScreen() };
}

Core::Screen::Ptr Platform::primaryScreen() const
{
    return std::make_shared<flutter::Screen>();
}

void Platform::onFloatingWindowCreated(Core::FloatingWindow *)
{
    qWarning() << Q_FUNC_INFO << "Implemented in dart";
}

void Platform::onFloatingWindowDestroyed(Core::FloatingWindow *)
{
    qWarning() << Q_FUNC_INFO << "Implemented in dart";
}

void Platform::onMainWindowCreated(Core::MainWindow *)
{
    qWarning() << Q_FUNC_INFO << "Implemented in dart";
}

void Platform::onMainWindowDestroyed(Core::MainWindow *)
{
    qWarning() << Q_FUNC_INFO << "Implemented in dart";
}

void Platform::onDropIndicatorOverlayCreated(flutter::IndicatorWindow *)
{
    qWarning() << Q_FUNC_INFO << "Implemented in dart";
}

void Platform::onDropIndicatorOverlayDestroyed(flutter::IndicatorWindow *)
{
    qWarning() << Q_FUNC_INFO << "Implemented in dart";
}

void Platform::rebuildWindowOverlay()
{
    qWarning() << Q_FUNC_INFO << "Implemented in dart";
}

void Platform::runDelayed(int, Core::DelayedCall *)
{
    Q_UNREACHABLE(); // Platform.dart gets called instead
}

QPoint Platform::cursorPos() const
{
    return flutter::Platform::s_lastCursorPosition;
}

void Platform::setCursorPos(QPoint)
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
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

Core::View *Platform::tests_createFocusableView(Core::CreateViewOptions opts, Core::View *parent)
{
    // TODOm3: It's not focusable. To fix when we get to those tests
    return tests_createView(opts, parent);
}

Core::View *Platform::tests_createNonClosableView(Core::View *parent)
{
    // TODOm3: It's not non-closable. To fix when we get to those tests
    return tests_createView({ .isVisible = true }, parent);
}

Core::MainWindow *Platform::createMainWindow(const QString &, Core::CreateViewOptions,
                                             MainWindowOptions, Core::View *,
                                             Qt::WindowFlags) const
{
    Q_UNREACHABLE(); // Platform.dart gets called instead
    return {};
}


KDDW_QCORO_TASK Platform::tests_waitForWindowActive(std::shared_ptr<Core::Window>, int) const
{
    co_await m_coRoutines.wait(1000);
    co_return true;
}

KDDW_QCORO_TASK Platform::tests_waitForEvent(QObject *, Event::Type, int) const
{
    co_await m_coRoutines.wait(1000);
    co_return true;
}

KDDW_QCORO_TASK Platform::tests_waitForEvent(Core::View *, Event::Type, int) const
{
    co_await m_coRoutines.wait(1000);
    co_return true;
}

KDDW_QCORO_TASK Platform::tests_waitForEvent(std::shared_ptr<Core::Window>, Event::Type,
                                             int) const
{
    co_await m_coRoutines.wait(1000);
    co_return true;
}

void Platform::tests_sendEvent(std::shared_ptr<Core::Window> window, Event *ev) const
{
    ( void )window;
    ( void )ev;
}


void Platform::tests_doubleClickOn(QPoint, Core::View *)
{
}

void Platform::tests_doubleClickOn(QPoint, std::shared_ptr<Core::Window>)
{
}

void Platform::tests_pressOn(QPoint, Core::View *)
{
}

void Platform::tests_pressOn(QPoint, std::shared_ptr<Core::Window>)
{
}

void Platform::tests_releaseOn(QPoint, Core::View *)
{
}

bool Platform::tests_mouseMove(QPoint, Core::View *)
{
    return true;
}

KDDW_QCORO_TASK Platform::tests_wait(int ms) const
{
    co_await m_coRoutines.wait(ms);
    co_return true;
}

KDDW_QCORO_TASK Platform::tests_waitForResize(Core::View *, int) const
{
    co_await m_coRoutines.wait(1000);
    co_return true;
}

KDDW_QCORO_TASK Platform::tests_waitForResize(Core::Controller *, int) const
{
    co_await m_coRoutines.wait(1000);
    co_return true;
}

KDDW_QCORO_TASK Platform::tests_waitForDeleted(QObject *obj, int) const
{
    if (!obj)
        co_return true;

    QPointer<QObject> guard = obj;
    co_await m_coRoutines.wait(1000);
    co_return guard.isNull();
}

KDDW_QCORO_TASK Platform::tests_waitForDeleted(Core::View *view, int) const
{
    if (!view)
        co_return true;

    Core::ViewGuard guard(view);
    co_await m_coRoutines.wait(1000);
    co_return guard.isNull();
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
