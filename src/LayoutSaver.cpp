/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file
 * @brief Class to save and restore dock widget layouts.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "LayoutSaver.h"
#include "LayoutSaver_p.h"
#include "Config.h"
#include "DockRegistry_p.h"
#include "DockWidgetBase.h"
#include "DropArea_p.h"
#include "Logging_p.h"
#include "Frame_p.h"
#include "LastPosition_p.h"
#include "multisplitter/Anchor_p.h"
#include "multisplitter/Item_p.h"
#include "FrameworkWidgetFactory.h"

#include <qmath.h>
#include <QDebug>
#include <QSettings>
#include <QApplication>
#include <QFile>

#include <memory>

using namespace KDDockWidgets;

QHash<QString, LayoutSaver::DockWidget::Ptr> LayoutSaver::DockWidget::s_dockWidgets;
LayoutSaver::Layout* LayoutSaver::Layout::s_currentLayoutBeingRestored = nullptr;

static QVariantMap sizeToMap(QSize sz)
{
    QVariantMap map;
    map.insert(QStringLiteral("width"), sz.width());
    map.insert(QStringLiteral("height"), sz.height());

    return map;
}

static QVariantMap rectToMap(QRect rect)
{
    QVariantMap map;
    map.insert(QStringLiteral("x"), rect.x());
    map.insert(QStringLiteral("y"), rect.y());
    map.insert(QStringLiteral("width"), rect.width());
    map.insert(QStringLiteral("height"), rect.height());

    return map;
}

static QSize mapToSize(const QVariantMap &map)
{
    return { map.value(QStringLiteral("width")).toInt(),
             map.value(QStringLiteral("height")).toInt() };
}

static QRect mapToRect(const QVariantMap &map)
{
    return QRect(map.value(QStringLiteral("x")).toInt(),
                 map.value(QStringLiteral("y")).toInt(),
                 map.value(QStringLiteral("width")).toInt(),
                 map.value(QStringLiteral("height")).toInt());
}

class KDDockWidgets::LayoutSaver::Private
{
public:

    struct RAIIIsRestoring
    {
        RAIIIsRestoring()
        {
            LayoutSaver::Private::s_restoreInProgress = true;
        }

        ~RAIIIsRestoring()
        {
            LayoutSaver::Private::s_restoreInProgress = false;
        }
        Q_DISABLE_COPY(RAIIIsRestoring)
    };

    Private(RestoreOptions options)
        : m_dockRegistry(DockRegistry::self())
        , m_restoreOptions(options)
    {
    }

    bool matchesAffinity(const QString &affinityName) const {
        return m_affinityNames.isEmpty() || affinityName.isEmpty() || m_affinityNames.contains(affinityName);
    }

    template <typename T>
    void deserializeWindowGeometry(const T &saved, QWidgetOrQuick *topLevel);
    void deleteEmptyFrames();
    void clearRestoredProperty();

    std::unique_ptr<QSettings> settings() const;
    DockRegistry *const m_dockRegistry;
    const RestoreOptions m_restoreOptions;
    QStringList m_affinityNames;
    static bool s_restoreInProgress;
};

