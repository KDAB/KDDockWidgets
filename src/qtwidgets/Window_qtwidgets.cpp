/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "Window_qtwidgets.h"
#include "qtwidgets/views/ViewWrapper_qtwidgets.h"

#include <QWidget>
#include <QVariant>
#include <QWindow>
#include <QDebug>

using namespace KDDockWidgets;

Window_qtwidgets::~Window_qtwidgets() = default;

Window_qtwidgets::Window_qtwidgets(QWidget *topLevel)
    : Window_qt(topLevel->windowHandle())
{
    // QWidgetWindow is private API, we have no way for going from QWindow to the top-level QWidget
    // So set it as a property
    setProperty("kddockwidgets_qwidget", QVariant::fromValue<QWidget *>(topLevel));
}

std::shared_ptr<ViewWrapper> Window_qtwidgets::rootView() const
{
    if (!m_window)
        return {};

    if (QWidget *widget = m_window->property("kddockwidgets_qwidget").value<QWidget *>())
        return std::shared_ptr<ViewWrapper>(new Views::ViewWrapper_qtwidgets(widget));

    qWarning() << Q_FUNC_INFO << "Window does not have a root";
    return nullptr;
}

Window::Ptr Window_qtwidgets::transientParent() const
{
    if (QWindow *w = m_window->transientParent())
        return Window::Ptr(new Window_qtwidgets(w));

    return nullptr;
}
