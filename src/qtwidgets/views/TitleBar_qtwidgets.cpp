/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TitleBar_qtwidgets.h"

#include "kddockwidgets/controllers/TitleBar.h"
#include "kddockwidgets/controllers/FloatingWindow.h"

#include "private/Utils_p.h"
#include "private/Logging_p.h"
#include "kddockwidgets/ViewFactory.h"
#include "kddockwidgets/private/DockRegistry.h"
#include "qtwidgets/ViewFactory_qtwidgets.h"
#include "Window.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOptionDockWidget>
#include <QHBoxLayout>
#include <QLabel>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

Button::~Button()
{
}

void Button::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QStyleOptionToolButton opt;
    opt.initFrom(this);

    if (isEnabled() && underMouse()) {
        if (isDown()) {
            opt.state |= QStyle::State_Sunken;
        } else {
            opt.state |= QStyle::State_Raised;
        }
        style()->drawPrimitive(QStyle::PE_PanelButtonTool, &opt, &p, this);
    }

    opt.subControls = QStyle::SC_None;
    opt.features = QStyleOptionToolButton::None;
    opt.icon = icon();

    // The first icon size is for scaling 1x, and is what QStyle expects. QStyle will pick ones
    // with higher resolution automatically when needed.
    const QList<QSize> iconSizes = opt.icon.availableSizes();
    if (!iconSizes.isEmpty()) {
        opt.iconSize = iconSizes.constFirst();

        const qreal logicalFactor = logicalDpiX() / 96.0;

        // On Linux there's dozens of window managers and ways of setting the scaling.
        // Some window managers will just change the font dpi (which affects logical dpi), while
        // others will only change the device pixel ratio. Take care of both cases.
        // macOS is easier, as it never changes logical DPI.
        // On Windows, with AA_EnableHighDpiScaling, logical DPI is always 96 and physical is manipulated instead.
#if defined(Q_OS_LINUX)
        const qreal dpr = devicePixelRatioF();
        const qreal combinedFactor = logicalFactor * dpr;

        if (scalingFactorIsSupported(combinedFactor)) // Older Qt has rendering bugs with fractional factors
            opt.iconSize = opt.iconSize * combinedFactor;
#elif defined(Q_OS_WIN) && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        // Probably Windows could use the same code path as Linux, but I'm seeing too thick icons on Windows...
        if (!QGuiApplication::testAttribute(Qt::AA_EnableHighDpiScaling)
            && scalingFactorIsSupported(logicalFactor)) // Older Qt has rendering bugs with fractional factors
            opt.iconSize = opt.iconSize * logicalFactor;
#else
        Q_UNUSED(logicalFactor);
#endif
    }

    style()->drawComplexControl(QStyle::CC_ToolButton, &opt, &p, this);
}

QSize Button::sizeHint() const
{
    // Pass an opt so it scales against the logical dpi of the correct screen (since Qt 5.14) even if the HDPI Qt::AA_ attributes are off.
    QStyleOption opt;
    opt.initFrom(this);

    const int m = style()->pixelMetric(QStyle::PM_SmallIconSize, &opt, this);
    return QSize(m, m);
}

TitleBar_qtwidgets::TitleBar_qtwidgets(Controllers::TitleBar *controller, View *parent)
    : View_qtwidgets(controller, Type::TitleBar, View_qt::asQWidget(parent))
    , Views::TitleBarViewInterface(controller)
    , m_layout(new QHBoxLayout(this))
{
}

void TitleBar_qtwidgets::init()
{
    qCDebug(creation) << "TitleBarWidget" << this;
    if (m_titleBar->titleBarIsFocusable())
        setFocusPolicy(Qt::StrongFocus);

    m_dockWidgetIcon = new QLabel(this);
    m_layout->addWidget(m_dockWidgetIcon);

    m_layout->addStretch();
    updateMargins();

    auto factory = static_cast<ViewFactory_qtwidgets *>(Config::self().viewFactory());

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

    connect(m_floatButton, &QAbstractButton::clicked, m_titleBar, &Controllers::TitleBar::onFloatClicked);
    connect(m_closeButton, &QAbstractButton::clicked, m_titleBar, &Controllers::TitleBar::onCloseClicked);
    connect(m_maximizeButton, &QAbstractButton::clicked, m_titleBar, &Controllers::TitleBar::onMaximizeClicked);
    connect(m_minimizeButton, &QAbstractButton::clicked, m_titleBar, &Controllers::TitleBar::onMinimizeClicked);
    connect(m_autoHideButton, &QAbstractButton::clicked, m_titleBar, &Controllers::TitleBar::onAutoHideClicked);

    m_minimizeButton->setToolTip(tr("Minimize"));
    m_closeButton->setToolTip(tr("Close"));

    connect(m_titleBar, &Controllers::TitleBar::titleChanged, this, [this] {
        update();
    });

    connect(m_titleBar, &Controllers::TitleBar::iconChanged, this, [this] {
        if (m_titleBar->icon().isNull()) {
            m_dockWidgetIcon->setPixmap(QPixmap());
        } else {
            const QPixmap pix = m_titleBar->icon().pixmap(QSize(28, 28));
            m_dockWidgetIcon->setPixmap(pix);
        }
        update();
    });

    m_closeButton->setEnabled(m_titleBar->closeButtonEnabled());
    connect(m_titleBar, &Controllers::TitleBar::closeButtonEnabledChanged, m_closeButton, &QAbstractButton::setEnabled);

    connect(m_titleBar, &Controllers::TitleBar::floatButtonToolTipChanged, m_floatButton, &QWidget::setToolTip);
    connect(m_titleBar, &Controllers::TitleBar::floatButtonVisibleChanged, m_floatButton, &QWidget::setVisible);
    connect(m_titleBar, &Controllers::TitleBar::autoHideButtonChanged, this, &TitleBar_qtwidgets::updateAutoHideButton);
    connect(m_titleBar, &Controllers::TitleBar::minimizeButtonChanged, this, &TitleBar_qtwidgets::updateMinimizeButton);
    connect(m_titleBar, &Controllers::TitleBar::maximizeButtonChanged, this, &TitleBar_qtwidgets::updateMaximizeButton);

    m_floatButton->setVisible(m_titleBar->floatButtonVisible());
    m_floatButton->setToolTip(m_titleBar->floatButtonToolTip());

    connect(DockRegistry::self(), &DockRegistry::windowChangedScreen, this, [this](Window::Ptr w) {
        if (isInWindow(w))
            updateMargins();
    });
}

