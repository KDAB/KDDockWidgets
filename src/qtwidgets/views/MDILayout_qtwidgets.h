/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"

#include "qtwidgets/views/View_qtwidgets.h"

namespace KDDockWidgets {

namespace Core {
class MDILayout;
}

namespace qtwidgets {

class DOCKS_EXPORT MDILayout : public qtwidgets::View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit MDILayout(Core::MDILayout *controller, View *parent);
    ~MDILayout();

private:
    Core::MDILayout *const m_controller;
};

}
}
