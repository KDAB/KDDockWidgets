/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "QList_wrapper.h"


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
//tag=1006
template <typename T>QList_wrapper<T>::QList_wrapper() : ::QList<T>() {}
template <typename T>void QList_wrapper<T>::append(const QList<T > & t){
//tag=1000

//tag=1004
::QList<T>::append(t);}
template <typename T>void QList_wrapper<T>::append(const T & t){
//tag=1000

//tag=1004
::QList<T>::append(t);}
template <typename T>const T & QList_wrapper<T>::at(int i)const{
//tag=1000

//tag=1004
return ::QList<T>::at(i);}
template <typename T>T & QList_wrapper<T>::back(){
//tag=1000

//tag=1004
return ::QList<T>::back();}
template <typename T>void QList_wrapper<T>::clear(){
//tag=1000

//tag=1004
::QList<T>::clear();}
template <typename T>const T & QList_wrapper<T>::constFirst()const{
//tag=1000

//tag=1004
return ::QList<T>::constFirst();}
template <typename T>const T & QList_wrapper<T>::constLast()const{
//tag=1000

//tag=1004
return ::QList<T>::constLast();}
template <typename T>bool QList_wrapper<T>::contains(const T & t)const{
//tag=1000

//tag=1004
return ::QList<T>::contains(t);}
template <typename T>int QList_wrapper<T>::count()const{
//tag=1000

//tag=1004
return ::QList<T>::count();}
template <typename T>int QList_wrapper<T>::count(const T & t)const{
//tag=1000

//tag=1004
return ::QList<T>::count(t);}
template <typename T>void QList_wrapper<T>::detach(){
//tag=1000

//tag=1004
::QList<T>::detach();}
template <typename T>void QList_wrapper<T>::detachShared(){
//tag=1000

//tag=1004
::QList<T>::detachShared();}
template <typename T>bool QList_wrapper<T>::empty()const{
//tag=1000

//tag=1004
return ::QList<T>::empty();}
template <typename T>bool QList_wrapper<T>::endsWith(const T & t)const{
//tag=1000

//tag=1004
return ::QList<T>::endsWith(t);}
template <typename T>T & QList_wrapper<T>::first(){
//tag=1000

//tag=1004
return ::QList<T>::first();}
template <typename T>T & QList_wrapper<T>::front(){
//tag=1000

//tag=1004
return ::QList<T>::front();}
template <typename T>int QList_wrapper<T>::indexOf(const T & t,int from)const{
//tag=1000

//tag=1004
return ::QList<T>::indexOf(t,from);}
template <typename T>void QList_wrapper<T>::insert(int i,const T & t){
//tag=1000

//tag=1004
::QList<T>::insert(i,t);}
template <typename T>bool QList_wrapper<T>::isDetached()const{
//tag=1000

//tag=1004
return ::QList<T>::isDetached();}
template <typename T>bool QList_wrapper<T>::isEmpty()const{
//tag=1000

//tag=1004
return ::QList<T>::isEmpty();}
template <typename T>bool QList_wrapper<T>::isSharedWith(const QList<T > & other)const{
//tag=1000

//tag=1004
return ::QList<T>::isSharedWith(other);}
template <typename T>T & QList_wrapper<T>::last(){
//tag=1000

//tag=1004
return ::QList<T>::last();}
template <typename T>int QList_wrapper<T>::lastIndexOf(const T & t,int from)const{
//tag=1000

//tag=1004
return ::QList<T>::lastIndexOf(t,from);}
template <typename T>int QList_wrapper<T>::length()const{
//tag=1000

//tag=1004
return ::QList<T>::length();}
template <typename T>QList<T > QList_wrapper<T>::mid(int pos,int length)const{
//tag=1000

//tag=1004
return ::QList<T>::mid(pos,length);}
template <typename T>void QList_wrapper<T>::move(int from,int to){
//tag=1000

//tag=1004
::QList<T>::move(from,to);}
template <typename T>void QList_wrapper<T>::pop_back(){
//tag=1000

//tag=1004
::QList<T>::pop_back();}
template <typename T>void QList_wrapper<T>::pop_front(){
//tag=1000

//tag=1004
::QList<T>::pop_front();}
template <typename T>void QList_wrapper<T>::prepend(const T & t){
//tag=1000

//tag=1004
::QList<T>::prepend(t);}
template <typename T>void QList_wrapper<T>::push_back(const T & t){
//tag=1000

//tag=1004
::QList<T>::push_back(t);}
template <typename T>void QList_wrapper<T>::push_front(const T & t){
//tag=1000

//tag=1004
::QList<T>::push_front(t);}
template <typename T>int QList_wrapper<T>::removeAll(const T & t){
//tag=1000

//tag=1004
return ::QList<T>::removeAll(t);}
template <typename T>void QList_wrapper<T>::removeAt(int i){
//tag=1000

//tag=1004
::QList<T>::removeAt(i);}
template <typename T>void QList_wrapper<T>::removeFirst(){
//tag=1000

//tag=1004
::QList<T>::removeFirst();}
template <typename T>void QList_wrapper<T>::removeLast(){
//tag=1000

//tag=1004
::QList<T>::removeLast();}
template <typename T>bool QList_wrapper<T>::removeOne(const T & t){
//tag=1000

//tag=1004
return ::QList<T>::removeOne(t);}
template <typename T>void QList_wrapper<T>::replace(int i,const T & t){
//tag=1000

//tag=1004
::QList<T>::replace(i,t);}
template <typename T>void QList_wrapper<T>::reserve(int size){
//tag=1000

//tag=1004
::QList<T>::reserve(size);}
template <typename T>void QList_wrapper<T>::setSharable(bool sharable){
//tag=1000

//tag=1004
::QList<T>::setSharable(sharable);}
template <typename T>int QList_wrapper<T>::size()const{
//tag=1000

//tag=1004
return ::QList<T>::size();}
template <typename T>bool QList_wrapper<T>::startsWith(const T & t)const{
//tag=1000

//tag=1004
return ::QList<T>::startsWith(t);}
template <typename T>void QList_wrapper<T>::swapItemsAt(int i,int j){
//tag=1000

//tag=1004
::QList<T>::swapItemsAt(i,j);}
template <typename T>T QList_wrapper<T>::takeAt(int i){
//tag=1000

//tag=1004
return ::QList<T>::takeAt(i);}
template <typename T>T QList_wrapper<T>::takeFirst(){
//tag=1000

//tag=1004
return ::QList<T>::takeFirst();}
template <typename T>T QList_wrapper<T>::takeLast(){
//tag=1000

//tag=1004
return ::QList<T>::takeLast();}
template <typename T>T QList_wrapper<T>::value(int i)const{
//tag=1000

//tag=1004
return ::QList<T>::value(i);}
template <typename T>T QList_wrapper<T>::value(int i,const T & defaultValue)const{
//tag=1000

//tag=1004
return ::QList<T>::value(i,defaultValue);}

