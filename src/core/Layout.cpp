/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "core/LayoutSaver_p.h"
#include "core/Position_p.h"
#include "Config.h"
#include "Platform.h"
#include "core/ViewFactory.h"
#include "core/Utils_p.h"
#include "core/View_p.h"
#include "core/Layout.h"
#include "core/Layout_p.h"
#include "core/Logging_p.h"
#include "core/ScopedValueRollback_p.h"
#include "core/DropArea.h"
#include "core/DockWidget_p.h"
#include "core/Group.h"
#include "core/FloatingWindow.h"
#include "core/MainWindow.h"

#include "core/layouting/Item_p.h"

#include <unordered_map>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;


Layout::Layout(ViewType type, View *view)
    : Controller(type, view)
    , d(new Private())
{
    assert(view);
    view->d->layoutInvalidated.connect([this] { updateSizeConstraints(); });

    view->d->resized.connect(&Layout::onResize, this);
}

Layout::~Layout()
{
    d->m_minSizeChangedHandler.disconnect();

    if (d->m_rootItem && !d->m_viewDeleted)
        viewAboutToBeDeleted();
    DockRegistry::self()->unregisterLayout(this);
    delete d;
}

void Layout::viewAboutToBeDeleted()
{
    if (view()) {
        if (view()->equals(d->m_rootItem->hostView())) {
            delete d->m_rootItem;
            d->m_rootItem = nullptr;
        }

        d->m_viewDeleted = true;
    }
}

bool Layout::isInMainWindow(bool honourNesting) const
{
    return mainWindow(honourNesting) != nullptr;
}

Core::MainWindow *Layout::mainWindow(bool honourNesting) const
{
    // QtQuick doesn't support nesting yet
    honourNesting = honourNesting && Platform::instance()->isQtWidgets();

    if (honourNesting) {
        // This layout might be a MDIArea, nested in DropArea, which is main window.
        if (Controller *c = view()->d->firstParentOfType(ViewType::MainWindow))
            return static_cast<Core::MainWindow *>(c);
        return nullptr;
    } else {
        if (auto pw = view()->parentView()) {
            // Note that if pw is a FloatingWindow then pw->parentWidget() can be a MainWindow too,
            // as it's parented
            if (pw->viewName() == QLatin1String("MyCentralWidget"))
                return pw->parentView()->asMainWindowController();

            if (auto mw = pw->asMainWindowController())
                return mw;
        }
    }

    return nullptr;
}

Core::FloatingWindow *Layout::floatingWindow() const
{
    auto parent = view()->rootView();
    return parent ? parent->asFloatingWindowController() : nullptr;
}

void Layout::setRootItem(Core::ItemContainer *root)
{
    delete d->m_rootItem;
    d->m_rootItem = root;
    d->m_rootItem->numVisibleItemsChanged.connect(
        [this](int count) { d->visibleWidgetCountChanged.emit(count); });

    d->m_minSizeChangedHandler =
        d->m_rootItem->minSizeChanged.connect([this] { view()->setMinimumSize(layoutMinimumSize()); });
}

Size Layout::layoutMinimumSize() const
{
    return d->m_rootItem->minSize();
}

Size Layout::layoutMaximumSizeHint() const
{
    return d->m_rootItem->maxSizeHint();
}

void Layout::setLayoutMinimumSize(Size sz)
{
    if (sz != d->m_rootItem->minSize()) {
        setLayoutSize(layoutSize().expandedTo(d->m_rootItem->minSize())); // Increase size in case we
                                                                          // need to
        d->m_rootItem->setMinSize(sz);
    }
}

Size Layout::layoutSize() const
{
    return d->m_rootItem->size();
}

void Layout::clearLayout()
{
    d->m_rootItem->clear();
}

bool Layout::checkSanity() const
{
    return d->m_rootItem->checkSanity();
}

void Layout::dumpLayout() const
{
    d->m_rootItem->dumpLayout();
}

void Layout::restorePlaceholder(Core::DockWidget *dw, Core::Item *item, int tabIndex)
{
    if (item->isPlaceholder()) {
        auto newGroup = new Core::Group(view());
        item->restore(newGroup->view());
    }

    auto group = item->asGroupController();
    assert(group);
    if (group->inDtor() || group->beingDeletedLater()) {
        // Known bug. Let's print diagnostics early, as this is usually difficult to debug
        // further up the stack. Will also fatal the tests.
        KDDW_ERROR("Layout::restorePlaceholder: Trying to use a group that's being deleted");
    }

    if (tabIndex != -1 && group->dockWidgetCount() >= tabIndex) {
        group->insertWidget(dw, tabIndex);
    } else {
        group->addTab(dw);
    }

    group->setVisible(true);
}

