/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief Class to save and restore dock widget layouts.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "LayoutSaver.h"
#include "Config.h"
#include "core/DropArea.h"
#include "core/ViewFactory.h"
#include "core/LayoutSaver_p.h"
#include "core/Logging_p.h"
#include "core/Position_p.h"
#include "core/Utils_p.h"
#include "core/View_p.h"

#include "core/DockRegistry.h"
#include "core/Platform.h"
#include "core/Layout.h"
#include "core/Group.h"
#include "core/FloatingWindow.h"
#include "core/DockWidget.h"
#include "core/DockWidget_p.h"
#include "core/MainWindow.h"
#include "core/nlohmann_helpers_p.h"
#include "core/layouting/Item_p.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <qtestsupport_core.h>
#include <utility>

/**
 * Some implementation details:
 *
 * Restoring is done in two phases. From the JSON, we construct an intermediate representation,
 * which doesn't have any GUI types. Finally we then construct the GUI from the intermediate
 * representation.
 *
 *     JSON <-> Intermediate rep (bunch non-gui structs) <-> GUI classes
 *
 * This is in contrast to many other dock widget frameworks which just do:
 *     serialized <-> GUI
 *
 * The advantage of having the intermediate structs is that we can do validations on them and if
 * we find some corruption we don't even start messing with the GUI.
 *
 * See the LayoutSaver::* structs in LayoutSaver_p.h, those are the intermediate structs.
 * They have methods to convert to/from JSON.
 * All other gui classes have methods to convert to/from these structs. For example
 * FloatingWindow::serialize()/deserialize()
 */
using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

std::map<QString, LayoutSaver::DockWidget::Ptr> LayoutSaver::DockWidget::s_dockWidgets;
LayoutSaver::Layout *LayoutSaver::Layout::s_currentLayoutBeingRestored = nullptr;
std::unordered_map<QString, std::shared_ptr<KDDockWidgets::Positions>> LayoutSaver::Private::s_unrestoredPositions;
std::unordered_map<QString, CloseReason> LayoutSaver::Private::s_unrestoredProperties;

static InternalRestoreOptions internalRestoreOptions(RestoreOptions options)
{
    InternalRestoreOptions ret = {};
    if (options.testFlag(RestoreOption_RelativeToMainWindow)) {
        ret.setFlag(InternalRestoreOption::SkipMainWindowGeometry);
        ret.setFlag(InternalRestoreOption::RelativeFloatingWindowGeometry);
        options.setFlag(RestoreOption_RelativeToMainWindow, false);
    }
    if (options.testFlag(RestoreOption_AbsoluteFloatingDockWindows)) {
        ret.setFlag(InternalRestoreOption::RelativeFloatingWindowGeometry, false);
        options.setFlag(RestoreOption_AbsoluteFloatingDockWindows, false);
    }
    if (options.testFlag(RestoreOption_CloseUnknownDockWidgets)) {
        ret.setFlag(InternalRestoreOption::CloseUnknownDockWidgets);
        options.setFlag(RestoreOption_CloseUnknownDockWidgets, false);
    }

    if (options != RestoreOption_None) {
        KDDW_ERROR("Unknown options={}", int(options));
    }

    return ret;
}

bool LayoutSaver::Private::s_restoreInProgress = false;

