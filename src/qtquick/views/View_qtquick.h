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

inline QQuickItem *asQQuickItem(Controller *controller)
{
    if (!controller)
        return nullptr;

    return asQQuickItem(controller->view());
}

inline std::shared_ptr<ViewWrapper> asQQuickWrapper(QQuickItem *item)
{
    auto wrapper = new ViewWrapper_qtquick(item);
    return std::shared_ptr<ViewWrapper>(wrapper);
}



class DOCKS_EXPORT View_qtquick : public QQuickItem,
                                  public View
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
    void setParent(QQuickItem *parent);
    void raiseAndActivate() override;
    void activateWindow() override;
    void raise() override;
    QVariant property(const char *name) const override;
    static bool isRootView(const QQuickItem *);
    bool isRootView() const override;
    QQuickView *quickView() const;
    QPoint mapToGlobal(QPoint localPt) const override;
    QPoint mapFromGlobal(QPoint globalPt) const override;
    QPoint mapTo(View *parent, QPoint pos) const override;
    void setWindowOpacity(double v) override;
    void setSizePolicy(SizePolicy, SizePolicy) override;
    SizePolicy verticalSizePolicy() const override;
    SizePolicy horizontalSizePolicy() const override;

    static bool close(QQuickItem *);
    bool close() override;
    void setFlag(Qt::WindowType f, bool on = true) override;
    void setAttribute(Qt::WidgetAttribute attr, bool enable = true) override;
    bool testAttribute(Qt::WidgetAttribute attr) const override;
    Qt::WindowFlags flags() const override;

    void setWindowTitle(const QString &title) override;
    void setWindowIcon(const QIcon &icon) override;
    bool isActiveWindow() const override;

    Q_INVOKABLE void redirectMouseEvents(QObject *from);
    Q_INVOKABLE void showNormal() override;
    Q_INVOKABLE void showMinimized() override;
    Q_INVOKABLE void showMaximized() override;

    bool isMinimized() const override;
    bool isMaximized() const override;

    std::shared_ptr<Window> window() const override;
    std::shared_ptr<ViewWrapper> childViewAt(QPoint p) const override;
    std::shared_ptr<ViewWrapper> rootView() const override;
    std::shared_ptr<ViewWrapper> parentView() const override;

    std::shared_ptr<ViewWrapper> asWrapper() override;

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
    virtual QQuickItem *visualItem() const;

    /// @brief This is equivalent to "anchors.fill: parent but in C++
    void makeItemFillParent(QQuickItem *item);
    void onWindowStateChangeEvent(QWindowStateChangeEvent *);

    /// @brief Convenience to create a QQuickItem
    static QQuickItem *createItem(QQmlEngine *engine, const QString &filename);
    static std::shared_ptr<ViewWrapper> parentViewFor(const QQuickItem *);

Q_SIGNALS:
    void geometryUpdated(); // similar to QLayout stuff, when size constraints change
    void itemGeometryChanged(); // emitted when the geometry changes. QQuickItem::geometryChanged()
                                // isn't a signal, so prefixed item

protected:
    void QQUICKITEMgeometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    void itemChange(QQuickItem::ItemChange, const QQuickItem::ItemChangeData &) override;
    bool eventFilter(QObject *watched, QEvent *ev) override;
    bool event(QEvent *) override;
    QQuickItem *createQQuickItem(const QString &filename, QQuickItem *parent) const;

private:
    Q_DISABLE_COPY(View_qtquick)
    void updateNormalGeometry();
    bool m_inSetParent = false;
    QSize m_sizeHint;
    SizePolicy m_verticalSizePolicy = SizePolicy::Preferred;
    SizePolicy m_horizontalSizePolicy = SizePolicy::Preferred;
    Qt::WindowFlags m_windowFlags;
    int m_widgetAttributes = 0; // Qt::WidgetAttribute
    Qt::FocusPolicy m_focusPolicy = Qt::NoFocus;
    bool m_mouseTrackingEnabled = false;
    QRect m_normalGeometry;
    Qt::WindowStates m_oldWindowState = Qt::WindowState::WindowNoState;
    MouseEventRedirector *m_mouseEventRedirector = nullptr;
};

inline View_qtquick *asView_qtquick(View *view)
{
    if (!view)
        return nullptr;
    return static_cast<View_qtquick *>(view);
}

inline View_qtquick *asView_qtquick(Controller *controller)
{
    if (!controller)
        return nullptr;

    return static_cast<View_qtquick *>(controller->view());
}

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
