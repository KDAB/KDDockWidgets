/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
#include "kddockwidgets/ViewFactory.h"
#include "nlohmann_qt_helpers.h"

#include "private/multisplitter/Item_p.h"
#include "private/LayoutSaver_p.h"
#include "DockRegistry.h"
#include "private/Logging_p.h"
#include "private/Position_p.h"
#include "private/Utils_p.h"
#include "Platform.h"

#include "controllers/Layout.h"
#include "controllers/Group.h"
#include "controllers/FloatingWindow.h"
#include "controllers/DockWidget.h"
#include "controllers/DockWidget_p.h"
#include "controllers/MainWindow.h"


#include <qmath.h>
#include <QDebug>
#include <QFile>

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
using namespace KDDockWidgets::Controllers;

QHash<QString, LayoutSaver::DockWidget::Ptr> LayoutSaver::DockWidget::s_dockWidgets;
LayoutSaver::Layout *LayoutSaver::Layout::s_currentLayoutBeingRestored = nullptr;


inline InternalRestoreOptions internalRestoreOptions(RestoreOptions options)
{
    if (options == RestoreOption_None) {
        return InternalRestoreOption::None;
    } else if (options == RestoreOption_RelativeToMainWindow) {
        return InternalRestoreOptions(InternalRestoreOption::SkipMainWindowGeometry)
            | InternalRestoreOption::RelativeFloatingWindowGeometry;
    } else {
        qWarning() << Q_FUNC_INFO << "Unknown options" << options;
        return {};
    }
}

bool LayoutSaver::Private::s_restoreInProgress = false;

namespace KDDockWidgets {
template<typename Type>
void to_json(nlohmann::json &json, const typename Type::List &list)
{
    for (const auto &l : list) {
        json.push_back(l);
    }
}

void to_json(nlohmann::json &json, const LayoutSaver::Group &f)
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
void from_json(const nlohmann::json &json, LayoutSaver::Group &f)
{
    f.id = json.value("id", QString());
    f.isNull = json.value("isNull", true);
    f.objectName = json.value("objectName", QString());
    f.geometry = json.value("geometry", QRect());
    f.options = json.value("options", QFlags<FrameOption>::Int {});
    f.currentTabIndex = json.value("currentTabIndex", 0);
    f.mainWindowUniqueName = json.value("mainWindowUniqueName", QString());

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

void to_json(nlohmann::json &json, const LayoutSaver::MultiSplitter &s)
{
    json["layout"] = s.layout;
    auto &groups = json["frames"];
    for (const auto &group : qAsConst(s.groups)) {
        groups[group.id.toStdString()] = group;
    }
}
void from_json(const nlohmann::json &json, LayoutSaver::MultiSplitter &s)
{
    s.groups.clear();
    s.layout = json.value("layout", QVariantMap());
    auto it = json.find("frames");
    if (it == json.end())
        return;
    if (it->is_null())
        return;

    auto &frms = *it;
    if (!frms.is_object())
        qWarning() << Q_FUNC_INFO << "Unexpected not object";

    for (const auto &kv : frms.items()) {
        QString key = QString::fromStdString(kv.key());
        auto group = kv.value().get<LayoutSaver::Group>();
        s.groups.insert(key, group);
    }
}

void to_json(nlohmann::json &json, const LayoutSaver::MainWindow &mw)
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
        const QStringList dockWidgets = mw.dockWidgetsPerSideBar.value(loc);
        if (!dockWidgets.isEmpty()) {
            std::string key = std::string("sidebar-") + std::to_string(( int )loc);
            json[key] = dockWidgets;
        }
    }
}

void from_json(const nlohmann::json &json, LayoutSaver::MainWindow &mw)
{
    mw.options = static_cast<decltype(mw.options)>(json.value("options", 0));
    mw.multiSplitterLayout = json.value("multiSplitterLayout", LayoutSaver::MultiSplitter());
    mw.uniqueName = json.value("uniqueName", QString());
    mw.geometry = json.value("geometry", QRect());
    mw.normalGeometry = json.value("normalGeometry", QRect());
    mw.screenIndex = json.value("screenIndex", 0);
    mw.screenSize = json.value("screenSize", QSize(800, 600));
    mw.isVisible = json.value("isVisible", false);
    mw.affinities = json.value("affinities", QStringList());
    mw.windowState = ( WindowState )json.value("windowState", 0);

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
            mw.dockWidgetsPerSideBar[loc] = val.get<QStringList>();
        }
    }
}

