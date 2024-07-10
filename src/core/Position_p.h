/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file Helper class so dockwidgets can be restored to their previous position.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDDOCKWIDGETS_POSITION_P_H
#define KDDOCKWIDGETS_POSITION_P_H

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/LayoutSaver.h"
#include "ObjectGuard_p.h"

#include <kdbindings/signal.h>

#include <memory>
#include <unordered_map>

namespace KDDockWidgets {

namespace Core {
class Item;
class DockWidget;
class Group;
class Layout;
class LayoutingHost;
}

/**
 * @internal
 * @brief Represents the DockWidget's last position.
 *
 * The DockWidget's position is saved when it's closed and restored when it's shown.
 * This class holds that position.
 *
 * This class is not directly related to LayoutSaver which saves/restores in bulk. It's more
 * for redocking back when you double-click a floating dock widget title-bar for example.
 */
class DOCKS_EXPORT_FOR_UNIT_TESTS Position
{
    KDDW_DELETE_COPY_CTOR(Position)
public:
    typedef std::shared_ptr<Position> Ptr;
    Position() = default;
    ~Position();

    void deserialize(const LayoutSaver::Position &);
    LayoutSaver::Position serialize() const;

    /**
     * @brief Returns whether the Position is valid. If invalid then the DockWidget was never
     * in a MainWindow.
     */
    bool isValid() const;

    ///@brief The tab index in case the dock widget was in a TabWidget, -1 otherwise.
    int m_tabIndex = -1;

    ///@brief true if the DockWidget was floating when it was closed
    bool m_wasFloating = false;

    ///@brief Adds the last layout item where the dock widget was (or is)
    /// This is called at the moment the dock widget is added into any layout
    void addPlaceholderItem(Core::Item *placeholder);

    bool containsPlaceholder(Core::Item *) const;
    void removePlaceholders();

    ///@brief Removes the placeholders that belong to this multisplitter
    void removePlaceholders(const Core::LayoutingHost *);

    ///@brief Removes the placeholders that reference a FloatingWindow
    void removeNonMainWindowPlaceholders();

    ///@brief removes the Item @p placeholder
    void removePlaceholder(Core::Item *placeholder);

    /// The amount of placeholders we know about
    /// this will be either:
    /// 0 - if dock widget hasn't been docked
    /// 1 - if it has been docked
    /// 2 - if it has been docked to main window and to a floating window
    /// We don't support memorizing more than 1 main window or more than 1 floating window
    int placeholderCount() const;

    void saveTabIndex(int tabIndex, bool isFloating)
    {
        m_tabIndex = tabIndex;
        m_wasFloating = isFloating;
    }

    void setLastFloatingGeometry(Rect geo)
    {
        m_lastFloatingGeometry = geo;
    }

    bool wasFloating() const
    {
        return m_wasFloating;
    }

    Rect lastFloatingGeometry() const
    {
        return m_lastFloatingGeometry;
    }

    Core::Item *lastItem() const;

    int lastTabIndex() const
    {
        return m_tabIndex;
    }

    Rect lastOverlayedGeometry(SideBarLocation loc) const
    {
        auto it = m_lastOverlayedGeometries.find(loc);
        return it == m_lastOverlayedGeometries.cend() ? Rect() : it->second;
    }

    void setLastOverlayedGeometry(SideBarLocation loc, Rect rect)
    {
        m_lastOverlayedGeometries[loc] = rect;
    }

private:
    /// A RAII class so we don't forget to unref
    struct ItemRef
    {
        explicit ItemRef(KDBindings::ConnectionHandle conn, Core::Item *);
        ~ItemRef();

        bool isInMainWindow() const;

        Core::ObjectGuard<Core::Item> item;
        KDBindings::ConnectionHandle connection;

    private:
        KDDW_DELETE_COPY_CTOR(ItemRef)
    };


    // The last places where this dock widget was (or is), so it can be restored when
    // setFloating(false) or show() is called.
    std::vector<std::unique_ptr<ItemRef>> m_placeholders;
    Rect m_lastFloatingGeometry;
    std::unordered_map<SideBarLocation, Rect> m_lastOverlayedGeometries;
    bool m_clearing = false; // to prevent re-entrancy
};

}

#endif
