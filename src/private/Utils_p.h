/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
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
