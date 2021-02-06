/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_DOCKWIDGET_BASE_P_H
#define KD_DOCKWIDGET_BASE_P_H

#include "DockWidgetBase.h"
#include "SideBar_p.h"
#include "DockRegistry_p.h"
#include "Position_p.h"
#include "FloatingWindow_p.h"

#include <QCoreApplication>
#include <QString>
#include <QSize>

namespace KDDockWidgets {

class DockWidgetBase::Private : public QObject
{
public:
    Private(const QString &dockName, DockWidgetBase::Options options_,
            LayoutSaverOptions layoutSaverOptions_, DockWidgetBase *qq)
        : name(dockName)
        , title(dockName)
        , q(qq)
        , options(options_)
        , layoutSaverOptions(layoutSaverOptions_)
        , toggleAction(new QAction(q))
        , floatAction(new QAction(q))
    {
        q->connect(toggleAction, &QAction::toggled, q, [this] (bool enabled) {
            if (!m_updatingToggleAction) { // guard against recursiveness
                toggleAction->blockSignals(true); // and don't emit spurious toggle. Like when a dock widget is inserted into a tab widget it might get hide events, ignore those. The Dock Widget is open.
                m_processingToggleAction = true;
                toggle(enabled);
                toggleAction->blockSignals(false);
                m_processingToggleAction = false;
            }
        });

        q->connect(floatAction, &QAction::toggled, q, [this] (bool checked) {
            if (!m_updatingFloatAction) { // guard against recursiveness
                q->setFloating(checked);
            }

            Q_EMIT q->isFloatingChanged(checked);

            // When floating, we remove from the sidebar
            if (checked && q->isOpen()) {
                if (SideBar *sb = DockRegistry::self()->sideBarForDockWidget(q)) {
                    sb->mainWindow()->clearSideBarOverlay(/* deleteFrame=*/false);
                    sb->removeDockWidget(q);
                }
            }
        });

        toggleAction->setCheckable(true);
        floatAction->setCheckable(true);

        qApp->installEventFilter(this);
    }

    void init()
    {
        updateTitle();
    }

    /**
     * @brief returns the FloatingWindow this dock widget is in. If nullptr then it's in a
     * MainWindow.
     *
     * Note: Being in a FloatingWindow doesn't necessarily mean @ref isFloating() returns true, as
     * the dock widget might be in a floating window with other dock widgets side by side.
     */
    FloatingWindow *floatingWindow() const
    {
        return qobject_cast<FloatingWindow*>(q->window());
    }

    MainWindowBase *mainWindow() const
    {
        if (q->isWindow())
            return nullptr;

        // Note: Don't simply use window(), as the MainWindow might be embedded into something else
        QWidgetOrQuick *p = q->parentWidget();
        while (p) {
            if (auto window = qobject_cast<MainWindowBase*>(p))
                return window;

            if (p->isWindow())
                return nullptr;

            p = p->parentWidget();
        }

        return nullptr;
    }

    SideBar* sideBar() const
    {
        return DockRegistry::self()->sideBarForDockWidget(q);
    }

    ///@brief adds the current layout item containing this dock widget
    void addPlaceholderItem(Layouting::Item *);

    ///@brief returns the last position, just for tests.
    LastPositions &lastPositions();

    void forceClose();
    QPoint defaultCenterPosForFloating();

    bool eventFilter(QObject *watched, QEvent *event) override;

    void updateTitle();
    void toggle(bool enabled);
    void updateToggleAction();
    void updateFloatAction();
    void onDockWidgetShown();
    void onDockWidgetHidden();
    void show();
    void close();
    bool restoreToPreviousPosition();
    void maybeRestoreToPreviousPosition();
    int currentTabIndex() const;

    /**
     * @brief Serializes this dock widget into an intermediate form
     */
    std::shared_ptr<LayoutSaver::DockWidget> serialize() const;

    /**
     * @brief the Frame which contains this dock widgets.
     *
     * A frame wraps a docked DockWidget, giving it a TabWidget so it can accept other dock widgets.
     * Frame is also the actual class that goes into a MultiSplitter.
     *
     * It's nullptr immediately after creation.
     */
    Frame *frame() const;

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
    KDDockWidgets::FloatingWindow *morphIntoFloatingWindow();

    /// @brief calls morphIntoFloatingWindow() if the dock widget is visible and is a top-level
    /// This is called delayed whenever we show a floating dock widget, so we get a FloatingWindow
    void maybeMorphIntoFloatingWindow();

    const QString name;
    QStringList affinities;
    QString title;
    QIcon titleBarIcon;
    QIcon tabBarIcon;
    QWidgetOrQuick *widget = nullptr;
    DockWidgetBase *const q;
    DockWidgetBase::Options options;
    const LayoutSaverOptions layoutSaverOptions;
    QAction *const toggleAction;
    QAction *const floatAction;
    LastPositions m_lastPositions;
    bool m_processingToggleAction = false;
    bool m_updatingToggleAction = false;
    bool m_updatingFloatAction = false;
    bool m_isForceClosing = false;
    bool m_isMovingToSideBar = false;
    QSize m_lastOverlayedSize = QSize(0, 0);
};

}

#endif
