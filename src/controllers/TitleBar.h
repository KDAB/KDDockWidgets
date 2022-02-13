/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

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

namespace KDDockWidgets {

namespace Views {
class FloatingWindow_qtwidgets;
}

}

namespace KDDockWidgets::Controllers {

class Frame;
class FloatingWindow;

class DOCKS_EXPORT TitleBar : public Controller, public Draggable
{
    Q_OBJECT
public:
    explicit TitleBar(Frame *parent);
    explicit TitleBar(FloatingWindow *parent);
    virtual ~TitleBar() override;

    /// From Draggable interface
    bool isMDI() const override;
    std::unique_ptr<WindowBeingDragged> makeWindow() override;
    bool isWindow() const override;
    Controllers::DockWidgetBase *singleDockWidget() const override;

    void setTitle(const QString &title);
    QString title() const;

    ///@brief Returns true if the dock widget which has this title bar is floating
    bool isFloating() const;

    ///@brief the list of dockwidgets under this TitleBar.
    /// There should always be at least 1. If more than 1 then they are tabbed.
    DockWidgetBase::List dockWidgets() const;

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

    ///@brief returns whether this title bar has an icon
    bool hasIcon() const;

    ///@brief returns whether any of the DockWidgets this TitleBar controls has a child focus
    /// Not to be confused with QWidget::hasFocus(), which just refers to 1 widget. This works more
    /// like QtQuick's FocusScope
    bool isFocused() const;

    bool titleBarIsFocusable() const;

    ///@brief getter for m_frame
    Controllers::Frame *frame() const;

    ///@brief getter for m_floatingWindow
    FloatingWindow *floatingWindow() const;

    ///@brief If this title bar belongs to a dock widget docked into the main window, returns the main window
    /// Returns nullptr otherwise
    MainWindowBase *mainWindow() const;

    // slots:
    bool onDoubleClicked();
    void focusInEvent(QFocusEvent *);

    /// @brief updates the close button enabled state
    void updateButtons();

    Q_INVOKABLE void onCloseClicked();
    Q_INVOKABLE void onFloatClicked();
    QString floatButtonToolTip() const;
    Q_INVOKABLE void onMaximizeClicked();
    Q_INVOKABLE void onMinimizeClicked();
    Q_INVOKABLE void onAutoHideClicked();
    Q_INVOKABLE void toggleMaximized();

    bool closeButtonEnabled() const;
    bool floatButtonVisible() const;

Q_SIGNALS:
    void titleChanged();
    void iconChanged();
    void isFocusedChanged();
    void closeButtonEnabledChanged(bool);
    void floatButtonVisibleChanged(bool);
    void floatButtonToolTipChanged(const QString &);

protected:
    virtual void updateMaximizeButton()
    {
    }
    virtual void updateMinimizeButton()
    {
    }
    virtual void updateAutoHideButton()
    {
    }

    bool isOverlayed() const;

private:
    friend class ::TestDocks;
    friend class Views::FloatingWindow_qtwidgets;

    void updateFloatButton();
    void updateCloseButton();
    void setCloseButtonEnabled(bool);
    void setFloatButtonVisible(bool);
    void setFloatButtonToolTip(const QString &);
    void init();

    QPoint m_pressPos;
    QString m_title;
    QIcon m_icon;

    Controllers::Frame *const m_frame;
    FloatingWindow *const m_floatingWindow;
    const bool m_supportsAutoHide;
    bool m_closeButtonEnabled = true;
    bool m_floatButtonVisible = true;
    QString m_floatButtonToolTip;
};

}
