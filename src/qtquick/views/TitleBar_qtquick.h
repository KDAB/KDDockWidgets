/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_TITLEBARQUICK_P_H
#define KD_TITLEBARQUICK_P_H
#pragma once

#include "kddockwidgets/docks_export.h"
#include "views/TitleBar.h"
#include "View_qtquick.h"

namespace KDDockWidgets::Views {

class DOCKS_EXPORT TitleBar_qtquick : public View_qtquick, public Views::TitleBar
{
    Q_OBJECT
    // These properties is just for the unit-tests
    Q_PROPERTY(QQuickItem *titleBarQmlItem READ titleBarQmlItem WRITE setTitleBarQmlItem NOTIFY titleBarQmlItemChanged)
    Q_PROPERTY(QQuickItem *titleBarMouseArea READ titleBarMouseArea CONSTANT)
public:
    explicit TitleBar_qtquick(Controllers::TitleBar *controller, QQuickItem *parent = nullptr);
    ~TitleBar_qtquick() override;

protected:
#ifdef DOCKS_DEVELOPER_MODE
    // These 4 just for unit-tests
    bool isCloseButtonEnabled() const override;
    bool isCloseButtonVisible() const override;
    bool isFloatButtonVisible() const override;
#endif

    /*void paintEvent(QPaintEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override; */

    QQuickItem *titleBarQmlItem() const;
    QQuickItem *titleBarMouseArea() const;
    void setTitleBarQmlItem(QQuickItem *);
    void updateMaximizeButton() override;

Q_SIGNALS:
    void titleBarQmlItemChanged();

private:
    QQuickItem *floatButton() const;
    QQuickItem *closeButton() const;

    QPointer<QQuickItem> m_titleBarQmlItem;
};

}

#endif
