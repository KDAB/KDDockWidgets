/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
namespace KDDockWidgets_wrappersNS {
// tag=1006
QByteArray_wrapper::QByteArray_wrapper()
    : ::QByteArray()
{
}

// tag=1006
QByteArray_wrapper::QByteArray_wrapper(const char *arg__1, int size)
    : ::QByteArray(arg__1, size)
{
}
QByteArray &QByteArray_wrapper::append(const QByteArray &a)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::append(a);
}
QByteArray &QByteArray_wrapper::append(const char *s)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::append(s);
}
QByteArray &QByteArray_wrapper::append(const char *s, int len)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::append(s, len);
}
char QByteArray_wrapper::at(int i) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::at(i);
}
char QByteArray_wrapper::back() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::back();
}
int QByteArray_wrapper::capacity() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::capacity();
}
const char *QByteArray_wrapper::cbegin() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::cbegin();
}
const char *QByteArray_wrapper::cend() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::cend();
}
void QByteArray_wrapper::chop(int n)
{
    // tag=1000

    // tag=1004
    ::QByteArray::chop(n);
}
QByteArray QByteArray_wrapper::chopped(int len) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::chopped(len);
}
void QByteArray_wrapper::clear()
{
    // tag=1000

    // tag=1004
    ::QByteArray::clear();
}
int QByteArray_wrapper::compare(const QByteArray &a) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::compare(a);
}
int QByteArray_wrapper::compare(const char *c) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::compare(c);
}
const char *QByteArray_wrapper::constBegin() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::constBegin();
}
const char *QByteArray_wrapper::constData() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::constData();
}
const char *QByteArray_wrapper::constEnd() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::constEnd();
}
bool QByteArray_wrapper::contains(const QByteArray &a) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::contains(a);
}
bool QByteArray_wrapper::contains(const char *a) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::contains(a);
}
int QByteArray_wrapper::count() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::count();
}
int QByteArray_wrapper::count(const QByteArray &a) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::count(a);
}
int QByteArray_wrapper::count(const char *a) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::count(a);
}
void QByteArray_wrapper::detach()
{
    // tag=1000

    // tag=1004
    ::QByteArray::detach();
}
bool QByteArray_wrapper::endsWith(const QByteArray &a) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::endsWith(a);
}
bool QByteArray_wrapper::endsWith(const char *c) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::endsWith(c);
}
QByteArray QByteArray_wrapper::fromBase64(const QByteArray &base64)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::fromBase64(base64);
}
QByteArray QByteArray_wrapper::fromHex(const QByteArray &hexEncoded)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::fromHex(hexEncoded);
}
QByteArray QByteArray_wrapper::fromRawData(const char *arg__1, int size)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::fromRawData(arg__1, size);
}
char QByteArray_wrapper::front() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::front();
}
int QByteArray_wrapper::indexOf(const QByteArray &a, int from) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::indexOf(a, from);
}
int QByteArray_wrapper::indexOf(const char *c, int from) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::indexOf(c, from);
}
QByteArray &QByteArray_wrapper::insert(int i, const QByteArray &a)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::insert(i, a);
}
QByteArray &QByteArray_wrapper::insert(int i, const char *s)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::insert(i, s);
}
QByteArray &QByteArray_wrapper::insert(int i, const char *s, int len)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::insert(i, s, len);
}
bool QByteArray_wrapper::isDetached() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::isDetached();
}
bool QByteArray_wrapper::isEmpty() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::isEmpty();
}
bool QByteArray_wrapper::isLower() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::isLower();
}
bool QByteArray_wrapper::isNull() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::isNull();
}
bool QByteArray_wrapper::isSharedWith(const QByteArray &other) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::isSharedWith(other);
}
bool QByteArray_wrapper::isUpper() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::isUpper();
}
int QByteArray_wrapper::lastIndexOf(const QByteArray &a, int from) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::lastIndexOf(a, from);
}
int QByteArray_wrapper::lastIndexOf(const char *c, int from) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::lastIndexOf(c, from);
}
QByteArray QByteArray_wrapper::left(int len) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::left(len);
}
int QByteArray_wrapper::length() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::length();
}
QByteArray QByteArray_wrapper::mid(int index, int len) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::mid(index, len);
}
QByteArray QByteArray_wrapper::number(int arg__1, int base)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::number(arg__1, base);
}
QByteArray QByteArray_wrapper::number(qint64 arg__1, int base)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::number(arg__1, base);
}
QByteArray &QByteArray_wrapper::prepend(const QByteArray &a)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::prepend(a);
}
QByteArray &QByteArray_wrapper::prepend(const char *s)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::prepend(s);
}
QByteArray &QByteArray_wrapper::prepend(const char *s, int len)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::prepend(s, len);
}
void QByteArray_wrapper::push_back(const QByteArray &a)
{
    // tag=1000

    // tag=1004
    ::QByteArray::push_back(a);
}
void QByteArray_wrapper::push_back(const char *c)
{
    // tag=1000

    // tag=1004
    ::QByteArray::push_back(c);
}
void QByteArray_wrapper::push_front(const QByteArray &a)
{
    // tag=1000

    // tag=1004
    ::QByteArray::push_front(a);
}
void QByteArray_wrapper::push_front(const char *c)
{
    // tag=1000

    // tag=1004
    ::QByteArray::push_front(c);
}
QByteArray &QByteArray_wrapper::remove(int index, int len)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::remove(index, len);
}
QByteArray QByteArray_wrapper::repeated(int times) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::repeated(times);
}
QByteArray &QByteArray_wrapper::replace(const QByteArray &before, const QByteArray &after)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::replace(before, after);
}
QByteArray &QByteArray_wrapper::replace(const QByteArray &before, const char *after)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::replace(before, after);
}
QByteArray &QByteArray_wrapper::replace(const char *before, const QByteArray &after)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::replace(before, after);
}
QByteArray &QByteArray_wrapper::replace(const char *before, const char *after)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::replace(before, after);
}
QByteArray &QByteArray_wrapper::replace(const char *before, int bsize, const char *after, int asize)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::replace(before, bsize, after, asize);
}
QByteArray &QByteArray_wrapper::replace(int index, int len, const QByteArray &s)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::replace(index, len, s);
}
QByteArray &QByteArray_wrapper::replace(int index, int len, const char *s)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::replace(index, len, s);
}
QByteArray &QByteArray_wrapper::replace(int index, int len, const char *s, int alen)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::replace(index, len, s, alen);
}
void QByteArray_wrapper::reserve(int size)
{
    // tag=1000

    // tag=1004
    ::QByteArray::reserve(size);
}
void QByteArray_wrapper::resize(int size)
{
    // tag=1000

    // tag=1004
    ::QByteArray::resize(size);
}
QByteArray QByteArray_wrapper::right(int len) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::right(len);
}
QByteArray &QByteArray_wrapper::setNum(int arg__1, int base)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::setNum(arg__1, base);
}
QByteArray &QByteArray_wrapper::setNum(qint64 arg__1, int base)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::setNum(arg__1, base);
}
QByteArray &QByteArray_wrapper::setNum(short arg__1, int base)
{
    // tag=1000

    // tag=1004
    return ::QByteArray::setNum(arg__1, base);
}
void QByteArray_wrapper::shrink_to_fit()
{
    // tag=1000

    // tag=1004
    ::QByteArray::shrink_to_fit();
}
QByteArray QByteArray_wrapper::simplified()
{
    // tag=1000

    // tag=1004
    return ::QByteArray::simplified();
}
int QByteArray_wrapper::size() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::size();
}
void QByteArray_wrapper::squeeze()
{
    // tag=1000

    // tag=1004
    ::QByteArray::squeeze();
}
bool QByteArray_wrapper::startsWith(const QByteArray &a) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::startsWith(a);
}
bool QByteArray_wrapper::startsWith(const char *c) const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::startsWith(c);
}
QByteArray QByteArray_wrapper::toBase64() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::toBase64();
}
QByteArray QByteArray_wrapper::toHex() const
{
    // tag=1000

    // tag=1004
    return ::QByteArray::toHex();
}
QByteArray QByteArray_wrapper::toLower()
{
    // tag=1000

    // tag=1004
    return ::QByteArray::toLower();
}
QByteArray QByteArray_wrapper::toUpper()
{
    // tag=1000

    // tag=1004
    return ::QByteArray::toUpper();
}
QByteArray QByteArray_wrapper::trimmed()
{
    // tag=1000

    // tag=1004
    return ::QByteArray::trimmed();
}
void QByteArray_wrapper::truncate(int pos)
{
    // tag=1000

    // tag=1004
    ::QByteArray::truncate(pos);
}

