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
#include "TabWidget_p.h"
#include "DropArea_p.h"
#include "Logging_p.h"
#include "DragController_p.h"
#include "FloatingWindow_p.h"
#include "Utils_p.h"
#include "MainWindow.h"
#include "LastPosition_p.h"
#include "DockRegistry_p.h"
#include "Config.h"

#include <QCloseEvent>
#include <QVBoxLayout>

#define MARGIN_THRESHOLD 100

static int s_dbg_numFrames = 0;

using namespace KDDockWidgets;

Frame::Frame(QWidget *parent, Options options)
    : QWidget(parent)
    , m_tabWidget(Config::self().frameWorkWidgetFactory()->createTabWidget(this))
    , m_titleBar(Config::self().frameWorkWidgetFactory()->createTitleBar(this))
    , m_options(options)
{
    s_dbg_numFrames++;
    DockRegistry::self()->registerFrame(this);
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

    connect(this, &Frame::currentDockWidgetChanged, this, &Frame::updateTitleAndIcon);

    m_tabWidget->setTabBarAutoHide(!alwaysShowsTabs());
}

Frame::~Frame()
{
    s_dbg_numFrames--;
    if (m_layoutItem)
        m_layoutItem->unref();

    qCDebug(creation) << "~Frame" << static_cast<void*>(this);
    DockRegistry::self()->unregisterFrame(this);
}

void Frame::updateTitleAndIcon()
{
    if (DockWidgetBase *dw = currentDockWidget()) {
        m_titleBar->setTitle(dw->title());
        m_titleBar->setIcon(dw->icon());

        if (auto fw = floatingWindow()) {
            if (fw->hasSingleFrame()) {
                fw->updateTitleAndIcon();
            }
        }

    } else if (currentTabIndex() != -1) {
        qWarning() << Q_FUNC_INFO << "Invalid dock widget for frame." << currentTabIndex();
    }
}


void Frame::addWidget(DockWidgetBase *dockWidget)
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
    for (DockWidgetBase *dockWidget : docks)
        addWidget(dockWidget);
}

void Frame::addWidget(FloatingWindow *floatingWindow)
{
    Q_ASSERT(floatingWindow);
    for (Frame *f : floatingWindow->frames())
        addWidget(f);
}

void Frame::insertWidget(DockWidgetBase *dockWidget, int index)
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

    connect(dockWidget, &DockWidgetBase::titleChanged, this, &Frame::updateTitleAndIcon);
    connect(dockWidget, &DockWidgetBase::iconChanged, this, &Frame::updateTitleAndIcon);
}

void Frame::removeWidget(DockWidgetBase *dw)
{
    disconnect(dw, &DockWidgetBase::titleChanged, this, &Frame::updateTitleAndIcon);
    disconnect(dw, &DockWidgetBase::iconChanged, this, &Frame::updateTitleAndIcon);
    m_tabWidget->removeDockWidget(dw);
}

void Frame::onDockWidgetCountChanged()
{
    qCDebug(docking) << "Frame::onDockWidgetCountChanged:" << this << "; widgetCount=" << dockWidgetCount();
    if (isEmpty() && !isCentralFrame()) {
        scheduleDeleteLater();
    } else {
        updateTitleBarVisibility();

        // We don't really keep track of the state, so emit even if the visibility didn't change. No biggie.
        if (!(m_options & Option_AlwaysShowsTabs))
            Q_EMIT hasTabsVisibleChanged();
    }
}

void Frame::updateTitleBarVisibility()
{
    if (!m_dropArea)
        return;

    bool visible = false;
    if (isCentralFrame()) {
        visible = false;
    } else if (FloatingWindow *fw = floatingWindow()) {
        // If there's nested frames then show each Frame's title bar
        visible = !fw->hasSingleFrame();
    } else {
        if ((Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible) && hasTabsVisible()) {
            visible = false;
        } else {
            visible = true;
        }
    }

    m_titleBar->setVisible(visible);
    if (auto fw = floatingWindow())
        fw->updateTitleBarVisibility();
}

bool Frame::containsMouse(QPoint globalPos) const
{
    return rect().contains(mapFromGlobal(globalPos));
}

TitleBar *Frame::titleBar() const
{
    return m_titleBar;
}

QString Frame::title() const
{
    return m_titleBar->title();
}

QIcon Frame::icon() const
{
    return m_titleBar->icon();
}

