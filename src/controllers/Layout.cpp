/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "private/LayoutSaver_p.h"
#include "private/Position_p.h"
#include "Config.h"
#include "Platform.h"
#include "kddockwidgets/ViewFactory.h"
#include "private/Utils_p.h"
#include "private/View_p.h"

#include "controllers/Layout.h"
#include "controllers/DropArea.h"
#include "controllers/DockWidget_p.h"
#include "controllers/Group.h"
#include "controllers/FloatingWindow.h"
#include "controllers/MainWindow.h"

#include "private/multisplitter/Item_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;


Layout::Layout(Type type, View *view)
    : Controller(type, view)
{
    Q_ASSERT(view);
    view->d->layoutInvalidated.connect([this] {
        updateSizeConstraints();
    });

    view->d->resized.connect(&Layout::onResize, this);
}

Layout::~Layout()
{
    m_minSizeChangedHandler.disconnect();

    if (m_rootItem && !m_viewDeleted)
        viewAboutToBeDeleted();
    DockRegistry::self()->unregisterLayout(this);
}

void Layout::viewAboutToBeDeleted()
{
    if (view()) {
        if (view()->equals(m_rootItem->hostView())) {
            delete m_rootItem;
            m_rootItem = nullptr;
        }

        m_viewDeleted = true;
    }
}

bool Layout::isInMainWindow(bool honourNesting) const
{
    return mainWindow(honourNesting) != nullptr;
}

Controllers::MainWindow *Layout::mainWindow(bool honourNesting) const
{
    // QtQuick doesn't support nesting yet
    honourNesting = honourNesting && Platform::instance()->isQtWidgets();

    if (honourNesting) {
        // This layout might be a MDIArea, nested in DropArea, which is main window.
        if (Controller *c = view()->firstParentOfType(Type::MainWindow))
            return static_cast<Controllers::MainWindow *>(c);
        return nullptr;
    } else {
        if (auto pw = view()->parentView()) {
            // Note that if pw is a FloatingWindow then pw->parentWidget() can be a MainWindow too, as
            // it's parented
            if (pw->objectName() == QLatin1String("MyCentralWidget"))
                return pw->parentView()->asMainWindowController();

            if (auto mw = pw->asMainWindowController())
                return mw;
        }
    }

    return nullptr;
}

Controllers::FloatingWindow *Layout::floatingWindow() const
{
    auto parent = view()->rootView();
    return parent ? parent->asFloatingWindowController() : nullptr;
}

void Layout::setRootItem(Layouting::ItemContainer *root)
{
    delete m_rootItem;
    m_rootItem = root;
    m_rootItem->numVisibleItemsChanged.connect([this](int count) {
        visibleWidgetCountChanged.emit(count);
    });

    m_minSizeChangedHandler = m_rootItem->minSizeChanged.connect([this] { view()->setMinimumSize(layoutMinimumSize()); });
}

QSize Layout::layoutMinimumSize() const
{
    return m_rootItem->minSize();
}

QSize Layout::layoutMaximumSizeHint() const
{
    return m_rootItem->maxSizeHint();
}

void Layout::setLayoutMinimumSize(QSize sz)
{
    if (sz != m_rootItem->minSize()) {
        setLayoutSize(layoutSize().expandedTo(m_rootItem->minSize())); // Increase size in case we need to
        m_rootItem->setMinSize(sz);
    }
}

QSize Layout::layoutSize() const
{
    return m_rootItem->size();
}

void Layout::clearLayout()
{
    m_rootItem->clear();
}

bool Layout::checkSanity() const
{
    return m_rootItem->checkSanity();
}

void Layout::dumpLayout() const
{
    m_rootItem->dumpLayout();
}

void Layout::restorePlaceholder(Controllers::DockWidget *dw, Layouting::Item *item, int tabIndex)
{
    if (item->isPlaceholder()) {
        auto newGroup = new Controllers::Group(view());
        item->restore(newGroup->view());
    }

    auto group = item->asGroupController();
    Q_ASSERT(group);

    if (tabIndex != -1 && group->dockWidgetCount() >= tabIndex) {
        group->insertWidget(dw, tabIndex);
    } else {
        group->addWidget(dw);
    }

    group->setVisible(true);
}

void Layout::unrefOldPlaceholders(const Controllers::Group::List &groupsBeingAdded) const
{
    for (Controllers::Group *group : groupsBeingAdded) {
        for (Controllers::DockWidget *dw : group->dockWidgets()) {
            dw->d->lastPosition()->removePlaceholders(this);
        }
    }
}

