/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief A widget that supports an arbitrary number of splitters (called Separators) in any
 * combination of vertical/horizontal.
 *
 * This is a widget wrapper around the multisplitter layout (Layouting::Item)
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDDOCKWIDGETS_LAYOUTWIDGET_P_H
#define KDDOCKWIDGETS_LAYOUTWIDGET_P_H

#pragma once

#include "docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"
#include "kddockwidgets/QWidgetAdapter.h"

#include <QList>

namespace Layouting {
class Item;
class Separator;
class Widget_qwidget;
}

namespace KDDockWidgets {

class MainWindowBase;
class FloatingWindow;
class Frame;
class DockWidgetBase;

/**
 * @brief The widget (QWidget or QQuickItem) which holds a layout of dock widgets.
 *
 * Usually this would simply be MultiSplitter, but we've introduced this base class to support
 * different layouts, like MDI layouts, which are very different than traditional dock widget
 * layouts.
 *
 * This class makes the bridge between the GUI world (QWidget) and Layouting::Item world.
 * It's suitable to be set as a main window central widget for instance. The actual layouting is
 * then done by the root Item.
 */
class DOCKS_EXPORT LayoutWidget : public LayoutGuestWidget
{
    Q_OBJECT
public:
    explicit LayoutWidget(QWidgetOrQuick *parent = nullptr);
    ~LayoutWidget() override;

    bool isInMainWindow() const;
    MainWindowBase *mainWindow() const;
    FloatingWindow *floatingWindow() const;

    /**
     * @brief returns the layout's minimum size
     * @ref setLayoutMinimumSize
     */
    QSize layoutMinimumSize() const;

    /**
     * @brief returns the layout's maximum size hint
     */
    QSize layoutMaximumSizeHint() const;

    /**
     * @brief returns the contents width.
     * Usually it's the same width as the respective parent MultiSplitter.
     */
    int width() const
    {
        return size().width();
    }

    /**
     * @brief returns the contents height.
     * Usually it's the same height as the respective parent MultiSplitter.
     */
    int height() const
    {
        return size().height();
    }

    /**
     * @brief getter for the size
     */
    QSize size() const;

    /// @brief Runs some sanity checks. Returns true if everything is OK
    bool checkSanity() const;

    /// @brief clears the layout
    void clearLayout();

    /// @brief dumps the layout to stderr
    void dumpLayout() const;

    /**
     * @brief setter for the contents size
     * The "contents size" is just the size() of this layout. However, since resizing
     * QWidgets is async and we need it to be sync. As sometimes adding widgets will increase
     * the MultiSplitter size (due to widget's min-size constraints).
     */
    void setLayoutSize(QSize);


    /// @brief restores the dockwidget @p dw to its previous position
    void restorePlaceholder(DockWidgetBase *dw, Layouting::Item *, int tabIndex);

protected:
    bool m_inResizeEvent = false;

    void setRootItem(Layouting::ItemContainer *root);
    /**
     * @brief setter for the minimum size
     * @ref minimumSize
     */
    void setLayoutMinimumSize(QSize);

    /**
     * @brief Removes unneeded placeholder items when adding new frames.
     *
     * A floating frame A might have a placeholder in the main window (for example to remember its
     * position on the Left), but then the user might attach it to the right, so the left
     * placeholder is no longer need. Right before adding the frame to the right we remove the left
     * placeholder, otherwise it's unrefed while we're adding causing a segfault. So what this does
     * is making the unrefing happen a bit earlier.
     */
    void unrefOldPlaceholders(const QList<Frame *> &framesBeingAdded) const;

Q_SIGNALS:
    void visibleWidgetCountChanged(int count);

private:
    Layouting::ItemContainer *m_rootItem = nullptr;
};

}

#endif
