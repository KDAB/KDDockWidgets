/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

//tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <qstring.h>
#include <qbytearray.h>

namespace KDDockWidgetsBindings_wrappersNS {
//tag=1043
class QString_wrapper : public ::QString {public:
~QString_wrapper();
//tag=1041
 QString_wrapper();
//tag=1041
QString & append(const QString & s);
//tag=1041
QString arg(const QString & a,int fieldWidth = 0)const;
//tag=1041
QString arg(const QString & a1,const QString & a2)const;
//tag=1041
QString arg(const QString & a1,const QString & a2,const QString & a3)const;
//tag=1041
QString arg(const QString & a1,const QString & a2,const QString & a3,const QString & a4)const;
//tag=1041
QString arg(const QString & a1,const QString & a2,const QString & a3,const QString & a4,const QString & a5)const;
//tag=1041
QString arg(const QString & a1,const QString & a2,const QString & a3,const QString & a4,const QString & a5,const QString & a6)const;
//tag=1041
QString arg(const QString & a1,const QString & a2,const QString & a3,const QString & a4,const QString & a5,const QString & a6,const QString & a7)const;
//tag=1041
QString arg(const QString & a1,const QString & a2,const QString & a3,const QString & a4,const QString & a5,const QString & a6,const QString & a7,const QString & a8)const;
//tag=1041
QString arg(const QString & a1,const QString & a2,const QString & a3,const QString & a4,const QString & a5,const QString & a6,const QString & a7,const QString & a8,const QString & a9)const;
//tag=1041
QString arg(int a,int fieldWidth = 0,int base = 10)const;
//tag=1041
QString arg(long a,int fieldwidth = 0,int base = 10)const;
//tag=1041
QString arg(qint64 a,int fieldwidth = 0,int base = 10)const;
//tag=1041
QString arg(short a,int fieldWidth = 0,int base = 10)const;
//tag=1041
static QString asprintf(const char * format);
//tag=1041
int capacity()const;
//tag=1041
void chop(int n);
//tag=1041
QString chopped(int n)const;
//tag=1041
void clear();
//tag=1041
int compare(const QString & s)const;
//tag=1041
static int compare(const QString & s1,const QString & s2);
//tag=1041
bool contains(const QString & s)const;
//tag=1041
int count()const;
//tag=1041
int count(const QString & s)const;
//tag=1041
void detach();
//tag=1041
bool endsWith(const QString & s)const;
//tag=1041
static QString fromLatin1(const QByteArray & str);
//tag=1041
static QString fromLatin1(const char * str,int size = -1);
//tag=1041
static QString fromLocal8Bit(const QByteArray & str);
//tag=1041
static QString fromLocal8Bit(const char * str,int size = -1);
//tag=1041
static QString fromUtf8(const QByteArray & str);
//tag=1041
static QString fromUtf8(const char * str,int size = -1);
//tag=1041
int indexOf(const QString & s,int from = 0)const;
//tag=1041
QString & insert(int i,const QString & s);
//tag=1041
bool isDetached()const;
//tag=1041
bool isEmpty()const;
//tag=1041
bool isLower()const;
//tag=1041
bool isNull()const;
//tag=1041
bool isRightToLeft()const;
//tag=1041
bool isSharedWith(const QString & other)const;
//tag=1041
bool isSimpleText()const;
//tag=1041
bool isUpper()const;
//tag=1041
bool isValidUtf16()const;
//tag=1041
int lastIndexOf(const QString & s,int from = -1)const;
//tag=1041
QString left(int n)const;
//tag=1041
QString leftJustified(int width)const;
//tag=1041
int length()const;
//tag=1041
int localeAwareCompare(const QString & s)const;
//tag=1041
static int localeAwareCompare(const QString & s1,const QString & s2);
//tag=1041
QString mid(int position,int n = -1)const;
//tag=1041
static QString number(int arg__1,int base = 10);
//tag=1041
static QString number(long arg__1,int base = 10);
//tag=1041
static QString number(qint64 arg__1,int base = 10);
//tag=1041
QString & prepend(const QString & s);
//tag=1041
void push_back(const QString & s);
//tag=1041
void push_front(const QString & s);
//tag=1041
QString & remove(const QString & s);
//tag=1041
QString & remove(int i,int len);
//tag=1041
QString repeated(int times)const;
//tag=1041
QString & replace(const QString & before,const QString & after);
//tag=1041
QString & replace(int i,int len,const QString & after);
//tag=1041
void reserve(int size);
//tag=1041
void resize(int size);
//tag=1041
QString right(int n)const;
//tag=1041
QString rightJustified(int width)const;
//tag=1041
QString section(const QString & in_sep,int start,int end = -1)const;
//tag=1041
QString & setNum(int arg__1,int base = 10);
//tag=1041
QString & setNum(long arg__1,int base = 10);
//tag=1041
QString & setNum(qint64 arg__1,int base = 10);
//tag=1041
QString & setNum(short arg__1,int base = 10);
//tag=1041
void shrink_to_fit();
//tag=1041
QString simplified();
//tag=1041
int size()const;
//tag=1041
void squeeze();
//tag=1041
bool startsWith(const QString & s)const;
//tag=1041
QString toCaseFolded();
//tag=1041
QString toHtmlEscaped()const;
//tag=1041
QByteArray toLatin1();
//tag=1041
QByteArray toLocal8Bit();
//tag=1041
QString toLower();
//tag=1041
QString toUpper();
//tag=1041
QByteArray toUtf8();
//tag=1041
QString trimmed();
//tag=1041
void truncate(int pos);

};
}extern "C" {

//tag=1067
// QString::QString()
KDDockWidgetsBindings_EXPORT void * c_QString__constructor();

//tag=1067
// QString::append(const QString & s)
KDDockWidgetsBindings_EXPORT void* c_QString__append_QString(void *thisObj,const char *s_);

//tag=1067
// QString::arg(const QString & a, int fieldWidth) const
KDDockWidgetsBindings_EXPORT void* c_QString__arg_QString_int(void *thisObj,const char *a_,int fieldWidth);

//tag=1067
// QString::arg(const QString & a1, const QString & a2) const
KDDockWidgetsBindings_EXPORT void* c_QString__arg_QString_QString(void *thisObj,const char *a1_,const char *a2_);

//tag=1067
// QString::arg(const QString & a1, const QString & a2, const QString & a3) const
KDDockWidgetsBindings_EXPORT void* c_QString__arg_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_);

