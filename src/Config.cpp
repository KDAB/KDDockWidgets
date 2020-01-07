/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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
 * @brief Application wide config to tune certain beahviours of the framework.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "Config.h"
#include "DockRegistry_p.h"
#include "FrameworkWidgetFactory.h"

#include <QApplication>
#include <QDebug>
#include <QOperatingSystemVersion>

using namespace KDDockWidgets;

class Config::Private
{
public:
    Private()
        : m_frameworkWidgetFactory(new DefaultWidgetFactory())
    {
    }

    ~Private()
    {
        delete m_frameworkWidgetFactory;
    }

    void fixFlags();

    QQmlEngine *m_qmlEngine = nullptr;
    DockWidgetFactoryFunc m_dockWidgetFactoryFunc = nullptr;
    FrameworkWidgetFactory *m_frameworkWidgetFactory;
    Flags m_flags = Flag_Default;
    int m_separatorThickness = 5;
#if defined(Q_OS_WIN)
    int m_staticSeparatorThickness = 1; // FIXME: Broken on Windows still.
#else
    int m_staticSeparatorThickness = 0;
#endif
};


Config::Config()
    : d(new Private())
{
    d->fixFlags();
}

Config& Config::self()
{
    static Config config;
    return config;
}

Config::~Config()
{
    delete d;
}

Config::Flags Config::flags() const
{
    return d->m_flags;
}

void Config::setFlags(Flags f)
{
    if (!DockRegistry::self()->isEmpty()) {
        qWarning() << Q_FUNC_INFO << "Only use this function at startup before creating any DockWidget or MainWindow";
        return;
    }

    d->m_flags = f;
    d->fixFlags();
}

void Config::setDockWidgetFactoryFunc(DockWidgetFactoryFunc func)
{
    d->m_dockWidgetFactoryFunc = func;
}

DockWidgetFactoryFunc Config::dockWidgetFactoryFunc() const
{
    return d->m_dockWidgetFactoryFunc;
}

void Config::setFrameworkWidgetFactory(FrameworkWidgetFactory *wf)
{
    Q_ASSERT(wf);
    delete d->m_frameworkWidgetFactory;
    d->m_frameworkWidgetFactory = wf;
}

FrameworkWidgetFactory *Config::frameworkWidgetFactory() const
{
    return d->m_frameworkWidgetFactory;
}

int Config::separatorThickness(bool staticSeparator) const
{
    return staticSeparator ? d->m_staticSeparatorThickness
                           : d->m_separatorThickness;
}

void Config::setSeparatorThickness(int value, bool staticSeparator)
{
    if ((value <= 0 && !staticSeparator) || (value < 0 && staticSeparator) || value >= 100) {
        qWarning() << Q_FUNC_INFO << "Invalid value" << value;
        return;
    }

    if (!DockRegistry::self()->isEmpty()) {
        qWarning() << Q_FUNC_INFO << "Only use this function at startup before creating any DockWidget or MainWindow";
        return;
    }

    if (staticSeparator)
        d->m_staticSeparatorThickness = value;
    else
        d->m_separatorThickness = value;
}

void Config::setQmlEngine(QQmlEngine *qmlEngine)
{
    if (d->m_qmlEngine) {
        qWarning() << Q_FUNC_INFO << "Already has QML engine";
        return;
    }

    d->m_qmlEngine = qmlEngine;
}

QQmlEngine *Config::qmlEngine() const
{
    return d->m_qmlEngine;
}

void Config::Private::fixFlags()
{
#if defined(Q_OS_WIN)
    if (QOperatingSystemVersion::current().majorVersion() < 10) {
        // Aero-snap requires Windows 10
        m_flags = m_flags & ~Flag_AeroSnapWithClientDecos;
    }

    // These are mutually exclusive:
    if ((m_flags & Flag_AeroSnapWithClientDecos) && (m_flags & Flag_NativeTitleBar)) {
        // We're either using native or client decorations, let's use native.
        m_flags = m_flags & ~Flag_AeroSnapWithClientDecos;
    }
#elif defined(Q_OS_MACOS)
    // Not supported on macOS:
    m_flags = m_flags & ~Flag_AeroSnapWithClientDecos;
#else
    // Not supported on linux.
    // On Linux, dragging the title bar of a window doesn't generate NonClientMouseEvents
    m_flags = m_flags & ~Flag_NativeTitleBar;
    m_flags = m_flags & ~Flag_AeroSnapWithClientDecos;
#endif

#if !defined(Q_OS_WIN) && !defined(Q_OS_MACOS)
    m_flags = m_flags & ~Flag_AeroSnapWithClientDecos;
#endif
}