// tag=1005
QByteArray_wrapper::~QByteArray_wrapper()
{
}

}
// tag=1013
static QByteArray *fromPtr(void *ptr)
{
    return reinterpret_cast<QByteArray *>(ptr);
}
// tag=1014
static KDDockWidgets_wrappersNS::QByteArray_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets_wrappersNS::QByteArray_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_QByteArray_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgets_wrappersNS::QByteArray_wrapper *>(cppObj);
}
void *c_QByteArray__constructor()
{

    // tag=1056
    auto ptr = new KDDockWidgets_wrappersNS::QByteArray_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void *c_QByteArray__constructor_char_int(const char *arg__1, int size)
{

    // tag=1056
    auto ptr = new KDDockWidgets_wrappersNS::QByteArray_wrapper(arg__1, size);
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// append(const QByteArray & a)
void *c_QByteArray__append_QByteArray(void *thisObj, void *a_)
{
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->append(a);
}

// tag=1050
// append(const char * s)
void *c_QByteArray__append_char(void *thisObj, const char *s)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->append(s);
}

// tag=1050
// append(const char * s, int len)
void *c_QByteArray__append_char_int(void *thisObj, const char *s, int len)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->append(s, len);
}

// tag=1050
// at(int i) const
char c_QByteArray__at_int(void *thisObj, int i)
{
    return
        // tag=1010
        fromPtr(thisObj)->at(i);
}

