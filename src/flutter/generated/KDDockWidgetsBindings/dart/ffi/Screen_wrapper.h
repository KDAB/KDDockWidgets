/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <Screen.h>
#include <qstring.h>
#include <qsize.h>
#include <qrect.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1017
class Screen_wrapper : public ::KDDockWidgets::Screen
{
public:
    ~Screen_wrapper();
    // tag=1041
    Screen_wrapper();
    // tag=1041
    virtual QRect availableGeometry() const;
    // tag=1008
    virtual QRect availableGeometry_nocallback() const;
    // tag=1041
    virtual QSize availableSize() const;
    // tag=1008
    virtual QSize availableSize_nocallback() const;
    // tag=1041
    virtual qreal devicePixelRatio() const;
    // tag=1008
    virtual qreal devicePixelRatio_nocallback() const;
    // tag=1041
    virtual QRect geometry() const;
    // tag=1008
    virtual QRect geometry_nocallback() const;
    // tag=1041
    virtual QString name() const;
    // tag=1008
    virtual QString name_nocallback() const;
    // tag=1041
    virtual QSize size() const;
    // tag=1008
    virtual QSize size_nocallback() const;
    // tag=1041
    virtual QRect virtualGeometry() const;
    // tag=1008
    virtual QRect virtualGeometry_nocallback() const;
    // tag=1041
    virtual QSize virtualSize() const;
    // tag=1008
    virtual QSize virtualSize_nocallback() const;
    // tag=1042
    typedef QRect *(*Callback_availableGeometry)(void *);
    Callback_availableGeometry m_availableGeometryCallback = nullptr;
    // tag=1042
    typedef QSize *(*Callback_availableSize)(void *);
    Callback_availableSize m_availableSizeCallback = nullptr;
    // tag=1042
    typedef qreal (*Callback_devicePixelRatio)(void *);
    Callback_devicePixelRatio m_devicePixelRatioCallback = nullptr;
    // tag=1042
    typedef QRect *(*Callback_geometry)(void *);
    Callback_geometry m_geometryCallback = nullptr;
    // tag=1042
    typedef QString *(*Callback_name)(void *);
    Callback_name m_nameCallback = nullptr;
    // tag=1042
    typedef QSize *(*Callback_size)(void *);
    Callback_size m_sizeCallback = nullptr;
    // tag=1042
    typedef QRect *(*Callback_virtualGeometry)(void *);
    Callback_virtualGeometry m_virtualGeometryCallback = nullptr;
    // tag=1042
    typedef QSize *(*Callback_virtualSize)(void *);
    Callback_virtualSize m_virtualSizeCallback = nullptr;
};
}
extern "C" {

// tag=1067
//  KDDockWidgets::Screen::Screen()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Screen__constructor();

// tag=1067
//  KDDockWidgets::Screen::availableGeometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Screen__availableGeometry(void *thisObj);

// tag=1067
//  KDDockWidgets::Screen::availableSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Screen__availableSize(void *thisObj);

// tag=1067
//  KDDockWidgets::Screen::devicePixelRatio() const
KDDockWidgetsBindings_EXPORT qreal c_KDDockWidgets__Screen__devicePixelRatio(void *thisObj);

// tag=1067
//  KDDockWidgets::Screen::geometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Screen__geometry(void *thisObj);

// tag=1067
//  KDDockWidgets::Screen::name() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Screen__name(void *thisObj);

// tag=1067
//  KDDockWidgets::Screen::size() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Screen__size(void *thisObj);

// tag=1067
//  KDDockWidgets::Screen::virtualGeometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Screen__virtualGeometry(void *thisObj);

// tag=1067
//  KDDockWidgets::Screen::virtualSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Screen__virtualSize(void *thisObj);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Screen__destructor(void *thisObj);

// tag=1046
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Screen__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Screen_Finalizer(void *, void *cppObj, void *);
}