namespace KDDockWidgets {

template<typename T>
static T jsonValue(const nlohmann::json &json, const char *name, const T &defaultValue)
{
    try {
        // value can throw if the type has "null" value, for instance.
        return json.value(name, defaultValue);
    } catch (...) {
        return defaultValue;
    }
}

template<typename Type>
static void to_json(nlohmann::json &json, const typename Type::List &list)
{
    for (const auto &l : list) {
        json.push_back(l);
    }
}

static void to_json(nlohmann::json &json, const LayoutSaver::Group &f)
{
    json["id"] = f.id;
    json["isNull"] = f.isNull;
    json["objectName"] = f.objectName;
    json["geometry"] = f.geometry;
    json["options"] = f.options;
    json["currentTabIndex"] = f.currentTabIndex;
    json["mainWindowUniqueName"] = f.mainWindowUniqueName;
    json["dockWidgets"] = dockWidgetNames(f.dockWidgets);
}

static void from_json(const nlohmann::json &json, LayoutSaver::Group &f)
{
    f.id = jsonValue(json, "id", QString());
    f.isNull = jsonValue(json, "isNull", true);
    f.objectName = jsonValue(json, "objectName", QString());
    f.geometry = jsonValue(json, "geometry", Rect());
    f.options = jsonValue(json, "options", QFlags<FrameOption>::Int {});
    f.currentTabIndex = jsonValue(json, "currentTabIndex", 0);
    f.mainWindowUniqueName = jsonValue(json, "mainWindowUniqueName", QString());

    auto it = json.find("dockWidgets");
    if (it == json.end())
        return;

    auto &dockWidgets = *it;
    f.dockWidgets.reserve(( int )dockWidgets.size());
    for (const auto &d : dockWidgets) {
        LayoutSaver::DockWidget::Ptr dw =
            LayoutSaver::DockWidget::dockWidgetForName(d.get<QString>());
        f.dockWidgets.push_back(dw);
    }
}

static void to_json(nlohmann::json &json, const LayoutSaver::MultiSplitter &s)
{
    json["layout"] = s.layout;
    auto &groups = json["frames"];
    for (const auto &it : s.groups) {
        const auto &group = it.second;
        groups[group.id.toStdString()] = group;
    }
}

static void from_json(const nlohmann::json &json, LayoutSaver::MultiSplitter &s)
{
    s.groups.clear();
    s.layout = jsonValue(json, "layout", nlohmann::json::object());
    auto it = json.find("frames");
    if (it == json.end())
        return;
    if (it->is_null())
        return;

    auto &frms = *it;
    if (!frms.is_object())
        KDDW_ERROR("Unexpected not object");

    for (const auto &kv : frms.items()) {
        QString key = QString::fromStdString(kv.key());
        auto group = kv.value().get<LayoutSaver::Group>();
        s.groups[key] = group;
    }
}

static void to_json(nlohmann::json &json, const LayoutSaver::MainWindow &mw)
{
    json["options"] = int(mw.options);
    json["multiSplitterLayout"] = mw.multiSplitterLayout;
    json["uniqueName"] = mw.uniqueName;
    json["geometry"] = mw.geometry;
    json["normalGeometry"] = mw.normalGeometry;
    json["screenIndex"] = mw.screenIndex;
    json["screenSize"] = mw.screenSize;
    json["isVisible"] = mw.isVisible;
    json["affinities"] = mw.affinities;
    json["windowState"] = mw.windowState;

    for (SideBarLocation loc : { SideBarLocation::North, SideBarLocation::East,
                                 SideBarLocation::West, SideBarLocation::South }) {
        const Vector<QString> dockWidgets = mw.dockWidgetsForSideBar(loc);
        if (!dockWidgets.isEmpty()) {
            std::string key = std::string("sidebar-") + std::to_string(( int )loc);
            json[key] = dockWidgets;
        }
    }
}

static void from_json(const nlohmann::json &json, LayoutSaver::MainWindow &mw)
{
    mw.options = static_cast<decltype(mw.options)>(jsonValue(json, "options", 0));
    mw.multiSplitterLayout = jsonValue(json, "multiSplitterLayout", LayoutSaver::MultiSplitter());
    mw.uniqueName = jsonValue(json, "uniqueName", QString());
    mw.geometry = jsonValue(json, "geometry", Rect());
    mw.normalGeometry = jsonValue(json, "normalGeometry", Rect());
    mw.screenIndex = jsonValue(json, "screenIndex", 0);
    mw.screenSize = jsonValue(json, "screenSize", Size(800, 600));
    mw.isVisible = jsonValue(json, "isVisible", false);
    mw.affinities = jsonValue(json, "affinities", Vector<QString>());
    mw.windowState = ( WindowState )jsonValue(json, "windowState", 0);

    // Compatibility hack. Old json format had a single "affinityName" instead of an "affinities"
    // list:
    if (json.find("affinityName") != json.end()) {
        QString affinityName = json["affinityName"].get<QString>();
        if (!mw.affinities.contains(affinityName)) {
            mw.affinities.push_back(affinityName);
        }
    }

    for (SideBarLocation loc : { SideBarLocation::North, SideBarLocation::East,
                                 SideBarLocation::West, SideBarLocation::South }) {
        std::string key = std::string("sidebar-") + std::to_string(( int )loc);
        auto it = json.find(key);
        if (it == json.end())
            continue;
        auto &val = *it;
        if (val.is_array() && !val.empty()) {
            mw.dockWidgetsPerSideBar[loc] = val.get<Vector<QString>>();
        }
    }
}

static void to_json(nlohmann::json &json, const LayoutSaver::FloatingWindow &window)
{
    json["multiSplitterLayout"] = window.multiSplitterLayout;
    json["parentIndex"] = window.parentIndex;
    json["parentMainWindowName"] = window.parentMainWindowName;
    json["geometry"] = window.geometry;
    json["normalGeometry"] = window.normalGeometry;
    json["screenIndex"] = window.screenIndex;
    json["screenSize"] = window.screenSize;
    json["flags"] = window.flags;
    json["isVisible"] = window.isVisible;
    json["windowState"] = window.windowState;

    if (!window.affinities.isEmpty()) {
        json["affinities"] = window.affinities;
    }
}

static void from_json(const nlohmann::json &json, LayoutSaver::FloatingWindow &window)
{
    window.multiSplitterLayout = jsonValue(json, "multiSplitterLayout", LayoutSaver::MultiSplitter());
    window.parentIndex = jsonValue(json, "parentIndex", -1);
    window.parentMainWindowName = jsonValue(json, "parentMainWindowName", QString());
    window.geometry = jsonValue(json, "geometry", Rect());
    window.normalGeometry = jsonValue(json, "normalGeometry", Rect());
    window.screenIndex = jsonValue(json, "screenIndex", 0);
    window.screenSize = jsonValue(json, "screenSize", Size(800, 600));
    window.isVisible = jsonValue(json, "isVisible", false);
    window.flags = jsonValue(json, "flags", int(FloatingWindowFlag::FromGlobalConfig));
    window.windowState = ( WindowState )jsonValue(json, "windowState", 0);
    window.affinities = jsonValue(json, "affinities", Vector<QString>());

    // Compatibility hack. Old json format had a single "affinityName" instead of an "affinities"
    // list:
    const QString affinityName = jsonValue(json, "affinityName", QString());
    if (!affinityName.isEmpty() && !window.affinities.contains(affinityName)) {
        window.affinities.push_back(affinityName);
    }
}

static void to_json(nlohmann::json &json, const LayoutSaver::ScreenInfo &screenInfo)
{
    json["index"] = screenInfo.index;
    json["geometry"] = screenInfo.geometry;
    json["name"] = screenInfo.name;
    json["devicePixelRatio"] = screenInfo.devicePixelRatio;
}

static void from_json(const nlohmann::json &j, LayoutSaver::ScreenInfo &screenInfo)
{
    screenInfo.index = j.value("index", 0);
    screenInfo.geometry = j.value("geometry", Rect());
    screenInfo.name = j.value("name", QString());
    screenInfo.devicePixelRatio = j.value("devicePixelRatio", 1.0);
}

static void to_json(nlohmann::json &json, const LayoutSaver::Placeholder &placeHolder)
{
    json["isFloatingWindow"] = placeHolder.isFloatingWindow;
    json["itemIndex"] = placeHolder.itemIndex;
    if (placeHolder.isFloatingWindow)
        json["indexOfFloatingWindow"] = placeHolder.indexOfFloatingWindow;
    else
        json["mainWindowUniqueName"] = placeHolder.mainWindowUniqueName;
}

static void from_json(const nlohmann::json &json, LayoutSaver::Placeholder &placeHolder)
{
    placeHolder.isFloatingWindow = jsonValue(json, "isFloatingWindow", false);
    placeHolder.itemIndex = jsonValue(json, "itemIndex", 0);
    placeHolder.indexOfFloatingWindow = jsonValue(json, "indexOfFloatingWindow", -1);
    placeHolder.mainWindowUniqueName = jsonValue(json, "mainWindowUniqueName", QString());
}

static void to_json(nlohmann::json &json, const LayoutSaver::Position &pos)
{
    json["lastFloatingGeometry"] = pos.lastFloatingGeometry;
    json["lastOverlayedGeometries"] = pos.lastOverlayedGeometries;
    json["tabIndex"] = pos.tabIndex;
    json["wasFloating"] = pos.wasFloating;
    json["placeholders"] = pos.placeholders;
}

static void from_json(const nlohmann::json &json, LayoutSaver::Position &pos)
{
    pos.lastFloatingGeometry = jsonValue(json, "lastFloatingGeometry", Rect());
    pos.lastOverlayedGeometries = jsonValue(json, "lastOverlayedGeometries", std::unordered_map<KDDockWidgets::SideBarLocation, Rect>());
    pos.tabIndex = jsonValue(json, "tabIndex", 0);
    pos.wasFloating = jsonValue(json, "wasFloating", false);
    pos.placeholders = jsonValue(json, "placeholders", LayoutSaver::Placeholder::List());
}

static void to_json(nlohmann::json &json, const LayoutSaver::DockWidget &dw)
{
    if (!dw.affinities.isEmpty())
        json["affinities"] = dw.affinities;
    json["uniqueName"] = dw.uniqueName;
    json["lastPosition"] = dw.lastPosition;
    json["lastCloseReason"] = dw.lastCloseReason;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    if (!dw.userData.isEmpty())
        json["userData"] = dw.userData;
#endif
}

static void from_json(const nlohmann::json &json, LayoutSaver::DockWidget &dw)
{
    auto it = json.find("affinities");
    if (it != json.end())
        dw.affinities = it->get<Vector<QString>>();

    dw.uniqueName = jsonValue(json, "uniqueName", QString());
    if (dw.uniqueName.isEmpty())
        KDDW_ERROR("Unexpected no uniqueName for dockWidget");

    dw.lastPosition = jsonValue(json, "lastPosition", LayoutSaver::Position());
    dw.lastCloseReason = jsonValue(json, "lastCloseReason", CloseReason::Unspecified);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    auto userDataIt = json.find("userData");
    if (userDataIt != json.end()) {
        QVariantMap userData;
        from_json(*userDataIt, userData);
        dw.userData = userData;
    }
#endif
}

static void to_json(nlohmann::json &json, const typename LayoutSaver::DockWidget::List &list)
{
    for (const auto &mw : list) {
        json.push_back(*mw);
    }
}

static void from_json(const nlohmann::json &json, typename LayoutSaver::DockWidget::List &list)
{
    list.clear();
    for (const auto &v : json) {
        auto it = v.find("uniqueName");
        if (it == v.end()) {
            KDDW_ERROR("Unexpected no uniqueName");
            continue;
        }
        QString uniqueName = it->get<QString>();
        auto dw = LayoutSaver::DockWidget::dockWidgetForName(uniqueName);
        from_json(v, *dw);
        list.push_back(dw);
    }
}

}

