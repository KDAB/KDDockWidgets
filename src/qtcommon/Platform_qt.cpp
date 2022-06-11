/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_qt.h"
#include "KDDockWidgets.h"
#include "Window_qt.h"

#include <QWindow>
#include <QDebug>
#include <QGuiApplication>
#include <QElapsedTimer>
#include <QScreen>

#include <QtTest/QTest>

using namespace KDDockWidgets;

#ifdef DOCKS_DEVELOPER_MODE

namespace KDDockWidgets::Tests {

static QtMessageHandler s_original = nullptr;

static bool shouldBlacklistWarning(const QString &msg, const QString &category)
{
    if (category == QLatin1String("qt.qpa.xcb"))
        return true;

    return msg.contains(QLatin1String("QSocketNotifier: Invalid socket"))
        || msg.contains(QLatin1String("QWindowsWindow::setGeometry"))
        || msg.contains(QLatin1String("This plugin does not support"))
        || msg.contains(QLatin1String("Note that Qt no longer ships fonts"))
        || msg.contains(QLatin1String("Another dock KDDockWidgets::DockWidget"))
        || msg.contains(QLatin1String("There's multiple MainWindows, not sure what to do about parenting"))
        || msg.contains(QLatin1String("Testing::"))
        || msg.contains(QLatin1String("outside any known screen, using primary screen"))
        || msg.contains(QLatin1String("Populating font family aliases took"))

        // Ignore benign warning in Material style when deleting a dock widget. Should be fixed in Qt.
        || (msg.contains(QLatin1String("TypeError: Cannot read property")) && msg.contains(QLatin1String("Material")));
}

static void fatalWarningsMessageHandler(QtMsgType t, const QMessageLogContext &context, const QString &msg)
{
    if (shouldBlacklistWarning(msg, QLatin1String(context.category)))
        return;
    s_original(t, context, msg);

    if (t == QtWarningMsg) {
        if (!Platform::s_expectedWarning.isEmpty() && msg.contains(Platform::s_expectedWarning))
            return;

        if (!Platform_qt::isGammaray() && !qEnvironmentVariableIsSet("NO_FATAL")) {

            if (Platform::s_warningObserver)
                Platform::s_warningObserver->onFatal();

            Platform::instance()->m_numWarningsEmitted++;
            QFAIL("Test caused warning");
        }
    }
}

/// @brief Helper class to help us with tests
class EventFilter : public QObject
{
public:
    EventFilter(QEvent::Type type)
        : m_type(type)
    {
    }
    ~EventFilter() override;
    bool eventFilter(QObject *, QEvent *e) override
    {
        if (e->type() == m_type)
            m_got = true;

        return false;
    }

    const QEvent::Type m_type;
    bool m_got = false;
};

EventFilter::~EventFilter() = default;

}
#endif

Platform_qt::Platform_qt()
{
    if (!qGuiApp)
        qWarning() << "Please call KDDockWidgets::initPlatform() after QGuiApplication";
}

Platform_qt::~Platform_qt()
{
}

std::shared_ptr<ViewWrapper> Platform_qt::focusedView() const
{
    return qobjectAsView(qGuiApp->focusObject());
}

Window::List Platform_qt::windows() const
{
    Window::List windows;
    const auto qtwindows = qGuiApp->topLevelWindows();
    windows.reserve(qtwindows.size());
    for (QWindow *qtwindow : qtwindows) {
        windows << windowFromQWindow(qtwindow);
    }

    return windows;
}

std::shared_ptr<Window> Platform_qt::qobjectAsWindow(QObject *obj) const
{
    if (auto window = qobject_cast<QWindow *>(obj))
        return windowFromQWindow(window);
    return nullptr;
}

int Platform_qt::screenNumberFor(std::shared_ptr<Window> window) const
{
    if (!window)
        return -1;

    return screenNumberForQWindow(static_cast<Window_qt *>(window.get())->qtWindow());
}

int Platform_qt::screenNumberForQWindow(QWindow *window) const
{
    if (QScreen *screen = window->screen()) {
        return qGuiApp->screens().indexOf(screen);
    }

    return -1;
}

void Platform_qt::sendEvent(View *view, QEvent *ev) const
{
    qGuiApp->sendEvent(view->asQObject(), ev);
}

