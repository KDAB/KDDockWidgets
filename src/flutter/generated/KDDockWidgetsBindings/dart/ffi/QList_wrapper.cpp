/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "QList_wrapper.h"


#include <QDebug>


namespace Dartagnan {

typedef int (*CleanupCallback)(void *thisPtr);
static CleanupCallback s_cleanupCallback = nullptr;

template<typename T>
struct ValueWrapper
{
    T value;
};

}
namespace KDDockWidgetsBindings_wrappersNS {
template<typename T>
QList_wrapper<T>::QList_wrapper()
    : ::QList<T>()
{
}
template<typename T>
void QList_wrapper<T>::append(const QList<T> &t)
{
    ::QList<T>::append(t);
}
template<typename T>
void QList_wrapper<T>::append(const T &t)
{
    ::QList<T>::append(t);
}
template<typename T>
const T &QList_wrapper<T>::at(int i) const
{
    return ::QList<T>::at(i);
}
template<typename T>
T &QList_wrapper<T>::back()
{
    return ::QList<T>::back();
}
template<typename T>
void QList_wrapper<T>::clear()
{
    ::QList<T>::clear();
}
template<typename T>
const T &QList_wrapper<T>::constFirst() const
{
    return ::QList<T>::constFirst();
}
template<typename T>
const T &QList_wrapper<T>::constLast() const
{
    return ::QList<T>::constLast();
}
template<typename T>
bool QList_wrapper<T>::contains(const T &t) const
{
    return ::QList<T>::contains(t);
}
template<typename T>
int QList_wrapper<T>::count() const
{
    return ::QList<T>::count();
}
template<typename T>
int QList_wrapper<T>::count(const T &t) const
{
    return ::QList<T>::count(t);
}
template<typename T>
void QList_wrapper<T>::detach()
{
    ::QList<T>::detach();
}
template<typename T>
void QList_wrapper<T>::detachShared()
{
    ::QList<T>::detachShared();
}
template<typename T>
bool QList_wrapper<T>::empty() const
{
    return ::QList<T>::empty();
}
template<typename T>
bool QList_wrapper<T>::endsWith(const T &t) const
{
    return ::QList<T>::endsWith(t);
}
template<typename T>
T &QList_wrapper<T>::first()
{
    return ::QList<T>::first();
}
template<typename T>
T &QList_wrapper<T>::front()
{
    return ::QList<T>::front();
}
template<typename T>
int QList_wrapper<T>::indexOf(const T &t, int from) const
{
    return ::QList<T>::indexOf(t, from);
}
template<typename T>
void QList_wrapper<T>::insert(int i, const T &t)
{
    ::QList<T>::insert(i, t);
}
template<typename T>
bool QList_wrapper<T>::isDetached() const
{
    return ::QList<T>::isDetached();
}
template<typename T>
bool QList_wrapper<T>::isEmpty() const
{
    return ::QList<T>::isEmpty();
}
template<typename T>
bool QList_wrapper<T>::isSharedWith(const QList<T> &other) const
{
    return ::QList<T>::isSharedWith(other);
}
template<typename T>
T &QList_wrapper<T>::last()
{
    return ::QList<T>::last();
}
template<typename T>
int QList_wrapper<T>::lastIndexOf(const T &t, int from) const
{
    return ::QList<T>::lastIndexOf(t, from);
}
template<typename T>
int QList_wrapper<T>::length() const
{
    return ::QList<T>::length();
}
template<typename T>
QList<T> QList_wrapper<T>::mid(int pos, int length) const
{
    return ::QList<T>::mid(pos, length);
}
template<typename T>
void QList_wrapper<T>::move(int from, int to)
{
    ::QList<T>::move(from, to);
}
template<typename T>
void QList_wrapper<T>::pop_back()
{
    ::QList<T>::pop_back();
}
template<typename T>
void QList_wrapper<T>::pop_front()
{
    ::QList<T>::pop_front();
}
template<typename T>
void QList_wrapper<T>::prepend(const T &t)
{
    ::QList<T>::prepend(t);
}
template<typename T>
void QList_wrapper<T>::push_back(const T &t)
{
    ::QList<T>::push_back(t);
}
template<typename T>
void QList_wrapper<T>::push_front(const T &t)
{
    ::QList<T>::push_front(t);
}
template<typename T>
int QList_wrapper<T>::removeAll(const T &t)
{
    return ::QList<T>::removeAll(t);
}
template<typename T>
void QList_wrapper<T>::removeAt(int i)
{
    ::QList<T>::removeAt(i);
}
template<typename T>
void QList_wrapper<T>::removeFirst()
{
    ::QList<T>::removeFirst();
}
template<typename T>
void QList_wrapper<T>::removeLast()
{
    ::QList<T>::removeLast();
}
template<typename T>
bool QList_wrapper<T>::removeOne(const T &t)
{
    return ::QList<T>::removeOne(t);
}
template<typename T>
void QList_wrapper<T>::replace(int i, const T &t)
{
    ::QList<T>::replace(i, t);
}
template<typename T>
void QList_wrapper<T>::reserve(int size)
{
    ::QList<T>::reserve(size);
}
template<typename T>
void QList_wrapper<T>::setSharable(bool sharable)
{
    ::QList<T>::setSharable(sharable);
}
template<typename T>
int QList_wrapper<T>::size() const
{
    return ::QList<T>::size();
}
template<typename T>
bool QList_wrapper<T>::startsWith(const T &t) const
{
    return ::QList<T>::startsWith(t);
}
template<typename T>
void QList_wrapper<T>::swapItemsAt(int i, int j)
{
    ::QList<T>::swapItemsAt(i, j);
}
template<typename T>
T QList_wrapper<T>::takeAt(int i)
{
    return ::QList<T>::takeAt(i);
}
template<typename T>
T QList_wrapper<T>::takeFirst()
{
    return ::QList<T>::takeFirst();
}
template<typename T>
T QList_wrapper<T>::takeLast()
{
    return ::QList<T>::takeLast();
}
template<typename T>
T QList_wrapper<T>::value(int i) const
{
    return ::QList<T>::value(i);
}
template<typename T>
T QList_wrapper<T>::value(int i, const T &defaultValue) const
{
    return ::QList<T>::value(i, defaultValue);
}
template<typename T>
QList_wrapper<T>::~QList_wrapper()
{
}

}
template<typename T>
static QList<T> *fromPtr(void *ptr)
{
    return reinterpret_cast<QList<T> *>(ptr);
}
template<typename T>
static KDDockWidgetsBindings_wrappersNS::QList_wrapper<T> *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<T> *>(ptr);
}
extern "C" {
void c_QList_T_QObject_T__Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<QObject *> *>(cppObj);
}
void *c_QList_T_QObject_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<QObject *>();
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & t)
void c_QList_T_QObject_T___append_QList_T(void *thisObj, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QList<QObject *> *>(t_);
    fromPtr<QObject *>(thisObj)->append(t);
}
// append(const T & t)
void c_QList_T_QObject_T___append_QObject(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<QObject *>(t_);
    fromPtr<QObject *>(thisObj)->append(t);
}
// at(int i) const
const void *c_QList_T_QObject_T___at_int(void *thisObj, int i)
{
    return fromPtr<QObject *>(thisObj)->at(i);
}
// back()
void *c_QList_T_QObject_T___back(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->back();
}
// clear()
void c_QList_T_QObject_T___clear(void *thisObj)
{
    fromPtr<QObject *>(thisObj)->clear();
}
// constFirst() const
const void *c_QList_T_QObject_T___constFirst(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->constFirst();
}
// constLast() const
const void *c_QList_T_QObject_T___constLast(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->constLast();
}
// contains(const T & t) const
bool c_QList_T_QObject_T___contains_QObject(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<QObject *>(t_);
    return fromPtr<QObject *>(thisObj)->contains(t);
}
// count() const
int c_QList_T_QObject_T___count(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->count();
}
// count(const T & t) const
int c_QList_T_QObject_T___count_QObject(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<QObject *>(t_);
    return fromPtr<QObject *>(thisObj)->count(t);
}
// detach()
void c_QList_T_QObject_T___detach(void *thisObj)
{
    fromPtr<QObject *>(thisObj)->detach();
}
// detachShared()
void c_QList_T_QObject_T___detachShared(void *thisObj)
{
    fromPtr<QObject *>(thisObj)->detachShared();
}
// empty() const
bool c_QList_T_QObject_T___empty(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->empty();
}
// endsWith(const T & t) const
bool c_QList_T_QObject_T___endsWith_QObject(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<QObject *>(t_);
    return fromPtr<QObject *>(thisObj)->endsWith(t);
}
// first()
void *c_QList_T_QObject_T___first(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->first();
}
// front()
void *c_QList_T_QObject_T___front(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->front();
}
// indexOf(const T & t, int from) const
int c_QList_T_QObject_T___indexOf_QObject_int(void *thisObj, void *t_, int from)
{
    auto t = reinterpret_cast<QObject *>(t_);
    return fromPtr<QObject *>(thisObj)->indexOf(t, from);
}
// insert(int i, const T & t)
void c_QList_T_QObject_T___insert_int_QObject(void *thisObj, int i, void *t_)
{
    auto t = reinterpret_cast<QObject *>(t_);
    fromPtr<QObject *>(thisObj)->insert(i, t);
}
// isDetached() const
bool c_QList_T_QObject_T___isDetached(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->isDetached();
}
// isEmpty() const
bool c_QList_T_QObject_T___isEmpty(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->isEmpty();
}
// isSharedWith(const QList<T > & other) const
bool c_QList_T_QObject_T___isSharedWith_QList_T(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QList<QObject *> *>(other_);
    return fromPtr<QObject *>(thisObj)->isSharedWith(other);
}
// last()
void *c_QList_T_QObject_T___last(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->last();
}
// lastIndexOf(const T & t, int from) const
int c_QList_T_QObject_T___lastIndexOf_QObject_int(void *thisObj, void *t_, int from)
{
    auto t = reinterpret_cast<QObject *>(t_);
    return fromPtr<QObject *>(thisObj)->lastIndexOf(t, from);
}
// length() const
int c_QList_T_QObject_T___length(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->length();
}
// mid(int pos, int length) const
void *c_QList_T_QObject_T___mid_int_int(void *thisObj, int pos, int length)
{
    return new Dartagnan::ValueWrapper<QList<QObject *>> { fromPtr<QObject *>(thisObj)->mid(
        pos, length) };
}
// move(int from, int to)
void c_QList_T_QObject_T___move_int_int(void *thisObj, int from, int to)
{
    fromPtr<QObject *>(thisObj)->move(from, to);
}
// pop_back()
void c_QList_T_QObject_T___pop_back(void *thisObj)
{
    fromPtr<QObject *>(thisObj)->pop_back();
}
// pop_front()
void c_QList_T_QObject_T___pop_front(void *thisObj)
{
    fromPtr<QObject *>(thisObj)->pop_front();
}
// prepend(const T & t)
void c_QList_T_QObject_T___prepend_QObject(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<QObject *>(t_);
    fromPtr<QObject *>(thisObj)->prepend(t);
}
// push_back(const T & t)
void c_QList_T_QObject_T___push_back_QObject(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<QObject *>(t_);
    fromPtr<QObject *>(thisObj)->push_back(t);
}
// push_front(const T & t)
void c_QList_T_QObject_T___push_front_QObject(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<QObject *>(t_);
    fromPtr<QObject *>(thisObj)->push_front(t);
}
// removeAll(const T & t)
int c_QList_T_QObject_T___removeAll_QObject(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<QObject *>(t_);
    return fromPtr<QObject *>(thisObj)->removeAll(t);
}
// removeAt(int i)
void c_QList_T_QObject_T___removeAt_int(void *thisObj, int i)
{
    fromPtr<QObject *>(thisObj)->removeAt(i);
}
// removeFirst()
void c_QList_T_QObject_T___removeFirst(void *thisObj)
{
    fromPtr<QObject *>(thisObj)->removeFirst();
}
// removeLast()
void c_QList_T_QObject_T___removeLast(void *thisObj)
{
    fromPtr<QObject *>(thisObj)->removeLast();
}
// removeOne(const T & t)
bool c_QList_T_QObject_T___removeOne_QObject(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<QObject *>(t_);
    return fromPtr<QObject *>(thisObj)->removeOne(t);
}
// replace(int i, const T & t)
void c_QList_T_QObject_T___replace_int_QObject(void *thisObj, int i, void *t_)
{
    auto t = reinterpret_cast<QObject *>(t_);
    fromPtr<QObject *>(thisObj)->replace(i, t);
}
// reserve(int size)
void c_QList_T_QObject_T___reserve_int(void *thisObj, int size)
{
    fromPtr<QObject *>(thisObj)->reserve(size);
}
// setSharable(bool sharable)
void c_QList_T_QObject_T___setSharable_bool(void *thisObj, bool sharable)
{
    fromPtr<QObject *>(thisObj)->setSharable(sharable);
}
// size() const
int c_QList_T_QObject_T___size(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->size();
}
// startsWith(const T & t) const
bool c_QList_T_QObject_T___startsWith_QObject(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<QObject *>(t_);
    return fromPtr<QObject *>(thisObj)->startsWith(t);
}
// swapItemsAt(int i, int j)
void c_QList_T_QObject_T___swapItemsAt_int_int(void *thisObj, int i, int j)
{
    fromPtr<QObject *>(thisObj)->swapItemsAt(i, j);
}
// takeAt(int i)
void *c_QList_T_QObject_T___takeAt_int(void *thisObj, int i)
{
    return fromPtr<QObject *>(thisObj)->takeAt(i);
}
// takeFirst()
void *c_QList_T_QObject_T___takeFirst(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->takeFirst();
}
// takeLast()
void *c_QList_T_QObject_T___takeLast(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->takeLast();
}
// value(int i) const
void *c_QList_T_QObject_T___value_int(void *thisObj, int i)
{
    return fromPtr<QObject *>(thisObj)->value(i);
}
// value(int i, const T & defaultValue) const
void *c_QList_T_QObject_T___value_int_QObject(void *thisObj, int i, void *defaultValue_)
{
    auto defaultValue = reinterpret_cast<QObject *>(defaultValue_);
    return fromPtr<QObject *>(thisObj)->value(i, defaultValue);
}
void c_QList_T_QObject_T___destructor(void *thisObj)
{
    delete fromPtr<QObject *>(thisObj);
}
}
extern "C" {
void c_QList_T_QByteArray_T__Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<QByteArray> *>(cppObj);
}
void *c_QList_T_QByteArray_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<QByteArray>();
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & t)
void c_QList_T_QByteArray_T___append_QList_T(void *thisObj, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QList<QByteArray> *>(t_);
    fromPtr<QByteArray>(thisObj)->append(t);
}
// append(const T & t)
void c_QList_T_QByteArray_T___append_QByteArray(void *thisObj, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    fromPtr<QByteArray>(thisObj)->append(t);
}
// at(int i) const
const void *c_QList_T_QByteArray_T___at_int(void *thisObj, int i)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->at(i) };
}
// back()
void *c_QList_T_QByteArray_T___back(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->back() };
}
// clear()
void c_QList_T_QByteArray_T___clear(void *thisObj)
{
    fromPtr<QByteArray>(thisObj)->clear();
}
// constFirst() const
const void *c_QList_T_QByteArray_T___constFirst(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->constFirst() };
}
// constLast() const
const void *c_QList_T_QByteArray_T___constLast(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->constLast() };
}
// contains(const T & t) const
bool c_QList_T_QByteArray_T___contains_QByteArray(void *thisObj, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    return fromPtr<QByteArray>(thisObj)->contains(t);
}
// count() const
int c_QList_T_QByteArray_T___count(void *thisObj)
{
    return fromPtr<QByteArray>(thisObj)->count();
}
// count(const T & t) const
int c_QList_T_QByteArray_T___count_QByteArray(void *thisObj, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    return fromPtr<QByteArray>(thisObj)->count(t);
}
// detach()
void c_QList_T_QByteArray_T___detach(void *thisObj)
{
    fromPtr<QByteArray>(thisObj)->detach();
}
// detachShared()
void c_QList_T_QByteArray_T___detachShared(void *thisObj)
{
    fromPtr<QByteArray>(thisObj)->detachShared();
}
// empty() const
bool c_QList_T_QByteArray_T___empty(void *thisObj)
{
    return fromPtr<QByteArray>(thisObj)->empty();
}
// endsWith(const T & t) const
bool c_QList_T_QByteArray_T___endsWith_QByteArray(void *thisObj, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    return fromPtr<QByteArray>(thisObj)->endsWith(t);
}
// first()
void *c_QList_T_QByteArray_T___first(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->first() };
}
// front()
void *c_QList_T_QByteArray_T___front(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->front() };
}
// indexOf(const T & t, int from) const
int c_QList_T_QByteArray_T___indexOf_QByteArray_int(void *thisObj, void *t_, int from)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    return fromPtr<QByteArray>(thisObj)->indexOf(t, from);
}
// insert(int i, const T & t)
void c_QList_T_QByteArray_T___insert_int_QByteArray(void *thisObj, int i, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    fromPtr<QByteArray>(thisObj)->insert(i, t);
}
// isDetached() const
bool c_QList_T_QByteArray_T___isDetached(void *thisObj)
{
    return fromPtr<QByteArray>(thisObj)->isDetached();
}
// isEmpty() const
bool c_QList_T_QByteArray_T___isEmpty(void *thisObj)
{
    return fromPtr<QByteArray>(thisObj)->isEmpty();
}
// isSharedWith(const QList<T > & other) const
bool c_QList_T_QByteArray_T___isSharedWith_QList_T(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QList<QByteArray> *>(other_);
    return fromPtr<QByteArray>(thisObj)->isSharedWith(other);
}
// last()
void *c_QList_T_QByteArray_T___last(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->last() };
}
// lastIndexOf(const T & t, int from) const
int c_QList_T_QByteArray_T___lastIndexOf_QByteArray_int(void *thisObj, void *t_, int from)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    return fromPtr<QByteArray>(thisObj)->lastIndexOf(t, from);
}
// length() const
int c_QList_T_QByteArray_T___length(void *thisObj)
{
    return fromPtr<QByteArray>(thisObj)->length();
}
// mid(int pos, int length) const
void *c_QList_T_QByteArray_T___mid_int_int(void *thisObj, int pos, int length)
{
    return new Dartagnan::ValueWrapper<QList<QByteArray>> { fromPtr<QByteArray>(thisObj)->mid(
        pos, length) };
}
// move(int from, int to)
void c_QList_T_QByteArray_T___move_int_int(void *thisObj, int from, int to)
{
    fromPtr<QByteArray>(thisObj)->move(from, to);
}
// pop_back()
void c_QList_T_QByteArray_T___pop_back(void *thisObj)
{
    fromPtr<QByteArray>(thisObj)->pop_back();
}
// pop_front()
void c_QList_T_QByteArray_T___pop_front(void *thisObj)
{
    fromPtr<QByteArray>(thisObj)->pop_front();
}
// prepend(const T & t)
void c_QList_T_QByteArray_T___prepend_QByteArray(void *thisObj, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    fromPtr<QByteArray>(thisObj)->prepend(t);
}
// push_back(const T & t)
void c_QList_T_QByteArray_T___push_back_QByteArray(void *thisObj, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    fromPtr<QByteArray>(thisObj)->push_back(t);
}
// push_front(const T & t)
void c_QList_T_QByteArray_T___push_front_QByteArray(void *thisObj, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    fromPtr<QByteArray>(thisObj)->push_front(t);
}
// removeAll(const T & t)
int c_QList_T_QByteArray_T___removeAll_QByteArray(void *thisObj, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    return fromPtr<QByteArray>(thisObj)->removeAll(t);
}
// removeAt(int i)
void c_QList_T_QByteArray_T___removeAt_int(void *thisObj, int i)
{
    fromPtr<QByteArray>(thisObj)->removeAt(i);
}
// removeFirst()
void c_QList_T_QByteArray_T___removeFirst(void *thisObj)
{
    fromPtr<QByteArray>(thisObj)->removeFirst();
}
// removeLast()
void c_QList_T_QByteArray_T___removeLast(void *thisObj)
{
    fromPtr<QByteArray>(thisObj)->removeLast();
}
// removeOne(const T & t)
bool c_QList_T_QByteArray_T___removeOne_QByteArray(void *thisObj, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    return fromPtr<QByteArray>(thisObj)->removeOne(t);
}
// replace(int i, const T & t)
void c_QList_T_QByteArray_T___replace_int_QByteArray(void *thisObj, int i, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    fromPtr<QByteArray>(thisObj)->replace(i, t);
}
// reserve(int size)
void c_QList_T_QByteArray_T___reserve_int(void *thisObj, int size)
{
    fromPtr<QByteArray>(thisObj)->reserve(size);
}
// setSharable(bool sharable)
void c_QList_T_QByteArray_T___setSharable_bool(void *thisObj, bool sharable)
{
    fromPtr<QByteArray>(thisObj)->setSharable(sharable);
}
// size() const
int c_QList_T_QByteArray_T___size(void *thisObj)
{
    return fromPtr<QByteArray>(thisObj)->size();
}
// startsWith(const T & t) const
bool c_QList_T_QByteArray_T___startsWith_QByteArray(void *thisObj, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QByteArray *>(t_);
    return fromPtr<QByteArray>(thisObj)->startsWith(t);
}
// swapItemsAt(int i, int j)
void c_QList_T_QByteArray_T___swapItemsAt_int_int(void *thisObj, int i, int j)
{
    fromPtr<QByteArray>(thisObj)->swapItemsAt(i, j);
}
// takeAt(int i)
void *c_QList_T_QByteArray_T___takeAt_int(void *thisObj, int i)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->takeAt(i) };
}
// takeFirst()
void *c_QList_T_QByteArray_T___takeFirst(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->takeFirst() };
}
// takeLast()
void *c_QList_T_QByteArray_T___takeLast(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->takeLast() };
}
// value(int i) const
void *c_QList_T_QByteArray_T___value_int(void *thisObj, int i)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->value(i) };
}
// value(int i, const T & defaultValue) const
void *c_QList_T_QByteArray_T___value_int_QByteArray(void *thisObj, int i, void *defaultValue_)
{
    assert(defaultValue_);
    auto &defaultValue = *reinterpret_cast<QByteArray *>(defaultValue_);
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->value(
        i, defaultValue) };
}
void c_QList_T_QByteArray_T___destructor(void *thisObj)
{
    delete fromPtr<QByteArray>(thisObj);
}
}
extern "C" {
void c_QList_T_Group_T__Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<
        KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Controllers::Group *> *>(
        cppObj);
}
void *c_QList_T_Group_T___constructor()
{
    auto ptr =
        new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Controllers::Group *>();
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & t)
void c_QList_T_Group_T___append_QList_T(void *thisObj, void *t_)
{
    assert(t_);
    auto &t = *reinterpret_cast<QList<KDDockWidgets::Controllers::Group *> *>(t_);
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->append(t);
}
// append(const T & t)
void c_QList_T_Group_T___append_Group(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->append(t);
}
// at(int i) const
const void *c_QList_T_Group_T___at_int(void *thisObj, int i)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->at(i);
}
// back()
void *c_QList_T_Group_T___back(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->back();
}
// clear()
void c_QList_T_Group_T___clear(void *thisObj)
{
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->clear();
}
// constFirst() const
const void *c_QList_T_Group_T___constFirst(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->constFirst();
}
// constLast() const
const void *c_QList_T_Group_T___constLast(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->constLast();
}
// contains(const T & t) const
bool c_QList_T_Group_T___contains_Group(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->contains(t);
}
// count() const
int c_QList_T_Group_T___count(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->count();
}
// count(const T & t) const
int c_QList_T_Group_T___count_Group(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->count(t);
}
// detach()
void c_QList_T_Group_T___detach(void *thisObj)
{
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->detach();
}
// detachShared()
void c_QList_T_Group_T___detachShared(void *thisObj)
{
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->detachShared();
}
// empty() const
bool c_QList_T_Group_T___empty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->empty();
}
// endsWith(const T & t) const
bool c_QList_T_Group_T___endsWith_Group(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->endsWith(t);
}
// first()
void *c_QList_T_Group_T___first(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->first();
}
// front()
void *c_QList_T_Group_T___front(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->front();
}
// indexOf(const T & t, int from) const
int c_QList_T_Group_T___indexOf_Group_int(void *thisObj, void *t_, int from)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->indexOf(t, from);
}
// insert(int i, const T & t)
void c_QList_T_Group_T___insert_int_Group(void *thisObj, int i, void *t_)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->insert(i, t);
}
// isDetached() const
bool c_QList_T_Group_T___isDetached(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->isDetached();
}
// isEmpty() const
bool c_QList_T_Group_T___isEmpty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->isEmpty();
}
// isSharedWith(const QList<T > & other) const
bool c_QList_T_Group_T___isSharedWith_QList_T(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QList<KDDockWidgets::Controllers::Group *> *>(other_);
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->isSharedWith(other);
}
// last()
void *c_QList_T_Group_T___last(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->last();
}
// lastIndexOf(const T & t, int from) const
int c_QList_T_Group_T___lastIndexOf_Group_int(void *thisObj, void *t_, int from)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->lastIndexOf(t, from);
}
// length() const
int c_QList_T_Group_T___length(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->length();
}
// mid(int pos, int length) const
void *c_QList_T_Group_T___mid_int_int(void *thisObj, int pos, int length)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Controllers::Group *>> {
        fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->mid(pos, length)
    };
}
// move(int from, int to)
void c_QList_T_Group_T___move_int_int(void *thisObj, int from, int to)
{
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->move(from, to);
}
// pop_back()
void c_QList_T_Group_T___pop_back(void *thisObj)
{
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->pop_back();
}
// pop_front()
void c_QList_T_Group_T___pop_front(void *thisObj)
{
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->pop_front();
}
// prepend(const T & t)
void c_QList_T_Group_T___prepend_Group(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->prepend(t);
}
// push_back(const T & t)
void c_QList_T_Group_T___push_back_Group(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->push_back(t);
}
// push_front(const T & t)
void c_QList_T_Group_T___push_front_Group(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->push_front(t);
}
// removeAll(const T & t)
int c_QList_T_Group_T___removeAll_Group(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->removeAll(t);
}
// removeAt(int i)
void c_QList_T_Group_T___removeAt_int(void *thisObj, int i)
{
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->removeAt(i);
}
// removeFirst()
void c_QList_T_Group_T___removeFirst(void *thisObj)
{
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->removeFirst();
}
// removeLast()
void c_QList_T_Group_T___removeLast(void *thisObj)
{
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->removeLast();
}
// removeOne(const T & t)
bool c_QList_T_Group_T___removeOne_Group(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->removeOne(t);
}
// replace(int i, const T & t)
void c_QList_T_Group_T___replace_int_Group(void *thisObj, int i, void *t_)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->replace(i, t);
}
// reserve(int size)
void c_QList_T_Group_T___reserve_int(void *thisObj, int size)
{
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->reserve(size);
}
// setSharable(bool sharable)
void c_QList_T_Group_T___setSharable_bool(void *thisObj, bool sharable)
{
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->setSharable(sharable);
}
// size() const
int c_QList_T_Group_T___size(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->size();
}
// startsWith(const T & t) const
bool c_QList_T_Group_T___startsWith_Group(void *thisObj, void *t_)
{
    auto t = reinterpret_cast<KDDockWidgets::Controllers::Group *>(t_);
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->startsWith(t);
}
// swapItemsAt(int i, int j)
void c_QList_T_Group_T___swapItemsAt_int_int(void *thisObj, int i, int j)
{
    fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->swapItemsAt(i, j);
}
// takeAt(int i)
void *c_QList_T_Group_T___takeAt_int(void *thisObj, int i)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->takeAt(i);
}
// takeFirst()
void *c_QList_T_Group_T___takeFirst(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->takeFirst();
}
// takeLast()
void *c_QList_T_Group_T___takeLast(void *thisObj)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->takeLast();
}
// value(int i) const
void *c_QList_T_Group_T___value_int(void *thisObj, int i)
{
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->value(i);
}
// value(int i, const T & defaultValue) const
void *c_QList_T_Group_T___value_int_Group(void *thisObj, int i, void *defaultValue_)
{
    auto defaultValue = reinterpret_cast<KDDockWidgets::Controllers::Group *>(defaultValue_);
    return fromPtr<KDDockWidgets::Controllers::Group *>(thisObj)->value(i, defaultValue);
}
void c_QList_T_Group_T___destructor(void *thisObj)
{
    delete fromPtr<KDDockWidgets::Controllers::Group *>(thisObj);
}
}
