/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View.h"
#include "docks_export.h"

namespace KDDockWidgets {

namespace Controllers {
class DropArea;
}


/// @brief The base class for view wrappers
/// A view wrapper is a view that doesn't own the native GUI element(QWidget, QQuickItem etc.)
/// It just adds View API to an existing GUI element
/// Useful for GUI elements that are not created by KDDW.
class DOCKS_EXPORT ViewWrapper : public View
{
public:
    using Ptr = std::shared_ptr<ViewWrapper>;

    explicit ViewWrapper(Controller *controller, QObject *thisObj); // TODOv2: Remove thisObj argument once all calls to asQWidget() are removed

    void setMinimumSize(QSize) override;
    QSize maxSizeHint() const override;
    QRect normalGeometry() const override;
    void setWidth(int width) override;
    void setHeight(int height) override;
    void show() override;
    void hide() override;
    void update() override;
    void raiseAndActivate() override;
    void raise() override;
    void setSizePolicy(QSizePolicy) override;
    void setFlag(Qt::WindowType, bool = true) override;
    void setAttribute(Qt::WidgetAttribute, bool enable = true) override;
    Qt::WindowFlags flags() const override;
    void setWindowIcon(const QIcon &) override;
    void showNormal() override;
    void showMinimized() override;
    void showMaximized() override;
    void setMaximumSize(QSize sz) override;
    bool isActiveWindow() const override;
    void setFixedWidth(int) override;
    void setFixedHeight(int) override;
    void setWindowOpacity(double) override;
    void releaseKeyboard() override;
    void render(QPainter *p) override;
    void setMouseTracking(bool) override;
    std::shared_ptr<ViewWrapper> asWrapper() override;

    /// TODOv2: Remove
    virtual Controllers::DropArea *asDropArea() const
    {
        return {};
    };
};

bool operator==(ViewWrapper::Ptr, ViewWrapper::Ptr) = delete;
bool operator!=(ViewWrapper::Ptr, ViewWrapper::Ptr) = delete;

}