#ifdef DOCKS_DEVELOPER_MODE

bool Platform_qt::tests_waitForWindowActive(Window::Ptr window, int timeout) const
{
    Q_ASSERT(window);
    auto windowqt = static_cast<Window_qt *>(window.get());
    return QTest::qWaitForWindowActive(windowqt->qtWindow(), timeout);
}

bool Platform_qt::tests_waitForEvent(QObject *w, QEvent::Type type, int timeout) const
{
    Tests::EventFilter filter(type);
    w->installEventFilter(&filter);
    QElapsedTimer time;
    time.start();

    while (!filter.m_got && time.elapsed() < timeout) {
        qGuiApp->processEvents();
        QTest::qWait(50);
    }

    return filter.m_got;
}

bool Platform_qt::tests_waitForEvent(View *view, QEvent::Type type, int timeout) const
{
    return tests_waitForEvent(view->asQObject(), type, timeout);
}

bool Platform_qt::tests_waitForResize(View *view, int timeout) const
{
    return tests_waitForEvent(view->asQObject(), QEvent::Resize, timeout);
}

bool Platform_qt::tests_waitForResize(Controller *c, int timeout) const
{
    return tests_waitForResize(c->view(), timeout);
}

bool Platform_qt::tests_waitForEvent(std::shared_ptr<Window> window, QEvent::Type type, int timeout) const
{
    auto windowqt = static_cast<Window_qt *>(window.get());
    return tests_waitForEvent(windowqt->qtWindow(), type, timeout);
}

bool Platform_qt::tests_waitForDeleted(View *view, int timeout) const
{
    QObject *o = view ? view->asQObject() : nullptr;
    if (!o)
        return true;

    QPointer<QObject> ptr = o;
    QElapsedTimer time;
    time.start();

    while (ptr && time.elapsed() < timeout) {
        qGuiApp->processEvents();
        QTest::qWait(50);
    }

    const bool wasDeleted = !ptr;
    return wasDeleted;
}


bool Platform_qt::tests_waitForDeleted(QObject *o, int timeout) const
{
    if (!o)
        return true;

    QPointer<QObject> ptr = o;
    QElapsedTimer time;
    time.start();

    while (ptr && time.elapsed() < timeout) {
        qGuiApp->processEvents();
        QTest::qWait(50);
    }

    const bool wasDeleted = !ptr;
    return wasDeleted;
}

void Platform_qt::tests_sendEvent(Window::Ptr window, QEvent *ev) const
{
    qGuiApp->sendEvent(static_cast<Window_qt *>(window.get())->qtWindow(), ev);
}

void Platform_qt::installMessageHandler()
{
    Tests::s_original = qInstallMessageHandler(Tests::fatalWarningsMessageHandler);
}

void Platform_qt::uninstallMessageHandler()
{
    if (!Tests::s_original)
        qWarning() << Q_FUNC_INFO << "No message handler was installed or the fatalWarningsMessageHandler was already uninstalled!";
    qInstallMessageHandler(Tests::s_original);
    Tests::s_original = nullptr;
}

void Platform_qt::tests_initPlatform_impl()
{
    qGuiApp->setOrganizationName(QStringLiteral("KDAB"));
    qGuiApp->setApplicationName(QStringLiteral("dockwidgets-unit-tests"));
}

void Platform_qt::tests_deinitPlatform_impl()
{
    delete qGuiApp;
}

/*static*/
extern quintptr Q_CORE_EXPORT qtHookData[];
bool Platform_qt::isGammaray()
{
    static bool is = qtHookData[3] != 0;
    return is;
}

Platform_qt::Platform_qt(int &argc, char **argv)
{
    // This CTOR is called before we have a QApplication

    bool qpaPassed = false;
    for (int i = 1; i < argc; ++i) {
        if (qstrcmp(argv[i], "-platform") == 0) {
            qpaPassed = true;
            break;
        }
    }

    if (!qpaPassed) {
        // Use offscreen by default as it's less annoying, doesn't create visible windows
        qputenv("QT_QPA_PLATFORM", "offscreen");
    }
}

void Platform_qt::tests_wait(int ms)
{
    QTest::qWait(ms);
}

#endif
