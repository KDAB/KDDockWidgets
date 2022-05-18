/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "qtcommon/Platform_qt.h"
#include "qtwidgets/DebugWindow_p.h"

namespace KDDockWidgets {

/// @brief implements functions specific to a particular platform
/// A platform can be for example qtwidgets, qtquick, etc.
class DOCKS_EXPORT Platform_qtwidgets : public Platform_qt
{
public:
    Platform_qtwidgets();
    ~Platform_qtwidgets() override;
    const char *name() const override;
    bool hasActivePopup() const override;
    std::shared_ptr<ViewWrapper> qobjectAsView(QObject *) const override;
    std::shared_ptr<Window> windowFromQWindow(QWindow *) const override;
    FrameworkWidgetFactory *createDefaultFrameworkWidgetFactory() override;
    std::shared_ptr<Window> windowAt(QPoint globalPos) const override;

    using Platform_qt::screenNumberFor;
    int screenNumberFor(View *) const override;
    QSize screenSizeFor(View *) const override;

    int startDragDistance() const override;
    View *createView(View *parent = nullptr) const override;
    View *createClassicDropIndicatorOverlayView(Controllers::ClassicIndicators *controller, View *parent = nullptr) const override;
    View *createSegmentedDropIndicatorOverlayView(Controllers::SegmentedIndicators *controller, View *parent = nullptr) const override;

#ifdef DOCKS_DEVELOPER_MODE
    explicit Platform_qtwidgets(int &argc, char **argv);
    void tests_initPlatform_impl() override;
    void tests_deinitPlatform_impl() override;
    View *tests_createView(CreateViewOptions, View *parent = nullptr) override;
    View *tests_createFocusableView(CreateViewOptions, View *parent = nullptr) override;
    View *tests_createNonClosableView(View *parent = nullptr) override;
#endif
protected:
    void init();
};

}
