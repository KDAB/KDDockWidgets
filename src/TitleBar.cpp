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

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>

using namespace KDDockWidgets;

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
    connect(m_floatingWindow, &FloatingWindow::numFramesChanged, this, &TitleBar::updateFloatButton);
    init();
}

void TitleBar::init()
{
    qCDebug(creation) << "TitleBar" << this;
    setFixedHeight(30);
    m_dockWidgetIcon = new QLabel(this);
    m_layout->addWidget(m_dockWidgetIcon);

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

int TitleBar::iconAreaWidth() const
{
    if (m_icon.isNull()) {
        return 0;
    } else {
        return 30;
    }
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

void TitleBar::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && supportsFloatingButton()) {
        Q_EMIT onFloatClicked();
    } else {
        QWidget::mouseDoubleClickEvent(e);
    }
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
        Q_EMIT titleChanged();
    }
}

void TitleBar::setIcon(const QIcon &icon)
{
    m_icon = icon;
    if (!m_icon.isNull()) {
        const QPixmap pix = m_icon.pixmap(QSize(28,28));
        m_dockWidgetIcon->setPixmap(pix);
    } else {
        m_dockWidgetIcon->setPixmap(QPixmap());
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
    titleOpt.rect = rect().adjusted(iconAreaWidth(), 0, -buttonAreaWidth(), 0);

    style()->drawControl(QStyle::CE_DockWidgetTitle, &titleOpt, &p, this);
}

void TitleBar::updateFloatButton()
{
    m_floatButton->setVisible(supportsFloatingButton());
}

bool TitleBar::supportsFloatingButton() const
{
    // If we have a floating window with nested dock widgets we can't re-attach, because we don't
    // know where to
    return !m_floatingWindow || m_floatingWindow->hasSingleFrame();
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
        if (m_frame->isTheOnlyFrame() && !m_frame->isInMainWindow()) {
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

bool TitleBar::isFloating() const
{
    if (m_dockWidget)
        return m_dockWidget->isFloating();

    if (m_floatingWindow)
        return m_floatingWindow->hasSingleDockWidget(); // Debatable! Maybe it's always floating.

    if (m_frame)
        return m_frame->isFloating();

    qWarning() << "TitleBar::isFloating: shouldn't happen";
    return false;
}

DockWidget::List TitleBar::dockWidgets() const
{
    if (m_dockWidget)
        return { m_dockWidget };

    if (m_floatingWindow) {
        DockWidget::List result;
        for (Frame *f : m_floatingWindow->frames()) {
            result << f->dockWidgets();
        }
        return result;
    }

    if (m_frame)
        return m_frame->dockWidgets();

     qWarning() << "TitleBar::dockWidget: shouldn't happen";
     return {};
}

void TitleBar::onFloatClicked()
{
    if (isFloating()) {
        DockWidget::List dockWidgets = this->dockWidgets();
        if (dockWidgets.isEmpty()) {
            qWarning() << "TitleBar::onFloatClicked: empty list. Shouldn't happen";
            return;
        }

        if (dockWidgets.size() == 1) {
            // Case 1: Single dockwidget floating
            dockWidgets[0]->setFloating(false);
        } else {
            // Case 2: Multiple dockwidgets are tabbed toghether and floating
            // TODO: Just reuse the whole frame and put it back. The frame currently doesn't remember the position in the main window
            // so use an hack for now
            for (auto dock : dockWidgets) {
                dock->setFloating(true);
                dock->setFloating(false);
            }
        }
    } else {
        makeWindow();
    }
}
