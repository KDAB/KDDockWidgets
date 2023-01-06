/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <qbytearray.h>
#include <qlist.h>

namespace KDDockWidgetsBindings_wrappersNS {
class QByteArray_wrapper : public ::QByteArray
{
public:
    ~QByteArray_wrapper();
    QByteArray_wrapper();
    QByteArray_wrapper(const char *arg__1, int size = -1);
    QByteArray &append(const QByteArray &a);
    QByteArray &append(const char *s);
    QByteArray &append(const char *s, int len);
    char at(int i) const;
    char back() const;
    const char *begin() const;
    int capacity() const;
    const char *cbegin() const;
    const char *cend() const;
    void chop(int n);
    QByteArray chopped(int len) const;
    void clear();
    int compare(const QByteArray &a) const;
    int compare(const char *c) const;
    const char *constBegin() const;
    const char *constData() const;
    const char *constEnd() const;
    bool contains(const QByteArray &a) const;
    bool contains(const char *a) const;
    int count() const;
    int count(const QByteArray &a) const;
    int count(const char *a) const;
    const char *data() const;
    void detach();
    const char *end() const;
    bool endsWith(const QByteArray &a) const;
    bool endsWith(const char *c) const;
    static QByteArray fromBase64(const QByteArray &base64);
    static QByteArray fromHex(const QByteArray &hexEncoded);
    static QByteArray fromRawData(const char *arg__1, int size);
    char front() const;
    int indexOf(const QByteArray &a, int from = 0) const;
    int indexOf(const char *c, int from = 0) const;
    QByteArray &insert(int i, const QByteArray &a);
    QByteArray &insert(int i, const char *s);
    QByteArray &insert(int i, const char *s, int len);
    bool isDetached() const;
    bool isEmpty() const;
    bool isLower() const;
    bool isNull() const;
    bool isSharedWith(const QByteArray &other) const;
    bool isUpper() const;
    int lastIndexOf(const QByteArray &a, int from = -1) const;
    int lastIndexOf(const char *c, int from = -1) const;
    QByteArray left(int len) const;
    int length() const;
    QByteArray mid(int index, int len = -1) const;
    static QByteArray number(int arg__1, int base = 10);
    static QByteArray number(qint64 arg__1, int base = 10);
    QByteArray &prepend(const QByteArray &a);
    QByteArray &prepend(const char *s);
    QByteArray &prepend(const char *s, int len);
    void push_back(const QByteArray &a);
    void push_back(const char *c);
    void push_front(const QByteArray &a);
    void push_front(const char *c);
    QByteArray &remove(int index, int len);
    QByteArray repeated(int times) const;
    QByteArray &replace(const QByteArray &before, const QByteArray &after);
    QByteArray &replace(const QByteArray &before, const char *after);
    QByteArray &replace(const char *before, const QByteArray &after);
    QByteArray &replace(const char *before, const char *after);
    QByteArray &replace(const char *before, int bsize, const char *after, int asize);
    QByteArray &replace(int index, int len, const QByteArray &s);
    QByteArray &replace(int index, int len, const char *s);
    QByteArray &replace(int index, int len, const char *s, int alen);
    void reserve(int size);
    void resize(int size);
    QByteArray right(int len) const;
    QByteArray &setNum(int arg__1, int base = 10);
    QByteArray &setNum(qint64 arg__1, int base = 10);
    QByteArray &setNum(short arg__1, int base = 10);
    void shrink_to_fit();
    QByteArray simplified();
    int size() const;
    void squeeze();
    bool startsWith(const QByteArray &a) const;
    bool startsWith(const char *c) const;
    QByteArray toBase64() const;
    QByteArray toHex() const;
    QByteArray toLower();
    QByteArray toUpper();
    QByteArray trimmed();
    void truncate(int pos);
};
}
extern "C" {
// QByteArray::QByteArray()
KDDockWidgetsBindings_EXPORT void *c_QByteArray__constructor();
// QByteArray::QByteArray(const char * arg__1, int size)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__constructor_char_int(const char *arg__1, int size);
// QByteArray::append(const QByteArray & a)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__append_QByteArray(void *thisObj, void *a_);
// QByteArray::append(const char * s)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__append_char(void *thisObj, const char *s);
// QByteArray::append(const char * s, int len)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__append_char_int(void *thisObj, const char *s,
                                                                 int len);
