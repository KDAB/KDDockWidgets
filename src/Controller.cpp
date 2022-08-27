/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Controller.h"
#include "View.h"

#include <QDebug>

using namespace KDDockWidgets;

Controller::Controller(Type type, View *view)
    : m_view(view)
    , m_type(type)
{
}

Controller::~Controller()
{
    m_inDtor = true;
    if (m_view && !m_view->inDtor())
        m_view->free();
}

Type Controller::type() const
{
    return m_type;
}

bool Controller::is(Type t) const
{
    return int(m_type) & int(t);
}

bool Controller::inDtor() const
{
    return m_inDtor;
}

View *Controller::view() const
{
    return m_view;
}

bool Controller::isVisible() const
{
    return m_view && m_view->isVisible();
}

void Controller::setVisible(bool is)
{
    if (m_view)
        m_view->setVisible(is);

    if (m_isVisible == is)
        return;

    Q_EMIT visibleChanged(is);
}

QRect Controller::rect() const
{
    if (m_view)
        return m_view->rect();

    return {};
}

QPoint Controller::mapToGlobal(QPoint localPt) const
{
    return m_view->mapToGlobal(localPt);
}

int Controller::height() const
{
    return m_view->height();
}

int Controller::width() const
{
    return m_view->width();
}

QSize Controller::size() const
{
    return m_view->size();
}

QRect Controller::geometry() const
{
    return m_view->geometry();
}

QPoint Controller::pos() const
{
    return m_view->geometry().topLeft();
}

int Controller::x() const
{
    return m_view->x();
}

int Controller::y() const
{
    return m_view->y();
}

bool Controller::close()
{
    return view() && view()->close();
}

std::shared_ptr<View> Controller::window() const
{
    return view()->rootView();
}

void Controller::show() const
{
    return view()->show();
}

void Controller::setParentView(View *parent)
{
    setParentView_impl(parent);
    Q_EMIT parentViewChanged(parent);
}

void Controller::setParentView_impl(View *parent)
{
    if (auto v = view()) {
        v->setParent(parent);
    } else {
        qWarning() << Q_FUNC_INFO << "No view()";
    }
}
