/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DropArea.h"
#include "Config.h"
#include "ViewFactory.h"
#include "private/DockRegistry_p.h"
#include "private/Draggable_p.h"
#include "private/Logging_p.h"
#include "private/Utils_p.h"
#include "private/multisplitter/Item_p.h"
#include "private/WindowBeingDragged_p.h"

#include "controllers/Frame.h"
#include "controllers/FloatingWindow.h"
#include "controllers/DockWidget.h"
#include "controllers/DockWidget_p.h"
#include "controllers/MainWindow.h"
#include "controllers/DropIndicatorOverlay.h"
#include "controllers/indicators/ClassicIndicators.h"
#include "controllers/indicators/NullIndicators.h"
#include "controllers/indicators/SegmentedIndicators.h"

#include <algorithm>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

namespace KDDockWidgets {
static Controllers::DropIndicatorOverlay *createDropIndicatorOverlay(Controllers::DropArea *dropArea)
{
#ifdef Q_OS_WASM
    // On WASM windows don't support translucency, which is required for the classic indicators.
    return new SegmentedIndicators(dropArea);
#endif

    switch (ViewFactory::s_dropIndicatorType) {
    case DropIndicatorType::Classic:
        return new Controllers::ClassicIndicators(dropArea);
    case DropIndicatorType::Segmented:
        return new Controllers::SegmentedIndicators(dropArea);
    case DropIndicatorType::None:
        return new Controllers::NullIndicators(dropArea);
    }

    return new Controllers::ClassicIndicators(dropArea);
}
}

DropArea::DropArea(View *parent, MainWindowOptions options, bool isMDIWrapper)
    : Layout(Type::DropArea, Config::self().viewFactory()->createDropArea(this, parent))
    , m_isMDIWrapper(isMDIWrapper)
    , m_dropIndicatorOverlay(createDropIndicatorOverlay(this))
    , m_centralFrame(createCentralFrame(options))
{
    Q_ASSERT(parent);
    setRootItem(new Layouting::ItemBoxContainer(view()));
    DockRegistry::self()->registerLayout(this);

    setLayoutSize(parent->size());

    // Initialize min size
    updateSizeConstraints();

    qCDebug(creation) << "DropArea";

    if (m_isMDIWrapper) {
        m_visibleWidgetCountConnection = visibleWidgetCountChanged.connect([this] {
            auto dw = mdiDockWidgetWrapper();
            if (!dw) {
                qWarning() << Q_FUNC_INFO << "Unexpected null wrapper dock widget";
                return;
            }

            if (visibleCount() > 0) {
                // The title of our MDI frame will need to change to the app name if we have more than 1 dock widget nested
                Q_EMIT dw->titleChanged(dw->title());
            } else {
                // Our wrapeper isn't needed anymore
                dw->deleteLater();
            }
        });
    }

    if (m_centralFrame)
        addWidget(m_centralFrame->view(), KDDockWidgets::Location_OnTop, {});
}

DropArea::~DropArea()
{
    m_inDestructor = true;
    qCDebug(creation) << "~DropArea";
}

Controllers::Frame::List DropArea::frames() const
{
    const Layouting::Item::List children = m_rootItem->items_recursive();
    Controllers::Frame::List frames;

    for (const Layouting::Item *child : children) {
        if (auto view = child->guestView()) {
            if (!view->freed()) {
                if (auto frame = view->asFrameController()) {
                    frames << frame;
                }
            }
        }
    }

    return frames;
}

Controllers::Frame *DropArea::frameContainingPos(QPoint globalPos) const
{
    const Layouting::Item::List &items = this->items();
    for (Layouting::Item *item : items) {
        auto frame = item->asFrameController();
        if (!frame || !frame->isVisible()) {
            continue;
        }

        if (frame->containsMouse(globalPos))
            return frame;
    }
    return nullptr;
}

void DropArea::updateFloatingActions()
{
    const Controllers::Frame::List frames = this->frames();
    for (Controllers::Frame *frame : frames)
        frame->updateFloatingActions();
}