//tag=1005
template <typename T>QList_wrapper<T>::~QList_wrapper() {}

}
//tag=1013
template <typename T>static QList<T>* fromPtr(void *ptr)
{return reinterpret_cast<QList<T>*>(ptr);}
//tag=1014
template <typename T>static KDDockWidgetsBindings_wrappersNS::QList_wrapper<T>* fromWrapperPtr(void *ptr)
{return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<T>*>(ptr);}extern "C" {

//tag=1049
 void c_QList_T_QObject_T__Finalizer(void *, void *cppObj, void *){delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<QObject *> *>(cppObj);}void * c_QList_T_QObject_T___constructor()
{

//tag=1056
auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<QObject *>();return reinterpret_cast<void*>(ptr);}

//tag=1050
//append(const QList<T > & t)
void c_QList_T_QObject_T___append_QList_T(void *thisObj,void* t_){auto &t = *reinterpret_cast<QList<QObject *> *>(t_);
//tag=1010
fromPtr<QObject *>(thisObj)->append(t);}

//tag=1050
//append(const T & t)
void c_QList_T_QObject_T___append_QObject(void *thisObj,void* t_){auto t = reinterpret_cast<QObject *>(t_);
//tag=1010
fromPtr<QObject *>(thisObj)->append(t);}

//tag=1050
//at(int i) const
const void* c_QList_T_QObject_T___at_int(void *thisObj,int i){return 
//tag=1010
fromPtr<QObject *>(thisObj)->at(i);}

//tag=1050
//back()
void* c_QList_T_QObject_T___back(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->back();}

//tag=1050
//clear()
void c_QList_T_QObject_T___clear(void *thisObj){
//tag=1010
fromPtr<QObject *>(thisObj)->clear();}

//tag=1050
//constFirst() const
const void* c_QList_T_QObject_T___constFirst(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->constFirst();}

//tag=1050
//constLast() const
const void* c_QList_T_QObject_T___constLast(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->constLast();}

//tag=1050
//contains(const T & t) const
bool c_QList_T_QObject_T___contains_QObject(void *thisObj,void* t_){auto t = reinterpret_cast<QObject *>(t_);return 
//tag=1010
fromPtr<QObject *>(thisObj)->contains(t);}

//tag=1050
//count() const
int c_QList_T_QObject_T___count(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->count();}

//tag=1050
//count(const T & t) const
int c_QList_T_QObject_T___count_QObject(void *thisObj,void* t_){auto t = reinterpret_cast<QObject *>(t_);return 
//tag=1010
fromPtr<QObject *>(thisObj)->count(t);}

//tag=1050
//detach()
void c_QList_T_QObject_T___detach(void *thisObj){
//tag=1010
fromPtr<QObject *>(thisObj)->detach();}

//tag=1050
//detachShared()
void c_QList_T_QObject_T___detachShared(void *thisObj){
//tag=1010
fromPtr<QObject *>(thisObj)->detachShared();}

//tag=1050
//empty() const
bool c_QList_T_QObject_T___empty(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->empty();}

//tag=1050
//endsWith(const T & t) const
bool c_QList_T_QObject_T___endsWith_QObject(void *thisObj,void* t_){auto t = reinterpret_cast<QObject *>(t_);return 
//tag=1010
fromPtr<QObject *>(thisObj)->endsWith(t);}

//tag=1050
//first()
void* c_QList_T_QObject_T___first(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->first();}

//tag=1050
//front()
void* c_QList_T_QObject_T___front(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->front();}

//tag=1050
//indexOf(const T & t, int from) const
int c_QList_T_QObject_T___indexOf_QObject_int(void *thisObj,void* t_,int from){auto t = reinterpret_cast<QObject *>(t_);return 
//tag=1010
fromPtr<QObject *>(thisObj)->indexOf(t,from);}

//tag=1050
//insert(int i, const T & t)
void c_QList_T_QObject_T___insert_int_QObject(void *thisObj,int i,void* t_){auto t = reinterpret_cast<QObject *>(t_);
//tag=1010
fromPtr<QObject *>(thisObj)->insert(i,t);}

//tag=1050
//isDetached() const
bool c_QList_T_QObject_T___isDetached(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->isDetached();}

//tag=1050
//isEmpty() const
bool c_QList_T_QObject_T___isEmpty(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->isEmpty();}

//tag=1050
//isSharedWith(const QList<T > & other) const
bool c_QList_T_QObject_T___isSharedWith_QList_T(void *thisObj,void* other_){auto &other = *reinterpret_cast<QList<QObject *> *>(other_);return 
//tag=1010
fromPtr<QObject *>(thisObj)->isSharedWith(other);}

//tag=1050
//last()
void* c_QList_T_QObject_T___last(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->last();}

//tag=1050
//lastIndexOf(const T & t, int from) const
int c_QList_T_QObject_T___lastIndexOf_QObject_int(void *thisObj,void* t_,int from){auto t = reinterpret_cast<QObject *>(t_);return 
//tag=1010
fromPtr<QObject *>(thisObj)->lastIndexOf(t,from);}

//tag=1050
//length() const
int c_QList_T_QObject_T___length(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->length();}

//tag=1050
//mid(int pos, int length) const
void* c_QList_T_QObject_T___mid_int_int(void *thisObj,int pos,int length){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QList<QObject *>>{fromPtr<QObject *>(thisObj)->mid(pos,length)};}

//tag=1050
//move(int from, int to)
void c_QList_T_QObject_T___move_int_int(void *thisObj,int from,int to){
//tag=1010
fromPtr<QObject *>(thisObj)->move(from,to);}

//tag=1050
//pop_back()
void c_QList_T_QObject_T___pop_back(void *thisObj){
//tag=1010
fromPtr<QObject *>(thisObj)->pop_back();}

//tag=1050
//pop_front()
void c_QList_T_QObject_T___pop_front(void *thisObj){
//tag=1010
fromPtr<QObject *>(thisObj)->pop_front();}

//tag=1050
//prepend(const T & t)
void c_QList_T_QObject_T___prepend_QObject(void *thisObj,void* t_){auto t = reinterpret_cast<QObject *>(t_);
//tag=1010
fromPtr<QObject *>(thisObj)->prepend(t);}

//tag=1050
//push_back(const T & t)
void c_QList_T_QObject_T___push_back_QObject(void *thisObj,void* t_){auto t = reinterpret_cast<QObject *>(t_);
//tag=1010
fromPtr<QObject *>(thisObj)->push_back(t);}

//tag=1050
//push_front(const T & t)
void c_QList_T_QObject_T___push_front_QObject(void *thisObj,void* t_){auto t = reinterpret_cast<QObject *>(t_);
//tag=1010
fromPtr<QObject *>(thisObj)->push_front(t);}

//tag=1050
//removeAll(const T & t)
int c_QList_T_QObject_T___removeAll_QObject(void *thisObj,void* t_){auto t = reinterpret_cast<QObject *>(t_);return 
//tag=1010
fromPtr<QObject *>(thisObj)->removeAll(t);}

//tag=1050
//removeAt(int i)
void c_QList_T_QObject_T___removeAt_int(void *thisObj,int i){
//tag=1010
fromPtr<QObject *>(thisObj)->removeAt(i);}

//tag=1050
//removeFirst()
void c_QList_T_QObject_T___removeFirst(void *thisObj){
//tag=1010
fromPtr<QObject *>(thisObj)->removeFirst();}

//tag=1050
//removeLast()
void c_QList_T_QObject_T___removeLast(void *thisObj){
//tag=1010
fromPtr<QObject *>(thisObj)->removeLast();}

//tag=1050
//removeOne(const T & t)
bool c_QList_T_QObject_T___removeOne_QObject(void *thisObj,void* t_){auto t = reinterpret_cast<QObject *>(t_);return 
//tag=1010
fromPtr<QObject *>(thisObj)->removeOne(t);}

//tag=1050
//replace(int i, const T & t)
void c_QList_T_QObject_T___replace_int_QObject(void *thisObj,int i,void* t_){auto t = reinterpret_cast<QObject *>(t_);
//tag=1010
fromPtr<QObject *>(thisObj)->replace(i,t);}

//tag=1050
//reserve(int size)
void c_QList_T_QObject_T___reserve_int(void *thisObj,int size){
//tag=1010
fromPtr<QObject *>(thisObj)->reserve(size);}

//tag=1050
//setSharable(bool sharable)
void c_QList_T_QObject_T___setSharable_bool(void *thisObj,bool sharable){
//tag=1010
fromPtr<QObject *>(thisObj)->setSharable(sharable);}

//tag=1050
//size() const
int c_QList_T_QObject_T___size(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->size();}

//tag=1050
//startsWith(const T & t) const
bool c_QList_T_QObject_T___startsWith_QObject(void *thisObj,void* t_){auto t = reinterpret_cast<QObject *>(t_);return 
//tag=1010
fromPtr<QObject *>(thisObj)->startsWith(t);}

//tag=1050
//swapItemsAt(int i, int j)
void c_QList_T_QObject_T___swapItemsAt_int_int(void *thisObj,int i,int j){
//tag=1010
fromPtr<QObject *>(thisObj)->swapItemsAt(i,j);}

//tag=1050
//takeAt(int i)
void* c_QList_T_QObject_T___takeAt_int(void *thisObj,int i){return 
//tag=1010
fromPtr<QObject *>(thisObj)->takeAt(i);}

//tag=1050
//takeFirst()
void* c_QList_T_QObject_T___takeFirst(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->takeFirst();}

//tag=1050
//takeLast()
void* c_QList_T_QObject_T___takeLast(void *thisObj){return 
//tag=1010
fromPtr<QObject *>(thisObj)->takeLast();}

//tag=1050
//value(int i) const
void* c_QList_T_QObject_T___value_int(void *thisObj,int i){return 
//tag=1010
fromPtr<QObject *>(thisObj)->value(i);}

//tag=1050
//value(int i, const T & defaultValue) const
void* c_QList_T_QObject_T___value_int_QObject(void *thisObj,int i,void* defaultValue_){auto defaultValue = reinterpret_cast<QObject *>(defaultValue_);return 
//tag=1010
fromPtr<QObject *>(thisObj)->value(i,defaultValue);}
void c_QList_T_QObject_T___destructor(void *thisObj)
{

//tag=1055
delete fromPtr<QObject *>(thisObj);}
}
extern "C" {

//tag=1049
 void c_QList_T_QByteArray_T__Finalizer(void *, void *cppObj, void *){delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QList_wrapper<QByteArray> *>(cppObj);}void * c_QList_T_QByteArray_T___constructor()
{

//tag=1056
auto ptr = new KDDockWidgetsBindings_wrappersNS::QList_wrapper<QByteArray>();return reinterpret_cast<void*>(ptr);}

//tag=1050
//append(const QList<T > & t)
void c_QList_T_QByteArray_T___append_QList_T(void *thisObj,void* t_){auto &t = *reinterpret_cast<QList<QByteArray> *>(t_);
//tag=1010
fromPtr<QByteArray>(thisObj)->append(t);}

//tag=1050
//append(const T & t)
void c_QList_T_QByteArray_T___append_QByteArray(void *thisObj,void* t_){auto &t = *reinterpret_cast<QByteArray *>(t_);
//tag=1010
fromPtr<QByteArray>(thisObj)->append(t);}

//tag=1050
//at(int i) const
const void* c_QList_T_QByteArray_T___at_int(void *thisObj,int i){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr<QByteArray>(thisObj)->at(i)};}