void Layout::unrefOldPlaceholders(const Core::Group::List &groupsBeingAdded) const
{
    for (Core::Group *group : groupsBeingAdded) {
        for (Core::DockWidget *dw : group->dockWidgets()) {
            dw->d->lastPosition()->removePlaceholders(this);
        }
    }
}

void Layout::setLayoutSize(Size size)
{
    if (size != layoutSize()) {
        d->m_rootItem->setSize_recursive(size);
        if (!d->m_inResizeEvent && !LayoutSaver::restoreInProgress())
            view()->resize(size);
    }
}

const Core::Item::List Layout::items() const
{
    return d->m_rootItem->items_recursive();
}

bool Layout::containsItem(const Core::Item *item) const
{
    return d->m_rootItem->contains_recursive(item);
}

bool Layout::containsFrame(const Core::Group *group) const
{
    return itemForFrame(group) != nullptr;
}

int Layout::count() const
{
    return d->m_rootItem->count_recursive();
}

int Layout::visibleCount() const
{
    return d->m_rootItem->visibleCount_recursive();
}

int Layout::placeholderCount() const
{
    return count() - visibleCount();
}

Core::Item *Layout::itemForFrame(const Core::Group *group) const
{
    if (!group)
        return nullptr;

    return d->m_rootItem->itemForView(group->view());
}

Core::DockWidget::List Layout::dockWidgets() const
{
    Core::DockWidget::List dockWidgets;
    const Core::Group::List groups = this->groups();
    for (Core::Group *group : groups)
        dockWidgets.append(group->dockWidgets());

    return dockWidgets;
}

Core::Group::List Layout::groupsFrom(View *groupOrMultiSplitter) const
{
    if (auto group = groupOrMultiSplitter->asGroupController())
        return { group };

    if (auto msw = groupOrMultiSplitter->asDropAreaController())
        return msw->groups();

    return {};
}

Core::Group::List Layout::groups() const
{
    const Core::Item::List items = d->m_rootItem->items_recursive();

    Core::Group::List result;
    result.reserve(items.size());

    for (Core::Item *item : items) {
        if (auto group = item->asGroupController()) {
            result.push_back(group);
        }
    }

    return result;
}

void Layout::removeItem(Core::Item *item)
{
    if (!item) {
        KDDW_ERROR("nullptr item");
        return;
    }

    item->parentContainer()->removeItem(item);
}

void Layout::updateSizeConstraints()
{
    const Size newMinSize = d->m_rootItem->minSize();
    setLayoutMinimumSize(newMinSize);
}

bool Layout::deserialize(const LayoutSaver::MultiSplitter &l)
{
    std::unordered_map<QString, View *> groups;
    for (auto it : l.groups) {
        const LayoutSaver::Group &group = it.second;
        Core::Group *f = Core::Group::deserialize(group);
        if (!f)
            return false;

        assert(!group.id.isEmpty());
        groups[group.id] = f->view();
    }

    d->m_rootItem->fillFromJson(l.layout, groups);
    updateSizeConstraints();

    const Size newLayoutSize = view()->size().expandedTo(d->m_rootItem->minSize());

    d->m_rootItem->setSize_recursive(newLayoutSize);

    return true;
}

bool Layout::onResize(Size newSize)
{
    ScopedValueRollback resizeGuard(d->m_inResizeEvent, true); // to avoid re-entrancy

    if (!LayoutSaver::restoreInProgress()) {
        // don't resize anything while we're restoring the layout
        setLayoutSize(newSize);
    }

    return false; // So QWidget::resizeEvent is called
}

LayoutSaver::MultiSplitter Layout::serialize() const
{
    LayoutSaver::MultiSplitter l;
    d->m_rootItem->to_json(l.layout);
    const Core::Item::List items = d->m_rootItem->items_recursive();
    l.groups.reserve(size_t(items.size()));
    for (Core::Item *item : items) {
        if (!item->isContainer()) {
            if (auto group = item->asGroupController()) {
                l.groups[group->view()->d->id()] = group->serialize();
            }
        }
    }

    return l;
}

Core::DropArea *Layout::asDropArea() const
{
    return view()->asDropAreaController();
}

MDILayout *Layout::asMDILayout() const
{
    if (auto v = view())
        return v->asMDILayoutController();

    return nullptr;
}

Core::ItemContainer *Layout::rootItem() const
{
    return d->m_rootItem;
}

void Layout::onCloseEvent(CloseEvent *e)
{
    e->accept(); // Accepted by default (will close unless ignored)

    const Core::Group::List groups = this->groups();
    for (Core::Group *group : groups) {
        group->view()->d->requestClose(e);
        if (!e->isAccepted())
            break; // Stop when the first group prevents closing
    }
}

Layout::Private *Layout::d_ptr()
{
    return d;
}
