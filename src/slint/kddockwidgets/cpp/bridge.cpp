// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

#include "bridge.h"

// The real, cxx-generated definitions of GroupGeometry, SeparatorGeometry
// and Location that bridge.h only forward-declares. See the comment there
// for why this can't be the other way around.
#include "kddockwidgets/src/ffi.rs.h"

#include "core/layouting/Item_p.h"
#include "core/layouting/LayoutingHost_p.h"
#include "core/layouting/LayoutingGuest_p.h"
#include "core/layouting/LayoutingSeparator_p.h"

#include <unordered_map>

using namespace KDDockWidgets;

namespace kddw_slint {

namespace {

KDDockWidgets::Location toKddwLocation(Location loc)
{
    switch (loc) {
    case Location::OnLeft:
        return KDDockWidgets::Location_OnLeft;
    case Location::OnTop:
        return KDDockWidgets::Location_OnTop;
    case Location::OnRight:
        return KDDockWidgets::Location_OnRight;
    case Location::OnBottom:
        return KDDockWidgets::Location_OnBottom;
    }
    return KDDockWidgets::Location_OnRight;
}

}

// A Group, from the engine's point of view. Doesn't know anything about
// tabs or titles: it's only a rectangle with a minimum size.
class Guest : public Core::LayoutingGuest
{
public:
    explicit Guest(Core::LayoutingHost *host, std::int32_t id, Size minSize)
        : m_id(id)
        , m_minSize(minSize)
    {
        // Ownership: the Item is owned by the layouting tree once inserted
        // (ItemBoxContainer takes over as parent). It is destroyed together
        // with its Guest via LayoutingGuest's destructor/signals.
        auto item = new Core::Item(host);
        item->setGuest(this);
    }

    ~Guest() override
    {
        // LayoutingGuest's own destructor doesn't emit this; subclasses are
        // expected to (see how KDDockWidgets::Core::Group does it). The
        // Item reacts to it by removing itself from the layout tree, which
        // is what makes remove_group() actually free up the space.
        beingDestroyed.emit();
    }

    Size minSize() const override
    {
        return m_minSize;
    }

    void setMinSize(Size size)
    {
        if (size == m_minSize)
            return;
        m_minSize = size;
        // Item reacts to this by re-reading minSize()
        layoutInvalidated.emit();
    }

    Size maxSizeHint() const override
    {
        return { 10000, 10000 };
    }

    void setGeometry(Rect r) override
    {
        m_geometry = r;
    }

    void setVisible(bool is) override
    {
        m_visible = is;
    }

    Rect geometry() const override
    {
        return m_geometry;
    }

    void setHost(Core::LayoutingHost *host) override
    {
        m_host = host;
    }

    Core::LayoutingHost *host() const override
    {
        return m_host;
    }

    QString id() const override
    {
        return QString::number(m_id);
    }

    GroupGeometry descriptor() const
    {
        return { m_id, m_visible, m_geometry.x(), m_geometry.y(), m_geometry.width(), m_geometry.height() };
    }

    const std::int32_t m_id;
    Size m_minSize;
    Core::LayoutingHost *m_host = nullptr;
    Rect m_geometry;
    bool m_visible = false;
};

// A Separator, from the engine's point of view. Created and destroyed by the
// engine itself (via Item::setCreateSeparatorFunc). `id` is unique per
// DockingEngine, see its constructor.
class Separator : public Core::LayoutingSeparator
{
public:
    explicit Separator(Core::LayoutingHost *host, Qt::Orientation orientation, Core::ItemBoxContainer *container,
                       std::int32_t id)
        : Core::LayoutingSeparator(host, orientation, container)
        , m_id(id)
    {
    }

    Rect geometry() const override
    {
        return m_geometry;
    }

    void setGeometry(Rect r) override
    {
        m_geometry = r;
    }

    SeparatorGeometry descriptor() const
    {
        return { m_id, m_geometry.x(), m_geometry.y(), m_geometry.width(), m_geometry.height(), isVertical() };
    }

    const std::int32_t m_id;
    Rect m_geometry;
};

namespace {

Separator *separatorById(Core::ItemBoxContainer *box, std::int32_t id)
{
    for (auto *sep : box->separators_recursive()) {
        auto *s = static_cast<Separator *>(sep);
        if (s->m_id == id)
            return s;
    }
    return nullptr;
}

}

struct DockingEngine::Impl : public Core::LayoutingHost
{
    Impl()
    {
        m_rootItem = new Core::ItemBoxContainer(this);
    }

    bool supportsHonouringLayoutMinSize() const override
    {
        return true;
    }

