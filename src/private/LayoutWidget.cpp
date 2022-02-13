/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "LayoutSaver_p.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"
#include "MainWindowBase.h"
#include "Position_p.h"
#include "Utils_p.h"

#include "controllers/DockWidget_p.h"
#include "controllers/Frame.h"
#include "controllers/FloatingWindow.h"

#include "views_qtwidgets/Frame_qtwidgets.h"
#include "views_qtwidgets/FloatingWindow_qtwidgets.h"
#include "multisplitter/Item_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;


LayoutWidget::LayoutWidget(QWidgetOrQuick *parent)
    : Views::View_qtwidgets<QWidget>(nullptr, View::Type::Layout, parent)
{
}

LayoutWidget::~LayoutWidget()
{
    m_minSizeChangedHandler.disconnect();

    if (m_rootItem->hostWidget() == this)
        delete m_rootItem;
    DockRegistry::self()->unregisterLayout(this);
}

bool LayoutWidget::isInMainWindow(bool honourNesting) const
{
    return mainWindow(honourNesting) != nullptr;
}

MainWindowBase *LayoutWidget::mainWindow(bool honourNesting) const
{
    // QtQuick doesn't support nesting yet
    honourNesting = honourNesting && kddwUsesQtWidgets();

    if (honourNesting) {
        // This layout might be a MDIArea, nested in DropArea, which is main window.
        return firstParentOfType<MainWindowBase>(this);
    } else {

        if (auto pw = QWidget::parentWidget()) {
            // Note that if pw is a FloatingWindow then pw->parentWidget() can be a MainWindow too, as
            // it's parented
            if (pw->objectName() == QLatin1String("MyCentralWidget"))
                return qobject_cast<MainWindowBase *>(pw->parentWidget());

            if (auto mw = qobject_cast<MainWindowBase *>(pw))
                return mw;
        }
    }

    return nullptr;
}

Controllers::FloatingWindow *LayoutWidget::floatingWindow() const
{
    auto view = qobject_cast<Views::FloatingWindow_qtwidgets *>(QWidget::parentWidget());
    return view ? view->floatingWindow() : nullptr;
}

void LayoutWidget::setRootItem(Layouting::ItemContainer *root)
{
    delete m_rootItem;
    m_rootItem = root;
    m_rootItem->numVisibleItemsChanged.connect([this](int count) {
        Q_EMIT visibleWidgetCountChanged(count);
    });

    m_minSizeChangedHandler = m_rootItem->minSizeChanged.connect([this] { setMinimumSize(layoutMinimumSize()); });
}

QSize LayoutWidget::layoutMinimumSize() const
{
    return m_rootItem->minSize();
}

QSize LayoutWidget::layoutMaximumSizeHint() const
{
    return m_rootItem->maxSizeHint();
}

void LayoutWidget::setLayoutMinimumSize(QSize sz)
{
    if (sz != m_rootItem->minSize()) {
        setLayoutSize(layoutSize().expandedTo(m_rootItem->minSize())); // Increase size in case we need to
        m_rootItem->setMinSize(sz);
    }
}

QSize LayoutWidget::layoutSize() const
{
    return m_rootItem->size();
}

void LayoutWidget::clearLayout()
{
    m_rootItem->clear();
}

bool LayoutWidget::checkSanity() const
{
    return m_rootItem->checkSanity();
}

void LayoutWidget::dumpLayout() const
{
    m_rootItem->dumpLayout();
}

void LayoutWidget::restorePlaceholder(DockWidgetBase *dw, Layouting::Item *item, int tabIndex)
{
    if (item->isPlaceholder()) {
        auto newFrame = new Controllers::Frame(this);
        item->restore(newFrame->view());
    }

    auto frameView = qobject_cast<Views::Frame_qtwidgets *>(item->guestAsQObject());
    auto frame = frameView->frame();
    Q_ASSERT(frame);

    if (tabIndex != -1 && frame->dockWidgetCount() >= tabIndex) {
        frame->insertWidget(dw, tabIndex);
    } else {
        frame->addWidget(dw);
    }

    frame->setVisible(true);
}

void LayoutWidget::unrefOldPlaceholders(const Controllers::Frame::List &framesBeingAdded) const
{
    for (Controllers::Frame *frame : framesBeingAdded) {
        for (DockWidgetBase *dw : frame->dockWidgets()) {
            dw->d->lastPosition()->removePlaceholders(this);
        }
    }
}

