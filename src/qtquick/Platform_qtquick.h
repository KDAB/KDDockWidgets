/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/KDDockWidgets.h"
#include "kddockwidgets/Platform_qt.h"

class QQmlEngine;
class QQuickItem;

namespace KDDockWidgets {

class QtQuickHelpers;
class ViewFactory_qtquick;

namespace Controllers {
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
    std::shared_ptr<Window> windowFromQWindow(QWindow *) const override;
    ViewFactory *createDefaultViewFactory() override;
    ViewFactory_qtquick *viewFactory() const;
    std::shared_ptr<Window> windowAt(QPoint globalPos) const override;
    using Platform_qt::screenNumberFor;
    int screenNumberFor(View *) const override;
    QSize screenSizeFor(View *) const override;
    void setQmlEngine(QQmlEngine *);
    QQmlEngine *qmlEngine() const;
    View *createView(View *parent = nullptr) const override;
    bool usesFallbackMouseGrabber() const override;
    bool inDisallowedDragView(QPoint globalPos) const override;
    void ungrabMouse() override;
    static Platform_qtquick *instance();

    static Controllers::DockWidget *dockWidgetForItem(QQuickItem *);

#ifdef DOCKS_DEVELOPER_MODE
    explicit Platform_qtquick(int &argc, char **argv);
    void tests_initPlatform_impl() override;
    void tests_deinitPlatform_impl() override;
    View *tests_createView(CreateViewOptions, View *parent = nullptr) override;
    View *tests_createFocusableView(CreateViewOptions, View *parent = nullptr) override;
    View *tests_createNonClosableView(View *parent = nullptr) override;
    Controllers::MainWindow *createMainWindow(const QString &uniqueName, CreateViewOptions,
                                              MainWindowOptions options = MainWindowOption_HasCentralFrame,
                                              View *parent = nullptr, Qt::WindowFlags = {}) const override;
#endif
private:
    void init();
    QQmlEngine *m_qmlEngine = nullptr;
    QtQuickHelpers *const m_qquickHelpers;
};

inline Platform_qtquick *plat()
{
    return static_cast<Platform_qtquick *>(Platform::instance());
}

}
