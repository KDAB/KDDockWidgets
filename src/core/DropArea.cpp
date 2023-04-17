/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DropArea.h"
#include "Config.h"
#include "kddockwidgets/ViewFactory.h"
#include "DockRegistry.h"
#include "Platform.h"
#include "core/Draggable_p.h"
#include "core/Logging_p.h"
#include "core/Utils_p.h"
#include "core/layouting/Item_p.h"
#include "core/WindowBeingDragged_p.h"

#include "core/Group.h"
#include "core/FloatingWindow.h"
#include "core/DockWidget.h"
#include "core/DockWidget_p.h"
#include "core/MainWindow.h"
#include "core/DropIndicatorOverlay.h"
#include "core/indicators/ClassicIndicators.h"
#include "core/indicators/NullIndicators.h"
#include "core/indicators/SegmentedIndicators.h"

#include "Window.h"

#include <algorithm>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

namespace KDDockWidgets {
static Core::DropIndicatorOverlay *
createDropIndicatorOverlay(Core::DropArea *dropArea)
{
#ifdef Q_OS_WASM
    // On WASM windows don't support translucency, which is required for the classic indicators.
    return new SegmentedIndicators(dropArea);
#endif

    switch (ViewFactory::s_dropIndicatorType) {
    case DropIndicatorType::Classic:
        return new Core::ClassicIndicators(dropArea);
    case DropIndicatorType::Segmented:
        return new Core::SegmentedIndicators(dropArea);
    case DropIndicatorType::None:
        return new Core::NullIndicators(dropArea);
    }

    return new Core::ClassicIndicators(dropArea);
}
}

DropArea::DropArea(View *parent, MainWindowOptions options, bool isMDIWrapper)
    : Layout(ViewType::DropArea, Config::self().viewFactory()->createDropArea(this, parent))
    , m_isMDIWrapper(isMDIWrapper)
    , m_dropIndicatorOverlay(createDropIndicatorOverlay(this))
    , m_centralFrame(createCentralFrame(options))
{
    setRootItem(new Core::ItemBoxContainer(view()));
    DockRegistry::self()->registerLayout(this);

    if (parent)
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
                // The title of our MDI group will need to change to the app name if we have more
                // than 1 dock widget nested
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
    delete m_dropIndicatorOverlay;
    qCDebug(creation) << "~DropArea";
}

Core::Group::List DropArea::groups() const
{
    const Core::Item::List children = m_rootItem->items_recursive();
    Core::Group::List groups;

    for (const Core::Item *child : children) {
        if (auto view = child->guestView()) {
            if (!view->freed()) {
                if (auto group = view->asGroupController()) {
                    groups << group;
                }
            }
        }
    }

    return groups;
}

Core::Group *DropArea::groupContainingPos(QPoint globalPos) const
{
    const Core::Item::List &items = this->items();
    for (Core::Item *item : items) {
        auto group = item->asGroupController();
        if (!group || !group->isVisible()) {
            continue;
        }

        if (group->containsMouse(globalPos))
            return group;
    }
    return nullptr;
}

void DropArea::updateFloatingActions()
{
    const Core::Group::List groups = this->groups();
    for (Core::Group *group : groups)
        group->updateFloatingActions();
}

Core::Item *DropArea::centralFrame() const
{
    for (Core::Item *item : this->items()) {
        if (auto group = item->asGroupController()) {
            if (group->isCentralFrame())
                return item;
        }
    }
    return nullptr;
}

void DropArea::addDockWidget(Core::DockWidget *dw, Location location,
                             Core::DockWidget *relativeTo, InitialOption option)
{
    if (!dw || dw == relativeTo || location == Location_None) {
        qWarning() << Q_FUNC_INFO << "Invalid parameters" << dw << relativeTo << location;
        return;
    }

    if ((option.visibility == InitialVisibilityOption::StartHidden) && dw->d->group() != nullptr) {
        // StartHidden is just to be used at startup, not to moving stuff around
        qWarning() << Q_FUNC_INFO << "Dock widget already exists in the layout";
        return;
    }

    if (!validateAffinity(dw))
        return;

    Core::DockWidget::Private::UpdateActions actionsUpdater(dw);

    Core::Group *group = nullptr;
    Core::Group *relativeToFrame = relativeTo ? relativeTo->d->group() : nullptr;

    dw->d->saveLastFloatingGeometry();

    const bool hadSingleFloatingFrame = hasSingleFloatingFrame();

    // Check if the dock widget already exists in the layout
    if (containsDockWidget(dw)) {
        Core::Group *oldFrame = dw->d->group();
        if (oldFrame->hasSingleDockWidget()) {
            Q_ASSERT(oldFrame->containsDockWidget(dw));
            // The group only has this dock widget, and the group is already in the layout. So move
            // the group instead
            group = oldFrame;
        } else {
            group = new Core::Group();
            group->addTab(dw);
        }
    } else {
        group = new Core::Group();
        group->addTab(dw);
    }

    if (option.startsHidden()) {
        addWidget(dw->view(), location, relativeToFrame, option);
    } else {
        addWidget(group->view(), location, relativeToFrame, option);
    }

    if (hadSingleFloatingFrame && !hasSingleFloatingFrame()) {
        // The dock widgets that already existed in our layout need to have their floatAction()
        // updated otherwise it's still checked. Only the dropped dock widget got updated
        updateFloatingActions();
    }
}

