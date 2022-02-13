/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_qtwidgets.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

namespace KDDockWidgets::Controllers {
class FloatingWindow;
class Frame;
}

namespace KDDockWidgets::Views {


class DOCKS_EXPORT FloatingWindow_qtwidgets : public View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit FloatingWindow_qtwidgets(Controllers::FloatingWindow *controller,
                                      MainWindowBase *parent = nullptr,
                                      Qt::WindowFlags windowFlags = {});

    Controllers::FloatingWindow *floatingWindow() const;

protected:
    void paintEvent(QPaintEvent *) override;
    void closeEvent(QCloseEvent *) override;
    bool event(QEvent *ev) override;
    void init() override;

private:
    Controllers::FloatingWindow *const m_controller;
    QVBoxLayout *const m_vlayout;
    QMetaObject::Connection m_screenChangedConnection;

    void updateMargins();
    Q_DISABLE_COPY(FloatingWindow_qtwidgets)
};
}