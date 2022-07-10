/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief FocusScope
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "FocusScope.h"
#include "Platform.h"
#include "ViewGuard.h"
#include "controllers/DockWidget.h"
#include "controllers/Group.h"
#include "DockRegistry.h"
#include "private/Platform_p.h"

using namespace KDDockWidgets;

// Our Private inherits from QObject since FocusScope can't (Since Frame is already QObject)
class FocusScope::Private : public QObject // clazy:exclude=missing-qobject-macro (breaks unity build with earlier cmake due to including .moc here.)
{
public:
    Private(FocusScope *qq, View *thisView)
        : q(qq)
        , m_thisView(thisView)
    {
        auto plat = Platform::instance();
        m_connection = plat->d->focusedViewChanged.connect(&Private::onFocusedViewChanged, this);

        onFocusedViewChanged(plat->focusedView());
        m_inCtor = false;
    }

    /// @brief Returns whether the last focused widget is the tab widget itself
    bool lastFocusedIsTabWidget() const
    {
        return m_lastFocusedInScope && !m_lastFocusedInScope->isNull() && m_lastFocusedInScope->is(Type::Stack);
    }

    ~Private() override;

    void setIsFocused(bool);
    void onFocusedViewChanged(std::shared_ptr<View> view);
    bool isInFocusScope(std::shared_ptr<View> view) const;

    FocusScope *const q;
    View *const m_thisView;
    bool m_isFocused = false;
    bool m_inCtor = true;
    std::shared_ptr<View> m_lastFocusedInScope;
    KDBindings::ConnectionHandle m_connection;
};

FocusScope::Private::~Private()
{
    m_connection.disconnect();
}

FocusScope::FocusScope(View *thisView)
    : d(new Private(this, thisView))
{
}

FocusScope::~FocusScope()
{
    delete d;
}

bool FocusScope::isFocused() const
{
    return d->m_isFocused;
}

void FocusScope::focus(Qt::FocusReason reason)
{
    if (d->m_lastFocusedInScope && !d->m_lastFocusedInScope->isNull() && !d->lastFocusedIsTabWidget()) {
        // When we focus the FocusScope, we give focus to the last focused widget, but let's
        // do better than focusing a tab widget. The tab widget itself being focused isn't
        // very useful.
        d->m_lastFocusedInScope->setFocus(reason);
    } else {
        if (auto group = d->m_thisView->asGroupController()) {
            if (auto dw = group->currentDockWidget()) {
                if (auto guest = dw->guestView()) {
                    if (guest->focusPolicy() != Qt::NoFocus)
                        guest->setFocus(reason);
                }
            }
        } else {
            // Not a use case right now
            d->m_thisView->setFocus(reason);
        }
    }
}

void FocusScope::Private::setIsFocused(bool is)
{
    if (is != m_isFocused) {
        m_isFocused = is;

        if (!m_inCtor) // Hack so we don't call pure-virtual
            /* Q_EMIT */ q->isFocusedChangedCallback();
    }
}

void FocusScope::Private::onFocusedViewChanged(std::shared_ptr<View> view)
{
    if (!view || view->isNull()) {
        setIsFocused(false);
        return;
    }

    const bool is = isInFocusScope(view);
    const bool focusViewChanged = !m_lastFocusedInScope || m_lastFocusedInScope->isNull() || !m_lastFocusedInScope->equals(view);
    if (is && focusViewChanged && !view->is(Type::TitleBar)) {
        m_lastFocusedInScope = view;
        setIsFocused(is);
        /* Q_EMIT */ q->focusedWidgetChangedCallback();
    } else {
        setIsFocused(is);
    }
}

bool FocusScope::Private::isInFocusScope(std::shared_ptr<View> view) const
{
    auto p = (view && !view->isNull()) ? view : std::shared_ptr<View>();
    while (p) {
        if (p->handle() == m_thisView->handle())
            return true;

        p = p->parentView();
    }

    return false;
}
