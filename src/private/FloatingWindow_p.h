/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
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

class DOCKS_EXPORT FloatingWindow
        : public QWidgetAdapter
        , public Draggable
{
    Q_OBJECT
    Q_PROPERTY(KDDockWidgets::TitleBar* titleBar READ titleBar CONSTANT)
    Q_PROPERTY(KDDockWidgets::DropArea* dropArea READ dropArea CONSTANT)
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
#if defined(Q_OS_WIN) && defined(KDDOCKWIDGETS_QTWIDGETS)
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
    bool m_deleteScheduled = false;
    bool m_inDtor = false;
    bool m_updatingTitleBarVisibility = false;
    QMetaObject::Connection m_layoutDestroyedConnection;
    QAbstractNativeEventFilter *m_nchittestFilter = nullptr;
};

}

#endif
