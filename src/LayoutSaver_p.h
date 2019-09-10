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

#ifndef KD_LAYOUTSAVER_P_H
#define KD_LAYOUTSAVER_P_H

#include "LayoutSaver.h"
#include "multisplitter/Anchor_p.h"
#include "multisplitter/MultiSplitterLayout_p.h"

#include <QDataStream>

#define KDDOCKWIDGETS_SERIALIZATION_VERSION 1

namespace KDDockWidgets {


struct LayoutSaver::Placeholder
{
    typedef QVector<LayoutSaver::Placeholder> List;
    bool isFloatingWindow;
    int indexOfFloatingWindow;
    int itemIndex;
    QString mainWindowUniqueName;
};


struct LayoutSaver::LastPosition
{
    QRect lastFloatingGeometry;
    int tabIndex;
    bool wasFloating;
    LayoutSaver::Placeholder::List placeholders;
};

struct LayoutSaver::DockWidget
{
    typedef QVector<LayoutSaver::DockWidget> List;

    QString uniqueName;
    LayoutSaver::LastPosition lastPosition;
};

struct LayoutSaver::Frame
{
    bool valid = true;
    QString objectName;
    QRect geometry;
    int options;
    int currentTabIndex;

    LayoutSaver::DockWidget::List dockWidgets;
};

struct LayoutSaver::Item
{
    typedef QVector<LayoutSaver::Item> List;

    QString objectName;
    bool isPlaceholder;
    QRect geometry;
    QSize minSize;

    int indexOfLeftAnchor;
    int indexOfTopAnchor;
    int indexOfRighttAnchor;
    int indexOfBottomAnchor;

    LayoutSaver::Frame frame;
};

struct LayoutSaver::Anchor
{
    typedef QVector<LayoutSaver::Anchor> List;

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
    LayoutSaver::Anchor::List anchors;
    LayoutSaver::Item::List items;
    QSize minSize;
    QSize size;
};

struct LayoutSaver::FloatingWindow
{
    typedef QVector<LayoutSaver::FloatingWindow> List;

    LayoutSaver::MultiSplitterLayout multiSplitterLayout;
    int parentIndex = -1;
    QRect geometry;
    bool isVisible = true;
};

struct LayoutSaver::MainWindow
{
public:
    typedef QVector<LayoutSaver::MainWindow> List;

    KDDockWidgets::MainWindowOptions options;
    LayoutSaver::MultiSplitterLayout multiSplitterLayout;
    QString uniqueName;
    QRect geometry;
    bool isVisible;
};

struct LayoutSaver::Layout
{
public:

    void fillFrom(const QByteArray &serialized);

