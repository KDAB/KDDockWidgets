/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <qlist.h>
#include <qobject.h>
#include <qstring.h>
#include <qcoreevent.h>
#include <qbytearray.h>
#include <Group.h>
#include <View.h>
#include <DockWidget.h>
#include <KDDockWidgets.h>
#include <FloatingWindow.h>
#include <Stack.h>
#include <TabBar.h>
#include <qpoint.h>
#include <TitleBar.h>
#include <Item_p.h>
#include <qrect.h>
#include <DropArea.h>
#include <controllers/Layout.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
template<typename T>
class QList_wrapper : public ::QList<T>
{
public:
    ~QList_wrapper();
    QList_wrapper();
    void append(const QList<T> &t);
    void append(const T &t);
    const T &at(int i) const;
    T &back();
    void clear();
    const T &constFirst() const;
    const T &constLast() const;
    bool contains(const T &t) const;
    int count() const;
    int count(const T &t) const;
    void detach();
    void detachShared();
    bool empty() const;
    bool endsWith(const T &t) const;
    T &first();
    T &front();
    int indexOf(const T &t, int from = 0) const;
    void insert(int i, const T &t);
    bool isDetached() const;
    bool isEmpty() const;
    bool isSharedWith(const QList<T> &other) const;
    T &last();
    int lastIndexOf(const T &t, int from = -1) const;
    int length() const;
    QList<T> mid(int pos, int length = -1) const;
    void move(int from, int to);
    void pop_back();
    void pop_front();
    void prepend(const T &t);
    void push_back(const T &t);
    void push_front(const T &t);
    int removeAll(const T &t);
    void removeAt(int i);
    void removeFirst();
    void removeLast();
    bool removeOne(const T &t);
    void replace(int i, const T &t);
    void reserve(int size);
    void setSharable(bool sharable);
    int size() const;
    bool startsWith(const T &t) const;
    void swapItemsAt(int i, int j);
    T takeAt(int i);
    T takeFirst();
    T takeLast();
    T value(int i) const;
    T value(int i, const T &defaultValue) const;
};
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___constructor();
// QList::append(const QList<T > & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___append_QList_T(void *thisObj, void *t_);
// QList::append(const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___append_QObject(void *thisObj, void *t_);
// QList::at(int i) const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QObject_T___at_int(void *thisObj, int i);
// QList::back()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___back(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QObject_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QObject_T___constLast(void *thisObj);
// QList::contains(const T & t) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QObject_T___contains_QObject(void *thisObj, void *t_);
// QList::count() const
KDDockWidgetsBindings_EXPORT int c_QList_T_QObject_T___count(void *thisObj);
// QList::count(const T & t) const
KDDockWidgetsBindings_EXPORT int c_QList_T_QObject_T___count_QObject(void *thisObj, void *t_);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___detach(void *thisObj);
// QList::detachShared()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___detachShared(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QObject_T___empty(void *thisObj);
// QList::endsWith(const T & t) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QObject_T___endsWith_QObject(void *thisObj, void *t_);
// QList::first()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___first(void *thisObj);
// QList::front()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___front(void *thisObj);
// QList::indexOf(const T & t, int from) const
KDDockWidgetsBindings_EXPORT int c_QList_T_QObject_T___indexOf_QObject_int(void *thisObj, void *t_,
                                                                           int from);
// QList::insert(int i, const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___insert_int_QObject(void *thisObj, int i,
                                                                           void *t_);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QObject_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QObject_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QObject_T___isSharedWith_QList_T(void *thisObj,
                                                                             void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___last(void *thisObj);
// QList::lastIndexOf(const T & t, int from) const
KDDockWidgetsBindings_EXPORT int c_QList_T_QObject_T___lastIndexOf_QObject_int(void *thisObj,
                                                                               void *t_, int from);
// QList::length() const
KDDockWidgetsBindings_EXPORT int c_QList_T_QObject_T___length(void *thisObj);
// QList::mid(int pos, int length) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___mid_int_int(void *thisObj, int pos,
                                                                     int length);
// QList::move(int from, int to)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___move_int_int(void *thisObj, int from,
                                                                     int to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___pop_front(void *thisObj);
// QList::prepend(const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___prepend_QObject(void *thisObj, void *t_);
// QList::push_back(const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___push_back_QObject(void *thisObj, void *t_);
// QList::push_front(const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___push_front_QObject(void *thisObj, void *t_);
// QList::removeAll(const T & t)
KDDockWidgetsBindings_EXPORT int c_QList_T_QObject_T___removeAll_QObject(void *thisObj, void *t_);
// QList::removeAt(int i)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___removeAt_int(void *thisObj, int i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___removeLast(void *thisObj);
// QList::removeOne(const T & t)
KDDockWidgetsBindings_EXPORT bool c_QList_T_QObject_T___removeOne_QObject(void *thisObj, void *t_);
// QList::replace(int i, const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___replace_int_QObject(void *thisObj, int i,
                                                                            void *t_);
