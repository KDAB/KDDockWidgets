/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_qt.h"
#include "kddockwidgets/qtcommon/Window.h"
#include "qtcommon/View_qt.h"

#include <QString>
#include <QTimer>
#include <QEventLoop>
#include <QWindow>
#include <QGuiApplication>
#include <QElapsedTimer>

using namespace KDDockWidgets;
using namespace KDDockWidgets::qtcommon;

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
        || msg.contains(
            QLatin1String("There's multiple MainWindows, not sure what to do about parenting"))
        || msg.contains(QLatin1String("Testing::"))
        || msg.contains(QLatin1String("outside any known screen, using primary screen"))
        || msg.contains(QLatin1String("Populating font family aliases took"))
        || msg.contains(QLatin1String("QSGThreadedRenderLoop: expose event received for window"))

        // Ignore benign warning in Material style when deleting a dock widget. Should be fixed in
        // Qt.
        || (msg.contains(QLatin1String("TypeError: Cannot read property"))
            && msg.contains(QLatin1String("Material")));
}

static void fatalWarningsMessageHandler(QtMsgType t, const QMessageLogContext &context,
                                        const QString &msg)
{
    if (shouldBlacklistWarning(msg, QLatin1String(context.category)))
        return;
    s_original(t, context, msg);

    if (t == QtWarningMsg) {
        if (!Core::Platform::s_expectedWarning.isEmpty() && msg.contains(Core::Platform::s_expectedWarning))
            return;

        if (!Platform_qt::isGammaray() && !qEnvironmentVariableIsSet("NO_FATAL")) {

            if (Core::Platform::s_warningObserver)
                Core::Platform::s_warningObserver->onFatal();

            Core::Platform::instance()->m_numWarningsEmitted++;
            // We don't link to QTest, so no QFAIL here. Bue will be heard by the CI:
            qFatal("Something is wrong, as KDDW is warnings clean!");
        }
    }
}

static void sleepWithEventLoop(int ms)
{
    if (!ms)
        return;

    QEventLoop loop;
    QTimer::singleShot(ms, &loop, [&loop] {
        loop.exit();
    });
    loop.exec();
}

template<typename Func>
static bool waitFor(Func func, int timeout)
{

    QElapsedTimer timer;
    timer.start();

    while (!func()) {
        if (timer.elapsed() >= timeout)
            return false;

        sleepWithEventLoop(100);
    }

    return true;
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

bool Platform_qt::tests_waitForWindowActive(Core::Window::Ptr window, int timeout) const
{
    Q_ASSERT(window);
    auto windowqt = static_cast<Window *>(window.get());
    QWindow *qwindow = windowqt->qtWindow();

    return Tests::waitFor([qwindow] {
        return qwindow && qwindow->isActive();
    },
                          timeout);
}

bool Platform_qt::tests_waitForEvent(QObject *w, QEvent::Type type, int timeout) const
{
    Tests::EventFilter filter(type);
    w->installEventFilter(&filter);
    QElapsedTimer time;
    time.start();

    while (!filter.m_got && time.elapsed() < timeout) {
        qGuiApp->processEvents();
        Tests::sleepWithEventLoop(50);
    }

    return filter.m_got;
}

bool Platform_qt::tests_waitForEvent(Core::View *view, QEvent::Type type, int timeout) const
{
    return tests_waitForEvent(qtcommon::View_qt::asQObject(view), type, timeout);
}

bool Platform_qt::tests_waitForResize(Core::View *view, int timeout) const
{
    return tests_waitForEvent(qtcommon::View_qt::asQObject(view), QEvent::Resize, timeout);
}

bool Platform_qt::tests_waitForResize(Core::Controller *c, int timeout) const
{
    return tests_waitForResize(c->view(), timeout);
}

bool Platform_qt::tests_waitForEvent(std::shared_ptr<Core::Window> window, QEvent::Type type,
                                     int timeout) const
{
    auto windowqt = static_cast<Window *>(window.get());
    return tests_waitForEvent(windowqt->qtWindow(), type, timeout);
}

bool Platform_qt::tests_waitForDeleted(Core::View *view, int timeout) const
{
    QObject *o = view ? qtcommon::View_qt::asQObject(view) : nullptr;
    if (!o)
        return true;

    QPointer<QObject> ptr = o;
    QElapsedTimer time;
    time.start();

    while (ptr && time.elapsed() < timeout) {
        qGuiApp->processEvents();
        Tests::sleepWithEventLoop(50);
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
        Tests::sleepWithEventLoop(50);
    }

    const bool wasDeleted = !ptr;
    return wasDeleted;
}

void Platform_qt::tests_doubleClickOn(QPoint globalPos, Core::View *receiver)
{
    QCursor::setPos(globalPos);
    tests_pressOn(globalPos, receiver); // double-click involves an initial press

    MouseEvent ev(Event::MouseButtonDblClick, receiver->mapFromGlobal(globalPos),
                  receiver->rootView()->mapFromGlobal(globalPos), globalPos, Qt::LeftButton,
                  Qt::LeftButton, Qt::NoModifier);

    if (auto actualReceiver = receiver->property("titleBarMouseArea").value<QObject *>()) {
        // QtQuick case, we need to send the event to the mouse area
        qGuiApp->sendEvent(actualReceiver, &ev);
    } else {
        // QtWidgets case
        Platform::instance()->sendEvent(receiver, &ev);
    }
}

void Platform_qt::tests_sendEvent(Core::Window::Ptr window, QEvent *ev) const
{
    qGuiApp->sendEvent(static_cast<Window *>(window.get())->qtWindow(), ev);
}

void Platform_qt::installMessageHandler()
{
    Tests::s_original = qInstallMessageHandler(Tests::fatalWarningsMessageHandler);
}

void Platform_qt::uninstallMessageHandler()
{
    if (!Tests::s_original)
        qWarning() << Q_FUNC_INFO
                   << "No message handler was installed or the fatalWarningsMessageHandler was "
                      "already uninstalled!";
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

void Platform_qt::tests_wait(int ms)
{
    Tests::sleepWithEventLoop(ms);
}

void Platform_qt::maybeSetOffscreenQPA(int argc, char **argv)
{
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