//tag=1067
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4) const
KDDockWidgetsBindings_EXPORT void* c_QString__arg_QString_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_,const char *a4_);

//tag=1067
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5) const
KDDockWidgetsBindings_EXPORT void* c_QString__arg_QString_QString_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_,const char *a4_,const char *a5_);

//tag=1067
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6) const
KDDockWidgetsBindings_EXPORT void* c_QString__arg_QString_QString_QString_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_,const char *a4_,const char *a5_,const char *a6_);

//tag=1067
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6, const QString & a7) const
KDDockWidgetsBindings_EXPORT void* c_QString__arg_QString_QString_QString_QString_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_,const char *a4_,const char *a5_,const char *a6_,const char *a7_);

//tag=1067
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6, const QString & a7, const QString & a8) const
KDDockWidgetsBindings_EXPORT void* c_QString__arg_QString_QString_QString_QString_QString_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_,const char *a4_,const char *a5_,const char *a6_,const char *a7_,const char *a8_);

//tag=1067
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6, const QString & a7, const QString & a8, const QString & a9) const
KDDockWidgetsBindings_EXPORT void* c_QString__arg_QString_QString_QString_QString_QString_QString_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_,const char *a4_,const char *a5_,const char *a6_,const char *a7_,const char *a8_,const char *a9_);

//tag=1067
// QString::arg(int a, int fieldWidth, int base) const
KDDockWidgetsBindings_EXPORT void* c_QString__arg_int_int_int(void *thisObj,int a,int fieldWidth,int base);

