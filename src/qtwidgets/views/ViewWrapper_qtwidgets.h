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
#include <QPointer>

namespace KDDockWidgets::Views {

/// @brief A View that doesn't own its QWidget
/// Implements a View API around an existing QWidget
/// Useful for widgets that are not created by KDDW.
class DOCKS_EXPORT ViewWrapper_qtwidgets : public ViewWrapper
{
public:
    explicit ViewWrapper_qtwidgets(QObject *widget);
    explicit ViewWrapper_qtwidgets(QWidget *widget);

    void setObjectName(const QString &name) override;
    QRect geometry() const override;
    void setGeometry(QRect) override;
    void move(int x, int y) override;
    void move(QPoint) override;
    QPoint mapToGlobal(QPoint) const override;
    QPoint mapFromGlobal(QPoint) const override;
    bool isTopLevel() const override;
    bool isVisible() const override;
    void setVisible(bool) override;
    void activateWindow() override;
    bool isMaximized() const override;
    bool isMinimized() const override;
    QSize maximumSize() const override;
    void setSize(int width, int height) override;
    bool is(Type) const override;
    std::shared_ptr<Window> windowHandle() const override;
    std::shared_ptr<ViewWrapper> window() const override;
    std::shared_ptr<ViewWrapper> parentView() const override;
    void setParent(View *) override;

    std::shared_ptr<ViewWrapper> childViewAt(QPoint localPos) const override;
    QVector<std::shared_ptr<View>> childViews() const override;
    HANDLE handle() const override;
    void grabMouse() override;
    void releaseMouse() override;
    QScreen *screen() const override;
    void setFocus(Qt::FocusReason) override;
    QString objectName() const override;
    QVariant property(const char *) const override;
    bool isNull() const override;
    void setWindowTitle(const QString &title) override;
    QPoint mapTo(View *, QPoint) const override;
    Controllers::DropArea *asDropArea() const override;
    bool testAttribute(Qt::WidgetAttribute) const override;
    void setCursor(Qt::CursorShape) override;
    QSize minSize() const override;

    QWidget *widget() const;

private:
    QPointer<QWidget> m_widget;
};

}
