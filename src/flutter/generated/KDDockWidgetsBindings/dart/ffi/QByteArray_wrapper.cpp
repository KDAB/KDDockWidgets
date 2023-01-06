/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "QByteArray_wrapper.h"


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
QByteArray_wrapper::QByteArray_wrapper(const char *arg__1, int size)
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
QByteArray &QByteArray_wrapper::append(const char *s, int len)
{
    return ::QByteArray::append(s, len);
}
char QByteArray_wrapper::at(int i) const
{
    return ::QByteArray::at(i);
}
char QByteArray_wrapper::back() const
{
    return ::QByteArray::back();
}
int QByteArray_wrapper::capacity() const
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
void QByteArray_wrapper::chop(int n)
{
    ::QByteArray::chop(n);
}
QByteArray QByteArray_wrapper::chopped(int len) const
{
    return ::QByteArray::chopped(len);
}
void QByteArray_wrapper::clear()
{
    ::QByteArray::clear();
}
int QByteArray_wrapper::compare(const QByteArray &a) const
{
    return ::QByteArray::compare(a);
}
int QByteArray_wrapper::compare(const char *c) const
{
    return ::QByteArray::compare(c);
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
bool QByteArray_wrapper::contains(const QByteArray &a) const
{
    return ::QByteArray::contains(a);
}
bool QByteArray_wrapper::contains(const char *a) const
{
    return ::QByteArray::contains(a);
}
int QByteArray_wrapper::count() const
{
    return ::QByteArray::count();
}
int QByteArray_wrapper::count(const QByteArray &a) const
{
    return ::QByteArray::count(a);
}
int QByteArray_wrapper::count(const char *a) const
{
    return ::QByteArray::count(a);
}
void QByteArray_wrapper::detach()
{
    ::QByteArray::detach();
}
bool QByteArray_wrapper::endsWith(const QByteArray &a) const
{
    return ::QByteArray::endsWith(a);
}
bool QByteArray_wrapper::endsWith(const char *c) const
{
    return ::QByteArray::endsWith(c);
}
QByteArray QByteArray_wrapper::fromBase64(const QByteArray &base64)
{
    return ::QByteArray::fromBase64(base64);
}
QByteArray QByteArray_wrapper::fromHex(const QByteArray &hexEncoded)
{
    return ::QByteArray::fromHex(hexEncoded);
}
QByteArray QByteArray_wrapper::fromRawData(const char *arg__1, int size)
{
    return ::QByteArray::fromRawData(arg__1, size);
}
char QByteArray_wrapper::front() const
{
    return ::QByteArray::front();
}
int QByteArray_wrapper::indexOf(const QByteArray &a, int from) const
{
    return ::QByteArray::indexOf(a, from);
}
int QByteArray_wrapper::indexOf(const char *c, int from) const
{
    return ::QByteArray::indexOf(c, from);
}
QByteArray &QByteArray_wrapper::insert(int i, const QByteArray &a)
{
    return ::QByteArray::insert(i, a);
}
QByteArray &QByteArray_wrapper::insert(int i, const char *s)
{
    return ::QByteArray::insert(i, s);
}
QByteArray &QByteArray_wrapper::insert(int i, const char *s, int len)
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
int QByteArray_wrapper::lastIndexOf(const QByteArray &a, int from) const
{
    return ::QByteArray::lastIndexOf(a, from);
}
int QByteArray_wrapper::lastIndexOf(const char *c, int from) const
{
    return ::QByteArray::lastIndexOf(c, from);
}
QByteArray QByteArray_wrapper::left(int len) const
{
    return ::QByteArray::left(len);
}
int QByteArray_wrapper::length() const
{
    return ::QByteArray::length();
}
QByteArray QByteArray_wrapper::mid(int index, int len) const
{
    return ::QByteArray::mid(index, len);
}
QByteArray QByteArray_wrapper::number(int arg__1, int base)
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
QByteArray &QByteArray_wrapper::prepend(const char *s, int len)
{
    return ::QByteArray::prepend(s, len);
}
void QByteArray_wrapper::push_back(const QByteArray &a)
{
    ::QByteArray::push_back(a);
}
void QByteArray_wrapper::push_back(const char *c)
{
    ::QByteArray::push_back(c);
}
void QByteArray_wrapper::push_front(const QByteArray &a)
{
    ::QByteArray::push_front(a);
}
void QByteArray_wrapper::push_front(const char *c)
{
    ::QByteArray::push_front(c);
}
QByteArray &QByteArray_wrapper::remove(int index, int len)
{
    return ::QByteArray::remove(index, len);
}
QByteArray QByteArray_wrapper::repeated(int times) const
{
    return ::QByteArray::repeated(times);
}
QByteArray &QByteArray_wrapper::replace(const QByteArray &before, const QByteArray &after)
{
    return ::QByteArray::replace(before, after);
}
QByteArray &QByteArray_wrapper::replace(const QByteArray &before, const char *after)
{
    return ::QByteArray::replace(before, after);
}
QByteArray &QByteArray_wrapper::replace(const char *before, const QByteArray &after)
{
    return ::QByteArray::replace(before, after);
}
QByteArray &QByteArray_wrapper::replace(const char *before, const char *after)
{
    return ::QByteArray::replace(before, after);
}
QByteArray &QByteArray_wrapper::replace(const char *before, int bsize, const char *after, int asize)
{
    return ::QByteArray::replace(before, bsize, after, asize);
}
QByteArray &QByteArray_wrapper::replace(int index, int len, const QByteArray &s)
{
    return ::QByteArray::replace(index, len, s);
}
QByteArray &QByteArray_wrapper::replace(int index, int len, const char *s)
{
    return ::QByteArray::replace(index, len, s);
}
QByteArray &QByteArray_wrapper::replace(int index, int len, const char *s, int alen)
{
    return ::QByteArray::replace(index, len, s, alen);
}
void QByteArray_wrapper::reserve(int size)
{
    ::QByteArray::reserve(size);
}
void QByteArray_wrapper::resize(int size)
{
    ::QByteArray::resize(size);
}
QByteArray QByteArray_wrapper::right(int len) const
{
    return ::QByteArray::right(len);
}
QByteArray &QByteArray_wrapper::setNum(int arg__1, int base)
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
void QByteArray_wrapper::shrink_to_fit()
{
    ::QByteArray::shrink_to_fit();
}
QByteArray QByteArray_wrapper::simplified()
{
    return ::QByteArray::simplified();
}
int QByteArray_wrapper::size() const
{
    return ::QByteArray::size();
}
void QByteArray_wrapper::squeeze()
{
    ::QByteArray::squeeze();
}
bool QByteArray_wrapper::startsWith(const QByteArray &a) const
{
    return ::QByteArray::startsWith(a);
}
bool QByteArray_wrapper::startsWith(const char *c) const
{
    return ::QByteArray::startsWith(c);
}
QByteArray QByteArray_wrapper::toBase64() const
{
    return ::QByteArray::toBase64();
}
QByteArray QByteArray_wrapper::toHex() const
{
    return ::QByteArray::toHex();
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
void QByteArray_wrapper::truncate(int pos)
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
void c_QByteArray_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper *>(cppObj);
}
void *c_QByteArray__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void *c_QByteArray__constructor_char_int(const char *arg__1, int size)
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
// append(const char * s, int len)
void *c_QByteArray__append_char_int(void *thisObj, const char *s, int len)
{
    return &fromPtr(thisObj)->append(s, len);
}
// at(int i) const
char c_QByteArray__at_int(void *thisObj, int i)
{
    return fromPtr(thisObj)->at(i);
}
// back() const
char c_QByteArray__back(void *thisObj)
{
    return fromPtr(thisObj)->back();
}
// capacity() const
int c_QByteArray__capacity(void *thisObj)
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
// chop(int n)
void c_QByteArray__chop_int(void *thisObj, int n)
{
    fromPtr(thisObj)->chop(n);
}
// chopped(int len) const
void *c_QByteArray__chopped_int(void *thisObj, int len)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->chopped(len) };
}
// clear()
void c_QByteArray__clear(void *thisObj)
{
    fromPtr(thisObj)->clear();
}
// compare(const QByteArray & a) const
int c_QByteArray__compare_QByteArray(void *thisObj, void *a_)
{
    assert(a_);
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return fromPtr(thisObj)->compare(a);
}
// compare(const char * c) const
int c_QByteArray__compare_char(void *thisObj, const char *c)
{
    return fromPtr(thisObj)->compare(c);
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
// contains(const QByteArray & a) const
bool c_QByteArray__contains_QByteArray(void *thisObj, void *a_)
{
    assert(a_);
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return fromPtr(thisObj)->contains(a);
}
// contains(const char * a) const
bool c_QByteArray__contains_char(void *thisObj, const char *a)
{
    return fromPtr(thisObj)->contains(a);
}
// count() const
int c_QByteArray__count(void *thisObj)
{
    return fromPtr(thisObj)->count();
}
// count(const QByteArray & a) const
int c_QByteArray__count_QByteArray(void *thisObj, void *a_)
{
    assert(a_);
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return fromPtr(thisObj)->count(a);
}
// count(const char * a) const
int c_QByteArray__count_char(void *thisObj, const char *a)
{
    return fromPtr(thisObj)->count(a);
}
// detach()
void c_QByteArray__detach(void *thisObj)
{
    fromPtr(thisObj)->detach();
}
// endsWith(const QByteArray & a) const
bool c_QByteArray__endsWith_QByteArray(void *thisObj, void *a_)
{
    assert(a_);
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return fromPtr(thisObj)->endsWith(a);
}
// endsWith(const char * c) const
bool c_QByteArray__endsWith_char(void *thisObj, const char *c)
{
    return fromPtr(thisObj)->endsWith(c);
}
// fromBase64(const QByteArray & base64)
void *c_static_QByteArray__fromBase64_QByteArray(void *base64_)
{
    assert(base64_);
    auto &base64 = *reinterpret_cast<QByteArray *>(base64_);
    return new Dartagnan::ValueWrapper<QByteArray> {
        KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper::fromBase64(base64)
    };
}
// fromHex(const QByteArray & hexEncoded)
void *c_static_QByteArray__fromHex_QByteArray(void *hexEncoded_)
{
    assert(hexEncoded_);
    auto &hexEncoded = *reinterpret_cast<QByteArray *>(hexEncoded_);
    return new Dartagnan::ValueWrapper<QByteArray> {
        KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper::fromHex(hexEncoded)
    };
}
// fromRawData(const char * arg__1, int size)
void *c_static_QByteArray__fromRawData_char_int(const char *arg__1, int size)
{
    return new Dartagnan::ValueWrapper<QByteArray> {
        KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper::fromRawData(arg__1, size)
    };
}
// front() const
char c_QByteArray__front(void *thisObj)
{
    return fromPtr(thisObj)->front();
}
// indexOf(const QByteArray & a, int from) const
int c_QByteArray__indexOf_QByteArray_int(void *thisObj, void *a_, int from)
{
    assert(a_);
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return fromPtr(thisObj)->indexOf(a, from);
}
// indexOf(const char * c, int from) const
int c_QByteArray__indexOf_char_int(void *thisObj, const char *c, int from)
{
    return fromPtr(thisObj)->indexOf(c, from);
}
// insert(int i, const QByteArray & a)
void *c_QByteArray__insert_int_QByteArray(void *thisObj, int i, void *a_)
{
    assert(a_);
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return &fromPtr(thisObj)->insert(i, a);
}
// insert(int i, const char * s)
void *c_QByteArray__insert_int_char(void *thisObj, int i, const char *s)
{
    return &fromPtr(thisObj)->insert(i, s);
}
// insert(int i, const char * s, int len)
void *c_QByteArray__insert_int_char_int(void *thisObj, int i, const char *s, int len)
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
// lastIndexOf(const QByteArray & a, int from) const
int c_QByteArray__lastIndexOf_QByteArray_int(void *thisObj, void *a_, int from)
{
    assert(a_);
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return fromPtr(thisObj)->lastIndexOf(a, from);
}
// lastIndexOf(const char * c, int from) const
int c_QByteArray__lastIndexOf_char_int(void *thisObj, const char *c, int from)
{
    return fromPtr(thisObj)->lastIndexOf(c, from);
}
// left(int len) const
void *c_QByteArray__left_int(void *thisObj, int len)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->left(len) };
}
// length() const
int c_QByteArray__length(void *thisObj)
{
    return fromPtr(thisObj)->length();
}
// mid(int index, int len) const
void *c_QByteArray__mid_int_int(void *thisObj, int index, int len)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->mid(index, len) };
}
// number(int arg__1, int base)
void *c_static_QByteArray__number_int_int(int arg__1, int base)
{
    return new Dartagnan::ValueWrapper<QByteArray> {
        KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper::number(arg__1, base)
    };
}
// number(qint64 arg__1, int base)
void *c_static_QByteArray__number_qint64_int(qint64 arg__1, int base)
{
    return new Dartagnan::ValueWrapper<QByteArray> {
        KDDockWidgetsBindings_wrappersNS::QByteArray_wrapper::number(arg__1, base)
    };
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
// prepend(const char * s, int len)
void *c_QByteArray__prepend_char_int(void *thisObj, const char *s, int len)
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
// push_back(const char * c)
void c_QByteArray__push_back_char(void *thisObj, const char *c)
{
    fromPtr(thisObj)->push_back(c);
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
// remove(int index, int len)
void *c_QByteArray__remove_int_int(void *thisObj, int index, int len)
{
    return &fromPtr(thisObj)->remove(index, len);
}
// repeated(int times) const
void *c_QByteArray__repeated_int(void *thisObj, int times)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->repeated(times) };
}
// replace(const QByteArray & before, const QByteArray & after)
void *c_QByteArray__replace_QByteArray_QByteArray(void *thisObj, void *before_, void *after_)
{
    assert(before_);
    auto &before = *reinterpret_cast<QByteArray *>(before_);
    assert(after_);
    auto &after = *reinterpret_cast<QByteArray *>(after_);
    return &fromPtr(thisObj)->replace(before, after);
}
// replace(const QByteArray & before, const char * after)
void *c_QByteArray__replace_QByteArray_char(void *thisObj, void *before_, const char *after)
{
    assert(before_);
    auto &before = *reinterpret_cast<QByteArray *>(before_);
    return &fromPtr(thisObj)->replace(before, after);
}
// replace(const char * before, const QByteArray & after)
void *c_QByteArray__replace_char_QByteArray(void *thisObj, const char *before, void *after_)
{
    assert(after_);
    auto &after = *reinterpret_cast<QByteArray *>(after_);
    return &fromPtr(thisObj)->replace(before, after);
}
// replace(const char * before, const char * after)
void *c_QByteArray__replace_char_char(void *thisObj, const char *before, const char *after)
{
    return &fromPtr(thisObj)->replace(before, after);
}
// replace(const char * before, int bsize, const char * after, int asize)
void *c_QByteArray__replace_char_int_char_int(void *thisObj, const char *before, int bsize,
                                              const char *after, int asize)
{
    return &fromPtr(thisObj)->replace(before, bsize, after, asize);
}
// replace(int index, int len, const QByteArray & s)
void *c_QByteArray__replace_int_int_QByteArray(void *thisObj, int index, int len, void *s_)
{
    assert(s_);
    auto &s = *reinterpret_cast<QByteArray *>(s_);
    return &fromPtr(thisObj)->replace(index, len, s);
}
// replace(int index, int len, const char * s)
void *c_QByteArray__replace_int_int_char(void *thisObj, int index, int len, const char *s)
{
    return &fromPtr(thisObj)->replace(index, len, s);
}
// replace(int index, int len, const char * s, int alen)
void *c_QByteArray__replace_int_int_char_int(void *thisObj, int index, int len, const char *s,
                                             int alen)
{
    return &fromPtr(thisObj)->replace(index, len, s, alen);
}
// reserve(int size)
void c_QByteArray__reserve_int(void *thisObj, int size)
{
    fromPtr(thisObj)->reserve(size);
}
// resize(int size)
void c_QByteArray__resize_int(void *thisObj, int size)
{
    fromPtr(thisObj)->resize(size);
}
// right(int len) const
void *c_QByteArray__right_int(void *thisObj, int len)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->right(len) };
}
// setNum(int arg__1, int base)
void *c_QByteArray__setNum_int_int(void *thisObj, int arg__1, int base)
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
int c_QByteArray__size(void *thisObj)
{
    return fromPtr(thisObj)->size();
}
// squeeze()
void c_QByteArray__squeeze(void *thisObj)
{
    fromPtr(thisObj)->squeeze();
}
// startsWith(const QByteArray & a) const
bool c_QByteArray__startsWith_QByteArray(void *thisObj, void *a_)
{
    assert(a_);
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return fromPtr(thisObj)->startsWith(a);
}
// startsWith(const char * c) const
bool c_QByteArray__startsWith_char(void *thisObj, const char *c)
{
    return fromPtr(thisObj)->startsWith(c);
}
// toBase64() const
void *c_QByteArray__toBase64(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->toBase64() };
}
// toHex() const
void *c_QByteArray__toHex(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->toHex() };
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
// truncate(int pos)
void c_QByteArray__truncate_int(void *thisObj, int pos)
{
    fromPtr(thisObj)->truncate(pos);
}
void c_QByteArray__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
}