void to_json(nlohmann::json &json, const LayoutSaver::FloatingWindow &window)
{
    json["multiSplitterLayout"] = window.multiSplitterLayout;
    json["parentIndex"] = window.parentIndex;
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

void from_json(const nlohmann::json &json, LayoutSaver::FloatingWindow &window)
{
    window.multiSplitterLayout = json.value("multiSplitterLayout", LayoutSaver::MultiSplitter());
    window.parentIndex = json.value("parentIndex", -1);
    window.geometry = json.value("geometry", QRect());
    window.normalGeometry = json.value("normalGeometry", QRect());
    window.screenIndex = json.value("screenIndex", 0);
    window.screenSize = json.value("screenSize", QSize(800, 600));
    window.isVisible = json.value("isVisible", false);
    window.flags = json.value("flags", -1);
    window.windowState = ( WindowState )json.value("windowState", 0);
    window.affinities = json.value("affinities", QStringList());

    // Compatibility hack. Old json format had a single "affinityName" instead of an "affinities"
    // list:
    const QString affinityName = json.value("affinityName", QString());
    if (!affinityName.isEmpty() && !window.affinities.contains(affinityName)) {
        window.affinities.push_back(affinityName);
    }
}

void to_json(nlohmann::json &json, const LayoutSaver::ScreenInfo &screenInfo)
{
    json["index"] = screenInfo.index;
    json["geometry"] = screenInfo.geometry;
    json["name"] = screenInfo.name;
    json["devicePixelRatio"] = screenInfo.devicePixelRatio;
}
void from_json(const nlohmann::json &j, LayoutSaver::ScreenInfo &screenInfo)
{
    screenInfo.index = j.value("index", 0);
    screenInfo.geometry = j.value("geometry", QRect());
    screenInfo.name = j.value("name", QString());
    screenInfo.devicePixelRatio = j.value("devicePixelRatio", 1.0);
}

void to_json(nlohmann::json &json, const LayoutSaver::Placeholder &placeHolder)
{
    json["isFloatingWindow"] = placeHolder.isFloatingWindow;
    json["itemIndex"] = placeHolder.itemIndex;
    if (placeHolder.isFloatingWindow)
        json["indexOfFloatingWindow"] = placeHolder.indexOfFloatingWindow;
    else
        json["mainWindowUniqueName"] = placeHolder.mainWindowUniqueName;
}

void from_json(const nlohmann::json &json, LayoutSaver::Placeholder &placeHolder)
{
    placeHolder.isFloatingWindow = json.value("isFloatingWindow", false);
    placeHolder.itemIndex = json.value("itemIndex", 0);
    placeHolder.indexOfFloatingWindow = json.value("indexOfFloatingWindow", -1);
    placeHolder.mainWindowUniqueName = json.value("mainWindowUniqueName", QString());
}

void to_json(nlohmann::json &json, const LayoutSaver::Position &pos)
{
    json["lastFloatingGeometry"] = pos.lastFloatingGeometry;
    json["tabIndex"] = pos.tabIndex;
    json["wasFloating"] = pos.wasFloating;
    json["placeholders"] = pos.placeholders;
}

void from_json(const nlohmann::json &json, LayoutSaver::Position &pos)
{
    pos.lastFloatingGeometry = json.value("lastFloatingGeometry", QRect());
    pos.tabIndex = json.value("tabIndex", 0);
    pos.wasFloating = json.value("wasFloating", false);
    pos.placeholders = json.value("placeholders", LayoutSaver::Placeholder::List());
}

void to_json(nlohmann::json &json, const LayoutSaver::DockWidget &dw)
{
    if (!dw.affinities.isEmpty())
        json["affinities"] = dw.affinities;
    json["uniqueName"] = dw.uniqueName;
    json["lastPosition"] = dw.lastPosition;
}
void from_json(const nlohmann::json &json, LayoutSaver::DockWidget &dw)
{
    auto it = json.find("affinities");
    if (it != json.end())
        dw.affinities = it->get<QStringList>();

    dw.uniqueName = json.value("uniqueName", QString());
    if (dw.uniqueName.isEmpty())
        qWarning() << Q_FUNC_INFO << "Unexpected no uniqueName for dockWidget";

    dw.lastPosition = json.value("lastPosition", LayoutSaver::Position());
}

void to_json(nlohmann::json &json, const typename LayoutSaver::DockWidget::List &list)
{
    for (const auto &mw : list) {
        json.push_back(*mw);
    }
}
void from_json(const nlohmann::json &json, typename LayoutSaver::DockWidget::List &list)
{
    list.clear();
    for (const auto &v : json) {
        auto it = v.find("uniqueName");
        if (it == v.end()) {
            qWarning() << Q_FUNC_INFO << "Unexpected no uniqueName";
            continue;
        }
        QString uniqueName = it->get<QString>();
        auto dw = LayoutSaver::DockWidget::dockWidgetForName(uniqueName);
        from_json(v, *dw);
        list.push_back(dw);
    }
}

}

