/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "MultiSplitterLayout_p.h"
#include "Logging_p.h"
#include "MultiSplitter_p.h"
#include "Frame_p.h"
#include "DockWidgetBase.h"
#include "Position_p.h"
#include "DockRegistry_p.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"
#include "LayoutSaver.h"
#include "multisplitter/Widget_qwidget.h"

using namespace KDDockWidgets;

MultiSplitterLayout::MultiSplitterLayout(MultiSplitter *parent)
    : QObject(parent)
    , m_multiSplitter(parent)
{
    Q_ASSERT(parent);
    setRootItem(new Layouting::ItemContainer(m_multiSplitter));
    DockRegistry::self()->registerLayout(this);

    setSize(parent->QWidget::size());

    qCDebug(multisplittercreation()) << "MultiSplitter";

    // Initialize min size
    updateSizeConstraints();
}

MultiSplitterLayout::~MultiSplitterLayout()
{
    qCDebug(multisplittercreation) << "~MultiSplitter" << this;
    if (m_rootItem->hostWidget()->asQObject() == multiSplitter())
        delete m_rootItem;
    DockRegistry::self()->unregisterLayout(this);
}

MultiSplitter *MultiSplitterLayout::multiSplitter() const
{
    return m_multiSplitter;
}

bool MultiSplitterLayout::validateInputs(QWidgetOrQuick *widget,
                                         Location location,
                                         const Frame *relativeToFrame, AddingOption option) const
{
    if (!widget) {
        qWarning() << Q_FUNC_INFO << "Widget is null";
        return false;
    }

    const bool isDockWidget = qobject_cast<DockWidgetBase*>(widget);
    const bool isStartHidden = option & AddingOption_StartHidden;

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

    if (contains(item)) {
        qWarning() << "MultiSplitterLayout::addWidget: Already contains" << widget;
        return false;
    }

    if (location == Location_None) {
        qWarning() << "MultiSplitterLayout::addWidget: not adding to location None";
        return false;
    }

    const bool relativeToThis = relativeToFrame == nullptr;

    Layouting::Item *relativeToItem = itemForFrame(relativeToFrame);
    if (!relativeToThis && !contains(relativeToItem)) {
        qWarning() << "MultiSplitterLayout::addWidget: Doesn't contain relativeTo:"
                   << "; relativeToFrame=" << relativeToFrame
                   << "; relativeToItem=" << relativeToItem
                   << "; options=" << option;
        return false;
    }

    return true;
}

void MultiSplitterLayout::addWidget(QWidgetOrQuick *w, Location location,
                                    Frame *relativeToWidget, DefaultSizeMode defaultSizeMode,
                                    AddingOption option)
{
    auto frame = qobject_cast<Frame*>(w);
    qCDebug(addwidget) << Q_FUNC_INFO << w
                       << "; location=" << locationStr(location)
                       << "; relativeTo=" << relativeToWidget
                       << "; size=" << size()
                       << "; w.size=" << w->size()
                       << "; frame=" << frame
                       << "; option=" << option;

    if (itemForFrame(frame) != nullptr) {
        // Item already exists, remove it.
        // Changing the frame parent will make the item clean itself up. It turns into a placeholder and is removed by unrefOldPlaceholders
        frame->QWidget::setParent(nullptr); // so ~Item doesn't delete it
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
        newItem = new Layouting::Item(m_multiSplitter);
        newItem->setGuest(frame);
    } else if (dw) {
        newItem = new Layouting::Item(m_multiSplitter);
        frame = new Frame();
        newItem->setGuest(frame);
        frame->addWidget(dw, option);
    } else if (auto ms = qobject_cast<MultiSplitter*>(w)) {
        newItem = ms->multiSplitterLayout()->rootItem();
        Q_ASSERT(newItem->hostWidget()->asQWidget() != multiSplitter());
        newItem->setHostWidget(m_multiSplitter);
        delete ms;
    }

    Q_ASSERT(!newItem->geometry().isEmpty());
    relativeTo->insertItem(newItem, Layouting::Item::Location(location),
                           Layouting::Item::DefaultSizeMode(defaultSizeMode), Layouting::Item::AddingOption(option));

    if (dw && option && AddingOption_StartHidden)
        delete frame;
}

