/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "ViewWrapper.h"

#include <QWidget>

namespace KDDockWidgets::Views {

/// @brief A View that doesn't own its QWidget
/// Implements a View API around an existing QWidget
/// Useful for widgets that are not created by KDDW.
class DOCKS_EXPORT ViewWrapper_qtwidgets : public ViewWrapper
{
public:
    explicit ViewWrapper_qtwidgets(QWidget *widget);

    void setObjectName(const QString &name) override;
    QRect geometry() const override;
    void setGeometry(QRect) override;
    void move(int x, int y) override;
    void move(QPoint) override;
    QPoint mapToGlobal(QPoint) const override;
    QPoint mapFromGlobal(QPoint) const override;
    QWindow *windowHandle() const override;
    bool isTopLevel() const override;
    bool isVisible() const override;
    void setVisible(bool) override;
    void activateWindow() override;
    bool isMaximized() const override;
    QSize maximumSize() const override;
    void setSize(int width, int height) override;
    bool is(Type) const override;
    std::unique_ptr<ViewWrapper> window() const override;
    std::unique_ptr<ViewWrapper> parentView() const override;

private:
    QWidget *const m_widget;
};

}