// tag=1050
// back() const
char c_QByteArray__back(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->back();
}

// tag=1050
// capacity() const
int c_QByteArray__capacity(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->capacity();
}

// tag=1050
// cbegin() const
const char *c_QByteArray__cbegin(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->cbegin();
}

// tag=1050
// cend() const
const char *c_QByteArray__cend(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->cend();
}

// tag=1050
// chop(int n)
void c_QByteArray__chop_int(void *thisObj, int n)
{
    // tag=1010
    fromPtr(thisObj)->chop(n);
}

// tag=1050
// chopped(int len) const
void *c_QByteArray__chopped_int(void *thisObj, int len)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->chopped(len) };
}

// tag=1050
// clear()
void c_QByteArray__clear(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->clear();
}

// tag=1050
// compare(const QByteArray & a) const
int c_QByteArray__compare_QByteArray(void *thisObj, void *a_)
{
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return
        // tag=1010
        fromPtr(thisObj)->compare(a);
}

// tag=1050
// compare(const char * c) const
int c_QByteArray__compare_char(void *thisObj, const char *c)
{
    return
        // tag=1010
        fromPtr(thisObj)->compare(c);
}

// tag=1050
// constBegin() const
const char *c_QByteArray__constBegin(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->constBegin();
}

// tag=1050
// constData() const
const char *c_QByteArray__constData(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->constData();
}

// tag=1050
// constEnd() const
const char *c_QByteArray__constEnd(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->constEnd();
}

// tag=1050
// contains(const QByteArray & a) const
bool c_QByteArray__contains_QByteArray(void *thisObj, void *a_)
{
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return
        // tag=1010
        fromPtr(thisObj)->contains(a);
}

