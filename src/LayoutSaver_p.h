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

#ifndef KD_LAYOUTSAVER_P_H
#define KD_LAYOUTSAVER_P_H

#include "LayoutSaver.h"
#include "KDDockWidgets.h"

#include <QRect>
#include <QDataStream>
#include <QDebug>
#include <QScreen>
#include <QApplication>
#include <QJsonDocument>

#include <memory>

#define ANCHOR_MAGIC_MARKER "e520c60e-cf5d-4a30-b1a7-588d2c569851"
#define MULTISPLITTER_LAYOUT_MAGIC_MARKER "bac9948e-5f1b-4271-acc5-07f1708e2611"

/**
  * Bump whenever the format changes, so we can still load old layouts.
  * version 1: Initial version
  * version 2: Introduced MainWindow::screenSize and FloatingWindow::screenSize
  */
#define KDDOCKWIDGETS_SERIALIZATION_VERSION 2


namespace KDDockWidgets {

template <typename T>
typename T::List fromVariantList(const QVariantList &listV)
{
    typename T::List result;

    result.reserve(listV.size());
    for (const QVariant &v : listV) {
        T t;
        t.fromVariantMap(v.toMap());
        result.push_back(t);
    }

    return result;
}

template <typename T>
QVariantList toVariantList(const typename T::List &list)
{
    QVariantList result;
    result.reserve(list.size());
    for (const T &v : list)
        result.push_back(v.toVariantMap());

    return result;
}

struct LayoutSaver::Placeholder
{
    typedef QVector<LayoutSaver::Placeholder> List;

    QVariantMap toVariantMap() const;
    void fromVariantMap(const QVariantMap &map);

    bool isFloatingWindow;
    int indexOfFloatingWindow;
    int itemIndex;
    QString mainWindowUniqueName;
};

///@brief contains info about how a main window is scaled.
///Used for RestoreOption_RelativeToMainWindow
struct LayoutSaver::ScalingInfo
{
    ScalingInfo() = default;
    explicit ScalingInfo(const QString &mainWindowId, QRect savedMainWindowGeo);

    bool isValid() const {
        return heightFactor > 0 && widthFactor > 0 && !((qFuzzyCompare(widthFactor, 1) && qFuzzyCompare(heightFactor, 1)));
    }

    void translatePos(QPoint &) const;
    void applyFactorsTo(QPoint &) const;
    void applyFactorsTo(QSize &) const;
    void applyFactorsTo(QRect &) const;

    QString mainWindowName;
    QRect savedMainWindowGeometry;
    QRect realMainWindowGeometry;
    double heightFactor = -1;
    double widthFactor = -1;
};

struct LayoutSaver::LastPosition
{
    QRect lastFloatingGeometry;
    int tabIndex;
    bool wasFloating;
    LayoutSaver::Placeholder::List placeholders;

    /// Iterates throught the layout and patches all absolute sizes. See RestoreOption_RelativeToMainWindow.
    void scaleSizes(const ScalingInfo &scalingInfo);

    QVariantMap toVariantMap() const;
    void fromVariantMap(const QVariantMap &map);
};

struct DOCKS_EXPORT LayoutSaver::DockWidget
{
    // Using shared ptr, as we need to modify shared instances
    typedef std::shared_ptr<LayoutSaver::DockWidget> Ptr;
    typedef QVector<Ptr> List;
    static QHash<QString, Ptr> s_dockWidgets;

    bool isValid() const;

    /// Iterates throught the layout and patches all absolute sizes. See RestoreOption_RelativeToMainWindow.
    void scaleSizes(const ScalingInfo &scalingInfo);

    static Ptr dockWidgetForName(const QString &name)
    {
        auto dw = s_dockWidgets.value(name);
        if (dw)
            return dw;

        dw = Ptr(new LayoutSaver::DockWidget);
        dw->uniqueName = name;

        return dw;
    }

    QVariantMap toVariantMap() const;
    void fromVariantMap(const QVariantMap &map);

    QString uniqueName;
    LayoutSaver::LastPosition lastPosition;

private:
    DockWidget() {}
};


inline QVariantList toVariantList(const LayoutSaver::DockWidget::List &list)
{
    QVariantList result;
    result.reserve(list.size());
    for (const auto &dw : list)
        result.push_back(dw->toVariantMap());

    return result;
}

inline QVariantList dockWidgetNames(const LayoutSaver::DockWidget::List &list)
{
    QVariantList result;
    result.reserve(list.size());
    for (auto &dw : list)
        result.push_back(dw->uniqueName);

    return result;
}

struct LayoutSaver::Frame
{
    bool isValid() const;

