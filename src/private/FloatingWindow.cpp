/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "FloatingWindow_p.h"
#include "MainWindowBase.h"
#include "Logging_p.h"
#include "Frame_p.h"
#include "DropArea_p.h"
#include "TitleBar_p.h"
#include "WindowBeingDragged_p.h"
#include "Utils_p.h"
#include "WidgetResizeHandler_p.h"
#include "DockRegistry_p.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"

#include <QCloseEvent>
#include <QAbstractNativeEventFilter>
#include <QWindow>

#if defined(Q_OS_WIN) && defined(KDDOCKWIDGETS_QTWIDGETS)
# include <Windows.h>
#endif

using namespace KDDockWidgets;

#if defined(Q_OS_WIN) && defined(KDDOCKWIDGETS_QTWIDGETS)
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

FloatingWindow::FloatingWindow(MainWindowBase *parent)
    : QWidgetAdapter(parent, KDDockWidgets::usesNativeDraggingAndResizing() ? Qt::Window : Qt::Tool)
    , Draggable(this, KDDockWidgets::usesNativeDraggingAndResizing()) // FloatingWindow is only draggable when using a native title bar. Otherwise the KDDockWidgets::TitleBar is the draggable
    , m_dropArea(new DropArea(this))
    , m_titleBar(Config::self().frameworkWidgetFactory()->createTitleBar(this))
{
#if defined(Q_OS_WIN) && defined(KDDOCKWIDGETS_QTWIDGETS)
    if (KDDockWidgets::usesAeroSnapWithCustomDecos()) {
        m_nchittestFilter = new NCHITTESTEventFilter(this);
        qApp->installNativeEventFilter(m_nchittestFilter);
    }
#endif

    DockRegistry::self()->registerNestedWindow(this);
    qCDebug(creation) << "FloatingWindow()" << this;

#if defined(Q_OS_WIN) && defined(KDDOCKWIDGETS_QTWIDGETS)
# if QT_VERSION < 0x051000
    // On Windows with Qt 5.9 (and maybe later but we don't care), the WM_NCALCSIZE isn't being processed unless we explicitly create the window.
    // So create it now, otherwise floating dock widgets will show a native title bar until resized.
    create();
# endif
#endif

    maybeCreateResizeHandler();

    updateTitleBarVisibility();
    connect(m_dropArea, &MultiSplitter::visibleWidgetCountChanged, this, &FloatingWindow::onFrameCountChanged);
    connect(m_dropArea, &MultiSplitter::visibleWidgetCountChanged, this, &FloatingWindow::numFramesChanged);
    connect(m_dropArea, &MultiSplitter::visibleWidgetCountChanged, this, &FloatingWindow::onVisibleFrameCountChanged);
    m_layoutDestroyedConnection = connect(m_dropArea, &QObject::destroyed, this, &FloatingWindow::scheduleDeleteLater);
}

static MainWindowBase* hackFindParentHarder(Frame *frame, MainWindowBase *candidateParent)
{
    // TODO: Using a parent helps the floating windows stay in front of the main window always.
    // We're not receiving the parent via ctor argument as the app can have multiple-main windows,
    // so use a hack here.
    // Not quite clear what to do if the app supports multiple main windows though.

    if (candidateParent)
        return candidateParent;

    const MainWindowBase::List windows = DockRegistry::self()->mainwindows();

    if (windows.isEmpty())
        return nullptr;

    if (windows.size() == 1) {
        return windows.first();
    } else {
        const QStringList affinities = frame ? frame->affinities() : QStringList();
        const MainWindowBase::List mainWindows = DockRegistry::self()->mainWindowsWithAffinity(affinities);

        if (mainWindows.isEmpty()) {
            qWarning() << Q_FUNC_INFO << "No window with affinity" << affinities << "found";
            return nullptr;
        } else {
            return mainWindows.first();
        }
    }
}

FloatingWindow::FloatingWindow(Frame *frame, MainWindowBase *parent)
    : FloatingWindow(hackFindParentHarder(frame, parent))
{
    m_disableSetVisible = true;
    // Adding a widget will trigger onFrameCountChanged, which triggers a setVisible(true).
    // The problem with setVisible(true) will forget about or requested geometry and place the window at 0,0
    // So disable the setVisible(true) call while in the ctor.
    m_dropArea->addWidget(frame, KDDockWidgets::Location_OnTop, {});
    m_disableSetVisible = false;
}

FloatingWindow::~FloatingWindow()
{
    m_inDtor = true;
    disconnect(m_layoutDestroyedConnection);
    delete m_nchittestFilter;

    DockRegistry::self()->unregisterNestedWindow(this);
    qCDebug(creation) << "~FloatingWindow";
}

#if defined(Q_OS_WIN) && defined(KDDOCKWIDGETS_QTWIDGETS)
bool FloatingWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if (!m_inDtor && !m_deleteScheduled && KDDockWidgets::usesAeroSnapWithCustomDecos()) {
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
#ifdef KDDOCKWIDGETS_QTWIDGETS
        setWidgetResizeHandler(new WidgetResizeHandler(this));
#endif
    }
}

