/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_MAIN_WINDOW_INSTANTIATOR_P_H
#define KD_MAIN_WINDOW_INSTANTIATOR_P_H

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"

#include <QQuickItem>

namespace KDDockWidgets {

class MainWindowQuick;
class DockWidgetInstantiator;
class SideBar;

namespace Controllers {
class DockWidget;
}

/// @brief A wrapper to workaround the limitation that QtQuick can't pass arguments through MainWindowQuick's ctor
/// So instead, user instantiates a MainWindowWrapper in QML and calls init.
class DOCKS_EXPORT MainWindowInstantiator
    : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString uniqueName READ uniqueName WRITE setUniqueName NOTIFY uniqueNameChanged)
    Q_PROPERTY(KDDockWidgets::MainWindowOptions options READ options WRITE setOptions NOTIFY optionsChanged)
    Q_PROPERTY(bool isMDI READ isMDI CONSTANT)
    Q_PROPERTY(QStringList affinities READ affinities CONSTANT)
public:
    ///@brief ctor, called by QML engine
    MainWindowInstantiator();

    QString uniqueName() const;
    void setUniqueName(const QString &);

    KDDockWidgets::MainWindowOptions options() const;
    void setOptions(KDDockWidgets::MainWindowOptions);

    QStringList affinities() const;
    bool isMDI() const;

    /// @brief See KDDockWidgets::MainWindowBase::addDockWidget()
    Q_INVOKABLE void addDockWidget(KDDockWidgets::Controllers::DockWidget *dockWidget,
                                   KDDockWidgets::Location location,
                                   KDDockWidgets::Controllers::DockWidget *relativeTo = nullptr,
                                   QSize initialSize = {}, KDDockWidgets::InitialVisibilityOption = {});

    Q_INVOKABLE void addDockWidget(KDDockWidgets::DockWidgetInstantiator *dockWidget,
                                   KDDockWidgets::Location location,
                                   KDDockWidgets::DockWidgetInstantiator *relativeTo = nullptr,
                                   QSize initialSize = {}, KDDockWidgets::InitialVisibilityOption = {});

    Q_INVOKABLE void layoutEqually();
    Q_INVOKABLE void layoutParentContainerEqually(KDDockWidgets::Controllers::DockWidget *dockWidget);
    Q_INVOKABLE void moveToSideBar(KDDockWidgets::Controllers::DockWidget *);
    Q_INVOKABLE void moveToSideBar(KDDockWidgets::Controllers::DockWidget *, KDDockWidgets::SideBarLocation);
    Q_INVOKABLE void restoreFromSideBar(KDDockWidgets::Controllers::DockWidget *);
    Q_INVOKABLE void overlayOnSideBar(KDDockWidgets::Controllers::DockWidget *);
    Q_INVOKABLE void toggleOverlayOnSideBar(KDDockWidgets::Controllers::DockWidget *);
    Q_INVOKABLE void clearSideBarOverlay(bool deleteFrame = true);
    Q_INVOKABLE KDDockWidgets::SideBar *sideBarForDockWidget(const KDDockWidgets::Controllers::DockWidget *) const;
    Q_INVOKABLE bool sideBarIsVisible(KDDockWidgets::SideBarLocation) const;
    Q_INVOKABLE bool closeDockWidgets(bool force = false);

protected:
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    void uniqueNameChanged();
    void optionsChanged();

private:
    QString m_uniqueName;
    MainWindowQuick *m_mainWindow = nullptr;
    KDDockWidgets::MainWindowOptions m_options = KDDockWidgets::MainWindowOption_None;
};

}

#endif
