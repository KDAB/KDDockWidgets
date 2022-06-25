/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/Platform.h"

namespace KDDockWidgets {

namespace Controllers {
class MainWindow;
}

/// @brief implements functions specific to a particular platform
/// A platform can be for example qtwidgets, qtquick, etc.
class DOCKS_EXPORT Platform_dummy : public Platform
{
public:
    Platform_dummy();
    ~Platform_dummy() override;
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
    explicit Platform_dummy(int &argc, char **argv);
    void tests_initPlatform_impl() override;
    void tests_deinitPlatform_impl() override;
    View *tests_createView(CreateViewOptions, View *parent = nullptr) override;
    View *tests_createFocusableView(CreateViewOptions, View *parent = nullptr) override;
    View *tests_createNonClosableView(View *parent = nullptr) override;
    Controllers::MainWindow *createMainWindow(const QString &uniqueName, CreateViewOptions,
                                              MainWindowOptions options = MainWindowOption_HasCentralFrame,
                                              View *parent = nullptr, Qt::WindowFlags = {}) const override;
#endif
protected:
    void init();
};

}
