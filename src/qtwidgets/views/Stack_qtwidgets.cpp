/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Stack_qtwidgets.h"
#include "Controller.h"
#include "kddockwidgets/controllers/Stack.h"
#include "kddockwidgets/controllers/TitleBar.h"
#include "qtwidgets/ViewFactory_qtwidgets.h"
#include "qtwidgets/views/DockWidget_qtwidgets.h"
#include "DockRegistry.h"
#include "Config.h"
#include "Window.h"
#include "private/View_p.h"

#include <QMouseEvent>
#include <QTabBar>
#include <QHBoxLayout>
#include <QAbstractButton>
#include <QMenu>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

Stack_qtwidgets::Stack_qtwidgets(Controllers::Stack *controller, QWidget *parent)
    : View_qtwidgets<QTabWidget>(controller, Type::Stack, parent)
    , StackViewInterface(controller)
{
}

Stack_qtwidgets::~Stack_qtwidgets()
{
}

void Stack_qtwidgets::init()
{
    setTabBar(tabBar());
    setTabsClosable(Config::self().flags() & Config::Flag_TabsHaveCloseButton);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTabWidget::customContextMenuRequested, this, &Stack_qtwidgets::showContextMenu);

    // In case tabs closable is set by the factory, a tabClosedRequested() is emitted when the user
    // presses [x]
    connect(this, &QTabWidget::tabCloseRequested, this, [this](int index) {
        if (auto dw = m_stack->tabBar()->dockWidgetAt(index)) {
            if (dw->options() & DockWidgetOption_NotClosable) {
                qWarning() << "QTabWidget::tabCloseRequested: Refusing to close dock widget with "
                              "Option_NotClosable option. name="
                           << dw->uniqueName();
            } else {
                dw->view()->close();
            }
        } else {
            qWarning() << "QTabWidget::tabCloseRequested Couldn't find dock widget for index"
                       << index << "; count=" << count();
        }
    });

    QTabWidget::setTabBarAutoHide(m_stack->tabBarAutoHide());

    m_tabBarAutoHideChanged = m_stack->tabBarAutoHideChanged.connect(
        [this](bool is) { QTabWidget::setTabBarAutoHide(is); });

    if (!QTabWidget::tabBar()->isVisible())
        setFocusProxy(nullptr);

    setupTabBarButtons();

    setDocumentMode(m_stack->options() & StackOption_DocumentMode);
}

void Stack_qtwidgets::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if (m_stack->onMouseDoubleClick(ev->pos())) {
        ev->accept();
    } else {
        ev->ignore();
    }
}

void Stack_qtwidgets::mousePressEvent(QMouseEvent *ev)
{
    QTabWidget::mousePressEvent(ev);

    if ((Config::self().flags() & Config::Flag_TitleBarIsFocusable)
        && !m_stack->group()->isFocused()) {
        // User clicked on the tab widget itself
        m_stack->group()->FocusScope::focus(Qt::MouseFocusReason);
    }
}

void Stack_qtwidgets::setupTabBarButtons()
{
    if (!(Config::self().flags() & Config::Flag_ShowButtonsOnTabBarIfTitleBarHidden))
        return;

    // TODOm3: Make sure people can only inherit from the Default*variants
    auto factory = static_cast<ViewFactory_qtwidgets *>(Config::self().viewFactory());
    m_closeButton = factory->createTitleBarButton(this, TitleBarButtonType::Close);
    m_floatButton = factory->createTitleBarButton(this, TitleBarButtonType::Float);

    auto cornerWidget = new QWidget(this);
    cornerWidget->setObjectName(QStringLiteral("Corner Widget"));

    setCornerWidget(cornerWidget, Qt::TopRightCorner);

    m_cornerWidgetLayout = new QHBoxLayout(cornerWidget);

    m_cornerWidgetLayout->addWidget(m_floatButton);
    m_cornerWidgetLayout->addWidget(m_closeButton);

    connect(m_floatButton, &QAbstractButton::clicked, this, [this] {
        Controllers::TitleBar *tb = m_stack->group()->titleBar();
        tb->onFloatClicked();
    });

    connect(m_closeButton, &QAbstractButton::clicked, this, [this] {
        Controllers::TitleBar *tb = m_stack->group()->titleBar();
        tb->onCloseClicked();
    });

    updateMargins();
    connect(DockRegistry::self(), &DockRegistry::windowChangedScreen, this, [this](Window::Ptr w) {
        if (isInWindow(w))
            updateMargins();
    });
}

void Stack_qtwidgets::updateMargins()
{
    const qreal factor = logicalDpiFactor(this);
    m_cornerWidgetLayout->setContentsMargins(QMargins(0, 0, 2, 0) * factor);
    m_cornerWidgetLayout->setSpacing(int(2 * factor));
}

void Stack_qtwidgets::showContextMenu(QPoint pos)
{
    if (!(Config::self().flags() & Config::Flag_AllowSwitchingTabsViaMenu))
        return;

    QTabBar *tabBar = QTabWidget::tabBar();
    // We don't want context menu if there is only one tab
    if (tabBar->count() <= 1)
        return;

    // Click on a tab => No menu
    if (tabBar->tabAt(pos) >= 0)
        return;

    // Right click is allowed only on the tabs area
    QRect tabAreaRect = tabBar->rect();
    tabAreaRect.setWidth(this->width());
    if (!tabAreaRect.contains(pos))
        return;

    QMenu menu(this);
    for (int i = 0; i < tabBar->count(); ++i) {
        QAction *action = menu.addAction(tabText(i), this, [this, i] { setCurrentIndex(i); });
        if (i == currentIndex())
            action->setDisabled(true);
    }
    menu.exec(mapToGlobal(pos));
}

QTabBar *Stack_qtwidgets::tabBar() const
{
    return static_cast<QTabBar *>(View_qt::asQWidget((m_stack->tabBar())));
}

void Stack_qtwidgets::setDocumentMode(bool is)
{
    QTabWidget::setDocumentMode(is);
}

Controllers::Stack *Stack_qtwidgets::stack() const
{
    return m_stack;
}

bool Stack_qtwidgets::isPositionDraggable(QPoint p) const
{
    if (tabPosition() != QTabWidget::North) {
        qWarning() << Q_FUNC_INFO << "Not implemented yet. Only North is supported";
        return false;
    }

    return p.y() >= 0 && p.y() <= tabBar()->height();
}
