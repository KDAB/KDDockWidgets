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
  - nesting in any main window
  - docking to center of main window
  - main window supporting detachable tabs in center widget
  - different forms of docking indicators (through plugins)
  - detaching arbitrary tabs from a tab bar into a dock area

- Discard unneeded features present in QDockWidgets that make the code complicated

- Clean codebase
  - Not mixing GUI with state with logic with animations
  - Unit-test everything, even the GUI and DnD operations


Licensing
=========

This software is provided as GPLv2 (See LICENSE.GPL.txt) or, alternatively,
contact KDAB at <info@kdab.com> if you need different licensing.
