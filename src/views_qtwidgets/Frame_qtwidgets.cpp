/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Frame_qtwidgets.h"

#include "views_qtwidgets/View_qtwidgets.h"
#include "views_qtwidgets/DockWidget_qtwidgets.h"

#include "private/LayoutWidget_p.h"
#include "controllers/Frame.h"
#include "controllers/Stack.h"
#include "controllers/TabBar.h"
#include "controllers/TitleBar.h"

#include <QPainter>
#include <QTabBar>
#include <QVBoxLayout>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

///@brief a QVBoxLayout that emits layoutInvalidated so that Item can detect minSize changes
class VBoxLayout : public QVBoxLayout // clazy:exclude=missing-qobject-macro
{
public:
    explicit VBoxLayout(Frame_qtwidgets *parent)
        : QVBoxLayout(parent)
        , m_frameWidget(parent)
    {
    }
    ~VBoxLayout() override;

    void invalidate() override
    {
        if (m_frameWidget->inDtor())
            return;
        QVBoxLayout::invalidate();
        Q_EMIT m_frameWidget->layoutInvalidated();
    }

    Frame_qtwidgets *const m_frameWidget;
};

VBoxLayout::~VBoxLayout() = default;

Frame_qtwidgets::Frame_qtwidgets(Controllers::Frame *controller, QWidget *parent)
    : View_qtwidgets<QWidget>(controller, View::Type::Frame, parent)
    , m_controller(controller)
{
}

void Frame_qtwidgets::init()
{
    auto vlayout = new VBoxLayout(this);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_controller->titleBar()->view()->asQWidget());
    auto tabWidget = m_controller->tabWidget();
    vlayout->addWidget(tabWidget->view()->asQWidget());

    tabWidget->setTabBarAutoHide(!m_controller->alwaysShowsTabs());

    if (m_controller->isOverlayed())
        setAutoFillBackground(true);
}

void Frame_qtwidgets::free_impl()
{
    // TODO: just use the base class impl, which uses deleteLater()
    // do it once there's no state here
    delete this;
}

void Frame_qtwidgets::setLayoutItem(Layouting::Item *item)
{
    // TODO: Remove from View, maybe
    m_controller->setLayoutItem(item);
}

void Frame_qtwidgets::renameTab(int index, const QString &text)
{
    m_controller->tabWidget()->renameTab(index, text);
}

void Frame_qtwidgets::changeTabIcon(int index, const QIcon &icon)
{
    m_controller->tabWidget()->changeTabIcon(index, icon);
}

int Frame_qtwidgets::nonContentsHeight() const
{
    Controllers::TitleBar *tb = m_controller->titleBar();
    QWidget *tabBar = m_controller->tabBar()->view()->asQWidget();

    return (tb->isVisible() ? tb->height() : 0) + (tabBar->isVisible() ? tabBar->height() : 0);
}

int Frame_qtwidgets::indexOfDockWidget_impl(const Controllers::DockWidgetBase *dw)
{
    return m_controller->tabWidget()->indexOfDockWidget(dw);
}

void Frame_qtwidgets::setCurrentDockWidget_impl(Controllers::DockWidgetBase *dw)
{
    m_controller->tabWidget()->setCurrentDockWidget(dw);
}

int Frame_qtwidgets::currentIndex_impl() const
{
    return m_controller->tabWidget()->currentIndex();
}

void Frame_qtwidgets::insertDockWidget_impl(Controllers::DockWidgetBase *dw, int index)
{
    m_controller->tabWidget()->insertDockWidget(dw, index);
}

void Frame_qtwidgets::removeWidget_impl(Controllers::DockWidgetBase *dw)
{
    m_controller->tabWidget()->removeDockWidget(dw);
}

void Frame_qtwidgets::setCurrentTabIndex_impl(int index)
{
    m_controller->tabWidget()->setCurrentDockWidget(index);
}

KDDockWidgets::Controllers::DockWidgetBase *Frame_qtwidgets::currentDockWidget_impl() const
{
    return m_controller->tabWidget()->dockwidgetAt(m_controller->tabWidget()->currentIndex());
}

KDDockWidgets::Controllers::DockWidgetBase *Frame_qtwidgets::dockWidgetAt_impl(int index) const
{
    return m_controller->tabWidget()->dockwidgetAt(index);
}

Controllers::Frame *Frame_qtwidgets::frame() const
{
    return m_controller;
}

bool Frame_qtwidgets::event(QEvent *e)
{
    if (freed())
        return QWidget::event(e);

    if (e->type() == QEvent::ParentChange) {
        if (auto layoutWidget = qobject_cast<LayoutWidget *>(QWidget::parentWidget())) {
            m_controller->setLayoutWidget(layoutWidget);
        } else {
            m_controller->setLayoutWidget(nullptr);
        }
    }

    return QWidget::event(e);
}

void Frame_qtwidgets::closeEvent(QCloseEvent *e)
{
    if (!freed())
        m_controller->onCloseEvent(e);
}

void Frame_qtwidgets::paintEvent(QPaintEvent *)
{
    if (freed())
        return;

    if (!m_controller->isFloating()) {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        const qreal penWidth = 1;
        const qreal halfPenWidth = penWidth / 2;
        const QRectF rectf = QWidget::rect();

        const bool isOverlayed = m_controller->isOverlayed();
        const QColor penColor = isOverlayed ? QColor(0x666666)
                                            : QColor(184, 184, 184, 184);
        QPen pen(penColor);
        pen.setWidthF(penWidth);
        p.setPen(pen);

        if (isOverlayed) {
            pen.setJoinStyle(Qt::MiterJoin);
            p.drawRect(rectf.adjusted(halfPenWidth, penWidth, -halfPenWidth, -halfPenWidth));
        } else {
            p.drawRoundedRect(rectf.adjusted(halfPenWidth, halfPenWidth, -halfPenWidth, -halfPenWidth), 2, 2);
        }
    }
}

QSize Frame_qtwidgets::maxSizeHint() const
{
    if (freed())
        return {};

    // waste due to QTabWidget margins, tabbar etc.
    const QSize waste = minSize() - m_controller->dockWidgetsMinSize();
    return waste + m_controller->biggestDockWidgetMaxSize();
}

QRect Frame_qtwidgets::dragRect() const
{
    QRect rect = m_controller->dragRect();
    if (rect.isValid())
        return rect;

    if (Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible) {
        auto tabBar = qobject_cast<QTabBar *>(m_controller->tabBar()->view()->asQWidget());
        rect.setHeight(tabBar->height());
        rect.setWidth(QWidget::width() - tabBar->width());
        rect.moveTopLeft(QPoint(tabBar->width(), tabBar->y()));
        rect.moveTopLeft(QWidget::mapToGlobal(rect.topLeft()));
    }

    return rect;
}