// tag=1050
// contains(const char * a) const
bool c_QByteArray__contains_char(void *thisObj, const char *a)
{
    return
        // tag=1010
        fromPtr(thisObj)->contains(a);
}

// tag=1050
// count() const
int c_QByteArray__count(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->count();
}

// tag=1050
// count(const QByteArray & a) const
int c_QByteArray__count_QByteArray(void *thisObj, void *a_)
{
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return
        // tag=1010
        fromPtr(thisObj)->count(a);
}

// tag=1050
// count(const char * a) const
int c_QByteArray__count_char(void *thisObj, const char *a)
{
    return
        // tag=1010
        fromPtr(thisObj)->count(a);
}

// tag=1050
// detach()
void c_QByteArray__detach(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->detach();
}

// tag=1050
// endsWith(const QByteArray & a) const
bool c_QByteArray__endsWith_QByteArray(void *thisObj, void *a_)
{
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return
        // tag=1010
        fromPtr(thisObj)->endsWith(a);
}

// tag=1050
// endsWith(const char * c) const
bool c_QByteArray__endsWith_char(void *thisObj, const char *c)
{
    return
        // tag=1010
        fromPtr(thisObj)->endsWith(c);
}

// tag=1050
// fromBase64(const QByteArray & base64)
void *c_static_QByteArray__fromBase64_QByteArray(void *base64_)
{
    auto &base64 = *reinterpret_cast<QByteArray *>(base64_);
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { KDDockWidgets_wrappersNS::QByteArray_wrapper::fromBase64(base64) };
}

// tag=1050
// fromHex(const QByteArray & hexEncoded)
void *c_static_QByteArray__fromHex_QByteArray(void *hexEncoded_)
{
    auto &hexEncoded = *reinterpret_cast<QByteArray *>(hexEncoded_);
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { KDDockWidgets_wrappersNS::QByteArray_wrapper::fromHex(hexEncoded) };
}

// tag=1050
// fromRawData(const char * arg__1, int size)
void *c_static_QByteArray__fromRawData_char_int(const char *arg__1, int size)
{
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { KDDockWidgets_wrappersNS::QByteArray_wrapper::fromRawData(arg__1, size) };
}

// tag=1050
// front() const
char c_QByteArray__front(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->front();
}

// tag=1050
// indexOf(const QByteArray & a, int from) const
int c_QByteArray__indexOf_QByteArray_int(void *thisObj, void *a_, int from)
{
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return
        // tag=1010
        fromPtr(thisObj)->indexOf(a, from);
}

// tag=1050
// indexOf(const char * c, int from) const
int c_QByteArray__indexOf_char_int(void *thisObj, const char *c, int from)
{
    return
        // tag=1010
        fromPtr(thisObj)->indexOf(c, from);
}

// tag=1050
// insert(int i, const QByteArray & a)
void *c_QByteArray__insert_int_QByteArray(void *thisObj, int i, void *a_)
{
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->insert(i, a);
}

// tag=1050
// insert(int i, const char * s)
void *c_QByteArray__insert_int_char(void *thisObj, int i, const char *s)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->insert(i, s);
}

// tag=1050
// insert(int i, const char * s, int len)
void *c_QByteArray__insert_int_char_int(void *thisObj, int i, const char *s, int len)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->insert(i, s, len);
}

// tag=1050
// isDetached() const
bool c_QByteArray__isDetached(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isDetached();
}

// tag=1050
// isEmpty() const
bool c_QByteArray__isEmpty(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isEmpty();
}

// tag=1050
// isLower() const
bool c_QByteArray__isLower(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isLower();
}

// tag=1050
// isNull() const
bool c_QByteArray__isNull(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isNull();
}

// tag=1050
// isSharedWith(const QByteArray & other) const
bool c_QByteArray__isSharedWith_QByteArray(void *thisObj, void *other_)
{
    auto &other = *reinterpret_cast<QByteArray *>(other_);
    return
        // tag=1010
        fromPtr(thisObj)->isSharedWith(other);
}

