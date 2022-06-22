/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/Platform.h"

#include <gtkmm/application.h>

namespace KDDockWidgets {

namespace Controllers {
class MainWindow;
}

/// @brief implements functions specific to a particular platform
/// A platform can be for example qtwidgets, qtquick, etc.
class DOCKS_EXPORT Platform_gtk : public Platform
{
public:
    Platform_gtk();
    ~Platform_gtk() override;
    const char *name() const override;
    bool hasActivePopup() const override;
    ViewFactory *createDefaultViewFactory() override;
    std::shared_ptr<Window> windowAt(QPoint globalPos) const override;

    int screenNumberFor(View *) const override;
    QSize screenSizeFor(View *) const override;

    View *createView(View *parent = nullptr) const override;
    bool inDisallowedDragView(QPoint globalPos) const override;
    bool usesFallbackMouseGrabber() const override;
    void ungrabMouse() override;

#ifdef DOCKS_DEVELOPER_MODE
    explicit Platform_gtk(int &argc, char **argv);
    void tests_initPlatform_impl() override;
    void tests_deinitPlatform_impl() override;
    View *tests_createView(CreateViewOptions, View *parent = nullptr) override;
    View *tests_createFocusableView(CreateViewOptions, View *parent = nullptr) override;
    View *tests_createNonClosableView(View *parent = nullptr) override;
    Controllers::MainWindow *createMainWindow(const QString &uniqueName, CreateViewOptions,
                                              MainWindowOptions options = MainWindowOption_HasCentralFrame,
                                              View *parent = nullptr, Qt::WindowFlags = {}) const override;
    bool tests_waitForWindowActive(std::shared_ptr<Window>, int timeout) const override;
    bool tests_waitForResize(View *, int timeout) const override;
    bool tests_waitForResize(Controller *, int timeout) const override;
    bool tests_waitForEvent(QObject *w, QEvent::Type type, int timeout) const override;
    bool tests_waitForEvent(View *, QEvent::Type type, int timeout) const override;
    bool tests_waitForEvent(std::shared_ptr<Window>, QEvent::Type type, int timeout) const override;
    bool tests_waitForDeleted(View *, int timeout) const override;
    bool tests_waitForDeleted(QObject *, int timeout) const override;
    std::shared_ptr<Window> tests_createWindow() override;
    void tests_sendEvent(std::shared_ptr<Window> window, QEvent *ev) const override;
    void tests_wait(int ms) override;
#endif

    bool isProcessingAppQuitEvent() const override;
    QString applicationName() const override;
    QString organizationName() const override;
    void setMouseCursor(Qt::CursorShape) override;
    void restoreMouseCursor() override;
    DisplayType displayType() const override;
    bool isLeftMouseButtonPressed() const override;

    std::shared_ptr<View> focusedView() const override;
    QVector<std::shared_ptr<Window>> windows() const override;
    void sendEvent(View *, QEvent *) const override;
    int screenNumberFor(std::shared_ptr<Window>) const override;
    void installMessageHandler() override;
    void uninstallMessageHandler() override;

protected:
    void init();

private:
    Glib::RefPtr<Gtk::Application> m_application;
};
}
