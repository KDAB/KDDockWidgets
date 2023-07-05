/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <cmath>

#include <QMargins>

namespace KDDockWidgets {

class Size
{
public:
    Size() = default;
    Size(int width, int height)
        : m_width(width)
        , m_height(height)
    {
    }

    int width() const
    {
        return m_width;
    }

    int height() const
    {
        return m_height;
    }

    void setWidth(int w)
    {
        m_width = w;
    }

    void setHeight(int h)
    {
        m_height = h;
    }

    bool isNull() const
    {
        return m_width == 0 && m_height == 0;
    }

    bool isEmpty() const
    {
        return m_width <= 0 || m_height <= 0;
    }

    bool isValid() const
    {
        return m_width >= 0 && m_height >= 0;
    }

    Size expandedTo(Size) const
    {
        return {};
    }

    Size boundedTo(Size) const
    {
        return {};
    }

    bool operator==(Size other) const
    {
        return m_width == other.m_width && m_height == other.m_height;
    }

private:
    int m_width = 0;
    int m_height = 0;
};

class Point
{
public:
    Point() = default;
    Point(int x, int y)
        : m_x(x)
        , m_y(y)
    {
    }

    int x() const
    {
        return m_x;
    }

    int y() const
    {
        return m_y;
    }

    void setX(int x)
    {
        m_x = x;
    }

    void setY(int y)
    {
        m_y = y;
    }

    bool isNull() const
    {
        return m_x == 0 && m_y == 0;
    }

    int manhattanLength() const
    {
        return std::abs(x()) + std::abs(y());
    }

    bool operator==(Point other) const
    {
        return m_x == other.m_x && m_y == other.m_y;
    }

private:
    int m_x = 0;
    int m_y = 0;
};

/// TODOm4: Remove after everything is ported away from QtCore
class PointF
{
public:
    PointF() = default;
    PointF(Point pos)
        : m_x(pos.x())
        , m_y(pos.y())
    {
    }

    explicit PointF(double x, double y)
        : m_x(x)
        , m_y(y)
    {
    }

    double x() const
    {
        return m_x;
    }

    double y() const
    {
        return m_y;
    }

    Point toPoint() const
    {
        return Point(int(m_x), int(m_y));
    }

private:
    double m_x = 0.0;
    double m_y = 0.0;
};

class Rect
{
public:
    Rect() = default;
    Rect(Point pos, Size size)
        : m_pos(pos)
        , m_size(size)
    {
    }

    Rect(int x, int y, int width, int height)
        : m_pos(Point(x, y))
        , m_size(Size(width, height))
    {
    }

    Point pos() const
    {
        return m_pos;
    };

    Size size() const
    {
        return m_size;
    }

    int width() const
    {
        return m_size.width();
    }

    int height() const
    {
        return m_size.height();
    }

    void setWidth(int w)
    {
        m_size.setWidth(w);
    }

    void setHeight(int h)
    {
        m_size.setHeight(h);
    }

    int x() const
    {
        return m_pos.x();
    }

    int y() const
    {
        return m_pos.y();
    }

    void setSize(Size sz)
    {
        m_size = sz;
    }

    Point topLeft() const
    {
        return m_pos;
    }

    int top() const
    {
        return y();
    }

    int bottom() const
    {
        return y() + height();
    }

    int right() const
    {
        return x() + width();
    }

    bool isNull() const
    {
        return m_pos.isNull() and m_size.isNull();
    }

    bool isValid() const
    {
        return !isEmpty();
    }

    bool isEmpty() const
    {
        return m_size.width() > 0 && m_size.height() > 0;
    }

    void moveTop(int y)
    {
        m_pos.setY(y);
    }

    void moveLeft(int x)
    {
        m_pos.setX(x);
    }

    void moveTopLeft(Point pt)
    {
        m_pos = pt;
    }

    void moveTo(Point)
    {
    }

    void moveTo(int, int)
    {
    }

    void setLeft(int x)
    {
        const int delta = m_pos.x() - x;
        const int width = m_size.width();
        m_pos.setX(x);
        m_size.setWidth(width + delta);
    }

    void setRight(int r)
    {
        const int delta = r - m_pos.x();
        const int width = m_size.width();
        m_size.setWidth(width + delta);
    }

    void setTop(int)
    {
    }

    void setTopLeft(Point)
    {
    }

    void setBottom(int)
    {
    }

    void setX(int)
    {
    }

    void setY(int)
    {
    }

    Rect marginsAdded(QMargins) const
    {
        return {};
    }

    Rect intersected(Rect) const
    {
        return Rect();
    }

    int left() const
    {
        return m_pos.x();
    }

    Point bottomLeft() const
    {
        return {};
    }

    Point bottomRight() const
    {
        return {};
    }

    Point topRight() const
    {
        return {};
    }

    bool contains(Point pt) const
    {
        return pt.x() >= x() && pt.y() >= y() && pt.x() < width() && pt.y() < height();
    }

    bool contains(Rect) const
    {
        return false;
    }

    Rect adjusted(int, int, int, int) const
    {
        return Rect();
    }

    void adjust(int, int, int, int) const
    {
    }

    Point center() const
    {
        return {};
    }

    void moveCenter(Point)
    {
    }

    void moveRight(int)
    {
    }

    void moveBottom(int)
    {
    }

    bool intersects(Rect) const
    {
        return false;
    }

    void translate(Point)
    {
    }

    bool operator==(Rect other) const
    {
        return m_pos == other.m_pos && m_size == other.m_size;
    }

private:
    Point m_pos;
    Size m_size;
};

inline const Point operator-(Point pt1, Point pt2)
{
    return { pt1.x() - pt2.x(), pt1.y() - pt2.y() };
}

inline const Point operator+(Point pt1, Point pt2)
{
    return { pt1.x() + pt2.x(), pt1.y() + pt2.y() };
}

inline const Size operator+(Size sz1, Size sz2)
{
    return { sz1.width() + sz2.width(), sz1.height() + sz2.height() };
}

inline const Size operator-(Size sz1, Size sz2)
{
    return { sz1.width() - sz2.width(), sz1.height() - sz2.height() };
}

}
