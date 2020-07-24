/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockRegistry_p.h"
#include "DockWidgetBase.h"
#include "Logging_p.h"
#include "DebugWindow_p.h"
#include "Position_p.h"
#include "widgets/MultiSplitter_p.h"
#include "quick/QmlTypes.h"

#include <QPointer>
#include <QDebug>
#include <QApplication>
#include <QWindow>

using namespace KDDockWidgets;

DockRegistry::DockRegistry(QObject *parent)
    : QObject(parent)
{
#ifdef KDDOCKWIDGETS_QTWIDGETS
    qApp->installEventFilter(this);

# ifdef DOCKS_DEVELOPER_MODE
    if (qEnvironmentVariableIntValue("KDDOCKWIDGETS_SHOW_DEBUG_WINDOW") == 1) {
        auto dv = new Debug::DebugWindow();
        dv->show();
    }
# endif

#else
    KDDockWidgets::registerQmlTypes();
#endif
}

DockRegistry::~DockRegistry()
{
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

void DockRegistry::checkSanityAll(bool dumpLayout)
{
    for (auto layout : qAsConst(m_layouts)) {
        layout->checkSanity();
        if (dumpLayout)
            layout->dumpLayout();
    }
}

bool DockRegistry::isProcessingAppQuitEvent() const
{
    return m_isProcessingAppQuitEvent;
}

bool DockRegistry::affinitiesMatch(const QStringList &affinities1, const QStringList &affinities2) const
{
    if (affinities1.isEmpty() && affinities2.isEmpty())
        return true;

    for (const QString &a1 : affinities1) {
        for (const QString &a2 : affinities2) {
            if (a1 == a2)
                return true;
        }
    }

    return false;
}

QStringList DockRegistry::mainWindowsNames() const
{
    QStringList names;
    names.reserve(m_mainWindows.size());
    for (auto mw : m_mainWindows)
        names.push_back(mw->uniqueName());

    return names;
}

QStringList DockRegistry::dockWidgetNames() const
{
    QStringList names;
    names.reserve(m_dockWidgets.size());
    for (auto dw : m_dockWidgets)
        names.push_back(dw->uniqueName());

    return names;
}

MainWindowBase::List DockRegistry::mainWindowsWithAffinity(const QStringList &affinities) const
{
    MainWindowBase::List result;

    for (auto mw : m_mainWindows) {
        const QStringList mwAffinities = mw->affinities();
        if (affinitiesMatch(mwAffinities, affinities))
            result << mw;
    }

    return result;
}

MultiSplitter *DockRegistry::layoutForItem(const Layouting::Item *item) const
{
    if (!item->hostWidget())
        return nullptr;

    if (auto ms = qobject_cast<MultiSplitter*>(item->hostWidget()->asQWidget()))
        return ms;

    return nullptr;
}

bool DockRegistry::itemIsInMainWindow(const Layouting::Item *item) const
{
    if (auto layout = layoutForItem(item))
        return layout->isInMainWindow();

    return false;
}

DockRegistry *DockRegistry::self()
{
    static QPointer<DockRegistry> s_dockRegistry;

    if (!s_dockRegistry) {
        s_dockRegistry = new DockRegistry();
    }

    return s_dockRegistry;
}

void DockRegistry::registerDockWidget(DockWidgetBase *dock)
{
    if (dock->uniqueName().isEmpty()) {
        qWarning() << Q_FUNC_INFO << "DockWidget" << dock << " doesn't have an ID";
    } else if (auto other = dockByName(dock->uniqueName())) {
        qWarning() << Q_FUNC_INFO << "Another DockWidget" << other << "with name" << dock->uniqueName() << " already exists." << dock;
    }

    m_dockWidgets << dock;
}

void DockRegistry::unregisterDockWidget(DockWidgetBase *dock)
{
    m_dockWidgets.removeOne(dock);
    maybeDelete();
}

void DockRegistry::registerMainWindow(MainWindowBase *mainWindow)
{
    if (mainWindow->uniqueName().isEmpty()) {
        qWarning() << Q_FUNC_INFO << "MainWindow" << mainWindow << " doesn't have an ID";
    } else if (auto other = mainWindowByName(mainWindow->uniqueName())) {
        qWarning() << Q_FUNC_INFO << "Another MainWindow" << other << "with name" << mainWindow->uniqueName() << " already exists." << mainWindow;
    }

    m_mainWindows << mainWindow;
}

void DockRegistry::unregisterMainWindow(MainWindowBase *mainWindow)
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

void DockRegistry::registerLayout(MultiSplitter *layout)
{
    m_layouts << layout;
}

void DockRegistry::unregisterLayout(MultiSplitter *layout)
{
    m_layouts.removeOne(layout);
}

void DockRegistry::registerFrame(Frame *frame)
{
    m_frames << frame;
}

void DockRegistry::unregisterFrame(Frame *frame)
{
    m_frames.removeOne(frame);
}

DockWidgetBase *DockRegistry::dockByName(const QString &name) const
{
    for (auto dock : qAsConst(m_dockWidgets)) {
        if (dock->uniqueName() == name)
            return dock;
    }

    return nullptr;
}

MainWindowBase *DockRegistry::mainWindowByName(const QString &name) const
{
    for (auto mainWindow : qAsConst(m_mainWindows)) {
        if (mainWindow->uniqueName() == name)
            return mainWindow;
    }

    return nullptr;
}

DockWidgetBase *DockRegistry::dockWidgetForGuest(QWidget *guest) const
{
    if (!guest)
        return nullptr;

    for (DockWidgetBase *dw : m_dockWidgets) {
        if (dw->widget() == guest)
            return dw;
    }

    return nullptr;
}

bool DockRegistry::isSane() const
{
    QSet<QString> names;
    for (auto dock : qAsConst(m_dockWidgets)) {
        const QString name = dock->uniqueName();
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

    names.clear();
    for (auto mainwindow : qAsConst(m_mainWindows)) {
        const QString name = mainwindow->uniqueName();
        if (name.isEmpty()) {
            qWarning() << "DockRegistry::isSane: MainWindow" << mainwindow << "is missing a name";
            return false;
        } else if (names.contains(name)) {
            qWarning() << "DockRegistry::isSane: mainWindow with duplicate names:" << name;
            return false;
        } else {
            names.insert(name);
        }

        if (!mainwindow->multiSplitter()->checkSanity())
            return false;
    }

    return true;
}

const DockWidgetBase::List DockRegistry::dockwidgets() const
{
    return m_dockWidgets;
}

const DockWidgetBase::List DockRegistry::dockWidgets(const QStringList &names)
{
    DockWidgetBase::List result;
    result.reserve(names.size());

    for (auto dw : qAsConst(m_dockWidgets)) {
        if (names.contains(dw->uniqueName()))
            result.push_back(dw);
    }

    return result;
}

const MainWindowBase::List DockRegistry::mainWindows(const QStringList &names)
{
    MainWindowBase::List result;
    result.reserve(names.size());

    for (auto mw : qAsConst(m_mainWindows)) {
        if (names.contains(mw->uniqueName()))
            result.push_back(mw);
    }

    return result;
}

const DockWidgetBase::List DockRegistry::closedDockwidgets() const
{
    DockWidgetBase::List result;
    result.reserve(m_dockWidgets.size());

    for (DockWidgetBase *dw : m_dockWidgets) {
        if (dw->parent() == nullptr && !dw->isVisible())
            result.push_back(dw);
    }

    return result;
}

const MainWindowBase::List DockRegistry::mainwindows() const
{
    return m_mainWindows;
}

const QVector<MultiSplitter *> DockRegistry::layouts() const
{
    return m_layouts;
}

const Frame::List DockRegistry::frames() const
{
    return m_frames;
}

const QVector<FloatingWindow *> DockRegistry::nestedwindows() const
{
    // Returns all the FloatingWindow which aren't being deleted
    QVector<FloatingWindow *> result;
    result.reserve(m_nestedWindows.size());
    for (FloatingWindow *fw : m_nestedWindows) {
        if (!fw->beingDeleted())
            result.push_back(fw);
    }

    return result;
}

FloatingWindow *DockRegistry::floatingWindowForHandle(QWindow *windowHandle) const
{
    for (FloatingWindow *fw : m_nestedWindows) {
        if (fw->windowHandle() == windowHandle)
            return fw;
    }

    return nullptr;
}

QVector<QWidget *> DockRegistry::topLevels(bool excludeFloatingDocks) const
{
    QVector<QWidget *> windows;
    windows.reserve(m_nestedWindows.size() + m_mainWindows.size());

    if (!excludeFloatingDocks) {
        for (FloatingWindow *fw : m_nestedWindows) {
            if (fw->isVisible())
                windows << fw;
        }
    }

    for (MainWindowBase *m : m_mainWindows) {
        if (m->isVisible())
            windows << m->topLevelWidget();
    }

    return windows;
}

void DockRegistry::clear(QStringList affinities)
{
    // Clears everything
    clear(m_dockWidgets, m_mainWindows, affinities);
}

void DockRegistry::clear(const DockWidgetBase::List &dockWidgets,
                         const MainWindowBase::List &mainWindows,
                         QStringList affinities)
{
    for (auto dw : qAsConst(dockWidgets)) {
        if (affinities.isEmpty() || affinitiesMatch(affinities, dw->affinities())) {
            dw->forceClose();
            dw->lastPositions().removePlaceholders();
        }
    }

    for (auto mw : qAsConst(mainWindows)) {
        if (affinities.isEmpty() || affinitiesMatch(affinities, mw->affinities())) {
            mw->multiSplitter()->rootItem()->clear();
        }
    }
}

void DockRegistry::ensureAllFloatingWidgetsAreMorphed()
{
    for (DockWidgetBase *dw : qAsConst(m_dockWidgets)) {
        if (dw->window() == dw && dw->isVisible())
            dw->morphIntoFloatingWindow();
    }
}

bool DockRegistry::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Quit && !m_isProcessingAppQuitEvent) {
        m_isProcessingAppQuitEvent = true;
        qApp->sendEvent(qApp, event);
        m_isProcessingAppQuitEvent = false;
        return true;
    } else if (event->type() == QEvent::Expose) {
        if (auto windowHandle = qobject_cast<QWindow*>(watched)) {
            if (FloatingWindow *fw = floatingWindowForHandle(windowHandle)) {
                // This floating window was exposed
                m_nestedWindows.removeOne(fw);
                m_nestedWindows.append(fw);
            }
        }
    }

    return false;
}
