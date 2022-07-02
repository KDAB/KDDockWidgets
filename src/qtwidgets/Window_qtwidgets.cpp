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

inline QWindow *windowForWidget(QWidget *topLevel)
{
    if (!topLevel->windowHandle())
        topLevel->winId();

    return topLevel->windowHandle();
}

Window_qtwidgets::Window_qtwidgets(QWidget *topLevel)
    : Window_qt(windowForWidget(topLevel))
{
    // QWidgetWindow is private API, we have no way for going from QWindow to the top-level QWidget
    // So set it as a property
    setProperty("kddockwidgets_qwidget", QVariant::fromValue<QWidget *>(topLevel));
}

std::shared_ptr<View> Window_qtwidgets::rootView() const
{
    if (!m_window)
        return {};

    if (QWidget *widget = m_window->property("kddockwidgets_qwidget").value<QWidget *>())
        return Views::ViewWrapper_qtwidgets::create(widget);

    qWarning() << Q_FUNC_INFO << "Window does not have a root";
    return nullptr;
}

Window::Ptr Window_qtwidgets::transientParent() const
{
    if (QWindow *w = m_window->transientParent())
        return Window::Ptr(new Window_qtwidgets(w));

    return nullptr;
}

void Window_qtwidgets::setGeometry(QRect geo) const
{
    if (auto v = rootView()) {
        // In QWidget world QWidget interface is prefered over QWindow
        v->setGeometry(geo);
    } else {
        // Go via QWindow instead
        Window_qt::setGeometry(geo);
    }
}

void Window_qtwidgets::setVisible(bool is)
{
    if (auto v = rootView()) {
        // In QWidget world QWidget interface is prefered over QWindow
        v->setVisible(is);
    } else {
        // Go via QWindow instead
        Window_qt::setVisible(is);
    }
}

bool Window_qtwidgets::supportsHonouringLayoutMinSize() const
{
    // QWidget's QLayout does this for us and propagates the min-size up to QWindow
    return true;
}

void Window_qtwidgets::destroy()
{
    if (auto v = rootView()) {
        // deleting the QWidget deletes its QWindow
        delete static_cast<Views::ViewWrapper_qtwidgets *>(v.get())->widget();
    } else {
        Window_qt::destroy();
    }
}
