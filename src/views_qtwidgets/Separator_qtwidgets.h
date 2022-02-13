/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_qtwidgets.h"
#include "kddockwidgets/Qt5Qt6Compat_p.h"
#include <qwidget.h>


namespace KDDockWidgets::Controllers {
class Separator;
}

namespace KDDockWidgets::Views {

class DOCKS_EXPORT Separator_qtwidgets : public View_qtwidgets<QWidget>
{
public:
    explicit Separator_qtwidgets(Controllers::Separator *controller, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void enterEvent(KDDockWidgets::Qt5Qt6Compat::QEnterEvent *) override;
    void leaveEvent(QEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;

private:
    Controllers::Separator *const m_controller;
};

}