    int serializationVersion = KDDOCKWIDGETS_SERIALIZATION_VERSION;
    LayoutSaver::MainWindow::List mainWindows;
    LayoutSaver::FloatingWindow::List floatingWindows;
    LayoutSaver::DockWidget::List closedDockWidgets;
    LayoutSaver::DockWidget::List allDockWidgets;
};

QDataStream &operator<<(QDataStream &ds, LayoutSaver::Placeholder *p)
{
    ds << p->isFloatingWindow;
    if (p->isFloatingWindow)
        ds << p->indexOfFloatingWindow;
    else
        ds << p->mainWindowUniqueName;

    ds << p->itemIndex;

    return ds;
}

QDataStream &operator>>(QDataStream &ds, LayoutSaver::Placeholder *p)
{
    ds >> p->isFloatingWindow;
    if (p->isFloatingWindow)
        ds >> p->indexOfFloatingWindow;
    else
        ds >> p->mainWindowUniqueName;

    ds >> p->itemIndex;

    return ds;
}

QDataStream &operator<<(QDataStream &ds, LayoutSaver::Anchor *a)
{
    ds << Anchor::s_magicMarker;
    ds << a->objectName;
    ds << a->geometry;
    ds << a->orientation;
    ds << a->type;
    ds << a->indexOfFrom;
    ds << a->indexOfTo;
    ds << a->indexOfFollowee;
    ds << a->side1Items;
    ds << a->side2Items;

    return ds;
}

QDataStream &operator>>(QDataStream &ds, LayoutSaver::Anchor *a)
{
    QString marker;

    ds >> marker;
    if (marker != Anchor::s_magicMarker)
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

QDataStream &operator<<(QDataStream &ds, LayoutSaver::DockWidget *dw)
{
    ds << dw->uniqueName;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, LayoutSaver::DockWidget *dw)
{
    ds >> dw->uniqueName;
    return ds;
}

QDataStream &operator<<(QDataStream &ds, LayoutSaver::Frame *frame)
{
    ds << frame->objectName;
    ds << frame->geometry;
    ds << frame->options;
    ds << frame->currentTabIndex;
    ds << frame->dockWidgets.size();

    for (auto &dock : frame->dockWidgets) {
        ds << &dock;
    }

    return ds;
}

QDataStream &operator>>(QDataStream &ds, LayoutSaver::Frame *frame)
{
    int numDockWidgets;
    frame->dockWidgets.clear();

    ds >> frame->objectName;
    ds >> frame->geometry;
    ds >> frame->options;
    ds >> frame->currentTabIndex;
    ds >> numDockWidgets;

    for (int i = 0; i < numDockWidgets; ++i) {
        LayoutSaver::DockWidget dock;
        ds >> &dock;
        frame->dockWidgets.push_back(dock);
    }

    return ds;
}

QDataStream &operator<<(QDataStream &ds, LayoutSaver::Item *item)
{
    ds << item->objectName;
    ds << item->isPlaceholder;
    ds << item->geometry;
    ds << item->minSize;

    ds << item->indexOfLeftAnchor;
    ds << item->indexOfTopAnchor;
    ds << item->indexOfRighttAnchor;
    ds << item->indexOfBottomAnchor;

    ds << item->frame.valid;
    if (item->frame.valid) {
        ds << &item->frame;
    }

    return ds;
}

QDataStream &operator>>(QDataStream &ds, LayoutSaver::Item *item)
{
    ds >> item->objectName;
    ds >> item->isPlaceholder;
    ds >> item->geometry;
    ds >> item->minSize;

    ds >> item->indexOfLeftAnchor;
    ds >> item->indexOfTopAnchor;
    ds >> item->indexOfRighttAnchor;
    ds >> item->indexOfBottomAnchor;

    bool hasFrame;
    ds >> hasFrame;
    if (hasFrame) {
        ds >> &item->frame;
    } else {
        item->frame.valid = false;
    }

    return ds;
}

QDataStream &operator<<(QDataStream &ds, LayoutSaver::MultiSplitterLayout *l)
{
    ds << MultiSplitterLayout::s_magicMarker;

    ds << l->size;
    ds << l->minSize;
    ds << l->items.size();
    ds << l->anchors.size();

    for (auto &item : l->items)
        ds << &item;

    for (auto &anchor : l->anchors)
        ds << &anchor;

    return ds;
}

QDataStream &operator>>(QDataStream &ds, LayoutSaver::MultiSplitterLayout *l)
{
    int numItems;
    int numAnchors;
    QString marker;
    ds >> marker;

    if (marker != MultiSplitterLayout::s_magicMarker)
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

QDataStream &operator<<(QDataStream &ds, LayoutSaver::LastPosition *lp)
{
    ds << lp->placeholders.size();

    for (auto &p : lp->placeholders) {
        ds << &p;
    }

    ds << lp->lastFloatingGeometry;
    ds << lp->tabIndex;
    ds << lp->wasFloating;

    return ds;
}

QDataStream &operator>>(QDataStream &ds, LayoutSaver::LastPosition *lp)
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

QDataStream &operator<<(QDataStream &ds, LayoutSaver::FloatingWindow *fw)
{
    ds << fw->parentIndex;
    ds << fw->geometry;
    ds << fw->isVisible;
    ds << &fw->multiSplitterLayout;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, LayoutSaver::FloatingWindow *fw)
{
    ds >> fw->parentIndex;
    ds >> fw->geometry;
    ds >> fw->isVisible;
    ds >> &fw->multiSplitterLayout;
    return ds;
}

QDataStream &operator<<(QDataStream &ds, LayoutSaver::MainWindow *m)
{
    ds << m->uniqueName;
    ds << m->geometry;
    ds << m->isVisible;
    ds << m->options;
    ds << &m->multiSplitterLayout;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, LayoutSaver::MainWindow *m)
{
    ds >> m->uniqueName;
    ds >> m->geometry;
    ds >> m->isVisible;
    ds >> m->options;
    ds >> &m->multiSplitterLayout;
    return ds;
}

QDataStream &operator<<(QDataStream &ds, LayoutSaver::Layout *l)
{
    ds << l->serializationVersion;
    ds << l->mainWindows.size();
    for (auto &m: l->mainWindows) {
        ds << &m;
    }

    ds << l->floatingWindows.size();
    for (auto &fw: l->floatingWindows) {
        ds << &fw;
    }

    ds << l->closedDockWidgets.size();
    for (auto &dw: l->closedDockWidgets) {
        ds << &dw;
    }

    ds << l->allDockWidgets.size();
    for (auto &dw: l->allDockWidgets) {
        ds << dw.uniqueName;
        ds << &dw.lastPosition;
    }

    return ds;
}

QDataStream &operator>>(QDataStream &ds, LayoutSaver::Layout *l)
{
    int numMainWindows;
    int numFloatingWindows;
    int numClosedDockWidgets;
    int numAllDockWidgets;

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
        LayoutSaver::DockWidget m;
        ds >> &m;
        l->closedDockWidgets.push_back(m);
    }

    ds >> numAllDockWidgets;
    l->allDockWidgets.clear();
    for (int i = 0; i < numAllDockWidgets; ++i) {
        QString name;

        LayoutSaver::DockWidget m;
        ds >> m.uniqueName;
        ds >> &m.lastPosition;

        l->allDockWidgets.push_back(m);
    }

    return ds;
}

}



#endif
