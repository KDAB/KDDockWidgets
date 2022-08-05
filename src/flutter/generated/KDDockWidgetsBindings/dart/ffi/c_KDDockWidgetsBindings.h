/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include <stdbool.h>
#include <QtCore/qglobal.h>

void c_Qt_Finalizer(void *, void *cppObj, void *); // QString::QString()
void *c_QString__constructor();
// QString::append(const QString & s)
void *c_QString__append_QString(void *thisObj, const char *s_);
// QString::arg(const QString & a, int fieldWidth) const
void *c_QString__arg_QString_int(void *thisObj, const char *a_, int fieldWidth);
// QString::arg(const QString & a1, const QString & a2) const
void *c_QString__arg_QString_QString(void *thisObj, const char *a1_, const char *a2_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3) const
void *c_QString__arg_QString_QString_QString(void *thisObj, const char *a1_, const char *a2_,
                                             const char *a3_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4)
// const
void *c_QString__arg_QString_QString_QString_QString(void *thisObj, const char *a1_,
                                                     const char *a2_, const char *a3_,
                                                     const char *a4_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4,
// const QString & a5) const
void *c_QString__arg_QString_QString_QString_QString_QString(void *thisObj, const char *a1_,
                                                             const char *a2_, const char *a3_,
                                                             const char *a4_, const char *a5_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4,
// const QString & a5, const QString & a6) const
void *c_QString__arg_QString_QString_QString_QString_QString_QString(
    void *thisObj, const char *a1_, const char *a2_, const char *a3_, const char *a4_,
    const char *a5_, const char *a6_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4,
// const QString & a5, const QString & a6, const QString & a7) const
void *c_QString__arg_QString_QString_QString_QString_QString_QString_QString(
    void *thisObj, const char *a1_, const char *a2_, const char *a3_, const char *a4_,
    const char *a5_, const char *a6_, const char *a7_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4,
// const QString & a5, const QString & a6, const QString & a7, const QString & a8) const
void *c_QString__arg_QString_QString_QString_QString_QString_QString_QString_QString(
    void *thisObj, const char *a1_, const char *a2_, const char *a3_, const char *a4_,
    const char *a5_, const char *a6_, const char *a7_, const char *a8_);
// QString::arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4,
// const QString & a5, const QString & a6, const QString & a7, const QString & a8, const QString &
// a9) const
void *c_QString__arg_QString_QString_QString_QString_QString_QString_QString_QString_QString(
    void *thisObj, const char *a1_, const char *a2_, const char *a3_, const char *a4_,
    const char *a5_, const char *a6_, const char *a7_, const char *a8_, const char *a9_);
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
void c_QString_Finalizer(void *, void *cppObj, void *); // QSize::QSize()
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
void c_QSize_Finalizer(void *, void *cppObj, void *); // QRect::QRect()
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
void c_QRect_Finalizer(void *, void *cppObj, void *); // QPoint::QPoint()
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
void c_QPoint_Finalizer(void *, void *cppObj, void *); // QObject::QObject(QObject * parent)
void *c_QObject__constructor_QObject(void *parent_);
// QObject::blockSignals(bool b)
bool c_QObject__blockSignals_bool(void *thisObj, bool b);
// QObject::children() const
void *c_QObject__children(void *thisObj);
// QObject::customEvent(QEvent * event)
void c_QObject__customEvent_QEvent(void *thisObj, void *event_);
// QObject::deleteLater()
void c_QObject__deleteLater(void *thisObj);
// QObject::destroyed(QObject * arg__1)
void c_QObject__destroyed_QObject(void *thisObj, void *arg__1_);
void c_QObject__onDestroyed_QObject(void *thisObj, void *contextQObject,
                                    void *callback); // QObject::disconnect(const QObject *
                                                     // receiver, const char * member) const
bool c_QObject__disconnect_QObject_char(void *thisObj, void *receiver_, const char *member);
// QObject::disconnect(const QObject * sender, const char * signal, const QObject * receiver, const
// char * member)
bool c_static_QObject__disconnect_QObject_char_QObject_char(void *sender_, const char *signal,
                                                            void *receiver_, const char *member);
// QObject::disconnect(const char * signal, const QObject * receiver, const char * member) const
bool c_QObject__disconnect_char_QObject_char(void *thisObj, const char *signal, void *receiver_,
                                             const char *member);
// QObject::dumpObjectInfo()
void c_QObject__dumpObjectInfo(void *thisObj);
// QObject::dumpObjectTree()
void c_QObject__dumpObjectTree(void *thisObj);
// QObject::dynamicPropertyNames() const
void *c_QObject__dynamicPropertyNames(void *thisObj);
// QObject::event(QEvent * event)
bool c_QObject__event_QEvent(void *thisObj, void *event_);
// QObject::eventFilter(QObject * watched, QEvent * event)
bool c_QObject__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_);
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
void c_QObject_Finalizer(void *, void *cppObj, void *); // QList::QList<T>()
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
void c_QList_T_QObject_T__Finalizer(void *, void *cppObj, void *); // QList::QList<T>()
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
void c_QList_T_QByteArray_T__Finalizer(void *, void *cppObj, void *); // QList::QList<T>()
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
void c_QList_T_Group_T__Finalizer(void *, void *cppObj,
                                  void *); // QEvent::QEvent(QEvent::Type type)
void *c_QEvent__constructor_Type(int type);
// QEvent::accept()
void c_QEvent__accept(void *thisObj);
// QEvent::ignore()
void c_QEvent__ignore(void *thisObj);
// QEvent::isAccepted() const
bool c_QEvent__isAccepted(void *thisObj);
// QEvent::registerEventType(int hint)
int c_static_QEvent__registerEventType_int(int hint);
// QEvent::setAccepted(bool accepted)
void c_QEvent__setAccepted_bool(void *thisObj, bool accepted);
// QEvent::spontaneous() const
bool c_QEvent__spontaneous(void *thisObj);
// QEvent::type() const
int c_QEvent__type(void *thisObj);
void c_QEvent__destructor(void *thisObj);
void c_QEvent__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_QEvent_Finalizer(void *, void *cppObj, void *); // QByteArray::QByteArray()
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
void *c_QByteArray__replace_char_int_char_int(void *thisObj, const char *before, int bsize,
                                              const char *after, int asize);
// QByteArray::replace(int index, int len, const QByteArray & s)
void *c_QByteArray__replace_int_int_QByteArray(void *thisObj, int index, int len, void *s_);
// QByteArray::replace(int index, int len, const char * s)
void *c_QByteArray__replace_int_int_char(void *thisObj, int index, int len, const char *s);
// QByteArray::replace(int index, int len, const char * s, int alen)
void *c_QByteArray__replace_int_int_char_int(void *thisObj, int index, int len, const char *s,
                                             int alen);
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
void c_QByteArray_Finalizer(void *, void *cppObj, void *);
void c_Layouting_Finalizer(void *, void *cppObj,
                           void *); // Layouting::Item::Item(KDDockWidgets::View * hostWidget)
void *c_Layouting__Item__constructor_View(void *hostWidget_);
// Layouting::Item::asGroupController() const
void *c_Layouting__Item__asGroupController(void *thisObj);
// Layouting::Item::checkSanity()
bool c_Layouting__Item__checkSanity(void *thisObj);
// Layouting::Item::customEvent(QEvent * event)
void c_Layouting__Item__customEvent_QEvent(void *thisObj, void *event_);
// Layouting::Item::dumpLayout(int level)
void c_Layouting__Item__dumpLayout_int(void *thisObj, int level);
// Layouting::Item::event(QEvent * event)
bool c_Layouting__Item__event_QEvent(void *thisObj, void *event_);
// Layouting::Item::eventFilter(QObject * watched, QEvent * event)
bool c_Layouting__Item__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_);
// Layouting::Item::geometry() const
void *c_Layouting__Item__geometry(void *thisObj);
// Layouting::Item::guestView() const
void *c_Layouting__Item__guestView(void *thisObj);
// Layouting::Item::height() const
int c_Layouting__Item__height(void *thisObj);
// Layouting::Item::hostView() const
void *c_Layouting__Item__hostView(void *thisObj);
// Layouting::Item::isBeingInserted() const
bool c_Layouting__Item__isBeingInserted(void *thisObj);
// Layouting::Item::isContainer() const
bool c_Layouting__Item__isContainer(void *thisObj);
// Layouting::Item::isMDI() const
bool c_Layouting__Item__isMDI(void *thisObj);
// Layouting::Item::isPlaceholder() const
bool c_Layouting__Item__isPlaceholder(void *thisObj);
// Layouting::Item::isRoot() const
bool c_Layouting__Item__isRoot(void *thisObj);
// Layouting::Item::isVisible(bool excludeBeingInserted) const
bool c_Layouting__Item__isVisible_bool(void *thisObj, bool excludeBeingInserted);
// Layouting::Item::mapFromParent(QPoint arg__1) const
void *c_Layouting__Item__mapFromParent_QPoint(void *thisObj, void *arg__1_);
// Layouting::Item::mapFromRoot(QPoint arg__1) const
void *c_Layouting__Item__mapFromRoot_QPoint(void *thisObj, void *arg__1_);
// Layouting::Item::mapFromRoot(QRect arg__1) const
void *c_Layouting__Item__mapFromRoot_QRect(void *thisObj, void *arg__1_);
// Layouting::Item::mapToRoot(QPoint arg__1) const
void *c_Layouting__Item__mapToRoot_QPoint(void *thisObj, void *arg__1_);
// Layouting::Item::mapToRoot(QRect arg__1) const
void *c_Layouting__Item__mapToRoot_QRect(void *thisObj, void *arg__1_);
// Layouting::Item::maxSizeHint() const
void *c_Layouting__Item__maxSizeHint(void *thisObj);
// Layouting::Item::minSize() const
void *c_Layouting__Item__minSize(void *thisObj);
// Layouting::Item::missingSize() const
void *c_Layouting__Item__missingSize(void *thisObj);
// Layouting::Item::pos() const
void *c_Layouting__Item__pos(void *thisObj);
// Layouting::Item::rect() const
void *c_Layouting__Item__rect(void *thisObj);
// Layouting::Item::ref()
void c_Layouting__Item__ref(void *thisObj);
// Layouting::Item::refCount() const
int c_Layouting__Item__refCount(void *thisObj);
// Layouting::Item::restore(KDDockWidgets::View * guestView)
void c_Layouting__Item__restore_View(void *thisObj, void *guestView_);
// Layouting::Item::setBeingInserted(bool arg__1)
void c_Layouting__Item__setBeingInserted_bool(void *thisObj, bool arg__1);
// Layouting::Item::setGeometry(QRect rect)
void c_Layouting__Item__setGeometry_QRect(void *thisObj, void *rect_);
// Layouting::Item::setGeometry_recursive(QRect rect)
void c_Layouting__Item__setGeometry_recursive_QRect(void *thisObj, void *rect_);
// Layouting::Item::setGuestView(KDDockWidgets::View * arg__1)
void c_Layouting__Item__setGuestView_View(void *thisObj, void *arg__1_);
// Layouting::Item::setHostView(KDDockWidgets::View * arg__1)
void c_Layouting__Item__setHostView_View(void *thisObj, void *arg__1_);
// Layouting::Item::setIsVisible(bool arg__1)
void c_Layouting__Item__setIsVisible_bool(void *thisObj, bool arg__1);
// Layouting::Item::setMaxSizeHint(QSize arg__1)
void c_Layouting__Item__setMaxSizeHint_QSize(void *thisObj, void *arg__1_);
// Layouting::Item::setMinSize(QSize arg__1)
void c_Layouting__Item__setMinSize_QSize(void *thisObj, void *arg__1_);
// Layouting::Item::setPos(QPoint arg__1)
void c_Layouting__Item__setPos_QPoint(void *thisObj, void *arg__1_);
// Layouting::Item::setSize(QSize arg__1)
void c_Layouting__Item__setSize_QSize(void *thisObj, void *arg__1_);
// Layouting::Item::size() const
void *c_Layouting__Item__size(void *thisObj);
// Layouting::Item::tr(const char * s, const char * c, int n)
void *c_static_Layouting__Item__tr_char_char_int(const char *s, const char *c, int n);
// Layouting::Item::unref()
void c_Layouting__Item__unref(void *thisObj);
// Layouting::Item::updateWidgetGeometries()
void c_Layouting__Item__updateWidgetGeometries(void *thisObj);
// Layouting::Item::visibleCount_recursive() const
int c_Layouting__Item__visibleCount_recursive(void *thisObj);
// Layouting::Item::width() const
int c_Layouting__Item__width(void *thisObj);
// Layouting::Item::x() const
int c_Layouting__Item__x(void *thisObj);
// Layouting::Item::y() const
int c_Layouting__Item__y(void *thisObj);
void c_Layouting__Item__destructor(void *thisObj);
int c_static_Layouting__Item___get_separatorThickness();
bool c_static_Layouting__Item___get_s_silenceSanityChecks();
void c_static_Layouting__Item___set_separatorThickness_int(int separatorThickness_);
void c_static_Layouting__Item___set_s_silenceSanityChecks_bool(bool s_silenceSanityChecks_);
void c_Layouting__Item__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_Layouting__Item_Finalizer(void *, void *cppObj,
                                 void *); // KDDockWidgets::initFrontend(KDDockWidgets::FrontendType
                                          // arg__1)
void c_static_KDDockWidgets__initFrontend_FrontendType(int arg__1);
// KDDockWidgets::locationStr(KDDockWidgets::Location loc)
void *c_static_KDDockWidgets__locationStr_Location(int loc);
void c_KDDockWidgets_Finalizer(
    void *, void *cppObj, void *); // KDDockWidgets::Views::asView_flutter(KDDockWidgets::Controller
                                   // * controller)
void *c_static_KDDockWidgets__Views__asView_flutter_Controller(void *controller_);
// KDDockWidgets::Views::asView_flutter(KDDockWidgets::View * view)
void *c_static_KDDockWidgets__Views__asView_flutter_View(void *view_);
void c_KDDockWidgets__Views_Finalizer(
    void *, void *cppObj,
    void
        *); // KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::ClassicIndicatorWindowViewInterface()
void *c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__constructor();
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::hover(QPoint arg__1)
int c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__hover_QPoint(void *thisObj,
                                                                              void *arg__1_);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::isWindow() const
bool c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__isWindow(void *thisObj);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::posForIndicator(KDDockWidgets::DropLocation
// arg__1) const
void *c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__posForIndicator_DropLocation(
    void *thisObj, int arg__1);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::raise()
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__raise(void *thisObj);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::resize(QSize arg__1)
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__resize_QSize(void *thisObj,
                                                                               void *arg__1_);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::setGeometry(QRect arg__1)
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setGeometry_QRect(void *thisObj,
                                                                                    void *arg__1_);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::setObjectName(const QString & arg__1)
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setObjectName_QString(
    void *thisObj, const char *arg__1_);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::setVisible(bool arg__1)
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setVisible_bool(void *thisObj,
                                                                                  bool arg__1);
// KDDockWidgets::Views::ClassicIndicatorWindowViewInterface::updatePositions()
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__updatePositions(void *thisObj);
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__destructor(void *thisObj);
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__registerVirtualMethodCallback(
    void *ptr, void *callback, int methodId);
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface_Finalizer(
    void *, void *cppObj, void *); // KDDockWidgets::ViewFactory::ViewFactory()
void *c_KDDockWidgets__ViewFactory__constructor();
// KDDockWidgets::ViewFactory::createClassicIndicatorWindow(KDDockWidgets::Controllers::ClassicIndicators
// * arg__1) const
void *c_KDDockWidgets__ViewFactory__createClassicIndicatorWindow_ClassicIndicators(void *thisObj,
                                                                                   void *arg__1_);
// KDDockWidgets::ViewFactory::createDockWidget(const QString & uniqueName,
// QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption>
// layoutSaverOptions, Qt::WindowFlags windowFlags) const
void *
c_KDDockWidgets__ViewFactory__createDockWidget_QString_DockWidgetOptions_LayoutSaverOptions_WindowFlags(
    void *thisObj, const char *uniqueName_, int options_, int layoutSaverOptions_, int windowFlags);
// KDDockWidgets::ViewFactory::createDropArea(KDDockWidgets::Controllers::DropArea * arg__1,
// KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory__createDropArea_DropArea_View(void *thisObj, void *arg__1_,
                                                                 void *parent_);
// KDDockWidgets::ViewFactory::createGroup(KDDockWidgets::Controllers::Group * arg__1,
// KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory__createGroup_Group_View(void *thisObj, void *arg__1_,
                                                           void *parent_);
// KDDockWidgets::ViewFactory::createRubberBand(KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory__createRubberBand_View(void *thisObj, void *parent_);
// KDDockWidgets::ViewFactory::createStack(KDDockWidgets::Controllers::Stack * stack,
// KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory__createStack_Stack_View(void *thisObj, void *stack_,
                                                           void *parent_);