void TitleBar_qtwidgets::paintEvent(QPaintEvent *)
{
    if (freed())
        return;

    QPainter p(this);

    QStyleOptionDockWidget titleOpt;
    titleOpt.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &titleOpt, &p, this);
    titleOpt.title = m_titleBar->title();
    titleOpt.rect = iconRect().isEmpty() ? rect().adjusted(2, 0, -buttonAreaWidth(), 0)
                                         : rect().adjusted(iconRect().right(), 0, -buttonAreaWidth(), 0);

    if (m_titleBar->isMDI()) {
        const QColor c = palette().color(QPalette::Base);
        p.fillRect(rect().adjusted(1, 1, -1, 0), c);
    }

    style()->drawControl(QStyle::CE_DockWidgetTitle, &titleOpt, &p, this);
}

void TitleBar_qtwidgets::updateMinimizeButton(bool visible, bool enabled)
{
    m_minimizeButton->setEnabled(enabled);
    m_minimizeButton->setVisible(visible);
}

void TitleBar_qtwidgets::updateAutoHideButton(bool visible, bool enabled, TitleBarButtonType type)
{
    m_autoHideButton->setToolTip(type == TitleBarButtonType::AutoHide ? tr("Auto-hide")
                                                                      : tr("Disable auto-hide"));
    auto factory = Config::self().viewFactory();
    m_autoHideButton->setIcon(factory->iconForButtonType(type, devicePixelRatioF()));
    m_autoHideButton->setVisible(visible);
    m_autoHideButton->setEnabled(enabled);
}

void TitleBar_qtwidgets::updateMaximizeButton(bool visible, bool enabled, TitleBarButtonType type)
{
    m_maximizeButton->setEnabled(enabled);
    m_maximizeButton->setVisible(visible);
    if (visible) {
        auto factory = Config::self().viewFactory();
        m_maximizeButton->setIcon(factory->iconForButtonType(type, devicePixelRatioF()));
        m_maximizeButton->setToolTip(type == TitleBarButtonType::Normal ? tr("Restore") : tr("Maximize"));
    }
}

QRect TitleBar_qtwidgets::iconRect() const
{
    if (m_titleBar->icon().isNull()) {
        return QRect(0, 0, 0, 0);
    } else {
        return QRect(3, 3, 30, 30);
    }
}

int TitleBar_qtwidgets::buttonAreaWidth() const
{
    int smallestX = width();

    for (auto button : { m_autoHideButton, m_minimizeButton, m_floatButton, m_maximizeButton, m_closeButton }) {
        if (button->isVisible() && button->x() < smallestX)
            smallestX = button->x();
    }

    return width() - smallestX;
}

void TitleBar_qtwidgets::updateMargins()
{
    const qreal factor = logicalDpiFactor(this);
    m_layout->setContentsMargins(QMargins(2, 2, 2, 2) * factor);
    m_layout->setSpacing(int(2 * factor));
}

void TitleBar_qtwidgets::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (!m_titleBar)
        return;

    if (e->button() == Qt::LeftButton)
        m_titleBar->onDoubleClicked();
}

QSize TitleBar_qtwidgets::sizeHint() const
{
    // Pass an opt so it scales against the logical dpi of the correct screen (since Qt 5.14) even if the HDPI Qt::AA_ attributes are off.
    QStyleOption opt;
    opt.initFrom(this);

    const int height =
        style()->pixelMetric(QStyle::PM_HeaderDefaultSectionSizeVertical, &opt, this);

    return QSize(0, height);
}

void TitleBar_qtwidgets::focusInEvent(QFocusEvent *ev)
{
    if (!freed())
        return;

    QWidget::focusInEvent(ev);
    m_titleBar->focusInEvent(ev);
}

#ifdef DOCKS_DEVELOPER_MODE

bool TitleBar_qtwidgets::isCloseButtonVisible() const
{
    return m_closeButton->isVisible();
}

bool TitleBar_qtwidgets::isCloseButtonEnabled() const
{
    return m_closeButton->isEnabled();
}

bool TitleBar_qtwidgets::isFloatButtonVisible() const
{
    return m_floatButton->isVisible();
}

#endif
