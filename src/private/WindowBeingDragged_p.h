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

namespace KDDockWidgets {

class FloatingWindow;
class Draggable;

struct DOCKS_EXPORT_FOR_UNIT_TESTS WindowBeingDragged
{
public:
    explicit WindowBeingDragged(FloatingWindow *fw, Draggable *draggable);
#if DOCKS_DEVELOPER_MODE
    // For tests.
    explicit WindowBeingDragged(FloatingWindow *fw);
#endif

    ~WindowBeingDragged();
    void init();

    FloatingWindow *floatingWindow() const { return m_floatingWindow; }

    ///@brief grabs or releases the mouse
    void grabMouse(bool grab);

    ///@brief returns the affinities of the window being dragged
    QStringList affinities() const;

    ///@brief size of the window being dragged contents
    QSize size() const;

    /// @brief returns the min-size of the window being dragged contents
    QSize minSize() const;

    /// @brief returns the max-size of the window being dragged contents
    QSize maxSize() const;

private:
    Q_DISABLE_COPY(WindowBeingDragged)
    QPointer<FloatingWindow> m_floatingWindow;
    QPointer<QWidgetOrQuick> m_draggable;
    const QStringList m_affinities;
};
}

#endif
