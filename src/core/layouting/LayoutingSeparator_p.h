/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"
#include "LayoutingHost_p.h"

namespace KDDockWidgets {

namespace Core {

class Separator;
class LayoutingHost;
class ItemBoxContainer;

class DOCKS_EXPORT LayoutingSeparator
{
public:
    typedef Vector<LayoutingSeparator *> List;

    explicit LayoutingSeparator(LayoutingHost *);

    virtual ~LayoutingSeparator();
    virtual void init(Core::ItemBoxContainer *parentContainer, Qt::Orientation orientation) = 0;
    virtual int position() const = 0;
    virtual ItemBoxContainer *parentContainer() const = 0;
    virtual Qt::Orientation orientation() const = 0;
    virtual Rect geometry() const = 0;
    virtual void setGeometry(Rect r) = 0;
    virtual void setGeometry(int pos, int pos2, int length) = 0;
    virtual void free() = 0;

    LayoutingHost *const m_host;

private:
    LayoutingSeparator(const LayoutingSeparator &) = delete;
    LayoutingSeparator &operator=(const LayoutingSeparator &) = delete;
};

}

}
