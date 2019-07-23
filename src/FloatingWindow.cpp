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
#include "TitleBar_p.h"
#include "DragController_p.h"
#include "multisplitter/MultiSplitterLayout_p.h"
#include "DropArea_p.h"
#include "WindowBeingDragged_p.h"
#include "Utils_p.h"
#include "WidgetResizeHandler_p.h"
#include "DockRegistry_p.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QCloseEvent>
#include <QPainter>

static int s_dbg_numFloatingWindows = 0;

using namespace KDDockWidgets;

FloatingWindow::FloatingWindow(QWidget *parent)
    : QWidget(parent, Qt::Tool)
    , Draggable(this)
    , m_titleBar(new TitleBar(this))
    , m_vlayout(new QVBoxLayout(this))
    , m_dropArea(new DropArea(this))
{
    auto ms = m_dropArea->multiSplitterLayout();
    ms->setExtraUselessSpace(QSize(0, m_titleBar->height()));

    DockRegistry::self()->registerNestedWindow(this);
    qCDebug(creation) << "FloatingWindow()" << this;

    m_vlayout->setSpacing(0);
    m_vlayout->setContentsMargins(0, 0, 0, 0);
    maybeCreateResizeHandler();
    m_vlayout->addWidget(m_titleBar);
    m_vlayout->addWidget(m_dropArea);

    updateTitleBarVisibility();
    connect(ms, &MultiSplitterLayout::visibleWidgetCountChanged, this, &FloatingWindow::onFrameCountChanged);
    connect(ms, &MultiSplitterLayout::visibleWidgetCountChanged, this, &FloatingWindow::numFramesChanged);
    connect(ms, &MultiSplitterLayout::visibleWidgetCountChanged, this, &FloatingWindow::onVisibleFrameCountChanged);
    m_layoutDestroyedConnection = connect(ms, &MultiSplitterLayout::destroyed, this, &FloatingWindow::scheduleDeleteLater);
}

static QWidget* hackFindParentHarder(QWidget *p)
{
    // TODO: Using a parent helps the floating windows stay in front of the main window always.
    // We're not receiving the parent via ctor argument as the app can have multiple-main windows,
    // so use a hack here.
    // Not quite clear what to do if the app supports multiple main windows though.

    if (p)
        return p;

    const MainWindow::List windows = DockRegistry::self()->mainwindows();

    if (windows.isEmpty())
        return nullptr;
    if (windows.size() == 1)
        return windows.first();
    else {
        qWarning() << Q_FUNC_INFO << "There's multiple MainWindows, not sure what to do about parenting";
        return windows.first();
    }
}

FloatingWindow::FloatingWindow(Frame *frame, QWidget *parent)
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

    DockRegistry::self()->unregisterNestedWindow(this);
    qCDebug(creation) << "~FloatingWindow";
}

void FloatingWindow::maybeCreateResizeHandler()
{
    if (!KDDockWidgets::supportsNativeTitleBar()) {
        setWindowFlag(Qt::FramelessWindowHint, true);
        setWidgetResizeHandler(new WidgetResizeHandler(this));
        m_vlayout->setContentsMargins(4, 4, 4, 4);
    }
}

std::unique_ptr<WindowBeingDragged> FloatingWindow::makeWindow()
{
    return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(this));
}

const Frame::List FloatingWindow::frames() const
{
    return findChildren<Frame *>(QString(), Qt::FindChildrenRecursively);
}

TitleBar *FloatingWindow::actualTitleBar() const
{
    if (hasSingleFrame())
        return frames().at(0)->titleBar();
    return titleBar();
}

void FloatingWindow::paintFrame(QWidget *w)
{
    QPainter p(w);
    p.setPen(0x666666);
    p.drawRect(w->rect().adjusted(0, 0, -1, -1));
}

void FloatingWindow::closeEvent(QCloseEvent *e)
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

void FloatingWindow::paintEvent(QPaintEvent *)
{
    paintFrame(this);
#ifdef DOCKS_DEVELOPER_MODE
    static const bool s_drawDebugTitleFrame = qEnvironmentVariableIsSet("KDDOCKWIDGETS_DRAW_DEBUG_FRAME");
    if (s_drawDebugTitleFrame) {
        QPainter p(this);
        p.drawRect(rect().adjusted(0, 0, -1, -1));
    }
#endif
}

void FloatingWindow::resizeEvent(QResizeEvent *ev)
{
    QWidget::resizeEvent(ev);
}

void FloatingWindow::scheduleDeleteLater()
{
    m_beingDeleted = true;
    deleteLater();
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
    m_titleBar->setTitle(windowTitle().isEmpty() ? qApp->applicationName() : windowTitle());
    const bool visible = m_dropArea->numFrames() > 1 && !KDDockWidgets::supportsNativeTitleBar();

    qCDebug(title) << Q_FUNC_INFO << "Setting title visible=" << visible
                   << "; was" << m_titleBar->isVisible();

    m_titleBar->setVisible(visible);
}

void FloatingWindow::fillFromDataStream(QDataStream &ds)
{
    dropArea()->multiSplitterLayout()->fillFromDataStream(ds);
    show();
}

QDataStream &KDDockWidgets::operator<<(QDataStream &ds, FloatingWindow *fw)
{
    ds << fw->dropArea()->multiSplitterLayout();
    return ds;
}
