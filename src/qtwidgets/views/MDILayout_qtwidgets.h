/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"

#include "qtwidgets/views/View_qtwidgets.h"

namespace KDDockWidgets {

namespace Controllers {
class MDILayout;
}

namespace Views {

class DOCKS_EXPORT MDILayout_qtwidgets : public Views::View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit MDILayout_qtwidgets(Controllers::MDILayout *controller, View *parent);
    ~MDILayout_qtwidgets();

private:
    Controllers::MDILayout *const m_controller;
};

}
}
