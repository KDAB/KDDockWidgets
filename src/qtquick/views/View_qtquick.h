/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "Controller.h"
#include "View.h"
#include "ViewWrapper_qtquick.h"

#include <QDebug>
#include <QEvent>
#include <QResizeEvent>
#include <QSizePolicy>
#include <QQuickItem>
#include <QQuickWindow>
#include <QScopedValueRollback>

#include <memory>

namespace KDDockWidgets::Views {

inline QQuickItem *asQQuickItem(View *view)
{
    if (!view)
        return nullptr;

    return qobject_cast<QQuickItem *>(view->asQObject());
}

inline std::shared_ptr<ViewWrapper> asQQuickWrapper(QQuickItem *item)
{
    auto wrapper = new ViewWrapper_qtquick(item);
    return std::shared_ptr<ViewWrapper>(wrapper);
}

class DOCKS_EXPORT View_qtquick : public QQuickItem, public View
{
public:
    using View::close;
    using View::height;
    using View::minimumHeight;

    using View::minimumWidth;
    using View::rect;
    using View::resize;
    using View::width;

    explicit View_qtquick(KDDockWidgets::Controller *controller, Type type,
                          QQuickItem *parent = nullptr,
                          Qt::WindowFlags windowFlags = {});

    ~View_qtquick() override = default;

    void free_impl() override
    {
        // QObject::deleteLater();
        delete this;
    }

    QSize sizeHint() const override
    {
        return {};
    }

    QSize minSize() const override
    {
        return {};
    }

    QSize maxSizeHint() const override
    {
        return {};
    }

    QSize maximumSize() const override
    {
        return {};
    }

    QRect geometry() const override
    {
        return {};
    }

    QRect normalGeometry() const override
    {
        return {};
    }

    void setGeometry(QRect) override
    {
    }

    void setMaximumSize(QSize) override
    {
    }

    bool isVisible() const override
    {
        return {};
    }

    void setVisible(bool) override
    {
    }

    void move(int x, int y) override
    {
        Q_UNUSED(x)
        Q_UNUSED(y)
    }

    void move(QPoint) override
    {
    }

    void setSize(int, int) override
    {
    }

    void setWidth(int) override
    {
    }

    void setHeight(int) override
    {
    }

    void setFixedWidth(int) override
    {
    }

    void setFixedHeight(int) override
    {
    }

    void show() override
    {
    }

    void hide() override
    {
    }

    void update() override
    {
    }

    void setParent(View *parent) override
    {
        auto parentItem = Views::asQQuickItem(parent);

        {
            QScopedValueRollback<bool> guard(m_inSetParent, true);
            QQuickItem::setParent(parentItem);
            QQuickItem::setParentItem(parentItem);
        }

        // Mimic QWidget::setParent(), hide widget when setting parent
        if (!parentItem)
            setVisible(false);
    }

    void raiseAndActivate() override
    {
    }

    void activateWindow() override
    {
    }

    void raise() override
    {
    }

    QVariant property(const char *) const override
    {
        return {};
    }

    bool isRootView() const override
    {
        return {};
    }

    QPoint mapToGlobal(QPoint /*localPt*/) const override
    {
        return {};
    }

    QPoint mapFromGlobal(QPoint /*globalPt*/) const override
    {
        return {};
    }

    QPoint mapTo(View *, QPoint) const override
    {
        return {};
    }

    void setWindowOpacity(double v) override
    {
        if (QWindow *w = QQuickItem::window())
            w->setOpacity(v);
    }

    void setSizePolicy(QSizePolicy) override
    {
    }

    QSizePolicy sizePolicy() const override
    {
        return {};
    }

    void closeWindow() override
    {
    }

    QRect windowGeometry() const override
    {
        return {};
    }

    virtual QSize parentSize() const override
    {
        return {};
    }

    bool close() override
    {
        return {};
    }

    void setFlag(Qt::WindowType, bool = true) override
    {
    }

    void setAttribute(Qt::WidgetAttribute, bool = true) override
    {
    }

    bool testAttribute(Qt::WidgetAttribute) const override
    {
        return {};
    }

    Qt::WindowFlags flags() const override
    {
        return {};
    }

    void setWindowTitle(const QString &) override
    {
    }

    void setWindowIcon(const QIcon &) override
    {
    }

    bool isActiveWindow() const override
    {
        return {};
    }

    void showNormal() override
    {
    }

    void showMinimized() override
    {
    }

    void showMaximized() override
    {
    }

    bool isMinimized() const override
    {
        return {};
    }

    bool isMaximized() const override
    {
        return {};
    }

    std::shared_ptr<Window> windowHandle() const override
    {
        return {};
    }

    HANDLE handle() const override
    {
        return reinterpret_cast<HANDLE>(this);
    }

    std::shared_ptr<ViewWrapper> childViewAt(QPoint) const override
    {
        return {};
    }

    std::shared_ptr<ViewWrapper> window() const override
    {
        return {};
    }

    std::shared_ptr<ViewWrapper> parentView() const override
    {
        auto p = QQuickItem::parentItem();
        return p ? asQQuickWrapper(p) : nullptr;
    }

    std::shared_ptr<ViewWrapper> asWrapper() override
    {
        ViewWrapper *wrapper = new ViewWrapper_qtquick(this);
        return std::shared_ptr<ViewWrapper>(wrapper);
    }

    void setObjectName(const QString &name) override
    {
        QQuickItem::setObjectName(name);
    }

    void grabMouse() override
    {
    }

    void releaseMouse() override
    {
    }

    void releaseKeyboard() override
    {
    }

    QScreen *screen() const override
    {
        return {};
    }

    void setFocus(Qt::FocusReason) override
    {
    }

    QString objectName() const override
    {
        return QQuickItem::objectName();
    }

    void setMinimumSize(QSize) override
    {
    }

    void render(QPainter *) override
    {
        qWarning() << Q_FUNC_INFO << "Implement me";
    }

    void setCursor(Qt::CursorShape shape) override
    {
        QQuickItem::setCursor(shape);
    }

    void setMouseTracking(bool enable) override
    {
        qWarning() << Q_FUNC_INFO << "Implement me" << enable;
    }

    QVector<std::shared_ptr<View>> childViews() const override
    {
        QVector<std::shared_ptr<View>> result;
        const auto childItems = QQuickItem::childItems();
        for (QQuickItem *child : childItems) {
            result << asQQuickWrapper(child);
        }

        return result;
    }

protected:
    bool event(QEvent *e) override
    {
        return QQuickItem::event(e);
    }

private:
    Q_DISABLE_COPY(View_qtquick)
    bool m_inSetParent = false;
};

} // namespace KDDockWidgets::Views
