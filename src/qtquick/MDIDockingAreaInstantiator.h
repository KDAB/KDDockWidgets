/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

namespace KDDockWidgets {

namespace Controllers {
class MainWindow;
class SideBar;
}

/// @brief A wrapper to workaround the limitation that QtQuick can't pass arguments through
/// MainWindow's ctor So instead, user instantiates a MainWindowWrapper in QML and calls init.
class DOCKS_EXPORT MDIDockingAreaInstantiator : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString uniqueName READ uniqueName WRITE setUniqueName NOTIFY uniqueNameChanged)
    Q_PROPERTY(QStringList affinities READ affinities CONSTANT)
public:
    ///@brief ctor, called by QML engine
    MDIDockingAreaInstantiator();

    QString uniqueName() const;
    void setUniqueName(const QString &);

    QStringList affinities() const;

    Q_INVOKABLE void addDockWidget(QQuickItem *dockWidget, QPoint localPos,
                                   InitialOption addingOption = {});

    Q_INVOKABLE bool closeDockWidgets(bool force = false);

protected:
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    void uniqueNameChanged();
    void optionsChanged();

private:
    QString m_uniqueName;
    Controllers::MainWindow *m_mainWindow = nullptr;
};

}

#endif
