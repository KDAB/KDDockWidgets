/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Widget_quick.h"

#include <QDebug>
#include <QQmlEngine>

using namespace Layouting;

Widget_quick::~Widget_quick()
{
}

QSize Widget_quick::minSize() const
{
    return QSize(0, 0);
}

QRect Widget_quick::geometry() const
{
    return QRect(m_thisWidget->x(), m_thisWidget->y(),
                 m_thisWidget->width(), m_thisWidget->height());
}

void Widget_quick::setGeometry(QRect rect)
{
    m_thisWidget->setPosition(rect.topLeft());
    m_thisWidget->setSize(rect.size());
}

void Widget_quick::setParent(Widget *parent)
{
    if (!parent) {
        m_thisWidget->setParent(nullptr);
        return;
    }

    if (auto qquickitem = qobject_cast<QQuickItem*>(parent->asQObject())) {
        m_thisWidget->setParentItem(qquickitem);
        m_thisWidget->setParent(qquickitem);
    } else {
        qWarning() << Q_FUNC_INFO << "parent is not a widget, you have a bug" << parent->asQObject();
        Q_ASSERT(false);
    }
}

QDebug &Widget_quick::dumpDebug(QDebug &d) const
{
    d << " Dump Start: Host=" << m_thisWidget << rect();
    return d;
}

bool Widget_quick::isVisible() const
{
    return m_thisWidget->isVisible();
}

void Widget_quick::setVisible(bool is) const
{
    m_thisWidget->setVisible(is);
}

std::unique_ptr<Widget> Widget_quick::parentWidget() const
{
    if (auto pw = m_thisWidget->parentItem()) {
        return std::unique_ptr<Widget>(new Widget_quick(pw));
    }

    return {};
}

QSize Widget_quick::maxSizeHint() const
{
    // Some arbitrary big value
    return QSize(30000, 30000);
}

/* uncomment when needed
std::unique_ptr<Widget> Widget_quick::window() const
{
    if (auto window = m_thisWidget->window()) {
        return std::unique_ptr<Widget>(new Widget_quick(window));
    }

    return {};
}
*/

void Widget_quick::show()
{
    m_thisWidget->setVisible(true);
}

void Widget_quick::hide()
{
    m_thisWidget->setVisible(false);
}

void Widget_quick::move(int x, int y)
{
    QRect geo = geometry();
    geo.setTopLeft(QPoint(x, y));
    setGeometry(geo);
}

void Widget_quick::setSize(int width, int height)
{
    m_thisWidget->setSize(QSize(width, height));
}

void Widget_quick::setWidth(int width)
{
    m_thisWidget->setWidth(width);
}

void Widget_quick::setHeight(int height)
{
    m_thisWidget->setHeight(height);
}

QQuickItem *Widget_quick::createQQuickItem(const QString &filename, QQuickItem *parent) const
{
    auto p = parent;
    QQmlEngine *engine = nullptr;
    while (p && !engine) {
        engine = qmlEngine(p);
        p = p->parentItem();
    }

    if (!engine) {
        qWarning() << Q_FUNC_INFO << "No engine found";
        return nullptr;
    }

    QQmlComponent component(engine, filename);
    auto qquickitem = qobject_cast<QQuickItem*>(component.create());
    if (!qquickitem) {
        qWarning() << Q_FUNC_INFO << component.errorString();
        return nullptr;
    }

    qquickitem->setParentItem(parent);
    qquickitem->QObject::setParent(parent);

    return qquickitem;
}
