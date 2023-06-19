/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include <stdbool.h>
#include <QtCore/qglobal.h>

void c_Qt_Finalizer(void *cppObj); // QString::QString()
void *c_QString__constructor();
// QString::append(const QString & s)
void *c_QString__append_QString(void *thisObj, const char *s_);
// QString::arg(const QString & a, int fieldWidth) const
void *c_QString__arg_QString_int(void *thisObj, const char *a_, int fieldWidth);
// QString::arg(const QString & a1, const QString & a2) const
void *c_QString__arg_QString_QString(void *thisObj, const char *a1_, const char *a2_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3) const
void *c_QString__arg_QString_QString_QString(void *thisObj, const char *a1_, const char *a2_, const char *a3_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4) const
void *c_QString__arg_QString_QString_QString_QString(void *thisObj, const char *a1_, const char *a2_, const char *a3_, const char *a4_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5) const
void *c_QString__arg_QString_QString_QString_QString_QString(void *thisObj, const char *a1_, const char *a2_, const char *a3_, const char *a4_, const char *a5_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6) const
void *c_QString__arg_QString_QString_QString_QString_QString_QString(void *thisObj, const char *a1_, const char *a2_, const char *a3_, const char *a4_, const char *a5_, const char *a6_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6, const QString & a7) const
void *c_QString__arg_QString_QString_QString_QString_QString_QString_QString(void *thisObj, const char *a1_, const char *a2_, const char *a3_, const char *a4_, const char *a5_, const char *a6_, const char *a7_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6, const QString & a7, const QString & a8) const
void *c_QString__arg_QString_QString_QString_QString_QString_QString_QString_QString(void *thisObj, const char *a1_, const char *a2_, const char *a3_, const char *a4_, const char *a5_, const char *a6_, const char *a7_, const char *a8_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6, const QString & a7, const QString & a8, const QString & a9) const
void *c_QString__arg_QString_QString_QString_QString_QString_QString_QString_QString_QString(void *thisObj, const char *a1_, const char *a2_, const char *a3_, const char *a4_, const char *a5_, const char *a6_, const char *a7_, const char *a8_, const char *a9_);
// QString::arg(int a, int fieldWidth, int base) const
void *c_QString__arg_int_int_int(void *thisObj, int a, int fieldWidth, int base);
// QString::arg(long a, int fieldwidth, int base) const
void *c_QString__arg_long_int_int(void *thisObj, long a, int fieldwidth, int base);
// QString::arg(qint64 a, int fieldwidth, int base) const
void *c_QString__arg_qint64_int_int(void *thisObj, qint64 a, int fieldwidth, int base);
// QString::arg(short a, int fieldWidth, int base) const
void *c_QString__arg_short_int_int(void *thisObj, short a, int fieldWidth, int base);
// QString::asprintf(const char * format)
void *c_static_QString__asprintf_char(const char *format);
// QString::capacity() const
int c_QString__capacity(void *thisObj);
// QString::chop(int n)
void c_QString__chop_int(void *thisObj, int n);
// QString::chopped(int n) const
void *c_QString__chopped_int(void *thisObj, int n);
// QString::clear()
void c_QString__clear(void *thisObj);
// QString::compare(const QString & s) const
int c_QString__compare_QString(void *thisObj, const char *s_);
// QString::compare(const QString & s1, const QString & s2)
int c_static_QString__compare_QString_QString(const char *s1_, const char *s2_);
// QString::contains(const QString & s) const
bool c_QString__contains_QString(void *thisObj, const char *s_);
// QString::count() const
int c_QString__count(void *thisObj);
// QString::count(const QString & s) const
int c_QString__count_QString(void *thisObj, const char *s_);
// QString::detach()
void c_QString__detach(void *thisObj);
// QString::endsWith(const QString & s) const
bool c_QString__endsWith_QString(void *thisObj, const char *s_);
// QString::fromLatin1(const QByteArray & str)
void *c_static_QString__fromLatin1_QByteArray(void *str_);
// QString::fromLatin1(const char * str, int size)
void *c_static_QString__fromLatin1_char_int(const char *str, int size);
// QString::fromLocal8Bit(const QByteArray & str)
void *c_static_QString__fromLocal8Bit_QByteArray(void *str_);
// QString::fromLocal8Bit(const char * str, int size)
void *c_static_QString__fromLocal8Bit_char_int(const char *str, int size);
// QString::fromUtf8(const QByteArray & str)
void *c_static_QString__fromUtf8_QByteArray(void *str_);
// QString::fromUtf8(const char * str, int size)
void *c_static_QString__fromUtf8_char_int(const char *str, int size);
// QString::indexOf(const QString & s, int from) const
int c_QString__indexOf_QString_int(void *thisObj, const char *s_, int from);
// QString::insert(int i, const QString & s)
void *c_QString__insert_int_QString(void *thisObj, int i, const char *s_);
// QString::isDetached() const
bool c_QString__isDetached(void *thisObj);
// QString::isEmpty() const
bool c_QString__isEmpty(void *thisObj);
// QString::isLower() const
bool c_QString__isLower(void *thisObj);
// QString::isNull() const
bool c_QString__isNull(void *thisObj);
// QString::isRightToLeft() const
bool c_QString__isRightToLeft(void *thisObj);
// QString::isSharedWith(const QString & other) const
bool c_QString__isSharedWith_QString(void *thisObj, const char *other_);
// QString::isSimpleText() const
bool c_QString__isSimpleText(void *thisObj);
// QString::isUpper() const
bool c_QString__isUpper(void *thisObj);
// QString::isValidUtf16() const
bool c_QString__isValidUtf16(void *thisObj);
// QString::lastIndexOf(const QString & s, int from) const
int c_QString__lastIndexOf_QString_int(void *thisObj, const char *s_, int from);
// QString::left(int n) const
void *c_QString__left_int(void *thisObj, int n);
// QString::leftJustified(int width) const
void *c_QString__leftJustified_int(void *thisObj, int width);
// QString::length() const
int c_QString__length(void *thisObj);
// QString::localeAwareCompare(const QString & s) const
int c_QString__localeAwareCompare_QString(void *thisObj, const char *s_);
// QString::localeAwareCompare(const QString & s1, const QString & s2)
int c_static_QString__localeAwareCompare_QString_QString(const char *s1_, const char *s2_);
// QString::mid(int position, int n) const
void *c_QString__mid_int_int(void *thisObj, int position, int n);
// QString::number(int arg__1, int base)
void *c_static_QString__number_int_int(int arg__1, int base);
// QString::number(long arg__1, int base)
void *c_static_QString__number_long_int(long arg__1, int base);
// QString::number(qint64 arg__1, int base)
void *c_static_QString__number_qint64_int(qint64 arg__1, int base);
// QString::prepend(const QString & s)
void *c_QString__prepend_QString(void *thisObj, const char *s_);
// QString::push_back(const QString & s)
void c_QString__push_back_QString(void *thisObj, const char *s_);
// QString::push_front(const QString & s)
void c_QString__push_front_QString(void *thisObj, const char *s_);
// QString::remove(const QString & s)
void *c_QString__remove_QString(void *thisObj, const char *s_);
// QString::remove(int i, int len)
void *c_QString__remove_int_int(void *thisObj, int i, int len);
// QString::repeated(int times) const
void *c_QString__repeated_int(void *thisObj, int times);
// QString::replace(const QString & before, const QString & after)
void *c_QString__replace_QString_QString(void *thisObj, const char *before_, const char *after_);
// QString::replace(int i, int len, const QString & after)
void *c_QString__replace_int_int_QString(void *thisObj, int i, int len, const char *after_);
// QString::reserve(int size)
void c_QString__reserve_int(void *thisObj, int size);
// QString::resize(int size)
void c_QString__resize_int(void *thisObj, int size);
// QString::right(int n) const
void *c_QString__right_int(void *thisObj, int n);
// QString::rightJustified(int width) const
void *c_QString__rightJustified_int(void *thisObj, int width);
// QString::section(const QString & in_sep, int start, int end) const
void *c_QString__section_QString_int_int(void *thisObj, const char *in_sep_, int start, int end);
// QString::setNum(int arg__1, int base)
void *c_QString__setNum_int_int(void *thisObj, int arg__1, int base);
// QString::setNum(long arg__1, int base)
void *c_QString__setNum_long_int(void *thisObj, long arg__1, int base);
// QString::setNum(qint64 arg__1, int base)
void *c_QString__setNum_qint64_int(void *thisObj, qint64 arg__1, int base);
// QString::setNum(short arg__1, int base)
void *c_QString__setNum_short_int(void *thisObj, short arg__1, int base);
// QString::shrink_to_fit()
void c_QString__shrink_to_fit(void *thisObj);
// QString::simplified()
void *c_QString__simplified(void *thisObj);
// QString::size() const
int c_QString__size(void *thisObj);
// QString::squeeze()
void c_QString__squeeze(void *thisObj);
// QString::startsWith(const QString & s) const
bool c_QString__startsWith_QString(void *thisObj, const char *s_);
// QString::toCaseFolded()
void *c_QString__toCaseFolded(void *thisObj);
// QString::toHtmlEscaped() const
void *c_QString__toHtmlEscaped(void *thisObj);
// QString::toLatin1()
void *c_QString__toLatin1(void *thisObj);
// QString::toLocal8Bit()
void *c_QString__toLocal8Bit(void *thisObj);
// QString::toLower()
void *c_QString__toLower(void *thisObj);
// QString::toUpper()
void *c_QString__toUpper(void *thisObj);
// QString::toUtf8()
void *c_QString__toUtf8(void *thisObj);
// QString::trimmed()
void *c_QString__trimmed(void *thisObj);
// QString::truncate(int pos)
void c_QString__truncate_int(void *thisObj, int pos);
void c_QString__destructor(void *thisObj);
void c_QString_Finalizer(void *cppObj); // QSize::QSize()
void *c_QSize__constructor();
// QSize::QSize(int w, int h)
void *c_QSize__constructor_int_int(int w, int h);
// QSize::boundedTo(const QSize & arg__1) const
void *c_QSize__boundedTo_QSize(void *thisObj, void *arg__1_);
// QSize::expandedTo(const QSize & arg__1) const
void *c_QSize__expandedTo_QSize(void *thisObj, void *arg__1_);
// QSize::height() const
int c_QSize__height(void *thisObj);
// QSize::isEmpty() const
bool c_QSize__isEmpty(void *thisObj);
// QSize::isNull() const
bool c_QSize__isNull(void *thisObj);
// QSize::isValid() const
bool c_QSize__isValid(void *thisObj);
// QSize::setHeight(int h)
void c_QSize__setHeight_int(void *thisObj, int h);
// QSize::setWidth(int w)
void c_QSize__setWidth_int(void *thisObj, int w);
// QSize::transpose()
void c_QSize__transpose(void *thisObj);
// QSize::transposed() const
void *c_QSize__transposed(void *thisObj);
// QSize::width() const
int c_QSize__width(void *thisObj);
void c_QSize__destructor(void *thisObj);
void c_QSize_Finalizer(void *cppObj); // QRect::QRect()
void *c_QRect__constructor();
// QRect::QRect(const QPoint & topleft, const QPoint & bottomright)
void *c_QRect__constructor_QPoint_QPoint(void *topleft_, void *bottomright_);
// QRect::QRect(const QPoint & topleft, const QSize & size)
void *c_QRect__constructor_QPoint_QSize(void *topleft_, void *size_);
// QRect::QRect(int left, int top, int width, int height)
void *c_QRect__constructor_int_int_int_int(int left, int top, int width, int height);
// QRect::adjust(int x1, int y1, int x2, int y2)
void c_QRect__adjust_int_int_int_int(void *thisObj, int x1, int y1, int x2, int y2);
// QRect::adjusted(int x1, int y1, int x2, int y2) const
void *c_QRect__adjusted_int_int_int_int(void *thisObj, int x1, int y1, int x2, int y2);
// QRect::bottom() const
int c_QRect__bottom(void *thisObj);
// QRect::bottomLeft() const
void *c_QRect__bottomLeft(void *thisObj);
// QRect::bottomRight() const
void *c_QRect__bottomRight(void *thisObj);
// QRect::center() const
void *c_QRect__center(void *thisObj);
// QRect::contains(const QPoint & p, bool proper) const
bool c_QRect__contains_QPoint_bool(void *thisObj, void *p_, bool proper);
// QRect::contains(const QRect & r, bool proper) const
bool c_QRect__contains_QRect_bool(void *thisObj, void *r_, bool proper);
// QRect::contains(int x, int y) const
bool c_QRect__contains_int_int(void *thisObj, int x, int y);
// QRect::contains(int x, int y, bool proper) const
bool c_QRect__contains_int_int_bool(void *thisObj, int x, int y, bool proper);
// QRect::height() const
int c_QRect__height(void *thisObj);
// QRect::intersected(const QRect & other) const
void *c_QRect__intersected_QRect(void *thisObj, void *other_);
// QRect::intersects(const QRect & r) const
bool c_QRect__intersects_QRect(void *thisObj, void *r_);
// QRect::isEmpty() const
bool c_QRect__isEmpty(void *thisObj);
// QRect::isNull() const
bool c_QRect__isNull(void *thisObj);
// QRect::isValid() const
bool c_QRect__isValid(void *thisObj);
// QRect::left() const
int c_QRect__left(void *thisObj);
// QRect::moveBottom(int pos)
void c_QRect__moveBottom_int(void *thisObj, int pos);
// QRect::moveBottomLeft(const QPoint & p)
void c_QRect__moveBottomLeft_QPoint(void *thisObj, void *p_);
// QRect::moveBottomRight(const QPoint & p)
void c_QRect__moveBottomRight_QPoint(void *thisObj, void *p_);
// QRect::moveCenter(const QPoint & p)
void c_QRect__moveCenter_QPoint(void *thisObj, void *p_);
// QRect::moveLeft(int pos)
void c_QRect__moveLeft_int(void *thisObj, int pos);
// QRect::moveRight(int pos)
void c_QRect__moveRight_int(void *thisObj, int pos);
// QRect::moveTo(const QPoint & p)
void c_QRect__moveTo_QPoint(void *thisObj, void *p_);
// QRect::moveTo(int x, int t)
void c_QRect__moveTo_int_int(void *thisObj, int x, int t);
// QRect::moveTop(int pos)
void c_QRect__moveTop_int(void *thisObj, int pos);
// QRect::moveTopLeft(const QPoint & p)
void c_QRect__moveTopLeft_QPoint(void *thisObj, void *p_);
// QRect::moveTopRight(const QPoint & p)
void c_QRect__moveTopRight_QPoint(void *thisObj, void *p_);
// QRect::normalized() const
void *c_QRect__normalized(void *thisObj);
// QRect::right() const
int c_QRect__right(void *thisObj);
// QRect::setBottom(int pos)
void c_QRect__setBottom_int(void *thisObj, int pos);
// QRect::setBottomLeft(const QPoint & p)
void c_QRect__setBottomLeft_QPoint(void *thisObj, void *p_);
// QRect::setBottomRight(const QPoint & p)
void c_QRect__setBottomRight_QPoint(void *thisObj, void *p_);
// QRect::setCoords(int x1, int y1, int x2, int y2)
void c_QRect__setCoords_int_int_int_int(void *thisObj, int x1, int y1, int x2, int y2);
// QRect::setHeight(int h)
void c_QRect__setHeight_int(void *thisObj, int h);
// QRect::setLeft(int pos)
void c_QRect__setLeft_int(void *thisObj, int pos);
// QRect::setRect(int x, int y, int w, int h)
void c_QRect__setRect_int_int_int_int(void *thisObj, int x, int y, int w, int h);
// QRect::setRight(int pos)
void c_QRect__setRight_int(void *thisObj, int pos);
// QRect::setSize(const QSize & s)
void c_QRect__setSize_QSize(void *thisObj, void *s_);
// QRect::setTop(int pos)
void c_QRect__setTop_int(void *thisObj, int pos);
// QRect::setTopLeft(const QPoint & p)
void c_QRect__setTopLeft_QPoint(void *thisObj, void *p_);
// QRect::setTopRight(const QPoint & p)
void c_QRect__setTopRight_QPoint(void *thisObj, void *p_);
// QRect::setWidth(int w)
void c_QRect__setWidth_int(void *thisObj, int w);
// QRect::setX(int x)
void c_QRect__setX_int(void *thisObj, int x);
// QRect::setY(int y)
void c_QRect__setY_int(void *thisObj, int y);
// QRect::size() const
void *c_QRect__size(void *thisObj);
// QRect::top() const
int c_QRect__top(void *thisObj);
// QRect::topLeft() const
void *c_QRect__topLeft(void *thisObj);
// QRect::topRight() const
void *c_QRect__topRight(void *thisObj);
// QRect::translate(const QPoint & p)
void c_QRect__translate_QPoint(void *thisObj, void *p_);
// QRect::translate(int dx, int dy)
void c_QRect__translate_int_int(void *thisObj, int dx, int dy);
// QRect::translated(const QPoint & p) const
void *c_QRect__translated_QPoint(void *thisObj, void *p_);
// QRect::translated(int dx, int dy) const
void *c_QRect__translated_int_int(void *thisObj, int dx, int dy);
// QRect::transposed() const
void *c_QRect__transposed(void *thisObj);
// QRect::united(const QRect & other) const
void *c_QRect__united_QRect(void *thisObj, void *other_);
// QRect::width() const
int c_QRect__width(void *thisObj);
// QRect::x() const
int c_QRect__x(void *thisObj);
// QRect::y() const
int c_QRect__y(void *thisObj);
void c_QRect__destructor(void *thisObj);
void c_QRect_Finalizer(void *cppObj); // QPoint::QPoint()
void *c_QPoint__constructor();
// QPoint::QPoint(int xpos, int ypos)
void *c_QPoint__constructor_int_int(int xpos, int ypos);
// QPoint::dotProduct(const QPoint & p1, const QPoint & p2)
int c_static_QPoint__dotProduct_QPoint_QPoint(void *p1_, void *p2_);
// QPoint::isNull() const
bool c_QPoint__isNull(void *thisObj);
// QPoint::manhattanLength() const
int c_QPoint__manhattanLength(void *thisObj);
// QPoint::setX(int x)
void c_QPoint__setX_int(void *thisObj, int x);
// QPoint::setY(int y)
void c_QPoint__setY_int(void *thisObj, int y);
// QPoint::transposed() const
void *c_QPoint__transposed(void *thisObj);
// QPoint::x() const
int c_QPoint__x(void *thisObj);
// QPoint::y() const
int c_QPoint__y(void *thisObj);
void c_QPoint__destructor(void *thisObj);
void c_QPoint_Finalizer(void *cppObj); // QObject::QObject(QObject * parent)
void *c_QObject__constructor_QObject(void *parent_);
// QObject::blockSignals(bool b)
bool c_QObject__blockSignals_bool(void *thisObj, bool b);
// QObject::children() const
void *c_QObject__children(void *thisObj);
// QObject::deleteLater()
void c_QObject__deleteLater(void *thisObj);
// QObject::destroyed(QObject * arg__1)
void c_QObject__destroyed_QObject(void *thisObj, void *arg__1_);
// QObject::disconnect(const QObject * receiver, const char * member) const
bool c_QObject__disconnect_QObject_char(void *thisObj, void *receiver_, const char *member);
// QObject::disconnect(const QObject * sender, const char * signal, const QObject * receiver, const char * member)
bool c_static_QObject__disconnect_QObject_char_QObject_char(void *sender_, const char *signal, void *receiver_, const char *member);
// QObject::disconnect(const char * signal, const QObject * receiver, const char * member) const
bool c_QObject__disconnect_char_QObject_char(void *thisObj, const char *signal, void *receiver_, const char *member);
// QObject::dumpObjectInfo()
void c_QObject__dumpObjectInfo(void *thisObj);
// QObject::dumpObjectTree()
void c_QObject__dumpObjectTree(void *thisObj);
// QObject::dynamicPropertyNames() const
void *c_QObject__dynamicPropertyNames(void *thisObj);
// QObject::inherits(const char * classname) const
bool c_QObject__inherits_char(void *thisObj, const char *classname);
// QObject::installEventFilter(QObject * filterObj)
void c_QObject__installEventFilter_QObject(void *thisObj, void *filterObj_);
// QObject::isWidgetType() const
bool c_QObject__isWidgetType(void *thisObj);
// QObject::isWindowType() const
bool c_QObject__isWindowType(void *thisObj);
// QObject::killTimer(int id)
void c_QObject__killTimer_int(void *thisObj, int id);
// QObject::objectName() const
void *c_QObject__objectName(void *thisObj);
// QObject::parent() const
void *c_QObject__parent(void *thisObj);
// QObject::receivers(const char * signal) const
int c_QObject__receivers_char(void *thisObj, const char *signal);
// QObject::removeEventFilter(QObject * obj)
void c_QObject__removeEventFilter_QObject(void *thisObj, void *obj_);
// QObject::sender() const
void *c_QObject__sender(void *thisObj);
// QObject::senderSignalIndex() const
int c_QObject__senderSignalIndex(void *thisObj);
// QObject::setObjectName(const QString & name)
void c_QObject__setObjectName_QString(void *thisObj, const char *name_);
// QObject::setParent(QObject * parent)
void c_QObject__setParent_QObject(void *thisObj, void *parent_);
// QObject::signalsBlocked() const
bool c_QObject__signalsBlocked(void *thisObj);
// QObject::startTimer(int interval)
int c_QObject__startTimer_int(void *thisObj, int interval);
// QObject::tr(const char * s, const char * c, int n)
void *c_static_QObject__tr_char_char_int(const char *s, const char *c, int n);
void c_QObject__destructor(void *thisObj);
void c_QObject__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_QObject_Finalizer(void *cppObj); // QList::QList<T>()
void *c_QList_T_QObject_T___constructor();
// QList::append(const QList<T > & t)
void c_QList_T_QObject_T___append_QList_T(void *thisObj, void *t_);
// QList::append(const T & t)
void c_QList_T_QObject_T___append_QObject(void *thisObj, void *t_);
// QList::at(int i) const
const void *c_QList_T_QObject_T___at_int(void *thisObj, int i);
// QList::back()
void *c_QList_T_QObject_T___back(void *thisObj);
// QList::clear()
void c_QList_T_QObject_T___clear(void *thisObj);
// QList::constFirst() const
const void *c_QList_T_QObject_T___constFirst(void *thisObj);
// QList::constLast() const
const void *c_QList_T_QObject_T___constLast(void *thisObj);
// QList::contains(const T & t) const
bool c_QList_T_QObject_T___contains_QObject(void *thisObj, void *t_);
// QList::count() const
int c_QList_T_QObject_T___count(void *thisObj);
// QList::count(const T & t) const
int c_QList_T_QObject_T___count_QObject(void *thisObj, void *t_);
// QList::detach()
void c_QList_T_QObject_T___detach(void *thisObj);
// QList::detachShared()
void c_QList_T_QObject_T___detachShared(void *thisObj);
// QList::empty() const
bool c_QList_T_QObject_T___empty(void *thisObj);
// QList::endsWith(const T & t) const
bool c_QList_T_QObject_T___endsWith_QObject(void *thisObj, void *t_);
// QList::first()
void *c_QList_T_QObject_T___first(void *thisObj);
// QList::front()
void *c_QList_T_QObject_T___front(void *thisObj);
// QList::indexOf(const T & t, int from) const
int c_QList_T_QObject_T___indexOf_QObject_int(void *thisObj, void *t_, int from);
// QList::insert(int i, const T & t)
void c_QList_T_QObject_T___insert_int_QObject(void *thisObj, int i, void *t_);
// QList::isDetached() const
bool c_QList_T_QObject_T___isDetached(void *thisObj);
// QList::isEmpty() const
bool c_QList_T_QObject_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
bool c_QList_T_QObject_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
void *c_QList_T_QObject_T___last(void *thisObj);
// QList::lastIndexOf(const T & t, int from) const
int c_QList_T_QObject_T___lastIndexOf_QObject_int(void *thisObj, void *t_, int from);
// QList::length() const
int c_QList_T_QObject_T___length(void *thisObj);
// QList::mid(int pos, int length) const
void *c_QList_T_QObject_T___mid_int_int(void *thisObj, int pos, int length);
// QList::move(int from, int to)
void c_QList_T_QObject_T___move_int_int(void *thisObj, int from, int to);
// QList::pop_back()
void c_QList_T_QObject_T___pop_back(void *thisObj);
// QList::pop_front()
void c_QList_T_QObject_T___pop_front(void *thisObj);
// QList::prepend(const T & t)
void c_QList_T_QObject_T___prepend_QObject(void *thisObj, void *t_);
// QList::push_back(const T & t)
void c_QList_T_QObject_T___push_back_QObject(void *thisObj, void *t_);
// QList::push_front(const T & t)
void c_QList_T_QObject_T___push_front_QObject(void *thisObj, void *t_);
// QList::removeAll(const T & t)
int c_QList_T_QObject_T___removeAll_QObject(void *thisObj, void *t_);
// QList::removeAt(int i)
void c_QList_T_QObject_T___removeAt_int(void *thisObj, int i);
// QList::removeFirst()
void c_QList_T_QObject_T___removeFirst(void *thisObj);
// QList::removeLast()
void c_QList_T_QObject_T___removeLast(void *thisObj);
// QList::removeOne(const T & t)
bool c_QList_T_QObject_T___removeOne_QObject(void *thisObj, void *t_);
// QList::replace(int i, const T & t)
void c_QList_T_QObject_T___replace_int_QObject(void *thisObj, int i, void *t_);
// QList::reserve(int size)
void c_QList_T_QObject_T___reserve_int(void *thisObj, int size);
// QList::setSharable(bool sharable)
void c_QList_T_QObject_T___setSharable_bool(void *thisObj, bool sharable);
// QList::size() const
int c_QList_T_QObject_T___size(void *thisObj);
// QList::startsWith(const T & t) const
bool c_QList_T_QObject_T___startsWith_QObject(void *thisObj, void *t_);
// QList::swapItemsAt(int i, int j)
void c_QList_T_QObject_T___swapItemsAt_int_int(void *thisObj, int i, int j);
// QList::takeAt(int i)
void *c_QList_T_QObject_T___takeAt_int(void *thisObj, int i);
// QList::takeFirst()
void *c_QList_T_QObject_T___takeFirst(void *thisObj);
// QList::takeLast()
void *c_QList_T_QObject_T___takeLast(void *thisObj);
// QList::value(int i) const
void *c_QList_T_QObject_T___value_int(void *thisObj, int i);
// QList::value(int i, const T & defaultValue) const
void *c_QList_T_QObject_T___value_int_QObject(void *thisObj, int i, void *defaultValue_);
void c_QList_T_QObject_T___destructor(void *thisObj);
void c_QList_T_QObject_T__Finalizer(void *cppObj); // QList::QList<T>()
void *c_QList_T_QByteArray_T___constructor();
// QList::append(const QList<T > & t)
void c_QList_T_QByteArray_T___append_QList_T(void *thisObj, void *t_);
// QList::append(const T & t)
void c_QList_T_QByteArray_T___append_QByteArray(void *thisObj, void *t_);
// QList::at(int i) const
const void *c_QList_T_QByteArray_T___at_int(void *thisObj, int i);
// QList::back()
void *c_QList_T_QByteArray_T___back(void *thisObj);
// QList::clear()
void c_QList_T_QByteArray_T___clear(void *thisObj);
// QList::constFirst() const
const void *c_QList_T_QByteArray_T___constFirst(void *thisObj);
// QList::constLast() const
const void *c_QList_T_QByteArray_T___constLast(void *thisObj);
// QList::contains(const T & t) const
bool c_QList_T_QByteArray_T___contains_QByteArray(void *thisObj, void *t_);
// QList::count() const
int c_QList_T_QByteArray_T___count(void *thisObj);
// QList::count(const T & t) const
int c_QList_T_QByteArray_T___count_QByteArray(void *thisObj, void *t_);
// QList::detach()
void c_QList_T_QByteArray_T___detach(void *thisObj);
// QList::detachShared()
void c_QList_T_QByteArray_T___detachShared(void *thisObj);
// QList::empty() const
bool c_QList_T_QByteArray_T___empty(void *thisObj);
// QList::endsWith(const T & t) const
bool c_QList_T_QByteArray_T___endsWith_QByteArray(void *thisObj, void *t_);
// QList::first()
void *c_QList_T_QByteArray_T___first(void *thisObj);
// QList::front()
void *c_QList_T_QByteArray_T___front(void *thisObj);
// QList::indexOf(const T & t, int from) const
int c_QList_T_QByteArray_T___indexOf_QByteArray_int(void *thisObj, void *t_, int from);
// QList::insert(int i, const T & t)
void c_QList_T_QByteArray_T___insert_int_QByteArray(void *thisObj, int i, void *t_);
// QList::isDetached() const
bool c_QList_T_QByteArray_T___isDetached(void *thisObj);
// QList::isEmpty() const
bool c_QList_T_QByteArray_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
bool c_QList_T_QByteArray_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
void *c_QList_T_QByteArray_T___last(void *thisObj);
// QList::lastIndexOf(const T & t, int from) const
int c_QList_T_QByteArray_T___lastIndexOf_QByteArray_int(void *thisObj, void *t_, int from);
// QList::length() const
int c_QList_T_QByteArray_T___length(void *thisObj);
// QList::mid(int pos, int length) const
void *c_QList_T_QByteArray_T___mid_int_int(void *thisObj, int pos, int length);
// QList::move(int from, int to)
void c_QList_T_QByteArray_T___move_int_int(void *thisObj, int from, int to);
// QList::pop_back()
void c_QList_T_QByteArray_T___pop_back(void *thisObj);
// QList::pop_front()
void c_QList_T_QByteArray_T___pop_front(void *thisObj);
// QList::prepend(const T & t)
void c_QList_T_QByteArray_T___prepend_QByteArray(void *thisObj, void *t_);
// QList::push_back(const T & t)
void c_QList_T_QByteArray_T___push_back_QByteArray(void *thisObj, void *t_);
// QList::push_front(const T & t)
void c_QList_T_QByteArray_T___push_front_QByteArray(void *thisObj, void *t_);
// QList::removeAll(const T & t)
int c_QList_T_QByteArray_T___removeAll_QByteArray(void *thisObj, void *t_);
// QList::removeAt(int i)
void c_QList_T_QByteArray_T___removeAt_int(void *thisObj, int i);
// QList::removeFirst()
void c_QList_T_QByteArray_T___removeFirst(void *thisObj);
// QList::removeLast()
void c_QList_T_QByteArray_T___removeLast(void *thisObj);
// QList::removeOne(const T & t)
bool c_QList_T_QByteArray_T___removeOne_QByteArray(void *thisObj, void *t_);
// QList::replace(int i, const T & t)
void c_QList_T_QByteArray_T___replace_int_QByteArray(void *thisObj, int i, void *t_);
// QList::reserve(int size)
void c_QList_T_QByteArray_T___reserve_int(void *thisObj, int size);
// QList::setSharable(bool sharable)
void c_QList_T_QByteArray_T___setSharable_bool(void *thisObj, bool sharable);
// QList::size() const
int c_QList_T_QByteArray_T___size(void *thisObj);
// QList::startsWith(const T & t) const
bool c_QList_T_QByteArray_T___startsWith_QByteArray(void *thisObj, void *t_);
// QList::swapItemsAt(int i, int j)
void c_QList_T_QByteArray_T___swapItemsAt_int_int(void *thisObj, int i, int j);
// QList::takeAt(int i)
void *c_QList_T_QByteArray_T___takeAt_int(void *thisObj, int i);
// QList::takeFirst()
void *c_QList_T_QByteArray_T___takeFirst(void *thisObj);
// QList::takeLast()
void *c_QList_T_QByteArray_T___takeLast(void *thisObj);
// QList::value(int i) const
void *c_QList_T_QByteArray_T___value_int(void *thisObj, int i);
// QList::value(int i, const T & defaultValue) const
void *c_QList_T_QByteArray_T___value_int_QByteArray(void *thisObj, int i, void *defaultValue_);
void c_QList_T_QByteArray_T___destructor(void *thisObj);
void c_QList_T_QByteArray_T__Finalizer(void *cppObj); // QList::QList<T>()
void *c_QList_T_Group_T___constructor();
// QList::append(const QList<T > & t)
void c_QList_T_Group_T___append_QList_T(void *thisObj, void *t_);
// QList::append(const T & t)
void c_QList_T_Group_T___append_Group(void *thisObj, void *t_);
// QList::at(int i) const
const void *c_QList_T_Group_T___at_int(void *thisObj, int i);
// QList::back()
void *c_QList_T_Group_T___back(void *thisObj);
// QList::clear()
void c_QList_T_Group_T___clear(void *thisObj);
// QList::constFirst() const
const void *c_QList_T_Group_T___constFirst(void *thisObj);
// QList::constLast() const
const void *c_QList_T_Group_T___constLast(void *thisObj);
// QList::contains(const T & t) const
bool c_QList_T_Group_T___contains_Group(void *thisObj, void *t_);
// QList::count() const
int c_QList_T_Group_T___count(void *thisObj);
// QList::count(const T & t) const
int c_QList_T_Group_T___count_Group(void *thisObj, void *t_);
// QList::detach()
void c_QList_T_Group_T___detach(void *thisObj);
// QList::detachShared()
void c_QList_T_Group_T___detachShared(void *thisObj);
// QList::empty() const
bool c_QList_T_Group_T___empty(void *thisObj);
// QList::endsWith(const T & t) const
bool c_QList_T_Group_T___endsWith_Group(void *thisObj, void *t_);
// QList::first()
void *c_QList_T_Group_T___first(void *thisObj);
// QList::front()
void *c_QList_T_Group_T___front(void *thisObj);
// QList::indexOf(const T & t, int from) const
int c_QList_T_Group_T___indexOf_Group_int(void *thisObj, void *t_, int from);
// QList::insert(int i, const T & t)
void c_QList_T_Group_T___insert_int_Group(void *thisObj, int i, void *t_);
// QList::isDetached() const
bool c_QList_T_Group_T___isDetached(void *thisObj);
// QList::isEmpty() const
bool c_QList_T_Group_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
bool c_QList_T_Group_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
void *c_QList_T_Group_T___last(void *thisObj);
// QList::lastIndexOf(const T & t, int from) const
int c_QList_T_Group_T___lastIndexOf_Group_int(void *thisObj, void *t_, int from);
// QList::length() const
int c_QList_T_Group_T___length(void *thisObj);
// QList::mid(int pos, int length) const
void *c_QList_T_Group_T___mid_int_int(void *thisObj, int pos, int length);
// QList::move(int from, int to)
void c_QList_T_Group_T___move_int_int(void *thisObj, int from, int to);
// QList::pop_back()
void c_QList_T_Group_T___pop_back(void *thisObj);
// QList::pop_front()
void c_QList_T_Group_T___pop_front(void *thisObj);
// QList::prepend(const T & t)
void c_QList_T_Group_T___prepend_Group(void *thisObj, void *t_);
// QList::push_back(const T & t)
void c_QList_T_Group_T___push_back_Group(void *thisObj, void *t_);
// QList::push_front(const T & t)
void c_QList_T_Group_T___push_front_Group(void *thisObj, void *t_);
// QList::removeAll(const T & t)
int c_QList_T_Group_T___removeAll_Group(void *thisObj, void *t_);
// QList::removeAt(int i)
void c_QList_T_Group_T___removeAt_int(void *thisObj, int i);
// QList::removeFirst()
void c_QList_T_Group_T___removeFirst(void *thisObj);
// QList::removeLast()
void c_QList_T_Group_T___removeLast(void *thisObj);
// QList::removeOne(const T & t)
bool c_QList_T_Group_T___removeOne_Group(void *thisObj, void *t_);
// QList::replace(int i, const T & t)
void c_QList_T_Group_T___replace_int_Group(void *thisObj, int i, void *t_);
// QList::reserve(int size)
void c_QList_T_Group_T___reserve_int(void *thisObj, int size);
// QList::setSharable(bool sharable)
void c_QList_T_Group_T___setSharable_bool(void *thisObj, bool sharable);
// QList::size() const
int c_QList_T_Group_T___size(void *thisObj);
// QList::startsWith(const T & t) const
bool c_QList_T_Group_T___startsWith_Group(void *thisObj, void *t_);
// QList::swapItemsAt(int i, int j)
void c_QList_T_Group_T___swapItemsAt_int_int(void *thisObj, int i, int j);
// QList::takeAt(int i)
void *c_QList_T_Group_T___takeAt_int(void *thisObj, int i);
// QList::takeFirst()
void *c_QList_T_Group_T___takeFirst(void *thisObj);
// QList::takeLast()
void *c_QList_T_Group_T___takeLast(void *thisObj);
// QList::value(int i) const
void *c_QList_T_Group_T___value_int(void *thisObj, int i);
// QList::value(int i, const T & defaultValue) const
void *c_QList_T_Group_T___value_int_Group(void *thisObj, int i, void *defaultValue_);
void c_QList_T_Group_T___destructor(void *thisObj);
void c_QList_T_Group_T__Finalizer(void *cppObj); // QByteArray::QByteArray()
void *c_QByteArray__constructor();
// QByteArray::QByteArray(const char * arg__1, int size)
void *c_QByteArray__constructor_char_int(const char *arg__1, int size);
// QByteArray::append(const QByteArray & a)
void *c_QByteArray__append_QByteArray(void *thisObj, void *a_);
// QByteArray::append(const char * s)
void *c_QByteArray__append_char(void *thisObj, const char *s);
// QByteArray::append(const char * s, int len)
void *c_QByteArray__append_char_int(void *thisObj, const char *s, int len);
// QByteArray::at(int i) const
char c_QByteArray__at_int(void *thisObj, int i);
// QByteArray::back() const
char c_QByteArray__back(void *thisObj);
// QByteArray::begin() const
const char *c_QByteArray__begin(void *thisObj);
// QByteArray::capacity() const
int c_QByteArray__capacity(void *thisObj);
// QByteArray::cbegin() const
const char *c_QByteArray__cbegin(void *thisObj);
// QByteArray::cend() const
const char *c_QByteArray__cend(void *thisObj);
// QByteArray::chop(int n)
void c_QByteArray__chop_int(void *thisObj, int n);
// QByteArray::chopped(int len) const
void *c_QByteArray__chopped_int(void *thisObj, int len);
// QByteArray::clear()
void c_QByteArray__clear(void *thisObj);
// QByteArray::compare(const QByteArray & a) const
int c_QByteArray__compare_QByteArray(void *thisObj, void *a_);
// QByteArray::compare(const char * c) const
int c_QByteArray__compare_char(void *thisObj, const char *c);
// QByteArray::constBegin() const
const char *c_QByteArray__constBegin(void *thisObj);
// QByteArray::constData() const
const char *c_QByteArray__constData(void *thisObj);
// QByteArray::constEnd() const
const char *c_QByteArray__constEnd(void *thisObj);
// QByteArray::contains(const QByteArray & a) const
bool c_QByteArray__contains_QByteArray(void *thisObj, void *a_);
// QByteArray::contains(const char * a) const
bool c_QByteArray__contains_char(void *thisObj, const char *a);
// QByteArray::count() const
int c_QByteArray__count(void *thisObj);
// QByteArray::count(const QByteArray & a) const
int c_QByteArray__count_QByteArray(void *thisObj, void *a_);
// QByteArray::count(const char * a) const
int c_QByteArray__count_char(void *thisObj, const char *a);
// QByteArray::data() const
const char *c_QByteArray__data(void *thisObj);
// QByteArray::detach()
void c_QByteArray__detach(void *thisObj);
// QByteArray::end() const
const char *c_QByteArray__end(void *thisObj);
// QByteArray::endsWith(const QByteArray & a) const
bool c_QByteArray__endsWith_QByteArray(void *thisObj, void *a_);
// QByteArray::endsWith(const char * c) const
bool c_QByteArray__endsWith_char(void *thisObj, const char *c);
// QByteArray::fromBase64(const QByteArray & base64)
void *c_static_QByteArray__fromBase64_QByteArray(void *base64_);
// QByteArray::fromHex(const QByteArray & hexEncoded)
void *c_static_QByteArray__fromHex_QByteArray(void *hexEncoded_);
// QByteArray::fromRawData(const char * arg__1, int size)
void *c_static_QByteArray__fromRawData_char_int(const char *arg__1, int size);
// QByteArray::front() const
char c_QByteArray__front(void *thisObj);
// QByteArray::indexOf(const QByteArray & a, int from) const
int c_QByteArray__indexOf_QByteArray_int(void *thisObj, void *a_, int from);
// QByteArray::indexOf(const char * c, int from) const
int c_QByteArray__indexOf_char_int(void *thisObj, const char *c, int from);
// QByteArray::insert(int i, const QByteArray & a)
void *c_QByteArray__insert_int_QByteArray(void *thisObj, int i, void *a_);
// QByteArray::insert(int i, const char * s)
void *c_QByteArray__insert_int_char(void *thisObj, int i, const char *s);
// QByteArray::insert(int i, const char * s, int len)
void *c_QByteArray__insert_int_char_int(void *thisObj, int i, const char *s, int len);
// QByteArray::isDetached() const
bool c_QByteArray__isDetached(void *thisObj);
// QByteArray::isEmpty() const
bool c_QByteArray__isEmpty(void *thisObj);
// QByteArray::isLower() const
bool c_QByteArray__isLower(void *thisObj);
// QByteArray::isNull() const
bool c_QByteArray__isNull(void *thisObj);
// QByteArray::isSharedWith(const QByteArray & other) const
bool c_QByteArray__isSharedWith_QByteArray(void *thisObj, void *other_);
// QByteArray::isUpper() const
bool c_QByteArray__isUpper(void *thisObj);
// QByteArray::lastIndexOf(const QByteArray & a, int from) const
int c_QByteArray__lastIndexOf_QByteArray_int(void *thisObj, void *a_, int from);
// QByteArray::lastIndexOf(const char * c, int from) const
int c_QByteArray__lastIndexOf_char_int(void *thisObj, const char *c, int from);
// QByteArray::left(int len) const
void *c_QByteArray__left_int(void *thisObj, int len);
// QByteArray::length() const
int c_QByteArray__length(void *thisObj);
// QByteArray::mid(int index, int len) const
void *c_QByteArray__mid_int_int(void *thisObj, int index, int len);
// QByteArray::number(int arg__1, int base)
void *c_static_QByteArray__number_int_int(int arg__1, int base);
// QByteArray::number(qint64 arg__1, int base)
void *c_static_QByteArray__number_qint64_int(qint64 arg__1, int base);
// QByteArray::prepend(const QByteArray & a)
void *c_QByteArray__prepend_QByteArray(void *thisObj, void *a_);
// QByteArray::prepend(const char * s)
void *c_QByteArray__prepend_char(void *thisObj, const char *s);
// QByteArray::prepend(const char * s, int len)
void *c_QByteArray__prepend_char_int(void *thisObj, const char *s, int len);
// QByteArray::push_back(const QByteArray & a)
void c_QByteArray__push_back_QByteArray(void *thisObj, void *a_);
// QByteArray::push_back(const char * c)
void c_QByteArray__push_back_char(void *thisObj, const char *c);
// QByteArray::push_front(const QByteArray & a)
void c_QByteArray__push_front_QByteArray(void *thisObj, void *a_);
// QByteArray::push_front(const char * c)
void c_QByteArray__push_front_char(void *thisObj, const char *c);
// QByteArray::remove(int index, int len)
void *c_QByteArray__remove_int_int(void *thisObj, int index, int len);
// QByteArray::repeated(int times) const
void *c_QByteArray__repeated_int(void *thisObj, int times);
// QByteArray::replace(const QByteArray & before, const QByteArray & after)
void *c_QByteArray__replace_QByteArray_QByteArray(void *thisObj, void *before_, void *after_);
// QByteArray::replace(const QByteArray & before, const char * after)
void *c_QByteArray__replace_QByteArray_char(void *thisObj, void *before_, const char *after);
// QByteArray::replace(const char * before, const QByteArray & after)
void *c_QByteArray__replace_char_QByteArray(void *thisObj, const char *before, void *after_);
// QByteArray::replace(const char * before, const char * after)
void *c_QByteArray__replace_char_char(void *thisObj, const char *before, const char *after);
// QByteArray::replace(const char * before, int bsize, const char * after, int asize)
void *c_QByteArray__replace_char_int_char_int(void *thisObj, const char *before, int bsize, const char *after, int asize);
// QByteArray::replace(int index, int len, const QByteArray & s)
void *c_QByteArray__replace_int_int_QByteArray(void *thisObj, int index, int len, void *s_);
// QByteArray::replace(int index, int len, const char * s)
void *c_QByteArray__replace_int_int_char(void *thisObj, int index, int len, const char *s);
// QByteArray::replace(int index, int len, const char * s, int alen)
void *c_QByteArray__replace_int_int_char_int(void *thisObj, int index, int len, const char *s, int alen);
// QByteArray::reserve(int size)
void c_QByteArray__reserve_int(void *thisObj, int size);
// QByteArray::resize(int size)
void c_QByteArray__resize_int(void *thisObj, int size);
// QByteArray::right(int len) const
void *c_QByteArray__right_int(void *thisObj, int len);
// QByteArray::setNum(int arg__1, int base)
void *c_QByteArray__setNum_int_int(void *thisObj, int arg__1, int base);
// QByteArray::setNum(qint64 arg__1, int base)
void *c_QByteArray__setNum_qint64_int(void *thisObj, qint64 arg__1, int base);
// QByteArray::setNum(short arg__1, int base)
void *c_QByteArray__setNum_short_int(void *thisObj, short arg__1, int base);
// QByteArray::shrink_to_fit()
void c_QByteArray__shrink_to_fit(void *thisObj);
// QByteArray::simplified()
void *c_QByteArray__simplified(void *thisObj);
// QByteArray::size() const
int c_QByteArray__size(void *thisObj);
// QByteArray::squeeze()
void c_QByteArray__squeeze(void *thisObj);
// QByteArray::startsWith(const QByteArray & a) const
bool c_QByteArray__startsWith_QByteArray(void *thisObj, void *a_);
// QByteArray::startsWith(const char * c) const
bool c_QByteArray__startsWith_char(void *thisObj, const char *c);
// QByteArray::toBase64() const
void *c_QByteArray__toBase64(void *thisObj);
// QByteArray::toHex() const
void *c_QByteArray__toHex(void *thisObj);
// QByteArray::toLower()
void *c_QByteArray__toLower(void *thisObj);
// QByteArray::toUpper()
void *c_QByteArray__toUpper(void *thisObj);
// QByteArray::trimmed()
void *c_QByteArray__trimmed(void *thisObj);
// QByteArray::truncate(int pos)
void c_QByteArray__truncate_int(void *thisObj, int pos);
void c_QByteArray__destructor(void *thisObj);
void c_QByteArray_Finalizer(void *cppObj); // KDDockWidgets::initFrontend(KDDockWidgets::FrontendType arg__1)
void c_static_KDDockWidgets__initFrontend_FrontendType(int arg__1);
void c_KDDockWidgets_Finalizer(void *cppObj); // KDDockWidgets::flutter::asView_flutter(KDDockWidgets::Core::Controller * controller)
void *c_static_KDDockWidgets__flutter__asView_flutter_Controller(void *controller_);
// KDDockWidgets::flutter::asView_flutter(KDDockWidgets::Core::View * view)
void *c_static_KDDockWidgets__flutter__asView_flutter_View(void *view_);
void c_KDDockWidgets__flutter_Finalizer(void *cppObj); // KDDockWidgets::flutter::Window::destroy()
void c_KDDockWidgets__flutter__Window__destroy(void *thisObj);
// KDDockWidgets::flutter::Window::frameGeometry() const
void *c_KDDockWidgets__flutter__Window__frameGeometry(void *thisObj);
// KDDockWidgets::flutter::Window::fromNativePixels(QPoint arg__1) const
void *c_KDDockWidgets__flutter__Window__fromNativePixels_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::Window::geometry() const
void *c_KDDockWidgets__flutter__Window__geometry(void *thisObj);
// KDDockWidgets::flutter::Window::isActive() const
bool c_KDDockWidgets__flutter__Window__isActive(void *thisObj);
// KDDockWidgets::flutter::Window::isFullScreen() const
bool c_KDDockWidgets__flutter__Window__isFullScreen(void *thisObj);
// KDDockWidgets::flutter::Window::isVisible() const
bool c_KDDockWidgets__flutter__Window__isVisible(void *thisObj);
// KDDockWidgets::flutter::Window::mapFromGlobal(QPoint globalPos) const
void *c_KDDockWidgets__flutter__Window__mapFromGlobal_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::flutter::Window::mapToGlobal(QPoint localPos) const
void *c_KDDockWidgets__flutter__Window__mapToGlobal_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::flutter::Window::maxSize() const
void *c_KDDockWidgets__flutter__Window__maxSize(void *thisObj);
// KDDockWidgets::flutter::Window::minSize() const
void *c_KDDockWidgets__flutter__Window__minSize(void *thisObj);
// KDDockWidgets::flutter::Window::resize(int width, int height)
void c_KDDockWidgets__flutter__Window__resize_int_int(void *thisObj, int width, int height);
// KDDockWidgets::flutter::Window::setFramePosition(QPoint targetPos)
void c_KDDockWidgets__flutter__Window__setFramePosition_QPoint(void *thisObj, void *targetPos_);
// KDDockWidgets::flutter::Window::setGeometry(QRect arg__1)
void c_KDDockWidgets__flutter__Window__setGeometry_QRect(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::Window::setVisible(bool arg__1)
void c_KDDockWidgets__flutter__Window__setVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::flutter::Window::supportsHonouringLayoutMinSize() const
bool c_KDDockWidgets__flutter__Window__supportsHonouringLayoutMinSize(void *thisObj);
void c_KDDockWidgets__flutter__Window__destructor(void *thisObj);
void c_KDDockWidgets__flutter__Window__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__flutter__Window_Finalizer(void *cppObj); // KDDockWidgets::LayoutSaver::LayoutSaver()
void *c_KDDockWidgets__LayoutSaver__constructor();
// KDDockWidgets::LayoutSaver::restoreFromFile(const QString & jsonFilename)
bool c_KDDockWidgets__LayoutSaver__restoreFromFile_QString(void *thisObj, const char *jsonFilename_);
// KDDockWidgets::LayoutSaver::restoreInProgress()
bool c_static_KDDockWidgets__LayoutSaver__restoreInProgress();
// KDDockWidgets::LayoutSaver::restoreLayout(const QByteArray & arg__1)
bool c_KDDockWidgets__LayoutSaver__restoreLayout_QByteArray(void *thisObj, void *arg__1_);
// KDDockWidgets::LayoutSaver::saveToFile(const QString & jsonFilename)
bool c_KDDockWidgets__LayoutSaver__saveToFile_QString(void *thisObj, const char *jsonFilename_);
// KDDockWidgets::LayoutSaver::serializeLayout() const
void *c_KDDockWidgets__LayoutSaver__serializeLayout(void *thisObj);
void c_KDDockWidgets__LayoutSaver__destructor(void *thisObj);
void c_KDDockWidgets__LayoutSaver_Finalizer(void *cppObj); // KDDockWidgets::InitialOption::InitialOption()
void *c_KDDockWidgets__InitialOption__constructor();
// KDDockWidgets::InitialOption::InitialOption(KDDockWidgets::DefaultSizeMode mode)
void *c_KDDockWidgets__InitialOption__constructor_DefaultSizeMode(int mode);
// KDDockWidgets::InitialOption::InitialOption(KDDockWidgets::InitialVisibilityOption v)
void *c_KDDockWidgets__InitialOption__constructor_InitialVisibilityOption(int v);
// KDDockWidgets::InitialOption::InitialOption(KDDockWidgets::InitialVisibilityOption v, QSize size)
void *c_KDDockWidgets__InitialOption__constructor_InitialVisibilityOption_QSize(int v, void *size_);
// KDDockWidgets::InitialOption::InitialOption(QSize size)
void *c_KDDockWidgets__InitialOption__constructor_QSize(void *size_);
// KDDockWidgets::InitialOption::preservesCurrentTab() const
bool c_KDDockWidgets__InitialOption__preservesCurrentTab(void *thisObj);
// KDDockWidgets::InitialOption::startsHidden() const
bool c_KDDockWidgets__InitialOption__startsHidden(void *thisObj);
void c_KDDockWidgets__InitialOption__destructor(void *thisObj);
void c_KDDockWidgets__InitialOption_Finalizer(void *cppObj); // KDDockWidgets::Event::Event(KDDockWidgets::Event::Type type)
void *c_KDDockWidgets__Event__constructor_Type(int type);
// KDDockWidgets::Event::accept()
void c_KDDockWidgets__Event__accept(void *thisObj);
// KDDockWidgets::Event::ignore()
void c_KDDockWidgets__Event__ignore(void *thisObj);
// KDDockWidgets::Event::isAccepted() const
bool c_KDDockWidgets__Event__isAccepted(void *thisObj);
// KDDockWidgets::Event::spontaneous() const
bool c_KDDockWidgets__Event__spontaneous(void *thisObj);
// KDDockWidgets::Event::type() const
int c_KDDockWidgets__Event__type(void *thisObj);
void c_KDDockWidgets__Event__destructor(void *thisObj);
bool c_KDDockWidgets__Event___get_m_accepted(void *thisObj);
bool c_KDDockWidgets__Event___get_m_spontaneous(void *thisObj);
void c_KDDockWidgets__Event___set_m_accepted_bool(void *thisObj, bool m_accepted_);
void c_KDDockWidgets__Event___set_m_spontaneous_bool(void *thisObj, bool m_spontaneous_);
void c_KDDockWidgets__Event_Finalizer(void *cppObj); // KDDockWidgets::DockRegistry::checkSanityAll(bool dumpDebug)
void c_KDDockWidgets__DockRegistry__checkSanityAll_bool(void *thisObj, bool dumpDebug);
// KDDockWidgets::DockRegistry::clear()
void c_KDDockWidgets__DockRegistry__clear(void *thisObj);
// KDDockWidgets::DockRegistry::containsDockWidget(const QString & uniqueName) const
bool c_KDDockWidgets__DockRegistry__containsDockWidget_QString(void *thisObj, const char *uniqueName_);
// KDDockWidgets::DockRegistry::containsMainWindow(const QString & uniqueName) const
bool c_KDDockWidgets__DockRegistry__containsMainWindow_QString(void *thisObj, const char *uniqueName_);
// KDDockWidgets::DockRegistry::dockByName(const QString & arg__1) const
void *c_KDDockWidgets__DockRegistry__dockByName_QString(void *thisObj, const char *arg__1_);
// KDDockWidgets::DockRegistry::dropIndicatorsInhibitedChanged(bool inhibited)
void c_KDDockWidgets__DockRegistry__dropIndicatorsInhibitedChanged_bool(void *thisObj, bool inhibited);
// KDDockWidgets::DockRegistry::ensureAllFloatingWidgetsAreMorphed()
void c_KDDockWidgets__DockRegistry__ensureAllFloatingWidgetsAreMorphed(void *thisObj);
// KDDockWidgets::DockRegistry::focusedDockWidget() const
void *c_KDDockWidgets__DockRegistry__focusedDockWidget(void *thisObj);
// KDDockWidgets::DockRegistry::groupInMDIResize() const
void *c_KDDockWidgets__DockRegistry__groupInMDIResize(void *thisObj);
// KDDockWidgets::DockRegistry::groupInMDIResizeChanged()
void c_KDDockWidgets__DockRegistry__groupInMDIResizeChanged(void *thisObj);
// KDDockWidgets::DockRegistry::groups() const
void *c_KDDockWidgets__DockRegistry__groups(void *thisObj);
// KDDockWidgets::DockRegistry::hasFloatingWindows() const
bool c_KDDockWidgets__DockRegistry__hasFloatingWindows(void *thisObj);
// KDDockWidgets::DockRegistry::isEmpty(bool excludeBeingDeleted) const
bool c_KDDockWidgets__DockRegistry__isEmpty_bool(void *thisObj, bool excludeBeingDeleted);
// KDDockWidgets::DockRegistry::isSane() const
bool c_KDDockWidgets__DockRegistry__isSane(void *thisObj);
// KDDockWidgets::DockRegistry::itemIsInMainWindow(const KDDockWidgets::Core::Item * arg__1) const
bool c_KDDockWidgets__DockRegistry__itemIsInMainWindow_Item(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::layoutForItem(const KDDockWidgets::Core::Item * arg__1) const
void *c_KDDockWidgets__DockRegistry__layoutForItem_Item(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::mainWindowByName(const QString & arg__1) const
void *c_KDDockWidgets__DockRegistry__mainWindowByName_QString(void *thisObj, const char *arg__1_);
// KDDockWidgets::DockRegistry::registerDockWidget(KDDockWidgets::Core::DockWidget * arg__1)
void c_KDDockWidgets__DockRegistry__registerDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::registerFloatingWindow(KDDockWidgets::Core::FloatingWindow * arg__1)
void c_KDDockWidgets__DockRegistry__registerFloatingWindow_FloatingWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::registerGroup(KDDockWidgets::Core::Group * arg__1)
void c_KDDockWidgets__DockRegistry__registerGroup_Group(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::registerLayout(KDDockWidgets::Core::Layout * arg__1)
void c_KDDockWidgets__DockRegistry__registerLayout_Layout(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::registerMainWindow(KDDockWidgets::Core::MainWindow * arg__1)
void c_KDDockWidgets__DockRegistry__registerMainWindow_MainWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::self()
void *c_static_KDDockWidgets__DockRegistry__self();
// KDDockWidgets::DockRegistry::sideBarForDockWidget(const KDDockWidgets::Core::DockWidget * arg__1) const
void *c_KDDockWidgets__DockRegistry__sideBarForDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__DockRegistry__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::DockRegistry::unregisterDockWidget(KDDockWidgets::Core::DockWidget * arg__1)
void c_KDDockWidgets__DockRegistry__unregisterDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::unregisterFloatingWindow(KDDockWidgets::Core::FloatingWindow * arg__1)
void c_KDDockWidgets__DockRegistry__unregisterFloatingWindow_FloatingWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::unregisterGroup(KDDockWidgets::Core::Group * arg__1)
void c_KDDockWidgets__DockRegistry__unregisterGroup_Group(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::unregisterLayout(KDDockWidgets::Core::Layout * arg__1)
void c_KDDockWidgets__DockRegistry__unregisterLayout_Layout(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::unregisterMainWindow(KDDockWidgets::Core::MainWindow * arg__1)
void c_KDDockWidgets__DockRegistry__unregisterMainWindow_MainWindow(void *thisObj, void *arg__1_);
void c_KDDockWidgets__DockRegistry__destructor(void *thisObj);
void c_KDDockWidgets__DockRegistry__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__DockRegistry_Finalizer(void *cppObj);
void c_KDDockWidgets__Core_Finalizer(void *cppObj); // KDDockWidgets::Core::ViewFactory::ViewFactory()
void *c_KDDockWidgets__Core__ViewFactory__constructor();
// KDDockWidgets::Core::ViewFactory::createClassicIndicatorWindow(KDDockWidgets::Core::ClassicDropIndicatorOverlay * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__Core__ViewFactory__createClassicIndicatorWindow_ClassicDropIndicatorOverlay_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::Core::ViewFactory::createDockWidget(const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions, Qt::WindowFlags windowFlags) const
void *c_KDDockWidgets__Core__ViewFactory__createDockWidget_QString_DockWidgetOptions_LayoutSaverOptions_WindowFlags(void *thisObj, const char *uniqueName_, int options_, int layoutSaverOptions_, int windowFlags);
// KDDockWidgets::Core::ViewFactory::createDropArea(KDDockWidgets::Core::DropArea * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__Core__ViewFactory__createDropArea_DropArea_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::Core::ViewFactory::createFloatingWindow(KDDockWidgets::Core::FloatingWindow * controller, KDDockWidgets::Core::MainWindow * parent, Qt::WindowFlags windowFlags) const
void *c_KDDockWidgets__Core__ViewFactory__createFloatingWindow_FloatingWindow_MainWindow_WindowFlags(void *thisObj, void *controller_, void *parent_, int windowFlags);
// KDDockWidgets::Core::ViewFactory::createGroup(KDDockWidgets::Core::Group * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__Core__ViewFactory__createGroup_Group_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::Core::ViewFactory::createRubberBand(KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__Core__ViewFactory__createRubberBand_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::ViewFactory::createSeparator(KDDockWidgets::Core::Separator * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__Core__ViewFactory__createSeparator_Separator_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::Core::ViewFactory::createSideBar(KDDockWidgets::Core::SideBar * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__Core__ViewFactory__createSideBar_SideBar_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::Core::ViewFactory::createStack(KDDockWidgets::Core::Stack * stack, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__Core__ViewFactory__createStack_Stack_View(void *thisObj, void *stack_, void *parent_);
// KDDockWidgets::Core::ViewFactory::createTabBar(KDDockWidgets::Core::TabBar * tabBar, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__Core__ViewFactory__createTabBar_TabBar_View(void *thisObj, void *tabBar_, void *parent_);
// KDDockWidgets::Core::ViewFactory::createTitleBar(KDDockWidgets::Core::TitleBar * controller, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__Core__ViewFactory__createTitleBar_TitleBar_View(void *thisObj, void *controller_, void *parent_);
// KDDockWidgets::Core::ViewFactory::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__ViewFactory__tr_char_char_int(const char *s, const char *c, int n);
void c_KDDockWidgets__Core__ViewFactory__destructor(void *thisObj);
void c_KDDockWidgets__Core__ViewFactory__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__ViewFactory_Finalizer(void *cppObj); // KDDockWidgets::flutter::ViewFactory::ViewFactory()
void *c_KDDockWidgets__flutter__ViewFactory__constructor();
// KDDockWidgets::flutter::ViewFactory::createClassicIndicatorWindow(KDDockWidgets::Core::ClassicDropIndicatorOverlay * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__flutter__ViewFactory__createClassicIndicatorWindow_ClassicDropIndicatorOverlay_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::flutter::ViewFactory::createClassicIndicatorWindow_flutter(KDDockWidgets::Core::ClassicDropIndicatorOverlay * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__flutter__ViewFactory__createClassicIndicatorWindow_flutter_ClassicDropIndicatorOverlay_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::flutter::ViewFactory::createDockWidget(const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> arg__2, QFlags<KDDockWidgets::LayoutSaverOption> arg__3, Qt::WindowFlags arg__4) const
void *c_KDDockWidgets__flutter__ViewFactory__createDockWidget_QString_DockWidgetOptions_LayoutSaverOptions_WindowFlags(void *thisObj, const char *uniqueName_, int arg__2_, int arg__3_, int arg__4);
// KDDockWidgets::flutter::ViewFactory::createDropArea(KDDockWidgets::Core::DropArea * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__flutter__ViewFactory__createDropArea_DropArea_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::flutter::ViewFactory::createFloatingWindow(KDDockWidgets::Core::FloatingWindow * arg__1, KDDockWidgets::Core::MainWindow * parent, Qt::WindowFlags windowFlags) const
void *c_KDDockWidgets__flutter__ViewFactory__createFloatingWindow_FloatingWindow_MainWindow_WindowFlags(void *thisObj, void *arg__1_, void *parent_, int windowFlags);
// KDDockWidgets::flutter::ViewFactory::createGroup(KDDockWidgets::Core::Group * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__flutter__ViewFactory__createGroup_Group_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::flutter::ViewFactory::createRubberBand(KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__flutter__ViewFactory__createRubberBand_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::ViewFactory::createSeparator(KDDockWidgets::Core::Separator * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__flutter__ViewFactory__createSeparator_Separator_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::flutter::ViewFactory::createSideBar(KDDockWidgets::Core::SideBar * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__flutter__ViewFactory__createSideBar_SideBar_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::flutter::ViewFactory::createStack(KDDockWidgets::Core::Stack * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__flutter__ViewFactory__createStack_Stack_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::flutter::ViewFactory::createTabBar(KDDockWidgets::Core::TabBar * tabBar, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__flutter__ViewFactory__createTabBar_TabBar_View(void *thisObj, void *tabBar_, void *parent_);
// KDDockWidgets::flutter::ViewFactory::createTitleBar(KDDockWidgets::Core::TitleBar * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__flutter__ViewFactory__createTitleBar_TitleBar_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::flutter::ViewFactory::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__flutter__ViewFactory__tr_char_char_int(const char *s, const char *c, int n);
void c_KDDockWidgets__flutter__ViewFactory__destructor(void *thisObj);
void c_KDDockWidgets__flutter__ViewFactory__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__flutter__ViewFactory_Finalizer(void *cppObj); // KDDockWidgets::Core::Platform::Platform()
void *c_KDDockWidgets__Core__Platform__constructor();
// KDDockWidgets::Core::Platform::applicationName() const
void *c_KDDockWidgets__Core__Platform__applicationName(void *thisObj);
// KDDockWidgets::Core::Platform::createDefaultViewFactory()
void *c_KDDockWidgets__Core__Platform__createDefaultViewFactory(void *thisObj);
// KDDockWidgets::Core::Platform::createMainWindow(const QString & uniqueName, KDDockWidgets::Core::CreateViewOptions arg__2, QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::Core::View * parent, Qt::WindowFlags arg__5) const
void *c_KDDockWidgets__Core__Platform__createMainWindow_QString_CreateViewOptions_MainWindowOptions_View_WindowFlags(void *thisObj, const char *uniqueName_, void *arg__2_, int options_, void *parent_, int arg__5);
// KDDockWidgets::Core::Platform::createView(KDDockWidgets::Core::Controller * arg__1, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__Core__Platform__createView_Controller_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::Core::Platform::cursorPos() const
void *c_KDDockWidgets__Core__Platform__cursorPos(void *thisObj);
// KDDockWidgets::Core::Platform::dumpManagedBacktrace()
void c_KDDockWidgets__Core__Platform__dumpManagedBacktrace(void *thisObj);
// KDDockWidgets::Core::Platform::hasActivePopup() const
bool c_KDDockWidgets__Core__Platform__hasActivePopup(void *thisObj);
// KDDockWidgets::Core::Platform::inDisallowedDragView(QPoint globalPos) const
bool c_KDDockWidgets__Core__Platform__inDisallowedDragView_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::Core::Platform::installMessageHandler()
void c_KDDockWidgets__Core__Platform__installMessageHandler(void *thisObj);
// KDDockWidgets::Core::Platform::instance()
void *c_static_KDDockWidgets__Core__Platform__instance();
// KDDockWidgets::Core::Platform::isInitialized()
bool c_static_KDDockWidgets__Core__Platform__isInitialized();
// KDDockWidgets::Core::Platform::isLeftMouseButtonPressed() const
bool c_KDDockWidgets__Core__Platform__isLeftMouseButtonPressed(void *thisObj);
// KDDockWidgets::Core::Platform::isProcessingAppQuitEvent() const
bool c_KDDockWidgets__Core__Platform__isProcessingAppQuitEvent(void *thisObj);
// KDDockWidgets::Core::Platform::isQt() const
bool c_KDDockWidgets__Core__Platform__isQt(void *thisObj);
// KDDockWidgets::Core::Platform::isQtQuick() const
bool c_KDDockWidgets__Core__Platform__isQtQuick(void *thisObj);
// KDDockWidgets::Core::Platform::isQtWidgets() const
bool c_KDDockWidgets__Core__Platform__isQtWidgets(void *thisObj);
// KDDockWidgets::Core::Platform::name() const
const char *c_KDDockWidgets__Core__Platform__name(void *thisObj);
// KDDockWidgets::Core::Platform::onFloatingWindowCreated(KDDockWidgets::Core::FloatingWindow * arg__1)
void c_KDDockWidgets__Core__Platform__onFloatingWindowCreated_FloatingWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Platform::onFloatingWindowDestroyed(KDDockWidgets::Core::FloatingWindow * arg__1)
void c_KDDockWidgets__Core__Platform__onFloatingWindowDestroyed_FloatingWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Platform::onMainWindowCreated(KDDockWidgets::Core::MainWindow * arg__1)
void c_KDDockWidgets__Core__Platform__onMainWindowCreated_MainWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Platform::onMainWindowDestroyed(KDDockWidgets::Core::MainWindow * arg__1)
void c_KDDockWidgets__Core__Platform__onMainWindowDestroyed_MainWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Platform::pauseForDebugger()
void c_KDDockWidgets__Core__Platform__pauseForDebugger(void *thisObj);
// KDDockWidgets::Core::Platform::restoreMouseCursor()
void c_KDDockWidgets__Core__Platform__restoreMouseCursor(void *thisObj);
// KDDockWidgets::Core::Platform::runDelayed(int ms, KDDockWidgets::Core::DelayedCall * c)
void c_KDDockWidgets__Core__Platform__runDelayed_int_DelayedCall(void *thisObj, int ms, void *c_);
// KDDockWidgets::Core::Platform::screenNumberFor(KDDockWidgets::Core::View * arg__1) const
int c_KDDockWidgets__Core__Platform__screenNumberFor_View(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Platform::screenSizeFor(KDDockWidgets::Core::View * arg__1) const
void *c_KDDockWidgets__Core__Platform__screenSizeFor_View(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Platform::sendEvent(KDDockWidgets::Core::View * arg__1, KDDockWidgets::Event * arg__2) const
void c_KDDockWidgets__Core__Platform__sendEvent_View_Event(void *thisObj, void *arg__1_, void *arg__2_);
// KDDockWidgets::Core::Platform::setCursorPos(QPoint arg__1)
void c_KDDockWidgets__Core__Platform__setCursorPos_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Platform::setMouseCursor(Qt::CursorShape arg__1)
void c_KDDockWidgets__Core__Platform__setMouseCursor_CursorShape(void *thisObj, int arg__1);
// KDDockWidgets::Core::Platform::startDragDistance() const
int c_KDDockWidgets__Core__Platform__startDragDistance(void *thisObj);
// KDDockWidgets::Core::Platform::startDragDistance_impl() const
int c_KDDockWidgets__Core__Platform__startDragDistance_impl(void *thisObj);
// KDDockWidgets::Core::Platform::tests_createFocusableView(KDDockWidgets::Core::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)
void *c_KDDockWidgets__Core__Platform__tests_createFocusableView_CreateViewOptions_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::Core::Platform::tests_createNonClosableView(KDDockWidgets::Core::View * parent)
void *c_KDDockWidgets__Core__Platform__tests_createNonClosableView_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::Platform::tests_createView(KDDockWidgets::Core::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)
void *c_KDDockWidgets__Core__Platform__tests_createView_CreateViewOptions_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::Core::Platform::tests_deinitPlatform()
void c_static_KDDockWidgets__Core__Platform__tests_deinitPlatform();
// KDDockWidgets::Core::Platform::tests_deinitPlatform_impl()
void c_KDDockWidgets__Core__Platform__tests_deinitPlatform_impl(void *thisObj);
// KDDockWidgets::Core::Platform::tests_initPlatform_impl()
void c_KDDockWidgets__Core__Platform__tests_initPlatform_impl(void *thisObj);
// KDDockWidgets::Core::Platform::ungrabMouse()
void c_KDDockWidgets__Core__Platform__ungrabMouse(void *thisObj);
// KDDockWidgets::Core::Platform::uninstallMessageHandler()
void c_KDDockWidgets__Core__Platform__uninstallMessageHandler(void *thisObj);
// KDDockWidgets::Core::Platform::usesFallbackMouseGrabber() const
bool c_KDDockWidgets__Core__Platform__usesFallbackMouseGrabber(void *thisObj);
void c_KDDockWidgets__Core__Platform__destructor(void *thisObj);
int c_KDDockWidgets__Core__Platform___get_m_numWarningsEmitted(void *thisObj);
void c_KDDockWidgets__Core__Platform___set_m_numWarningsEmitted_int(void *thisObj, int m_numWarningsEmitted_);
void c_KDDockWidgets__Core__Platform__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__Platform_Finalizer(void *cppObj); // KDDockWidgets::flutter::Platform::Platform()
void *c_KDDockWidgets__flutter__Platform__constructor();
// KDDockWidgets::flutter::Platform::applicationName() const
void *c_KDDockWidgets__flutter__Platform__applicationName(void *thisObj);
// KDDockWidgets::flutter::Platform::createDefaultViewFactory()
void *c_KDDockWidgets__flutter__Platform__createDefaultViewFactory(void *thisObj);
// KDDockWidgets::flutter::Platform::createMainWindow(const QString & uniqueName, KDDockWidgets::Core::CreateViewOptions viewOpts, QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::Core::View * parent, Qt::WindowFlags flags) const
void *c_KDDockWidgets__flutter__Platform__createMainWindow_QString_CreateViewOptions_MainWindowOptions_View_WindowFlags(void *thisObj, const char *uniqueName_, void *viewOpts_, int options_, void *parent_, int flags);
// KDDockWidgets::flutter::Platform::createView(KDDockWidgets::Core::Controller * controller, KDDockWidgets::Core::View * parent) const
void *c_KDDockWidgets__flutter__Platform__createView_Controller_View(void *thisObj, void *controller_, void *parent_);
// KDDockWidgets::flutter::Platform::cursorPos() const
void *c_KDDockWidgets__flutter__Platform__cursorPos(void *thisObj);
// KDDockWidgets::flutter::Platform::dumpManagedBacktrace()
void c_KDDockWidgets__flutter__Platform__dumpManagedBacktrace(void *thisObj);
// KDDockWidgets::flutter::Platform::hasActivePopup() const
bool c_KDDockWidgets__flutter__Platform__hasActivePopup(void *thisObj);
// KDDockWidgets::flutter::Platform::inDisallowedDragView(QPoint globalPos) const
bool c_KDDockWidgets__flutter__Platform__inDisallowedDragView_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::flutter::Platform::init()
void c_KDDockWidgets__flutter__Platform__init(void *thisObj);
// KDDockWidgets::flutter::Platform::installMessageHandler()
void c_KDDockWidgets__flutter__Platform__installMessageHandler(void *thisObj);
// KDDockWidgets::flutter::Platform::isLeftMouseButtonPressed() const
bool c_KDDockWidgets__flutter__Platform__isLeftMouseButtonPressed(void *thisObj);
// KDDockWidgets::flutter::Platform::isProcessingAppQuitEvent() const
bool c_KDDockWidgets__flutter__Platform__isProcessingAppQuitEvent(void *thisObj);
// KDDockWidgets::flutter::Platform::name() const
const char *c_KDDockWidgets__flutter__Platform__name(void *thisObj);
// KDDockWidgets::flutter::Platform::onDropIndicatorOverlayCreated(KDDockWidgets::flutter::IndicatorWindow * arg__1)
void c_KDDockWidgets__flutter__Platform__onDropIndicatorOverlayCreated_IndicatorWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::Platform::onDropIndicatorOverlayDestroyed(KDDockWidgets::flutter::IndicatorWindow * arg__1)
void c_KDDockWidgets__flutter__Platform__onDropIndicatorOverlayDestroyed_IndicatorWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::Platform::onFloatingWindowCreated(KDDockWidgets::Core::FloatingWindow * arg__1)
void c_KDDockWidgets__flutter__Platform__onFloatingWindowCreated_FloatingWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::Platform::onFloatingWindowDestroyed(KDDockWidgets::Core::FloatingWindow * arg__1)
void c_KDDockWidgets__flutter__Platform__onFloatingWindowDestroyed_FloatingWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::Platform::onMainWindowCreated(KDDockWidgets::Core::MainWindow * arg__1)
void c_KDDockWidgets__flutter__Platform__onMainWindowCreated_MainWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::Platform::onMainWindowDestroyed(KDDockWidgets::Core::MainWindow * arg__1)
void c_KDDockWidgets__flutter__Platform__onMainWindowDestroyed_MainWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::Platform::pauseForDartDebugger()
void c_KDDockWidgets__flutter__Platform__pauseForDartDebugger(void *thisObj);
// KDDockWidgets::flutter::Platform::pauseForDebugger()
void c_KDDockWidgets__flutter__Platform__pauseForDebugger(void *thisObj);
// KDDockWidgets::flutter::Platform::platformFlutter()
void *c_static_KDDockWidgets__flutter__Platform__platformFlutter();
// KDDockWidgets::flutter::Platform::rebuildWindowOverlay()
void c_KDDockWidgets__flutter__Platform__rebuildWindowOverlay(void *thisObj);
// KDDockWidgets::flutter::Platform::restoreMouseCursor()
void c_KDDockWidgets__flutter__Platform__restoreMouseCursor(void *thisObj);
// KDDockWidgets::flutter::Platform::resumeCoRoutines()
void c_KDDockWidgets__flutter__Platform__resumeCoRoutines(void *thisObj);
// KDDockWidgets::flutter::Platform::runDelayed(int ms, KDDockWidgets::Core::DelayedCall * c)
void c_KDDockWidgets__flutter__Platform__runDelayed_int_DelayedCall(void *thisObj, int ms, void *c_);
// KDDockWidgets::flutter::Platform::runTests()
void c_KDDockWidgets__flutter__Platform__runTests(void *thisObj);
// KDDockWidgets::flutter::Platform::scheduleResumeCoRoutines(int ms) const
void c_KDDockWidgets__flutter__Platform__scheduleResumeCoRoutines_int(void *thisObj, int ms);
// KDDockWidgets::flutter::Platform::screenNumberFor(KDDockWidgets::Core::View * arg__1) const
int c_KDDockWidgets__flutter__Platform__screenNumberFor_View(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::Platform::screenSizeFor(KDDockWidgets::Core::View * arg__1) const
void *c_KDDockWidgets__flutter__Platform__screenSizeFor_View(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::Platform::sendEvent(KDDockWidgets::Core::View * arg__1, KDDockWidgets::Event * arg__2) const
void c_KDDockWidgets__flutter__Platform__sendEvent_View_Event(void *thisObj, void *arg__1_, void *arg__2_);
// KDDockWidgets::flutter::Platform::setCursorPos(QPoint arg__1)
void c_KDDockWidgets__flutter__Platform__setCursorPos_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::Platform::setMouseCursor(Qt::CursorShape arg__1)
void c_KDDockWidgets__flutter__Platform__setMouseCursor_CursorShape(void *thisObj, int arg__1);
// KDDockWidgets::flutter::Platform::startDragDistance_impl() const
int c_KDDockWidgets__flutter__Platform__startDragDistance_impl(void *thisObj);
// KDDockWidgets::flutter::Platform::tests_createFocusableView(KDDockWidgets::Core::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)
void *c_KDDockWidgets__flutter__Platform__tests_createFocusableView_CreateViewOptions_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::flutter::Platform::tests_createNonClosableView(KDDockWidgets::Core::View * parent)
void *c_KDDockWidgets__flutter__Platform__tests_createNonClosableView_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::Platform::tests_createView(KDDockWidgets::Core::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)
void *c_KDDockWidgets__flutter__Platform__tests_createView_CreateViewOptions_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::flutter::Platform::tests_deinitPlatform_impl()
void c_KDDockWidgets__flutter__Platform__tests_deinitPlatform_impl(void *thisObj);
// KDDockWidgets::flutter::Platform::tests_initPlatform_impl()
void c_KDDockWidgets__flutter__Platform__tests_initPlatform_impl(void *thisObj);
// KDDockWidgets::flutter::Platform::ungrabMouse()
void c_KDDockWidgets__flutter__Platform__ungrabMouse(void *thisObj);
// KDDockWidgets::flutter::Platform::uninstallMessageHandler()
void c_KDDockWidgets__flutter__Platform__uninstallMessageHandler(void *thisObj);
// KDDockWidgets::flutter::Platform::usesFallbackMouseGrabber() const
bool c_KDDockWidgets__flutter__Platform__usesFallbackMouseGrabber(void *thisObj);
void c_KDDockWidgets__flutter__Platform__destructor(void *thisObj);
void c_KDDockWidgets__flutter__Platform__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__flutter__Platform_Finalizer(void *cppObj); // KDDockWidgets::Core::Item::Item(KDDockWidgets::Core::View * hostWidget)
void *c_KDDockWidgets__Core__Item__constructor_View(void *hostWidget_);
// KDDockWidgets::Core::Item::asGroupController() const
void *c_KDDockWidgets__Core__Item__asGroupController(void *thisObj);
// KDDockWidgets::Core::Item::checkSanity()
bool c_KDDockWidgets__Core__Item__checkSanity(void *thisObj);
// KDDockWidgets::Core::Item::dumpLayout(int level)
void c_KDDockWidgets__Core__Item__dumpLayout_int(void *thisObj, int level);
// KDDockWidgets::Core::Item::geometry() const
void *c_KDDockWidgets__Core__Item__geometry(void *thisObj);
// KDDockWidgets::Core::Item::guestView() const
void *c_KDDockWidgets__Core__Item__guestView(void *thisObj);
// KDDockWidgets::Core::Item::height() const
int c_KDDockWidgets__Core__Item__height(void *thisObj);
// KDDockWidgets::Core::Item::hostView() const
void *c_KDDockWidgets__Core__Item__hostView(void *thisObj);
// KDDockWidgets::Core::Item::isBeingInserted() const
bool c_KDDockWidgets__Core__Item__isBeingInserted(void *thisObj);
// KDDockWidgets::Core::Item::isContainer() const
bool c_KDDockWidgets__Core__Item__isContainer(void *thisObj);
// KDDockWidgets::Core::Item::isMDI() const
bool c_KDDockWidgets__Core__Item__isMDI(void *thisObj);
// KDDockWidgets::Core::Item::isPlaceholder() const
bool c_KDDockWidgets__Core__Item__isPlaceholder(void *thisObj);
// KDDockWidgets::Core::Item::isRoot() const
bool c_KDDockWidgets__Core__Item__isRoot(void *thisObj);
// KDDockWidgets::Core::Item::isVisible(bool excludeBeingInserted) const
bool c_KDDockWidgets__Core__Item__isVisible_bool(void *thisObj, bool excludeBeingInserted);
// KDDockWidgets::Core::Item::mapFromParent(QPoint arg__1) const
void *c_KDDockWidgets__Core__Item__mapFromParent_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Item::mapFromRoot(QPoint arg__1) const
void *c_KDDockWidgets__Core__Item__mapFromRoot_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Item::mapFromRoot(QRect arg__1) const
void *c_KDDockWidgets__Core__Item__mapFromRoot_QRect(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Item::mapToRoot(QPoint arg__1) const
void *c_KDDockWidgets__Core__Item__mapToRoot_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Item::mapToRoot(QRect arg__1) const
void *c_KDDockWidgets__Core__Item__mapToRoot_QRect(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Item::maxSizeHint() const
void *c_KDDockWidgets__Core__Item__maxSizeHint(void *thisObj);
// KDDockWidgets::Core::Item::minSize() const
void *c_KDDockWidgets__Core__Item__minSize(void *thisObj);
// KDDockWidgets::Core::Item::missingSize() const
void *c_KDDockWidgets__Core__Item__missingSize(void *thisObj);
// KDDockWidgets::Core::Item::pos() const
void *c_KDDockWidgets__Core__Item__pos(void *thisObj);
// KDDockWidgets::Core::Item::rect() const
void *c_KDDockWidgets__Core__Item__rect(void *thisObj);
// KDDockWidgets::Core::Item::ref()
void c_KDDockWidgets__Core__Item__ref(void *thisObj);
// KDDockWidgets::Core::Item::refCount() const
int c_KDDockWidgets__Core__Item__refCount(void *thisObj);
// KDDockWidgets::Core::Item::restore(KDDockWidgets::Core::View * guestView)
void c_KDDockWidgets__Core__Item__restore_View(void *thisObj, void *guestView_);
// KDDockWidgets::Core::Item::setBeingInserted(bool arg__1)
void c_KDDockWidgets__Core__Item__setBeingInserted_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::Item::setGeometry(QRect rect)
void c_KDDockWidgets__Core__Item__setGeometry_QRect(void *thisObj, void *rect_);
// KDDockWidgets::Core::Item::setGeometry_recursive(QRect rect)
void c_KDDockWidgets__Core__Item__setGeometry_recursive_QRect(void *thisObj, void *rect_);
// KDDockWidgets::Core::Item::setGuestView(KDDockWidgets::Core::View * arg__1)
void c_KDDockWidgets__Core__Item__setGuestView_View(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Item::setHostView(KDDockWidgets::Core::View * arg__1)
void c_KDDockWidgets__Core__Item__setHostView_View(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Item::setIsVisible(bool arg__1)
void c_KDDockWidgets__Core__Item__setIsVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::Item::setMaxSizeHint(QSize arg__1)
void c_KDDockWidgets__Core__Item__setMaxSizeHint_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Item::setMinSize(QSize arg__1)
void c_KDDockWidgets__Core__Item__setMinSize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Item::setPos(QPoint arg__1)
void c_KDDockWidgets__Core__Item__setPos_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Item::setSize(QSize arg__1)
void c_KDDockWidgets__Core__Item__setSize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Item::size() const
void *c_KDDockWidgets__Core__Item__size(void *thisObj);
// KDDockWidgets::Core::Item::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__Item__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Core::Item::turnIntoPlaceholder()
void c_KDDockWidgets__Core__Item__turnIntoPlaceholder(void *thisObj);
// KDDockWidgets::Core::Item::unref()
void c_KDDockWidgets__Core__Item__unref(void *thisObj);
// KDDockWidgets::Core::Item::updateWidgetGeometries()
void c_KDDockWidgets__Core__Item__updateWidgetGeometries(void *thisObj);
// KDDockWidgets::Core::Item::visibleCount_recursive() const
int c_KDDockWidgets__Core__Item__visibleCount_recursive(void *thisObj);
// KDDockWidgets::Core::Item::width() const
int c_KDDockWidgets__Core__Item__width(void *thisObj);
// KDDockWidgets::Core::Item::x() const
int c_KDDockWidgets__Core__Item__x(void *thisObj);
// KDDockWidgets::Core::Item::y() const
int c_KDDockWidgets__Core__Item__y(void *thisObj);
void c_KDDockWidgets__Core__Item__destructor(void *thisObj);
int c_static_KDDockWidgets__Core__Item___get_separatorThickness();
bool c_static_KDDockWidgets__Core__Item___get_s_silenceSanityChecks();
bool c_KDDockWidgets__Core__Item___get_m_isContainer(void *thisObj);
bool c_KDDockWidgets__Core__Item___get_m_isSettingGuest(void *thisObj);
void c_static_KDDockWidgets__Core__Item___set_separatorThickness_int(int separatorThickness_);
void c_static_KDDockWidgets__Core__Item___set_s_silenceSanityChecks_bool(bool s_silenceSanityChecks_);
void c_KDDockWidgets__Core__Item___set_m_isSettingGuest_bool(void *thisObj, bool m_isSettingGuest_);
void c_KDDockWidgets__Core__Item__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__Item_Finalizer(void *cppObj); // KDDockWidgets::Core::DelayedCall::DelayedCall()
void *c_KDDockWidgets__Core__DelayedCall__constructor();
// KDDockWidgets::Core::DelayedCall::call()
void c_KDDockWidgets__Core__DelayedCall__call(void *thisObj);
void c_KDDockWidgets__Core__DelayedCall__destructor(void *thisObj);
void c_KDDockWidgets__Core__DelayedCall__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__DelayedCall_Finalizer(void *cppObj); // KDDockWidgets::Core::CreateViewOptions::CreateViewOptions()
void *c_KDDockWidgets__Core__CreateViewOptions__constructor();
// KDDockWidgets::Core::CreateViewOptions::getMaxSize() const
void *c_KDDockWidgets__Core__CreateViewOptions__getMaxSize(void *thisObj);
// KDDockWidgets::Core::CreateViewOptions::getMinSize() const
void *c_KDDockWidgets__Core__CreateViewOptions__getMinSize(void *thisObj);
// KDDockWidgets::Core::CreateViewOptions::getSize() const
void *c_KDDockWidgets__Core__CreateViewOptions__getSize(void *thisObj);
void c_KDDockWidgets__Core__CreateViewOptions__destructor(void *thisObj);
bool c_KDDockWidgets__Core__CreateViewOptions___get_isVisible(void *thisObj);
bool c_KDDockWidgets__Core__CreateViewOptions___get_createWindow(void *thisObj);
void c_KDDockWidgets__Core__CreateViewOptions___set_isVisible_bool(void *thisObj, bool isVisible_);
void c_KDDockWidgets__Core__CreateViewOptions___set_createWindow_bool(void *thisObj, bool createWindow_);
void c_KDDockWidgets__Core__CreateViewOptions_Finalizer(void *cppObj); // KDDockWidgets::Core::Controller::Controller(KDDockWidgets::Core::ViewType type, KDDockWidgets::Core::View * arg__2)
void *c_KDDockWidgets__Core__Controller__constructor_ViewType_View(int type, void *arg__2_);
// KDDockWidgets::Core::Controller::close()
bool c_KDDockWidgets__Core__Controller__close(void *thisObj);
// KDDockWidgets::Core::Controller::destroyLater()
void c_KDDockWidgets__Core__Controller__destroyLater(void *thisObj);
// KDDockWidgets::Core::Controller::geometry() const
void *c_KDDockWidgets__Core__Controller__geometry(void *thisObj);
// KDDockWidgets::Core::Controller::height() const
int c_KDDockWidgets__Core__Controller__height(void *thisObj);
// KDDockWidgets::Core::Controller::inDtor() const
bool c_KDDockWidgets__Core__Controller__inDtor(void *thisObj);
// KDDockWidgets::Core::Controller::isVisible() const
bool c_KDDockWidgets__Core__Controller__isVisible(void *thisObj);
// KDDockWidgets::Core::Controller::mapToGlobal(QPoint arg__1) const
void *c_KDDockWidgets__Core__Controller__mapToGlobal_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Controller::parentViewChanged(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__Controller__parentViewChanged_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::Controller::pos() const
void *c_KDDockWidgets__Core__Controller__pos(void *thisObj);
// KDDockWidgets::Core::Controller::rect() const
void *c_KDDockWidgets__Core__Controller__rect(void *thisObj);
// KDDockWidgets::Core::Controller::setParentView(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__Controller__setParentView_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::Controller::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__Controller__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::Controller::setVisible(bool arg__1)
void c_KDDockWidgets__Core__Controller__setVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::Controller::show() const
void c_KDDockWidgets__Core__Controller__show(void *thisObj);
// KDDockWidgets::Core::Controller::size() const
void *c_KDDockWidgets__Core__Controller__size(void *thisObj);
// KDDockWidgets::Core::Controller::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__Controller__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Core::Controller::type() const
int c_KDDockWidgets__Core__Controller__type(void *thisObj);
// KDDockWidgets::Core::Controller::view() const
void *c_KDDockWidgets__Core__Controller__view(void *thisObj);
// KDDockWidgets::Core::Controller::width() const
int c_KDDockWidgets__Core__Controller__width(void *thisObj);
// KDDockWidgets::Core::Controller::x() const
int c_KDDockWidgets__Core__Controller__x(void *thisObj);
// KDDockWidgets::Core::Controller::y() const
int c_KDDockWidgets__Core__Controller__y(void *thisObj);
void c_KDDockWidgets__Core__Controller__destructor(void *thisObj);
void c_KDDockWidgets__Core__Controller__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__Controller_Finalizer(void *cppObj); // KDDockWidgets::Core::View::activateWindow()
void c_KDDockWidgets__Core__View__activateWindow(void *thisObj);
// KDDockWidgets::Core::View::asDockWidgetController() const
void *c_KDDockWidgets__Core__View__asDockWidgetController(void *thisObj);
// KDDockWidgets::Core::View::asDropAreaController() const
void *c_KDDockWidgets__Core__View__asDropAreaController(void *thisObj);
// KDDockWidgets::Core::View::asFloatingWindowController() const
void *c_KDDockWidgets__Core__View__asFloatingWindowController(void *thisObj);
// KDDockWidgets::Core::View::asGroupController() const
void *c_KDDockWidgets__Core__View__asGroupController(void *thisObj);
// KDDockWidgets::Core::View::asLayout() const
void *c_KDDockWidgets__Core__View__asLayout(void *thisObj);
// KDDockWidgets::Core::View::asMainWindowController() const
void *c_KDDockWidgets__Core__View__asMainWindowController(void *thisObj);
// KDDockWidgets::Core::View::asStackController() const
void *c_KDDockWidgets__Core__View__asStackController(void *thisObj);
// KDDockWidgets::Core::View::asTabBarController() const
void *c_KDDockWidgets__Core__View__asTabBarController(void *thisObj);
// KDDockWidgets::Core::View::asTitleBarController() const
void *c_KDDockWidgets__Core__View__asTitleBarController(void *thisObj);
// KDDockWidgets::Core::View::close()
bool c_KDDockWidgets__Core__View__close(void *thisObj);
// KDDockWidgets::Core::View::controller() const
void *c_KDDockWidgets__Core__View__controller(void *thisObj);
// KDDockWidgets::Core::View::createPlatformWindow()
void c_KDDockWidgets__Core__View__createPlatformWindow(void *thisObj);
// KDDockWidgets::Core::View::deliverViewEventToFilters(KDDockWidgets::Event * e)
bool c_KDDockWidgets__Core__View__deliverViewEventToFilters_Event(void *thisObj, void *e_);
// KDDockWidgets::Core::View::dumpDebug()
void c_KDDockWidgets__Core__View__dumpDebug(void *thisObj);
// KDDockWidgets::Core::View::equals(const KDDockWidgets::Core::View * one, const KDDockWidgets::Core::View * two)
bool c_static_KDDockWidgets__Core__View__equals_View_View(void *one_, void *two_);
// KDDockWidgets::Core::View::equals(const KDDockWidgets::Core::View * other) const
bool c_KDDockWidgets__Core__View__equals_View(void *thisObj, void *other_);
// KDDockWidgets::Core::View::firstParentOfType(KDDockWidgets::Core::View * view, KDDockWidgets::Core::ViewType arg__2)
void *c_static_KDDockWidgets__Core__View__firstParentOfType_View_ViewType(void *view_, int arg__2);
// KDDockWidgets::Core::View::flags() const
int c_KDDockWidgets__Core__View__flags(void *thisObj);
// KDDockWidgets::Core::View::geometry() const
void *c_KDDockWidgets__Core__View__geometry(void *thisObj);
// KDDockWidgets::Core::View::grabMouse()
void c_KDDockWidgets__Core__View__grabMouse(void *thisObj);
// KDDockWidgets::Core::View::hardcodedMinimumSize()
void *c_static_KDDockWidgets__Core__View__hardcodedMinimumSize();
// KDDockWidgets::Core::View::hasFocus() const
bool c_KDDockWidgets__Core__View__hasFocus(void *thisObj);
// KDDockWidgets::Core::View::height() const
int c_KDDockWidgets__Core__View__height(void *thisObj);
// KDDockWidgets::Core::View::hide()
void c_KDDockWidgets__Core__View__hide(void *thisObj);
// KDDockWidgets::Core::View::inDtor() const
bool c_KDDockWidgets__Core__View__inDtor(void *thisObj);
// KDDockWidgets::Core::View::init()
void c_KDDockWidgets__Core__View__init(void *thisObj);
// KDDockWidgets::Core::View::isActiveWindow() const
bool c_KDDockWidgets__Core__View__isActiveWindow(void *thisObj);
// KDDockWidgets::Core::View::isExplicitlyHidden() const
bool c_KDDockWidgets__Core__View__isExplicitlyHidden(void *thisObj);
// KDDockWidgets::Core::View::isMaximized() const
bool c_KDDockWidgets__Core__View__isMaximized(void *thisObj);
// KDDockWidgets::Core::View::isMinimized() const
bool c_KDDockWidgets__Core__View__isMinimized(void *thisObj);
// KDDockWidgets::Core::View::isNull() const
bool c_KDDockWidgets__Core__View__isNull(void *thisObj);
// KDDockWidgets::Core::View::isRootView() const
bool c_KDDockWidgets__Core__View__isRootView(void *thisObj);
// KDDockWidgets::Core::View::isVisible() const
bool c_KDDockWidgets__Core__View__isVisible(void *thisObj);
// KDDockWidgets::Core::View::mapFromGlobal(QPoint arg__1) const
void *c_KDDockWidgets__Core__View__mapFromGlobal_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::View::mapTo(KDDockWidgets::Core::View * arg__1, QPoint arg__2) const
void *c_KDDockWidgets__Core__View__mapTo_View_QPoint(void *thisObj, void *arg__1_, void *arg__2_);
// KDDockWidgets::Core::View::mapToGlobal(QPoint arg__1) const
void *c_KDDockWidgets__Core__View__mapToGlobal_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::View::maxSizeHint() const
void *c_KDDockWidgets__Core__View__maxSizeHint(void *thisObj);
// KDDockWidgets::Core::View::minSize() const
void *c_KDDockWidgets__Core__View__minSize(void *thisObj);
// KDDockWidgets::Core::View::minimumHeight() const
int c_KDDockWidgets__Core__View__minimumHeight(void *thisObj);
// KDDockWidgets::Core::View::minimumWidth() const
int c_KDDockWidgets__Core__View__minimumWidth(void *thisObj);
// KDDockWidgets::Core::View::move(QPoint arg__1)
void c_KDDockWidgets__Core__View__move_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::View::move(int x, int y)
void c_KDDockWidgets__Core__View__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::Core::View::normalGeometry() const
void *c_KDDockWidgets__Core__View__normalGeometry(void *thisObj);
// KDDockWidgets::Core::View::onResize(QSize arg__1)
bool c_KDDockWidgets__Core__View__onResize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::View::onResize(int h, int w)
bool c_KDDockWidgets__Core__View__onResize_int_int(void *thisObj, int h, int w);
// KDDockWidgets::Core::View::pos() const
void *c_KDDockWidgets__Core__View__pos(void *thisObj);
// KDDockWidgets::Core::View::raise()
void c_KDDockWidgets__Core__View__raise(void *thisObj);
// KDDockWidgets::Core::View::raiseAndActivate()
void c_KDDockWidgets__Core__View__raiseAndActivate(void *thisObj);
// KDDockWidgets::Core::View::rect() const
void *c_KDDockWidgets__Core__View__rect(void *thisObj);
// KDDockWidgets::Core::View::releaseKeyboard()
void c_KDDockWidgets__Core__View__releaseKeyboard(void *thisObj);
// KDDockWidgets::Core::View::releaseMouse()
void c_KDDockWidgets__Core__View__releaseMouse(void *thisObj);
// KDDockWidgets::Core::View::resize(QSize arg__1)
void c_KDDockWidgets__Core__View__resize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::View::resize(int w, int h)
void c_KDDockWidgets__Core__View__resize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::Core::View::setCursor(Qt::CursorShape arg__1)
void c_KDDockWidgets__Core__View__setCursor_CursorShape(void *thisObj, int arg__1);
// KDDockWidgets::Core::View::setFixedHeight(int arg__1)
void c_KDDockWidgets__Core__View__setFixedHeight_int(void *thisObj, int arg__1);
// KDDockWidgets::Core::View::setFixedWidth(int arg__1)
void c_KDDockWidgets__Core__View__setFixedWidth_int(void *thisObj, int arg__1);
// KDDockWidgets::Core::View::setGeometry(QRect arg__1)
void c_KDDockWidgets__Core__View__setGeometry_QRect(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::View::setHeight(int height)
void c_KDDockWidgets__Core__View__setHeight_int(void *thisObj, int height);
// KDDockWidgets::Core::View::setMaximumSize(QSize sz)
void c_KDDockWidgets__Core__View__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::Core::View::setMinimumSize(QSize arg__1)
void c_KDDockWidgets__Core__View__setMinimumSize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::View::setMouseTracking(bool arg__1)
void c_KDDockWidgets__Core__View__setMouseTracking_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::View::setParent(KDDockWidgets::Core::View * arg__1)
void c_KDDockWidgets__Core__View__setParent_View(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::View::setSize(QSize arg__1)
void c_KDDockWidgets__Core__View__setSize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::View::setSize(int width, int height)
void c_KDDockWidgets__Core__View__setSize_int_int(void *thisObj, int width, int height);
// KDDockWidgets::Core::View::setViewName(const QString & arg__1)
void c_KDDockWidgets__Core__View__setViewName_QString(void *thisObj, const char *arg__1_);
// KDDockWidgets::Core::View::setVisible(bool arg__1)
void c_KDDockWidgets__Core__View__setVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::View::setWidth(int width)
void c_KDDockWidgets__Core__View__setWidth_int(void *thisObj, int width);
// KDDockWidgets::Core::View::setWindowOpacity(double arg__1)
void c_KDDockWidgets__Core__View__setWindowOpacity_double(void *thisObj, double arg__1);
// KDDockWidgets::Core::View::setWindowTitle(const QString & title)
void c_KDDockWidgets__Core__View__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::Core::View::setZOrder(int arg__1)
void c_KDDockWidgets__Core__View__setZOrder_int(void *thisObj, int arg__1);
// KDDockWidgets::Core::View::show()
void c_KDDockWidgets__Core__View__show(void *thisObj);
// KDDockWidgets::Core::View::showMaximized()
void c_KDDockWidgets__Core__View__showMaximized(void *thisObj);
// KDDockWidgets::Core::View::showMinimized()
void c_KDDockWidgets__Core__View__showMinimized(void *thisObj);
// KDDockWidgets::Core::View::showNormal()
void c_KDDockWidgets__Core__View__showNormal(void *thisObj);
// KDDockWidgets::Core::View::size() const
void *c_KDDockWidgets__Core__View__size(void *thisObj);
// KDDockWidgets::Core::View::update()
void c_KDDockWidgets__Core__View__update(void *thisObj);
// KDDockWidgets::Core::View::viewName() const
void *c_KDDockWidgets__Core__View__viewName(void *thisObj);
// KDDockWidgets::Core::View::width() const
int c_KDDockWidgets__Core__View__width(void *thisObj);
// KDDockWidgets::Core::View::x() const
int c_KDDockWidgets__Core__View__x(void *thisObj);
// KDDockWidgets::Core::View::y() const
int c_KDDockWidgets__Core__View__y(void *thisObj);
void c_KDDockWidgets__Core__View__destructor(void *thisObj);
void c_KDDockWidgets__Core__View__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__View_Finalizer(void *cppObj); // KDDockWidgets::flutter::View::View(KDDockWidgets::Core::Controller * controller, KDDockWidgets::Core::ViewType type, KDDockWidgets::Core::View * arg__3, Qt::WindowFlags windowFlags)
void *c_KDDockWidgets__flutter__View__constructor_Controller_ViewType_View_WindowFlags(void *controller_, int type, void *arg__3_, int windowFlags);
// KDDockWidgets::flutter::View::activateWindow()
void c_KDDockWidgets__flutter__View__activateWindow(void *thisObj);
// KDDockWidgets::flutter::View::close()
bool c_KDDockWidgets__flutter__View__close(void *thisObj);
// KDDockWidgets::flutter::View::createPlatformWindow()
void c_KDDockWidgets__flutter__View__createPlatformWindow(void *thisObj);
// KDDockWidgets::flutter::View::flags() const
int c_KDDockWidgets__flutter__View__flags(void *thisObj);
// KDDockWidgets::flutter::View::geometry() const
void *c_KDDockWidgets__flutter__View__geometry(void *thisObj);
// KDDockWidgets::flutter::View::grabMouse()
void c_KDDockWidgets__flutter__View__grabMouse(void *thisObj);
// KDDockWidgets::flutter::View::hasFocus() const
bool c_KDDockWidgets__flutter__View__hasFocus(void *thisObj);
// KDDockWidgets::flutter::View::hide()
void c_KDDockWidgets__flutter__View__hide(void *thisObj);
// KDDockWidgets::flutter::View::init()
void c_KDDockWidgets__flutter__View__init(void *thisObj);
// KDDockWidgets::flutter::View::isActiveWindow() const
bool c_KDDockWidgets__flutter__View__isActiveWindow(void *thisObj);
// KDDockWidgets::flutter::View::isExplicitlyHidden() const
bool c_KDDockWidgets__flutter__View__isExplicitlyHidden(void *thisObj);
// KDDockWidgets::flutter::View::isMaximized() const
bool c_KDDockWidgets__flutter__View__isMaximized(void *thisObj);
// KDDockWidgets::flutter::View::isMinimized() const
bool c_KDDockWidgets__flutter__View__isMinimized(void *thisObj);
// KDDockWidgets::flutter::View::isMounted() const
bool c_KDDockWidgets__flutter__View__isMounted(void *thisObj);
// KDDockWidgets::flutter::View::isNull() const
bool c_KDDockWidgets__flutter__View__isNull(void *thisObj);
// KDDockWidgets::flutter::View::isRootView() const
bool c_KDDockWidgets__flutter__View__isRootView(void *thisObj);
// KDDockWidgets::flutter::View::isVisible() const
bool c_KDDockWidgets__flutter__View__isVisible(void *thisObj);
// KDDockWidgets::flutter::View::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__flutter__View__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::flutter::View::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
void *c_KDDockWidgets__flutter__View__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_);
// KDDockWidgets::flutter::View::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__flutter__View__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::flutter::View::maxSizeHint() const
void *c_KDDockWidgets__flutter__View__maxSizeHint(void *thisObj);
// KDDockWidgets::flutter::View::minSize() const
void *c_KDDockWidgets__flutter__View__minSize(void *thisObj);
// KDDockWidgets::flutter::View::move(int x, int y)
void c_KDDockWidgets__flutter__View__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::flutter::View::normalGeometry() const
void *c_KDDockWidgets__flutter__View__normalGeometry(void *thisObj);
// KDDockWidgets::flutter::View::onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__View__onChildAdded_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::View::onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__View__onChildRemoved_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::View::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__View__onChildVisibilityChanged_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::View::onFlutterWidgetResized(int w, int h)
bool c_KDDockWidgets__flutter__View__onFlutterWidgetResized_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::View::onGeometryChanged()
void c_KDDockWidgets__flutter__View__onGeometryChanged(void *thisObj);
// KDDockWidgets::flutter::View::onMouseEvent(KDDockWidgets::Event::Type eventType, QPoint localPos, QPoint globalPos, bool leftIsPressed)
void c_KDDockWidgets__flutter__View__onMouseEvent_Type_QPoint_QPoint_bool(void *thisObj, int eventType, void *localPos_, void *globalPos_, bool leftIsPressed);
// KDDockWidgets::flutter::View::onRebuildRequested()
void c_KDDockWidgets__flutter__View__onRebuildRequested(void *thisObj);
// KDDockWidgets::flutter::View::onResize(int h, int w)
bool c_KDDockWidgets__flutter__View__onResize_int_int(void *thisObj, int h, int w);
// KDDockWidgets::flutter::View::raise()
void c_KDDockWidgets__flutter__View__raise(void *thisObj);
// KDDockWidgets::flutter::View::raiseAndActivate()
void c_KDDockWidgets__flutter__View__raiseAndActivate(void *thisObj);
// KDDockWidgets::flutter::View::raiseChild(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__View__raiseChild_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::View::raiseWindow(KDDockWidgets::Core::View * rootView)
void c_KDDockWidgets__flutter__View__raiseWindow_View(void *thisObj, void *rootView_);
// KDDockWidgets::flutter::View::releaseKeyboard()
void c_KDDockWidgets__flutter__View__releaseKeyboard(void *thisObj);
// KDDockWidgets::flutter::View::releaseMouse()
void c_KDDockWidgets__flutter__View__releaseMouse(void *thisObj);
// KDDockWidgets::flutter::View::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__View__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::flutter::View::setFixedHeight(int h)
void c_KDDockWidgets__flutter__View__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::View::setFixedWidth(int w)
void c_KDDockWidgets__flutter__View__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::View::setGeometry(QRect geometry)
void c_KDDockWidgets__flutter__View__setGeometry_QRect(void *thisObj, void *geometry_);
// KDDockWidgets::flutter::View::setHeight(int h)
void c_KDDockWidgets__flutter__View__setHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::View::setMaximumSize(QSize sz)
void c_KDDockWidgets__flutter__View__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::View::setMinimumSize(QSize sz)
void c_KDDockWidgets__flutter__View__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::View::setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__View__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::flutter::View::setNormalGeometry(QRect geo)
void c_KDDockWidgets__flutter__View__setNormalGeometry_QRect(void *thisObj, void *geo_);
// KDDockWidgets::flutter::View::setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__View__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::View::setSize(int w, int h)
void c_KDDockWidgets__flutter__View__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::View::setViewName(const QString & name)
void c_KDDockWidgets__flutter__View__setViewName_QString(void *thisObj, const char *name_);
// KDDockWidgets::flutter::View::setVisible(bool visible)
void c_KDDockWidgets__flutter__View__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::flutter::View::setWidth(int w)
void c_KDDockWidgets__flutter__View__setWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::View::setWindowOpacity(double v)
void c_KDDockWidgets__flutter__View__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::flutter::View::setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__View__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::flutter::View::setZOrder(int z)
void c_KDDockWidgets__flutter__View__setZOrder_int(void *thisObj, int z);
// KDDockWidgets::flutter::View::show()
void c_KDDockWidgets__flutter__View__show(void *thisObj);
// KDDockWidgets::flutter::View::showMaximized()
void c_KDDockWidgets__flutter__View__showMaximized(void *thisObj);
// KDDockWidgets::flutter::View::showMinimized()
void c_KDDockWidgets__flutter__View__showMinimized(void *thisObj);
// KDDockWidgets::flutter::View::showNormal()
void c_KDDockWidgets__flutter__View__showNormal(void *thisObj);
// KDDockWidgets::flutter::View::update()
void c_KDDockWidgets__flutter__View__update(void *thisObj);
// KDDockWidgets::flutter::View::updateGeometry()
void c_KDDockWidgets__flutter__View__updateGeometry(void *thisObj);
// KDDockWidgets::flutter::View::viewName() const
void *c_KDDockWidgets__flutter__View__viewName(void *thisObj);
void c_KDDockWidgets__flutter__View__destructor(void *thisObj);
void c_KDDockWidgets__flutter__View__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__flutter__View_Finalizer(void *cppObj); // KDDockWidgets::flutter::TitleBar::TitleBar(KDDockWidgets::Core::TitleBar * controller, KDDockWidgets::Core::View * parent)
void *c_KDDockWidgets__flutter__TitleBar__constructor_TitleBar_View(void *controller_, void *parent_);
// KDDockWidgets::flutter::TitleBar::activateWindow()
void c_KDDockWidgets__flutter__TitleBar__activateWindow(void *thisObj);
// KDDockWidgets::flutter::TitleBar::close()
bool c_KDDockWidgets__flutter__TitleBar__close(void *thisObj);
// KDDockWidgets::flutter::TitleBar::createPlatformWindow()
void c_KDDockWidgets__flutter__TitleBar__createPlatformWindow(void *thisObj);
// KDDockWidgets::flutter::TitleBar::flags() const
int c_KDDockWidgets__flutter__TitleBar__flags(void *thisObj);
// KDDockWidgets::flutter::TitleBar::geometry() const
void *c_KDDockWidgets__flutter__TitleBar__geometry(void *thisObj);
// KDDockWidgets::flutter::TitleBar::grabMouse()
void c_KDDockWidgets__flutter__TitleBar__grabMouse(void *thisObj);
// KDDockWidgets::flutter::TitleBar::hasFocus() const
bool c_KDDockWidgets__flutter__TitleBar__hasFocus(void *thisObj);
// KDDockWidgets::flutter::TitleBar::hide()
void c_KDDockWidgets__flutter__TitleBar__hide(void *thisObj);
// KDDockWidgets::flutter::TitleBar::init()
void c_KDDockWidgets__flutter__TitleBar__init(void *thisObj);
// KDDockWidgets::flutter::TitleBar::isActiveWindow() const
bool c_KDDockWidgets__flutter__TitleBar__isActiveWindow(void *thisObj);
// KDDockWidgets::flutter::TitleBar::isCloseButtonEnabled() const
bool c_KDDockWidgets__flutter__TitleBar__isCloseButtonEnabled(void *thisObj);
// KDDockWidgets::flutter::TitleBar::isCloseButtonVisible() const
bool c_KDDockWidgets__flutter__TitleBar__isCloseButtonVisible(void *thisObj);
// KDDockWidgets::flutter::TitleBar::isExplicitlyHidden() const
bool c_KDDockWidgets__flutter__TitleBar__isExplicitlyHidden(void *thisObj);
// KDDockWidgets::flutter::TitleBar::isFloatButtonVisible() const
bool c_KDDockWidgets__flutter__TitleBar__isFloatButtonVisible(void *thisObj);
// KDDockWidgets::flutter::TitleBar::isMaximized() const
bool c_KDDockWidgets__flutter__TitleBar__isMaximized(void *thisObj);
// KDDockWidgets::flutter::TitleBar::isMinimized() const
bool c_KDDockWidgets__flutter__TitleBar__isMinimized(void *thisObj);
// KDDockWidgets::flutter::TitleBar::isMounted() const
bool c_KDDockWidgets__flutter__TitleBar__isMounted(void *thisObj);
// KDDockWidgets::flutter::TitleBar::isNull() const
bool c_KDDockWidgets__flutter__TitleBar__isNull(void *thisObj);
// KDDockWidgets::flutter::TitleBar::isRootView() const
bool c_KDDockWidgets__flutter__TitleBar__isRootView(void *thisObj);
// KDDockWidgets::flutter::TitleBar::isVisible() const
bool c_KDDockWidgets__flutter__TitleBar__isVisible(void *thisObj);
// KDDockWidgets::flutter::TitleBar::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__flutter__TitleBar__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::flutter::TitleBar::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
void *c_KDDockWidgets__flutter__TitleBar__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_);
// KDDockWidgets::flutter::TitleBar::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__flutter__TitleBar__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::flutter::TitleBar::maxSizeHint() const
void *c_KDDockWidgets__flutter__TitleBar__maxSizeHint(void *thisObj);
// KDDockWidgets::flutter::TitleBar::minSize() const
void *c_KDDockWidgets__flutter__TitleBar__minSize(void *thisObj);
// KDDockWidgets::flutter::TitleBar::move(int x, int y)
void c_KDDockWidgets__flutter__TitleBar__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::flutter::TitleBar::normalGeometry() const
void *c_KDDockWidgets__flutter__TitleBar__normalGeometry(void *thisObj);
// KDDockWidgets::flutter::TitleBar::onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__TitleBar__onChildAdded_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::TitleBar::onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__TitleBar__onChildRemoved_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::TitleBar::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__TitleBar__onChildVisibilityChanged_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::TitleBar::onGeometryChanged()
void c_KDDockWidgets__flutter__TitleBar__onGeometryChanged(void *thisObj);
// KDDockWidgets::flutter::TitleBar::onRebuildRequested()
void c_KDDockWidgets__flutter__TitleBar__onRebuildRequested(void *thisObj);
// KDDockWidgets::flutter::TitleBar::onResize(int h, int w)
bool c_KDDockWidgets__flutter__TitleBar__onResize_int_int(void *thisObj, int h, int w);
// KDDockWidgets::flutter::TitleBar::onTitleBarChanged(const QString & arg__1)
void c_KDDockWidgets__flutter__TitleBar__onTitleBarChanged_QString(void *thisObj, const char *arg__1_);
// KDDockWidgets::flutter::TitleBar::raise()
void c_KDDockWidgets__flutter__TitleBar__raise(void *thisObj);
// KDDockWidgets::flutter::TitleBar::raiseAndActivate()
void c_KDDockWidgets__flutter__TitleBar__raiseAndActivate(void *thisObj);
// KDDockWidgets::flutter::TitleBar::raiseChild(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__TitleBar__raiseChild_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::TitleBar::raiseWindow(KDDockWidgets::Core::View * rootView)
void c_KDDockWidgets__flutter__TitleBar__raiseWindow_View(void *thisObj, void *rootView_);
// KDDockWidgets::flutter::TitleBar::releaseKeyboard()
void c_KDDockWidgets__flutter__TitleBar__releaseKeyboard(void *thisObj);
// KDDockWidgets::flutter::TitleBar::releaseMouse()
void c_KDDockWidgets__flutter__TitleBar__releaseMouse(void *thisObj);
// KDDockWidgets::flutter::TitleBar::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__TitleBar__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::flutter::TitleBar::setFixedHeight(int h)
void c_KDDockWidgets__flutter__TitleBar__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::TitleBar::setFixedWidth(int w)
void c_KDDockWidgets__flutter__TitleBar__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::TitleBar::setGeometry(QRect geometry)
void c_KDDockWidgets__flutter__TitleBar__setGeometry_QRect(void *thisObj, void *geometry_);
// KDDockWidgets::flutter::TitleBar::setHeight(int h)
void c_KDDockWidgets__flutter__TitleBar__setHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::TitleBar::setMaximumSize(QSize sz)
void c_KDDockWidgets__flutter__TitleBar__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::TitleBar::setMinimumSize(QSize sz)
void c_KDDockWidgets__flutter__TitleBar__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::TitleBar::setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__TitleBar__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::flutter::TitleBar::setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__TitleBar__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::TitleBar::setSize(int w, int h)
void c_KDDockWidgets__flutter__TitleBar__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::TitleBar::setViewName(const QString & name)
void c_KDDockWidgets__flutter__TitleBar__setViewName_QString(void *thisObj, const char *name_);
// KDDockWidgets::flutter::TitleBar::setVisible(bool visible)
void c_KDDockWidgets__flutter__TitleBar__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::flutter::TitleBar::setWidth(int w)
void c_KDDockWidgets__flutter__TitleBar__setWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::TitleBar::setWindowOpacity(double v)
void c_KDDockWidgets__flutter__TitleBar__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::flutter::TitleBar::setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__TitleBar__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::flutter::TitleBar::setZOrder(int z)
void c_KDDockWidgets__flutter__TitleBar__setZOrder_int(void *thisObj, int z);
// KDDockWidgets::flutter::TitleBar::show()
void c_KDDockWidgets__flutter__TitleBar__show(void *thisObj);
// KDDockWidgets::flutter::TitleBar::showMaximized()
void c_KDDockWidgets__flutter__TitleBar__showMaximized(void *thisObj);
// KDDockWidgets::flutter::TitleBar::showMinimized()
void c_KDDockWidgets__flutter__TitleBar__showMinimized(void *thisObj);
// KDDockWidgets::flutter::TitleBar::showNormal()
void c_KDDockWidgets__flutter__TitleBar__showNormal(void *thisObj);
// KDDockWidgets::flutter::TitleBar::update()
void c_KDDockWidgets__flutter__TitleBar__update(void *thisObj);
// KDDockWidgets::flutter::TitleBar::viewName() const
void *c_KDDockWidgets__flutter__TitleBar__viewName(void *thisObj);
void c_KDDockWidgets__flutter__TitleBar__destructor(void *thisObj);
void c_KDDockWidgets__flutter__TitleBar__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__flutter__TitleBar_Finalizer(void *cppObj); // KDDockWidgets::flutter::TabBar::TabBar(KDDockWidgets::Core::TabBar * controller, KDDockWidgets::Core::View * parent)
void *c_KDDockWidgets__flutter__TabBar__constructor_TabBar_View(void *controller_, void *parent_);
// KDDockWidgets::flutter::TabBar::activateWindow()
void c_KDDockWidgets__flutter__TabBar__activateWindow(void *thisObj);
// KDDockWidgets::flutter::TabBar::close()
bool c_KDDockWidgets__flutter__TabBar__close(void *thisObj);
// KDDockWidgets::flutter::TabBar::createPlatformWindow()
void c_KDDockWidgets__flutter__TabBar__createPlatformWindow(void *thisObj);
// KDDockWidgets::flutter::TabBar::flags() const
int c_KDDockWidgets__flutter__TabBar__flags(void *thisObj);
// KDDockWidgets::flutter::TabBar::geometry() const
void *c_KDDockWidgets__flutter__TabBar__geometry(void *thisObj);
// KDDockWidgets::flutter::TabBar::grabMouse()
void c_KDDockWidgets__flutter__TabBar__grabMouse(void *thisObj);
// KDDockWidgets::flutter::TabBar::hasFocus() const
bool c_KDDockWidgets__flutter__TabBar__hasFocus(void *thisObj);
// KDDockWidgets::flutter::TabBar::hide()
void c_KDDockWidgets__flutter__TabBar__hide(void *thisObj);
// KDDockWidgets::flutter::TabBar::init()
void c_KDDockWidgets__flutter__TabBar__init(void *thisObj);
// KDDockWidgets::flutter::TabBar::isActiveWindow() const
bool c_KDDockWidgets__flutter__TabBar__isActiveWindow(void *thisObj);
// KDDockWidgets::flutter::TabBar::isExplicitlyHidden() const
bool c_KDDockWidgets__flutter__TabBar__isExplicitlyHidden(void *thisObj);
// KDDockWidgets::flutter::TabBar::isMaximized() const
bool c_KDDockWidgets__flutter__TabBar__isMaximized(void *thisObj);
// KDDockWidgets::flutter::TabBar::isMinimized() const
bool c_KDDockWidgets__flutter__TabBar__isMinimized(void *thisObj);
// KDDockWidgets::flutter::TabBar::isMounted() const
bool c_KDDockWidgets__flutter__TabBar__isMounted(void *thisObj);
// KDDockWidgets::flutter::TabBar::isNull() const
bool c_KDDockWidgets__flutter__TabBar__isNull(void *thisObj);
// KDDockWidgets::flutter::TabBar::isRootView() const
bool c_KDDockWidgets__flutter__TabBar__isRootView(void *thisObj);
// KDDockWidgets::flutter::TabBar::isVisible() const
bool c_KDDockWidgets__flutter__TabBar__isVisible(void *thisObj);
// KDDockWidgets::flutter::TabBar::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__flutter__TabBar__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::flutter::TabBar::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
void *c_KDDockWidgets__flutter__TabBar__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_);
// KDDockWidgets::flutter::TabBar::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__flutter__TabBar__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::flutter::TabBar::maxSizeHint() const
void *c_KDDockWidgets__flutter__TabBar__maxSizeHint(void *thisObj);
// KDDockWidgets::flutter::TabBar::minSize() const
void *c_KDDockWidgets__flutter__TabBar__minSize(void *thisObj);
// KDDockWidgets::flutter::TabBar::move(int x, int y)
void c_KDDockWidgets__flutter__TabBar__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::flutter::TabBar::moveTabTo(int from, int to)
void c_KDDockWidgets__flutter__TabBar__moveTabTo_int_int(void *thisObj, int from, int to);
// KDDockWidgets::flutter::TabBar::normalGeometry() const
void *c_KDDockWidgets__flutter__TabBar__normalGeometry(void *thisObj);
// KDDockWidgets::flutter::TabBar::onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__TabBar__onChildAdded_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::TabBar::onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__TabBar__onChildRemoved_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::TabBar::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__TabBar__onChildVisibilityChanged_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::TabBar::onGeometryChanged()
void c_KDDockWidgets__flutter__TabBar__onGeometryChanged(void *thisObj);
// KDDockWidgets::flutter::TabBar::onRebuildRequested()
void c_KDDockWidgets__flutter__TabBar__onRebuildRequested(void *thisObj);
// KDDockWidgets::flutter::TabBar::onResize(int h, int w)
bool c_KDDockWidgets__flutter__TabBar__onResize_int_int(void *thisObj, int h, int w);
// KDDockWidgets::flutter::TabBar::raise()
void c_KDDockWidgets__flutter__TabBar__raise(void *thisObj);
// KDDockWidgets::flutter::TabBar::raiseAndActivate()
void c_KDDockWidgets__flutter__TabBar__raiseAndActivate(void *thisObj);
// KDDockWidgets::flutter::TabBar::raiseChild(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__TabBar__raiseChild_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::TabBar::raiseWindow(KDDockWidgets::Core::View * rootView)
void c_KDDockWidgets__flutter__TabBar__raiseWindow_View(void *thisObj, void *rootView_);
// KDDockWidgets::flutter::TabBar::rectForTab(int index) const
void *c_KDDockWidgets__flutter__TabBar__rectForTab_int(void *thisObj, int index);
// KDDockWidgets::flutter::TabBar::releaseKeyboard()
void c_KDDockWidgets__flutter__TabBar__releaseKeyboard(void *thisObj);
// KDDockWidgets::flutter::TabBar::releaseMouse()
void c_KDDockWidgets__flutter__TabBar__releaseMouse(void *thisObj);
// KDDockWidgets::flutter::TabBar::removeDockWidget(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__flutter__TabBar__removeDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::flutter::TabBar::renameTab(int index, const QString & name)
void c_KDDockWidgets__flutter__TabBar__renameTab_int_QString(void *thisObj, int index, const char *name_);
// KDDockWidgets::flutter::TabBar::setCurrentIndex(int index)
void c_KDDockWidgets__flutter__TabBar__setCurrentIndex_int(void *thisObj, int index);
// KDDockWidgets::flutter::TabBar::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__TabBar__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::flutter::TabBar::setFixedHeight(int h)
void c_KDDockWidgets__flutter__TabBar__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::TabBar::setFixedWidth(int w)
void c_KDDockWidgets__flutter__TabBar__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::TabBar::setGeometry(QRect geometry)
void c_KDDockWidgets__flutter__TabBar__setGeometry_QRect(void *thisObj, void *geometry_);
// KDDockWidgets::flutter::TabBar::setHeight(int h)
void c_KDDockWidgets__flutter__TabBar__setHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::TabBar::setMaximumSize(QSize sz)
void c_KDDockWidgets__flutter__TabBar__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::TabBar::setMinimumSize(QSize sz)
void c_KDDockWidgets__flutter__TabBar__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::TabBar::setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__TabBar__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::flutter::TabBar::setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__TabBar__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::TabBar::setSize(int w, int h)
void c_KDDockWidgets__flutter__TabBar__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::TabBar::setViewName(const QString & name)
void c_KDDockWidgets__flutter__TabBar__setViewName_QString(void *thisObj, const char *name_);
// KDDockWidgets::flutter::TabBar::setVisible(bool visible)
void c_KDDockWidgets__flutter__TabBar__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::flutter::TabBar::setWidth(int w)
void c_KDDockWidgets__flutter__TabBar__setWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::TabBar::setWindowOpacity(double v)
void c_KDDockWidgets__flutter__TabBar__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::flutter::TabBar::setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__TabBar__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::flutter::TabBar::setZOrder(int z)
void c_KDDockWidgets__flutter__TabBar__setZOrder_int(void *thisObj, int z);
// KDDockWidgets::flutter::TabBar::show()
void c_KDDockWidgets__flutter__TabBar__show(void *thisObj);
// KDDockWidgets::flutter::TabBar::showMaximized()
void c_KDDockWidgets__flutter__TabBar__showMaximized(void *thisObj);
// KDDockWidgets::flutter::TabBar::showMinimized()
void c_KDDockWidgets__flutter__TabBar__showMinimized(void *thisObj);
// KDDockWidgets::flutter::TabBar::showNormal()
void c_KDDockWidgets__flutter__TabBar__showNormal(void *thisObj);
// KDDockWidgets::flutter::TabBar::tabAt(QPoint localPos) const
int c_KDDockWidgets__flutter__TabBar__tabAt_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::flutter::TabBar::text(int index) const
void *c_KDDockWidgets__flutter__TabBar__text_int(void *thisObj, int index);
// KDDockWidgets::flutter::TabBar::update()
void c_KDDockWidgets__flutter__TabBar__update(void *thisObj);
// KDDockWidgets::flutter::TabBar::viewName() const
void *c_KDDockWidgets__flutter__TabBar__viewName(void *thisObj);
void c_KDDockWidgets__flutter__TabBar__destructor(void *thisObj);
void c_KDDockWidgets__flutter__TabBar__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__flutter__TabBar_Finalizer(void *cppObj); // KDDockWidgets::flutter::Stack::Stack(KDDockWidgets::Core::Stack * controller, KDDockWidgets::Core::View * parent)
void *c_KDDockWidgets__flutter__Stack__constructor_Stack_View(void *controller_, void *parent_);
// KDDockWidgets::flutter::Stack::activateWindow()
void c_KDDockWidgets__flutter__Stack__activateWindow(void *thisObj);
// KDDockWidgets::flutter::Stack::close()
bool c_KDDockWidgets__flutter__Stack__close(void *thisObj);
// KDDockWidgets::flutter::Stack::createPlatformWindow()
void c_KDDockWidgets__flutter__Stack__createPlatformWindow(void *thisObj);
// KDDockWidgets::flutter::Stack::flags() const
int c_KDDockWidgets__flutter__Stack__flags(void *thisObj);
// KDDockWidgets::flutter::Stack::geometry() const
void *c_KDDockWidgets__flutter__Stack__geometry(void *thisObj);
// KDDockWidgets::flutter::Stack::grabMouse()
void c_KDDockWidgets__flutter__Stack__grabMouse(void *thisObj);
// KDDockWidgets::flutter::Stack::hasFocus() const
bool c_KDDockWidgets__flutter__Stack__hasFocus(void *thisObj);
// KDDockWidgets::flutter::Stack::hide()
void c_KDDockWidgets__flutter__Stack__hide(void *thisObj);
// KDDockWidgets::flutter::Stack::init()
void c_KDDockWidgets__flutter__Stack__init(void *thisObj);
// KDDockWidgets::flutter::Stack::isActiveWindow() const
bool c_KDDockWidgets__flutter__Stack__isActiveWindow(void *thisObj);
// KDDockWidgets::flutter::Stack::isExplicitlyHidden() const
bool c_KDDockWidgets__flutter__Stack__isExplicitlyHidden(void *thisObj);
// KDDockWidgets::flutter::Stack::isMaximized() const
bool c_KDDockWidgets__flutter__Stack__isMaximized(void *thisObj);
// KDDockWidgets::flutter::Stack::isMinimized() const
bool c_KDDockWidgets__flutter__Stack__isMinimized(void *thisObj);
// KDDockWidgets::flutter::Stack::isMounted() const
bool c_KDDockWidgets__flutter__Stack__isMounted(void *thisObj);
// KDDockWidgets::flutter::Stack::isNull() const
bool c_KDDockWidgets__flutter__Stack__isNull(void *thisObj);
// KDDockWidgets::flutter::Stack::isPositionDraggable(QPoint p) const
bool c_KDDockWidgets__flutter__Stack__isPositionDraggable_QPoint(void *thisObj, void *p_);
// KDDockWidgets::flutter::Stack::isRootView() const
bool c_KDDockWidgets__flutter__Stack__isRootView(void *thisObj);
// KDDockWidgets::flutter::Stack::isVisible() const
bool c_KDDockWidgets__flutter__Stack__isVisible(void *thisObj);
// KDDockWidgets::flutter::Stack::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__flutter__Stack__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::flutter::Stack::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
void *c_KDDockWidgets__flutter__Stack__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_);
// KDDockWidgets::flutter::Stack::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__flutter__Stack__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::flutter::Stack::maxSizeHint() const
void *c_KDDockWidgets__flutter__Stack__maxSizeHint(void *thisObj);
// KDDockWidgets::flutter::Stack::minSize() const
void *c_KDDockWidgets__flutter__Stack__minSize(void *thisObj);
// KDDockWidgets::flutter::Stack::move(int x, int y)
void c_KDDockWidgets__flutter__Stack__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::flutter::Stack::normalGeometry() const
void *c_KDDockWidgets__flutter__Stack__normalGeometry(void *thisObj);
// KDDockWidgets::flutter::Stack::onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__Stack__onChildAdded_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::Stack::onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__Stack__onChildRemoved_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::Stack::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__Stack__onChildVisibilityChanged_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::Stack::onGeometryChanged()
void c_KDDockWidgets__flutter__Stack__onGeometryChanged(void *thisObj);
// KDDockWidgets::flutter::Stack::onRebuildRequested()
void c_KDDockWidgets__flutter__Stack__onRebuildRequested(void *thisObj);
// KDDockWidgets::flutter::Stack::onResize(int h, int w)
bool c_KDDockWidgets__flutter__Stack__onResize_int_int(void *thisObj, int h, int w);
// KDDockWidgets::flutter::Stack::raise()
void c_KDDockWidgets__flutter__Stack__raise(void *thisObj);
// KDDockWidgets::flutter::Stack::raiseAndActivate()
void c_KDDockWidgets__flutter__Stack__raiseAndActivate(void *thisObj);
// KDDockWidgets::flutter::Stack::raiseChild(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__Stack__raiseChild_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::Stack::raiseWindow(KDDockWidgets::Core::View * rootView)
void c_KDDockWidgets__flutter__Stack__raiseWindow_View(void *thisObj, void *rootView_);
// KDDockWidgets::flutter::Stack::releaseKeyboard()
void c_KDDockWidgets__flutter__Stack__releaseKeyboard(void *thisObj);
// KDDockWidgets::flutter::Stack::releaseMouse()
void c_KDDockWidgets__flutter__Stack__releaseMouse(void *thisObj);
// KDDockWidgets::flutter::Stack::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__Stack__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::flutter::Stack::setDocumentMode(bool arg__1)
void c_KDDockWidgets__flutter__Stack__setDocumentMode_bool(void *thisObj, bool arg__1);
// KDDockWidgets::flutter::Stack::setFixedHeight(int h)
void c_KDDockWidgets__flutter__Stack__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::Stack::setFixedWidth(int w)
void c_KDDockWidgets__flutter__Stack__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::Stack::setGeometry(QRect geometry)
void c_KDDockWidgets__flutter__Stack__setGeometry_QRect(void *thisObj, void *geometry_);
// KDDockWidgets::flutter::Stack::setHeight(int h)
void c_KDDockWidgets__flutter__Stack__setHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::Stack::setMaximumSize(QSize sz)
void c_KDDockWidgets__flutter__Stack__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::Stack::setMinimumSize(QSize sz)
void c_KDDockWidgets__flutter__Stack__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::Stack::setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__Stack__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::flutter::Stack::setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__Stack__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::Stack::setSize(int w, int h)
void c_KDDockWidgets__flutter__Stack__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::Stack::setViewName(const QString & name)
void c_KDDockWidgets__flutter__Stack__setViewName_QString(void *thisObj, const char *name_);
// KDDockWidgets::flutter::Stack::setVisible(bool visible)
void c_KDDockWidgets__flutter__Stack__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::flutter::Stack::setWidth(int w)
void c_KDDockWidgets__flutter__Stack__setWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::Stack::setWindowOpacity(double v)
void c_KDDockWidgets__flutter__Stack__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::flutter::Stack::setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__Stack__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::flutter::Stack::setZOrder(int z)
void c_KDDockWidgets__flutter__Stack__setZOrder_int(void *thisObj, int z);
// KDDockWidgets::flutter::Stack::show()
void c_KDDockWidgets__flutter__Stack__show(void *thisObj);
// KDDockWidgets::flutter::Stack::showMaximized()
void c_KDDockWidgets__flutter__Stack__showMaximized(void *thisObj);
// KDDockWidgets::flutter::Stack::showMinimized()
void c_KDDockWidgets__flutter__Stack__showMinimized(void *thisObj);
// KDDockWidgets::flutter::Stack::showNormal()
void c_KDDockWidgets__flutter__Stack__showNormal(void *thisObj);
// KDDockWidgets::flutter::Stack::update()
void c_KDDockWidgets__flutter__Stack__update(void *thisObj);
// KDDockWidgets::flutter::Stack::viewName() const
void *c_KDDockWidgets__flutter__Stack__viewName(void *thisObj);
void c_KDDockWidgets__flutter__Stack__destructor(void *thisObj);
void c_KDDockWidgets__flutter__Stack__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__flutter__Stack_Finalizer(void *cppObj); // KDDockWidgets::flutter::MainWindow::MainWindow(const QString & uniqueName, QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::flutter::View * parent, Qt::WindowFlags flags)
void *c_KDDockWidgets__flutter__MainWindow__constructor_QString_MainWindowOptions_View_WindowFlags(const char *uniqueName_, int options_, void *parent_, int flags);
// KDDockWidgets::flutter::MainWindow::activateWindow()
void c_KDDockWidgets__flutter__MainWindow__activateWindow(void *thisObj);
// KDDockWidgets::flutter::MainWindow::centralAreaGeometry() const
void *c_KDDockWidgets__flutter__MainWindow__centralAreaGeometry(void *thisObj);
// KDDockWidgets::flutter::MainWindow::close()
bool c_KDDockWidgets__flutter__MainWindow__close(void *thisObj);
// KDDockWidgets::flutter::MainWindow::createPlatformWindow()
void c_KDDockWidgets__flutter__MainWindow__createPlatformWindow(void *thisObj);
// KDDockWidgets::flutter::MainWindow::flags() const
int c_KDDockWidgets__flutter__MainWindow__flags(void *thisObj);
// KDDockWidgets::flutter::MainWindow::geometry() const
void *c_KDDockWidgets__flutter__MainWindow__geometry(void *thisObj);
// KDDockWidgets::flutter::MainWindow::grabMouse()
void c_KDDockWidgets__flutter__MainWindow__grabMouse(void *thisObj);
// KDDockWidgets::flutter::MainWindow::hasFocus() const
bool c_KDDockWidgets__flutter__MainWindow__hasFocus(void *thisObj);
// KDDockWidgets::flutter::MainWindow::hide()
void c_KDDockWidgets__flutter__MainWindow__hide(void *thisObj);
// KDDockWidgets::flutter::MainWindow::init()
void c_KDDockWidgets__flutter__MainWindow__init(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isActiveWindow() const
bool c_KDDockWidgets__flutter__MainWindow__isActiveWindow(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isExplicitlyHidden() const
bool c_KDDockWidgets__flutter__MainWindow__isExplicitlyHidden(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isMaximized() const
bool c_KDDockWidgets__flutter__MainWindow__isMaximized(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isMinimized() const
bool c_KDDockWidgets__flutter__MainWindow__isMinimized(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isMounted() const
bool c_KDDockWidgets__flutter__MainWindow__isMounted(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isNull() const
bool c_KDDockWidgets__flutter__MainWindow__isNull(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isRootView() const
bool c_KDDockWidgets__flutter__MainWindow__isRootView(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isVisible() const
bool c_KDDockWidgets__flutter__MainWindow__isVisible(void *thisObj);
// KDDockWidgets::flutter::MainWindow::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__flutter__MainWindow__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::flutter::MainWindow::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
void *c_KDDockWidgets__flutter__MainWindow__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_);
// KDDockWidgets::flutter::MainWindow::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__flutter__MainWindow__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::flutter::MainWindow::maxSizeHint() const
void *c_KDDockWidgets__flutter__MainWindow__maxSizeHint(void *thisObj);
// KDDockWidgets::flutter::MainWindow::minSize() const
void *c_KDDockWidgets__flutter__MainWindow__minSize(void *thisObj);
// KDDockWidgets::flutter::MainWindow::move(int x, int y)
void c_KDDockWidgets__flutter__MainWindow__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::flutter::MainWindow::normalGeometry() const
void *c_KDDockWidgets__flutter__MainWindow__normalGeometry(void *thisObj);
// KDDockWidgets::flutter::MainWindow::onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__MainWindow__onChildAdded_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::MainWindow::onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__MainWindow__onChildRemoved_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::MainWindow::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__MainWindow__onChildVisibilityChanged_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::MainWindow::onGeometryChanged()
void c_KDDockWidgets__flutter__MainWindow__onGeometryChanged(void *thisObj);
// KDDockWidgets::flutter::MainWindow::onRebuildRequested()
void c_KDDockWidgets__flutter__MainWindow__onRebuildRequested(void *thisObj);
// KDDockWidgets::flutter::MainWindow::onResize(int h, int w)
bool c_KDDockWidgets__flutter__MainWindow__onResize_int_int(void *thisObj, int h, int w);
// KDDockWidgets::flutter::MainWindow::raise()
void c_KDDockWidgets__flutter__MainWindow__raise(void *thisObj);
// KDDockWidgets::flutter::MainWindow::raiseAndActivate()
void c_KDDockWidgets__flutter__MainWindow__raiseAndActivate(void *thisObj);
// KDDockWidgets::flutter::MainWindow::raiseChild(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__MainWindow__raiseChild_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::MainWindow::raiseWindow(KDDockWidgets::Core::View * rootView)
void c_KDDockWidgets__flutter__MainWindow__raiseWindow_View(void *thisObj, void *rootView_);
// KDDockWidgets::flutter::MainWindow::releaseKeyboard()
void c_KDDockWidgets__flutter__MainWindow__releaseKeyboard(void *thisObj);
// KDDockWidgets::flutter::MainWindow::releaseMouse()
void c_KDDockWidgets__flutter__MainWindow__releaseMouse(void *thisObj);
// KDDockWidgets::flutter::MainWindow::setContentsMargins(int left, int top, int right, int bottom)
void c_KDDockWidgets__flutter__MainWindow__setContentsMargins_int_int_int_int(void *thisObj, int left, int top, int right, int bottom);
// KDDockWidgets::flutter::MainWindow::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__MainWindow__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::flutter::MainWindow::setFixedHeight(int h)
void c_KDDockWidgets__flutter__MainWindow__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::MainWindow::setFixedWidth(int w)
void c_KDDockWidgets__flutter__MainWindow__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::MainWindow::setGeometry(QRect geometry)
void c_KDDockWidgets__flutter__MainWindow__setGeometry_QRect(void *thisObj, void *geometry_);
// KDDockWidgets::flutter::MainWindow::setHeight(int h)
void c_KDDockWidgets__flutter__MainWindow__setHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::MainWindow::setMaximumSize(QSize sz)
void c_KDDockWidgets__flutter__MainWindow__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::MainWindow::setMinimumSize(QSize sz)
void c_KDDockWidgets__flutter__MainWindow__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::MainWindow::setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__MainWindow__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::flutter::MainWindow::setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__MainWindow__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::MainWindow::setSize(int w, int h)
void c_KDDockWidgets__flutter__MainWindow__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::MainWindow::setViewName(const QString & name)
void c_KDDockWidgets__flutter__MainWindow__setViewName_QString(void *thisObj, const char *name_);
// KDDockWidgets::flutter::MainWindow::setVisible(bool visible)
void c_KDDockWidgets__flutter__MainWindow__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::flutter::MainWindow::setWidth(int w)
void c_KDDockWidgets__flutter__MainWindow__setWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::MainWindow::setWindowOpacity(double v)
void c_KDDockWidgets__flutter__MainWindow__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::flutter::MainWindow::setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__MainWindow__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::flutter::MainWindow::setZOrder(int z)
void c_KDDockWidgets__flutter__MainWindow__setZOrder_int(void *thisObj, int z);
// KDDockWidgets::flutter::MainWindow::show()
void c_KDDockWidgets__flutter__MainWindow__show(void *thisObj);
// KDDockWidgets::flutter::MainWindow::showMaximized()
void c_KDDockWidgets__flutter__MainWindow__showMaximized(void *thisObj);
// KDDockWidgets::flutter::MainWindow::showMinimized()
void c_KDDockWidgets__flutter__MainWindow__showMinimized(void *thisObj);
// KDDockWidgets::flutter::MainWindow::showNormal()
void c_KDDockWidgets__flutter__MainWindow__showNormal(void *thisObj);
// KDDockWidgets::flutter::MainWindow::update()
void c_KDDockWidgets__flutter__MainWindow__update(void *thisObj);
// KDDockWidgets::flutter::MainWindow::viewName() const
void *c_KDDockWidgets__flutter__MainWindow__viewName(void *thisObj);
void c_KDDockWidgets__flutter__MainWindow__destructor(void *thisObj);
void c_KDDockWidgets__flutter__MainWindow__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__flutter__MainWindow_Finalizer(void *cppObj); // KDDockWidgets::flutter::Group::Group(KDDockWidgets::Core::Group * controller, KDDockWidgets::Core::View * parent)
void *c_KDDockWidgets__flutter__Group__constructor_Group_View(void *controller_, void *parent_);
// KDDockWidgets::flutter::Group::activateWindow()
void c_KDDockWidgets__flutter__Group__activateWindow(void *thisObj);
// KDDockWidgets::flutter::Group::close()
bool c_KDDockWidgets__flutter__Group__close(void *thisObj);
// KDDockWidgets::flutter::Group::createPlatformWindow()
void c_KDDockWidgets__flutter__Group__createPlatformWindow(void *thisObj);
// KDDockWidgets::flutter::Group::currentIndex() const
int c_KDDockWidgets__flutter__Group__currentIndex(void *thisObj);
// KDDockWidgets::flutter::Group::dragRect() const
void *c_KDDockWidgets__flutter__Group__dragRect(void *thisObj);
// KDDockWidgets::flutter::Group::flags() const
int c_KDDockWidgets__flutter__Group__flags(void *thisObj);
// KDDockWidgets::flutter::Group::geometry() const
void *c_KDDockWidgets__flutter__Group__geometry(void *thisObj);
// KDDockWidgets::flutter::Group::grabMouse()
void c_KDDockWidgets__flutter__Group__grabMouse(void *thisObj);
// KDDockWidgets::flutter::Group::hasFocus() const
bool c_KDDockWidgets__flutter__Group__hasFocus(void *thisObj);
// KDDockWidgets::flutter::Group::hide()
void c_KDDockWidgets__flutter__Group__hide(void *thisObj);
// KDDockWidgets::flutter::Group::isActiveWindow() const
bool c_KDDockWidgets__flutter__Group__isActiveWindow(void *thisObj);
// KDDockWidgets::flutter::Group::isExplicitlyHidden() const
bool c_KDDockWidgets__flutter__Group__isExplicitlyHidden(void *thisObj);
// KDDockWidgets::flutter::Group::isMaximized() const
bool c_KDDockWidgets__flutter__Group__isMaximized(void *thisObj);
// KDDockWidgets::flutter::Group::isMinimized() const
bool c_KDDockWidgets__flutter__Group__isMinimized(void *thisObj);
// KDDockWidgets::flutter::Group::isMounted() const
bool c_KDDockWidgets__flutter__Group__isMounted(void *thisObj);
// KDDockWidgets::flutter::Group::isNull() const
bool c_KDDockWidgets__flutter__Group__isNull(void *thisObj);
// KDDockWidgets::flutter::Group::isRootView() const
bool c_KDDockWidgets__flutter__Group__isRootView(void *thisObj);
// KDDockWidgets::flutter::Group::isVisible() const
bool c_KDDockWidgets__flutter__Group__isVisible(void *thisObj);
// KDDockWidgets::flutter::Group::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__flutter__Group__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::flutter::Group::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
void *c_KDDockWidgets__flutter__Group__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_);
// KDDockWidgets::flutter::Group::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__flutter__Group__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::flutter::Group::maxSizeHint() const
void *c_KDDockWidgets__flutter__Group__maxSizeHint(void *thisObj);
// KDDockWidgets::flutter::Group::minSize() const
void *c_KDDockWidgets__flutter__Group__minSize(void *thisObj);
// KDDockWidgets::flutter::Group::move(int x, int y)
void c_KDDockWidgets__flutter__Group__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::flutter::Group::nonContentsHeight() const
int c_KDDockWidgets__flutter__Group__nonContentsHeight(void *thisObj);
// KDDockWidgets::flutter::Group::normalGeometry() const
void *c_KDDockWidgets__flutter__Group__normalGeometry(void *thisObj);
// KDDockWidgets::flutter::Group::onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__Group__onChildAdded_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::Group::onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__Group__onChildRemoved_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::Group::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__Group__onChildVisibilityChanged_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::Group::onGeometryChanged()
void c_KDDockWidgets__flutter__Group__onGeometryChanged(void *thisObj);
// KDDockWidgets::flutter::Group::onRebuildRequested()
void c_KDDockWidgets__flutter__Group__onRebuildRequested(void *thisObj);
// KDDockWidgets::flutter::Group::onResize(int h, int w)
bool c_KDDockWidgets__flutter__Group__onResize_int_int(void *thisObj, int h, int w);
// KDDockWidgets::flutter::Group::raise()
void c_KDDockWidgets__flutter__Group__raise(void *thisObj);
// KDDockWidgets::flutter::Group::raiseAndActivate()
void c_KDDockWidgets__flutter__Group__raiseAndActivate(void *thisObj);
// KDDockWidgets::flutter::Group::raiseChild(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__Group__raiseChild_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::Group::raiseWindow(KDDockWidgets::Core::View * rootView)
void c_KDDockWidgets__flutter__Group__raiseWindow_View(void *thisObj, void *rootView_);
// KDDockWidgets::flutter::Group::releaseKeyboard()
void c_KDDockWidgets__flutter__Group__releaseKeyboard(void *thisObj);
// KDDockWidgets::flutter::Group::releaseMouse()
void c_KDDockWidgets__flutter__Group__releaseMouse(void *thisObj);
// KDDockWidgets::flutter::Group::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__Group__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::flutter::Group::setFixedHeight(int h)
void c_KDDockWidgets__flutter__Group__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::Group::setFixedWidth(int w)
void c_KDDockWidgets__flutter__Group__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::Group::setGeometry(QRect geometry)
void c_KDDockWidgets__flutter__Group__setGeometry_QRect(void *thisObj, void *geometry_);
// KDDockWidgets::flutter::Group::setHeight(int h)
void c_KDDockWidgets__flutter__Group__setHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::Group::setMaximumSize(QSize sz)
void c_KDDockWidgets__flutter__Group__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::Group::setMinimumSize(QSize sz)
void c_KDDockWidgets__flutter__Group__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::Group::setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__Group__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::flutter::Group::setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__Group__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::Group::setSize(int w, int h)
void c_KDDockWidgets__flutter__Group__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::Group::setViewName(const QString & name)
void c_KDDockWidgets__flutter__Group__setViewName_QString(void *thisObj, const char *name_);
// KDDockWidgets::flutter::Group::setVisible(bool visible)
void c_KDDockWidgets__flutter__Group__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::flutter::Group::setWidth(int w)
void c_KDDockWidgets__flutter__Group__setWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::Group::setWindowOpacity(double v)
void c_KDDockWidgets__flutter__Group__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::flutter::Group::setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__Group__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::flutter::Group::setZOrder(int z)
void c_KDDockWidgets__flutter__Group__setZOrder_int(void *thisObj, int z);
// KDDockWidgets::flutter::Group::show()
void c_KDDockWidgets__flutter__Group__show(void *thisObj);
// KDDockWidgets::flutter::Group::showMaximized()
void c_KDDockWidgets__flutter__Group__showMaximized(void *thisObj);
// KDDockWidgets::flutter::Group::showMinimized()
void c_KDDockWidgets__flutter__Group__showMinimized(void *thisObj);
// KDDockWidgets::flutter::Group::showNormal()
void c_KDDockWidgets__flutter__Group__showNormal(void *thisObj);
// KDDockWidgets::flutter::Group::update()
void c_KDDockWidgets__flutter__Group__update(void *thisObj);
// KDDockWidgets::flutter::Group::viewName() const
void *c_KDDockWidgets__flutter__Group__viewName(void *thisObj);
void c_KDDockWidgets__flutter__Group__destructor(void *thisObj);
void c_KDDockWidgets__flutter__Group__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__flutter__Group_Finalizer(void *cppObj); // KDDockWidgets::flutter::DropArea::DropArea(KDDockWidgets::Core::DropArea * arg__1, KDDockWidgets::Core::View * parent)
void *c_KDDockWidgets__flutter__DropArea__constructor_DropArea_View(void *arg__1_, void *parent_);
// KDDockWidgets::flutter::DropArea::activateWindow()
void c_KDDockWidgets__flutter__DropArea__activateWindow(void *thisObj);
// KDDockWidgets::flutter::DropArea::close()
bool c_KDDockWidgets__flutter__DropArea__close(void *thisObj);
// KDDockWidgets::flutter::DropArea::createPlatformWindow()
void c_KDDockWidgets__flutter__DropArea__createPlatformWindow(void *thisObj);
// KDDockWidgets::flutter::DropArea::flags() const
int c_KDDockWidgets__flutter__DropArea__flags(void *thisObj);
// KDDockWidgets::flutter::DropArea::geometry() const
void *c_KDDockWidgets__flutter__DropArea__geometry(void *thisObj);
// KDDockWidgets::flutter::DropArea::grabMouse()
void c_KDDockWidgets__flutter__DropArea__grabMouse(void *thisObj);
// KDDockWidgets::flutter::DropArea::hasFocus() const
bool c_KDDockWidgets__flutter__DropArea__hasFocus(void *thisObj);
// KDDockWidgets::flutter::DropArea::hide()
void c_KDDockWidgets__flutter__DropArea__hide(void *thisObj);
// KDDockWidgets::flutter::DropArea::indicatorWindow() const
void *c_KDDockWidgets__flutter__DropArea__indicatorWindow(void *thisObj);
// KDDockWidgets::flutter::DropArea::init()
void c_KDDockWidgets__flutter__DropArea__init(void *thisObj);
// KDDockWidgets::flutter::DropArea::isActiveWindow() const
bool c_KDDockWidgets__flutter__DropArea__isActiveWindow(void *thisObj);
// KDDockWidgets::flutter::DropArea::isExplicitlyHidden() const
bool c_KDDockWidgets__flutter__DropArea__isExplicitlyHidden(void *thisObj);
// KDDockWidgets::flutter::DropArea::isMaximized() const
bool c_KDDockWidgets__flutter__DropArea__isMaximized(void *thisObj);
// KDDockWidgets::flutter::DropArea::isMinimized() const
bool c_KDDockWidgets__flutter__DropArea__isMinimized(void *thisObj);
// KDDockWidgets::flutter::DropArea::isMounted() const
bool c_KDDockWidgets__flutter__DropArea__isMounted(void *thisObj);
// KDDockWidgets::flutter::DropArea::isNull() const
bool c_KDDockWidgets__flutter__DropArea__isNull(void *thisObj);
// KDDockWidgets::flutter::DropArea::isRootView() const
bool c_KDDockWidgets__flutter__DropArea__isRootView(void *thisObj);
// KDDockWidgets::flutter::DropArea::isVisible() const
bool c_KDDockWidgets__flutter__DropArea__isVisible(void *thisObj);
// KDDockWidgets::flutter::DropArea::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__flutter__DropArea__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::flutter::DropArea::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
void *c_KDDockWidgets__flutter__DropArea__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_);
// KDDockWidgets::flutter::DropArea::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__flutter__DropArea__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::flutter::DropArea::maxSizeHint() const
void *c_KDDockWidgets__flutter__DropArea__maxSizeHint(void *thisObj);
// KDDockWidgets::flutter::DropArea::minSize() const
void *c_KDDockWidgets__flutter__DropArea__minSize(void *thisObj);
// KDDockWidgets::flutter::DropArea::move(int x, int y)
void c_KDDockWidgets__flutter__DropArea__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::flutter::DropArea::normalGeometry() const
void *c_KDDockWidgets__flutter__DropArea__normalGeometry(void *thisObj);
// KDDockWidgets::flutter::DropArea::onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__DropArea__onChildAdded_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::DropArea::onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__DropArea__onChildRemoved_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::DropArea::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__DropArea__onChildVisibilityChanged_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::DropArea::onGeometryChanged()
void c_KDDockWidgets__flutter__DropArea__onGeometryChanged(void *thisObj);
// KDDockWidgets::flutter::DropArea::onRebuildRequested()
void c_KDDockWidgets__flutter__DropArea__onRebuildRequested(void *thisObj);
// KDDockWidgets::flutter::DropArea::onResize(int h, int w)
bool c_KDDockWidgets__flutter__DropArea__onResize_int_int(void *thisObj, int h, int w);
// KDDockWidgets::flutter::DropArea::raise()
void c_KDDockWidgets__flutter__DropArea__raise(void *thisObj);
// KDDockWidgets::flutter::DropArea::raiseAndActivate()
void c_KDDockWidgets__flutter__DropArea__raiseAndActivate(void *thisObj);
// KDDockWidgets::flutter::DropArea::raiseChild(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__DropArea__raiseChild_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::DropArea::raiseWindow(KDDockWidgets::Core::View * rootView)
void c_KDDockWidgets__flutter__DropArea__raiseWindow_View(void *thisObj, void *rootView_);
// KDDockWidgets::flutter::DropArea::releaseKeyboard()
void c_KDDockWidgets__flutter__DropArea__releaseKeyboard(void *thisObj);
// KDDockWidgets::flutter::DropArea::releaseMouse()
void c_KDDockWidgets__flutter__DropArea__releaseMouse(void *thisObj);
// KDDockWidgets::flutter::DropArea::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__DropArea__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::flutter::DropArea::setFixedHeight(int h)
void c_KDDockWidgets__flutter__DropArea__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::DropArea::setFixedWidth(int w)
void c_KDDockWidgets__flutter__DropArea__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::DropArea::setGeometry(QRect geometry)
void c_KDDockWidgets__flutter__DropArea__setGeometry_QRect(void *thisObj, void *geometry_);
// KDDockWidgets::flutter::DropArea::setHeight(int h)
void c_KDDockWidgets__flutter__DropArea__setHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::DropArea::setMaximumSize(QSize sz)
void c_KDDockWidgets__flutter__DropArea__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::DropArea::setMinimumSize(QSize sz)
void c_KDDockWidgets__flutter__DropArea__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::DropArea::setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__DropArea__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::flutter::DropArea::setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__DropArea__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::DropArea::setSize(int w, int h)
void c_KDDockWidgets__flutter__DropArea__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::DropArea::setViewName(const QString & name)
void c_KDDockWidgets__flutter__DropArea__setViewName_QString(void *thisObj, const char *name_);
// KDDockWidgets::flutter::DropArea::setVisible(bool visible)
void c_KDDockWidgets__flutter__DropArea__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::flutter::DropArea::setWidth(int w)
void c_KDDockWidgets__flutter__DropArea__setWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::DropArea::setWindowOpacity(double v)
void c_KDDockWidgets__flutter__DropArea__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::flutter::DropArea::setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__DropArea__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::flutter::DropArea::setZOrder(int z)
void c_KDDockWidgets__flutter__DropArea__setZOrder_int(void *thisObj, int z);
// KDDockWidgets::flutter::DropArea::show()
void c_KDDockWidgets__flutter__DropArea__show(void *thisObj);
// KDDockWidgets::flutter::DropArea::showMaximized()
void c_KDDockWidgets__flutter__DropArea__showMaximized(void *thisObj);
// KDDockWidgets::flutter::DropArea::showMinimized()
void c_KDDockWidgets__flutter__DropArea__showMinimized(void *thisObj);
// KDDockWidgets::flutter::DropArea::showNormal()
void c_KDDockWidgets__flutter__DropArea__showNormal(void *thisObj);
// KDDockWidgets::flutter::DropArea::update()
void c_KDDockWidgets__flutter__DropArea__update(void *thisObj);
// KDDockWidgets::flutter::DropArea::viewName() const
void *c_KDDockWidgets__flutter__DropArea__viewName(void *thisObj);
void c_KDDockWidgets__flutter__DropArea__destructor(void *thisObj);
void c_KDDockWidgets__flutter__DropArea__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__flutter__DropArea_Finalizer(void *cppObj); // KDDockWidgets::flutter::DockWidget::DockWidget(const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions)
void *c_KDDockWidgets__flutter__DockWidget__constructor_QString_DockWidgetOptions_LayoutSaverOptions(const char *uniqueName_, int options_, int layoutSaverOptions_);
// KDDockWidgets::flutter::DockWidget::activateWindow()
void c_KDDockWidgets__flutter__DockWidget__activateWindow(void *thisObj);
// KDDockWidgets::flutter::DockWidget::close()
bool c_KDDockWidgets__flutter__DockWidget__close(void *thisObj);
// KDDockWidgets::flutter::DockWidget::createPlatformWindow()
void c_KDDockWidgets__flutter__DockWidget__createPlatformWindow(void *thisObj);
// KDDockWidgets::flutter::DockWidget::dockWidget() const
void *c_KDDockWidgets__flutter__DockWidget__dockWidget(void *thisObj);
// KDDockWidgets::flutter::DockWidget::flags() const
int c_KDDockWidgets__flutter__DockWidget__flags(void *thisObj);
// KDDockWidgets::flutter::DockWidget::geometry() const
void *c_KDDockWidgets__flutter__DockWidget__geometry(void *thisObj);
// KDDockWidgets::flutter::DockWidget::grabMouse()
void c_KDDockWidgets__flutter__DockWidget__grabMouse(void *thisObj);
// KDDockWidgets::flutter::DockWidget::hasFocus() const
bool c_KDDockWidgets__flutter__DockWidget__hasFocus(void *thisObj);
// KDDockWidgets::flutter::DockWidget::hide()
void c_KDDockWidgets__flutter__DockWidget__hide(void *thisObj);
// KDDockWidgets::flutter::DockWidget::init()
void c_KDDockWidgets__flutter__DockWidget__init(void *thisObj);
// KDDockWidgets::flutter::DockWidget::isActiveWindow() const
bool c_KDDockWidgets__flutter__DockWidget__isActiveWindow(void *thisObj);
// KDDockWidgets::flutter::DockWidget::isExplicitlyHidden() const
bool c_KDDockWidgets__flutter__DockWidget__isExplicitlyHidden(void *thisObj);
// KDDockWidgets::flutter::DockWidget::isMaximized() const
bool c_KDDockWidgets__flutter__DockWidget__isMaximized(void *thisObj);
// KDDockWidgets::flutter::DockWidget::isMinimized() const
bool c_KDDockWidgets__flutter__DockWidget__isMinimized(void *thisObj);
// KDDockWidgets::flutter::DockWidget::isMounted() const
bool c_KDDockWidgets__flutter__DockWidget__isMounted(void *thisObj);
// KDDockWidgets::flutter::DockWidget::isNull() const
bool c_KDDockWidgets__flutter__DockWidget__isNull(void *thisObj);
// KDDockWidgets::flutter::DockWidget::isRootView() const
bool c_KDDockWidgets__flutter__DockWidget__isRootView(void *thisObj);
// KDDockWidgets::flutter::DockWidget::isVisible() const
bool c_KDDockWidgets__flutter__DockWidget__isVisible(void *thisObj);
// KDDockWidgets::flutter::DockWidget::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__flutter__DockWidget__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::flutter::DockWidget::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
void *c_KDDockWidgets__flutter__DockWidget__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_);
// KDDockWidgets::flutter::DockWidget::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__flutter__DockWidget__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::flutter::DockWidget::maxSizeHint() const
void *c_KDDockWidgets__flutter__DockWidget__maxSizeHint(void *thisObj);
// KDDockWidgets::flutter::DockWidget::minSize() const
void *c_KDDockWidgets__flutter__DockWidget__minSize(void *thisObj);
// KDDockWidgets::flutter::DockWidget::move(int x, int y)
void c_KDDockWidgets__flutter__DockWidget__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::flutter::DockWidget::normalGeometry() const
void *c_KDDockWidgets__flutter__DockWidget__normalGeometry(void *thisObj);
// KDDockWidgets::flutter::DockWidget::onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__DockWidget__onChildAdded_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::DockWidget::onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__DockWidget__onChildRemoved_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::DockWidget::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__DockWidget__onChildVisibilityChanged_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::DockWidget::onGeometryChanged()
void c_KDDockWidgets__flutter__DockWidget__onGeometryChanged(void *thisObj);
// KDDockWidgets::flutter::DockWidget::onRebuildRequested()
void c_KDDockWidgets__flutter__DockWidget__onRebuildRequested(void *thisObj);
// KDDockWidgets::flutter::DockWidget::onResize(int h, int w)
bool c_KDDockWidgets__flutter__DockWidget__onResize_int_int(void *thisObj, int h, int w);
// KDDockWidgets::flutter::DockWidget::raise()
void c_KDDockWidgets__flutter__DockWidget__raise(void *thisObj);
// KDDockWidgets::flutter::DockWidget::raiseAndActivate()
void c_KDDockWidgets__flutter__DockWidget__raiseAndActivate(void *thisObj);
// KDDockWidgets::flutter::DockWidget::raiseChild(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__DockWidget__raiseChild_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::DockWidget::raiseWindow(KDDockWidgets::Core::View * rootView)
void c_KDDockWidgets__flutter__DockWidget__raiseWindow_View(void *thisObj, void *rootView_);
// KDDockWidgets::flutter::DockWidget::releaseKeyboard()
void c_KDDockWidgets__flutter__DockWidget__releaseKeyboard(void *thisObj);
// KDDockWidgets::flutter::DockWidget::releaseMouse()
void c_KDDockWidgets__flutter__DockWidget__releaseMouse(void *thisObj);
// KDDockWidgets::flutter::DockWidget::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__DockWidget__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::flutter::DockWidget::setFixedHeight(int h)
void c_KDDockWidgets__flutter__DockWidget__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::DockWidget::setFixedWidth(int w)
void c_KDDockWidgets__flutter__DockWidget__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::DockWidget::setGeometry(QRect geometry)
void c_KDDockWidgets__flutter__DockWidget__setGeometry_QRect(void *thisObj, void *geometry_);
// KDDockWidgets::flutter::DockWidget::setHeight(int h)
void c_KDDockWidgets__flutter__DockWidget__setHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::DockWidget::setMaximumSize(QSize sz)
void c_KDDockWidgets__flutter__DockWidget__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::DockWidget::setMinimumSize(QSize sz)
void c_KDDockWidgets__flutter__DockWidget__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::DockWidget::setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__DockWidget__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::flutter::DockWidget::setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__DockWidget__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::DockWidget::setSize(int w, int h)
void c_KDDockWidgets__flutter__DockWidget__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::DockWidget::setViewName(const QString & name)
void c_KDDockWidgets__flutter__DockWidget__setViewName_QString(void *thisObj, const char *name_);
// KDDockWidgets::flutter::DockWidget::setVisible(bool visible)
void c_KDDockWidgets__flutter__DockWidget__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::flutter::DockWidget::setWidth(int w)
void c_KDDockWidgets__flutter__DockWidget__setWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::DockWidget::setWindowOpacity(double v)
void c_KDDockWidgets__flutter__DockWidget__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::flutter::DockWidget::setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__DockWidget__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::flutter::DockWidget::setZOrder(int z)
void c_KDDockWidgets__flutter__DockWidget__setZOrder_int(void *thisObj, int z);
// KDDockWidgets::flutter::DockWidget::show()
void c_KDDockWidgets__flutter__DockWidget__show(void *thisObj);
// KDDockWidgets::flutter::DockWidget::showMaximized()
void c_KDDockWidgets__flutter__DockWidget__showMaximized(void *thisObj);
// KDDockWidgets::flutter::DockWidget::showMinimized()
void c_KDDockWidgets__flutter__DockWidget__showMinimized(void *thisObj);
// KDDockWidgets::flutter::DockWidget::showNormal()
void c_KDDockWidgets__flutter__DockWidget__showNormal(void *thisObj);
// KDDockWidgets::flutter::DockWidget::update()
void c_KDDockWidgets__flutter__DockWidget__update(void *thisObj);
// KDDockWidgets::flutter::DockWidget::viewName() const
void *c_KDDockWidgets__flutter__DockWidget__viewName(void *thisObj);
void c_KDDockWidgets__flutter__DockWidget__destructor(void *thisObj);
void c_KDDockWidgets__flutter__DockWidget__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__flutter__DockWidget_Finalizer(void *cppObj); // KDDockWidgets::Core::TitleBar::TitleBar(KDDockWidgets::Core::FloatingWindow * parent)
void *c_KDDockWidgets__Core__TitleBar__constructor_FloatingWindow(void *parent_);
// KDDockWidgets::Core::TitleBar::TitleBar(KDDockWidgets::Core::Group * parent)
void *c_KDDockWidgets__Core__TitleBar__constructor_Group(void *parent_);
// KDDockWidgets::Core::TitleBar::TitleBar(KDDockWidgets::Core::View * arg__1)
void *c_KDDockWidgets__Core__TitleBar__constructor_View(void *arg__1_);
// KDDockWidgets::Core::TitleBar::closeButtonEnabled() const
bool c_KDDockWidgets__Core__TitleBar__closeButtonEnabled(void *thisObj);
// KDDockWidgets::Core::TitleBar::closeButtonEnabledChanged(bool arg__1)
void c_KDDockWidgets__Core__TitleBar__closeButtonEnabledChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::TitleBar::floatButtonToolTip() const
void *c_KDDockWidgets__Core__TitleBar__floatButtonToolTip(void *thisObj);
// KDDockWidgets::Core::TitleBar::floatButtonToolTipChanged(const QString & arg__1)
void c_KDDockWidgets__Core__TitleBar__floatButtonToolTipChanged_QString(void *thisObj, const char *arg__1_);
// KDDockWidgets::Core::TitleBar::floatButtonVisible() const
bool c_KDDockWidgets__Core__TitleBar__floatButtonVisible(void *thisObj);
// KDDockWidgets::Core::TitleBar::floatButtonVisibleChanged(bool arg__1)
void c_KDDockWidgets__Core__TitleBar__floatButtonVisibleChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::TitleBar::floatingWindow() const
void *c_KDDockWidgets__Core__TitleBar__floatingWindow(void *thisObj);
// KDDockWidgets::Core::TitleBar::group() const
void *c_KDDockWidgets__Core__TitleBar__group(void *thisObj);
// KDDockWidgets::Core::TitleBar::hasIcon() const
bool c_KDDockWidgets__Core__TitleBar__hasIcon(void *thisObj);
// KDDockWidgets::Core::TitleBar::iconChanged()
void c_KDDockWidgets__Core__TitleBar__iconChanged(void *thisObj);
// KDDockWidgets::Core::TitleBar::isCloseButtonEnabled() const
bool c_KDDockWidgets__Core__TitleBar__isCloseButtonEnabled(void *thisObj);
// KDDockWidgets::Core::TitleBar::isCloseButtonVisible() const
bool c_KDDockWidgets__Core__TitleBar__isCloseButtonVisible(void *thisObj);
// KDDockWidgets::Core::TitleBar::isFloatButtonVisible() const
bool c_KDDockWidgets__Core__TitleBar__isFloatButtonVisible(void *thisObj);
// KDDockWidgets::Core::TitleBar::isFloating() const
bool c_KDDockWidgets__Core__TitleBar__isFloating(void *thisObj);
// KDDockWidgets::Core::TitleBar::isFocused() const
bool c_KDDockWidgets__Core__TitleBar__isFocused(void *thisObj);
// KDDockWidgets::Core::TitleBar::isFocusedChanged()
void c_KDDockWidgets__Core__TitleBar__isFocusedChanged(void *thisObj);
// KDDockWidgets::Core::TitleBar::isMDI() const
bool c_KDDockWidgets__Core__TitleBar__isMDI(void *thisObj);
// KDDockWidgets::Core::TitleBar::isOverlayed() const
bool c_KDDockWidgets__Core__TitleBar__isOverlayed(void *thisObj);
// KDDockWidgets::Core::TitleBar::isStandalone() const
bool c_KDDockWidgets__Core__TitleBar__isStandalone(void *thisObj);
// KDDockWidgets::Core::TitleBar::isWindow() const
bool c_KDDockWidgets__Core__TitleBar__isWindow(void *thisObj);
// KDDockWidgets::Core::TitleBar::mainWindow() const
void *c_KDDockWidgets__Core__TitleBar__mainWindow(void *thisObj);
// KDDockWidgets::Core::TitleBar::maximizeButtonVisible() const
bool c_KDDockWidgets__Core__TitleBar__maximizeButtonVisible(void *thisObj);
// KDDockWidgets::Core::TitleBar::minimizeButtonChanged(bool visible, bool enabled)
void c_KDDockWidgets__Core__TitleBar__minimizeButtonChanged_bool_bool(void *thisObj, bool visible, bool enabled);
// KDDockWidgets::Core::TitleBar::numDockWidgetsChanged()
void c_KDDockWidgets__Core__TitleBar__numDockWidgetsChanged(void *thisObj);
// KDDockWidgets::Core::TitleBar::onAutoHideClicked()
void c_KDDockWidgets__Core__TitleBar__onAutoHideClicked(void *thisObj);
// KDDockWidgets::Core::TitleBar::onCloseClicked()
void c_KDDockWidgets__Core__TitleBar__onCloseClicked(void *thisObj);
// KDDockWidgets::Core::TitleBar::onDoubleClicked()
bool c_KDDockWidgets__Core__TitleBar__onDoubleClicked(void *thisObj);
// KDDockWidgets::Core::TitleBar::onFloatClicked()
void c_KDDockWidgets__Core__TitleBar__onFloatClicked(void *thisObj);
// KDDockWidgets::Core::TitleBar::onMaximizeClicked()
void c_KDDockWidgets__Core__TitleBar__onMaximizeClicked(void *thisObj);
// KDDockWidgets::Core::TitleBar::onMinimizeClicked()
void c_KDDockWidgets__Core__TitleBar__onMinimizeClicked(void *thisObj);
// KDDockWidgets::Core::TitleBar::setCloseButtonEnabled(bool arg__1)
void c_KDDockWidgets__Core__TitleBar__setCloseButtonEnabled_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::TitleBar::setFloatButtonVisible(bool arg__1)
void c_KDDockWidgets__Core__TitleBar__setFloatButtonVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::TitleBar::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__TitleBar__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::TitleBar::setTitle(const QString & title)
void c_KDDockWidgets__Core__TitleBar__setTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::Core::TitleBar::singleDockWidget() const
void *c_KDDockWidgets__Core__TitleBar__singleDockWidget(void *thisObj);
// KDDockWidgets::Core::TitleBar::supportsAutoHideButton() const
bool c_KDDockWidgets__Core__TitleBar__supportsAutoHideButton(void *thisObj);
// KDDockWidgets::Core::TitleBar::supportsFloatingButton() const
bool c_KDDockWidgets__Core__TitleBar__supportsFloatingButton(void *thisObj);
// KDDockWidgets::Core::TitleBar::supportsMaximizeButton() const
bool c_KDDockWidgets__Core__TitleBar__supportsMaximizeButton(void *thisObj);
// KDDockWidgets::Core::TitleBar::supportsMinimizeButton() const
bool c_KDDockWidgets__Core__TitleBar__supportsMinimizeButton(void *thisObj);
// KDDockWidgets::Core::TitleBar::tabBar() const
void *c_KDDockWidgets__Core__TitleBar__tabBar(void *thisObj);
// KDDockWidgets::Core::TitleBar::title() const
void *c_KDDockWidgets__Core__TitleBar__title(void *thisObj);
// KDDockWidgets::Core::TitleBar::titleBarIsFocusable() const
bool c_KDDockWidgets__Core__TitleBar__titleBarIsFocusable(void *thisObj);
// KDDockWidgets::Core::TitleBar::titleChanged()
void c_KDDockWidgets__Core__TitleBar__titleChanged(void *thisObj);
// KDDockWidgets::Core::TitleBar::toggleMaximized()
void c_KDDockWidgets__Core__TitleBar__toggleMaximized(void *thisObj);
// KDDockWidgets::Core::TitleBar::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__TitleBar__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Core::TitleBar::updateButtons()
void c_KDDockWidgets__Core__TitleBar__updateButtons(void *thisObj);
void c_KDDockWidgets__Core__TitleBar__destructor(void *thisObj);
void c_KDDockWidgets__Core__TitleBar__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__TitleBar_Finalizer(void *cppObj); // KDDockWidgets::Core::TabBar::TabBar(KDDockWidgets::Core::Stack * tabWidget)
void *c_KDDockWidgets__Core__TabBar__constructor_Stack(void *tabWidget_);
// KDDockWidgets::Core::TabBar::countChanged()
void c_KDDockWidgets__Core__TabBar__countChanged(void *thisObj);
// KDDockWidgets::Core::TabBar::currentDockWidget() const
void *c_KDDockWidgets__Core__TabBar__currentDockWidget(void *thisObj);
// KDDockWidgets::Core::TabBar::currentDockWidgetChanged(KDDockWidgets::Core::DockWidget * arg__1)
void c_KDDockWidgets__Core__TabBar__currentDockWidgetChanged_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::TabBar::currentIndex() const
int c_KDDockWidgets__Core__TabBar__currentIndex(void *thisObj);
// KDDockWidgets::Core::TabBar::dockWidgetAt(QPoint localPos) const
void *c_KDDockWidgets__Core__TabBar__dockWidgetAt_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::Core::TabBar::dockWidgetAt(int index) const
void *c_KDDockWidgets__Core__TabBar__dockWidgetAt_int(void *thisObj, int index);
// KDDockWidgets::Core::TabBar::dragCanStart(QPoint pressPos, QPoint pos) const
bool c_KDDockWidgets__Core__TabBar__dragCanStart_QPoint_QPoint(void *thisObj, void *pressPos_, void *pos_);
// KDDockWidgets::Core::TabBar::group() const
void *c_KDDockWidgets__Core__TabBar__group(void *thisObj);
// KDDockWidgets::Core::TabBar::hasSingleDockWidget() const
bool c_KDDockWidgets__Core__TabBar__hasSingleDockWidget(void *thisObj);
// KDDockWidgets::Core::TabBar::indexOfDockWidget(const KDDockWidgets::Core::DockWidget * dw) const
int c_KDDockWidgets__Core__TabBar__indexOfDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::TabBar::isMDI() const
bool c_KDDockWidgets__Core__TabBar__isMDI(void *thisObj);
// KDDockWidgets::Core::TabBar::isWindow() const
bool c_KDDockWidgets__Core__TabBar__isWindow(void *thisObj);
// KDDockWidgets::Core::TabBar::moveTabTo(int from, int to)
void c_KDDockWidgets__Core__TabBar__moveTabTo_int_int(void *thisObj, int from, int to);
// KDDockWidgets::Core::TabBar::numDockWidgets() const
int c_KDDockWidgets__Core__TabBar__numDockWidgets(void *thisObj);
// KDDockWidgets::Core::TabBar::onMouseDoubleClick(QPoint localPos)
void c_KDDockWidgets__Core__TabBar__onMouseDoubleClick_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::Core::TabBar::onMousePress(QPoint localPos)
void c_KDDockWidgets__Core__TabBar__onMousePress_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::Core::TabBar::rectForTab(int index) const
void *c_KDDockWidgets__Core__TabBar__rectForTab_int(void *thisObj, int index);
// KDDockWidgets::Core::TabBar::removeDockWidget(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__Core__TabBar__removeDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::TabBar::renameTab(int index, const QString & arg__2)
void c_KDDockWidgets__Core__TabBar__renameTab_int_QString(void *thisObj, int index, const char *arg__2_);
// KDDockWidgets::Core::TabBar::setCurrentDockWidget(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__Core__TabBar__setCurrentDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::TabBar::setCurrentIndex(int index)
void c_KDDockWidgets__Core__TabBar__setCurrentIndex_int(void *thisObj, int index);
// KDDockWidgets::Core::TabBar::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__TabBar__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::TabBar::singleDockWidget() const
void *c_KDDockWidgets__Core__TabBar__singleDockWidget(void *thisObj);
// KDDockWidgets::Core::TabBar::stack() const
void *c_KDDockWidgets__Core__TabBar__stack(void *thisObj);
// KDDockWidgets::Core::TabBar::tabsAreMovable() const
bool c_KDDockWidgets__Core__TabBar__tabsAreMovable(void *thisObj);
// KDDockWidgets::Core::TabBar::text(int index) const
void *c_KDDockWidgets__Core__TabBar__text_int(void *thisObj, int index);
// KDDockWidgets::Core::TabBar::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__TabBar__tr_char_char_int(const char *s, const char *c, int n);
void c_KDDockWidgets__Core__TabBar__destructor(void *thisObj);
void c_KDDockWidgets__Core__TabBar__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__TabBar_Finalizer(void *cppObj); // KDDockWidgets::Core::Stack::addDockWidget(KDDockWidgets::Core::DockWidget * arg__1)
void c_KDDockWidgets__Core__Stack__addDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Stack::contains(KDDockWidgets::Core::DockWidget * dw) const
bool c_KDDockWidgets__Core__Stack__contains_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::Stack::group() const
void *c_KDDockWidgets__Core__Stack__group(void *thisObj);
// KDDockWidgets::Core::Stack::insertDockWidget(KDDockWidgets::Core::DockWidget * dockwidget, int index)
bool c_KDDockWidgets__Core__Stack__insertDockWidget_DockWidget_int(void *thisObj, void *dockwidget_, int index);
// KDDockWidgets::Core::Stack::isMDI() const
bool c_KDDockWidgets__Core__Stack__isMDI(void *thisObj);
// KDDockWidgets::Core::Stack::isPositionDraggable(QPoint p) const
bool c_KDDockWidgets__Core__Stack__isPositionDraggable_QPoint(void *thisObj, void *p_);
// KDDockWidgets::Core::Stack::isWindow() const
bool c_KDDockWidgets__Core__Stack__isWindow(void *thisObj);
// KDDockWidgets::Core::Stack::numDockWidgets() const
int c_KDDockWidgets__Core__Stack__numDockWidgets(void *thisObj);
// KDDockWidgets::Core::Stack::onMouseDoubleClick(QPoint localPos)
bool c_KDDockWidgets__Core__Stack__onMouseDoubleClick_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::Core::Stack::setDocumentMode(bool arg__1)
void c_KDDockWidgets__Core__Stack__setDocumentMode_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::Stack::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__Stack__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::Stack::setTabBarAutoHide(bool arg__1)
void c_KDDockWidgets__Core__Stack__setTabBarAutoHide_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::Stack::singleDockWidget() const
void *c_KDDockWidgets__Core__Stack__singleDockWidget(void *thisObj);
// KDDockWidgets::Core::Stack::tabBar() const
void *c_KDDockWidgets__Core__Stack__tabBar(void *thisObj);
// KDDockWidgets::Core::Stack::tabBarAutoHide() const
bool c_KDDockWidgets__Core__Stack__tabBarAutoHide(void *thisObj);
// KDDockWidgets::Core::Stack::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__Stack__tr_char_char_int(const char *s, const char *c, int n);
void c_KDDockWidgets__Core__Stack__destructor(void *thisObj);
void c_KDDockWidgets__Core__Stack__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__Stack_Finalizer(void *cppObj); // KDDockWidgets::Core::SideBar::addDockWidget(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__Core__SideBar__addDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::SideBar::clear()
void c_KDDockWidgets__Core__SideBar__clear(void *thisObj);
// KDDockWidgets::Core::SideBar::containsDockWidget(KDDockWidgets::Core::DockWidget * arg__1) const
bool c_KDDockWidgets__Core__SideBar__containsDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::SideBar::isEmpty() const
bool c_KDDockWidgets__Core__SideBar__isEmpty(void *thisObj);
// KDDockWidgets::Core::SideBar::isVertical() const
bool c_KDDockWidgets__Core__SideBar__isVertical(void *thisObj);
// KDDockWidgets::Core::SideBar::mainWindow() const
void *c_KDDockWidgets__Core__SideBar__mainWindow(void *thisObj);
// KDDockWidgets::Core::SideBar::onButtonClicked(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__Core__SideBar__onButtonClicked_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::SideBar::removeDockWidget(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__Core__SideBar__removeDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::SideBar::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__SideBar__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::SideBar::toggleOverlay(KDDockWidgets::Core::DockWidget * arg__1)
void c_KDDockWidgets__Core__SideBar__toggleOverlay_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::SideBar::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__SideBar__tr_char_char_int(const char *s, const char *c, int n);
void c_KDDockWidgets__Core__SideBar__destructor(void *thisObj);
void c_KDDockWidgets__Core__SideBar__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__SideBar_Finalizer(void *cppObj); // KDDockWidgets::Core::Separator::Separator(KDDockWidgets::Core::View * host)
void *c_KDDockWidgets__Core__Separator__constructor_View(void *host_);
// KDDockWidgets::Core::Separator::isResizing()
bool c_static_KDDockWidgets__Core__Separator__isResizing();
// KDDockWidgets::Core::Separator::isVertical() const
bool c_KDDockWidgets__Core__Separator__isVertical(void *thisObj);
// KDDockWidgets::Core::Separator::move(int p)
void c_KDDockWidgets__Core__Separator__move_int(void *thisObj, int p);
// KDDockWidgets::Core::Separator::numSeparators()
int c_static_KDDockWidgets__Core__Separator__numSeparators();
// KDDockWidgets::Core::Separator::onMouseDoubleClick()
void c_KDDockWidgets__Core__Separator__onMouseDoubleClick(void *thisObj);
// KDDockWidgets::Core::Separator::onMouseMove(QPoint pos)
void c_KDDockWidgets__Core__Separator__onMouseMove_QPoint(void *thisObj, void *pos_);
// KDDockWidgets::Core::Separator::onMousePress()
void c_KDDockWidgets__Core__Separator__onMousePress(void *thisObj);
// KDDockWidgets::Core::Separator::onMouseReleased()
void c_KDDockWidgets__Core__Separator__onMouseReleased(void *thisObj);
// KDDockWidgets::Core::Separator::position() const
int c_KDDockWidgets__Core__Separator__position(void *thisObj);
// KDDockWidgets::Core::Separator::setGeometry(QRect r)
void c_KDDockWidgets__Core__Separator__setGeometry_QRect(void *thisObj, void *r_);
// KDDockWidgets::Core::Separator::setGeometry(int pos, int pos2, int length)
void c_KDDockWidgets__Core__Separator__setGeometry_int_int_int(void *thisObj, int pos, int pos2, int length);
// KDDockWidgets::Core::Separator::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__Separator__setParentView_impl_View(void *thisObj, void *parent_);
void c_KDDockWidgets__Core__Separator__destructor(void *thisObj);
void c_KDDockWidgets__Core__Separator__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__Separator_Finalizer(void *cppObj); // KDDockWidgets::Core::MainWindow::MainWindow(KDDockWidgets::Core::View * view, const QString & uniqueName, QFlags<KDDockWidgets::MainWindowOption> options)
void *c_KDDockWidgets__Core__MainWindow__constructor_View_QString_MainWindowOptions(void *view_, const char *uniqueName_, int options_);
// KDDockWidgets::Core::MainWindow::addDockWidget(KDDockWidgets::Core::DockWidget * dockWidget, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget * relativeTo, KDDockWidgets::InitialOption initialOption)
void c_KDDockWidgets__Core__MainWindow__addDockWidget_DockWidget_Location_DockWidget_InitialOption(void *thisObj, void *dockWidget_, int location, void *relativeTo_, void *initialOption_);
// KDDockWidgets::Core::MainWindow::addDockWidgetAsTab(KDDockWidgets::Core::DockWidget * dockwidget)
void c_KDDockWidgets__Core__MainWindow__addDockWidgetAsTab_DockWidget(void *thisObj, void *dockwidget_);
// KDDockWidgets::Core::MainWindow::anySideBarIsVisible() const
bool c_KDDockWidgets__Core__MainWindow__anySideBarIsVisible(void *thisObj);
// KDDockWidgets::Core::MainWindow::centralAreaGeometry() const
void *c_KDDockWidgets__Core__MainWindow__centralAreaGeometry(void *thisObj);
// KDDockWidgets::Core::MainWindow::clearSideBarOverlay(bool deleteFrame)
void c_KDDockWidgets__Core__MainWindow__clearSideBarOverlay_bool(void *thisObj, bool deleteFrame);
// KDDockWidgets::Core::MainWindow::closeDockWidgets(bool force)
bool c_KDDockWidgets__Core__MainWindow__closeDockWidgets_bool(void *thisObj, bool force);
// KDDockWidgets::Core::MainWindow::dropArea() const
void *c_KDDockWidgets__Core__MainWindow__dropArea(void *thisObj);
// KDDockWidgets::Core::MainWindow::groupCountChanged(int arg__1)
void c_KDDockWidgets__Core__MainWindow__groupCountChanged_int(void *thisObj, int arg__1);
// KDDockWidgets::Core::MainWindow::init(const QString & name)
void c_KDDockWidgets__Core__MainWindow__init_QString(void *thisObj, const char *name_);
// KDDockWidgets::Core::MainWindow::isMDI() const
bool c_KDDockWidgets__Core__MainWindow__isMDI(void *thisObj);
// KDDockWidgets::Core::MainWindow::layout() const
void *c_KDDockWidgets__Core__MainWindow__layout(void *thisObj);
// KDDockWidgets::Core::MainWindow::layoutEqually()
void c_KDDockWidgets__Core__MainWindow__layoutEqually(void *thisObj);
// KDDockWidgets::Core::MainWindow::layoutParentContainerEqually(KDDockWidgets::Core::DockWidget * dockWidget)
void c_KDDockWidgets__Core__MainWindow__layoutParentContainerEqually_DockWidget(void *thisObj, void *dockWidget_);
// KDDockWidgets::Core::MainWindow::moveToSideBar(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__Core__MainWindow__moveToSideBar_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::MainWindow::multiSplitter() const
void *c_KDDockWidgets__Core__MainWindow__multiSplitter(void *thisObj);
// KDDockWidgets::Core::MainWindow::options() const
int c_KDDockWidgets__Core__MainWindow__options(void *thisObj);
// KDDockWidgets::Core::MainWindow::overlayMargin() const
int c_KDDockWidgets__Core__MainWindow__overlayMargin(void *thisObj);
// KDDockWidgets::Core::MainWindow::overlayMarginChanged(int margin)
void c_KDDockWidgets__Core__MainWindow__overlayMarginChanged_int(void *thisObj, int margin);
// KDDockWidgets::Core::MainWindow::overlayOnSideBar(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__Core__MainWindow__overlayOnSideBar_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::MainWindow::overlayedDockWidget() const
void *c_KDDockWidgets__Core__MainWindow__overlayedDockWidget(void *thisObj);
// KDDockWidgets::Core::MainWindow::restoreFromSideBar(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__Core__MainWindow__restoreFromSideBar_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::MainWindow::setContentsMargins(int l, int t, int r, int b)
void c_KDDockWidgets__Core__MainWindow__setContentsMargins_int_int_int_int(void *thisObj, int l, int t, int r, int b);
// KDDockWidgets::Core::MainWindow::setOverlayMargin(int margin)
void c_KDDockWidgets__Core__MainWindow__setOverlayMargin_int(void *thisObj, int margin);
// KDDockWidgets::Core::MainWindow::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__MainWindow__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::MainWindow::setUniqueName(const QString & uniqueName)
void c_KDDockWidgets__Core__MainWindow__setUniqueName_QString(void *thisObj, const char *uniqueName_);
// KDDockWidgets::Core::MainWindow::sideBarForDockWidget(const KDDockWidgets::Core::DockWidget * dw) const
void *c_KDDockWidgets__Core__MainWindow__sideBarForDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::MainWindow::toggleOverlayOnSideBar(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__Core__MainWindow__toggleOverlayOnSideBar_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::MainWindow::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__MainWindow__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Core::MainWindow::uniqueName() const
void *c_KDDockWidgets__Core__MainWindow__uniqueName(void *thisObj);
// KDDockWidgets::Core::MainWindow::uniqueNameChanged()
void c_KDDockWidgets__Core__MainWindow__uniqueNameChanged(void *thisObj);
void c_KDDockWidgets__Core__MainWindow__destructor(void *thisObj);
void c_KDDockWidgets__Core__MainWindow__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__MainWindow_Finalizer(void *cppObj); // KDDockWidgets::Core::Layout::Layout(KDDockWidgets::Core::ViewType arg__1, KDDockWidgets::Core::View * arg__2)
void *c_KDDockWidgets__Core__Layout__constructor_ViewType_View(int arg__1, void *arg__2_);
// KDDockWidgets::Core::Layout::asDropArea() const
void *c_KDDockWidgets__Core__Layout__asDropArea(void *thisObj);
// KDDockWidgets::Core::Layout::checkSanity() const
bool c_KDDockWidgets__Core__Layout__checkSanity(void *thisObj);
// KDDockWidgets::Core::Layout::clearLayout()
void c_KDDockWidgets__Core__Layout__clearLayout(void *thisObj);
// KDDockWidgets::Core::Layout::containsFrame(const KDDockWidgets::Core::Group * arg__1) const
bool c_KDDockWidgets__Core__Layout__containsFrame_Group(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Layout::containsItem(const KDDockWidgets::Core::Item * arg__1) const
bool c_KDDockWidgets__Core__Layout__containsItem_Item(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Layout::count() const
int c_KDDockWidgets__Core__Layout__count(void *thisObj);
// KDDockWidgets::Core::Layout::dumpLayout() const
void c_KDDockWidgets__Core__Layout__dumpLayout(void *thisObj);
// KDDockWidgets::Core::Layout::floatingWindow() const
void *c_KDDockWidgets__Core__Layout__floatingWindow(void *thisObj);
// KDDockWidgets::Core::Layout::groups() const
void *c_KDDockWidgets__Core__Layout__groups(void *thisObj);
// KDDockWidgets::Core::Layout::groupsFrom(KDDockWidgets::Core::View * groupOrMultiSplitter) const
void *c_KDDockWidgets__Core__Layout__groupsFrom_View(void *thisObj, void *groupOrMultiSplitter_);
// KDDockWidgets::Core::Layout::isInMainWindow(bool honourNesting) const
bool c_KDDockWidgets__Core__Layout__isInMainWindow_bool(void *thisObj, bool honourNesting);
// KDDockWidgets::Core::Layout::itemForFrame(const KDDockWidgets::Core::Group * group) const
void *c_KDDockWidgets__Core__Layout__itemForFrame_Group(void *thisObj, void *group_);
// KDDockWidgets::Core::Layout::layoutHeight() const
int c_KDDockWidgets__Core__Layout__layoutHeight(void *thisObj);
// KDDockWidgets::Core::Layout::layoutMaximumSizeHint() const
void *c_KDDockWidgets__Core__Layout__layoutMaximumSizeHint(void *thisObj);
// KDDockWidgets::Core::Layout::layoutMinimumSize() const
void *c_KDDockWidgets__Core__Layout__layoutMinimumSize(void *thisObj);
// KDDockWidgets::Core::Layout::layoutSize() const
void *c_KDDockWidgets__Core__Layout__layoutSize(void *thisObj);
// KDDockWidgets::Core::Layout::layoutWidth() const
int c_KDDockWidgets__Core__Layout__layoutWidth(void *thisObj);
// KDDockWidgets::Core::Layout::mainWindow(bool honourNesting) const
void *c_KDDockWidgets__Core__Layout__mainWindow_bool(void *thisObj, bool honourNesting);
// KDDockWidgets::Core::Layout::placeholderCount() const
int c_KDDockWidgets__Core__Layout__placeholderCount(void *thisObj);
// KDDockWidgets::Core::Layout::removeItem(KDDockWidgets::Core::Item * item)
void c_KDDockWidgets__Core__Layout__removeItem_Item(void *thisObj, void *item_);
// KDDockWidgets::Core::Layout::restorePlaceholder(KDDockWidgets::Core::DockWidget * dw, KDDockWidgets::Core::Item * arg__2, int tabIndex)
void c_KDDockWidgets__Core__Layout__restorePlaceholder_DockWidget_Item_int(void *thisObj, void *dw_, void *arg__2_, int tabIndex);
// KDDockWidgets::Core::Layout::setLayoutMinimumSize(QSize arg__1)
void c_KDDockWidgets__Core__Layout__setLayoutMinimumSize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Layout::setLayoutSize(QSize arg__1)
void c_KDDockWidgets__Core__Layout__setLayoutSize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Layout::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__Layout__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::Layout::unrefOldPlaceholders(const QList<KDDockWidgets::Core::Group* > & groupsBeingAdded) const
void c_KDDockWidgets__Core__Layout__unrefOldPlaceholders_QList_Group(void *thisObj, void *groupsBeingAdded_);
// KDDockWidgets::Core::Layout::updateSizeConstraints()
void c_KDDockWidgets__Core__Layout__updateSizeConstraints(void *thisObj);
// KDDockWidgets::Core::Layout::viewAboutToBeDeleted()
void c_KDDockWidgets__Core__Layout__viewAboutToBeDeleted(void *thisObj);
// KDDockWidgets::Core::Layout::visibleCount() const
int c_KDDockWidgets__Core__Layout__visibleCount(void *thisObj);
void c_KDDockWidgets__Core__Layout__destructor(void *thisObj);
void c_KDDockWidgets__Core__Layout__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__Layout_Finalizer(void *cppObj); // KDDockWidgets::Core::DropArea::DropArea(KDDockWidgets::Core::View * parent, QFlags<KDDockWidgets::MainWindowOption> options, bool isMDIWrapper)
void *c_KDDockWidgets__Core__DropArea__constructor_View_MainWindowOptions_bool(void *parent_, int options_, bool isMDIWrapper);
// KDDockWidgets::Core::DropArea::addDockWidget(KDDockWidgets::Core::DockWidget * dw, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget * relativeTo, KDDockWidgets::InitialOption initialOption)
void c_KDDockWidgets__Core__DropArea__addDockWidget_DockWidget_Location_DockWidget_InitialOption(void *thisObj, void *dw_, int location, void *relativeTo_, void *initialOption_);
// KDDockWidgets::Core::DropArea::addMultiSplitter(KDDockWidgets::Core::DropArea * splitter, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo, KDDockWidgets::InitialOption option)
void c_KDDockWidgets__Core__DropArea__addMultiSplitter_DropArea_Location_Group_InitialOption(void *thisObj, void *splitter_, int location, void *relativeTo_, void *option_);
// KDDockWidgets::Core::DropArea::addWidget(KDDockWidgets::Core::View * widget, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo, KDDockWidgets::InitialOption option)
void c_KDDockWidgets__Core__DropArea__addWidget_View_Location_Group_InitialOption(void *thisObj, void *widget_, int location, void *relativeTo_, void *option_);
// KDDockWidgets::Core::DropArea::availableSize() const
void *c_KDDockWidgets__Core__DropArea__availableSize(void *thisObj);
// KDDockWidgets::Core::DropArea::centralFrame() const
void *c_KDDockWidgets__Core__DropArea__centralFrame(void *thisObj);
// KDDockWidgets::Core::DropArea::centralGroup() const
void *c_KDDockWidgets__Core__DropArea__centralGroup(void *thisObj);
// KDDockWidgets::Core::DropArea::containsDockWidget(KDDockWidgets::Core::DockWidget * arg__1) const
bool c_KDDockWidgets__Core__DropArea__containsDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::DropArea::createCentralFrame(QFlags<KDDockWidgets::MainWindowOption> options)
void *c_static_KDDockWidgets__Core__DropArea__createCentralFrame_MainWindowOptions(int options_);
// KDDockWidgets::Core::DropArea::currentDropLocation() const
int c_KDDockWidgets__Core__DropArea__currentDropLocation(void *thisObj);
// KDDockWidgets::Core::DropArea::drop(KDDockWidgets::Core::View * droppedwindow, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo)
bool c_KDDockWidgets__Core__DropArea__drop_View_Location_Group(void *thisObj, void *droppedwindow_, int location, void *relativeTo_);
// KDDockWidgets::Core::DropArea::dropIndicatorOverlay() const
void *c_KDDockWidgets__Core__DropArea__dropIndicatorOverlay(void *thisObj);
// KDDockWidgets::Core::DropArea::groupContainingPos(QPoint globalPos) const
void *c_KDDockWidgets__Core__DropArea__groupContainingPos_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::Core::DropArea::groups() const
void *c_KDDockWidgets__Core__DropArea__groups(void *thisObj);
// KDDockWidgets::Core::DropArea::hasSingleFloatingFrame() const
bool c_KDDockWidgets__Core__DropArea__hasSingleFloatingFrame(void *thisObj);
// KDDockWidgets::Core::DropArea::hasSingleFrame() const
bool c_KDDockWidgets__Core__DropArea__hasSingleFrame(void *thisObj);
// KDDockWidgets::Core::DropArea::isMDIWrapper() const
bool c_KDDockWidgets__Core__DropArea__isMDIWrapper(void *thisObj);
// KDDockWidgets::Core::DropArea::layoutEqually()
void c_KDDockWidgets__Core__DropArea__layoutEqually(void *thisObj);
// KDDockWidgets::Core::DropArea::layoutParentContainerEqually(KDDockWidgets::Core::DockWidget * arg__1)
void c_KDDockWidgets__Core__DropArea__layoutParentContainerEqually_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::DropArea::mdiDockWidgetWrapper() const
void *c_KDDockWidgets__Core__DropArea__mdiDockWidgetWrapper(void *thisObj);
// KDDockWidgets::Core::DropArea::removeHover()
void c_KDDockWidgets__Core__DropArea__removeHover(void *thisObj);
// KDDockWidgets::Core::DropArea::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__DropArea__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::DropArea::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__DropArea__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Core::DropArea::updateFloatingActions()
void c_KDDockWidgets__Core__DropArea__updateFloatingActions(void *thisObj);
// KDDockWidgets::Core::DropArea::validateInputs(KDDockWidgets::Core::View * widget, KDDockWidgets::Location location, const KDDockWidgets::Core::Group * relativeToFrame, KDDockWidgets::InitialOption option) const
bool c_KDDockWidgets__Core__DropArea__validateInputs_View_Location_Group_InitialOption(void *thisObj, void *widget_, int location, void *relativeToFrame_, void *option_);
void c_KDDockWidgets__Core__DropArea__destructor(void *thisObj);
void c_KDDockWidgets__Core__DropArea__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__DropArea_Finalizer(void *cppObj); // KDDockWidgets::Core::Group::Group(KDDockWidgets::Core::View * parent)
void *c_KDDockWidgets__Core__Group__constructor_View(void *parent_);
// KDDockWidgets::Core::Group::actualTitleBar() const
void *c_KDDockWidgets__Core__Group__actualTitleBar(void *thisObj);
// KDDockWidgets::Core::Group::actualTitleBarChanged()
void c_KDDockWidgets__Core__Group__actualTitleBarChanged(void *thisObj);
// KDDockWidgets::Core::Group::addTab(KDDockWidgets::Core::DockWidget * arg__1, KDDockWidgets::InitialOption arg__2)
void c_KDDockWidgets__Core__Group__addTab_DockWidget_InitialOption(void *thisObj, void *arg__1_, void *arg__2_);
// KDDockWidgets::Core::Group::addTab(KDDockWidgets::Core::FloatingWindow * floatingWindow, KDDockWidgets::InitialOption arg__2)
void c_KDDockWidgets__Core__Group__addTab_FloatingWindow_InitialOption(void *thisObj, void *floatingWindow_, void *arg__2_);
// KDDockWidgets::Core::Group::addTab(KDDockWidgets::Core::Group * arg__1, KDDockWidgets::InitialOption arg__2)
void c_KDDockWidgets__Core__Group__addTab_Group_InitialOption(void *thisObj, void *arg__1_, void *arg__2_);
// KDDockWidgets::Core::Group::allDockWidgetsHave(KDDockWidgets::DockWidgetOption arg__1) const
bool c_KDDockWidgets__Core__Group__allDockWidgetsHave_DockWidgetOption(void *thisObj, int arg__1);
// KDDockWidgets::Core::Group::allDockWidgetsHave(KDDockWidgets::LayoutSaverOption arg__1) const
bool c_KDDockWidgets__Core__Group__allDockWidgetsHave_LayoutSaverOption(void *thisObj, int arg__1);
// KDDockWidgets::Core::Group::alwaysShowsTabs() const
bool c_KDDockWidgets__Core__Group__alwaysShowsTabs(void *thisObj);
// KDDockWidgets::Core::Group::anyDockWidgetsHas(KDDockWidgets::DockWidgetOption arg__1) const
bool c_KDDockWidgets__Core__Group__anyDockWidgetsHas_DockWidgetOption(void *thisObj, int arg__1);
// KDDockWidgets::Core::Group::anyDockWidgetsHas(KDDockWidgets::LayoutSaverOption arg__1) const
bool c_KDDockWidgets__Core__Group__anyDockWidgetsHas_LayoutSaverOption(void *thisObj, int arg__1);
// KDDockWidgets::Core::Group::anyNonClosable() const
bool c_KDDockWidgets__Core__Group__anyNonClosable(void *thisObj);
// KDDockWidgets::Core::Group::anyNonDockable() const
bool c_KDDockWidgets__Core__Group__anyNonDockable(void *thisObj);
// KDDockWidgets::Core::Group::beingDeletedLater() const
bool c_KDDockWidgets__Core__Group__beingDeletedLater(void *thisObj);
// KDDockWidgets::Core::Group::biggestDockWidgetMaxSize() const
void *c_KDDockWidgets__Core__Group__biggestDockWidgetMaxSize(void *thisObj);
// KDDockWidgets::Core::Group::containsDockWidget(KDDockWidgets::Core::DockWidget * w) const
bool c_KDDockWidgets__Core__Group__containsDockWidget_DockWidget(void *thisObj, void *w_);
// KDDockWidgets::Core::Group::containsMouse(QPoint globalPos) const
bool c_KDDockWidgets__Core__Group__containsMouse_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::Core::Group::currentDockWidget() const
void *c_KDDockWidgets__Core__Group__currentDockWidget(void *thisObj);
// KDDockWidgets::Core::Group::currentIndex() const
int c_KDDockWidgets__Core__Group__currentIndex(void *thisObj);
// KDDockWidgets::Core::Group::currentTabIndex() const
int c_KDDockWidgets__Core__Group__currentTabIndex(void *thisObj);
// KDDockWidgets::Core::Group::dbg_numFrames()
int c_static_KDDockWidgets__Core__Group__dbg_numFrames();
// KDDockWidgets::Core::Group::detachTab(KDDockWidgets::Core::DockWidget * arg__1)
void *c_KDDockWidgets__Core__Group__detachTab_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Group::dockWidgetAt(int index) const
void *c_KDDockWidgets__Core__Group__dockWidgetAt_int(void *thisObj, int index);
// KDDockWidgets::Core::Group::dockWidgetCount() const
int c_KDDockWidgets__Core__Group__dockWidgetCount(void *thisObj);
// KDDockWidgets::Core::Group::dockWidgetsMinSize() const
void *c_KDDockWidgets__Core__Group__dockWidgetsMinSize(void *thisObj);
// KDDockWidgets::Core::Group::dragRect() const
void *c_KDDockWidgets__Core__Group__dragRect(void *thisObj);
// KDDockWidgets::Core::Group::floatingWindow() const
void *c_KDDockWidgets__Core__Group__floatingWindow(void *thisObj);
// KDDockWidgets::Core::Group::focusedWidgetChanged()
void c_KDDockWidgets__Core__Group__focusedWidgetChanged(void *thisObj);
// KDDockWidgets::Core::Group::focusedWidgetChangedCallback()
void c_KDDockWidgets__Core__Group__focusedWidgetChangedCallback(void *thisObj);
// KDDockWidgets::Core::Group::hasNestedMDIDockWidgets() const
bool c_KDDockWidgets__Core__Group__hasNestedMDIDockWidgets(void *thisObj);
// KDDockWidgets::Core::Group::hasSingleDockWidget() const
bool c_KDDockWidgets__Core__Group__hasSingleDockWidget(void *thisObj);
// KDDockWidgets::Core::Group::hasTabsVisible() const
bool c_KDDockWidgets__Core__Group__hasTabsVisible(void *thisObj);
// KDDockWidgets::Core::Group::hasTabsVisibleChanged()
void c_KDDockWidgets__Core__Group__hasTabsVisibleChanged(void *thisObj);
// KDDockWidgets::Core::Group::indexOfDockWidget(const KDDockWidgets::Core::DockWidget * arg__1)
int c_KDDockWidgets__Core__Group__indexOfDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Group::insertDockWidget(KDDockWidgets::Core::DockWidget * arg__1, int index)
void c_KDDockWidgets__Core__Group__insertDockWidget_DockWidget_int(void *thisObj, void *arg__1_, int index);
// KDDockWidgets::Core::Group::insertWidget(KDDockWidgets::Core::DockWidget * arg__1, int index, KDDockWidgets::InitialOption arg__3)
void c_KDDockWidgets__Core__Group__insertWidget_DockWidget_int_InitialOption(void *thisObj, void *arg__1_, int index, void *arg__3_);
// KDDockWidgets::Core::Group::isCentralFrame() const
bool c_KDDockWidgets__Core__Group__isCentralFrame(void *thisObj);
// KDDockWidgets::Core::Group::isDockable() const
bool c_KDDockWidgets__Core__Group__isDockable(void *thisObj);
// KDDockWidgets::Core::Group::isEmpty() const
bool c_KDDockWidgets__Core__Group__isEmpty(void *thisObj);
// KDDockWidgets::Core::Group::isFloating() const
bool c_KDDockWidgets__Core__Group__isFloating(void *thisObj);
// KDDockWidgets::Core::Group::isFocusedChanged()
void c_KDDockWidgets__Core__Group__isFocusedChanged(void *thisObj);
// KDDockWidgets::Core::Group::isFocusedChangedCallback()
void c_KDDockWidgets__Core__Group__isFocusedChangedCallback(void *thisObj);
// KDDockWidgets::Core::Group::isInFloatingWindow() const
bool c_KDDockWidgets__Core__Group__isInFloatingWindow(void *thisObj);
// KDDockWidgets::Core::Group::isInMainWindow() const
bool c_KDDockWidgets__Core__Group__isInMainWindow(void *thisObj);
// KDDockWidgets::Core::Group::isInMainWindowChanged()
void c_KDDockWidgets__Core__Group__isInMainWindowChanged(void *thisObj);
// KDDockWidgets::Core::Group::isMDI() const
bool c_KDDockWidgets__Core__Group__isMDI(void *thisObj);
// KDDockWidgets::Core::Group::isMDIChanged()
void c_KDDockWidgets__Core__Group__isMDIChanged(void *thisObj);
// KDDockWidgets::Core::Group::isMDIWrapper() const
bool c_KDDockWidgets__Core__Group__isMDIWrapper(void *thisObj);
// KDDockWidgets::Core::Group::isOverlayed() const
bool c_KDDockWidgets__Core__Group__isOverlayed(void *thisObj);
// KDDockWidgets::Core::Group::isTheOnlyGroup() const
bool c_KDDockWidgets__Core__Group__isTheOnlyGroup(void *thisObj);
// KDDockWidgets::Core::Group::layoutItem() const
void *c_KDDockWidgets__Core__Group__layoutItem(void *thisObj);
// KDDockWidgets::Core::Group::mainWindow() const
void *c_KDDockWidgets__Core__Group__mainWindow(void *thisObj);
// KDDockWidgets::Core::Group::mdiDockWidgetWrapper() const
void *c_KDDockWidgets__Core__Group__mdiDockWidgetWrapper(void *thisObj);
// KDDockWidgets::Core::Group::mdiDropAreaWrapper() const
void *c_KDDockWidgets__Core__Group__mdiDropAreaWrapper(void *thisObj);
// KDDockWidgets::Core::Group::mdiFrame() const
void *c_KDDockWidgets__Core__Group__mdiFrame(void *thisObj);
// KDDockWidgets::Core::Group::nonContentsHeight() const
int c_KDDockWidgets__Core__Group__nonContentsHeight(void *thisObj);
// KDDockWidgets::Core::Group::numDockWidgetsChanged()
void c_KDDockWidgets__Core__Group__numDockWidgetsChanged(void *thisObj);
// KDDockWidgets::Core::Group::onDockWidgetCountChanged()
void c_KDDockWidgets__Core__Group__onDockWidgetCountChanged(void *thisObj);
// KDDockWidgets::Core::Group::onDockWidgetTitleChanged()
void c_KDDockWidgets__Core__Group__onDockWidgetTitleChanged(void *thisObj);
// KDDockWidgets::Core::Group::removeWidget(KDDockWidgets::Core::DockWidget * arg__1)
void c_KDDockWidgets__Core__Group__removeWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Group::renameTab(int index, const QString & arg__2)
void c_KDDockWidgets__Core__Group__renameTab_int_QString(void *thisObj, int index, const char *arg__2_);
// KDDockWidgets::Core::Group::restoreToPreviousPosition()
void c_KDDockWidgets__Core__Group__restoreToPreviousPosition(void *thisObj);
// KDDockWidgets::Core::Group::setCurrentDockWidget(KDDockWidgets::Core::DockWidget * arg__1)
void c_KDDockWidgets__Core__Group__setCurrentDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Group::setCurrentTabIndex(int index)
void c_KDDockWidgets__Core__Group__setCurrentTabIndex_int(void *thisObj, int index);
// KDDockWidgets::Core::Group::setLayout(KDDockWidgets::Core::Layout * arg__1)
void c_KDDockWidgets__Core__Group__setLayout_Layout(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Group::setLayoutItem(KDDockWidgets::Core::Item * item)
void c_KDDockWidgets__Core__Group__setLayoutItem_Item(void *thisObj, void *item_);
// KDDockWidgets::Core::Group::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__Group__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::Group::stack() const
void *c_KDDockWidgets__Core__Group__stack(void *thisObj);
// KDDockWidgets::Core::Group::tabBar() const
void *c_KDDockWidgets__Core__Group__tabBar(void *thisObj);
// KDDockWidgets::Core::Group::title() const
void *c_KDDockWidgets__Core__Group__title(void *thisObj);
// KDDockWidgets::Core::Group::titleBar() const
void *c_KDDockWidgets__Core__Group__titleBar(void *thisObj);
// KDDockWidgets::Core::Group::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__Group__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Core::Group::unoverlay()
void c_KDDockWidgets__Core__Group__unoverlay(void *thisObj);
// KDDockWidgets::Core::Group::updateFloatingActions()
void c_KDDockWidgets__Core__Group__updateFloatingActions(void *thisObj);
// KDDockWidgets::Core::Group::updateTitleAndIcon()
void c_KDDockWidgets__Core__Group__updateTitleAndIcon(void *thisObj);
// KDDockWidgets::Core::Group::updateTitleBarVisibility()
void c_KDDockWidgets__Core__Group__updateTitleBarVisibility(void *thisObj);
// KDDockWidgets::Core::Group::userType() const
int c_KDDockWidgets__Core__Group__userType(void *thisObj);
void c_KDDockWidgets__Core__Group__destructor(void *thisObj);
void c_KDDockWidgets__Core__Group__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__Group_Finalizer(void *cppObj); // KDDockWidgets::Core::FloatingWindow::FloatingWindow(KDDockWidgets::Core::Group * group, QRect suggestedGeometry, KDDockWidgets::Core::MainWindow * parent)
void *c_KDDockWidgets__Core__FloatingWindow__constructor_Group_QRect_MainWindow(void *group_, void *suggestedGeometry_, void *parent_);
// KDDockWidgets::Core::FloatingWindow::FloatingWindow(QRect suggestedGeometry, KDDockWidgets::Core::MainWindow * parent)
void *c_KDDockWidgets__Core__FloatingWindow__constructor_QRect_MainWindow(void *suggestedGeometry_, void *parent_);
// KDDockWidgets::Core::FloatingWindow::activatedChanged()
void c_KDDockWidgets__Core__FloatingWindow__activatedChanged(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::addDockWidget(KDDockWidgets::Core::DockWidget * arg__1, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget * relativeTo, KDDockWidgets::InitialOption arg__4)
void c_KDDockWidgets__Core__FloatingWindow__addDockWidget_DockWidget_Location_DockWidget_InitialOption(void *thisObj, void *arg__1_, int location, void *relativeTo_, void *arg__4_);
// KDDockWidgets::Core::FloatingWindow::allDockWidgetsHave(KDDockWidgets::DockWidgetOption arg__1) const
bool c_KDDockWidgets__Core__FloatingWindow__allDockWidgetsHave_DockWidgetOption(void *thisObj, int arg__1);
// KDDockWidgets::Core::FloatingWindow::allDockWidgetsHave(KDDockWidgets::LayoutSaverOption arg__1) const
bool c_KDDockWidgets__Core__FloatingWindow__allDockWidgetsHave_LayoutSaverOption(void *thisObj, int arg__1);
// KDDockWidgets::Core::FloatingWindow::anyDockWidgetsHas(KDDockWidgets::DockWidgetOption arg__1) const
bool c_KDDockWidgets__Core__FloatingWindow__anyDockWidgetsHas_DockWidgetOption(void *thisObj, int arg__1);
// KDDockWidgets::Core::FloatingWindow::anyDockWidgetsHas(KDDockWidgets::LayoutSaverOption arg__1) const
bool c_KDDockWidgets__Core__FloatingWindow__anyDockWidgetsHas_LayoutSaverOption(void *thisObj, int arg__1);
// KDDockWidgets::Core::FloatingWindow::anyNonClosable() const
bool c_KDDockWidgets__Core__FloatingWindow__anyNonClosable(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::anyNonDockable() const
bool c_KDDockWidgets__Core__FloatingWindow__anyNonDockable(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::beingDeleted() const
bool c_KDDockWidgets__Core__FloatingWindow__beingDeleted(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::dragRect() const
void *c_KDDockWidgets__Core__FloatingWindow__dragRect(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::dropArea() const
void *c_KDDockWidgets__Core__FloatingWindow__dropArea(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::ensureRectIsOnScreen(QRect & geometry)
void c_static_KDDockWidgets__Core__FloatingWindow__ensureRectIsOnScreen_QRect(void *geometry_);
// KDDockWidgets::Core::FloatingWindow::hasSingleDockWidget() const
bool c_KDDockWidgets__Core__FloatingWindow__hasSingleDockWidget(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::hasSingleFrame() const
bool c_KDDockWidgets__Core__FloatingWindow__hasSingleFrame(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::isInDragArea(QPoint globalPoint) const
bool c_KDDockWidgets__Core__FloatingWindow__isInDragArea_QPoint(void *thisObj, void *globalPoint_);
// KDDockWidgets::Core::FloatingWindow::isMDI() const
bool c_KDDockWidgets__Core__FloatingWindow__isMDI(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::isUtilityWindow() const
bool c_KDDockWidgets__Core__FloatingWindow__isUtilityWindow(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::isWindow() const
bool c_KDDockWidgets__Core__FloatingWindow__isWindow(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::layout() const
void *c_KDDockWidgets__Core__FloatingWindow__layout(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::mainWindow() const
void *c_KDDockWidgets__Core__FloatingWindow__mainWindow(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::maybeCreateResizeHandler()
void c_KDDockWidgets__Core__FloatingWindow__maybeCreateResizeHandler(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::multiSplitter() const
void *c_KDDockWidgets__Core__FloatingWindow__multiSplitter(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::numDockWidgetsChanged()
void c_KDDockWidgets__Core__FloatingWindow__numDockWidgetsChanged(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::numFramesChanged()
void c_KDDockWidgets__Core__FloatingWindow__numFramesChanged(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::scheduleDeleteLater()
void c_KDDockWidgets__Core__FloatingWindow__scheduleDeleteLater(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__FloatingWindow__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::FloatingWindow::setSuggestedGeometry(QRect suggestedRect)
void c_KDDockWidgets__Core__FloatingWindow__setSuggestedGeometry_QRect(void *thisObj, void *suggestedRect_);
// KDDockWidgets::Core::FloatingWindow::singleDockWidget() const
void *c_KDDockWidgets__Core__FloatingWindow__singleDockWidget(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::singleFrame() const
void *c_KDDockWidgets__Core__FloatingWindow__singleFrame(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::supportsMaximizeButton() const
bool c_KDDockWidgets__Core__FloatingWindow__supportsMaximizeButton(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::supportsMinimizeButton() const
bool c_KDDockWidgets__Core__FloatingWindow__supportsMinimizeButton(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::titleBar() const
void *c_KDDockWidgets__Core__FloatingWindow__titleBar(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__FloatingWindow__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Core::FloatingWindow::updateTitleAndIcon()
void c_KDDockWidgets__Core__FloatingWindow__updateTitleAndIcon(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::updateTitleBarVisibility()
void c_KDDockWidgets__Core__FloatingWindow__updateTitleBarVisibility(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::userType() const
int c_KDDockWidgets__Core__FloatingWindow__userType(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::windowStateChanged()
void c_KDDockWidgets__Core__FloatingWindow__windowStateChanged(void *thisObj);
void c_KDDockWidgets__Core__FloatingWindow__destructor(void *thisObj);
void c_KDDockWidgets__Core__FloatingWindow__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__FloatingWindow_Finalizer(void *cppObj); // KDDockWidgets::Core::DropIndicatorOverlay::DropIndicatorOverlay(KDDockWidgets::Core::DropArea * dropArea)
void *c_KDDockWidgets__Core__DropIndicatorOverlay__constructor_DropArea(void *dropArea_);
// KDDockWidgets::Core::DropIndicatorOverlay::DropIndicatorOverlay(KDDockWidgets::Core::DropArea * dropArea, KDDockWidgets::Core::View * view)
void *c_KDDockWidgets__Core__DropIndicatorOverlay__constructor_DropArea_View(void *dropArea_, void *view_);
// KDDockWidgets::Core::DropIndicatorOverlay::currentDropLocation() const
int c_KDDockWidgets__Core__DropIndicatorOverlay__currentDropLocation(void *thisObj);
// KDDockWidgets::Core::DropIndicatorOverlay::currentDropLocationChanged()
void c_KDDockWidgets__Core__DropIndicatorOverlay__currentDropLocationChanged(void *thisObj);
// KDDockWidgets::Core::DropIndicatorOverlay::dropIndicatorVisible(KDDockWidgets::DropLocation arg__1) const
bool c_KDDockWidgets__Core__DropIndicatorOverlay__dropIndicatorVisible_DropLocation(void *thisObj, int arg__1);
// KDDockWidgets::Core::DropIndicatorOverlay::hover(QPoint globalPos)
int c_KDDockWidgets__Core__DropIndicatorOverlay__hover_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::Core::DropIndicatorOverlay::hover_impl(QPoint globalPos)
int c_KDDockWidgets__Core__DropIndicatorOverlay__hover_impl_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::Core::DropIndicatorOverlay::hoveredGroup() const
void *c_KDDockWidgets__Core__DropIndicatorOverlay__hoveredGroup(void *thisObj);
// KDDockWidgets::Core::DropIndicatorOverlay::hoveredGroupChanged(KDDockWidgets::Core::Group * arg__1)
void c_KDDockWidgets__Core__DropIndicatorOverlay__hoveredGroupChanged_Group(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::DropIndicatorOverlay::hoveredGroupRect() const
void *c_KDDockWidgets__Core__DropIndicatorOverlay__hoveredGroupRect(void *thisObj);
// KDDockWidgets::Core::DropIndicatorOverlay::hoveredGroupRectChanged()
void c_KDDockWidgets__Core__DropIndicatorOverlay__hoveredGroupRectChanged(void *thisObj);
// KDDockWidgets::Core::DropIndicatorOverlay::isHovered() const
bool c_KDDockWidgets__Core__DropIndicatorOverlay__isHovered(void *thisObj);
// KDDockWidgets::Core::DropIndicatorOverlay::multisplitterLocationFor(KDDockWidgets::DropLocation arg__1)
int c_static_KDDockWidgets__Core__DropIndicatorOverlay__multisplitterLocationFor_DropLocation(int arg__1);
// KDDockWidgets::Core::DropIndicatorOverlay::onHoveredGroupChanged(KDDockWidgets::Core::Group * arg__1)
void c_KDDockWidgets__Core__DropIndicatorOverlay__onHoveredGroupChanged_Group(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::DropIndicatorOverlay::posForIndicator(KDDockWidgets::DropLocation arg__1) const
void *c_KDDockWidgets__Core__DropIndicatorOverlay__posForIndicator_DropLocation(void *thisObj, int arg__1);
// KDDockWidgets::Core::DropIndicatorOverlay::removeHover()
void c_KDDockWidgets__Core__DropIndicatorOverlay__removeHover(void *thisObj);
// KDDockWidgets::Core::DropIndicatorOverlay::setCurrentDropLocation(KDDockWidgets::DropLocation arg__1)
void c_KDDockWidgets__Core__DropIndicatorOverlay__setCurrentDropLocation_DropLocation(void *thisObj, int arg__1);
// KDDockWidgets::Core::DropIndicatorOverlay::setHoveredGroup(KDDockWidgets::Core::Group * arg__1)
void c_KDDockWidgets__Core__DropIndicatorOverlay__setHoveredGroup_Group(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::DropIndicatorOverlay::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__DropIndicatorOverlay__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::DropIndicatorOverlay::setWindowBeingDragged(bool arg__1)
void c_KDDockWidgets__Core__DropIndicatorOverlay__setWindowBeingDragged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::DropIndicatorOverlay::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__DropIndicatorOverlay__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Core::DropIndicatorOverlay::updateVisibility()
void c_KDDockWidgets__Core__DropIndicatorOverlay__updateVisibility(void *thisObj);
void c_KDDockWidgets__Core__DropIndicatorOverlay__destructor(void *thisObj);
void c_KDDockWidgets__Core__DropIndicatorOverlay__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__DropIndicatorOverlay_Finalizer(void *cppObj); // KDDockWidgets::Core::DockWidget::DockWidget(KDDockWidgets::Core::View * view, const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions)
void *c_KDDockWidgets__Core__DockWidget__constructor_View_QString_DockWidgetOptions_LayoutSaverOptions(void *view_, const char *uniqueName_, int options_, int layoutSaverOptions_);
// KDDockWidgets::Core::DockWidget::aboutToDelete(KDDockWidgets::Core::DockWidget * arg__1)
void c_KDDockWidgets__Core__DockWidget__aboutToDelete_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::DockWidget::aboutToDeleteOnClose()
void c_KDDockWidgets__Core__DockWidget__aboutToDeleteOnClose(void *thisObj);
// KDDockWidgets::Core::DockWidget::actualTitleBarChanged()
void c_KDDockWidgets__Core__DockWidget__actualTitleBarChanged(void *thisObj);
// KDDockWidgets::Core::DockWidget::addDockWidgetAsTab(KDDockWidgets::Core::DockWidget * other, KDDockWidgets::InitialOption initialOption)
void c_KDDockWidgets__Core__DockWidget__addDockWidgetAsTab_DockWidget_InitialOption(void *thisObj, void *other_, void *initialOption_);
// KDDockWidgets::Core::DockWidget::addDockWidgetToContainingWindow(KDDockWidgets::Core::DockWidget * other, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget * relativeTo, KDDockWidgets::InitialOption initialOption)
void c_KDDockWidgets__Core__DockWidget__addDockWidgetToContainingWindow_DockWidget_Location_DockWidget_InitialOption(void *thisObj, void *other_, int location, void *relativeTo_, void *initialOption_);
// KDDockWidgets::Core::DockWidget::byName(const QString & uniqueName)
void *c_static_KDDockWidgets__Core__DockWidget__byName_QString(const char *uniqueName_);
// KDDockWidgets::Core::DockWidget::closed()
void c_KDDockWidgets__Core__DockWidget__closed(void *thisObj);
// KDDockWidgets::Core::DockWidget::currentTabIndex() const
int c_KDDockWidgets__Core__DockWidget__currentTabIndex(void *thisObj);
// KDDockWidgets::Core::DockWidget::floatingWindow() const
void *c_KDDockWidgets__Core__DockWidget__floatingWindow(void *thisObj);
// KDDockWidgets::Core::DockWidget::forceClose()
void c_KDDockWidgets__Core__DockWidget__forceClose(void *thisObj);
// KDDockWidgets::Core::DockWidget::groupGeometry() const
void *c_KDDockWidgets__Core__DockWidget__groupGeometry(void *thisObj);
// KDDockWidgets::Core::DockWidget::guestViewChanged()
void c_KDDockWidgets__Core__DockWidget__guestViewChanged(void *thisObj);
// KDDockWidgets::Core::DockWidget::hasPreviousDockedLocation() const
bool c_KDDockWidgets__Core__DockWidget__hasPreviousDockedLocation(void *thisObj);
// KDDockWidgets::Core::DockWidget::iconChanged()
void c_KDDockWidgets__Core__DockWidget__iconChanged(void *thisObj);
// KDDockWidgets::Core::DockWidget::init()
void c_KDDockWidgets__Core__DockWidget__init(void *thisObj);
// KDDockWidgets::Core::DockWidget::isCurrentTab() const
bool c_KDDockWidgets__Core__DockWidget__isCurrentTab(void *thisObj);
// KDDockWidgets::Core::DockWidget::isFloating() const
bool c_KDDockWidgets__Core__DockWidget__isFloating(void *thisObj);
// KDDockWidgets::Core::DockWidget::isFloatingChanged(bool arg__1)
void c_KDDockWidgets__Core__DockWidget__isFloatingChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::DockWidget::isFocused() const
bool c_KDDockWidgets__Core__DockWidget__isFocused(void *thisObj);
// KDDockWidgets::Core::DockWidget::isFocusedChanged(bool arg__1)
void c_KDDockWidgets__Core__DockWidget__isFocusedChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::DockWidget::isInMainWindow() const
bool c_KDDockWidgets__Core__DockWidget__isInMainWindow(void *thisObj);
// KDDockWidgets::Core::DockWidget::isInSideBar() const
bool c_KDDockWidgets__Core__DockWidget__isInSideBar(void *thisObj);
// KDDockWidgets::Core::DockWidget::isMainWindow() const
bool c_KDDockWidgets__Core__DockWidget__isMainWindow(void *thisObj);
// KDDockWidgets::Core::DockWidget::isOpen() const
bool c_KDDockWidgets__Core__DockWidget__isOpen(void *thisObj);
// KDDockWidgets::Core::DockWidget::isOpenChanged(bool isOpen)
void c_KDDockWidgets__Core__DockWidget__isOpenChanged_bool(void *thisObj, bool isOpen);
// KDDockWidgets::Core::DockWidget::isOverlayed() const
bool c_KDDockWidgets__Core__DockWidget__isOverlayed(void *thisObj);
// KDDockWidgets::Core::DockWidget::isOverlayedChanged(bool arg__1)
void c_KDDockWidgets__Core__DockWidget__isOverlayedChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::DockWidget::isPersistentCentralDockWidget() const
bool c_KDDockWidgets__Core__DockWidget__isPersistentCentralDockWidget(void *thisObj);
// KDDockWidgets::Core::DockWidget::isTabbed() const
bool c_KDDockWidgets__Core__DockWidget__isTabbed(void *thisObj);
// KDDockWidgets::Core::DockWidget::lastOverlayedSize() const
void *c_KDDockWidgets__Core__DockWidget__lastOverlayedSize(void *thisObj);
// KDDockWidgets::Core::DockWidget::layoutSaverOptions() const
int c_KDDockWidgets__Core__DockWidget__layoutSaverOptions(void *thisObj);
// KDDockWidgets::Core::DockWidget::mainWindow() const
void *c_KDDockWidgets__Core__DockWidget__mainWindow(void *thisObj);
// KDDockWidgets::Core::DockWidget::moveToSideBar()
void c_KDDockWidgets__Core__DockWidget__moveToSideBar(void *thisObj);
// KDDockWidgets::Core::DockWidget::onResize(QSize newSize)
void c_KDDockWidgets__Core__DockWidget__onResize_QSize(void *thisObj, void *newSize_);
// KDDockWidgets::Core::DockWidget::open()
void c_KDDockWidgets__Core__DockWidget__open(void *thisObj);
// KDDockWidgets::Core::DockWidget::options() const
int c_KDDockWidgets__Core__DockWidget__options(void *thisObj);
// KDDockWidgets::Core::DockWidget::optionsChanged(QFlags<KDDockWidgets::DockWidgetOption> arg__1)
void c_KDDockWidgets__Core__DockWidget__optionsChanged_DockWidgetOptions(void *thisObj, int arg__1_);
// KDDockWidgets::Core::DockWidget::raise()
void c_KDDockWidgets__Core__DockWidget__raise(void *thisObj);
// KDDockWidgets::Core::DockWidget::removedFromSideBar()
void c_KDDockWidgets__Core__DockWidget__removedFromSideBar(void *thisObj);
// KDDockWidgets::Core::DockWidget::setAffinityName(const QString & name)
void c_KDDockWidgets__Core__DockWidget__setAffinityName_QString(void *thisObj, const char *name_);
// KDDockWidgets::Core::DockWidget::setAsCurrentTab()
void c_KDDockWidgets__Core__DockWidget__setAsCurrentTab(void *thisObj);
// KDDockWidgets::Core::DockWidget::setFloating(bool floats)
bool c_KDDockWidgets__Core__DockWidget__setFloating_bool(void *thisObj, bool floats);
// KDDockWidgets::Core::DockWidget::setFloatingGeometry(QRect geo)
void c_KDDockWidgets__Core__DockWidget__setFloatingGeometry_QRect(void *thisObj, void *geo_);
// KDDockWidgets::Core::DockWidget::setMDIPosition(QPoint pos)
void c_KDDockWidgets__Core__DockWidget__setMDIPosition_QPoint(void *thisObj, void *pos_);
// KDDockWidgets::Core::DockWidget::setMDISize(QSize size)
void c_KDDockWidgets__Core__DockWidget__setMDISize_QSize(void *thisObj, void *size_);
// KDDockWidgets::Core::DockWidget::setMDIZ(int z)
void c_KDDockWidgets__Core__DockWidget__setMDIZ_int(void *thisObj, int z);
// KDDockWidgets::Core::DockWidget::setOptions(QFlags<KDDockWidgets::DockWidgetOption> arg__1)
void c_KDDockWidgets__Core__DockWidget__setOptions_DockWidgetOptions(void *thisObj, int arg__1_);
// KDDockWidgets::Core::DockWidget::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__DockWidget__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::DockWidget::setTitle(const QString & title)
void c_KDDockWidgets__Core__DockWidget__setTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::Core::DockWidget::setUserType(int userType)
void c_KDDockWidgets__Core__DockWidget__setUserType_int(void *thisObj, int userType);
// KDDockWidgets::Core::DockWidget::show()
void c_KDDockWidgets__Core__DockWidget__show(void *thisObj);
// KDDockWidgets::Core::DockWidget::skipsRestore() const
bool c_KDDockWidgets__Core__DockWidget__skipsRestore(void *thisObj);
// KDDockWidgets::Core::DockWidget::tabIndex() const
int c_KDDockWidgets__Core__DockWidget__tabIndex(void *thisObj);
// KDDockWidgets::Core::DockWidget::title() const
void *c_KDDockWidgets__Core__DockWidget__title(void *thisObj);
// KDDockWidgets::Core::DockWidget::titleBar() const
void *c_KDDockWidgets__Core__DockWidget__titleBar(void *thisObj);
// KDDockWidgets::Core::DockWidget::titleChanged(const QString & title)
void c_KDDockWidgets__Core__DockWidget__titleChanged_QString(void *thisObj, const char *title_);
// KDDockWidgets::Core::DockWidget::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__DockWidget__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Core::DockWidget::uniqueName() const
void *c_KDDockWidgets__Core__DockWidget__uniqueName(void *thisObj);
// KDDockWidgets::Core::DockWidget::userType() const
int c_KDDockWidgets__Core__DockWidget__userType(void *thisObj);
// KDDockWidgets::Core::DockWidget::windowActiveAboutToChange(bool activated)
void c_KDDockWidgets__Core__DockWidget__windowActiveAboutToChange_bool(void *thisObj, bool activated);
void c_KDDockWidgets__Core__DockWidget__destructor(void *thisObj);
void c_KDDockWidgets__Core__DockWidget__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__DockWidget_Finalizer(void *cppObj); // KDDockWidgets::Core::ClassicIndicatorWindowViewInterface::ClassicIndicatorWindowViewInterface()
void *c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__constructor();
// KDDockWidgets::Core::ClassicIndicatorWindowViewInterface::hover(QPoint arg__1)
int c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__hover_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::ClassicIndicatorWindowViewInterface::isWindow() const
bool c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__isWindow(void *thisObj);
// KDDockWidgets::Core::ClassicIndicatorWindowViewInterface::posForIndicator(KDDockWidgets::DropLocation arg__1) const
void *c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__posForIndicator_DropLocation(void *thisObj, int arg__1);
// KDDockWidgets::Core::ClassicIndicatorWindowViewInterface::raise()
void c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__raise(void *thisObj);
// KDDockWidgets::Core::ClassicIndicatorWindowViewInterface::resize(QSize arg__1)
void c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__resize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::ClassicIndicatorWindowViewInterface::setGeometry(QRect arg__1)
void c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__setGeometry_QRect(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::ClassicIndicatorWindowViewInterface::setObjectName(const QString & arg__1)
void c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__setObjectName_QString(void *thisObj, const char *arg__1_);
// KDDockWidgets::Core::ClassicIndicatorWindowViewInterface::setVisible(bool arg__1)
void c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__setVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::ClassicIndicatorWindowViewInterface::updatePositions()
void c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__updatePositions(void *thisObj);
void c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__destructor(void *thisObj);
void c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface_Finalizer(void *cppObj); // KDDockWidgets::flutter::IndicatorWindow::IndicatorWindow(KDDockWidgets::Core::ClassicDropIndicatorOverlay * arg__1, KDDockWidgets::Core::View * parent)
void *c_KDDockWidgets__flutter__IndicatorWindow__constructor_ClassicDropIndicatorOverlay_View(void *arg__1_, void *parent_);
// KDDockWidgets::flutter::IndicatorWindow::activateWindow()
void c_KDDockWidgets__flutter__IndicatorWindow__activateWindow(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::close()
bool c_KDDockWidgets__flutter__IndicatorWindow__close(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::createPlatformWindow()
void c_KDDockWidgets__flutter__IndicatorWindow__createPlatformWindow(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::flags() const
int c_KDDockWidgets__flutter__IndicatorWindow__flags(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::geometry() const
void *c_KDDockWidgets__flutter__IndicatorWindow__geometry(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::grabMouse()
void c_KDDockWidgets__flutter__IndicatorWindow__grabMouse(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::hasFocus() const
bool c_KDDockWidgets__flutter__IndicatorWindow__hasFocus(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::hide()
void c_KDDockWidgets__flutter__IndicatorWindow__hide(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::hover(QPoint globalPos)
int c_KDDockWidgets__flutter__IndicatorWindow__hover_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::flutter::IndicatorWindow::hover_flutter(QPoint globalPos)
int c_KDDockWidgets__flutter__IndicatorWindow__hover_flutter_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::flutter::IndicatorWindow::hoveredGroup() const
void *c_KDDockWidgets__flutter__IndicatorWindow__hoveredGroup(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::init()
void c_KDDockWidgets__flutter__IndicatorWindow__init(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::isActiveWindow() const
bool c_KDDockWidgets__flutter__IndicatorWindow__isActiveWindow(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::isExplicitlyHidden() const
bool c_KDDockWidgets__flutter__IndicatorWindow__isExplicitlyHidden(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::isMaximized() const
bool c_KDDockWidgets__flutter__IndicatorWindow__isMaximized(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::isMinimized() const
bool c_KDDockWidgets__flutter__IndicatorWindow__isMinimized(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::isMounted() const
bool c_KDDockWidgets__flutter__IndicatorWindow__isMounted(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::isNull() const
bool c_KDDockWidgets__flutter__IndicatorWindow__isNull(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::isRootView() const
bool c_KDDockWidgets__flutter__IndicatorWindow__isRootView(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::isVisible() const
bool c_KDDockWidgets__flutter__IndicatorWindow__isVisible(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::isWindow() const
bool c_KDDockWidgets__flutter__IndicatorWindow__isWindow(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__flutter__IndicatorWindow__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::flutter::IndicatorWindow::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
void *c_KDDockWidgets__flutter__IndicatorWindow__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_);
// KDDockWidgets::flutter::IndicatorWindow::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__flutter__IndicatorWindow__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::flutter::IndicatorWindow::maxSizeHint() const
void *c_KDDockWidgets__flutter__IndicatorWindow__maxSizeHint(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::minSize() const
void *c_KDDockWidgets__flutter__IndicatorWindow__minSize(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::move(int x, int y)
void c_KDDockWidgets__flutter__IndicatorWindow__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::flutter::IndicatorWindow::normalGeometry() const
void *c_KDDockWidgets__flutter__IndicatorWindow__normalGeometry(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__IndicatorWindow__onChildAdded_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::IndicatorWindow::onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__IndicatorWindow__onChildRemoved_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::IndicatorWindow::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__IndicatorWindow__onChildVisibilityChanged_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::IndicatorWindow::onGeometryChanged()
void c_KDDockWidgets__flutter__IndicatorWindow__onGeometryChanged(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::onRebuildRequested()
void c_KDDockWidgets__flutter__IndicatorWindow__onRebuildRequested(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::onResize(int h, int w)
bool c_KDDockWidgets__flutter__IndicatorWindow__onResize_int_int(void *thisObj, int h, int w);
// KDDockWidgets::flutter::IndicatorWindow::posForIndicator(KDDockWidgets::DropLocation arg__1) const
void *c_KDDockWidgets__flutter__IndicatorWindow__posForIndicator_DropLocation(void *thisObj, int arg__1);
// KDDockWidgets::flutter::IndicatorWindow::posForIndicator_flutter(KDDockWidgets::DropLocation arg__1) const
void *c_KDDockWidgets__flutter__IndicatorWindow__posForIndicator_flutter_DropLocation(void *thisObj, int arg__1);
// KDDockWidgets::flutter::IndicatorWindow::raise()
void c_KDDockWidgets__flutter__IndicatorWindow__raise(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::raiseAndActivate()
void c_KDDockWidgets__flutter__IndicatorWindow__raiseAndActivate(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::raiseChild(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__IndicatorWindow__raiseChild_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::IndicatorWindow::raiseWindow(KDDockWidgets::Core::View * rootView)
void c_KDDockWidgets__flutter__IndicatorWindow__raiseWindow_View(void *thisObj, void *rootView_);
// KDDockWidgets::flutter::IndicatorWindow::releaseKeyboard()
void c_KDDockWidgets__flutter__IndicatorWindow__releaseKeyboard(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::releaseMouse()
void c_KDDockWidgets__flutter__IndicatorWindow__releaseMouse(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::resize(QSize arg__1)
void c_KDDockWidgets__flutter__IndicatorWindow__resize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::IndicatorWindow::rubberBand() const
void *c_KDDockWidgets__flutter__IndicatorWindow__rubberBand(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__IndicatorWindow__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::flutter::IndicatorWindow::setFixedHeight(int h)
void c_KDDockWidgets__flutter__IndicatorWindow__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::IndicatorWindow::setFixedWidth(int w)
void c_KDDockWidgets__flutter__IndicatorWindow__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::IndicatorWindow::setGeometry(QRect arg__1)
void c_KDDockWidgets__flutter__IndicatorWindow__setGeometry_QRect(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::IndicatorWindow::setHeight(int h)
void c_KDDockWidgets__flutter__IndicatorWindow__setHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::IndicatorWindow::setMaximumSize(QSize sz)
void c_KDDockWidgets__flutter__IndicatorWindow__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::IndicatorWindow::setMinimumSize(QSize sz)
void c_KDDockWidgets__flutter__IndicatorWindow__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::IndicatorWindow::setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__IndicatorWindow__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::flutter::IndicatorWindow::setObjectName(const QString & arg__1)
void c_KDDockWidgets__flutter__IndicatorWindow__setObjectName_QString(void *thisObj, const char *arg__1_);
// KDDockWidgets::flutter::IndicatorWindow::setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__IndicatorWindow__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::IndicatorWindow::setSize(int w, int h)
void c_KDDockWidgets__flutter__IndicatorWindow__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::IndicatorWindow::setViewName(const QString & name)
void c_KDDockWidgets__flutter__IndicatorWindow__setViewName_QString(void *thisObj, const char *name_);
// KDDockWidgets::flutter::IndicatorWindow::setVisible(bool arg__1)
void c_KDDockWidgets__flutter__IndicatorWindow__setVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::flutter::IndicatorWindow::setWidth(int w)
void c_KDDockWidgets__flutter__IndicatorWindow__setWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::IndicatorWindow::setWindowOpacity(double v)
void c_KDDockWidgets__flutter__IndicatorWindow__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::flutter::IndicatorWindow::setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__IndicatorWindow__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::flutter::IndicatorWindow::setZOrder(int z)
void c_KDDockWidgets__flutter__IndicatorWindow__setZOrder_int(void *thisObj, int z);
// KDDockWidgets::flutter::IndicatorWindow::show()
void c_KDDockWidgets__flutter__IndicatorWindow__show(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::showMaximized()
void c_KDDockWidgets__flutter__IndicatorWindow__showMaximized(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::showMinimized()
void c_KDDockWidgets__flutter__IndicatorWindow__showMinimized(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::showNormal()
void c_KDDockWidgets__flutter__IndicatorWindow__showNormal(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::update()
void c_KDDockWidgets__flutter__IndicatorWindow__update(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::updatePositions()
void c_KDDockWidgets__flutter__IndicatorWindow__updatePositions(void *thisObj);
// KDDockWidgets::flutter::IndicatorWindow::updatePositions_flutter(int overlayWidth, int overlayHeight, KDDockWidgets::Core::Group * hoveredGroup, int visibleLocations)
bool c_KDDockWidgets__flutter__IndicatorWindow__updatePositions_flutter_int_int_Group_int(void *thisObj, int overlayWidth, int overlayHeight, void *hoveredGroup_, int visibleLocations);
// KDDockWidgets::flutter::IndicatorWindow::viewName() const
void *c_KDDockWidgets__flutter__IndicatorWindow__viewName(void *thisObj);
void c_KDDockWidgets__flutter__IndicatorWindow__destructor(void *thisObj);
void c_KDDockWidgets__flutter__IndicatorWindow__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__flutter__IndicatorWindow_Finalizer(void *cppObj); // KDDockWidgets::Core::ClassicDropIndicatorOverlay::ClassicDropIndicatorOverlay(KDDockWidgets::Core::DropArea * dropArea)
void *c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__constructor_DropArea(void *dropArea_);
// KDDockWidgets::Core::ClassicDropIndicatorOverlay::dropIndicatorVisible(KDDockWidgets::DropLocation arg__1) const
bool c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__dropIndicatorVisible_DropLocation(void *thisObj, int arg__1);
// KDDockWidgets::Core::ClassicDropIndicatorOverlay::hover_impl(QPoint globalPos)
int c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__hover_impl_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::Core::ClassicDropIndicatorOverlay::indicatorWindow() const
void *c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__indicatorWindow(void *thisObj);
// KDDockWidgets::Core::ClassicDropIndicatorOverlay::indicatorsVisibleChanged()
void c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__indicatorsVisibleChanged(void *thisObj);
// KDDockWidgets::Core::ClassicDropIndicatorOverlay::onHoveredGroupChanged(KDDockWidgets::Core::Group * arg__1)
void c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__onHoveredGroupChanged_Group(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::ClassicDropIndicatorOverlay::onResize(QSize newSize)
bool c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__onResize_QSize(void *thisObj, void *newSize_);
// KDDockWidgets::Core::ClassicDropIndicatorOverlay::posForIndicator(KDDockWidgets::DropLocation arg__1) const
void *c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__posForIndicator_DropLocation(void *thisObj, int arg__1);
// KDDockWidgets::Core::ClassicDropIndicatorOverlay::rubberBand() const
void *c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__rubberBand(void *thisObj);
// KDDockWidgets::Core::ClassicDropIndicatorOverlay::setCurrentDropLocation(KDDockWidgets::DropLocation arg__1)
void c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__setCurrentDropLocation_DropLocation(void *thisObj, int arg__1);
// KDDockWidgets::Core::ClassicDropIndicatorOverlay::setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::ClassicDropIndicatorOverlay::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Core__ClassicDropIndicatorOverlay__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Core::ClassicDropIndicatorOverlay::updateVisibility()
void c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__updateVisibility(void *thisObj);
void c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__destructor(void *thisObj);
void c_KDDockWidgets__Core__ClassicDropIndicatorOverlay__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Core__ClassicDropIndicatorOverlay_Finalizer(void *cppObj); // KDDockWidgets::Config::absoluteWidgetMaxSize() const
void *c_KDDockWidgets__Config__absoluteWidgetMaxSize(void *thisObj);
// KDDockWidgets::Config::absoluteWidgetMinSize() const
void *c_KDDockWidgets__Config__absoluteWidgetMinSize(void *thisObj);
// KDDockWidgets::Config::draggedWindowOpacity() const
qreal c_KDDockWidgets__Config__draggedWindowOpacity(void *thisObj);
// KDDockWidgets::Config::dropIndicatorsInhibited() const
bool c_KDDockWidgets__Config__dropIndicatorsInhibited(void *thisObj);
// KDDockWidgets::Config::mdiPopupThreshold() const
int c_KDDockWidgets__Config__mdiPopupThreshold(void *thisObj);
// KDDockWidgets::Config::printDebug()
void c_KDDockWidgets__Config__printDebug(void *thisObj);
// KDDockWidgets::Config::self()
void *c_static_KDDockWidgets__Config__self();
// KDDockWidgets::Config::separatorThickness() const
int c_KDDockWidgets__Config__separatorThickness(void *thisObj);
// KDDockWidgets::Config::setAbsoluteWidgetMaxSize(QSize size)
void c_KDDockWidgets__Config__setAbsoluteWidgetMaxSize_QSize(void *thisObj, void *size_);
// KDDockWidgets::Config::setAbsoluteWidgetMinSize(QSize size)
void c_KDDockWidgets__Config__setAbsoluteWidgetMinSize_QSize(void *thisObj, void *size_);
// KDDockWidgets::Config::setDraggedWindowOpacity(qreal opacity)
void c_KDDockWidgets__Config__setDraggedWindowOpacity_qreal(void *thisObj, qreal opacity);
// KDDockWidgets::Config::setDropIndicatorsInhibited(bool inhibit) const
void c_KDDockWidgets__Config__setDropIndicatorsInhibited_bool(void *thisObj, bool inhibit);
// KDDockWidgets::Config::setMDIPopupThreshold(int arg__1)
void c_KDDockWidgets__Config__setMDIPopupThreshold_int(void *thisObj, int arg__1);
// KDDockWidgets::Config::setSeparatorThickness(int value)
void c_KDDockWidgets__Config__setSeparatorThickness_int(void *thisObj, int value);
// KDDockWidgets::Config::setStartDragDistance(int arg__1)
void c_KDDockWidgets__Config__setStartDragDistance_int(void *thisObj, int arg__1);
// KDDockWidgets::Config::setTransparencyOnlyOverDropIndicator(bool only)
void c_KDDockWidgets__Config__setTransparencyOnlyOverDropIndicator_bool(void *thisObj, bool only);
// KDDockWidgets::Config::setViewFactory(KDDockWidgets::Core::ViewFactory * arg__1)
void c_KDDockWidgets__Config__setViewFactory_ViewFactory(void *thisObj, void *arg__1_);
// KDDockWidgets::Config::startDragDistance() const
int c_KDDockWidgets__Config__startDragDistance(void *thisObj);
// KDDockWidgets::Config::transparencyOnlyOverDropIndicator() const
bool c_KDDockWidgets__Config__transparencyOnlyOverDropIndicator(void *thisObj);
// KDDockWidgets::Config::viewFactory() const
void *c_KDDockWidgets__Config__viewFactory(void *thisObj);
void c_KDDockWidgets__Config__destructor(void *thisObj);
void c_KDDockWidgets__Config_Finalizer(void *cppObj);