void LayoutWidget::setLayoutSize(QSize size)
{
    if (size != layoutSize()) {
        m_rootItem->setSize_recursive(size);
        if (!m_inResizeEvent && !LayoutSaver::restoreInProgress())
            QWidget::resize(size); // TODO: Remove widget references
    }
}

const Layouting::Item::List LayoutWidget::items() const
{
    return m_rootItem->items_recursive();
}

bool LayoutWidget::containsItem(const Layouting::Item *item) const
{
    return m_rootItem->contains_recursive(item);
}

bool LayoutWidget::containsFrame(const Controllers::Frame *frame) const
{
    return itemForFrame(frame) != nullptr;
}

int LayoutWidget::count() const
{
    return m_rootItem->count_recursive();
}

int LayoutWidget::visibleCount() const
{
    return m_rootItem->visibleCount_recursive();
}

int LayoutWidget::placeholderCount() const
{
    return count() - visibleCount();
}

Layouting::Item *LayoutWidget::itemForFrame(const Controllers::Frame *frame) const
{
    if (!frame)
        return nullptr;

    return m_rootItem->itemForWidget(frame->view()); // TODO: layout could have just the controller
}

DockWidgetBase::List LayoutWidget::dockWidgets() const
{
    DockWidgetBase::List dockWidgets;
    const Controllers::Frame::List frames = this->frames();
    for (Controllers::Frame *frame : frames)
        dockWidgets << frame->dockWidgets();

    return dockWidgets;
}

Controllers::Frame::List LayoutWidget::framesFrom(QWidgetOrQuick *frameOrMultiSplitter) const
{
    if (auto frame = qobject_cast<Controllers::Frame *>(frameOrMultiSplitter))
        return { frame };

    if (auto msw = qobject_cast<MultiSplitter *>(frameOrMultiSplitter))
        return msw->frames();

    return {};
}

Controllers::Frame::List LayoutWidget::frames() const
{
    const Layouting::Item::List items = m_rootItem->items_recursive();

    Controllers::Frame::List result;
    result.reserve(items.size());

    for (Layouting::Item *item : items) {
        if (auto frameView = static_cast<Views::Frame_qtwidgets *>(item->guestAsQObject())) // TODO: Store Frame in the layout, not the view
            if (!frameView->freed())
                result.push_back(frameView->frame());
    }

    return result;
}

void LayoutWidget::removeItem(Layouting::Item *item)
{
    if (!item) {
        qWarning() << Q_FUNC_INFO << "nullptr item";
        return;
    }

    item->parentContainer()->removeItem(item);
}

void LayoutWidget::updateSizeConstraints()
{
    const QSize newMinSize = m_rootItem->minSize();
    qCDebug(sizing) << Q_FUNC_INFO << "Updating size constraints from" << minSize() << "to"
                    << newMinSize;

    setLayoutMinimumSize(newMinSize);
}

bool LayoutWidget::deserialize(const LayoutSaver::MultiSplitter &l)
{
    QHash<QString, View *> frames;
    for (const LayoutSaver::Frame &frame : qAsConst(l.frames)) {
        Controllers::Frame *f = Controllers::Frame::deserialize(frame);
        Q_ASSERT(!frame.id.isEmpty());
        frames.insert(frame.id, f->view());
    }

    m_rootItem->fillFromVariantMap(l.layout, frames);

    updateSizeConstraints();

    // This qMin() isn't needed for QtWidgets (but harmless), but it's required for QtQuick
    // as some sizing is async
    const QSize newLayoutSize = View::size().expandedTo(m_rootItem->minSize());

    m_rootItem->setSize_recursive(newLayoutSize);

    return true;
}

void LayoutWidget::onLayoutRequest()
{
    updateSizeConstraints();
}

bool LayoutWidget::onResize(QSize newSize)
{
    QScopedValueRollback<bool> resizeGuard(m_inResizeEvent, true); // to avoid re-entrancy

    if (!LayoutSaver::restoreInProgress()) {
        // don't resize anything while we're restoring the layout
        setLayoutSize(newSize);
    }

    return false; // So QWidget::resizeEvent is called
}

LayoutSaver::MultiSplitter LayoutWidget::serialize() const
{
    LayoutSaver::MultiSplitter l;
    l.layout = m_rootItem->toVariantMap();
    const Layouting::Item::List items = m_rootItem->items_recursive();
    l.frames.reserve(items.size());
    for (Layouting::Item *item : items) {
        if (!item->isContainer()) {
            if (auto frameView = qobject_cast<Views::Frame_qtwidgets *>(item->guestAsQObject()))
                l.frames.insert(frameView->id(), frameView->frame()->serialize());
        }
    }

    return l;
}