LayoutSaver::LayoutSaver(RestoreOptions options)
    : d(new Private(options))
{
}

LayoutSaver::~LayoutSaver()
{
    delete d;
}

bool LayoutSaver::saveToFile(const QString &jsonFilename)
{
    const QByteArray data = serializeLayout();

    QFile f(jsonFilename);
    if (!f.open(QIODevice::WriteOnly)) {
        qWarning() << Q_FUNC_INFO << "Failed to open" << jsonFilename << f.errorString();
        return false;
    }

    f.write(data);
    return true;
}

bool LayoutSaver::restoreFromFile(const QString &jsonFilename)
{
    QFile f(jsonFilename);
    if (!f.open(QIODevice::ReadOnly)) {
        qWarning() << Q_FUNC_INFO << "Failed to open" << jsonFilename << f.errorString();
        return false;
    }

    const QByteArray data = f.readAll();
    const bool result = restoreLayout(data);

    return result;
}

QByteArray LayoutSaver::serializeLayout() const
{
    if (!d->m_dockRegistry->isSane()) {
        qWarning() << Q_FUNC_INFO << "Refusing to serialize this layout. Check previous warnings.";
        return {};
    }

    LayoutSaver::Layout layout;

    // Just a simplification. One less type of windows to handle.
    d->m_dockRegistry->ensureAllFloatingWidgetsAreMorphed();

    const auto mainWindows = d->m_dockRegistry->mainwindows();
    layout.mainWindows.reserve(mainWindows.size());
    for (auto mainWindow : mainWindows) {
        if (d->matchesAffinity(mainWindow->affinities()))
            layout.mainWindows.push_back(mainWindow->serialize());
    }

    const QVector<Controllers::FloatingWindow *> floatingWindows =
        d->m_dockRegistry->floatingWindows();
    layout.floatingWindows.reserve(floatingWindows.size());
    for (Controllers::FloatingWindow *floatingWindow : floatingWindows) {
        if (d->matchesAffinity(floatingWindow->affinities()))
            layout.floatingWindows.push_back(floatingWindow->serialize());
    }

    // Closed dock widgets also have interesting things to save, like geometry and placeholder info
    const Controllers::DockWidget::List closedDockWidgets = d->m_dockRegistry->closedDockwidgets();
    layout.closedDockWidgets.reserve(closedDockWidgets.size());
    for (Controllers::DockWidget *dockWidget : closedDockWidgets) {
        if (d->matchesAffinity(dockWidget->affinities()))
            layout.closedDockWidgets.push_back(dockWidget->d->serialize());
    }

    // Save the placeholder info. We do it last, as we also restore it last, since we need all items
    // to be created before restoring the placeholders

    const Controllers::DockWidget::List dockWidgets = d->m_dockRegistry->dockwidgets();
    layout.allDockWidgets.reserve(dockWidgets.size());
    for (Controllers::DockWidget *dockWidget : dockWidgets) {
        if (d->matchesAffinity(dockWidget->affinities())) {
            auto dw = dockWidget->d->serialize();
            dw->lastPosition = dockWidget->d->lastPosition()->serialize();
            layout.allDockWidgets.push_back(dw);
        }
    }

    return layout.toJson();
}

