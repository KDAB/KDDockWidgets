/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "QList_c.h"


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
QList_wrapper<T>::QList_wrapper(qsizetype size)
    : ::QList<T>(size)
{
}
template<typename T>
void QList_wrapper<T>::append(const QList<T> &l)
{
    ::QList<T>::append(l);
}
template<typename T>
const T &QList_wrapper<T>::at(qsizetype i) const
{
    return ::QList<T>::at(i);
}
template<typename T>
T &QList_wrapper<T>::back()
{
    return ::QList<T>::back();
}
template<typename T>
qsizetype QList_wrapper<T>::capacity() const
{
    return ::QList<T>::capacity();
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
qsizetype QList_wrapper<T>::count() const
{
    return ::QList<T>::count();
}
template<typename T>
void QList_wrapper<T>::detach()
{
    ::QList<T>::detach();
}
template<typename T>
bool QList_wrapper<T>::empty() const
{
    return ::QList<T>::empty();
}
template<typename T>
T &QList_wrapper<T>::first()
{
    return ::QList<T>::first();
}
template<typename T>
QList<T> QList_wrapper<T>::first(qsizetype n) const
{
    return ::QList<T>::first(n);
}
template<typename T>
T &QList_wrapper<T>::front()
{
    return ::QList<T>::front();
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
QList<T> QList_wrapper<T>::last(qsizetype n) const
{
    return ::QList<T>::last(n);
}
template<typename T>
qsizetype QList_wrapper<T>::length() const
{
    return ::QList<T>::length();
}
template<typename T>
QList<T> QList_wrapper<T>::mid(qsizetype pos, qsizetype len) const
{
    return ::QList<T>::mid(pos, len);
}
template<typename T>
void QList_wrapper<T>::move(qsizetype from, qsizetype to)
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
void QList_wrapper<T>::remove(qsizetype i, qsizetype n)
{
    ::QList<T>::remove(i, n);
}
template<typename T>
void QList_wrapper<T>::removeAt(qsizetype i)
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
void QList_wrapper<T>::reserve(qsizetype size)
{
    ::QList<T>::reserve(size);
}
template<typename T>
void QList_wrapper<T>::resize(qsizetype size)
{
    ::QList<T>::resize(size);
}
template<typename T>
void QList_wrapper<T>::shrink_to_fit()
{
    ::QList<T>::shrink_to_fit();
}
template<typename T>
qsizetype QList_wrapper<T>::size() const
{
    return ::QList<T>::size();
}
template<typename T>
QList<T> QList_wrapper<T>::sliced(qsizetype pos) const
{
    return ::QList<T>::sliced(pos);
}
template<typename T>
QList<T> QList_wrapper<T>::sliced(qsizetype pos, qsizetype n) const
{
    return ::QList<T>::sliced(pos, n);
}
template<typename T>
void QList_wrapper<T>::squeeze()
{
    ::QList<T>::squeeze();
}
template<typename T>
void QList_wrapper<T>::swapItemsAt(qsizetype i, qsizetype j)
{
    ::QList<T>::swapItemsAt(i, j);
}
template<typename T>
T QList_wrapper<T>::takeAt(qsizetype i)
{
    return ::QList<T>::takeAt(i);
}
template<typename T>
QList<T> QList_wrapper<T>::toList() const
{
    return ::QList<T>::toList();
}
template<typename T>
QList<T> QList_wrapper<T>::toVector() const
{
    return ::QList<T>::toVector();
}
template<typename T>
T QList_wrapper<T>::value(qsizetype i) const
{
    return ::QList<T>::value(i);
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
void c_QList_T_QString_T__Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<QString> *>(cppObj);
}
void *c_QList_T_QString_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<QString>();
    return reinterpret_cast<void *>(ptr);
}
void *c_QList_T_QString_T___constructor_qsizetype(qsizetype size)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<QString>(size);
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & l)
void c_QList_T_QString_T___append_QList_T(void *thisObj, void *l_)
{
    assert(l_);
    auto &l = *reinterpret_cast<QList<QString> *>(l_);
    fromPtr<QString>(thisObj)->append(l);
}
// at(qsizetype i) const
const void *c_QList_T_QString_T___at_qsizetype(void *thisObj, qsizetype i)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr<QString>(thisObj)->at(i) };
}
// back()
void *c_QList_T_QString_T___back(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr<QString>(thisObj)->back() };
}
// capacity() const
qsizetype c_QList_T_QString_T___capacity(void *thisObj)
{
    return fromPtr<QString>(thisObj)->capacity();
}
// clear()
void c_QList_T_QString_T___clear(void *thisObj)
{
    fromPtr<QString>(thisObj)->clear();
}
// constFirst() const
const void *c_QList_T_QString_T___constFirst(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr<QString>(thisObj)->constFirst() };
}
// constLast() const
const void *c_QList_T_QString_T___constLast(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr<QString>(thisObj)->constLast() };
}
// count() const
qsizetype c_QList_T_QString_T___count(void *thisObj)
{
    return fromPtr<QString>(thisObj)->count();
}
// detach()
void c_QList_T_QString_T___detach(void *thisObj)
{
    fromPtr<QString>(thisObj)->detach();
}
// empty() const
bool c_QList_T_QString_T___empty(void *thisObj)
{
    return fromPtr<QString>(thisObj)->empty();
}
// first()
void *c_QList_T_QString_T___first(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr<QString>(thisObj)->first() };
}
// first(qsizetype n) const
void *c_QList_T_QString_T___first_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<QString>> { fromPtr<QString>(thisObj)->first(n) };
}
// front()
void *c_QList_T_QString_T___front(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr<QString>(thisObj)->front() };
}
// isDetached() const
bool c_QList_T_QString_T___isDetached(void *thisObj)
{
    return fromPtr<QString>(thisObj)->isDetached();
}
// isEmpty() const
bool c_QList_T_QString_T___isEmpty(void *thisObj)
{
    return fromPtr<QString>(thisObj)->isEmpty();
}
// isSharedWith(const QList<T > & other) const
bool c_QList_T_QString_T___isSharedWith_QList_T(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QList<QString> *>(other_);
    return fromPtr<QString>(thisObj)->isSharedWith(other);
}
// last()
void *c_QList_T_QString_T___last(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr<QString>(thisObj)->last() };
}
// last(qsizetype n) const
void *c_QList_T_QString_T___last_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<QString>> { fromPtr<QString>(thisObj)->last(n) };
}
// length() const
qsizetype c_QList_T_QString_T___length(void *thisObj)
{
    return fromPtr<QString>(thisObj)->length();
}
// mid(qsizetype pos, qsizetype len) const
void *c_QList_T_QString_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QList<QString>> { fromPtr<QString>(thisObj)->mid(pos, len) };
}
// move(qsizetype from, qsizetype to)
void c_QList_T_QString_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to)
{
    fromPtr<QString>(thisObj)->move(from, to);
}
// pop_back()
void c_QList_T_QString_T___pop_back(void *thisObj)
{
    fromPtr<QString>(thisObj)->pop_back();
}
// pop_front()
void c_QList_T_QString_T___pop_front(void *thisObj)
{
    fromPtr<QString>(thisObj)->pop_front();
}
// remove(qsizetype i, qsizetype n)
void c_QList_T_QString_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n)
{
    fromPtr<QString>(thisObj)->remove(i, n);
}
// removeAt(qsizetype i)
void c_QList_T_QString_T___removeAt_qsizetype(void *thisObj, qsizetype i)
{
    fromPtr<QString>(thisObj)->removeAt(i);
}
// removeFirst()
void c_QList_T_QString_T___removeFirst(void *thisObj)
{
    fromPtr<QString>(thisObj)->removeFirst();
}
// removeLast()
void c_QList_T_QString_T___removeLast(void *thisObj)
{
    fromPtr<QString>(thisObj)->removeLast();
}
// reserve(qsizetype size)
void c_QList_T_QString_T___reserve_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<QString>(thisObj)->reserve(size);
}
// resize(qsizetype size)
void c_QList_T_QString_T___resize_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<QString>(thisObj)->resize(size);
}
// shrink_to_fit()
void c_QList_T_QString_T___shrink_to_fit(void *thisObj)
{
    fromPtr<QString>(thisObj)->shrink_to_fit();
}
// size() const
qsizetype c_QList_T_QString_T___size(void *thisObj)
{
    return fromPtr<QString>(thisObj)->size();
}
// sliced(qsizetype pos) const
void *c_QList_T_QString_T___sliced_qsizetype(void *thisObj, qsizetype pos)
{
    return new Dartagnan::ValueWrapper<QList<QString>> { fromPtr<QString>(thisObj)->sliced(pos) };
}
// sliced(qsizetype pos, qsizetype n) const
void *c_QList_T_QString_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<QString>> { fromPtr<QString>(thisObj)->sliced(pos, n) };
}
// squeeze()
void c_QList_T_QString_T___squeeze(void *thisObj)
{
    fromPtr<QString>(thisObj)->squeeze();
}
// swapItemsAt(qsizetype i, qsizetype j)
void c_QList_T_QString_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j)
{
    fromPtr<QString>(thisObj)->swapItemsAt(i, j);
}
// takeAt(qsizetype i)
void *c_QList_T_QString_T___takeAt_qsizetype(void *thisObj, qsizetype i)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr<QString>(thisObj)->takeAt(i) };
}
// toList() const
void *c_QList_T_QString_T___toList(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<QString>> { fromPtr<QString>(thisObj)->toList() };
}
// toVector() const
void *c_QList_T_QString_T___toVector(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<QString>> { fromPtr<QString>(thisObj)->toVector() };
}
// value(qsizetype i) const
void *c_QList_T_QString_T___value_qsizetype(void *thisObj, qsizetype i)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr<QString>(thisObj)->value(i) };
}
void c_QList_T_QString_T___destructor(void *thisObj)
{
    delete fromPtr<QString>(thisObj);
}
}
extern "C" {
void c_QList_T_unsigned_int_T__Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<unsigned int> *>(cppObj);
}
void *c_QList_T_unsigned_int_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<unsigned int>();
    return reinterpret_cast<void *>(ptr);
}
void *c_QList_T_unsigned_int_T___constructor_qsizetype(qsizetype size)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<unsigned int>(size);
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & l)
void c_QList_T_unsigned_int_T___append_QList_T(void *thisObj, void *l_)
{
    assert(l_);
    auto &l = *reinterpret_cast<QList<unsigned int> *>(l_);
    fromPtr<unsigned int>(thisObj)->append(l);
}
// at(qsizetype i) const
const unsigned int c_QList_T_unsigned_int_T___at_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<unsigned int>(thisObj)->at(i);
}
// back()
unsigned int c_QList_T_unsigned_int_T___back(void *thisObj)
{
    return fromPtr<unsigned int>(thisObj)->back();
}
// capacity() const
qsizetype c_QList_T_unsigned_int_T___capacity(void *thisObj)
{
    return fromPtr<unsigned int>(thisObj)->capacity();
}
// clear()
void c_QList_T_unsigned_int_T___clear(void *thisObj)
{
    fromPtr<unsigned int>(thisObj)->clear();
}
// constFirst() const
const unsigned int c_QList_T_unsigned_int_T___constFirst(void *thisObj)
{
    return fromPtr<unsigned int>(thisObj)->constFirst();
}
// constLast() const
const unsigned int c_QList_T_unsigned_int_T___constLast(void *thisObj)
{
    return fromPtr<unsigned int>(thisObj)->constLast();
}
// count() const
qsizetype c_QList_T_unsigned_int_T___count(void *thisObj)
{
    return fromPtr<unsigned int>(thisObj)->count();
}
// detach()
void c_QList_T_unsigned_int_T___detach(void *thisObj)
{
    fromPtr<unsigned int>(thisObj)->detach();
}
// empty() const
bool c_QList_T_unsigned_int_T___empty(void *thisObj)
{
    return fromPtr<unsigned int>(thisObj)->empty();
}
// first()
unsigned int c_QList_T_unsigned_int_T___first(void *thisObj)
{
    return fromPtr<unsigned int>(thisObj)->first();
}
// first(qsizetype n) const
void *c_QList_T_unsigned_int_T___first_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<unsigned int>> { fromPtr<unsigned int>(thisObj)->first(n) };
}
// front()
unsigned int c_QList_T_unsigned_int_T___front(void *thisObj)
{
    return fromPtr<unsigned int>(thisObj)->front();
}
// isDetached() const
bool c_QList_T_unsigned_int_T___isDetached(void *thisObj)
{
    return fromPtr<unsigned int>(thisObj)->isDetached();
}
// isEmpty() const
bool c_QList_T_unsigned_int_T___isEmpty(void *thisObj)
{
    return fromPtr<unsigned int>(thisObj)->isEmpty();
}
// isSharedWith(const QList<T > & other) const
bool c_QList_T_unsigned_int_T___isSharedWith_QList_T(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QList<unsigned int> *>(other_);
    return fromPtr<unsigned int>(thisObj)->isSharedWith(other);
}
// last()
unsigned int c_QList_T_unsigned_int_T___last(void *thisObj)
{
    return fromPtr<unsigned int>(thisObj)->last();
}
// last(qsizetype n) const
void *c_QList_T_unsigned_int_T___last_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<unsigned int>> { fromPtr<unsigned int>(thisObj)->last(n) };
}
// length() const
qsizetype c_QList_T_unsigned_int_T___length(void *thisObj)
{
    return fromPtr<unsigned int>(thisObj)->length();
}
// mid(qsizetype pos, qsizetype len) const
void *c_QList_T_unsigned_int_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QList<unsigned int>> { fromPtr<unsigned int>(thisObj)->mid(pos, len) };
}
// move(qsizetype from, qsizetype to)
void c_QList_T_unsigned_int_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to)
{
    fromPtr<unsigned int>(thisObj)->move(from, to);
}
// pop_back()
void c_QList_T_unsigned_int_T___pop_back(void *thisObj)
{
    fromPtr<unsigned int>(thisObj)->pop_back();
}
// pop_front()
void c_QList_T_unsigned_int_T___pop_front(void *thisObj)
{
    fromPtr<unsigned int>(thisObj)->pop_front();
}
// remove(qsizetype i, qsizetype n)
void c_QList_T_unsigned_int_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n)
{
    fromPtr<unsigned int>(thisObj)->remove(i, n);
}
// removeAt(qsizetype i)
void c_QList_T_unsigned_int_T___removeAt_qsizetype(void *thisObj, qsizetype i)
{
    fromPtr<unsigned int>(thisObj)->removeAt(i);
}
// removeFirst()
void c_QList_T_unsigned_int_T___removeFirst(void *thisObj)
{
    fromPtr<unsigned int>(thisObj)->removeFirst();
}
// removeLast()
void c_QList_T_unsigned_int_T___removeLast(void *thisObj)
{
    fromPtr<unsigned int>(thisObj)->removeLast();
}
// reserve(qsizetype size)
void c_QList_T_unsigned_int_T___reserve_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<unsigned int>(thisObj)->reserve(size);
}
// resize(qsizetype size)
void c_QList_T_unsigned_int_T___resize_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<unsigned int>(thisObj)->resize(size);
}
// shrink_to_fit()
void c_QList_T_unsigned_int_T___shrink_to_fit(void *thisObj)
{
    fromPtr<unsigned int>(thisObj)->shrink_to_fit();
}
// size() const
qsizetype c_QList_T_unsigned_int_T___size(void *thisObj)
{
    return fromPtr<unsigned int>(thisObj)->size();
}
// sliced(qsizetype pos) const
void *c_QList_T_unsigned_int_T___sliced_qsizetype(void *thisObj, qsizetype pos)
{
    return new Dartagnan::ValueWrapper<QList<unsigned int>> { fromPtr<unsigned int>(thisObj)->sliced(pos) };
}
// sliced(qsizetype pos, qsizetype n) const
void *c_QList_T_unsigned_int_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<unsigned int>> { fromPtr<unsigned int>(thisObj)->sliced(pos, n) };
}
// squeeze()
void c_QList_T_unsigned_int_T___squeeze(void *thisObj)
{
    fromPtr<unsigned int>(thisObj)->squeeze();
}
// swapItemsAt(qsizetype i, qsizetype j)
void c_QList_T_unsigned_int_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j)
{
    fromPtr<unsigned int>(thisObj)->swapItemsAt(i, j);
}
// takeAt(qsizetype i)
unsigned int c_QList_T_unsigned_int_T___takeAt_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<unsigned int>(thisObj)->takeAt(i);
}
// toList() const
void *c_QList_T_unsigned_int_T___toList(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<unsigned int>> { fromPtr<unsigned int>(thisObj)->toList() };
}
// toVector() const
void *c_QList_T_unsigned_int_T___toVector(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<unsigned int>> { fromPtr<unsigned int>(thisObj)->toVector() };
}
// value(qsizetype i) const
unsigned int c_QList_T_unsigned_int_T___value_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<unsigned int>(thisObj)->value(i);
}
void c_QList_T_unsigned_int_T___destructor(void *thisObj)
{
    delete fromPtr<unsigned int>(thisObj);
}
}
extern "C" {
void c_QList_T_QObject_T__Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<QObject *> *>(cppObj);
}
void *c_QList_T_QObject_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<QObject *>();
    return reinterpret_cast<void *>(ptr);
}
void *c_QList_T_QObject_T___constructor_qsizetype(qsizetype size)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<QObject *>(size);
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & l)
void c_QList_T_QObject_T___append_QList_T(void *thisObj, void *l_)
{
    assert(l_);
    auto &l = *reinterpret_cast<QList<QObject *> *>(l_);
    fromPtr<QObject *>(thisObj)->append(l);
}
// at(qsizetype i) const
const void *c_QList_T_QObject_T___at_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<QObject *>(thisObj)->at(i);
}
// back()
void *c_QList_T_QObject_T___back(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->back();
}
// capacity() const
qsizetype c_QList_T_QObject_T___capacity(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->capacity();
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
// count() const
qsizetype c_QList_T_QObject_T___count(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->count();
}
// detach()
void c_QList_T_QObject_T___detach(void *thisObj)
{
    fromPtr<QObject *>(thisObj)->detach();
}
// empty() const
bool c_QList_T_QObject_T___empty(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->empty();
}
// first()
void *c_QList_T_QObject_T___first(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->first();
}
// first(qsizetype n) const
void *c_QList_T_QObject_T___first_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<QObject *>> { fromPtr<QObject *>(thisObj)->first(n) };
}
// front()
void *c_QList_T_QObject_T___front(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->front();
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
// last(qsizetype n) const
void *c_QList_T_QObject_T___last_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<QObject *>> { fromPtr<QObject *>(thisObj)->last(n) };
}
// length() const
qsizetype c_QList_T_QObject_T___length(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->length();
}
// mid(qsizetype pos, qsizetype len) const
void *c_QList_T_QObject_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QList<QObject *>> { fromPtr<QObject *>(thisObj)->mid(pos, len) };
}
// move(qsizetype from, qsizetype to)
void c_QList_T_QObject_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to)
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
// remove(qsizetype i, qsizetype n)
void c_QList_T_QObject_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n)
{
    fromPtr<QObject *>(thisObj)->remove(i, n);
}
// removeAt(qsizetype i)
void c_QList_T_QObject_T___removeAt_qsizetype(void *thisObj, qsizetype i)
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
// reserve(qsizetype size)
void c_QList_T_QObject_T___reserve_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<QObject *>(thisObj)->reserve(size);
}
// resize(qsizetype size)
void c_QList_T_QObject_T___resize_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<QObject *>(thisObj)->resize(size);
}
// shrink_to_fit()
void c_QList_T_QObject_T___shrink_to_fit(void *thisObj)
{
    fromPtr<QObject *>(thisObj)->shrink_to_fit();
}
// size() const
qsizetype c_QList_T_QObject_T___size(void *thisObj)
{
    return fromPtr<QObject *>(thisObj)->size();
}
// sliced(qsizetype pos) const
void *c_QList_T_QObject_T___sliced_qsizetype(void *thisObj, qsizetype pos)
{
    return new Dartagnan::ValueWrapper<QList<QObject *>> { fromPtr<QObject *>(thisObj)->sliced(pos) };
}
// sliced(qsizetype pos, qsizetype n) const
void *c_QList_T_QObject_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<QObject *>> { fromPtr<QObject *>(thisObj)->sliced(pos, n) };
}
// squeeze()
void c_QList_T_QObject_T___squeeze(void *thisObj)
{
    fromPtr<QObject *>(thisObj)->squeeze();
}
// swapItemsAt(qsizetype i, qsizetype j)
void c_QList_T_QObject_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j)
{
    fromPtr<QObject *>(thisObj)->swapItemsAt(i, j);
}
// takeAt(qsizetype i)
void *c_QList_T_QObject_T___takeAt_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<QObject *>(thisObj)->takeAt(i);
}
// toList() const
void *c_QList_T_QObject_T___toList(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<QObject *>> { fromPtr<QObject *>(thisObj)->toList() };
}
// toVector() const
void *c_QList_T_QObject_T___toVector(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<QObject *>> { fromPtr<QObject *>(thisObj)->toVector() };
}
// value(qsizetype i) const
void *c_QList_T_QObject_T___value_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<QObject *>(thisObj)->value(i);
}
void c_QList_T_QObject_T___destructor(void *thisObj)
{
    delete fromPtr<QObject *>(thisObj);
}
}
extern "C" {
void c_QList_T_QByteArray_T__Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<QByteArray> *>(cppObj);
}
void *c_QList_T_QByteArray_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<QByteArray>();
    return reinterpret_cast<void *>(ptr);
}
void *c_QList_T_QByteArray_T___constructor_qsizetype(qsizetype size)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<QByteArray>(size);
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & l)
void c_QList_T_QByteArray_T___append_QList_T(void *thisObj, void *l_)
{
    assert(l_);
    auto &l = *reinterpret_cast<QList<QByteArray> *>(l_);
    fromPtr<QByteArray>(thisObj)->append(l);
}
// at(qsizetype i) const
const void *c_QList_T_QByteArray_T___at_qsizetype(void *thisObj, qsizetype i)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->at(i) };
}
// back()
void *c_QList_T_QByteArray_T___back(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->back() };
}
// capacity() const
qsizetype c_QList_T_QByteArray_T___capacity(void *thisObj)
{
    return fromPtr<QByteArray>(thisObj)->capacity();
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
// count() const
qsizetype c_QList_T_QByteArray_T___count(void *thisObj)
{
    return fromPtr<QByteArray>(thisObj)->count();
}
// detach()
void c_QList_T_QByteArray_T___detach(void *thisObj)
{
    fromPtr<QByteArray>(thisObj)->detach();
}
// empty() const
bool c_QList_T_QByteArray_T___empty(void *thisObj)
{
    return fromPtr<QByteArray>(thisObj)->empty();
}
// first()
void *c_QList_T_QByteArray_T___first(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->first() };
}
// first(qsizetype n) const
void *c_QList_T_QByteArray_T___first_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<QByteArray>> { fromPtr<QByteArray>(thisObj)->first(n) };
}
// front()
void *c_QList_T_QByteArray_T___front(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->front() };
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
// last(qsizetype n) const
void *c_QList_T_QByteArray_T___last_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<QByteArray>> { fromPtr<QByteArray>(thisObj)->last(n) };
}
// length() const
qsizetype c_QList_T_QByteArray_T___length(void *thisObj)
{
    return fromPtr<QByteArray>(thisObj)->length();
}
// mid(qsizetype pos, qsizetype len) const
void *c_QList_T_QByteArray_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QList<QByteArray>> { fromPtr<QByteArray>(thisObj)->mid(pos, len) };
}
// move(qsizetype from, qsizetype to)
void c_QList_T_QByteArray_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to)
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
// remove(qsizetype i, qsizetype n)
void c_QList_T_QByteArray_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n)
{
    fromPtr<QByteArray>(thisObj)->remove(i, n);
}
// removeAt(qsizetype i)
void c_QList_T_QByteArray_T___removeAt_qsizetype(void *thisObj, qsizetype i)
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
// reserve(qsizetype size)
void c_QList_T_QByteArray_T___reserve_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<QByteArray>(thisObj)->reserve(size);
}
// resize(qsizetype size)
void c_QList_T_QByteArray_T___resize_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<QByteArray>(thisObj)->resize(size);
}
// shrink_to_fit()
void c_QList_T_QByteArray_T___shrink_to_fit(void *thisObj)
{
    fromPtr<QByteArray>(thisObj)->shrink_to_fit();
}
// size() const
qsizetype c_QList_T_QByteArray_T___size(void *thisObj)
{
    return fromPtr<QByteArray>(thisObj)->size();
}
// sliced(qsizetype pos) const
void *c_QList_T_QByteArray_T___sliced_qsizetype(void *thisObj, qsizetype pos)
{
    return new Dartagnan::ValueWrapper<QList<QByteArray>> { fromPtr<QByteArray>(thisObj)->sliced(pos) };
}
// sliced(qsizetype pos, qsizetype n) const
void *c_QList_T_QByteArray_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<QByteArray>> { fromPtr<QByteArray>(thisObj)->sliced(pos, n) };
}
// squeeze()
void c_QList_T_QByteArray_T___squeeze(void *thisObj)
{
    fromPtr<QByteArray>(thisObj)->squeeze();
}
// swapItemsAt(qsizetype i, qsizetype j)
void c_QList_T_QByteArray_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j)
{
    fromPtr<QByteArray>(thisObj)->swapItemsAt(i, j);
}
// takeAt(qsizetype i)
void *c_QList_T_QByteArray_T___takeAt_qsizetype(void *thisObj, qsizetype i)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->takeAt(i) };
}
// toList() const
void *c_QList_T_QByteArray_T___toList(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<QByteArray>> { fromPtr<QByteArray>(thisObj)->toList() };
}
// toVector() const
void *c_QList_T_QByteArray_T___toVector(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<QByteArray>> { fromPtr<QByteArray>(thisObj)->toVector() };
}
// value(qsizetype i) const
void *c_QList_T_QByteArray_T___value_qsizetype(void *thisObj, qsizetype i)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr<QByteArray>(thisObj)->value(i) };
}
void c_QList_T_QByteArray_T___destructor(void *thisObj)
{
    delete fromPtr<QByteArray>(thisObj);
}
}
extern "C" {
void c_QList_T_DockWidget_T__Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::DockWidget *> *>(cppObj);
}
void *c_QList_T_DockWidget_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::DockWidget *>();
    return reinterpret_cast<void *>(ptr);
}
void *c_QList_T_DockWidget_T___constructor_qsizetype(qsizetype size)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::DockWidget *>(size);
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & l)
void c_QList_T_DockWidget_T___append_QList_T(void *thisObj, void *l_)
{
    assert(l_);
    auto &l = *reinterpret_cast<QList<KDDockWidgets::Core::DockWidget *> *>(l_);
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->append(l);
}
// at(qsizetype i) const
const void *c_QList_T_DockWidget_T___at_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->at(i);
}
// back()
void *c_QList_T_DockWidget_T___back(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->back();
}
// capacity() const
qsizetype c_QList_T_DockWidget_T___capacity(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->capacity();
}
// clear()
void c_QList_T_DockWidget_T___clear(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->clear();
}
// constFirst() const
const void *c_QList_T_DockWidget_T___constFirst(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->constFirst();
}
// constLast() const
const void *c_QList_T_DockWidget_T___constLast(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->constLast();
}
// count() const
qsizetype c_QList_T_DockWidget_T___count(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->count();
}
// detach()
void c_QList_T_DockWidget_T___detach(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->detach();
}
// empty() const
bool c_QList_T_DockWidget_T___empty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->empty();
}
// first()
void *c_QList_T_DockWidget_T___first(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->first();
}
// first(qsizetype n) const
void *c_QList_T_DockWidget_T___first_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::DockWidget *>> { fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->first(n) };
}
// front()
void *c_QList_T_DockWidget_T___front(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->front();
}
// isDetached() const
bool c_QList_T_DockWidget_T___isDetached(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->isDetached();
}
// isEmpty() const
bool c_QList_T_DockWidget_T___isEmpty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->isEmpty();
}
// isSharedWith(const QList<T > & other) const
bool c_QList_T_DockWidget_T___isSharedWith_QList_T(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QList<KDDockWidgets::Core::DockWidget *> *>(other_);
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->isSharedWith(other);
}
// last()
void *c_QList_T_DockWidget_T___last(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->last();
}
// last(qsizetype n) const
void *c_QList_T_DockWidget_T___last_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::DockWidget *>> { fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->last(n) };
}
// length() const
qsizetype c_QList_T_DockWidget_T___length(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->length();
}
// mid(qsizetype pos, qsizetype len) const
void *c_QList_T_DockWidget_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::DockWidget *>> { fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->mid(pos, len) };
}
// move(qsizetype from, qsizetype to)
void c_QList_T_DockWidget_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->move(from, to);
}
// pop_back()
void c_QList_T_DockWidget_T___pop_back(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->pop_back();
}
// pop_front()
void c_QList_T_DockWidget_T___pop_front(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->pop_front();
}
// remove(qsizetype i, qsizetype n)
void c_QList_T_DockWidget_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->remove(i, n);
}
// removeAt(qsizetype i)
void c_QList_T_DockWidget_T___removeAt_qsizetype(void *thisObj, qsizetype i)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->removeAt(i);
}
// removeFirst()
void c_QList_T_DockWidget_T___removeFirst(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->removeFirst();
}
// removeLast()
void c_QList_T_DockWidget_T___removeLast(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->removeLast();
}
// reserve(qsizetype size)
void c_QList_T_DockWidget_T___reserve_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->reserve(size);
}
// resize(qsizetype size)
void c_QList_T_DockWidget_T___resize_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->resize(size);
}
// shrink_to_fit()
void c_QList_T_DockWidget_T___shrink_to_fit(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->shrink_to_fit();
}
// size() const
qsizetype c_QList_T_DockWidget_T___size(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->size();
}
// sliced(qsizetype pos) const
void *c_QList_T_DockWidget_T___sliced_qsizetype(void *thisObj, qsizetype pos)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::DockWidget *>> { fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->sliced(pos) };
}
// sliced(qsizetype pos, qsizetype n) const
void *c_QList_T_DockWidget_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::DockWidget *>> { fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->sliced(pos, n) };
}
// squeeze()
void c_QList_T_DockWidget_T___squeeze(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->squeeze();
}
// swapItemsAt(qsizetype i, qsizetype j)
void c_QList_T_DockWidget_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j)
{
    fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->swapItemsAt(i, j);
}
// takeAt(qsizetype i)
void *c_QList_T_DockWidget_T___takeAt_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->takeAt(i);
}
// toList() const
void *c_QList_T_DockWidget_T___toList(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::DockWidget *>> { fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->toList() };
}
// toVector() const
void *c_QList_T_DockWidget_T___toVector(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::DockWidget *>> { fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->toVector() };
}
// value(qsizetype i) const
void *c_QList_T_DockWidget_T___value_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj)->value(i);
}
void c_QList_T_DockWidget_T___destructor(void *thisObj)
{
    delete fromPtr<KDDockWidgets::Core::DockWidget *>(thisObj);
}
}
extern "C" {
void c_QList_T_FloatingWindow_T__Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::FloatingWindow *> *>(cppObj);
}
void *c_QList_T_FloatingWindow_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::FloatingWindow *>();
    return reinterpret_cast<void *>(ptr);
}
void *c_QList_T_FloatingWindow_T___constructor_qsizetype(qsizetype size)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::FloatingWindow *>(size);
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & l)
void c_QList_T_FloatingWindow_T___append_QList_T(void *thisObj, void *l_)
{
    assert(l_);
    auto &l = *reinterpret_cast<QList<KDDockWidgets::Core::FloatingWindow *> *>(l_);
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->append(l);
}
// at(qsizetype i) const
const void *c_QList_T_FloatingWindow_T___at_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->at(i);
}
// back()
void *c_QList_T_FloatingWindow_T___back(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->back();
}
// capacity() const
qsizetype c_QList_T_FloatingWindow_T___capacity(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->capacity();
}
// clear()
void c_QList_T_FloatingWindow_T___clear(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->clear();
}
// constFirst() const
const void *c_QList_T_FloatingWindow_T___constFirst(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->constFirst();
}
// constLast() const
const void *c_QList_T_FloatingWindow_T___constLast(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->constLast();
}
// count() const
qsizetype c_QList_T_FloatingWindow_T___count(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->count();
}
// detach()
void c_QList_T_FloatingWindow_T___detach(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->detach();
}
// empty() const
bool c_QList_T_FloatingWindow_T___empty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->empty();
}
// first()
void *c_QList_T_FloatingWindow_T___first(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->first();
}
// first(qsizetype n) const
void *c_QList_T_FloatingWindow_T___first_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::FloatingWindow *>> { fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->first(n) };
}
// front()
void *c_QList_T_FloatingWindow_T___front(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->front();
}
// isDetached() const
bool c_QList_T_FloatingWindow_T___isDetached(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->isDetached();
}
// isEmpty() const
bool c_QList_T_FloatingWindow_T___isEmpty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->isEmpty();
}
// isSharedWith(const QList<T > & other) const
bool c_QList_T_FloatingWindow_T___isSharedWith_QList_T(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QList<KDDockWidgets::Core::FloatingWindow *> *>(other_);
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->isSharedWith(other);
}
// last()
void *c_QList_T_FloatingWindow_T___last(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->last();
}
// last(qsizetype n) const
void *c_QList_T_FloatingWindow_T___last_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::FloatingWindow *>> { fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->last(n) };
}
// length() const
qsizetype c_QList_T_FloatingWindow_T___length(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->length();
}
// mid(qsizetype pos, qsizetype len) const
void *c_QList_T_FloatingWindow_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::FloatingWindow *>> { fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->mid(pos, len) };
}
// move(qsizetype from, qsizetype to)
void c_QList_T_FloatingWindow_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->move(from, to);
}
// pop_back()
void c_QList_T_FloatingWindow_T___pop_back(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->pop_back();
}
// pop_front()
void c_QList_T_FloatingWindow_T___pop_front(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->pop_front();
}
// remove(qsizetype i, qsizetype n)
void c_QList_T_FloatingWindow_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->remove(i, n);
}
// removeAt(qsizetype i)
void c_QList_T_FloatingWindow_T___removeAt_qsizetype(void *thisObj, qsizetype i)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->removeAt(i);
}
// removeFirst()
void c_QList_T_FloatingWindow_T___removeFirst(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->removeFirst();
}
// removeLast()
void c_QList_T_FloatingWindow_T___removeLast(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->removeLast();
}
// reserve(qsizetype size)
void c_QList_T_FloatingWindow_T___reserve_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->reserve(size);
}
// resize(qsizetype size)
void c_QList_T_FloatingWindow_T___resize_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->resize(size);
}
// shrink_to_fit()
void c_QList_T_FloatingWindow_T___shrink_to_fit(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->shrink_to_fit();
}
// size() const
qsizetype c_QList_T_FloatingWindow_T___size(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->size();
}
// sliced(qsizetype pos) const
void *c_QList_T_FloatingWindow_T___sliced_qsizetype(void *thisObj, qsizetype pos)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::FloatingWindow *>> { fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->sliced(pos) };
}
// sliced(qsizetype pos, qsizetype n) const
void *c_QList_T_FloatingWindow_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::FloatingWindow *>> { fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->sliced(pos, n) };
}
// squeeze()
void c_QList_T_FloatingWindow_T___squeeze(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->squeeze();
}
// swapItemsAt(qsizetype i, qsizetype j)
void c_QList_T_FloatingWindow_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j)
{
    fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->swapItemsAt(i, j);
}
// takeAt(qsizetype i)
void *c_QList_T_FloatingWindow_T___takeAt_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->takeAt(i);
}
// toList() const
void *c_QList_T_FloatingWindow_T___toList(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::FloatingWindow *>> { fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->toList() };
}
// toVector() const
void *c_QList_T_FloatingWindow_T___toVector(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::FloatingWindow *>> { fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->toVector() };
}
// value(qsizetype i) const
void *c_QList_T_FloatingWindow_T___value_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj)->value(i);
}
void c_QList_T_FloatingWindow_T___destructor(void *thisObj)
{
    delete fromPtr<KDDockWidgets::Core::FloatingWindow *>(thisObj);
}
}
extern "C" {
void c_QList_T_Group_T__Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::Group *> *>(cppObj);
}
void *c_QList_T_Group_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::Group *>();
    return reinterpret_cast<void *>(ptr);
}
void *c_QList_T_Group_T___constructor_qsizetype(qsizetype size)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::Group *>(size);
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & l)
void c_QList_T_Group_T___append_QList_T(void *thisObj, void *l_)
{
    assert(l_);
    auto &l = *reinterpret_cast<QList<KDDockWidgets::Core::Group *> *>(l_);
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->append(l);
}
// at(qsizetype i) const
const void *c_QList_T_Group_T___at_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->at(i);
}
// back()
void *c_QList_T_Group_T___back(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->back();
}
// capacity() const
qsizetype c_QList_T_Group_T___capacity(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->capacity();
}
// clear()
void c_QList_T_Group_T___clear(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->clear();
}
// constFirst() const
const void *c_QList_T_Group_T___constFirst(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->constFirst();
}
// constLast() const
const void *c_QList_T_Group_T___constLast(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->constLast();
}
// count() const
qsizetype c_QList_T_Group_T___count(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->count();
}
// detach()
void c_QList_T_Group_T___detach(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->detach();
}
// empty() const
bool c_QList_T_Group_T___empty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->empty();
}
// first()
void *c_QList_T_Group_T___first(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->first();
}
// first(qsizetype n) const
void *c_QList_T_Group_T___first_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Group *>> { fromPtr<KDDockWidgets::Core::Group *>(thisObj)->first(n) };
}
// front()
void *c_QList_T_Group_T___front(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->front();
}
// isDetached() const
bool c_QList_T_Group_T___isDetached(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->isDetached();
}
// isEmpty() const
bool c_QList_T_Group_T___isEmpty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->isEmpty();
}
// isSharedWith(const QList<T > & other) const
bool c_QList_T_Group_T___isSharedWith_QList_T(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QList<KDDockWidgets::Core::Group *> *>(other_);
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->isSharedWith(other);
}
// last()
void *c_QList_T_Group_T___last(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->last();
}
// last(qsizetype n) const
void *c_QList_T_Group_T___last_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Group *>> { fromPtr<KDDockWidgets::Core::Group *>(thisObj)->last(n) };
}
// length() const
qsizetype c_QList_T_Group_T___length(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->length();
}
// mid(qsizetype pos, qsizetype len) const
void *c_QList_T_Group_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Group *>> { fromPtr<KDDockWidgets::Core::Group *>(thisObj)->mid(pos, len) };
}
// move(qsizetype from, qsizetype to)
void c_QList_T_Group_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->move(from, to);
}
// pop_back()
void c_QList_T_Group_T___pop_back(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->pop_back();
}
// pop_front()
void c_QList_T_Group_T___pop_front(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->pop_front();
}
// remove(qsizetype i, qsizetype n)
void c_QList_T_Group_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->remove(i, n);
}
// removeAt(qsizetype i)
void c_QList_T_Group_T___removeAt_qsizetype(void *thisObj, qsizetype i)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->removeAt(i);
}
// removeFirst()
void c_QList_T_Group_T___removeFirst(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->removeFirst();
}
// removeLast()
void c_QList_T_Group_T___removeLast(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->removeLast();
}
// reserve(qsizetype size)
void c_QList_T_Group_T___reserve_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->reserve(size);
}
// resize(qsizetype size)
void c_QList_T_Group_T___resize_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->resize(size);
}
// shrink_to_fit()
void c_QList_T_Group_T___shrink_to_fit(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->shrink_to_fit();
}
// size() const
qsizetype c_QList_T_Group_T___size(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->size();
}
// sliced(qsizetype pos) const
void *c_QList_T_Group_T___sliced_qsizetype(void *thisObj, qsizetype pos)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Group *>> { fromPtr<KDDockWidgets::Core::Group *>(thisObj)->sliced(pos) };
}
// sliced(qsizetype pos, qsizetype n) const
void *c_QList_T_Group_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Group *>> { fromPtr<KDDockWidgets::Core::Group *>(thisObj)->sliced(pos, n) };
}
// squeeze()
void c_QList_T_Group_T___squeeze(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->squeeze();
}
// swapItemsAt(qsizetype i, qsizetype j)
void c_QList_T_Group_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j)
{
    fromPtr<KDDockWidgets::Core::Group *>(thisObj)->swapItemsAt(i, j);
}
// takeAt(qsizetype i)
void *c_QList_T_Group_T___takeAt_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->takeAt(i);
}
// toList() const
void *c_QList_T_Group_T___toList(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Group *>> { fromPtr<KDDockWidgets::Core::Group *>(thisObj)->toList() };
}
// toVector() const
void *c_QList_T_Group_T___toVector(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Group *>> { fromPtr<KDDockWidgets::Core::Group *>(thisObj)->toVector() };
}
// value(qsizetype i) const
void *c_QList_T_Group_T___value_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::Group *>(thisObj)->value(i);
}
void c_QList_T_Group_T___destructor(void *thisObj)
{
    delete fromPtr<KDDockWidgets::Core::Group *>(thisObj);
}
}
extern "C" {
void c_QList_T_Layout_T__Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::Layout *> *>(cppObj);
}
void *c_QList_T_Layout_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::Layout *>();
    return reinterpret_cast<void *>(ptr);
}
void *c_QList_T_Layout_T___constructor_qsizetype(qsizetype size)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::Layout *>(size);
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & l)
void c_QList_T_Layout_T___append_QList_T(void *thisObj, void *l_)
{
    assert(l_);
    auto &l = *reinterpret_cast<QList<KDDockWidgets::Core::Layout *> *>(l_);
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->append(l);
}
// at(qsizetype i) const
const void *c_QList_T_Layout_T___at_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->at(i);
}
// back()
void *c_QList_T_Layout_T___back(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->back();
}
// capacity() const
qsizetype c_QList_T_Layout_T___capacity(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->capacity();
}
// clear()
void c_QList_T_Layout_T___clear(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->clear();
}
// constFirst() const
const void *c_QList_T_Layout_T___constFirst(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->constFirst();
}
// constLast() const
const void *c_QList_T_Layout_T___constLast(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->constLast();
}
// count() const
qsizetype c_QList_T_Layout_T___count(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->count();
}
// detach()
void c_QList_T_Layout_T___detach(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->detach();
}
// empty() const
bool c_QList_T_Layout_T___empty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->empty();
}
// first()
void *c_QList_T_Layout_T___first(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->first();
}
// first(qsizetype n) const
void *c_QList_T_Layout_T___first_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Layout *>> { fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->first(n) };
}
// front()
void *c_QList_T_Layout_T___front(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->front();
}
// isDetached() const
bool c_QList_T_Layout_T___isDetached(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->isDetached();
}
// isEmpty() const
bool c_QList_T_Layout_T___isEmpty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->isEmpty();
}
// isSharedWith(const QList<T > & other) const
bool c_QList_T_Layout_T___isSharedWith_QList_T(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QList<KDDockWidgets::Core::Layout *> *>(other_);
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->isSharedWith(other);
}
// last()
void *c_QList_T_Layout_T___last(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->last();
}
// last(qsizetype n) const
void *c_QList_T_Layout_T___last_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Layout *>> { fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->last(n) };
}
// length() const
qsizetype c_QList_T_Layout_T___length(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->length();
}
// mid(qsizetype pos, qsizetype len) const
void *c_QList_T_Layout_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Layout *>> { fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->mid(pos, len) };
}
// move(qsizetype from, qsizetype to)
void c_QList_T_Layout_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->move(from, to);
}
// pop_back()
void c_QList_T_Layout_T___pop_back(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->pop_back();
}
// pop_front()
void c_QList_T_Layout_T___pop_front(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->pop_front();
}
// remove(qsizetype i, qsizetype n)
void c_QList_T_Layout_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->remove(i, n);
}
// removeAt(qsizetype i)
void c_QList_T_Layout_T___removeAt_qsizetype(void *thisObj, qsizetype i)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->removeAt(i);
}
// removeFirst()
void c_QList_T_Layout_T___removeFirst(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->removeFirst();
}
// removeLast()
void c_QList_T_Layout_T___removeLast(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->removeLast();
}
// reserve(qsizetype size)
void c_QList_T_Layout_T___reserve_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->reserve(size);
}
// resize(qsizetype size)
void c_QList_T_Layout_T___resize_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->resize(size);
}
// shrink_to_fit()
void c_QList_T_Layout_T___shrink_to_fit(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->shrink_to_fit();
}
// size() const
qsizetype c_QList_T_Layout_T___size(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->size();
}
// sliced(qsizetype pos) const
void *c_QList_T_Layout_T___sliced_qsizetype(void *thisObj, qsizetype pos)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Layout *>> { fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->sliced(pos) };
}
// sliced(qsizetype pos, qsizetype n) const
void *c_QList_T_Layout_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Layout *>> { fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->sliced(pos, n) };
}
// squeeze()
void c_QList_T_Layout_T___squeeze(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->squeeze();
}
// swapItemsAt(qsizetype i, qsizetype j)
void c_QList_T_Layout_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j)
{
    fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->swapItemsAt(i, j);
}
// takeAt(qsizetype i)
void *c_QList_T_Layout_T___takeAt_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->takeAt(i);
}
// toList() const
void *c_QList_T_Layout_T___toList(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Layout *>> { fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->toList() };
}
// toVector() const
void *c_QList_T_Layout_T___toVector(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Layout *>> { fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->toVector() };
}
// value(qsizetype i) const
void *c_QList_T_Layout_T___value_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::Layout *>(thisObj)->value(i);
}
void c_QList_T_Layout_T___destructor(void *thisObj)
{
    delete fromPtr<KDDockWidgets::Core::Layout *>(thisObj);
}
}
extern "C" {
void c_QList_T_MainWindow_T__Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::MainWindow *> *>(cppObj);
}
void *c_QList_T_MainWindow_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::MainWindow *>();
    return reinterpret_cast<void *>(ptr);
}
void *c_QList_T_MainWindow_T___constructor_qsizetype(qsizetype size)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::MainWindow *>(size);
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & l)
void c_QList_T_MainWindow_T___append_QList_T(void *thisObj, void *l_)
{
    assert(l_);
    auto &l = *reinterpret_cast<QList<KDDockWidgets::Core::MainWindow *> *>(l_);
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->append(l);
}
// at(qsizetype i) const
const void *c_QList_T_MainWindow_T___at_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->at(i);
}
// back()
void *c_QList_T_MainWindow_T___back(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->back();
}
// capacity() const
qsizetype c_QList_T_MainWindow_T___capacity(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->capacity();
}
// clear()
void c_QList_T_MainWindow_T___clear(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->clear();
}
// constFirst() const
const void *c_QList_T_MainWindow_T___constFirst(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->constFirst();
}
// constLast() const
const void *c_QList_T_MainWindow_T___constLast(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->constLast();
}
// count() const
qsizetype c_QList_T_MainWindow_T___count(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->count();
}
// detach()
void c_QList_T_MainWindow_T___detach(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->detach();
}
// empty() const
bool c_QList_T_MainWindow_T___empty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->empty();
}
// first()
void *c_QList_T_MainWindow_T___first(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->first();
}
// first(qsizetype n) const
void *c_QList_T_MainWindow_T___first_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::MainWindow *>> { fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->first(n) };
}
// front()
void *c_QList_T_MainWindow_T___front(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->front();
}
// isDetached() const
bool c_QList_T_MainWindow_T___isDetached(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->isDetached();
}
// isEmpty() const
bool c_QList_T_MainWindow_T___isEmpty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->isEmpty();
}
// isSharedWith(const QList<T > & other) const
bool c_QList_T_MainWindow_T___isSharedWith_QList_T(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QList<KDDockWidgets::Core::MainWindow *> *>(other_);
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->isSharedWith(other);
}
// last()
void *c_QList_T_MainWindow_T___last(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->last();
}
// last(qsizetype n) const
void *c_QList_T_MainWindow_T___last_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::MainWindow *>> { fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->last(n) };
}
// length() const
qsizetype c_QList_T_MainWindow_T___length(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->length();
}
// mid(qsizetype pos, qsizetype len) const
void *c_QList_T_MainWindow_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::MainWindow *>> { fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->mid(pos, len) };
}
// move(qsizetype from, qsizetype to)
void c_QList_T_MainWindow_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->move(from, to);
}
// pop_back()
void c_QList_T_MainWindow_T___pop_back(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->pop_back();
}
// pop_front()
void c_QList_T_MainWindow_T___pop_front(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->pop_front();
}
// remove(qsizetype i, qsizetype n)
void c_QList_T_MainWindow_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->remove(i, n);
}
// removeAt(qsizetype i)
void c_QList_T_MainWindow_T___removeAt_qsizetype(void *thisObj, qsizetype i)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->removeAt(i);
}
// removeFirst()
void c_QList_T_MainWindow_T___removeFirst(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->removeFirst();
}
// removeLast()
void c_QList_T_MainWindow_T___removeLast(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->removeLast();
}
// reserve(qsizetype size)
void c_QList_T_MainWindow_T___reserve_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->reserve(size);
}
// resize(qsizetype size)
void c_QList_T_MainWindow_T___resize_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->resize(size);
}
// shrink_to_fit()
void c_QList_T_MainWindow_T___shrink_to_fit(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->shrink_to_fit();
}
// size() const
qsizetype c_QList_T_MainWindow_T___size(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->size();
}
// sliced(qsizetype pos) const
void *c_QList_T_MainWindow_T___sliced_qsizetype(void *thisObj, qsizetype pos)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::MainWindow *>> { fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->sliced(pos) };
}
// sliced(qsizetype pos, qsizetype n) const
void *c_QList_T_MainWindow_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::MainWindow *>> { fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->sliced(pos, n) };
}
// squeeze()
void c_QList_T_MainWindow_T___squeeze(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->squeeze();
}
// swapItemsAt(qsizetype i, qsizetype j)
void c_QList_T_MainWindow_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j)
{
    fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->swapItemsAt(i, j);
}
// takeAt(qsizetype i)
void *c_QList_T_MainWindow_T___takeAt_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->takeAt(i);
}
// toList() const
void *c_QList_T_MainWindow_T___toList(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::MainWindow *>> { fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->toList() };
}
// toVector() const
void *c_QList_T_MainWindow_T___toVector(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::MainWindow *>> { fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->toVector() };
}
// value(qsizetype i) const
void *c_QList_T_MainWindow_T___value_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj)->value(i);
}
void c_QList_T_MainWindow_T___destructor(void *thisObj)
{
    delete fromPtr<KDDockWidgets::Core::MainWindow *>(thisObj);
}
}
extern "C" {
void c_QList_T_int_T__Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<int> *>(cppObj);
}
void *c_QList_T_int_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<int>();
    return reinterpret_cast<void *>(ptr);
}
void *c_QList_T_int_T___constructor_qsizetype(qsizetype size)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<int>(size);
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & l)
void c_QList_T_int_T___append_QList_T(void *thisObj, void *l_)
{
    assert(l_);
    auto &l = *reinterpret_cast<QList<int> *>(l_);
    fromPtr<int>(thisObj)->append(l);
}
// at(qsizetype i) const
const int c_QList_T_int_T___at_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<int>(thisObj)->at(i);
}
// back()
int c_QList_T_int_T___back(void *thisObj)
{
    return fromPtr<int>(thisObj)->back();
}
// capacity() const
qsizetype c_QList_T_int_T___capacity(void *thisObj)
{
    return fromPtr<int>(thisObj)->capacity();
}
// clear()
void c_QList_T_int_T___clear(void *thisObj)
{
    fromPtr<int>(thisObj)->clear();
}
// constFirst() const
const int c_QList_T_int_T___constFirst(void *thisObj)
{
    return fromPtr<int>(thisObj)->constFirst();
}
// constLast() const
const int c_QList_T_int_T___constLast(void *thisObj)
{
    return fromPtr<int>(thisObj)->constLast();
}
// count() const
qsizetype c_QList_T_int_T___count(void *thisObj)
{
    return fromPtr<int>(thisObj)->count();
}
// detach()
void c_QList_T_int_T___detach(void *thisObj)
{
    fromPtr<int>(thisObj)->detach();
}
// empty() const
bool c_QList_T_int_T___empty(void *thisObj)
{
    return fromPtr<int>(thisObj)->empty();
}
// first()
int c_QList_T_int_T___first(void *thisObj)
{
    return fromPtr<int>(thisObj)->first();
}
// first(qsizetype n) const
void *c_QList_T_int_T___first_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<int>> { fromPtr<int>(thisObj)->first(n) };
}
// front()
int c_QList_T_int_T___front(void *thisObj)
{
    return fromPtr<int>(thisObj)->front();
}
// isDetached() const
bool c_QList_T_int_T___isDetached(void *thisObj)
{
    return fromPtr<int>(thisObj)->isDetached();
}
// isEmpty() const
bool c_QList_T_int_T___isEmpty(void *thisObj)
{
    return fromPtr<int>(thisObj)->isEmpty();
}
// isSharedWith(const QList<T > & other) const
bool c_QList_T_int_T___isSharedWith_QList_T(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QList<int> *>(other_);
    return fromPtr<int>(thisObj)->isSharedWith(other);
}
// last()
int c_QList_T_int_T___last(void *thisObj)
{
    return fromPtr<int>(thisObj)->last();
}
// last(qsizetype n) const
void *c_QList_T_int_T___last_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<int>> { fromPtr<int>(thisObj)->last(n) };
}
// length() const
qsizetype c_QList_T_int_T___length(void *thisObj)
{
    return fromPtr<int>(thisObj)->length();
}
// mid(qsizetype pos, qsizetype len) const
void *c_QList_T_int_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QList<int>> { fromPtr<int>(thisObj)->mid(pos, len) };
}
// move(qsizetype from, qsizetype to)
void c_QList_T_int_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to)
{
    fromPtr<int>(thisObj)->move(from, to);
}
// pop_back()
void c_QList_T_int_T___pop_back(void *thisObj)
{
    fromPtr<int>(thisObj)->pop_back();
}
// pop_front()
void c_QList_T_int_T___pop_front(void *thisObj)
{
    fromPtr<int>(thisObj)->pop_front();
}
// remove(qsizetype i, qsizetype n)
void c_QList_T_int_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n)
{
    fromPtr<int>(thisObj)->remove(i, n);
}
// removeAt(qsizetype i)
void c_QList_T_int_T___removeAt_qsizetype(void *thisObj, qsizetype i)
{
    fromPtr<int>(thisObj)->removeAt(i);
}
// removeFirst()
void c_QList_T_int_T___removeFirst(void *thisObj)
{
    fromPtr<int>(thisObj)->removeFirst();
}
// removeLast()
void c_QList_T_int_T___removeLast(void *thisObj)
{
    fromPtr<int>(thisObj)->removeLast();
}
// reserve(qsizetype size)
void c_QList_T_int_T___reserve_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<int>(thisObj)->reserve(size);
}
// resize(qsizetype size)
void c_QList_T_int_T___resize_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<int>(thisObj)->resize(size);
}
// shrink_to_fit()
void c_QList_T_int_T___shrink_to_fit(void *thisObj)
{
    fromPtr<int>(thisObj)->shrink_to_fit();
}
// size() const
qsizetype c_QList_T_int_T___size(void *thisObj)
{
    return fromPtr<int>(thisObj)->size();
}
// sliced(qsizetype pos) const
void *c_QList_T_int_T___sliced_qsizetype(void *thisObj, qsizetype pos)
{
    return new Dartagnan::ValueWrapper<QList<int>> { fromPtr<int>(thisObj)->sliced(pos) };
}
// sliced(qsizetype pos, qsizetype n) const
void *c_QList_T_int_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<int>> { fromPtr<int>(thisObj)->sliced(pos, n) };
}
// squeeze()
void c_QList_T_int_T___squeeze(void *thisObj)
{
    fromPtr<int>(thisObj)->squeeze();
}
// swapItemsAt(qsizetype i, qsizetype j)
void c_QList_T_int_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j)
{
    fromPtr<int>(thisObj)->swapItemsAt(i, j);
}
// takeAt(qsizetype i)
int c_QList_T_int_T___takeAt_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<int>(thisObj)->takeAt(i);
}
// toList() const
void *c_QList_T_int_T___toList(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<int>> { fromPtr<int>(thisObj)->toList() };
}
// toVector() const
void *c_QList_T_int_T___toVector(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<int>> { fromPtr<int>(thisObj)->toVector() };
}
// value(qsizetype i) const
int c_QList_T_int_T___value_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<int>(thisObj)->value(i);
}
void c_QList_T_int_T___destructor(void *thisObj)
{
    delete fromPtr<int>(thisObj);
}
}
extern "C" {
void c_QList_T_Item_T__Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::Item *> *>(cppObj);
}
void *c_QList_T_Item_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::Item *>();
    return reinterpret_cast<void *>(ptr);
}
void *c_QList_T_Item_T___constructor_qsizetype(qsizetype size)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::Item *>(size);
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & l)
void c_QList_T_Item_T___append_QList_T(void *thisObj, void *l_)
{
    assert(l_);
    auto &l = *reinterpret_cast<QList<KDDockWidgets::Core::Item *> *>(l_);
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->append(l);
}
// at(qsizetype i) const
const void *c_QList_T_Item_T___at_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->at(i);
}
// back()
void *c_QList_T_Item_T___back(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->back();
}
// capacity() const
qsizetype c_QList_T_Item_T___capacity(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->capacity();
}
// clear()
void c_QList_T_Item_T___clear(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->clear();
}
// constFirst() const
const void *c_QList_T_Item_T___constFirst(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->constFirst();
}
// constLast() const
const void *c_QList_T_Item_T___constLast(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->constLast();
}
// count() const
qsizetype c_QList_T_Item_T___count(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->count();
}
// detach()
void c_QList_T_Item_T___detach(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->detach();
}
// empty() const
bool c_QList_T_Item_T___empty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->empty();
}
// first()
void *c_QList_T_Item_T___first(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->first();
}
// first(qsizetype n) const
void *c_QList_T_Item_T___first_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Item *>> { fromPtr<KDDockWidgets::Core::Item *>(thisObj)->first(n) };
}
// front()
void *c_QList_T_Item_T___front(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->front();
}
// isDetached() const
bool c_QList_T_Item_T___isDetached(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->isDetached();
}
// isEmpty() const
bool c_QList_T_Item_T___isEmpty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->isEmpty();
}
// isSharedWith(const QList<T > & other) const
bool c_QList_T_Item_T___isSharedWith_QList_T(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QList<KDDockWidgets::Core::Item *> *>(other_);
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->isSharedWith(other);
}
// last()
void *c_QList_T_Item_T___last(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->last();
}
// last(qsizetype n) const
void *c_QList_T_Item_T___last_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Item *>> { fromPtr<KDDockWidgets::Core::Item *>(thisObj)->last(n) };
}
// length() const
qsizetype c_QList_T_Item_T___length(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->length();
}
// mid(qsizetype pos, qsizetype len) const
void *c_QList_T_Item_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Item *>> { fromPtr<KDDockWidgets::Core::Item *>(thisObj)->mid(pos, len) };
}
// move(qsizetype from, qsizetype to)
void c_QList_T_Item_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->move(from, to);
}
// pop_back()
void c_QList_T_Item_T___pop_back(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->pop_back();
}
// pop_front()
void c_QList_T_Item_T___pop_front(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->pop_front();
}
// remove(qsizetype i, qsizetype n)
void c_QList_T_Item_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->remove(i, n);
}
// removeAt(qsizetype i)
void c_QList_T_Item_T___removeAt_qsizetype(void *thisObj, qsizetype i)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->removeAt(i);
}
// removeFirst()
void c_QList_T_Item_T___removeFirst(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->removeFirst();
}
// removeLast()
void c_QList_T_Item_T___removeLast(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->removeLast();
}
// reserve(qsizetype size)
void c_QList_T_Item_T___reserve_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->reserve(size);
}
// resize(qsizetype size)
void c_QList_T_Item_T___resize_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->resize(size);
}
// shrink_to_fit()
void c_QList_T_Item_T___shrink_to_fit(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->shrink_to_fit();
}
// size() const
qsizetype c_QList_T_Item_T___size(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->size();
}
// sliced(qsizetype pos) const
void *c_QList_T_Item_T___sliced_qsizetype(void *thisObj, qsizetype pos)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Item *>> { fromPtr<KDDockWidgets::Core::Item *>(thisObj)->sliced(pos) };
}
// sliced(qsizetype pos, qsizetype n) const
void *c_QList_T_Item_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Item *>> { fromPtr<KDDockWidgets::Core::Item *>(thisObj)->sliced(pos, n) };
}
// squeeze()
void c_QList_T_Item_T___squeeze(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->squeeze();
}
// swapItemsAt(qsizetype i, qsizetype j)
void c_QList_T_Item_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j)
{
    fromPtr<KDDockWidgets::Core::Item *>(thisObj)->swapItemsAt(i, j);
}
// takeAt(qsizetype i)
void *c_QList_T_Item_T___takeAt_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->takeAt(i);
}
// toList() const
void *c_QList_T_Item_T___toList(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Item *>> { fromPtr<KDDockWidgets::Core::Item *>(thisObj)->toList() };
}
// toVector() const
void *c_QList_T_Item_T___toVector(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Item *>> { fromPtr<KDDockWidgets::Core::Item *>(thisObj)->toVector() };
}
// value(qsizetype i) const
void *c_QList_T_Item_T___value_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::Item *>(thisObj)->value(i);
}
void c_QList_T_Item_T___destructor(void *thisObj)
{
    delete fromPtr<KDDockWidgets::Core::Item *>(thisObj);
}
}
extern "C" {
void c_QList_T_Separator_T__Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::Separator *> *>(cppObj);
}
void *c_QList_T_Separator_T___constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::Separator *>();
    return reinterpret_cast<void *>(ptr);
}
void *c_QList_T_Separator_T___constructor_qsizetype(qsizetype size)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<KDDockWidgets::Core::Separator *>(size);
    return reinterpret_cast<void *>(ptr);
}
// append(const QList<T > & l)
void c_QList_T_Separator_T___append_QList_T(void *thisObj, void *l_)
{
    assert(l_);
    auto &l = *reinterpret_cast<QList<KDDockWidgets::Core::Separator *> *>(l_);
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->append(l);
}
// at(qsizetype i) const
const void *c_QList_T_Separator_T___at_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->at(i);
}
// back()
void *c_QList_T_Separator_T___back(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->back();
}
// capacity() const
qsizetype c_QList_T_Separator_T___capacity(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->capacity();
}
// clear()
void c_QList_T_Separator_T___clear(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->clear();
}
// constFirst() const
const void *c_QList_T_Separator_T___constFirst(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->constFirst();
}
// constLast() const
const void *c_QList_T_Separator_T___constLast(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->constLast();
}
// count() const
qsizetype c_QList_T_Separator_T___count(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->count();
}
// detach()
void c_QList_T_Separator_T___detach(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->detach();
}
// empty() const
bool c_QList_T_Separator_T___empty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->empty();
}
// first()
void *c_QList_T_Separator_T___first(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->first();
}
// first(qsizetype n) const
void *c_QList_T_Separator_T___first_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Separator *>> { fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->first(n) };
}
// front()
void *c_QList_T_Separator_T___front(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->front();
}
// isDetached() const
bool c_QList_T_Separator_T___isDetached(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->isDetached();
}
// isEmpty() const
bool c_QList_T_Separator_T___isEmpty(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->isEmpty();
}
// isSharedWith(const QList<T > & other) const
bool c_QList_T_Separator_T___isSharedWith_QList_T(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QList<KDDockWidgets::Core::Separator *> *>(other_);
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->isSharedWith(other);
}
// last()
void *c_QList_T_Separator_T___last(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->last();
}
// last(qsizetype n) const
void *c_QList_T_Separator_T___last_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Separator *>> { fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->last(n) };
}
// length() const
qsizetype c_QList_T_Separator_T___length(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->length();
}
// mid(qsizetype pos, qsizetype len) const
void *c_QList_T_Separator_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Separator *>> { fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->mid(pos, len) };
}
// move(qsizetype from, qsizetype to)
void c_QList_T_Separator_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->move(from, to);
}
// pop_back()
void c_QList_T_Separator_T___pop_back(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->pop_back();
}
// pop_front()
void c_QList_T_Separator_T___pop_front(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->pop_front();
}
// remove(qsizetype i, qsizetype n)
void c_QList_T_Separator_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->remove(i, n);
}
// removeAt(qsizetype i)
void c_QList_T_Separator_T___removeAt_qsizetype(void *thisObj, qsizetype i)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->removeAt(i);
}
// removeFirst()
void c_QList_T_Separator_T___removeFirst(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->removeFirst();
}
// removeLast()
void c_QList_T_Separator_T___removeLast(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->removeLast();
}
// reserve(qsizetype size)
void c_QList_T_Separator_T___reserve_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->reserve(size);
}
// resize(qsizetype size)
void c_QList_T_Separator_T___resize_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->resize(size);
}
// shrink_to_fit()
void c_QList_T_Separator_T___shrink_to_fit(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->shrink_to_fit();
}
// size() const
qsizetype c_QList_T_Separator_T___size(void *thisObj)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->size();
}
// sliced(qsizetype pos) const
void *c_QList_T_Separator_T___sliced_qsizetype(void *thisObj, qsizetype pos)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Separator *>> { fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->sliced(pos) };
}
// sliced(qsizetype pos, qsizetype n) const
void *c_QList_T_Separator_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Separator *>> { fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->sliced(pos, n) };
}
// squeeze()
void c_QList_T_Separator_T___squeeze(void *thisObj)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->squeeze();
}
// swapItemsAt(qsizetype i, qsizetype j)
void c_QList_T_Separator_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j)
{
    fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->swapItemsAt(i, j);
}
// takeAt(qsizetype i)
void *c_QList_T_Separator_T___takeAt_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->takeAt(i);
}
// toList() const
void *c_QList_T_Separator_T___toList(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Separator *>> { fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->toList() };
}
// toVector() const
void *c_QList_T_Separator_T___toVector(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Separator *>> { fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->toVector() };
}
// value(qsizetype i) const
void *c_QList_T_Separator_T___value_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr<KDDockWidgets::Core::Separator *>(thisObj)->value(i);
}
void c_QList_T_Separator_T___destructor(void *thisObj)
{
    delete fromPtr<KDDockWidgets::Core::Separator *>(thisObj);
}
}
