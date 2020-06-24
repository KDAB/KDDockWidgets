/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KD_FLOATING_WINDOW_P_H
#define KD_FLOATING_WINDOW_P_H

#include "docks_export.h"
#include "Frame_p.h"
#include "Draggable_p.h"
#include "QWidgetAdapter.h"
#include "LayoutSaver_p.h"

QT_BEGIN_NAMESPACE
class QAbstractNativeEventFilter;
class QWindowStateChangeEvent;
QT_END_NAMESPACE

namespace KDDockWidgets {

class MainWindowBase;
class DropArea;
class Frame;
class MultiSplitter;

class DOCKS_EXPORT FloatingWindow : public QWidgetAdapter
    , public Draggable
{
    Q_OBJECT
public:
    explicit FloatingWindow(MainWindowBase *parent = nullptr);
    explicit FloatingWindow(Frame *frame, MainWindowBase *parent = nullptr);
    ~FloatingWindow() override;

    bool deserialize(const LayoutSaver::FloatingWindow &);
    LayoutSaver::FloatingWindow serialize() const;

    // Draggable:
    std::unique_ptr<WindowBeingDragged> makeWindow() override;
    DockWidgetBase *singleDockWidget() const override;

    const Frame::List frames() const;
    DropArea *dropArea() const { return m_dropArea; }

    /**
     * @brief Returns the title bar.
     *
     * This TitleBar is hidden if we're using a native title bar.
     */
    TitleBar *titleBar() const { return m_titleBar; }

    /**
     * @brief Equivalent to setGeometry(), but the value might be adjusted.
     *
     * For example, if the suggestedRect is bigger than max size, we'll make it smaller.
     *
     * @param preserveCenter, if true, then the center is preserved
     *
     */
    void setSuggestedGeometry(QRect suggestedRect, bool preserveCenter = false);

    bool anyNonClosable() const;
    bool anyNonDockable() const;

    /**
     * @brief checks if this FloatingWindow only has one frame.
     * If true it means there's no side-by-side dock widgets here. There's only 1 frame.
     * Note that despite having only 1 frame it can still have multiple DockWidgets,
     * as they can be tabbed into the single frame.
     * @return true if this FloatingWindow has a single frame.
     */
    bool hasSingleFrame() const;

    /**
     * @brief checks if this FloatingWindow only has one dockwidget.
     * This is a more specific case than hasSingleFrame(), it implies not only a single frame,
     * but that frame must only have 1 dock widget.
     * @return true if this FloatingWindow only has one dockwidget.
     */
    bool hasSingleDockWidget() const;

    /**
     * @brief Returns whether a deleteLater has already been issued
     */
    bool beingDeleted() const;

    /**
     * @brief Equivalent to deleteLater() but sets beingDeleted() to true
     */
    void scheduleDeleteLater();

    /**
     * @brief Returns the MultiSplitter
     */
    MultiSplitter *multiSplitter() const;

    /**
     * @brief Returns whether @p globalPoint is inside the title bar (or, when there's no title-bar, the draggable empty
     * area of a tab bar)
     */
    bool isInDragArea(QPoint globalPoint) const;

    ///@brief updates the title and the icon
    void updateTitleAndIcon();
    void updateTitleBarVisibility();

    QStringList affinities() const;

    /**
     * Returns the drag rect in global coordinates. This is usually the title bar rect.
     * However, when using Config::Flag_HideTitleBarWhenTabsVisible it will be the tab bar background.
     * Returns global coordinates.
     */
    QRect dragRect() const;

Q_SIGNALS:
    void numFramesChanged();
    void windowStateChanged(QWindowStateChangeEvent *);
protected:
#ifdef Q_OS_WIN
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
#endif

    void onCloseEvent(QCloseEvent *) override;

    DropArea *const m_dropArea;
    TitleBar *const m_titleBar;
private:
    Q_DISABLE_COPY(FloatingWindow)
    void maybeCreateResizeHandler();
    void onFrameCountChanged(int count);
    void onVisibleFrameCountChanged(int count);
    bool m_disableSetVisible = false;
    bool m_beingDeleted = false;
    QMetaObject::Connection m_layoutDestroyedConnection;
    QAbstractNativeEventFilter *m_nchittestFilter = nullptr;
};

}

#endif
