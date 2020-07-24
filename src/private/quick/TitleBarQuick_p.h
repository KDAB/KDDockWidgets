/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_TITLEBARQUICK_P_H
#define KD_TITLEBARQUICK_P_H

#include "../docks_export.h"
#include "../TitleBar_p.h"

namespace KDDockWidgets {

class DockWidget;
class Frame;

class DOCKS_EXPORT TitleBarQuick : public TitleBar
{
    Q_OBJECT
public:
    explicit TitleBarQuick(Frame *parent);
    explicit TitleBarQuick(FloatingWindow *parent);
    ~TitleBarQuick() override;

    ///@brief getter for the close button
    //QWidget* closeButton() const;

protected:
    /*void paintEvent(QPaintEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
    void updateFloatButton() override;
    void updateCloseButton() override;*/
//
};



}

#endif
