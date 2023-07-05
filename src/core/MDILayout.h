/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/



#ifndef KDDOCKWIDGETS_MDI_LAYOUT_WIDGET_P_H
#define KDDOCKWIDGETS_MDI_LAYOUT_WIDGET_P_H

#include "kddockwidgets/core/Layout.h"
#include "kddockwidgets/KDDockWidgets.h"
#include "kddockwidgets/docks_export.h"


namespace KDDockWidgets {

namespace Core {

class ItemFreeContainer;

/**
 * @brief The MDILayout class implements a layout suitable for MDI style docking.
 * Where dock widgets are free to be positioned in arbitrary positions, not restricted by layouting.
 */
class DOCKS_EXPORT MDILayout : public Layout
{
    Q_OBJECT
public:
    explicit MDILayout(View *parent = nullptr);
    ~MDILayout() override;

    /// @brief docks the dock widgets into this MDI area, at the specified position
    void addDockWidget(Core::DockWidget *dw, Point localPt,
                       InitialOption addingOption = {});

    /// @brief Moves a dock widget @p dw to point @p pos
    void moveDockWidget(Core::DockWidget *dw, Point pos);

    /// @brief Moves a dock widget @p f to point @p pos
    /// Convenience overload.
    void moveDockWidget(Core::Group *f, Point pos);

    /// @brief Sets the size of dock widget @p dw to @p size
    void resizeDockWidget(Core::DockWidget *dw, Size size);

    /// @brief Sets the size of dock widget @p f to @p size
    /// Convenience overload.
    void resizeDockWidget(Core::Group *f, Size size);

    /// @brief sets the size and position of the dock widget @p f
    void setDockWidgetGeometry(Core::Group *f, Rect);

private:
    Core::ItemFreeContainer *const m_rootItem;
};

}

}

#endif
