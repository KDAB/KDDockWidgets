/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_MDI_AREA_H
#define KDDOCKWIDGETS_MDI_AREA_H

#include "kddockwidgets/docks_export.h"
#include "KDDockWidgets.h"
#include "QWidgetAdapter.h"

#include <QWidget>

namespace KDDockWidgets {

class MDILayoutWidget;
class DockWidgetBase;
class Frame;

/**
 * @brief MDIArea allows to host dock widget in MDI mode.
 * This is an alternative to using a full blown MainWindowMDI.
 * The use case is when you already have a MainWindow (doing normal docking) and you
 * want to add an area where you want to use MDI dock widgets. Instead of docking a MainWindowMDI,
 * you'd just use an MDIArea, and avoid having nested main windows.
 *
 * See examples/mdi_with_docking/.
 */
class DOCKS_EXPORT MDIArea : public QWidgetAdapter
{
    Q_OBJECT
public:
    explicit MDIArea(QWidgetOrQuick *parent = nullptr);
    ~MDIArea();

    /// @brief docks the dock widgets into this MDI area, at the specified position
    void addDockWidget(DockWidgetBase *dw, QPoint localPt, InitialOption addingOption = {});

    /// @brief Moves a dock widget @p dw to point @p pos
    void moveDockWidget(DockWidgetBase *dw, QPoint pos);

    /// @brief Sets the size of dock widget @p dw to @p size
    void resizeDockWidget(DockWidgetBase *dw, QSize size);

    /// @brief Returns the list of frames in this MDI Area
    /// Each Frame object represents a 'window' emebedded in the MDI Area
    QList<Frame *> frames() const;

    /// @brief Forwards the close event to the MDI dock widgets, aborts closing if at least one
    /// dock widget doesn't allow it
    void onCloseEvent(QCloseEvent *) override;

private:
    class Private;
    Private *const d;
};

}

#endif
