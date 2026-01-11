---
applyTo: '**'
---

1. Converting from core/ types to Qt types
1.1 Converting core::Window to QWindow
  - #include "qtcommon/Window_p.h"
  - #include <QWindow>
  - static_cast to QtCommon::Window*, which then has a `qtWindow()` method

1.2 Converting from core::View to QQuickItem
  - #include "qtquick/views/View.h"
  - #include <QQuickItem>
  - QQuickItem *item = KDDockWidgets::QtQuick::asQQuickItem(view.get());

2. Debugging
  - When adding temporary logging statements you can use qDebug() instead of KDDW_LOG macros
  - #include <QDebug>
