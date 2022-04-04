/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Stack_qtquick.h"
#include "Controller.h"
#include "controllers/Stack.h"
#include "controllers/TitleBar.h"
#include "qtwidgets/views/DockWidget_qtquick.h"
#include "private/DockRegistry_p.h"
#include "kddockwidgets/FrameworkWidgetFactory.h"

#include <QMouseEvent>
#include <QTabBar>
#include <QHBoxLayout>
#include <QAbstractButton>
#include <QMenu>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

Stack_qtquick::Stack_qtquick(Controllers::Stack *controller, Controllers::Frame *parent)
    : View_qtquick<QTabWidget>(controller, Type::Separator, parent ? parent->view()->asQWidget() : nullptr)
    , m_stack(controller)
{
}

void Stack_qtquick::init()
{
    setTabBar(tabBar());
    setTabsClosable(Config::self().flags() & Config::Flag_TabsHaveCloseButton);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTabWidget::customContextMenuRequested, this, &Stack_qtquick::showContextMenu);

    // In case tabs closable is set by the factory, a tabClosedRequested() is emitted when the user presses [x]
    connect(this, &QTabWidget::tabCloseRequested, this, [this](int index) {
        if (auto dw = dockwidgetAt(index)) {
            if (dw->options() & Controllers::DockWidget::Option_NotClosable) {
                qWarning() << "QTabWidget::tabCloseRequested: Refusing to close dock widget with Option_NotClosable option. name=" << dw->uniqueName();
            } else {
                dw->view()->close();
            }
        } else {
            qWarning() << "QTabWidget::tabCloseRequested Couldn't find dock widget for index" << index << "; count=" << count();
        }
    });

    connect(this, &QTabWidget::currentChanged, this, [this](int index) {
        m_stack->onCurrentTabChanged(index);
        Q_EMIT m_stack->currentTabChanged(index);
        Q_EMIT m_stack->currentDockWidgetChanged(m_stack->currentDockWidget());
    });

    if (!QTabWidget::tabBar()->isVisible())
        setFocusProxy(nullptr);

    setupTabBarButtons();

    setDocumentMode(m_stack->options() & StackOption_DocumentMode);
}

int Stack_qtquick::numDockWidgets() const
{
    return count();
}

void Stack_qtquick::removeDockWidget(Controllers::DockWidget *dw)
{
    removeTab(indexOf(dw->view()->asQWidget()));
}

int Stack_qtquick::indexOfDockWidget(const Controllers::DockWidget *dw) const
{
    return indexOf(dw->view()->asQWidget());
}

void Stack_qtquick::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if (m_stack->onMouseDoubleClick(ev->pos())) {
        ev->accept();
    } else {
        ev->ignore();
    }
}

void Stack_qtquick::mousePressEvent(QMouseEvent *ev)
{
    QTabWidget::mousePressEvent(ev);

    if ((Config::self().flags() & Config::Flag_TitleBarIsFocusable) && !m_stack->frame()->isFocused()) {
        // User clicked on the tab widget itself
        m_stack->frame()->FocusScope::focus(Qt::MouseFocusReason);
    }
}

void Stack_qtquick::tabInserted(int)
{
    m_stack->onTabInserted();
}

void Stack_qtquick::tabRemoved(int)
{
    m_stack->onTabRemoved();
}

void Stack_qtquick::setCurrentDockWidget(int index)
{
    setCurrentIndex(index);
}

bool Stack_qtquick::insertDockWidget(int index, Controllers::DockWidget *dw,
                                       const QIcon &icon, const QString &title)
{
    insertTab(index, dw->view()->asQWidget(), icon, title);
    return true;
}

void Stack_qtquick::setTabBarAutoHide(bool b)
{
    QTabWidget::setTabBarAutoHide(b);
}

void Stack_qtquick::renameTab(int index, const QString &text)
{
    setTabText(index, text);
}

void Stack_qtquick::changeTabIcon(int index, const QIcon &icon)
{
    setTabIcon(index, icon);
}

Controllers::DockWidget *Stack_qtquick::dockwidgetAt(int index) const
{
    auto view = qobject_cast<DockWidget_qtquick *>(widget(index));
    return view ? view->dockWidget() : nullptr;
}

int Stack_qtquick::currentIndex() const
{
    return QTabWidget::currentIndex();
}

void Stack_qtquick::setupTabBarButtons()
{
    if (!(Config::self().flags() & Config::Flag_ShowButtonsOnTabBarIfTitleBarHidden))
        return;

    auto factory = Config::self().frameworkWidgetFactory();
    m_closeButton = factory->createTitleBarButton(this, TitleBarButtonType::Close);
    m_floatButton = factory->createTitleBarButton(this, TitleBarButtonType::Float);

    auto cornerWidget = new QWidget(this);
    cornerWidget->setObjectName(QStringLiteral("Corner Widget"));

    setCornerWidget(cornerWidget, Qt::TopRightCorner);

    m_cornerWidgetLayout = new QHBoxLayout(cornerWidget);

    m_cornerWidgetLayout->addWidget(m_floatButton);
    m_cornerWidgetLayout->addWidget(m_closeButton);

    connect(m_floatButton, &QAbstractButton::clicked, this, [this] {
        Controllers::TitleBar *tb = m_stack->frame()->titleBar();
        tb->onFloatClicked();
    });

    connect(m_closeButton, &QAbstractButton::clicked, this, [this] {
        Controllers::TitleBar *tb = m_stack->frame()->titleBar();
        tb->onCloseClicked();
    });

    updateMargins();
    connect(DockRegistry::self(), &DockRegistry::windowChangedScreen, this, [this](QWindow *w) {
        if (w == window()->windowHandle())
            updateMargins();
    });
}

void Stack_qtquick::updateMargins()
{
    const qreal factor = logicalDpiFactor(this);
    m_cornerWidgetLayout->setContentsMargins(QMargins(0, 0, 2, 0) * factor);
    m_cornerWidgetLayout->setSpacing(int(2 * factor));
}

void Stack_qtquick::showContextMenu(QPoint pos)
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
        QAction *action = menu.addAction(tabText(i), this, [this, i] {
            setCurrentIndex(i);
        });
        if (i == currentIndex())
            action->setDisabled(true);
    }
    menu.exec(mapToGlobal(pos));
}

QTabBar *Stack_qtquick::tabBar() const
{
    return static_cast<QTabBar *>(m_stack->tabBar()->view()->asQWidget());
}

Controllers::Stack *Stack_qtquick::stack() const
{
    return m_stack;
}

bool Stack_qtquick::isPositionDraggable(QPoint p) const
{
    if (tabPosition() != QTabWidget::North) {
        qWarning() << Q_FUNC_INFO << "Not implemented yet. Only North is supported";
        return false;
    }

    return p.y() >= 0 && p.y() <= tabBar()->height();
}
