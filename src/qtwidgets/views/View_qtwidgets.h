/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "private/Utils_p.h"
#include "Controller.h"
#include "View.h"
#include "ViewWrapper_qtwidgets.h"
#include "qtwidgets/Window_qtwidgets.h"

#include <QDebug>
#include <QEvent>
#include <QResizeEvent>
#include <QSizePolicy>
#include <QWidget>

#include <memory>

namespace KDDockWidgets::Views {

template<typename Base>
class DOCKS_EXPORT View_qtwidgets : public Base, public View
{
public:
    using View::close;
    using View::height;
    using View::minimumHeight;
    using View::minimumWidth;
    using View::rect;
    using View::resize;
    using View::width;

    explicit View_qtwidgets(KDDockWidgets::Controller *controller, Type type,
                            QWidget *parent = nullptr,
                            Qt::WindowFlags windowFlags = {});

    ~View_qtwidgets() override = default;

    void free_impl() override
    {
        // QObject::deleteLater();
        delete this;
    }

    QSize sizeHint() const override
    {
        return Base::sizeHint();
    }

    QSize minSize() const override
    {
        const int minW = Base::minimumWidth() > 0 ? Base::minimumWidth()
                                                  : minimumSizeHint().width();

        const int minH = Base::minimumHeight() > 0 ? Base::minimumHeight()
                                                   : minimumSizeHint().height();

        return QSize(minW, minH).expandedTo(View::hardcodedMinimumSize());
    }

    QSize minimumSizeHint() const override
    {
        return Base::minimumSizeHint();
    }

    void setMinimumSize(QSize sz) override
    {
        if (sz != QWidget::minimumSize()) {
            QWidget::setMinimumSize(sz);
            layoutInvalidated.emit();
        }
    }

    QSize maxSizeHint() const override
    {
        // The max size is usually QWidget::maximumSize(), but we also honour the QSizePolicy::Fixed+sizeHint() case
        // as widgets don't need to have QWidget::maximumSize() to have a max size honoured

        const QSize min = minSize();
        QSize max = maximumSize();
        max = boundedMaxSize(min, max); // for safety against weird values

        const QSizePolicy policy = sizePolicy();

        if (policy.verticalPolicy() == QSizePolicy::Fixed || policy.verticalPolicy() == QSizePolicy::Maximum)
            max.setHeight(qMin(max.height(), sizeHint().height()));
        if (policy.horizontalPolicy() == QSizePolicy::Fixed || policy.horizontalPolicy() == QSizePolicy::Maximum)
            max.setWidth(qMin(max.width(), sizeHint().width()));

        max = View::boundedMaxSize(min, max); // for safety against weird values
        return max;
    }

    QSize maximumSize() const override
    {
        return Base::maximumSize();
    }

    QRect geometry() const override
    {
        return Base::geometry();
    }

    QRect normalGeometry() const override
    {
        return Base::normalGeometry();
    }

    void setGeometry(QRect geo) override
    {
        Base::setGeometry(geo);
    }

    void setMaximumSize(QSize sz) override
    {
        if (sz != QWidget::maximumSize()) {
            Base::setMaximumSize(sz);
            layoutInvalidated.emit();
        }
    }

    bool isVisible() const override
    {
        return Base::isVisible();
    }

    void setVisible(bool is) override
    {
        Base::setVisible(is);
    }

    void move(int x, int y) override
    {
        Base::move(x, y);
    }

    void setSize(int width, int height) override
    {
        Base::resize(width, height);
    }

    void setWidth(int width) override
    {
        setSize(width, QWidget::height());
    }

    void setHeight(int height) override
    {
        setSize(QWidget::width(), height);
    }

    void setFixedWidth(int w) override
    {
        QWidget::setFixedWidth(w);
    }

    void setFixedHeight(int h) override
    {
        QWidget::setFixedHeight(h);
    }

    void show() override
    {
        Base::show();
    }

    void createPlatformWindow()
    {
        QWidget::create();
    }

    void hide() override
    {
        Base::hide();
    }

    void update() override
    {
        Base::update();
    }

    static void setParentFor(QWidget *widget, View *parent)
    {
        if (!parent) {
            widget->QWidget::setParent(nullptr);
            return;
        }

        if (auto qwidget = qobject_cast<QWidget *>(parent->asQObject())) {
            widget->QWidget::setParent(qwidget);
        } else {
            qWarning() << Q_FUNC_INFO << "parent is not a widget, you have a bug"
                       << parent->asQObject();
            Q_ASSERT(false);
        }
    }

    void setParent(View *parent) override
    {
        setParentFor(this, parent);
    }

    void raiseAndActivate() override
    {
        Base::window()->raise();
        if (!isWayland())
            Base::window()->activateWindow();
    }

    void activateWindow() override
    {
        Base::activateWindow();
    }

    void raise() override
    {
        Base::window()->raise();
    }

    bool isRootView() const override
    {
        return QWidget::isWindow();
    }

    QPoint mapToGlobal(QPoint localPt) const override
    {
        return Base::mapToGlobal(localPt);
    }

    QPoint mapFromGlobal(QPoint globalPt) const override
    {
        return Base::mapFromGlobal(globalPt);
    }

    QPoint mapTo(View *someAncestor, QPoint pos) const override
    {
        return QWidget::mapTo(qobject_cast<QWidget *>(someAncestor->asQObject()), pos);
    }

    void setSizePolicy(QSizePolicy policy) override
    {
        Base::setSizePolicy(policy);
    }

    QSizePolicy sizePolicy() const override
    {
        return QWidget::sizePolicy();
    }

    void setWindowOpacity(double v) override
    {
        QWidget::setWindowOpacity(v);
    }

    void render(QPainter *p) override
    {
        Base::render(p);
    }

