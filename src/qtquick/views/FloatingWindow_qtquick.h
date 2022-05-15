/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_FLOATING_WINDOWQUICK_P_H
#define KD_FLOATING_WINDOWQUICK_P_H

#include "View_qtquick.h"

class QQuickView;

namespace KDDockWidgets {

namespace Controllers {
class FloatingWindow;
}

namespace Views {

class MainWindow_qtquick;

class DOCKS_EXPORT FloatingWindow_qtquick : public Views::View_qtquick
{
    Q_OBJECT
public:
    explicit FloatingWindow_qtquick(Controllers::FloatingWindow *controller, Views::MainWindow_qtquick *parent = nullptr);
    ~FloatingWindow_qtquick();

    QSize minSize() const override;

protected:
    void setGeometry(QRect) override;

private:
    int contentsMargins() const;
    int titleBarHeight() const;
    QWindow *candidateParentWindow() const;
    void init() override;
    QQuickView *const m_quickWindow;
    QQuickItem *m_visualItem = nullptr;
    Controllers::FloatingWindow *const m_controller;
    Q_DISABLE_COPY(FloatingWindow_qtquick)
};

}

}

#endif
