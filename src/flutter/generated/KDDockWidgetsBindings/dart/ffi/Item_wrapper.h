/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <Item_p.h>
#include <qstring.h>
#include <View.h>
#include <qsize.h>
#include <qpoint.h>
#include <qrect.h>
#include <Group.h>
#include <qobject.h>
#include <qlist.h>
#include <qbytearray.h>

namespace KDDockWidgetsBindings_wrappersNS {
class Item_wrapper : public ::Core::Item
{
public:
    ~Item_wrapper();
    Item_wrapper(KDDockWidgets::Core::View *hostWidget);
    KDDockWidgets::Core::Group *asGroupController() const;
    virtual bool checkSanity();
    virtual bool checkSanity_nocallback();
    virtual void dumpLayout(int level = 0);
    virtual void dumpLayout_nocallback(int level = 0);
    QRect geometry() const;
    KDDockWidgets::Core::View *guestView() const;
    int height() const;
    KDDockWidgets::Core::View *hostView() const;
    bool isBeingInserted() const;
    bool isContainer() const;
    bool isMDI() const;
    bool isPlaceholder() const;
    bool isRoot() const;
    virtual bool isVisible(bool excludeBeingInserted = false) const;
    virtual bool isVisible_nocallback(bool excludeBeingInserted = false) const;
    QPoint mapFromParent(QPoint arg__1) const;
    QPoint mapFromRoot(QPoint arg__1) const;
    QRect mapFromRoot(QRect arg__1) const;
    QPoint mapToRoot(QPoint arg__1) const;
    QRect mapToRoot(QRect arg__1) const;
    virtual QSize maxSizeHint() const;
    virtual QSize maxSizeHint_nocallback() const;
    virtual QSize minSize() const;
    virtual QSize minSize_nocallback() const;
    QSize missingSize() const;
    QPoint pos() const;
    QRect rect() const;
    void ref();
    int refCount() const;
    void restore(KDDockWidgets::Core::View *guestView);
    void setBeingInserted(bool arg__1);
    void setGeometry(QRect rect);
    virtual void setGeometry_recursive(QRect rect);
    virtual void setGeometry_recursive_nocallback(QRect rect);
    void setGuestView(KDDockWidgets::Core::View *arg__1);
    virtual void setHostView(KDDockWidgets::Core::View *arg__1);
    virtual void setHostView_nocallback(KDDockWidgets::Core::View *arg__1);
    virtual void setIsVisible(bool arg__1);
    virtual void setIsVisible_nocallback(bool arg__1);
    void setMaxSizeHint(QSize arg__1);
    void setMinSize(QSize arg__1);
    void setPos(QPoint arg__1);
    void setSize(QSize arg__1);
    QSize size() const;
    static QString tr(const char *s, const char *c, int n);
    void turnIntoPlaceholder();
    void unref();
    virtual void updateWidgetGeometries();
    virtual void updateWidgetGeometries_nocallback();
    virtual int visibleCount_recursive() const;
    virtual int visibleCount_recursive_nocallback() const;
    int width() const;
    int x() const;
    int y() const;
    typedef bool (*Callback_checkSanity)(void *);
    Callback_checkSanity m_checkSanityCallback = nullptr;
    typedef void (*Callback_dumpLayout)(void *, int level);
    Callback_dumpLayout m_dumpLayoutCallback = nullptr;
    typedef bool (*Callback_isVisible)(void *, bool excludeBeingInserted);
    Callback_isVisible m_isVisibleCallback = nullptr;
    typedef QSize *(*Callback_maxSizeHint)(void *);
    Callback_maxSizeHint m_maxSizeHintCallback = nullptr;
    typedef QSize *(*Callback_minSize)(void *);
    Callback_minSize m_minSizeCallback = nullptr;
    typedef void (*Callback_setGeometry_recursive)(void *, QRect *rect);
    Callback_setGeometry_recursive m_setGeometry_recursiveCallback = nullptr;
    typedef void (*Callback_setHostView)(void *, KDDockWidgets::Core::View *arg__1);
    Callback_setHostView m_setHostViewCallback = nullptr;
    typedef void (*Callback_setIsVisible)(void *, bool arg__1);
    Callback_setIsVisible m_setIsVisibleCallback = nullptr;
    typedef void (*Callback_updateWidgetGeometries)(void *);
    Callback_updateWidgetGeometries m_updateWidgetGeometriesCallback = nullptr;
    typedef int (*Callback_visibleCount_recursive)(void *);
    Callback_visibleCount_recursive m_visibleCount_recursiveCallback = nullptr;
};
}
extern "C" {
// Core::Item::Item(KDDockWidgets::Core::View * hostWidget)
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__constructor_View(void *hostWidget_);
// Core::Item::asGroupController() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__asGroupController(void *thisObj);
// Core::Item::checkSanity()
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__checkSanity(void *thisObj);
// Core::Item::dumpLayout(int level)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__dumpLayout_int(void *thisObj, int level);
// Core::Item::geometry() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__geometry(void *thisObj);
// Core::Item::guestView() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__guestView(void *thisObj);
// Core::Item::height() const
KDDockWidgetsBindings_EXPORT int c_Layouting__Item__height(void *thisObj);
// Core::Item::hostView() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__hostView(void *thisObj);
// Core::Item::isBeingInserted() const
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__isBeingInserted(void *thisObj);
// Core::Item::isContainer() const
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__isContainer(void *thisObj);
// Core::Item::isMDI() const
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__isMDI(void *thisObj);
// Core::Item::isPlaceholder() const
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__isPlaceholder(void *thisObj);
// Core::Item::isRoot() const
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__isRoot(void *thisObj);
// Core::Item::isVisible(bool excludeBeingInserted) const
KDDockWidgetsBindings_EXPORT bool c_Layouting__Item__isVisible_bool(void *thisObj, bool excludeBeingInserted);
// Core::Item::mapFromParent(QPoint arg__1) const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__mapFromParent_QPoint(void *thisObj, void *arg__1_);
// Core::Item::mapFromRoot(QPoint arg__1) const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__mapFromRoot_QPoint(void *thisObj, void *arg__1_);
// Core::Item::mapFromRoot(QRect arg__1) const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__mapFromRoot_QRect(void *thisObj, void *arg__1_);
// Core::Item::mapToRoot(QPoint arg__1) const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__mapToRoot_QPoint(void *thisObj, void *arg__1_);
// Core::Item::mapToRoot(QRect arg__1) const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__mapToRoot_QRect(void *thisObj, void *arg__1_);
// Core::Item::maxSizeHint() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__maxSizeHint(void *thisObj);
// Core::Item::minSize() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__minSize(void *thisObj);
// Core::Item::missingSize() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__missingSize(void *thisObj);
// Core::Item::pos() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__pos(void *thisObj);
// Core::Item::rect() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__rect(void *thisObj);
// Core::Item::ref()
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__ref(void *thisObj);
// Core::Item::refCount() const
KDDockWidgetsBindings_EXPORT int c_Layouting__Item__refCount(void *thisObj);
// Core::Item::restore(KDDockWidgets::Core::View * guestView)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__restore_View(void *thisObj, void *guestView_);
// Core::Item::setBeingInserted(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setBeingInserted_bool(void *thisObj, bool arg__1);
// Core::Item::setGeometry(QRect rect)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setGeometry_QRect(void *thisObj, void *rect_);
// Core::Item::setGeometry_recursive(QRect rect)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setGeometry_recursive_QRect(void *thisObj, void *rect_);
// Core::Item::setGuestView(KDDockWidgets::Core::View * arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setGuestView_View(void *thisObj, void *arg__1_);
// Core::Item::setHostView(KDDockWidgets::Core::View * arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setHostView_View(void *thisObj, void *arg__1_);
// Core::Item::setIsVisible(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setIsVisible_bool(void *thisObj, bool arg__1);
// Core::Item::setMaxSizeHint(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setMaxSizeHint_QSize(void *thisObj, void *arg__1_);
// Core::Item::setMinSize(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setMinSize_QSize(void *thisObj, void *arg__1_);
// Core::Item::setPos(QPoint arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setPos_QPoint(void *thisObj, void *arg__1_);
// Core::Item::setSize(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__setSize_QSize(void *thisObj, void *arg__1_);
// Core::Item::size() const
KDDockWidgetsBindings_EXPORT void *c_Layouting__Item__size(void *thisObj);
// Core::Item::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_Layouting__Item__tr_char_char_int(const char *s, const char *c, int n);
// Core::Item::turnIntoPlaceholder()
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__turnIntoPlaceholder(void *thisObj);
// Core::Item::unref()
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__unref(void *thisObj);
// Core::Item::updateWidgetGeometries()
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__updateWidgetGeometries(void *thisObj);
// Core::Item::visibleCount_recursive() const
KDDockWidgetsBindings_EXPORT int c_Layouting__Item__visibleCount_recursive(void *thisObj);
// Core::Item::width() const
KDDockWidgetsBindings_EXPORT int c_Layouting__Item__width(void *thisObj);
// Core::Item::x() const
KDDockWidgetsBindings_EXPORT int c_Layouting__Item__x(void *thisObj);
// Core::Item::y() const
KDDockWidgetsBindings_EXPORT int c_Layouting__Item__y(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT int c_static_Layouting__Item___get_separatorThickness();
KDDockWidgetsBindings_EXPORT bool c_static_Layouting__Item___get_s_silenceSanityChecks();
KDDockWidgetsBindings_EXPORT void c_static_Layouting__Item___set_separatorThickness_int(int separatorThickness_);
KDDockWidgetsBindings_EXPORT void c_static_Layouting__Item___set_s_silenceSanityChecks_bool(bool s_silenceSanityChecks_);
KDDockWidgetsBindings_EXPORT void c_Layouting__Item__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_Layouting__Item_Finalizer(void *, void *cppObj, void *);
}
