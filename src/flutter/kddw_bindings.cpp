/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "kddw_bindings.h"

#include "../core/layouting/LayoutingSeparator_p.h"
#include "../core/layouting/LayoutingGuest_p.h"
#include "../core/layouting/LayoutingHost_p.h"
#include "../core/layouting/Item_p.h"
#include "KDDockWidgets.h"

#include <cassert>
#include <cstdint>
#include <utility>
#include <iostream>
#include <mutex>

using namespace KDDockWidgets;

namespace {

class Separator;
class Host : public KDDockWidgets::Core::LayoutingHost
{
public:
    Host();
    ~Host() override;

    Separator *
    separatorForId(int id) const;

    void onFlutterWindowResized(int h, int w);
    bool supportsHonouringLayoutMinSize() const override
    {
        return true;
    }

    void (*_separator_added_callback)(void *host, void *separator, int isVertical) = nullptr;
    void (*_separator_removed_callback)(void *host, void *separator) = nullptr;
};

class Guest : public KDDockWidgets::Core::LayoutingGuest
{
public:
    static std::uint64_t s_nextId;
    explicit Guest(Host *host, void (*callback)(void *guest, int x, int y, int width, int height, int is_visible))
        : _item(new Core::Item(host))
        , _uniqueName(QString::fromStdString("id=" + std::to_string(s_nextId)))
        , _changed_callback(callback)
    {
        _item->setGuest(this);
    }

    Size minSize() const override
    {
        return { 100, 100 };
    }

    Size maxSizeHint() const override
    {
        return { 1000, 1000 };
    }

    void setGeometry(Rect r) override
    {
        if (r == _geometry)
            return;

        _geometry = r;
        tellFlutter();
    }

    void setVisible(bool is) override
    {
        if (_isVisible == is)
            return;

        _isVisible = is;
        tellFlutter();
    }

    Rect geometry() const override
    {
        return _geometry;
    }

    void setHost(Core::LayoutingHost *parent) override
    {
        if (_layoutingHost == parent)
            return;

        _layoutingHost = parent;
    }

    Core::LayoutingHost *host() const override
    {
        return _layoutingHost;
    }

    QString id() const override
    {
        return _uniqueName;
    }

    void tellFlutter()
    {
        assert(_changed_callback);
        _changed_callback(this, _geometry.x(), _geometry.y(), _geometry.width(), _geometry.height(), _isVisible ? 1 : 0);
    }

    Core::LayoutingHost *_layoutingHost = nullptr;
    Core::Item *const _item;
    QString _uniqueName;
    Rect _geometry;
    bool _isVisible = false;

    void (*_changed_callback)(void *guest_, int x, int y, int width, int height, int is_visible) = nullptr;
};
std::uint64_t Guest::s_nextId = 0;

class Separator : public Core::LayoutingSeparator
{
public:
    explicit Separator(Core::LayoutingHost *host, Qt::Orientation orientation, Core::ItemBoxContainer *container)
        : Core::LayoutingSeparator(host, orientation, container)
        , _host(static_cast<Host *>(host))
    {
        static int counter = 0;
        _id = ++counter;

        _host->_separator_added_callback(_host, this, orientation == Qt::Vertical ? 1 : 0);
    }

    ~Separator() override
    {
        _host->_separator_removed_callback(_host, this);
    }

    Rect
    geometry() const override
    {
        return _geo;
    }

    void setGeometry(Rect g) override
    {
        if (g == _geo)
            return;

        _geo = g;
        tellFlutter();
    }

    void tellFlutter()
    {
        assert(_changed_callback);
        _changed_callback(this, _geo.x(), _geo.y(), _geo.width(), _geo.height());
    }

    Rect _geo;
    int _id = 0;
    Host *const _host;
    void (*_changed_callback)(void *separator, int x, int y, int width, int height) = nullptr;
};
}

void Host::onFlutterWindowResized(int w, int h)
{
    m_rootItem->setSize_recursive({ w, h });
}

