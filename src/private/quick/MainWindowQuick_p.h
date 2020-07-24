/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_MAIN_WINDOW_QUICK_P_H
#define KD_MAIN_WINDOW_QUICK_P_H

#include "MainWindowBase.h"

namespace KDDockWidgets {

class MainWindowQuick : public MainWindowBase
{
    Q_OBJECT
    Q_PROPERTY(QString uniqueName READ uniqueName WRITE setUniqueName NOTIFY uniqueNameChanged)
    Q_PROPERTY(KDDockWidgets::DropAreaWithCentralFrame* dropArea READ dropArea WRITE setDropArea NOTIFY dropAreaChanged)
public:
    MainWindowQuick();
protected:
    DropAreaWithCentralFrame *dropArea() const override;
    void setDropArea(DropAreaWithCentralFrame*);
Q_SIGNALS:
    void dropAreaChanged();
private:
    DropAreaWithCentralFrame *m_dropArea = nullptr;
};

}

#endif
