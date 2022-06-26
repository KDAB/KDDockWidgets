/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/Window.h"

#include <QPointer>

QT_BEGIN_NAMESPACE
class QWindow;
QT_END_NAMESPACE

namespace KDDockWidgets {

class DOCKS_EXPORT Window_qt : public Window
{
public:
    explicit Window_qt(QWindow *);
    ~Window_qt() override;
    void setWindowState(WindowState) override;
    QRect geometry() const override;
    void setGeometry(QRect) const override;
    bool isVisible() const override;
    void setVisible(bool) override;
    WId handle() const override;

    bool equals(std::shared_ptr<Window> other) const override;
    void setFramePosition(QPoint targetPos) override;
    void resize(int width, int height) override;
    bool isActive() const override;
    WindowState windowState() const override;

    QRect frameGeometry() const override;
    QWindow *qtWindow() const;

    QPoint mapFromGlobal(QPoint globalPos) const override;
    QPoint mapToGlobal(QPoint localPos) const override;
    QScreen *screen() const override;
    void destroy() override;
    QSize minSize() const override;
    QSize maxSize() const override;
    QPoint fromNativePixels(QPoint) const override;
    void startSystemMove() override;

    bool isFullScreen() const override;

protected:
    QPointer<QWindow> m_window;

private:
    QMetaObject::Connection m_connection;
};

}