// KDDockWidgets::ViewFactory::createTabBar(KDDockWidgets::Controllers::TabBar * tabBar,
// KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory__createTabBar_TabBar_View(void *thisObj, void *tabBar_,
                                                             void *parent_);
// KDDockWidgets::ViewFactory::createTitleBar(KDDockWidgets::Controllers::TitleBar * controller,
// KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory__createTitleBar_TitleBar_View(void *thisObj, void *controller_,
                                                                 void *parent_);
// KDDockWidgets::ViewFactory::customEvent(QEvent * event)
void c_KDDockWidgets__ViewFactory__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::ViewFactory::event(QEvent * event)
bool c_KDDockWidgets__ViewFactory__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::ViewFactory::eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__ViewFactory__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                              void *event_);
// KDDockWidgets::ViewFactory::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__ViewFactory__tr_char_char_int(const char *s, const char *c, int n);
void c_KDDockWidgets__ViewFactory__destructor(void *thisObj);
void c_KDDockWidgets__ViewFactory__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                 int methodId);
void c_KDDockWidgets__ViewFactory_Finalizer(
    void *, void *cppObj, void *); // KDDockWidgets::ViewFactory_flutter::ViewFactory_flutter()
void *c_KDDockWidgets__ViewFactory_flutter__constructor();
// KDDockWidgets::ViewFactory_flutter::createClassicIndicatorWindow(KDDockWidgets::Controllers::ClassicIndicators
// * arg__1) const
void *
c_KDDockWidgets__ViewFactory_flutter__createClassicIndicatorWindow_ClassicIndicators(void *thisObj,
                                                                                     void *arg__1_);
// KDDockWidgets::ViewFactory_flutter::createDockWidget(const QString & uniqueName,
// QFlags<KDDockWidgets::DockWidgetOption> arg__2, QFlags<KDDockWidgets::LayoutSaverOption> arg__3,
// Qt::WindowFlags arg__4) const
void *
c_KDDockWidgets__ViewFactory_flutter__createDockWidget_QString_DockWidgetOptions_LayoutSaverOptions_WindowFlags(
    void *thisObj, const char *uniqueName_, int arg__2_, int arg__3_, int arg__4);
// KDDockWidgets::ViewFactory_flutter::createDropArea(KDDockWidgets::Controllers::DropArea * arg__1,
// KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createDropArea_DropArea_View(void *thisObj,
                                                                         void *arg__1_,
                                                                         void *parent_);
// KDDockWidgets::ViewFactory_flutter::createGroup(KDDockWidgets::Controllers::Group * arg__1,
// KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createGroup_Group_View(void *thisObj, void *arg__1_,
                                                                   void *parent_);
// KDDockWidgets::ViewFactory_flutter::createRubberBand(KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createRubberBand_View(void *thisObj, void *parent_);
// KDDockWidgets::ViewFactory_flutter::createStack(KDDockWidgets::Controllers::Stack * arg__1,
// KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createStack_Stack_View(void *thisObj, void *arg__1_,
                                                                   void *parent_);
// KDDockWidgets::ViewFactory_flutter::createTabBar(KDDockWidgets::Controllers::TabBar * tabBar,
// KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createTabBar_TabBar_View(void *thisObj, void *tabBar_,
                                                                     void *parent_);
// KDDockWidgets::ViewFactory_flutter::createTitleBar(KDDockWidgets::Controllers::TitleBar * arg__1,
// KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createTitleBar_TitleBar_View(void *thisObj,
                                                                         void *arg__1_,
                                                                         void *parent_);
// KDDockWidgets::ViewFactory_flutter::customEvent(QEvent * event)
void c_KDDockWidgets__ViewFactory_flutter__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::ViewFactory_flutter::event(QEvent * event)
bool c_KDDockWidgets__ViewFactory_flutter__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::ViewFactory_flutter::eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__ViewFactory_flutter__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                      void *event_);
// KDDockWidgets::ViewFactory_flutter::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__ViewFactory_flutter__tr_char_char_int(const char *s, const char *c,
                                                                    int n);
void c_KDDockWidgets__ViewFactory_flutter__destructor(void *thisObj);
void c_KDDockWidgets__ViewFactory_flutter__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                         int methodId);
void c_KDDockWidgets__ViewFactory_flutter_Finalizer(void *, void *cppObj,
                                                    void *); // KDDockWidgets::Platform::Platform()
void *c_KDDockWidgets__Platform__constructor();
// KDDockWidgets::Platform::applicationName() const
void *c_KDDockWidgets__Platform__applicationName(void *thisObj);
// KDDockWidgets::Platform::createDefaultViewFactory()
void *c_KDDockWidgets__Platform__createDefaultViewFactory(void *thisObj);
// KDDockWidgets::Platform::createView(KDDockWidgets::Controller * arg__1, KDDockWidgets::View *
// parent) const
void *c_KDDockWidgets__Platform__createView_Controller_View(void *thisObj, void *arg__1_,
                                                            void *parent_);
// KDDockWidgets::Platform::dumpManagedBacktrace()
void c_KDDockWidgets__Platform__dumpManagedBacktrace(void *thisObj);
// KDDockWidgets::Platform::hasActivePopup() const
bool c_KDDockWidgets__Platform__hasActivePopup(void *thisObj);
// KDDockWidgets::Platform::inDisallowedDragView(QPoint globalPos) const
bool c_KDDockWidgets__Platform__inDisallowedDragView_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::Platform::indirection()
void c_static_KDDockWidgets__Platform__indirection();
// KDDockWidgets::Platform::installMessageHandler()
void c_KDDockWidgets__Platform__installMessageHandler(void *thisObj);
// KDDockWidgets::Platform::instance()
void *c_static_KDDockWidgets__Platform__instance();
// KDDockWidgets::Platform::isLeftMouseButtonPressed() const
bool c_KDDockWidgets__Platform__isLeftMouseButtonPressed(void *thisObj);
// KDDockWidgets::Platform::isProcessingAppQuitEvent() const
bool c_KDDockWidgets__Platform__isProcessingAppQuitEvent(void *thisObj);
// KDDockWidgets::Platform::isQtQuick() const
bool c_KDDockWidgets__Platform__isQtQuick(void *thisObj);
// KDDockWidgets::Platform::isQtWidgets() const
bool c_KDDockWidgets__Platform__isQtWidgets(void *thisObj);
// KDDockWidgets::Platform::name() const
const char *c_KDDockWidgets__Platform__name(void *thisObj);
// KDDockWidgets::Platform::organizationName() const
void *c_KDDockWidgets__Platform__organizationName(void *thisObj);
// KDDockWidgets::Platform::restoreMouseCursor()
void c_KDDockWidgets__Platform__restoreMouseCursor(void *thisObj);
// KDDockWidgets::Platform::screenNumberFor(KDDockWidgets::View * arg__1) const
int c_KDDockWidgets__Platform__screenNumberFor_View(void *thisObj, void *arg__1_);
// KDDockWidgets::Platform::screenSizeFor(KDDockWidgets::View * arg__1) const
void *c_KDDockWidgets__Platform__screenSizeFor_View(void *thisObj, void *arg__1_);
// KDDockWidgets::Platform::sendEvent(KDDockWidgets::View * arg__1, QEvent * arg__2) const
void c_KDDockWidgets__Platform__sendEvent_View_QEvent(void *thisObj, void *arg__1_, void *arg__2_);
// KDDockWidgets::Platform::setMouseCursor(Qt::CursorShape arg__1)
void c_KDDockWidgets__Platform__setMouseCursor_CursorShape(void *thisObj, int arg__1);
// KDDockWidgets::Platform::startDragDistance() const
int c_KDDockWidgets__Platform__startDragDistance(void *thisObj);
// KDDockWidgets::Platform::startDragDistance_impl() const
int c_KDDockWidgets__Platform__startDragDistance_impl(void *thisObj);
// KDDockWidgets::Platform::tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1,
// KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform__tests_createFocusableView_CreateViewOptions_View(void *thisObj,
                                                                                  void *arg__1_,
                                                                                  void *parent_);
// KDDockWidgets::Platform::tests_createNonClosableView(KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform__tests_createNonClosableView_View(void *thisObj, void *parent_);
// KDDockWidgets::Platform::tests_createView(KDDockWidgets::CreateViewOptions arg__1,
// KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform__tests_createView_CreateViewOptions_View(void *thisObj,
                                                                         void *arg__1_,
                                                                         void *parent_);
// KDDockWidgets::Platform::tests_deinitPlatform()
void c_static_KDDockWidgets__Platform__tests_deinitPlatform();
// KDDockWidgets::Platform::tests_deinitPlatform_impl()
void c_KDDockWidgets__Platform__tests_deinitPlatform_impl(void *thisObj);
// KDDockWidgets::Platform::tests_initPlatform_impl()
void c_KDDockWidgets__Platform__tests_initPlatform_impl(void *thisObj);
// KDDockWidgets::Platform::tests_wait(int ms)
void c_KDDockWidgets__Platform__tests_wait_int(void *thisObj, int ms);
// KDDockWidgets::Platform::tests_waitForDeleted(KDDockWidgets::View * arg__1, int timeout) const
bool c_KDDockWidgets__Platform__tests_waitForDeleted_View_int(void *thisObj, void *arg__1_,
                                                              int timeout);
// KDDockWidgets::Platform::tests_waitForDeleted(QObject * arg__1, int timeout) const
bool c_KDDockWidgets__Platform__tests_waitForDeleted_QObject_int(void *thisObj, void *arg__1_,
                                                                 int timeout);
// KDDockWidgets::Platform::tests_waitForEvent(KDDockWidgets::View * arg__1, QEvent::Type type, int
// timeout) const
bool c_KDDockWidgets__Platform__tests_waitForEvent_View_Type_int(void *thisObj, void *arg__1_,
                                                                 int type, int timeout);
// KDDockWidgets::Platform::tests_waitForEvent(QObject * w, QEvent::Type type, int timeout) const
bool c_KDDockWidgets__Platform__tests_waitForEvent_QObject_Type_int(void *thisObj, void *w_,
                                                                    int type, int timeout);
// KDDockWidgets::Platform::tests_waitForResize(KDDockWidgets::Controller * arg__1, int timeout)
// const
bool c_KDDockWidgets__Platform__tests_waitForResize_Controller_int(void *thisObj, void *arg__1_,
                                                                   int timeout);
// KDDockWidgets::Platform::tests_waitForResize(KDDockWidgets::View * arg__1, int timeout) const
bool c_KDDockWidgets__Platform__tests_waitForResize_View_int(void *thisObj, void *arg__1_,
                                                             int timeout);
// KDDockWidgets::Platform::ungrabMouse()
void c_KDDockWidgets__Platform__ungrabMouse(void *thisObj);
// KDDockWidgets::Platform::uninstallMessageHandler()
void c_KDDockWidgets__Platform__uninstallMessageHandler(void *thisObj);
// KDDockWidgets::Platform::usesFallbackMouseGrabber() const
bool c_KDDockWidgets__Platform__usesFallbackMouseGrabber(void *thisObj);
void c_KDDockWidgets__Platform__destructor(void *thisObj);
int c_KDDockWidgets__Platform___get_m_numWarningsEmitted(void *thisObj);
void c_KDDockWidgets__Platform___set_m_numWarningsEmitted_int(void *thisObj,
                                                              int m_numWarningsEmitted_);
void c_KDDockWidgets__Platform__registerVirtualMethodCallback(void *ptr, void *callback,
                                                              int methodId);
void c_KDDockWidgets__Platform_Finalizer(
    void *, void *cppObj, void *); // KDDockWidgets::Platform_flutter::Platform_flutter()
void *c_KDDockWidgets__Platform_flutter__constructor();
// KDDockWidgets::Platform_flutter::applicationName() const
void *c_KDDockWidgets__Platform_flutter__applicationName(void *thisObj);
// KDDockWidgets::Platform_flutter::createDefaultViewFactory()
void *c_KDDockWidgets__Platform_flutter__createDefaultViewFactory(void *thisObj);
// KDDockWidgets::Platform_flutter::createView(KDDockWidgets::Controller * controller,
// KDDockWidgets::View * parent) const
void *c_KDDockWidgets__Platform_flutter__createView_Controller_View(void *thisObj,
                                                                    void *controller_,
                                                                    void *parent_);
// KDDockWidgets::Platform_flutter::dumpManagedBacktrace()
void c_KDDockWidgets__Platform_flutter__dumpManagedBacktrace(void *thisObj);
// KDDockWidgets::Platform_flutter::hasActivePopup() const
bool c_KDDockWidgets__Platform_flutter__hasActivePopup(void *thisObj);
// KDDockWidgets::Platform_flutter::inDisallowedDragView(QPoint globalPos) const
bool c_KDDockWidgets__Platform_flutter__inDisallowedDragView_QPoint(void *thisObj,
                                                                    void *globalPos_);
// KDDockWidgets::Platform_flutter::init()
void c_KDDockWidgets__Platform_flutter__init(void *thisObj);
// KDDockWidgets::Platform_flutter::installMessageHandler()
void c_KDDockWidgets__Platform_flutter__installMessageHandler(void *thisObj);
// KDDockWidgets::Platform_flutter::isLeftMouseButtonPressed() const
bool c_KDDockWidgets__Platform_flutter__isLeftMouseButtonPressed(void *thisObj);
// KDDockWidgets::Platform_flutter::isProcessingAppQuitEvent() const
bool c_KDDockWidgets__Platform_flutter__isProcessingAppQuitEvent(void *thisObj);
// KDDockWidgets::Platform_flutter::name() const
const char *c_KDDockWidgets__Platform_flutter__name(void *thisObj);
// KDDockWidgets::Platform_flutter::organizationName() const
void *c_KDDockWidgets__Platform_flutter__organizationName(void *thisObj);
// KDDockWidgets::Platform_flutter::restoreMouseCursor()
void c_KDDockWidgets__Platform_flutter__restoreMouseCursor(void *thisObj);
// KDDockWidgets::Platform_flutter::screenNumberFor(KDDockWidgets::View * arg__1) const
int c_KDDockWidgets__Platform_flutter__screenNumberFor_View(void *thisObj, void *arg__1_);
// KDDockWidgets::Platform_flutter::screenSizeFor(KDDockWidgets::View * arg__1) const
void *c_KDDockWidgets__Platform_flutter__screenSizeFor_View(void *thisObj, void *arg__1_);
// KDDockWidgets::Platform_flutter::sendEvent(KDDockWidgets::View * arg__1, QEvent * arg__2) const
void c_KDDockWidgets__Platform_flutter__sendEvent_View_QEvent(void *thisObj, void *arg__1_,
                                                              void *arg__2_);
