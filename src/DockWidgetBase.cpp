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

#include "DockWidgetBase.h"
#include "DragController_p.h"
#include "Frame_p.h"
#include "FloatingWindow_p.h"
#include "Logging_p.h"
#include "TabWidget_p.h"
#include "Utils_p.h"
#include "DockRegistry_p.h"
#include "WidgetResizeHandler_p.h"
#include "DropArea_p.h"
#include "LastPosition_p.h"
#include "multisplitter/Item_p.h"
#include "DockRegistry_p.h"
#include "Config.h"

#include <QAction>
#include <QEvent>
#include <QSignalBlocker>
#include <QCloseEvent>
#include <QTimer>

/**
 * @file
 * @brief Represents a dock widget.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

using namespace KDDockWidgets;

class DockWidgetBase::Private
{
public:
    Private(const QString &dockName, DockWidgetBase::Options options_, DockWidgetBase *qq)
        : name(dockName)
        , title(dockName)
        , q(qq)
        , options(options_)
        , toggleAction(new QAction(q))
    {
        q->connect(q, &DockWidgetBase::shown, q, [this] { onDockWidgetShown(); } );
        q->connect(q, &DockWidgetBase::hidden, q, [this] { onDockWidgetHidden(); } );

        q->connect(toggleAction, &QAction::toggled, q, [this] (bool enabled) {
            toggle(enabled);
        });

        toggleAction->setCheckable(true);
    }

    void init()
    {
        updateTitle();
    }

    void updateTitle();
    void updateIcon();
    void toggle(bool enabled);
    void updateToggleAction();
    void onDockWidgetShown();
    void onDockWidgetHidden();
    TabWidget *parentTabWidget() const;
    void show();
    void close();
    void restoreToPreviousPosition();
    void maybeRestoreToPreviousPosition();
    int currentTabIndex() const;

    /**
     * Before floating a dock widget we save its position. So it can be restored when calling
     * DockWidget::setFloating(false)
     */
    void saveTabIndex();

    const QString name;
    QString title;
    QIcon icon;
    QWidget *widget = nullptr;
    DockWidgetBase *const q;
    const DockWidgetBase::Options options;
    QAction *const toggleAction;
    LastPosition m_lastPosition;
};

DockWidgetBase::DockWidgetBase(const QString &name, Options options)
    : QWidget(nullptr, Qt::Tool)
    , d(new Private(name, options, this))
{
    d->init();
    DragController::instance();
    DockRegistry::self()->registerDockWidget(this);
    qCDebug(creation) << "DockWidget" << this;

    if (name.isEmpty())
        qWarning() << Q_FUNC_INFO << "Name can't be null";
}

DockWidgetBase::~DockWidgetBase()
{
    DockRegistry::self()->unregisterDockWidget(this);
    qCDebug(creation) << "~DockWidget" << this;
    delete d;
}

void DockWidgetBase::addDockWidgetAsTab(DockWidgetBase *other)
{
    qCDebug(addwidget) << Q_FUNC_INFO << other;
    if (other == this) {
        qWarning() << Q_FUNC_INFO << "Refusing to add dock widget into itself" << other;
        return;
    }

    if (!other) {
        qWarning() << Q_FUNC_INFO << "dock widget is null";
        return;
    }

    Frame *frame = this->frame();

    if (frame) {
        if (frame->contains(other)) {
            qWarning() << Q_FUNC_INFO << "Already contains" << other;
            return;
        }
    } else {
        if (isWindow()) {
            // Doesn't have a frame yet
            morphIntoFloatingWindow();
            frame = this->frame();
        }
    }

    Q_ASSERT(frame);
    frame->addWidget(other);
}

void DockWidgetBase::addDockWidgetToContainingWindow(DockWidgetBase *other, Location location, DockWidgetBase *relativeTo)
{
    qCDebug(addwidget) << Q_FUNC_INFO << other << location << relativeTo;
    if (qobject_cast<MainWindow*>(window())) {
        qWarning() << Q_FUNC_INFO << "Just use MainWindow::addWidget() directly. This function is for floating nested windows only.";
        return;
    }

    if (isWindow())
        morphIntoFloatingWindow();

    if (auto fw = qobject_cast<FloatingWindow *>(window())) {
        fw->dropArea()->addDockWidget(other, location, relativeTo);
    } else {
        qWarning() << Q_FUNC_INFO << "Couldn't find floating nested window";
    }
}

void DockWidgetBase::setWidget(QWidget *w)
{
    Q_ASSERT(w && !d->widget);
    qCDebug(addwidget) << Q_FUNC_INFO << w;

    d->widget = w;
    Q_EMIT widgetChanged(w);
    setWindowTitle(name());
}

QWidget *DockWidgetBase::widget() const
{
    return d->widget;
}

bool DockWidgetBase::isFloating() const
{
    if (isWindow())
        return true;

    auto fw = qobject_cast<FloatingWindow *>(window());
    return fw && fw->hasSingleDockWidget();
}