//tag=1050
//back()
void* c_QList_T_QByteArray_T___back(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr<QByteArray>(thisObj)->back()};}

//tag=1050
//clear()
void c_QList_T_QByteArray_T___clear(void *thisObj){
//tag=1010
fromPtr<QByteArray>(thisObj)->clear();}

//tag=1050
//constFirst() const
const void* c_QList_T_QByteArray_T___constFirst(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr<QByteArray>(thisObj)->constFirst()};}

//tag=1050
//constLast() const
const void* c_QList_T_QByteArray_T___constLast(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr<QByteArray>(thisObj)->constLast()};}

//tag=1050
//contains(const T & t) const
bool c_QList_T_QByteArray_T___contains_QByteArray(void *thisObj,void* t_){auto &t = *reinterpret_cast<QByteArray *>(t_);return 
//tag=1010
fromPtr<QByteArray>(thisObj)->contains(t);}

//tag=1050
//count() const
int c_QList_T_QByteArray_T___count(void *thisObj){return 
//tag=1010
fromPtr<QByteArray>(thisObj)->count();}

//tag=1050
//count(const T & t) const
int c_QList_T_QByteArray_T___count_QByteArray(void *thisObj,void* t_){auto &t = *reinterpret_cast<QByteArray *>(t_);return 
//tag=1010
fromPtr<QByteArray>(thisObj)->count(t);}

