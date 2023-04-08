/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/KDDockWidgets.h"
#include "kddockwidgets/Platform_qt.h"

#include <QPointer>

QT_BEGIN_NAMESPACE
class QQmlEngine;
class QQuickItem;
QT_END_NAMESPACE

namespace KDDockWidgets {

class QtQuickHelpers;
class ViewFactory_qtquick;

namespace Core {
class DockWidget;
}

/// @brief implements functions specific to a particular platform
/// A platform can be for example qtwidgets, qtquick, etc.
class DOCKS_EXPORT Platform_qtquick : public Platform_qt
{
public:
    Platform_qtquick();
    ~Platform_qtquick() override;
    const char *name() const override;
    std::shared_ptr<View> qobjectAsView(QObject *) const override;
    std::shared_ptr<Core::Window> windowFromQWindow(QWindow *) const override;
    Core::ViewFactory *createDefaultViewFactory() override;
    ViewFactory_qtquick *viewFactory() const;
    std::shared_ptr<Core::Window> windowAt(QPoint globalPos) const override;
    using Platform_qt::screenNumberFor;
    int screenNumberFor(View *) const override;
    QSize screenSizeFor(View *) const override;
    void setQmlEngine(QQmlEngine *);
    QQmlEngine *qmlEngine() const;
    View *createView(Controller *controller, View *parent = nullptr) const override;
    bool usesFallbackMouseGrabber() const override;
    bool inDisallowedDragView(QPoint globalPos) const override;
    void ungrabMouse() override;
    static Platform_qtquick *instance();

    static Core::DockWidget *dockWidgetForItem(QQuickItem *);

#ifdef DOCKS_DEVELOPER_MODE
    explicit Platform_qtquick(int &argc, char **argv);
    void tests_initPlatform_impl() override;
    void tests_deinitPlatform_impl() override;
    View *tests_createView(Core::CreateViewOptions, View *parent = nullptr) override;
    std::shared_ptr<Core::Window> tests_createWindow() override;
    View *tests_createFocusableView(Core::CreateViewOptions, View *parent = nullptr) override;
    View *tests_createNonClosableView(View *parent = nullptr) override;
    Core::MainWindow *
    createMainWindow(const QString &uniqueName, Core::CreateViewOptions,
                     MainWindowOptions options = MainWindowOption_HasCentralFrame,
                     View *parent = nullptr, Qt::WindowFlags = {}) const override;
#endif
private:
    void init();
    QPointer<QQmlEngine> m_qmlEngine;
    QtQuickHelpers *const m_qquickHelpers;
};

inline Platform_qtquick *plat()
{
    return static_cast<Platform_qtquick *>(Core::Platform::instance());
}

}
