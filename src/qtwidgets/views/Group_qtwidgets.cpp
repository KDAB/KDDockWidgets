/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
    explicit VBoxLayout(Group_qtwidgets *parent)
        : QVBoxLayout(parent)
        , m_groupWidget(parent)
    {
    }
    ~VBoxLayout() override;

    void invalidate() override
    {
        if (m_groupWidget->inDtor())
            return;
        QVBoxLayout::invalidate();
        m_groupWidget->d->layoutInvalidated.emit();
    }

    Group_qtwidgets *const m_groupWidget;
};

VBoxLayout::~VBoxLayout() = default;

Group_qtwidgets::Group_qtwidgets(Controllers::Group *controller, QWidget *parent)
    : View_qtwidgets<QWidget>(controller, Type::Frame, parent)
    , GroupViewInterface(controller)
{
}

void Group_qtwidgets::init()
{
    auto vlayout = new VBoxLayout(this);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setSpacing(0);
    vlayout->addWidget(asQWidget(m_group->titleBar()));

    vlayout->addWidget(asQWidget(m_group->stack()));

    if (m_group->isOverlayed())
        setAutoFillBackground(true);
}

void Group_qtwidgets::free_impl()
{
    // TODOm3: just use the base class impl, which uses deleteLater()
    // do it once there's no state here
    delete this;
}

int Group_qtwidgets::nonContentsHeight() const
{
    Controllers::TitleBar *tb = m_group->titleBar();
    QWidget *tabBar = asQWidget(m_group->tabBar());

    return (tb->isVisible() ? tb->height() : 0) + (tabBar->isVisible() ? tabBar->height() : 0);
}

void Group_qtwidgets::paintEvent(QPaintEvent *)
{
    if (freed())
        return;

    if (!m_group->isFloating()) {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        const qreal penWidth = 1;
        const qreal halfPenWidth = penWidth / 2;
        const QRectF rectf = QWidget::rect();

        const bool isOverlayed = m_group->isOverlayed();
        const QColor penColor = isOverlayed ? QColor(0x666666) : QColor(184, 184, 184, 184);
        QPen pen(penColor);
        pen.setWidthF(penWidth);
        p.setPen(pen);

        if (isOverlayed) {
            pen.setJoinStyle(Qt::MiterJoin);
            p.drawRect(rectf.adjusted(halfPenWidth, penWidth, -halfPenWidth, -halfPenWidth));
        } else {
            p.drawRoundedRect(
                rectf.adjusted(halfPenWidth, halfPenWidth, -halfPenWidth, -halfPenWidth), 2, 2);
        }
    }
}

QSize Group_qtwidgets::maxSizeHint() const
{
    if (freed())
        return {};

    // waste due to QTabWidget margins, tabbar etc.
    const QSize waste = minSize() - m_group->dockWidgetsMinSize();
    return waste + m_group->biggestDockWidgetMaxSize();
}

QRect Group_qtwidgets::dragRect() const
{
    QRect rect = m_group->dragRect();
    if (rect.isValid())
        return rect;

    if (Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible) {
        auto tabBar = qobject_cast<QTabBar *>(asQWidget(m_group->tabBar()));
        rect.setHeight(tabBar->height());
        rect.setWidth(QWidget::width() - tabBar->width());
        rect.moveTopLeft(QPoint(tabBar->width(), tabBar->y()));
        rect.moveTopLeft(QWidget::mapToGlobal(rect.topLeft()));
    }

    return rect;
}
