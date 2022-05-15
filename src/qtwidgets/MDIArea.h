/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_MDI_AREA_H
#define KDDOCKWIDGETS_MDI_AREA_H

#include "kddockwidgets/docks_export.h"
#include "KDDockWidgets.h"
#include "qtwidgets/views/View_qtwidgets.h"

namespace KDDockWidgets {

class MDILayout;

namespace Controllers {
class Frame;
class DockWidget;
}

/**
 * @brief MDIArea allows to host dock widget in MDI mode.
 * This is an alternative to using a full blown MainWindowMDI.
 * The use case is when you already have a MainWindow (doing normal docking) and you
 * want to add an area where you want to use MDI dock widgets. Instead of docking a MainWindowMDI,
 * you'd just use an MDIArea, and avoid having nested main windows.
 *
 * See examples/mdi_with_docking/.
 */
class DOCKS_EXPORT MDIArea : public Views::View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit MDIArea(QWidget *parent = nullptr);
    ~MDIArea();

    /// @brief docks the dock widgets into this MDI area, at the specified position
    void addDockWidget(Controllers::DockWidget *dw, QPoint localPt, InitialOption addingOption = {});

    /// @brief Moves a dock widget @p dw to point @p pos
    void moveDockWidget(Controllers::DockWidget *dw, QPoint pos);

    /// @brief Sets the size of dock widget @p dw to @p size
    void resizeDockWidget(Controllers::DockWidget *dw, QSize size);

    /// @brief Returns the list of frames in this MDI Area
    /// Each Frame object represents a 'window' emebedded in the MDI Area
    QList<Controllers::Frame *> frames() const;

private:
    class Private;
    Private *const d;
};

}

#endif
