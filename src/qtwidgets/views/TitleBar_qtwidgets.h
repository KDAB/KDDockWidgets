/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_qtwidgets.h"
#include "kddockwidgets/views/TitleBarViewInterface.h"

#include <QToolButton>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QLabel;
QT_END_NAMESPACE

namespace KDDockWidgets::Views {

class DOCKS_EXPORT TitleBar_qtwidgets : public View_qtwidgets<QWidget>, public Views::TitleBarViewInterface
{
    Q_OBJECT
public:
    explicit TitleBar_qtwidgets(Controllers::TitleBar *controller, View *parent = nullptr);

#ifdef DOCKS_DEVELOPER_MODE
    // The following are needed for the unit-tests
    bool isCloseButtonVisible() const override;
    bool isCloseButtonEnabled() const override;
    bool isFloatButtonVisible() const override;
#endif

protected:
    void init() override;
    void paintEvent(QPaintEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
    QSize sizeHint() const override;
    void focusInEvent(QFocusEvent *) override;

    friend class KDDockWidgets::Controllers::TitleBar;
    int buttonAreaWidth() const;
    QRect iconRect() const;
    void updateMargins();

    void updateMaximizeButton(bool visible, bool enabled, TitleBarButtonType);
    void updateAutoHideButton(bool visible, bool enabled, TitleBarButtonType);
    void updateMinimizeButton(bool visible, bool enabled);

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

protected:
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent *) override;
};

}