Layouting::Item *DropArea::centralFrame() const
{
    for (Layouting::Item *item : this->items()) {
        if (auto frame = item->asFrameController()) {
            if (frame->isCentralFrame())
                return item;
        }
    }
    return nullptr;
}

void DropArea::addDockWidget(Controllers::DockWidget *dw, Location location,
                             Controllers::DockWidget *relativeTo, InitialOption option)
{
    if (!dw || dw == relativeTo || location == Location_None) {
        qWarning() << Q_FUNC_INFO << "Invalid parameters" << dw << relativeTo << location;
        return;
    }

    if ((option.visibility == InitialVisibilityOption::StartHidden) && dw->d->frame() != nullptr) {
        // StartHidden is just to be used at startup, not to moving stuff around
        qWarning() << Q_FUNC_INFO << "Dock widget already exists in the layout";
        return;
    }

    if (!validateAffinity(dw))
        return;

    Controllers::DockWidget::Private::UpdateActions actionsUpdater(dw);

    Controllers::Frame *frame = nullptr;
    Controllers::Frame *relativeToFrame = relativeTo ? relativeTo->d->frame() : nullptr;

    dw->d->saveLastFloatingGeometry();

    const bool hadSingleFloatingFrame = hasSingleFloatingFrame();

    // Check if the dock widget already exists in the layout
    if (containsDockWidget(dw)) {
        Controllers::Frame *oldFrame = dw->d->frame();
        if (oldFrame->hasSingleDockWidget()) {
            Q_ASSERT(oldFrame->containsDockWidget(dw));
            // The frame only has this dock widget, and the frame is already in the layout. So move the frame instead
            frame = oldFrame;
        } else {
            frame = new Controllers::Frame();
            frame->addWidget(dw);
        }
    } else {
        frame = new Controllers::Frame();
        frame->addWidget(dw);
    }

    if (option.startsHidden()) {
        addWidget(dw->view(), location, relativeToFrame, option);
    } else {
        addWidget(frame->view(), location, relativeToFrame, option);
    }

    if (hadSingleFloatingFrame && !hasSingleFloatingFrame()) {
        // The dock widgets that already existed in our layout need to have their floatAction() updated
        // otherwise it's still checked. Only the dropped dock widget got updated
        updateFloatingActions();
    }
}

bool DropArea::containsDockWidget(Controllers::DockWidget *dw) const
{
    return dw->d->frame() && Layout::containsFrame(dw->d->frame());
}

bool DropArea::hasSingleFloatingFrame() const
{
    const Controllers::Frame::List frames = this->frames();
    return frames.size() == 1 && frames.first()->isFloating();
}

bool DropArea::hasSingleFrame() const
{
    return visibleCount() == 1;
}

QStringList DropArea::affinities() const
{
    if (auto mw = mainWindow()) {
        return mw->affinities();
    } else if (auto fw = floatingWindow()) {
        return fw->affinities();
    }

    return {};
}

void DropArea::layoutParentContainerEqually(Controllers::DockWidget *dw)
{
    Layouting::Item *item = itemForFrame(dw->d->frame());
    if (!item) {
        qWarning() << Q_FUNC_INFO << "Item not found for" << dw << dw->d->frame();
        return;
    }

    layoutEqually(item->parentBoxContainer());
}

DropLocation DropArea::hover(WindowBeingDragged *draggedWindow, QPoint globalPos)
{
    if (Config::self().dropIndicatorsInhibited() || !validateAffinity(draggedWindow))
        return DropLocation_None;

    if (!m_dropIndicatorOverlay) {
        qWarning() << Q_FUNC_INFO << "The frontend is missing a drop indicator overlay";
        return DropLocation_None;
    }

    Controllers::Frame *frame = frameContainingPos(globalPos); // Frame is nullptr if MainWindowOption_HasCentralFrame isn't set
    m_dropIndicatorOverlay->setWindowBeingDragged(true);
    m_dropIndicatorOverlay->setHoveredFrame(frame);
    return m_dropIndicatorOverlay->hover(globalPos);
}

