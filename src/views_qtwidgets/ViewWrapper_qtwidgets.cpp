/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewWrapper_qtwidgets.h"

#include <QDebug>

using namespace KDDockWidgets::Views;

ViewWrapper_qtwidgets::ViewWrapper_qtwidgets(QWidget *widget)
    : ViewWrapper(widget)
    , m_widget(widget)
{
}

void ViewWrapper_qtwidgets::setObjectName(const QString &name)
{
    m_widget->setObjectName(name);
}

QRect ViewWrapper_qtwidgets::geometry() const
{
    return m_widget->geometry();
}

QPoint ViewWrapper_qtwidgets::mapToGlobal(QPoint localPt) const
{
    return m_widget->mapToGlobal(localPt);
}

QPoint ViewWrapper_qtwidgets::mapFromGlobal(QPoint globalPt) const
{
    return m_widget->mapFromGlobal(globalPt);
}

void ViewWrapper_qtwidgets::setGeometry(QRect rect)
{
    m_widget->setGeometry(rect);
}

QWindow *ViewWrapper_qtwidgets::windowHandle() const
{
    return m_widget->windowHandle();
}

bool ViewWrapper_qtwidgets::isTopLevel() const
{
    return m_widget->isTopLevel();
}

void ViewWrapper_qtwidgets::setVisible(bool is)
{
    m_widget->setVisible(is);
}

bool ViewWrapper_qtwidgets::isVisible() const
{
    return m_widget->isVisible();
}

void ViewWrapper_qtwidgets::move(int x, int y)
{
    m_widget->move(x, y);
}

void ViewWrapper_qtwidgets::move(QPoint pt)
{
    m_widget->move(pt);
}

void ViewWrapper_qtwidgets::activateWindow()
{
    m_widget->activateWindow();
}

bool ViewWrapper_qtwidgets::isMaximized() const
{
    return m_widget->isMaximized();
}

QSize ViewWrapper_qtwidgets::maximumSize() const
{
    return m_widget->maximumSize();
}

void ViewWrapper_qtwidgets::setSize(int x, int y)
{
    m_widget->resize(x, y);
}