bool LayoutSaver::Private::s_restoreInProgress = false;

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

    const MainWindowBase::List mainWindows = d->m_dockRegistry->mainwindows();
    layout.mainWindows.reserve(mainWindows.size());
    for (MainWindowBase *mainWindow : mainWindows) {
        if (d->matchesAffinity(mainWindow->affinityName()))
            layout.mainWindows.push_back(mainWindow->serialize());
    }

    const QVector<KDDockWidgets::FloatingWindow*> floatingWindows = d->m_dockRegistry->nestedwindows();
    layout.floatingWindows.reserve(floatingWindows.size());
    for (KDDockWidgets::FloatingWindow *floatingWindow : floatingWindows) {
        if (d->matchesAffinity(floatingWindow->affinityName()))
            layout.floatingWindows.push_back(floatingWindow->serialize());
    }

    // Closed dock widgets also have interesting things to save, like geometry and placeholder info
    const DockWidgetBase::List closedDockWidgets = d->m_dockRegistry->closedDockwidgets();
    layout.closedDockWidgets.reserve(closedDockWidgets.size());
    for (DockWidgetBase *dockWidget : closedDockWidgets) {
        if (d->matchesAffinity(dockWidget->affinityName()))
            layout.closedDockWidgets.push_back(dockWidget->serialize());
    }

    // Save the placeholder info. We do it last, as we also restore it last, since we need all items to be created
    // before restoring the placeholders

    const DockWidgetBase::List dockWidgets = d->m_dockRegistry->dockwidgets();
    layout.allDockWidgets.reserve(dockWidgets.size());
    for (DockWidgetBase *dockWidget : dockWidgets) {
        if (d->matchesAffinity(dockWidget->affinityName())) {
            auto dw = dockWidget->serialize();
            dw->lastPosition = dockWidget->lastPosition()->serialize();
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

    struct EnsureItemsAtCorrectPlace {

        EnsureItemsAtCorrectPlace(LayoutSaver *ls)
            : layoutSaver(ls)
        {
        }

        ~EnsureItemsAtCorrectPlace()
        {
            // When using RestoreOption_RelativeToMainWindow we'll have many rounding errors so the layout won't be exact.
            // Make sure to run a relayout at the end
            // (Using RAII to make sure it runs after Private::RAIIIsRestoring went out of scope, since "isRestoring= true" inhibits relayout
            if (ensure) {
                for (auto layout : DockRegistry::self()->layouts()) {
                    if (layoutSaver->d->matchesAffinity(layout->affinityName()))
                        layout->redistributeSpace();
                }
            }
        }

        bool ensure = false;
        LayoutSaver *const layoutSaver;
    };

    EnsureItemsAtCorrectPlace ensureItemsAtCorrectPlace(this);
    Private::RAIIIsRestoring isRestoring;

    struct FrameCleanup {
        FrameCleanup(LayoutSaver *saver)
            : m_saver(saver)
        {
        }

        ~FrameCleanup()
        {
            m_saver->d->deleteEmptyFrames();
        }

        LayoutSaver *const m_saver;
    };

    FrameCleanup cleanup(this);
    LayoutSaver::Layout layout;
    if (!layout.fromJson(data)) {
        qWarning() << Q_FUNC_INFO << "Failed to parse json data";
        return false;
    }

    if (d->m_restoreOptions & RestoreOption_RelativeToMainWindow)
        layout.scaleSizes();

    // Hide all dockwidgets and unparent them from any layout before starting restore
    d->m_dockRegistry->clear(d->m_affinityNames, /*deleteStaticAnchors=*/true);

    // 1. Restore main windows
    for (const LayoutSaver::MainWindow &mw : qAsConst(layout.mainWindows)) {
        MainWindowBase *mainWindow = d->m_dockRegistry->mainWindowByName(mw.uniqueName);
        if (!mainWindow) {
            qWarning() << "Failed to restore layout create MainWindow with name" << mw.uniqueName << "first";
            return false;
        }

        if (!d->matchesAffinity(mainWindow->affinityName()))
            continue;

        if (!(d->m_restoreOptions & RestoreOption_RelativeToMainWindow))
            d->deserializeWindowGeometry(mw, mainWindow->window()); // window(), as the MainWindow can be embedded

        if (!mainWindow->deserialize(mw))
            return false;
    }

    // 2. Restore FloatingWindows
    for (const LayoutSaver::FloatingWindow &fw : qAsConst(layout.floatingWindows)) {
        if (!d->matchesAffinity(fw.affinityName))
            continue;

        MainWindowBase *parent = fw.parentIndex == -1 ? nullptr
                                                      : DockRegistry::self()->mainwindows().at(fw.parentIndex);

        auto floatingWindow = Config::self().frameworkWidgetFactory()->createFloatingWindow(parent);
        d->deserializeWindowGeometry(fw, floatingWindow);
        if (!floatingWindow->deserialize(fw)) {
            return false;
        }
    }

    // 3. Restore closed dock widgets. They remain closed but acquire geometry and placeholder properties
    for (const auto &dw : qAsConst(layout.closedDockWidgets)) {
        if (d->matchesAffinity(dw->affinityName)) {
            DockWidgetBase::deserialize(dw);
        }
    }

    // 4. Restore the placeholder info, now that the Items have been created
    for (const auto &dw : qAsConst(layout.allDockWidgets)) {
        if (!d->matchesAffinity(dw->affinityName))
            continue;

        if (DockWidgetBase *dockWidget = d->m_dockRegistry->dockByName(dw->uniqueName)) {
            dockWidget->lastPosition()->deserialize(dw->lastPosition);
        } else {
            qWarning() << Q_FUNC_INFO << "Couldn't find dock widget" << dw->uniqueName;
        }
    }

    // our raii class will run when
    ensureItemsAtCorrectPlace.ensure = d->m_restoreOptions & RestoreOption_RelativeToMainWindow;

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

DockWidgetBase::List LayoutSaver::restoredDockWidgets() const
{
    const DockWidgetBase::List &allDockWidgets = DockRegistry::self()->dockwidgets();
    DockWidgetBase::List result;
    result.reserve(allDockWidgets.size());
    for (DockWidgetBase *dw : allDockWidgets) {
        if (dw->property("kddockwidget_was_restored").toBool())
            result.push_back(dw);
    }

    return result;

}

void LayoutSaver::Private::clearRestoredProperty()
{
    const DockWidgetBase::List &allDockWidgets = DockRegistry::self()->dockwidgets();
    for (DockWidgetBase *dw : allDockWidgets) {
        dw->setProperty("kddockwidget_was_restored", QVariant());
    }
}

template <typename T>
void LayoutSaver::Private::deserializeWindowGeometry(const T &saved, QWidgetOrQuick *topLevel)
{
    topLevel->setGeometry(saved.geometry);
    topLevel->setVisible(saved.isVisible);
}

void LayoutSaver::Private::deleteEmptyFrames()
{
    // After a restore it can happen that some DockWidgets didn't exist, so weren't restored.
    // Delete their frame now.

    for (auto frame : m_dockRegistry->frames()) {
        if (!frame->beingDeletedLater() && frame->isEmpty() && !frame->isCentralFrame())
            delete frame;
    }
}

std::unique_ptr<QSettings> LayoutSaver::Private::settings() const
{
    auto settings = std::unique_ptr<QSettings>(new QSettings(qApp->organizationName(),
                                                             qApp->applicationName()));
    settings->beginGroup(QStringLiteral("KDDockWidgets::LayoutSaver"));

    return settings;
}

bool LayoutSaver::restoreInProgress()
{
    return Private::s_restoreInProgress;
}

bool LayoutSaver::Layout::isValid() const
{
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

bool LayoutSaver::Layout::fillFrom(const QByteArray &serialized)
{
    QDataStream ds(serialized);
    ds >> this;

    if (serializationVersion > KDDOCKWIDGETS_SERIALIZATION_VERSION) {
        qWarning() << "Unsupported serialization version. Got=" << serializationVersion
                   << "; expected equal or less than" << KDDOCKWIDGETS_SERIALIZATION_VERSION;
        return false;
    }

    return true;
}

QByteArray LayoutSaver::Layout::toJson() const
{
    QJsonDocument doc = QJsonDocument::fromVariant(toVariantMap());
    return doc.toJson();
}

bool LayoutSaver::Layout::fromJson(const QByteArray &jsonData)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);
    if (error.error == QJsonParseError::NoError)  {
        fromVariantMap(doc.toVariant().toMap());
        return true;
    }

    return false;
}

QVariantMap LayoutSaver::Layout::toVariantMap() const
{
    QVariantMap map;
    map.insert(QStringLiteral("serializationVersion"), serializationVersion);
    map.insert(QStringLiteral("mainWindows"), toVariantList<LayoutSaver::MainWindow>(mainWindows));
    map.insert(QStringLiteral("floatingWindows"), toVariantList<LayoutSaver::FloatingWindow>(floatingWindows));
    map.insert(QStringLiteral("closedDockWidgets"), dockWidgetNames(closedDockWidgets));
    map.insert(QStringLiteral("allDockWidgets"), toVariantList(allDockWidgets));
    map.insert(QStringLiteral("screenInfo"), toVariantList<LayoutSaver::ScreenInfo>(screenInfo));

    return map;
}

void LayoutSaver::Layout::fromVariantMap(const QVariantMap &map)
{
    allDockWidgets.clear();
    const QVariantList dockWidgetsV = map.value(QStringLiteral("allDockWidgets")).toList();
    for (const QVariant &v : dockWidgetsV) {
        const QVariantMap dwV = v.toMap();
        const QString name = dwV.value(QStringLiteral("uniqueName")).toString();
        auto dw = LayoutSaver::DockWidget::dockWidgetForName(name);
        dw->fromVariantMap(dwV);
        allDockWidgets.push_back(dw);
    }

    closedDockWidgets.clear();
    const QVariantList closedDockWidgetsV = map.value(QStringLiteral("closedDockWidgets")).toList();
    closedDockWidgets.reserve(closedDockWidgetsV.size());
    for (const QVariant &v : closedDockWidgetsV) {
        closedDockWidgets.push_back(LayoutSaver::DockWidget::dockWidgetForName(v.toString()));
    }

    serializationVersion = map.value(QStringLiteral("serializationVersion")).toInt();
    mainWindows = fromVariantList<LayoutSaver::MainWindow>(map.value(QStringLiteral("mainWindows")).toList());
    floatingWindows = fromVariantList<LayoutSaver::FloatingWindow>(map.value(QStringLiteral("floatingWindows")).toList());
    screenInfo = fromVariantList<LayoutSaver::ScreenInfo>(map.value(QStringLiteral("screenInfo")).toList());
}

void LayoutSaver::Layout::scaleSizes()
{
    if (mainWindows.isEmpty())
        return;

    for (auto &mw : mainWindows)
        mw.scaleSizes();

    for (auto &fw : floatingWindows) {
        LayoutSaver::MainWindow mw = mainWindowForIndex(fw.parentIndex);
        if (mw.scalingInfo.isValid())
            fw.scaleSizes(mw.scalingInfo);
    }

    const ScalingInfo firstScalingInfo = mainWindows.constFirst().scalingInfo;
    if (firstScalingInfo.isValid()) {
        for (auto &dw : allDockWidgets) {
            // TODO: Determine the best main window. This only interesting for closed dock widget geometry
            // which was previously floating. But they still have some other main window as parent.
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

bool LayoutSaver::Item::isValid(const LayoutSaver::MultiSplitterLayout &layout) const
{
    if (!frame.isValid())
        return false;

    const int numAnchors = layout.anchors.size();

    if (indexOfLeftAnchor < 0 || indexOfTopAnchor < 0 ||
            indexOfBottomAnchor < 0 || indexOfRightAnchor < 0 ||
            indexOfLeftAnchor >= numAnchors || indexOfTopAnchor >= numAnchors ||
            indexOfBottomAnchor >= numAnchors || indexOfRightAnchor >= numAnchors) {
        qWarning() << Q_FUNC_INFO << "Invalid anchor indexes"
                   << indexOfLeftAnchor << indexOfTopAnchor
                   << indexOfBottomAnchor << indexOfRightAnchor;
        return false;
    }

    return true;
}

void LayoutSaver::Item::scaleSizes(const ScalingInfo &scalingInfo)
{
    scalingInfo.applyFactorsTo(geometry);
    if (!frame.isNull)
        frame.scaleSizes(scalingInfo);
}

QVariantMap LayoutSaver::Item::toVariantMap() const
{
    QVariantMap map;
    map.insert(QStringLiteral("objectName"), objectName);
    map.insert(QStringLiteral("isPlaceholder"), isPlaceholder);
    map.insert(QStringLiteral("geometry"), rectToMap(geometry));
    map.insert(QStringLiteral("minSize"), sizeToMap(minSize));
    map.insert(QStringLiteral("indexOfLeftAnchor"), indexOfLeftAnchor);
    map.insert(QStringLiteral("indexOfTopAnchor"), indexOfTopAnchor);
    map.insert(QStringLiteral("indexOfRightAnchor"), indexOfRightAnchor);
    map.insert(QStringLiteral("indexOfBottomAnchor"), indexOfBottomAnchor);
    if (!frame.isNull)
        map.insert(QStringLiteral("frame"), frame.toVariantMap());

    return map;
}

void LayoutSaver::Item::fromVariantMap(const QVariantMap &map)
{
    objectName = map.value(QStringLiteral("objectName")).toString();
    isPlaceholder = map.value(QStringLiteral("isPlaceholder")).toBool();
    geometry = mapToRect(map.value(QStringLiteral("geometry")).toMap());
    minSize = mapToSize(map.value(QStringLiteral("minSize")).toMap());
    indexOfLeftAnchor = map.value(QStringLiteral("indexOfLeftAnchor")).toInt();
    indexOfTopAnchor = map.value(QStringLiteral("indexOfTopAnchor")).toInt();
    indexOfRightAnchor = map.value(QStringLiteral("indexOfRightAnchor")).toInt();
    indexOfBottomAnchor = map.value(QStringLiteral("indexOfBottomAnchor")).toInt();
    frame.fromVariantMap(map.value(QStringLiteral("frame"), QVariantMap()).toMap());
}

bool LayoutSaver::Frame::isValid() const
{
    if (!isNull)
        return true;

    if (!geometry.isValid()) {
        qWarning() << Q_FUNC_INFO << "Invalid geometry";
        return false;
    }

    if (options > 3) {
        qWarning() << Q_FUNC_INFO << "Invalid options" << options;
        return false;
    }

    if (currentTabIndex >= dockWidgets.size() || currentTabIndex < 0) {
        qWarning() << Q_FUNC_INFO << "Invalid tab index" << currentTabIndex << dockWidgets.size();
        return false;
    }

    for (auto &dw : dockWidgets) {
        if (!dw->isValid())
            return false;
    }

    return true;
}

void LayoutSaver::Frame::scaleSizes(const ScalingInfo &scalingInfo)
{
    scalingInfo.applyFactorsTo(geometry);
}

QVariantMap LayoutSaver::Frame::toVariantMap() const
{
    QVariantMap map;
    map.insert(QStringLiteral("isNull"), isNull);
    map.insert(QStringLiteral("objectName"), objectName);
    map.insert(QStringLiteral("geometry"), rectToMap(geometry));
    map.insert(QStringLiteral("options"), options);
    map.insert(QStringLiteral("currentTabIndex"), currentTabIndex);

    map.insert(QStringLiteral("dockWidgets"), dockWidgetNames(dockWidgets));

    return map;
}

void LayoutSaver::Frame::fromVariantMap(const QVariantMap &map)
{
    if (map.isEmpty()) {
        isNull = true;
        dockWidgets.clear();
        return;
    }

    isNull = map.value(QStringLiteral("isNull")).toBool();
    objectName = map.value(QStringLiteral("objectName")).toString();
    geometry = mapToRect(map.value(QStringLiteral("geometry")).toMap());
    options = map.value(QStringLiteral("options")).toUInt();
    currentTabIndex = map.value(QStringLiteral("currentTabIndex")).toInt();

    QVariantList dockWidgetsV = map.value(QStringLiteral("dockWidgets")).toList();

    dockWidgets.clear();
    dockWidgets.reserve(dockWidgetsV.size());
    for (const auto &variant : dockWidgetsV) {
        DockWidget::Ptr dw = DockWidget::dockWidgetForName(variant.toString());
        dockWidgets.push_back(dw);
    }
}

bool LayoutSaver::DockWidget::isValid() const
{
    return !uniqueName.isEmpty();
}

void LayoutSaver::DockWidget::scaleSizes(const ScalingInfo &scalingInfo)
{
    lastPosition.scaleSizes(scalingInfo);
}

QVariantMap LayoutSaver::DockWidget::toVariantMap() const
{
    QVariantMap map;
    if (!affinityName.isEmpty())
        map.insert(QStringLiteral("affinityName"), affinityName);
    map.insert(QStringLiteral("uniqueName"), uniqueName);
    map.insert(QStringLiteral("lastPosition"), lastPosition.toVariantMap());

    return map;
}

void LayoutSaver::DockWidget::fromVariantMap(const QVariantMap &map)
{
    affinityName = map.value(QStringLiteral("affinityName")).toString();
    uniqueName = map.value(QStringLiteral("uniqueName")).toString();
    lastPosition.fromVariantMap(map.value(QStringLiteral("lastPosition")).toMap());
}

bool LayoutSaver::Anchor::isValid(const LayoutSaver::MultiSplitterLayout &layout) const
{
    const bool isStatic = type != KDDockWidgets::Anchor::Type_None;
    const bool isFollowing = indexOfFollowee != -1;
    const int numAnchors = layout.anchors.size();

    if (!geometry.isValid() && !isStatic && !isFollowing) {
        qWarning() << Q_FUNC_INFO << "Invalid geometry" << geometry;
        return false;
    }

    if (indexOfFrom < 0 || indexOfTo < 0 || indexOfFrom == indexOfTo ||
        indexOfTo >= numAnchors || indexOfFrom >= numAnchors) {
        qWarning() << Q_FUNC_INFO << "Invalid indexes" << indexOfFrom << indexOfTo;
        return false;
    }

    auto &anchorTo = layout.anchors[indexOfTo];
    auto &anchorFrom = layout.anchors[indexOfFrom];
    if (anchorTo.orientation != anchorFrom.orientation || anchorTo.orientation == orientation) {
        qWarning() << Q_FUNC_INFO << "Invalid orientation" << anchorTo.orientation << anchorFrom.orientation
                   << orientation;
        return false;
    }

    if (orientation != Qt::Vertical && orientation != Qt::Horizontal) {
        qWarning() << Q_FUNC_INFO << "Invalid orientation" << orientation;
        return false;
    }

    if (type != KDDockWidgets::Anchor::Type_None &&
        type != KDDockWidgets::Anchor::Type_LeftStatic &&
        type != KDDockWidgets::Anchor::Type_RightStatic &&
        type != KDDockWidgets::Anchor::Type_TopStatic &&
        type != KDDockWidgets::Anchor::Type_BottomStatic) {
        qWarning() << Q_FUNC_INFO << "Invalid type" << type;
        return false;
    }

    if (!isStatic && !isFollowing && (side1Items.isEmpty() || side2Items.isEmpty())) {
        qWarning() << Q_FUNC_INFO << "Anchor should have items on both sides";
        return false;
    }

    return true;
}

QVariantMap LayoutSaver::Anchor::toVariantMap() const
{
    QVariantMap map;
    map.insert(QStringLiteral("objectName"), objectName);
    map.insert(QStringLiteral("geometry"), rectToMap(geometry));
    map.insert(QStringLiteral("orientation"), orientation);
    map.insert(QStringLiteral("type"), type);
    map.insert(QStringLiteral("indexOfFrom"), indexOfFrom);
    map.insert(QStringLiteral("indexOfTo"), indexOfTo);
    map.insert(QStringLiteral("indexOfFollowee"), indexOfFollowee);
    map.insert(QStringLiteral("positionPercentage"), positionPercentage);

    QVariantList side1ItemsV;
    QVariantList side2ItemsV;
    side1ItemsV.reserve(side1Items.size());
    side2ItemsV.reserve(side2Items.size());
    for (int index : qAsConst(side1Items))
        side1ItemsV.push_back(index);
    for (int index : qAsConst(side2Items))
        side2ItemsV.push_back(index);

    map.insert(QStringLiteral("side1Items"), side1ItemsV);
    map.insert(QStringLiteral("side2Items"), side2ItemsV);

    return map;
}

void LayoutSaver::Anchor::fromVariantMap(const QVariantMap &map)
{
    objectName = map.value(QStringLiteral("objectName")).toString();
    geometry = mapToRect(map.value(QStringLiteral("geometry")).toMap());

    orientation = map.value(QStringLiteral("orientation")).toInt();
    type = map.value(QStringLiteral("type")).toInt();
    indexOfFrom = map.value(QStringLiteral("indexOfFrom")).toInt();
    indexOfTo = map.value(QStringLiteral("indexOfTo")).toInt();
    indexOfFollowee = map.value(QStringLiteral("indexOfFollowee")).toInt();
    positionPercentage = map.value(QStringLiteral("positionPercentage")).toDouble();

    side1Items.clear();
    side2Items.clear();
    const QVariantList side1ItemsV = map.value(QStringLiteral("side1Items")).toList();
    const QVariantList side2ItemsV = map.value(QStringLiteral("side2Items")).toList();
    side1Items.reserve(side1ItemsV.size());
    side2Items.reserve(side2ItemsV.size());
    for (const QVariant &v : side1ItemsV)
        side1Items.push_back(v.toInt());
    for (const QVariant &v : side2ItemsV)
        side2Items.push_back(v.toInt());
}

void LayoutSaver::Anchor::scaleSizes(const ScalingInfo &scalingInfo)
{
    const QPoint pos = geometry.topLeft();

    if (isVertical()) {
        geometry.moveLeft(int(pos.x() * scalingInfo.widthFactor));
    } else {
        geometry.moveTop(int(pos.y() * scalingInfo.heightFactor));
    }
}

bool LayoutSaver::Anchor::isVertical() const
{
    return orientation == Qt::Vertical;
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

void LayoutSaver::FloatingWindow::scaleSizes(const ScalingInfo &scalingInfo)
{
    scalingInfo.applyFactorsTo(/*by-ref*/geometry);
    multiSplitterLayout.scaleSizes(scalingInfo);
}

QVariantMap LayoutSaver::FloatingWindow::toVariantMap() const
{
    QVariantMap map;
    map.insert(QStringLiteral("multiSplitterLayout"), multiSplitterLayout.toVariantMap());
    map.insert(QStringLiteral("parentIndex"), parentIndex);
    map.insert(QStringLiteral("geometry"), rectToMap(geometry));
    map.insert(QStringLiteral("screenIndex"), screenIndex);
    map.insert(QStringLiteral("screenSize"), sizeToMap(screenSize));
    map.insert(QStringLiteral("isVisible"), isVisible);

    if (!affinityName.isEmpty())
        map.insert(QStringLiteral("affinityName"), affinityName);

    return map;
}

void LayoutSaver::FloatingWindow::fromVariantMap(const QVariantMap &map)
{
    multiSplitterLayout.fromVariantMap(map.value(QStringLiteral("multiSplitterLayout")).toMap());
    parentIndex = map.value(QStringLiteral("parentIndex")).toInt();
    geometry = mapToRect(map.value(QStringLiteral("geometry")).toMap());
    screenIndex = map.value(QStringLiteral("screenIndex")).toInt();
    screenSize = mapToSize(map.value(QStringLiteral("screenSize")).toMap());
    isVisible = map.value(QStringLiteral("isVisible")).toBool();
    affinityName = map.value(QStringLiteral("affinityName")).toString();
}

bool LayoutSaver::MainWindow::isValid() const
{
    if (!multiSplitterLayout.isValid())
        return false;

    if (options != MainWindowOption_None && options != MainWindowOption_HasCentralFrame) {
        qWarning() << Q_FUNC_INFO << "Invalid option" << options;
        return false;
    }

    return true;
}

void LayoutSaver::MainWindow::scaleSizes()
{
    if (scalingInfo.isValid()) {
        // Doesn't happen, it's called only once
        Q_ASSERT(false);
        return;
    }

    scalingInfo = ScalingInfo(uniqueName, geometry);

    if (scalingInfo.isValid())
        multiSplitterLayout.scaleSizes(scalingInfo);
}

QVariantMap LayoutSaver::MainWindow::toVariantMap() const
{
    QVariantMap map;
    map.insert(QStringLiteral("options"), int(options));
    map.insert(QStringLiteral("multiSplitterLayout"), multiSplitterLayout.toVariantMap());
    map.insert(QStringLiteral("uniqueName"), uniqueName);
    map.insert(QStringLiteral("geometry"), rectToMap(geometry));
    map.insert(QStringLiteral("screenIndex"), screenIndex);
    map.insert(QStringLiteral("screenSize"), sizeToMap(screenSize));
    map.insert(QStringLiteral("isVisible"), isVisible);

    if (!affinityName.isEmpty())
        map.insert(QStringLiteral("affinityName"), affinityName);

    return map;
}

void LayoutSaver::MainWindow::fromVariantMap(const QVariantMap &map)
{
    options = KDDockWidgets::MainWindowOptions(map.value(QStringLiteral("options")).toInt());
    multiSplitterLayout.fromVariantMap(map.value(QStringLiteral("multiSplitterLayout")).toMap());
    uniqueName = map.value(QStringLiteral("uniqueName")).toString();
    affinityName = map.value(QStringLiteral("affinityName")).toString();
    geometry = mapToRect(map.value(QStringLiteral("geometry")).toMap());
    screenIndex = map.value(QStringLiteral("screenIndex")).toInt();
    screenSize = mapToSize(map.value(QStringLiteral("screenSize")).toMap());

    isVisible = map.value(QStringLiteral("isVisible")).toBool();
}

bool LayoutSaver::MultiSplitterLayout::isValid() const
{
    for (auto &item : items) {
        if (!item.isValid(*this))
            return false;
    }

    for (auto &anchor : anchors) {
        if (!anchor.isValid(*this))
            return false;
    }

    if (!size.isValid()) {
        qWarning() << Q_FUNC_INFO << "Invalid size";
        return false;
    }

    return true;
}

void LayoutSaver::MultiSplitterLayout::scaleSizes(const ScalingInfo &scalingInfo)
{
    scalingInfo.applyFactorsTo(/*by-ref*/size);
    for (LayoutSaver::Anchor &anchor : anchors)
        anchor.scaleSizes(scalingInfo);
    for (LayoutSaver::Item &item : items)
        item.scaleSizes(scalingInfo);
}

QVariantMap LayoutSaver::MultiSplitterLayout::toVariantMap() const
{
    QVariantMap map;

    map.insert(QStringLiteral("anchors"), toVariantList<LayoutSaver::Anchor>(anchors));
    map.insert(QStringLiteral("items"), toVariantList<LayoutSaver::Item>(items));
    map.insert(QStringLiteral("minSize"), sizeToMap(minSize));
    map.insert(QStringLiteral("size"), sizeToMap(size));

    return map;
}

void LayoutSaver::MultiSplitterLayout::fromVariantMap(const QVariantMap &map)
{
    anchors = fromVariantList<LayoutSaver::Anchor>(map.value(QStringLiteral("anchors")).toList());
    items = fromVariantList<LayoutSaver::Item>(map.value(QStringLiteral("items")).toList());
    minSize = mapToSize(map.value(QStringLiteral("minSize")).toMap());
    size = mapToSize(map.value(QStringLiteral("size")).toMap());
}

void LayoutSaver::LastPosition::scaleSizes(const ScalingInfo &scalingInfo)
{
    scalingInfo.applyFactorsTo(/*by-ref*/lastFloatingGeometry);
}

QVariantMap LayoutSaver::LastPosition::toVariantMap() const
{
    QVariantMap map;
    map.insert(QStringLiteral("lastFloatingGeometry"), rectToMap(lastFloatingGeometry));
    map.insert(QStringLiteral("tabIndex"), tabIndex);
    map.insert(QStringLiteral("wasFloating"), wasFloating);
    map.insert(QStringLiteral("placeholders"), toVariantList<LayoutSaver::Placeholder>(placeholders));

    return map;
}

void LayoutSaver::LastPosition::fromVariantMap(const QVariantMap &map)
{
    lastFloatingGeometry = mapToRect(map.value(QStringLiteral("lastFloatingGeometry")).toMap());
    tabIndex = map.value(QStringLiteral("tabIndex")).toInt();
    wasFloating = map.value(QStringLiteral("wasFloating")).toBool();
    placeholders = fromVariantList<LayoutSaver::Placeholder>(map.value(QStringLiteral("placeholders")).toList());
}

QVariantMap LayoutSaver::ScreenInfo::toVariantMap() const
{
    QVariantMap map;
    map.insert(QStringLiteral("index"), index);
    map.insert(QStringLiteral("geometry"), rectToMap(geometry));
    map.insert(QStringLiteral("name"), name);
    map.insert(QStringLiteral("devicePixelRatio"), devicePixelRatio);

    return map;
}

void LayoutSaver::ScreenInfo::fromVariantMap(const QVariantMap &map)
{
    index = map.value(QStringLiteral("index")).toInt();
    geometry = mapToRect(map.value(QStringLiteral("geometry")).toMap());
    name = map.value(QStringLiteral("name")).toString();
    devicePixelRatio = map.value(QStringLiteral("devicePixelRatio")).toDouble();
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

LayoutSaver::ScalingInfo::ScalingInfo(const QString &mainWindowId, QRect savedMainWindowGeo)
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

    this->mainWindowName = mainWindowId;
    this->savedMainWindowGeometry = savedMainWindowGeo;
    realMainWindowGeometry = mainWindow->geometry();
    widthFactor = double(realMainWindowGeometry.width()) / savedMainWindowGeo.width();
    heightFactor = double(realMainWindowGeometry.height()) / savedMainWindowGeo.height();
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
    pt.setX(qCeil(pt.x() * widthFactor));
    pt.setY(qCeil(pt.y() * heightFactor));
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

    applyFactorsTo(/*by-ref*/size);
    applyFactorsTo(/*by-ref*/pos);

    rect.moveTopLeft(pos);
    rect.setSize(size);
}