void MultiSplitterLayout::addMultiSplitter(MultiSplitter *sourceMultiSplitter,
                                           Location location,
                                           Frame *relativeTo)
{
    qCDebug(addwidget) << Q_FUNC_INFO << sourceMultiSplitter << location << relativeTo;
    addWidget(sourceMultiSplitter, location, relativeTo);
}

void MultiSplitterLayout::removeItem(Layouting::Item *item)
{
    if (!item)
        qWarning() << Q_FUNC_INFO << "nullptr item";

    if (!item)
        return;

    item->parentContainer()->removeItem(item);
}

bool MultiSplitterLayout::contains(const Layouting::Item *item) const
{
    return m_rootItem->contains_recursive(item);
}

bool MultiSplitterLayout::contains(const Frame *frame) const
{
    return itemForFrame(frame) != nullptr;
}

int MultiSplitterLayout::count() const
{
    return m_rootItem->count_recursive();
}

int MultiSplitterLayout::visibleCount() const
{
    return m_rootItem->visibleCount_recursive();
}

int MultiSplitterLayout::placeholderCount() const
{
    return count() - visibleCount();
}

Layouting::Separator::List MultiSplitterLayout::separators() const
{
    return m_rootItem->separators_recursive();
}

void MultiSplitterLayout::updateSizeConstraints()
{
    const QSize newMinSize = m_rootItem->minSize();
    qCDebug(sizing) << Q_FUNC_INFO << "Updating size constraints from" << minimumSize()
                    << "to" << newMinSize;

    setMinimumSize(newMinSize);
}

int MultiSplitterLayout::availableLengthForOrientation(Qt::Orientation orientation) const
{
    if (orientation == Qt::Vertical)
        return availableSize().height();
    else
        return availableSize().width();
}

QSize MultiSplitterLayout::availableSize() const
{
    return m_rootItem->availableSize();
}

Layouting::Item *MultiSplitterLayout::itemForFrame(const Frame *frame) const
{
    if (!frame)
        return nullptr;

    return m_rootItem->itemForWidget(frame);
}

Frame::List MultiSplitterLayout::framesFrom(QWidgetOrQuick *frameOrMultiSplitter) const
{
    if (auto frame = qobject_cast<Frame*>(frameOrMultiSplitter))
        return { frame };

    if (auto msw = qobject_cast<MultiSplitter*>(frameOrMultiSplitter))
        return msw->multiSplitterLayout()->frames();

    return {};
}

Frame::List MultiSplitterLayout::frames() const
{
    const Layouting::Item::List items = m_rootItem->items_recursive();

    Frame::List result;
    result.reserve(items.size());

    for (Layouting::Item *item : items) {
        if (auto f = static_cast<Frame*>(item->widget()))
            result.push_back(f);
    }

    return result;
}

void MultiSplitterLayout::restorePlaceholder(DockWidgetBase *dw, Layouting::Item *item, int tabIndex)
{
    if (item->isPlaceholder()) {
        Frame *newFrame = Config::self().frameworkWidgetFactory()->createFrame(multiSplitter());
        item->restore(newFrame);
    }

    auto frame = qobject_cast<Frame*>(item->widget());
    Q_ASSERT(frame);

    if (tabIndex != -1 && frame->dockWidgetCount() >= tabIndex) {
        frame->insertWidget(dw, tabIndex);
    } else {
        frame->addWidget(dw);
    }

    frame->QWidget::setVisible(true);
}

void MultiSplitterLayout::layoutEqually()
{
    layoutEqually(m_rootItem);
}

