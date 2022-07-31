/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <ClassicIndicatorWindowViewInterface.h>
#include <qstring.h>
#include <qpoint.h>
#include <qsize.h>
#include <qrect.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1017
class ClassicIndicatorWindowViewInterface_wrapper : public ::KDDockWidgets::Views::ClassicIndicatorWindowViewInterface
{
public:
    ~ClassicIndicatorWindowViewInterface_wrapper();
    // tag=1041
    ClassicIndicatorWindowViewInterface_wrapper();
    // tag=1041
    virtual KDDockWidgets::DropLocation hover(QPoint arg__1);
    // tag=1008
    virtual KDDockWidgets::DropLocation hover_nocallback(QPoint arg__1);
    // tag=1041
    virtual bool isWindow() const;
    // tag=1008
    virtual bool isWindow_nocallback() const;
    // tag=1041
    virtual QPoint posForIndicator(KDDockWidgets::DropLocation arg__1) const;
    // tag=1008
    virtual QPoint posForIndicator_nocallback(KDDockWidgets::DropLocation arg__1) const;
    // tag=1041
    virtual void raise();
    // tag=1008
    virtual void raise_nocallback();
    // tag=1041
    virtual void resize(QSize arg__1);
    // tag=1008
    virtual void resize_nocallback(QSize arg__1);
    // tag=1041
    virtual void setGeometry(QRect arg__1);
    // tag=1008
    virtual void setGeometry_nocallback(QRect arg__1);
    // tag=1041
    virtual void setObjectName(const QString &arg__1);
    // tag=1008
    virtual void setObjectName_nocallback(const QString &arg__1);
    // tag=1041
    virtual void setVisible(bool arg__1);
    // tag=1008
    virtual void setVisible_nocallback(bool arg__1);
    // tag=1041
    virtual void updatePositions();
    // tag=1008
    virtual void updatePositions_nocallback();
    // tag=1042
    typedef KDDockWidgets::DropLocation (*Callback_hover)(void *, QPoint arg__1);
    Callback_hover m_hoverCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_isWindow)(void *);
    Callback_isWindow m_isWindowCallback = nullptr;
    // tag=1042
    typedef QPoint *(*Callback_posForIndicator)(void *, KDDockWidgets::DropLocation arg__1);
    Callback_posForIndicator m_posForIndicatorCallback = nullptr;
    // tag=1042
    typedef void (*Callback_raise)(void *);
    Callback_raise m_raiseCallback = nullptr;
    // tag=1042
    typedef void (*Callback_resize)(void *, QSize arg__1);
    Callback_resize m_resizeCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setGeometry)(void *, QRect arg__1);
    Callback_setGeometry m_setGeometryCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setObjectName)(void *, const QString &arg__1);
    Callback_setObjectName m_setObjectNameCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setVisible)(void *, bool arg__1);
    Callback_setVisible m_setVisibleCallback = nullptr;
    // tag=1042
    typedef void (*Callback_updatePositions)(void *);
    Callback_updatePositions m_updatePositionsCallback = nullptr;
};
}
extern "C" {

// tag=1067
//  KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::ClassicIndicatorWindowViewInterface()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__constructor();

// tag=1067
//  KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::hover(QPoint arg__1)
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__hover_QPoint(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::isWindow() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__isWindow(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::posForIndicator(KDDockWidgets::DropLocation arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__posForIndicator_DropLocation(void *thisObj, int arg__1);

// tag=1067
//  KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::raise()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__raise(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::resize(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__resize_QSize(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::setGeometry(QRect arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setGeometry_QRect(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::setObjectName(const QString & arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setObjectName_QString(void *thisObj, const char *arg__1_);

// tag=1067
//  KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::setVisible(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setVisible_bool(void *thisObj, bool arg__1);

// tag=1067
//  KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::updatePositions()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__updatePositions(void *thisObj);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__destructor(void *thisObj);

// tag=1046
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface_Finalizer(void *, void *cppObj, void *);
}