    /// Iterates throught the layout and patches all absolute sizes. See RestoreOption_RelativeToMainWindow.
    void scaleSizes(const ScalingInfo &scalingInfo);

    QVariantMap toVariantMap() const;
    void fromVariantMap(const QVariantMap &map);

    bool isNull = true;
    QString objectName;
    QRect geometry;
    unsigned int options;
    int currentTabIndex;

    LayoutSaver::DockWidget::List dockWidgets;
};

struct LayoutSaver::Item
{
    typedef QVector<LayoutSaver::Item> List;

    bool isValid(const MultiSplitterLayout &) const;
    /// Iterates throught the layout and patches all absolute sizes. See RestoreOption_RelativeToMainWindow.
    void scaleSizes(const ScalingInfo &scalingInfo);

    QVariantMap toVariantMap() const;
    void fromVariantMap(const QVariantMap &map);

    QString objectName;
    bool isPlaceholder;
    QRect geometry;
    QSize minSize;
    int indexOfLeftAnchor;
    int indexOfTopAnchor;
    int indexOfRightAnchor;
    int indexOfBottomAnchor;
    LayoutSaver::Frame frame;
};

struct LayoutSaver::Anchor
{
    typedef QVector<LayoutSaver::Anchor> List;

    bool isValid(const LayoutSaver::MultiSplitterLayout &layout) const;

    QVariantMap toVariantMap() const;
    void fromVariantMap(const QVariantMap &map);
    void scaleSizes(const ScalingInfo &);

    bool isVertical() const;

    QString objectName;
    QRect geometry;
    int orientation;
    int type;
    int indexOfFrom;
    int indexOfTo;
    int indexOfFollowee;
    QVector<int> side1Items;
    QVector<int> side2Items;
};

struct LayoutSaver::MultiSplitterLayout
{
    bool isValid() const;
    /// Iterates throught the layout and patches all absolute sizes. See RestoreOption_RelativeToMainWindow.
    void scaleSizes(const ScalingInfo &scalingInfo);

    QVariantMap toVariantMap() const;
    void fromVariantMap(const QVariantMap &map);

    LayoutSaver::Anchor::List anchors;
    LayoutSaver::Item::List items;
    QSize minSize;
    QSize size;
};

struct LayoutSaver::FloatingWindow
{
    typedef QVector<LayoutSaver::FloatingWindow> List;

    bool isValid() const;

    /// Iterates throught the layout and patches all absolute sizes. See RestoreOption_RelativeToMainWindow.
    void scaleSizes(const ScalingInfo &);

    QVariantMap toVariantMap() const;
    void fromVariantMap(const QVariantMap &map);

    LayoutSaver::MultiSplitterLayout multiSplitterLayout;
    int parentIndex = -1;
    QRect geometry;
    int screenIndex;
    QSize screenSize;  // for relative-size restoring
    bool isVisible = true;
};

struct LayoutSaver::MainWindow
{
public:
    typedef QVector<LayoutSaver::MainWindow> List;

    bool isValid() const;

    /// Iterates throught the layout and patches all absolute sizes. See RestoreOption_RelativeToMainWindow.
    void scaleSizes();

    QVariantMap toVariantMap() const;
    void fromVariantMap(const QVariantMap &map);

    KDDockWidgets::MainWindowOptions options;
    LayoutSaver::MultiSplitterLayout multiSplitterLayout;
    QString uniqueName;
    QRect geometry;
    int screenIndex;
    QSize screenSize;  // for relative-size restoring
    bool isVisible;

    ScalingInfo scalingInfo;
};

///@brief we serialize some info about screens, so eventually we can make restore smarter when switching screens
///Not used currently, but nice to have in the json already
struct LayoutSaver::ScreenInfo
{
    typedef QVector<LayoutSaver::ScreenInfo> List;

    QVariantMap toVariantMap() const;
    void fromVariantMap(const QVariantMap &map);

    int index;
    QRect geometry;
    QString name;
    double devicePixelRatio;
};

struct LayoutSaver::Layout
{
public:

