/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_DOCKWIDGET_BASE_P_H
#define KD_DOCKWIDGET_BASE_P_H

#include "DockWidget.h"
#include "DockRegistry.h"
#include "private/Position_p.h"
#include "ViewWrapper.h"
#include "Action.h"
#include "private/View_p.h"

#include <QCoreApplication>
#include <QString>
#include <QSize>
#include <QIcon>


namespace KDDockWidgets {

namespace Controllers {
class SideBar;

class DOCKS_EXPORT_FOR_UNIT_TESTS DockWidget::Private : public QObject /// clazy:exclude=missing-qobject-macro
{
public:
    /// RAII class to help updating actions exactly once, otherwise they can be triggered in the middle
    /// of operations during reparenting
    struct UpdateActions
    {
        explicit UpdateActions(Controllers::DockWidget *dock)
            : dw(dock)
        {
            dw->d->m_willUpdateActions = true;
        }

        ~UpdateActions()
        {
            dw->d->m_willUpdateActions = false;
            dw->d->updateFloatAction();
        }

    private:
        Q_DISABLE_COPY(UpdateActions)
        Controllers::DockWidget *const dw;
    };

    Private(const QString &dockName, DockWidgetOptions options_,
            LayoutSaverOptions layoutSaverOptions_, DockWidget *qq);

    void init()
    {
        updateTitle();
        q->view()->d->closeRequested.connect([this](QCloseEvent *ev) {
            onCloseEvent(ev);
        });
    }

    /**
     * @brief returns the FloatingWindow this dock widget is in. If nullptr then it's in a
     * MainWindow.
     *
     * Note: Being in a FloatingWindow doesn't necessarily mean @ref isFloating() returns true, as
     * the dock widget might be in a floating window with other dock widgets side by side.
     */
    Controllers::FloatingWindow *floatingWindow() const
    {
        if (auto fw = q->view()->rootView()->asFloatingWindowController())
            return fw;

        return nullptr;
    }

    MainWindow *mainWindow() const
    {
        if (q->view()->isRootView())
            return nullptr;

        // Note: Don't simply use window(), as the MainWindow might be embedded into something else
        auto p = q->view()->parentView();
        while (p) {
            if (auto mw = p->asMainWindowController())
                return mw;

            if (p->isRootView())
                return nullptr;

            p = p->parentView();
        }

        return nullptr;
    }

    Controllers::SideBar *sideBar() const
    {
        return DockRegistry::self()->sideBarForDockWidget(q);
    }

    ///@brief adds the current layout item containing this dock widget
    void addPlaceholderItem(Layouting::Item *);

    ///@brief returns the last position, just for tests.
    Position::Ptr &lastPosition();

    void forceClose();
    QPoint defaultCenterPosForFloating();

    bool eventFilter(QObject *watched, QEvent *event) override;

    void updateTitle();
    void toggle(bool enabled);
    void updateToggleAction();
    void updateFloatAction();
    void onDockWidgetShown();
    void onDockWidgetHidden();
    void close();
    bool restoreToPreviousPosition();
    void maybeRestoreToPreviousPosition();
    int currentTabIndex() const;
    void onCloseEvent(QCloseEvent *e);

    /**
     * @brief Serializes this dock widget into an intermediate form
     */
    std::shared_ptr<LayoutSaver::DockWidget> serialize() const;

    /**
     * @brief the Group which contains this dock widgets.
     *
     * A group wraps a docked DockWidget, giving it a TabWidget so it can accept other dock widgets.
     * Frame is also the actual class that goes into a LayoutWidget.
     *
     * It's nullptr immediately after creation.
     */
    Controllers::Group *group() const;

    ///@brief If this dock widget is floating, then it saves its geometry
    void saveLastFloatingGeometry();

    /**
     * Before floating a dock widget we save its position. So it can be restored when calling
     * DockWidget::setFloating(false)
     */
    void saveTabIndex();

    /**
     * @brief Creates a FloatingWindow and adds itself into it
     * @return the created FloatingWindow
     */
    Controllers::FloatingWindow *morphIntoFloatingWindow();

    /// @brief calls morphIntoFloatingWindow() if the dock widget is visible and is a top-level
    /// This is called delayed whenever we show a floating dock widget, so we get a FloatingWindow
    void maybeMorphIntoFloatingWindow();

    /// @brief Returns the mdi layout this dock widget is in, if any.
    MDILayout *mdiLayout() const;

    /// @brief Returns if this is an helper DockWidget created automatically to host a drop area inside MDI
    /// This is only used by the DockWidget::Option_MDINestable feature
    bool isMDIWrapper() const;

    /// @brief If this dock widget is an MDI wrapper (isMDIWrapper()), then returns the wrapper drop area
    DropArea *mdiDropAreaWrapper() const;

    /// @brief If this dock widget is inside a drop area nested in MDI then returns the wrapper dock widget
    /// This goes up the hierarchy, while mdiDropAreaWrapper goes down.
    DockWidget *mdiDockWidgetWrapper() const;

    const QString name;
    QStringList affinities;
    QString title;
    QIcon titleBarIcon;
    QIcon tabBarIcon;
    std::shared_ptr<ViewWrapper> guest;
    DockWidget *const q;
    DockWidgetOptions options;
    const LayoutSaverOptions layoutSaverOptions;
    QAction *const toggleAction;
    QAction *const floatAction;
    Position::Ptr m_lastPosition = std::make_shared<Position>();
    bool m_isPersistentCentralDockWidget = false;
    bool m_processingToggleAction = false;
    bool m_updatingToggleAction = false;
    bool m_updatingFloatAction = false;
    bool m_isForceClosing = false;
    bool m_isMovingToSideBar = false;
    QSize m_lastOverlayedSize = QSize(0, 0);
    int m_userType = 0;
    bool m_willUpdateActions = false;
};

}

}

#endif
