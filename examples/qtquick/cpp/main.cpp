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
#include <kddockwidgets/core/views/MainWindowViewInterface.h>
#include <kddockwidgets/qtquick/Platform.h>
#include <kddockwidgets/qtquick/views/DockWidget.h>

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QGuiApplication>

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
        dw->setGuestItem(QStringLiteral("qrc:/Guest.qml"));

        auto mainArea = KDDockWidgets::DockRegistry::self()->mainDockingAreas().constFirst();
        mainArea->addDockWidget(dw, KDDockWidgets::Location_OnRight);
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
};

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif
    QGuiApplication app(argc, argv);

    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtQuick);

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
