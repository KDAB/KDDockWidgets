/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "View.h"
#include "private/multisplitter/Item_p.h"

#include <QWidget> // TODOv2 remove

using namespace KDDockWidgets;

namespace KDDockWidgets {
static qint64 s_nextId = 1;
}

View::View(Controller *controller, Type type, QObject *thisObj)
    : m_controller(controller)
    , m_thisObj(thisObj)
    , m_id(QString::number(KDDockWidgets::s_nextId++))
    , m_type(type)
{
}

View::~View()
{
    m_inDtor = true;

    if (!freed()) {
        // TODOv2
        // Views should be deleted via View::free()!
        // However some of our deletes are coming from widgets parent destroying their children
        // But we want the controllers to drive things instead. For now detect the view destruction
        // and destroy its controller, which was the old behaviour.
        delete m_controller;
    }
}

QString View::id() const
{
    return m_id;
}

View::Type View::type() const
{
    return m_type;
}

QObject *View::asQObject() const
{
    return m_thisObj;
}

QWidget *View::asQWidget() const
{
    return qobject_cast<QWidget *>(m_thisObj);
}

QObject *View::parent() const
{
    return m_thisObj->parent();
}

void View::free()
{
    if (m_freed) {
        qWarning() << Q_FUNC_INFO << "Free already called";
        return;
    }

    m_freed = true;
    free_impl();
}

bool View::freed() const
{
    return m_freed;
}

bool View::inDtor() const
{
    return m_inDtor;
}

void View::free_impl()
{
    delete this;
}

QSize View::sizeHint() const
{
    return {};
}

QSize View::size() const
{
    return geometry().size();
}

QPoint View::pos() const
{
    return geometry().topLeft();
}

QRect View::rect() const
{
    return QRect(QPoint(0, 0), size());
}

int View::x() const
{
    return geometry().x();
}

int View::y() const
{
    return geometry().y();
}

int View::height() const
{
    return geometry().height();
}

int View::width() const
{
    return geometry().width();
}

void View::resize(QSize sz)
{
    setSize(sz.width(), sz.height());
}

QSize View::boundedMaxSize(QSize min, QSize max)
{
    // Max should be bigger than min, but not bigger than the hardcoded max
    max = max.boundedTo(Layouting::Item::hardcodedMaximumSize);

    // 0 interpreted as not having max
    if (max.width() <= 0)
        max.setWidth(Layouting::Item::hardcodedMaximumSize.width());
    if (max.height() <= 0)
        max.setHeight(Layouting::Item::hardcodedMaximumSize.height());

    max = max.expandedTo(min);

    return max;
}

/** static */
QSize View::hardcodedMinimumSize()
{
    return Layouting::Item::hardcodedMinimumSize;
}