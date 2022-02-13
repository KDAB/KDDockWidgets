/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TitleBar.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"
#include "View.h"
#include "views_qtwidgets/View_qtwidgets.h"
#include "views_qtwidgets/TitleBar_qtwidgets.h"
#include "private/WindowBeingDragged_p.h"
#include "private/Utils_p.h"
#include "private/Logging_p.h"

#include "controllers/FloatingWindow.h"
#include "controllers/TabBar.h"

#include "kddockwidgets/FrameworkWidgetFactory.h"
#include "kddockwidgets/private/MDILayoutWidget_p.h"
#include "kddockwidgets/MainWindowBase.h"

#include <QTimer>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;


TitleBar::TitleBar(Frame *parent)
    : Controller(Config::self().frameworkWidgetFactory()->createTitleBar(this, parent))
    , Draggable(view()->asQWidget()) // TODO
    , m_frame(parent)
    , m_floatingWindow(nullptr)
    , m_supportsAutoHide(Config::self().flags() & Config::Flag_AutoHideSupport)
{
    init();
    connect(m_frame, &Frame::numDockWidgetsChanged, this, &TitleBar::updateCloseButton);
    connect(m_frame, &Frame::isFocusedChanged, this, &TitleBar::isFocusedChanged);
    connect(m_frame, &Frame::isInMainWindowChanged, this, &TitleBar::updateAutoHideButton);
}

TitleBar::TitleBar(FloatingWindow *parent)
    : Controller(Config::self().frameworkWidgetFactory()->createTitleBar(this, parent))
    , Draggable(view()->asQWidget()) // TODO
    , m_frame(nullptr)
    , m_floatingWindow(parent)
    , m_supportsAutoHide(Config::self().flags() & Config::Flag_AutoHideSupport)
{
    init();
    connect(m_floatingWindow, &FloatingWindow::numFramesChanged, this, &TitleBar::updateButtons);
    connect(m_floatingWindow, &FloatingWindow::windowStateChanged, static_cast<Views::TitleBar_qtwidgets *>(view()), &Views::TitleBar_qtwidgets::updateMaximizeButton); // TODO
    connect(m_floatingWindow, &FloatingWindow::activatedChanged, this, &TitleBar::isFocusedChanged);
}

void TitleBar::init()
{
    qobject_cast<Views::TitleBar_qtwidgets *>(view()->asQWidget())->init(); // TODO
    view()->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed));

    connect(this, &TitleBar::isFocusedChanged, this, [this] {
        // repaint
        view()->update();
    });

    updateButtons();
    QTimer::singleShot(0, this, &TitleBar::updateAutoHideButton); // have to wait after the frame is
                                                                  // constructed
}

TitleBar::~TitleBar()
{
}

bool TitleBar::titleBarIsFocusable() const
{
    return Config::self().flags() & Config::Flag_TitleBarIsFocusable;
}


KDDockWidgets::MainWindowBase *TitleBar::mainWindow() const
{
    if (m_floatingWindow)
        return nullptr;

    if (m_frame)
        return m_frame->mainWindow();

    qWarning() << Q_FUNC_INFO << "null frame and null floating window";
    return nullptr;
}

bool TitleBar::isMDI() const
{
    QObject *p = view()->asQWidget();
    while (p) {
        if (qobject_cast<const QWindow *>(p)) {
            // Ignore QObject hierarchies spanning though multiple windows
            return false;
        }

        if (qobject_cast<MDILayoutWidget *>(p))
            return true;

        if (qobject_cast<DropArea *>(p)) {
            // Note that the TitleBar can be inside a DropArea that's inside a MDIArea
            // so we need this additional check
            return false;
        }

        p = p->parent();
    }

    return false;
}

QString TitleBar::title() const
{
    return m_title;
}

