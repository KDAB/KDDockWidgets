/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

#include <QObject>
#include <QGuiApplication>

using namespace KDDockWidgets;

// Our Private inherits from QObject since FocusScope can't (Since Frame is already QObject)
class FocusScope::Private : public QObject
{
public:
    Private(FocusScope *qq, QWidgetAdapter *thisWidget)
        : q(qq)
        , m_thisWidget(thisWidget)
    {
        connect(qApp, &QGuiApplication::focusObjectChanged,
                this, &Private::onFocusObjectChanged);

        onFocusObjectChanged(qApp->focusObject());
        m_inCtor = false;
    }

    void setIsFocused(bool);
    void onFocusObjectChanged(QObject *);
    bool isInFocusScope(WidgetType *) const;

    FocusScope *const q;
    QWidgetAdapter *const m_thisWidget;
    bool m_isFocused = false;
    bool m_inCtor = true;
};


FocusScope::FocusScope(QWidgetAdapter *thisWidget)
    : d(new Private(this, thisWidget))
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

void FocusScope::Private::setIsFocused(bool is)
{
    if (is != m_isFocused) {
        m_isFocused = is;
        if (!m_inCtor) // Hack so we don't call pure-virtual
            Q_EMIT q->isFocusedChanged();
    }
}

void FocusScope::Private::onFocusObjectChanged(QObject *obj)
{
    auto widget = qobject_cast<WidgetType*>(obj);
    if (!widget)
        return;

    setIsFocused(isInFocusScope(widget));
}

bool FocusScope::Private::isInFocusScope(WidgetType *widget) const
{
    WidgetType *p = widget;
    while (p) {
        if (p == m_thisWidget)
            return true;

        p = KDDockWidgets::Private::parentWidget(p);
    }

    return false;
}
