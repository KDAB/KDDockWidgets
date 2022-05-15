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
#include "Position_p.h"
#include "Utils_p.h"

#include "controllers/DockWidget_p.h"
#include "controllers/Frame.h"
#include "controllers/FloatingWindow.h"
#include "controllers/MainWindow.h"

#include "qtwidgets/views/MainWindow_qtwidgets.h"

#include "multisplitter/Item_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;


Layout::Layout(Type type, View *view)
    : Controller(type, view)
{
}

Layout::~Layout()
{
    m_minSizeChangedHandler.disconnect();

    if (m_rootItem && !m_viewDeleted)
        viewAboutToBeDeleted(); // TODO: Rename
    DockRegistry::self()->unregisterLayout(this);
}

void Layout::viewAboutToBeDeleted()
{
    if (view()) {
        if (view()->equals(m_rootItem->hostWidget())) {
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
    honourNesting = honourNesting && kddwUsesQtWidgets();

    if (honourNesting) {
        // This layout might be a MDIArea, nested in DropArea, which is main window.
        auto v = firstParentOfType<Views::MainWindow_qtwidgets>(view()->asQObject());
        return v ? v->mainWindow() : nullptr;
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
    auto parent = view()->parentView();
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
        auto newFrame = new Controllers::Frame(view());
        item->restore(newFrame->view());
    }

    auto frame = item->asFrameController();
    Q_ASSERT(frame);

    if (tabIndex != -1 && frame->dockWidgetCount() >= tabIndex) {
        frame->insertWidget(dw, tabIndex);
    } else {
        frame->addWidget(dw);
    }

    frame->setVisible(true);
}

void Layout::unrefOldPlaceholders(const Controllers::Frame::List &framesBeingAdded) const
{
    for (Controllers::Frame *frame : framesBeingAdded) {
        for (Controllers::DockWidget *dw : frame->dockWidgets()) {
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

bool Layout::containsFrame(const Controllers::Frame *frame) const
{
    return itemForFrame(frame) != nullptr;
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

Layouting::Item *Layout::itemForFrame(const Controllers::Frame *frame) const
{
    if (!frame)
        return nullptr;

    return m_rootItem->itemForWidget(frame->view()); // TODO: layout could have just the controller
}

Controllers::DockWidget::List Layout::dockWidgets() const
{
    Controllers::DockWidget::List dockWidgets;
    const Controllers::Frame::List frames = this->frames();
    for (Controllers::Frame *frame : frames)
        dockWidgets << frame->dockWidgets();

    return dockWidgets;
}

Controllers::Frame::List Layout::framesFrom(View *frameOrMultiSplitter) const
{
    if (auto frame = frameOrMultiSplitter->asFrameController())
        return { frame };

    if (auto msw = frameOrMultiSplitter->asDropAreaController())
        return msw->frames();

    return {};
}

Controllers::Frame::List Layout::frames() const
{
    const Layouting::Item::List items = m_rootItem->items_recursive();

    Controllers::Frame::List result;
    result.reserve(items.size());

    for (Layouting::Item *item : items) {
        if (auto frame = item->asFrameController()) {
            result.push_back(frame);
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
    l.frames.reserve(items.size());
    for (Layouting::Item *item : items) {
        if (!item->isContainer()) {
            if (auto frame = item->asFrameController()) {
                l.frames.insert(frame->view()->id(), frame->serialize());
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
    return view()->asMDILayoutController();
}
