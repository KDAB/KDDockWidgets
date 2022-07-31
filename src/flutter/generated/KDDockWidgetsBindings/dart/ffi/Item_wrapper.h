/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <Item_p.h>
#include <qstring.h>
#include <View.h>
#include <qsize.h>
#include <qpoint.h>
#include <qrect.h>
#include <qobject.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qbytearray.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1017
class Item_wrapper : public ::Layouting::Item
{
public:
    ~Item_wrapper();
    // tag=1041
    Item_wrapper(KDDockWidgets::View *hostWidget);
    // tag=1041
    virtual bool checkSanity();
    // tag=1008
    virtual bool checkSanity_nocallback();
    // tag=1041
    virtual void customEvent(QEvent *event);
    // tag=1008
    virtual void customEvent_nocallback(QEvent *event);
    // tag=1041
    virtual void dumpLayout(int level = 0);
    // tag=1008
    virtual void dumpLayout_nocallback(int level = 0);
    // tag=1041
    virtual bool event(QEvent *event);
    // tag=1008
    virtual bool event_nocallback(QEvent *event);
    // tag=1041
    virtual bool eventFilter(QObject *watched, QEvent *event);
    // tag=1008
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    // tag=1041
    QRect geometry() const;
    // tag=1041
    KDDockWidgets::View *guestView() const;
    // tag=1041
    int height() const;
    // tag=1041
    KDDockWidgets::View *hostView() const;
    // tag=1041
    bool isBeingInserted() const;
    // tag=1041
    bool isContainer() const;
    // tag=1041
    bool isMDI() const;
    // tag=1041
    bool isPlaceholder() const;
    // tag=1041
    bool isRoot() const;
    // tag=1041
    virtual bool isVisible(bool excludeBeingInserted = false) const;
    // tag=1008
    virtual bool isVisible_nocallback(bool excludeBeingInserted = false) const;
    // tag=1041
    QPoint mapFromParent(QPoint arg__1) const;
    // tag=1041
    QPoint mapFromRoot(QPoint arg__1) const;
    // tag=1041
    QRect mapFromRoot(QRect arg__1) const;
    // tag=1041
    QPoint mapToRoot(QPoint arg__1) const;
    // tag=1041
    QRect mapToRoot(QRect arg__1) const;
    // tag=1041
    virtual QSize maxSizeHint() const;
    // tag=1008
    virtual QSize maxSizeHint_nocallback() const;
    // tag=1041
    virtual QSize minSize() const;
    // tag=1008
    virtual QSize minSize_nocallback() const;
    // tag=1041
    QSize missingSize() const;
    // tag=1041
    QPoint pos() const;
    // tag=1041
    QRect rect() const;
    // tag=1041
    void ref();
    // tag=1041
    int refCount() const;
    // tag=1041
    void restore(KDDockWidgets::View *guestView);
    // tag=1041
    void setBeingInserted(bool arg__1);
    // tag=1041
    void setGeometry(QRect rect);
    // tag=1041
    virtual void setGeometry_recursive(QRect rect);
    // tag=1008
    virtual void setGeometry_recursive_nocallback(QRect rect);
    // tag=1041
    void setGuestView(KDDockWidgets::View *arg__1);
    // tag=1041
    virtual void setHostView(KDDockWidgets::View *arg__1);
    // tag=1008
    virtual void setHostView_nocallback(KDDockWidgets::View *arg__1);
    // tag=1041
    virtual void setIsVisible(bool arg__1);
    // tag=1008
    virtual void setIsVisible_nocallback(bool arg__1);
    // tag=1041
    void setMaxSizeHint(QSize arg__1);
    // tag=1041
    void setMinSize(QSize arg__1);
    // tag=1041
    void setPos(QPoint arg__1);
    // tag=1041
    void setSize(QSize arg__1);
    // tag=1041
    QSize size() const;
    // tag=1041
    static QString tr(const char *s, const char *c, int n);
    // tag=1041
    void unref();
    // tag=1041
    virtual void updateWidgetGeometries();
    // tag=1008
    virtual void updateWidgetGeometries_nocallback();
    // tag=1041
    virtual int visibleCount_recursive() const;
    // tag=1008
    virtual int visibleCount_recursive_nocallback() const;
    // tag=1041
    int width() const;
    // tag=1041
    int x() const;
    // tag=1041
    int y() const;
    // tag=1042
    typedef bool (*Callback_checkSanity)(void *);
    Callback_checkSanity m_checkSanityCallback = nullptr;
    // tag=1042
    typedef void (*Callback_customEvent)(void *, QEvent *event);
    Callback_customEvent m_customEventCallback = nullptr;
    // tag=1042
    typedef void (*Callback_dumpLayout)(void *, int level);
    Callback_dumpLayout m_dumpLayoutCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_event)(void *, QEvent *event);
    Callback_event m_eventCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_eventFilter)(void *, QObject *watched, QEvent *event);
    Callback_eventFilter m_eventFilterCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_isVisible)(void *, bool excludeBeingInserted);
    Callback_isVisible m_isVisibleCallback = nullptr;
    // tag=1042
    typedef QSize *(*Callback_maxSizeHint)(void *);
    Callback_maxSizeHint m_maxSizeHintCallback = nullptr;
    // tag=1042
    typedef QSize *(*Callback_minSize)(void *);
    Callback_minSize m_minSizeCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setGeometry_recursive)(void *, QRect rect);
    Callback_setGeometry_recursive m_setGeometry_recursiveCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setHostView)(void *, KDDockWidgets::View *arg__1);
    Callback_setHostView m_setHostViewCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setIsVisible)(void *, bool arg__1);
    Callback_setIsVisible m_setIsVisibleCallback = nullptr;
    // tag=1042
    typedef void (*Callback_updateWidgetGeometries)(void *);
    Callback_updateWidgetGeometries m_updateWidgetGeometriesCallback = nullptr;
    // tag=1042
    typedef int (*Callback_visibleCount_recursive)(void *);
    Callback_visibleCount_recursive m_visibleCount_recursiveCallback = nullptr;
};
}
extern "C" {

// tag=1067
//  Layouting::Item::Item(KDDockWidgets::View * hostWidget)
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__constructor_View(void *hostWidget_);

// tag=1067
//  Layouting::Item::checkSanity()
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__checkSanity(void *thisObj);

// tag=1067
//  Layouting::Item::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__customEvent_QEvent(void *thisObj, void *event_);

// tag=1067
//  Layouting::Item::dumpLayout(int level)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__dumpLayout_int(void *thisObj, int level);

// tag=1067
//  Layouting::Item::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__event_QEvent(void *thisObj, void *event_);

// tag=1067
//  Layouting::Item::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_);

// tag=1067
//  Layouting::Item::geometry() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__geometry(void *thisObj);

// tag=1067
//  Layouting::Item::guestView() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__guestView(void *thisObj);

// tag=1067
//  Layouting::Item::height() const
KDDockWidgetsBindings_EXPORT int c_Layouting__Item__height(void *thisObj);

// tag=1067
//  Layouting::Item::hostView() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__hostView(void *thisObj);

// tag=1067
//  Layouting::Item::isBeingInserted() const
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__isBeingInserted(void *thisObj);

// tag=1067
//  Layouting::Item::isContainer() const
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__isContainer(void *thisObj);

// tag=1067
//  Layouting::Item::isMDI() const
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__isMDI(void *thisObj);

// tag=1067
//  Layouting::Item::isPlaceholder() const
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__isPlaceholder(void *thisObj);

// tag=1067
//  Layouting::Item::isRoot() const
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__isRoot(void *thisObj);

// tag=1067
//  Layouting::Item::isVisible(bool excludeBeingInserted) const
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__isVisible_bool(void *thisObj, bool excludeBeingInserted);

// tag=1067
//  Layouting::Item::mapFromParent(QPoint arg__1) const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__mapFromParent_QPoint(void *thisObj, void *arg__1_);

// tag=1067
//  Layouting::Item::mapFromRoot(QPoint arg__1) const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__mapFromRoot_QPoint(void *thisObj, void *arg__1_);

// tag=1067
//  Layouting::Item::mapFromRoot(QRect arg__1) const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__mapFromRoot_QRect(void *thisObj, void *arg__1_);

// tag=1067
//  Layouting::Item::mapToRoot(QPoint arg__1) const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__mapToRoot_QPoint(void *thisObj, void *arg__1_);

// tag=1067
//  Layouting::Item::mapToRoot(QRect arg__1) const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__mapToRoot_QRect(void *thisObj, void *arg__1_);

// tag=1067
//  Layouting::Item::maxSizeHint() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__maxSizeHint(void *thisObj);

// tag=1067
//  Layouting::Item::minSize() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__minSize(void *thisObj);

// tag=1067
//  Layouting::Item::missingSize() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__missingSize(void *thisObj);

// tag=1067
//  Layouting::Item::pos() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__pos(void *thisObj);

// tag=1067
//  Layouting::Item::rect() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__rect(void *thisObj);

// tag=1067
//  Layouting::Item::ref()
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__ref(void *thisObj);

// tag=1067
//  Layouting::Item::refCount() const
KDDockWidgetsBindings_EXPORT int c_Layouting__Item__refCount(void *thisObj);

// tag=1067
//  Layouting::Item::restore(KDDockWidgets::View * guestView)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__restore_View(void *thisObj, void *guestView_);

// tag=1067
//  Layouting::Item::setBeingInserted(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setBeingInserted_bool(void *thisObj, bool arg__1);

// tag=1067
//  Layouting::Item::setGeometry(QRect rect)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setGeometry_QRect(void *thisObj, void *rect_);

// tag=1067
//  Layouting::Item::setGeometry_recursive(QRect rect)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setGeometry_recursive_QRect(void *thisObj, void *rect_);

// tag=1067
//  Layouting::Item::setGuestView(KDDockWidgets::View * arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setGuestView_View(void *thisObj, void *arg__1_);

// tag=1067
//  Layouting::Item::setHostView(KDDockWidgets::View * arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setHostView_View(void *thisObj, void *arg__1_);

// tag=1067
//  Layouting::Item::setIsVisible(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setIsVisible_bool(void *thisObj, bool arg__1);

// tag=1067
//  Layouting::Item::setMaxSizeHint(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setMaxSizeHint_QSize(void *thisObj, void *arg__1_);

// tag=1067
//  Layouting::Item::setMinSize(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setMinSize_QSize(void *thisObj, void *arg__1_);

// tag=1067
//  Layouting::Item::setPos(QPoint arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setPos_QPoint(void *thisObj, void *arg__1_);

// tag=1067
//  Layouting::Item::setSize(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setSize_QSize(void *thisObj, void *arg__1_);

// tag=1067
//  Layouting::Item::size() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__size(void *thisObj);

// tag=1067
//  Layouting::Item::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_Layouting__Item__tr_char_char_int(const char *s, const char *c, int n);

// tag=1067
//  Layouting::Item::unref()
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__unref(void *thisObj);

// tag=1067
//  Layouting::Item::updateWidgetGeometries()
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__updateWidgetGeometries(void *thisObj);

// tag=1067
//  Layouting::Item::visibleCount_recursive() const
KDDockWidgetsBindings_EXPORT int c_Layouting__Item__visibleCount_recursive(void *thisObj);

// tag=1067
//  Layouting::Item::width() const
KDDockWidgetsBindings_EXPORT int c_Layouting__Item__width(void *thisObj);

// tag=1067
//  Layouting::Item::x() const
KDDockWidgetsBindings_EXPORT int c_Layouting__Item__x(void *thisObj);

// tag=1067
//  Layouting::Item::y() const
KDDockWidgetsBindings_EXPORT int c_Layouting__Item__y(void *thisObj);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__destructor(void *thisObj);

// tag=1044
KDDockWidgetsBindings_EXPORT int c_static_Layouting__Item___get_separatorThickness();

// tag=1044
KDDockWidgetsBindings_EXPORT bool c_static_Layouting__Item___get_s_silenceSanityChecks();

// tag=1045
KDDockWidgetsBindings_EXPORT void c_static_Layouting__Item___set_separatorThickness_int(int separatorThickness_);

// tag=1045
KDDockWidgetsBindings_EXPORT void c_static_Layouting__Item___set_s_silenceSanityChecks_bool(bool s_silenceSanityChecks_);

// tag=1046
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgetsBindings_EXPORT void c_Layouting__Item_Finalizer(void *, void *cppObj, void *);
}