// QList::reserve(int size)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___reserve_int(void *thisObj, int size);
// QList::setSharable(bool sharable)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___setSharable_bool(void *thisObj,
                                                                         bool sharable);
// QList::size() const
KDDockWidgetsBindings_EXPORT int c_QList_T_QObject_T___size(void *thisObj);
// QList::startsWith(const T & t) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QObject_T___startsWith_QObject(void *thisObj, void *t_);
// QList::swapItemsAt(int i, int j)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___swapItemsAt_int_int(void *thisObj, int i,
                                                                            int j);
// QList::takeAt(int i)
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___takeAt_int(void *thisObj, int i);
// QList::takeFirst()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___takeFirst(void *thisObj);
// QList::takeLast()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___takeLast(void *thisObj);
// QList::value(int i) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___value_int(void *thisObj, int i);
// QList::value(int i, const T & defaultValue) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___value_int_QObject(void *thisObj, int i,
                                                                           void *defaultValue_);
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T__Finalizer(void *, void *cppObj, void *);
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___constructor();
// QList::append(const QList<T > & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___append_QList_T(void *thisObj, void *t_);
// QList::append(const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___append_QByteArray(void *thisObj,
                                                                             void *t_);
// QList::at(int i) const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QByteArray_T___at_int(void *thisObj, int i);
// QList::back()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___back(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QByteArray_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QByteArray_T___constLast(void *thisObj);
// QList::contains(const T & t) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QByteArray_T___contains_QByteArray(void *thisObj,
                                                                               void *t_);
// QList::count() const
KDDockWidgetsBindings_EXPORT int c_QList_T_QByteArray_T___count(void *thisObj);
// QList::count(const T & t) const
KDDockWidgetsBindings_EXPORT int c_QList_T_QByteArray_T___count_QByteArray(void *thisObj, void *t_);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___detach(void *thisObj);
// QList::detachShared()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___detachShared(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QByteArray_T___empty(void *thisObj);
// QList::endsWith(const T & t) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QByteArray_T___endsWith_QByteArray(void *thisObj,
                                                                               void *t_);
// QList::first()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___first(void *thisObj);
// QList::front()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___front(void *thisObj);
// QList::indexOf(const T & t, int from) const
KDDockWidgetsBindings_EXPORT int
c_QList_T_QByteArray_T___indexOf_QByteArray_int(void *thisObj, void *t_, int from);
// QList::insert(int i, const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___insert_int_QByteArray(void *thisObj,
                                                                                 int i, void *t_);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QByteArray_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QByteArray_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QByteArray_T___isSharedWith_QList_T(void *thisObj,
                                                                                void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___last(void *thisObj);
// QList::lastIndexOf(const T & t, int from) const
KDDockWidgetsBindings_EXPORT int
c_QList_T_QByteArray_T___lastIndexOf_QByteArray_int(void *thisObj, void *t_, int from);
// QList::length() const
KDDockWidgetsBindings_EXPORT int c_QList_T_QByteArray_T___length(void *thisObj);
// QList::mid(int pos, int length) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___mid_int_int(void *thisObj, int pos,
                                                                        int length);
// QList::move(int from, int to)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___move_int_int(void *thisObj, int from,
                                                                        int to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___pop_front(void *thisObj);
// QList::prepend(const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___prepend_QByteArray(void *thisObj,
                                                                              void *t_);
// QList::push_back(const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___push_back_QByteArray(void *thisObj,
                                                                                void *t_);
// QList::push_front(const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___push_front_QByteArray(void *thisObj,
                                                                                 void *t_);
// QList::removeAll(const T & t)
KDDockWidgetsBindings_EXPORT int c_QList_T_QByteArray_T___removeAll_QByteArray(void *thisObj,
                                                                               void *t_);
// QList::removeAt(int i)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___removeAt_int(void *thisObj, int i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___removeLast(void *thisObj);
// QList::removeOne(const T & t)
KDDockWidgetsBindings_EXPORT bool c_QList_T_QByteArray_T___removeOne_QByteArray(void *thisObj,
                                                                                void *t_);
// QList::replace(int i, const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___replace_int_QByteArray(void *thisObj,
                                                                                  int i, void *t_);
// QList::reserve(int size)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___reserve_int(void *thisObj, int size);
// QList::setSharable(bool sharable)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___setSharable_bool(void *thisObj,
                                                                            bool sharable);
