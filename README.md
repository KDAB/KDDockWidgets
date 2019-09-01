KDDockWidgets
==============
`KDDockWidgets` is a KDAB effort to provide an advanced docking system for Qt.

Throughout the years KDAB has contributed and funded bug fixes and features to `QDockWidget`.
Sadly, the `QDockWidget` code is in such a state that each bug fix took many days
and sometimes caused regressions. The codebase mixes GUI code, with logic, with state
in a spaghetti manner, which makes it very hard to move forward with new features.

In hindsight, what led to `QDockWidget` complexity is that is supports a multitude
of options and a exponential number of option combinations, times 3 platforms. From
talking with our customers we gathered that none of them cared about most of those options,
and all of them wanted the same 3 or 4 missing features.

This framework is under active development and has no planned release date yet.

![Screen capture](/screencap.gif?raw=true "The docking system in action")

Goals
=====
- Provide advanced docking that QDockWidgets doesn't support:
  - nesting dock widgets in a floating window and docking that group back to main window
  - docking to any main window, not only to the parent main window
  - docking to center of main window, or simply removing the concept of "central widget"
  - main window supporting detachable tabs in center widget
  - different forms of docking indicators (through plugins)
  - detaching arbitrary tabs from a tab bar into a dock area
  - QtQuick support
  - Exposing inner helper widgets so the user can customize them or provide his own

- Clean codebase
  - Not mixing GUI with state with logic with animations
  - Unit-test everything, even the GUI and DnD operations

Licensing
=========
KDDockWidgets is (C) 2018-2019, Klarälvdalens Datakonsult AB, and is available
under the terms of the GPLv2 (see LICENSE.GPL.txt).

Contact KDAB at <info@kdab.com> if you need different licensing options.

About KDAB
==========
KDDockWidgets is supported and maintained by Klarälvdalens Datakonsult AB (KDAB).

The KDAB Group is the global No.1 software consultancy for Qt, C++ and
OpenGL applications across desktop, embedded and mobile platforms.

The KDAB Group provides consulting and mentoring for developing Qt applications
from scratch and in porting from all popular and legacy frameworks to Qt.
We continue to help develop parts of Qt and are one of the major contributors
to the Qt Project. We can give advanced or standard trainings anywhere
around the globe on Qt as well as C++, OpenGL, 3D and more.

Please visit http://www.kdab.com to meet the people who write code like this.
