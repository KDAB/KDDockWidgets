/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Controller.h"
#include "View.h"

#include <QDebug>
#include <QWidget>

using namespace KDDockWidgets;

Controller::Controller(View *view)
    : m_view(view)
{
}

Controller::~Controller()
{
    m_inDtor = true;
    if (m_view && !m_view->inDtor())
        m_view->free();
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
    else
        qWarning() << Q_FUNC_INFO << "No view";
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

QWidget *Controller::window() const
{
    return view()->asQWidget()->window();
}
