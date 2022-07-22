/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/Controller.h"
#include "kddockwidgets/View.h"

#include <QDebug>
#include <QEvent>
#include <QResizeEvent>

#include <memory>

namespace KDDockWidgets::Views {


class DOCKS_EXPORT View_flutter : public View
{
public:
    using View::close;
    using View::height;
    using View::minimumHeight;

    using View::minimumWidth;
    using View::rect;
    using View::resize;
    using View::width;

    explicit View_flutter(KDDockWidgets::Controller *controller, Type type,
                          void *, Qt::WindowFlags windowFlags = {});

    ~View_flutter() override = default;

    void free_impl() override;
    QSize sizeHint() const override;
    QSize minSize() const override;
    QSize maxSizeHint() const override;
    QSize maximumSize() const override;
    QRect geometry() const override;
    QRect normalGeometry() const override;
    void setNormalGeometry(QRect geo);
    void setGeometry(QRect) override;
    void setMaximumSize(QSize sz) override;

    bool isVisible() const override;
    void setVisible(bool is) override;

    void move(int x, int y) override;
    void setSize(int w, int h) override;

    void setWidth(int w) override;
    void setHeight(int h) override;
    void setFixedWidth(int w) override;
    void setFixedHeight(int h) override;
    void show() override;
    void hide() override;
    void updateGeometry();
    void update() override;
    void setParent(View *parent) override;
    void raiseAndActivate() override;
    void activateWindow() override;
    void raise() override;
    QVariant property(const char *name) const override;
    bool isRootView() const override;
    QPoint mapToGlobal(QPoint localPt) const override;
    QPoint mapFromGlobal(QPoint globalPt) const override;
    QPoint mapTo(View *parent, QPoint pos) const override;
    void setWindowOpacity(double v) override;
    void setSizePolicy(SizePolicy, SizePolicy) override;
    SizePolicy verticalSizePolicy() const override;
    SizePolicy horizontalSizePolicy() const override;

    bool close() override;
    void setFlag(Qt::WindowType f, bool on = true) override;
    void setAttribute(Qt::WidgetAttribute attr, bool enable = true) override;
    bool testAttribute(Qt::WidgetAttribute attr) const override;
    Qt::WindowFlags flags() const override;

    void setWindowTitle(const QString &title) override;
    void setWindowIcon(const QIcon &icon) override;
    bool isActiveWindow() const override;

    void showNormal() override;
    void showMinimized() override;
    void showMaximized() override;

    bool isMinimized() const override;
    bool isMaximized() const override;

    std::shared_ptr<Window> window() const override;
    std::shared_ptr<View> childViewAt(QPoint p) const override;
    std::shared_ptr<View> rootView() const override;
    std::shared_ptr<View> parentView() const override;
    std::shared_ptr<View> asWrapper() override;

    void setObjectName(const QString &name) override;
    void grabMouse() override;
    void releaseMouse() override;
    void releaseKeyboard() override;
    void setFocus(Qt::FocusReason reason) override;
    Qt::FocusPolicy focusPolicy() const override;
    bool hasFocus() const override;
    void setFocusPolicy(Qt::FocusPolicy) override;
    QString objectName() const override;
    void setMinimumSize(QSize sz) override;
    void render(QPainter *) override;
    void setCursor(Qt::CursorShape shape) override;
    void setMouseTracking(bool enable) override;
    QVector<std::shared_ptr<View>> childViews() const override;
    void setZOrder(int) override;

private:
    Q_DISABLE_COPY(View_flutter)
};

inline View_flutter *asView_flutter(View *view)
{
    if (!view)
        return nullptr;
    return static_cast<View_flutter *>(view);
}

inline View_flutter *asView_flutter(Controller *controller)
{
    if (!controller)
        return nullptr;

    return static_cast<View_flutter *>(controller->view());
}

} // namespace KDDockWidgets::Views
