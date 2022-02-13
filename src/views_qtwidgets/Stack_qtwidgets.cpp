/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Stack_qtwidgets.h"
#include "Controller.h"
#include "controllers/Stack.h"
#include "controllers/TitleBar.h"
#include "views_qtwidgets/DockWidget_qtwidgets.h"
#include "private/DockRegistry_p.h"
#include "kddockwidgets/FrameworkWidgetFactory.h"

#include <QMouseEvent>
#include <QTabBar>
#include <QHBoxLayout>
#include <QAbstractButton>
#include <QMenu>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

Stack_qtwidgets::Stack_qtwidgets(Controllers::Stack *controller, Controllers::Frame *parent)
    : View_qtwidgets<QTabWidget>(controller, View::Type::Separator, parent ? parent->view()->asQWidget() : nullptr)
    , m_stack(controller)
{
}

void Stack_qtwidgets::init()
{
    setTabBar(tabBar());
    setTabsClosable(Config::self().flags() & Config::Flag_TabsHaveCloseButton);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTabWidget::customContextMenuRequested, this, &Stack_qtwidgets::showContextMenu);

    // In case tabs closable is set by the factory, a tabClosedRequested() is emitted when the user presses [x]
    connect(this, &QTabWidget::tabCloseRequested, this, [this](int index) {
        if (auto dw = dockwidgetAt(index)) {
            if (dw->options() & Controllers::DockWidgetBase::Option_NotClosable) {
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

    setDocumentMode(m_stack->options() & TabWidgetOption_DocumentMode);
}

int Stack_qtwidgets::numDockWidgets() const
{
    return count();
}

void Stack_qtwidgets::removeDockWidget(Controllers::DockWidgetBase *dw)
{
    removeTab(indexOf(dw->view()->asQWidget()));
}

int Stack_qtwidgets::indexOfDockWidget(const Controllers::DockWidgetBase *dw) const
{
    return indexOf(dw->view()->asQWidget());
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

    if ((Config::self().flags() & Config::Flag_TitleBarIsFocusable) && !m_stack->frame()->isFocused()) {
        // User clicked on the tab widget itself
        m_stack->frame()->FocusScope::focus(Qt::MouseFocusReason);
    }
}

void Stack_qtwidgets::tabInserted(int)
{
    m_stack->onTabInserted();
}

void Stack_qtwidgets::tabRemoved(int)
{
    m_stack->onTabRemoved();
}

void Stack_qtwidgets::setCurrentDockWidget(int index)
{
    setCurrentIndex(index);
}

bool Stack_qtwidgets::insertDockWidget(int index, Controllers::DockWidgetBase *dw,
                                       const QIcon &icon, const QString &title)
{
    insertTab(index, dw->view()->asQWidget(), icon, title);
    return true;
}

void Stack_qtwidgets::setTabBarAutoHide(bool b)
{
    QTabWidget::setTabBarAutoHide(b);
}

void Stack_qtwidgets::renameTab(int index, const QString &text)
{
    setTabText(index, text);
}

void Stack_qtwidgets::changeTabIcon(int index, const QIcon &icon)
{
    setTabIcon(index, icon);
}

Controllers::DockWidgetBase *Stack_qtwidgets::dockwidgetAt(int index) const
{
    auto view = qobject_cast<DockWidget_qtwidgets *>(widget(index));
    return view ? view->dockWidget() : nullptr;
}

int Stack_qtwidgets::currentIndex() const
{
    return QTabWidget::currentIndex();
}

void Stack_qtwidgets::setupTabBarButtons()
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
        QAction *action = menu.addAction(tabText(i), this, [this, i] {
            setCurrentIndex(i);
        });
        if (i == currentIndex())
            action->setDisabled(true);
    }
    menu.exec(mapToGlobal(pos));
}

QTabBar *Stack_qtwidgets::tabBar() const
{
    return static_cast<QTabBar *>(m_stack->tabBar()->view()->asQWidget());
}

Controllers::Stack *Stack_qtwidgets::stack() const
{
    return m_stack;
}
