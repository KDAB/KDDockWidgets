/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

    m_maximizeButton = TitleBarWidget::createButton(this, TitleBarButtonType::Maximize);
    m_minimizeButton = TitleBarWidget::createButton(this, TitleBarButtonType::Minimize);
    m_floatButton = TitleBarWidget::createButton(this, TitleBarButtonType::Float);
    m_closeButton = TitleBarWidget::createButton(this, TitleBarButtonType::Close);
    m_autoHideButton = TitleBarWidget::createButton(this, TitleBarButtonType::AutoHide);

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

    updateCloseButton();
    updateFloatButton();
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

void TitleBarWidget::updateFloatButton()
{
    m_floatButton->setToolTip(floatingWindow()? tr("Dock window") : tr("Undock window"));
    m_floatButton->setVisible(supportsFloatingButton());
}

void TitleBarWidget::updateCloseButton()
{
    const bool anyNonClosable = frame() ? frame()->anyNonClosable()
                                        : (floatingWindow() ? floatingWindow()->anyNonClosable()
                                                            : false);

    qCDebug(closebutton) << Q_FUNC_INFO << "enabled=" << !anyNonClosable;
    m_closeButton->setEnabled(!anyNonClosable);
}

void TitleBarWidget::updateMinimizeButton()
{
    m_minimizeButton->setVisible(supportsMinimizeButton());
}

QIcon TitleBarWidget::iconForButtonType(TitleBarButtonType type) const
{
    const QString iconName = iconNameForButtonType(type);
    if (iconName.isEmpty())
        return {};

    QIcon icon(QStringLiteral(":/img/%1.png").arg(iconName));

#if QT_VERSION < QT_VERSION_CHECK(5, 15, 2)
    const bool isFractional = (1.0 * devicePixelRatio() != devicePixelRatioF());
    if (isFractional) {
        // We don't support 1.5x yet.
        // Linux is the only one affected as Windows and macOS use integral factors.
        // Problem with Linux is that rendering is off due to a rounding bug only fixed in 5.15.2
        // Will enable for fractional later.
        // QTBUG-86170
        return icon;
    }
#else
    // Not using Qt's sugar syntax, which doesn't support 1.5x anyway when we need it.
    // Simply add the high-res files and Qt will pick them when needed

    icon.addFile(QStringLiteral(":/img/%1-1.5x.png").arg(iconName));
#endif
    icon.addFile(QStringLiteral(":/img/%1-2x.png").arg(iconName));

    return icon;
}

QString TitleBarWidget::iconNameForButtonType(TitleBar::TitleBarButtonType type) const
{
    switch (type) {
    case TitleBarButtonType::AutoHide:
        return QStringLiteral("auto-hide");
    case TitleBarButtonType::UnautoHide:
        return QStringLiteral("unauto-hide");
    case TitleBarButtonType::Close:
        return QStringLiteral("close");
    case TitleBarButtonType::Minimize:
        return QStringLiteral("min");
    case TitleBarButtonType::Maximize:
        return QStringLiteral("max");
    case TitleBarButtonType::Float:
        return QStringLiteral("dock-float");
    }

    qWarning() << Q_FUNC_INFO << "Unknown icon type";
    return QString();
}

void TitleBarWidget::updateAutoHideButton()
{
    if (Config::self().flags() & Config::Flag_AutoHideSupport) {
        if (const Frame *f = frame()) {
            if (f->isInMainWindow()) {
                QIcon icon(QStringLiteral(":/img/auto-hide.png"));
                m_autoHideButton->setIcon(iconForButtonType(TitleBarButtonType::AutoHide));
                m_autoHideButton->setToolTip(tr("Auto-hide"));
            } else if (f->isOverlayed()) {
                m_autoHideButton->setIcon(iconForButtonType(TitleBarButtonType::UnautoHide));
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
        m_maximizeButton->setIcon(fw->isMaximized() ? iconForButtonType(TitleBarButtonType::Float)
                                                    : iconForButtonType(TitleBarButtonType::Maximize));

        m_maximizeButton->setVisible(supportsMaximizeButton());
        m_maximizeButton->setToolTip(fw->isMaximized() ? tr("Restore") : tr("Maximize"));
    } else {
        m_maximizeButton->setVisible(false);
    }
}

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

QAbstractButton *TitleBarWidget::createButton(QWidget *parent, TitleBarButtonType type)
{
    auto button = new Button(parent);
    button->setIcon(iconForButtonType(type));
    return button;
}