void DockWidgetBase::setFloating(bool floats)
{
    const bool alreadyFloating = isFloating();

    qCDebug(docking) << Q_FUNC_INFO << "yes=" << floats
                     << "; already floating=" << alreadyFloating;

    if ((floats && alreadyFloating) || (!floats && !alreadyFloating))
        return; // Nothing to do

    if (floats) {
        d->saveTabIndex();
        if (isTabbed()) {
            TabWidget *tabWidget= d->parentTabWidget();
            if (!tabWidget) {
                qWarning() << "DockWidget::setFloating: Tabbed but no tabbar exists"
                           << this;
                Q_ASSERT(false);
            }

            tabWidget->detachTab(this);
        } else {
            frame()->titleBar()->makeWindow();
        }
    } else {
        if (d->m_lastPosition.isValid()) {
            d->restoreToPreviousPosition();
        } else {
            qCDebug(placeholder) << Q_FUNC_INFO << "Don't have a place to restore";
            // TODO: Restore to prefered place ?
        }
    }
}

QAction *DockWidgetBase::toggleAction() const
{
    return d->toggleAction;
}

QString DockWidgetBase::name() const
{
    return d->name;
}

QString DockWidgetBase::title() const
{
    return d->title;
}

void DockWidgetBase::setTitle(const QString &title)
{
    if (title != d->title) {
        d->title = title;
        d->updateTitle();
        Q_EMIT titleChanged();
    }
}

DockWidgetBase::Options DockWidgetBase::options() const
{
    return d->options;
}

bool DockWidgetBase::isTabbed() const
{
    if (TabWidget* tabWidget = d->parentTabWidget()) {
        return frame()->alwaysShowsTabs() || tabWidget->numDockWidgets() > 1;
    } else {
        if (!isFloating())
            qWarning() << "DockWidget::isTabbed() Couldn't find any tab widget.";
        return false;
    }
}

bool DockWidgetBase::isCurrentTab() const
{
    if (TabWidget* tabWidget = d->parentTabWidget()) {
        return tabWidget->currentIndex() == tabWidget->indexOfDockWidget(const_cast<DockWidgetBase*>(this));
    } else {
        return true;
    }
}

void DockWidgetBase::setAsCurrentTab()
{
    if (TabWidget* tabWidget = d->parentTabWidget())
        tabWidget->setCurrentDockWidget(this);
}

void DockWidgetBase::setIcon(const QIcon &icon)
{
    d->icon = icon;
    d->updateIcon();
    Q_EMIT iconChanged();
}

QIcon DockWidgetBase::icon() const
{
    return d->icon;
}

void DockWidgetBase::forceClose()
{
    d->close();
}

FloatingWindow *DockWidgetBase::morphIntoFloatingWindow()
{
    qCDebug(creation) << "DockWidget::morphIntoFloatingWindow() this=" << this
                      << "; visible=" << isVisible();

    if (auto fw = qobject_cast<FloatingWindow*>(window()))
        return fw; // Nothing to do

    if (isWindow()) {
        QRect geo = lastPosition()->lastFloatingGeometry();
        if (geo.isNull())
            geo = geometry();

        auto frame = Config::self().frameWorkWidgetFactory()->createFrame();
        frame->addWidget(this);
        auto floatingWindow = Config::self().frameWorkWidgetFactory()->createFloatingWindow(frame);
        floatingWindow->setGeometry(geo);
        floatingWindow->show();

        return floatingWindow;
    } else {
        return nullptr;
    }
}

void DockWidgetBase::maybeMorphIntoFloatingWindow()
{
    if (isWindow() && isVisible())
        morphIntoFloatingWindow();
}

Frame *DockWidgetBase::frame() const
{
    QWidget *p = parentWidget();
    while (p) {
        if (auto frame = qobject_cast<Frame *>(p))
            return frame;
        p = p->parentWidget();
    }
    return nullptr;
}

FloatingWindow *DockWidgetBase::floatingWindow() const
{
    return qobject_cast<FloatingWindow*>(window());
}

void DockWidgetBase::addPlaceholderItem(Item *item)
{
    qCDebug(placeholder) << Q_FUNC_INFO << this << item;
    Q_ASSERT(item);
    d->m_lastPosition.addPlaceholderItem(item);
}

LastPosition *DockWidgetBase::lastPosition() const
{
    return &d->m_lastPosition;
}

void DockWidgetBase::Private::updateTitle()
{
    if (q->isFloating())
        q->window()->setWindowTitle(title);


    toggleAction->setText(title);
}

void DockWidgetBase::Private::updateIcon()
{

}

void DockWidgetBase::Private::toggle(bool enabled)
{
    if (enabled) {
        show();
    } else {
        q->close();
    }
}

void DockWidgetBase::Private::updateToggleAction()
{
    QSignalBlocker blocker(toggleAction);
    if ((q->isVisible() || parentTabWidget()) && !toggleAction->isChecked()) {
        toggleAction->setChecked(true);
    } else if ((!q->isVisible() && !parentTabWidget()) && toggleAction->isChecked()) {
        toggleAction->setChecked(false);
    }
}