// tag=1050
// isUpper() const
bool c_QByteArray__isUpper(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isUpper();
}

// tag=1050
// lastIndexOf(const QByteArray & a, int from) const
int c_QByteArray__lastIndexOf_QByteArray_int(void *thisObj, void *a_, int from)
{
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return
        // tag=1010
        fromPtr(thisObj)->lastIndexOf(a, from);
}

// tag=1050
// lastIndexOf(const char * c, int from) const
int c_QByteArray__lastIndexOf_char_int(void *thisObj, const char *c, int from)
{
    return
        // tag=1010
        fromPtr(thisObj)->lastIndexOf(c, from);
}

// tag=1050
// left(int len) const
void *c_QByteArray__left_int(void *thisObj, int len)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->left(len) };
}

// tag=1050
// length() const
int c_QByteArray__length(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->length();
}

// tag=1050
// mid(int index, int len) const
void *c_QByteArray__mid_int_int(void *thisObj, int index, int len)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->mid(index, len) };
}

// tag=1050
// number(int arg__1, int base)
void *c_static_QByteArray__number_int_int(int arg__1, int base)
{
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { KDDockWidgets_wrappersNS::QByteArray_wrapper::number(arg__1, base) };
}

// tag=1050
// number(qint64 arg__1, int base)
void *c_static_QByteArray__number_qint64_int(qint64 arg__1, int base)
{
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { KDDockWidgets_wrappersNS::QByteArray_wrapper::number(arg__1, base) };
}

// tag=1050
// prepend(const QByteArray & a)
void *c_QByteArray__prepend_QByteArray(void *thisObj, void *a_)
{
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->prepend(a);
}

// tag=1050
// prepend(const char * s)
void *c_QByteArray__prepend_char(void *thisObj, const char *s)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->prepend(s);
}

// tag=1050
// prepend(const char * s, int len)
void *c_QByteArray__prepend_char_int(void *thisObj, const char *s, int len)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->prepend(s, len);
}

// tag=1050
// push_back(const QByteArray & a)
void c_QByteArray__push_back_QByteArray(void *thisObj, void *a_)
{
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    // tag=1010
    fromPtr(thisObj)->push_back(a);
}

// tag=1050
// push_back(const char * c)
void c_QByteArray__push_back_char(void *thisObj, const char *c)
{
    // tag=1010
    fromPtr(thisObj)->push_back(c);
}

// tag=1050
// push_front(const QByteArray & a)
void c_QByteArray__push_front_QByteArray(void *thisObj, void *a_)
{
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    // tag=1010
    fromPtr(thisObj)->push_front(a);
}

// tag=1050
// push_front(const char * c)
void c_QByteArray__push_front_char(void *thisObj, const char *c)
{
    // tag=1010
    fromPtr(thisObj)->push_front(c);
}

// tag=1050
// remove(int index, int len)
void *c_QByteArray__remove_int_int(void *thisObj, int index, int len)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->remove(index, len);
}

// tag=1050
// repeated(int times) const
void *c_QByteArray__repeated_int(void *thisObj, int times)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->repeated(times) };
}

// tag=1050
// replace(const QByteArray & before, const QByteArray & after)
void *c_QByteArray__replace_QByteArray_QByteArray(void *thisObj, void *before_, void *after_)
{
    auto &before = *reinterpret_cast<QByteArray *>(before_);
    auto &after = *reinterpret_cast<QByteArray *>(after_);
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->replace(before, after);
}

// tag=1050
// replace(const QByteArray & before, const char * after)
void *c_QByteArray__replace_QByteArray_char(void *thisObj, void *before_, const char *after)
{
    auto &before = *reinterpret_cast<QByteArray *>(before_);
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->replace(before, after);
}

// tag=1050
// replace(const char * before, const QByteArray & after)
void *c_QByteArray__replace_char_QByteArray(void *thisObj, const char *before, void *after_)
{
    auto &after = *reinterpret_cast<QByteArray *>(after_);
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->replace(before, after);
}

