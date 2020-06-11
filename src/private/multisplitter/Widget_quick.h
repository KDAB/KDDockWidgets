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

#pragma once

#include "Widget.h"

#include <QQuickItem>

class QQuickItem;

///@file
///@brief A Layouting::Widget that's deals in QQuickItem

namespace Layouting {

///@brief A Layouting::Widget that's deals in QQuickItem
/// Allows to host a QQuickItem in the layout
class Widget_quick : public Widget
{
public:
    explicit Widget_quick(QQuickItem *thisWidget)
        : Widget(thisWidget)
        , m_thisWidget(thisWidget)
    {
    }

    ~Widget_quick() override;

    QSize minSize() const override;
    QSize maxSizeHint() const override;
    QRect geometry() const override;
    void setGeometry(QRect) override;
    void setParent(Widget *) override;
    QDebug& dumpDebug(QDebug&) const override;
    bool isVisible() const override;
    void setVisible(bool) const override;
    std::unique_ptr<Widget> parentWidget() const override;
    std::unique_ptr<Widget> topLevel() const override;
    void setLayoutItem(Item *) override {}
    void show() override;
    void hide() override;
    void move(int x, int y) override;
    void setSize(int width, int height) override;
    void setWidth(int width) override;
    void setHeight(int height) override;

    static QSize widgetMinSize(const QWidget *w);

protected:
    QQuickItem *createQQuickItem(const QString &filename, QQuickItem *parent) const;

private:
    QQuickItem *const m_thisWidget;
    Q_DISABLE_COPY(Widget_quick)
};

}