// KDDockWidgets::Platform_flutter::setMouseCursor(Qt::CursorShape arg__1)
void c_KDDockWidgets__Platform_flutter__setMouseCursor_CursorShape(void *thisObj, int arg__1);
// KDDockWidgets::Platform_flutter::startDragDistance_impl() const
int c_KDDockWidgets__Platform_flutter__startDragDistance_impl(void *thisObj);
// KDDockWidgets::Platform_flutter::tests_createFocusableView(KDDockWidgets::CreateViewOptions
// arg__1, KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform_flutter__tests_createFocusableView_CreateViewOptions_View(
    void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::Platform_flutter::tests_createNonClosableView(KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform_flutter__tests_createNonClosableView_View(void *thisObj,
                                                                          void *parent_);
// KDDockWidgets::Platform_flutter::tests_createView(KDDockWidgets::CreateViewOptions arg__1,
// KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform_flutter__tests_createView_CreateViewOptions_View(void *thisObj,
                                                                                 void *arg__1_,
                                                                                 void *parent_);
// KDDockWidgets::Platform_flutter::tests_deinitPlatform_impl()
void c_KDDockWidgets__Platform_flutter__tests_deinitPlatform_impl(void *thisObj);
// KDDockWidgets::Platform_flutter::tests_initPlatform_impl()
void c_KDDockWidgets__Platform_flutter__tests_initPlatform_impl(void *thisObj);
// KDDockWidgets::Platform_flutter::tests_wait(int ms)
void c_KDDockWidgets__Platform_flutter__tests_wait_int(void *thisObj, int ms);
// KDDockWidgets::Platform_flutter::ungrabMouse()
void c_KDDockWidgets__Platform_flutter__ungrabMouse(void *thisObj);
// KDDockWidgets::Platform_flutter::uninstallMessageHandler()
void c_KDDockWidgets__Platform_flutter__uninstallMessageHandler(void *thisObj);
// KDDockWidgets::Platform_flutter::usesFallbackMouseGrabber() const
bool c_KDDockWidgets__Platform_flutter__usesFallbackMouseGrabber(void *thisObj);
void c_KDDockWidgets__Platform_flutter__destructor(void *thisObj);
void c_KDDockWidgets__Platform_flutter__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                      int methodId);
void c_KDDockWidgets__Platform_flutter_Finalizer(
    void *, void *cppObj, void *); // KDDockWidgets::InitialOption::InitialOption()
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
void c_KDDockWidgets__InitialOption_Finalizer(
    void *, void *cppObj, void *); // KDDockWidgets::CreateViewOptions::CreateViewOptions()
void *c_KDDockWidgets__CreateViewOptions__constructor();
void c_KDDockWidgets__CreateViewOptions__destructor(void *thisObj);
bool c_KDDockWidgets__CreateViewOptions___get_isVisible(void *thisObj);
bool c_KDDockWidgets__CreateViewOptions___get_createWindow(void *thisObj);
void c_KDDockWidgets__CreateViewOptions___set_isVisible_bool(void *thisObj, bool isVisible_);
void c_KDDockWidgets__CreateViewOptions___set_createWindow_bool(void *thisObj, bool createWindow_);
void c_KDDockWidgets__CreateViewOptions_Finalizer(void *, void *cppObj, void *);
void c_KDDockWidgets__Controllers_Finalizer(
    void *, void *cppObj,
    void
        *); // KDDockWidgets::Controllers::ClassicIndicators::ClassicIndicators(KDDockWidgets::Controllers::DropArea
            // * dropArea)
void *c_KDDockWidgets__Controllers__ClassicIndicators__constructor_DropArea(void *dropArea_);
// KDDockWidgets::Controllers::ClassicIndicators::hover_impl(QPoint globalPos)
int c_KDDockWidgets__Controllers__ClassicIndicators__hover_impl_QPoint(void *thisObj,
                                                                       void *globalPos_);
// KDDockWidgets::Controllers::ClassicIndicators::indicatorsVisibleChanged()
void c_KDDockWidgets__Controllers__ClassicIndicators__indicatorsVisibleChanged(void *thisObj);
void c_KDDockWidgets__Controllers__ClassicIndicators__onIndicatorsVisibleChanged(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::ClassicIndicators::onResize(QSize newSize)
bool c_KDDockWidgets__Controllers__ClassicIndicators__onResize_QSize(void *thisObj, void *newSize_);
// KDDockWidgets::Controllers::ClassicIndicators::posForIndicator(KDDockWidgets::DropLocation
// arg__1) const
void *c_KDDockWidgets__Controllers__ClassicIndicators__posForIndicator_DropLocation(void *thisObj,
                                                                                    int arg__1);
// KDDockWidgets::Controllers::ClassicIndicators::setDropLocation(KDDockWidgets::DropLocation
// arg__1)
void c_KDDockWidgets__Controllers__ClassicIndicators__setDropLocation_DropLocation(void *thisObj,
                                                                                   int arg__1);
// KDDockWidgets::Controllers::ClassicIndicators::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__ClassicIndicators__tr_char_char_int(const char *s,
                                                                               const char *c,
                                                                               int n);
// KDDockWidgets::Controllers::ClassicIndicators::updateVisibility()
void c_KDDockWidgets__Controllers__ClassicIndicators__updateVisibility(void *thisObj);
void c_KDDockWidgets__Controllers__ClassicIndicators__destructor(void *thisObj);
void c_KDDockWidgets__Controllers__ClassicIndicators__registerVirtualMethodCallback(void *ptr,
                                                                                    void *callback,
                                                                                    int methodId);
void c_KDDockWidgets__Controllers__ClassicIndicators_Finalizer(
    void *, void *cppObj,
    void *); // KDDockWidgets::Controller::Controller(KDDockWidgets::Type
             // type, KDDockWidgets::View
             // * arg__2)