//tag=1050
//detach()
void c_QList_T_QByteArray_T___detach(void *thisObj){
//tag=1010
fromPtr<QByteArray>(thisObj)->detach();}

//tag=1050
//detachShared()
void c_QList_T_QByteArray_T___detachShared(void *thisObj){
//tag=1010
fromPtr<QByteArray>(thisObj)->detachShared();}

//tag=1050
//empty() const
bool c_QList_T_QByteArray_T___empty(void *thisObj){return 
//tag=1010
fromPtr<QByteArray>(thisObj)->empty();}

//tag=1050
//endsWith(const T & t) const
bool c_QList_T_QByteArray_T___endsWith_QByteArray(void *thisObj,void* t_){auto &t = *reinterpret_cast<QByteArray *>(t_);return 
//tag=1010
fromPtr<QByteArray>(thisObj)->endsWith(t);}

//tag=1050
//first()
void* c_QList_T_QByteArray_T___first(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr<QByteArray>(thisObj)->first()};}

//tag=1050
//front()
void* c_QList_T_QByteArray_T___front(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr<QByteArray>(thisObj)->front()};}

//tag=1050
//indexOf(const T & t, int from) const
int c_QList_T_QByteArray_T___indexOf_QByteArray_int(void *thisObj,void* t_,int from){auto &t = *reinterpret_cast<QByteArray *>(t_);return 
//tag=1010
fromPtr<QByteArray>(thisObj)->indexOf(t,from);}

