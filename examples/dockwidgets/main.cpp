/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MyWidget.h"
#include "MyMainWindow.h"
#include "MyViewFactory.h"
#include "CtrlKeyEventFilter.h"

#include <kddockwidgets/Config.h>
#include <kddockwidgets/qtwidgets/ViewFactory.h>
#include <kddockwidgets/core/DockWidget.h>
#include <kddockwidgets/core/Draggable_p.h>

#include <QStyleFactory>
#include <QApplication>
#include <QDebug>
#include <QCommandLineParser>

#include <algorithm>

// clazy:excludeall=qstring-allocations

using namespace KDDockWidgets;

int main(int argc, char **argv)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    QApplication app(argc, argv);
    app.setOrganizationName(QStringLiteral("KDAB"));
    app.setApplicationName(QStringLiteral("Test app"));

    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtWidgets);

    QCommandLineParser parser;
    parser.setApplicationDescription("KDDockWidgets example application");
    parser.addHelpOption();

    // Fusion looks better in general, but feel free to change
    qApp->setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    QCommandLineOption customStyle(
        "p",
        QCoreApplication::translate("main",
                                    "Shows how to style framework internals via ViewFactory"));
    parser.addOption(customStyle);

    QCommandLineOption reorderTabsOption(
        "r", QCoreApplication::translate("main", "Support re-ordering tabs with mouse"));
    parser.addOption(reorderTabsOption);

    QCommandLineOption noTitleBars(
        "t", QCoreApplication::translate("main", "Hide titlebars when tabs are visible"));
    parser.addOption(noTitleBars);

    QCommandLineOption alwaysTitleBarWhenFloating(
        "q",
        QCoreApplication::translate("main",
                                    "Don't hide title bars if floating, even if "
                                    "Flag_HideTitleBarWhenTabsVisible is specified."));
    parser.addOption(alwaysTitleBarWhenFloating);

    QCommandLineOption alwaysTabs(
        "z", QCoreApplication::translate("main", "Show tabs even if there's only one"));
    parser.addOption(alwaysTabs);

    QCommandLineOption lazyResizeOption("l",
                                        QCoreApplication::translate("main", "Use lazy resize"));
    parser.addOption(lazyResizeOption);

    QCommandLineOption multipleMainWindows(
        "m", QCoreApplication::translate("main", "Shows two multiple main windows"));
    parser.addOption(multipleMainWindows);

    QCommandLineOption incompatibleMainWindows(
        "i",
        QCoreApplication::translate(
            "main",
            "Only usable with -m. Make the two main windows incompatible with each other. "
            "(Illustrates (MainWindowBase::setAffinityName))"));
    parser.addOption(incompatibleMainWindows);

    QCommandLineOption tabsHaveCloseButton(
        "c", QCoreApplication::translate("main", "Tabs have a close button"));
    parser.addOption(tabsHaveCloseButton);

    QCommandLineOption nonClosableDockWidget(
        "n", QCoreApplication::translate("main", "DockWidget #0 will be non-closable"));
    parser.addOption(nonClosableDockWidget);

    QCommandLineOption relativeRestore(
        "s",
        QCoreApplication::translate(
            "main", "Don't restore main window geometry, restore dock widgets in relative sizes"));
    parser.addOption(relativeRestore);

    QCommandLineOption doubleClickMaximize(
        "x",
        QCoreApplication::translate("main",
                                    "Double clicking a title bar will maximize a floating window"));
    parser.addOption(doubleClickMaximize);

    QCommandLineOption nonDockable(
        "d", QCoreApplication::translate("main", "DockWidget #9 will be non-dockable"));
    parser.addOption(nonDockable);

    QCommandLineOption maximizeButtonOption(
        "b",
        QCoreApplication::translate(
            "main",
            "Floating dockWidgets have maximize/restore buttons instead of float/dock button"));
    parser.addOption(maximizeButtonOption);

    QCommandLineOption minimizeButtonOption(
        "k",
        QCoreApplication::translate("main",
                                    "Floating dockWidgets have a minimize button. Implies not "
                                    "being an utility window (~Qt::Tool)"));
    parser.addOption(minimizeButtonOption);

    QCommandLineOption segmentedIndicators(
        "y", QCoreApplication::translate("main", "Use segmented indicators instead of classical"));
    parser.addOption(segmentedIndicators);

    QCommandLineOption noUtilityWindows(
        "u",
        QCoreApplication::translate(
            "main", "FloatingWindows will be normal windows instead of utility windows"));
    parser.addOption(noUtilityWindows);

    QCommandLineOption keepAbove(
        "o",
        QCoreApplication::translate("main",
                                    "FloatingWindows will have Qt::WindowStaysOnTopHint. Implies "
                                    "not being an utility window (try it with -u too)"));
    parser.addOption(keepAbove);

    parser.addPositionalArgument(
        "savedlayout",
        QCoreApplication::translate("main", "loads the specified json file at startup"));

    QCommandLineOption dockableMainWindows(
        "j",
        QCoreApplication::translate("main",
                                    "Allow main windows to be docked inside other main windows"));
    parser.addOption(dockableMainWindows);

    QCommandLineOption maxSizeOption(
        "g", QCoreApplication::translate("main", "Make dock #8 have a max-size of 200x200."));
    parser.addOption(maxSizeOption);

    QCommandLineOption centralFrame(
        "f", QCoreApplication::translate("main", "Persistent central group"));

    QCommandLineOption autoHideSupport(
        "w",
        QCoreApplication::translate("main", "Enables auto-hide/minimization to side-bar support"));
    parser.addOption(autoHideSupport);

    QCommandLineOption closeOnlyCurrentTab(
        "close-only-current-tab",
        QCoreApplication::translate(
            "main",
            "The title bar's close button will only close the current tab instead of all. "
            "Illustrates using Config::Flag_CloseOnlyCurrentTab"));
    parser.addOption(closeOnlyCurrentTab);

    QCommandLineOption dontCloseBeforeRestore(
        "dont-close-widget-before-restore", // krazy:exclude=spelling
        QCoreApplication::translate("main",
                                    "DockWidgets 6, 7 and 8 won't be closed before a restore. Illustrates "
                                    "LayoutSaverOption::Skip"));
    parser.addOption(dontCloseBeforeRestore);

    QCommandLineOption blockCloseEvent(
        "block-close-event",
        QCoreApplication::translate("main", "DockWidget #0 will block close events"));
    parser.addOption(blockCloseEvent);

    QCommandLineOption programmaticDragEvent(
        "programmatic-drag",
        QCoreApplication::translate("main", "Shows how to start a drag programmatically (advanced usage)"));
    parser.addOption(programmaticDragEvent);

    QCommandLineOption showButtonsInTabBarIfTitleBarHidden(
        "show-buttons-in-tabbar-if-titlebar-hidden",
        QCoreApplication::translate("main",
                                    "If we're not using title bars we'll still show the close and "
                                    "float button in the tab bar"));
    parser.addOption(showButtonsInTabBarIfTitleBarHidden);

    QCommandLineOption centralWidget(
        "central-widget",
        QCoreApplication::translate("main",
                                    "The main window will have a non-detachable central widget"));
    parser.addOption(centralWidget);

    QCommandLineOption tabsAtBottom("tabs-at-bottom", QCoreApplication::translate("main", "Shows tabs at bottom"));
    parser.addOption(tabsAtBottom);

    QCommandLineOption ctxtMenuOnTabs(
        "allow-switch-tabs-via-menu",
        QCoreApplication::translate("main", "Allow switching tabs via context menu in tabs area"));
    parser.addOption(ctxtMenuOnTabs);

    QCommandLineOption hideCertainDockingIndicators(
        "hide-certain-docking-indicators",
        QCoreApplication::translate("main",
                                    "Illustrates usage of Config::setDropIndicatorAllowedFunc()"));
    parser.addOption(hideCertainDockingIndicators);

    QCommandLineOption ctrlTogglesDropIndicators(
        "ctrl-toggles-drop-indicators",
        QCoreApplication::translate("main", "Ctrl key toggles drop indicators"));
    parser.addOption(ctrlTogglesDropIndicators);