std::unique_ptr<WindowBeingDragged> FloatingWindow::makeWindow()
{
    return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(this, this));
}

DockWidgetBase *FloatingWindow::singleDockWidget() const
{
    const Frame::List frames = this->frames();
    if (frames.size() == 1) {
        Frame *frame = frames.first();
        if (frame->hasSingleDockWidget())
            return frame->dockWidgetAt(0);
    }

    return nullptr;
}

const Frame::List FloatingWindow::frames() const
{
    Q_ASSERT(m_dropArea);
    return m_dropArea->frames();
}

void FloatingWindow::setSuggestedGeometry(QRect suggestedRect, bool preserveCenter)
{
    const Frame::List frames = this->frames();
    if (frames.size() == 1) {
        // Let's honour max-size when we have a single-frame.
        // multi-frame cases are more complicated and we're not sure if we want the window to bounce around.
        // single-frame is the most common case, like floating a dock widget, so let's do that first, it's also
        // easy.
        Frame *frame = frames[0];
        const QSize waste = (minimumSize() - frame->minSize()).expandedTo(QSize(0, 0));
        const QSize size = (frame->maxSizeHint() + waste).boundedTo(suggestedRect.size());

        // Resize to new size but preserve center
        const QPoint originalCenter = suggestedRect.center();
        suggestedRect.setSize(size);
        if (preserveCenter)
            suggestedRect.moveCenter(originalCenter);
    }

    setGeometry(suggestedRect);
}

void FloatingWindow::scheduleDeleteLater()
{
    m_deleteScheduled = true;
    DockRegistry::self()->unregisterNestedWindow(this);
    deleteLater();
}

MultiSplitter *FloatingWindow::multiSplitter() const
{
    return m_dropArea;
}

bool FloatingWindow::isInDragArea(QPoint globalPoint) const
{
    return dragRect().adjusted(8, 8, 0, 0).contains(globalPoint);
}

bool FloatingWindow::anyNonClosable() const
{
    for (Frame *frame : frames()) {
        if (frame->anyNonClosable())
            return true;
    }
    return false;
}

bool FloatingWindow::anyNonDockable() const
{
    for (Frame *frame : frames()) {
        if (frame->anyNonDockable())
            return true;
    }
    return false;
}

bool FloatingWindow::hasSingleFrame() const
{
    return m_dropArea->numFrames() == 1;
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
    if (m_deleteScheduled)
        return true;

    // TODO: Confusing logic
    for (Frame *f : frames()) {
        if (!f->beingDeletedLater())
            return false;
    }

    return true;
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
        const auto flags = Config::self().flags();
        if ((flags & Config::Flag_HideTitleBarWhenTabsVisible) && !(flags & Config::Flag_AlwaysTitleBarWhenFloating)) {
            if (hasSingleFrame()) {
                visible = !frames().first()->hasTabsVisible();
            }
        }

        for (Frame *frame : frames())
            frame->updateTitleBarVisibility();
    }

    m_titleBar->setVisible(visible);
}

QStringList FloatingWindow::affinities() const
{
    auto frames = this->frames();
    return frames.isEmpty() ? QStringList() : frames.constFirst()->affinities();
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

    if (e->spontaneous() && anyNonClosable()) {
        // Event from the window system won't close us
        e->ignore();
        return;
    }

    e->accept(); // Accepted by default (will close unless ignored)

    const Frame::List frames = this->frames();
    for (Frame *frame : frames) {
        qApp->sendEvent(frame, e);
        if (!e->isAccepted())
            break; // Stop when the first frame prevents closing
    }
}

bool FloatingWindow::deserialize(const LayoutSaver::FloatingWindow &fw)
{
    if (dropArea()->deserialize(fw.multiSplitterLayout)) {
        updateTitleBarVisibility();
        show();
        return true;
    } else {
        return false;
    }
}

LayoutSaver::FloatingWindow FloatingWindow::serialize() const
{
    LayoutSaver::FloatingWindow fw;

    fw.geometry = geometry();
    fw.isVisible = isVisible();
    fw.multiSplitterLayout = dropArea()->serialize();
    fw.screenIndex = screenNumberForWidget(this);
    fw.screenSize = screenSizeForWidget(this);
    fw.affinities = affinities();

    auto mainWindow = qobject_cast<MainWindowBase*>(parentWidget());
    fw.parentIndex = mainWindow ? DockRegistry::self()->mainwindows().indexOf(mainWindow)
                                : -1;
    return fw;
}

QRect FloatingWindow::dragRect() const
{
    QRect rect;
    if (m_titleBar->isVisible()) {
        rect = m_titleBar->rect();
        rect.moveTopLeft(m_titleBar->mapToGlobal(QPoint(0, 0)));
    } else if (hasSingleFrame()) {
        rect = frames().constFirst()->dragRect();
    } else {
        qWarning() << Q_FUNC_INFO << "Expected a title bar";
    }

    return rect;
}

bool FloatingWindow::event(QEvent *ev)
{
    if (ev->type() == QEvent::ActivationChange) {
        // Since QWidget is missing a signal for window activation
        Q_EMIT activatedChanged();
    }

    return QWidgetAdapter::event(ev);
}

