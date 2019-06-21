/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "Item_p.h"
#include "MultiSplitterLayout_p.h"
#include "Logging_p.h"
#include "AnchorGroup_p.h"

#include <QEvent>

using namespace KDDockWidgets;

class Item::Private {
public:

    Private(Item *qq, QWidget *widget, MultiSplitterLayout *parent)
        : q(qq)
        , m_anchorGroup(parent)
        , m_widget(widget)
        , m_geometry(m_widget->geometry())
    {
    }

    void updateObjectName();
    Item *const q;
    AnchorGroup m_anchorGroup;
    const QPointer<QWidget> m_widget;
    QPointer<MultiSplitterLayout> m_layout;
    QRect m_geometry;
    bool m_destroying = false;
};

Item::Item(QWidget *widget, MultiSplitterLayout *parent)
    : QObject(parent)
    , d(new Private(this, widget, parent))
{
    Q_ASSERT(parent);
    Q_ASSERT(d->m_widget);
    setLayout(parent);
    d->m_widget->installEventFilter(this);

    // auto destruction
    connect(d->m_widget, &QObject::destroyed, this, [this] {
        if (!d->m_destroying) {
            d->m_destroying = true;
            delete this;
        }
    });

    connect(d->m_widget, &QObject::objectNameChanged, this, [this] { d->updateObjectName(); });
    d->updateObjectName();
}

Item::~Item()
{
    if (!d->m_destroying) {
        d->m_destroying = true;
        delete d->m_widget;
    }

    if (d->m_layout) {
        d->m_layout->removeItem(this);
    }
    delete d;
}

int Item::x() const
{
    return d->m_geometry.x();
}

int Item::y() const
{
    return d->m_geometry.y();
}

QPoint Item::pos() const
{
    return d->m_geometry.topLeft();
}

int Item::position(Qt::Orientation orientation) const
{
    return orientation == Qt::Vertical ? x()
                                       : y();
}

QSize Item::size() const
{
    return d->m_geometry.size();
}

int Item::width() const
{
    return size().width();
}

int Item::height() const
{
    return size().height();
}

bool Item::isVisible() const
{
    Q_ASSERT(d->m_widget);
    return d->m_widget->isVisible();
}

void Item::setVisible(bool v)
{
    Q_ASSERT(d->m_widget);
    d->m_widget->setVisible(v);
}

void Item::setGeometry(QRect geo)
{
    Q_ASSERT(d->m_widget);
    if (geo != d->m_geometry) {

        GeometryDiff geoDiff(d->m_geometry, geo);

        d->m_geometry = geo;
        d->m_widget->setGeometry(geo);

        if (d->m_anchorGroup.isValid() && geoDiff.onlyOneSideChanged) {
            const int lengthDelta = length(geoDiff.orientation()) - minLength(geoDiff.orientation());
            if (lengthDelta < 0) {
                Anchor *anchorThatMoved = anchor(geoDiff);
                Q_ASSERT(anchorThatMoved);
                Anchor *anchorToMove = d->m_anchorGroup.oppositeAnchor(anchorThatMoved);
                Q_ASSERT(anchorToMove);
                anchorToMove->setPosition(anchorToMove->position() - (lengthDelta * geoDiff.signess()));
            }
        }
    }
}

QRect Item::geometry() const
{
    return d->m_geometry;
}

bool Item::eventFilter(QObject *o, QEvent *e)
{
    if (!d->m_layout)
        return false;

    if (e->type() == QEvent::ParentChange && !d->m_layout->m_beingMergedIntoAnotherMultiSplitter) {
        if (o->parent() != d->m_layout->parentWidget())
            d->m_layout->removeItem(this);
    } else if (e->type() == QEvent::Show || e->type() == QEvent::Hide) {
        d->m_layout->emitVisibleWidgetCountChanged();
    }
    return false;
}

QWidget *Item::widget() const
{
    return d->m_widget;
}

QWidget *Item::parentWidget() const
{
    Q_ASSERT(d->m_widget);
    return d->m_widget->parentWidget();
}

MultiSplitterLayout *Item::layout() const
{
    return d->m_layout;
}

void Item::setLayout(MultiSplitterLayout *m)
{
    Q_ASSERT(m);
    Q_ASSERT(d->m_widget);
    if (m != d->m_layout) {
        d->m_layout = m;
        d->m_anchorGroup.layout = m;
        setParent(m);
        d->m_widget->setParent(m->parentWidget());
    }
}

int Item::length(Qt::Orientation orientation) const
{
    return KDDockWidgets::widgetLength(this, orientation);
}

int Item::minLength(Qt::Orientation orientation) const
{
    return KDDockWidgets::widgetMinLength(this, orientation);
}

Anchor *Item::anchor(Anchor::Side side, Qt::Orientation orientation) const
{
    return d->m_anchorGroup.anchor(side, orientation);
}

Anchor *Item::anchor(const GeometryDiff &geoDiff) const
{
    if (!geoDiff.onlyOneSideChanged)
        return nullptr;
    if (geoDiff.leftDiff)
        return d->m_anchorGroup.left;
    if (geoDiff.topDiff)
        return d->m_anchorGroup.top;
    if (geoDiff.bottomDiff)
        return d->m_anchorGroup.bottom;
    if (geoDiff.rightDiff)
        return d->m_anchorGroup.right;

    Q_UNREACHABLE();
    return nullptr;
}

AnchorGroup& Item::anchorGroup()
{
    return d->m_anchorGroup;
}

const AnchorGroup &Item::anchorGroup() const
{
    return d->m_anchorGroup;
}

int Item::cumulativeMinLength(Anchor::Side side, Qt::Orientation orientation) const
{
    return minLength(orientation) + anchor(Anchor::oppositeSide(side), orientation)->cumulativeMinLength(side);
}

int Item::minimumWidth() const
{
    Q_ASSERT(d->m_widget);
    return d->m_widget->minimumWidth();
}

int Item::minimumHeight() const
{
    Q_ASSERT(d->m_widget);
    return d->m_widget->minimumHeight();
}

QSize Item::minimumSize() const
{
    Q_ASSERT(d->m_widget);
    return d->m_widget->minimumSize();
}

QSize Item::minimumSizeHint() const
{
    Q_ASSERT(d->m_widget);
    return d->m_widget->minimumSizeHint();
}

void Item::Private::updateObjectName()
{
    q->setObjectName(m_widget->objectName());
}
