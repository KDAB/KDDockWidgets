/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "View_qtwidgets.h"

#include <QRubberBand>

namespace KDDockWidgets {

namespace Views {

class DOCKS_EXPORT RubberBand_qtwidgets : public View_qtwidgets<QRubberBand>
{
    Q_OBJECT
public:
    explicit RubberBand_qtwidgets(QWidget *parent = nullptr);
    ~RubberBand_qtwidgets() override;
};

}

}