bool LayoutSaver::restoreLayout(const QByteArray &data)
{
    d->clearRestoredProperty();
    if (data.isEmpty())
        return true;

    struct FrameCleanup
    {
        FrameCleanup(LayoutSaver *saver)
            : m_saver(saver)
        {
        }

        ~FrameCleanup()
        {
            m_saver->d->deleteEmptyGroups();
        }

        LayoutSaver *const m_saver;
    };

    FrameCleanup cleanup(this);
    LayoutSaver::Layout layout;
    if (!layout.fromJson(data)) {
        qWarning() << Q_FUNC_INFO << "Failed to parse json data";
        return false;
    }

    if (!layout.isValid()) {
        return false;
    }

    layout.scaleSizes(d->m_restoreOptions);

    d->floatWidgetsWhichSkipRestore(layout.mainWindowNames());
    d->floatUnknownWidgets(layout);

    Private::RAIIIsRestoring isRestoring;

    // Hide all dockwidgets and unparent them from any layout before starting restore
    // We only close the stuff that the loaded JSON knows about. Unknown widgets might be newer.

    d->m_dockRegistry->clear(d->m_dockRegistry->dockWidgets(layout.dockWidgetsToClose()),
                             d->m_dockRegistry->mainWindows(layout.mainWindowNames()),
                             d->m_affinityNames);

    // 1. Restore main windows
    for (const LayoutSaver::MainWindow &mw : qAsConst(layout.mainWindows)) {
        auto mainWindow = d->m_dockRegistry->mainWindowByName(mw.uniqueName);
        if (!mainWindow) {
            if (auto mwFunc = Config::self().mainWindowFactoryFunc()) {
                mainWindow = mwFunc(mw.uniqueName);
            } else {
                qWarning() << "Failed to restore layout create MainWindow with name"
                           << mw.uniqueName << "first";
                return false;
            }
        }

        if (!d->matchesAffinity(mainWindow->affinities()))
            continue;

        if (!(d->m_restoreOptions & InternalRestoreOption::SkipMainWindowGeometry)) {
            Window::Ptr window = mainWindow->view()->window();
            d->deserializeWindowGeometry(mw, window);
            if (mw.windowState != WindowState::None) {
                if (auto w = mainWindow->view()->window()) {
                    w->setWindowState(mw.windowState);
                }
            }
        }

        if (!mainWindow->deserialize(mw))
            return false;
    }

    // 2. Restore FloatingWindows
    for (LayoutSaver::FloatingWindow &fw : layout.floatingWindows) {
        if (!d->matchesAffinity(fw.affinities) || fw.skipsRestore())
            continue;

        auto parent =
            fw.parentIndex == -1 ? nullptr : DockRegistry::self()->mainwindows().at(fw.parentIndex);

        auto floatingWindow =
            new Controllers::FloatingWindow({}, parent, static_cast<FloatingWindowFlags>(fw.flags));
        fw.floatingWindowInstance = floatingWindow;
        d->deserializeWindowGeometry(fw, floatingWindow->view()->window());
        if (!floatingWindow->deserialize(fw)) {
            qWarning() << Q_FUNC_INFO << "Failed to deserialize floating window";
            return false;
        }
    }

    // 3. Restore closed dock widgets. They remain closed but acquire geometry and placeholder
    // properties
    for (const auto &dw : qAsConst(layout.closedDockWidgets)) {
        if (d->matchesAffinity(dw->affinities)) {
            Controllers::DockWidget::deserialize(dw);
        }
    }

    // 4. Restore the placeholder info, now that the Items have been created
    for (const auto &dw : qAsConst(layout.allDockWidgets)) {
        if (!d->matchesAffinity(dw->affinities))
            continue;

        if (Controllers::DockWidget *dockWidget = d->m_dockRegistry->dockByName(
                dw->uniqueName, DockRegistry::DockByNameFlag::ConsultRemapping)) {
            dockWidget->d->lastPosition()->deserialize(dw->lastPosition);
        } else {
            qWarning() << Q_FUNC_INFO << "Couldn't find dock widget" << dw->uniqueName;
        }
    }

    return true;
}

void LayoutSaver::setAffinityNames(const QStringList &affinityNames)
{
    d->m_affinityNames = affinityNames;
    if (affinityNames.contains(QString())) {
        // Any window with empty affinity will also be subject to save/restore
        d->m_affinityNames << QString();
    }
}

LayoutSaver::Private *LayoutSaver::dptr() const
{
    return d;
}