    void setCursor(Qt::CursorShape shape) override
    {
        QWidget::setCursor(shape);
    }

    void setMouseTracking(bool enable) override
    {
        QWidget::setMouseTracking(enable);
    }

    bool close() override
    {
        return QWidget::close();
    }

    void setFlag(Qt::WindowType flag, bool on = true) override
    {
        QWidget::setWindowFlag(flag, on);
    }

    void setAttribute(Qt::WidgetAttribute attr, bool enable = true) override
    {
        QWidget::setAttribute(attr, enable);
    }

    bool testAttribute(Qt::WidgetAttribute attr) const override
    {
        return QWidget::testAttribute(attr);
    }

    Qt::WindowFlags flags() const override
    {
        return QWidget::windowFlags();
    }

    void setWindowTitle(const QString &title) override
    {
        QWidget::setWindowTitle(title);
    }

    void setWindowIcon(const QIcon &icon) override
    {
        QWidget::setWindowIcon(icon);
    }

    bool isActiveWindow() const override
    {
        return QWidget::isActiveWindow();
    }

    void showNormal() override
    {
        return QWidget::showNormal();
    }

    void showMinimized() override
    {
        return QWidget::showMinimized();
    }

    void showMaximized() override
    {
        return QWidget::showMaximized();
    }

    bool isMinimized() const override
    {
        return QWidget::isMinimized();
    }

    bool isMaximized() const override
    {
        return QWidget::isMaximized();
    }

    Qt::FocusPolicy focusPolicy() const override
    {
        return QWidget::focusPolicy();
    }

    bool hasFocus() const override
    {
        return QWidget::hasFocus();
    }

    std::shared_ptr<ViewWrapper> childViewAt(QPoint localPos) const override
    {
        if (QWidget *child = QWidget::childAt(localPos))
            return std::shared_ptr<ViewWrapper>(new ViewWrapper_qtwidgets(child));

        return {};
    }

    std::shared_ptr<Window> window() const override
    {
        if (QWidget *root = QWidget::window()) {
            if (root->window()) {
                return std::shared_ptr<Window>(new Window_qtwidgets(root));
            }
        }

        return {};
    }

    std::shared_ptr<ViewWrapper> rootView() const override
    {
        if (auto w = QWidget::window()) {
            ViewWrapper *wrapper = new ViewWrapper_qtwidgets(w);
            return std::shared_ptr<ViewWrapper>(wrapper);
        }

        return {};
    }

    std::shared_ptr<ViewWrapper> parentView() const override
    {
        if (QWidget *p = QWidget::parentWidget()) {
            ViewWrapper *wrapper = new ViewWrapper_qtwidgets(p);
            return std::shared_ptr<ViewWrapper>(wrapper);
        }

        return {};
    }

    std::shared_ptr<ViewWrapper> asWrapper() override
    {
        ViewWrapper *wrapper = new ViewWrapper_qtwidgets(this);
        return std::shared_ptr<ViewWrapper>(wrapper);
    }

    void setObjectName(const QString &name) override
    {
        QWidget::setObjectName(name);
    }

    void grabMouse() override
    {
        QWidget::grabMouse();
    }

    void releaseMouse() override
    {
        QWidget::releaseMouse();
    }

    void releaseKeyboard() override
    {
        QWidget::releaseKeyboard();
    }

    void setFocus(Qt::FocusReason reason) override
    {
        QWidget::setFocus(reason);
    }

    void setFocusPolicy(Qt::FocusPolicy policy) override
    {
        QWidget::setFocusPolicy(policy);
    }

    QString objectName() const override
    {
        return QWidget::objectName();
    }

    QVariant property(const char *name) const override
    {
        return QWidget::property(name);
    }

    static QWidget *asQWidget(View *view)
    {
        if (!view)
            return nullptr;

        return qobject_cast<QWidget *>(view->asQObject());
    }

    static QWidget *asQWidget(Controller *controller)
    {
        if (!controller)
            return nullptr;
        return asQWidget(controller->view());
    }

    static QVector<std::shared_ptr<View>> childViewsFor(const QWidget *parent)
    {
        QVector<std::shared_ptr<View>> result;
        const QObjectList children = parent->children();
        result.reserve(children.size());
        for (QObject *child : children) {
            if (auto widget = qobject_cast<QWidget *>(child)) {
                ViewWrapper *wrapper = new ViewWrapper_qtwidgets(widget);
                result.push_back(ViewWrapper::Ptr(wrapper));
            }
        }

        return result;
    }

    QVector<std::shared_ptr<View>> childViews() const override
    {
        return childViewsFor(this);
    }

protected:
    bool event(QEvent *e) override
    {
        if (e->type() == QEvent::LayoutRequest)
            onLayoutRequest();

        return Base::event(e);
    }

    void resizeEvent(QResizeEvent *ev) override
    {
        if (!onResize(ev->size()))
            Base::resizeEvent(ev);
    }

    void closeEvent(QCloseEvent *ev) override
    {
        closeRequested.emit(ev);
    }

private:
    Q_DISABLE_COPY(View_qtwidgets)
};

inline qreal logicalDpiFactor(const QWidget *w)
{
#ifdef Q_OS_MACOS
    // It's always 72 on mac
    Q_UNUSED(w);
    return 1;
#else
    return w->logicalDpiX() / 96.0;
#endif
}

inline QWindow *windowForWidget(const QWidget *w)
{
    return w ? w->window()->windowHandle() : nullptr;
}


/// @brief sets the geometry on the QWindow containing the specified item
inline void setTopLevelGeometry(QRect geometry, const QWidget *widget)
{
    if (!widget)
        return;

    if (QWidget *topLevel = widget->window())
        topLevel->setGeometry(geometry);
}

} // namespace KDDockWidgets::Views