/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file
 * @brief Window to show debug information. Used for debugging only, for apps that don't support GammaRay.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */
#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include "ObjectViewer_p.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
class QEventLoop;
QT_END_NAMESPACE

namespace KDDockWidgets {
namespace Debug {

class DebugWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DebugWindow(QWidget *parent = nullptr);

private:
#ifdef Q_OS_WIN
    void dumpWindow(QWidget *);
    void dumpWindows();
#endif

    void repaintWidgetRecursive(QWidget *);

    void dumpDockWidgetInfo();
    ObjectViewer m_objectViewer;
    QEventLoop *m_isPickingWidget = nullptr;

protected:
    void mousePressEvent(QMouseEvent *event) override;
};
}
}

#endif
