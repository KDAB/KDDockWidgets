/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief A widget that supports an arbitrary number of splitters (called Separators) in any
 * combination of vertical/horizontal.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */


#include "MultiSplitter_p.h"
#include "MainWindowBase.h"
#include "FloatingWindow_p.h"
#include "LayoutSaver.h"
#include "Logging_p.h"
#include "Frame_p.h"
#include "DockWidgetBase.h"
#include "Position_p.h"
#include "DockRegistry_p.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"
#include "multisplitter/Widget.h"
#include "DropArea_p.h"
#include "WindowBeingDragged_p.h"

#include <QScopedValueRollback>

using namespace KDDockWidgets;

MultiSplitter::MultiSplitter(QWidgetOrQuick *parent)
    : LayoutGuestWidget(parent)
{
    Q_ASSERT(parent);
    setRootItem(new Layouting::ItemBoxContainer(this));
    DockRegistry::self()->registerLayout(this);

    setLayoutSize(parent->size());

    qCDebug(creation) << "MultiSplitter";

    // Initialize min size
    updateSizeConstraints();

    setMinimumSize(minimumSize());
}

MultiSplitter::~MultiSplitter()
{
    qCDebug(creation) << "~MultiSplitter" << this;
    if (m_rootItem->hostWidget()->asQObject() == this)
        delete m_rootItem;
    DockRegistry::self()->unregisterLayout(this);
}

void MultiSplitter::onLayoutRequest()
{
    updateSizeConstraints();
}

bool MultiSplitter::onResize(QSize newSize)
{
    qCDebug(sizing) << Q_FUNC_INFO << "; new=" << newSize
                    << "; window=" << window();

    QScopedValueRollback<bool> resizeGuard(m_inResizeEvent, true); // to avoid re-entrancy

    if (!LayoutSaver::restoreInProgress()) {
        // don't resize anything while we're restoring the layout
        setLayoutSize(newSize);
    }

    return false; // So QWidget::resizeEvent is called
}

bool MultiSplitter::isInMainWindow() const
{
    return mainWindow() != nullptr;
}

MainWindowBase *MultiSplitter::mainWindow() const
{
    if (auto pw = QWidgetAdapter::parentWidget()) {
        // Note that if pw is a FloatingWindow then pw->parentWidget() can be a MainWindow too, as it's parented
        if (pw->objectName() == QLatin1String("MyCentralWidget"))
            return qobject_cast<MainWindowBase*>(pw->parentWidget());

        if (auto mw = qobject_cast<MainWindowBase*>(pw))
            return mw;
    }

    return nullptr;
}

FloatingWindow *MultiSplitter::floatingWindow() const
{
    return qobject_cast<FloatingWindow*>(QWidgetAdapter::parentWidget());
}

bool MultiSplitter::validateInputs(QWidgetOrQuick *widget,
                                         Location location,
                                         const Frame *relativeToFrame, InitialOption option) const
{
    if (!widget) {
        qWarning() << Q_FUNC_INFO << "Widget is null";
        return false;
    }

    const bool isDockWidget = qobject_cast<DockWidgetBase*>(widget);
    const bool isStartHidden = option.startsHidden();

    if (!qobject_cast<Frame*>(widget) && !qobject_cast<MultiSplitter*>(widget) && !isDockWidget) {
        qWarning() << "Unknown widget type" << widget;
        return false;
    }

    if (isDockWidget != isStartHidden) {
        qWarning() << "Wrong parameters" << isDockWidget << isStartHidden;
        return false;
    }

    if (relativeToFrame && relativeToFrame == widget) {
        qWarning() << "widget can't be relative to itself";
        return false;
    }

    Layouting::Item *item = itemForFrame(qobject_cast<Frame*>(widget));

    if (containsItem(item)) {
        qWarning() << "MultiSplitter::addWidget: Already contains" << widget;
        return false;
    }

    if (location == Location_None) {
        qWarning() << "MultiSplitter::addWidget: not adding to location None";
        return false;
    }

    const bool relativeToThis = relativeToFrame == nullptr;

    Layouting::Item *relativeToItem = itemForFrame(relativeToFrame);
    if (!relativeToThis && !containsItem(relativeToItem)) {
        qWarning() << "MultiSplitter::addWidget: Doesn't contain relativeTo:"
                   << "; relativeToFrame=" << relativeToFrame
                   << "; relativeToItem=" << relativeToItem
                   << "; options=" << option;
        return false;
    }

    return true;
}

