/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include <QDataStream>
#include <QDebug>
#include <QSettings>
#include <QApplication>

#include <memory>

using namespace KDDockWidgets;

QHash<QString, LayoutSaver::DockWidget::Ptr> LayoutSaver::DockWidget::s_dockWidgets;

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

    Private()
        : m_dockRegistry(DockRegistry::self())
    {
    }

    void serializeWindowGeometry(QDataStream &ds, QWidgetOrQuick *topLevel);
    void deserializeWindowGeometry(QDataStream &ds, QWidgetOrQuick *topLevel);
    void deleteEmptyFrames();
    void clearRestoredProperty();

    std::unique_ptr<QSettings> settings() const;
    DockRegistry *const m_dockRegistry;
    static bool s_restoreInProgress;
};

bool LayoutSaver::Private::s_restoreInProgress = false;

LayoutSaver::LayoutSaver()
    : d(new Private())
{
}

LayoutSaver::~LayoutSaver()
{
    delete d;
}

bool LayoutSaver::saveToDisk()
{
    if (qApp->organizationName().isEmpty() || qApp->applicationName().isEmpty()) {
        qWarning() << Q_FUNC_INFO
                   << "Cannot save. Either organization name or application name is empty.";
        return false;
    }

    const QByteArray data = serializeLayout();
    d->settings()->setValue(QStringLiteral("data"), data);
    return true;
}

bool LayoutSaver::restoreFromDisk()
{
    const QByteArray data = d->settings()->value(QStringLiteral("data")).toByteArray();
    const bool result = restoreLayout(data);
    return result;
}

QByteArray LayoutSaver::serializeLayout() const
{
    if (!d->m_dockRegistry->isSane()) {
        qWarning() << Q_FUNC_INFO << "Refusing to serialize insane layout";
        return {};
    }

    QByteArray result;
    QDataStream ds(&result, QIODevice::WriteOnly);
    ds << KDDOCKWIDGETS_SERIALIZATION_VERSION;

    // Just a simplification. One less type of windows to handle.
    d->m_dockRegistry->ensureAllFloatingWidgetsAreMorphed();

    const MainWindowBase::List mainWindows = d->m_dockRegistry->mainwindows();
    ds << mainWindows.size();
    for (MainWindowBase *mainWindow : mainWindows) {
        ds << mainWindow->uniqueName();
        d->serializeWindowGeometry(ds, mainWindow->window()); // window() as the MainWindow can be embedded
        ds << mainWindow;
    }

    const QVector<KDDockWidgets::FloatingWindow*> floatingWindows = d->m_dockRegistry->nestedwindows();
    ds << floatingWindows.size();
    for (KDDockWidgets::FloatingWindow *floatingWindow : floatingWindows) {

        auto mainWindow = qobject_cast<MainWindowBase*>(floatingWindow->parentWidget());
        const int parentIndex = mainWindow ? DockRegistry::self()->mainwindows().indexOf(mainWindow)
                                           : -1;

        ds << parentIndex;

        d->serializeWindowGeometry(ds, floatingWindow);
        ds << floatingWindow;
    }

    // Closed dock widgets also have interesting things to save, like geometry and placeholder info
    const DockWidgetBase::List closedDockWidgets = d->m_dockRegistry->closedDockwidgets();
    ds << closedDockWidgets.size();
    for (DockWidgetBase *dockWidget : closedDockWidgets) {
        ds << dockWidget;
    }

    // Save the placeholder info. We do it last, as we also restore it last, since we need all items to be created
    // before restoring the placeholders

    const DockWidgetBase::List dockWidgets = d->m_dockRegistry->dockwidgets();
    ds << dockWidgets.size();
    for (DockWidgetBase *dw : dockWidgets) {
        ds << dw->uniqueName();
        ds << dw->lastPosition();
    }

    return result;
}

