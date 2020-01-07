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
 * @brief Tree Widget to show the object tree. Used for debugging only, for apps that don't support GammaRay.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef OBJECTVIEWER_H
#define OBJECTVIEWER_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTreeView>
#include <QPointer>
#include <QObject>
#include <QMenu>

QT_BEGIN_NAMESPACE
class QStandardItem;
QT_END_NAMESPACE

namespace KDDockWidgets {
namespace Debug {

class ObjectViewer : public QWidget //clazy:exclude=missing-qobject-macro
{
public:
    explicit ObjectViewer(QWidget *parent = nullptr);

    void refresh();

private:
    void dumpSelectedWidgetToPng();
    void updateSelectedWidget();
    void toggleVisible();
    void dumpWindows();
    QString nameForObj(QObject *o) const;
    void add(QObject *obj, QStandardItem *parent);
    void remove(QObject *obj);
    void onSelectionChanged();
    void printProperties(QObject *) const;
    QObject* selectedObject() const;
    QWidget *selectedWidget() const;
    void updateItemAppearence(QStandardItem*);
    QObject *objectForItem(QStandardItem*) const;
    QWidget *widgetForItem(QStandardItem*) const;

#ifdef Q_OS_WIN
    void sendHitTest();
#endif

    QTreeView m_treeView;
    QStandardItemModel m_model;
    QPointer<QObject> m_selectedObject;
    QMenu m_menu;
    bool m_highlightsWidget = true;
    bool m_ignoreMenus = true;
    bool m_ignoreShortcuts = true;
    bool m_ignoreToolBars = true;
    QHash<QObject*, QStandardItem*> m_itemMap;

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
};
}
}

#endif
