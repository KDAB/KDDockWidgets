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

std::shared_ptr<ViewWrapper> Window_qtquick::rootView() const
{
    if (auto quickwindow = qobject_cast<QQuickWindow *>(m_window)) {
        auto contentItem = quickwindow->contentItem();
        Q_ASSERT(contentItem->childItems().size() == 1);
        return Views::asQQuickWrapper(contentItem->childItems().first());
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
