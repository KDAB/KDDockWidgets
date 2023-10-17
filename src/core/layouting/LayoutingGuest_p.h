/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "core/View.h"
#include "kddockwidgets/docks_export.h"
#include "QtCompat_p.h"

#include <kdbindings/signal.h>

namespace KDDockWidgets {

namespace Core {

class Item;
class LayoutingHost;

/// The interface graphical components need to implement in order to be hosted by a layout
/// The layout engine doesn't know about any GUI, only about LayoutingHost and LayoutingGuest
/// This allows to keep the layouting engine separate from the rest of KDDW and even
/// reused by non-KDDW projects
/// TODO: View is only here as a porting aid, to be removed soon.

class DOCKS_EXPORT LayoutingGuest
{
public:
    LayoutingGuest(View *v)
        : m_view(v)
    {
    }

    virtual ~LayoutingGuest();
    virtual void setLayoutItem(Item *) = 0;

    Size minSize() const
    {
        return m_view->minSize();
    }

    Size maxSizeHint() const
    {
        return m_view->maxSizeHint();
    }

    void setGeometry(Rect r)
    {
        m_view->setGeometry(r);
    }

    void setVisible(bool is) const
    {
        m_view->setVisible(is);
    }

    Rect guestGeometry() const
    {
        return m_view->geometry();
    }

    QString viewName() const
    {
        return m_view->viewName();
    }

    virtual void setHost(LayoutingHost *parent) = 0;
    virtual LayoutingHost *host() const = 0;

    View *const m_view;
    KDBindings::Signal<LayoutingHost *> hostChanged;
};

}

}
