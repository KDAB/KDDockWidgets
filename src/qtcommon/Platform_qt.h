/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/Platform.h"

QT_BEGIN_NAMESPACE
class QCoreApplication;
QT_END_NAMESPACE

namespace KDDockWidgets {

class Window;

/// @brief Baseclass platform for Qt based platform
/// Useful since QtWidgets and QtQuick share some similarities
class DOCKS_EXPORT Platform_qt : public Platform
{
public:
    Platform_qt();
    ~Platform_qt() override;

    std::shared_ptr<View> focusedView() const override;
    QVector<std::shared_ptr<Window>> windows() const override;
    virtual std::shared_ptr<Window> windowFromQWindow(QWindow *) const = 0;
    int screenNumberFor(std::shared_ptr<Window>) const override;

    void sendEvent(View *, QEvent *) const override;

    bool isProcessingAppQuitEvent() const override;

    QString applicationName() const override;
    QString organizationName() const override;

    void setMouseCursor(Qt::CursorShape) override;
    void restoreMouseCursor() override;

    DisplayType displayType() const override;
    bool isLeftMouseButtonPressed() const override;

    QVector<std::shared_ptr<Screen>> screens() const override;

    /// @brief Returns the specified QObject casted to View
    /// Nullptr if it's not a view. TODOm3: This is shared between the
    /// QtQuick and QWidgets impl, but will be remove once we started removing Qt from backend
    virtual std::shared_ptr<View> qobjectAsView(QObject *) const = 0;
    std::shared_ptr<Window> qobjectAsWindow(QObject *) const;

    static Platform_qt *instance();

    std::shared_ptr<Screen> primaryScreen() const override;

#ifdef DOCKS_DEVELOPER_MODE
    static bool isGammaray();
    explicit Platform_qt(QCoreApplication *);
    bool tests_waitForWindowActive(std::shared_ptr<Window>, int timeout = 5000) const override;
    bool tests_waitForEvent(QObject *w, QEvent::Type type, int timeout = 5000) const override;
    bool tests_waitForEvent(View *, QEvent::Type type, int timeout = 5000) const override;
    bool tests_waitForEvent(std::shared_ptr<Window>, QEvent::Type type,
                            int timeout = 5000) const override;
    bool tests_waitForResize(View *, int timeout = 2000) const override;
    bool tests_waitForResize(Controller *, int timeout = 2000) const override;
    bool tests_waitForDeleted(View *, int timeout = 2000) const override;
    bool tests_waitForDeleted(QObject *, int timeout = 2000) const override;
    void tests_sendEvent(std::shared_ptr<Window>, QEvent *) const override;
    void tests_initPlatform_impl() override;
    void tests_deinitPlatform_impl() override;
    void tests_wait(int ms) override;

    void installMessageHandler() override;
    void uninstallMessageHandler() override;

    /// @brief if "-platform" wasn't passed it picks the offscreen QPA to run the tests
    static void maybeSetOffscreenQPA(int argc, char **argv);
#endif

protected:
    int screenNumberForQWindow(QWindow *) const;

private:
    class GlobalEventFilter;
    GlobalEventFilter *const m_globalEventFilter;
};

}