Host::Host()
{
    static std::once_flag s_initFlag;
    std::call_once(s_initFlag, []() {
        /// Tell KDDW about our separators
        Core::Item::setCreateSeparatorFunc([](Core::LayoutingHost *host, Qt::Orientation orientation, Core::ItemBoxContainer *container) -> Core::LayoutingSeparator * {
            return new Separator(host, orientation, container);
        });
    });

    m_rootItem = new Core::ItemBoxContainer(this);
}

Host::~Host()
{
}

void on_flutter_droparea_widget_resized(void *host_, int width, int height)
{
    auto host = reinterpret_cast<Host *>(host_);
    host->onFlutterWindowResized(width, height);
}

void on_separator_mouse_button_event(void *separator_, int pressed)
{
    auto separator = reinterpret_cast<Separator *>(separator_);
    if (pressed == 1) {
        separator->onMousePress();
    } else {
        separator->onMouseRelease();
    }
}

void on_separator_mouse_move_event(void *separator_, float x, float y)
{
    auto separator = reinterpret_cast<Separator *>(separator_);
    if (separator->isVertical()) {
        const int oldPos = separator->position();
        separator->onMouseMove({ 0, oldPos + int(y) });
    } else {
        const int oldPos = separator->position();
        separator->onMouseMove({ oldPos + int(x), 0 });
    }
}

void *create_host()
{
    return new Host();
}

void delete_host(void *host)
{
    delete reinterpret_cast<Host *>(host);
}

void *create_guest(void *host, void (*callback)(void *guest, int x, int y, int width, int height, int is_visible))
{
    return new Guest(reinterpret_cast<Host *>(host), callback);
}

void delete_guest(void *guest)
{
    delete reinterpret_cast<Guest *>(guest);
}

void validate_enum(int location)
{
    auto loc = static_cast<KDDockWidgets::Location>(location);
    switch (loc) {
    case Location_None:
    case Location_OnLeft:
    case Location_OnTop:
    case Location_OnRight:
    case Location_OnBottom:
        break;
    default:
        assert(false);
    }
}

void insert_item(void *_host, void *_guest, int _location)
{
    auto host = reinterpret_cast<Host *>(_host);
    auto guest = reinterpret_cast<Guest *>(_guest);
    auto location = static_cast<KDDockWidgets::Location>(_location);

    validate_enum(location);
    assert(host);
    assert(guest);

    host->insertItem(guest, location);
}

void insert_item_relative_to(void *host_, void *guest_, void *relativeToGuest_, int location_)
{
    auto host = reinterpret_cast<Host *>(host_);
    auto guest = reinterpret_cast<Guest *>(guest_);
    auto relativeToGuest = reinterpret_cast<Guest *>(relativeToGuest_);
    auto location = static_cast<KDDockWidgets::Location>(location_);

    validate_enum(location);
    assert(host);
    assert(guest);
    assert(relativeToGuest);
    host->insertItemRelativeTo(guest, relativeToGuest, location);
}

void set_guest_changed_callback(void *guest_, void (*callback)(void *guest_, int x, int y, int width, int height, int is_visible))
{
    assert(callback);
    assert(guest_);
    auto guest = reinterpret_cast<Guest *>(guest_);
    assert(!guest->_changed_callback);
    guest->_changed_callback = callback;
}

void set_separator_changed_callback(void *separator_, void (*callback)(void *separator_, int x, int y, int width, int height))
{
    assert(callback);
    assert(separator_);
    auto separator = reinterpret_cast<Separator *>(separator_);
    separator->_changed_callback = callback;
}

void remove_guest(void *host_, void *guest_)
{
    assert(host_);
    assert(guest_);

    auto host = reinterpret_cast<Host *>(host_);
    auto guest = reinterpret_cast<Guest *>(guest_);

    host->m_rootItem->removeItem(guest->_item);
}

void set_separator_added_callback(void *host_, void (*callback)(void *host, void *separator, int isVertical))
{
    assert(host_);
    auto host = reinterpret_cast<Host *>(host_);
    assert(host->_separator_added_callback == nullptr);
    host->_separator_added_callback = callback;
}

void set_separator_removed_callback(void *host_, void (*callback)(void *host, void *separator))
{
    assert(host_);
    auto host = reinterpret_cast<Host *>(host_);
    assert(host->_separator_removed_callback == nullptr);
    host->_separator_removed_callback = callback;
}