//tag=1067
// QString::arg(long a, int fieldwidth, int base) const
KDDockWidgetsBindings_EXPORT void* c_QString__arg_long_int_int(void *thisObj,long a,int fieldwidth,int base);

//tag=1067
// QString::arg(qint64 a, int fieldwidth, int base) const
KDDockWidgetsBindings_EXPORT void* c_QString__arg_qint64_int_int(void *thisObj,qint64 a,int fieldwidth,int base);

//tag=1067
// QString::arg(short a, int fieldWidth, int base) const
KDDockWidgetsBindings_EXPORT void* c_QString__arg_short_int_int(void *thisObj,short a,int fieldWidth,int base);

//tag=1067
// QString::asprintf(const char * format)
KDDockWidgetsBindings_EXPORT void* c_static_QString__asprintf_char(const char * format);

//tag=1067
// QString::capacity() const
KDDockWidgetsBindings_EXPORT int c_QString__capacity(void *thisObj);

//tag=1067
// QString::chop(int n)
KDDockWidgetsBindings_EXPORT void c_QString__chop_int(void *thisObj,int n);

//tag=1067
// QString::chopped(int n) const
KDDockWidgetsBindings_EXPORT void* c_QString__chopped_int(void *thisObj,int n);

//tag=1067
// QString::clear()
KDDockWidgetsBindings_EXPORT void c_QString__clear(void *thisObj);

//tag=1067
// QString::compare(const QString & s) const
KDDockWidgetsBindings_EXPORT int c_QString__compare_QString(void *thisObj,const char *s_);

//tag=1067
// QString::compare(const QString & s1, const QString & s2)
KDDockWidgetsBindings_EXPORT int c_static_QString__compare_QString_QString(const char *s1_,const char *s2_);

//tag=1067
// QString::contains(const QString & s) const
KDDockWidgetsBindings_EXPORT bool c_QString__contains_QString(void *thisObj,const char *s_);

//tag=1067
// QString::count() const
KDDockWidgetsBindings_EXPORT int c_QString__count(void *thisObj);

//tag=1067
// QString::count(const QString & s) const
KDDockWidgetsBindings_EXPORT int c_QString__count_QString(void *thisObj,const char *s_);

//tag=1067
// QString::detach()
KDDockWidgetsBindings_EXPORT void c_QString__detach(void *thisObj);

//tag=1067
// QString::endsWith(const QString & s) const
KDDockWidgetsBindings_EXPORT bool c_QString__endsWith_QString(void *thisObj,const char *s_);

//tag=1067
// QString::fromLatin1(const QByteArray & str)
KDDockWidgetsBindings_EXPORT void* c_static_QString__fromLatin1_QByteArray(void* str_);

//tag=1067
// QString::fromLatin1(const char * str, int size)
KDDockWidgetsBindings_EXPORT void* c_static_QString__fromLatin1_char_int(const char * str,int size);

//tag=1067
// QString::fromLocal8Bit(const QByteArray & str)
KDDockWidgetsBindings_EXPORT void* c_static_QString__fromLocal8Bit_QByteArray(void* str_);

//tag=1067
// QString::fromLocal8Bit(const char * str, int size)
KDDockWidgetsBindings_EXPORT void* c_static_QString__fromLocal8Bit_char_int(const char * str,int size);

//tag=1067
// QString::fromUtf8(const QByteArray & str)
KDDockWidgetsBindings_EXPORT void* c_static_QString__fromUtf8_QByteArray(void* str_);

//tag=1067
// QString::fromUtf8(const char * str, int size)
KDDockWidgetsBindings_EXPORT void* c_static_QString__fromUtf8_char_int(const char * str,int size);

//tag=1067
// QString::indexOf(const QString & s, int from) const
KDDockWidgetsBindings_EXPORT int c_QString__indexOf_QString_int(void *thisObj,const char *s_,int from);

//tag=1067
// QString::insert(int i, const QString & s)
KDDockWidgetsBindings_EXPORT void* c_QString__insert_int_QString(void *thisObj,int i,const char *s_);

//tag=1067
// QString::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QString__isDetached(void *thisObj);

//tag=1067
// QString::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QString__isEmpty(void *thisObj);