//tag=1050
//insert(int i, const T & t)
void c_QList_T_QByteArray_T___insert_int_QByteArray(void *thisObj,int i,void* t_){auto &t = *reinterpret_cast<QByteArray *>(t_);
//tag=1010
fromPtr<QByteArray>(thisObj)->insert(i,t);}

//tag=1050
//isDetached() const
bool c_QList_T_QByteArray_T___isDetached(void *thisObj){return 
//tag=1010
fromPtr<QByteArray>(thisObj)->isDetached();}

//tag=1050
//isEmpty() const
bool c_QList_T_QByteArray_T___isEmpty(void *thisObj){return 
//tag=1010
fromPtr<QByteArray>(thisObj)->isEmpty();}

//tag=1050
//isSharedWith(const QList<T > & other) const
bool c_QList_T_QByteArray_T___isSharedWith_QList_T(void *thisObj,void* other_){auto &other = *reinterpret_cast<QList<QByteArray> *>(other_);return 
//tag=1010
fromPtr<QByteArray>(thisObj)->isSharedWith(other);}

//tag=1050
//last()
void* c_QList_T_QByteArray_T___last(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr<QByteArray>(thisObj)->last()};}

//tag=1050
//lastIndexOf(const T & t, int from) const
int c_QList_T_QByteArray_T___lastIndexOf_QByteArray_int(void *thisObj,void* t_,int from){auto &t = *reinterpret_cast<QByteArray *>(t_);return 
//tag=1010
fromPtr<QByteArray>(thisObj)->lastIndexOf(t,from);}

