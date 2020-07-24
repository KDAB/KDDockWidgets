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
    ~WindowBeingDragged();
    void init();

    FloatingWindow *floatingWindow() const { return m_floatingWindow; }

    ///@brief grabs or releases the mouse
    void grabMouse(bool grab);

private:
    Q_DISABLE_COPY(WindowBeingDragged)
    QPointer<FloatingWindow> m_floatingWindow;
    QPointer<QWidgetOrQuick> m_draggable;
};
}

#endif
