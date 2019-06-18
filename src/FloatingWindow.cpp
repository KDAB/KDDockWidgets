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
#include "multisplitter/MultiSplitter_p.h"
#include "DropArea_p.h"
#include "WindowBeingDragged_p.h"
#include "Utils_p.h"
#include "WidgetResizeHandler_p.h"
#include "DockRegistry_p.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QCloseEvent>
#include <QPainter>

using namespace KDDockWidgets;

FloatingWindow::FloatingWindow(QWidget *parent)
    : QWidget(parent, Qt::Tool)
    , Draggable(this)
    , m_titleBar(new TitleBar(this))
    , m_vlayout(new QVBoxLayout(this))
    , m_dropArea(new DropArea(this))

{
    m_dropArea->setExtraUselessSpace(QSize(0, m_titleBar->height()));

    DockRegistry::self()->registerNestedWindow(this);
    qCDebug(creation) << "FloatingWindow()" << this;

    m_vlayout->setSpacing(0);
    m_vlayout->setContentsMargins(0, 0, 0, 0);
    maybeCreateResizeHandler();
    m_vlayout->addWidget(m_titleBar);
    m_vlayout->addWidget(m_dropArea);

    updateTitleBarVisibility();
    connect(m_dropArea, &MultiSplitter::widgetCountChanged, this, &FloatingWindow::onFrameCountChanged);
    connect(m_dropArea, &MultiSplitter::widgetCountChanged, this, &FloatingWindow::numFramesChanged);
    connect(m_dropArea, &MultiSplitter::visibleWidgetCountChanged, this, &FloatingWindow::onVisibleFrameCountChanged);
}

FloatingWindow::FloatingWindow(Frame *frame, QWidget *parent)
    : FloatingWindow(parent)
{
    m_dropArea->addWidget(frame, KDDockWidgets::Location_OnTop, {});
}

FloatingWindow::~FloatingWindow()
{
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
    e->accept();

    Frame::List frames = this->frames();
    for (Frame *frame : frames) // TODO: First ask if they want to close
        frame->close();
}

void FloatingWindow::paintEvent(QPaintEvent *)
{
    paintFrame(this);
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
    return frame->widgetCount() == 1;
}

void FloatingWindow::onFrameCountChanged(int count)
{
    qCDebug(docking) << "FloatingWindow::onFrameCountChanged" << count;
    if (count == 0) {
        deleteLater();
    } else {
        updateTitleBarVisibility();
    }
}

void FloatingWindow::onVisibleFrameCountChanged(int count)
{
    qCDebug(hiding) << "FloatingWindow::onVisibleFrameCountChanged count=" << count;
    setVisible(count > 0);
}

void FloatingWindow::updateTitleBarVisibility()
{
    m_titleBar->setTitle(windowTitle().isEmpty() ? qApp->applicationName() : windowTitle());
    const bool visible = m_dropArea->numFrames() > 1 && !KDDockWidgets::supportsNativeTitleBar();

    qCDebug(title) << Q_FUNC_INFO << "Setting title visible=" << visible
                   << "; was" << m_titleBar->isVisible();

    m_titleBar->setVisible(visible);
}
