/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <ClassicIndicators.h>
#include <qstring.h>
#include <DropArea.h>
#include <qpoint.h>
#include <qsize.h>
#include <qrect.h>

namespace KDDockWidgetsBindings_wrappersNS {
class ClassicIndicators_wrapper : public ::KDDockWidgets::Controllers::ClassicIndicators
{
public:
    ~ClassicIndicators_wrapper();
    ClassicIndicators_wrapper(KDDockWidgets::Controllers::DropArea *dropArea);
    virtual KDDockWidgets::DropLocation hover_impl(QPoint globalPos);
    virtual KDDockWidgets::DropLocation hover_impl_nocallback(QPoint globalPos);
    void indicatorsVisibleChanged();
    bool onResize(QSize newSize);
    virtual QPoint posForIndicator(KDDockWidgets::DropLocation arg__1) const;
    virtual QPoint posForIndicator_nocallback(KDDockWidgets::DropLocation arg__1) const;
    void setDropLocation(KDDockWidgets::DropLocation arg__1);
    static QString tr(const char *s, const char *c, int n);
    virtual void updateVisibility();
    virtual void updateVisibility_nocallback();
    typedef KDDockWidgets::DropLocation (*Callback_hover_impl)(void *, QPoint globalPos);
    Callback_hover_impl m_hover_implCallback = nullptr;
    typedef QPoint *(*Callback_posForIndicator)(void *, KDDockWidgets::DropLocation arg__1);
    Callback_posForIndicator m_posForIndicatorCallback = nullptr;
    typedef void (*Callback_updateVisibility)(void *);
    Callback_updateVisibility m_updateVisibilityCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::Controllers::ClassicIndicators::ClassicIndicators(KDDockWidgets::Controllers::DropArea
// * dropArea)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__ClassicIndicators__constructor_DropArea(void *dropArea_);
// KDDockWidgets::Controllers::ClassicIndicators::hover_impl(QPoint globalPos)
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Controllers__ClassicIndicators__hover_impl_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::Controllers::ClassicIndicators::indicatorsVisibleChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__indicatorsVisibleChanged(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__onIndicatorsVisibleChanged(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::ClassicIndicators::onResize(QSize newSize)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__ClassicIndicators__onResize_QSize(void *thisObj, void *newSize_);
// KDDockWidgets::Controllers::ClassicIndicators::posForIndicator(KDDockWidgets::DropLocation
// arg__1) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__ClassicIndicators__posForIndicator_DropLocation(void *thisObj,
                                                                              int arg__1);
// KDDockWidgets::Controllers::ClassicIndicators::setDropLocation(KDDockWidgets::DropLocation
// arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__setDropLocation_DropLocation(void *thisObj,
                                                                              int arg__1);
// KDDockWidgets::Controllers::ClassicIndicators::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *
c_static_KDDockWidgets__Controllers__ClassicIndicators__tr_char_char_int(const char *s,
                                                                         const char *c, int n);
// KDDockWidgets::Controllers::ClassicIndicators::updateVisibility()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__updateVisibility(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__registerVirtualMethodCallback(void *ptr,
                                                                               void *callback,
                                                                               int methodId);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators_Finalizer(void *, void *cppObj, void *);
}
