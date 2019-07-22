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
#include "DockRegistry_p.h"
#include "DockWidget.h"
#include "DropArea_p.h"
#include "Logging_p.h"
#include "Frame_p.h"
#include "multisplitter/Anchor_p.h"
#include "multisplitter/Item_p.h"

#include <QDataStream>
#include <QDebug>
#include <QSettings>
#include <QApplication>

#include <memory>

using namespace KDDockWidgets;


class KDDockWidgets::LayoutSaver::Private
{
public:
    Private()
        : m_dockRegistry(DockRegistry::self())
    {
    }

    void serializeWindowGeometry(QDataStream &ds, QWidget *topLevel);
    void deserializeWindowGeometry(QDataStream &ds, QWidget *topLevel);

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

void LayoutSaver::restoreFromDisk()
{
    const QByteArray data = d->settings()->value(QStringLiteral("data")).toByteArray();
    Private::s_restoreInProgress = true;
    restoreLayout(data);
    Private::s_restoreInProgress = false;
}

QByteArray LayoutSaver::serializeLayout() const
{
    if (!d->m_dockRegistry->isSane()) {
        qWarning() << Q_FUNC_INFO << "Refusing to serialize insane layout";
        return {};
    }

    QByteArray result;
    QDataStream ds(&result, QIODevice::WriteOnly);

    // Just a simplification. One less type of windows to handle.
    d->m_dockRegistry->ensureAllFloatingWidgetsAreMorphed();

    const MainWindow::List mainWindows = d->m_dockRegistry->mainwindows();
    ds << mainWindows.size();
    for (MainWindow *mainWindow : mainWindows) {
        ds << mainWindow->name();
        d->serializeWindowGeometry(ds, mainWindow);
        ds << mainWindow;
    }

    const QVector<FloatingWindow*> floatingWindows = d->m_dockRegistry->nestedwindows();
    ds << floatingWindows.size();
    for (FloatingWindow *floatingWindow : floatingWindows) {
        ds << floatingWindow;
        d->serializeWindowGeometry(ds, floatingWindow);
    }

    // TODO: Restore geometry in hidden dock widgets
    // TODO: Restore the placeholder for hidden dock widgets

    return result;
}

bool LayoutSaver::restoreLayout(const QByteArray &data)
{
    if (data.isEmpty())
        return false;

    QDataStream ds(data);

    // Hide all dockwidgets and unparent them from any layout before starting restore
    d->m_dockRegistry->clear();

    int numMainWindows;
    ds >> numMainWindows;
    for (int i = 0 ; i < numMainWindows; ++i) {
        QString name;
        ds >> name;

        MainWindow *mainWindow = d->m_dockRegistry->mainWindowByName(name);
        if (!mainWindow) {
            qWarning() << "Failed to restore layout create MainWindow with name" << name << "first";
            return false;
        }

        d->deserializeWindowGeometry(ds, mainWindow);

        if (!mainWindow->fillFromDataStream(ds))
            return false;
    }

    int numFloating;
    ds >> numFloating;
    for (int i = 0; i < numFloating; ++i) {
        auto fw = new FloatingWindow();
        fw->fillFromDataStream(ds);
        d->deserializeWindowGeometry(ds, fw);
    }

    return true;
}

void LayoutSaver::Private::serializeWindowGeometry(QDataStream &ds, QWidget *topLevel)
{
    ds << topLevel->geometry();
    ds << topLevel->isVisible();
}

void LayoutSaver::Private::deserializeWindowGeometry(QDataStream &ds, QWidget *topLevel)
{
    QRect geo;
    bool visible;
    ds >> geo;
    ds >> visible;
    topLevel->setGeometry(geo);
    topLevel->setVisible(visible);
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
