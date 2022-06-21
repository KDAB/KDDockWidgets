/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief A MultiSplitter with support for drop indicators when hovering over.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_DROP_AREA_P_H
#define KD_DROP_AREA_P_H
#pragma once

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"

#include "controllers/Layout.h"

class TestQtWidgets;
class TestDocks;

namespace KDDockWidgets {

class Draggable;
struct WindowBeingDragged;

namespace Controllers {
class Group;
class DockWidget;
class Separator;
class DropIndicatorOverlay;

/**
 * MultiSplitter is simply a wrapper around Layouting::Item in which the hosted widgets are
 * of class KDDockWidgets::Frame. The stuff in Layouting:: being agnostic and generic, not specific
 * to KDDW.
 *
 * A MultiSplitter is like a QSplitter but supports mixing vertical and horizontal splitters in
 * any combination.
 *
 * It supports adding a widget to the left/top/bottom/right of the whole MultiSplitter or adding
 * relative to a single widget.
 */

class DOCKS_EXPORT DropArea : public Layout
{
    Q_OBJECT
public:
    explicit DropArea(View *parent, MainWindowOptions options, bool isMDIWrapper = false);
    ~DropArea();

    void removeHover();
    DropLocation hover(WindowBeingDragged *draggedWindow, QPoint globalPos);
    ///@brief Called when a user drops a widget via DND
    bool drop(WindowBeingDragged *droppedWindow, QPoint globalPos);
    QList<Controllers::Group *> groups() const;

    Layouting::Item *centralFrame() const;
    DropIndicatorOverlay *dropIndicatorOverlay() const
    {
        return m_dropIndicatorOverlay;
    }
    void addDockWidget(DockWidget *, KDDockWidgets::Location location,
                       DockWidget *relativeTo, InitialOption = {});

    bool containsDockWidget(DockWidget *) const;

    /// Returns whether this layout has a single dock widget which is floating
    /// Implies it's in a FloatingWindow and that it has only one dock widget
    bool hasSingleFloatingFrame() const;

    /// Returns whether this drop area has only 1 frame.
    /// See further explanation in FloatingWindow::hasSingleFrame()
    bool hasSingleFrame() const;

    QStringList affinities() const;
    void layoutParentContainerEqually(DockWidget *);

    /// When DockWidget::Option_MDINestable is used, docked MDI dock widgets will be wrapped inside a DropArea, so they accept drops
    /// This DropArea is created implicitly while docking, and this function will return true
    bool isMDIWrapper() const;

    /// Returns the helper dock widget for implementing DockWidget::Option_MDINestable.
    Controllers::DockWidget *mdiDockWidgetWrapper() const;

    static Controllers::Group *createCentralFrame(MainWindowOptions options);

    /**
     * @brief Adds a widget to this MultiSplitter.
     */
    void addWidget(View *widget, KDDockWidgets::Location location,
                   Controllers::Group *relativeTo = nullptr,
                   InitialOption option = DefaultSizeMode::Fair);

    /**
     * Adds an entire MultiSplitter into this layout. The donor MultiSplitter will be deleted
     * after all its Frames are stolen. All added Frames will preserve their original layout, so,
     * if widgetFoo was at the left of widgetBar when in the donor splitter, then it will still be at left
     * of widgetBar when the whole splitter is dropped into this one.
     */
    void addMultiSplitter(Controllers::DropArea *splitter, KDDockWidgets::Location location,
                          Controllers::Group *relativeTo = nullptr,
                          InitialOption option = DefaultSizeMode::Fair);

    /**
     * Called by the indicators, so they draw the drop rubber band at the correct place.
     * The rect for the rubberband when dropping a widget at the specified location.
     * Excludes the Separator thickness, result is actually smaller than what needed. In other words,
     * the result will be exactly the same as the geometry the widget will get.
     */
    QRect rectForDrop(const WindowBeingDragged *wbd, KDDockWidgets::Location location,
                      const Layouting::Item *relativeTo) const;

    bool deserialize(const LayoutSaver::MultiSplitter &) override;

    ///@brief returns the list of separators
    QVector<Controllers::Separator *> separators() const;

    /// @brief See docs for MainWindowBase::layoutEqually()
    void layoutEqually();

    /// @brief overload that just resizes widgets within a sub-tree
    void layoutEqually(Layouting::ItemBoxContainer *);

    /// @brief Returns the number of items layed out horizontally or vertically
    /// But honours nesting
    int numSideBySide_recursive(Qt::Orientation) const;

    Layouting::ItemBoxContainer *rootItem() const;

private:
    Q_DISABLE_COPY(DropArea)
    friend class Controllers::MainWindow;
    friend class Controllers::Group;
    friend class Controllers::FloatingWindow;
    friend class ::TestDocks;
    friend class ::TestQtWidgets;
    friend class DropIndicatorOverlay;
    friend class AnimatedIndicators;

    // For debug/hardening
    bool validateInputs(View *widget, KDDockWidgets::Location location,
                        const Controllers::Group *relativeToFrame, InitialOption option) const;


    void setRootItem(Layouting::ItemBoxContainer *);

    /**
     * @brief Like @ref availableLengthForDrop but just returns the total available width or height (depending on @p orientation)
     * So no need to receive any location.
     * @param orientation If Qt::Vertical then returns the available height. Width otherwise.
     */
    int availableLengthForOrientation(Qt::Orientation orientation) const;

    /**
     * @brief Equivalent to @ref availableLengthForOrientation but returns for both orientations.
     * width is for Qt::Vertical.
     */
    QSize availableSize() const;

    template<typename T>
    bool validateAffinity(T *, Controllers::Group *acceptingFrame = nullptr) const;
    bool drop(WindowBeingDragged *draggedWindow, Controllers::Group *acceptingFrame, DropLocation);
    bool drop(View *droppedwindow, KDDockWidgets::Location location, Controllers::Group *relativeTo);
    Controllers::Group *groupContainingPos(QPoint globalPos) const;
    void updateFloatingActions();

    bool m_inDestructor = false;
    const bool m_isMDIWrapper;
    QString m_affinityName;
    DropIndicatorOverlay *m_dropIndicatorOverlay = nullptr;
    Controllers::Group *const m_centralFrame = nullptr;
    Layouting::ItemBoxContainer *m_rootItem = nullptr;
    KDBindings::ScopedConnection m_visibleWidgetCountConnection;
};
}
}

#endif
