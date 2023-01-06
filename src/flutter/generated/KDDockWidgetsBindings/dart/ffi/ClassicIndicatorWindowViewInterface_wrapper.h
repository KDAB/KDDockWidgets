/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <ClassicIndicatorWindowViewInterface.h>
#include <qstring.h>
#include <qpoint.h>
#include <qsize.h>
#include <qrect.h>

namespace KDDockWidgetsBindings_wrappersNS {
class ClassicIndicatorWindowViewInterface_wrapper
    : public ::KDDockWidgets::Views::ClassicIndicatorWindowViewInterface
{
public:
    ~ClassicIndicatorWindowViewInterface_wrapper();
    ClassicIndicatorWindowViewInterface_wrapper();
    virtual KDDockWidgets::DropLocation hover(QPoint arg__1);
    virtual KDDockWidgets::DropLocation hover_nocallback(QPoint arg__1);
    virtual bool isWindow() const;
    virtual bool isWindow_nocallback() const;
    virtual QPoint posForIndicator(KDDockWidgets::DropLocation arg__1) const;
    virtual QPoint posForIndicator_nocallback(KDDockWidgets::DropLocation arg__1) const;
    virtual void raise();
    virtual void raise_nocallback();
    virtual void resize(QSize arg__1);
    virtual void resize_nocallback(QSize arg__1);
    virtual void setGeometry(QRect arg__1);
    virtual void setGeometry_nocallback(QRect arg__1);
    virtual void setObjectName(const QString &arg__1);
    virtual void setObjectName_nocallback(const QString &arg__1);
    virtual void setVisible(bool arg__1);
    virtual void setVisible_nocallback(bool arg__1);
    virtual void updatePositions();
    virtual void updatePositions_nocallback();
    typedef KDDockWidgets::DropLocation (*Callback_hover)(void *, QPoint *arg__1);
    Callback_hover m_hoverCallback = nullptr;
    typedef bool (*Callback_isWindow)(void *);
    Callback_isWindow m_isWindowCallback = nullptr;
    typedef QPoint *(*Callback_posForIndicator)(void *, KDDockWidgets::DropLocation arg__1);
    Callback_posForIndicator m_posForIndicatorCallback = nullptr;
    typedef void (*Callback_raise)(void *);
    Callback_raise m_raiseCallback = nullptr;
    typedef void (*Callback_resize)(void *, QSize *arg__1);
    Callback_resize m_resizeCallback = nullptr;
    typedef void (*Callback_setGeometry)(void *, QRect *arg__1);
    Callback_setGeometry m_setGeometryCallback = nullptr;
    typedef void (*Callback_setObjectName)(void *, const QString &arg__1);
    Callback_setObjectName m_setObjectNameCallback = nullptr;
    typedef void (*Callback_setVisible)(void *, bool arg__1);
    Callback_setVisible m_setVisibleCallback = nullptr;
    typedef void (*Callback_updatePositions)(void *);
    Callback_updatePositions m_updatePositionsCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::ClassicIndicatorWindowViewInterface()
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__constructor();
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::hover(QPoint arg__1)
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__hover_QPoint(void *thisObj,
                                                                          void *arg__1_);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::isWindow() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__isWindow(void *thisObj);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::posForIndicator(KDDockWidgets::DropLocation
// arg__1) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__posForIndicator_DropLocation(
    void *thisObj, int arg__1);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::raise()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__raise(void *thisObj);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::resize(QSize arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__resize_QSize(void *thisObj,
                                                                          void *arg__1_);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::setGeometry(QRect arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setGeometry_QRect(void *thisObj,
                                                                               void *arg__1_);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::setObjectName(const QString & arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setObjectName_QString(
    void *thisObj, const char *arg__1_);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::setVisible(bool arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setVisible_bool(void *thisObj,
                                                                             bool arg__1);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::updatePositions()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__updatePositions(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__registerVirtualMethodCallback(
    void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface_Finalizer(void *, void *cppObj, void *);
}