void DockWidgetBase::Private::onDockWidgetShown()
{
    updateToggleAction();
    qCDebug(hiding) << Q_FUNC_INFO << "parent=" << q->parentWidget();
}

void DockWidgetBase::Private::onDockWidgetHidden()
{
    updateToggleAction();
    qCDebug(hiding) << Q_FUNC_INFO << "parent=" << q->parentWidget();
}

TabWidget *DockWidgetBase::Private::parentTabWidget() const
{
    if (auto f = q->frame())
        return f->tabWidget();

    return nullptr;
}

void DockWidgetBase::Private::close()
{
    if (q->isFloating())
        m_lastPosition.setLastFloatingGeometry(q->window()->geometry());

    qCDebug(hiding) << "DockWidget::close" << this;
    saveTabIndex();

    // Do some cleaning. Widget is hidden, but we must hide the tab containing it.
    if (auto tabWidget = parentTabWidget()) {
        tabWidget->removeDockWidget(q);
        q->setParent(nullptr);
    }
}

void DockWidgetBase::Private::restoreToPreviousPosition()
{
    if (!m_lastPosition.isValid()) {
        qWarning() << Q_FUNC_INFO << "Only restoring to MainWindow supported for now";
        return;
    }

    m_lastPosition.layoutItem()->restorePlaceholder(q, m_lastPosition.m_tabIndex);
}

void DockWidgetBase::Private::maybeRestoreToPreviousPosition()
{
    // This is called when we get a QEvent::Show. Let's see if we have to restore it to a previous position.
    Item *layoutItem = m_lastPosition.layoutItem();
    qCDebug(placeholder) << Q_FUNC_INFO << layoutItem << m_lastPosition.m_wasFloating;
    if (!layoutItem)
        return; // nothing to do, no last position

    if (m_lastPosition.m_wasFloating)
        return; // Nothing to do, it was floating before, now it'll just get visible

    Frame *frame = q->frame();

    if (frame && frame->parentWidget() == layoutItem->parentWidget()) {
        // There's a frame already. Means the DockWidget was hidden instead of closed.
        // Nothing to do, the dock widget will simply be shown
        qCDebug(placeholder) << Q_FUNC_INFO << "Already had frame.";
        return;
    }

    // Now we deal with the case where the DockWidget was close()ed. In this case it doesn't have a parent.

    if (q->parentWidget()) {
        // The QEvent::Show is due to it being made floating. Nothing to restore.
        qCDebug(placeholder) << Q_FUNC_INFO << "Already had parentWidget";
        return;
    }

    // Finally, restore it
    restoreToPreviousPosition();
}

int DockWidgetBase::Private::currentTabIndex() const
{
    TabWidget *tabWidget = parentTabWidget();
    return tabWidget ? tabWidget->indexOfDockWidget(q) : 0;
}

void DockWidgetBase::Private::saveTabIndex()
{
    m_lastPosition.m_tabIndex = currentTabIndex();
    m_lastPosition.m_wasFloating = q->isFloating();
}

void DockWidgetBase::Private::show()
{
    // Only show for now
    q->show();
}

void DockWidgetBase::onParentChanged()
{
    Q_EMIT parentChanged();
    d->updateToggleAction();
}

void DockWidgetBase::onShown(bool spontaneous)
{
    Q_EMIT shown();

    if (Frame *f = frame()) {
        if (!spontaneous) {
            f->onDockWidgetShown(this);
        }
    }

    d->maybeRestoreToPreviousPosition();

    // Transform into a FloatingWindow if this will be a regular floating dock widget.
    QTimer::singleShot(0, this, &DockWidgetBase::maybeMorphIntoFloatingWindow);
}

void DockWidgetBase::onHidden(bool spontaneous)
{
    Q_EMIT hidden();

    if (Frame *f = frame()) {
        if (!spontaneous) {
            f->onDockWidgetHidden(this);
        }
    }
}

void DockWidgetBase::onClosed(QCloseEvent *e)
{
    e->accept(); // By default we accept, means DockWidget closes
    if (d->widget)
        qApp->sendEvent(d->widget, e); // Give a change for the widget to ignore

    if (e->isAccepted())
        d->close();
}

DockWidgetBase *DockWidgetBase::createFromDataStream(QDataStream &ds)
{
    QString name;
    ds >> name;

    DockWidgetBase *dw = DockRegistry::self()->dockByName(name);
    if (!dw) {
        if (auto factoryFunc = Config::self().dockWidgetFactoryFunc()) {
            // DockWidget doesn't exist, ask to create it
            dw = factoryFunc(name);
        }
    }

    if (dw) {
        if (QWidget *w = dw->widget())
            w->setVisible(true);
    } else {
        qWarning() << Q_FUNC_INFO << "Couldn't find dock widget" << name;
    }

    return dw;
}

QDataStream &KDDockWidgets::operator<<(QDataStream &ds, DockWidgetBase *dw)
{
    ds << dw->name();
    return ds;
}
