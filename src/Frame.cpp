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

#include <QCloseEvent>
#include <QVBoxLayout>

#define MARGIN_THRESHOLD 100

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
    qCDebug(creation) << "Frame";
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
                qWarning() << "dockaWidgetAt" << index << "returned nullptr" << this;
            }
        }
    });

    connect(this, &Frame::currentDockWidgetChanged, m_titleBar, [this] (DockWidget *dock) {
        m_titleBar->setTitle(dock->name());
    });

    m_tabWidget->setTabBarAutoHide(!alwaysShowsTabs());
}

Frame::~Frame()
{
    qCDebug(creation) << "~Frame" << this;
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
    Q_ASSERT(dockWidget);
    if (contains(dockWidget)) {
        qWarning() << "Frame::addWidget dockWidget already exists. this=" << this << "; dockWidget=" << dockWidget;
        return;
    }

    m_tabWidget->insertDockWidget(dockWidget, index);

    if (hasSingleDockWidget()) {
        Q_EMIT currentDockWidgetChanged(dockWidget);
    }
}

void Frame::onDockWidgetCountChanged()
{
    qCDebug(docking) << "Frame::onDockWidgetCountChanged; widgetCount=" << dockWidgetCount();
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
    e->accept();
    DockWidget::List docks = dockWidgets();
    for (DockWidget *dock : docks) // TODO: Ask first if they want to close
        dock->close();
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

DockWidget *Frame::dockWidgetAt(int index) const
{
    return qobject_cast<DockWidget *>(m_tabWidget->widget(index));
}

void Frame::setDropArea(DropArea *dt)
{
    if (dt != m_dropArea) {
        qCDebug(docking) << "Frame::setDropArea dt=" << dt;
        if (m_dropArea)
            disconnect(m_dropArea->multiSplitter(), &MultiSplitterLayout::widgetCountChanged,
                       this, &Frame::updateTitleBarVisibility);

        m_dropArea = dt;

        if (m_dropArea) {
            connect(m_dropArea->multiSplitter(), &MultiSplitterLayout::widgetCountChanged,
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
