/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgets_exports.h"
#include <qlist.h>
#include <qobject.h>
#include <qstring.h>
#include <qbytearray.h>

namespace KDDockWidgets_wrappersNS {
// tag=1043
template<typename T>
class QList_wrapper : public ::QList<T>
{
public:
    ~QList_wrapper();
    // tag=1041
    QList_wrapper();
    // tag=1041
    void append(const QList<T> &t);
    // tag=1041
    void append(const T &t);
    // tag=1041
    const T &at(int i) const;
    // tag=1041
    T &back();
    // tag=1041
    void clear();
    // tag=1041
    const T &constFirst() const;
    // tag=1041
    const T &constLast() const;
    // tag=1041
    bool contains(const T &t) const;
    // tag=1041
    int count() const;
    // tag=1041
    int count(const T &t) const;
    // tag=1041
    void detach();
    // tag=1041
    void detachShared();
    // tag=1041
    bool empty() const;
    // tag=1041
    bool endsWith(const T &t) const;
    // tag=1041
    T &first();
    // tag=1041
    T &front();
    // tag=1041
    int indexOf(const T &t, int from = 0) const;
    // tag=1041
    void insert(int i, const T &t);
    // tag=1041
    bool isDetached() const;
    // tag=1041
    bool isEmpty() const;
    // tag=1041
    bool isSharedWith(const QList<T> &other) const;
    // tag=1041
    T &last();
    // tag=1041
    int lastIndexOf(const T &t, int from = -1) const;
    // tag=1041
    int length() const;
    // tag=1041
    QList<T> mid(int pos, int length = -1) const;
    // tag=1041
    void move(int from, int to);
    // tag=1041
    void pop_back();
    // tag=1041
    void pop_front();
    // tag=1041
    void prepend(const T &t);
    // tag=1041
    void push_back(const T &t);
    // tag=1041
    void push_front(const T &t);
    // tag=1041
    int removeAll(const T &t);
    // tag=1041
    void removeAt(int i);
    // tag=1041
    void removeFirst();
    // tag=1041
    void removeLast();
    // tag=1041
    bool removeOne(const T &t);
    // tag=1041
    void replace(int i, const T &t);
    // tag=1041
    void reserve(int size);
    // tag=1041
    void setSharable(bool sharable);
    // tag=1041
    int size() const;
    // tag=1041
    bool startsWith(const T &t) const;
    // tag=1041
    void swapItemsAt(int i, int j);
    // tag=1041
    T takeAt(int i);
    // tag=1041
    T takeFirst();
    // tag=1041
    T takeLast();
    // tag=1041
    T value(int i) const;
    // tag=1041
    T value(int i, const T &defaultValue) const;
};
}
extern "C" {

// tag=1067
//  QList::QList<T>()
KDDockWidgets_EXPORT void *c_QList_T_QObject_T___constructor();

// tag=1067
//  QList::append(const QList<T > & t)
KDDockWidgets_EXPORT void c_QList_T_QObject_T___append_QList_T(void *thisObj, void *t_);

// tag=1067
//  QList::append(const T & t)
KDDockWidgets_EXPORT void c_QList_T_QObject_T___append_QObject(void *thisObj, void *t_);

// tag=1067
//  QList::at(int i) const
KDDockWidgets_EXPORT const void *c_QList_T_QObject_T___at_int(void *thisObj, int i);

// tag=1067
//  QList::back()
KDDockWidgets_EXPORT void *c_QList_T_QObject_T___back(void *thisObj);

// tag=1067
//  QList::clear()
KDDockWidgets_EXPORT void c_QList_T_QObject_T___clear(void *thisObj);

// tag=1067
//  QList::constFirst() const
KDDockWidgets_EXPORT const void *c_QList_T_QObject_T___constFirst(void *thisObj);

// tag=1067
//  QList::constLast() const
KDDockWidgets_EXPORT const void *c_QList_T_QObject_T___constLast(void *thisObj);

// tag=1067
//  QList::contains(const T & t) const
KDDockWidgets_EXPORT bool c_QList_T_QObject_T___contains_QObject(void *thisObj, void *t_);

// tag=1067
//  QList::count() const
KDDockWidgets_EXPORT int c_QList_T_QObject_T___count(void *thisObj);

// tag=1067
//  QList::count(const T & t) const
KDDockWidgets_EXPORT int c_QList_T_QObject_T___count_QObject(void *thisObj, void *t_);

// tag=1067
//  QList::detach()
KDDockWidgets_EXPORT void c_QList_T_QObject_T___detach(void *thisObj);

// tag=1067
//  QList::detachShared()
KDDockWidgets_EXPORT void c_QList_T_QObject_T___detachShared(void *thisObj);

// tag=1067
//  QList::empty() const
KDDockWidgets_EXPORT bool c_QList_T_QObject_T___empty(void *thisObj);

// tag=1067
//  QList::endsWith(const T & t) const
KDDockWidgets_EXPORT bool c_QList_T_QObject_T___endsWith_QObject(void *thisObj, void *t_);

// tag=1067
//  QList::first()
KDDockWidgets_EXPORT void *c_QList_T_QObject_T___first(void *thisObj);

// tag=1067
//  QList::front()
KDDockWidgets_EXPORT void *c_QList_T_QObject_T___front(void *thisObj);

// tag=1067
//  QList::indexOf(const T & t, int from) const
KDDockWidgets_EXPORT int c_QList_T_QObject_T___indexOf_QObject_int(void *thisObj, void *t_, int from);

// tag=1067
//  QList::insert(int i, const T & t)
KDDockWidgets_EXPORT void c_QList_T_QObject_T___insert_int_QObject(void *thisObj, int i, void *t_);

// tag=1067
//  QList::isDetached() const
KDDockWidgets_EXPORT bool c_QList_T_QObject_T___isDetached(void *thisObj);

// tag=1067
//  QList::isEmpty() const
KDDockWidgets_EXPORT bool c_QList_T_QObject_T___isEmpty(void *thisObj);

// tag=1067
//  QList::isSharedWith(const QList<T > & other) const
KDDockWidgets_EXPORT bool c_QList_T_QObject_T___isSharedWith_QList_T(void *thisObj, void *other_);

// tag=1067
//  QList::last()
KDDockWidgets_EXPORT void *c_QList_T_QObject_T___last(void *thisObj);

// tag=1067
//  QList::lastIndexOf(const T & t, int from) const
KDDockWidgets_EXPORT int c_QList_T_QObject_T___lastIndexOf_QObject_int(void *thisObj, void *t_, int from);

// tag=1067
//  QList::length() const
KDDockWidgets_EXPORT int c_QList_T_QObject_T___length(void *thisObj);

// tag=1067
//  QList::mid(int pos, int length) const
KDDockWidgets_EXPORT void *c_QList_T_QObject_T___mid_int_int(void *thisObj, int pos, int length);

// tag=1067
//  QList::move(int from, int to)
KDDockWidgets_EXPORT void c_QList_T_QObject_T___move_int_int(void *thisObj, int from, int to);

// tag=1067
//  QList::pop_back()
KDDockWidgets_EXPORT void c_QList_T_QObject_T___pop_back(void *thisObj);

// tag=1067
//  QList::pop_front()
KDDockWidgets_EXPORT void c_QList_T_QObject_T___pop_front(void *thisObj);

// tag=1067
//  QList::prepend(const T & t)
KDDockWidgets_EXPORT void c_QList_T_QObject_T___prepend_QObject(void *thisObj, void *t_);

// tag=1067
//  QList::push_back(const T & t)
KDDockWidgets_EXPORT void c_QList_T_QObject_T___push_back_QObject(void *thisObj, void *t_);

// tag=1067
//  QList::push_front(const T & t)
KDDockWidgets_EXPORT void c_QList_T_QObject_T___push_front_QObject(void *thisObj, void *t_);

// tag=1067
//  QList::removeAll(const T & t)
KDDockWidgets_EXPORT int c_QList_T_QObject_T___removeAll_QObject(void *thisObj, void *t_);

// tag=1067
//  QList::removeAt(int i)
KDDockWidgets_EXPORT void c_QList_T_QObject_T___removeAt_int(void *thisObj, int i);

// tag=1067
//  QList::removeFirst()
KDDockWidgets_EXPORT void c_QList_T_QObject_T___removeFirst(void *thisObj);

// tag=1067
//  QList::removeLast()
KDDockWidgets_EXPORT void c_QList_T_QObject_T___removeLast(void *thisObj);

// tag=1067
//  QList::removeOne(const T & t)
KDDockWidgets_EXPORT bool c_QList_T_QObject_T___removeOne_QObject(void *thisObj, void *t_);

// tag=1067
//  QList::replace(int i, const T & t)
KDDockWidgets_EXPORT void c_QList_T_QObject_T___replace_int_QObject(void *thisObj, int i, void *t_);

// tag=1067
//  QList::reserve(int size)
KDDockWidgets_EXPORT void c_QList_T_QObject_T___reserve_int(void *thisObj, int size);

// tag=1067
//  QList::setSharable(bool sharable)
KDDockWidgets_EXPORT void c_QList_T_QObject_T___setSharable_bool(void *thisObj, bool sharable);

// tag=1067
//  QList::size() const
KDDockWidgets_EXPORT int c_QList_T_QObject_T___size(void *thisObj);

// tag=1067
//  QList::startsWith(const T & t) const
KDDockWidgets_EXPORT bool c_QList_T_QObject_T___startsWith_QObject(void *thisObj, void *t_);

// tag=1067
//  QList::swapItemsAt(int i, int j)
KDDockWidgets_EXPORT void c_QList_T_QObject_T___swapItemsAt_int_int(void *thisObj, int i, int j);

// tag=1067
//  QList::takeAt(int i)
KDDockWidgets_EXPORT void *c_QList_T_QObject_T___takeAt_int(void *thisObj, int i);

// tag=1067
//  QList::takeFirst()
KDDockWidgets_EXPORT void *c_QList_T_QObject_T___takeFirst(void *thisObj);

// tag=1067
//  QList::takeLast()
KDDockWidgets_EXPORT void *c_QList_T_QObject_T___takeLast(void *thisObj);

// tag=1067
//  QList::value(int i) const
KDDockWidgets_EXPORT void *c_QList_T_QObject_T___value_int(void *thisObj, int i);

// tag=1067
//  QList::value(int i, const T & defaultValue) const
KDDockWidgets_EXPORT void *c_QList_T_QObject_T___value_int_QObject(void *thisObj, int i, void *defaultValue_);

// tag=1066
KDDockWidgets_EXPORT void c_QList_T_QObject_T___destructor(void *thisObj);

// tag=1047
KDDockWidgets_EXPORT void c_QList_T_QObject_T__Finalizer(void *, void *cppObj, void *);
}
extern "C" {

// tag=1067
//  QList::QList<T>()
KDDockWidgets_EXPORT void *c_QList_T_QByteArray_T___constructor();

// tag=1067
//  QList::append(const QList<T > & t)
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___append_QList_T(void *thisObj, void *t_);

// tag=1067
//  QList::append(const T & t)
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___append_QByteArray(void *thisObj, void *t_);

// tag=1067
//  QList::at(int i) const
KDDockWidgets_EXPORT const void *c_QList_T_QByteArray_T___at_int(void *thisObj, int i);

// tag=1067
//  QList::back()
KDDockWidgets_EXPORT void *c_QList_T_QByteArray_T___back(void *thisObj);

// tag=1067
//  QList::clear()
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___clear(void *thisObj);

// tag=1067
//  QList::constFirst() const
KDDockWidgets_EXPORT const void *c_QList_T_QByteArray_T___constFirst(void *thisObj);

// tag=1067
//  QList::constLast() const
KDDockWidgets_EXPORT const void *c_QList_T_QByteArray_T___constLast(void *thisObj);

// tag=1067
//  QList::contains(const T & t) const
KDDockWidgets_EXPORT bool c_QList_T_QByteArray_T___contains_QByteArray(void *thisObj, void *t_);

// tag=1067
//  QList::count() const
KDDockWidgets_EXPORT int c_QList_T_QByteArray_T___count(void *thisObj);

// tag=1067
//  QList::count(const T & t) const
KDDockWidgets_EXPORT int c_QList_T_QByteArray_T___count_QByteArray(void *thisObj, void *t_);

// tag=1067
//  QList::detach()
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___detach(void *thisObj);

// tag=1067
//  QList::detachShared()
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___detachShared(void *thisObj);

// tag=1067
//  QList::empty() const
KDDockWidgets_EXPORT bool c_QList_T_QByteArray_T___empty(void *thisObj);

// tag=1067
//  QList::endsWith(const T & t) const
KDDockWidgets_EXPORT bool c_QList_T_QByteArray_T___endsWith_QByteArray(void *thisObj, void *t_);

// tag=1067
//  QList::first()
KDDockWidgets_EXPORT void *c_QList_T_QByteArray_T___first(void *thisObj);

// tag=1067
//  QList::front()
KDDockWidgets_EXPORT void *c_QList_T_QByteArray_T___front(void *thisObj);

// tag=1067
//  QList::indexOf(const T & t, int from) const
KDDockWidgets_EXPORT int c_QList_T_QByteArray_T___indexOf_QByteArray_int(void *thisObj, void *t_, int from);

// tag=1067
//  QList::insert(int i, const T & t)
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___insert_int_QByteArray(void *thisObj, int i, void *t_);

// tag=1067
//  QList::isDetached() const
KDDockWidgets_EXPORT bool c_QList_T_QByteArray_T___isDetached(void *thisObj);

// tag=1067
//  QList::isEmpty() const
KDDockWidgets_EXPORT bool c_QList_T_QByteArray_T___isEmpty(void *thisObj);

// tag=1067
//  QList::isSharedWith(const QList<T > & other) const
KDDockWidgets_EXPORT bool c_QList_T_QByteArray_T___isSharedWith_QList_T(void *thisObj, void *other_);

// tag=1067
//  QList::last()
KDDockWidgets_EXPORT void *c_QList_T_QByteArray_T___last(void *thisObj);

// tag=1067
//  QList::lastIndexOf(const T & t, int from) const
KDDockWidgets_EXPORT int c_QList_T_QByteArray_T___lastIndexOf_QByteArray_int(void *thisObj, void *t_, int from);

// tag=1067
//  QList::length() const
KDDockWidgets_EXPORT int c_QList_T_QByteArray_T___length(void *thisObj);

// tag=1067
//  QList::mid(int pos, int length) const
KDDockWidgets_EXPORT void *c_QList_T_QByteArray_T___mid_int_int(void *thisObj, int pos, int length);

// tag=1067
//  QList::move(int from, int to)
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___move_int_int(void *thisObj, int from, int to);

// tag=1067
//  QList::pop_back()
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___pop_back(void *thisObj);

// tag=1067
//  QList::pop_front()
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___pop_front(void *thisObj);

// tag=1067
//  QList::prepend(const T & t)
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___prepend_QByteArray(void *thisObj, void *t_);

// tag=1067
//  QList::push_back(const T & t)
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___push_back_QByteArray(void *thisObj, void *t_);

// tag=1067
//  QList::push_front(const T & t)
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___push_front_QByteArray(void *thisObj, void *t_);

// tag=1067
//  QList::removeAll(const T & t)
KDDockWidgets_EXPORT int c_QList_T_QByteArray_T___removeAll_QByteArray(void *thisObj, void *t_);

// tag=1067
//  QList::removeAt(int i)
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___removeAt_int(void *thisObj, int i);

// tag=1067
//  QList::removeFirst()
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___removeFirst(void *thisObj);

// tag=1067
//  QList::removeLast()
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___removeLast(void *thisObj);

// tag=1067
//  QList::removeOne(const T & t)
KDDockWidgets_EXPORT bool c_QList_T_QByteArray_T___removeOne_QByteArray(void *thisObj, void *t_);

// tag=1067
//  QList::replace(int i, const T & t)
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___replace_int_QByteArray(void *thisObj, int i, void *t_);

// tag=1067
//  QList::reserve(int size)
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___reserve_int(void *thisObj, int size);

// tag=1067
//  QList::setSharable(bool sharable)
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___setSharable_bool(void *thisObj, bool sharable);

// tag=1067
//  QList::size() const
KDDockWidgets_EXPORT int c_QList_T_QByteArray_T___size(void *thisObj);

// tag=1067
//  QList::startsWith(const T & t) const
KDDockWidgets_EXPORT bool c_QList_T_QByteArray_T___startsWith_QByteArray(void *thisObj, void *t_);

// tag=1067
//  QList::swapItemsAt(int i, int j)
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___swapItemsAt_int_int(void *thisObj, int i, int j);

// tag=1067
//  QList::takeAt(int i)
KDDockWidgets_EXPORT void *c_QList_T_QByteArray_T___takeAt_int(void *thisObj, int i);

// tag=1067
//  QList::takeFirst()
KDDockWidgets_EXPORT void *c_QList_T_QByteArray_T___takeFirst(void *thisObj);

// tag=1067
//  QList::takeLast()
KDDockWidgets_EXPORT void *c_QList_T_QByteArray_T___takeLast(void *thisObj);

// tag=1067
//  QList::value(int i) const
KDDockWidgets_EXPORT void *c_QList_T_QByteArray_T___value_int(void *thisObj, int i);

// tag=1067
//  QList::value(int i, const T & defaultValue) const
KDDockWidgets_EXPORT void *c_QList_T_QByteArray_T___value_int_QByteArray(void *thisObj, int i, void *defaultValue_);

// tag=1066
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T___destructor(void *thisObj);

// tag=1047
KDDockWidgets_EXPORT void c_QList_T_QByteArray_T__Finalizer(void *, void *cppObj, void *);
}