// QByteArray::at(int i) const
KDDockWidgetsBindings_EXPORT char c_QByteArray__at_int(void *thisObj, int i);
// QByteArray::back() const
KDDockWidgetsBindings_EXPORT char c_QByteArray__back(void *thisObj);
// QByteArray::begin() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__begin(void *thisObj);
// QByteArray::capacity() const
KDDockWidgetsBindings_EXPORT int c_QByteArray__capacity(void *thisObj);
// QByteArray::cbegin() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__cbegin(void *thisObj);
// QByteArray::cend() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__cend(void *thisObj);
// QByteArray::chop(int n)
KDDockWidgetsBindings_EXPORT void c_QByteArray__chop_int(void *thisObj, int n);
// QByteArray::chopped(int len) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__chopped_int(void *thisObj, int len);
// QByteArray::clear()
KDDockWidgetsBindings_EXPORT void c_QByteArray__clear(void *thisObj);
// QByteArray::compare(const QByteArray & a) const
KDDockWidgetsBindings_EXPORT int c_QByteArray__compare_QByteArray(void *thisObj, void *a_);
// QByteArray::compare(const char * c) const
KDDockWidgetsBindings_EXPORT int c_QByteArray__compare_char(void *thisObj, const char *c);
// QByteArray::constBegin() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__constBegin(void *thisObj);
// QByteArray::constData() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__constData(void *thisObj);
// QByteArray::constEnd() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__constEnd(void *thisObj);
// QByteArray::contains(const QByteArray & a) const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__contains_QByteArray(void *thisObj, void *a_);
// QByteArray::contains(const char * a) const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__contains_char(void *thisObj, const char *a);
// QByteArray::count() const
KDDockWidgetsBindings_EXPORT int c_QByteArray__count(void *thisObj);
// QByteArray::count(const QByteArray & a) const
KDDockWidgetsBindings_EXPORT int c_QByteArray__count_QByteArray(void *thisObj, void *a_);
// QByteArray::count(const char * a) const
KDDockWidgetsBindings_EXPORT int c_QByteArray__count_char(void *thisObj, const char *a);
// QByteArray::data() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__data(void *thisObj);
// QByteArray::detach()
KDDockWidgetsBindings_EXPORT void c_QByteArray__detach(void *thisObj);
// QByteArray::end() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__end(void *thisObj);
// QByteArray::endsWith(const QByteArray & a) const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__endsWith_QByteArray(void *thisObj, void *a_);
// QByteArray::endsWith(const char * c) const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__endsWith_char(void *thisObj, const char *c);
// QByteArray::fromBase64(const QByteArray & base64)
KDDockWidgetsBindings_EXPORT void *c_static_QByteArray__fromBase64_QByteArray(void *base64_);
// QByteArray::fromHex(const QByteArray & hexEncoded)
KDDockWidgetsBindings_EXPORT void *c_static_QByteArray__fromHex_QByteArray(void *hexEncoded_);
// QByteArray::fromRawData(const char * arg__1, int size)
KDDockWidgetsBindings_EXPORT void *c_static_QByteArray__fromRawData_char_int(const char *arg__1,
                                                                             int size);
// QByteArray::front() const
KDDockWidgetsBindings_EXPORT char c_QByteArray__front(void *thisObj);
// QByteArray::indexOf(const QByteArray & a, int from) const
KDDockWidgetsBindings_EXPORT int c_QByteArray__indexOf_QByteArray_int(void *thisObj, void *a_,
                                                                      int from);
// QByteArray::indexOf(const char * c, int from) const
KDDockWidgetsBindings_EXPORT int c_QByteArray__indexOf_char_int(void *thisObj, const char *c,
                                                                int from);
// QByteArray::insert(int i, const QByteArray & a)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__insert_int_QByteArray(void *thisObj, int i,
                                                                       void *a_);
// QByteArray::insert(int i, const char * s)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__insert_int_char(void *thisObj, int i,
                                                                 const char *s);
// QByteArray::insert(int i, const char * s, int len)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__insert_int_char_int(void *thisObj, int i,
                                                                     const char *s, int len);
// QByteArray::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__isDetached(void *thisObj);
// QByteArray::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__isEmpty(void *thisObj);
// QByteArray::isLower() const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__isLower(void *thisObj);
// QByteArray::isNull() const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__isNull(void *thisObj);
// QByteArray::isSharedWith(const QByteArray & other) const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__isSharedWith_QByteArray(void *thisObj,
                                                                        void *other_);
// QByteArray::isUpper() const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__isUpper(void *thisObj);
// QByteArray::lastIndexOf(const QByteArray & a, int from) const
KDDockWidgetsBindings_EXPORT int c_QByteArray__lastIndexOf_QByteArray_int(void *thisObj, void *a_,
                                                                          int from);
// QByteArray::lastIndexOf(const char * c, int from) const
KDDockWidgetsBindings_EXPORT int c_QByteArray__lastIndexOf_char_int(void *thisObj, const char *c,
                                                                    int from);
// QByteArray::left(int len) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__left_int(void *thisObj, int len);
// QByteArray::length() const
KDDockWidgetsBindings_EXPORT int c_QByteArray__length(void *thisObj);
// QByteArray::mid(int index, int len) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__mid_int_int(void *thisObj, int index, int len);
// QByteArray::number(int arg__1, int base)
KDDockWidgetsBindings_EXPORT void *c_static_QByteArray__number_int_int(int arg__1, int base);
// QByteArray::number(qint64 arg__1, int base)
KDDockWidgetsBindings_EXPORT void *c_static_QByteArray__number_qint64_int(qint64 arg__1, int base);
// QByteArray::prepend(const QByteArray & a)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__prepend_QByteArray(void *thisObj, void *a_);
// QByteArray::prepend(const char * s)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__prepend_char(void *thisObj, const char *s);
// QByteArray::prepend(const char * s, int len)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__prepend_char_int(void *thisObj, const char *s,
                                                                  int len);