QIcon TitleBar::icon() const
{
    return m_icon;
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

bool TitleBar::floatButtonVisible() const
{
    return m_floatButtonVisible;
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

    if (DockWidgetBase *dw = singleDockWidget()) {
        // Don't show the dock/undock button if the window is not dockable
        if (dw->options() & DockWidgetBase::Option_NotDockable)
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
    return m_supportsAutoHide && m_frame && (m_frame->isInMainWindow() || m_frame->isOverlayed());
}

bool TitleBar::hasIcon() const
{
    return !m_icon.isNull();
}

Controllers::Frame *TitleBar::frame() const
{
    return m_frame;
}

Controllers::FloatingWindow *TitleBar::floatingWindow() const
{
    return m_floatingWindow;
}

void TitleBar::focusInEvent(QFocusEvent *ev)
{
    if (!m_frame || !(Config::self().flags() & Config::Flag_TitleBarIsFocusable))
        return;

    // For some reason QWidget::setFocusProxy() isn't working, so forward manually
    m_frame->FocusScope::focus(ev->reason());
}

void TitleBar::updateButtons()
{
    updateCloseButton();
    updateFloatButton();
    updateMaximizeButton();
    updateMinimizeButton();
    updateAutoHideButton();
}

void TitleBar::updateCloseButton()
{

    const bool anyNonClosable = frame() ? frame()->anyNonClosable()
                                        : (floatingWindow() ? floatingWindow()->anyNonClosable()
                                                            : false);

    setCloseButtonEnabled(!anyNonClosable);
}

void TitleBar::toggleMaximized()
{
    if (!m_floatingWindow)
        return;

    if (m_floatingWindow->isMaximizedOverride())
        m_floatingWindow->showNormal();
    else
        m_floatingWindow->showMaximized();
}

bool TitleBar::isOverlayed() const
{
    return m_frame && m_frame->isOverlayed();
}

void TitleBar::setCloseButtonEnabled(bool enabled)
{
    if (enabled != m_closeButtonEnabled) {
        m_closeButtonEnabled = enabled;
        Q_EMIT closeButtonEnabledChanged(enabled);
    }
}

void TitleBar::setFloatButtonVisible(bool visible)
{
    if (visible != m_floatButtonVisible) {
        m_floatButtonVisible = visible;
        Q_EMIT floatButtonVisibleChanged(visible);
    }
}

void TitleBar::setFloatButtonToolTip(const QString &tip)
{
    if (tip != m_floatButtonToolTip) {
        m_floatButtonToolTip = tip;
        Q_EMIT floatButtonToolTipChanged(tip);
    }
}

void TitleBar::setTitle(const QString &title)
{
    if (title != m_title) {
        m_title = title;
        view()->update();
        Q_EMIT titleChanged();
    }
}

void TitleBar::setIcon(const QIcon &icon)
{
    m_icon = icon;
    Q_EMIT iconChanged();
}

void TitleBar::onCloseClicked()
{
    const bool closeOnlyCurrentTab = Config::self().flags() & Config::Flag_CloseOnlyCurrentTab;

    if (m_frame) {
        if (closeOnlyCurrentTab) {
            if (auto dw = m_frame->currentDockWidget()) {
                dw->view()->close();
            } else {
                // Doesn't happen
                qWarning() << Q_FUNC_INFO << "Frame with no dock widgets";
            }
        } else {
            if (m_frame->isTheOnlyFrame() && !m_frame->isInMainWindow()) {
                m_frame->view()->closeWindow();
            } else {
                m_frame->view()->close();
            }
        }
    } else if (m_floatingWindow) {

        if (closeOnlyCurrentTab) {
            if (Frame *f = m_floatingWindow->singleFrame()) {
                if (DockWidgetBase *dw = f->currentDockWidget()) {
                    dw->view()->close();
                } else {
                    // Doesn't happen
                    qWarning() << Q_FUNC_INFO << "Frame with no dock widgets";
                }
            } else {
                m_floatingWindow->view()->close();
            }
        } else {
            m_floatingWindow->view()->close();
        }
    }
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

    if (KDDockWidgets::usesUtilityWindows()) {
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

bool TitleBar::closeButtonEnabled() const
{
    return m_closeButtonEnabled;
}

std::unique_ptr<KDDockWidgets::WindowBeingDragged> TitleBar::makeWindow()
{
    if (!isVisible() && view()->asQWidget()->QWidget::window()->isVisible() && !(Config::self().flags() & Config::Flag_ShowButtonsOnTabBarIfTitleBarHidden)) {

        // When using Flag_ShowButtonsOnTabBarIfTitleBarHidden we forward the call from the tab bar's
        // buttons to the title bar's buttons, just to reuse logic

        qWarning() << "TitleBar::makeWindow shouldn't be called on invisible title bar"
                   << this << view()->asQWidget()->QWidget::window()->isVisible();
        if (m_frame) {
            qWarning() << "this=" << this << "; actual=" << m_frame->actualTitleBar();
        } else if (m_floatingWindow) {
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

    if (FloatingWindow *fw = floatingWindow()) { // Already floating
        if (m_frame->isTheOnlyFrame()) { // We don't detach. This one drags the entire window instead.
            qCDebug(hovering) << "TitleBar::makeWindow no detach needed";
            return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(fw, this));
        }
    }

    QRect r = m_frame->view()->geometry();
    r.moveTopLeft(m_frame->mapToGlobal(QPoint(0, 0)));

    auto floatingWindow = new Controllers::FloatingWindow(m_frame, {});
    floatingWindow->setSuggestedGeometry(r, SuggestedGeometryHint_GeometryIsFromDocked);
    floatingWindow->view()->show();

    auto draggable = KDDockWidgets::usesNativeTitleBar() ? static_cast<Draggable *>(floatingWindow)
                                                         : static_cast<Draggable *>(this);
    return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(floatingWindow, draggable));
}

bool TitleBar::isWindow() const
{
    return m_floatingWindow != nullptr;
}

Controllers::DockWidgetBase::List TitleBar::dockWidgets() const
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

Controllers::DockWidgetBase *TitleBar::singleDockWidget() const
{
    const DockWidgetBase::List dockWidgets = this->dockWidgets();
    return dockWidgets.isEmpty() ? nullptr : dockWidgets.first();
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

bool TitleBar::isFocused() const
{
    if (m_frame)
        return m_frame->isFocused();
    else if (m_floatingWindow)
        return m_floatingWindow->view()->isActiveWindow();

    return false;
}

void TitleBar::updateFloatButton()
{
    setFloatButtonToolTip(floatingWindow() ? tr("Dock window") : tr("Undock window"));
    setFloatButtonVisible(supportsFloatingButton());
}

QString TitleBar::floatButtonToolTip() const
{
    return m_floatButtonToolTip;
}