    std::unordered_map<std::int32_t, std::unique_ptr<Guest>> guests;
    std::int32_t lastSeparatorId = 0;
};

DockingEngine::DockingEngine()
{
    // KDDockWidgets only lets us install one global factory function (it's
    // a plain function pointer, not a std::function), so it can't capture
    // per-instance state. It doesn't need to: the host it's handed is always
    // our Impl (the only LayoutingHost we create), which is where the
    // per-engine id counter lives. A global counter would be shared by
    // engines on different threads, e.g. Rust tests running in parallel.
    //
    // This has to happen before constructing Impl below: ItemBoxContainer's
    // constructor asserts that a factory is already installed.
    static const bool separatorFactoryInstalled = [] {
        Core::Item::setCreateSeparatorFunc(
            [](Core::LayoutingHost *host, Qt::Orientation orientation, Core::ItemBoxContainer *container) -> Core::LayoutingSeparator * {
                auto *impl = static_cast<DockingEngine::Impl *>(host);
                return new Separator(host, orientation, container, ++impl->lastSeparatorId);
            });
        return true;
    }();
    ( void )separatorFactoryInstalled;

    d = std::make_unique<Impl>();
}

DockingEngine::~DockingEngine() = default;

void DockingEngine::resize(std::int32_t width, std::int32_t height)
{
    d->m_rootItem->setSize_recursive({ width, height });
}

void DockingEngine::addGroup(std::int32_t id, std::int32_t minWidth, std::int32_t minHeight, Location location)
{
    auto guest = std::make_unique<Guest>(d.get(), id, Size(minWidth, minHeight));
    d->insertItem(guest.get(), toKddwLocation(location));
    d->guests.emplace(id, std::move(guest));
}

void DockingEngine::addGroupRelativeTo(std::int32_t id, std::int32_t minWidth, std::int32_t minHeight,
                                       Location location, std::int32_t relativeToId)
{
    auto guest = std::make_unique<Guest>(d.get(), id, Size(minWidth, minHeight));
    auto it = d->guests.find(relativeToId);
    if (it == d->guests.end()) {
        d->insertItem(guest.get(), toKddwLocation(location));
    } else {
        d->insertItemRelativeTo(guest.get(), it->second.get(), toKddwLocation(location));
    }
    d->guests.emplace(id, std::move(guest));
}

void DockingEngine::removeGroup(std::int32_t id)
{
    d->guests.erase(id);
}

void DockingEngine::setGroupMinSize(std::int32_t id, std::int32_t minWidth, std::int32_t minHeight)
{
    auto it = d->guests.find(id);
    if (it != d->guests.end())
        it->second->setMinSize(Size(minWidth, minHeight));
}

void DockingEngine::moveGroup(std::int32_t id, std::int32_t minWidth, std::int32_t minHeight, Location location,
                              std::int32_t relativeToId)
{
    if (id == relativeToId || d->guests.find(id) == d->guests.end())
        return;

    // Destroying the old Guest makes its Item remove itself from the tree
    // (see ~Guest), freeing up its space, exactly as removeGroup() does.
    // We then insert a fresh Guest under the same id, the same way
    // addGroup()/addGroupRelativeTo() do.
    d->guests.erase(id);

    auto guest = std::make_unique<Guest>(d.get(), id, Size(minWidth, minHeight));
    auto it = relativeToId != 0 ? d->guests.find(relativeToId) : d->guests.end();
    if (it == d->guests.end()) {
        d->insertItem(guest.get(), toKddwLocation(location));
    } else {
        d->insertItemRelativeTo(guest.get(), it->second.get(), toKddwLocation(location));
    }
    d->guests.emplace(id, std::move(guest));
}

DropRect DockingEngine::dropRect(std::int32_t draggedId, Location location, std::int32_t relativeToId) const
{
    auto draggedIt = d->guests.find(draggedId);
    if (draggedIt == d->guests.end())
        return { 0, 0, 0, 0 };
    Guest *dragged = draggedIt->second.get();

    // Mirrors Core::DropArea::rectForDrop: a throwaway Item, sized like the
    // Group being dragged, fed to the same suggestedDropRect() the Qt
    // frontends use for their own rubber band.
    Core::Item item(nullptr);
    item.setSize(dragged->geometry().size());
    item.setMinSize(dragged->minSize());
    item.setMaxSizeHint(dragged->maxSizeHint());

    Core::Item *relativeTo = nullptr;
    auto *container = static_cast<Core::ItemBoxContainer *>(d->m_rootItem);
    if (relativeToId != 0) {
        auto relativeToIt = d->guests.find(relativeToId);
        if (relativeToIt == d->guests.end())
            return { 0, 0, 0, 0 };
        relativeTo = relativeToIt->second->layoutItem();
        container = relativeTo->parentBoxContainer();
    }

    const Rect r = container->suggestedDropRect(&item, relativeTo, toKddwLocation(location));
    return { r.x(), r.y(), r.width(), r.height() };
}

void DockingEngine::separatorMousePress(std::int32_t id)
{
    auto *box = static_cast<Core::ItemBoxContainer *>(d->m_rootItem);
    if (auto *sep = separatorById(box, id))
        sep->onMousePress();
}

void DockingEngine::separatorMouseRelease(std::int32_t id)
{
    auto *box = static_cast<Core::ItemBoxContainer *>(d->m_rootItem);
    if (auto *sep = separatorById(box, id))
        sep->onMouseRelease();
}

void DockingEngine::separatorMouseMove(std::int32_t id, std::int32_t dx, std::int32_t dy)
{
    auto *box = static_cast<Core::ItemBoxContainer *>(d->m_rootItem);
    auto *sep = separatorById(box, id);
    if (!sep)
        return;

    // The separator's own axis (position()/onMouseMove()) is the opposite of
    // what one might expect: isVertical() means the *split* is vertical
    // (Groups stacked top/bottom), so the separator itself is a horizontal
    // line whose position is a y-coordinate, moved by vertical dragging.
    const int oldPos = sep->position();
    if (sep->isVertical())
        sep->onMouseMove({ 0, oldPos + dy });
    else
        sep->onMouseMove({ oldPos + dx, 0 });
}

rust::Vec<GroupGeometry> DockingEngine::groups() const
{
    rust::Vec<GroupGeometry> result;
    result.reserve(d->guests.size());
    for (const auto &[id, guest] : d->guests)
        result.push_back(guest->descriptor());
    return result;
}

rust::Vec<SeparatorGeometry> DockingEngine::separators() const
{
    auto *box = static_cast<Core::ItemBoxContainer *>(d->m_rootItem);
    rust::Vec<SeparatorGeometry> result;
    for (auto *sep : box->separators_recursive())
        result.push_back(static_cast<Separator *>(sep)->descriptor());
    return result;
}

std::unique_ptr<DockingEngine> new_docking_engine()
{
    return std::make_unique<DockingEngine>();
}

}
