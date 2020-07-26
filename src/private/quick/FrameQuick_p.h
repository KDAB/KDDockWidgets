/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#ifndef KD_FRAME_QUICK_P_H
#define KD_FRAME_QUICK_P_H

#include "Frame_p.h"

namespace KDDockWidgets {

/**
 * @brief The GUI counterpart of Frame.
 */
class DOCKS_EXPORT FrameQuick : public Frame
{
    Q_OBJECT
public:
    explicit FrameQuick(QWidgetAdapter *parent = nullptr, FrameOptions = FrameOption::FrameOption_None);

protected:
    void removeWidget_impl(DockWidgetBase *) override;
    void detachTab_impl(DockWidgetBase *) override;
    int indexOfDockWidget_impl(DockWidgetBase *) override;
    int currentIndex_impl() const override;
    void setCurrentTabIndex_impl(int index) override;
    void setCurrentDockWidget_impl(DockWidgetBase *) override;
    void insertDockWidget_impl(DockWidgetBase *, int index) override;
    DockWidgetBase *dockWidgetAt_impl(int index) const override;
    DockWidgetBase *currentDockWidget_impl() const override;
    int dockWidgetCount_impl() const override;
};

}

#endif
