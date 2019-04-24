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

#include "DockRegistry_p.h"
#include "DockWidget.h"
#include "Logging_p.h"

#include <QPointer>
#include <QDebug>

using namespace KDDockWidgets;

DockRegistry::DockRegistry()
    : QObject()
{
    KDDockWidgets::setLoggingFilterRules();
}

void DockRegistry::maybeDelete()
{
    if (isEmpty())
        delete this;
}

bool DockRegistry::isEmpty() const
{
    return m_dockWidgets.isEmpty() && m_mainWindows.isEmpty() && m_nestedWindows.isEmpty();
}

DockRegistry *DockRegistry::self()
{
    static QPointer<DockRegistry> s_dockRegistry;

    if (!s_dockRegistry) {
        s_dockRegistry = new DockRegistry();
    }

    return s_dockRegistry;
}

void DockRegistry::registerDockWidget(DockWidget *dock)
{
    m_dockWidgets << dock;
}

void DockRegistry::unregisterDockWidget(DockWidget *dock)
{
    m_dockWidgets.removeOne(dock);
    maybeDelete();
}

void DockRegistry::registerMainWindow(MainWindow *mainWindow)
{
    m_mainWindows << mainWindow;
}

void DockRegistry::unregisterMainWindow(MainWindow *mainWindow)
{
    m_mainWindows.removeOne(mainWindow);
    maybeDelete();
}

void DockRegistry::registerNestedWindow(FloatingWindow *window)
{
    m_nestedWindows << window;
}

void DockRegistry::unregisterNestedWindow(FloatingWindow *window)
{
    m_nestedWindows.removeOne(window);
    maybeDelete();
}

DockWidget *DockRegistry::dockByName(const QString &name) const
{
    for (auto dock : qAsConst(m_dockWidgets)) {
        if (dock->name() == name)
            return dock;
    }

    return nullptr;
}

MainWindow *DockRegistry::mainWindowByName(const QString &name) const
{
    for (auto mainWindow : qAsConst(m_mainWindows)) {
        if (mainWindow->name() == name)
            return mainWindow;
    }

    return nullptr;
}

bool DockRegistry::isSane() const
{
    QSet<QString> names;
    for (auto dock : qAsConst(m_dockWidgets)) {
        const QString name = dock->name();
        if (name.isEmpty()) {
            qWarning() << "DockRegistry::isSane: DockWidget" << dock << "is missing a name";
            return false;
        } else if (names.contains(name)) {
            qWarning() << "DockRegistry::isSane: dockWidgets with duplicate names:" << name;
            return false;
        } else {
            names.insert(name);
        }
    }
    return true;
}

DockWidget::List DockRegistry::dockwidgets() const
{
    return m_dockWidgets;
}

MainWindow::List DockRegistry::mainwindows() const
{
    return m_mainWindows;
}

QVector<FloatingWindow *> DockRegistry::nestedwindows() const
{
    return m_nestedWindows;
}

void DockRegistry::closeAllDockWidgets()
{
    for (auto dw : qAsConst(m_dockWidgets)) {
        dw->close();
    }

    qCDebug(restoring) << Q_FUNC_INFO << "; dockwidgets=" << m_dockWidgets.size()
                       << "; nestedwindows=" << m_nestedWindows.size();
}

DockRegistry::~DockRegistry()
{
}
