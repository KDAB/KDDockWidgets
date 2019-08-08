/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "FloatingWindow_p.h"
#include "Logging_p.h"
#include "Frame_p.h"
#include "DragController_p.h"
#include "multisplitter/MultiSplitterLayout_p.h"
#include "DropArea_p.h"
#include "WindowBeingDragged_p.h"
#include "Utils_p.h"
#include "WidgetResizeHandler_p.h"
#include "DockRegistry_p.h"
#include "Config.h"

#include <QApplication>
#include <QCloseEvent>
#include <QPainter>
#include <QAbstractNativeEventFilter>
#include <QWindow>

#ifdef Q_OS_WIN
# include <Windows.h>
#endif

static int s_dbg_numFloatingWindows = 0;

using namespace KDDockWidgets;

#ifdef Q_OS_WIN
namespace KDDockWidgets {


/**
 * @brief Helper to rediriect WM_NCHITTEST from child widgets to the top-level widget
 *
 * To implement aero-snap the top-level window must respond to WM_NCHITTEST, we do that
 * in FloatingWindow::nativeEvent(). But if the child widgets have a native handle, then
 * the WM_NCHITTEST will go to them. They have to respond HTTRANSPARENT so the event
 * is redirected.
 */
class NCHITTESTEventFilter : public QAbstractNativeEventFilter
{
public:
    explicit NCHITTESTEventFilter(FloatingWindow *fw) : m_floatingWindow(fw) {}
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override
    {
        if (eventType != "windows_generic_MSG" || !m_floatingWindow)
            return false;

        auto msg = static_cast<MSG *>(message);
        if (msg->message != WM_NCHITTEST)
            return false;
        QWidget *child = QWidget::find(WId(msg->hwnd));
        if (!child || child->window() != m_floatingWindow)
            return false;

        if (child != m_floatingWindow) {
            *result = HTTRANSPARENT;
            return true;
        }

        return false;
    }

    QPointer<FloatingWindow> m_floatingWindow;
};
}
#endif

FloatingWindow::FloatingWindow(QWidgetOrQuick *parent)
    : QWidgetAdapter(parent, KDDockWidgets::usesNativeDraggingAndResizing() ? Qt::Window : Qt::Tool)
    , Draggable(this, KDDockWidgets::usesNativeDraggingAndResizing()) // FloatingWindow is only draggable when using a native title bar. Otherwise the KDDockWidgets::TitleBar is the draggable
    , m_titleBar(Config::self().frameWorkWidgetFactory()->createTitleBar(this))
    , m_dropArea(new DropArea(this))
{
#ifdef Q_OS_WIN
    if (KDDockWidgets::usesAeroSnapWithCustomDecos()) {
        m_nchittestFilter = new NCHITTESTEventFilter(this);
        qApp->installNativeEventFilter(m_nchittestFilter);
    }
#endif

    auto ms = m_dropArea->multiSplitterLayout();

    DockRegistry::self()->registerNestedWindow(this);
    qCDebug(creation) << "FloatingWindow()" << this;


    maybeCreateResizeHandler();

    updateTitleBarVisibility();
    connect(ms, &MultiSplitterLayout::visibleWidgetCountChanged, this, &FloatingWindow::onFrameCountChanged);
    connect(ms, &MultiSplitterLayout::visibleWidgetCountChanged, this, &FloatingWindow::numFramesChanged);
    connect(ms, &MultiSplitterLayout::visibleWidgetCountChanged, this, &FloatingWindow::onVisibleFrameCountChanged);
    m_layoutDestroyedConnection = connect(ms, &MultiSplitterLayout::destroyed, this, &FloatingWindow::scheduleDeleteLater);
}

static QWidgetOrQuick* hackFindParentHarder(QWidgetOrQuick *p)
{
    // TODO: Using a parent helps the floating windows stay in front of the main window always.
    // We're not receiving the parent via ctor argument as the app can have multiple-main windows,
    // so use a hack here.
    // Not quite clear what to do if the app supports multiple main windows though.

    if (p)
        return p;

#ifdef KDDOCKWIDGETS_QTWIDGETS
    const MainWindow::List windows = DockRegistry::self()->mainwindows();

    if (windows.isEmpty())
        return nullptr;
    if (windows.size() == 1)
        return windows.first();
    else {
        qWarning() << Q_FUNC_INFO << "There's multiple MainWindows, not sure what to do about parenting";
        return windows.first();
    }
#else
    qWarning() << "Implement and abstract me!";
#endif
}

FloatingWindow::FloatingWindow(Frame *frame, QWidgetOrQuick *parent)
    : FloatingWindow(hackFindParentHarder(parent))
{
    m_disableSetVisible = true;
    // Adding a widget will trigger onFrameCountChanged, which triggers a setVisible(true).
    // The problem with setVisible(true) will forget about or requested geometry and place the window at 0,0
    // So disable the setVisible(true) call while in the ctor.
    m_dropArea->multiSplitterLayout()->addWidget(frame, KDDockWidgets::Location_OnTop, {});
    m_disableSetVisible = false;
}