const DockWidgetBase::List Frame::dockWidgets() const
{
    DockWidgetBase::List dockWidgets;
    const int count = dockWidgetCount();
    dockWidgets.reserve(count);
    for (int i = 0, e = count; i != e; ++i) {
        dockWidgets << dockWidgetAt(i);
    }

    return dockWidgets;
}

bool Frame::contains(DockWidgetBase *dockWidget) const
{
    const int count = dockWidgetCount();
    for (int i = 0, e = count; i != e; ++i) {
        if (dockWidget == dockWidgetAt(i))
            return true;
    }
    return false;
}

FloatingWindow *Frame::floatingWindow() const
{
    return qobject_cast<FloatingWindow*>(window());
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
    DockWidgetBase::List docks = dockWidgets();
    for (DockWidgetBase *dock : docks) {
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

DockWidgetBase *Frame::currentDockWidget() const
{
    return qobject_cast<DockWidgetBase*>(m_tabWidget->currentWidget());
}

bool Frame::anyNonClosable() const
{
    for (auto dw : dockWidgets()) {
        if (dw->options() & DockWidgetBase::Option_NotClosable)
            return true;
    }

    return false;
}

void Frame::onDockWidgetShown(DockWidgetBase *w)
{
    if (hasSingleDockWidget() && contains(w)) { // We have to call contains because it might be being in process of being reparented
        if (!isVisible()) {
            qCDebug(hiding) << "Widget" << w << " was shown, we're=" << "; visible=" << isVisible();
            setVisible(true);
        }
    }
}

void Frame::onDockWidgetHidden(DockWidgetBase *w)
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
        for (DockWidgetBase *dw : dockWidgets())
            dw->addPlaceholderItem(item);
    } else {
        for (DockWidgetBase *dw : dockWidgets())
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

bool Frame::beingDeletedLater() const
{
    return m_beingDeleted;
}

TabWidget *Frame::tabWidget() const
{
    return m_tabWidget;
}

TabBar *Frame::tabBar() const
{
    return qobject_cast<TabBar*>(m_tabWidget->tabBar());
}

bool Frame::hasTabsVisible() const
{
    return alwaysShowsTabs() || dockWidgetCount() > 1;
}

DockWidgetBase *Frame::dockWidgetAt(int index) const
{
    return qobject_cast<DockWidgetBase *>(m_tabWidget->widget(index));
}

void Frame::setDropArea(DropArea *dt)
{
    if (dt != m_dropArea) {
        qCDebug(docking) << "Frame::setDropArea dt=" << dt;
        if (m_dropArea)
            disconnect(m_dropArea->multiSplitterLayout(), &MultiSplitterLayout::visibleWidgetCountChanged,
                       this, &Frame::updateTitleBarVisibility);

        m_dropArea = dt;

        if (m_dropArea) {
            connect(m_dropArea->multiSplitterLayout(), &MultiSplitterLayout::visibleWidgetCountChanged,
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

bool Frame::isInFloatingWindow() const
{
    return floatingWindow() != nullptr;
}

bool Frame::isInMainWindow() const
{
    return m_dropArea && m_dropArea->isInMainWindow();
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

Frame *Frame::createFromDataStream(QDataStream &ds)
{
    QString objectName;
    QRect geo;
    int options;
    int currentTabIndex;
    int numDocks;
    ds >> objectName;
    ds >> geo;
    ds >> options;
    ds >> currentTabIndex;
    ds >> numDocks;

    auto frame = Config::self().frameWorkWidgetFactory()->createFrame(/*parent=*/nullptr, Frame::Options(options));
    frame->setObjectName(objectName);

    for (int i = 0; i < numDocks; ++i) {
        if (DockWidgetBase *dw = DockWidgetBase::createFromDataStream(ds)) {
            frame->addWidget(dw);
        }
    }

    frame->setCurrentTabIndex(currentTabIndex);
    frame->setGeometry(geo);

    return frame;
}

QDataStream &KDDockWidgets::operator<<(QDataStream &ds, Frame *frame)
{
    const DockWidgetBase::List docks = frame->dockWidgets();

    ds << frame->objectName();
    ds << frame->geometry();
    ds << frame->options();
    ds << frame->currentTabIndex();
    ds << docks.size();

    for (DockWidgetBase *dock : docks) {
        ds << dock;
    }

    return ds;
}

void Frame::scheduleDeleteLater()
{
    qCDebug(creation) << Q_FUNC_INFO << this;
    m_beingDeleted = true;
    deleteLater();
}

