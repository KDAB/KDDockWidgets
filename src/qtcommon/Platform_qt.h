/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "docks_export.h"
#include "Platform.h"
#include "Window_qt.h"

namespace KDDockWidgets {

/// @brief Baseclass platform for Qt based platform
/// Useful since QtWidgets and QtQuick share some similarities
class DOCKS_EXPORT Platform_qt : public Platform
{
public:
    Platform_qt();
    ~Platform_qt() override;

    std::shared_ptr<ViewWrapper> focusedView() const override;
    QVector<std::shared_ptr<Window>> windows() const override;
    std::shared_ptr<Window> qobjectAsWindow(QObject *) const override;
    virtual std::shared_ptr<Window> windowFromQWindow(QWindow *) const = 0;
    int screenNumberFor(std::shared_ptr<Window>) const override;

    void sendEvent(View *, QEvent *) const override;

#ifdef DOCKS_DEVELOPER_MODE
    static bool isGammaray();
    explicit Platform_qt(int &argc, char **argv);
    bool tests_waitForWindowActive(std::shared_ptr<Window>, int timeout = 5000) const override;
    bool tests_waitForEvent(QObject *w, QEvent::Type type, int timeout = 5000) const override;
    bool tests_waitForEvent(View *, QEvent::Type type, int timeout = 5000) const override;
    bool tests_waitForEvent(std::shared_ptr<Window>, QEvent::Type type, int timeout = 5000) const override;
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
#endif
protected:
    int screenNumberForQWindow(QWindow *) const;
};

}