#if defined(DOCKS_DEVELOPER_MODE)
    parser.addOption(centralFrame);

    QCommandLineOption noQtTool(
        "no-qttool", QCoreApplication::translate("main", "(internal) Don't use Qt::Tool"));
    QCommandLineOption noParentForFloating(
        "no-parent-for-floating",
        QCoreApplication::translate("main", "(internal) FloatingWindows won't have a parent"));
    QCommandLineOption nativeTitleBar(
        "native-title-bar",
        QCoreApplication::translate("main", "(internal) FloatingWindows a native title bar"));
    QCommandLineOption noDropIndicators(
        "no-drop-indicators",
        QCoreApplication::translate("main", "(internal) Don't use any drop indicators"));

    parser.addOption(noQtTool);
    parser.addOption(noParentForFloating);
    parser.addOption(nativeTitleBar);
    parser.addOption(noDropIndicators);

#if defined(Q_OS_WIN)
    QCommandLineOption noAeroSnap(
        "no-aero-snap", QCoreApplication::translate("main", "(internal) Disable AeroSnap"));
    parser.addOption(noAeroSnap);
#endif
#else
    KDDW_UNUSED(centralFrame)
#endif

    parser.process(app);

    if (parser.isSet(customStyle)) {
        Config::self().setViewFactory(new CustomWidgetFactory()); // Sets our custom factory

        // Increase the separator size, just for demo
        Config::self().setSeparatorThickness(10);
    }

    if (parser.isSet(segmentedIndicators))
        KDDockWidgets::Core::ViewFactory::s_dropIndicatorType =
            KDDockWidgets::DropIndicatorType::Segmented;

    MainWindowOptions options = MainWindowOption_None;
    auto flags = KDDockWidgets::Config::self().flags();
