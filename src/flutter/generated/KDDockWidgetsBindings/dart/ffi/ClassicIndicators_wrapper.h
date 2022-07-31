/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <ClassicIndicators.h>
#include <qstring.h>
#include <DropArea.h>
#include <qpoint.h>
#include <qsize.h>
#include <qrect.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1017
class ClassicIndicators_wrapper : public ::KDDockWidgets::Controllers::ClassicIndicators
{
public:
    ~ClassicIndicators_wrapper();
    // tag=1041
    ClassicIndicators_wrapper(KDDockWidgets::Controllers::DropArea *dropArea);
    // tag=1041
    virtual KDDockWidgets::DropLocation hover_impl(QPoint globalPos);
    // tag=1008
    virtual KDDockWidgets::DropLocation hover_impl_nocallback(QPoint globalPos);
    // tag=1041
    void indicatorsVisibleChanged();
    // tag=1041
    bool onResize(QSize newSize);
    // tag=1041
    virtual QPoint posForIndicator(KDDockWidgets::DropLocation arg__1) const;
    // tag=1008
    virtual QPoint posForIndicator_nocallback(KDDockWidgets::DropLocation arg__1) const;
    // tag=1041
    void setDropLocation(KDDockWidgets::DropLocation arg__1);
    // tag=1041
    static QString tr(const char *s, const char *c, int n);
    // tag=1041
    virtual void updateVisibility();
    // tag=1008
    virtual void updateVisibility_nocallback();
    // tag=1042
    typedef KDDockWidgets::DropLocation (*Callback_hover_impl)(void *, QPoint globalPos);
    Callback_hover_impl m_hover_implCallback = nullptr;
    // tag=1042
    typedef QPoint *(*Callback_posForIndicator)(void *, KDDockWidgets::DropLocation arg__1);
    Callback_posForIndicator m_posForIndicatorCallback = nullptr;
    // tag=1042
    typedef void (*Callback_updateVisibility)(void *);
    Callback_updateVisibility m_updateVisibilityCallback = nullptr;
};
}
extern "C" {

// tag=1067
//  KDDockWidgets::Controllers::ClassicIndicators::ClassicIndicators(KDDockWidgets::Controllers::DropArea * dropArea)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__ClassicIndicators__constructor_DropArea(void *dropArea_);

// tag=1067
//  KDDockWidgets::Controllers::ClassicIndicators::hover_impl(QPoint globalPos)
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__ClassicIndicators__hover_impl_QPoint(void *thisObj, void *globalPos_);

// tag=1067
//  KDDockWidgets::Controllers::ClassicIndicators::indicatorsVisibleChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__ClassicIndicators__indicatorsVisibleChanged(void *thisObj);

// tag=1078
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__ClassicIndicators__onIndicatorsVisibleChanged(void *thisObj, void *contextQObject, void *callback);
// tag=1067
//  KDDockWidgets::Controllers::ClassicIndicators::onResize(QSize newSize)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__ClassicIndicators__onResize_QSize(void *thisObj, void *newSize_);

// tag=1067
//  KDDockWidgets::Controllers::ClassicIndicators::posForIndicator(KDDockWidgets::DropLocation arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__ClassicIndicators__posForIndicator_DropLocation(void *thisObj, int arg__1);

// tag=1067
//  KDDockWidgets::Controllers::ClassicIndicators::setDropLocation(KDDockWidgets::DropLocation arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__ClassicIndicators__setDropLocation_DropLocation(void *thisObj, int arg__1);

// tag=1067
//  KDDockWidgets::Controllers::ClassicIndicators::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Controllers__ClassicIndicators__tr_char_char_int(const char *s, const char *c, int n);

// tag=1067
//  KDDockWidgets::Controllers::ClassicIndicators::updateVisibility()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__ClassicIndicators__updateVisibility(void *thisObj);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__ClassicIndicators__destructor(void *thisObj);

// tag=1046
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__ClassicIndicators__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__ClassicIndicators_Finalizer(void *, void *cppObj, void *);
}
