KDDockWidgets
==============
`KDDockWidgets` is a KDAB effort to provide an advanced docking system for Qt.

Throughout the years KDAB contributed and funded bug fixes and features to `QDockWidget`.
Sadly, this was very painful. Each bug fix or feature took many days of implementation,
and an equal number of days just to fix dozens of regressions.

`QDockWidget` mixes GUI code with logic with state, making it very hard
to move forward with new features. Furthermore, our customers were getting more
creative with their requests, so it was clear we needed a better docking framework.


Features
========
- Provide advanced docking that QDockWidgets doesn't support:
  - Nesting dock widgets in a floating window and docking that group back to main window
  - Docking to any main window, not only to the parent main window
  - Docking to center of main window, or simply removing the concept of "central widget"
  - Main window supporting detachable tabs in center widget
  - Detaching arbitrary tabs from a tab bar into a dock area
  - Exposing inner helper widgets so the user can customize them or provide his own
    - Customize tab widgets
    - Customize title bars
    - Customize window frames

- Clean codebase
  - Not mixing GUI with state with logic with animations
  - Unit-test everything, even the GUI and DnD operations (140 tests currently)
  - Fuzzer for doing random testing

![Screen capture](/screencap.gif?raw=true "The docking system in action")

Roadmap:
========
  - Different forms of docking indicators (through plugins)
  - QtQuick support

Licensing
=========
KDDockWidgets is (C) 2018-2019, Klarälvdalens Datakonsult AB, and is available
under the terms of the GPLv2 (see LICENSE.GPL.txt).

Contact KDAB at <info@kdab.com> if you need different licensing options.

Get Involved
============
KDAB will happily accept external contributions; however, **all**
contributions will require a signed Contributor License Agreement
(see docs/KDDockWidgets-CopyrightAssignmentForm.docx).

Contact info@kdab.com for more information.

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