FloatingWindow::~FloatingWindow()
{
    disconnect(m_layoutDestroyedConnection);
    delete m_nchittestFilter;

    DockRegistry::self()->unregisterNestedWindow(this);
    qCDebug(creation) << "~FloatingWindow";
}

#if defined(Q_OS_WIN)
bool FloatingWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if (KDDockWidgets::usesAeroSnapWithCustomDecos()) {
        // To enable aero snap we need to tell Windows where's our custom title bar
        if (WidgetResizeHandler::handleWindowsNativeEvent(this, eventType, message, result))
            return true;
    }

    return QWidget::nativeEvent(eventType, message, result);
}
#endif

void FloatingWindow::maybeCreateResizeHandler()
{
    if (!KDDockWidgets::usesNativeDraggingAndResizing()) {
        setFlag(Qt::FramelessWindowHint, true);
        setWidgetResizeHandler(new WidgetResizeHandler(this));
    }
}

std::unique_ptr<WindowBeingDragged> FloatingWindow::makeWindow()
{
    return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(this, this));
}

const Frame::List FloatingWindow::frames() const
{
    return findChildren<Frame *>(QString(), Qt::FindChildrenRecursively);
}

void FloatingWindow::scheduleDeleteLater()
{
    m_beingDeleted = true;
    DockRegistry::self()->unregisterNestedWindow(this);
    deleteLater();
}

MultiSplitterLayout *FloatingWindow::multiSplitterLayout() const
{
    return m_dropArea->multiSplitterLayout();
}

bool FloatingWindow::isInTitleBar(QPoint globalPoint) const
{
    if (KDDockWidgets::usesNativeTitleBar()) {
#ifdef Q_OS_WIN
        WPARAM wparam = 0;
        LPARAM lparam = MAKELPARAM(globalPoint.x(), globalPoint.y());
        auto result = SendMessage(HWND(winId()), WM_NCHITTEST, wparam, lparam);
        return result == HTCAPTION;
#else
        // TODO: Support native title bar on macOS. Just needs a way for us to check that we're in it.
        qFatal("Not implemented on this platform");
#endif
    } else {
        return m_titleBar->rect().adjusted(8, 8, 0, 0).contains(m_titleBar->mapFromGlobal(globalPoint));
    }
}

bool FloatingWindow::anyNonClosable() const
{
    for (Frame *frame : frames()) {
        if (frame->anyNonClosable())
            return true;
    }
    return false;
}

bool FloatingWindow::hasSingleFrame() const
{
    return frames().size() == 1;
}

bool FloatingWindow::hasSingleDockWidget() const
{
    const Frame::List frames = this->frames();
    if (frames.size() != 1)
        return false;

    Frame *frame = frames.first();
    return frame->dockWidgetCount() == 1;
}

bool FloatingWindow::beingDeleted() const
{
    if (m_beingDeleted)
        return true;

    for (Frame *f : frames()) {
        if (!f->beingDeletedLater())
            return false;
    }

    return true;
}

int FloatingWindow::dbg_numFrames()
{
    return s_dbg_numFloatingWindows;
}

void FloatingWindow::onFrameCountChanged(int count)
{
    qCDebug(docking) << "FloatingWindow::onFrameCountChanged" << count;
    if (count == 0) {
        scheduleDeleteLater();
    } else {
        updateTitleBarVisibility();
    }
}

void FloatingWindow::onVisibleFrameCountChanged(int count)
{
    if (!m_disableSetVisible) {
        qCDebug(hiding) << "FloatingWindow::onVisibleFrameCountChanged count=" << count;
        setVisible(count > 0);
    }
}

void FloatingWindow::updateTitleBarVisibility()
{
    updateTitleAndIcon();

    bool visible = true;

    if (KDDockWidgets::usesNativeTitleBar()) {
        visible = false;
    } else {
        if (Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible) {
            if (hasSingleFrame()) {
                visible = !frames().first()->hasTabsVisible();
            }
        }
    }

    m_titleBar->setVisible(visible);
}

void FloatingWindow::updateTitleAndIcon()
{
    QString title;
    QIcon icon;
    if (hasSingleFrame()) {
        const Frame *frame = frames().constFirst();
        title = frame->title();
        icon = frame->icon();
    } else {
        title = qApp->applicationName();
    }
    m_titleBar->setTitle(title);
    m_titleBar->setIcon(icon);

    if (KDDockWidgets::usesNativeTitleBar()) {
        setWindowTitle(title);
        setWindowIcon(icon);
    }
}

void FloatingWindow::onCloseEvent(QCloseEvent *e)
{
    qCDebug(closing) << "Frame::closeEvent";
    e->accept(); // Accepted by default (will close unless ignored)

    Frame::List frames = this->frames();
    for (Frame *frame : frames) {
        qApp->sendEvent(frame, e);
        if (!e->isAccepted())
            break; // Stop when the first frame prevents closing
    }
}

bool FloatingWindow::fillFromDataStream(QDataStream &ds)
{
    if (dropArea()->multiSplitterLayout()->fillFromDataStream(ds)) {
        show();
        return true;
    } else {
        return false;
    }
}

QDataStream &KDDockWidgets::operator<<(QDataStream &ds, FloatingWindow *fw)
{
    ds << fw->dropArea()->multiSplitterLayout();
    return ds;
}
