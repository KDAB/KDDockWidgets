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

#ifndef KD_DOCKWIDGET_WIDGETS_H
#define KD_DOCKWIDGET_WIDGETS_H
#pragma once

#include "kddockwidgets/controllers/DockWidget.h"
#include "View_qtwidgets.h"

// clazy:excludeall=ctor-missing-parent-argument

namespace KDDockWidgets {

namespace Views {

/**
 * @brief Represents a dock widget.
 *
 * Most of the interface lives in Controllers::DockWidget, to facilitate sharing with QtQuick.
 */
class DOCKS_EXPORT DockWidget_qtwidgets : public View_qtwidgets<QWidget>
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
    explicit DockWidget_qtwidgets(const QString &uniqueName,
                                  Controllers::DockWidget::Options options = {},
                                  Controllers::DockWidget::LayoutSaverOptions layoutSaverOptions = {},
                                  Qt::WindowFlags windowFlags = Qt::Tool);

    ///@brief destructor
    ~DockWidget_qtwidgets() override;

    Controllers::DockWidget *dockWidget() const;

    /**
     * @brief sets the widget which this dock widget hosts.
     * @param widget the widget to show inside this dock widget. Must not be null.
     *
     * Ownership for @p widget is transferred to Controllers::DockWidget.
     * Ownsership for any previously existing widget is transferred back to the user. Meaning if you
     * call setWidget(A) followed by setWidget(B) then A will have to be deleted by you, while B is
     * owned by the dock widget.
     */
    void setWidget(QWidget *widget);

protected:
    void init() override;
    bool event(QEvent *) override;
    void resizeEvent(QResizeEvent *) override;

private:
    class Private;
    Private *const d;
};

}

}

#endif