namespace {

bool isDocumentMode(const Core::MainWindow::List &mainWindows,
                    const QVector<QString> &affinities)
{
    if (mainWindows.size() != 1) {
        // more than 1 window not supported (yet, until someone needs it ?)
        return false;
    }

    if (affinities.size() != 1) {
        // Not supported
        return false;
    }

    auto mainWindow = mainWindows.first();
    const QString &documentAffinity = mainWindow->documentAffinity();
    if (documentAffinity.isEmpty()) {
        return false;
    }

    if ((mainWindow->options() & MainWindowOption_HasCentralGroup) == 0) {
        // we need to be in document mode
        return false;
    }

    return true;
}

bool isRestoringDocuments(const Core::MainWindow::List &mainWindows,
                          const QVector<QString> &affinities)
{
    return isDocumentMode(mainWindows, affinities) && affinities.first() == mainWindows.first()->documentAffinity();
}

/// The dock widget @p mainWindow is nested in, if it's a nested main window
Core::DockWidget *hostDockWidget(Core::MainWindow *mainWindow)
{
    auto view = mainWindow->view();
    if (!view)
        return nullptr;

    auto parent = view->parentView();
    if (!parent)
        return nullptr;

    if (auto c = Core::View::firstParentOfType(parent.get(), ViewType::DockWidget))
        return static_cast<Core::DockWidget *>(c);

    return nullptr;
}

/// The dock widgets that appear inside the already-serialized windows of @p layout
Vector<QString> dockWidgetNamesIn(const LayoutSaver::Layout &layout)
{
    Vector<QString> names;

    auto addGroups = [&names](const LayoutSaver::MultiSplitter &multiSplitter) {
        for (const auto &it : multiSplitter.groups) {
            for (const auto &dw : it.second.dockWidgets)
                names.push_back(dw->uniqueName);
        }
    };

    for (const auto &mw : layout.mainWindows) {
        addGroups(mw.multiSplitterLayout);
        for (const auto &it : mw.dockWidgetsPerSideBar) {
            for (const QString &name : it.second)
                names.push_back(name);
        }
    }

    for (const auto &fw : layout.floatingWindows)
        addGroups(fw.multiSplitterLayout);

    return names;
}

}

LayoutSaver::LayoutSaver(RestoreOptions options)
    : d(new Private(options))
{
    d->m_dockRegistry->registerLayoutSaver();
}

LayoutSaver::~LayoutSaver()
{
    d->m_dockRegistry->unregisterLayoutSaver();
    delete d;
}

bool LayoutSaver::saveToFile(const QString &jsonFilename)
{
    const QByteArray data = serializeLayout();
    if (data.isEmpty()) {
        // Refused to serialize. Don't leave an empty file behind.
        return false;
    }

    std::ofstream file(jsonFilename.toStdString(), std::ios::binary);
    if (!file.is_open()) {
        KDDW_ERROR("Failed to open {}", jsonFilename);
        return false;
    }

    file.write(data.constData(), data.size());
    file.close();
    return true;
}

bool LayoutSaver::restoreFromFile(const QString &jsonFilename)
{
    bool ok = false;
    const QByteArray data = Platform::instance()->readFile(jsonFilename, /*by-ref*/ ok);

    if (!ok)
        return false;

    return restoreLayout(data);
}

QByteArray LayoutSaver::serializeLayout() const
{
    if (!d->m_dockRegistry->isSane()) {
        KDDW_ERROR("Refusing to serialize this layout. Check previous warnings.");
        return {};
    }

    LayoutSaver::Layout layout;

    // Just a simplification. One less type of windows to handle.
    d->m_dockRegistry->ensureAllFloatingWidgetsAreMorphed();

    // Resolve the scope once. Placeholders reference floating windows by index into it,
    // so it has to be stable for the whole serialization.
    const SaveScope scope = d->resolveScope();

    if (!d->checkScopeIsRestorable(scope))
        return {};

    const auto mainWindows = d->m_dockRegistry->mainWindows(scope.mainWindowNames);
    layout.mainWindows.reserve(mainWindows.size());
    for (auto mainWindow : mainWindows)
        layout.mainWindows.push_back(mainWindow->serialize(scope));

    layout.floatingWindows.reserve(scope.floatingWindows.size());
    for (Core::FloatingWindow *floatingWindow : scope.floatingWindows) {
        layout.floatingWindows.push_back(floatingWindow->serialize(scope));
    }

    // Save the placeholder info. We do it last, as we also restore it last, since we need all items
    // to be created before restoring the placeholders

    const Vector<QString> namesInSavedWindows =
        scope.hasWindowSelection ? dockWidgetNamesIn(layout) : Vector<QString>();

    const Core::DockWidget::List dockWidgets = d->m_dockRegistry->dockwidgets();
    layout.allDockWidgets.reserve(dockWidgets.size());
    for (Core::DockWidget *dockWidget : dockWidgets) {
        if (dockWidget->skipsRestore())
            continue;

        if (scope.hasWindowSelection) {
            // Placeholders are already filtered down to the selected windows, so a dock widget
            // with none of them left has nothing to do with this save. Sidebar dock widgets are
            // the exception, hence also checking the windows themselves.
            //
            // A dock widget currently open in a window we didn't select is out of scope too,
            // even if it also left a stale placeholder behind in a selected one: restoring must
            // leave it alone, not close it.
            const bool inSavedWindow = namesInSavedWindows.contains(dockWidget->uniqueName());
            if (!inSavedWindow && dockWidget->isOpen())
                continue;

            auto lastPosition = dockWidget->d->lastPosition()->serialize(scope);
            if (!inSavedWindow && lastPosition.placeholders.isEmpty())
                continue;

            auto dw = dockWidget->d->serialize();
            dw->lastPosition = lastPosition;
            layout.allDockWidgets.push_back(dw);
        } else if (scope.matchesAffinity(dockWidget->affinities())) {
            auto dw = dockWidget->d->serialize();
            dw->lastPosition = dockWidget->d->lastPosition()->serialize(scope);
            layout.allDockWidgets.push_back(dw);
        }
    }

    // Closed dock widgets also have interesting things to save, like geometry and placeholder info
    const Vector<QString> savedNames = layout.dockWidgetNames();
    const Core::DockWidget::List closedDockWidgets = d->m_dockRegistry->closedDockwidgets(/*honourSkipped=*/true);
    layout.closedDockWidgets.reserve(closedDockWidgets.size());
    for (Core::DockWidget *dockWidget : closedDockWidgets) {
        const bool inScope = scope.hasWindowSelection
            ? savedNames.contains(dockWidget->uniqueName())
            : scope.matchesAffinity(dockWidget->affinities());
        if (inScope)
            layout.closedDockWidgets.push_back(dockWidget->d->serialize());
    }

    return layout.toJson();
}

