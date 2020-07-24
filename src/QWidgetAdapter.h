/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_QWIDGETADAPTER_H
#define KDDOCKWIDGETS_QWIDGETADAPTER_H

#if !defined(KDDOCKWIDGETS_QTWIDGETS) && !defined(KDDOCKWIDGETS_QTQUICK)
# define KDDOCKWIDGETS_QTWIDGETS
#endif

/**
 * @file
 * @brief Abstraction for supporting both QtWidgets and QtQuick.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifdef KDDOCKWIDGETS_QTWIDGETS
# include "private/widgets/QWidgetAdapter_widgets_p.h"
#include <QMainWindow>
typedef QWidget QWidgetOrQuick;
typedef QMainWindow QMainWindowOrQuick;
#else
# include "quick/QWidgetAdapter_quick_p.h"
typedef KDDockWidgets::QWidgetAdapter QWidgetOrQuick;
typedef QWidgetOrQuick QMainWindowOrQuick;
#endif

#endif
