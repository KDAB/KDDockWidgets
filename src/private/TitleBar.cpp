/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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
#include "Utils_p.h"
#include "FrameworkWidgetFactory.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>

using namespace KDDockWidgets;

TitleBar::TitleBar(Frame *parent)
    : QWidgetAdapter(parent)
    , Draggable(this)
    , m_frame(parent)
    , m_floatingWindow(nullptr)
{
    connect(m_frame, &Frame::numDockWidgetsChanged, this, &TitleBar::updateCloseButton);
    init();
}

TitleBar::TitleBar(FloatingWindow *parent)
    : QWidgetAdapter(parent)
    , Draggable(this)
    , m_frame(nullptr)
    , m_floatingWindow(parent)
{
    connect(m_floatingWindow, &FloatingWindow::numFramesChanged, this, &TitleBar::updateCloseButton);
    connect(m_floatingWindow, &FloatingWindow::numFramesChanged, this, &TitleBar::updateFloatButton);
    connect(m_floatingWindow, &FloatingWindow::numFramesChanged, this, &TitleBar::updateMaximizeButton);
    connect(m_floatingWindow, &FloatingWindow::windowStateChanged, this, &TitleBar::updateMaximizeButton);
    init();
}

void TitleBar::init()
{
    qCDebug(creation) << "TitleBar" << this;
    setFixedHeight(30);
}

TitleBar::~TitleBar()
{
}

bool TitleBar::onDoubleClicked()
{
    if ((Config::self().flags() & Config::Flag_DoubleClickMaximizes) && m_floatingWindow) {
        // Not using isFloating(), as that can be a dock widget nested in a floating window. By convention it's floating, but it's not the title bar of the top-level window.
        toggleMaximized();
        return true;
    } else if (supportsFloatingButton()) {
        onFloatClicked();
        return true;
    }

    return false;
}

void TitleBar::toggleMaximized()
{
    if (!m_floatingWindow)
        return;

    if (m_floatingWindow->isMaximized())
        m_floatingWindow->showNormal();
    else
        m_floatingWindow->showMaximized();
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
    Q_EMIT iconChanged();
}

std::unique_ptr<WindowBeingDragged> TitleBar::makeWindow()
{
    if (!isVisible() && window()->isVisible()) {
        qWarning() << "TitleBar::makeWindow shouldn't be called on invisible title bar"
                   << this << window()->isVisible() << parentWidget();

        if (m_floatingWindow) {
            qWarning() << "Has floating window with titlebar=" << m_floatingWindow->titleBar()
                       << "; fw->isVisible=" << m_floatingWindow->isVisible();
        }

        Q_ASSERT(false);
        return {};
    }

    if (m_floatingWindow) {
        // We're already a floating window, no detach needed
        return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(m_floatingWindow, this));
    }

    qCDebug(hovering) << "TitleBar::makeWindow: isFloating=" << floatingWindow() << "; isTheOnlyFrame=" << m_frame->isTheOnlyFrame() << "; frame=" << m_frame;
    if (FloatingWindow *fw = QWidgetAdapter::floatingWindow()) { // Already floating
        if (m_frame->isTheOnlyFrame()) { // We dont' detach. This one drags the entire window instead.
            qCDebug(hovering) << "TitleBar::makeWindow no detach needed";
            return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(fw, this));
        }
    }

    QRect r = m_frame->QWidget::geometry();
    qCDebug(hovering) << "TitleBar::makeWindow original geometry" << r;
    r.moveTopLeft(m_frame->mapToGlobal(QPoint(0, 0)));

    auto floatingWindow = Config::self().frameworkWidgetFactory()->createFloatingWindow(m_frame);
    floatingWindow->setGeometry(r);
    floatingWindow->show();
    qCDebug(hovering) << "TitleBar::makeWindow setting geometry" << r << "actual=" << floatingWindow->geometry();

    auto draggable = KDDockWidgets::usesNativeTitleBar() ? static_cast<Draggable*>(floatingWindow)
                                                         : static_cast<Draggable*>(this);
    return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(floatingWindow, draggable));
}

DockWidgetBase *TitleBar::singleDockWidget() const
{
    const DockWidgetBase::List dockWidgets = this->dockWidgets();
    return dockWidgets.isEmpty() ? nullptr : dockWidgets.first();
}

bool TitleBar::supportsFloatingButton() const
{
    if (Config::self().flags() & Config::Flag_TitleBarHasMaximizeButton) {
        // Apps having a maximize/restore button traditionally don't have a floating one,
        // QDockWidget style only has floating and no maximize/restore.
        // We can add an option later if we need them to co-exist
        return false;
    }

    // If we have a floating window with nested dock widgets we can't re-attach, because we don't
    // know where to
    return !m_floatingWindow || m_floatingWindow->hasSingleFrame();
}

bool TitleBar::supportsMaximizeButton() const
{
    if (!(Config::self().flags() & Config::Flag_TitleBarHasMaximizeButton))
        return false;

    return m_floatingWindow != nullptr;
}

bool TitleBar::hasIcon() const
{
    return !m_icon.isNull();
}

QIcon TitleBar::icon() const
{
    return m_icon;
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

    if (m_floatingWindow)
        m_floatingWindow->close();
}

bool TitleBar::isFloating() const
{

    if (m_floatingWindow)
        return m_floatingWindow->hasSingleDockWidget(); // Debatable! Maybe it's always floating.

    if (m_frame)
        return m_frame->isFloating();

    qWarning() << "TitleBar::isFloating: shouldn't happen";
    return false;
}

DockWidgetBase::List TitleBar::dockWidgets() const
{
    if (m_floatingWindow) {
        DockWidgetBase::List result;
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
    const DockWidgetBase::List dockWidgets = this->dockWidgets();
    if (isFloating()) {
        // Let's dock it

        if (dockWidgets.isEmpty()) {
            qWarning() << "TitleBar::onFloatClicked: empty list. Shouldn't happen";
            return;
        }

        if (dockWidgets.size() == 1) {
            // Case 1: Single dockwidget floating
            dockWidgets[0]->setFloating(false);
        } else {
            // Case 2: Multiple dockwidgets are tabbed together and floating
            // TODO: Just reuse the whole frame and put it back. The frame currently doesn't remember the position in the main window
            // so use an hack for now
            for (auto dock : qAsConst(dockWidgets)) {
                dock->setFloating(true);
                dock->setFloating(false);
            }
        }
    } else {
        // Let's float it
        if (dockWidgets.size() == 1) {
            // If there's a single dock widget, just call DockWidget::setFloating(true). The only difference
            // is that it has logic for using the last used geometry for the floating window
            dockWidgets[0]->setFloating(true);
        } else {
            makeWindow();
        }
    }
}

void TitleBar::onMaximizeClicked()
{
    toggleMaximized();
}
