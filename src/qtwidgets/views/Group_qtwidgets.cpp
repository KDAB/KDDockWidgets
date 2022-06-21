/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Group_qtwidgets.h"

#include "qtwidgets/views/View_qtwidgets.h"
#include "qtwidgets/views/DockWidget_qtwidgets.h"

#include "kddockwidgets/controllers/Layout.h"
#include "kddockwidgets/controllers/Group.h"
#include "kddockwidgets/controllers/Stack.h"
#include "kddockwidgets/controllers/TabBar.h"
#include "kddockwidgets/controllers/TitleBar.h"
#include "Config.h"
#include "private/View_p.h"

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
        m_frameWidget->d->layoutInvalidated.emit();
    }

    Frame_qtwidgets *const m_frameWidget;
};

VBoxLayout::~VBoxLayout() = default;

Frame_qtwidgets::Frame_qtwidgets(Controllers::Frame *controller, QWidget *parent)
    : View_qtwidgets<QWidget>(controller, Type::Frame, parent)
    , FrameViewInterface(controller)
{
}

void Frame_qtwidgets::init()
{
    auto vlayout = new VBoxLayout(this);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setSpacing(0);
    vlayout->addWidget(asQWidget(m_frame->titleBar()));
    auto tabWidget = m_frame->tabWidget();
    vlayout->addWidget(asQWidget(m_frame->tabWidget()));

    tabWidget->setTabBarAutoHide(!m_frame->alwaysShowsTabs());

    if (m_frame->isOverlayed())
        setAutoFillBackground(true);
}

void Frame_qtwidgets::free_impl()
{
    // TODOm3: just use the base class impl, which uses deleteLater()
    // do it once there's no state here
    delete this;
}

void Frame_qtwidgets::renameTab(int index, const QString &text)
{
    m_frame->tabWidget()->renameTab(index, text);
}

void Frame_qtwidgets::changeTabIcon(int index, const QIcon &icon)
{
    m_frame->tabWidget()->changeTabIcon(index, icon);
}

int Frame_qtwidgets::nonContentsHeight() const
{
    Controllers::TitleBar *tb = m_frame->titleBar();
    QWidget *tabBar = asQWidget(m_frame->tabBar());

    return (tb->isVisible() ? tb->height() : 0) + (tabBar->isVisible() ? tabBar->height() : 0);
}

int Frame_qtwidgets::indexOfDockWidget_impl(const Controllers::DockWidget *dw)
{
    return m_frame->tabWidget()->indexOfDockWidget(dw);
}

void Frame_qtwidgets::setCurrentDockWidget_impl(Controllers::DockWidget *dw)
{
    m_frame->tabWidget()->setCurrentDockWidget(dw);
}

int Frame_qtwidgets::currentIndex_impl() const
{
    return m_frame->tabWidget()->currentIndex();
}

void Frame_qtwidgets::insertDockWidget_impl(Controllers::DockWidget *dw, int index)
{
    m_frame->tabWidget()->insertDockWidget(dw, index);
}

void Frame_qtwidgets::removeWidget_impl(Controllers::DockWidget *dw)
{
    m_frame->tabWidget()->removeDockWidget(dw);
}

void Frame_qtwidgets::setCurrentTabIndex_impl(int index)
{
    m_frame->tabWidget()->setCurrentDockWidget(index);
}

KDDockWidgets::Controllers::DockWidget *Frame_qtwidgets::currentDockWidget_impl() const
{
    return m_frame->tabWidget()->dockwidgetAt(m_frame->tabWidget()->currentIndex());
}

KDDockWidgets::Controllers::DockWidget *Frame_qtwidgets::dockWidgetAt_impl(int index) const
{
    return m_frame->tabWidget()->dockwidgetAt(index);
}

bool Frame_qtwidgets::event(QEvent *e)
{
    if (freed())
        return QWidget::event(e);

    if (e->type() == QEvent::ParentChange) {
        auto p = parentView();
        m_frame->setLayout(p ? p->asLayout() : nullptr);
    }

    return QWidget::event(e);
}

void Frame_qtwidgets::paintEvent(QPaintEvent *)
{
    if (freed())
        return;

    if (!m_frame->isFloating()) {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        const qreal penWidth = 1;
        const qreal halfPenWidth = penWidth / 2;
        const QRectF rectf = QWidget::rect();

        const bool isOverlayed = m_frame->isOverlayed();
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
    const QSize waste = minSize() - m_frame->dockWidgetsMinSize();
    return waste + m_frame->biggestDockWidgetMaxSize();
}

QRect Frame_qtwidgets::dragRect() const
{
    QRect rect = m_frame->dragRect();
    if (rect.isValid())
        return rect;

    if (Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible) {
        auto tabBar = qobject_cast<QTabBar *>(asQWidget(m_frame->tabBar()));
        rect.setHeight(tabBar->height());
        rect.setWidth(QWidget::width() - tabBar->width());
        rect.moveTopLeft(QPoint(tabBar->width(), tabBar->y()));
        rect.moveTopLeft(QWidget::mapToGlobal(rect.topLeft()));
    }

    return rect;
}