bool LayoutSaver::restoreLayout(const QByteArray &data)
{
    LayoutSaver::DockWidget::s_dockWidgets.clear();
    d->clearRestoredProperty();
    if (data.isEmpty())
        return true;

    struct GroupCleanup
    {
        explicit GroupCleanup(LayoutSaver *saver)
            : m_saver(saver)
        {
        }

        ~GroupCleanup()
        {
            m_saver->d->deleteEmptyGroups();
        }

        GroupCleanup(const GroupCleanup &) = delete;
        GroupCleanup &operator=(const GroupCleanup) = delete;

        LayoutSaver *const m_saver;
    };

    GroupCleanup cleanup(this);
    LayoutSaver::Layout layout;
    if (!layout.fromJson(data)) {
        KDDW_ERROR("Failed to parse json data");
        return false;
    }

    if (!layout.isValid()) {
        return false;
    }

    layout.scaleSizes(d->m_restoreOptions);

    d->floatWidgetsWhichSkipRestore(layout.mainWindowNames());

    Private::RAIIIsRestoring isRestoring;

    // Hide all dockwidgets and unparent them from any layout before starting restore
    // We only close the stuff that the loaded JSON knows about. Unknown widgets might be newer.

    auto dockWidgetsToClose = d->m_dockRegistry->dockWidgets(layout.dockWidgetsToClose());
    auto mainWindowsToConsider = d->m_dockRegistry->mainWindows(layout.mainWindowNames());
    const bool isRestoringDocuments = ::isRestoringDocuments(mainWindowsToConsider, d->m_scope.affinities);

    if (!isDocumentMode(mainWindowsToConsider, d->m_scope.affinities))
        d->floatUnknownWidgets(layout);

    d->m_dockRegistry->clear(dockWidgetsToClose,
                             mainWindowsToConsider,
                             d->m_scope.affinities, isRestoringDocuments);

    // 1. Restore main windows

    for (const LayoutSaver::MainWindow &mw : std::as_const(layout.mainWindows)) {
        auto mainWindow = d->m_dockRegistry->mainWindowByName(mw.uniqueName);
        if (!mainWindow) {
            if (auto mwFunc = Config::self().mainWindowFactoryFunc()) {
                mainWindow = mwFunc(mw.uniqueName, mw.options);
            } else {
                KDDW_ERROR("Failed to restore layout create MainWindow with name {} first", mw.uniqueName);
                return false;
            }
        }

        if (!d->matchesAffinity(mainWindow->affinities()))
            continue;

        if (isRestoringDocuments) {
            // In 'document mode' we only restore the central tabs
            if (const auto centralGroup = mw.multiSplitterLayout.centralGroup(); !centralGroup.isNull) {
                for (const auto &savedDock : centralGroup.dockWidgets) {
                    Core::DockWidget *dw = d->m_dockRegistry->dockByName(
                        savedDock->uniqueName, DockRegistry::DockByNameFlag::CreateIfNotFound);
                    if (dw)
                        mainWindow->addDockWidgetAsTab(dw);
                }
            }
        } else {
            if (!(d->m_restoreOptions & InternalRestoreOption::SkipMainWindowGeometry) && !mainWindow->isInDockWidget()) {
                Window::Ptr window = mainWindow->view()->window();
                if (window->windowState() == WindowState::Maximized) {
                    // Restoring geometry needs to be done in normal state.
                    // Qt doesn't support restoring normal geometry on maximized windows.
                    window->setWindowState(WindowState::None);
                }

                d->deserializeWindowGeometry(mw, window);
                window->setWindowState(mw.windowState);
            }

            if (!mainWindow->deserialize(mw))
                return false;
        }
    }

    // 2. Restore FloatingWindows
    for (LayoutSaver::FloatingWindow &fw : layout.floatingWindows) {
        if (!d->matchesAffinity(fw.affinities) || fw.skipsRestore())
            continue;

        Core::MainWindow *parent = d->resolveParentMainWindow(fw);

        auto flags = static_cast<FloatingWindowFlags>(fw.flags);
        flags.setFlag(FloatingWindowFlag::StartsMinimized, int(fw.windowState) & int(WindowState::Minimized));

        auto floatingWindow =
            new Core::FloatingWindow({}, parent, flags);
        fw.floatingWindowInstance = floatingWindow;
        d->deserializeWindowGeometry(fw, floatingWindow->view()->window());
        if (!floatingWindow->deserialize(fw)) {
            KDDW_ERROR("Failed to deserialize floating window");
            return false;
        }
    }

    // 3. Restore closed dock widgets. They remain closed but acquire geometry and placeholder
    // properties
    for (const auto &dw : std::as_const(layout.closedDockWidgets)) {
        if (d->matchesAffinity(dw->affinities)) {
            Core::DockWidget::deserialize(dw);
        }
    }

    LayoutSaver::Private::s_unrestoredPositions.clear();
    LayoutSaver::Private::s_unrestoredProperties.clear();

    // 4. Restore the placeholder info, now that the Items have been created
    for (const auto &dw : std::as_const(layout.allDockWidgets)) {
        if (!d->matchesAffinity(dw->affinities))
            continue;

        if (Core::DockWidget *dockWidget = d->m_dockRegistry->dockByName(
                dw->uniqueName, DockRegistry::DockByNameFlag::ConsultRemapping)) {
            dockWidget->d->lastPosition()->deserialize(dw->lastPosition, dw->uniqueName);
        } else {
            KDDW_INFO("Couldn't find dock widget {}", dw->uniqueName);
            auto pos = std::make_shared<KDDockWidgets::Positions>();
            pos->deserialize(dw->lastPosition, dw->uniqueName);
            LayoutSaver::Private::s_unrestoredPositions[dw->uniqueName] = pos;
            LayoutSaver::Private::s_unrestoredProperties[dw->uniqueName] = dw->lastCloseReason;
        }
    }

    return true;
}

void LayoutSaver::addWindowToSave(Core::MainWindow *mainWindow)
{
    if (!mainWindow) {
        KDDW_ERROR("LayoutSaver::addWindowToSave: null main window");
        return;
    }

    addMainWindowToSave(mainWindow->uniqueName());
}

void LayoutSaver::addMainWindowToSave(const QString &uniqueName)
{
    if (uniqueName.isEmpty()) {
        KDDW_ERROR("LayoutSaver::addMainWindowToSave: empty name");
        return;
    }

    d->m_scope.hasWindowSelection = true;
    if (!d->m_scope.mainWindowNames.contains(uniqueName))
        d->m_scope.mainWindowNames.push_back(uniqueName);
}

void LayoutSaver::addWindowToSave(Core::FloatingWindow *floatingWindow)
{
    if (!floatingWindow) {
        KDDW_ERROR("LayoutSaver::addWindowToSave: null floating window");
        return;
    }

    d->m_scope.hasWindowSelection = true;
    if (!d->m_scope.floatingWindows.contains(floatingWindow))
        d->m_scope.floatingWindows.push_back(floatingWindow);
}

