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

/**
 * @file
 * @brief A DockWidget wrapper that adds a QTabWidget and a TitleBar.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "Frame_p.h"
#include "TitleBar_p.h"
#include "TabWidget_p.h"
#include "DropArea_p.h"
#include "Logging_p.h"
#include "DragController_p.h"
#include "FloatingWindow_p.h"
#include "Utils_p.h"
#include "MainWindow.h"
#include "LastPosition_p.h"

#include <QCloseEvent>
#include <QVBoxLayout>

#define MARGIN_THRESHOLD 100

static int s_dbg_numFrames = 0;

using namespace KDDockWidgets;

static quint64 nextId()
{
    static quint64 id = 0;
    id++;
    return id;
}

Frame::Frame(QWidget *parent, Options options)
    : QWidget(parent)
    , m_tabWidget(new TabWidget(this))
    , m_titleBar(new TitleBar(this))
    , m_options(options)
    , m_id(nextId())
{
    s_dbg_numFrames++;
    qCDebug(creation) << "Frame" << ((void*)this) << s_dbg_numFrames;
    auto vlayout = new QVBoxLayout(this);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_titleBar);
    vlayout->addWidget(m_tabWidget);

    connect(m_tabWidget, &TabWidget::dockWidgetCountChanged, this, &Frame::onDockWidgetCountChanged);
    connect(m_tabWidget, &TabWidget::dockWidgetCountChanged, this, &Frame::numDockWidgetsChanged);

    connect(m_tabWidget, &QTabWidget::currentChanged, this, [this] (int index) {
        if (index != -1) {
            if (auto dock = dockWidgetAt(index)) {
                Q_EMIT currentDockWidgetChanged(dock);
            } else {
                qWarning() << "dockWidgetAt" << index << "returned nullptr" << this;
            }
        }
    });

    connect(this, &Frame::currentDockWidgetChanged, m_titleBar, [this] (DockWidget *dock) {
        m_titleBar->setTitle(dock->title());
        m_titleBar->setIcon(dock->icon());
    });

    m_tabWidget->setTabBarAutoHide(!alwaysShowsTabs());
}

Frame::~Frame()
{
    s_dbg_numFrames--;
    if (m_layoutItem)
        m_layoutItem->unref();

    qCDebug(creation) << "~Frame" << (void*)this;
}

void Frame::addWidget(DockWidget *dockWidget)
{
    insertWidget(dockWidget, m_tabWidget->count()); // append
}

void Frame::addWidget(Frame *frame)
{
    if (frame->isEmpty()) {
        qWarning() << "Frame::addWidget: frame is empty." << frame;
        return;
    }

    const auto &docks = frame->dockWidgets();
    for (DockWidget *dockWidget : docks)
        addWidget(dockWidget);
}

void Frame::addWidget(Draggable *draggable)
{
    QWidget *w = draggable->asWidget();
    Q_ASSERT(w);

    if (auto dock = qobject_cast<DockWidget *>(w)) {
        addWidget(dock);
    } else if (auto fw = qobject_cast<FloatingWindow *>(w)) {
        for (Frame *f : fw->frames())
            addWidget(f);
    } else {
        qWarning() << "Unknown" << w;
        Q_ASSERT(false);
    }
}

void Frame::insertWidget(DockWidget *dockWidget, int index)
{
    qCDebug(addwidget()) << Q_FUNC_INFO << ((void*)this) <<  "; dockWidget=" << dockWidget << "; oldFrame=" << dockWidget->frame();

    Q_ASSERT(dockWidget);
    if (contains(dockWidget)) {
        qWarning() << "Frame::addWidget dockWidget already exists. this=" << this << "; dockWidget=" << dockWidget;
        return;
    }

    if (m_layoutItem)
        dockWidget->addPlaceholderItem(m_layoutItem);

    m_tabWidget->insertDockWidget(dockWidget, index);

    if (hasSingleDockWidget()) {
        Q_EMIT currentDockWidgetChanged(dockWidget);
    }
}

void Frame::removeWidget(DockWidget *dw)
{
    m_tabWidget->removeDockWidget(dw);
}

void Frame::onDockWidgetCountChanged()
{
    qCDebug(docking) << "Frame::onDockWidgetCountChanged:" << this << "; widgetCount=" << dockWidgetCount();
    if (isEmpty() && !isCentralFrame()) {
        qCDebug(creation) << "Frame::onDockWidgetCountChanged: deleteLater on" << this;
        deleteLater();
    } else {
        updateTitleBarVisibility();
    }
}

void Frame::updateTitleBarVisibility()
{
    if (!m_dropArea)
        return;

    if (isCentralFrame()) {
        m_titleBar->setVisible(false);
        return;
    }

    bool visible = false;

    if (m_dropArea->numFrames() > 1) {
        visible = true;
    } else if (m_dropArea->numFrames() == 1) {
        visible = !KDDockWidgets::supportsNativeTitleBar();
    }

    m_titleBar->setVisible(visible);
}

bool Frame::containsMouse(QPoint globalPos) const
{
    return rect().contains(mapFromGlobal(globalPos));
}

TitleBar *Frame::titleBar() const
{
    return m_titleBar;
}

const DockWidget::List Frame::dockWidgets() const
{
    DockWidget::List dockWidgets;
    const int count = dockWidgetCount();
    dockWidgets.reserve(count);
    for (int i = 0, e = count; i != e; ++i) {
        dockWidgets << dockWidgetAt(i);
    }

    return dockWidgets;
}

bool Frame::contains(DockWidget *dockWidget) const
{
    const int count = dockWidgetCount();
    for (int i = 0, e = count; i != e; ++i) {
        if (dockWidget == dockWidgetAt(i))
            return true;
    }
    return false;
}

void Frame::restoreToPreviousPosition()
{
    if (hasSingleDockWidget()) {
        qWarning() << Q_FUNC_INFO << "Invalid usage, there's no tabs";
        return;
    }

    if (!m_layoutItem) {
        qCDebug(placeholder) << Q_FUNC_INFO << "There's no previous position known";
        return;
    }

    if (!m_layoutItem->isPlaceholder()) {
        // Maybe in this case just fold the frame into the placeholder, which probably has other dockwidgets which were added meanwhile. TODO
        qCDebug(placeholder) << Q_FUNC_INFO << "Previous position isn't a placeholder";
        return;
    }

    m_layoutItem->restorePlaceholder(this);
}

QPoint Frame::dragPointForWidget(int index) const
{
    if (hasSingleDockWidget()) {
        Q_ASSERT(index == 0);
        return m_titleBar->mapToGlobal(QPoint(5, 5));
    } else {
        QRect rect = m_tabWidget->tabBar()->tabRect(index);
        return m_tabWidget->tabBar()->mapToGlobal(rect.center());
    }
}

void Frame::closeEvent(QCloseEvent *e)
{
    qCDebug(closing) << "Frame::closeEvent";
    e->accept(); // Accepted by default (will close unless ignored)
    DockWidget::List docks = dockWidgets();
    for (DockWidget *dock : docks) {
        qApp->sendEvent(dock, e);
        if (!e->isAccepted())
            break; // Stop when the first dockwidget prevents closing
    }
}

int Frame::currentTabIndex() const
{
    return m_tabWidget->currentIndex();
}

void Frame::setCurrentTabIndex(int index)
{
    m_tabWidget->setCurrentIndex(index);
}

quint64 Frame::id() const
{
    // The id is simply an helper to coorelate frames when doing save/restore
    return m_id;
}

bool Frame::anyNonClosable() const
{
    for (auto dw : dockWidgets()) {
        if (dw->options() & DockWidget::Option_NotClosable)
            return true;
    }

    return false;
}

void Frame::onDockWidgetShown(DockWidget *w)
{
    if (hasSingleDockWidget() && contains(w)) { // We have to call contains because it might be being in process of being reparented
        if (!isVisible()) {
            qCDebug(hiding) << "Widget" << w << " was shown, we're=" << "; visible=" << isVisible();
            setVisible(true);
        }
    }
}

void Frame::onDockWidgetHidden(DockWidget *w)
{
    if (hasSingleDockWidget() && contains(w)) { // We have to call contains because it might be being in process of being reparented
        if (isVisible()) {
            qCDebug(hiding) << "Widget" << w << " was hidden, we're="
                            << "; visible=" << isVisible()
                            << "; dockWidgets=" << dockWidgets();
            setVisible(false);
        }
    }
}

void Frame::setLayoutItem(Item *item)
{
    if (item == m_layoutItem)
        return;

    if (m_layoutItem)
        m_layoutItem->unref();

    if (item)
        item->ref();

    m_layoutItem = item;
    if (item) {
        for (DockWidget *dw : dockWidgets())
            dw->addPlaceholderItem(item);
    } else {
        for (DockWidget *dw : dockWidgets())
            dw->lastPosition()->removePlaceholders();
    }
}

Item *Frame::layoutItem() const
{
    return m_layoutItem;
}

int Frame::dbg_numFrames()
{
    return s_dbg_numFrames;
}

void Frame::dumpDebug()
{
    qDebug() << "        Frame:" << (void*)this;
    qDebug() << "            layoutItem=" << m_layoutItem << "; num=" << m_tabWidget->count();
    for (auto dw : dockWidgets()) {
        qDebug() << "            dockwidget=" << dw << "; dw->layoutItem=" << dw->lastPosition()->layoutItem();
        dw->lastPosition()->dumpDebug();
    }
}

#ifdef DOCKS_DEVELOPER_MODE
void Frame::paintEvent(QPaintEvent *)
{
    static const bool s_drawDebugTitleFrame = qEnvironmentVariableIsSet("KDDOCKWIDGETS_DRAW_DEBUG_FRAME");
    if (s_drawDebugTitleFrame) {
        QPainter p(this);
        p.drawRect(rect().adjusted(0, 0, -1, -1));
    }
}
#endif

DockWidget *Frame::dockWidgetAt(int index) const
{
    return qobject_cast<DockWidget *>(m_tabWidget->widget(index));
}

void Frame::setDropArea(DropArea *dt)
{
    if (dt != m_dropArea) {
        qCDebug(docking) << "Frame::setDropArea dt=" << dt;
        if (m_dropArea)
            disconnect(m_dropArea->multiSplitter(), &MultiSplitterLayout::visibleWidgetCountChanged,
                       this, &Frame::updateTitleBarVisibility);

        m_dropArea = dt;

        if (m_dropArea) {
            connect(m_dropArea->multiSplitter(), &MultiSplitterLayout::visibleWidgetCountChanged,
                    this, &Frame::updateTitleBarVisibility);
            updateTitleBarVisibility();
        }
    }
}

bool Frame::isTheOnlyFrame() const
{
    qCDebug(docking) << "Frame::isTheOnlyFrame() m_dropArea=" << m_dropArea << "; numFrames"
                     << (m_dropArea ? m_dropArea->numFrames() : 0);
    return m_dropArea && m_dropArea->numFrames() == 1;
}

bool Frame::isFloating() const
{
    if (isInMainWindow())
        return false;

    return isTheOnlyFrame();
}

bool Frame::isInMainWindow() const
{
    return m_dropArea && qobject_cast<MainWindow*>(m_dropArea->parentWidget());
}

int Frame::dockWidgetCount() const
{
    return m_tabWidget->count();
}

bool Frame::event(QEvent *e)
{
    if (e->type() == QEvent::ParentChange) {
        qCDebug(docking) << "Frame: parent changed to =" << parentWidget();
        if (auto dropArea = qobject_cast<DropArea *>(parentWidget())) {
            setDropArea(dropArea);
        } else {
            Q_ASSERT(!parent());
            setDropArea(nullptr);
        }
    }

    return QWidget::event(e);
}