void *c_KDDockWidgets__Controller__constructor_Type_View(int type, void *arg__2_);
// KDDockWidgets::Controller::close()
bool c_KDDockWidgets__Controller__close(void *thisObj);
// KDDockWidgets::Controller::customEvent(QEvent * event)
void c_KDDockWidgets__Controller__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controller::event(QEvent * event)
bool c_KDDockWidgets__Controller__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controller::eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controller__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                             void *event_);
// KDDockWidgets::Controller::geometry() const
void *c_KDDockWidgets__Controller__geometry(void *thisObj);
// KDDockWidgets::Controller::height() const
int c_KDDockWidgets__Controller__height(void *thisObj);
// KDDockWidgets::Controller::inDtor() const
bool c_KDDockWidgets__Controller__inDtor(void *thisObj);
// KDDockWidgets::Controller::isVisible() const
bool c_KDDockWidgets__Controller__isVisible(void *thisObj);
// KDDockWidgets::Controller::mapToGlobal(QPoint arg__1) const
void *c_KDDockWidgets__Controller__mapToGlobal_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::Controller::parentViewChanged(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controller__parentViewChanged_View(void *thisObj, void *parent_);
void c_KDDockWidgets__Controller__onParentViewChanged_View(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controller::pos()
                     // const
void *c_KDDockWidgets__Controller__pos(void *thisObj);
// KDDockWidgets::Controller::rect() const
void *c_KDDockWidgets__Controller__rect(void *thisObj);
// KDDockWidgets::Controller::setParentView(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controller__setParentView_View(void *thisObj, void *parent_);
// KDDockWidgets::Controller::setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controller__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controller::setVisible(bool arg__1)
void c_KDDockWidgets__Controller__setVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controller::show() const
void c_KDDockWidgets__Controller__show(void *thisObj);
// KDDockWidgets::Controller::size() const
void *c_KDDockWidgets__Controller__size(void *thisObj);
// KDDockWidgets::Controller::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controller__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Controller::type() const
int c_KDDockWidgets__Controller__type(void *thisObj);
// KDDockWidgets::Controller::view() const
void *c_KDDockWidgets__Controller__view(void *thisObj);
// KDDockWidgets::Controller::width() const
int c_KDDockWidgets__Controller__width(void *thisObj);
// KDDockWidgets::Controller::x() const
int c_KDDockWidgets__Controller__x(void *thisObj);
// KDDockWidgets::Controller::y() const
int c_KDDockWidgets__Controller__y(void *thisObj);
void c_KDDockWidgets__Controller__destructor(void *thisObj);
void c_KDDockWidgets__Controller__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                int methodId);
void c_KDDockWidgets__Controller_Finalizer(
    void *, void *cppObj,
    void *); // KDDockWidgets::View::View(KDDockWidgets::Controller
             // * controller, KDDockWidgets::Type arg__2)
void *c_KDDockWidgets__View__constructor_Controller_Type(void *controller_, int arg__2);
// KDDockWidgets::View::aboutToBeDestroyed() const
bool c_KDDockWidgets__View__aboutToBeDestroyed(void *thisObj);
// KDDockWidgets::View::activateWindow()
void c_KDDockWidgets__View__activateWindow(void *thisObj);
// KDDockWidgets::View::asDropAreaController() const
void *c_KDDockWidgets__View__asDropAreaController(void *thisObj);
// KDDockWidgets::View::asGroupController() const
void *c_KDDockWidgets__View__asGroupController(void *thisObj);
// KDDockWidgets::View::asLayout() const
void *c_KDDockWidgets__View__asLayout(void *thisObj);
// KDDockWidgets::View::asStackController() const
void *c_KDDockWidgets__View__asStackController(void *thisObj);
// KDDockWidgets::View::asTabBarController() const
void *c_KDDockWidgets__View__asTabBarController(void *thisObj);
// KDDockWidgets::View::asTitleBarController() const
void *c_KDDockWidgets__View__asTitleBarController(void *thisObj);
// KDDockWidgets::View::boundedMaxSize(QSize min, QSize max)
void *c_static_KDDockWidgets__View__boundedMaxSize_QSize_QSize(void *min_, void *max_);
// KDDockWidgets::View::close()
bool c_KDDockWidgets__View__close(void *thisObj);
// KDDockWidgets::View::closeRootView()
void c_KDDockWidgets__View__closeRootView(void *thisObj);
// KDDockWidgets::View::controller() const
void *c_KDDockWidgets__View__controller(void *thisObj);
// KDDockWidgets::View::createPlatformWindow()
void c_KDDockWidgets__View__createPlatformWindow(void *thisObj);
// KDDockWidgets::View::equals(const KDDockWidgets::View * one, const KDDockWidgets::View * two)
bool c_static_KDDockWidgets__View__equals_View_View(void *one_, void *two_);
// KDDockWidgets::View::equals(const KDDockWidgets::View * other) const
bool c_KDDockWidgets__View__equals_View(void *thisObj, void *other_);
// KDDockWidgets::View::firstParentOfType(KDDockWidgets::Type arg__1) const
void *c_KDDockWidgets__View__firstParentOfType_Type(void *thisObj, int arg__1);
// KDDockWidgets::View::firstParentOfType(KDDockWidgets::View * view, KDDockWidgets::Type arg__2)
void *c_static_KDDockWidgets__View__firstParentOfType_View_Type(void *view_, int arg__2);
// KDDockWidgets::View::flags() const
int c_KDDockWidgets__View__flags(void *thisObj);
// KDDockWidgets::View::free()
void c_KDDockWidgets__View__free(void *thisObj);
// KDDockWidgets::View::free_impl()
void c_KDDockWidgets__View__free_impl(void *thisObj);
// KDDockWidgets::View::freed() const
bool c_KDDockWidgets__View__freed(void *thisObj);
// KDDockWidgets::View::geometry() const
void *c_KDDockWidgets__View__geometry(void *thisObj);
// KDDockWidgets::View::globalGeometry() const
void *c_KDDockWidgets__View__globalGeometry(void *thisObj);
// KDDockWidgets::View::grabMouse()
void c_KDDockWidgets__View__grabMouse(void *thisObj);
// KDDockWidgets::View::hardcodedMinimumSize()
void *c_static_KDDockWidgets__View__hardcodedMinimumSize();
// KDDockWidgets::View::hasFocus() const
bool c_KDDockWidgets__View__hasFocus(void *thisObj);
// KDDockWidgets::View::height() const
int c_KDDockWidgets__View__height(void *thisObj);
// KDDockWidgets::View::hide()
void c_KDDockWidgets__View__hide(void *thisObj);
// KDDockWidgets::View::id() const
void *c_KDDockWidgets__View__id(void *thisObj);
// KDDockWidgets::View::inDtor() const
bool c_KDDockWidgets__View__inDtor(void *thisObj);
// KDDockWidgets::View::init()
void c_KDDockWidgets__View__init(void *thisObj);
// KDDockWidgets::View::isActiveWindow() const
bool c_KDDockWidgets__View__isActiveWindow(void *thisObj);
// KDDockWidgets::View::isMaximized() const
bool c_KDDockWidgets__View__isMaximized(void *thisObj);
// KDDockWidgets::View::isMinimized() const
bool c_KDDockWidgets__View__isMinimized(void *thisObj);
// KDDockWidgets::View::isNull() const
bool c_KDDockWidgets__View__isNull(void *thisObj);
// KDDockWidgets::View::isRootView() const
bool c_KDDockWidgets__View__isRootView(void *thisObj);
// KDDockWidgets::View::isVisible() const
bool c_KDDockWidgets__View__isVisible(void *thisObj);
// KDDockWidgets::View::mapFromGlobal(QPoint arg__1) const
void *c_KDDockWidgets__View__mapFromGlobal_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::View::mapTo(KDDockWidgets::View * arg__1, QPoint arg__2) const
void *c_KDDockWidgets__View__mapTo_View_QPoint(void *thisObj, void *arg__1_, void *arg__2_);
// KDDockWidgets::View::mapToGlobal(QPoint arg__1) const
void *c_KDDockWidgets__View__mapToGlobal_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::View::maxSizeHint() const
void *c_KDDockWidgets__View__maxSizeHint(void *thisObj);
// KDDockWidgets::View::maximumSize() const
void *c_KDDockWidgets__View__maximumSize(void *thisObj);
// KDDockWidgets::View::minSize() const
void *c_KDDockWidgets__View__minSize(void *thisObj);
// KDDockWidgets::View::minimumHeight() const
int c_KDDockWidgets__View__minimumHeight(void *thisObj);
// KDDockWidgets::View::minimumWidth() const
int c_KDDockWidgets__View__minimumWidth(void *thisObj);
// KDDockWidgets::View::move(QPoint arg__1)
void c_KDDockWidgets__View__move_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::View::move(int x, int y)
void c_KDDockWidgets__View__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::View::normalGeometry() const
void *c_KDDockWidgets__View__normalGeometry(void *thisObj);
// KDDockWidgets::View::objectName() const
void *c_KDDockWidgets__View__objectName(void *thisObj);
// KDDockWidgets::View::onResize(QSize newSize)
bool c_KDDockWidgets__View__onResize_QSize(void *thisObj, void *newSize_);
// KDDockWidgets::View::parentSize() const
void *c_KDDockWidgets__View__parentSize(void *thisObj);
// KDDockWidgets::View::pos() const
void *c_KDDockWidgets__View__pos(void *thisObj);
// KDDockWidgets::View::raise()
void c_KDDockWidgets__View__raise(void *thisObj);
// KDDockWidgets::View::raiseAndActivate()
void c_KDDockWidgets__View__raiseAndActivate(void *thisObj);
// KDDockWidgets::View::rect() const
void *c_KDDockWidgets__View__rect(void *thisObj);
// KDDockWidgets::View::releaseKeyboard()
void c_KDDockWidgets__View__releaseKeyboard(void *thisObj);
// KDDockWidgets::View::releaseMouse()
void c_KDDockWidgets__View__releaseMouse(void *thisObj);
// KDDockWidgets::View::resize(QSize arg__1)
void c_KDDockWidgets__View__resize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::View::resize(int w, int h)
void c_KDDockWidgets__View__resize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::View::setAboutToBeDestroyed()
void c_KDDockWidgets__View__setAboutToBeDestroyed(void *thisObj);
// KDDockWidgets::View::setCursor(Qt::CursorShape arg__1)
void c_KDDockWidgets__View__setCursor_CursorShape(void *thisObj, int arg__1);
// KDDockWidgets::View::setFixedHeight(int arg__1)
void c_KDDockWidgets__View__setFixedHeight_int(void *thisObj, int arg__1);
// KDDockWidgets::View::setFixedWidth(int arg__1)
void c_KDDockWidgets__View__setFixedWidth_int(void *thisObj, int arg__1);
// KDDockWidgets::View::setGeometry(QRect arg__1)
void c_KDDockWidgets__View__setGeometry_QRect(void *thisObj, void *arg__1_);
// KDDockWidgets::View::setHeight(int height)
void c_KDDockWidgets__View__setHeight_int(void *thisObj, int height);
// KDDockWidgets::View::setMaximumSize(QSize sz)
void c_KDDockWidgets__View__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::View::setMinimumSize(QSize arg__1)
void c_KDDockWidgets__View__setMinimumSize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::View::setMouseTracking(bool arg__1)
void c_KDDockWidgets__View__setMouseTracking_bool(void *thisObj, bool arg__1);
// KDDockWidgets::View::setObjectName(const QString & arg__1)
void c_KDDockWidgets__View__setObjectName_QString(void *thisObj, const char *arg__1_);
// KDDockWidgets::View::setParent(KDDockWidgets::View * arg__1)
void c_KDDockWidgets__View__setParent_View(void *thisObj, void *arg__1_);
// KDDockWidgets::View::setSize(QSize arg__1)
void c_KDDockWidgets__View__setSize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::View::setSize(int width, int height)
void c_KDDockWidgets__View__setSize_int_int(void *thisObj, int width, int height);
// KDDockWidgets::View::setVisible(bool arg__1)
void c_KDDockWidgets__View__setVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::View::setWidth(int width)
void c_KDDockWidgets__View__setWidth_int(void *thisObj, int width);
// KDDockWidgets::View::setWindowOpacity(double arg__1)
void c_KDDockWidgets__View__setWindowOpacity_double(void *thisObj, double arg__1);
// KDDockWidgets::View::setWindowTitle(const QString & title)
void c_KDDockWidgets__View__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::View::setZOrder(int arg__1)
void c_KDDockWidgets__View__setZOrder_int(void *thisObj, int arg__1);
// KDDockWidgets::View::show()
void c_KDDockWidgets__View__show(void *thisObj);
// KDDockWidgets::View::showMaximized()
void c_KDDockWidgets__View__showMaximized(void *thisObj);
// KDDockWidgets::View::showMinimized()
void c_KDDockWidgets__View__showMinimized(void *thisObj);
// KDDockWidgets::View::showNormal()
void c_KDDockWidgets__View__showNormal(void *thisObj);
// KDDockWidgets::View::size() const
void *c_KDDockWidgets__View__size(void *thisObj);
// KDDockWidgets::View::sizeHint() const
void *c_KDDockWidgets__View__sizeHint(void *thisObj);
// KDDockWidgets::View::type() const
int c_KDDockWidgets__View__type(void *thisObj);
// KDDockWidgets::View::update()
void c_KDDockWidgets__View__update(void *thisObj);
// KDDockWidgets::View::width() const
int c_KDDockWidgets__View__width(void *thisObj);
// KDDockWidgets::View::windowGeometry() const
void *c_KDDockWidgets__View__windowGeometry(void *thisObj);
// KDDockWidgets::View::x() const
int c_KDDockWidgets__View__x(void *thisObj);
// KDDockWidgets::View::y() const
int c_KDDockWidgets__View__y(void *thisObj);
void c_KDDockWidgets__View__destructor(void *thisObj);
void c_KDDockWidgets__View__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
void c_KDDockWidgets__View_Finalizer(
    void *, void *cppObj,
    void *); // KDDockWidgets::Views::View_flutter::View_flutter(KDDockWidgets::Controller
             // * controller, KDDockWidgets::Type type,
             // KDDockWidgets::View * arg__3, Qt::WindowFlags
             // windowFlags)
void *c_KDDockWidgets__Views__View_flutter__constructor_Controller_Type_View_WindowFlags(
    void *controller_, int type, void *arg__3_, int windowFlags);
// KDDockWidgets::Views::View_flutter::activateWindow()
void c_KDDockWidgets__Views__View_flutter__activateWindow(void *thisObj);
// KDDockWidgets::Views::View_flutter::close()
bool c_KDDockWidgets__Views__View_flutter__close(void *thisObj);
// KDDockWidgets::Views::View_flutter::createPlatformWindow()
void c_KDDockWidgets__Views__View_flutter__createPlatformWindow(void *thisObj);
// KDDockWidgets::Views::View_flutter::flags() const
int c_KDDockWidgets__Views__View_flutter__flags(void *thisObj);
// KDDockWidgets::Views::View_flutter::free_impl()
void c_KDDockWidgets__Views__View_flutter__free_impl(void *thisObj);
// KDDockWidgets::Views::View_flutter::geometry() const
void *c_KDDockWidgets__Views__View_flutter__geometry(void *thisObj);
// KDDockWidgets::Views::View_flutter::grabMouse()
void c_KDDockWidgets__Views__View_flutter__grabMouse(void *thisObj);
// KDDockWidgets::Views::View_flutter::hasFocus() const
bool c_KDDockWidgets__Views__View_flutter__hasFocus(void *thisObj);
// KDDockWidgets::Views::View_flutter::hide()
void c_KDDockWidgets__Views__View_flutter__hide(void *thisObj);
// KDDockWidgets::Views::View_flutter::init()
void c_KDDockWidgets__Views__View_flutter__init(void *thisObj);
// KDDockWidgets::Views::View_flutter::isActiveWindow() const
bool c_KDDockWidgets__Views__View_flutter__isActiveWindow(void *thisObj);
// KDDockWidgets::Views::View_flutter::isMaximized() const
bool c_KDDockWidgets__Views__View_flutter__isMaximized(void *thisObj);
// KDDockWidgets::Views::View_flutter::isMinimized() const
bool c_KDDockWidgets__Views__View_flutter__isMinimized(void *thisObj);
// KDDockWidgets::Views::View_flutter::isNull() const
bool c_KDDockWidgets__Views__View_flutter__isNull(void *thisObj);
// KDDockWidgets::Views::View_flutter::isRootView() const
bool c_KDDockWidgets__Views__View_flutter__isRootView(void *thisObj);
// KDDockWidgets::Views::View_flutter::isVisible() const
bool c_KDDockWidgets__Views__View_flutter__isVisible(void *thisObj);
// KDDockWidgets::Views::View_flutter::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__Views__View_flutter__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::Views::View_flutter::mapTo(KDDockWidgets::View * parent, QPoint pos) const
void *c_KDDockWidgets__Views__View_flutter__mapTo_View_QPoint(void *thisObj, void *parent_,
                                                              void *pos_);
// KDDockWidgets::Views::View_flutter::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__Views__View_flutter__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::Views::View_flutter::maxSizeHint() const
void *c_KDDockWidgets__Views__View_flutter__maxSizeHint(void *thisObj);
// KDDockWidgets::Views::View_flutter::maximumSize() const
void *c_KDDockWidgets__Views__View_flutter__maximumSize(void *thisObj);
// KDDockWidgets::Views::View_flutter::minSize() const
void *c_KDDockWidgets__Views__View_flutter__minSize(void *thisObj);
// KDDockWidgets::Views::View_flutter::minimumHeight() const
int c_KDDockWidgets__Views__View_flutter__minimumHeight(void *thisObj);
// KDDockWidgets::Views::View_flutter::minimumWidth() const
int c_KDDockWidgets__Views__View_flutter__minimumWidth(void *thisObj);
// KDDockWidgets::Views::View_flutter::move(int x, int y)
void c_KDDockWidgets__Views__View_flutter__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::Views::View_flutter::normalGeometry() const
void *c_KDDockWidgets__Views__View_flutter__normalGeometry(void *thisObj);
// KDDockWidgets::Views::View_flutter::objectName() const
void *c_KDDockWidgets__Views__View_flutter__objectName(void *thisObj);
// KDDockWidgets::Views::View_flutter::onResize(QSize newSize)
bool c_KDDockWidgets__Views__View_flutter__onResize_QSize(void *thisObj, void *newSize_);
// KDDockWidgets::Views::View_flutter::raise()
void c_KDDockWidgets__Views__View_flutter__raise(void *thisObj);
// KDDockWidgets::Views::View_flutter::raiseAndActivate()
void c_KDDockWidgets__Views__View_flutter__raiseAndActivate(void *thisObj);
// KDDockWidgets::Views::View_flutter::releaseKeyboard()
void c_KDDockWidgets__Views__View_flutter__releaseKeyboard(void *thisObj);
// KDDockWidgets::Views::View_flutter::releaseMouse()
void c_KDDockWidgets__Views__View_flutter__releaseMouse(void *thisObj);
// KDDockWidgets::Views::View_flutter::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__Views__View_flutter__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::Views::View_flutter::setFixedHeight(int h)
void c_KDDockWidgets__Views__View_flutter__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::Views::View_flutter::setFixedWidth(int w)
void c_KDDockWidgets__Views__View_flutter__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::Views::View_flutter::setGeometry(QRect arg__1)
void c_KDDockWidgets__Views__View_flutter__setGeometry_QRect(void *thisObj, void *arg__1_);
// KDDockWidgets::Views::View_flutter::setHeight(int h)
void c_KDDockWidgets__Views__View_flutter__setHeight_int(void *thisObj, int h);
// KDDockWidgets::Views::View_flutter::setMaximumSize(QSize sz)
void c_KDDockWidgets__Views__View_flutter__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::Views::View_flutter::setMinimumSize(QSize sz)
void c_KDDockWidgets__Views__View_flutter__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::Views::View_flutter::setMouseTracking(bool enable)
void c_KDDockWidgets__Views__View_flutter__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::Views::View_flutter::setNormalGeometry(QRect geo)
void c_KDDockWidgets__Views__View_flutter__setNormalGeometry_QRect(void *thisObj, void *geo_);
// KDDockWidgets::Views::View_flutter::setObjectName(const QString & name)
void c_KDDockWidgets__Views__View_flutter__setObjectName_QString(void *thisObj, const char *name_);
// KDDockWidgets::Views::View_flutter::setParent(KDDockWidgets::View * parent)
void c_KDDockWidgets__Views__View_flutter__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::Views::View_flutter::setSize(int w, int h)
void c_KDDockWidgets__Views__View_flutter__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::Views::View_flutter::setVisible(bool visible)
void c_KDDockWidgets__Views__View_flutter__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::Views::View_flutter::setWidth(int w)
void c_KDDockWidgets__Views__View_flutter__setWidth_int(void *thisObj, int w);
// KDDockWidgets::Views::View_flutter::setWindowOpacity(double v)
void c_KDDockWidgets__Views__View_flutter__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::Views::View_flutter::setWindowTitle(const QString & title)
void c_KDDockWidgets__Views__View_flutter__setWindowTitle_QString(void *thisObj,
                                                                  const char *title_);
// KDDockWidgets::Views::View_flutter::setZOrder(int arg__1)
void c_KDDockWidgets__Views__View_flutter__setZOrder_int(void *thisObj, int arg__1);
// KDDockWidgets::Views::View_flutter::show()
void c_KDDockWidgets__Views__View_flutter__show(void *thisObj);
// KDDockWidgets::Views::View_flutter::showMaximized()
void c_KDDockWidgets__Views__View_flutter__showMaximized(void *thisObj);
// KDDockWidgets::Views::View_flutter::showMinimized()
void c_KDDockWidgets__Views__View_flutter__showMinimized(void *thisObj);
// KDDockWidgets::Views::View_flutter::showNormal()
void c_KDDockWidgets__Views__View_flutter__showNormal(void *thisObj);
// KDDockWidgets::Views::View_flutter::sizeHint() const
void *c_KDDockWidgets__Views__View_flutter__sizeHint(void *thisObj);
// KDDockWidgets::Views::View_flutter::update()
void c_KDDockWidgets__Views__View_flutter__update(void *thisObj);
// KDDockWidgets::Views::View_flutter::updateGeometry()
void c_KDDockWidgets__Views__View_flutter__updateGeometry(void *thisObj);
void c_KDDockWidgets__Views__View_flutter__destructor(void *thisObj);
void c_KDDockWidgets__Views__View_flutter__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                         int methodId);
void c_KDDockWidgets__Views__View_flutter_Finalizer(
    void *, void *cppObj,
    void
        *); // KDDockWidgets::Views::TitleBar_flutter::TitleBar_flutter(KDDockWidgets::Controllers::TitleBar
            // * controller, KDDockWidgets::View *
            // parent)
void *c_KDDockWidgets__Views__TitleBar_flutter__constructor_TitleBar_View(void *controller_,
                                                                          void *parent_);