void LayoutSaver::addWindowToSave(Core::DockWidget *dockWidget)
{
    if (!dockWidget) {
        KDDW_ERROR("LayoutSaver::addWindowToSave: null dock widget");
        return;
    }

    if (auto fw = dockWidget->floatingWindow()) {
        addWindowToSave(fw);
    } else if (auto mw = dockWidget->mainWindow()) {
        addWindowToSave(mw);
    } else {
        KDDW_ERROR("LayoutSaver::addWindowToSave: dock widget {} is in no window",
                   dockWidget->uniqueName());
    }
}

void LayoutSaver::clearWindowsToSave()
{
    d->m_scope.hasWindowSelection = false;
    d->m_scope.mainWindowNames.clear();
    d->m_scope.floatingWindows.clear();
}

void LayoutSaver::setAffinityNames(const Vector<QString> &affinityNames)
{
    d->m_scope.affinities = affinityNames;
    if (affinityNames.contains(QString())) {
        // Any window with empty affinity will also be subject to save/restore
        d->m_scope.affinities.push_back(QString());
    }
}

LayoutSaver::Private *LayoutSaver::dptr() const
{
    return d;
}

Core::DockWidget::List LayoutSaver::restoredDockWidgets() const
{
    const Core::DockWidget::List &allDockWidgets = DockRegistry::self()->dockwidgets();
    Core::DockWidget::List result;
    result.reserve(allDockWidgets.size());
    for (Core::DockWidget *dw : allDockWidgets) {
        if (dw->d->m_wasRestored)
            result.push_back(dw);
    }

    return result;
}

void LayoutSaver::Private::clearRestoredProperty()
{
    const Core::DockWidget::List &allDockWidgets = DockRegistry::self()->dockwidgets();
    for (Core::DockWidget *dw : allDockWidgets) {
        dw->d->m_wasRestored = false;
    }
}

template<typename T>
void LayoutSaver::Private::deserializeWindowGeometry(const T &saved, Window::Ptr window)
{
    // Not simply calling QWidget::setGeometry() here.
    // For QtQuick we need to modify the QWindow's geometry.

    Rect geometry = saved.geometry;
    if (!isNormalWindowState(saved.windowState)) {
        // The window will be maximized. We first set its geometry to normal
        // Later it's maximized and will remember this value
        geometry = saved.normalGeometry;

        if (saved.screenIndex != Platform::instance()->screenNumberForPoint(geometry.topLeft())) {
            // Workaround bug #553. Window is maximized on screen 2 but its normal
            // geometry is on screen 1. Restoring normal geometry would move it to screen 2
            // To avoid that, we move its normal geometry to screen 2. Could be fixed
            // without workarounds if Qt supported QWindow::setNormalGeometry()
            window->setScreen(saved.screenIndex);
            if (auto screen = window->screen()) {
                // center is as good as any
                geometry.moveCenter(screen->geometry().center());
            }
        }
    }

    Core::FloatingWindow::ensureRectIsOnScreen(geometry);

    window->setGeometry(geometry);
    window->setVisible(saved.isVisible);
}

LayoutSaver::Private::Private(RestoreOptions options)
    : m_dockRegistry(DockRegistry::self())
    , m_restoreOptions(internalRestoreOptions(options))
{
}

/*static*/
void LayoutSaver::Private::restorePendingPositions(Core::DockWidget *dw)
{
    if (!dw)
        return;

    {
        auto it = s_unrestoredPositions.find(dw->uniqueName());
        if (it != s_unrestoredPositions.end()) {
            dw->d->m_lastPositions = it->second;
            s_unrestoredPositions.erase(it);
        }
    }

    {
        auto it = s_unrestoredProperties.find(dw->uniqueName());
        if (it != s_unrestoredProperties.end()) {
            dw->d->m_lastCloseReason = it->second;
            s_unrestoredProperties.erase(it);
        }
    }
}

void LayoutSaver::Private::addNestedMainWindows(SaveScope &scope) const
{
    // A main window nested in a dock widget is part of that dock widget's window, but is a
    // separate entry in the layout. Selecting the outer window has to pull it in, otherwise its
    // dock widgets come back unrestored. Loop until nothing new shows up, since nesting can go
    // deeper than one level.

    const auto mainWindows = m_dockRegistry->mainwindows();
    bool addedOne = true;
    while (addedOne) {
        addedOne = false;
        for (auto mainWindow : mainWindows) {
            if (scope.mainWindowNames.contains(mainWindow->uniqueName()))
                continue;

            auto host = hostDockWidget(mainWindow);
            if (!host)
                continue;

            const bool hostIsInScope = scope.floatingWindows.contains(host->floatingWindow())
                || (host->mainWindow()
                    && scope.mainWindowNames.contains(host->mainWindow()->uniqueName()));

            if (hostIsInScope) {
                scope.mainWindowNames.push_back(mainWindow->uniqueName());
                addedOne = true;
            }
        }
    }
}

bool LayoutSaver::Private::checkScopeIsRestorable(const SaveScope &scope) const
{
    if (scope.hasWindowSelection || scope.affinities.isEmpty())
        return true;

    const auto mainWindows = m_dockRegistry->mainwindows();

    // Document mode deliberately saves only the central group of its main window
    if (isDocumentMode(mainWindows, scope.affinities))
        return true;

    bool restorable = true;
    for (auto mainWindow : mainWindows) {
        const bool mainWindowMatches = scope.mainWindowNames.contains(mainWindow->uniqueName());
        const Core::DockWidget::List docks = mainWindow->layout()->dockWidgets();
        for (auto dw : docks) {
            if (dw->isPersistentCentralDockWidget())
                continue;

            if (scope.matchesAffinity(dw->affinities()) == mainWindowMatches)
                continue;

            KDDW_ERROR("Refusing to save: the affinity filter covers {} but not {}. A main "
                       "window's layout is saved whole or not at all. To save one window, use "
                       "LayoutSaver::addWindowToSave() instead of affinities.",
                       mainWindowMatches ? mainWindow->uniqueName() : dw->uniqueName(),
                       mainWindowMatches ? dw->uniqueName() : mainWindow->uniqueName());
            restorable = false;
        }
    }

    return restorable;
}

LayoutSaver::SaveScope LayoutSaver::Private::resolveScope() const
{
    SaveScope scope = m_scope;

    if (scope.hasWindowSelection) {
        // Drop selected windows that are gone, or were never there. Comparing against the
        // registry also means we never dereference a stale floating window pointer.
        const auto liveFloatingWindows =
            m_dockRegistry->floatingWindows(/*includeBeingDeleted=*/false, /*honourSkipped=*/true);
        scope.floatingWindows.clear();
        for (auto fw : std::as_const(m_scope.floatingWindows)) {
            if (liveFloatingWindows.contains(fw))
                scope.floatingWindows.push_back(fw);
        }

        scope.mainWindowNames.clear();
        for (const QString &name : std::as_const(m_scope.mainWindowNames)) {
            if (m_dockRegistry->mainWindowByName(name)) {
                scope.mainWindowNames.push_back(name);
            } else {
                KDDW_WARN("LayoutSaver: main window {} doesn't exist, not saving it", name);
            }
        }

        addNestedMainWindows(scope);
        return scope;
    }

    scope.floatingWindows = Core::floatingWindowsForAffinity(scope.affinities);

    const auto mainWindows = m_dockRegistry->mainwindows();
    scope.mainWindowNames.reserve(mainWindows.size());
    for (auto mainWindow : mainWindows) {
        if (scope.matchesAffinity(mainWindow->affinities()))
            scope.mainWindowNames.push_back(mainWindow->uniqueName());
    }

    return scope;
}