    Layout() {
        s_currentLayoutBeingRestored = this;

        const QList<QScreen*> screens = qApp->screens();
        for (int i = 0; i < screens.size(); ++i) {
            ScreenInfo info;
            info.index = i;
            info.geometry = screens[i]->geometry();
            info.name = screens[i]->name();
            info.devicePixelRatio = screens[i]->devicePixelRatio();
            screenInfo.push_back(info);
        }
    }

    ~Layout() {
        s_currentLayoutBeingRestored = nullptr;
    }

    bool isValid() const;

    bool fillFrom(const QByteArray &serialized);
    QByteArray toJson() const;
    bool fromJson(const QByteArray &jsonData);
    QVariantMap toVariantMap() const;
    void fromVariantMap(const QVariantMap &map);

    /// Iterates throught the layout and patches all absolute sizes. See RestoreOption_RelativeToMainWindow.
    void scaleSizes();

    friend QDataStream &operator>>(QDataStream &ds, LayoutSaver::Frame *frame);
    static LayoutSaver::Layout* s_currentLayoutBeingRestored;

    LayoutSaver::MainWindow mainWindowForIndex(int index) const;

    int serializationVersion = KDDOCKWIDGETS_SERIALIZATION_VERSION;
    LayoutSaver::MainWindow::List mainWindows;
    LayoutSaver::FloatingWindow::List floatingWindows;
    LayoutSaver::DockWidget::List closedDockWidgets;
    LayoutSaver::DockWidget::List allDockWidgets;
    ScreenInfo::List screenInfo;
};

inline QDataStream &operator>>(QDataStream &ds, LayoutSaver::ScreenInfo *info)
{
    ds >> info->index;
    ds >> info->geometry;
    ds >> info->name;
    ds >> info->devicePixelRatio;

    return ds;
}

inline QDataStream &operator>>(QDataStream &ds, LayoutSaver::Placeholder *p)
{
    ds >> p->isFloatingWindow;
    if (p->isFloatingWindow)
        ds >> p->indexOfFloatingWindow;
    else
        ds >> p->mainWindowUniqueName;

    ds >> p->itemIndex;

    return ds;
}

inline  QDataStream &operator>>(QDataStream &ds, LayoutSaver::Anchor *a)
{
    QString marker;

    ds >> marker;
    if (marker != QLatin1String(ANCHOR_MAGIC_MARKER))
        qWarning() << Q_FUNC_INFO << "Corrupt stream";

    ds >> a->objectName;
    ds >> a->geometry;
    ds >> a->orientation;
    ds >> a->type;
    ds >> a->indexOfFrom;
    ds >> a->indexOfTo;
    ds >> a->indexOfFollowee;
    ds >> a->side1Items;
    ds >> a->side2Items;

    return ds;
}

inline QDataStream &operator>>(QDataStream &ds, LayoutSaver::Frame *frame)
{
    int numDockWidgets;
    frame->dockWidgets.clear();
    frame->isNull = false;

    ds >> frame->objectName;
    ds >> frame->geometry;

    if (LayoutSaver::Layout::s_currentLayoutBeingRestored->serializationVersion >= 2) {
        QSize sz;
        ds >> sz; // deprecated field, just discard
    }

    ds >> frame->options;
    ds >> frame->currentTabIndex;
    ds >> numDockWidgets;

    for (int i = 0; i < numDockWidgets; ++i) {
        QString name;
        ds >> name;
        auto dw = LayoutSaver::DockWidget::dockWidgetForName(name);
        frame->dockWidgets.push_back(dw);
    }

    return ds;
}

inline QDataStream &operator>>(QDataStream &ds, LayoutSaver::Item *item)
{
    ds >> item->objectName;
    ds >> item->isPlaceholder;
    ds >> item->geometry;
    ds >> item->minSize;

    ds >> item->indexOfLeftAnchor;
    ds >> item->indexOfTopAnchor;
    ds >> item->indexOfRightAnchor;
    ds >> item->indexOfBottomAnchor;

    bool hasFrame;
    ds >> hasFrame;
    if (hasFrame) {
        ds >> &item->frame;
        item->frame.isNull = false;
    } else {
        item->frame.isNull = true;
    }

    return ds;
}

inline QDataStream &operator>>(QDataStream &ds, LayoutSaver::MultiSplitterLayout *l)
{
    int numItems;
    int numAnchors;
    QString marker;
    ds >> marker;

    if (marker != QLatin1String(MULTISPLITTER_LAYOUT_MAGIC_MARKER))
        qWarning() << Q_FUNC_INFO << "Corrupt stream, invalid magic";

    ds >> l->size;
    ds >> l->minSize;
    ds >> numItems;
    ds >> numAnchors;

    l->items.clear();
    l->anchors.clear();

    for (int i = 0 ; i < numItems; ++i) {
        LayoutSaver::Item item;
        ds >> &item;
        l->items.push_back(item);
    }

    for (int i = 0 ; i < numAnchors; ++i) {
        LayoutSaver::Anchor a;
        ds >> &a;
        l->anchors.push_back(a);
    }

    return ds;
}

inline QDataStream &operator>>(QDataStream &ds, LayoutSaver::LastPosition *lp)
{
    int numPlaceholders;
    ds >> numPlaceholders;

    lp->placeholders.clear();
    for (int i = 0 ; i < numPlaceholders; ++i) {
        LayoutSaver::Placeholder p;
        ds >> &p;
        lp->placeholders.push_back(p);
    }

    ds >> lp->lastFloatingGeometry;
    ds >> lp->tabIndex;
    ds >> lp->wasFloating;

    return ds;
}

inline QDataStream &operator>>(QDataStream &ds, LayoutSaver::FloatingWindow *fw)
{
    ds >> fw->parentIndex;
    ds >> fw->geometry;
    if (LayoutSaver::Layout::s_currentLayoutBeingRestored->serializationVersion >= 2) {
        ds >> fw->screenIndex;
        ds >> fw->screenSize;
    }

    ds >> fw->isVisible;
    ds >> &fw->multiSplitterLayout;
    return ds;
}

inline QDataStream &operator>>(QDataStream &ds, LayoutSaver::MainWindow *m)
{
    ds >> m->uniqueName;
    ds >> m->geometry;
    if (LayoutSaver::Layout::s_currentLayoutBeingRestored->serializationVersion >= 2) {
        ds >> m->screenIndex;
        ds >> m->screenSize;
    }
    ds >> m->isVisible;
    ds >> m->options;
    ds >> &m->multiSplitterLayout;
    return ds;
}

inline QDataStream &operator>>(QDataStream &ds, LayoutSaver::Layout *l)
{
    LayoutSaver::DockWidget::s_dockWidgets.clear();
    int numMainWindows;
    int numFloatingWindows;
    int numClosedDockWidgets;
    int numAllDockWidgets;
    int numScreenInfo;

    ds >> l->serializationVersion;

    ds >> numMainWindows;
    l->mainWindows.clear();
    for (int i = 0; i < numMainWindows; ++i) {
        LayoutSaver::MainWindow m;
        ds >> &m;
        l->mainWindows.push_back(m);
    }

    ds >> numFloatingWindows;
    l->floatingWindows.clear();
    for (int i = 0; i < numFloatingWindows; ++i) {
        LayoutSaver::FloatingWindow m;
        ds >> &m;
        l->floatingWindows.push_back(m);
    }

    ds >> numClosedDockWidgets;
    l->closedDockWidgets.clear();
    for (int i = 0; i < numClosedDockWidgets; ++i) {
        QString name;
        ds >> name;
        auto dw = LayoutSaver::DockWidget::dockWidgetForName(name);
        l->closedDockWidgets.push_back(dw);
    }

    ds >> numAllDockWidgets;
    l->allDockWidgets.clear();
    for (int i = 0; i < numAllDockWidgets; ++i) {
        QString name;
        ds >> name;

        auto dw = LayoutSaver::DockWidget::dockWidgetForName(name);
        ds >> &dw->lastPosition;
        l->allDockWidgets.push_back(dw);
    }


    if (LayoutSaver::Layout::s_currentLayoutBeingRestored->serializationVersion >= 2) {
        ds >> numScreenInfo;
        l->screenInfo.clear();
        l->screenInfo.reserve(numScreenInfo);
        for (int i = 0; i < numScreenInfo; ++i) {
            LayoutSaver::ScreenInfo info;
            ds >> &info;
            l->screenInfo.push_back(info);
        }
    }

    return ds;
}

}

#endif
