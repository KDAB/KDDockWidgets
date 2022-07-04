/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_UTILS_P_H
#define KD_UTILS_P_H

#include "KDDockWidgets_p.h"
#include "kddockwidgets/Config.h"
#include "kddockwidgets/View.h"
#include "kddockwidgets/Platform.h"

#include <QScreen>
#include <QWindow>
#include <QMouseEvent>
#include <QGuiApplication>

#ifdef QT_X11EXTRAS_LIB
#include <QtX11Extras/QX11Info>
#endif

QT_BEGIN_NAMESPACE
class QWidget;
class QWindow;
QT_END_NAMESPACE

namespace KDDockWidgets {

inline bool isWayland()
{
    return Platform::instance()->displayType() == Platform::DisplayType::Wayland;
}

inline bool isOffscreen()
{
    return Platform::instance()->displayType() == Platform::DisplayType::QtOffscreen;
}

inline bool isXCB()
{
    return Platform::instance()->displayType() == Platform::DisplayType::X11;
}

inline bool isEGLFS()
{
    return Platform::instance()->displayType() == Platform::DisplayType::QtEGLFS;
}

inline bool isWindows()
{
    return Platform::instance()->displayType() == Platform::DisplayType::Windows;
}

inline bool isLeftButtonPressed()
{
    return Platform::instance()->isLeftMouseButtonPressed();
}

inline bool usesNativeTitleBar()
{
    return Config::self().flags() & Config::Flag_NativeTitleBar;
}

inline bool usesClientTitleBar()
{
    if (isWayland()) {
        // Wayland has both client and native title bars, due to limitations.
        return true;
    }

    // All other platforms have either the OS native title bar or a Qt title bar (aka client title bar).
    return !usesNativeTitleBar();
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

inline bool linksToXLib()
{
#ifdef KDDockWidgets_XLIB
    return true;
#else
    return false;
#endif
}

inline bool usesUtilityWindows()
{
    const auto flags = Config::self().internalFlags();

    const bool dontUse = (flags & Config::InternalFlag_DontUseParentForFloatingWindows) && (flags & Config::InternalFlag_DontUseQtToolWindowsForFloatingWindows);

    return !dontUse;
}

inline bool isNormalWindowState(WindowStates states)
{
    return !(states & WindowState::Maximized) && !(states & WindowState::FullScreen);
}

inline bool windowManagerHasTranslucency()
{
    if (qEnvironmentVariableIsSet("KDDW_NO_TRANSLUCENCY") || (Config::self().internalFlags() & Config::InternalFlag_DisableTranslucency))
        return false;

#ifdef QT_X11EXTRAS_LIB
    if (isXCB())
        return QX11Info::isCompositingManagerRunning();
#endif

    // macOS and Windows are fine
    return true;
}

inline QMouseEvent *mouseEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
    case QEvent::NonClientAreaMouseButtonPress:
    case QEvent::NonClientAreaMouseButtonRelease:
    case QEvent::NonClientAreaMouseMove:
    case QEvent::NonClientAreaMouseButtonDblClick:
        return static_cast<QMouseEvent *>(e);
    default:
        break;
    }

    return nullptr;
}

inline bool isNonClientMouseEvent(const QEvent *e)
{
    switch (e->type()) {
    case QEvent::NonClientAreaMouseButtonPress:
    case QEvent::NonClientAreaMouseButtonRelease:
    case QEvent::NonClientAreaMouseMove:
        return true;
    default:
        break;
    }

    return false;
}

inline bool isDnDEvent(const QEvent *e)
{
    switch (e->type()) {
    case QEvent::DragEnter:
    case QEvent::DragLeave:
    case QEvent::DragMove:
    case QEvent::Drop:
        return true;
    default:
        break;
    }

    return false;
}

/// @brief Returns whether we support the specified scalling factor
/// This is a workaround against a bug in older Qt (QTBUG-86170).
/// Mostly affects Linux. Unless you're using Qt::HighDpiScaleFactorRoundingPolicy::PassThrough, in which case it will affect other OSes too.
inline bool scalingFactorIsSupported(qreal factor)
{
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 2)
    // We don't support fractional factors in older Qt.
    const bool isInteger = int(factor) == factor;
    return isInteger;
#else
    Q_UNUSED(factor);
    return true;
#endif
}

};

#endif