Core::MainWindow *
LayoutSaver::Private::resolveParentMainWindow(const LayoutSaver::FloatingWindow &fw) const
{
    if (!fw.parentMainWindowName.isEmpty()) {
        if (auto mw = m_dockRegistry->mainWindowByName(fw.parentMainWindowName))
            return mw;

        KDDW_WARN("Floating window references main window {}, which doesn't exist. Restoring it "
                  "without a parent.",
                  fw.parentMainWindowName);
        return nullptr;
    }

    // Layouts saved by <= v2.5 only have an index into the registry
    if (fw.parentIndex < 0)
        return nullptr;

    const auto mainWindows = m_dockRegistry->mainwindows();
    if (fw.parentIndex >= mainWindows.size()) {
        KDDW_WARN("Floating window references main window #{}, but only {} exist. Restoring it "
                  "without a parent.",
                  fw.parentIndex, mainWindows.size());
        return nullptr;
    }

    return mainWindows.at(fw.parentIndex);
}

bool LayoutSaver::SaveScope::matchesAffinity(const Vector<QString> &candidate) const
{
    return affinities.isEmpty() || candidate.isEmpty()
        || DockRegistry::self()->affinitiesMatch(affinities, candidate);
}

int LayoutSaver::SaveScope::indexOfFloatingWindow(const Core::FloatingWindow *fw) const
{
    return floatingWindows.indexOf(const_cast<Core::FloatingWindow *>(fw));
}

bool LayoutSaver::SaveScope::includesLayout(Core::Layout *layout) const
{
    if (!layout)
        return false;

    if (auto fw = layout->floatingWindow())
        return floatingWindows.contains(fw);

    if (auto mw = layout->mainWindow(/*honourNesting=*/true))
        return mainWindowNames.contains(mw->uniqueName());

    return false;
}

bool LayoutSaver::Private::matchesAffinity(const Vector<QString> &affinities) const
{
    return m_scope.matchesAffinity(affinities);
}

void LayoutSaver::Private::floatWidgetsWhichSkipRestore(const Vector<QString> &mainWindowNames)
{
    // Widgets with the LayoutSaverOptions::Skip flag skip restore completely.
    // If they were visible before they need to remain visible now.
    // If they were previously docked we need to float them, as the main window they were on will
    // be loading a new layout.

    const auto mainWindows = DockRegistry::self()->mainWindows(mainWindowNames);
    for (auto mw : mainWindows) {
        const Core::DockWidget::List docks = mw->layout()->dockWidgets();
        for (auto dw : docks) {
            if (dw->skipsRestore()) {
                dw->setFloating(true);
            }
        }
    }
}

void LayoutSaver::Private::floatUnknownWidgets(const LayoutSaver::Layout &layout)
{
    // The layout being restored might not know about every dock widget currently in the main
    // windows it covers, either because it's an old *.json file or because it was saved with a
    // selection of windows. Either way the main window layout is about to be cleared, so get
    // those dock widgets out of it first.

    const bool close = m_restoreOptions & InternalRestoreOption::CloseUnknownDockWidgets;

    const auto mainWindows = DockRegistry::self()->mainWindows(layout.mainWindowNames());
    for (auto mw : mainWindows) {
        const Core::DockWidget::List docks = mw->layout()->dockWidgets();
        for (Core::DockWidget *dw : docks) {
            if (!layout.containsDockWidget(dw->uniqueName())) {
                if (close)
                    dw->forceClose();
                else
                    dw->setFloating(true);
            }
        }
    }
}

void LayoutSaver::Private::deleteEmptyGroups() const
{
    // After a restore it can happen that some DockWidgets didn't exist, so weren't restored.
    // Delete their group now.

    const auto groups = m_dockRegistry->groups();
    for (auto group : groups) {
        if (!group->beingDeletedLater() && group->isEmpty() && !group->isCentralGroup()) {
            if (auto item = group->layoutItem()) {
                item->turnIntoPlaceholder();
            } else {
                // This doesn't happen. But the warning will make the tests fail if there's a regression.
                KDDW_ERROR("Expected item for group");
            }
            delete group;
        }
    }
}

bool LayoutSaver::restoreInProgress()
{
    return Private::s_restoreInProgress;
}

bool LayoutSaver::Layout::isValid() const
{
    if (serializationVersion != KDDOCKWIDGETS_SERIALIZATION_VERSION) {
        KDDW_ERROR("Serialization format is too old {}, current={}", serializationVersion, KDDOCKWIDGETS_SERIALIZATION_VERSION);
        return false;
    }

    for (auto &m : mainWindows) {
        if (!m.isValid())
            return false;
    }

    for (auto &m : floatingWindows) {
        if (!m.isValid())
            return false;
    }

    for (auto &m : allDockWidgets) {
        if (!m->isValid())
            return false;
    }

    return true;
}

Vector<QString> LayoutSaver::openedDockWidgetsInLayout(const QString &jsonFilename)
{
    bool ok = false;
    const QByteArray data = Platform::instance()->readFile(jsonFilename, /*by-ref*/ ok);

    if (!ok)
        return {};

    return openedDockWidgetsInLayout(data);
}

Vector<QString> LayoutSaver::openedDockWidgetsInLayout(const QByteArray &serialized)
{
    LayoutSaver::Layout layout;
    if (!layout.fromJson(serialized))
        return {};

    Vector<QString> names;
    names.reserve(layout.allDockWidgets.size()); // over-reserve so we have a single allocation

    for (const auto &dock : std::as_const(layout.allDockWidgets)) {
        auto it = std::find_if(layout.closedDockWidgets.cbegin(), layout.closedDockWidgets.cend(), [&dock](auto closedDock) {
            return dock->uniqueName == closedDock->uniqueName;
        });

        const bool itsOpen = it == layout.closedDockWidgets.cend();
        if (itsOpen)
            names.push_back(dock->uniqueName);
    }

    return names;
}

Vector<QString> LayoutSaver::sideBarDockWidgetsInLayout(const QString &jsonFilename)
{
    bool ok = false;
    const QByteArray data = Platform::instance()->readFile(jsonFilename, /*by-ref*/ ok);

    if (!ok)
        return {};

    return sideBarDockWidgetsInLayout(data);
}

Vector<QString> LayoutSaver::sideBarDockWidgetsInLayout(const QByteArray &serialized)
{
    LayoutSaver::Layout layout;
    if (!layout.fromJson(serialized))
        return {};

    Vector<QString> names;
    names.reserve(layout.allDockWidgets.size()); // over-reserve so we have a single allocation

    for (const auto &mainWindow : std::as_const(layout.mainWindows)) {
        for (const auto &it : mainWindow.dockWidgetsPerSideBar) {
            for (const auto &name : it.second)
                names.push_back(name);
        }
    }

    return names;
}

