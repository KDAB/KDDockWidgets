/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "Widget.h"

#include <QWidget>

///@file
///@brief A Layouting::Widget that's deals in QWidget

namespace Layouting {

///@brief A Layouting::Widget that's deals in QWidget
/// Allows to host a QWidget in the layout
class MULTISPLITTER_EXPORT Widget_qwidget : public Widget
{
public:
    explicit Widget_qwidget(QWidget *thisWidget)
        : Widget(thisWidget)
        , m_thisWidget(thisWidget)
    {
    }

    ~Widget_qwidget() override;

    QWidget* asQWidget() const override {
        return m_thisWidget;
    }

    QSize sizeHint() const override;
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
    void update() override;
    QPoint mapFromGlobal(QPoint p) const override;
    QPoint mapToGlobal(QPoint p) const override;

    static QSize widgetMinSize(const QWidget *w);
    static QSize widgetMaxSize(const QWidget *w);
private:
    QWidget *const m_thisWidget;
    Q_DISABLE_COPY(Widget_qwidget)
};

inline int widgetMinLength(const QWidget *w, Qt::Orientation o)
{
    const QSize sz = Widget_qwidget::widgetMinSize(w);
    return o == Qt::Vertical ? sz.height() : sz.width();
}

}
