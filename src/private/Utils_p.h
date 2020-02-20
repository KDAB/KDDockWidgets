/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef KD_UTILS_P_H
#define KD_UTILS_P_H

#include "Config.h"

#include <QApplication>
#include <QScreen>
#include <QWidget>
#include <QWindow>

#ifdef QT_X11EXTRAS_LIB
# include <QtX11Extras/QX11Info>
#endif

namespace KDDockWidgets {

inline bool isLeftButtonPressed()
{
    return qApp->mouseButtons() & Qt::LeftButton;
}

inline bool usesNativeTitleBar()
{
    return Config::self().flags() & Config::Flag_NativeTitleBar;
}

inline bool usesAeroSnapWithCustomDecos()
{
    return Config::self().flags() & Config::Flag_AeroSnapWithClientDecos;
}

inline bool usesNativeDraggingAndResizing()
{
    // a native title bar implies native resizing and dragging
    // Windows Aero-Snap also implies native dragging, and implies no native-title bar
    Q_ASSERT(!(usesNativeTitleBar() && usesAeroSnapWithCustomDecos()));
    return usesNativeTitleBar() || usesAeroSnapWithCustomDecos();
}

inline bool windowManagerHasTranslucency()
{
#ifdef QT_X11EXTRAS_LIB
    if (qApp->platformName() == QLatin1String("xcb"))
        return QX11Info::isCompositingManagerRunning();
#endif

    // macOS and Windows are fine
    return true;
}

inline QSize screenSizeForWidget(const QWidget *w)
{
    QWidget *topLevel = w->window();
    if (QWindow *window = topLevel->windowHandle()) {
        if (QScreen *screen = window->screen()) {
            return screen->size();
        }
    }

    return {};
}

inline int screenNumberForWidget(const QWidget *w)
{
    QWidget *topLevel = w->window();
    if (QWindow *window = topLevel->windowHandle()) {
        if (QScreen *screen = window->screen()) {
            return qApp->screens().indexOf(screen);
        }
    }

    return -1;
}

};

#endif