#if defined(DOCKS_DEVELOPER_MODE)
    auto internalFlags = KDDockWidgets::Config::self().internalFlags();

    options = parser.isSet(centralFrame) ? MainWindowOption_HasCentralGroup : MainWindowOption_None;

    if (parser.isSet(centralWidget))
        options |= MainWindowOption_HasCentralWidget;

    if (parser.isSet(noQtTool))
        internalFlags |= KDDockWidgets::Config::InternalFlag_DontUseQtToolWindowsForFloatingWindows;

    if (parser.isSet(keepAbove))
        flags |= KDDockWidgets::Config::Flag_KeepAboveIfNotUtilityWindow;

    if (parser.isSet(noParentForFloating))
        internalFlags |= KDDockWidgets::Config::InternalFlag_DontUseParentForFloatingWindows;

    if (parser.isSet(nativeTitleBar))
        flags |= KDDockWidgets::Config::Flag_NativeTitleBar;

    if (parser.isSet(noDropIndicators))
        KDDockWidgets::Core::ViewFactory::s_dropIndicatorType = KDDockWidgets::DropIndicatorType::None;

#if defined(Q_OS_WIN)
    if (parser.isSet(noAeroSnap))
        internalFlags |= KDDockWidgets::Config::InternalFlag_NoAeroSnap;
#endif
    Config::self().setInternalFlags(internalFlags);
