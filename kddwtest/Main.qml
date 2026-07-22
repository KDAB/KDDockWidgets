import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 1024
    height: 700
    minimumWidth: 400
    minimumHeight: 300
    visible: true
    title: "KDDW QML Bug Repros"

    header: TabBar {
        id: tabBar
        currentIndex: swipe.currentIndex
        TabButton { text: "Bug 1 – OS Close" }
        TabButton { text: "Bug 2 – Initial Size" }
        TabButton { text: "Bug 3 – Maximize Button" }
        TabButton { text: "Bug 4 – FloatingWindowFlags" }
        TabButton { text: "Bug 5 – Titlebar Mouse Leak" }
        TabButton { text: "Bug 6 – Titlebar Theme" }
    }

    SwipeView {
        id: swipe
        anchors.fill: parent
        interactive: false
        currentIndex: tabBar.currentIndex

        // Bug 1: OS titlebar close button on a floating MDI dock does not
        // trigger DockWidget::closed — dock stays in DockRegistry and
        // cannot be re-opened.
        FloatingCloseRepro {}

        // Bug 2: InitialOption / initial dock size cannot be set from QML
        // because InitialOption is not constructible in QML.
        InitialSizeRepro {}

        // Bug 3: Flag_TitleBarHasMaximizeButton removes the undock button
        // without showing a maximize button on MDI docks (because
        // supportsMaximizeButton() requires m_floatingWindow != nullptr).
        MaximizeButtonRepro {}

        // Bug 4: Per-dock FloatingWindowFlags cannot be set from QML —
        // DockWidget::setFloatingWindowFlags() has no QML counterpart.
        MdiRepro {}

        // Bug 5: KDDW titlebar leaks mouse events — cursors set by content
        // underneath bleed through the titlebar area.
        TitleBarMouseLeakRepro {}

        // Bug 6: KDDW titlebar does not follow the QtQuick Controls theme
        // (wrong colours in non-default / dark themes).
        TitleBarThemeRepro {}
    }
}
