/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgets_exports.h"
#include <qbytearray.h>
#include <qlist.h>

namespace KDDockWidgets_wrappersNS {
// tag=1043
class QByteArray_wrapper : public ::QByteArray
{
public:
    ~QByteArray_wrapper();
    // tag=1041
    QByteArray_wrapper();
    // tag=1041
    QByteArray_wrapper(const char *arg__1, int size = -1);
    // tag=1041
    QByteArray &append(const QByteArray &a);
    // tag=1041
    QByteArray &append(const char *s);
    // tag=1041
    QByteArray &append(const char *s, int len);
    // tag=1041
    char at(int i) const;
    // tag=1041
    char back() const;
    // tag=1041
    const char *begin() const;
    // tag=1041
    int capacity() const;
    // tag=1041
    const char *cbegin() const;
    // tag=1041
    const char *cend() const;
    // tag=1041
    void chop(int n);
    // tag=1041
    QByteArray chopped(int len) const;
    // tag=1041
    void clear();
    // tag=1041
    int compare(const QByteArray &a) const;
    // tag=1041
    int compare(const char *c) const;
    // tag=1041
    const char *constBegin() const;
    // tag=1041
    const char *constData() const;
    // tag=1041
    const char *constEnd() const;
    // tag=1041
    bool contains(const QByteArray &a) const;
    // tag=1041
    bool contains(const char *a) const;
    // tag=1041
    int count() const;
    // tag=1041
    int count(const QByteArray &a) const;
    // tag=1041
    int count(const char *a) const;
    // tag=1041
    const char *data() const;
    // tag=1041
    void detach();
    // tag=1041
    const char *end() const;
    // tag=1041
    bool endsWith(const QByteArray &a) const;
    // tag=1041
    bool endsWith(const char *c) const;
    // tag=1041
    static QByteArray fromBase64(const QByteArray &base64);
    // tag=1041
    static QByteArray fromHex(const QByteArray &hexEncoded);
    // tag=1041
    static QByteArray fromRawData(const char *arg__1, int size);
    // tag=1041
    char front() const;
    // tag=1041
    int indexOf(const QByteArray &a, int from = 0) const;
    // tag=1041
    int indexOf(const char *c, int from = 0) const;
    // tag=1041
    QByteArray &insert(int i, const QByteArray &a);
    // tag=1041
    QByteArray &insert(int i, const char *s);
    // tag=1041
    QByteArray &insert(int i, const char *s, int len);
    // tag=1041
    bool isDetached() const;
    // tag=1041
    bool isEmpty() const;
    // tag=1041
    bool isLower() const;
    // tag=1041
    bool isNull() const;
    // tag=1041
    bool isSharedWith(const QByteArray &other) const;
    // tag=1041
    bool isUpper() const;
    // tag=1041
    int lastIndexOf(const QByteArray &a, int from = -1) const;
    // tag=1041
    int lastIndexOf(const char *c, int from = -1) const;
    // tag=1041
    QByteArray left(int len) const;
    // tag=1041
    int length() const;
    // tag=1041
    QByteArray mid(int index, int len = -1) const;
    // tag=1041
    static QByteArray number(int arg__1, int base = 10);
    // tag=1041
    static QByteArray number(qint64 arg__1, int base = 10);
    // tag=1041
    QByteArray &prepend(const QByteArray &a);
    // tag=1041
    QByteArray &prepend(const char *s);
    // tag=1041
    QByteArray &prepend(const char *s, int len);
    // tag=1041
    void push_back(const QByteArray &a);
    // tag=1041
    void push_back(const char *c);
    // tag=1041
    void push_front(const QByteArray &a);
    // tag=1041
    void push_front(const char *c);
    // tag=1041
    QByteArray &remove(int index, int len);
    // tag=1041
    QByteArray repeated(int times) const;
    // tag=1041
    QByteArray &replace(const QByteArray &before, const QByteArray &after);
    // tag=1041
    QByteArray &replace(const QByteArray &before, const char *after);
    // tag=1041
    QByteArray &replace(const char *before, const QByteArray &after);
    // tag=1041
    QByteArray &replace(const char *before, const char *after);
    // tag=1041
    QByteArray &replace(const char *before, int bsize, const char *after, int asize);
    // tag=1041
    QByteArray &replace(int index, int len, const QByteArray &s);
    // tag=1041
    QByteArray &replace(int index, int len, const char *s);
    // tag=1041
    QByteArray &replace(int index, int len, const char *s, int alen);
    // tag=1041
    void reserve(int size);
    // tag=1041
    void resize(int size);
    // tag=1041
    QByteArray right(int len) const;
    // tag=1041
    QByteArray &setNum(int arg__1, int base = 10);
    // tag=1041
    QByteArray &setNum(qint64 arg__1, int base = 10);
    // tag=1041
    QByteArray &setNum(short arg__1, int base = 10);
    // tag=1041
    void shrink_to_fit();
    // tag=1041
    QByteArray simplified();
    // tag=1041
    int size() const;
    // tag=1041
    void squeeze();
    // tag=1041
    bool startsWith(const QByteArray &a) const;
    // tag=1041
    bool startsWith(const char *c) const;
    // tag=1041
    QByteArray toBase64() const;
    // tag=1041
    QByteArray toHex() const;
    // tag=1041
    QByteArray toLower();
    // tag=1041
    QByteArray toUpper();
    // tag=1041
    QByteArray trimmed();
    // tag=1041
    void truncate(int pos);
};
}
extern "C" {

// tag=1067
//  QByteArray::QByteArray()
KDDockWidgets_EXPORT void *c_QByteArray__constructor();

// tag=1067
//  QByteArray::QByteArray(const char * arg__1, int size)
KDDockWidgets_EXPORT void *c_QByteArray__constructor_char_int(const char *arg__1, int size);

// tag=1067
//  QByteArray::append(const QByteArray & a)
KDDockWidgets_EXPORT void *c_QByteArray__append_QByteArray(void *thisObj, void *a_);

// tag=1067
//  QByteArray::append(const char * s)
KDDockWidgets_EXPORT void *c_QByteArray__append_char(void *thisObj, const char *s);

// tag=1067
//  QByteArray::append(const char * s, int len)
KDDockWidgets_EXPORT void *c_QByteArray__append_char_int(void *thisObj, const char *s, int len);

// tag=1067
//  QByteArray::at(int i) const
KDDockWidgets_EXPORT char c_QByteArray__at_int(void *thisObj, int i);

// tag=1067
//  QByteArray::back() const
KDDockWidgets_EXPORT char c_QByteArray__back(void *thisObj);

// tag=1067
//  QByteArray::begin() const
KDDockWidgets_EXPORT const char *c_QByteArray__begin(void *thisObj);

// tag=1067
//  QByteArray::capacity() const
KDDockWidgets_EXPORT int c_QByteArray__capacity(void *thisObj);

// tag=1067
//  QByteArray::cbegin() const
KDDockWidgets_EXPORT const char *c_QByteArray__cbegin(void *thisObj);

// tag=1067
//  QByteArray::cend() const
KDDockWidgets_EXPORT const char *c_QByteArray__cend(void *thisObj);

// tag=1067
//  QByteArray::chop(int n)
KDDockWidgets_EXPORT void c_QByteArray__chop_int(void *thisObj, int n);

// tag=1067
//  QByteArray::chopped(int len) const
KDDockWidgets_EXPORT void *c_QByteArray__chopped_int(void *thisObj, int len);

// tag=1067
//  QByteArray::clear()
KDDockWidgets_EXPORT void c_QByteArray__clear(void *thisObj);

// tag=1067
//  QByteArray::compare(const QByteArray & a) const
KDDockWidgets_EXPORT int c_QByteArray__compare_QByteArray(void *thisObj, void *a_);

// tag=1067
//  QByteArray::compare(const char * c) const
KDDockWidgets_EXPORT int c_QByteArray__compare_char(void *thisObj, const char *c);

// tag=1067
//  QByteArray::constBegin() const
KDDockWidgets_EXPORT const char *c_QByteArray__constBegin(void *thisObj);

// tag=1067
//  QByteArray::constData() const
KDDockWidgets_EXPORT const char *c_QByteArray__constData(void *thisObj);

// tag=1067
//  QByteArray::constEnd() const
KDDockWidgets_EXPORT const char *c_QByteArray__constEnd(void *thisObj);

// tag=1067
//  QByteArray::contains(const QByteArray & a) const
KDDockWidgets_EXPORT bool c_QByteArray__contains_QByteArray(void *thisObj, void *a_);

// tag=1067
//  QByteArray::contains(const char * a) const
KDDockWidgets_EXPORT bool c_QByteArray__contains_char(void *thisObj, const char *a);

// tag=1067
//  QByteArray::count() const
KDDockWidgets_EXPORT int c_QByteArray__count(void *thisObj);

// tag=1067
//  QByteArray::count(const QByteArray & a) const
KDDockWidgets_EXPORT int c_QByteArray__count_QByteArray(void *thisObj, void *a_);

// tag=1067
//  QByteArray::count(const char * a) const
KDDockWidgets_EXPORT int c_QByteArray__count_char(void *thisObj, const char *a);

// tag=1067
//  QByteArray::data() const
KDDockWidgets_EXPORT const char *c_QByteArray__data(void *thisObj);

// tag=1067
//  QByteArray::detach()
KDDockWidgets_EXPORT void c_QByteArray__detach(void *thisObj);

// tag=1067
//  QByteArray::end() const
KDDockWidgets_EXPORT const char *c_QByteArray__end(void *thisObj);

// tag=1067
//  QByteArray::endsWith(const QByteArray & a) const
KDDockWidgets_EXPORT bool c_QByteArray__endsWith_QByteArray(void *thisObj, void *a_);

// tag=1067
//  QByteArray::endsWith(const char * c) const
KDDockWidgets_EXPORT bool c_QByteArray__endsWith_char(void *thisObj, const char *c);

// tag=1067
//  QByteArray::fromBase64(const QByteArray & base64)
KDDockWidgets_EXPORT void *c_static_QByteArray__fromBase64_QByteArray(void *base64_);

// tag=1067
//  QByteArray::fromHex(const QByteArray & hexEncoded)
KDDockWidgets_EXPORT void *c_static_QByteArray__fromHex_QByteArray(void *hexEncoded_);

// tag=1067
//  QByteArray::fromRawData(const char * arg__1, int size)
KDDockWidgets_EXPORT void *c_static_QByteArray__fromRawData_char_int(const char *arg__1, int size);

// tag=1067
//  QByteArray::front() const
KDDockWidgets_EXPORT char c_QByteArray__front(void *thisObj);

// tag=1067
//  QByteArray::indexOf(const QByteArray & a, int from) const
KDDockWidgets_EXPORT int c_QByteArray__indexOf_QByteArray_int(void *thisObj, void *a_, int from);

// tag=1067
//  QByteArray::indexOf(const char * c, int from) const
KDDockWidgets_EXPORT int c_QByteArray__indexOf_char_int(void *thisObj, const char *c, int from);

// tag=1067
//  QByteArray::insert(int i, const QByteArray & a)
KDDockWidgets_EXPORT void *c_QByteArray__insert_int_QByteArray(void *thisObj, int i, void *a_);

// tag=1067
//  QByteArray::insert(int i, const char * s)
KDDockWidgets_EXPORT void *c_QByteArray__insert_int_char(void *thisObj, int i, const char *s);

// tag=1067
//  QByteArray::insert(int i, const char * s, int len)
KDDockWidgets_EXPORT void *c_QByteArray__insert_int_char_int(void *thisObj, int i, const char *s, int len);

// tag=1067
//  QByteArray::isDetached() const
KDDockWidgets_EXPORT bool c_QByteArray__isDetached(void *thisObj);

// tag=1067
//  QByteArray::isEmpty() const
KDDockWidgets_EXPORT bool c_QByteArray__isEmpty(void *thisObj);

// tag=1067
//  QByteArray::isLower() const
KDDockWidgets_EXPORT bool c_QByteArray__isLower(void *thisObj);

// tag=1067
//  QByteArray::isNull() const
KDDockWidgets_EXPORT bool c_QByteArray__isNull(void *thisObj);

// tag=1067
//  QByteArray::isSharedWith(const QByteArray & other) const
KDDockWidgets_EXPORT bool c_QByteArray__isSharedWith_QByteArray(void *thisObj, void *other_);

// tag=1067
//  QByteArray::isUpper() const
KDDockWidgets_EXPORT bool c_QByteArray__isUpper(void *thisObj);

// tag=1067
//  QByteArray::lastIndexOf(const QByteArray & a, int from) const
KDDockWidgets_EXPORT int c_QByteArray__lastIndexOf_QByteArray_int(void *thisObj, void *a_, int from);

// tag=1067
//  QByteArray::lastIndexOf(const char * c, int from) const
KDDockWidgets_EXPORT int c_QByteArray__lastIndexOf_char_int(void *thisObj, const char *c, int from);

// tag=1067
//  QByteArray::left(int len) const
KDDockWidgets_EXPORT void *c_QByteArray__left_int(void *thisObj, int len);

// tag=1067
//  QByteArray::length() const
KDDockWidgets_EXPORT int c_QByteArray__length(void *thisObj);

// tag=1067
//  QByteArray::mid(int index, int len) const
KDDockWidgets_EXPORT void *c_QByteArray__mid_int_int(void *thisObj, int index, int len);

// tag=1067
//  QByteArray::number(int arg__1, int base)
KDDockWidgets_EXPORT void *c_static_QByteArray__number_int_int(int arg__1, int base);

// tag=1067
//  QByteArray::number(qint64 arg__1, int base)
KDDockWidgets_EXPORT void *c_static_QByteArray__number_qint64_int(qint64 arg__1, int base);

// tag=1067
//  QByteArray::prepend(const QByteArray & a)
KDDockWidgets_EXPORT void *c_QByteArray__prepend_QByteArray(void *thisObj, void *a_);

// tag=1067
//  QByteArray::prepend(const char * s)
KDDockWidgets_EXPORT void *c_QByteArray__prepend_char(void *thisObj, const char *s);

// tag=1067
//  QByteArray::prepend(const char * s, int len)
KDDockWidgets_EXPORT void *c_QByteArray__prepend_char_int(void *thisObj, const char *s, int len);

// tag=1067
//  QByteArray::push_back(const QByteArray & a)
KDDockWidgets_EXPORT void c_QByteArray__push_back_QByteArray(void *thisObj, void *a_);

// tag=1067
//  QByteArray::push_back(const char * c)
KDDockWidgets_EXPORT void c_QByteArray__push_back_char(void *thisObj, const char *c);

// tag=1067
//  QByteArray::push_front(const QByteArray & a)
KDDockWidgets_EXPORT void c_QByteArray__push_front_QByteArray(void *thisObj, void *a_);

// tag=1067
//  QByteArray::push_front(const char * c)
KDDockWidgets_EXPORT void c_QByteArray__push_front_char(void *thisObj, const char *c);

// tag=1067
//  QByteArray::remove(int index, int len)
KDDockWidgets_EXPORT void *c_QByteArray__remove_int_int(void *thisObj, int index, int len);

// tag=1067
//  QByteArray::repeated(int times) const
KDDockWidgets_EXPORT void *c_QByteArray__repeated_int(void *thisObj, int times);

// tag=1067
//  QByteArray::replace(const QByteArray & before, const QByteArray & after)
KDDockWidgets_EXPORT void *c_QByteArray__replace_QByteArray_QByteArray(void *thisObj, void *before_, void *after_);

// tag=1067
//  QByteArray::replace(const QByteArray & before, const char * after)
KDDockWidgets_EXPORT void *c_QByteArray__replace_QByteArray_char(void *thisObj, void *before_, const char *after);

// tag=1067
//  QByteArray::replace(const char * before, const QByteArray & after)
KDDockWidgets_EXPORT void *c_QByteArray__replace_char_QByteArray(void *thisObj, const char *before, void *after_);

// tag=1067
//  QByteArray::replace(const char * before, const char * after)
KDDockWidgets_EXPORT void *c_QByteArray__replace_char_char(void *thisObj, const char *before, const char *after);

// tag=1067
//  QByteArray::replace(const char * before, int bsize, const char * after, int asize)
KDDockWidgets_EXPORT void *c_QByteArray__replace_char_int_char_int(void *thisObj, const char *before, int bsize, const char *after, int asize);

// tag=1067
//  QByteArray::replace(int index, int len, const QByteArray & s)
KDDockWidgets_EXPORT void *c_QByteArray__replace_int_int_QByteArray(void *thisObj, int index, int len, void *s_);

// tag=1067
//  QByteArray::replace(int index, int len, const char * s)
KDDockWidgets_EXPORT void *c_QByteArray__replace_int_int_char(void *thisObj, int index, int len, const char *s);

// tag=1067
//  QByteArray::replace(int index, int len, const char * s, int alen)
KDDockWidgets_EXPORT void *c_QByteArray__replace_int_int_char_int(void *thisObj, int index, int len, const char *s, int alen);

// tag=1067
//  QByteArray::reserve(int size)
KDDockWidgets_EXPORT void c_QByteArray__reserve_int(void *thisObj, int size);

// tag=1067
//  QByteArray::resize(int size)
KDDockWidgets_EXPORT void c_QByteArray__resize_int(void *thisObj, int size);

// tag=1067
//  QByteArray::right(int len) const
KDDockWidgets_EXPORT void *c_QByteArray__right_int(void *thisObj, int len);

// tag=1067
//  QByteArray::setNum(int arg__1, int base)
KDDockWidgets_EXPORT void *c_QByteArray__setNum_int_int(void *thisObj, int arg__1, int base);

// tag=1067
//  QByteArray::setNum(qint64 arg__1, int base)
KDDockWidgets_EXPORT void *c_QByteArray__setNum_qint64_int(void *thisObj, qint64 arg__1, int base);

// tag=1067
//  QByteArray::setNum(short arg__1, int base)
KDDockWidgets_EXPORT void *c_QByteArray__setNum_short_int(void *thisObj, short arg__1, int base);

// tag=1067
//  QByteArray::shrink_to_fit()
KDDockWidgets_EXPORT void c_QByteArray__shrink_to_fit(void *thisObj);

// tag=1067
//  QByteArray::simplified()
KDDockWidgets_EXPORT void *c_QByteArray__simplified(void *thisObj);

// tag=1067
//  QByteArray::size() const
KDDockWidgets_EXPORT int c_QByteArray__size(void *thisObj);

// tag=1067
//  QByteArray::squeeze()
KDDockWidgets_EXPORT void c_QByteArray__squeeze(void *thisObj);

// tag=1067
//  QByteArray::startsWith(const QByteArray & a) const
KDDockWidgets_EXPORT bool c_QByteArray__startsWith_QByteArray(void *thisObj, void *a_);

// tag=1067
//  QByteArray::startsWith(const char * c) const
KDDockWidgets_EXPORT bool c_QByteArray__startsWith_char(void *thisObj, const char *c);

// tag=1067
//  QByteArray::toBase64() const
KDDockWidgets_EXPORT void *c_QByteArray__toBase64(void *thisObj);

// tag=1067
//  QByteArray::toHex() const
KDDockWidgets_EXPORT void *c_QByteArray__toHex(void *thisObj);

// tag=1067
//  QByteArray::toLower()
KDDockWidgets_EXPORT void *c_QByteArray__toLower(void *thisObj);

// tag=1067
//  QByteArray::toUpper()
KDDockWidgets_EXPORT void *c_QByteArray__toUpper(void *thisObj);

// tag=1067
//  QByteArray::trimmed()
KDDockWidgets_EXPORT void *c_QByteArray__trimmed(void *thisObj);

// tag=1067
//  QByteArray::truncate(int pos)
KDDockWidgets_EXPORT void c_QByteArray__truncate_int(void *thisObj, int pos);

// tag=1066
KDDockWidgets_EXPORT void c_QByteArray__destructor(void *thisObj);

// tag=1047
KDDockWidgets_EXPORT void c_QByteArray_Finalizer(void *, void *cppObj, void *);
}