#endif

    if (parser.isSet(autoHideSupport))
        flags |= Config::Flag_AutoHideSupport;

    if (parser.isSet(closeOnlyCurrentTab))
        flags |= Config::Flag_CloseOnlyCurrentTab;

    if (parser.isSet(showButtonsInTabBarIfTitleBarHidden))
        flags |= Config::Flag_ShowButtonsOnTabBarIfTitleBarHidden;

    if (parser.isSet(noTitleBars))
        flags |= KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible;

    if (parser.isSet(noUtilityWindows))
        flags |= KDDockWidgets::Config::Flag_DontUseUtilityFloatingWindows;

    if (parser.isSet(alwaysTabs))
        flags |= KDDockWidgets::Config::Flag_AlwaysShowTabs;

    if (parser.isSet(alwaysTitleBarWhenFloating)) {
        flags |= KDDockWidgets::Config::Flag_AlwaysTitleBarWhenFloating;
        if (!(flags & KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible)) {
            qWarning() << "Flag_AlwaysTitleBarWhenFloating is unneeded if "
                          "Flag_HideTitleBarWhenTabsVisible isn't used."
                       << "As floating windows already have title bars by default.";
        }
    }

    if (parser.isSet(customStyle) || qEnvironmentVariableIsSet("KDDW_DEBUG_FOCUS"))
        flags |= KDDockWidgets::Config::Flag_TitleBarIsFocusable; // also showing title bar focus
                                                                  // with -p, just to not introduce
                                                                  // another switch

    if (parser.isSet(reorderTabsOption))
        flags |= KDDockWidgets::Config::Flag_AllowReorderTabs;

    if (parser.isSet(maximizeButtonOption))
        flags |= KDDockWidgets::Config::Flag_TitleBarHasMaximizeButton;

    if (parser.isSet(minimizeButtonOption))
        flags |= KDDockWidgets::Config::Flag_TitleBarHasMinimizeButton;

    if (parser.isSet(lazyResizeOption))
        flags |= KDDockWidgets::Config::Flag_LazyResize;

    if (parser.isSet(tabsHaveCloseButton))
        flags |= KDDockWidgets::Config::Flag_TabsHaveCloseButton;

    if (parser.isSet(ctxtMenuOnTabs))
        flags |= KDDockWidgets::Config::Flag_AllowSwitchingTabsViaMenu;


    if (parser.isSet(doubleClickMaximize))
        flags |= KDDockWidgets::Config::Flag_DoubleClickMaximizes;

    if (parser.isSet(incompatibleMainWindows) && !parser.isSet(multipleMainWindows)) {
        qWarning() << "Error: Argument -i requires -m";
        return 1;
    }

    if (parser.isSet(programmaticDragEvent) && parser.isSet(ctrlTogglesDropIndicators)) {
        qWarning() << "Error: Arguments --programmatic-drag and --ctrl-toggles-drop-indicators are "
                      "mutually exclusive. The latter is already included in the former.";
        return 1;
    }

    if (parser.isSet(hideCertainDockingIndicators)) {
        // Here we exemplify adding a restriction to "Dock Widget 8"
        // Dock widget 8 will only be allowed to dock to the outer areas
        auto func = [](KDDockWidgets::DropLocation location,
                       const KDDockWidgets::Core::DockWidget::List &source,
                       const KDDockWidgets::Core::DockWidget::List &target,
                       Core::DropArea *) {
            KDDW_UNUSED(target); // When dragging into a tab, 'target' would have the list of already
                                 // tabbed dock widgets

            const bool isDraggingDW8 =
                std::find_if(source.cbegin(), source.cend(),
                             [](KDDockWidgets::Core::DockWidget *dw) {
                                 return dw->uniqueName() == QLatin1String("DockWidget #8");
                             })
                != source.cend();

            return (location & KDDockWidgets::DropLocation_Outter) || !isDraggingDW8;
        };

        KDDockWidgets::Config::self().setDropIndicatorAllowedFunc(func);
    }

    KDDockWidgets::Config::self().setTabsAtBottom(parser.isSet(tabsAtBottom));
    KDDockWidgets::Config::self().setFlags(flags);


    MyMainWindow::ExampleOptions exampleOptions = {};

    if (parser.isSet(ctrlTogglesDropIndicators))
        exampleOptions |= MyMainWindow::ExampleOption::CtrlKeyFiltersDropIndicators;
    if (parser.isSet(nonClosableDockWidget))
        exampleOptions |= MyMainWindow::ExampleOption::DockWidget0IsNonClosable;
    if (parser.isSet(relativeRestore))
        exampleOptions |= MyMainWindow::ExampleOption::RestoreIsRelative;
    if (parser.isSet(nonDockable))
        exampleOptions |= MyMainWindow::ExampleOption::NonDockableDockWidget9;
    if (parser.isSet(maxSizeOption))
        exampleOptions |= MyMainWindow::ExampleOption::MaxSizeForDockWidget8;
    if (parser.isSet(dontCloseBeforeRestore))
        exampleOptions |= MyMainWindow::ExampleOption::DockWidgets678DontCloseBeforeRestore;
    if (parser.isSet(blockCloseEvent))
        exampleOptions |= MyMainWindow::ExampleOption::Dock0BlocksCloseEvent;
    if (parser.isSet(programmaticDragEvent)) {
        exampleOptions |= MyMainWindow::ExampleOption::ProgrammaticDragEvent;

        static auto s_ctrlKeyEventFilter = new CtrlKeyEventFilter(qApp);

        /// Here we demonstrate how to use setDragAboutToStartFunc()/setDragEndedFunc() to prevent a drag from happening
        /// In this made up example:
        /// 1. If ctrl is pressed, we always allow the drag
        /// 2. If the drag is programmatic (DockWidget::startDrag()), we always allow the drag as well
        /// 3. If the dragged widget is already a window, we allow a drag to move it, but not dock it
        ///   3.1. We also install an event filter to show the drop indicators when ctrl is pressed

        KDDockWidgets::Config::self().setDragAboutToStartFunc([](Core::Draggable *draggable) -> bool {
            const bool ctrlIsPressed = qApp->keyboardModifiers() & Qt::ControlModifier;

            if (ctrlIsPressed || draggable->isInProgrammaticDrag()) {
                KDDockWidgets::Config::self().setDropIndicatorsInhibited(false);
                return true;
            }

            if (draggable->isWindow()) {
                qApp->installEventFilter(s_ctrlKeyEventFilter);

                // Ctrl might already be pressed before the DnD even starts, so honour that as well
                KDDockWidgets::Config::self().setDropIndicatorsInhibited(!ctrlIsPressed);

                return true;
            }

            return false;
        });

        KDDockWidgets::Config::self().setDragEndedFunc([]() {
            // cleanup
            qApp->removeEventFilter(s_ctrlKeyEventFilter);
        });
    }

    const bool usesMainWindowsWithAffinity = parser.isSet(multipleMainWindows);
    const bool usesDockableMainWindows = parser.isSet(dockableMainWindows);

    MyMainWindow mainWindow(QStringLiteral("MyMainWindow"), options, exampleOptions);
    mainWindow.setWindowTitle("Main Window 1");
    mainWindow.resize(1200, 1200);
    mainWindow.show();

    if (usesMainWindowsWithAffinity) {
        if (usesDockableMainWindows) {
            qWarning() << "MainWindows with affinity option is incompatible with Dockable Main "
                          "Windows option";
            return 1;
        }

        // By default a dock widget can dock into any main window.
        // By setting an affinity name we can prevent that. Dock widgets of different affinities are
        // incompatible.
        const QString affinity =
            parser.isSet(incompatibleMainWindows) ? QStringLiteral("affinity1") : QString();

        auto mainWindow2 =
            new MyMainWindow(QStringLiteral("MyMainWindow-2"), options, exampleOptions, affinity);
        if (affinity.isEmpty())
            mainWindow2->setWindowTitle("Main Window 2");
        else
            mainWindow2->setWindowTitle("Main Window 2 (different affinity)");

        mainWindow2->resize(1200, 1200);
        mainWindow2->show();
    } else if (usesDockableMainWindows) {
        auto mainWindowDockWidget =
            new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyMainWindow-2-DW"));

        const QString affinity = QStringLiteral("Inner-DockWidgets-2");
        MyMainWindow::ExampleOptions exampleOptions2 = {};
        if (parser.isSet(relativeRestore))
            exampleOptions2 |= MyMainWindow::ExampleOption::RestoreIsRelative;
        auto dockableMainWindow =
            new MyMainWindow(QStringLiteral("MyMainWindow-2"), options, exampleOptions2, affinity);

        dockableMainWindow->setAffinities({ affinity });
        dockableMainWindow->setStyleSheet(QStringLiteral("background: yellow"));

        dockableMainWindow->setWindowTitle("Dockable Main Window");
        dockableMainWindow->show();
        mainWindowDockWidget->setWidget(dockableMainWindow);
        mainWindowDockWidget->open();
        mainWindowDockWidget->resize(QSize(800, 800));
    }

    const QStringList args = parser.positionalArguments();
    if (!args.isEmpty()) {
        const QString sourceJsonFileName = args[0];
        KDDockWidgets::LayoutSaver loader;
        if (!loader.restoreFromFile(sourceJsonFileName)) {
            qWarning() << Q_FUNC_INFO << "Failed to restore from" << sourceJsonFileName;
            return 1;
        }
    }


    return app.exec();
}