Controllers::DockWidget::List LayoutSaver::restoredDockWidgets() const
{
    const Controllers::DockWidget::List &allDockWidgets = DockRegistry::self()->dockwidgets();
    Controllers::DockWidget::List result;
    result.reserve(allDockWidgets.size());
    for (Controllers::DockWidget *dw : allDockWidgets) {
        if (dw->property("kddockwidget_was_restored").toBool())
            result.push_back(dw);
    }

    return result;
}

void LayoutSaver::Private::clearRestoredProperty()
{
    const Controllers::DockWidget::List &allDockWidgets = DockRegistry::self()->dockwidgets();
    for (Controllers::DockWidget *dw : allDockWidgets) {
        dw->setProperty("kddockwidget_was_restored", QVariant());
    }
}

template<typename T>
void LayoutSaver::Private::deserializeWindowGeometry(const T &saved, Window::Ptr window)
{
    // Not simply calling QWidget::setGeometry() here.
    // For QtQuick we need to modify the QWindow's geometry.

    QRect geometry = saved.geometry;
    if (!isNormalWindowState(saved.windowState)) {
        // The window will be maximized. We first set its geometry to normal
        // Later it's maximized and will remember this value
        geometry = saved.normalGeometry;
    }

    Controllers::FloatingWindow::ensureRectIsOnScreen(geometry);

    window->setGeometry(geometry);
    window->setVisible(saved.isVisible);
}

LayoutSaver::Private::Private(RestoreOptions options)
    : m_dockRegistry(DockRegistry::self())
    , m_restoreOptions(internalRestoreOptions(options))
{
}

bool LayoutSaver::Private::matchesAffinity(const QStringList &affinities) const
{
    return m_affinityNames.isEmpty() || affinities.isEmpty()
        || DockRegistry::self()->affinitiesMatch(m_affinityNames, affinities);
}

void LayoutSaver::Private::floatWidgetsWhichSkipRestore(const QStringList &mainWindowNames)
{
    // Widgets with the LayoutSaverOptions::Skip flag skip restore completely.
    // If they were visible before they need to remain visible now.
    // If they were previously docked we need to float them, as the main window they were on will
    // be loading a new layout.

    for (auto mw : DockRegistry::self()->mainWindows(mainWindowNames)) {
        const Controllers::DockWidget::List docks = mw->layout()->dockWidgets();
        for (auto dw : docks) {
            if (dw->skipsRestore()) {
                dw->setFloating(true);
            }
        }
    }
}

void LayoutSaver::Private::floatUnknownWidgets(const LayoutSaver::Layout &layout)
{
    // An old *.json layout file might have not know about existing dock widgets
    // When restoring such a file, we need to float any visible dock widgets which it doesn't know
    // about so we can restore the MainWindow layout properly

    for (auto mw : DockRegistry::self()->mainWindows(layout.mainWindowNames())) {
        const Controllers::DockWidget::List docks = mw->layout()->dockWidgets();
        for (Controllers::DockWidget *dw : docks) {
            if (!layout.containsDockWidget(dw->uniqueName())) {
                dw->setFloating(true);
            }
        }
    }
}

void LayoutSaver::Private::deleteEmptyGroups()
{
    // After a restore it can happen that some DockWidgets didn't exist, so weren't restored.
    // Delete their group now.

    for (auto group : m_dockRegistry->groups()) {
        if (!group->beingDeletedLater() && group->isEmpty() && !group->isCentralFrame())
            delete group;
    }
}

std::unique_ptr<QSettings> LayoutSaver::Private::settings() const
{
    auto settings = std::unique_ptr<QSettings>(new QSettings(
        Platform::instance()->organizationName(), Platform::instance()->applicationName()));
    settings->beginGroup(QStringLiteral("KDDockWidgets::LayoutSaver"));

    return settings;
}

bool LayoutSaver::restoreInProgress()
{
    return Private::s_restoreInProgress;
}

