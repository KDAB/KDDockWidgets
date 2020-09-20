/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


/**
 * @file
 * @brief The MainWindow base class that's shared between QtWidgets and QtQuick stack
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "MainWindowBase.h"
#include "DockRegistry_p.h"
#include "DropArea_p.h"
#include "Frame_p.h"
#include "Utils_p.h"
#include "SideBar_p.h"
#include "Logging_p.h"
#include "Item_p.h"
#include "FrameworkWidgetFactory.h"
#include "DropAreaWithCentralFrame_p.h"

using namespace KDDockWidgets;

class MainWindowBase::Private
{
public:
    explicit Private(MainWindowBase *mainWindow, MainWindowOptions options)
        : m_options(options)
        , q(mainWindow)
        , m_dropArea(new DropAreaWithCentralFrame(mainWindow, options))
    {
    }

    bool supportsCentralFrame() const
    {
        return m_options & MainWindowOption_HasCentralFrame;
    }

    QRect rectForOverlay(Frame *, SideBarLocation) const;
    SideBarLocation preferredSideBar(DockWidgetBase *) const;
    void updateOverlayGeometry();

    QString name;
    QStringList affinities;
    const MainWindowOptions m_options;
    MainWindowBase *const q;
    QPointer<DockWidgetBase> m_overlayedDockWidget;
    DropAreaWithCentralFrame *const m_dropArea;
};

MainWindowBase::MainWindowBase(const QString &uniqueName, KDDockWidgets::MainWindowOptions options,
                               QWidgetOrQuick *parent, Qt::WindowFlags flags)
    : QMainWindowOrQuick(parent, flags)
    , d(new Private(this, options))
{
    setUniqueName(uniqueName);
}

MainWindowBase::~MainWindowBase()
{
    DockRegistry::self()->unregisterMainWindow(this);
    delete d;
}

void MainWindowBase::addDockWidgetAsTab(DockWidgetBase *widget)
{
    Q_ASSERT(widget);
    qCDebug(addwidget) << Q_FUNC_INFO << widget;

    if (!DockRegistry::self()->affinitiesMatch(d->affinities, widget->affinities())) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock widget with incompatible affinity."
                   << widget->affinities() << affinities();
        return;
    }

    if (widget->options() & DockWidgetBase::Option_NotDockable) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock non-dockable widget" << widget;
        return;
    }

    if (d->supportsCentralFrame()) {
        dropArea()->m_centralFrame->addWidget(widget);
    } else {
        qWarning() << Q_FUNC_INFO << "Not supported without MainWindowOption_HasCentralFrame";
    }
}

void MainWindowBase::addDockWidget(DockWidgetBase *dw, Location location, DockWidgetBase *relativeTo, AddingOption option)
{
    if (dw->options() & DockWidgetBase::Option_NotDockable) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock non-dockable widget" << dw;
        return;
    }

    dropArea()->addDockWidget(dw, location, relativeTo, option);
}

QString MainWindowBase::uniqueName() const
{
    return d->name;
}

MainWindowOptions MainWindowBase::options() const
{
    return d->m_options;
}

DropAreaWithCentralFrame *MainWindowBase::dropArea() const
{
    return d->m_dropArea;
}

MultiSplitter *MainWindowBase::multiSplitter() const
{
    return dropArea();
}

void MainWindowBase::setAffinities(const QStringList &affinityNames)
{
    QStringList affinities = affinityNames;
    affinities.removeAll(QString());

    if (d->affinities == affinities)
        return;

    if (!d->affinities.isEmpty()) {
        qWarning() << Q_FUNC_INFO
                   << "Affinity is already set, refusing to change."
                   << "Submit a feature request with a good justification.";
        return;
    }

    d->affinities = affinities;
}

QStringList MainWindowBase::affinities() const
{
    return d->affinities;
}

void MainWindowBase::layoutEqually()
{
    dropArea()->layoutEqually();
}

void MainWindowBase::layoutParentContainerEqually(DockWidgetBase *dockWidget)
{
    dropArea()->layoutParentContainerEqually(dockWidget);
}

QRect MainWindowBase::Private::rectForOverlay(Frame *frame, SideBarLocation location) const
{
    SideBar *sb = q->sideBar(location);
    if (!sb)
        return {};

    const QWidget *centralWidget = q->centralWidget();
    const QMargins centerWidgetMargins = q->centerWidgetMargins();

    QRect rect;
    const int margin = 1;
    switch (location) {
    case SideBarLocation::North:
    case SideBarLocation::South: {

        SideBar *leftSideBar = q->sideBar(SideBarLocation::West);
        SideBar *rightSideBar = q->sideBar(SideBarLocation::East);
        const int leftSideBarWidth = (leftSideBar && leftSideBar->isVisible()) ? leftSideBar->width()
                                                                               : 0;
        const int rightSideBarWidth = (rightSideBar && rightSideBar->isVisible()) ? rightSideBar->width()
                                                                                  : 0;
        rect.setHeight(qMax(300, frame->minSize().height()));
        rect.setWidth(centralWidget->width() - margin * 2 - leftSideBarWidth - rightSideBarWidth);
        rect.moveLeft(margin + leftSideBarWidth);
        if (location == SideBarLocation::South) {
            rect.moveTop(centralWidget->geometry().bottom() - centerWidgetMargins.bottom() - rect.height() - sb->height());
        } else {
            rect.moveTop(centralWidget->y() + sb->height() + centerWidgetMargins.top());
        }
        break;
    }
    case SideBarLocation::West:
    case SideBarLocation::East: {
        SideBar *topSideBar = q->sideBar(SideBarLocation::North);
        SideBar *bottomSideBar = q->sideBar(SideBarLocation::South);
        const int topSideBarHeight = (topSideBar && topSideBar->isVisible()) ? topSideBar->height()
                                                                             : 0;
        const int bottomSideBarHeight = (bottomSideBar && bottomSideBar->isVisible()) ? bottomSideBar->height()
                                                                                      : 0;
        rect.setWidth(qMax(300, frame->minSize().width()));
        rect.setHeight(centralWidget->height() - topSideBarHeight - bottomSideBarHeight - centerWidgetMargins.top() - centerWidgetMargins.bottom());
        rect.moveTop(sb->mapTo(q, QPoint(0, 0)).y() + topSideBarHeight - 1);
        if (location == SideBarLocation::East) {
            rect.moveLeft(centralWidget->width() - rect.width() - sb->width() - centerWidgetMargins.right() - margin);
        } else {
            rect.moveLeft(margin + centralWidget->x() + centerWidgetMargins.left() + sb->width());
        }

        break;
    }
    case SideBarLocation::None:
        break;
    }

    return rect;
}

SideBarLocation MainWindowBase::Private::preferredSideBar(DockWidgetBase *dw) const
{
    Layouting::Item *item = q->multiSplitter()->itemForFrame(dw->frame());
    if (!item) {
        qWarning() << Q_FUNC_INFO << "No item for dock widget";
        return SideBarLocation::None;
    }

    const Layouting::Item::LayoutBorderLocations borders = item->adjacentLayoutBorders();

    // Simple algorithm for now.
    if (borders & Layouting::Item::LayoutBorderLocation_South)
        return SideBarLocation::South;

    if (borders & Layouting::Item::LayoutBorderLocation_North)
        return SideBarLocation::North;

    return SideBarLocation::South;
}

void MainWindowBase::Private::updateOverlayGeometry()
{
    if (!m_overlayedDockWidget)
        return;

    SideBar *sb = q->sideBarForDockWidget(m_overlayedDockWidget);
    if (!sb) {
        qWarning() << Q_FUNC_INFO << "Expected a sidebar";
        return;
    }

    m_overlayedDockWidget->frame()->QWidgetAdapter::setGeometry(rectForOverlay(m_overlayedDockWidget->frame(), sb->location()));
}

void MainWindowBase::moveToSideBar(DockWidgetBase *dw)
{
    moveToSideBar(dw, d->preferredSideBar(dw));
}

void MainWindowBase::moveToSideBar(DockWidgetBase *dw, SideBarLocation location)
{
    if (SideBar *sb = sideBar(location)) {
        dw->forceClose();
        sb->addDockWidget(dw);
    } else {
        // Shouldn't happen
        qWarning() << Q_FUNC_INFO << "Minimization supported, probably disabled in Config::self().flags()";
    }
}

void MainWindowBase::restoreFromSideBar(DockWidgetBase *dw)
{
    // First un-overlay it, if it's overlayed
    if (dw == d->m_overlayedDockWidget)
        clearSideBarOverlay();

    SideBar *sb = sideBarForDockWidget(dw);
    if (!sb) {
        // Doesn't happen
        qWarning() << Q_FUNC_INFO << "Dock widget isn't in any sidebar";
        return;
    }

    sb->removeDockWidget(dw);
    dw->setFloating(false); // dock it
}

void MainWindowBase::overlayOnSideBar(DockWidgetBase *dw)
{
    if (!dw)
        return;

    const SideBar *sb = sideBarForDockWidget(dw);
    if (sb == nullptr) {
        qWarning() << Q_FUNC_INFO << "You need to add the dock widget to the sidebar before you can overlay it";
        return;
    }

    if (d->m_overlayedDockWidget == dw) {
        // Already overlayed
        return;
    }

    // We only support one overlay at a time, remove any existing overlay
    clearSideBarOverlay();

    auto frame = Config::self().frameworkWidgetFactory()->createFrame(this, FrameOption_IsOverlayed);
    d->m_overlayedDockWidget = dw;
    frame->addWidget(dw);
    d->updateOverlayGeometry();
    frame->QWidgetAdapter::show();

    Q_EMIT dw->isOverlayedChanged(true);
}

void MainWindowBase::toggleOverlayOnSideBar(DockWidgetBase *dw)
{
    const bool wasOverlayed = d->m_overlayedDockWidget == dw;
    clearSideBarOverlay();
    if (!wasOverlayed) {
        overlayOnSideBar(dw);
    }
}

void MainWindowBase::clearSideBarOverlay()
{
    if (!d->m_overlayedDockWidget)
        return;

    Frame *frame = d->m_overlayedDockWidget->frame();
    d->m_overlayedDockWidget->setParent(nullptr);
    Q_EMIT d->m_overlayedDockWidget->isOverlayedChanged(false);
    d->m_overlayedDockWidget = nullptr;
    delete frame;
}

SideBar *MainWindowBase::sideBarForDockWidget(DockWidgetBase *dw) const
{
    for (auto loc : { SideBarLocation::North, SideBarLocation::South,
                      SideBarLocation::East, SideBarLocation::West }) {

        if (SideBar *sb = sideBar(loc)) {
            if (sb->contains(dw))
                return sb;
        }
    }

    return nullptr;
}

DockWidgetBase *MainWindowBase::overlayedDockWidget() const
{
    return d->m_overlayedDockWidget;
}

bool MainWindowBase::sideBarIsVisible(SideBarLocation loc) const
{
    if (SideBar *sb = sideBar(loc))
        return sb->isVisible();

    return false;
}

void MainWindowBase::setUniqueName(const QString &uniqueName)
{
    if (uniqueName.isEmpty())
        return;

    if (d->name.isEmpty()) {
        d->name = uniqueName;
        Q_EMIT uniqueNameChanged();
        DockRegistry::self()->registerMainWindow(this);
    } else {
        qWarning() << Q_FUNC_INFO << "Already has a name." << this->uniqueName() << uniqueName;
    }
}

void MainWindowBase::onResized(QResizeEvent *)
{
    if (d->m_overlayedDockWidget)
        d->updateOverlayGeometry();
}

bool MainWindowBase::deserialize(const LayoutSaver::MainWindow &mw)
{
    if (mw.options != options()) {
        qWarning() << Q_FUNC_INFO << "Refusing to restore MainWindow with different options"
                   << "; expected=" << mw.options << "; has=" << options();
        return false;
    }

    if (d->affinities != mw.affinities) {
        qWarning() << Q_FUNC_INFO << "Affinty name changed from" << d->affinities
                   << "; to" << mw.affinities;

        d->affinities = mw.affinities;
    }

    return dropArea()->deserialize(mw.multiSplitterLayout);
}

LayoutSaver::MainWindow MainWindowBase::serialize() const
{
    LayoutSaver::MainWindow m;

    m.options = options();
    m.geometry = window()->geometry(); // window() as the MainWindow can be embedded
    m.isVisible = isVisible();
    m.uniqueName = uniqueName();
    m.screenIndex = screenNumberForWidget(this);
    m.screenSize = screenSizeForWidget(this);
    m.multiSplitterLayout = dropArea()->serialize();
    m.affinities = d->affinities;

    return m;
}