// tag=1050
// replace(const char * before, const char * after)
void *c_QByteArray__replace_char_char(void *thisObj, const char *before, const char *after)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->replace(before, after);
}

// tag=1050
// replace(const char * before, int bsize, const char * after, int asize)
void *c_QByteArray__replace_char_int_char_int(void *thisObj, const char *before, int bsize, const char *after, int asize)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->replace(before, bsize, after, asize);
}

// tag=1050
// replace(int index, int len, const QByteArray & s)
void *c_QByteArray__replace_int_int_QByteArray(void *thisObj, int index, int len, void *s_)
{
    auto &s = *reinterpret_cast<QByteArray *>(s_);
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->replace(index, len, s);
}

// tag=1050
// replace(int index, int len, const char * s)
void *c_QByteArray__replace_int_int_char(void *thisObj, int index, int len, const char *s)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->replace(index, len, s);
}

// tag=1050
// replace(int index, int len, const char * s, int alen)
void *c_QByteArray__replace_int_int_char_int(void *thisObj, int index, int len, const char *s, int alen)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->replace(index, len, s, alen);
}

// tag=1050
// reserve(int size)
void c_QByteArray__reserve_int(void *thisObj, int size)
{
    // tag=1010
    fromPtr(thisObj)->reserve(size);
}

// tag=1050
// resize(int size)
void c_QByteArray__resize_int(void *thisObj, int size)
{
    // tag=1010
    fromPtr(thisObj)->resize(size);
}

// tag=1050
// right(int len) const
void *c_QByteArray__right_int(void *thisObj, int len)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->right(len) };
}

// tag=1050
// setNum(int arg__1, int base)
void *c_QByteArray__setNum_int_int(void *thisObj, int arg__1, int base)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->setNum(arg__1, base);
}

// tag=1050
// setNum(qint64 arg__1, int base)
void *c_QByteArray__setNum_qint64_int(void *thisObj, qint64 arg__1, int base)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->setNum(arg__1, base);
}

// tag=1050
// setNum(short arg__1, int base)
void *c_QByteArray__setNum_short_int(void *thisObj, short arg__1, int base)
{
    return
        // tag=1010

        // tag=1070
        &fromPtr(thisObj)->setNum(arg__1, base);
}

// tag=1050
// shrink_to_fit()
void c_QByteArray__shrink_to_fit(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->shrink_to_fit();
}

// tag=1050
// simplified()
void *c_QByteArray__simplified(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->simplified() };
}

// tag=1050
// size() const
int c_QByteArray__size(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->size();
}

// tag=1050
// squeeze()
void c_QByteArray__squeeze(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->squeeze();
}

// tag=1050
// startsWith(const QByteArray & a) const
bool c_QByteArray__startsWith_QByteArray(void *thisObj, void *a_)
{
    auto &a = *reinterpret_cast<QByteArray *>(a_);
    return
        // tag=1010
        fromPtr(thisObj)->startsWith(a);
}

// tag=1050
// startsWith(const char * c) const
bool c_QByteArray__startsWith_char(void *thisObj, const char *c)
{
    return
        // tag=1010
        fromPtr(thisObj)->startsWith(c);
}

// tag=1050
// toBase64() const
void *c_QByteArray__toBase64(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->toBase64() };
}

// tag=1050
// toHex() const
void *c_QByteArray__toHex(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->toHex() };
}

// tag=1050
// toLower()
void *c_QByteArray__toLower(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->toLower() };
}

// tag=1050
// toUpper()
void *c_QByteArray__toUpper(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->toUpper() };
}

// tag=1050
// trimmed()
void *c_QByteArray__trimmed(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->trimmed() };
}

// tag=1050
// truncate(int pos)
void c_QByteArray__truncate_int(void *thisObj, int pos)
{
    // tag=1010
    fromPtr(thisObj)->truncate(pos);
}
void c_QByteArray__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
}
