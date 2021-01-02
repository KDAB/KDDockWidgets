/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "multisplitter.h"

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Layouting::MultiSplitter *);
public Q_SLOTS:
    void addItem(int loc, QQuickItem *relativeTo);
private:
    Layouting::MultiSplitter *const m_multiSplitter;
};

#endif