void Layout::setLayoutSize(QSize size)
{
    if (size != layoutSize()) {
        m_rootItem->setSize_recursive(size);
        if (!m_inResizeEvent && !LayoutSaver::restoreInProgress())
            view()->resize(size);
    }
}

const Layouting::Item::List Layout::items() const
{
    return m_rootItem->items_recursive();
}

bool Layout::containsItem(const Layouting::Item *item) const
{
    return m_rootItem->contains_recursive(item);
}

bool Layout::containsFrame(const Controllers::Group *group) const
{
    return itemForFrame(group) != nullptr;
}

int Layout::count() const
{
    return m_rootItem->count_recursive();
}

int Layout::visibleCount() const
{
    return m_rootItem->visibleCount_recursive();
}

int Layout::placeholderCount() const
{
    return count() - visibleCount();
}

Layouting::Item *Layout::itemForFrame(const Controllers::Group *group) const
{
    if (!group)
        return nullptr;

    return m_rootItem->itemForView(group->view());
}

Controllers::DockWidget::List Layout::dockWidgets() const
{
    Controllers::DockWidget::List dockWidgets;
    const Controllers::Group::List groups = this->groups();
    for (Controllers::Group *group : groups)
        dockWidgets << group->dockWidgets();

    return dockWidgets;
}

Controllers::Group::List Layout::groupsFrom(View *groupOrMultiSplitter) const
{
    if (auto group = groupOrMultiSplitter->asGroupController())
        return { group };

    if (auto msw = groupOrMultiSplitter->asDropAreaController())
        return msw->groups();

    return {};
}

Controllers::Group::List Layout::groups() const
{
    const Layouting::Item::List items = m_rootItem->items_recursive();

    Controllers::Group::List result;
    result.reserve(items.size());

    for (Layouting::Item *item : items) {
        if (auto group = item->asGroupController()) {
            result.push_back(group);
        }
    }

    return result;
}

void Layout::removeItem(Layouting::Item *item)
{
    if (!item) {
        qWarning() << Q_FUNC_INFO << "nullptr item";
        return;
    }

    item->parentContainer()->removeItem(item);
}

void Layout::updateSizeConstraints()
{
    const QSize newMinSize = m_rootItem->minSize();
    qCDebug(sizing) << Q_FUNC_INFO << "Updating size constraints from" << view()->minSize() << "to"
                    << newMinSize;

    setLayoutMinimumSize(newMinSize);
}

bool Layout::deserialize(const LayoutSaver::MultiSplitter &l)
{
    QHash<QString, View *> groups;
    for (const LayoutSaver::Group &group : qAsConst(l.groups)) {
        Controllers::Group *f = Controllers::Group::deserialize(group);
        Q_ASSERT(!group.id.isEmpty());
        groups.insert(group.id, f->view());
    }

    m_rootItem->fillFromVariantMap(l.layout, groups);

    updateSizeConstraints();

    // This qMin() isn't needed for QtWidgets (but harmless), but it's required for QtQuick
    // as some sizing is async
    const QSize newLayoutSize = view()->size().expandedTo(m_rootItem->minSize());

    m_rootItem->setSize_recursive(newLayoutSize);

    return true;
}

bool Layout::onResize(QSize newSize)
{
    QScopedValueRollback<bool> resizeGuard(m_inResizeEvent, true); // to avoid re-entrancy

    if (!LayoutSaver::restoreInProgress()) {
        // don't resize anything while we're restoring the layout
        setLayoutSize(newSize);
    }

    return false; // So QWidget::resizeEvent is called
}

LayoutSaver::MultiSplitter Layout::serialize() const
{
    LayoutSaver::MultiSplitter l;
    l.layout = m_rootItem->toVariantMap();
    const Layouting::Item::List items = m_rootItem->items_recursive();
    l.groups.reserve(items.size());
    for (Layouting::Item *item : items) {
        if (!item->isContainer()) {
            if (auto group = item->asGroupController()) {
                l.groups.insert(group->view()->id(), group->serialize());
            }
        }
    }

    return l;
}

Controllers::DropArea *Layout::asDropArea() const
{
    return view()->asDropAreaController();
}

MDILayout *Layout::asMDILayout() const
{
    if (auto v = view())
        return v->asMDILayoutController();

    return nullptr;
}

Layouting::ItemContainer *Layout::rootItem() const
{
    return m_rootItem;
}


void Layout::onCloseEvent(QCloseEvent *e)
{
    e->accept(); // Accepted by default (will close unless ignored)

    const Controllers::Group::List groups = this->groups();
    for (Controllers::Group *group : groups) {
        Platform::instance()->sendEvent(group->view(), e);
        if (!e->isAccepted())
            break; // Stop when the first group prevents closing
    }
}
