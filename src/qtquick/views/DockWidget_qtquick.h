/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief Represents a dock widget.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#pragma once

#include "controllers/DockWidget.h"
#include "View_qtquick.h"

QT_BEGIN_NAMESPACE
class QCloseEvent;
QT_END_NAMESPACE

namespace KDDockWidgets {

namespace Views {

/**
 * @brief Represents a dock widget.
 *
 * Most of the interface lives in DockWidgetBase, to facilitate sharing with QtQuick.
 */
class DOCKS_EXPORT DockWidget_qtquick : public View_qtquick<QQuickItem>
{
    Q_OBJECT
public:
    /**
     * @brief constructs a new DockWidget
     * @param uniqueName Mandatory name that should be unique between all DockWidget instances.
     *        This name won't be user visible and just used internally for the save/restore.
     *        Use setTitle() for user visible text.
     * @param options optional options controlling behaviour
     *
     * There's no parent argument. The DockWidget is either parented to FloatingWindow or MainWindow
     * when visible, or stays without a parent when hidden. This allows to support docking
     * to different main windows.
     */
    explicit DockWidget_qtquick(Controllers::DockWidget *controller,
                                Qt::WindowFlags windowFlags = {});

    ///@brief destructor
    ~DockWidget_qtquick() override;

    Controllers::DockWidget *dockWidget() const;

private:

};

}

}