// QList::size() const
KDDockWidgetsBindings_EXPORT int c_QList_T_QByteArray_T___size(void *thisObj);
// QList::startsWith(const T & t) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QByteArray_T___startsWith_QByteArray(void *thisObj,
                                                                                 void *t_);
// QList::swapItemsAt(int i, int j)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___swapItemsAt_int_int(void *thisObj, int i,
                                                                               int j);
// QList::takeAt(int i)
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___takeAt_int(void *thisObj, int i);
// QList::takeFirst()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___takeFirst(void *thisObj);
// QList::takeLast()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___takeLast(void *thisObj);
// QList::value(int i) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___value_int(void *thisObj, int i);
// QList::value(int i, const T & defaultValue) const
KDDockWidgetsBindings_EXPORT void *
c_QList_T_QByteArray_T___value_int_QByteArray(void *thisObj, int i, void *defaultValue_);
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T__Finalizer(void *, void *cppObj, void *);
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___constructor();
// QList::append(const QList<T > & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___append_QList_T(void *thisObj, void *t_);
// QList::append(const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___append_Group(void *thisObj, void *t_);
// QList::at(int i) const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Group_T___at_int(void *thisObj, int i);
// QList::back()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___back(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Group_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Group_T___constLast(void *thisObj);
// QList::contains(const T & t) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Group_T___contains_Group(void *thisObj, void *t_);
// QList::count() const
KDDockWidgetsBindings_EXPORT int c_QList_T_Group_T___count(void *thisObj);
// QList::count(const T & t) const
KDDockWidgetsBindings_EXPORT int c_QList_T_Group_T___count_Group(void *thisObj, void *t_);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___detach(void *thisObj);
// QList::detachShared()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___detachShared(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Group_T___empty(void *thisObj);
// QList::endsWith(const T & t) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Group_T___endsWith_Group(void *thisObj, void *t_);
// QList::first()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___first(void *thisObj);
// QList::front()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___front(void *thisObj);
// QList::indexOf(const T & t, int from) const
KDDockWidgetsBindings_EXPORT int c_QList_T_Group_T___indexOf_Group_int(void *thisObj, void *t_,
                                                                       int from);
// QList::insert(int i, const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___insert_int_Group(void *thisObj, int i,
                                                                       void *t_);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Group_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Group_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Group_T___isSharedWith_QList_T(void *thisObj,
                                                                           void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___last(void *thisObj);
// QList::lastIndexOf(const T & t, int from) const
KDDockWidgetsBindings_EXPORT int c_QList_T_Group_T___lastIndexOf_Group_int(void *thisObj, void *t_,
                                                                           int from);
// QList::length() const
KDDockWidgetsBindings_EXPORT int c_QList_T_Group_T___length(void *thisObj);
// QList::mid(int pos, int length) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___mid_int_int(void *thisObj, int pos,
                                                                   int length);
// QList::move(int from, int to)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___move_int_int(void *thisObj, int from, int to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___pop_front(void *thisObj);
// QList::prepend(const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___prepend_Group(void *thisObj, void *t_);
// QList::push_back(const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___push_back_Group(void *thisObj, void *t_);
// QList::push_front(const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___push_front_Group(void *thisObj, void *t_);
// QList::removeAll(const T & t)
KDDockWidgetsBindings_EXPORT int c_QList_T_Group_T___removeAll_Group(void *thisObj, void *t_);
// QList::removeAt(int i)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___removeAt_int(void *thisObj, int i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___removeLast(void *thisObj);
// QList::removeOne(const T & t)
KDDockWidgetsBindings_EXPORT bool c_QList_T_Group_T___removeOne_Group(void *thisObj, void *t_);
// QList::replace(int i, const T & t)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___replace_int_Group(void *thisObj, int i,
                                                                        void *t_);
// QList::reserve(int size)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___reserve_int(void *thisObj, int size);
// QList::setSharable(bool sharable)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___setSharable_bool(void *thisObj,
                                                                       bool sharable);
// QList::size() const
KDDockWidgetsBindings_EXPORT int c_QList_T_Group_T___size(void *thisObj);
// QList::startsWith(const T & t) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Group_T___startsWith_Group(void *thisObj, void *t_);
// QList::swapItemsAt(int i, int j)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___swapItemsAt_int_int(void *thisObj, int i,
                                                                          int j);
// QList::takeAt(int i)
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___takeAt_int(void *thisObj, int i);
// QList::takeFirst()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___takeFirst(void *thisObj);
// QList::takeLast()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___takeLast(void *thisObj);
// QList::value(int i) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___value_int(void *thisObj, int i);
// QList::value(int i, const T & defaultValue) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___value_int_Group(void *thisObj, int i,
                                                                       void *defaultValue_);
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T__Finalizer(void *, void *cppObj, void *);
}