namespace KDDockWidgets {
static void to_json(nlohmann::json &j, const LayoutSaver::Layout &layout)
{
    j["serializationVersion"] = layout.serializationVersion;
    j["mainWindows"] = layout.mainWindows;
    j["floatingWindows"] = layout.floatingWindows;
    j["closedDockWidgets"] = ::dockWidgetNames(layout.closedDockWidgets);
    j["allDockWidgets"] = layout.allDockWidgets;
    j["screenInfo"] = layout.screenInfo;
}

static void from_json(const nlohmann::json &j, LayoutSaver::Layout &layout)
{
    layout.serializationVersion = j.value("serializationVersion", 0);
    layout.mainWindows = j.value("mainWindows", LayoutSaver::MainWindow::List {});
    layout.allDockWidgets = j.value("allDockWidgets", LayoutSaver::DockWidget::List {});

    layout.closedDockWidgets.clear();

    const auto closedDockWidgets = j.value("closedDockWidgets", Vector<QString>());
    for (const QString &name : closedDockWidgets) {
        layout.closedDockWidgets.push_back(
            LayoutSaver::DockWidget::dockWidgetForName(name));
    }

    layout.floatingWindows = j.value("floatingWindows", LayoutSaver::FloatingWindow::List {});
    layout.screenInfo = j.value("screenInfo", LayoutSaver::ScreenInfo::List {});
}
}

QByteArray LayoutSaver::Layout::toJson() const
{
    nlohmann::json json = *this;
    return QByteArray::fromStdString(json.dump(4));
}

bool LayoutSaver::Layout::fromJson(const QByteArray &jsonData)
{
    nlohmann::json json = nlohmann::json::parse(jsonData, nullptr, /*allow_exceptions=*/false);
    if (json.is_discarded()) {
        return false;
    }

    try {
        from_json(json, *this);
    } catch (const std::exception &e) {
        KDDW_ERROR("LayoutSaver::Layout::fromJson: Caught exception: {}", e.what());
        return false;
    } catch (...) {
        KDDW_ERROR("LayoutSaver::Layout::fromJson: Caught exception.");
        return false;
    }

    return true;
}

void LayoutSaver::Layout::scaleSizes(InternalRestoreOptions options)
{
    if (mainWindows.isEmpty())
        return;

    const bool skipsMainWindowGeometry = options & InternalRestoreOption::SkipMainWindowGeometry;
    if (!skipsMainWindowGeometry) {
        // No scaling to do. All windows will be restored with the exact size specified in the
        // saved JSON layouts.
        return;
    }

    // We won't restore MainWindow's geometry, we use whatever the user has now, meaning
    // we need to scale all dock widgets inside the layout, as the layout might not have
    // the same size as specified in the saved JSON layout
    for (auto &mw : mainWindows)
        mw.scaleSizes();


    // MainWindow has a different size than the one in JSON, so we also restore FloatingWindows
    // relatively to the user set new MainWindow size
    const bool useRelativeSizesForFloatingWidgets =
        options & InternalRestoreOption::RelativeFloatingWindowGeometry;

    if (useRelativeSizesForFloatingWidgets) {
        for (auto &fw : floatingWindows) {
            LayoutSaver::MainWindow mw = parentMainWindowOf(fw);
            if (mw.scalingInfo.isValid())
                fw.scaleSizes(mw.scalingInfo);
        }
    }

    const ScalingInfo firstScalingInfo = mainWindows.constFirst().scalingInfo;
    if (firstScalingInfo.isValid()) {
        for (auto &dw : allDockWidgets) {
            // TODO: Determine the best main window. This only interesting for closed dock
            // widget geometry which was previously floating. But they still have some other
            // main window as parent.
            dw->scaleSizes(firstScalingInfo);
        }
    }
}

LayoutSaver::MainWindow LayoutSaver::Layout::mainWindowForIndex(int index) const
{
    if (index < 0 || index >= mainWindows.size())
        return {};

    return mainWindows.at(index);
}

LayoutSaver::MainWindow LayoutSaver::Layout::mainWindowForName(const QString &uniqueName) const
{
    for (const auto &mw : mainWindows) {
        if (mw.uniqueName == uniqueName)
            return mw;
    }

    return {};
}

LayoutSaver::MainWindow
LayoutSaver::Layout::parentMainWindowOf(const LayoutSaver::FloatingWindow &fw) const
{
    if (!fw.parentMainWindowName.isEmpty())
        return mainWindowForName(fw.parentMainWindowName);

    return mainWindowForIndex(fw.parentIndex);
}

LayoutSaver::FloatingWindow LayoutSaver::Layout::floatingWindowForIndex(int index) const
{
    if (index < 0 || index >= floatingWindows.size())
        return {};

    return floatingWindows.at(index);
}

Vector<QString> LayoutSaver::Layout::mainWindowNames() const
{
    Vector<QString> names;
    names.reserve(mainWindows.size());
    for (const auto &mw : mainWindows) {
        names.push_back(mw.uniqueName);
    }

    return names;
}

Vector<QString> LayoutSaver::Layout::dockWidgetNames() const
{
    Vector<QString> names;
    names.reserve(allDockWidgets.size());
    for (const auto &dw : allDockWidgets) {
        names.push_back(dw->uniqueName);
    }

    return names;
}

Vector<QString> LayoutSaver::Layout::dockWidgetsToClose() const
{
    // Before restoring a layout we close all dock widgets, unless they're a floating window with
    // the DontCloseBeforeRestore flag

    Vector<QString> names;
    names.reserve(allDockWidgets.size());
    auto registry = DockRegistry::self();
    for (const auto &dw : allDockWidgets) {
        if (Core::DockWidget *dockWidget = registry->dockByName(dw->uniqueName)) {

            bool doClose = true;

            if (dockWidget->skipsRestore()) {
                if (auto fw = dockWidget->floatingWindow()) {
                    if (fw->allDockWidgetsHave(LayoutSaverOption::Skip)) {
                        // All dock widgets in this floating window skips float, so we can honour it
                        // for all.
                        doClose = false;
                    }
                }
            }

            if (doClose)
                names.push_back(dw->uniqueName);
        }
    }

    return names;
}

bool LayoutSaver::Layout::containsDockWidget(const QString &uniqueName) const
{
    return std::find_if(allDockWidgets.cbegin(), allDockWidgets.cend(),
                        [uniqueName](const std::shared_ptr<LayoutSaver::DockWidget> &dock) {
                            return dock->uniqueName == uniqueName;
                        })
        != allDockWidgets.cend();
}

bool LayoutSaver::Group::isValid() const
{
    if (isNull)
        return true;

    if (!geometry.isValid()) {
        KDDW_ERROR("Invalid geometry");
        return false;
    }

    if (id.isEmpty()) {
        KDDW_ERROR("Invalid id");
        return false;
    }

    if (!dockWidgets.isEmpty()) {
        if (currentTabIndex >= dockWidgets.size() || currentTabIndex < 0) {

            if (dockWidgets.isEmpty() || KDDockWidgets::Config::self().layoutSaverUsesStrictMode()) {
                KDDW_ERROR("Invalid tab index = {}, size = {}", currentTabIndex, dockWidgets.size());
                return false;
            }

            // Layout seems corrupted. Use 0 as current tab and let's continue.
            KDDW_WARN("Invalid tab index = {}, size = {}", currentTabIndex, dockWidgets.size());
            const_cast<LayoutSaver::Group *>(this)->currentTabIndex = 0;
        }
    }

    for (auto &dw : dockWidgets) {
        if (!dw->isValid())
            return false;
    }

    return true;
}