//tag=1050
//length() const
int c_QList_T_QByteArray_T___length(void *thisObj){return 
//tag=1010
fromPtr<QByteArray>(thisObj)->length();}

//tag=1050
//mid(int pos, int length) const
void* c_QList_T_QByteArray_T___mid_int_int(void *thisObj,int pos,int length){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QList<QByteArray>>{fromPtr<QByteArray>(thisObj)->mid(pos,length)};}

//tag=1050
//move(int from, int to)
void c_QList_T_QByteArray_T___move_int_int(void *thisObj,int from,int to){
//tag=1010
fromPtr<QByteArray>(thisObj)->move(from,to);}

//tag=1050
//pop_back()
void c_QList_T_QByteArray_T___pop_back(void *thisObj){
//tag=1010
fromPtr<QByteArray>(thisObj)->pop_back();}

//tag=1050
//pop_front()
void c_QList_T_QByteArray_T___pop_front(void *thisObj){
//tag=1010
fromPtr<QByteArray>(thisObj)->pop_front();}

//tag=1050
//prepend(const T & t)
void c_QList_T_QByteArray_T___prepend_QByteArray(void *thisObj,void* t_){auto &t = *reinterpret_cast<QByteArray *>(t_);
//tag=1010
fromPtr<QByteArray>(thisObj)->prepend(t);}

//tag=1050
//push_back(const T & t)
void c_QList_T_QByteArray_T___push_back_QByteArray(void *thisObj,void* t_){auto &t = *reinterpret_cast<QByteArray *>(t_);
//tag=1010
fromPtr<QByteArray>(thisObj)->push_back(t);}

