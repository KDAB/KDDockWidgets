/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#ifndef KDMULTISPLITTER_QUICK_H
#define KDMULTISPLITTER_QUICK_H

#include "Widget_quick.h"
#include "Item_p.h"

#include <QQuickItem>

namespace Layouting {

class MultiSplitter
        : public QQuickItem
        , public Layouting::Widget_quick
{
    Q_OBJECT
public:
    MultiSplitter();
    ~MultiSplitter() override;
    void addItem(const QString &filename, Layouting::Item::Location, QQuickItem *relativeTo);
    void addItem(const QString &filename, Layouting::Item::Location, Layouting::Item *relativeTo);

private:
    void onSizeChanged();
    Layouting::ItemContainer *const m_rootContainer;
};
}

#endif