bool LayoutSaver::Group::hasSingleDockWidget() const
{
    return dockWidgets.size() == 1;
}

bool LayoutSaver::Group::skipsRestore() const
{
    return std::all_of(dockWidgets.cbegin(), dockWidgets.cend(),
                       [](LayoutSaver::DockWidget::Ptr dw) { return dw->skipsRestore(); });
}

LayoutSaver::DockWidget::Ptr LayoutSaver::Group::singleDockWidget() const
{
    if (!hasSingleDockWidget())
        return {};

    return dockWidgets.first();
}

bool LayoutSaver::DockWidget::isValid() const
{
    return !uniqueName.isEmpty();
}

void LayoutSaver::DockWidget::scaleSizes(const ScalingInfo &scalingInfo)
{
    lastPosition.scaleSizes(scalingInfo);
}

bool LayoutSaver::DockWidget::skipsRestore() const
{
    if (Core::DockWidget *dw = DockRegistry::self()->dockByName(uniqueName))
        return dw->skipsRestore();

    return false;
}

bool LayoutSaver::FloatingWindow::isValid() const
{
    if (!multiSplitterLayout.isValid())
        return false;

    if (!geometry.isValid()) {
        KDDW_ERROR("Invalid geometry");
        return false;
    }

    return true;
}

bool LayoutSaver::FloatingWindow::hasSingleDockWidget() const
{
    return multiSplitterLayout.hasSingleDockWidget();
}

LayoutSaver::DockWidget::Ptr LayoutSaver::FloatingWindow::singleDockWidget() const
{
    return multiSplitterLayout.singleDockWidget();
}

bool LayoutSaver::FloatingWindow::skipsRestore() const
{
    return multiSplitterLayout.skipsRestore();
}

void LayoutSaver::FloatingWindow::scaleSizes(const ScalingInfo &scalingInfo)
{
    scalingInfo.applyFactorsTo(/*by-ref*/ geometry);
}

bool LayoutSaver::MainWindow::isValid() const
{
    return multiSplitterLayout.isValid();
}

Vector<QString> LayoutSaver::MainWindow::dockWidgetsForSideBar(SideBarLocation loc) const
{
    auto it = dockWidgetsPerSideBar.find(loc);
    return it == dockWidgetsPerSideBar.cend() ? Vector<QString>() : it->second;
}

void LayoutSaver::MainWindow::scaleSizes()
{
    if (scalingInfo.isValid()) {
        // Doesn't happen, it's called only once
        assert(false);
        return;
    }

    scalingInfo = ScalingInfo(uniqueName, geometry, screenIndex);
}

bool LayoutSaver::MultiSplitter::isValid() const
{
    return layout.is_object() && !layout.empty();
}

bool LayoutSaver::MultiSplitter::hasSingleDockWidget() const
{
    return groups.size() == 1 && groups.cbegin()->second.hasSingleDockWidget();
}

LayoutSaver::DockWidget::Ptr LayoutSaver::MultiSplitter::singleDockWidget() const
{
    if (!hasSingleDockWidget())
        return {};

    const auto &group = groups.begin()->second;
    return group.singleDockWidget();
}

bool LayoutSaver::MultiSplitter::skipsRestore() const
{
    return std::all_of(groups.cbegin(), groups.cend(),
                       [](auto it) { return it.second.skipsRestore(); });
}

LayoutSaver::Group LayoutSaver::MultiSplitter::centralGroup() const
{
    for (const auto &[id, group] : groups) {
        if (group.options & FrameOption_IsCentralFrame)
            return group;
    }
    return {};
}

void LayoutSaver::Position::scaleSizes(const ScalingInfo &scalingInfo)
{
    scalingInfo.applyFactorsTo(/*by-ref*/ lastFloatingGeometry);
}

namespace {

Core::Screen::Ptr screenForMainWindow(Core::MainWindow *mw)
{
    return mw->view()->d->screen();
}

}

LayoutSaver::ScalingInfo::ScalingInfo(const QString &mainWindowId, Rect savedMainWindowGeo,
                                      int screenIndex)
{
    auto mainWindow = DockRegistry::self()->mainWindowByName(mainWindowId);
    if (!mainWindow) {
        KDDW_ERROR("Failed to find main window with name {}", mainWindowId);
        return;
    }

    if (!savedMainWindowGeo.isValid() || savedMainWindowGeo.isNull()) {
        KDDW_ERROR("Invalid saved main window geometry {}", savedMainWindowGeo);
        return;
    }

    if (!mainWindow->geometry().isValid() || mainWindow->geometry().isNull()) {
        KDDW_ERROR("Invalid main window geometry {}", mainWindow->geometry());
        return;
    }

    const int currentScreenIndex =
        Platform::instance()->screens().indexOf(screenForMainWindow(mainWindow));

    this->mainWindowName = mainWindowId;
    this->savedMainWindowGeometry = savedMainWindowGeo;
    realMainWindowGeometry =
        mainWindow->window()->d->windowGeometry(); // window() as our main window might be embedded
    widthFactor = double(realMainWindowGeometry.width()) / savedMainWindowGeo.width();
    heightFactor = double(realMainWindowGeometry.height()) / savedMainWindowGeo.height();
    mainWindowChangedScreen = currentScreenIndex != screenIndex;
}

void LayoutSaver::ScalingInfo::translatePos(Point &pt) const
{
    const int deltaX = pt.x() - savedMainWindowGeometry.x();
    const int deltaY = pt.y() - savedMainWindowGeometry.y();

    const double newDeltaX = deltaX * widthFactor;
    const double newDeltaY = deltaY * heightFactor;

    pt.setX(int(std::ceil(savedMainWindowGeometry.x() + newDeltaX)));
    pt.setY(int(std::ceil(savedMainWindowGeometry.y() + newDeltaY)));
}

void LayoutSaver::ScalingInfo::applyFactorsTo(Point &pt) const
{
    translatePos(pt);
}

void LayoutSaver::ScalingInfo::applyFactorsTo(Size &sz) const
{
    sz.setWidth(int(widthFactor * sz.width()));
    sz.setHeight(int(heightFactor * sz.height()));
}

void LayoutSaver::ScalingInfo::applyFactorsTo(Rect &rect) const
{
    if (rect.isEmpty())
        return;

    Point pos = rect.topLeft();
    Size size = rect.size();

    applyFactorsTo(/*by-ref*/ size);


    if (!mainWindowChangedScreen) {
        // Don't play with floating window position if the main window changed screen.
        // There's too many corner cases that push the floating windows out of bounds, and
        // we're not even considering monitors with different HDPI. We can support only the simple
        // case. For complex cases we'll try to guarantee the window is placed somewhere reasonable.
        applyFactorsTo(/*by-ref*/ pos);
    }

    rect.moveTopLeft(pos);
    rect.setSize(size);
}

LayoutSaver::Private::RAIIIsRestoring::RAIIIsRestoring()
{
    LayoutSaver::Private::s_restoreInProgress = true;
}

LayoutSaver::Private::RAIIIsRestoring::~RAIIIsRestoring()
{
    LayoutSaver::Private::s_restoreInProgress = false;
}
