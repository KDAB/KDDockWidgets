/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TitleBarWidget_p.h"
#include "DragController_p.h"
#include "Frame_p.h"
#include "FloatingWindow_p.h"
#include "Logging_p.h"
#include "WindowBeingDragged_p.h"
#include "FrameworkWidgetFactory.h"
#include "Utils_p.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>

using namespace KDDockWidgets;

Button::~Button() {}

TitleBarWidget::TitleBarWidget(Frame *parent)
    : TitleBar(parent)
    , m_layout(new QHBoxLayout(this))
{
    init();
}

TitleBarWidget::TitleBarWidget(FloatingWindow *parent)
    : TitleBar(parent)
    , m_layout(new QHBoxLayout(this))
{
    init();
}

void TitleBarWidget::init()
{
    qCDebug(creation) << "TitleBarWidget" << this;
    m_dockWidgetIcon = new QLabel(this);
    m_layout->addWidget(m_dockWidgetIcon);

    m_layout->addStretch();
    m_layout->setContentsMargins(2, 2, 2, 2);
    m_layout->setSpacing(2);

    auto factory = Config::self().frameworkWidgetFactory();

    m_maximizeButton = factory->createTitleBarButton(this, TitleBarButtonType::Maximize);
    m_minimizeButton = factory->createTitleBarButton(this, TitleBarButtonType::Minimize);
    m_floatButton = factory->createTitleBarButton(this, TitleBarButtonType::Float);
    m_closeButton = factory->createTitleBarButton(this, TitleBarButtonType::Close);
    m_autoHideButton = factory->createTitleBarButton(this, TitleBarButtonType::AutoHide);

    m_layout->addWidget(m_autoHideButton);
    m_layout->addWidget(m_minimizeButton);
    m_layout->addWidget(m_maximizeButton);
    m_layout->addWidget(m_floatButton);
    m_layout->addWidget(m_closeButton);

    m_autoHideButton->setVisible(false);

    connect(m_floatButton, &QAbstractButton::clicked, this, &TitleBarWidget::onFloatClicked);
    connect(m_closeButton, &QAbstractButton::clicked, this, &TitleBarWidget::onCloseClicked);
    connect(m_maximizeButton, &QAbstractButton::clicked, this, &TitleBarWidget::onMaximizeClicked);
    connect(m_minimizeButton, &QAbstractButton::clicked, this, &TitleBarWidget::onMinimizeClicked);
    connect(m_autoHideButton, &QAbstractButton::clicked, this, &TitleBarWidget::onAutoHideClicked);

    updateMaximizeButton();
    updateMinimizeButton();

    m_minimizeButton->setToolTip(tr("Minimize"));
    m_closeButton->setToolTip(tr("Close"));

    connect(this, &TitleBar::titleChanged, this, [this] {
        update();
    });

    connect(this, &TitleBar::iconChanged, this, [this] {
        if (icon().isNull()) {
            m_dockWidgetIcon->setPixmap(QPixmap());
        } else {
            const QPixmap pix = icon().pixmap(QSize(28,28));
            m_dockWidgetIcon->setPixmap(pix);
        }
        update();
    });

    m_closeButton->setEnabled(closeButtonEnabled());
    connect(this, &TitleBar::closeButtonEnabledChanged, m_closeButton, &QAbstractButton::setEnabled);

    connect(this, &TitleBar::floatButtonToolTipChanged, m_floatButton, &QWidget::setToolTip);
    connect(this, &TitleBar::floatButtonVisibleChanged, m_floatButton, &QWidget::setVisible);
    m_floatButton->setVisible(floatButtonVisible());
    m_floatButton->setToolTip(floatButtonToolTip());
}

QRect TitleBarWidget::iconRect() const
{
    if (icon().isNull()) {
        return QRect(0,0, 0,0);
    } else {
        return QRect(3, 3, 30, 30);
    }
}

int TitleBarWidget::buttonAreaWidth() const
{
    int smallestX = width();

    for (auto button : { m_autoHideButton, m_minimizeButton, m_floatButton, m_maximizeButton, m_closeButton }) {
        if (button->isVisible() && button->x() < smallestX)
            smallestX = button->x();
    }

    return width() - smallestX;
}

TitleBarWidget::~TitleBarWidget()
{
    // To avoid a crash
    for (auto button : { m_autoHideButton, m_minimizeButton, m_floatButton, m_maximizeButton, m_closeButton }) {
        button->setParent(nullptr);
        button->deleteLater();
    }
}

void TitleBarWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        onDoubleClicked();
}

QWidget *TitleBarWidget::closeButton() const
{
    return m_closeButton;
}

void TitleBarWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    QStyleOptionDockWidget titleOpt;
    titleOpt.title = title();
    titleOpt.rect = iconRect().isEmpty() ? rect().adjusted(2, 0, -buttonAreaWidth(), 0)
                                         : rect().adjusted(iconRect().right(), 0, -buttonAreaWidth(), 0);

    style()->drawControl(QStyle::CE_DockWidgetTitle, &titleOpt, &p, this);
}

void TitleBarWidget::updateMinimizeButton()
{
    m_minimizeButton->setVisible(supportsMinimizeButton());
}

void TitleBarWidget::updateAutoHideButton()
{
    if (Config::self().flags() & Config::Flag_AutoHideSupport) {
        auto factory = Config::self().frameworkWidgetFactory();
        if (const Frame *f = frame()) {
            if (f->isInMainWindow()) {
                m_autoHideButton->setIcon(factory->iconForButtonType(TitleBarButtonType::AutoHide, devicePixelRatioF()));
                m_autoHideButton->setToolTip(tr("Auto-hide"));
            } else if (f->isOverlayed()) {
                m_autoHideButton->setIcon(factory->iconForButtonType(TitleBarButtonType::UnautoHide, devicePixelRatioF()));
                m_autoHideButton->setToolTip(tr("Disable auto-hide"));
            }

            m_autoHideButton->setVisible(true);
        } else {
            m_autoHideButton->setVisible(false);
        }
    } else {
        m_autoHideButton->setVisible(false);
    }
}

void TitleBarWidget::updateMaximizeButton()
{
    if (auto fw = floatingWindow()) {
        auto factory = Config::self().frameworkWidgetFactory();
        const TitleBarButtonType iconType = fw->isMaximized() ? TitleBarButtonType::Normal
                                                              : TitleBarButtonType::Maximize;
        m_maximizeButton->setIcon(factory->iconForButtonType(iconType, devicePixelRatioF()));

        m_maximizeButton->setVisible(supportsMaximizeButton());
        m_maximizeButton->setToolTip(fw->isMaximized() ? tr("Restore") : tr("Maximize"));
    } else {
        m_maximizeButton->setVisible(false);
    }
}

#ifdef DOCKS_DEVELOPER_MODE

bool TitleBarWidget::isCloseButtonVisible() const
{
    return m_closeButton->isVisible();
}

bool TitleBarWidget::isCloseButtonEnabled() const
{
    return m_closeButton->isEnabled();
}

bool TitleBarWidget::isFloatButtonVisible() const
{
    return m_floatButton->isVisible();
}

bool TitleBarWidget::isFloatButtonEnabled() const
{
    return m_floatButton->isEnabled();
}

#endif
