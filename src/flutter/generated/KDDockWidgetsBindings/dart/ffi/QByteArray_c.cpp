/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "QByteArray_c.h"


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
QByteArray_wrapper::QByteArray_wrapper()
    : ::QByteArray()
{
}
QByteArray_wrapper::QByteArray_wrapper(const char *arg__1, qsizetype size)
    : ::QByteArray(arg__1, size)
{
}
QByteArray &QByteArray_wrapper::append(const QByteArray &a)
{
    return ::QByteArray::append(a);
}
QByteArray &QByteArray_wrapper::append(const char *s)
{
    return ::QByteArray::append(s);
}
QByteArray &QByteArray_wrapper::append(const char *s, qsizetype len)
{
    return ::QByteArray::append(s, len);
}
char QByteArray_wrapper::at(qsizetype i) const
{
    return ::QByteArray::at(i);
}
qsizetype QByteArray_wrapper::capacity() const
{
    return ::QByteArray::capacity();
}
const char *QByteArray_wrapper::cbegin() const
{
    return ::QByteArray::cbegin();
}
const char *QByteArray_wrapper::cend() const
{
    return ::QByteArray::cend();
}
void QByteArray_wrapper::chop(qsizetype n)
{
    ::QByteArray::chop(n);
}
QByteArray QByteArray_wrapper::chopped(qsizetype len) const
{
    return ::QByteArray::chopped(len);
}
void QByteArray_wrapper::clear()
{
    ::QByteArray::clear();
}
const char *QByteArray_wrapper::constBegin() const
{
    return ::QByteArray::constBegin();
}
const char *QByteArray_wrapper::constData() const
{
    return ::QByteArray::constData();
}
const char *QByteArray_wrapper::constEnd() const
{
    return ::QByteArray::constEnd();
}
void QByteArray_wrapper::detach()
{
    ::QByteArray::detach();
}
QByteArray QByteArray_wrapper::first(qsizetype n) const
{
    return ::QByteArray::first(n);
}
QByteArray QByteArray_wrapper::fromBase64(const QByteArray &base64)
{
    return ::QByteArray::fromBase64(base64);
}
QByteArray QByteArray_wrapper::fromHex(const QByteArray &hexEncoded)
{
    return ::QByteArray::fromHex(hexEncoded);
}
QByteArray QByteArray_wrapper::fromRawData(const char *data, qsizetype size)
{
    return ::QByteArray::fromRawData(data, size);
}
QByteArray &QByteArray_wrapper::insert(qsizetype i, const QByteArray &data)
{
    return ::QByteArray::insert(i, data);
}
QByteArray &QByteArray_wrapper::insert(qsizetype i, const char *s)
{
    return ::QByteArray::insert(i, s);
}
QByteArray &QByteArray_wrapper::insert(qsizetype i, const char *s, qsizetype len)
{
    return ::QByteArray::insert(i, s, len);
}
bool QByteArray_wrapper::isDetached() const
{
    return ::QByteArray::isDetached();
}
bool QByteArray_wrapper::isEmpty() const
{
    return ::QByteArray::isEmpty();
}
bool QByteArray_wrapper::isLower() const
{
    return ::QByteArray::isLower();
}
bool QByteArray_wrapper::isNull() const
{
    return ::QByteArray::isNull();
}
bool QByteArray_wrapper::isSharedWith(const QByteArray &other) const
{
    return ::QByteArray::isSharedWith(other);
}
bool QByteArray_wrapper::isUpper() const
{
    return ::QByteArray::isUpper();
}
bool QByteArray_wrapper::isValidUtf8() const
{
    return ::QByteArray::isValidUtf8();
}
QByteArray QByteArray_wrapper::last(qsizetype n) const
{
    return ::QByteArray::last(n);
}
QByteArray QByteArray_wrapper::left(qsizetype len) const
{
    return ::QByteArray::left(len);
}
qsizetype QByteArray_wrapper::length() const
{
    return ::QByteArray::length();
}
QByteArray QByteArray_wrapper::mid(qsizetype index, qsizetype len) const
{
    return ::QByteArray::mid(index, len);
}
QByteArray QByteArray_wrapper::number(int arg__1, int base)
{
    return ::QByteArray::number(arg__1, base);
}
QByteArray QByteArray_wrapper::number(long arg__1, int base)
{
    return ::QByteArray::number(arg__1, base);
}
QByteArray QByteArray_wrapper::number(qint64 arg__1, int base)
{
    return ::QByteArray::number(arg__1, base);
}
QByteArray &QByteArray_wrapper::prepend(const QByteArray &a)
{
    return ::QByteArray::prepend(a);
}
QByteArray &QByteArray_wrapper::prepend(const char *s)
{
    return ::QByteArray::prepend(s);
}
QByteArray &QByteArray_wrapper::prepend(const char *s, qsizetype len)
{
    return ::QByteArray::prepend(s, len);
}
void QByteArray_wrapper::push_back(const QByteArray &a)
{
    ::QByteArray::push_back(a);
}
void QByteArray_wrapper::push_back(const char *s)
{
    ::QByteArray::push_back(s);
}
void QByteArray_wrapper::push_front(const QByteArray &a)
{
    ::QByteArray::push_front(a);
}
void QByteArray_wrapper::push_front(const char *c)
{
    ::QByteArray::push_front(c);
}
QByteArray &QByteArray_wrapper::remove(qsizetype index, qsizetype len)
{
    return ::QByteArray::remove(index, len);
}
QByteArray &QByteArray_wrapper::removeAt(qsizetype pos)
{
    return ::QByteArray::removeAt(pos);
}
QByteArray &QByteArray_wrapper::removeFirst()
{
    return ::QByteArray::removeFirst();
}
QByteArray &QByteArray_wrapper::removeLast()
{
    return ::QByteArray::removeLast();
}
QByteArray QByteArray_wrapper::repeated(qsizetype times) const
{
    return ::QByteArray::repeated(times);
}
QByteArray &QByteArray_wrapper::replace(const char *before, qsizetype bsize, const char *after, qsizetype asize)
{
    return ::QByteArray::replace(before, bsize, after, asize);
}
QByteArray &QByteArray_wrapper::replace(qsizetype index, qsizetype len, const char *s, qsizetype alen)
{
    return ::QByteArray::replace(index, len, s, alen);
}
void QByteArray_wrapper::reserve(qsizetype size)
{
    ::QByteArray::reserve(size);
}
void QByteArray_wrapper::resize(qsizetype size)
{
    ::QByteArray::resize(size);
}
QByteArray QByteArray_wrapper::right(qsizetype len) const
{
    return ::QByteArray::right(len);
}
QByteArray &QByteArray_wrapper::setNum(int arg__1, int base)
{
    return ::QByteArray::setNum(arg__1, base);
}
QByteArray &QByteArray_wrapper::setNum(long arg__1, int base)
{
    return ::QByteArray::setNum(arg__1, base);
}
QByteArray &QByteArray_wrapper::setNum(qint64 arg__1, int base)
{
    return ::QByteArray::setNum(arg__1, base);
}
QByteArray &QByteArray_wrapper::setNum(short arg__1, int base)
{
    return ::QByteArray::setNum(arg__1, base);
}
QByteArray &QByteArray_wrapper::setRawData(const char *a, qsizetype n)
{
    return ::QByteArray::setRawData(a, n);
}
void QByteArray_wrapper::shrink_to_fit()
{
    ::QByteArray::shrink_to_fit();
}
QByteArray QByteArray_wrapper::simplified()
{
    return ::QByteArray::simplified();
}
qsizetype QByteArray_wrapper::size() const
{
    return ::QByteArray::size();
}
QByteArray QByteArray_wrapper::sliced(qsizetype pos) const
{
    return ::QByteArray::sliced(pos);
}
QByteArray QByteArray_wrapper::sliced(qsizetype pos, qsizetype n) const
{
    return ::QByteArray::sliced(pos, n);
}
void QByteArray_wrapper::squeeze()
{
    ::QByteArray::squeeze();
}
QByteArray QByteArray_wrapper::toBase64() const
{
    return ::QByteArray::toBase64();
}
QByteArray QByteArray_wrapper::toLower()
{
    return ::QByteArray::toLower();
}
QByteArray QByteArray_wrapper::toUpper()
{
    return ::QByteArray::toUpper();
}
QByteArray QByteArray_wrapper::trimmed()
{
    return ::QByteArray::trimmed();
}
void QByteArray_wrapper::truncate(qsizetype pos)
{
    ::QByteArray::truncate(pos);
}
QByteArray_wrapper::~QByteArray_wrapper()
{
}

}
static QByteArray *fromPtr(void *ptr)
{
    return reinterpret_cast<QByteArray *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper *>(ptr);
}
extern "C" {
void c_QByteArray_Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper *>(cppObj);
}
void *c_QByteArray__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void *c_QByteArray__constructor_char_qsizetype(const char *arg__1, qsizetype size)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper(arg__1, size);
    return reinterpret_cast<void *>(ptr);
}
// append(const QByteArray & a)
void *c_QByteArray__append_QByteArray(void *thisObj, void *a_)
{
    assert(a_);
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return &fromPtr(thisObj)->append(a);
}
// append(const char * s)
void *c_QByteArray__append_char(void *thisObj, const char *s)
{
    return &fromPtr(thisObj)->append(s);
}
// append(const char * s, qsizetype len)
void *c_QByteArray__append_char_qsizetype(void *thisObj, const char *s, qsizetype len)
{
    return &fromPtr(thisObj)->append(s, len);
}
// at(qsizetype i) const
char c_QByteArray__at_qsizetype(void *thisObj, qsizetype i)
{
    return fromPtr(thisObj)->at(i);
}
// capacity() const
qsizetype c_QByteArray__capacity(void *thisObj)
{
    return fromPtr(thisObj)->capacity();
}
// cbegin() const
const char *c_QByteArray__cbegin(void *thisObj)
{
    return fromPtr(thisObj)->cbegin();
}
// cend() const
const char *c_QByteArray__cend(void *thisObj)
{
    return fromPtr(thisObj)->cend();
}
// chop(qsizetype n)
void c_QByteArray__chop_qsizetype(void *thisObj, qsizetype n)
{
    fromPtr(thisObj)->chop(n);
}
// chopped(qsizetype len) const
void *c_QByteArray__chopped_qsizetype(void *thisObj, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->chopped(len) };
}
// clear()
void c_QByteArray__clear(void *thisObj)
{
    fromPtr(thisObj)->clear();
}
// constBegin() const
const char *c_QByteArray__constBegin(void *thisObj)
{
    return fromPtr(thisObj)->constBegin();
}
// constData() const
const char *c_QByteArray__constData(void *thisObj)
{
    return fromPtr(thisObj)->constData();
}
// constEnd() const
const char *c_QByteArray__constEnd(void *thisObj)
{
    return fromPtr(thisObj)->constEnd();
}
// detach()
void c_QByteArray__detach(void *thisObj)
{
    fromPtr(thisObj)->detach();
}
// first(qsizetype n) const
void *c_QByteArray__first_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->first(n) };
}
// fromBase64(const QByteArray & base64)
void *c_static_QByteArray__fromBase64_QByteArray(void *base64_)
{
    assert(base64_);
    auto &base64 = *reinterpret_cast<QByteArray *>(base64_);
    return new Dartagnan::ValueWrapper<QByteArray> { KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper::fromBase64(base64) };
}
// fromHex(const QByteArray & hexEncoded)
void *c_static_QByteArray__fromHex_QByteArray(void *hexEncoded_)
{
    assert(hexEncoded_);
    auto &hexEncoded = *reinterpret_cast<QByteArray *>(hexEncoded_);
    return new Dartagnan::ValueWrapper<QByteArray> { KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper::fromHex(hexEncoded) };
}
// fromRawData(const char * data, qsizetype size)
void *c_static_QByteArray__fromRawData_char_qsizetype(const char *data, qsizetype size)
{
    return new Dartagnan::ValueWrapper<QByteArray> { KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper::fromRawData(data, size) };
}
// insert(qsizetype i, const QByteArray & data)
void *c_QByteArray__insert_qsizetype_QByteArray(void *thisObj, qsizetype i, void *data_)
{
    assert(data_);
    auto &data = *reinterpret_cast<QByteArray *>(data_);
    return &fromPtr(thisObj)->insert(i, data);
}
// insert(qsizetype i, const char * s)
void *c_QByteArray__insert_qsizetype_char(void *thisObj, qsizetype i, const char *s)
{
    return &fromPtr(thisObj)->insert(i, s);
}
// insert(qsizetype i, const char * s, qsizetype len)
void *c_QByteArray__insert_qsizetype_char_qsizetype(void *thisObj, qsizetype i, const char *s, qsizetype len)
{
    return &fromPtr(thisObj)->insert(i, s, len);
}
// isDetached() const
bool c_QByteArray__isDetached(void *thisObj)
{
    return fromPtr(thisObj)->isDetached();
}
// isEmpty() const
bool c_QByteArray__isEmpty(void *thisObj)
{
    return fromPtr(thisObj)->isEmpty();
}
// isLower() const
bool c_QByteArray__isLower(void *thisObj)
{
    return fromPtr(thisObj)->isLower();
}
// isNull() const
bool c_QByteArray__isNull(void *thisObj)
{
    return fromPtr(thisObj)->isNull();
}
// isSharedWith(const QByteArray & other) const
bool c_QByteArray__isSharedWith_QByteArray(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QByteArray *>(other_);
    return fromPtr(thisObj)->isSharedWith(other);
}
// isUpper() const
bool c_QByteArray__isUpper(void *thisObj)
{
    return fromPtr(thisObj)->isUpper();
}
// isValidUtf8() const
bool c_QByteArray__isValidUtf8(void *thisObj)
{
    return fromPtr(thisObj)->isValidUtf8();
}
// last(qsizetype n) const
void *c_QByteArray__last_qsizetype(void *thisObj, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->last(n) };
}
// left(qsizetype len) const
void *c_QByteArray__left_qsizetype(void *thisObj, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->left(len) };
}
// length() const
qsizetype c_QByteArray__length(void *thisObj)
{
    return fromPtr(thisObj)->length();
}
// mid(qsizetype index, qsizetype len) const
void *c_QByteArray__mid_qsizetype_qsizetype(void *thisObj, qsizetype index, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->mid(index, len) };
}
// number(int arg__1, int base)
void *c_static_QByteArray__number_int_int(int arg__1, int base)
{
    return new Dartagnan::ValueWrapper<QByteArray> { KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper::number(arg__1, base) };
}
// number(long arg__1, int base)
void *c_static_QByteArray__number_long_int(long arg__1, int base)
{
    return new Dartagnan::ValueWrapper<QByteArray> { KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper::number(arg__1, base) };
}
// number(qint64 arg__1, int base)
void *c_static_QByteArray__number_qint64_int(qint64 arg__1, int base)
{
    return new Dartagnan::ValueWrapper<QByteArray> { KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper::number(arg__1, base) };
}
// prepend(const QByteArray & a)
void *c_QByteArray__prepend_QByteArray(void *thisObj, void *a_)
{
    assert(a_);
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return &fromPtr(thisObj)->prepend(a);
}
// prepend(const char * s)
void *c_QByteArray__prepend_char(void *thisObj, const char *s)
{
    return &fromPtr(thisObj)->prepend(s);
}
// prepend(const char * s, qsizetype len)
void *c_QByteArray__prepend_char_qsizetype(void *thisObj, const char *s, qsizetype len)
{
    return &fromPtr(thisObj)->prepend(s, len);
}
// push_back(const QByteArray & a)
void c_QByteArray__push_back_QByteArray(void *thisObj, void *a_)
{
    assert(a_);
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    fromPtr(thisObj)->push_back(a);
}
// push_back(const char * s)
void c_QByteArray__push_back_char(void *thisObj, const char *s)
{
    fromPtr(thisObj)->push_back(s);
}
// push_front(const QByteArray & a)
void c_QByteArray__push_front_QByteArray(void *thisObj, void *a_)
{
    assert(a_);
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    fromPtr(thisObj)->push_front(a);
}
// push_front(const char * c)
void c_QByteArray__push_front_char(void *thisObj, const char *c)
{
    fromPtr(thisObj)->push_front(c);
}
// remove(qsizetype index, qsizetype len)
void *c_QByteArray__remove_qsizetype_qsizetype(void *thisObj, qsizetype index, qsizetype len)
{
    return &fromPtr(thisObj)->remove(index, len);
}
// removeAt(qsizetype pos)
void *c_QByteArray__removeAt_qsizetype(void *thisObj, qsizetype pos)
{
    return &fromPtr(thisObj)->removeAt(pos);
}
// removeFirst()
void *c_QByteArray__removeFirst(void *thisObj)
{
    return &fromPtr(thisObj)->removeFirst();
}
// removeLast()
void *c_QByteArray__removeLast(void *thisObj)
{
    return &fromPtr(thisObj)->removeLast();
}
// repeated(qsizetype times) const
void *c_QByteArray__repeated_qsizetype(void *thisObj, qsizetype times)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->repeated(times) };
}
// replace(const char * before, qsizetype bsize, const char * after, qsizetype asize)
void *c_QByteArray__replace_char_qsizetype_char_qsizetype(void *thisObj, const char *before, qsizetype bsize, const char *after, qsizetype asize)
{
    return &fromPtr(thisObj)->replace(before, bsize, after, asize);
}
// replace(qsizetype index, qsizetype len, const char * s, qsizetype alen)
void *c_QByteArray__replace_qsizetype_qsizetype_char_qsizetype(void *thisObj, qsizetype index, qsizetype len, const char *s, qsizetype alen)
{
    return &fromPtr(thisObj)->replace(index, len, s, alen);
}
// reserve(qsizetype size)
void c_QByteArray__reserve_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr(thisObj)->reserve(size);
}
// resize(qsizetype size)
void c_QByteArray__resize_qsizetype(void *thisObj, qsizetype size)
{
    fromPtr(thisObj)->resize(size);
}
// right(qsizetype len) const
void *c_QByteArray__right_qsizetype(void *thisObj, qsizetype len)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->right(len) };
}
// setNum(int arg__1, int base)
void *c_QByteArray__setNum_int_int(void *thisObj, int arg__1, int base)
{
    return &fromPtr(thisObj)->setNum(arg__1, base);
}
// setNum(long arg__1, int base)
void *c_QByteArray__setNum_long_int(void *thisObj, long arg__1, int base)
{
    return &fromPtr(thisObj)->setNum(arg__1, base);
}
// setNum(qint64 arg__1, int base)
void *c_QByteArray__setNum_qint64_int(void *thisObj, qint64 arg__1, int base)
{
    return &fromPtr(thisObj)->setNum(arg__1, base);
}
// setNum(short arg__1, int base)
void *c_QByteArray__setNum_short_int(void *thisObj, short arg__1, int base)
{
    return &fromPtr(thisObj)->setNum(arg__1, base);
}
// setRawData(const char * a, qsizetype n)
void *c_QByteArray__setRawData_char_qsizetype(void *thisObj, const char *a, qsizetype n)
{
    return &fromPtr(thisObj)->setRawData(a, n);
}
// shrink_to_fit()
void c_QByteArray__shrink_to_fit(void *thisObj)
{
    fromPtr(thisObj)->shrink_to_fit();
}
// simplified()
void *c_QByteArray__simplified(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->simplified() };
}
// size() const
qsizetype c_QByteArray__size(void *thisObj)
{
    return fromPtr(thisObj)->size();
}
// sliced(qsizetype pos) const
void *c_QByteArray__sliced_qsizetype(void *thisObj, qsizetype pos)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->sliced(pos) };
}
// sliced(qsizetype pos, qsizetype n) const
void *c_QByteArray__sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->sliced(pos, n) };
}
// squeeze()
void c_QByteArray__squeeze(void *thisObj)
{
    fromPtr(thisObj)->squeeze();
}
// toBase64() const
void *c_QByteArray__toBase64(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->toBase64() };
}
// toLower()
void *c_QByteArray__toLower(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->toLower() };
}
// toUpper()
void *c_QByteArray__toUpper(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->toUpper() };
}
// trimmed()
void *c_QByteArray__trimmed(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->trimmed() };
}
// truncate(qsizetype pos)
void c_QByteArray__truncate_qsizetype(void *thisObj, qsizetype pos)
{
    fromPtr(thisObj)->truncate(pos);
}
void c_QByteArray__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
}