void MultiSplitterLayout::layoutEqually(Layouting::ItemContainer *container)
{
    if (container) {
        container->layoutEqually_recursive();
    } else {
        qWarning() << Q_FUNC_INFO << "null container";
    }
}

bool MultiSplitterLayout::checkSanity() const
{
    return m_rootItem->checkSanity();
}

void MultiSplitterLayout::unrefOldPlaceholders(const Frame::List &framesBeingAdded) const
{
    for (Frame *frame : framesBeingAdded) {
        for (DockWidgetBase *dw : frame->dockWidgets()) {
            dw->lastPositions().removePlaceholders(multiSplitter());
        }
    }
}

void MultiSplitterLayout::dumpDebug() const
{
    m_rootItem->dumpLayout();
}

void MultiSplitterLayout::setSize(QSize size)
{
    if (size != this->size()) {
        m_rootItem->setSize_recursive(size);
        Q_EMIT sizeChanged(size);
    }
}

QSize MultiSplitterLayout::minimumSize() const
{
    return m_rootItem->minSize();
}

QSize MultiSplitterLayout::size() const { return m_rootItem->size(); }

void MultiSplitterLayout::setMinimumSize(QSize sz)
{
    if (sz != m_rootItem->minSize()) {
        setSize(size().expandedTo(m_rootItem->minSize())); // Increase size in case we need to
        m_rootItem->setMinSize(sz);
    }

    qCDebug(sizing) << Q_FUNC_INFO << "minSize = " << m_rootItem->minSize();
}

void MultiSplitterLayout::setRootItem(Layouting::ItemContainer *root)
{
    delete m_rootItem;
    m_rootItem = root;
    connect(m_rootItem, &Layouting::ItemContainer::numVisibleItemsChanged,
            this, &MultiSplitterLayout::visibleWidgetCountChanged);
    connect(m_rootItem, &Layouting::ItemContainer::minSizeChanged, this, [this] {
        Q_EMIT minimumSizeChanged(minimumSize());
    });
}

const Layouting::Item::List MultiSplitterLayout::items() const
{
    return m_rootItem->items_recursive();
}

Layouting::ItemContainer *MultiSplitterLayout::rootItem() const
{
    return m_rootItem;
}

QRect MultiSplitterLayout::rectForDrop(const QWidgetOrQuick *widget, Location location,
                                       const Layouting::Item *relativeTo) const
{
    Layouting::Item item(nullptr);
    item.setSize(widget->size());
    item.setMinSize(Layouting::Widget_qwidget::widgetMinSize(widget));
    item.setMaxSize(widget->maximumSize());

    Layouting::ItemContainer *container = relativeTo ? relativeTo->parentContainer()
                                                     : m_rootItem;

    return container->suggestedDropRect(&item, relativeTo, Layouting::Item::Location(location));
}

bool MultiSplitterLayout::deserialize(const LayoutSaver::MultiSplitterLayout &l)
{
    setRootItem(new Layouting::ItemContainer(m_multiSplitter));

    QHash<QString, Layouting::Widget*> frames;
    for (const LayoutSaver::Frame &frame : qAsConst(l.frames)) {
        Frame *f = Frame::deserialize(frame);
        Q_ASSERT(!frame.id.isEmpty());
        frames.insert(frame.id, f);
    }

    m_rootItem->fillFromVariantMap(l.layout, frames);

    updateSizeConstraints();
    m_rootItem->setSize_recursive(multiSplitter()->QWidget::size());

    return true;
}

LayoutSaver::MultiSplitterLayout MultiSplitterLayout::serialize() const
{
    LayoutSaver::MultiSplitterLayout l;
    l.layout = m_rootItem->toVariantMap();
    const Layouting::Item::List items = m_rootItem->items_recursive();
    l.frames.reserve(items.size());
    for (Layouting::Item *item : items) {
        if (!item->isContainer()) {
            if (auto frame = qobject_cast<Frame*>(item->widget()))
                l.frames.insert(QString::number(qint64(frame)), frame->serialize());
        }
    }

    return l;
}
