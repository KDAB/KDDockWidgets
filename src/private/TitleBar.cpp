/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TitleBar_p.h"
#include "Frame_p.h"
#include "FloatingWindow_p.h"
#include "Logging_p.h"
#include "WindowBeingDragged_p.h"
#include "Utils_p.h"
#include "FrameworkWidgetFactory.h"
#include "Config.h"
#include "MainWindowBase.h"

#include <QTimer>
#include <QWindowStateChangeEvent>

using namespace KDDockWidgets;

TitleBar::TitleBar(Frame *parent)
    : QWidgetAdapter(parent)
    , Draggable(this)
    , m_frame(parent)
    , m_floatingWindow(nullptr)
    , m_supportsAutoHide(Config::self().flags() & Config::Flag_internal_AutoHideSupport)
{
    connect(m_frame, &Frame::numDockWidgetsChanged, this, &TitleBar::updateCloseButton);
    connect(m_frame, &Frame::isFocusedChanged, this, &TitleBar::isFocusedChanged);
    connect(m_frame, &Frame::isInMainWindowChanged, this, &TitleBar::updateAutoHideButton);

    init();

    if (Config::self().flags() & Config::Flag_TitleBarIsFocusable)
        setFocusPolicy(Qt::StrongFocus);

    QTimer::singleShot(0, this, &TitleBar::updateAutoHideButton); // have to wait after the frame is constructed
    updateAutoHideButton();
}

TitleBar::TitleBar(FloatingWindow *parent)
    : QWidgetAdapter(parent)
    , Draggable(this)
    , m_frame(nullptr)
    , m_floatingWindow(parent)
    , m_supportsAutoHide(Config::self().flags() & Config::Flag_internal_AutoHideSupport)
{
    connect(m_floatingWindow, &FloatingWindow::numFramesChanged, this, &TitleBar::updateCloseButton);
    connect(m_floatingWindow, &FloatingWindow::numFramesChanged, this, &TitleBar::updateFloatButton);
    connect(m_floatingWindow, &FloatingWindow::numFramesChanged, this, &TitleBar::updateMaximizeButton);
    connect(m_floatingWindow, &FloatingWindow::numFramesChanged, this, &TitleBar::updateMinimizeButton);
    connect(m_floatingWindow, &FloatingWindow::windowStateChanged, this, &TitleBar::updateMaximizeButton);
    connect(m_floatingWindow, &FloatingWindow::activatedChanged , this, &TitleBar::isFocusedChanged);
    init();
    updateAutoHideButton(); // always hidden when we're in a FloatingWindow.
}

void TitleBar::init()
{
    qCDebug(creation) << "TitleBar" << this;
    setFixedHeight(30);
    connect(this, &TitleBar::isFocusedChanged, this, [this] {
        // repaint
        update();
    });
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

void TitleBar::focusInEvent(QFocusEvent *ev)
{
    QWidgetAdapter::focusInEvent(ev);

    if (!m_frame || !(Config::self().flags() & Config::Flag_TitleBarIsFocusable))
        return;

    // For some reason QWidget::setFocusProxy() isn't working, so forward manually
    m_frame->FocusScope::focus(ev->reason());
}

bool TitleBar::isOverlayed() const
{
    return m_frame && m_frame->isOverlayed();
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

    QRect r = m_frame->QWidgetAdapter::geometry();
    qCDebug(hovering) << "TitleBar::makeWindow original geometry" << r;
    r.moveTopLeft(m_frame->mapToGlobal(QPoint(0, 0))); // TODO: Remove static_cast if it compiles. Ambiguous base for now

    auto floatingWindow = Config::self().frameworkWidgetFactory()->createFloatingWindow(m_frame);
    floatingWindow->setSuggestedGeometry(r);
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

    if (Config::self().flags() & Config::Flag_TitleBarNoFloatButton) {
        // Was explicitly disabled
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

bool TitleBar::supportsMinimizeButton() const
{
    if ((Config::self().flags() & Config::Flag_TitleBarHasMinimizeButton) != Config::Flag_TitleBarHasMinimizeButton) // this specific flag is not base^2
        return false;

    return m_floatingWindow != nullptr;
}

bool TitleBar::supportsAutoHideButton() const
{
    // Only dock widgets docked into the MainWindow can minimize
    return m_supportsAutoHide && m_frame && m_frame->isInMainWindow();
}

bool TitleBar::hasIcon() const
{
    return !m_icon.isNull();
}

bool TitleBar::isFocused() const
{
    if (m_frame)
        return m_frame->isFocused();
    else if (m_floatingWindow)
        return m_floatingWindow->isActiveWindow();

    return false;
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

void TitleBar::onMinimizeClicked()
{
    if (!m_floatingWindow)
        return;

    if (!(Config::self().flags() & Config::Flag_DontUseUtilityFloatingWindows)) {
        // Qt::Tool windows don't appear in the task bar.
        // Unless someone tells me a good reason to allow this situation.
        return;
    }

    m_floatingWindow->showMinimized();
}

void TitleBar::onAutoHideClicked()
{
    if (!m_frame) {
        // Doesn't happen
        qWarning() << Q_FUNC_INFO << "Minimize not supported on floating windows";
        return;
    }

    const auto &dockwidgets = m_frame->dockWidgets();
    for (DockWidgetBase *dw : dockwidgets) {
        if (dw->isOverlayed()) {
            // restore
            MainWindowBase *mainWindow = dw->mainWindow();
            mainWindow->restoreFromSideBar(dw);
        } else {
            dw->moveToSideBar();
        }
    }
}
