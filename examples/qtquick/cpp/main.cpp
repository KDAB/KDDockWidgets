/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// This example shows how to drive KDDockWidgets' QtQuick frontend entirely
// from C++. Unlike the other QtQuick examples, no DockWidget is declared in
// QML; main.qml only sets up the window, the menu and an empty DockingArea.
// DockWidgetFactory (below) is exposed to QML as a context property and its
// invocable methods are what actually create/save/restore dock widgets.

#include <kddockwidgets/Config.h>
#include <kddockwidgets/LayoutSaver.h>
#include <kddockwidgets/core/DockRegistry.h>
#include <kddockwidgets/core/DockWidget.h>
#include <kddockwidgets/core/views/MainWindowViewInterface.h>
#include <kddockwidgets/qtquick/Platform.h>
#include <kddockwidgets/qtquick/views/DockWidget.h>

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QGuiApplication>
#include <QHash>

// Which component is loaded into each dock widget is application state, not layout
// state: LayoutSaver only records the uniqueName. We keep the mapping here, which is
// enough to restore a layout saved by this same run.

// In a real app replace with a sidecar file
static QHash<QString, QString> s_components;

// Replaces the QML component hosted by a dock widget.
static void setComponent(KDDockWidgets::QtQuick::DockWidget *dw, const QString &qmlFile)
{
    // Grab the old guest before swapping: setGuestItem() only unparents it, giving
    // ownership back to us, so it's up to us to delete it.
    QQuickItem *oldGuest = dw->guestItem();

    dw->setGuestItem(qmlFile);

    if (oldGuest && oldGuest != dw->guestItem())
        oldGuest->deleteLater();

    s_components[dw->uniqueName()] = qmlFile;
}

static QString lastComponent(const QString &uniqueName)
{
    // in a real app replace with sidecar file
    return s_components.value(uniqueName, QStringLiteral("qrc:/Guest.qml"));
}

// Called by LayoutSaver, while restoring, for each dock widget in the layout file
// that doesn't exist yet, so we recreate it and put its guest back.
static KDDockWidgets::Core::DockWidget *dockWidgetFactory(const QString &uniqueName)
{
    auto dw = new KDDockWidgets::QtQuick::DockWidget(uniqueName);
    dw->setTitle(uniqueName);
    setComponent(dw, lastComponent(uniqueName));

    return dw->dockWidget();
}

class DockWidgetFactory : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;

    Q_INVOKABLE void newDockWidget()
    {
        ++m_count;
        const QString uniqueName = QStringLiteral("cpp-dock-%1").arg(m_count);

        auto dw = new KDDockWidgets::QtQuick::DockWidget(uniqueName);
        dw->setTitle(QStringLiteral("C++ Dock #%1").arg(m_count));
        setComponent(dw, QStringLiteral("qrc:/Guest.qml"));

        auto mainArea = KDDockWidgets::DockRegistry::self()->mainDockingAreas().constFirst();
        mainArea->addDockWidget(dw, KDDockWidgets::Location_OnRight);
    }

    // Swapping the contents of an existing dock widget is just calling the guest
    // setter again. Alternates between the two components, so it can be triggered
    // repeatedly.
    Q_INVOKABLE void swapGuest()
    {
        auto dock = KDDockWidgets::DockRegistry::self()->dockByName(QStringLiteral("cpp-dock-1"));
        if (!dock)
            return;

        m_swapped = !m_swapped;
        setComponent(static_cast<KDDockWidgets::QtQuick::DockWidget *>(dock->view()),
                     m_swapped ? QStringLiteral("qrc:/Guest2.qml")
                               : QStringLiteral("qrc:/Guest.qml"));
    }

    Q_INVOKABLE void saveLayout()
    {
        KDDockWidgets::LayoutSaver saver;
        saver.saveToFile(QStringLiteral("mySavedLayout.json"));
    }

    Q_INVOKABLE void restoreLayout()
    {
        KDDockWidgets::LayoutSaver saver;
        saver.restoreFromFile(QStringLiteral("mySavedLayout.json"));
    }

private:
    int m_count = 0;
    bool m_swapped = false;
};

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif
    QGuiApplication app(argc, argv);

    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtQuick);

    // Required so LayoutSaver can recreate the dock widgets that don't exist yet,
    // for example when restoring a layout saved by a previous run.
    KDDockWidgets::Config::self().setDockWidgetFactoryFunc(&dockWidgetFactory);

    QQmlApplicationEngine appEngine;
    KDDockWidgets::QtQuick::Platform::instance()->setQmlEngine(&appEngine);

    DockWidgetFactory dockWidgetFactory;
    appEngine.rootContext()->setContextProperty("dockWidgetFactory", &dockWidgetFactory);

    appEngine.load(QUrl("qrc:/main.qml"));

    // Create a few initial dock widgets, using the same C++ API that's
    // wired to the "New DockWidget" menu entry.
    dockWidgetFactory.newDockWidget();
    dockWidgetFactory.newDockWidget();
    dockWidgetFactory.newDockWidget();

    return app.exec();
}

#include "main.moc"
