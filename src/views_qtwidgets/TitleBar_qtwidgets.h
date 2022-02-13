/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_qtwidgets.h"
#include "controllers/FloatingWindow.h"

#include <QToolButton>

class QHBoxLayout;
class QLabel;

namespace KDDockWidgets::Controllers {
class TitleBar;
}

namespace KDDockWidgets::Views {

class DOCKS_EXPORT TitleBar_qtwidgets : public View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit TitleBar_qtwidgets(Controllers::TitleBar *controller, QWidget *parent = nullptr);

    // TODO:
    void updateMaximizeButton();
    void updateMinimizeButton();
    void updateAutoHideButton();

#ifdef DOCKS_DEVELOPER_MODE
    // The following are needed for the unit-tests
    bool isCloseButtonVisible() const;
    bool isCloseButtonEnabled() const;
    bool isFloatButtonVisible() const;
    bool isFloatButtonEnabled() const;
#endif

    Controllers::TitleBar *titleBar() const;

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
    QSize sizeHint() const override;
    void focusInEvent(QFocusEvent *) override;

private:
    friend class KDDockWidgets::Controllers::TitleBar;
    void init() override;
    int buttonAreaWidth() const;
    QRect iconRect() const;
    void updateMargins();

    Controllers::TitleBar *const m_controller;
    QHBoxLayout *const m_layout;
    QAbstractButton *m_closeButton = nullptr;
    QAbstractButton *m_floatButton = nullptr;
    QAbstractButton *m_maximizeButton = nullptr;
    QAbstractButton *m_minimizeButton = nullptr;
    QAbstractButton *m_autoHideButton = nullptr;
    QLabel *m_dockWidgetIcon = nullptr;
};

/// @brief Button widget to be used in the TitleBar.
/// These are the KDDockWidget default buttons. Users can replace with their own and are not
/// forced to use these.
class Button : public QToolButton
{
    Q_OBJECT
public:
    explicit Button(QWidget *parent)
        : QToolButton(parent)
    {
        setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    }

    ~Button() override;
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent *) override;
};

}
