/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_qtwidgets.h"
#include "views/GroupViewInterface.h"

namespace KDDockWidgets::Controllers {
class Group;
}

namespace KDDockWidgets::Views {

class DOCKS_EXPORT Group_qtwidgets : public View_qtwidgets<QWidget>, public GroupViewInterface
{
    Q_OBJECT
public:
    explicit Group_qtwidgets(Controllers::Group *controller, QWidget *parent = nullptr);
    void init() override;

    int nonContentsHeight() const override;
    QRect dragRect() const override;

protected:
    void free_impl() override;
    void paintEvent(QPaintEvent *) override;
    QSize maxSizeHint() const override;
};

}
