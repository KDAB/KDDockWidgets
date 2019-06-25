/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "TitleBar_p.h"
#include "DragController_p.h"
#include "Frame_p.h"
#include "FloatingWindow_p.h"
#include "Logging_p.h"
#include "WindowBeingDragged_p.h"

#include <QPainter>
#include <QToolButton>
#include <QHBoxLayout>
#include <QStyle>
#include <QStyleOptionFrame>

using namespace KDDockWidgets;

namespace KDDockWidgets {

class Button : public QToolButton
{
    Q_OBJECT
public:
    explicit Button(QWidget *parent)
        : QToolButton(parent)
    {
        //const int margin = style()->pixelMetric(QStyle::PM_DockWidgetTitleBarButtonMargin, nullptr, this) * 2;
        QSize sz = /*QSize(margin, margin) + */ QSize(16, 16);
        setFixedSize(sz);
    }

    ~Button() override;

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        QStyleOptionToolButton opt;
        opt.init(this);

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
        opt.iconSize = size();
        style()->drawComplexControl(QStyle::CC_ToolButton, &opt, &p, this);
    }
};
}

Button::~Button() {}

TitleBar::TitleBar(DockWidget *dockwidget)
    : QWidget(dockwidget)
    , Draggable(this)
    , m_layout(new QHBoxLayout(this))
    , m_dockWidget(dockwidget)
    , m_frame(nullptr)
    , m_floatingWindow(nullptr)
{
    init();
}

TitleBar::TitleBar(Frame *parent)
    : QWidget(parent)
    , Draggable(this)
    , m_layout(new QHBoxLayout(this))
    , m_dockWidget(nullptr)
    , m_frame(parent)
    , m_floatingWindow(nullptr)
{
    connect(m_frame, &Frame::numDockWidgetsChanged, this, &TitleBar::updateCloseButton);
    init();
}

TitleBar::TitleBar(FloatingWindow *parent)
    : QWidget(parent)
    , Draggable(this)
    , m_layout(new QHBoxLayout(this))
    , m_dockWidget(nullptr)
    , m_frame(nullptr)
    , m_floatingWindow(parent)
{
    connect(m_floatingWindow, &FloatingWindow::numFramesChanged, this, &TitleBar::updateCloseButton);
    init();
}

void TitleBar::init()
{
    qCDebug(creation) << "TitleBar" << this;
    setFixedHeight(30);
    m_layout->addStretch();
    m_layout->setContentsMargins(0, 2, 2, 2);
    m_layout->setSpacing(2);

    m_closeButton = new Button(this);
    m_floatButton = new Button(this);
    m_floatButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarNormalButton));
    m_closeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    m_layout->addWidget(m_floatButton);
    m_layout->addWidget(m_closeButton);

    connect(m_floatButton, &QAbstractButton::clicked, this, &TitleBar::onFloatClicked);
    connect(m_closeButton, &QAbstractButton::clicked, this, &TitleBar::onCloseClicked);

    updateCloseButton();
}

int TitleBar::buttonAreaWidth() const
{
    if (m_floatButton->isVisible())
        return width() - m_floatButton->x();
    else
        return width() - m_closeButton->x();
}

TitleBar::~TitleBar()
{
}

void TitleBar::setTitle(const QString &title)
{
    if (title != m_title) {
        m_title = title;
        qCDebug(::title) << Q_FUNC_INFO << "\n    title=" << title
                         << "\n    this=" << this
                         << "\n    parentWidget=" << parentWidget()
                         << "\n    isVisible=" << isVisible()
                         << "\nwindow=" << window();
        update();
    }
}

std::unique_ptr<WindowBeingDragged> TitleBar::makeWindow()
{
    if (!isVisible()) {
        qWarning() << "TitleBar::makeWindow shouldn't be called on invisible title bar"
                   << this;

        if (m_floatingWindow) {
            qWarning() << "Has floating window with titlebar=" << m_floatingWindow->titleBar()
                       << "; and actual titleBar=" << m_floatingWindow->actualTitleBar()
                       << "; fw->isVisible=" << m_floatingWindow->isVisible();
        }

        Q_ASSERT(false);
        return {};
    }

    if (m_floatingWindow) {
        // We're already a floating window, no detach needed
        return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(m_floatingWindow));
    }

    if (m_dockWidget) {
        // It's a dock widget that wasn't transformed into FloatingWindow yet
        qCDebug(hovering) << "TitleBar::makeWindow: Returning unmorphed DockWidget";
        return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(m_dockWidget));
    }

    qCDebug(hovering) << "TitleBar::makeWindow: isFloating=" << isFloatingWindow() << "; isTheOnlyFrame=" << m_frame->isTheOnlyFrame() << "; frame=" << m_frame;
    if (FloatingWindow *fw = isFloatingWindow()) { // Already floating
        if (m_frame->isTheOnlyFrame()) { // We dont' detach. This one drags the entire window instead.
            qCDebug(hovering) << "TitleBar::makeWindow no detach needed";
            return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(fw));
        }
    }

    QRect r = m_frame->geometry();
    qCDebug(hovering) << "TitleBar::makeWindow original geometry" << r;
    r.moveTopLeft(m_frame->mapToGlobal(QPoint(0, 0)));

    auto floatingWindow = new FloatingWindow(m_frame);
    floatingWindow->setGeometry(r);
    floatingWindow->show();
    qCDebug(hovering) << "TitleBar::makeWindow setting geometry" << r << "actual=" << floatingWindow->geometry();

    return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(floatingWindow));
}

QWidget *TitleBar::closeButton() const
{
    return m_closeButton;
}

void TitleBar::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    QStyleOptionDockWidget titleOpt;
    titleOpt.title = m_title;
    titleOpt.rect = rect().adjusted(0, 0, -buttonAreaWidth(), 0);

    style()->drawControl(QStyle::CE_DockWidgetTitle, &titleOpt, &p, this);
}

void TitleBar::updateCloseButton()
{
    const bool anyNonClosable = m_frame ? m_frame->anyNonClosable()
                                        : (m_dockWidget ? bool(m_dockWidget->options() & DockWidget::Option_NotClosable)
                                                        : (m_floatingWindow ? m_floatingWindow->anyNonClosable()
                                                                            : false));

    qCDebug(closebutton) << Q_FUNC_INFO << "enabled=" << !anyNonClosable;
    m_closeButton->setEnabled(!anyNonClosable);
}

void TitleBar::onCloseClicked()
{
    if (m_frame) {
        if (m_frame->isTheOnlyFrame()) {
            m_frame->window()->close();
        } else {
            m_frame->close();
        }
    }

    if (m_dockWidget)
        m_dockWidget->close();

    if (m_floatingWindow)
        m_floatingWindow->close();
}

void TitleBar::onFloatClicked()
{
    makeWindow();
}

#include "TitleBar.moc"