static bool isOutterLocation(DropLocation location)
{
    switch (location) {
    case DropLocation_OutterLeft:
    case DropLocation_OutterTop:
    case DropLocation_OutterRight:
    case DropLocation_OutterBottom:
        return true;
    default:
        return false;
    }
}

bool DropArea::drop(WindowBeingDragged *droppedWindow, QPoint globalPos)
{
    Controllers::FloatingWindow *floatingWindow = droppedWindow->floatingWindow();

    if (floatingWindow->view()->equals(window())) {
        qWarning() << "Refusing to drop onto itself"; // Doesn't happen
        return false;
    }

    if (m_dropIndicatorOverlay->currentDropLocation() == DropLocation_None) {
        qCDebug(hovering) << "DropArea::drop: bailing out, drop location = none";
        return false;
    }

    qCDebug(dropping) << "DropArea::drop:" << droppedWindow;

    hover(droppedWindow, globalPos);
    auto droploc = m_dropIndicatorOverlay->currentDropLocation();
    Controllers::Frame *acceptingFrame = m_dropIndicatorOverlay->hoveredFrame();
    if (!(acceptingFrame || isOutterLocation(droploc))) {
        qWarning() << "DropArea::drop: asserted with frame=" << acceptingFrame
                   << "; Location=" << droploc;
        return false;
    }

    return drop(droppedWindow, acceptingFrame, droploc);
}

bool DropArea::drop(WindowBeingDragged *draggedWindow, Controllers::Frame *acceptingFrame,
                    DropLocation droploc)
{
    Controllers::FloatingWindow *droppedWindow = draggedWindow ? draggedWindow->floatingWindow()
                                                               : nullptr;

    if (isWayland() && !droppedWindow) {
        // This is the Wayland special case.
        // With other platforms, when detaching a tab or dock widget we create the FloatingWindow immediately.
        // With Wayland we delay the floating window until we drop it.
        // Ofc, we could just dock the dockwidget without the temporary FloatingWindow, but this way we reuse
        // 99% of the rest of the code, without adding more wayland special cases
        droppedWindow = draggedWindow->draggable()->makeWindow()->floatingWindow();
        if (!droppedWindow) {
            // Doesn't happen
            qWarning() << Q_FUNC_INFO << "Wayland: Expected window" << draggedWindow;
            return false;
        }
    }

    bool result = true;
    const bool needToFocusNewlyDroppedWidgets = Config::self().flags() & Config::Flag_TitleBarIsFocusable;
    const Controllers::DockWidget::List droppedDockWidgets = needToFocusNewlyDroppedWidgets
        ? droppedWindow->layout()->dockWidgets()
        : Controllers::DockWidget::List(); // just so save some memory allocations for the case where this
    // variable isn't used

    switch (droploc) {
    case DropLocation_Left:
    case DropLocation_Top:
    case DropLocation_Bottom:
    case DropLocation_Right:
        result = drop(droppedWindow->view(), DropIndicatorOverlay::multisplitterLocationFor(droploc), acceptingFrame);
        break;
    case DropLocation_OutterLeft:
    case DropLocation_OutterTop:
    case DropLocation_OutterRight:
    case DropLocation_OutterBottom:
        result = drop(droppedWindow->view(), DropIndicatorOverlay::multisplitterLocationFor(droploc), nullptr);
        break;
    case DropLocation_Center:
        qCDebug(hovering) << "Tabbing" << droppedWindow << "into" << acceptingFrame;
        if (!validateAffinity(droppedWindow, acceptingFrame))
            return false;
        acceptingFrame->addWidget(droppedWindow);
        break;

    default:
        qWarning() << "DropArea::drop: Unexpected drop location" << m_dropIndicatorOverlay->currentDropLocation();
        result = false;
        break;
    }

    if (result) {
        // Window receiving the drop gets raised:
        view()->raiseAndActivate();

        if (needToFocusNewlyDroppedWidgets) {
            // Let's also focus the newly dropped dock widget
            if (!droppedDockWidgets.isEmpty()) {
                // If more than 1 was dropped, we only focus the first one
                Controllers::Frame *frame = droppedDockWidgets.first()->d->frame();
                frame->FocusScope::focus(Qt::MouseFocusReason);
            } else {
                // Doesn't happen.
                qWarning() << Q_FUNC_INFO << "Nothing was dropped?";
            }
        }
    }

    return result;
}

