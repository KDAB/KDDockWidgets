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
# include "../multisplitter/Widget_qwidget.h"
# include "private/widgets/QWidgetAdapter_widgets_p.h"
# include <QMainWindow>
  namespace KDDockWidgets {
    class MainWindow;
    class DockWidget;
  }

  typedef QWidget QWidgetOrQuick;
  typedef QMainWindow QMainWindowOrQuick;
  typedef Layouting::Widget_qwidget LayoutGuestWidgetBase;
  typedef KDDockWidgets::MainWindow MainWindowType;
  typedef KDDockWidgets::DockWidget DockWidgetType;
#else
# include "../multisplitter/Widget_quick.h"
# include "private/quick/QWidgetAdapter_quick_p.h"
  namespace KDDockWidgets {
    class MainWindowQuick;
    class DockWidgetQuick;
  }

  typedef KDDockWidgets::QWidgetAdapter QWidgetOrQuick;
  typedef QWidgetOrQuick QMainWindowOrQuick;
  typedef Layouting::Widget_quick LayoutGuestWidgetBase;
  typedef KDDockWidgets::MainWindowQuick MainWindowType;
  typedef KDDockWidgets::DockWidgetQuick DockWidgetType;
#endif

class LayoutGuestWidget : public KDDockWidgets::QWidgetAdapter
                        , public LayoutGuestWidgetBase
{
public:
    explicit LayoutGuestWidget(QWidgetOrQuick *parent)
        : QWidgetAdapter(parent)
        , LayoutGuestWidgetBase(this)
    {
    }
};

#endif
