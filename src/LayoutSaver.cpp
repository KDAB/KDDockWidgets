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

namespace KDDockWidgets
{

static QString name(QWidget *w)
{
    if (auto dw = qobject_cast<DockWidget*>(w))
        return dw->name();

    if (auto mw = qobject_cast<MainWindow*>(w))
        return mw->name();

    qWarning() << w;
    qFatal("Invalid Widget");
    return QString();
}

struct WindowState {
    explicit WindowState(QWidget *w, const QString &name_)
        : name(name_)
        , geometry(w->geometry())
        , isTopLevel(w->isTopLevel())
        , isVisible(w->isVisible())
    {
    }

    WindowState() = default;

    void restore(QWidget *w)
    {
        if (isTopLevel)
            w->setWindowFlag(Qt::Window, true);

        w->setVisible(isVisible);
        w->setGeometry(geometry);
    }

    static const QString s_magicMarker; // Just to validate serialize is simetric to deserialize
    QString name;
    QRect geometry;
    bool isTopLevel = false;
    bool isVisible = false;
};

struct LayoutState
{
    struct FrameState {
        explicit FrameState(Frame *f)
        {
            currentTabIndex = f->currentTabIndex();
            options = f->options();
            const auto docks = f->dockWidgets();
            dockWidgets.reserve(docks.size());
            for (DockWidget *dw : docks)
                dockWidgets.push_back(dw->name());
            id = f->id();
            geometry = f->geometry();
        }

        FrameState() = default;
        typedef QVector<FrameState> List;

        bool isCentralFrame() const
        {
            return options & Frame::Option_IsCentralFrame;
        }

        static const QString s_magicMarker; // Just to validate serialize is simetric to deserialize
        QStringList dockWidgets;
        int currentTabIndex = -1;
        Frame::Options options;
        QRect geometry;
        quint64 id = 0;
    };

    struct AnchorState {
        explicit AnchorState(Anchor *a)
            : orientation(a->orientation())
            , position(a->position())
            , type(a->type())
        {
            auto constructFrameState = [] (const ItemList &widgets, LayoutState::FrameState::List &frameStates) {
                for (Item *item : widgets) {
                    auto frame = item->frame();
                    if (!frame) {
                        qWarning() << Q_FUNC_INFO << "expected a frame" << item;
                        continue;
                    }

                    LayoutState::FrameState f(frame);
                    frameStates.push_back(f);
                }
            };

            constructFrameState(a->side1Items(), side1FrameStates);
            constructFrameState(a->side2Items(), side2FrameStates);

            const Anchor::List allAnchors = a->m_layout->anchors();
            index = allAnchors.indexOf(a);
            fromIndex = allAnchors.indexOf(a->from());
            toIndex = allAnchors.indexOf(a->to());
            followsIndex = a->followee() ? allAnchors.indexOf(a->followee())
                                         : -1;
        }

        AnchorState() = default;

        bool isValid(bool warn = false) const
        {
            if (index == -1 || toIndex == -1 || fromIndex == -1) {
                if (warn)
                    qWarning() << Q_FUNC_INFO << "Invalid indexes" << index << toIndex << fromIndex;
                return false;
            }

            return true;
        }

        bool isStatic() const
        {
            return type & Anchor::Type_Static;
        }

        typedef QVector<AnchorState> List;

        static const QString s_magicMarker; // Just to validate serialize is simetric to deserialize
        FrameState::List side1FrameStates;
        FrameState::List side2FrameStates;
        Qt::Orientation orientation;
        int position;
        Anchor::Type type;

        int index;
        int fromIndex;
        int toIndex;
        int followsIndex;
    };

    explicit LayoutState(const DropArea *a)
        : m_dropArea(a)
        , m_isInMainWindow(a->isInMainWindow())
        , m_isInFloatingWindow(a->isInFloatingWindow())
    {
        if (m_isInMainWindow) {
            // The name of the MainWindow, so we can restore it later.
            // Needed since we support multiple main windows.
            m_name = name(a->parentWidget());
        }
    }

    LayoutState() = default;

    bool isValid(bool warn = false) const
    {
        // Don't accept anything else
        if (!((m_isInMainWindow && !m_name.isEmpty()) || m_isInFloatingWindow)) {
            if (warn)
                qWarning() << Q_FUNC_INFO << "Invalid layout m_name=" << m_name
                           << "; m_isInFloatingWindow=" << m_isInFloatingWindow
                           << "; m_isInMainWindow=" << m_isInMainWindow;
            return false;
        }

        bool valid = true;
        for (const auto &anchorState : m_anchors)
            valid = valid && anchorState.isValid(warn);

        return valid;
    }