bool DropArea::containsDockWidget(Core::DockWidget *dw) const
{
    return dw->d->group() && Layout::containsFrame(dw->d->group());
}

bool DropArea::hasSingleFloatingFrame() const
{
    const Core::Group::List groups = this->groups();
    return groups.size() == 1 && groups.first()->isFloating();
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

void DropArea::layoutParentContainerEqually(Core::DockWidget *dw)
{
    Core::Item *item = itemForFrame(dw->d->group());
    if (!item) {
        qWarning() << Q_FUNC_INFO << "Item not found for" << dw << dw->d->group();
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

    Core::Group *group = groupContainingPos(
        globalPos); // Group is nullptr if MainWindowOption_HasCentralFrame isn't set
    m_dropIndicatorOverlay->setWindowBeingDragged(true);
    m_dropIndicatorOverlay->setHoveredFrame(group);
    draggedWindow->updateTransparency(true);

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
    Core::FloatingWindow *floatingWindow = droppedWindow->floatingWindow();

    if (!floatingWindow) {
        qWarning() << Q_FUNC_INFO << "Expected floating window controller";
        return false;
    }

    if (!floatingWindow->view()) {
        qWarning() << Q_FUNC_INFO << "Expected floating window view";
        return false;
    }

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
    Core::Group *acceptingGroup = m_dropIndicatorOverlay->hoveredFrame();
    if (!(acceptingGroup || isOutterLocation(droploc))) {
        qWarning() << "DropArea::drop: asserted with group=" << acceptingGroup
                   << "; Location=" << droploc;
        return false;
    }

    return drop(droppedWindow, acceptingGroup, droploc);
}

bool DropArea::drop(WindowBeingDragged *draggedWindow, Core::Group *acceptingGroup,
                    DropLocation droploc)
{
    Core::FloatingWindow *droppedWindow =
        draggedWindow ? draggedWindow->floatingWindow() : nullptr;

    if (isWayland() && !droppedWindow) {
        // This is the Wayland special case.
        // With other platforms, when detaching a tab or dock widget we create the FloatingWindow
        // immediately. With Wayland we delay the floating window until we drop it. Ofc, we could
        // just dock the dockwidget without the temporary FloatingWindow, but this way we reuse 99%
        // of the rest of the code, without adding more wayland special cases
        droppedWindow =
            draggedWindow ? draggedWindow->draggable()->makeWindow()->floatingWindow() : nullptr;
        if (!droppedWindow) {
            // Doesn't happen
            qWarning() << Q_FUNC_INFO << "Wayland: Expected window" << draggedWindow;
            return false;
        }
    }

    bool result = true;
    const bool needToFocusNewlyDroppedWidgets =
        Config::self().flags() & Config::Flag_TitleBarIsFocusable;
    const Core::DockWidget::List droppedDockWidgets = needToFocusNewlyDroppedWidgets
        ? droppedWindow->layout()->dockWidgets()
        : Core::DockWidget::List(); // just so save some memory allocations for the case
                                    // where this
    // variable isn't used

    switch (droploc) {
    case DropLocation_Left:
    case DropLocation_Top:
    case DropLocation_Bottom:
    case DropLocation_Right:
        result = drop(droppedWindow->view(),
                      DropIndicatorOverlay::multisplitterLocationFor(droploc), acceptingGroup);
        break;
    case DropLocation_OutterLeft:
    case DropLocation_OutterTop:
    case DropLocation_OutterRight:
    case DropLocation_OutterBottom:
        result = drop(droppedWindow->view(),
                      DropIndicatorOverlay::multisplitterLocationFor(droploc), nullptr);
        break;
    case DropLocation_Center:
        qCDebug(hovering) << "Tabbing" << droppedWindow << "into" << acceptingGroup;
        if (!validateAffinity(droppedWindow, acceptingGroup))
            return false;
        acceptingGroup->addTab(droppedWindow);
        break;

    default:
        qWarning() << "DropArea::drop: Unexpected drop location"
                   << m_dropIndicatorOverlay->currentDropLocation();
        result = false;
        break;
    }

    if (result) {
        // Window receiving the drop gets raised
        // Window receiving the drop gets raised.
        // Exception: Under EGLFS we don't raise the fullscreen main window, as then all floating
        // windows would go behind. It's also unneeded to raise, as it's fullscreen.

        const bool isEGLFSRootWindow =
            isEGLFS() && (view()->window()->isFullScreen() || window()->isMaximized());
        if (!isEGLFSRootWindow)
            view()->raiseAndActivate();

        if (needToFocusNewlyDroppedWidgets) {
            // Let's also focus the newly dropped dock widget
            if (!droppedDockWidgets.isEmpty()) {
                // If more than 1 was dropped, we only focus the first one
                Core::Group *group = droppedDockWidgets.first()->d->group();
                group->FocusScope::focus(Qt::MouseFocusReason);
            } else {
                // Doesn't happen.
                qWarning() << Q_FUNC_INFO << "Nothing was dropped?";
            }
        }
    }

    return result;
}

bool DropArea::drop(View *droppedWindow, KDDockWidgets::Location location,
                    Core::Group *relativeTo)
{
    qCDebug(docking) << "DropArea::addFrame";

    if (auto dock = droppedWindow->asDockWidgetController()) {
        if (!validateAffinity(dock))
            return false;

        auto group = new Core::Group();
        group->addTab(dock);
        addWidget(group->view(), location, relativeTo, DefaultSizeMode::FairButFloor);
    } else if (auto floatingWindow = droppedWindow->asFloatingWindowController()) {
        if (!validateAffinity(floatingWindow))
            return false;

        addMultiSplitter(floatingWindow->dropArea(), location, relativeTo,
                         DefaultSizeMode::FairButFloor);

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
bool DropArea::validateAffinity(T *window, Core::Group *acceptingGroup) const
{
    if (!DockRegistry::self()->affinitiesMatch(window->affinities(), affinities())) {
        return false;
    }

    if (acceptingGroup) {
        // We're dropping into another group (as tabbed), so also check the affinity of the group
        // not only of the main window, which might be more forgiving
        if (!DockRegistry::self()->affinitiesMatch(window->affinities(),
                                                   acceptingGroup->affinities())) {
            return false;
        }
    }

    return true;
}

bool DropArea::isMDIWrapper() const
{
    return m_isMDIWrapper;
}

Core::DockWidget *DropArea::mdiDockWidgetWrapper() const
{
    if (m_isMDIWrapper) {
        return view()->parentView()->asDockWidgetController();
    }

    return nullptr;
}

Core::Group *DropArea::createCentralFrame(MainWindowOptions options)
{
    Core::Group *group = nullptr;

    if (options & MainWindowOption_HasCentralFrame) {
        FrameOptions groupOptions = FrameOption_IsCentralFrame;
        const bool hasPersistentCentralWidget =
            (options & MainWindowOption_HasCentralWidget) == MainWindowOption_HasCentralWidget;
        if (hasPersistentCentralWidget) {
            groupOptions |= FrameOption_NonDockable;
        } else {
            // With a persistent central widget we don't allow detaching it
            groupOptions |= FrameOption_AlwaysShowsTabs;
        }

        group = new Core::Group(nullptr, groupOptions);
        group->setObjectName(QStringLiteral("central group"));
    }

    return group;
}


bool DropArea::validateInputs(View *widget, Location location,
                              const Core::Group *relativeToFrame, InitialOption option) const
{
    if (!widget) {
        qWarning() << Q_FUNC_INFO << "Widget is null";
        return false;
    }

    const bool isDockWidget = widget->is(ViewType::DockWidget);
    const bool isStartHidden = option.startsHidden();

    const bool isLayout = widget->is(ViewType::DropArea) || widget->is(ViewType::MDILayout);
    if (!widget->is(ViewType::Frame) && !isLayout && !isDockWidget) {
        qWarning() << Q_FUNC_INFO << "Unknown widget type" << widget;
        return false;
    }

    if (isDockWidget != isStartHidden) {
        qWarning() << Q_FUNC_INFO << "Wrong parameters" << isDockWidget << isStartHidden;
        return false;
    }

    if (relativeToFrame && relativeToFrame->view()->equals(widget)) {
        qWarning() << Q_FUNC_INFO << "widget can't be relative to itself";
        return false;
    }

    Core::Item *item = itemForFrame(widget->asGroupController());

    if (containsItem(item)) {
        qWarning() << Q_FUNC_INFO << "DropArea::addWidget: Already contains" << widget;
        return false;
    }

    if (location == Location_None) {
        qWarning() << Q_FUNC_INFO << "DropArea::addWidget: not adding to location None";
        return false;
    }

    const bool relativeToThis = relativeToFrame == nullptr;

    Core::Item *relativeToItem = itemForFrame(relativeToFrame);
    if (!relativeToThis && !containsItem(relativeToItem)) {
        qWarning() << "DropArea::addWidget: Doesn't contain relativeTo:"
                   << "; relativeToFrame=" << relativeToFrame
                   << "; relativeToItem=" << relativeToItem << "; options=" << option;
        return false;
    }

    return true;
}

void DropArea::addWidget(View *w, Location location, Core::Group *relativeToWidget,
                         InitialOption option)
{

    auto group = w->asGroupController();
    if (itemForFrame(group) != nullptr) {
        // Item already exists, remove it.
        // Changing the group parent will make the item clean itself up. It turns into a placeholder
        // and is removed by unrefOldPlaceholders
        group->setParentView(nullptr); // so ~Item doesn't delete it
        group->setLayoutItem(nullptr); // so Item is destroyed, as there's no refs to it
    }

    // Make some sanity checks:
    if (!validateInputs(w, location, relativeToWidget, option))
        return;

    Core::Item *relativeTo = itemForFrame(relativeToWidget);
    if (!relativeTo)
        relativeTo = m_rootItem;

    Core::Item *newItem = nullptr;

    Core::Group::List groups = groupsFrom(w);
    unrefOldPlaceholders(groups);
    auto dw = w->asDockWidgetController();
    auto thisView = view();

    if (group) {
        newItem = new Core::Item(thisView);
        newItem->setGuestView(group->view());
    } else if (dw) {
        newItem = new Core::Item(thisView);
        group = new Core::Group();
        newItem->setGuestView(group->view());
        group->addTab(dw, option);
    } else if (auto ms = w->asDropAreaController()) {
        newItem = ms->m_rootItem;
        newItem->setHostView(thisView);

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
    Core::ItemBoxContainer::insertItemRelativeTo(newItem, relativeTo, location, option);

    if (dw && option.startsHidden())
        delete group;
}

void DropArea::addMultiSplitter(Core::DropArea *sourceMultiSplitter, Location location,
                                Core::Group *relativeTo, InitialOption option)
{
    qCDebug(addwidget) << Q_FUNC_INFO << sourceMultiSplitter << location << relativeTo;
    addWidget(sourceMultiSplitter->view(), location, relativeTo, option);

    // Some widgets changed to/from floating
    updateFloatingActions();
}

QVector<Core::Separator *> DropArea::separators() const
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

void DropArea::layoutEqually(Core::ItemBoxContainer *container)
{
    if (container) {
        container->layoutEqually_recursive();
    } else {
        qWarning() << Q_FUNC_INFO << "null container";
    }
}

void DropArea::setRootItem(Core::ItemBoxContainer *root)
{
    Layout::setRootItem(root);
    m_rootItem = root;
}

Core::ItemBoxContainer *DropArea::rootItem() const
{
    return m_rootItem;
}

QRect DropArea::rectForDrop(const WindowBeingDragged *wbd, Location location,
                            const Core::Item *relativeTo) const
{
    Core::Item item(nullptr);
    if (!wbd)
        return {};

    item.setSize(wbd->size().boundedTo(wbd->maxSize()));
    item.setMinSize(wbd->minSize());
    item.setMaxSizeHint(wbd->maxSize());

    Core::ItemBoxContainer *container =
        relativeTo ? relativeTo->parentBoxContainer() : m_rootItem;

    return container->suggestedDropRect(&item, relativeTo, location);
}

bool DropArea::deserialize(const LayoutSaver::MultiSplitter &l)
{
    setRootItem(new Core::ItemBoxContainer(view()));
    return Layout::deserialize(l);
}

int DropArea::numSideBySide_recursive(Qt::Orientation o) const
{
    return m_rootItem->numSideBySide_recursive(o);
}

DropLocation DropArea::currentDropLocation() const
{
    return m_dropIndicatorOverlay ? m_dropIndicatorOverlay->currentDropLocation() : DropLocation_None;
}
