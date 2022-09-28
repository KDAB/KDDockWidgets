/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "../Controller.h"
#include "../private/Draggable_p.h"
#include "kddockwidgets/docks_export.h"
#include "DockWidget.h"

#include <QString>
#include <QIcon>

namespace KDDockWidgets::Controllers {

class Group;
class FloatingWindow;
class TabBar;

class DOCKS_EXPORT TitleBar : public Controller, public Draggable
{
    Q_OBJECT
public:
    explicit TitleBar(Group *parent);
    explicit TitleBar(FloatingWindow *parent);
    virtual ~TitleBar() override;

    /// From Draggable interface
    bool isMDI() const override;
    std::unique_ptr<WindowBeingDragged> makeWindow() override;
    bool isWindow() const override;
    Controllers::DockWidget *singleDockWidget() const override;

    void setTitle(const QString &title);
    QString title() const;

    ///@brief Returns true if this title-bar is the title bar of a floating window
    bool isFloating() const;

    ///@brief the list of dockwidgets under this TitleBar.
    /// There should always be at least 1. If more than 1 then they are tabbed.
    DockWidget::List dockWidgets() const;

    ///@brief the icon
    QIcon icon() const;
    void setIcon(const QIcon &icon);

    ///@brief returns whether this title bar supports a floating/docking button
    bool supportsFloatingButton() const;

    ///@brief returns whether this title bar supports a maximize/restore button
    bool supportsMaximizeButton() const;

    ///@brief returns whether this title bar supports a minimize button
    bool supportsMinimizeButton() const;

    ///@brief returns whether this title bar supports the auto-hide button
    bool supportsAutoHideButton() const;

    /// @brief returns whether the float button is visible
    bool isFloatButtonVisible() const;
    bool isCloseButtonVisible() const;
    bool isCloseButtonEnabled() const;

    ///@brief returns whether this title bar has an icon
    bool hasIcon() const;

    ///@brief returns whether any of the DockWidgets this TitleBar controls has a child focus
    /// Not to be confused with QWidget::hasFocus(), which just refers to 1 widget. This works more
    /// like QtQuick's FocusScope
    bool isFocused() const;

    bool titleBarIsFocusable() const;

    ///@brief getter for m_group
    Controllers::Group *group() const;

    ///@brief getter for m_floatingWindow
    FloatingWindow *floatingWindow() const;

    ///@brief If this title bar belongs to a dock widget docked into the main window, returns the
    /// main window
    /// Returns nullptr otherwise
    MainWindow *mainWindow() const;

    ///@brief Returns the tab bar which is under this title bar.
    /// It's only nullptr for the case of having a Floating Window with more than one nested Frame
    TabBar *tabBar() const;

    void focusInEvent(QFocusEvent *);

    /// @brief updates the close button enabled state
    void updateButtons();
    QString floatButtonToolTip() const;

    bool onDoubleClicked();
    void onCloseClicked();
    void onFloatClicked();
    void onMaximizeClicked();
    void onMinimizeClicked();
    void onAutoHideClicked();
    void toggleMaximized();

    bool closeButtonEnabled() const;
    bool floatButtonVisible() const;
    void setCloseButtonEnabled(bool);
    void setFloatButtonVisible(bool);

Q_SIGNALS:
    void titleChanged();
    void iconChanged();
    void isFocusedChanged();
    void closeButtonEnabledChanged(bool);
    void floatButtonVisibleChanged(bool);
    void floatButtonToolTipChanged(const QString &);
    void numDockWidgetsChanged();

    /// @brief Emitted to tell the views to update their auto-hide button
    void autoHideButtonChanged(bool visible, bool enabled, TitleBarButtonType);

    /// @brief Emitted to tell the views to update their minimize button
    void minimizeButtonChanged(bool visible, bool enabled);

    /// @brief Emitted to tell the views to update their maximize button
    void maximizeButtonChanged(bool visible, bool enabled, TitleBarButtonType);

protected:
    bool isOverlayed() const;

private:
    friend class ::TestDocks;

    void updateAutoHideButton();
    void updateMaximizeButton();

    void updateFloatButton();
    void updateCloseButton();
    void setFloatButtonToolTip(const QString &);
    void init();

    QPoint m_pressPos;
    QString m_title;
    QIcon m_icon;

    Controllers::Group *const m_group;
    FloatingWindow *const m_floatingWindow;
    const bool m_supportsAutoHide;
    bool m_closeButtonEnabled = true;
    bool m_floatButtonVisible = true;
    QString m_floatButtonToolTip;
};

}