//tag=1050
//push_front(const T & t)
void c_QList_T_QByteArray_T___push_front_QByteArray(void *thisObj,void* t_){auto &t = *reinterpret_cast<QByteArray *>(t_);
//tag=1010
fromPtr<QByteArray>(thisObj)->push_front(t);}

//tag=1050
//removeAll(const T & t)
int c_QList_T_QByteArray_T___removeAll_QByteArray(void *thisObj,void* t_){auto &t = *reinterpret_cast<QByteArray *>(t_);return 
//tag=1010
fromPtr<QByteArray>(thisObj)->removeAll(t);}

//tag=1050
//removeAt(int i)
void c_QList_T_QByteArray_T___removeAt_int(void *thisObj,int i){
//tag=1010
fromPtr<QByteArray>(thisObj)->removeAt(i);}

//tag=1050
//removeFirst()
void c_QList_T_QByteArray_T___removeFirst(void *thisObj){
//tag=1010
fromPtr<QByteArray>(thisObj)->removeFirst();}

//tag=1050
//removeLast()
void c_QList_T_QByteArray_T___removeLast(void *thisObj){
//tag=1010
fromPtr<QByteArray>(thisObj)->removeLast();}

//tag=1050
//removeOne(const T & t)
bool c_QList_T_QByteArray_T___removeOne_QByteArray(void *thisObj,void* t_){auto &t = *reinterpret_cast<QByteArray *>(t_);return 
//tag=1010
fromPtr<QByteArray>(thisObj)->removeOne(t);}

//tag=1050
//replace(int i, const T & t)
void c_QList_T_QByteArray_T___replace_int_QByteArray(void *thisObj,int i,void* t_){auto &t = *reinterpret_cast<QByteArray *>(t_);
//tag=1010
fromPtr<QByteArray>(thisObj)->replace(i,t);}

//tag=1050
//reserve(int size)
void c_QList_T_QByteArray_T___reserve_int(void *thisObj,int size){
//tag=1010
fromPtr<QByteArray>(thisObj)->reserve(size);}

//tag=1050
//setSharable(bool sharable)
void c_QList_T_QByteArray_T___setSharable_bool(void *thisObj,bool sharable){
//tag=1010
fromPtr<QByteArray>(thisObj)->setSharable(sharable);}

//tag=1050
//size() const
int c_QList_T_QByteArray_T___size(void *thisObj){return 
//tag=1010
fromPtr<QByteArray>(thisObj)->size();}

//tag=1050
//startsWith(const T & t) const
bool c_QList_T_QByteArray_T___startsWith_QByteArray(void *thisObj,void* t_){auto &t = *reinterpret_cast<QByteArray *>(t_);return 
//tag=1010
fromPtr<QByteArray>(thisObj)->startsWith(t);}

//tag=1050
//swapItemsAt(int i, int j)
void c_QList_T_QByteArray_T___swapItemsAt_int_int(void *thisObj,int i,int j){
//tag=1010
fromPtr<QByteArray>(thisObj)->swapItemsAt(i,j);}

//tag=1050
//takeAt(int i)
void* c_QList_T_QByteArray_T___takeAt_int(void *thisObj,int i){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr<QByteArray>(thisObj)->takeAt(i)};}

//tag=1050
//takeFirst()
void* c_QList_T_QByteArray_T___takeFirst(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr<QByteArray>(thisObj)->takeFirst()};}

//tag=1050
//takeLast()
void* c_QList_T_QByteArray_T___takeLast(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr<QByteArray>(thisObj)->takeLast()};}

//tag=1050
//value(int i) const
void* c_QList_T_QByteArray_T___value_int(void *thisObj,int i){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr<QByteArray>(thisObj)->value(i)};}

//tag=1050
//value(int i, const T & defaultValue) const
void* c_QList_T_QByteArray_T___value_int_QByteArray(void *thisObj,int i,void* defaultValue_){auto &defaultValue = *reinterpret_cast<QByteArray *>(defaultValue_);return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr<QByteArray>(thisObj)->value(i,defaultValue)};}
void c_QList_T_QByteArray_T___destructor(void *thisObj)
{

//tag=1055
delete fromPtr<QByteArray>(thisObj);}
}