    void restore(DropArea *dropArea);

    static const QString s_magicMarker; // Just to validate serialize is simetric to deserialize
    const DropArea *m_dropArea = nullptr;
    bool m_isInMainWindow = false;
    bool m_isInFloatingWindow = false;
    QString m_name;
    AnchorState::List m_anchors;
};

const QString KDDockWidgets::WindowState::s_magicMarker = QStringLiteral("9ff8744b-72ee-40de-94a2-4d73d10d5180");
const QString KDDockWidgets::LayoutState::s_magicMarker = QStringLiteral("bac9948e-5f1b-4271-acc5-07f1708e2611");
const QString KDDockWidgets::LayoutState::FrameState::s_magicMarker = QStringLiteral("9240c11b-57c9-4011-ac54-899663a1fe31");
const QString KDDockWidgets::LayoutState::AnchorState::s_magicMarker = QStringLiteral("e520c60e-cf5d-4a30-b1a7-588d2c569851");


QDataStream &operator<<(QDataStream &ds, const KDDockWidgets::WindowState &s)
{
    ds << WindowState::s_magicMarker;
    ds << s.name;
    ds << s.geometry;
    ds << s.isVisible;
    ds << s.isTopLevel;

    return ds;
}

QDataStream &operator>>(QDataStream &ds, KDDockWidgets::WindowState &s)
{
    QString magic;
    ds >> magic;
    ds >> s.name;
    ds >> s.geometry;
    ds >> s.isVisible;
    ds >> s.isTopLevel;

    if (magic != WindowState::s_magicMarker)
        qWarning() << "WindowState: stream is corrupted";

    return ds;
}

QDataStream &operator<<(QDataStream &ds, const KDDockWidgets::LayoutState::FrameState &f)
{
    ds << LayoutState::FrameState::s_magicMarker;
    ds << f.options;
    ds << f.currentTabIndex;
    ds << f.dockWidgets;
    ds << f.id;
    ds << f.geometry;

    if (f.dockWidgets.isEmpty() && !f.isCentralFrame())
        qWarning() << "Serialized empty FrameState";

    return ds;
}

QDataStream &operator>>(QDataStream &ds, KDDockWidgets::LayoutState::FrameState &f)
{
    QString magic;
    ds >> magic;
    ds >> f.options;
    ds >> f.currentTabIndex;
    ds >> f.dockWidgets;
    ds >> f.id;
    ds >> f.geometry;

    if (f.dockWidgets.isEmpty() && !f.isCentralFrame())
        qWarning() << "Deserialized empty FrameState";

    if (magic != LayoutState::FrameState::s_magicMarker)
        qWarning() << "FrameState: stream is corrupted";

    return ds;
}

QDataStream &operator<<(QDataStream &ds, const KDDockWidgets::LayoutState::FrameState::List &list)
{
    ds << list.size();
    for (const auto &f : list)
        ds << f;

    return ds;
}

QDataStream &operator>>(QDataStream &ds, KDDockWidgets::LayoutState::FrameState::List &list)
{
    int numFrames;
    ds >> numFrames;
    list.reserve(numFrames);
    for (int i = 0; i < numFrames; ++i) {
        LayoutState::FrameState f;
        ds >> f;
        list.push_back(f);
    }

    return ds;
}

QDataStream &operator<<(QDataStream &ds, const KDDockWidgets::LayoutState::AnchorState &a)
{
    ds << LayoutState::AnchorState::s_magicMarker;
    ds << a.type;
    ds << a.position;
    int ori = a.orientation;
    ds << ori;
    ds << a.side1FrameStates;
    ds << a.side2FrameStates;
    ds << a.index;
    ds << a.toIndex;
    ds << a.fromIndex;
    ds << a.followsIndex;

    return ds;
}

QDataStream &operator>>(QDataStream &ds, KDDockWidgets::LayoutState::AnchorState &a)
{
    QString magic;
    ds >> magic;
    int type;
    ds >> type;
    a.type = static_cast<Anchor::Type>(type);
    ds >> a.position;
    int ori;
    ds >> ori;
    a.orientation = static_cast<Qt::Orientation>(ori);
    ds >> a.side1FrameStates;
    ds >> a.side2FrameStates;
    ds >> a.index;
    ds >> a.toIndex;
    ds >> a.fromIndex;
    ds >> a.followsIndex;

    if (magic != LayoutState::AnchorState::s_magicMarker)
        qWarning() << "AnchorState: stream is corrupted";

    return ds;
}

QDataStream &operator<<(QDataStream &ds, const KDDockWidgets::LayoutState &s)
{
    ds << LayoutState::s_magicMarker;
    ds << s.m_isInMainWindow;
    ds << s.m_isInFloatingWindow;
    ds << s.m_name;

    const auto anchors = s.m_dropArea->multiSplitterLayout()->anchors();
    ds << anchors.size();

    for (Anchor *anchor : anchors) {
        LayoutState::AnchorState anchorState(anchor);
        ds << anchorState;
    }

    if (!s.isValid(/*warn*/true))
        qWarning() << "Saving invalid layout";

    return ds;
}

QDataStream &operator>>(QDataStream &ds, KDDockWidgets::LayoutState &s)
{
    QString magic;
    ds >> magic;
    ds >> s.m_isInMainWindow;
    ds >> s.m_isInFloatingWindow;
    ds >> s.m_name;

    int numAnchors;
    ds >> numAnchors;
    for (int i = 0; i < numAnchors; ++i) {
        LayoutState::AnchorState anchorState;
        ds >> anchorState;
        s.m_anchors.push_back(anchorState);
    }

    if (magic != LayoutState::s_magicMarker)
        qWarning() << "LayoutState: stream is corrupted";

    return ds;
}

void LayoutState::restore(DropArea *dropArea)
{
     if (!dropArea) {
         qWarning() << Q_FUNC_INFO << "MainWindow is missing a drop area";
         Q_ASSERT(false);
         return;
     }

     if (!isValid(/*warn=*/ true)) {
         qWarning() << "Layout isn't valid";
         return;
     }

     if (!dropArea->checkSanity()) {
         qWarning() << "Drop area is not sane, refusing to restore";
         return;
     }

     MultiSplitterLayout *layout = dropArea->multiSplitterLayout();

     QHash<quint64, Frame*> framesById;
     QHash<int, Anchor*> anchorByIndex;
     // Create the Anchors
     for (const AnchorState &a : qAsConst(m_anchors)) {
         if (!a.isValid()) {
             qWarning() << "Ignoring invalid AnchorState for" << dropArea;
             continue;
         }

         Anchor *anchor = nullptr;
         if (a.isStatic()) {
             anchor = layout->staticAnchor(a.type);
             Q_ASSERT(anchor);
         } else {
             anchor = new Anchor(a.orientation, layout);
             if (a.followsIndex == -1) // doesn't follow another anchor
                 anchor->setPosition(a.position);
         }

         anchorByIndex.insert(a.index, anchor);
     }

     // Set the Anchor's to/from/follower
     for (const AnchorState &a : qAsConst(m_anchors)) {
         if (!a.isValid() || a.isStatic())
             continue;

         Anchor *anchor = anchorByIndex.value(a.index);
         Anchor *anchorTo = anchorByIndex.value(a.toIndex);
         Anchor *anchorFrom = anchorByIndex.value(a.fromIndex);

         anchor->setTo(anchorTo);
         anchor->setFrom(anchorFrom);
         if (a.followsIndex != -1)
             anchor->setFollowee(anchorByIndex.value(a.followsIndex));
     }

     if (Item *item = dropArea->centralFrame()) {
         // Remove the built-in frame, it's much easier to just restore everything
         layout->removeItem(item);
     }

     for (const AnchorState &a : qAsConst(m_anchors)) {
         if (!a.isValid())
             continue;

         Anchor *anchor = anchorByIndex.value(a.index);

         auto restoreFrames = [&framesById, anchor, layout] (Anchor::Side side, const LayoutState::FrameState::List &frameStates) {
             for (LayoutState::FrameState f : qAsConst(frameStates)) {
                 Frame *frame = nullptr;
                 if (framesById.contains(f.id)) {
                     frame = framesById.value(f.id);
                 } else {
                     frame = new Frame(nullptr, f.options);
                     frame->setGeometry(f.geometry);
                     auto item = new Item(frame, layout);
                     framesById.insert(f.id, frame);

                     // qCDebug(restoring) << "Restoring frame name =" << frameName << "; numDocks=" << f.dockWidgets.size();
                     for (const QString &dockWidgetName : qAsConst(f.dockWidgets)) {
                         DockWidget *dw = DockRegistry::self()->dockByName(dockWidgetName);
                         frame->addWidget(dw);
                     }

                     frame->setCurrentTabIndex(f.currentTabIndex);
                     layout->addItems_internal({ item }, /*updateSizeConstraints=*/ false);

                 }

                 anchor->addItem(layout->itemForFrame(frame), side);
             }
         };

         restoreFrames(Anchor::Side1, a.side1FrameStates);
         restoreFrames(Anchor::Side2, a.side2FrameStates);
     }

     layout->updateSizeConstraints();
     if (!dropArea->checkSanity()) {
         qWarning() << "Restored an invalid layout, this should not happen";
     }
}

}

