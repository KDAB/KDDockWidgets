/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_TESTS_UTILS_H
#define KDDOCKWIDGETS_TESTS_UTILS_H

// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

#include "Config.h"
#include "core/Logging_p.h"
#include "kddockwidgets/KDDockWidgets.h"
#include "kddockwidgets/core/DockRegistry.h"
#include "kddockwidgets/core/DropIndicatorOverlay.h"
#include "kddockwidgets/core/DropArea.h"
#include "kddockwidgets/core/TitleBar.h"
#include "kddockwidgets/core/Stack.h"
#include "kddockwidgets/core/Platform.h"
#include "kddockwidgets/core/FloatingWindow.h"
#include "kddockwidgets/core/DockWidget.h"
#include "core/DockWidget_p.h"
#include "core/ObjectGuard_p.h"
#include "kddockwidgets/core/Utils_p.h"
#include "kddockwidgets/core/ViewFactory.h"
#include "kddockwidgets/core/MainWindow.h"
#include "kddockwidgets/core/Window.h"
#include "kddockwidgets/core/Platform.h"

#include <QVector>

#include <memory>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

static bool s_pauseBeforePress = false; // for debugging
static bool s_pauseBeforeMove = false; // for debugging
#define DEBUGGING_PAUSE_DURATION 5000 // 5 seconds

// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates

namespace KDDockWidgets {

namespace Tests {

enum ButtonAction {
    ButtonAction_None,
    ButtonAction_Press = 1,
    ButtonAction_Release = 2
};
Q_DECLARE_FLAGS(ButtonActions, ButtonAction)

struct DockDescriptor
{
    Location loc;
    int relativeToIndex;
    Core::ObjectGuard<Core::DockWidget> createdDock;
    KDDockWidgets::InitialVisibilityOption option;
};

inline QPoint dragPointForWidget(Core::Group *group, int index)
{
    if (group->hasSingleDockWidget()) {
        Q_ASSERT(index == 0);
        return group->titleBar()->mapToGlobal(QPoint(5, 5));
    } else {
        QRect rect = group->stack()->tabBar()->rectForTab(index);
        return group->stack()->tabBar()->view()->mapToGlobal(rect.center());
    }
}

struct EnsureTopLevelsDeleted
{
    EnsureTopLevelsDeleted()
        : m_originalFlags(Config::self().flags())
        , m_originalInternalFlags(Config::self().internalFlags())
        , m_originalSeparatorThickness(Config::self().separatorThickness())
    {
    }

    ~EnsureTopLevelsDeleted()
    {
        qDeleteAll(DockRegistry::self()->floatingWindows(/*includeBeingDeleted=*/true));
        qDeleteAll(DockRegistry::self()->dockwidgets());

        if (!DockRegistry::self()->isEmpty()) {
            auto dr = DockRegistry::self();
            KDDW_UNUSED(dr);
            KDDW_WARN("There's still top-level widgets present!"
                      "\nfloatings: {}"
                      "\nmainWindows: {}"
                      "\ndocks: {}",
                      dr->floatingWindows(/*includeBeingDeleted=*/true).size(),
                      dr->mainWindowsNames().size(),
                      dr->dockWidgetNames().size());
        }

        // Other cleanup, since we use this class everywhere
        Config::self().setDockWidgetFactoryFunc(nullptr);
        Config::self().setInternalFlags(m_originalInternalFlags);
        Config::self().setFlags(m_originalFlags);
        Config::self().setSeparatorThickness(m_originalSeparatorThickness);
    }

