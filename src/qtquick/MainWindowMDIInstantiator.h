/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_MDIMAIN_WINDOW_INSTANTIATOR_P_H
#define KD_MDIMAIN_WINDOW_INSTANTIATOR_P_H
#pragma once

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"

#include <QQuickItem>
#include <QQmlEngine>

namespace KDDockWidgets {

namespace Core {
class MainWindow;
class SideBar;
}

/// @brief A wrapper to workaround the limitation that QtQuick can't pass arguments through
/// MainWindow's ctor So instead, user instantiates a MainWindowWrapper in QML and calls init.
class DOCKS_EXPORT MainWindowMDIInstantiator : public QQuickItem
{
    Q_OBJECT
    QML_NAMED_ELEMENT(MDIDockingArea)
    Q_PROPERTY(QString uniqueName READ uniqueName WRITE setUniqueName NOTIFY uniqueNameChanged)
    Q_PROPERTY(QVector<QString> affinities READ affinities WRITE setAffinities NOTIFY affinitiesChanged)
public:
    ///@brief ctor, called by QML engine
    MainWindowMDIInstantiator();

    QString uniqueName() const;
    void setUniqueName(const QString &);

    QVector<QString> affinities() const;
    /// @brief Only applied when the main window is created. Changing it later has no effect.
    void setAffinities(const QVector<QString> &);

    Q_INVOKABLE void addDockWidget(QQuickItem *dockWidget, QPoint localPos, QSize initialSize = {},
                                   KDDockWidgets::InitialVisibilityOption = {});

    Q_INVOKABLE bool closeDockWidgets(bool force = false);

protected:
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    void uniqueNameChanged();
    void optionsChanged();
    void affinitiesChanged();

private:
    QString m_uniqueName;
    QVector<QString> m_affinities;
    Core::MainWindow *m_mainWindow = nullptr;
};

}

#endif