class KDDockWidgets::LayoutSaver::Private
{
public:
    Private()
        : m_dockRegistry(DockRegistry::self())
    {
    }

    void serializeWindowGeometry(QDataStream &ds, QWidget *topLevel);
    void deserializeWindowGeometry(QDataStream &ds, QWidget *topLevel);

    DockWidget::List floatingDockWidgets() const;
    MainWindow::List mainWindows() const;
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
        d->serializeWindowGeometry(ds, floatingWindow);
        ds << floatingWindow;
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
        FloatingWindow::createFromDataStream(ds);
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

/*
QByteArray LayoutSaver::serializeLayout_old() const
{
    QByteArray result;
    QDataStream ds(&result, QIODevice::WriteOnly);

    // Save floating dock widgets (just geometry and visibility):
    const DockWidget::List floatingDocks = d->floatingDockWidgets();
    ds << floatingDocks.size();
    for (auto floating : floatingDocks) {
        WindowState state(floating, floating->name());
        ds << state;
    }

    // Save main windows (geometry, visibility and dockwidget layout):
    auto mainWindows = d->mainWindows();

    ds << mainWindows.size();
    for (auto mainWindow : mainWindows) {
        WindowState windowState(mainWindow, mainWindow->name());
        LayoutState layoutState(mainWindow->dropArea());
        ds << windowState;
        ds << layoutState;
    }

    // Save the floating nested windows:
    const auto floatingNestedWindows = d->m_dockRegistry->nestedwindows();
    ds << floatingNestedWindows.size();
    for (auto window : floatingNestedWindows) {
        WindowState windowState(window, QString());
        LayoutState layoutState(window->dropArea());
        ds << windowState;
        ds << layoutState;
    }

    return result;
}

void LayoutSaver::restoreLayout_old(const QByteArray &data)
{
    if (data.isEmpty())
        return;

    // Hide all dockwidgets and unparent them from any layout before starting restore
    d->m_dockRegistry->clear();

    QDataStream ds(data);

    // Restore geometry and visibility of floating dock widgets:
    int numFloating;
    ds >> numFloating;
    DockWidget::List floatingDocks;
    floatingDocks.reserve(numFloating);
    for (int i = 0; i < numFloating; i++) {
        WindowState windowState;
        ds >> windowState;

        if (DockWidget *dw = d->m_dockRegistry->dockByName(windowState.name)) {
            qCDebug(restoring) << "Restoring dockwidget" << dw << "; to=" << windowState.geometry;
            windowState.restore(dw);
        } else {
            qWarning() << "Unable to restore DockWidget" << windowState.name;
        }
    }

    // Restore geometry and visibility of main windows:
    int numMainWindows;
    ds >> numMainWindows;
    MainWindow::List mainWindows;
    mainWindows.reserve(numMainWindows);
    for (int i = 0; i < numMainWindows; i++) {
        WindowState windowState;
        LayoutState layoutState;
        ds >> windowState;
        ds >> layoutState;
        MainWindow *w = d->m_dockRegistry->mainWindowByName(windowState.name);
        if (!w) {
            qWarning() << "Unable to restore MainWindow" << windowState.name
                     << "; You need to create it before restoring.";
            continue;
        }

        if (windowState.isTopLevel)
            windowState.restore(w);

        qCDebug(restoring) << "Restoring MainWindow";
        layoutState.restore(w->dropArea());
    }

    // Restore floating nested windows
    int numNestedWindows;
    ds >> numNestedWindows;

    for (int i = 0; i < numNestedWindows; i++) {
        WindowState windowState;
        LayoutState layoutState;
        ds >> windowState;
        ds >> layoutState;

        qCDebug(restoring) << "Restoring FloatingWindow";
        auto fw = new FloatingWindow();
        windowState.restore(fw);
        layoutState.restore(fw->dropArea());
    }
}
*/
bool LayoutSaver::restoreInProgress()
{
    return Private::s_restoreInProgress;
}

DockWidget::List LayoutSaver::Private::floatingDockWidgets() const
{
    const auto dockwidgets = m_dockRegistry->dockwidgets();
    DockWidget::List result;
    result.reserve(dockwidgets.size());
    std::copy_if(dockwidgets.cbegin(), dockwidgets.cend(),
                 std::back_inserter(result), [] (DockWidget *dw) {
        return dw->isFloating() && dw->window() == dw; // because it could be in a nested window (FloatingWindow)
    });
    return result;
}

MainWindow::List LayoutSaver::Private::mainWindows() const
{
    return m_dockRegistry->mainwindows();
}

