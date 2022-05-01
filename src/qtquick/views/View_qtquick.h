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
#include "private/multisplitter/Item_p.h"
#include "qtquick/Window_qtquick.h"

#include <QDebug>
#include <QEvent>
#include <QResizeEvent>
#include <QSizePolicy>
#include <QQuickItem>
#include <QQuickWindow>
#include <QScopedValueRollback>
#include <QQuickView>
#include <QScreen>

#include <memory>

namespace KDDockWidgets::Views {

class MouseEventRedirector;

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
    Q_OBJECT
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
        return m_sizeHint;
    }

    QSize minSize() const override
    {
        if (m_isWrapper) {
            const auto children = childItems();
            if (!children.isEmpty()) {
                const QSize min = children.constFirst()->property("kddockwidgets_min_size").toSize();
                return min.expandedTo(Layouting::Item::hardcodedMinimumSize);
            }
        }

        const QSize min = property("kddockwidgets_min_size").toSize();
        return min.expandedTo(Layouting::Item::hardcodedMinimumSize);
    }

    QSize maxSizeHint() const override
    {
        if (m_isWrapper) {
            const auto children = childItems();
            if (!children.isEmpty()) {
                const QSize max = children.constFirst()->property("kddockwidgets_max_size").toSize();
                return max.isEmpty() ? Layouting::Item::hardcodedMaximumSize
                                     : max.boundedTo(Layouting::Item::hardcodedMaximumSize);
            }
        }

        const QSize max = property("kddockwidgets_max_size").toSize();
        return max.isEmpty() ? Layouting::Item::hardcodedMaximumSize
                             : max.boundedTo(Layouting::Item::hardcodedMaximumSize);
    }

    QSize maximumSize() const override
    {
        return {};
    }

    QRect geometry() const override
    {
        if (isRootView()) {
            if (QWindow *w = QQuickItem::window()) {
                return w->geometry();
            }
        }

        QRect r(QPointF(QQuickItem::x(), QQuickItem::y()).toPoint(), QQuickItem::size().toSize());
        return r;
    }

    QRect normalGeometry() const override
    {
        return m_normalGeometry;
    }

    void setNormalGeometry(QRect geo)
    {
        m_normalGeometry = geo;
    }

    void setGeometry(QRect) override;

    void setMaximumSize(QSize sz) override
    {
        if (maximumSize() != sz) {
            setProperty("kddockwidgets_max_size", sz);
            updateGeometry();
        }
    }

    bool isVisible() const override;
    void setVisible(bool is) override;

    void move(int x, int y) override;
    void setSize(int w, int h) override;

    void setWidth(int w) override
    {
        QQuickItem::setWidth(w);
    }

    void setHeight(int h) override
    {
        QQuickItem::setHeight(h);
    }

    void setFixedWidth(int w) override
    {
        setWidth(w);
    }

    void setFixedHeight(int h) override
    {
        setHeight(h);
    }

    void show() override
    {
        setVisible(true);
    }

    void hide() override
    {
        setVisible(false);
    }

    void updateGeometry()
    {
        Q_EMIT geometryUpdated();
    }

    // TODOv2: Check if this is even called from controllers
    void update() override
    {
        // Nothing to do for QtQuick
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
        // if (!parentItem) // TODOv2: Why was this if needed, QWidget hides unconditionally
        setVisible(false);
    }

    void raiseAndActivate() override
    {
        if (QWindow *w = QQuickItem::window()) {
            w->raise();
            w->requestActivate();
        }
    }

    void activateWindow() override
    {
        if (QWindow *w = QQuickItem::window())
            w->requestActivate();
    }

    void raise() override
    {
        if (isRootView()) {
            if (QWindow *w = QQuickItem::window())
                w->raise();
        } else if (auto p = QQuickItem::parentItem()) {
            // It's not a top-level, so just increase its Z-order
            const auto siblings = p->childItems();
            QQuickItem *last = siblings.last();
            if (last != this)
                stackAfter(last);
        }
    }

    QVariant property(const char *name) const override
    {
        return QObject::property(name);
    }

    bool isRootView() const override
    {
        QQuickItem *parent = parentItem();
        if (!parent)
            return true;

        if (QQuickView *w = quickView()) {
            if (parent == w->contentItem() || parent == w->rootObject())
                return true;
        }

        return false;
    }

    QQuickView *quickView() const
    {
        return qobject_cast<QQuickView *>(QQuickItem::window());
    }

    QPoint mapToGlobal(QPoint localPt) const override
    {
        return QQuickItem::mapToGlobal(localPt).toPoint();
    }

    QPoint mapFromGlobal(QPoint globalPt) const override
    {
        return QQuickItem::mapFromGlobal(globalPt).toPoint();
    }

    QPoint mapTo(View *parent, QPoint pos) const override
    {
        if (!parent)
            return {};

        auto parentItem = asQQuickItem(parent);
        return parentItem->mapFromGlobal(QQuickItem::mapToGlobal(pos)).toPoint();
    }

    void setWindowOpacity(double v) override
    {
        if (QWindow *w = QQuickItem::window())
            w->setOpacity(v);
    }

    void setSizePolicy(QSizePolicy sp) override
    {
        m_sizePolicy = sp;
    }

    QSizePolicy sizePolicy() const override
    {
        return m_sizePolicy;
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

    bool close() override;

    void setFlag(Qt::WindowType f, bool on = true) override
    {
        if (on) {
            m_windowFlags |= f;
        } else {
            m_windowFlags &= ~f;
        }
    }

    void setAttribute(Qt::WidgetAttribute attr, bool enable = true) override
    {
        if (enable)
            m_widgetAttributes |= attr;
        else
            m_widgetAttributes &= ~attr;
    }

    bool testAttribute(Qt::WidgetAttribute attr) const override
    {
        return m_widgetAttributes & attr;
    }

    Qt::WindowFlags flags() const override
    {
        return m_windowFlags;
    }

    void setWindowTitle(const QString &title) override
    {
        if (QWindow *w = QQuickItem::window())
            w->setTitle(title);
    }

    void setWindowIcon(const QIcon &icon) override
    {
        if (QWindow *w = QQuickItem::window())
            w->setIcon(icon);
    }

    bool isActiveWindow() const override
    {
        if (QWindow *w = QQuickItem::window())
            return w->isActive();

        return false;
    }

    Q_INVOKABLE void redirectMouseEvents(QObject *from);

    Q_INVOKABLE void showNormal() override
    {
        if (QWindow *w = QQuickItem::window())
            w->showNormal();
    }

    Q_INVOKABLE void showMinimized() override
    {
        if (QWindow *w = QQuickItem::window())
            w->showMinimized();
    }

    Q_INVOKABLE void showMaximized() override
    {
        if (QWindow *w = QQuickItem::window())
            w->showMaximized();
    }

    bool isMinimized() const override
    {
        if (QWindow *w = QQuickItem::window())
            return w->windowStates() & Qt::WindowMinimized;

        return false;
    }

    bool isMaximized() const override
    {
        if (QWindow *w = QQuickItem::window())
            return w->windowStates() & Qt::WindowMaximized;

        return false;
    }

    std::shared_ptr<Window> windowHandle() const override
    {
        if (QWindow *w = QQuickItem::window()) {
            auto windowqtquick = new Window_qtquick(w);
            return std::shared_ptr<Window>(windowqtquick);
        }

        return {};
    }

    HANDLE handle() const override
    {
        return reinterpret_cast<HANDLE>(this);
    }

    std::shared_ptr<ViewWrapper> childViewAt(QPoint p) const override
    {
        auto child = QQuickItem::childAt(p.x(), p.y());
        return child ? asQQuickWrapper(child) : nullptr;
    }

    std::shared_ptr<ViewWrapper> window() const override
    {
        return {};
    }

    std::shared_ptr<ViewWrapper> parentView() const override
    {
        auto p = QQuickItem::parentItem();
        if (QQuickWindow *window = QQuickItem::window()) {
            if (p == window->contentItem()) {
                // For our purposes, the root view is the one directly bellow QQuickWindow::contentItem
                return nullptr;
            }
        }

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
        QQuickItem::grabMouse();
    }

    void releaseMouse() override
    {
        QQuickItem::ungrabMouse();
    }

    void releaseKeyboard() override
    {
        // Not needed for QtQuick
    }

    QScreen *screen() const override
    {
        if (QWindow *w = QQuickItem::window())
            return w->screen();

        return nullptr;
    }

    void setFocus(Qt::FocusReason reason) override
    {
        QQuickItem::setFocus(true, reason);
        forceActiveFocus(reason);
    }

    Qt::FocusPolicy focusPolicy() const
    {
        return m_focusPolicy;
    }
    /// TODOv2: Make these 2 virtual ?
    void setFocusPolicy(Qt::FocusPolicy policy)
    {
        m_focusPolicy = policy;
    }

    QString objectName() const override
    {
        return QQuickItem::objectName();
    }

    void setMinimumSize(QSize sz) override
    {
        if (minSize() != sz) {
            setProperty("kddockwidgets_min_size", sz);
            updateGeometry();
        }
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
        m_mouseTrackingEnabled = enable;
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

    // TODOv2: Check if this is still needed
    void setWindowIsBeingDestroyed(bool is)
    {
        m_windowIsBeingDestroyed = is;
    }

    // TODOv2: Check if this is still needed
    void setIsWrapper()
    {
        m_isWrapper = true;
    }

    // TODOv2: Check if this is still needed
    bool isWrapper() const
    {
        return m_isWrapper;
    }

    /// @brief This is equivalent to "anchors.fill: parent but in C++
    void makeItemFillParent(QQuickItem *item)
    {
        if (!item) {
            qWarning() << Q_FUNC_INFO << "Invalid item";
            return;
        }

        QQuickItem *parentItem = item->parentItem();
        if (!parentItem) {
            qWarning() << Q_FUNC_INFO << "Invalid parentItem for" << item;
            return;
        }

        QObject *anchors = item->property("anchors").value<QObject *>();
        if (!anchors) {
            qWarning() << Q_FUNC_INFO << "Invalid anchors for" << item;
            return;
        }

        anchors->setProperty("fill", QVariant::fromValue(parentItem));
    }

    void onWindowStateChangeEvent(QWindowStateChangeEvent *)
    {
        if (QWindow *window = QQuickItem::window()) {
            m_oldWindowState = window->windowState();
        }
    }

    /// @brief Convenience to create a QQuickItem
    static QQuickItem *createItem(QQmlEngine *engine, const QString &filename);

Q_SIGNALS:
    void geometryUpdated(); // similar to QLayout stuff, when size constraints change
    void itemGeometryChanged(); // emitted when the geometry changes. QQuickItem::geometryChanged()
                                // isn't a signal, so prefixed item

protected:
    void QQUICKITEMgeometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    void itemChange(QQuickItem::ItemChange, const QQuickItem::ItemChangeData &) override;
    bool eventFilter(QObject *watched, QEvent *ev) override;
    bool event(QEvent *) override;

    // TODOv2: Port these
    void onCloseEvent(QCloseEvent *)
    {
    }
    void onMoveEvent(QMoveEvent *);
    void onResizeEvent(QResizeEvent *);

private:
    Q_DISABLE_COPY(View_qtquick)
    bool m_inSetParent = false;
    QSize m_sizeHint;
    QSizePolicy m_sizePolicy = QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    Qt::WindowFlags m_windowFlags;
    int m_widgetAttributes = 0; // Qt::WidgetAttribute
    Qt::FocusPolicy m_focusPolicy = Qt::NoFocus;
    bool m_windowIsBeingDestroyed = false;
    bool m_mouseTrackingEnabled = false;
    bool m_isWrapper = false; // TODOv2: What's this about
    QRect m_normalGeometry;
    Qt::WindowStates m_oldWindowState = Qt::WindowState::WindowNoState;
    MouseEventRedirector *m_mouseEventRedirector = nullptr;
};

inline qreal logicalDpiFactor(const QQuickItem *item)
{
#ifndef Q_OS_MACOS
    if (QQuickWindow *window = item->window()) {
        if (QScreen *s = window->screen()) {
            return s->logicalDotsPerInch() / 96.0;
        }
    }
#endif

    // It's always 72 on mac
    Q_UNUSED(item);
    return 1;
}

} // namespace KDDockWidgets::Views