void MultiSplitter::addWidget(QWidgetOrQuick *w, Location location,
                              Frame *relativeToWidget,
                              InitialOption option)
{
    auto frame = qobject_cast<Frame*>(w);
    qCDebug(addwidget) << Q_FUNC_INFO << w
                       << "; location=" << locationStr(location)
                       << "; relativeTo=" << relativeToWidget
                       << "; size=" << size()
                       << "; w.size=" << w->size()
                       << "; frame=" << frame
                       << "; options=" << option;

    if (itemForFrame(frame) != nullptr) {
        // Item already exists, remove it.
        // Changing the frame parent will make the item clean itself up. It turns into a placeholder and is removed by unrefOldPlaceholders
        frame->QWidgetAdapter::setParent(nullptr); // so ~Item doesn't delete it
        frame->setLayoutItem(nullptr); // so Item is destroyed, as there's no refs to it
    }

    // Make some sanity checks:
    if (!validateInputs(w, location, relativeToWidget, option))
        return;

    Layouting::Item *relativeTo = itemForFrame(relativeToWidget);
    if (!relativeTo)
        relativeTo = m_rootItem;

    Layouting::Item *newItem = nullptr;

    Frame::List frames = framesFrom(w);
    unrefOldPlaceholders(frames);
    auto dw = qobject_cast<DockWidgetBase*>(w);

    if (frame) {
        newItem = new Layouting::Item(this);
        newItem->setGuestWidget(frame);
    } else if (dw) {
        newItem = new Layouting::Item(this);
        frame = Config::self().frameworkWidgetFactory()->createFrame();
        newItem->setGuestWidget(frame);
        frame->addWidget(dw, option);
    } else if (auto ms = qobject_cast<MultiSplitter*>(w)) {
        newItem = ms->m_rootItem;
        newItem->setHostWidget(this);

        if (FloatingWindow *fw = ms->floatingWindow()) {
            newItem->setSize_recursive(fw->size());
        }

        delete ms;
    } else {
        // This doesn't happen but let's make coverity happy.
        // Tests will fail if this is ever printed.
        qWarning() << Q_FUNC_INFO << "Unknown widget added" << w;
        return;
    }

    Q_ASSERT(!newItem->geometry().isEmpty());
    Layouting::ItemBoxContainer::insertItemRelativeTo(newItem, relativeTo, location, option);

    if (dw && option.startsHidden())
        delete frame;
}

void MultiSplitter::addMultiSplitter(MultiSplitter *sourceMultiSplitter, Location location,
                                     Frame *relativeTo,
                                     InitialOption option)
{
    qCDebug(addwidget) << Q_FUNC_INFO << sourceMultiSplitter << location << relativeTo;
    addWidget(sourceMultiSplitter, location, relativeTo, option);
}

void MultiSplitter::removeItem(Layouting::Item *item)
{
    if (!item) {
        qWarning() << Q_FUNC_INFO << "nullptr item";
        return;
    }

    item->parentContainer()->removeItem(item);
}

bool MultiSplitter::containsItem(const Layouting::Item *item) const
{
    return m_rootItem->contains_recursive(item);
}

bool MultiSplitter::containsFrame(const Frame *frame) const
{
    return itemForFrame(frame) != nullptr;
}

int MultiSplitter::count() const
{
    return m_rootItem->count_recursive();
}

int MultiSplitter::visibleCount() const
{
    return m_rootItem->visibleCount_recursive();
}

int MultiSplitter::placeholderCount() const
{
    return count() - visibleCount();
}

QVector<Layouting::Separator*> MultiSplitter::separators() const
{
    return m_rootItem->separators_recursive();
}

void MultiSplitter::updateSizeConstraints()
{
    const QSize newMinSize = m_rootItem->minSize();
    qCDebug(sizing) << Q_FUNC_INFO << "Updating size constraints from" << minimumSize()
                    << "to" << newMinSize;

    setLayoutMinimumSize(newMinSize);
}

int MultiSplitter::availableLengthForOrientation(Qt::Orientation orientation) const
{
    if (orientation == Qt::Vertical)
        return availableSize().height();
    else
        return availableSize().width();
}

QSize MultiSplitter::availableSize() const
{
    return m_rootItem->availableSize();
}

Layouting::Item *MultiSplitter::itemForFrame(const Frame *frame) const
{
    if (!frame)
        return nullptr;

    return m_rootItem->itemForWidget(frame);
}

DockWidgetBase::List MultiSplitter::dockWidgets() const
{
    DockWidgetBase::List dockWidgets;
    const Frame::List frames = this->frames();
    for (Frame *frame : frames)
        dockWidgets << frame->dockWidgets();

    return dockWidgets;
}

Frame::List MultiSplitter::framesFrom(QWidgetOrQuick *frameOrMultiSplitter) const
{
    if (auto frame = qobject_cast<Frame*>(frameOrMultiSplitter))
        return { frame };

    if (auto msw = qobject_cast<MultiSplitter*>(frameOrMultiSplitter))
        return msw->frames();

    return {};
}

Frame::List MultiSplitter::frames() const
{
    const Layouting::Item::List items = m_rootItem->items_recursive();

    Frame::List result;
    result.reserve(items.size());

    for (Layouting::Item *item : items) {
        if (auto f = static_cast<Frame*>(item->guestAsQObject()))
            result.push_back(f);
    }

    return result;
}

