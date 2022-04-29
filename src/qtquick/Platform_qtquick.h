/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "KDDockWidgets.h"
#include "qtcommon/Platform_qt.h"

namespace KDDockWidgets {

/// @brief implements functions specific to a particular platform
/// A platform can be for example qtwidgets, qtquick, etc.
class DOCKS_EXPORT Platform_qtquick : public Platform_qt
{
public:
    Platform_qtquick();
    ~Platform_qtquick() override;
    const char *name() const override;
    std::shared_ptr<ViewWrapper> qobjectAsView(QObject *) const override;
    std::shared_ptr<Window> windowFromQWindow(QWindow *) const override;
    FrameworkWidgetFactory *createDefaultFrameworkWidgetFactory() override;
    Window::Ptr windowAt(QPoint globalPos) const override;
    using Platform_qt::screenNumberFor;
    int screenNumberFor(View *) const override;
    QSize screenSizeFor(View *) const override;

#ifdef DOCKS_DEVELOPER_MODE
    explicit Platform_qtquick(int argc, char *argv[]);
    void tests_initPlatform_impl() override;
    void tests_deinitPlatform_impl() override;
    std::shared_ptr<ViewWrapper> tests_createView(std::shared_ptr<ViewWrapper> parent = {}) override;
#endif
private:
    void init();
};

}
