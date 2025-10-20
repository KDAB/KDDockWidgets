/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_DOCKWIDGET_INSTANTIATOR_P_H
#define KD_DOCKWIDGET_INSTANTIATOR_P_H

#include "qtquick/views/DockWidget.h"

#include <QQmlParserStatus>
#include <QQuickItem>
#include <QString>
#include <QQmlEngine>

namespace KDDockWidgets {

/**
 * @brief Indirection helper to instantiate dock widgets from QML
 *
 * "DockWidget {}" in QML won't create a KDDockWidget::DockWidget directly, but instead an
 * DockWidgetInstantiator. DockWidgetInstantiator will then create the DockWidget instance only
 * when the QML parsing ends (and all properties are set)
 *
 * This allows to pass the correct uniqueName to DockWidget's ctor.
 */
class DockWidgetInstantiator : public QQuickItem
{
    Q_OBJECT
    QML_NAMED_ELEMENT(DockWidget)
    Q_PROPERTY(QString uniqueName READ uniqueName WRITE setUniqueName NOTIFY uniqueNameChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(KDDockWidgets::QtQuick::DockWidget *dockWidget READ dockWidget NOTIFY
                   dockWidgetChanged)
    Q_PROPERTY(QObject *actualTitleBar READ actualTitleBar NOTIFY actualTitleBarChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(bool isFocused READ isFocused NOTIFY isFocusedChanged)
    Q_PROPERTY(bool isFloating READ isFloating WRITE setFloating NOTIFY isFloatingChanged)
    Q_PROPERTY(bool isOpen READ isOpen NOTIFY isOpenChanged)
    Q_PROPERTY(QVector<QString> affinities READ affinities WRITE setAffinities NOTIFY affinitiesChanged)
    Q_PROPERTY(KDDockWidgets::DockWidgetOptions options READ options WRITE setOptions NOTIFY optionsChanged)
    Q_PROPERTY(KDDockWidgets::CloseReason lastCloseReason READ lastCloseReason NOTIFY lastCloseReasonChanged)
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    Q_PROPERTY(QVariantMap userData READ userData WRITE setUserData NOTIFY userDataChanged)
#endif
public:
    DockWidgetInstantiator();
    ~DockWidgetInstantiator() override;

    QString uniqueName() const;
    void setUniqueName(const QString &);

    QString source() const;
    void setSource(const QString &);

    Q_INVOKABLE KDDockWidgets::QtQuick::DockWidget *dockWidget() const;
    Q_INVOKABLE KDDockWidgets::Core::DockWidget *controller() const;
    QObject *actualTitleBar() const;

    QString title() const;
    void setTitle(const QString &title);

    bool isFocused() const;
    bool isFloating() const;
    bool isOpen() const;
    void setFloating(bool);
    QVector<QString> affinities() const;
    void setAffinities(const QVector<QString> &);

    KDDockWidgets::DockWidgetOptions options() const;
    void setOptions(KDDockWidgets::DockWidgetOptions);

    KDDockWidgets::CloseReason lastCloseReason() const;

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QVariantMap userData() const;
    void setUserData(const QVariantMap &userData);
#endif

    Q_INVOKABLE void addDockWidgetAsTab(QQuickItem *other,
                                        KDDockWidgets::InitialVisibilityOption = {});

    Q_INVOKABLE void addDockWidgetToContainingWindow(QQuickItem *other,
                                                     KDDockWidgets::Location location,
                                                     QQuickItem *relativeTo = nullptr,
                                                     QSize initialSize = {},
                                                     KDDockWidgets::InitialVisibilityOption = {});

    Q_INVOKABLE void setAsCurrentTab();
    Q_INVOKABLE void forceClose();
    Q_INVOKABLE bool close();
    Q_INVOKABLE void open();
    Q_INVOKABLE void show();
    Q_INVOKABLE void raise();
    Q_INVOKABLE void moveToSideBar();

    /// Deletes the dock widget
    ///
    /// Deleting involves deleting the controller (Core::DockWidget), the view (View::DockWidget)
    /// and this instantiator itself as well.
    ///
    /// It's more usual to just hide dock widgets though.
    Q_INVOKABLE void deleteDockWidget();

protected:
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    void uniqueNameChanged();
    void sourceChanged();
    void dockWidgetChanged();
    void actualTitleBarChanged();
    void titleChanged(const QString &title);
    void iconChanged();
    void closed();
    void guestViewChanged(QQuickItem *);
    void optionsChanged(KDDockWidgets::DockWidgetOptions);
    void isFocusedChanged(bool);
    void isOverlayedChanged(bool);
    void isFloatingChanged(bool);
    void isOpenChanged(bool);
    void removedFromSideBar();
    void windowActiveAboutToChange(bool activated);
    void affinitiesChanged();
    void lastCloseReasonChanged();
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void userDataChanged();
#endif

private:
    class Private;
    Private *const d;
};
}

#endif
