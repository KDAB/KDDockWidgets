/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

/**
 * @file Helper class so dockwidgets can be restored to their previous position.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "Position_p.h"
#include "DockRegistry_p.h"
#include "widgets/MultiSplitterLayout_p.h"
#include "widgets/MultiSplitter_p.h"

#include <algorithm>

using namespace KDDockWidgets;

Position::~Position()
{
    m_placeholders.clear();
}

void Position::addPlaceholderItem(Layouting::Item *placeholder)
{
    Q_ASSERT(placeholder);

    // 1. Already exists, nothing to do
    if (containsPlaceholder(placeholder))
        return;

    if (DockRegistry::self()->itemIsInMainWindow(placeholder)) {
        // 2. If we have a MainWindow placeholder we don't need nothing else
        removePlaceholders();
    } else {
        // 3. It's a placeholder to a FloatingWindow. Let's still keep any MainWindow placeholders we have
        // as FloatingWindow are temporary so we might need the MainWindow placeholder later.
        removeNonMainWindowPlaceholders();
    }

    // Make sure our list only contains valid placeholders. We save the result so we can disconnect from the lambda, since the Item might outlive LastPosition
    QMetaObject::Connection connection = QObject::connect(placeholder, &QObject::destroyed, placeholder, [this, placeholder] {
        removePlaceholder(placeholder);
    });

    m_placeholders.push_back(std::unique_ptr<ItemRef>(new ItemRef(connection, placeholder)));

    // NOTE: We use a list instead of simply two variables to keep the placeholders, because
    // a placeholder from a FloatingWindow might become a MainWindow one without we knowing,
    // like when dragging a floating window into a MainWindow. So, isInMainWindow() won't return
    // the same value always, hence we just shove them into a list, instead of giving them meaningful names in separated variables
}

QWidgetOrQuick *Position::window() const
{
    if (Layouting::Item *placeholder = layoutItem())
        return placeholder->window();

    return nullptr;
}

Layouting::Item *Position::layoutItem() const
{
    // Return the layout item that is in a MainWindow, that's where we restore the dock widget to.
    // In the future we might want to restore it to FloatingWindows.

    for (const auto &itemref : m_placeholders) {
        if (DockRegistry::self()->itemIsInMainWindow(itemref->item))
            return itemref->item;
    }

    return nullptr;
}

bool Position::containsPlaceholder(Layouting::Item *item) const
{
    for (const auto &itemRef : m_placeholders)
        if (itemRef->item == item)
            return true;

    return false;
}

void Position::removePlaceholders()
{
    QScopedValueRollback<bool>(m_clearing, true);
    m_placeholders.clear();
}

void Position::removePlaceholders(const MultiSplitter *ms)
{
    m_placeholders.erase(std::remove_if(m_placeholders.begin(), m_placeholders.end(), [ms] (const std::unique_ptr<ItemRef> &itemref) {
                             return itemref->item->hostWidget() == *ms;
                         }), m_placeholders.end());
}

void Position::removeNonMainWindowPlaceholders()
{
    auto it = m_placeholders.begin();
    while (it != m_placeholders.end()) {
        ItemRef *itemref = it->get();
        if (!DockRegistry::self()->itemIsInMainWindow(itemref->item))
            it = m_placeholders.erase(it);
        else
            ++it;
    }
}

void Position::removePlaceholder(Layouting::Item *placeholder)
{
    if (m_clearing) // reentrancy guard
        return;

    m_placeholders.erase(std::remove_if(m_placeholders.begin(), m_placeholders.end(), [placeholder] (const std::unique_ptr<ItemRef> &itemref) {
                             return itemref->item == placeholder;
    }), m_placeholders.end());
}

void Position::deserialize(const LayoutSaver::Position &lp)
{
    for (const auto &placeholder : qAsConst(lp.placeholders)) {
        MultiSplitterLayout *layout;
        int itemIndex = placeholder.itemIndex;
        if (placeholder.isFloatingWindow) {
            if (placeholder.indexOfFloatingWindow == -1) {
                continue; // Skip
            } else {
                FloatingWindow *fw = DockRegistry::self()->nestedwindows().at(placeholder.indexOfFloatingWindow);
                layout = fw->multiSplitterLayout();
            }
        } else {
            MainWindowBase *mainWindow = DockRegistry::self()->mainWindowByName(placeholder.mainWindowUniqueName);
            layout = mainWindow->multiSplitterLayout();
        }

        const Layouting::Item::List &items = layout->items();
        if (itemIndex < items.size()) {
            Layouting::Item *item = items.at(itemIndex);
            addPlaceholderItem(item);
        } else {
            // Shouldn't happen, maybe even assert
            qWarning() << Q_FUNC_INFO <<"Couldn't find item index" << itemIndex << "in" << items;
        }

    }

    m_tabIndex = lp.tabIndex;
    m_wasFloating = lp.wasFloating;
}

LayoutSaver::Position Position::serialize() const
{
    LayoutSaver::Position l;

    for (auto &itemRef : m_placeholders) {
        LayoutSaver::Placeholder p;

        Layouting::Item *item = itemRef->item;
        MultiSplitterLayout *layout = DockRegistry::self()->layoutForItem(item);
        const int itemIndex = layout->items().indexOf(item);

        auto fw = layout->multiSplitter()->floatingWindow();
        auto mainWindow = layout->multiSplitter()->mainWindow();
        Q_ASSERT(mainWindow || fw);
        p.isFloatingWindow = fw;

        if (p.isFloatingWindow) {
            p.indexOfFloatingWindow = fw->beingDeleted() ? -1 : DockRegistry::self()->nestedwindows().indexOf(fw); // TODO: Remove once we stop using deleteLater with FloatingWindow. delete would be better
        } else {
            p.mainWindowUniqueName = mainWindow->uniqueName();
            Q_ASSERT(!p.mainWindowUniqueName.isEmpty());
        }

        p.itemIndex = itemIndex;
        l.placeholders.push_back(p);
    }

    l.tabIndex = m_tabIndex;
    l.wasFloating = m_wasFloating;

    return l;
}

ItemRef::ItemRef(const QMetaObject::Connection &conn, Layouting::Item *it)
    : item(it)
    , guard(it)
    , connection(conn)
{
    item->ref();
}

ItemRef::~ItemRef()
{
    if (guard) {
        QObject::disconnect(connection);
        item->unref();
    }
}