bool LayoutSaver::Layout::isValid() const
{
    if (serializationVersion != KDDOCKWIDGETS_SERIALIZATION_VERSION) {
        qWarning() << Q_FUNC_INFO << "Serialization format is too old" << serializationVersion
                   << "current=" << KDDOCKWIDGETS_SERIALIZATION_VERSION;
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

namespace KDDockWidgets {
void to_json(nlohmann::json &j, const LayoutSaver::Layout &layout)
{
    j["serializationVersion"] = layout.serializationVersion;
    j["mainWindows"] = layout.mainWindows;
    j["floatingWindows"] = layout.floatingWindows;
    j["closedDockWidgets"] = ::dockWidgetNames(layout.closedDockWidgets);
    j["allDockWidgets"] = layout.allDockWidgets;
    j["screenInfo"] = layout.screenInfo;
}

void from_json(const nlohmann::json &j, LayoutSaver::Layout &layout)
{
    layout.serializationVersion = j.value("serializationVersion", 0);
    layout.mainWindows = j.value("mainWindows", LayoutSaver::MainWindow::List {});
    layout.allDockWidgets = j.value("allDockWidgets", LayoutSaver::DockWidget::List {});

    layout.closedDockWidgets.clear();
    const QVariantList closedDockWidgetsV = j.value("closedDockWidgets", QVariantList {});
    for (const QVariant &v : closedDockWidgetsV) {
        layout.closedDockWidgets.push_back(
            LayoutSaver::DockWidget::dockWidgetForName(v.toString()));
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
    nlohmann::json json = nlohmann::json::parse(jsonData, nullptr, /*DisableExceptions=*/true);
    if (json.is_discarded()) {
        return false;
    }
    from_json(json, *this);
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
            LayoutSaver::MainWindow mw = mainWindowForIndex(fw.parentIndex);
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

LayoutSaver::FloatingWindow LayoutSaver::Layout::floatingWindowForIndex(int index) const
{
    if (index < 0 || index >= floatingWindows.size())
        return {};

    return floatingWindows.at(index);
}

QStringList LayoutSaver::Layout::mainWindowNames() const
{
    QStringList names;
    names.reserve(mainWindows.size());
    for (const auto &mw : mainWindows) {
        names << mw.uniqueName;
    }

    return names;
}

QStringList LayoutSaver::Layout::dockWidgetNames() const
{
    QStringList names;
    names.reserve(allDockWidgets.size());
    for (const auto &dw : allDockWidgets) {
        names << dw->uniqueName;
    }

    return names;
}

QStringList LayoutSaver::Layout::dockWidgetsToClose() const
{
    // Before restoring a layout we close all dock widgets, unless they're a floating window with
    // the DontCloseBeforeRestore flag

    QStringList names;
    names.reserve(allDockWidgets.size());
    auto registry = DockRegistry::self();
    for (const auto &dw : allDockWidgets) {
        if (Controllers::DockWidget *dockWidget = registry->dockByName(dw->uniqueName)) {

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
                names << dw->uniqueName;
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
        qWarning() << Q_FUNC_INFO << "Invalid geometry";
        return false;
    }

    if (id.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "Invalid id";
        return false;
    }

    if (!dockWidgets.isEmpty()) {
        if (currentTabIndex >= dockWidgets.size() || currentTabIndex < 0) {
            qWarning() << Q_FUNC_INFO << "Invalid tab index" << currentTabIndex
                       << dockWidgets.size();
            return false;
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
    if (Controllers::DockWidget *dw = DockRegistry::self()->dockByName(uniqueName))
        return dw->skipsRestore();

    return false;
}

bool LayoutSaver::FloatingWindow::isValid() const
{
    if (!multiSplitterLayout.isValid())
        return false;

    if (!geometry.isValid()) {
        qWarning() << Q_FUNC_INFO << "Invalid geometry";
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
    if (!multiSplitterLayout.isValid())
        return false;

    return true;
}

void LayoutSaver::MainWindow::scaleSizes()
{
    if (scalingInfo.isValid()) {
        // Doesn't happen, it's called only once
        Q_ASSERT(false);
        return;
    }

    scalingInfo = ScalingInfo(uniqueName, geometry, screenIndex);
}

bool LayoutSaver::MultiSplitter::isValid() const
{
    if (layout.isEmpty())
        return false;

    /*if (!size.isValid()) {
        qWarning() << Q_FUNC_INFO << "Invalid size";
        return false;
    }*/

    return true;
}

bool LayoutSaver::MultiSplitter::hasSingleDockWidget() const
{
    return groups.size() == 1 && groups.cbegin()->hasSingleDockWidget();
}

LayoutSaver::DockWidget::Ptr LayoutSaver::MultiSplitter::singleDockWidget() const
{
    if (!hasSingleDockWidget())
        return {};

    return groups.cbegin()->singleDockWidget();
}

bool LayoutSaver::MultiSplitter::skipsRestore() const
{
    return std::all_of(groups.cbegin(), groups.cend(),
                       [](const LayoutSaver::Group &group) { return group.skipsRestore(); });
}

void LayoutSaver::Position::scaleSizes(const ScalingInfo &scalingInfo)
{
    scalingInfo.applyFactorsTo(/*by-ref*/ lastFloatingGeometry);
}

QVariantMap LayoutSaver::Placeholder::toVariantMap() const
{
    QVariantMap map;
    map.insert(QStringLiteral("isFloatingWindow"), isFloatingWindow);
    map.insert(QStringLiteral("itemIndex"), itemIndex);

    if (isFloatingWindow)
        map.insert(QStringLiteral("indexOfFloatingWindow"), indexOfFloatingWindow);
    else
        map.insert(QStringLiteral("mainWindowUniqueName"), mainWindowUniqueName);

    return map;
}

void LayoutSaver::Placeholder::fromVariantMap(const QVariantMap &map)
{
    isFloatingWindow = map.value(QStringLiteral("isFloatingWindow")).toBool();
    indexOfFloatingWindow = map.value(QStringLiteral("indexOfFloatingWindow"), -1).toInt();
    itemIndex = map.value(QStringLiteral("itemIndex")).toInt();
    mainWindowUniqueName = map.value(QStringLiteral("mainWindowUniqueName")).toString();
}

static Screen::Ptr screenForMainWindow(Controllers::MainWindow *mw)
{
    return mw->view()->screen();
}

LayoutSaver::ScalingInfo::ScalingInfo(const QString &mainWindowId, QRect savedMainWindowGeo,
                                      int screenIndex)
{
    auto mainWindow = DockRegistry::self()->mainWindowByName(mainWindowId);
    if (!mainWindow) {
        qWarning() << Q_FUNC_INFO << "Failed to find main window with name" << mainWindowName;
        return;
    }

    if (!savedMainWindowGeo.isValid() || savedMainWindowGeo.isNull()) {
        qWarning() << Q_FUNC_INFO << "Invalid saved main window geometry" << savedMainWindowGeo;
        return;
    }

    if (!mainWindow->geometry().isValid() || mainWindow->geometry().isNull()) {
        qWarning() << Q_FUNC_INFO << "Invalid main window geometry" << mainWindow->geometry();
        return;
    }

    const int currentScreenIndex =
        Platform::instance()->screens().indexOf(screenForMainWindow(mainWindow));

    this->mainWindowName = mainWindowId;
    this->savedMainWindowGeometry = savedMainWindowGeo;
    realMainWindowGeometry =
        mainWindow->window()->geometry(); // window() as our main window might be embedded
    widthFactor = double(realMainWindowGeometry.width()) / savedMainWindowGeo.width();
    heightFactor = double(realMainWindowGeometry.height()) / savedMainWindowGeo.height();
    mainWindowChangedScreen = currentScreenIndex != screenIndex;
}

void LayoutSaver::ScalingInfo::translatePos(QPoint &pt) const
{
    const int deltaX = pt.x() - savedMainWindowGeometry.x();
    const int deltaY = pt.y() - savedMainWindowGeometry.y();

    const double newDeltaX = deltaX * widthFactor;
    const double newDeltaY = deltaY * heightFactor;

    pt.setX(qCeil(savedMainWindowGeometry.x() + newDeltaX));
    pt.setY(qCeil(savedMainWindowGeometry.y() + newDeltaY));
}

void LayoutSaver::ScalingInfo::applyFactorsTo(QPoint &pt) const
{
    translatePos(pt);
}

void LayoutSaver::ScalingInfo::applyFactorsTo(QSize &sz) const
{
    sz.setWidth(int(widthFactor * sz.width()));
    sz.setHeight(int(heightFactor * sz.height()));
}

void LayoutSaver::ScalingInfo::applyFactorsTo(QRect &rect) const
{
    if (rect.isEmpty())
        return;

    QPoint pos = rect.topLeft();
    QSize size = rect.size();

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