// QByteArray::push_back(const QByteArray & a)
KDDockWidgetsBindings_EXPORT void c_QByteArray__push_back_QByteArray(void *thisObj, void *a_);
// QByteArray::push_back(const char * c)
KDDockWidgetsBindings_EXPORT void c_QByteArray__push_back_char(void *thisObj, const char *c);
// QByteArray::push_front(const QByteArray & a)
KDDockWidgetsBindings_EXPORT void c_QByteArray__push_front_QByteArray(void *thisObj, void *a_);
// QByteArray::push_front(const char * c)
KDDockWidgetsBindings_EXPORT void c_QByteArray__push_front_char(void *thisObj, const char *c);
// QByteArray::remove(int index, int len)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__remove_int_int(void *thisObj, int index, int len);
// QByteArray::repeated(int times) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__repeated_int(void *thisObj, int times);
// QByteArray::replace(const QByteArray & before, const QByteArray & after)
KDDockWidgetsBindings_EXPORT void *
c_QByteArray__replace_QByteArray_QByteArray(void *thisObj, void *before_, void *after_);
// QByteArray::replace(const QByteArray & before, const char * after)
KDDockWidgetsBindings_EXPORT void *
c_QByteArray__replace_QByteArray_char(void *thisObj, void *before_, const char *after);
// QByteArray::replace(const char * before, const QByteArray & after)
KDDockWidgetsBindings_EXPORT void *
c_QByteArray__replace_char_QByteArray(void *thisObj, const char *before, void *after_);
// QByteArray::replace(const char * before, const char * after)
KDDockWidgetsBindings_EXPORT void *
c_QByteArray__replace_char_char(void *thisObj, const char *before, const char *after);
// QByteArray::replace(const char * before, int bsize, const char * after, int asize)
KDDockWidgetsBindings_EXPORT void *
c_QByteArray__replace_char_int_char_int(void *thisObj, const char *before, int bsize,
                                        const char *after, int asize);
// QByteArray::replace(int index, int len, const QByteArray & s)
KDDockWidgetsBindings_EXPORT void *
c_QByteArray__replace_int_int_QByteArray(void *thisObj, int index, int len, void *s_);
// QByteArray::replace(int index, int len, const char * s)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__replace_int_int_char(void *thisObj, int index,
                                                                      int len, const char *s);
// QByteArray::replace(int index, int len, const char * s, int alen)
KDDockWidgetsBindings_EXPORT void *
c_QByteArray__replace_int_int_char_int(void *thisObj, int index, int len, const char *s, int alen);
// QByteArray::reserve(int size)
KDDockWidgetsBindings_EXPORT void c_QByteArray__reserve_int(void *thisObj, int size);
// QByteArray::resize(int size)
KDDockWidgetsBindings_EXPORT void c_QByteArray__resize_int(void *thisObj, int size);
// QByteArray::right(int len) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__right_int(void *thisObj, int len);
// QByteArray::setNum(int arg__1, int base)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__setNum_int_int(void *thisObj, int arg__1,
                                                                int base);
// QByteArray::setNum(qint64 arg__1, int base)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__setNum_qint64_int(void *thisObj, qint64 arg__1,
                                                                   int base);
// QByteArray::setNum(short arg__1, int base)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__setNum_short_int(void *thisObj, short arg__1,
                                                                  int base);
// QByteArray::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QByteArray__shrink_to_fit(void *thisObj);
// QByteArray::simplified()
KDDockWidgetsBindings_EXPORT void *c_QByteArray__simplified(void *thisObj);
// QByteArray::size() const
KDDockWidgetsBindings_EXPORT int c_QByteArray__size(void *thisObj);
// QByteArray::squeeze()
KDDockWidgetsBindings_EXPORT void c_QByteArray__squeeze(void *thisObj);
// QByteArray::startsWith(const QByteArray & a) const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__startsWith_QByteArray(void *thisObj, void *a_);
// QByteArray::startsWith(const char * c) const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__startsWith_char(void *thisObj, const char *c);
// QByteArray::toBase64() const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__toBase64(void *thisObj);
// QByteArray::toHex() const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__toHex(void *thisObj);
// QByteArray::toLower()
KDDockWidgetsBindings_EXPORT void *c_QByteArray__toLower(void *thisObj);
// QByteArray::toUpper()
KDDockWidgetsBindings_EXPORT void *c_QByteArray__toUpper(void *thisObj);
// QByteArray::trimmed()
KDDockWidgetsBindings_EXPORT void *c_QByteArray__trimmed(void *thisObj);
// QByteArray::truncate(int pos)
KDDockWidgetsBindings_EXPORT void c_QByteArray__truncate_int(void *thisObj, int pos);
KDDockWidgetsBindings_EXPORT void c_QByteArray__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QByteArray_Finalizer(void *, void *cppObj, void *);
}