    const Config::Flags m_originalFlags;
    const Config::InternalFlags m_originalInternalFlags;
    const int m_originalSeparatorThickness;
};

bool shouldBlacklistWarning(const QString &msg, const QString &category = {});

std::unique_ptr<Core::MainWindow>
createMainWindow(QSize sz = { 1000, 1000 },
                 KDDockWidgets::MainWindowOptions options = MainWindowOption_HasCentralFrame,
                 const QString &name = {}, bool show = true);



std::unique_ptr<Core::MainWindow> createMainWindow(QVector<DockDescriptor> &docks);

Core::DockWidget *createDockWidget(const QString &name, Core::View *guest,
                                   DockWidgetOptions options = {},
                                   LayoutSaverOptions layoutSaverOptions = {},
                                   bool show = true, const QString &affinityName = {});

Core::DockWidget *createDockWidget(const QString &name);

void nestDockWidget(Core::DockWidget *dock, Core::DropArea *dropArea,
                    Core::Group *relativeTo, KDDockWidgets::Location location);


void doubleClickOn(QPoint globalPos, std::shared_ptr<Core::Window> receiver);
void pressOn(QPoint globalPos, Core::View *receiver);
void pressOn(QPoint globalPos, std::shared_ptr<Core::Window> receiver);
KDDW_QCORO_TASK releaseOn(QPoint globalPos, Core::View *receiver);
void clickOn(QPoint globalPos, Core::View *receiver);
KDDW_QCORO_TASK moveMouseTo(QPoint globalDest, Core::View *receiver);

inline Core::FloatingWindow *createFloatingWindow()
{
    static int count = 0;
    count++;
    auto dock = createDockWidget(QString("dock %1").arg(count));
    return dock->d->morphIntoFloatingWindow();
}

inline Core::View *draggableFor(Core::View *view)
{
    Core::View *draggable = nullptr;
    if (auto dw = view->asDockWidgetController()) {
        if (auto group = dw->d->group())
            draggable = group->titleBar()->view();
    } else if (auto fw = view->asFloatingWindowController()) {
        Core::Group *group = fw->hasSingleFrame()
            ? static_cast<Core::Group *>(fw->groups().first())
            : nullptr;

        if ((KDDockWidgets::Config::self().flags()
             & KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible)
            && group && group->hasTabsVisible()) {
            draggable = group->stack()->view();
        } else {
            draggable = fw->titleBar()->view();
        }
    } else if (view->is(Core::ViewType::Stack) || view->is(Core::ViewType::TitleBar)) {
        draggable = view;
    }

    // spdlog:info("Draggable is {} for {}", draggable, view);
    return draggable;
}

inline KDDW_QCORO_TASK drag(Core::View *sourceWidget, QPoint pressGlobalPos, QPoint globalDest,
                            ButtonActions buttonActions = ButtonActions(ButtonAction_Press)
                                | ButtonAction_Release)
{
    if (buttonActions & ButtonAction_Press) {
        if (s_pauseBeforePress)
            KDDW_CO_AWAIT Core::Platform::instance()->tests_wait(DEBUGGING_PAUSE_DURATION);

        pressOn(pressGlobalPos, sourceWidget);
    }

    sourceWidget->activateWindow();

    if (s_pauseBeforeMove)
        KDDW_CO_AWAIT Core::Platform::instance()->tests_wait(DEBUGGING_PAUSE_DURATION);

    KDDW_CO_AWAIT moveMouseTo(globalDest, sourceWidget);
    pressGlobalPos = sourceWidget->mapToGlobal(QPoint(10, 10));
    if (buttonActions & ButtonAction_Release)
        KDDW_CO_AWAIT releaseOn(globalDest, sourceWidget);

    KDDW_CO_RETURN true;
}

inline KDDW_QCORO_TASK drag(Core::View *sourceView, QPoint globalDest,
                            ButtonActions buttonActions = ButtonActions(ButtonAction_Press)
                                | ButtonAction_Release)
{
    Q_ASSERT(sourceView && sourceView->controller()->isVisible());

    Core::View *draggable = draggableFor(sourceView);

    Q_ASSERT(draggable && draggable->controller()->isVisible());
    const QPoint pressGlobalPos = draggable->mapToGlobal(QPoint(15, 15));

    auto result = KDDW_CO_AWAIT drag(draggable, pressGlobalPos, globalDest, buttonActions);
    KDDW_CO_RETURN result;
}

inline KDDW_QCORO_TASK dragFloatingWindowTo(Core::FloatingWindow *fw, QPoint globalDest,
                                            ButtonActions buttonActions = ButtonActions(ButtonAction_Press)
                                                | ButtonAction_Release)
{
    Core::View *draggable = draggableFor(fw->view());
    Q_ASSERT(draggable);
    Q_ASSERT(draggable->controller()->isVisible());
    auto result = KDDW_CO_AWAIT drag(draggable, draggable->mapToGlobal(QPoint(10, 10)), globalDest, buttonActions);
    KDDW_CO_RETURN result;
}

inline KDDW_QCORO_TASK dragFloatingWindowTo(Core::FloatingWindow *fw, Core::DropArea *target,
                                            DropLocation dropLocation)
{
    // run one event loop, needed by flutter
    KDDW_CO_AWAIT Core::Platform::instance()->tests_wait(100);

    auto draggable = draggableFor(fw->view());
    Q_ASSERT(draggable);

    // First we drag over it, so the drop indicators appear:
    KDDW_CO_AWAIT drag(draggable, draggable->mapToGlobal(QPoint(10, 10)),
                       target->window()->mapToGlobal(target->window()->rect().center()), ButtonAction_Press);

    // Now we drag over the drop indicator and only then release mouse:
    Core::DropIndicatorOverlay *dropIndicatorOverlay = target->dropIndicatorOverlay();
    const QPoint dropPoint = dropIndicatorOverlay->posForIndicator(dropLocation);

    auto result = KDDW_CO_AWAIT drag(draggable, QPoint(), dropPoint, ButtonAction_Release);
    KDDW_CO_RETURN result;
}

inline int osWindowMinWidth()
{
#ifdef Q_OS_WIN
    return GetSystemMetrics(SM_CXMIN);
#else
    return 140; // Some random value for our windows. It's only important on Windows
#endif
}

/// Helper function so we don't write such a big line everywhere
inline Core::DockWidget *newDockWidget(const QString &uniqueName,
                                       DockWidgetOptions opts = {},
                                       LayoutSaverOptions layoutSaverOptions = {})
{
    return Config::self()
        .viewFactory()
        ->createDockWidget(uniqueName, opts, layoutSaverOptions)
        ->asDockWidgetController();
}

inline Core::DockWidget *createAndNestDockWidget(KDDockWidgets::Core::DropArea *dropArea,
                                                 Core::Group *relativeTo,
                                                 KDDockWidgets::Location location)
{
    static int count = 0;
    count++;
    const QString name = QString("dock%1").arg(count);
    auto dock = createDockWidget(name);
    dock->setObjectName(name);
    nestDockWidget(dock, dropArea, relativeTo, location);
    dropArea->checkSanity();
    return dock;
}

inline std::unique_ptr<KDDockWidgets::Core::MainWindow>
createSimpleNestedMainWindow(Core::DockWidget **centralDock,
                             Core::DockWidget **leftDock,
                             Core::DockWidget **rightDock)
{
    auto window = createMainWindow({ 900, 500 });
    *centralDock = createDockWidget("centralDock");
    window->addDockWidgetAsTab(*centralDock);
    auto dropArea = window->dropArea();

    *leftDock = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnLeft);
    *rightDock = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnRight);
    return window;
}

}

}

Q_DECLARE_METATYPE(KDDockWidgets::Tests::DockDescriptor)


#endif
