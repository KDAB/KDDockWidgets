/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/core/Platform.h"
#include "kddockwidgets/qtcommon/Platform.h"

namespace KDDockWidgets {

namespace slint {
class DOCKS_EXPORT Platform : public QtCommon::Platform_qt
{
public:
    Platform();
    ~Platform() override;
    const char *name() const override;
    bool hasActivePopup() const override;
    Core::ViewFactory *createDefaultViewFactory() override;
    std::shared_ptr<Core::Window> windowAt(Point globalPos) const override;
    int screenNumberForView(Core::View *) const override;
    Size screenSizeFor(Core::View *) const override;
    Core::View *createView(Core::Controller *controller, Core::View *parent = nullptr) const override;
    void runDelayed(int ms, Core::DelayedCall *c) override;
    std::shared_ptr<Core::View> focusedView() const override;
    Vector<std::shared_ptr<Core::Window>> windows() const override;
    void sendEvent(Core::View *, Event *) const override;
    int screenNumberForWindow(std::shared_ptr<Core::Window>) const override;
    bool isProcessingAppQuitEvent() const override;
    QString applicationName() const override;
    void setMouseCursor(Qt::CursorShape, bool discardLast = false) override;
    void restoreMouseCursor() override;
    DisplayType displayType() const override;
    bool isLeftMouseButtonPressed() const override;
    Point cursorPos() const override;
    void setCursorPos(Point) override;
};

}
}