// KDDockWidgets::Views::TitleBar_flutter::activateWindow()
void c_KDDockWidgets__Views__TitleBar_flutter__activateWindow(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::close()
bool c_KDDockWidgets__Views__TitleBar_flutter__close(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::createPlatformWindow()
void c_KDDockWidgets__Views__TitleBar_flutter__createPlatformWindow(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::flags() const
int c_KDDockWidgets__Views__TitleBar_flutter__flags(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::free_impl()
void c_KDDockWidgets__Views__TitleBar_flutter__free_impl(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::geometry() const
void *c_KDDockWidgets__Views__TitleBar_flutter__geometry(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::grabMouse()
void c_KDDockWidgets__Views__TitleBar_flutter__grabMouse(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::hasFocus() const
bool c_KDDockWidgets__Views__TitleBar_flutter__hasFocus(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::hide()
void c_KDDockWidgets__Views__TitleBar_flutter__hide(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::init()
void c_KDDockWidgets__Views__TitleBar_flutter__init(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isActiveWindow() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isActiveWindow(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isCloseButtonEnabled() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isCloseButtonEnabled(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isCloseButtonVisible() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isCloseButtonVisible(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isFloatButtonVisible() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isFloatButtonVisible(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isMaximized() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isMaximized(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isMinimized() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isMinimized(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isNull() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isNull(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isRootView() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isRootView(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isVisible() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isVisible(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__Views__TitleBar_flutter__mapFromGlobal_QPoint(void *thisObj,
                                                                     void *globalPt_);
// KDDockWidgets::Views::TitleBar_flutter::mapTo(KDDockWidgets::View * parent, QPoint pos) const
void *c_KDDockWidgets__Views__TitleBar_flutter__mapTo_View_QPoint(void *thisObj, void *parent_,
                                                                  void *pos_);
// KDDockWidgets::Views::TitleBar_flutter::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__Views__TitleBar_flutter__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::Views::TitleBar_flutter::maxSizeHint() const
void *c_KDDockWidgets__Views__TitleBar_flutter__maxSizeHint(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::maximumSize() const
void *c_KDDockWidgets__Views__TitleBar_flutter__maximumSize(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::minSize() const
void *c_KDDockWidgets__Views__TitleBar_flutter__minSize(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::minimumHeight() const
int c_KDDockWidgets__Views__TitleBar_flutter__minimumHeight(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::minimumWidth() const
int c_KDDockWidgets__Views__TitleBar_flutter__minimumWidth(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::move(int x, int y)
void c_KDDockWidgets__Views__TitleBar_flutter__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::Views::TitleBar_flutter::normalGeometry() const
void *c_KDDockWidgets__Views__TitleBar_flutter__normalGeometry(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::objectName() const
void *c_KDDockWidgets__Views__TitleBar_flutter__objectName(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::onResize(QSize newSize)
bool c_KDDockWidgets__Views__TitleBar_flutter__onResize_QSize(void *thisObj, void *newSize_);
// KDDockWidgets::Views::TitleBar_flutter::raise()
void c_KDDockWidgets__Views__TitleBar_flutter__raise(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::raiseAndActivate()
void c_KDDockWidgets__Views__TitleBar_flutter__raiseAndActivate(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::releaseKeyboard()
void c_KDDockWidgets__Views__TitleBar_flutter__releaseKeyboard(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::releaseMouse()
void c_KDDockWidgets__Views__TitleBar_flutter__releaseMouse(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__Views__TitleBar_flutter__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::Views::TitleBar_flutter::setFixedHeight(int h)
void c_KDDockWidgets__Views__TitleBar_flutter__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::Views::TitleBar_flutter::setFixedWidth(int w)
void c_KDDockWidgets__Views__TitleBar_flutter__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::Views::TitleBar_flutter::setGeometry(QRect arg__1)
void c_KDDockWidgets__Views__TitleBar_flutter__setGeometry_QRect(void *thisObj, void *arg__1_);
// KDDockWidgets::Views::TitleBar_flutter::setHeight(int h)
void c_KDDockWidgets__Views__TitleBar_flutter__setHeight_int(void *thisObj, int h);
// KDDockWidgets::Views::TitleBar_flutter::setMaximumSize(QSize sz)
void c_KDDockWidgets__Views__TitleBar_flutter__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::Views::TitleBar_flutter::setMinimumSize(QSize sz)
void c_KDDockWidgets__Views__TitleBar_flutter__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::Views::TitleBar_flutter::setMouseTracking(bool enable)
void c_KDDockWidgets__Views__TitleBar_flutter__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::Views::TitleBar_flutter::setObjectName(const QString & name)
void c_KDDockWidgets__Views__TitleBar_flutter__setObjectName_QString(void *thisObj,
                                                                     const char *name_);
// KDDockWidgets::Views::TitleBar_flutter::setParent(KDDockWidgets::View * parent)
void c_KDDockWidgets__Views__TitleBar_flutter__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::Views::TitleBar_flutter::setSize(int w, int h)
void c_KDDockWidgets__Views__TitleBar_flutter__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::Views::TitleBar_flutter::setVisible(bool visible)
void c_KDDockWidgets__Views__TitleBar_flutter__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::Views::TitleBar_flutter::setWidth(int w)
void c_KDDockWidgets__Views__TitleBar_flutter__setWidth_int(void *thisObj, int w);
// KDDockWidgets::Views::TitleBar_flutter::setWindowOpacity(double v)
void c_KDDockWidgets__Views__TitleBar_flutter__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::Views::TitleBar_flutter::setWindowTitle(const QString & title)
void c_KDDockWidgets__Views__TitleBar_flutter__setWindowTitle_QString(void *thisObj,
                                                                      const char *title_);
// KDDockWidgets::Views::TitleBar_flutter::setZOrder(int arg__1)
void c_KDDockWidgets__Views__TitleBar_flutter__setZOrder_int(void *thisObj, int arg__1);
// KDDockWidgets::Views::TitleBar_flutter::show()
void c_KDDockWidgets__Views__TitleBar_flutter__show(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::showMaximized()
void c_KDDockWidgets__Views__TitleBar_flutter__showMaximized(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::showMinimized()
void c_KDDockWidgets__Views__TitleBar_flutter__showMinimized(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::showNormal()
void c_KDDockWidgets__Views__TitleBar_flutter__showNormal(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::sizeHint() const
void *c_KDDockWidgets__Views__TitleBar_flutter__sizeHint(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::update()
void c_KDDockWidgets__Views__TitleBar_flutter__update(void *thisObj);
void c_KDDockWidgets__Views__TitleBar_flutter__destructor(void *thisObj);
void c_KDDockWidgets__Views__TitleBar_flutter__registerVirtualMethodCallback(void *ptr,
                                                                             void *callback,
                                                                             int methodId);
void c_KDDockWidgets__Views__TitleBar_flutter_Finalizer(
    void *, void *cppObj,
    void
        *); // KDDockWidgets::Views::TabBar_flutter::TabBar_flutter(KDDockWidgets::Controllers::TabBar
            // * controller,
            // KDDockWidgets::View * parent)
void *c_KDDockWidgets__Views__TabBar_flutter__constructor_TabBar_View(void *controller_,
                                                                      void *parent_);
// KDDockWidgets::Views::TabBar_flutter::activateWindow()
void c_KDDockWidgets__Views__TabBar_flutter__activateWindow(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::close()
bool c_KDDockWidgets__Views__TabBar_flutter__close(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::createPlatformWindow()
void c_KDDockWidgets__Views__TabBar_flutter__createPlatformWindow(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::flags() const
int c_KDDockWidgets__Views__TabBar_flutter__flags(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::free_impl()
void c_KDDockWidgets__Views__TabBar_flutter__free_impl(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::geometry() const
void *c_KDDockWidgets__Views__TabBar_flutter__geometry(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::grabMouse()
void c_KDDockWidgets__Views__TabBar_flutter__grabMouse(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::hasFocus() const
bool c_KDDockWidgets__Views__TabBar_flutter__hasFocus(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::hide()
void c_KDDockWidgets__Views__TabBar_flutter__hide(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::init()
void c_KDDockWidgets__Views__TabBar_flutter__init(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::isActiveWindow() const
bool c_KDDockWidgets__Views__TabBar_flutter__isActiveWindow(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::isMaximized() const
bool c_KDDockWidgets__Views__TabBar_flutter__isMaximized(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::isMinimized() const
bool c_KDDockWidgets__Views__TabBar_flutter__isMinimized(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::isNull() const
bool c_KDDockWidgets__Views__TabBar_flutter__isNull(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::isRootView() const
bool c_KDDockWidgets__Views__TabBar_flutter__isRootView(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::isVisible() const
bool c_KDDockWidgets__Views__TabBar_flutter__isVisible(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__Views__TabBar_flutter__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::Views::TabBar_flutter::mapTo(KDDockWidgets::View * parent, QPoint pos) const
void *c_KDDockWidgets__Views__TabBar_flutter__mapTo_View_QPoint(void *thisObj, void *parent_,
                                                                void *pos_);
// KDDockWidgets::Views::TabBar_flutter::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__Views__TabBar_flutter__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::Views::TabBar_flutter::maxSizeHint() const
void *c_KDDockWidgets__Views__TabBar_flutter__maxSizeHint(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::maximumSize() const
void *c_KDDockWidgets__Views__TabBar_flutter__maximumSize(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::minSize() const
void *c_KDDockWidgets__Views__TabBar_flutter__minSize(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::minimumHeight() const
int c_KDDockWidgets__Views__TabBar_flutter__minimumHeight(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::minimumWidth() const
int c_KDDockWidgets__Views__TabBar_flutter__minimumWidth(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::move(int x, int y)
void c_KDDockWidgets__Views__TabBar_flutter__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::Views::TabBar_flutter::moveTabTo(int from, int to)
void c_KDDockWidgets__Views__TabBar_flutter__moveTabTo_int_int(void *thisObj, int from, int to);
// KDDockWidgets::Views::TabBar_flutter::normalGeometry() const
void *c_KDDockWidgets__Views__TabBar_flutter__normalGeometry(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::objectName() const
void *c_KDDockWidgets__Views__TabBar_flutter__objectName(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::onResize(QSize newSize)
bool c_KDDockWidgets__Views__TabBar_flutter__onResize_QSize(void *thisObj, void *newSize_);
// KDDockWidgets::Views::TabBar_flutter::raise()
void c_KDDockWidgets__Views__TabBar_flutter__raise(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::raiseAndActivate()
void c_KDDockWidgets__Views__TabBar_flutter__raiseAndActivate(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::rectForTab(int index) const
void *c_KDDockWidgets__Views__TabBar_flutter__rectForTab_int(void *thisObj, int index);
// KDDockWidgets::Views::TabBar_flutter::releaseKeyboard()
void c_KDDockWidgets__Views__TabBar_flutter__releaseKeyboard(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::releaseMouse()
void c_KDDockWidgets__Views__TabBar_flutter__releaseMouse(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__Views__TabBar_flutter__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::Views::TabBar_flutter::setFixedHeight(int h)
void c_KDDockWidgets__Views__TabBar_flutter__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::Views::TabBar_flutter::setFixedWidth(int w)
void c_KDDockWidgets__Views__TabBar_flutter__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::Views::TabBar_flutter::setGeometry(QRect arg__1)
void c_KDDockWidgets__Views__TabBar_flutter__setGeometry_QRect(void *thisObj, void *arg__1_);
// KDDockWidgets::Views::TabBar_flutter::setHeight(int h)
void c_KDDockWidgets__Views__TabBar_flutter__setHeight_int(void *thisObj, int h);
// KDDockWidgets::Views::TabBar_flutter::setMaximumSize(QSize sz)
void c_KDDockWidgets__Views__TabBar_flutter__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::Views::TabBar_flutter::setMinimumSize(QSize sz)
void c_KDDockWidgets__Views__TabBar_flutter__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::Views::TabBar_flutter::setMouseTracking(bool enable)
void c_KDDockWidgets__Views__TabBar_flutter__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::Views::TabBar_flutter::setObjectName(const QString & name)
void c_KDDockWidgets__Views__TabBar_flutter__setObjectName_QString(void *thisObj,
                                                                   const char *name_);
// KDDockWidgets::Views::TabBar_flutter::setParent(KDDockWidgets::View * parent)
void c_KDDockWidgets__Views__TabBar_flutter__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::Views::TabBar_flutter::setSize(int w, int h)
void c_KDDockWidgets__Views__TabBar_flutter__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::Views::TabBar_flutter::setVisible(bool visible)
void c_KDDockWidgets__Views__TabBar_flutter__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::Views::TabBar_flutter::setWidth(int w)
void c_KDDockWidgets__Views__TabBar_flutter__setWidth_int(void *thisObj, int w);
// KDDockWidgets::Views::TabBar_flutter::setWindowOpacity(double v)
void c_KDDockWidgets__Views__TabBar_flutter__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::Views::TabBar_flutter::setWindowTitle(const QString & title)
void c_KDDockWidgets__Views__TabBar_flutter__setWindowTitle_QString(void *thisObj,
                                                                    const char *title_);
// KDDockWidgets::Views::TabBar_flutter::setZOrder(int arg__1)
void c_KDDockWidgets__Views__TabBar_flutter__setZOrder_int(void *thisObj, int arg__1);
// KDDockWidgets::Views::TabBar_flutter::show()
void c_KDDockWidgets__Views__TabBar_flutter__show(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::showMaximized()
void c_KDDockWidgets__Views__TabBar_flutter__showMaximized(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::showMinimized()
void c_KDDockWidgets__Views__TabBar_flutter__showMinimized(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::showNormal()
void c_KDDockWidgets__Views__TabBar_flutter__showNormal(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::sizeHint() const
void *c_KDDockWidgets__Views__TabBar_flutter__sizeHint(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::tabAt(QPoint localPos) const
int c_KDDockWidgets__Views__TabBar_flutter__tabAt_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::Views::TabBar_flutter::tabsAreMovable() const
bool c_KDDockWidgets__Views__TabBar_flutter__tabsAreMovable(void *thisObj);
// KDDockWidgets::Views::TabBar_flutter::text(int index) const
void *c_KDDockWidgets__Views__TabBar_flutter__text_int(void *thisObj, int index);
// KDDockWidgets::Views::TabBar_flutter::update()
void c_KDDockWidgets__Views__TabBar_flutter__update(void *thisObj);
void c_KDDockWidgets__Views__TabBar_flutter__destructor(void *thisObj);
void c_KDDockWidgets__Views__TabBar_flutter__registerVirtualMethodCallback(void *ptr,
                                                                           void *callback,
                                                                           int methodId);
void c_KDDockWidgets__Views__TabBar_flutter_Finalizer(
    void *, void *cppObj,
    void *); // KDDockWidgets::Views::Stack_flutter::Stack_flutter(KDDockWidgets::Controllers::Stack
             // * controller, KDDockWidgets::View
             // * parent)
void *c_KDDockWidgets__Views__Stack_flutter__constructor_Stack_View(void *controller_,
                                                                    void *parent_);
// KDDockWidgets::Views::Stack_flutter::activateWindow()
void c_KDDockWidgets__Views__Stack_flutter__activateWindow(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::close()
bool c_KDDockWidgets__Views__Stack_flutter__close(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::createPlatformWindow()
void c_KDDockWidgets__Views__Stack_flutter__createPlatformWindow(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::currentIndex() const
int c_KDDockWidgets__Views__Stack_flutter__currentIndex(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::flags() const
int c_KDDockWidgets__Views__Stack_flutter__flags(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::free_impl()
void c_KDDockWidgets__Views__Stack_flutter__free_impl(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::geometry() const
void *c_KDDockWidgets__Views__Stack_flutter__geometry(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::grabMouse()
void c_KDDockWidgets__Views__Stack_flutter__grabMouse(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::hasFocus() const
bool c_KDDockWidgets__Views__Stack_flutter__hasFocus(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::hide()
void c_KDDockWidgets__Views__Stack_flutter__hide(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::init()
void c_KDDockWidgets__Views__Stack_flutter__init(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::isActiveWindow() const
bool c_KDDockWidgets__Views__Stack_flutter__isActiveWindow(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::isMaximized() const
bool c_KDDockWidgets__Views__Stack_flutter__isMaximized(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::isMinimized() const
bool c_KDDockWidgets__Views__Stack_flutter__isMinimized(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::isNull() const
bool c_KDDockWidgets__Views__Stack_flutter__isNull(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::isPositionDraggable(QPoint p) const
bool c_KDDockWidgets__Views__Stack_flutter__isPositionDraggable_QPoint(void *thisObj, void *p_);
// KDDockWidgets::Views::Stack_flutter::isRootView() const
bool c_KDDockWidgets__Views__Stack_flutter__isRootView(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::isVisible() const
bool c_KDDockWidgets__Views__Stack_flutter__isVisible(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__Views__Stack_flutter__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::Views::Stack_flutter::mapTo(KDDockWidgets::View * parent, QPoint pos) const
void *c_KDDockWidgets__Views__Stack_flutter__mapTo_View_QPoint(void *thisObj, void *parent_,
                                                               void *pos_);
// KDDockWidgets::Views::Stack_flutter::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__Views__Stack_flutter__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::Views::Stack_flutter::maxSizeHint() const
void *c_KDDockWidgets__Views__Stack_flutter__maxSizeHint(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::maximumSize() const
void *c_KDDockWidgets__Views__Stack_flutter__maximumSize(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::minSize() const
void *c_KDDockWidgets__Views__Stack_flutter__minSize(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::minimumHeight() const
int c_KDDockWidgets__Views__Stack_flutter__minimumHeight(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::minimumWidth() const
int c_KDDockWidgets__Views__Stack_flutter__minimumWidth(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::move(int x, int y)
void c_KDDockWidgets__Views__Stack_flutter__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::Views::Stack_flutter::normalGeometry() const
void *c_KDDockWidgets__Views__Stack_flutter__normalGeometry(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::numDockWidgets() const
int c_KDDockWidgets__Views__Stack_flutter__numDockWidgets(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::objectName() const
void *c_KDDockWidgets__Views__Stack_flutter__objectName(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::onResize(QSize newSize)
bool c_KDDockWidgets__Views__Stack_flutter__onResize_QSize(void *thisObj, void *newSize_);
// KDDockWidgets::Views::Stack_flutter::raise()
void c_KDDockWidgets__Views__Stack_flutter__raise(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::raiseAndActivate()
void c_KDDockWidgets__Views__Stack_flutter__raiseAndActivate(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::releaseKeyboard()
void c_KDDockWidgets__Views__Stack_flutter__releaseKeyboard(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::releaseMouse()
void c_KDDockWidgets__Views__Stack_flutter__releaseMouse(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::renameTab(int index, const QString & arg__2)
void c_KDDockWidgets__Views__Stack_flutter__renameTab_int_QString(void *thisObj, int index,
                                                                  const char *arg__2_);
// KDDockWidgets::Views::Stack_flutter::setCurrentDockWidget(int index)
void c_KDDockWidgets__Views__Stack_flutter__setCurrentDockWidget_int(void *thisObj, int index);
// KDDockWidgets::Views::Stack_flutter::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__Views__Stack_flutter__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::Views::Stack_flutter::setDocumentMode(bool arg__1)
void c_KDDockWidgets__Views__Stack_flutter__setDocumentMode_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Views::Stack_flutter::setFixedHeight(int h)
void c_KDDockWidgets__Views__Stack_flutter__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::Views::Stack_flutter::setFixedWidth(int w)
void c_KDDockWidgets__Views__Stack_flutter__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::Views::Stack_flutter::setGeometry(QRect arg__1)
void c_KDDockWidgets__Views__Stack_flutter__setGeometry_QRect(void *thisObj, void *arg__1_);
// KDDockWidgets::Views::Stack_flutter::setHeight(int h)
void c_KDDockWidgets__Views__Stack_flutter__setHeight_int(void *thisObj, int h);
// KDDockWidgets::Views::Stack_flutter::setMaximumSize(QSize sz)
void c_KDDockWidgets__Views__Stack_flutter__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::Views::Stack_flutter::setMinimumSize(QSize sz)
void c_KDDockWidgets__Views__Stack_flutter__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::Views::Stack_flutter::setMouseTracking(bool enable)
void c_KDDockWidgets__Views__Stack_flutter__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::Views::Stack_flutter::setObjectName(const QString & name)
void c_KDDockWidgets__Views__Stack_flutter__setObjectName_QString(void *thisObj, const char *name_);
// KDDockWidgets::Views::Stack_flutter::setParent(KDDockWidgets::View * parent)
void c_KDDockWidgets__Views__Stack_flutter__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::Views::Stack_flutter::setSize(int w, int h)
void c_KDDockWidgets__Views__Stack_flutter__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::Views::Stack_flutter::setVisible(bool visible)
void c_KDDockWidgets__Views__Stack_flutter__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::Views::Stack_flutter::setWidth(int w)
void c_KDDockWidgets__Views__Stack_flutter__setWidth_int(void *thisObj, int w);
// KDDockWidgets::Views::Stack_flutter::setWindowOpacity(double v)
void c_KDDockWidgets__Views__Stack_flutter__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::Views::Stack_flutter::setWindowTitle(const QString & title)
void c_KDDockWidgets__Views__Stack_flutter__setWindowTitle_QString(void *thisObj,
                                                                   const char *title_);
// KDDockWidgets::Views::Stack_flutter::setZOrder(int arg__1)
void c_KDDockWidgets__Views__Stack_flutter__setZOrder_int(void *thisObj, int arg__1);
// KDDockWidgets::Views::Stack_flutter::show()
void c_KDDockWidgets__Views__Stack_flutter__show(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::showMaximized()
void c_KDDockWidgets__Views__Stack_flutter__showMaximized(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::showMinimized()
void c_KDDockWidgets__Views__Stack_flutter__showMinimized(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::showNormal()
void c_KDDockWidgets__Views__Stack_flutter__showNormal(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::sizeHint() const
void *c_KDDockWidgets__Views__Stack_flutter__sizeHint(void *thisObj);
// KDDockWidgets::Views::Stack_flutter::update()
void c_KDDockWidgets__Views__Stack_flutter__update(void *thisObj);
void c_KDDockWidgets__Views__Stack_flutter__destructor(void *thisObj);
void c_KDDockWidgets__Views__Stack_flutter__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                          int methodId);
void c_KDDockWidgets__Views__Stack_flutter_Finalizer(
    void *, void *cppObj,
    void *); // KDDockWidgets::Views::Group_flutter::Group_flutter(KDDockWidgets::Controllers::Group
             // * controller, KDDockWidgets::View *
             // parent)
void *c_KDDockWidgets__Views__Group_flutter__constructor_Group_View(void *controller_,
                                                                    void *parent_);
// KDDockWidgets::Views::Group_flutter::activateWindow()
void c_KDDockWidgets__Views__Group_flutter__activateWindow(void *thisObj);
// KDDockWidgets::Views::Group_flutter::close()
bool c_KDDockWidgets__Views__Group_flutter__close(void *thisObj);
// KDDockWidgets::Views::Group_flutter::createPlatformWindow()
void c_KDDockWidgets__Views__Group_flutter__createPlatformWindow(void *thisObj);
// KDDockWidgets::Views::Group_flutter::currentIndex() const
int c_KDDockWidgets__Views__Group_flutter__currentIndex(void *thisObj);
// KDDockWidgets::Views::Group_flutter::dragRect() const
void *c_KDDockWidgets__Views__Group_flutter__dragRect(void *thisObj);
// KDDockWidgets::Views::Group_flutter::flags() const
int c_KDDockWidgets__Views__Group_flutter__flags(void *thisObj);
// KDDockWidgets::Views::Group_flutter::free_impl()
void c_KDDockWidgets__Views__Group_flutter__free_impl(void *thisObj);
// KDDockWidgets::Views::Group_flutter::geometry() const
void *c_KDDockWidgets__Views__Group_flutter__geometry(void *thisObj);
// KDDockWidgets::Views::Group_flutter::grabMouse()
void c_KDDockWidgets__Views__Group_flutter__grabMouse(void *thisObj);
// KDDockWidgets::Views::Group_flutter::hasFocus() const
bool c_KDDockWidgets__Views__Group_flutter__hasFocus(void *thisObj);
// KDDockWidgets::Views::Group_flutter::hide()
void c_KDDockWidgets__Views__Group_flutter__hide(void *thisObj);
// KDDockWidgets::Views::Group_flutter::isActiveWindow() const
bool c_KDDockWidgets__Views__Group_flutter__isActiveWindow(void *thisObj);
// KDDockWidgets::Views::Group_flutter::isMaximized() const
bool c_KDDockWidgets__Views__Group_flutter__isMaximized(void *thisObj);
// KDDockWidgets::Views::Group_flutter::isMinimized() const
bool c_KDDockWidgets__Views__Group_flutter__isMinimized(void *thisObj);
// KDDockWidgets::Views::Group_flutter::isNull() const
bool c_KDDockWidgets__Views__Group_flutter__isNull(void *thisObj);
// KDDockWidgets::Views::Group_flutter::isRootView() const
bool c_KDDockWidgets__Views__Group_flutter__isRootView(void *thisObj);
// KDDockWidgets::Views::Group_flutter::isVisible() const
bool c_KDDockWidgets__Views__Group_flutter__isVisible(void *thisObj);
// KDDockWidgets::Views::Group_flutter::mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__Views__Group_flutter__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::Views::Group_flutter::mapTo(KDDockWidgets::View * parent, QPoint pos) const
void *c_KDDockWidgets__Views__Group_flutter__mapTo_View_QPoint(void *thisObj, void *parent_,
                                                               void *pos_);
// KDDockWidgets::Views::Group_flutter::mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__Views__Group_flutter__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::Views::Group_flutter::maxSizeHint() const
void *c_KDDockWidgets__Views__Group_flutter__maxSizeHint(void *thisObj);
// KDDockWidgets::Views::Group_flutter::maximumSize() const
void *c_KDDockWidgets__Views__Group_flutter__maximumSize(void *thisObj);
// KDDockWidgets::Views::Group_flutter::minSize() const
void *c_KDDockWidgets__Views__Group_flutter__minSize(void *thisObj);
// KDDockWidgets::Views::Group_flutter::minimumHeight() const
int c_KDDockWidgets__Views__Group_flutter__minimumHeight(void *thisObj);
// KDDockWidgets::Views::Group_flutter::minimumWidth() const
int c_KDDockWidgets__Views__Group_flutter__minimumWidth(void *thisObj);
// KDDockWidgets::Views::Group_flutter::move(int x, int y)
void c_KDDockWidgets__Views__Group_flutter__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::Views::Group_flutter::nonContentsHeight() const
int c_KDDockWidgets__Views__Group_flutter__nonContentsHeight(void *thisObj);
// KDDockWidgets::Views::Group_flutter::normalGeometry() const
void *c_KDDockWidgets__Views__Group_flutter__normalGeometry(void *thisObj);
// KDDockWidgets::Views::Group_flutter::objectName() const
void *c_KDDockWidgets__Views__Group_flutter__objectName(void *thisObj);
// KDDockWidgets::Views::Group_flutter::onResize(QSize newSize)
bool c_KDDockWidgets__Views__Group_flutter__onResize_QSize(void *thisObj, void *newSize_);
// KDDockWidgets::Views::Group_flutter::raise()
void c_KDDockWidgets__Views__Group_flutter__raise(void *thisObj);
// KDDockWidgets::Views::Group_flutter::raiseAndActivate()
void c_KDDockWidgets__Views__Group_flutter__raiseAndActivate(void *thisObj);
// KDDockWidgets::Views::Group_flutter::releaseKeyboard()
void c_KDDockWidgets__Views__Group_flutter__releaseKeyboard(void *thisObj);
// KDDockWidgets::Views::Group_flutter::releaseMouse()
void c_KDDockWidgets__Views__Group_flutter__releaseMouse(void *thisObj);
// KDDockWidgets::Views::Group_flutter::renameTab(int index, const QString & arg__2)
void c_KDDockWidgets__Views__Group_flutter__renameTab_int_QString(void *thisObj, int index,
                                                                  const char *arg__2_);
// KDDockWidgets::Views::Group_flutter::setCurrentTabIndex_impl(int index)
void c_KDDockWidgets__Views__Group_flutter__setCurrentTabIndex_impl_int(void *thisObj, int index);
// KDDockWidgets::Views::Group_flutter::setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__Views__Group_flutter__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::Views::Group_flutter::setFixedHeight(int h)
void c_KDDockWidgets__Views__Group_flutter__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::Views::Group_flutter::setFixedWidth(int w)
void c_KDDockWidgets__Views__Group_flutter__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::Views::Group_flutter::setGeometry(QRect arg__1)
void c_KDDockWidgets__Views__Group_flutter__setGeometry_QRect(void *thisObj, void *arg__1_);
// KDDockWidgets::Views::Group_flutter::setHeight(int h)
void c_KDDockWidgets__Views__Group_flutter__setHeight_int(void *thisObj, int h);
// KDDockWidgets::Views::Group_flutter::setMaximumSize(QSize sz)
void c_KDDockWidgets__Views__Group_flutter__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::Views::Group_flutter::setMinimumSize(QSize sz)
void c_KDDockWidgets__Views__Group_flutter__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::Views::Group_flutter::setMouseTracking(bool enable)
void c_KDDockWidgets__Views__Group_flutter__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::Views::Group_flutter::setObjectName(const QString & name)
void c_KDDockWidgets__Views__Group_flutter__setObjectName_QString(void *thisObj, const char *name_);
// KDDockWidgets::Views::Group_flutter::setParent(KDDockWidgets::View * parent)
void c_KDDockWidgets__Views__Group_flutter__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::Views::Group_flutter::setSize(int w, int h)
void c_KDDockWidgets__Views__Group_flutter__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::Views::Group_flutter::setVisible(bool visible)
void c_KDDockWidgets__Views__Group_flutter__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::Views::Group_flutter::setWidth(int w)
void c_KDDockWidgets__Views__Group_flutter__setWidth_int(void *thisObj, int w);
// KDDockWidgets::Views::Group_flutter::setWindowOpacity(double v)
void c_KDDockWidgets__Views__Group_flutter__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::Views::Group_flutter::setWindowTitle(const QString & title)
void c_KDDockWidgets__Views__Group_flutter__setWindowTitle_QString(void *thisObj,
                                                                   const char *title_);
// KDDockWidgets::Views::Group_flutter::setZOrder(int arg__1)
void c_KDDockWidgets__Views__Group_flutter__setZOrder_int(void *thisObj, int arg__1);
// KDDockWidgets::Views::Group_flutter::show()
void c_KDDockWidgets__Views__Group_flutter__show(void *thisObj);
// KDDockWidgets::Views::Group_flutter::showMaximized()
void c_KDDockWidgets__Views__Group_flutter__showMaximized(void *thisObj);
// KDDockWidgets::Views::Group_flutter::showMinimized()
void c_KDDockWidgets__Views__Group_flutter__showMinimized(void *thisObj);
// KDDockWidgets::Views::Group_flutter::showNormal()
void c_KDDockWidgets__Views__Group_flutter__showNormal(void *thisObj);
// KDDockWidgets::Views::Group_flutter::sizeHint() const
void *c_KDDockWidgets__Views__Group_flutter__sizeHint(void *thisObj);
// KDDockWidgets::Views::Group_flutter::update()
void c_KDDockWidgets__Views__Group_flutter__update(void *thisObj);
void c_KDDockWidgets__Views__Group_flutter__destructor(void *thisObj);
void c_KDDockWidgets__Views__Group_flutter__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                          int methodId);
void c_KDDockWidgets__Views__Group_flutter_Finalizer(
    void *, void *cppObj,
    void *); // KDDockWidgets::Controllers::TitleBar::TitleBar(KDDockWidgets::Controllers::Group
             // * parent)
void *c_KDDockWidgets__Controllers__TitleBar__constructor_Group(void *parent_);
// KDDockWidgets::Controllers::TitleBar::closeButtonEnabled() const
bool c_KDDockWidgets__Controllers__TitleBar__closeButtonEnabled(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::closeButtonEnabledChanged(bool arg__1)
void c_KDDockWidgets__Controllers__TitleBar__closeButtonEnabledChanged_bool(void *thisObj,
                                                                            bool arg__1);
void c_KDDockWidgets__Controllers__TitleBar__onCloseButtonEnabledChanged_bool(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::TitleBar::customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__TitleBar__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::TitleBar::event(QEvent * event)
bool c_KDDockWidgets__Controllers__TitleBar__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::TitleBar::eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__TitleBar__eventFilter_QObject_QEvent(void *thisObj,
                                                                        void *watched_,
                                                                        void *event_);
// KDDockWidgets::Controllers::TitleBar::floatButtonToolTip() const
void *c_KDDockWidgets__Controllers__TitleBar__floatButtonToolTip(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::floatButtonToolTipChanged(const QString & arg__1)
void c_KDDockWidgets__Controllers__TitleBar__floatButtonToolTipChanged_QString(void *thisObj,
                                                                               const char *arg__1_);
void c_KDDockWidgets__Controllers__TitleBar__onFloatButtonToolTipChanged_QString(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::TitleBar::floatButtonVisible() const
bool c_KDDockWidgets__Controllers__TitleBar__floatButtonVisible(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::floatButtonVisibleChanged(bool arg__1)
void c_KDDockWidgets__Controllers__TitleBar__floatButtonVisibleChanged_bool(void *thisObj,
                                                                            bool arg__1);
void c_KDDockWidgets__Controllers__TitleBar__onFloatButtonVisibleChanged_bool(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::TitleBar::group() const
void *c_KDDockWidgets__Controllers__TitleBar__group(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::hasIcon() const
bool c_KDDockWidgets__Controllers__TitleBar__hasIcon(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::iconChanged()
void c_KDDockWidgets__Controllers__TitleBar__iconChanged(void *thisObj);
void c_KDDockWidgets__Controllers__TitleBar__onIconChanged(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::TitleBar::isCloseButtonEnabled()
                     // const
bool c_KDDockWidgets__Controllers__TitleBar__isCloseButtonEnabled(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isCloseButtonVisible() const
bool c_KDDockWidgets__Controllers__TitleBar__isCloseButtonVisible(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isFloatButtonVisible() const
bool c_KDDockWidgets__Controllers__TitleBar__isFloatButtonVisible(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isFloating() const
bool c_KDDockWidgets__Controllers__TitleBar__isFloating(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isFocused() const
bool c_KDDockWidgets__Controllers__TitleBar__isFocused(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isFocusedChanged()
void c_KDDockWidgets__Controllers__TitleBar__isFocusedChanged(void *thisObj);
void c_KDDockWidgets__Controllers__TitleBar__onIsFocusedChanged(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::TitleBar::isMDI()
                     // const
bool c_KDDockWidgets__Controllers__TitleBar__isMDI(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isOverlayed() const
bool c_KDDockWidgets__Controllers__TitleBar__isOverlayed(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isWindow() const
bool c_KDDockWidgets__Controllers__TitleBar__isWindow(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::minimizeButtonChanged(bool visible, bool enabled)
void c_KDDockWidgets__Controllers__TitleBar__minimizeButtonChanged_bool_bool(void *thisObj,
                                                                             bool visible,
                                                                             bool enabled);
void c_KDDockWidgets__Controllers__TitleBar__onMinimizeButtonChanged_bool_bool(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::TitleBar::onAutoHideClicked()
void c_KDDockWidgets__Controllers__TitleBar__onAutoHideClicked(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::onCloseClicked()
void c_KDDockWidgets__Controllers__TitleBar__onCloseClicked(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::onDoubleClicked()
bool c_KDDockWidgets__Controllers__TitleBar__onDoubleClicked(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::onFloatClicked()
void c_KDDockWidgets__Controllers__TitleBar__onFloatClicked(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::onMaximizeClicked()
void c_KDDockWidgets__Controllers__TitleBar__onMaximizeClicked(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::onMinimizeClicked()
void c_KDDockWidgets__Controllers__TitleBar__onMinimizeClicked(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::setCloseButtonEnabled(bool arg__1)
void c_KDDockWidgets__Controllers__TitleBar__setCloseButtonEnabled_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controllers::TitleBar::setFloatButtonVisible(bool arg__1)
void c_KDDockWidgets__Controllers__TitleBar__setFloatButtonVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controllers::TitleBar::setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__TitleBar__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::TitleBar::setTitle(const QString & title)
void c_KDDockWidgets__Controllers__TitleBar__setTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::Controllers::TitleBar::supportsAutoHideButton() const
bool c_KDDockWidgets__Controllers__TitleBar__supportsAutoHideButton(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::supportsFloatingButton() const
bool c_KDDockWidgets__Controllers__TitleBar__supportsFloatingButton(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::supportsMaximizeButton() const
bool c_KDDockWidgets__Controllers__TitleBar__supportsMaximizeButton(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::supportsMinimizeButton() const
bool c_KDDockWidgets__Controllers__TitleBar__supportsMinimizeButton(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::tabBar() const
void *c_KDDockWidgets__Controllers__TitleBar__tabBar(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::title() const
void *c_KDDockWidgets__Controllers__TitleBar__title(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::titleBarIsFocusable() const
bool c_KDDockWidgets__Controllers__TitleBar__titleBarIsFocusable(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::titleChanged()
void c_KDDockWidgets__Controllers__TitleBar__titleChanged(void *thisObj);
void c_KDDockWidgets__Controllers__TitleBar__onTitleChanged(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::TitleBar::toggleMaximized()
void c_KDDockWidgets__Controllers__TitleBar__toggleMaximized(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__TitleBar__tr_char_char_int(const char *s, const char *c,
                                                                      int n);
// KDDockWidgets::Controllers::TitleBar::updateButtons()
void c_KDDockWidgets__Controllers__TitleBar__updateButtons(void *thisObj);
void c_KDDockWidgets__Controllers__TitleBar__destructor(void *thisObj);
void c_KDDockWidgets__Controllers__TitleBar__registerVirtualMethodCallback(void *ptr,
                                                                           void *callback,
                                                                           int methodId);
void c_KDDockWidgets__Controllers__TitleBar_Finalizer(
    void *, void *cppObj,
    void *); // KDDockWidgets::Controllers::TabBar::TabBar(KDDockWidgets::Controllers::Stack
             // * tabWidget)
void *c_KDDockWidgets__Controllers__TabBar__constructor_Stack(void *tabWidget_);
// KDDockWidgets::Controllers::TabBar::customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__TabBar__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::TabBar::dragCanStart(QPoint pressPos, QPoint pos) const
bool c_KDDockWidgets__Controllers__TabBar__dragCanStart_QPoint_QPoint(void *thisObj,
                                                                      void *pressPos_, void *pos_);
// KDDockWidgets::Controllers::TabBar::event(QEvent * event)
bool c_KDDockWidgets__Controllers__TabBar__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::TabBar::eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__TabBar__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                      void *event_);
// KDDockWidgets::Controllers::TabBar::group() const
void *c_KDDockWidgets__Controllers__TabBar__group(void *thisObj);
// KDDockWidgets::Controllers::TabBar::hasSingleDockWidget() const
bool c_KDDockWidgets__Controllers__TabBar__hasSingleDockWidget(void *thisObj);
// KDDockWidgets::Controllers::TabBar::isMDI() const
bool c_KDDockWidgets__Controllers__TabBar__isMDI(void *thisObj);
// KDDockWidgets::Controllers::TabBar::isWindow() const
bool c_KDDockWidgets__Controllers__TabBar__isWindow(void *thisObj);
// KDDockWidgets::Controllers::TabBar::moveTabTo(int from, int to)
void c_KDDockWidgets__Controllers__TabBar__moveTabTo_int_int(void *thisObj, int from, int to);
// KDDockWidgets::Controllers::TabBar::numDockWidgets() const
int c_KDDockWidgets__Controllers__TabBar__numDockWidgets(void *thisObj);
// KDDockWidgets::Controllers::TabBar::onMouseDoubleClick(QPoint localPos)
void c_KDDockWidgets__Controllers__TabBar__onMouseDoubleClick_QPoint(void *thisObj,
                                                                     void *localPos_);
// KDDockWidgets::Controllers::TabBar::onMousePress(QPoint localPos)
void c_KDDockWidgets__Controllers__TabBar__onMousePress_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::Controllers::TabBar::rectForTab(int index) const
void *c_KDDockWidgets__Controllers__TabBar__rectForTab_int(void *thisObj, int index);
// KDDockWidgets::Controllers::TabBar::setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__TabBar__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::TabBar::stack() const
void *c_KDDockWidgets__Controllers__TabBar__stack(void *thisObj);
// KDDockWidgets::Controllers::TabBar::tabsAreMovable() const
bool c_KDDockWidgets__Controllers__TabBar__tabsAreMovable(void *thisObj);
// KDDockWidgets::Controllers::TabBar::text(int index) const
void *c_KDDockWidgets__Controllers__TabBar__text_int(void *thisObj, int index);
// KDDockWidgets::Controllers::TabBar::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__TabBar__tr_char_char_int(const char *s, const char *c,
                                                                    int n);
void c_KDDockWidgets__Controllers__TabBar__destructor(void *thisObj);
void c_KDDockWidgets__Controllers__TabBar__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                         int methodId);
void c_KDDockWidgets__Controllers__TabBar_Finalizer(
    void *, void *cppObj, void *); // KDDockWidgets::Controllers::Stack::countChanged()
void c_KDDockWidgets__Controllers__Stack__countChanged(void *thisObj);
void c_KDDockWidgets__Controllers__Stack__onCountChanged(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::Stack::currentIndex()
                     // const
int c_KDDockWidgets__Controllers__Stack__currentIndex(void *thisObj);
// KDDockWidgets::Controllers::Stack::currentTabChanged(int index)
void c_KDDockWidgets__Controllers__Stack__currentTabChanged_int(void *thisObj, int index);
void c_KDDockWidgets__Controllers__Stack__onCurrentTabChanged_int(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::Stack::customEvent(QEvent
                     // * event)
void c_KDDockWidgets__Controllers__Stack__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::Stack::event(QEvent * event)
bool c_KDDockWidgets__Controllers__Stack__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::Stack::eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__Stack__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                     void *event_);
// KDDockWidgets::Controllers::Stack::group() const
void *c_KDDockWidgets__Controllers__Stack__group(void *thisObj);
// KDDockWidgets::Controllers::Stack::isMDI() const
bool c_KDDockWidgets__Controllers__Stack__isMDI(void *thisObj);
// KDDockWidgets::Controllers::Stack::isPositionDraggable(QPoint p) const
bool c_KDDockWidgets__Controllers__Stack__isPositionDraggable_QPoint(void *thisObj, void *p_);
// KDDockWidgets::Controllers::Stack::isWindow() const
bool c_KDDockWidgets__Controllers__Stack__isWindow(void *thisObj);
// KDDockWidgets::Controllers::Stack::numDockWidgets() const
int c_KDDockWidgets__Controllers__Stack__numDockWidgets(void *thisObj);
// KDDockWidgets::Controllers::Stack::onCurrentTabChanged(int index)
void c_KDDockWidgets__Controllers__Stack__onCurrentTabChanged_int(void *thisObj, int index);
// KDDockWidgets::Controllers::Stack::onMouseDoubleClick(QPoint localPos)
bool c_KDDockWidgets__Controllers__Stack__onMouseDoubleClick_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::Controllers::Stack::onTabInserted()
void c_KDDockWidgets__Controllers__Stack__onTabInserted(void *thisObj);
// KDDockWidgets::Controllers::Stack::onTabRemoved()
void c_KDDockWidgets__Controllers__Stack__onTabRemoved(void *thisObj);
// KDDockWidgets::Controllers::Stack::renameTab(int index, const QString & arg__2)
void c_KDDockWidgets__Controllers__Stack__renameTab_int_QString(void *thisObj, int index,
                                                                const char *arg__2_);
// KDDockWidgets::Controllers::Stack::setCurrentDockWidget(int index)
void c_KDDockWidgets__Controllers__Stack__setCurrentDockWidget_int(void *thisObj, int index);
// KDDockWidgets::Controllers::Stack::setDocumentMode(bool arg__1)
void c_KDDockWidgets__Controllers__Stack__setDocumentMode_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controllers::Stack::setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__Stack__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::Stack::setTabBarAutoHide(bool arg__1)
void c_KDDockWidgets__Controllers__Stack__setTabBarAutoHide_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controllers::Stack::tabBar() const
void *c_KDDockWidgets__Controllers__Stack__tabBar(void *thisObj);
// KDDockWidgets::Controllers::Stack::tabBarAutoHide() const
bool c_KDDockWidgets__Controllers__Stack__tabBarAutoHide(void *thisObj);
// KDDockWidgets::Controllers::Stack::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__Stack__tr_char_char_int(const char *s, const char *c,
                                                                   int n);
void c_KDDockWidgets__Controllers__Stack__destructor(void *thisObj);
void c_KDDockWidgets__Controllers__Stack__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                        int methodId);
void c_KDDockWidgets__Controllers__Stack_Finalizer(
    void *, void *cppObj,
    void *); // KDDockWidgets::Controllers::Layout::Layout(KDDockWidgets::Type
             // arg__1, KDDockWidgets::View * arg__2)
void *c_KDDockWidgets__Controllers__Layout__constructor_Type_View(int arg__1, void *arg__2_);
// KDDockWidgets::Controllers::Layout::asDropArea() const
void *c_KDDockWidgets__Controllers__Layout__asDropArea(void *thisObj);
// KDDockWidgets::Controllers::Layout::checkSanity() const
bool c_KDDockWidgets__Controllers__Layout__checkSanity(void *thisObj);
// KDDockWidgets::Controllers::Layout::clearLayout()
void c_KDDockWidgets__Controllers__Layout__clearLayout(void *thisObj);
// KDDockWidgets::Controllers::Layout::containsFrame(const KDDockWidgets::Controllers::Group *
// arg__1) const
bool c_KDDockWidgets__Controllers__Layout__containsFrame_Group(void *thisObj, void *arg__1_);
// KDDockWidgets::Controllers::Layout::containsItem(const Layouting::Item * arg__1) const
bool c_KDDockWidgets__Controllers__Layout__containsItem_Item(void *thisObj, void *arg__1_);
// KDDockWidgets::Controllers::Layout::count() const
int c_KDDockWidgets__Controllers__Layout__count(void *thisObj);
// KDDockWidgets::Controllers::Layout::customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__Layout__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::Layout::dumpLayout() const
void c_KDDockWidgets__Controllers__Layout__dumpLayout(void *thisObj);
// KDDockWidgets::Controllers::Layout::event(QEvent * event)
bool c_KDDockWidgets__Controllers__Layout__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::Layout::eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__Layout__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                      void *event_);
// KDDockWidgets::Controllers::Layout::groups() const
void *c_KDDockWidgets__Controllers__Layout__groups(void *thisObj);
// KDDockWidgets::Controllers::Layout::groupsFrom(KDDockWidgets::View * groupOrMultiSplitter) const
void *c_KDDockWidgets__Controllers__Layout__groupsFrom_View(void *thisObj,
                                                            void *groupOrMultiSplitter_);
// KDDockWidgets::Controllers::Layout::isInMainWindow(bool honourNesting) const
bool c_KDDockWidgets__Controllers__Layout__isInMainWindow_bool(void *thisObj, bool honourNesting);
// KDDockWidgets::Controllers::Layout::itemForFrame(const KDDockWidgets::Controllers::Group * group)
// const
void *c_KDDockWidgets__Controllers__Layout__itemForFrame_Group(void *thisObj, void *group_);
// KDDockWidgets::Controllers::Layout::layoutHeight() const
int c_KDDockWidgets__Controllers__Layout__layoutHeight(void *thisObj);
// KDDockWidgets::Controllers::Layout::layoutMaximumSizeHint() const
void *c_KDDockWidgets__Controllers__Layout__layoutMaximumSizeHint(void *thisObj);
// KDDockWidgets::Controllers::Layout::layoutMinimumSize() const
void *c_KDDockWidgets__Controllers__Layout__layoutMinimumSize(void *thisObj);
// KDDockWidgets::Controllers::Layout::layoutSize() const
void *c_KDDockWidgets__Controllers__Layout__layoutSize(void *thisObj);
// KDDockWidgets::Controllers::Layout::layoutWidth() const
int c_KDDockWidgets__Controllers__Layout__layoutWidth(void *thisObj);
// KDDockWidgets::Controllers::Layout::placeholderCount() const
int c_KDDockWidgets__Controllers__Layout__placeholderCount(void *thisObj);
// KDDockWidgets::Controllers::Layout::removeItem(Layouting::Item * item)
void c_KDDockWidgets__Controllers__Layout__removeItem_Item(void *thisObj, void *item_);
// KDDockWidgets::Controllers::Layout::setLayoutMinimumSize(QSize arg__1)
void c_KDDockWidgets__Controllers__Layout__setLayoutMinimumSize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Controllers::Layout::setLayoutSize(QSize arg__1)
void c_KDDockWidgets__Controllers__Layout__setLayoutSize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Controllers::Layout::setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__Layout__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::Layout::unrefOldPlaceholders(const
// QList<KDDockWidgets::Controllers::Group* > & groupsBeingAdded) const
void c_KDDockWidgets__Controllers__Layout__unrefOldPlaceholders_QList_Group(
    void *thisObj, void *groupsBeingAdded_);
// KDDockWidgets::Controllers::Layout::updateSizeConstraints()
void c_KDDockWidgets__Controllers__Layout__updateSizeConstraints(void *thisObj);
// KDDockWidgets::Controllers::Layout::viewAboutToBeDeleted()
void c_KDDockWidgets__Controllers__Layout__viewAboutToBeDeleted(void *thisObj);
// KDDockWidgets::Controllers::Layout::visibleCount() const
int c_KDDockWidgets__Controllers__Layout__visibleCount(void *thisObj);
void c_KDDockWidgets__Controllers__Layout__destructor(void *thisObj);
void c_KDDockWidgets__Controllers__Layout__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                         int methodId);
void c_KDDockWidgets__Controllers__Layout_Finalizer(
    void *, void *cppObj,
    void *); // KDDockWidgets::Controllers::DropArea::DropArea(KDDockWidgets::View
             // * parent,
             // QFlags<KDDockWidgets::MainWindowOption>
             // options, bool isMDIWrapper)
void *c_KDDockWidgets__Controllers__DropArea__constructor_View_MainWindowOptions_bool(
    void *parent_, int options_, bool isMDIWrapper);
// KDDockWidgets::Controllers::DropArea::addMultiSplitter(KDDockWidgets::Controllers::DropArea *
// splitter, KDDockWidgets::Location location, KDDockWidgets::Controllers::Group * relativeTo,
// KDDockWidgets::InitialOption option)
void c_KDDockWidgets__Controllers__DropArea__addMultiSplitter_DropArea_Location_Group_InitialOption(
    void *thisObj, void *splitter_, int location, void *relativeTo_, void *option_);
// KDDockWidgets::Controllers::DropArea::addWidget(KDDockWidgets::View * widget,
// KDDockWidgets::Location location, KDDockWidgets::Controllers::Group * relativeTo,
// KDDockWidgets::InitialOption option)
void c_KDDockWidgets__Controllers__DropArea__addWidget_View_Location_Group_InitialOption(
    void *thisObj, void *widget_, int location, void *relativeTo_, void *option_);
// KDDockWidgets::Controllers::DropArea::centralFrame() const
void *c_KDDockWidgets__Controllers__DropArea__centralFrame(void *thisObj);
// KDDockWidgets::Controllers::DropArea::createCentralFrame(QFlags<KDDockWidgets::MainWindowOption>
// options)
void *
c_static_KDDockWidgets__Controllers__DropArea__createCentralFrame_MainWindowOptions(int options_);
// KDDockWidgets::Controllers::DropArea::customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__DropArea__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::DropArea::event(QEvent * event)
bool c_KDDockWidgets__Controllers__DropArea__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::DropArea::eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__DropArea__eventFilter_QObject_QEvent(void *thisObj,
                                                                        void *watched_,
                                                                        void *event_);
// KDDockWidgets::Controllers::DropArea::groups() const
void *c_KDDockWidgets__Controllers__DropArea__groups(void *thisObj);
// KDDockWidgets::Controllers::DropArea::hasSingleFloatingFrame() const
bool c_KDDockWidgets__Controllers__DropArea__hasSingleFloatingFrame(void *thisObj);
// KDDockWidgets::Controllers::DropArea::hasSingleFrame() const
bool c_KDDockWidgets__Controllers__DropArea__hasSingleFrame(void *thisObj);
// KDDockWidgets::Controllers::DropArea::isMDIWrapper() const
bool c_KDDockWidgets__Controllers__DropArea__isMDIWrapper(void *thisObj);
// KDDockWidgets::Controllers::DropArea::layoutEqually()
void c_KDDockWidgets__Controllers__DropArea__layoutEqually(void *thisObj);
// KDDockWidgets::Controllers::DropArea::removeHover()
void c_KDDockWidgets__Controllers__DropArea__removeHover(void *thisObj);
// KDDockWidgets::Controllers::DropArea::setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__DropArea__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::DropArea::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__DropArea__tr_char_char_int(const char *s, const char *c,
                                                                      int n);
void c_KDDockWidgets__Controllers__DropArea__destructor(void *thisObj);
void c_KDDockWidgets__Controllers__DropArea__registerVirtualMethodCallback(void *ptr,
                                                                           void *callback,
                                                                           int methodId);
void c_KDDockWidgets__Controllers__DropArea_Finalizer(
    void *, void *cppObj, void *); // KDDockWidgets::Controllers::Group::Group(KDDockWidgets::View
                                   // * parent)
void *c_KDDockWidgets__Controllers__Group__constructor_View(void *parent_);
// KDDockWidgets::Controllers::Group::actualTitleBar() const
void *c_KDDockWidgets__Controllers__Group__actualTitleBar(void *thisObj);
// KDDockWidgets::Controllers::Group::actualTitleBarChanged()
void c_KDDockWidgets__Controllers__Group__actualTitleBarChanged(void *thisObj);
void c_KDDockWidgets__Controllers__Group__onActualTitleBarChanged(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::Group::addTab(KDDockWidgets::Controllers::Group
                     // * arg__1, KDDockWidgets::InitialOption arg__2)
void c_KDDockWidgets__Controllers__Group__addTab_Group_InitialOption(void *thisObj, void *arg__1_,
                                                                     void *arg__2_);
// KDDockWidgets::Controllers::Group::allDockWidgetsHave(KDDockWidgets::DockWidgetOption arg__1)
// const
bool c_KDDockWidgets__Controllers__Group__allDockWidgetsHave_DockWidgetOption(void *thisObj,
                                                                              int arg__1);
// KDDockWidgets::Controllers::Group::allDockWidgetsHave(KDDockWidgets::LayoutSaverOption arg__1)
// const
bool c_KDDockWidgets__Controllers__Group__allDockWidgetsHave_LayoutSaverOption(void *thisObj,
                                                                               int arg__1);
// KDDockWidgets::Controllers::Group::alwaysShowsTabs() const
bool c_KDDockWidgets__Controllers__Group__alwaysShowsTabs(void *thisObj);
// KDDockWidgets::Controllers::Group::anyDockWidgetsHas(KDDockWidgets::DockWidgetOption arg__1)
// const
bool c_KDDockWidgets__Controllers__Group__anyDockWidgetsHas_DockWidgetOption(void *thisObj,
                                                                             int arg__1);
// KDDockWidgets::Controllers::Group::anyDockWidgetsHas(KDDockWidgets::LayoutSaverOption arg__1)
// const
bool c_KDDockWidgets__Controllers__Group__anyDockWidgetsHas_LayoutSaverOption(void *thisObj,
                                                                              int arg__1);
// KDDockWidgets::Controllers::Group::anyNonClosable() const
bool c_KDDockWidgets__Controllers__Group__anyNonClosable(void *thisObj);
// KDDockWidgets::Controllers::Group::anyNonDockable() const
bool c_KDDockWidgets__Controllers__Group__anyNonDockable(void *thisObj);
// KDDockWidgets::Controllers::Group::beingDeletedLater() const
bool c_KDDockWidgets__Controllers__Group__beingDeletedLater(void *thisObj);
// KDDockWidgets::Controllers::Group::biggestDockWidgetMaxSize() const
void *c_KDDockWidgets__Controllers__Group__biggestDockWidgetMaxSize(void *thisObj);
// KDDockWidgets::Controllers::Group::containsMouse(QPoint globalPos) const
bool c_KDDockWidgets__Controllers__Group__containsMouse_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::Controllers::Group::currentIndex() const
int c_KDDockWidgets__Controllers__Group__currentIndex(void *thisObj);
// KDDockWidgets::Controllers::Group::currentTabIndex() const
int c_KDDockWidgets__Controllers__Group__currentTabIndex(void *thisObj);
// KDDockWidgets::Controllers::Group::customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__Group__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::Group::dbg_numFrames()
int c_static_KDDockWidgets__Controllers__Group__dbg_numFrames();
// KDDockWidgets::Controllers::Group::dockWidgetCount() const
int c_KDDockWidgets__Controllers__Group__dockWidgetCount(void *thisObj);
// KDDockWidgets::Controllers::Group::dockWidgetsMinSize() const
void *c_KDDockWidgets__Controllers__Group__dockWidgetsMinSize(void *thisObj);
// KDDockWidgets::Controllers::Group::dragRect() const
void *c_KDDockWidgets__Controllers__Group__dragRect(void *thisObj);
// KDDockWidgets::Controllers::Group::event(QEvent * event)
bool c_KDDockWidgets__Controllers__Group__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::Group::eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__Group__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                     void *event_);
// KDDockWidgets::Controllers::Group::focusedWidgetChanged()
void c_KDDockWidgets__Controllers__Group__focusedWidgetChanged(void *thisObj);
void c_KDDockWidgets__Controllers__Group__onFocusedWidgetChanged(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::Group::focusedWidgetChangedCallback()
void c_KDDockWidgets__Controllers__Group__focusedWidgetChangedCallback(void *thisObj);
// KDDockWidgets::Controllers::Group::hasNestedMDIDockWidgets() const
bool c_KDDockWidgets__Controllers__Group__hasNestedMDIDockWidgets(void *thisObj);
// KDDockWidgets::Controllers::Group::hasSingleDockWidget() const
bool c_KDDockWidgets__Controllers__Group__hasSingleDockWidget(void *thisObj);
// KDDockWidgets::Controllers::Group::hasTabsVisible() const
bool c_KDDockWidgets__Controllers__Group__hasTabsVisible(void *thisObj);
// KDDockWidgets::Controllers::Group::hasTabsVisibleChanged()
void c_KDDockWidgets__Controllers__Group__hasTabsVisibleChanged(void *thisObj);
void c_KDDockWidgets__Controllers__Group__onHasTabsVisibleChanged(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::Group::isCentralFrame()
                     // const
bool c_KDDockWidgets__Controllers__Group__isCentralFrame(void *thisObj);
// KDDockWidgets::Controllers::Group::isDockable() const
bool c_KDDockWidgets__Controllers__Group__isDockable(void *thisObj);
// KDDockWidgets::Controllers::Group::isEmpty() const
bool c_KDDockWidgets__Controllers__Group__isEmpty(void *thisObj);
// KDDockWidgets::Controllers::Group::isFloating() const
bool c_KDDockWidgets__Controllers__Group__isFloating(void *thisObj);
// KDDockWidgets::Controllers::Group::isFocusedChanged()
void c_KDDockWidgets__Controllers__Group__isFocusedChanged(void *thisObj);
void c_KDDockWidgets__Controllers__Group__onIsFocusedChanged(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::Group::isFocusedChangedCallback()
void c_KDDockWidgets__Controllers__Group__isFocusedChangedCallback(void *thisObj);
// KDDockWidgets::Controllers::Group::isInFloatingWindow() const
bool c_KDDockWidgets__Controllers__Group__isInFloatingWindow(void *thisObj);
// KDDockWidgets::Controllers::Group::isInMainWindow() const
bool c_KDDockWidgets__Controllers__Group__isInMainWindow(void *thisObj);
// KDDockWidgets::Controllers::Group::isInMainWindowChanged()
void c_KDDockWidgets__Controllers__Group__isInMainWindowChanged(void *thisObj);
void c_KDDockWidgets__Controllers__Group__onIsInMainWindowChanged(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::Group::isMDI()
                     // const
bool c_KDDockWidgets__Controllers__Group__isMDI(void *thisObj);
// KDDockWidgets::Controllers::Group::isMDIChanged()
void c_KDDockWidgets__Controllers__Group__isMDIChanged(void *thisObj);
void c_KDDockWidgets__Controllers__Group__onIsMDIChanged(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::Group::isMDIWrapper()
                     // const
bool c_KDDockWidgets__Controllers__Group__isMDIWrapper(void *thisObj);
// KDDockWidgets::Controllers::Group::isOverlayed() const
bool c_KDDockWidgets__Controllers__Group__isOverlayed(void *thisObj);
// KDDockWidgets::Controllers::Group::isTheOnlyFrame() const
bool c_KDDockWidgets__Controllers__Group__isTheOnlyFrame(void *thisObj);
// KDDockWidgets::Controllers::Group::layoutItem() const
void *c_KDDockWidgets__Controllers__Group__layoutItem(void *thisObj);
// KDDockWidgets::Controllers::Group::mdiDropAreaWrapper() const
void *c_KDDockWidgets__Controllers__Group__mdiDropAreaWrapper(void *thisObj);
// KDDockWidgets::Controllers::Group::mdiFrame() const
void *c_KDDockWidgets__Controllers__Group__mdiFrame(void *thisObj);
// KDDockWidgets::Controllers::Group::nonContentsHeight() const
int c_KDDockWidgets__Controllers__Group__nonContentsHeight(void *thisObj);
// KDDockWidgets::Controllers::Group::numDockWidgetsChanged()
void c_KDDockWidgets__Controllers__Group__numDockWidgetsChanged(void *thisObj);
void c_KDDockWidgets__Controllers__Group__onNumDockWidgetsChanged(
    void *thisObj, void *contextQObject,
    void *callback); // KDDockWidgets::Controllers::Group::onCurrentTabChanged(int
                     // index)
void c_KDDockWidgets__Controllers__Group__onCurrentTabChanged_int(void *thisObj, int index);
// KDDockWidgets::Controllers::Group::onDockWidgetCountChanged()
void c_KDDockWidgets__Controllers__Group__onDockWidgetCountChanged(void *thisObj);
// KDDockWidgets::Controllers::Group::onDockWidgetTitleChanged()
void c_KDDockWidgets__Controllers__Group__onDockWidgetTitleChanged(void *thisObj);
// KDDockWidgets::Controllers::Group::renameTab(int index, const QString & arg__2)
void c_KDDockWidgets__Controllers__Group__renameTab_int_QString(void *thisObj, int index,
                                                                const char *arg__2_);
// KDDockWidgets::Controllers::Group::restoreToPreviousPosition()
void c_KDDockWidgets__Controllers__Group__restoreToPreviousPosition(void *thisObj);
// KDDockWidgets::Controllers::Group::setCurrentTabIndex(int index)
void c_KDDockWidgets__Controllers__Group__setCurrentTabIndex_int(void *thisObj, int index);
// KDDockWidgets::Controllers::Group::setLayout(KDDockWidgets::Controllers::Layout * arg__1)
void c_KDDockWidgets__Controllers__Group__setLayout_Layout(void *thisObj, void *arg__1_);
// KDDockWidgets::Controllers::Group::setLayoutItem(Layouting::Item * item)
void c_KDDockWidgets__Controllers__Group__setLayoutItem_Item(void *thisObj, void *item_);
// KDDockWidgets::Controllers::Group::setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__Group__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::Group::stack() const
void *c_KDDockWidgets__Controllers__Group__stack(void *thisObj);
// KDDockWidgets::Controllers::Group::tabBar() const
void *c_KDDockWidgets__Controllers__Group__tabBar(void *thisObj);
// KDDockWidgets::Controllers::Group::title() const
void *c_KDDockWidgets__Controllers__Group__title(void *thisObj);
// KDDockWidgets::Controllers::Group::titleBar() const
void *c_KDDockWidgets__Controllers__Group__titleBar(void *thisObj);
// KDDockWidgets::Controllers::Group::tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__Group__tr_char_char_int(const char *s, const char *c,
                                                                   int n);
// KDDockWidgets::Controllers::Group::unoverlay()
void c_KDDockWidgets__Controllers__Group__unoverlay(void *thisObj);
// KDDockWidgets::Controllers::Group::updateFloatingActions()
void c_KDDockWidgets__Controllers__Group__updateFloatingActions(void *thisObj);
// KDDockWidgets::Controllers::Group::updateTitleAndIcon()
void c_KDDockWidgets__Controllers__Group__updateTitleAndIcon(void *thisObj);
// KDDockWidgets::Controllers::Group::updateTitleBarVisibility()
void c_KDDockWidgets__Controllers__Group__updateTitleBarVisibility(void *thisObj);
// KDDockWidgets::Controllers::Group::userType() const
int c_KDDockWidgets__Controllers__Group__userType(void *thisObj);
void c_KDDockWidgets__Controllers__Group__destructor(void *thisObj);
void c_KDDockWidgets__Controllers__Group__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                        int methodId);
void c_KDDockWidgets__Controllers__Group_Finalizer(
    void *, void *cppObj, void *); // KDDockWidgets::Config::absoluteWidgetMaxSize()
                                   // const
void *c_KDDockWidgets__Config__absoluteWidgetMaxSize(void *thisObj);
// KDDockWidgets::Config::absoluteWidgetMinSize() const
void *c_KDDockWidgets__Config__absoluteWidgetMinSize(void *thisObj);
// KDDockWidgets::Config::draggedWindowOpacity() const
qreal c_KDDockWidgets__Config__draggedWindowOpacity(void *thisObj);
// KDDockWidgets::Config::dropIndicatorsInhibited() const
bool c_KDDockWidgets__Config__dropIndicatorsInhibited(void *thisObj);
// KDDockWidgets::Config::mdiPopupThreshold() const
int c_KDDockWidgets__Config__mdiPopupThreshold(void *thisObj);
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
// KDDockWidgets::Config::setViewFactory(KDDockWidgets::ViewFactory * arg__1)
void c_KDDockWidgets__Config__setViewFactory_ViewFactory(void *thisObj, void *arg__1_);
// KDDockWidgets::Config::startDragDistance() const
int c_KDDockWidgets__Config__startDragDistance(void *thisObj);
// KDDockWidgets::Config::viewFactory() const
void *c_KDDockWidgets__Config__viewFactory(void *thisObj);
void c_KDDockWidgets__Config__destructor(void *thisObj);
void c_KDDockWidgets__Config_Finalizer(void *, void *cppObj, void *);
