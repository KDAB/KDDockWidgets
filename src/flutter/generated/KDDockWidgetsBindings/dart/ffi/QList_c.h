/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <qlist.h>
#include <qstring.h>
#include <qbytearray.h>
#include <qobject.h>
#include <core/DockWidget.h>
#include <core/View.h>
#include <KDDockWidgets.h>
#include <FloatingWindow.h>
#include <qrect.h>
#include "core/TitleBar.h"
#include "core/MainWindow.h"
#include <qsize.h>
#include <qpoint.h>
#include <core/Group.h>
#include "core/DropArea.h"
#include <core/Layout.h>
#include "core/Stack.h"
#include <TabBar.h>
#include <Item_p.h>
#include <SideBar.h>
#include <Separator.h>

namespace KDDockWidgetsBindings_wrappersNS {
template<typename T>
class QList_wrapper : public ::QList<T>
{
public:
    ~QList_wrapper();
    QList_wrapper();
    QList_wrapper(qsizetype size);
    void append(const QList<T> &l);
    const T &at(qsizetype i) const;
    T &back();
    qsizetype capacity() const;
    void clear();
    const T &constFirst() const;
    const T &constLast() const;
    qsizetype count() const;
    void detach();
    bool empty() const;
    T &first();
    QList<T> first(qsizetype n) const;
    T &front();
    bool isDetached() const;
    bool isEmpty() const;
    bool isSharedWith(const QList<T> &other) const;
    T &last();
    QList<T> last(qsizetype n) const;
    qsizetype length() const;
    QList<T> mid(qsizetype pos, qsizetype len = -1) const;
    void move(qsizetype from, qsizetype to);
    void pop_back();
    void pop_front();
    void remove(qsizetype i, qsizetype n = 1);
    void removeAt(qsizetype i);
    void removeFirst();
    void removeLast();
    void reserve(qsizetype size);
    void resize(qsizetype size);
    void shrink_to_fit();
    qsizetype size() const;
    QList<T> sliced(qsizetype pos) const;
    QList<T> sliced(qsizetype pos, qsizetype n) const;
    void squeeze();
    void swapItemsAt(qsizetype i, qsizetype j);
    T takeAt(qsizetype i);
    QList<T> toList() const;
    QList<T> toVector() const;
    T value(qsizetype i) const;
};
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___constructor();
// QList::QList<T>(qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___constructor_qsizetype(qsizetype size);
// QList::append(const QList<T > & l)
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___append_QList_T(void *thisObj, void *l_);
// QList::at(qsizetype i) const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QString_T___at_qsizetype(void *thisObj, qsizetype i);
// QList::back()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___back(void *thisObj);
// QList::capacity() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_QString_T___capacity(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QString_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QString_T___constLast(void *thisObj);
// QList::count() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_QString_T___count(void *thisObj);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___detach(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QString_T___empty(void *thisObj);
// QList::first()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___first(void *thisObj);
// QList::first(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___first_qsizetype(void *thisObj, qsizetype n);
// QList::front()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___front(void *thisObj);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QString_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QString_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QString_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___last(void *thisObj);
// QList::last(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___last_qsizetype(void *thisObj, qsizetype n);
// QList::length() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_QString_T___length(void *thisObj);
// QList::mid(qsizetype pos, qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len);
// QList::move(qsizetype from, qsizetype to)
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___pop_front(void *thisObj);
// QList::remove(qsizetype i, qsizetype n)
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n);
// QList::removeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___removeAt_qsizetype(void *thisObj, qsizetype i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___removeLast(void *thisObj);
// QList::reserve(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___reserve_qsizetype(void *thisObj, qsizetype size);
// QList::resize(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___resize_qsizetype(void *thisObj, qsizetype size);
// QList::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___shrink_to_fit(void *thisObj);
// QList::size() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_QString_T___size(void *thisObj);
// QList::sliced(qsizetype pos) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___sliced_qsizetype(void *thisObj, qsizetype pos);
// QList::sliced(qsizetype pos, qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n);
// QList::squeeze()
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___squeeze(void *thisObj);
// QList::swapItemsAt(qsizetype i, qsizetype j)
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j);
// QList::takeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___takeAt_qsizetype(void *thisObj, qsizetype i);
// QList::toList() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___toList(void *thisObj);
// QList::toVector() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___toVector(void *thisObj);
// QList::value(qsizetype i) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QString_T___value_qsizetype(void *thisObj, qsizetype i);
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_QString_T__Finalizer(void *cppObj);
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_unsigned_int_T___constructor();
// QList::QList<T>(qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_QList_T_unsigned_int_T___constructor_qsizetype(qsizetype size);
// QList::append(const QList<T > & l)
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___append_QList_T(void *thisObj, void *l_);
// QList::at(qsizetype i) const
KDDockWidgetsBindings_EXPORT const unsigned int c_QList_T_unsigned_int_T___at_qsizetype(void *thisObj, qsizetype i);
// QList::back()
KDDockWidgetsBindings_EXPORT unsigned int c_QList_T_unsigned_int_T___back(void *thisObj);
// QList::capacity() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_unsigned_int_T___capacity(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const unsigned int c_QList_T_unsigned_int_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const unsigned int c_QList_T_unsigned_int_T___constLast(void *thisObj);
// QList::count() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_unsigned_int_T___count(void *thisObj);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___detach(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_unsigned_int_T___empty(void *thisObj);
// QList::first()
KDDockWidgetsBindings_EXPORT unsigned int c_QList_T_unsigned_int_T___first(void *thisObj);
// QList::first(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_unsigned_int_T___first_qsizetype(void *thisObj, qsizetype n);
// QList::front()
KDDockWidgetsBindings_EXPORT unsigned int c_QList_T_unsigned_int_T___front(void *thisObj);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_unsigned_int_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_unsigned_int_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_unsigned_int_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT unsigned int c_QList_T_unsigned_int_T___last(void *thisObj);
// QList::last(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_unsigned_int_T___last_qsizetype(void *thisObj, qsizetype n);
// QList::length() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_unsigned_int_T___length(void *thisObj);
// QList::mid(qsizetype pos, qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_unsigned_int_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len);
// QList::move(qsizetype from, qsizetype to)
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___pop_front(void *thisObj);
// QList::remove(qsizetype i, qsizetype n)
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n);
// QList::removeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___removeAt_qsizetype(void *thisObj, qsizetype i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___removeLast(void *thisObj);
// QList::reserve(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___reserve_qsizetype(void *thisObj, qsizetype size);
// QList::resize(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___resize_qsizetype(void *thisObj, qsizetype size);
// QList::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___shrink_to_fit(void *thisObj);
// QList::size() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_unsigned_int_T___size(void *thisObj);
// QList::sliced(qsizetype pos) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_unsigned_int_T___sliced_qsizetype(void *thisObj, qsizetype pos);
// QList::sliced(qsizetype pos, qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_unsigned_int_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n);
// QList::squeeze()
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___squeeze(void *thisObj);
// QList::swapItemsAt(qsizetype i, qsizetype j)
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j);
// QList::takeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT unsigned int c_QList_T_unsigned_int_T___takeAt_qsizetype(void *thisObj, qsizetype i);
// QList::toList() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_unsigned_int_T___toList(void *thisObj);
// QList::toVector() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_unsigned_int_T___toVector(void *thisObj);
// QList::value(qsizetype i) const
KDDockWidgetsBindings_EXPORT unsigned int c_QList_T_unsigned_int_T___value_qsizetype(void *thisObj, qsizetype i);
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_unsigned_int_T__Finalizer(void *cppObj);
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___constructor();
// QList::QList<T>(qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___constructor_qsizetype(qsizetype size);
// QList::append(const QList<T > & l)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___append_QList_T(void *thisObj, void *l_);
// QList::at(qsizetype i) const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QObject_T___at_qsizetype(void *thisObj, qsizetype i);
// QList::back()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___back(void *thisObj);
// QList::capacity() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_QObject_T___capacity(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QObject_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QObject_T___constLast(void *thisObj);
// QList::count() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_QObject_T___count(void *thisObj);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___detach(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QObject_T___empty(void *thisObj);
// QList::first()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___first(void *thisObj);
// QList::first(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___first_qsizetype(void *thisObj, qsizetype n);
// QList::front()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___front(void *thisObj);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QObject_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QObject_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QObject_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___last(void *thisObj);
// QList::last(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___last_qsizetype(void *thisObj, qsizetype n);
// QList::length() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_QObject_T___length(void *thisObj);
// QList::mid(qsizetype pos, qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len);
// QList::move(qsizetype from, qsizetype to)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___pop_front(void *thisObj);
// QList::remove(qsizetype i, qsizetype n)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n);
// QList::removeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___removeAt_qsizetype(void *thisObj, qsizetype i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___removeLast(void *thisObj);
// QList::reserve(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___reserve_qsizetype(void *thisObj, qsizetype size);
// QList::resize(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___resize_qsizetype(void *thisObj, qsizetype size);
// QList::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___shrink_to_fit(void *thisObj);
// QList::size() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_QObject_T___size(void *thisObj);
// QList::sliced(qsizetype pos) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___sliced_qsizetype(void *thisObj, qsizetype pos);
// QList::sliced(qsizetype pos, qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n);
// QList::squeeze()
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___squeeze(void *thisObj);
// QList::swapItemsAt(qsizetype i, qsizetype j)
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j);
// QList::takeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___takeAt_qsizetype(void *thisObj, qsizetype i);
// QList::toList() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___toList(void *thisObj);
// QList::toVector() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___toVector(void *thisObj);
// QList::value(qsizetype i) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QObject_T___value_qsizetype(void *thisObj, qsizetype i);
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_QObject_T__Finalizer(void *cppObj);
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___constructor();
// QList::QList<T>(qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___constructor_qsizetype(qsizetype size);
// QList::append(const QList<T > & l)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___append_QList_T(void *thisObj, void *l_);
// QList::at(qsizetype i) const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QByteArray_T___at_qsizetype(void *thisObj, qsizetype i);
// QList::back()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___back(void *thisObj);
// QList::capacity() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_QByteArray_T___capacity(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QByteArray_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_QByteArray_T___constLast(void *thisObj);
// QList::count() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_QByteArray_T___count(void *thisObj);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___detach(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QByteArray_T___empty(void *thisObj);
// QList::first()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___first(void *thisObj);
// QList::first(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___first_qsizetype(void *thisObj, qsizetype n);
// QList::front()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___front(void *thisObj);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QByteArray_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QByteArray_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_QByteArray_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___last(void *thisObj);
// QList::last(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___last_qsizetype(void *thisObj, qsizetype n);
// QList::length() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_QByteArray_T___length(void *thisObj);
// QList::mid(qsizetype pos, qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len);
// QList::move(qsizetype from, qsizetype to)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___pop_front(void *thisObj);
// QList::remove(qsizetype i, qsizetype n)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n);
// QList::removeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___removeAt_qsizetype(void *thisObj, qsizetype i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___removeLast(void *thisObj);
// QList::reserve(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___reserve_qsizetype(void *thisObj, qsizetype size);
// QList::resize(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___resize_qsizetype(void *thisObj, qsizetype size);
// QList::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___shrink_to_fit(void *thisObj);
// QList::size() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_QByteArray_T___size(void *thisObj);
// QList::sliced(qsizetype pos) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___sliced_qsizetype(void *thisObj, qsizetype pos);
// QList::sliced(qsizetype pos, qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n);
// QList::squeeze()
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___squeeze(void *thisObj);
// QList::swapItemsAt(qsizetype i, qsizetype j)
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j);
// QList::takeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___takeAt_qsizetype(void *thisObj, qsizetype i);
// QList::toList() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___toList(void *thisObj);
// QList::toVector() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___toVector(void *thisObj);
// QList::value(qsizetype i) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_QByteArray_T___value_qsizetype(void *thisObj, qsizetype i);
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_QByteArray_T__Finalizer(void *cppObj);
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___constructor();
// QList::QList<T>(qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___constructor_qsizetype(qsizetype size);
// QList::append(const QList<T > & l)
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___append_QList_T(void *thisObj, void *l_);
// QList::at(qsizetype i) const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_DockWidget_T___at_qsizetype(void *thisObj, qsizetype i);
// QList::back()
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___back(void *thisObj);
// QList::capacity() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_DockWidget_T___capacity(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_DockWidget_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_DockWidget_T___constLast(void *thisObj);
// QList::count() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_DockWidget_T___count(void *thisObj);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___detach(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_DockWidget_T___empty(void *thisObj);
// QList::first()
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___first(void *thisObj);
// QList::first(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___first_qsizetype(void *thisObj, qsizetype n);
// QList::front()
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___front(void *thisObj);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_DockWidget_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_DockWidget_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_DockWidget_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___last(void *thisObj);
// QList::last(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___last_qsizetype(void *thisObj, qsizetype n);
// QList::length() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_DockWidget_T___length(void *thisObj);
// QList::mid(qsizetype pos, qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len);
// QList::move(qsizetype from, qsizetype to)
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___pop_front(void *thisObj);
// QList::remove(qsizetype i, qsizetype n)
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n);
// QList::removeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___removeAt_qsizetype(void *thisObj, qsizetype i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___removeLast(void *thisObj);
// QList::reserve(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___reserve_qsizetype(void *thisObj, qsizetype size);
// QList::resize(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___resize_qsizetype(void *thisObj, qsizetype size);
// QList::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___shrink_to_fit(void *thisObj);
// QList::size() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_DockWidget_T___size(void *thisObj);
// QList::sliced(qsizetype pos) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___sliced_qsizetype(void *thisObj, qsizetype pos);
// QList::sliced(qsizetype pos, qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n);
// QList::squeeze()
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___squeeze(void *thisObj);
// QList::swapItemsAt(qsizetype i, qsizetype j)
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j);
// QList::takeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___takeAt_qsizetype(void *thisObj, qsizetype i);
// QList::toList() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___toList(void *thisObj);
// QList::toVector() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___toVector(void *thisObj);
// QList::value(qsizetype i) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_DockWidget_T___value_qsizetype(void *thisObj, qsizetype i);
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_DockWidget_T__Finalizer(void *cppObj);
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___constructor();
// QList::QList<T>(qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___constructor_qsizetype(qsizetype size);
// QList::append(const QList<T > & l)
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___append_QList_T(void *thisObj, void *l_);
// QList::at(qsizetype i) const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_FloatingWindow_T___at_qsizetype(void *thisObj, qsizetype i);
// QList::back()
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___back(void *thisObj);
// QList::capacity() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_FloatingWindow_T___capacity(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_FloatingWindow_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_FloatingWindow_T___constLast(void *thisObj);
// QList::count() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_FloatingWindow_T___count(void *thisObj);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___detach(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_FloatingWindow_T___empty(void *thisObj);
// QList::first()
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___first(void *thisObj);
// QList::first(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___first_qsizetype(void *thisObj, qsizetype n);
// QList::front()
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___front(void *thisObj);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_FloatingWindow_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_FloatingWindow_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_FloatingWindow_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___last(void *thisObj);
// QList::last(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___last_qsizetype(void *thisObj, qsizetype n);
// QList::length() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_FloatingWindow_T___length(void *thisObj);
// QList::mid(qsizetype pos, qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len);
// QList::move(qsizetype from, qsizetype to)
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___pop_front(void *thisObj);
// QList::remove(qsizetype i, qsizetype n)
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n);
// QList::removeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___removeAt_qsizetype(void *thisObj, qsizetype i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___removeLast(void *thisObj);
// QList::reserve(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___reserve_qsizetype(void *thisObj, qsizetype size);
// QList::resize(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___resize_qsizetype(void *thisObj, qsizetype size);
// QList::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___shrink_to_fit(void *thisObj);
// QList::size() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_FloatingWindow_T___size(void *thisObj);
// QList::sliced(qsizetype pos) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___sliced_qsizetype(void *thisObj, qsizetype pos);
// QList::sliced(qsizetype pos, qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n);
// QList::squeeze()
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___squeeze(void *thisObj);
// QList::swapItemsAt(qsizetype i, qsizetype j)
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j);
// QList::takeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___takeAt_qsizetype(void *thisObj, qsizetype i);
// QList::toList() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___toList(void *thisObj);
// QList::toVector() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___toVector(void *thisObj);
// QList::value(qsizetype i) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_FloatingWindow_T___value_qsizetype(void *thisObj, qsizetype i);
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_FloatingWindow_T__Finalizer(void *cppObj);
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___constructor();
// QList::QList<T>(qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___constructor_qsizetype(qsizetype size);
// QList::append(const QList<T > & l)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___append_QList_T(void *thisObj, void *l_);
// QList::at(qsizetype i) const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Group_T___at_qsizetype(void *thisObj, qsizetype i);
// QList::back()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___back(void *thisObj);
// QList::capacity() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Group_T___capacity(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Group_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Group_T___constLast(void *thisObj);
// QList::count() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Group_T___count(void *thisObj);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___detach(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Group_T___empty(void *thisObj);
// QList::first()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___first(void *thisObj);
// QList::first(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___first_qsizetype(void *thisObj, qsizetype n);
// QList::front()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___front(void *thisObj);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Group_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Group_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Group_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___last(void *thisObj);
// QList::last(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___last_qsizetype(void *thisObj, qsizetype n);
// QList::length() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Group_T___length(void *thisObj);
// QList::mid(qsizetype pos, qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len);
// QList::move(qsizetype from, qsizetype to)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___pop_front(void *thisObj);
// QList::remove(qsizetype i, qsizetype n)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n);
// QList::removeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___removeAt_qsizetype(void *thisObj, qsizetype i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___removeLast(void *thisObj);
// QList::reserve(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___reserve_qsizetype(void *thisObj, qsizetype size);
// QList::resize(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___resize_qsizetype(void *thisObj, qsizetype size);
// QList::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___shrink_to_fit(void *thisObj);
// QList::size() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Group_T___size(void *thisObj);
// QList::sliced(qsizetype pos) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___sliced_qsizetype(void *thisObj, qsizetype pos);
// QList::sliced(qsizetype pos, qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n);
// QList::squeeze()
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___squeeze(void *thisObj);
// QList::swapItemsAt(qsizetype i, qsizetype j)
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j);
// QList::takeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___takeAt_qsizetype(void *thisObj, qsizetype i);
// QList::toList() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___toList(void *thisObj);
// QList::toVector() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___toVector(void *thisObj);
// QList::value(qsizetype i) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Group_T___value_qsizetype(void *thisObj, qsizetype i);
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_Group_T__Finalizer(void *cppObj);
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___constructor();
// QList::QList<T>(qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___constructor_qsizetype(qsizetype size);
// QList::append(const QList<T > & l)
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___append_QList_T(void *thisObj, void *l_);
// QList::at(qsizetype i) const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Layout_T___at_qsizetype(void *thisObj, qsizetype i);
// QList::back()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___back(void *thisObj);
// QList::capacity() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Layout_T___capacity(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Layout_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Layout_T___constLast(void *thisObj);
// QList::count() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Layout_T___count(void *thisObj);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___detach(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Layout_T___empty(void *thisObj);
// QList::first()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___first(void *thisObj);
// QList::first(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___first_qsizetype(void *thisObj, qsizetype n);
// QList::front()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___front(void *thisObj);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Layout_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Layout_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Layout_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___last(void *thisObj);
// QList::last(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___last_qsizetype(void *thisObj, qsizetype n);
// QList::length() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Layout_T___length(void *thisObj);
// QList::mid(qsizetype pos, qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len);
// QList::move(qsizetype from, qsizetype to)
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___pop_front(void *thisObj);
// QList::remove(qsizetype i, qsizetype n)
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n);
// QList::removeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___removeAt_qsizetype(void *thisObj, qsizetype i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___removeLast(void *thisObj);
// QList::reserve(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___reserve_qsizetype(void *thisObj, qsizetype size);
// QList::resize(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___resize_qsizetype(void *thisObj, qsizetype size);
// QList::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___shrink_to_fit(void *thisObj);
// QList::size() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Layout_T___size(void *thisObj);
// QList::sliced(qsizetype pos) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___sliced_qsizetype(void *thisObj, qsizetype pos);
// QList::sliced(qsizetype pos, qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n);
// QList::squeeze()
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___squeeze(void *thisObj);
// QList::swapItemsAt(qsizetype i, qsizetype j)
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j);
// QList::takeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___takeAt_qsizetype(void *thisObj, qsizetype i);
// QList::toList() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___toList(void *thisObj);
// QList::toVector() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___toVector(void *thisObj);
// QList::value(qsizetype i) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Layout_T___value_qsizetype(void *thisObj, qsizetype i);
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_Layout_T__Finalizer(void *cppObj);
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___constructor();
// QList::QList<T>(qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___constructor_qsizetype(qsizetype size);
// QList::append(const QList<T > & l)
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___append_QList_T(void *thisObj, void *l_);
// QList::at(qsizetype i) const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_MainWindow_T___at_qsizetype(void *thisObj, qsizetype i);
// QList::back()
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___back(void *thisObj);
// QList::capacity() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_MainWindow_T___capacity(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_MainWindow_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_MainWindow_T___constLast(void *thisObj);
// QList::count() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_MainWindow_T___count(void *thisObj);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___detach(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_MainWindow_T___empty(void *thisObj);
// QList::first()
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___first(void *thisObj);
// QList::first(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___first_qsizetype(void *thisObj, qsizetype n);
// QList::front()
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___front(void *thisObj);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_MainWindow_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_MainWindow_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_MainWindow_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___last(void *thisObj);
// QList::last(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___last_qsizetype(void *thisObj, qsizetype n);
// QList::length() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_MainWindow_T___length(void *thisObj);
// QList::mid(qsizetype pos, qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len);
// QList::move(qsizetype from, qsizetype to)
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___pop_front(void *thisObj);
// QList::remove(qsizetype i, qsizetype n)
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n);
// QList::removeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___removeAt_qsizetype(void *thisObj, qsizetype i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___removeLast(void *thisObj);
// QList::reserve(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___reserve_qsizetype(void *thisObj, qsizetype size);
// QList::resize(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___resize_qsizetype(void *thisObj, qsizetype size);
// QList::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___shrink_to_fit(void *thisObj);
// QList::size() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_MainWindow_T___size(void *thisObj);
// QList::sliced(qsizetype pos) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___sliced_qsizetype(void *thisObj, qsizetype pos);
// QList::sliced(qsizetype pos, qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n);
// QList::squeeze()
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___squeeze(void *thisObj);
// QList::swapItemsAt(qsizetype i, qsizetype j)
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j);
// QList::takeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___takeAt_qsizetype(void *thisObj, qsizetype i);
// QList::toList() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___toList(void *thisObj);
// QList::toVector() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___toVector(void *thisObj);
// QList::value(qsizetype i) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_MainWindow_T___value_qsizetype(void *thisObj, qsizetype i);
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_MainWindow_T__Finalizer(void *cppObj);
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_int_T___constructor();
// QList::QList<T>(qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_QList_T_int_T___constructor_qsizetype(qsizetype size);
// QList::append(const QList<T > & l)
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___append_QList_T(void *thisObj, void *l_);
// QList::at(qsizetype i) const
KDDockWidgetsBindings_EXPORT const int c_QList_T_int_T___at_qsizetype(void *thisObj, qsizetype i);
// QList::back()
KDDockWidgetsBindings_EXPORT int c_QList_T_int_T___back(void *thisObj);
// QList::capacity() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_int_T___capacity(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const int c_QList_T_int_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const int c_QList_T_int_T___constLast(void *thisObj);
// QList::count() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_int_T___count(void *thisObj);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___detach(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_int_T___empty(void *thisObj);
// QList::first()
KDDockWidgetsBindings_EXPORT int c_QList_T_int_T___first(void *thisObj);
// QList::first(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_int_T___first_qsizetype(void *thisObj, qsizetype n);
// QList::front()
KDDockWidgetsBindings_EXPORT int c_QList_T_int_T___front(void *thisObj);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_int_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_int_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_int_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT int c_QList_T_int_T___last(void *thisObj);
// QList::last(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_int_T___last_qsizetype(void *thisObj, qsizetype n);
// QList::length() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_int_T___length(void *thisObj);
// QList::mid(qsizetype pos, qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_int_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len);
// QList::move(qsizetype from, qsizetype to)
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___pop_front(void *thisObj);
// QList::remove(qsizetype i, qsizetype n)
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n);
// QList::removeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___removeAt_qsizetype(void *thisObj, qsizetype i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___removeLast(void *thisObj);
// QList::reserve(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___reserve_qsizetype(void *thisObj, qsizetype size);
// QList::resize(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___resize_qsizetype(void *thisObj, qsizetype size);
// QList::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___shrink_to_fit(void *thisObj);
// QList::size() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_int_T___size(void *thisObj);
// QList::sliced(qsizetype pos) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_int_T___sliced_qsizetype(void *thisObj, qsizetype pos);
// QList::sliced(qsizetype pos, qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_int_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n);
// QList::squeeze()
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___squeeze(void *thisObj);
// QList::swapItemsAt(qsizetype i, qsizetype j)
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j);
// QList::takeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT int c_QList_T_int_T___takeAt_qsizetype(void *thisObj, qsizetype i);
// QList::toList() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_int_T___toList(void *thisObj);
// QList::toVector() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_int_T___toVector(void *thisObj);
// QList::value(qsizetype i) const
KDDockWidgetsBindings_EXPORT int c_QList_T_int_T___value_qsizetype(void *thisObj, qsizetype i);
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_int_T__Finalizer(void *cppObj);
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___constructor();
// QList::QList<T>(qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___constructor_qsizetype(qsizetype size);
// QList::append(const QList<T > & l)
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___append_QList_T(void *thisObj, void *l_);
// QList::at(qsizetype i) const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Item_T___at_qsizetype(void *thisObj, qsizetype i);
// QList::back()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___back(void *thisObj);
// QList::capacity() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Item_T___capacity(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Item_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Item_T___constLast(void *thisObj);
// QList::count() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Item_T___count(void *thisObj);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___detach(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Item_T___empty(void *thisObj);
// QList::first()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___first(void *thisObj);
// QList::first(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___first_qsizetype(void *thisObj, qsizetype n);
// QList::front()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___front(void *thisObj);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Item_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Item_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Item_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___last(void *thisObj);
// QList::last(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___last_qsizetype(void *thisObj, qsizetype n);
// QList::length() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Item_T___length(void *thisObj);
// QList::mid(qsizetype pos, qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len);
// QList::move(qsizetype from, qsizetype to)
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___pop_front(void *thisObj);
// QList::remove(qsizetype i, qsizetype n)
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n);
// QList::removeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___removeAt_qsizetype(void *thisObj, qsizetype i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___removeLast(void *thisObj);
// QList::reserve(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___reserve_qsizetype(void *thisObj, qsizetype size);
// QList::resize(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___resize_qsizetype(void *thisObj, qsizetype size);
// QList::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___shrink_to_fit(void *thisObj);
// QList::size() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Item_T___size(void *thisObj);
// QList::sliced(qsizetype pos) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___sliced_qsizetype(void *thisObj, qsizetype pos);
// QList::sliced(qsizetype pos, qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n);
// QList::squeeze()
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___squeeze(void *thisObj);
// QList::swapItemsAt(qsizetype i, qsizetype j)
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j);
// QList::takeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___takeAt_qsizetype(void *thisObj, qsizetype i);
// QList::toList() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___toList(void *thisObj);
// QList::toVector() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___toVector(void *thisObj);
// QList::value(qsizetype i) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Item_T___value_qsizetype(void *thisObj, qsizetype i);
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_Item_T__Finalizer(void *cppObj);
}
extern "C" {
// QList::QList<T>()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___constructor();
// QList::QList<T>(qsizetype size)
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___constructor_qsizetype(qsizetype size);
// QList::append(const QList<T > & l)
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___append_QList_T(void *thisObj, void *l_);
// QList::at(qsizetype i) const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Separator_T___at_qsizetype(void *thisObj, qsizetype i);
// QList::back()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___back(void *thisObj);
// QList::capacity() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Separator_T___capacity(void *thisObj);
// QList::clear()
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___clear(void *thisObj);
// QList::constFirst() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Separator_T___constFirst(void *thisObj);
// QList::constLast() const
KDDockWidgetsBindings_EXPORT const void *c_QList_T_Separator_T___constLast(void *thisObj);
// QList::count() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Separator_T___count(void *thisObj);
// QList::detach()
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___detach(void *thisObj);
// QList::empty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Separator_T___empty(void *thisObj);
// QList::first()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___first(void *thisObj);
// QList::first(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___first_qsizetype(void *thisObj, qsizetype n);
// QList::front()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___front(void *thisObj);
// QList::isDetached() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Separator_T___isDetached(void *thisObj);
// QList::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Separator_T___isEmpty(void *thisObj);
// QList::isSharedWith(const QList<T > & other) const
KDDockWidgetsBindings_EXPORT bool c_QList_T_Separator_T___isSharedWith_QList_T(void *thisObj, void *other_);
// QList::last()
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___last(void *thisObj);
// QList::last(qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___last_qsizetype(void *thisObj, qsizetype n);
// QList::length() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Separator_T___length(void *thisObj);
// QList::mid(qsizetype pos, qsizetype len) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___mid_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype len);
// QList::move(qsizetype from, qsizetype to)
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___move_qsizetype_qsizetype(void *thisObj, qsizetype from, qsizetype to);
// QList::pop_back()
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___pop_back(void *thisObj);
// QList::pop_front()
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___pop_front(void *thisObj);
// QList::remove(qsizetype i, qsizetype n)
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___remove_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype n);
// QList::removeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___removeAt_qsizetype(void *thisObj, qsizetype i);
// QList::removeFirst()
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___removeFirst(void *thisObj);
// QList::removeLast()
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___removeLast(void *thisObj);
// QList::reserve(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___reserve_qsizetype(void *thisObj, qsizetype size);
// QList::resize(qsizetype size)
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___resize_qsizetype(void *thisObj, qsizetype size);
// QList::shrink_to_fit()
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___shrink_to_fit(void *thisObj);
// QList::size() const
KDDockWidgetsBindings_EXPORT qsizetype c_QList_T_Separator_T___size(void *thisObj);
// QList::sliced(qsizetype pos) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___sliced_qsizetype(void *thisObj, qsizetype pos);
// QList::sliced(qsizetype pos, qsizetype n) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___sliced_qsizetype_qsizetype(void *thisObj, qsizetype pos, qsizetype n);
// QList::squeeze()
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___squeeze(void *thisObj);
// QList::swapItemsAt(qsizetype i, qsizetype j)
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___swapItemsAt_qsizetype_qsizetype(void *thisObj, qsizetype i, qsizetype j);
// QList::takeAt(qsizetype i)
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___takeAt_qsizetype(void *thisObj, qsizetype i);
// QList::toList() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___toList(void *thisObj);
// QList::toVector() const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___toVector(void *thisObj);
// QList::value(qsizetype i) const
KDDockWidgetsBindings_EXPORT void *c_QList_T_Separator_T___value_qsizetype(void *thisObj, qsizetype i);
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T___destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QList_T_Separator_T__Finalizer(void *cppObj);
}
