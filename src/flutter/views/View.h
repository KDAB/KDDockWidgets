/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/core/Controller.h"
#include "kddockwidgets/core/View.h"

#include <QDebug>

#include <memory>
#include <optional>

namespace KDDockWidgets::flutter {

class DOCKS_EXPORT View : public Core::View
{
public:
    using Core::View::close;
    using Core::View::height;
    using Core::View::minimumHeight;
    using Core::View::minimumWidth;
    using Core::View::rect;
    using Core::View::resize;
    using Core::View::width;

    explicit View(Core::Controller *controller, Core::ViewType type, Core::View *,
                  Qt::WindowFlags windowFlags = {});

    ~View() override;

    QSize sizeHint() const override;
    QSize minSize() const override;
    QSize maxSizeHint() const override;
    QRect geometry() const override;
    QRect normalGeometry() const override;
    void setNormalGeometry(QRect geo);
    void setGeometry(QRect geometry) override;
    void setMaximumSize(QSize sz) override;

    bool isVisible() const override;
    void setVisible(bool visible) override;
    bool isExplicitlyHidden() const override;

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
    void setParent(Core::View *parent) override;
    void raiseAndActivate() override;
    void activateWindow() override;
    void raise() override;
    QVariant property(const char *name) const override;
    bool isRootView() const override;
    QPoint mapToGlobal(QPoint localPt) const override;
    QPoint mapFromGlobal(QPoint globalPt) const override;
    QPoint mapTo(Core::View *parent, QPoint pos) const override;
    void setWindowOpacity(double v) override;
    void setSizePolicy(SizePolicy hPolicy, SizePolicy vPolicy) override;
    SizePolicy verticalSizePolicy() const override;
    SizePolicy horizontalSizePolicy() const override;

    /// Called when the flutter widget was resized by its own initiative (and not kddw)
    /// Usually it's kddw driving geometry, but there's 2 cases where flutter might trigger it
    ///     - Window is resized by user with mouse
    ///     - Widget has m_fillsParent=true and its parent was resized
    bool onFlutterWidgetResized(int w, int h);

    bool close() override;
    void setFlag(Qt::WindowType f, bool on = true) override;
    void setAttribute(Qt::WidgetAttribute attr, bool enable = true) override;
    bool testAttribute(Qt::WidgetAttribute attr) const override;
    Qt::WindowFlags flags() const override;

    void setWindowTitle(const QString &title) override;
    void setWindowIcon(const Icon &icon) override;
    bool isActiveWindow() const override;

    void showNormal() override;
    void showMinimized() override;
    void showMaximized() override;

    bool isMinimized() const override;
    bool isMaximized() const override;

    std::shared_ptr<Core::Window> window() const override;
    std::shared_ptr<Core::View> childViewAt(QPoint p) const override;
    std::shared_ptr<Core::View> rootView() const override;
    std::shared_ptr<Core::View> parentView() const override;
    std::shared_ptr<Core::View> asWrapper() override;

    void setObjectName(const QString &name) override;
    void grabMouse() override;
    void releaseMouse() override;
    void releaseKeyboard() override;
    void setFocus(Qt::FocusReason reason) override;
    Qt::FocusPolicy focusPolicy() const override;
    bool hasFocus() const override;
    void setFocusPolicy(Qt::FocusPolicy policy) override;
    QString objectName() const override;
    void setMinimumSize(QSize sz) override;
    void render(QPainter *) override;
    void setCursor(Qt::CursorShape shape) override;
    void setMouseTracking(bool enable) override;
    QVector<std::shared_ptr<Core::View>> childViews() const override;
    void setZOrder(int z) override;
    HANDLE handle() const override;

    virtual void onChildAdded(Core::View *childView);
    virtual void onChildRemoved(Core::View *childView);
    virtual void onChildVisibilityChanged(Core::View *childView);

    /// Called by flutter when a mouse event is received
    void onMouseEvent(Event::Type eventType, QPoint localPos, QPoint globalPos, bool leftIsPressed);

    void setSizeHint(QSize);

private:
    View *m_parentView = nullptr;
    QString m_name;
    QSize m_sizeHint;
    QSize m_minSize;
    QSize m_maxSize;
    std::optional<bool> m_visible;
    bool m_inCtor = true;
    Q_DISABLE_COPY(View)
};

inline View *asView_flutter(Core::View *view)
{
    if (!view)
        return nullptr;
    return static_cast<View *>(view);
}

inline View *asView_flutter(Core::Controller *controller)
{
    if (!controller)
        return nullptr;

    return static_cast<View *>(controller->view());
}

} // namespace KDDockWidgets::flutter