bool LayoutSaver::restoreLayout(const QByteArray &data)
{
    d->clearRestoredProperty();
    if (data.isEmpty())
        return true;

    Private::RAIIIsRestoring isRestoring;

    struct FrameCleanup {
        FrameCleanup(LayoutSaver *saver) : m_saver(saver)
        {
        }

        ~FrameCleanup()
        {
            m_saver->d->deleteEmptyFrames();
        }

        LayoutSaver *const m_saver;

    };

    FrameCleanup cleanup(this);

    QDataStream ds(data);
    int serializationVersion;
    ds >> serializationVersion;

    if (serializationVersion != KDDOCKWIDGETS_SERIALIZATION_VERSION) {
        qWarning() << "Unsupported serialization version. Got=" << serializationVersion
                   << "; expected=" << KDDOCKWIDGETS_SERIALIZATION_VERSION;
        return false;
    }

    // Hide all dockwidgets and unparent them from any layout before starting restore
    d->m_dockRegistry->clear(/*deleteStaticAnchors=*/true);

    // 1. Restore main windows
    int numMainWindows;
    ds >> numMainWindows;
    for (int i = 0 ; i < numMainWindows; ++i) {
        QString name;
        ds >> name;

        MainWindowBase *mainWindow = d->m_dockRegistry->mainWindowByName(name);
        if (!mainWindow) {
            qWarning() << "Failed to restore layout create MainWindow with name" << name << "first";
            return false;
        }

        d->deserializeWindowGeometry(ds, mainWindow->window()); // window() as the MainWindow can be embedded

        if (!mainWindow->fillFromDataStream(ds))
            return false;
    }

    // 2. Restore FloatingWindows
    int numFloating;
    ds >> numFloating;
    for (int i = 0; i < numFloating; ++i) {

        int parentIndex;
        ds >> parentIndex;
        QWidget *parent = parentIndex == -1 ? nullptr
                                            : DockRegistry::self()->mainwindows().at(parentIndex);

        auto fw = Config::self().frameWorkWidgetFactory()->createFloatingWindow(parent);
        d->deserializeWindowGeometry(ds, fw);
        if (!fw->fillFromDataStream(ds)) {
            return false;
        }
    }

    // 3. Restore closed dock widgets. They remain closed but acquire geometry and placeholder properties
    int numClosedDockWidgets;
    ds >> numClosedDockWidgets;
    for (int i = 0; i < numClosedDockWidgets; ++i) {
        DockWidgetBase::createFromDataStream(ds);
    }

    // 4. Restore the placeholder info, now that the Items have been created
    int numDockWidgets;
    ds >> numDockWidgets;
    for (int i = 0; i < numDockWidgets; ++i) {
        QString name;
        ds >> name;

        if (DockWidgetBase *dw = d->m_dockRegistry->dockByName(name)) {
            dw->lastPosition()->fillFromDataStream(ds);
        } else {
            qWarning() << Q_FUNC_INFO << "Couldn't find dock widget" << name;
            KDDockWidgets::LastPosition dummy;
            dummy.fillFromDataStream(ds); // Add a dummy just to consume the stream
        }
    }

    return true;
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

#if defined(DOCKS_DEVELOPER_MODE)
void LayoutSaver::dumpLayout(const QByteArray &savedLayout)
{
    QDataStream ds(savedLayout);
    int serializationVersion;
    ds >> serializationVersion;


}
#endif

void LayoutSaver::Private::clearRestoredProperty()
{
    const DockWidgetBase::List &allDockWidgets = DockRegistry::self()->dockwidgets();
    for (DockWidgetBase *dw : allDockWidgets) {
        dw->setProperty("kddockwidget_was_restored", QVariant());
    }
}

void LayoutSaver::Private::serializeWindowGeometry(QDataStream &ds, QWidgetOrQuick *topLevel)
{
    ds << topLevel->geometry();
    ds << topLevel->isVisible();
}

void LayoutSaver::Private::deserializeWindowGeometry(QDataStream &ds, QWidgetOrQuick *topLevel)
{
    QRect geo;
    bool visible;
    ds >> geo;
    ds >> visible;
    topLevel->setGeometry(geo);
    topLevel->setVisible(visible);
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

void LayoutSaver::Layout::fillFrom(const QByteArray &serialized)
{
    QDataStream ds(serialized);
    ds >> this;
}