bool DropArea::drop(View *droppedWindow, KDDockWidgets::Location location, Controllers::Frame *relativeTo)
{
    qCDebug(docking) << "DropArea::addFrame";

    if (auto dock = droppedWindow->asDockWidgetController()) {
        if (!validateAffinity(dock))
            return false;

        auto frame = new Controllers::Frame();
        frame->addWidget(dock);
        addWidget(frame->view(), location, relativeTo, DefaultSizeMode::FairButFloor);
    } else if (auto floatingWindow = droppedWindow->asFloatingWindowController()) {
        if (!validateAffinity(floatingWindow))
            return false;

        const bool hadSingleFloatingFrame = hasSingleFloatingFrame();
        addMultiSplitter(floatingWindow->dropArea(), location, relativeTo,
                         DefaultSizeMode::FairButFloor);
        if (hadSingleFloatingFrame != hasSingleFloatingFrame())
            updateFloatingActions();

        floatingWindow->scheduleDeleteLater();
        return true;
    } else {
        qWarning() << "Unknown dropped widget" << droppedWindow;
        return false;
    }

    return true;
}

void DropArea::removeHover()
{
    m_dropIndicatorOverlay->removeHover();
}

template<typename T>
bool DropArea::validateAffinity(T *window, Controllers::Frame *acceptingFrame) const
{
    if (!DockRegistry::self()->affinitiesMatch(window->affinities(), affinities())) {
        return false;
    }

    if (acceptingFrame) {
        // We're dropping into another frame (as tabbed), so also check the affinity of the frame
        // not only of the main window, which might be more forgiving
        if (!DockRegistry::self()->affinitiesMatch(window->affinities(), acceptingFrame->affinities())) {
            return false;
        }
    }

    return true;
}

bool DropArea::isMDIWrapper() const
{
    return m_isMDIWrapper;
}

Controllers::DockWidget *DropArea::mdiDockWidgetWrapper() const
{
    if (m_isMDIWrapper) {
        return view()->parentView()->asDockWidgetController();
    }

    return nullptr;
}

Controllers::Frame *DropArea::createCentralFrame(MainWindowOptions options)
{
    Controllers::Frame *frame = nullptr;
    if (options & MainWindowOption_HasCentralFrame) {
        FrameOptions frameOptions = FrameOption_IsCentralFrame;
        const bool hasPersistentCentralWidget = (options & MainWindowOption_HasCentralWidget) == MainWindowOption_HasCentralWidget;
        if (hasPersistentCentralWidget) {
            frameOptions |= FrameOption_NonDockable;
        } else {
            // With a persistent central widget we don't allow detaching it
            frameOptions |= FrameOption_AlwaysShowsTabs;
        }

        frame = new Controllers::Frame(nullptr, frameOptions);
        frame->setObjectName(QStringLiteral("central frame"));
    }

    return frame;
}


