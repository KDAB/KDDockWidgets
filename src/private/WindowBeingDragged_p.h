/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_WINDOWBEINGDRAGGED_P_H
#define KD_WINDOWBEINGDRAGGED_P_H

#include "docks_export.h"
#include "FloatingWindow_p.h"

#include <QPointer>

QT_BEGIN_NAMESPACE
class QPixmap;
QT_END_NAMESPACE

namespace KDDockWidgets {

class FloatingWindow;
class Draggable;
class DropArea;

struct DOCKS_EXPORT_FOR_UNIT_TESTS WindowBeingDragged
{
public:
    explicit WindowBeingDragged(FloatingWindow *fw, Draggable *draggable);

#if DOCKS_DEVELOPER_MODE
    // For tests.
    explicit WindowBeingDragged(FloatingWindow *fw);
#endif

    virtual ~WindowBeingDragged();
    void init();

    FloatingWindow *floatingWindow() const { return m_floatingWindow; }

    ///@brief grabs or releases the mouse
    void grabMouse(bool grab);

    ///@brief returns the affinities of the window being dragged
    QStringList affinities() const;

    ///@brief size of the window being dragged contents
    virtual QSize size() const;

    /// @brief returns the min-size of the window being dragged contents
    virtual QSize minSize() const;

    /// @brief returns the max-size of the window being dragged contents
    virtual QSize maxSize() const;

    /// @brief returns whether the window being dragged contains the specified drop area
    /// useful since we don't want to drop onto outselves.
    bool contains(DropArea *) const;

    /// @brief Returns a pixmap representing this Window. For purposes of QDrag. Wayland only.
    virtual QPixmap pixmap() const { return {}; }

    /// @brief Returns the draggable
    Draggable *draggable() const;
protected:
    explicit WindowBeingDragged(Draggable *);
    Q_DISABLE_COPY(WindowBeingDragged)
    QPointer<FloatingWindow> m_floatingWindow;
    Draggable *const m_draggable;
    QPointer<QWidgetOrQuick> m_draggableWidget; // Just to have a QPointer on it

    const QStringList m_affinities;
};

struct WindowBeingDraggedWayland : public WindowBeingDragged
{
public:
    explicit WindowBeingDraggedWayland(Draggable *draggable);
    ~WindowBeingDraggedWayland() override;

    // These two are set for Wayland only, where we can't make the floating window immediately (no way to position it)
    // So we're dragging either a frame with multiple dock widgets or a single tab, keep them here.
    // It's important to know what we're dragging, so drop rubber band respect min/max sizes.
    QPointer<Frame> m_frame;
    QPointer<DockWidgetBase> m_dockWidget;

    QSize size() const override;
    QSize minSize() const override;
    QSize maxSize() const override;
    QPixmap pixmap() const override;
};

}

#endif
