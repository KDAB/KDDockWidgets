/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "Screen.h"
#include "kddockwidgets/Window.h"

namespace KDDockWidgets {
class DOCKS_EXPORT Window_flutter : public Window
{
public:
    Window_flutter();
    ~Window_flutter() override;
    std::shared_ptr<View> rootView() const override;
    Window::Ptr transientParent() const override;
    void setGeometry(QRect) const override;
    void setVisible(bool) override;
    bool supportsHonouringLayoutMinSize() const override;

    void setWindowState(WindowState) override;
    QRect geometry() const override;
    void setProperty(const char *name, const QVariant &value) override;
    QVariant property(const char *name) const override;
    bool isVisible() const override;
    WId handle() const override;
    bool equals(std::shared_ptr<Window> other) const override;
    void setFramePosition(QPoint targetPos) override;
    QRect frameGeometry() const override;
    void resize(int width, int height) override;
    bool isActive() const override;
    WindowState windowState() const override;
    QPoint mapFromGlobal(QPoint globalPos) const override;
    QPoint mapToGlobal(QPoint localPos) const override;
    Screen::Ptr screen() const override;
    void destroy() override;
    QSize minSize() const override;
    QSize maxSize() const override;
    QPoint fromNativePixels(QPoint) const override;
    bool isFullScreen() const override;
};
}
