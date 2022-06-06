/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Window_qtquick.h"
#include "views/View_qtquick.h"

#include <QWindow>
#include <QQuickWindow>
#include <QDebug>

using namespace KDDockWidgets;

Window_qtquick::~Window_qtquick()
{
}

inline View *topMostKDDWView(QQuickItem *parent)
{
    if (!parent)
        return {};

    if (auto v = qobject_cast<Views::View_qtquick *>(parent))
        return v;

    const auto children = parent->childItems();
    for (QQuickItem *item : children) {
        if (auto v = topMostKDDWView(item))
            return v;
    }

    return nullptr;
}

std::shared_ptr<ViewWrapper> Window_qtquick::rootView() const
{
    if (auto quickwindow = qobject_cast<QQuickWindow *>(m_window)) {
        auto contentItem = quickwindow->contentItem();
        if (View *view = topMostKDDWView(contentItem)) {
            // This block is for retrocompatibility with 1.x. For QtQuick the topmost "widget" is a KDDW known widget
            // and not any arbitrary user QtQuickItem.
            // TODOm3: I'd like to change it so it's normalized.
            return view->asWrapper();
        } else {
            const auto children = contentItem->childItems();
            Q_ASSERT(!children.isEmpty());

            return Views::asQQuickWrapper(contentItem->childItems().first());
        }
    } else {
        qWarning() << Q_FUNC_INFO << "Expected QQuickView";
    }

    qWarning() << Q_FUNC_INFO << "Window does not have a root";
    return {};
}

Window::Ptr Window_qtquick::transientParent() const
{
    if (QWindow *w = m_window->transientParent())
        return Window::Ptr(new Window_qtquick(w));

    return nullptr;
}
