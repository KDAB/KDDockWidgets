/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <qbytearray.h>

namespace KDDockWidgetsBindings_wrappersNS {
class QByteArray_wrapper : public ::QByteArray
{
public:
    ~QByteArray_wrapper();
    QByteArray_wrapper();
    QByteArray_wrapper(const char *arg__1, qsizetype size = -1);
    QByteArray &append(const QByteArray &a);
    QByteArray &append(const char *s);
    QByteArray &append(const char *s, qsizetype len);
    char at(qsizetype i) const;
    char back() const;
    const char *begin() const;
    qsizetype capacity() const;
    const char *cbegin() const;
    const char *cend() const;
    void chop(qsizetype n);
    QByteArray chopped(qsizetype len) const;
    void clear();
    const char *constBegin() const;
    const char *constData() const;
    const char *constEnd() const;
    const char *data() const;
    void detach();
    const char *end() const;
    QByteArray first(qsizetype n) const;
    static QByteArray fromBase64(const QByteArray &base64);
    static QByteArray fromHex(const QByteArray &hexEncoded);
    static QByteArray fromRawData(const char *data, qsizetype size);
    char front() const;
    QByteArray &insert(qsizetype i, const QByteArray &data);
    QByteArray &insert(qsizetype i, const char *s);
    QByteArray &insert(qsizetype i, const char *s, qsizetype len);
    bool isDetached() const;
    bool isEmpty() const;
    bool isLower() const;
    bool isNull() const;
    bool isSharedWith(const QByteArray &other) const;
    bool isUpper() const;
    bool isValidUtf8() const;
    QByteArray last(qsizetype n) const;
    QByteArray left(qsizetype len) const;
    qsizetype length() const;
    QByteArray mid(qsizetype index, qsizetype len = -1) const;
    static QByteArray number(int arg__1, int base = 10);
    static QByteArray number(long arg__1, int base = 10);
    static QByteArray number(qint64 arg__1, int base = 10);
    QByteArray &prepend(const QByteArray &a);
    QByteArray &prepend(const char *s);
    QByteArray &prepend(const char *s, qsizetype len);
    void push_back(const QByteArray &a);
    void push_back(const char *s);
    void push_front(const QByteArray &a);
    void push_front(const char *c);
    QByteArray &remove(qsizetype index, qsizetype len);
    QByteArray &removeAt(qsizetype pos);
    QByteArray &removeFirst();
    QByteArray &removeLast();
    QByteArray repeated(qsizetype times) const;
    QByteArray &replace(const char *before, qsizetype bsize, const char *after, qsizetype asize);
    QByteArray &replace(qsizetype index, qsizetype len, const char *s, qsizetype alen);
    void reserve(qsizetype size);
    void resize(qsizetype size);
    QByteArray right(qsizetype len) const;
    QByteArray &setNum(int arg__1, int base = 10);
    QByteArray &setNum(long arg__1, int base = 10);
    QByteArray &setNum(qint64 arg__1, int base = 10);
    QByteArray &setNum(short arg__1, int base = 10);
    QByteArray &setRawData(const char *a, qsizetype n);
    void shrink_to_fit();
    QByteArray simplified();
    qsizetype size() const;
    QByteArray sliced(qsizetype pos) const;
    QByteArray sliced(qsizetype pos, qsizetype n) const;
    void squeeze();
    QByteArray toBase64() const;
    QByteArray toLower();
    QByteArray toUpper();
    QByteArray trimmed();
    void truncate(qsizetype pos);
};
}
extern "C" {
// QByteArray::QByteArray()
KDDockWidgetsBindings_EXPORT void *c_QByteArray__constructor();
// QByteArray::QByteArray(const char * arg__1, qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__constructor_char_qsizetype(const char *arg__1, qsizetype size);
// QByteArray::append(const QByteArray & a)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__append_QByteArray(void *thisObj, void *a_);
// QByteArray::append(const char * s)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__append_char(void *thisObj, const char *s);
// QByteArray::append(const char * s, qsizetype len)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__append_char_qsizetype(void *thisObj, const char *s, qsizetype len);
// QByteArray::at(qsizetype i) const
KDDockWidgetsBindings_EXPORT char c_QByteArray__at_qsizetype(void *thisObj, qsizetype i);
// QByteArray::back() const
KDDockWidgetsBindings_EXPORT char c_QByteArray__back(void *thisObj);
// QByteArray::begin() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__begin(void *thisObj);
// QByteArray::capacity() const
KDDockWidgetsBindings_EXPORT qsizetype c_QByteArray__capacity(void *thisObj);
// QByteArray::cbegin() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__cbegin(void *thisObj);
// QByteArray::cend() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__cend(void *thisObj);
// QByteArray::chop(qsizetype n)
KDDockWidgetsBindings_EXPORT void c_QByteArray__chop_qsizetype(void *thisObj, qsizetype n);
// QByteArray::chopped(qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__chopped_qsizetype(void *thisObj, qsizetype len);
// QByteArray::clear()
KDDockWidgetsBindings_EXPORT void c_QByteArray__clear(void *thisObj);
// QByteArray::constBegin() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__constBegin(void *thisObj);
// QByteArray::constData() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__constData(void *thisObj);
// QByteArray::constEnd() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__constEnd(void *thisObj);
// QByteArray::data() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__data(void *thisObj);
// QByteArray::detach()
KDDockWidgetsBindings_EXPORT void c_QByteArray__detach(void *thisObj);
// QByteArray::end() const
KDDockWidgetsBindings_EXPORT const char *c_QByteArray__end(void *thisObj);
// QByteArray::first(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__first_qsizetype(void *thisObj, qsizetype n);
// QByteArray::fromBase64(const QByteArray & base64)
KDDockWidgetsBindings_EXPORT void *c_static_QByteArray__fromBase64_QByteArray(void *base64_);
// QByteArray::fromHex(const QByteArray & hexEncoded)
KDDockWidgetsBindings_EXPORT void *c_static_QByteArray__fromHex_QByteArray(void *hexEncoded_);
// QByteArray::fromRawData(const char * data, qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_static_QByteArray__fromRawData_char_qsizetype(const char *data, qsizetype size);
// QByteArray::front() const
KDDockWidgetsBindings_EXPORT char c_QByteArray__front(void *thisObj);
// QByteArray::insert(qsizetype i, const QByteArray & data)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__insert_qsizetype_QByteArray(void *thisObj, qsizetype i, void *data_);
// QByteArray::insert(qsizetype i, const char * s)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__insert_qsizetype_char(void *thisObj, qsizetype i, const char *s);
// QByteArray::insert(qsizetype i, const char * s, qsizetype len)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__insert_qsizetype_char_qsizetype(void *thisObj, qsizetype i, const char *s, qsizetype len);
// QByteArray::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__isDetached(void *thisObj);
// QByteArray::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__isEmpty(void *thisObj);
// QByteArray::isLower() const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__isLower(void *thisObj);
// QByteArray::isNull() const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__isNull(void *thisObj);
// QByteArray::isSharedWith(const QByteArray & other) const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__isSharedWith_QByteArray(void *thisObj, void *other_);
// QByteArray::isUpper() const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__isUpper(void *thisObj);
// QByteArray::isValidUtf8() const
KDDockWidgetsBindings_EXPORT bool c_QByteArray__isValidUtf8(void *thisObj);
// QByteArray::last(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__last_qsizetype(void *thisObj, qsizetype n);
// QByteArray::left(qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__left_qsizetype(void *thisObj, qsizetype len);
// QByteArray::length() const
KDDockWidgetsBindings_EXPORT qsizetype c_QByteArray__length(void *thisObj);
// QByteArray::mid(qsizetype index, qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__mid_qsizetype_qsizetype(void *thisObj, qsizetype index, qsizetype len);
// QByteArray::number(int arg__1, int base)
KDDockWidgetsBindings_EXPORT void *c_static_QByteArray__number_int_int(int arg__1, int base);
// QByteArray::number(long arg__1, int base)
KDDockWidgetsBindings_EXPORT void *c_static_QByteArray__number_long_int(long arg__1, int base);
// QByteArray::number(qint64 arg__1, int base)
KDDockWidgetsBindings_EXPORT void *c_static_QByteArray__number_qint64_int(qint64 arg__1, int base);
// QByteArray::prepend(const QByteArray & a)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__prepend_QByteArray(void *thisObj, void *a_);
// QByteArray::prepend(const char * s)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__prepend_char(void *thisObj, const char *s);
// QByteArray::prepend(const char * s, qsizetype len)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__prepend_char_qsizetype(void *thisObj, const char *s, qsizetype len);
// QByteArray::push_back(const QByteArray & a)
KDDockWidgetsBindings_EXPORT void c_QByteArray__push_back_QByteArray(void *thisObj, void *a_);
// QByteArray::push_back(const char * s)
KDDockWidgetsBindings_EXPORT void c_QByteArray__push_back_char(void *thisObj, const char *s);
// QByteArray::push_front(const QByteArray & a)
KDDockWidgetsBindings_EXPORT void c_QByteArray__push_front_QByteArray(void *thisObj, void *a_);
// QByteArray::push_front(const char * c)
KDDockWidgetsBindings_EXPORT void c_QByteArray__push_front_char(void *thisObj, const char *c);
// QByteArray::remove(qsizetype index, qsizetype len)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__remove_qsizetype_qsizetype(void *thisObj, qsizetype index, qsizetype len);
// QByteArray::removeAt(qsizetype pos)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__removeAt_qsizetype(void *thisObj, qsizetype pos);
// QByteArray::removeFirst()
KDDockWidgetsBindings_EXPORT void *c_QByteArray__removeFirst(void *thisObj);
// QByteArray::removeLast()
KDDockWidgetsBindings_EXPORT void *c_QByteArray__removeLast(void *thisObj);
// QByteArray::repeated(qsizetype times) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__repeated_qsizetype(void *thisObj, qsizetype times);
// QByteArray::replace(const char * before, qsizetype bsize, const char * after, qsizetype asize)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__replace_char_qsizetype_char_qsizetype(void *thisObj, const char *before, qsizetype bsize, const char *after, qsizetype asize);
// QByteArray::replace(qsizetype index, qsizetype len, const char * s, qsizetype alen)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__replace_qsizetype_qsizetype_char_qsizetype(void *thisObj, qsizetype index, qsizetype len, const char *s, qsizetype alen);
// QByteArray::reserve(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QByteArray__reserve_qsizetype(void *thisObj, qsizetype size);
// QByteArray::resize(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QByteArray__resize_qsizetype(void *thisObj, qsizetype size);
// QByteArray::right(qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__right_qsizetype(void *thisObj, qsizetype len);
// QByteArray::setNum(int arg__1, int base)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__setNum_int_int(void *thisObj, int arg__1, int base);
// QByteArray::setNum(long arg__1, int base)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__setNum_long_int(void *thisObj, long arg__1, int base);
// QByteArray::setNum(qint64 arg__1, int base)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__setNum_qint64_int(void *thisObj, qint64 arg__1, int base);
// QByteArray::setNum(short arg__1, int base)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__setNum_short_int(void *thisObj, short arg__1, int base);
// QByteArray::setRawData(const char * a, qsizetype n)
KDDockWidgetsBindings_EXPORT void *c_QByteArray__setRawData_char_qsizetype(void *thisObj, const char *a, qsizetype n);
// QByteArray::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QByteArray__shrink_to_fit(void *thisObj);
// QByteArray::simplified()
KDDockWidgetsBindings_EXPORT void *c_QByteArray__simplified(void *thisObj);
// QByteArray::size() const
KDDockWidgetsBindings_EXPORT qsizetype c_QByteArray__size(void *thisObj);
// QByteArray::sliced(qsizetype pos) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__sliced_qsizetype(void *thisObj, qsizetype pos);
// QByteArray::sliced(qsizetype pos, qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n);
// QByteArray::squeeze()
KDDockWidgetsBindings_EXPORT void c_QByteArray__squeeze(void *thisObj);
// QByteArray::toBase64() const
KDDockWidgetsBindings_EXPORT void *c_QByteArray__toBase64(void *thisObj);
// QByteArray::toLower()
KDDockWidgetsBindings_EXPORT void *c_QByteArray__toLower(void *thisObj);
// QByteArray::toUpper()
KDDockWidgetsBindings_EXPORT void *c_QByteArray__toUpper(void *thisObj);
// QByteArray::trimmed()
KDDockWidgetsBindings_EXPORT void *c_QByteArray__trimmed(void *thisObj);
// QByteArray::truncate(qsizetype pos)
KDDockWidgetsBindings_EXPORT void c_QByteArray__truncate_qsizetype(void *thisObj, qsizetype pos);
KDDockWidgetsBindings_EXPORT void c_QByteArray__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QByteArray_Finalizer(void *cppObj);
}