void MultiSplitter::restorePlaceholder(DockWidgetBase *dw, Layouting::Item *item, int tabIndex)
{
    if (item->isPlaceholder()) {
        Frame *newFrame = Config::self().frameworkWidgetFactory()->createFrame(this);
        item->restore(newFrame);
    }

    auto frame = qobject_cast<Frame*>(item->guestAsQObject());
    Q_ASSERT(frame);

    if (tabIndex != -1 && frame->dockWidgetCount() >= tabIndex) {
        frame->insertWidget(dw, tabIndex);
    } else {
        frame->addWidget(dw);
    }

    frame->QWidgetAdapter::setVisible(true);
}

void MultiSplitter::layoutEqually()
{
    layoutEqually(m_rootItem);
}

void MultiSplitter::layoutEqually(Layouting::ItemBoxContainer *container)
{
    if (container) {
        container->layoutEqually_recursive();
    } else {
        qWarning() << Q_FUNC_INFO << "null container";
    }
}

void MultiSplitter::clearLayout()
{
    m_rootItem->clear();
}

bool MultiSplitter::checkSanity() const
{
    return m_rootItem->checkSanity();
}

void MultiSplitter::unrefOldPlaceholders(const Frame::List &framesBeingAdded) const
{
    for (Frame *frame : framesBeingAdded) {
        for (DockWidgetBase *dw : frame->dockWidgets()) {
            dw->lastPositions().removePlaceholders(this);
        }
    }
}

void MultiSplitter::dumpLayout() const
{
    m_rootItem->dumpLayout();
}

void MultiSplitter::setLayoutSize(QSize size)
{
    if (size != this->size()) {
        m_rootItem->setSize_recursive(size);
        if (!m_inResizeEvent && !LayoutSaver::restoreInProgress())
            resize(size);
    }
}

QSize MultiSplitter::layoutMinimumSize() const
{
    return m_rootItem->minSize();
}

QSize MultiSplitter::layoutMaximumSizeHint() const
{
    return m_rootItem->maxSizeHint();
}

QSize MultiSplitter::size() const { return m_rootItem->size(); }

void MultiSplitter::setLayoutMinimumSize(QSize sz)
{
    if (sz != m_rootItem->minSize()) {
        setLayoutSize(size().expandedTo(m_rootItem->minSize())); // Increase size in case we need to
        m_rootItem->setMinSize(sz);
    }

    qCDebug(sizing) << Q_FUNC_INFO << "minSize = " << m_rootItem->minSize();
}

void MultiSplitter::setRootItem(Layouting::ItemBoxContainer *root)
{
    delete m_rootItem;
    m_rootItem = root;
    connect(m_rootItem, &Layouting::ItemBoxContainer::numVisibleItemsChanged,
            this, &MultiSplitter::visibleWidgetCountChanged);
    connect(m_rootItem, &Layouting::ItemBoxContainer::minSizeChanged, this, [this] {
        setMinimumSize(layoutMinimumSize());
    });
}

const Layouting::Item::List MultiSplitter::items() const
{
    return m_rootItem->items_recursive();
}

Layouting::ItemBoxContainer *MultiSplitter::rootItem() const
{
    return m_rootItem;
}

QRect MultiSplitter::rectForDrop(const WindowBeingDragged *wbd, Location location,
                                 const Layouting::Item *relativeTo) const
{
    Layouting::Item item(nullptr);
    if (!wbd)
        return {};

    item.setSize(wbd->size().boundedTo(wbd->maxSize()));
    item.setMinSize(wbd->minSize());
    item.setMaxSizeHint(wbd->maxSize());

    Layouting::ItemBoxContainer *container = relativeTo ? relativeTo->parentBoxContainer()
                                                        : m_rootItem;

    return container->suggestedDropRect(&item, relativeTo, location);
}

bool MultiSplitter::deserialize(const LayoutSaver::MultiSplitter &l)
{
    setRootItem(new Layouting::ItemBoxContainer(this));

    QHash<QString, Layouting::Widget*> frames;
    for (const LayoutSaver::Frame &frame : qAsConst(l.frames)) {
        Frame *f = Frame::deserialize(frame);
        Q_ASSERT(!frame.id.isEmpty());
        frames.insert(frame.id, f);
    }

    m_rootItem->fillFromVariantMap(l.layout, frames);

    updateSizeConstraints();
    m_rootItem->setSize_recursive(QWidgetAdapter::size());

    return true;
}

LayoutSaver::MultiSplitter MultiSplitter::serialize() const
{
    LayoutSaver::MultiSplitter l;
    l.layout = m_rootItem->toVariantMap();
    const Layouting::Item::List items = m_rootItem->items_recursive();
    l.frames.reserve(items.size());
    for (Layouting::Item *item : items) {
        if (!item->isContainer()) {
            if (auto frame = qobject_cast<Frame*>(item->guestAsQObject()))
                l.frames.insert(frame->id(), frame->serialize());
        }
    }

    return l;
}
