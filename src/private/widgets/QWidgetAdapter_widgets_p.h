/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief A class that is QWidget when building for QtWidgets, and QObject when building for QtQuick.
 *
 * Allows to have the same code base supporting both stacks.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDDOCKWIDGETS_QWIDGETADAPTERWIDGETS_P_H
#define KDDOCKWIDGETS_QWIDGETADAPTERWIDGETS_P_H

#include "../../docks_export.h"

#include <QWidget>

namespace KDDockWidgets {

/// @brief Helper since QQuickItem::parentItem() has a different name than QWidget::parentWidget()
inline QWidget *parentWidget(QWidget *widget)
{
    return widget ? widget->parentWidget() : nullptr;
}

class FloatingWindow;

class DOCKS_EXPORT QWidgetAdapter : public QWidget
{
    Q_OBJECT
public:
    explicit QWidgetAdapter(QWidget *parent = nullptr, Qt::WindowFlags f = {});
    ~QWidgetAdapter() override;

    ///@brief returns the FloatingWindow this widget is in, otherwise nullptr
    FloatingWindow *floatingWindow() const;

    void setFlag(Qt::WindowType, bool on = true);

protected:
    void raiseAndActivate();
    bool event(QEvent *e) override;
    void resizeEvent(QResizeEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void closeEvent(QCloseEvent *) override;

    virtual bool onResize(QSize newSize);
    virtual void onLayoutRequest();
    virtual void onMousePress();
    virtual void onMouseMove(QPoint globalPos);
    virtual void onMouseRelease();
    virtual void onCloseEvent(QCloseEvent *);
};

}

#endif