//tag=1067
// QString::isLower() const
KDDockWidgetsBindings_EXPORT bool c_QString__isLower(void *thisObj);

//tag=1067
// QString::isNull() const
KDDockWidgetsBindings_EXPORT bool c_QString__isNull(void *thisObj);

//tag=1067
// QString::isRightToLeft() const
KDDockWidgetsBindings_EXPORT bool c_QString__isRightToLeft(void *thisObj);

//tag=1067
// QString::isSharedWith(const QString & other) const
KDDockWidgetsBindings_EXPORT bool c_QString__isSharedWith_QString(void *thisObj,const char *other_);

//tag=1067
// QString::isSimpleText() const
KDDockWidgetsBindings_EXPORT bool c_QString__isSimpleText(void *thisObj);

//tag=1067
// QString::isUpper() const
KDDockWidgetsBindings_EXPORT bool c_QString__isUpper(void *thisObj);

//tag=1067
// QString::isValidUtf16() const
KDDockWidgetsBindings_EXPORT bool c_QString__isValidUtf16(void *thisObj);

//tag=1067
// QString::lastIndexOf(const QString & s, int from) const
KDDockWidgetsBindings_EXPORT int c_QString__lastIndexOf_QString_int(void *thisObj,const char *s_,int from);

//tag=1067
// QString::left(int n) const
KDDockWidgetsBindings_EXPORT void* c_QString__left_int(void *thisObj,int n);

//tag=1067
// QString::leftJustified(int width) const
KDDockWidgetsBindings_EXPORT void* c_QString__leftJustified_int(void *thisObj,int width);

//tag=1067
// QString::length() const
KDDockWidgetsBindings_EXPORT int c_QString__length(void *thisObj);

//tag=1067
// QString::localeAwareCompare(const QString & s) const
KDDockWidgetsBindings_EXPORT int c_QString__localeAwareCompare_QString(void *thisObj,const char *s_);

//tag=1067
// QString::localeAwareCompare(const QString & s1, const QString & s2)
KDDockWidgetsBindings_EXPORT int c_static_QString__localeAwareCompare_QString_QString(const char *s1_,const char *s2_);

//tag=1067
// QString::mid(int position, int n) const
KDDockWidgetsBindings_EXPORT void* c_QString__mid_int_int(void *thisObj,int position,int n);

//tag=1067
// QString::number(int arg__1, int base)
KDDockWidgetsBindings_EXPORT void* c_static_QString__number_int_int(int arg__1,int base);

//tag=1067
// QString::number(long arg__1, int base)
KDDockWidgetsBindings_EXPORT void* c_static_QString__number_long_int(long arg__1,int base);

//tag=1067
// QString::number(qint64 arg__1, int base)
KDDockWidgetsBindings_EXPORT void* c_static_QString__number_qint64_int(qint64 arg__1,int base);

//tag=1067
// QString::prepend(const QString & s)
KDDockWidgetsBindings_EXPORT void* c_QString__prepend_QString(void *thisObj,const char *s_);

//tag=1067
// QString::push_back(const QString & s)
KDDockWidgetsBindings_EXPORT void c_QString__push_back_QString(void *thisObj,const char *s_);

//tag=1067
// QString::push_front(const QString & s)
KDDockWidgetsBindings_EXPORT void c_QString__push_front_QString(void *thisObj,const char *s_);

//tag=1067
// QString::remove(const QString & s)
KDDockWidgetsBindings_EXPORT void* c_QString__remove_QString(void *thisObj,const char *s_);

//tag=1067
// QString::remove(int i, int len)
KDDockWidgetsBindings_EXPORT void* c_QString__remove_int_int(void *thisObj,int i,int len);

//tag=1067
// QString::repeated(int times) const
KDDockWidgetsBindings_EXPORT void* c_QString__repeated_int(void *thisObj,int times);

//tag=1067
// QString::replace(const QString & before, const QString & after)
KDDockWidgetsBindings_EXPORT void* c_QString__replace_QString_QString(void *thisObj,const char *before_,const char *after_);

