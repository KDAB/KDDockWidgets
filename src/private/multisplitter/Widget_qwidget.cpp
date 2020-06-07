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

#include "Widget_qwidget.h"
#include "Item_p.h"

#include <QDebug>

using namespace Layouting;

Widget_qwidget::~Widget_qwidget()
{
}

QSize Widget_qwidget::sizeHint() const
{
    return m_thisWidget->sizeHint();
}

QSize Widget_qwidget::minSize() const
{
    return widgetMinSize(m_thisWidget);
}

QSize Widget_qwidget::maxSizeHint() const
{
    return widgetMaxSize(m_thisWidget);
}

QRect Widget_qwidget::geometry() const
{
    return m_thisWidget->geometry();
}

void Widget_qwidget::setGeometry(QRect rect)
{
    m_thisWidget->setGeometry(rect);
}

void Widget_qwidget::setParent(Widget *parent)
{
    if (!parent) {
        m_thisWidget->setParent(nullptr);
        return;
    }

    if (auto qwidget = qobject_cast<QWidget*>(parent->asQObject())) {
        m_thisWidget->setParent(qwidget);
    } else {
        qWarning() << Q_FUNC_INFO << "parent is not a widget, you have a bug" << parent->asQObject();
        Q_ASSERT(false);
    }
}

QDebug &Widget_qwidget::dumpDebug(QDebug &d) const
{
    d << " Dump Start: Host=" << m_thisWidget << rect()
      << "; dpr=" << m_thisWidget->devicePixelRatio() << ")";

    return d;
}

bool Widget_qwidget::isVisible() const
{
    return m_thisWidget->isVisible();
}

void Widget_qwidget::setVisible(bool is) const
{
    m_thisWidget->setVisible(is);
}

std::unique_ptr<Widget> Widget_qwidget::parentWidget() const
{
    if (auto pw = m_thisWidget->parentWidget()) {
        return std::unique_ptr<Widget>(new Widget_qwidget(pw));
    }

    return {};
}

/* uncomment when needed
std::unique_ptr<Widget> Widget_qwidget::window() const
{
    if (auto window = m_thisWidget->window()) {
        return std::unique_ptr<Widget>(new Widget_qwidget(window));
    }

    return {};
}
*/

void Widget_qwidget::show()
{
    m_thisWidget->show();
}

void Widget_qwidget::hide()
{
    m_thisWidget->hide();
}

void Widget_qwidget::move(int x, int y)
{
    m_thisWidget->move(x, y);
}

QSize Widget_qwidget::widgetMinSize(const QWidget *w)
{
    const int minW = w->minimumWidth() > 0 ? w->minimumWidth()
                                           : w->minimumSizeHint().width();

    const int minH = w->minimumHeight() > 0 ? w->minimumHeight()
                                            : w->minimumSizeHint().height();

    return QSize(minW, minH).expandedTo(Item::hardcodedMinimumSize);
}

QSize Widget_qwidget::widgetMaxSize(const QWidget *w)
{
    // The max size is usually QWidget::maximumSize(), but we also honour the QSizePolicy::Fixed+sizeHint() case
    // as widgets don't need to have QWidget::maximumSize() to have a max size honoured

    const QSize min = widgetMinSize(w);
    QSize max = w->maximumSize();
    max = boundedMaxSize(min, max); // for safety against weird values

    const QSizePolicy policy = w->sizePolicy();

    if (policy.verticalPolicy() == QSizePolicy::Fixed || policy.verticalPolicy() == QSizePolicy::Maximum)
        max.setHeight(qMin(max.height(), w->sizeHint().height()));
    if (policy.horizontalPolicy() == QSizePolicy::Fixed || policy.horizontalPolicy() == QSizePolicy::Maximum)
        max.setWidth(qMin(max.width(), w->sizeHint().width()));

    max = boundedMaxSize(min, max); // for safety against weird values
    return max;
}

void Widget_qwidget::setSize(int width, int height)
{
    m_thisWidget->resize(QSize(width, height));
}

void Widget_qwidget::setWidth(int width)
{
    setSize(width, m_thisWidget->height());
}

void Widget_qwidget::setHeight(int height)
{
    setSize(m_thisWidget->width(), height);
}
