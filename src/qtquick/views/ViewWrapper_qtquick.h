/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "ViewWrapper.h"

#include <QQuickItem>
#include <QPointer>

namespace KDDockWidgets::Views {

/// @brief A View that doesn't own its QQuickItem
/// Implements a View API around an existing QQuickItem
/// Useful for items that are not created by KDDW.
class DOCKS_EXPORT ViewWrapper_qtquick : public ViewWrapper
{
public:
    explicit ViewWrapper_qtquick(QObject *widget);
    explicit ViewWrapper_qtquick(QQuickItem *widget);

    void setObjectName(const QString &name) override;
    QRect geometry() const override;
    void setGeometry(QRect) override;
    void move(int x, int y) override;
    QPoint mapToGlobal(QPoint) const override;
    QPoint mapFromGlobal(QPoint) const override;
    bool isRootView() const override;
    bool isVisible() const override;
    void setVisible(bool) override;
    void activateWindow() override;
    bool isMaximized() const override;
    bool isMinimized() const override;
    QSize maximumSize() const override;
    void setSize(int width, int height) override;
    bool is(Type) const override;
    std::shared_ptr<ViewWrapper> childViewAt(QPoint) const override;
    QVector<std::shared_ptr<View>> childViews() const override;
    std::shared_ptr<Window> window() const override;
    std::shared_ptr<ViewWrapper> rootView() const override;
    std::shared_ptr<ViewWrapper> parentView() const override;
    void setParent(View *) override; // TODOv2: Rename to setParentView
    HANDLE handle() const override;
    void grabMouse() override;
    void releaseMouse() override;
    void setFocus(Qt::FocusReason) override;
    QString objectName() const override;
    QVariant property(const char *) const override;
    bool isNull() const override;
    void setWindowTitle(const QString &title) override;
    QPoint mapTo(View *someAncestor, QPoint pos) const override;
    bool testAttribute(Qt::WidgetAttribute) const override;
    void setCursor(Qt::CursorShape) override;
    QSize minSize() const override;
    bool close() override;

    const View *unwrap() const;
    View *unwrap();

private:
    QPointer<QQuickItem> m_item;
};

}