//tag=1067
// QString::replace(int i, int len, const QString & after)
KDDockWidgetsBindings_EXPORT void* c_QString__replace_int_int_QString(void *thisObj,int i,int len,const char *after_);

//tag=1067
// QString::reserve(int size)
KDDockWidgetsBindings_EXPORT void c_QString__reserve_int(void *thisObj,int size);

//tag=1067
// QString::resize(int size)
KDDockWidgetsBindings_EXPORT void c_QString__resize_int(void *thisObj,int size);

//tag=1067
// QString::right(int n) const
KDDockWidgetsBindings_EXPORT void* c_QString__right_int(void *thisObj,int n);

//tag=1067
// QString::rightJustified(int width) const
KDDockWidgetsBindings_EXPORT void* c_QString__rightJustified_int(void *thisObj,int width);

//tag=1067
// QString::section(const QString & in_sep, int start, int end) const
KDDockWidgetsBindings_EXPORT void* c_QString__section_QString_int_int(void *thisObj,const char *in_sep_,int start,int end);

//tag=1067
// QString::setNum(int arg__1, int base)
KDDockWidgetsBindings_EXPORT void* c_QString__setNum_int_int(void *thisObj,int arg__1,int base);

//tag=1067
// QString::setNum(long arg__1, int base)
KDDockWidgetsBindings_EXPORT void* c_QString__setNum_long_int(void *thisObj,long arg__1,int base);

//tag=1067
// QString::setNum(qint64 arg__1, int base)
KDDockWidgetsBindings_EXPORT void* c_QString__setNum_qint64_int(void *thisObj,qint64 arg__1,int base);

//tag=1067
// QString::setNum(short arg__1, int base)
KDDockWidgetsBindings_EXPORT void* c_QString__setNum_short_int(void *thisObj,short arg__1,int base);

//tag=1067
// QString::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QString__shrink_to_fit(void *thisObj);

//tag=1067
// QString::simplified()
KDDockWidgetsBindings_EXPORT void* c_QString__simplified(void *thisObj);

//tag=1067
// QString::size() const
KDDockWidgetsBindings_EXPORT int c_QString__size(void *thisObj);

//tag=1067
// QString::squeeze()
KDDockWidgetsBindings_EXPORT void c_QString__squeeze(void *thisObj);

//tag=1067
// QString::startsWith(const QString & s) const
KDDockWidgetsBindings_EXPORT bool c_QString__startsWith_QString(void *thisObj,const char *s_);

//tag=1067
// QString::toCaseFolded()
KDDockWidgetsBindings_EXPORT void* c_QString__toCaseFolded(void *thisObj);

//tag=1067
// QString::toHtmlEscaped() const
KDDockWidgetsBindings_EXPORT void* c_QString__toHtmlEscaped(void *thisObj);

//tag=1067
// QString::toLatin1()
KDDockWidgetsBindings_EXPORT void* c_QString__toLatin1(void *thisObj);

//tag=1067
// QString::toLocal8Bit()
KDDockWidgetsBindings_EXPORT void* c_QString__toLocal8Bit(void *thisObj);

//tag=1067
// QString::toLower()
KDDockWidgetsBindings_EXPORT void* c_QString__toLower(void *thisObj);

//tag=1067
// QString::toUpper()
KDDockWidgetsBindings_EXPORT void* c_QString__toUpper(void *thisObj);

//tag=1067
// QString::toUtf8()
KDDockWidgetsBindings_EXPORT void* c_QString__toUtf8(void *thisObj);

//tag=1067
// QString::trimmed()
KDDockWidgetsBindings_EXPORT void* c_QString__trimmed(void *thisObj);

//tag=1067
// QString::truncate(int pos)
KDDockWidgetsBindings_EXPORT void c_QString__truncate_int(void *thisObj,int pos);

//tag=1066
KDDockWidgetsBindings_EXPORT void c_QString__destructor(void *thisObj);

//tag=1047
KDDockWidgetsBindings_EXPORT  void c_QString_Finalizer(void *, void *cppObj, void *);}