bool DropArea::validateInputs(View *widget, Location location,
                              const Controllers::Frame *relativeToFrame, InitialOption option) const
{
    if (!widget) {
        qWarning() << Q_FUNC_INFO << "Widget is null";
        return false;
    }

    const bool isDockWidget = widget->is(Type::DockWidget);
    const bool isStartHidden = option.startsHidden();

    const bool isLayout = widget->is(Type::DropArea) || widget->is(Type::MDILayout);
    if (!widget->is(Type::Frame) && !isLayout && !isDockWidget) {
        qWarning() << "Unknown widget type" << widget;
        return false;
    }

    if (isDockWidget != isStartHidden) {
        qWarning() << "Wrong parameters" << isDockWidget << isStartHidden;
        return false;
    }

    if (relativeToFrame && relativeToFrame->view()->equals(widget)) {
        qWarning() << "widget can't be relative to itself";
        return false;
    }

    Layouting::Item *item = itemForFrame(widget->asFrameController());

    if (containsItem(item)) {
        qWarning() << "DropArea::addWidget: Already contains" << widget;
        return false;
    }

    if (location == Location_None) {
        qWarning() << "DropArea::addWidget: not adding to location None";
        return false;
    }

    const bool relativeToThis = relativeToFrame == nullptr;

    Layouting::Item *relativeToItem = itemForFrame(relativeToFrame);
    if (!relativeToThis && !containsItem(relativeToItem)) {
        qWarning() << "DropArea::addWidget: Doesn't contain relativeTo:"
                   << "; relativeToFrame=" << relativeToFrame
                   << "; relativeToItem=" << relativeToItem
                   << "; options=" << option;
        return false;
    }

    return true;
}

void DropArea::addWidget(View *w, Location location,
                         Controllers::Frame *relativeToWidget,
                         InitialOption option)
{

    auto frame = w->asFrameController();
    if (itemForFrame(frame) != nullptr) {
        // Item already exists, remove it.
        // Changing the frame parent will make the item clean itself up. It turns into a placeholder and is removed by unrefOldPlaceholders
        frame->view()->setParent(nullptr); // so ~Item doesn't delete it
        frame->setLayoutItem(nullptr); // so Item is destroyed, as there's no refs to it
    }

    // Make some sanity checks:
    if (!validateInputs(w, location, relativeToWidget, option))
        return;

    Layouting::Item *relativeTo = itemForFrame(relativeToWidget);
    if (!relativeTo)
        relativeTo = m_rootItem;

    Layouting::Item *newItem = nullptr;

    Controllers::Frame::List frames = framesFrom(w);
    unrefOldPlaceholders(frames);
    auto dw = w->asDockWidgetController();
    auto thisView = view();

    if (frame) {
        newItem = new Layouting::Item(thisView);
        newItem->setGuestView(frame->view());
    } else if (dw) {
        newItem = new Layouting::Item(thisView);
        frame = new Controllers::Frame();
        newItem->setGuestView(frame->view());
        frame->addWidget(dw, option);
    } else if (auto ms = w->asDropAreaController()) {
        newItem = ms->m_rootItem;
        newItem->setHostWidget(thisView);

        if (auto fw = ms->floatingWindow()) {
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

void DropArea::addMultiSplitter(Controllers::DropArea *sourceMultiSplitter, Location location,
                                Controllers::Frame *relativeTo,
                                InitialOption option)
{
    qCDebug(addwidget) << Q_FUNC_INFO << sourceMultiSplitter << location << relativeTo;
    addWidget(sourceMultiSplitter->view(), location, relativeTo, option);
}

QVector<Controllers::Separator *> DropArea::separators() const
{
    return m_rootItem->separators_recursive();
}

int DropArea::availableLengthForOrientation(Qt::Orientation orientation) const
{
    if (orientation == Qt::Vertical)
        return availableSize().height();
    else
        return availableSize().width();
}

QSize DropArea::availableSize() const
{
    return m_rootItem->availableSize();
}

void DropArea::layoutEqually()
{
    if (!checkSanity())
        return;

    layoutEqually(m_rootItem);
}

void DropArea::layoutEqually(Layouting::ItemBoxContainer *container)
{
    if (container) {
        container->layoutEqually_recursive();
    } else {
        qWarning() << Q_FUNC_INFO << "null container";
    }
}

void DropArea::setRootItem(Layouting::ItemBoxContainer *root)
{
    Layout::setRootItem(root);
    m_rootItem = root;
}

Layouting::ItemBoxContainer *DropArea::rootItem() const
{
    return m_rootItem;
}

QRect DropArea::rectForDrop(const WindowBeingDragged *wbd, Location location,
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

bool DropArea::deserialize(const LayoutSaver::MultiSplitter &l)
{
    setRootItem(new Layouting::ItemBoxContainer(view()));
    return Layout::deserialize(l);
}
