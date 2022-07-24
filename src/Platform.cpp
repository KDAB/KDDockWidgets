/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform.h"
#include "private/Platform_p.h"
#include "EventFilterInterface.h"

#ifdef KDDW_FRONTEND_QTWIDGETS
#include "qtwidgets/Platform_qtwidgets.h"
#endif

#ifdef KDDW_FRONTEND_QTQUICK
#include "qtquick/Platform_qtquick.h"
#endif

#ifdef KDDW_FRONTEND_DUMMY
#include "dummy/Platform_dummy.h"
#endif

#ifdef KDDW_FRONTEND_FLUTTER
#include "flutter/Platform_flutter.h"
#endif

#include "Config.h"

#include <qglobal.h>
#include <QDebug>

#include "kdbindings/signal.h"

using namespace KDDockWidgets;

static Platform *s_platform = nullptr;

EventFilterInterface::~EventFilterInterface() = default;

#ifdef DOCKS_DEVELOPER_MODE
QString Platform::s_expectedWarning = {};
Platform::WarningObserver *Platform::s_warningObserver = nullptr;
#endif

Platform::Platform()
    : d(new Private())
{
    Q_ASSERT(!s_platform);
    s_platform = this;

    qDebug() << "Created Platform";
}

Platform::~Platform()
{
    s_platform = nullptr;
    delete d;
}

Platform *Platform::instance()
{
    return s_platform;
}

bool Platform::hasActivePopup() const
{
    return false;
}

bool Platform::isQtWidgets() const
{
    return strcmp(name(), "qtwidgets") == 0;
}

bool Platform::isQtQuick() const
{
    return strcmp(name(), "qtquick") == 0;
}

int Platform::startDragDistance() const
{
    const int userRequestedDistance = Config::self().startDragDistance();
    if (userRequestedDistance > -1)
        return userRequestedDistance;

    return startDragDistance_impl();
}

int Platform::startDragDistance_impl() const
{
    // Override this method in derived classes for some different value if needed
    return 4;
}

#ifdef DOCKS_DEVELOPER_MODE

Platform::WarningObserver::~WarningObserver() = default;

/*static*/
void Platform::tests_initPlatform(int &argc, char **argv, KDDockWidgets::FrontendType type)
{
    if (Platform::instance())
        return;

    Platform *platform = nullptr;

    switch (type) {
    case FrontendType::QtWidgets:
#ifdef KDDW_FRONTEND_QTWIDGETS
        platform = new Platform_qtwidgets(argc, argv);
#endif
        break;
    case FrontendType::QtQuick:
#ifdef KDDW_FRONTEND_QTQUICK
        platform = new Platform_qtquick(argc, argv);
#endif
        break;
    case FrontendType::Dummy:
#ifdef KDDW_FRONTEND_DUMMY
        platform = new Platform_dummy(argc, argv);
#endif
        break;
    case FrontendType::Flutter:
#ifdef KDDW_FRONTEND_FLUTTER
        platform = new Platform_flutter(argc, argv);
#endif
        break;
    }

    if (!platform) {
        qCritical() << "Could not initialize platform for" << type << ". KDDockWidgets was built without support for it";
        qFatal("Aborting");
        return;
    }

    Platform::instance()->m_numWarningsEmitted = 0;

    /// Reset the default framework factory, so we can test several frontends in the same test run
    Config::self().setViewFactory(Platform::instance()->createDefaultViewFactory());

    /// Any additional setup
    Platform::instance()->tests_initPlatform_impl();
}

/*static */
void Platform::tests_deinitPlatform()
{
    auto plat = Platform::instance();
    plat->d->m_inDestruction = true;

    plat->tests_deinitPlatform_impl();
    delete plat;
}

/**static*/
std::vector<KDDockWidgets::FrontendType> Platform::frontendTypes()
{
    std::vector<KDDockWidgets::FrontendType> types;

#ifdef DOCKS_DEVELOPER_MODE
    // During development it's useful to quickly run tests only on the frontend we're developing.
    // The developer can set, for example, KDDW_TEST_FRONTEND=2 to run only the QtQuick tests
    bool ok = false;
    const int frontendId = qEnvironmentVariableIntValue("KDDW_TEST_FRONTEND", &ok);
    if (ok) {
        types.push_back(FrontendType(frontendId));
        return types;
    }

#endif

#ifdef KDDW_FRONTEND_QTQUICK
    types.push_back(FrontendType::QtQuick);
#endif

#ifdef KDDW_FRONTEND_QTWIDGETS
    types.push_back(FrontendType::QtWidgets);
#endif

    return types;
}

#endif

void Platform::installGlobalEventFilter(EventFilterInterface *filter)
{
    d->m_globalEventFilters.push_back(filter);
}

void Platform::removeGlobalEventFilter(EventFilterInterface *filter)
{
    d->m_globalEventFilters.erase(std::remove(d->m_globalEventFilters.begin(),
                                              d->m_globalEventFilters.end(), filter),
                                  d->m_globalEventFilters.end());
}
