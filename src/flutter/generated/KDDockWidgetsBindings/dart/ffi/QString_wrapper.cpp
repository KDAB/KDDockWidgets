/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "QString_wrapper.h"


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
QString_wrapper::QString_wrapper() : ::QString() {}
QString & QString_wrapper::append(const QString & s){
//tag=1000

//tag=1004
return ::QString::append(s);}
QString QString_wrapper::arg(const QString & a,int fieldWidth)const{
//tag=1000

//tag=1004
return ::QString::arg(a,fieldWidth);}
QString QString_wrapper::arg(const QString & a1,const QString & a2)const{
//tag=1000

//tag=1004
return ::QString::arg(a1,a2);}
QString QString_wrapper::arg(const QString & a1,const QString & a2,const QString & a3)const{
//tag=1000

//tag=1004
return ::QString::arg(a1,a2,a3);}
QString QString_wrapper::arg(const QString & a1,const QString & a2,const QString & a3,const QString & a4)const{
//tag=1000

//tag=1004
return ::QString::arg(a1,a2,a3,a4);}
QString QString_wrapper::arg(const QString & a1,const QString & a2,const QString & a3,const QString & a4,const QString & a5)const{
//tag=1000

//tag=1004
return ::QString::arg(a1,a2,a3,a4,a5);}
QString QString_wrapper::arg(const QString & a1,const QString & a2,const QString & a3,const QString & a4,const QString & a5,const QString & a6)const{
//tag=1000

//tag=1004
return ::QString::arg(a1,a2,a3,a4,a5,a6);}
QString QString_wrapper::arg(const QString & a1,const QString & a2,const QString & a3,const QString & a4,const QString & a5,const QString & a6,const QString & a7)const{
//tag=1000

//tag=1004
return ::QString::arg(a1,a2,a3,a4,a5,a6,a7);}
QString QString_wrapper::arg(const QString & a1,const QString & a2,const QString & a3,const QString & a4,const QString & a5,const QString & a6,const QString & a7,const QString & a8)const{
//tag=1000

//tag=1004
return ::QString::arg(a1,a2,a3,a4,a5,a6,a7,a8);}
QString QString_wrapper::arg(const QString & a1,const QString & a2,const QString & a3,const QString & a4,const QString & a5,const QString & a6,const QString & a7,const QString & a8,const QString & a9)const{
//tag=1000

//tag=1004
return ::QString::arg(a1,a2,a3,a4,a5,a6,a7,a8,a9);}
QString QString_wrapper::arg(int a,int fieldWidth,int base)const{
//tag=1000

//tag=1004
return ::QString::arg(a,fieldWidth,base);}
QString QString_wrapper::arg(long a,int fieldwidth,int base)const{
//tag=1000

//tag=1004
return ::QString::arg(a,fieldwidth,base);}
QString QString_wrapper::arg(qint64 a,int fieldwidth,int base)const{
//tag=1000

//tag=1004
return ::QString::arg(a,fieldwidth,base);}
QString QString_wrapper::arg(short a,int fieldWidth,int base)const{
//tag=1000

//tag=1004
return ::QString::arg(a,fieldWidth,base);}
QString QString_wrapper::asprintf(const char * format){
//tag=1000

//tag=1004
return ::QString::asprintf(format);}
int QString_wrapper::capacity()const{
//tag=1000

//tag=1004
return ::QString::capacity();}
void QString_wrapper::chop(int n){
//tag=1000

//tag=1004
::QString::chop(n);}
QString QString_wrapper::chopped(int n)const{
//tag=1000

//tag=1004
return ::QString::chopped(n);}
void QString_wrapper::clear(){
//tag=1000

//tag=1004
::QString::clear();}
int QString_wrapper::compare(const QString & s)const{
//tag=1000

//tag=1004
return ::QString::compare(s);}
int QString_wrapper::compare(const QString & s1,const QString & s2){
//tag=1000

//tag=1004
return ::QString::compare(s1,s2);}
bool QString_wrapper::contains(const QString & s)const{
//tag=1000

//tag=1004
return ::QString::contains(s);}
int QString_wrapper::count()const{
//tag=1000

//tag=1004
return ::QString::count();}
int QString_wrapper::count(const QString & s)const{
//tag=1000

//tag=1004
return ::QString::count(s);}
void QString_wrapper::detach(){
//tag=1000

//tag=1004
::QString::detach();}
bool QString_wrapper::endsWith(const QString & s)const{
//tag=1000

//tag=1004
return ::QString::endsWith(s);}
QString QString_wrapper::fromLatin1(const QByteArray & str){
//tag=1000

//tag=1004
return ::QString::fromLatin1(str);}
QString QString_wrapper::fromLatin1(const char * str,int size){
//tag=1000

//tag=1004
return ::QString::fromLatin1(str,size);}
QString QString_wrapper::fromLocal8Bit(const QByteArray & str){
//tag=1000

//tag=1004
return ::QString::fromLocal8Bit(str);}
QString QString_wrapper::fromLocal8Bit(const char * str,int size){
//tag=1000

//tag=1004
return ::QString::fromLocal8Bit(str,size);}
QString QString_wrapper::fromUtf8(const QByteArray & str){
//tag=1000

//tag=1004
return ::QString::fromUtf8(str);}
QString QString_wrapper::fromUtf8(const char * str,int size){
//tag=1000

//tag=1004
return ::QString::fromUtf8(str,size);}
int QString_wrapper::indexOf(const QString & s,int from)const{
//tag=1000

//tag=1004
return ::QString::indexOf(s,from);}
QString & QString_wrapper::insert(int i,const QString & s){
//tag=1000

//tag=1004
return ::QString::insert(i,s);}
bool QString_wrapper::isDetached()const{
//tag=1000

//tag=1004
return ::QString::isDetached();}
bool QString_wrapper::isEmpty()const{
//tag=1000

//tag=1004
return ::QString::isEmpty();}
bool QString_wrapper::isLower()const{
//tag=1000

//tag=1004
return ::QString::isLower();}
bool QString_wrapper::isNull()const{
//tag=1000

//tag=1004
return ::QString::isNull();}
bool QString_wrapper::isRightToLeft()const{
//tag=1000

//tag=1004
return ::QString::isRightToLeft();}
bool QString_wrapper::isSharedWith(const QString & other)const{
//tag=1000

//tag=1004
return ::QString::isSharedWith(other);}
bool QString_wrapper::isSimpleText()const{
//tag=1000

//tag=1004
return ::QString::isSimpleText();}
bool QString_wrapper::isUpper()const{
//tag=1000

//tag=1004
return ::QString::isUpper();}
bool QString_wrapper::isValidUtf16()const{
//tag=1000

//tag=1004
return ::QString::isValidUtf16();}
int QString_wrapper::lastIndexOf(const QString & s,int from)const{
//tag=1000

//tag=1004
return ::QString::lastIndexOf(s,from);}
QString QString_wrapper::left(int n)const{
//tag=1000

//tag=1004
return ::QString::left(n);}
QString QString_wrapper::leftJustified(int width)const{
//tag=1000

//tag=1004
return ::QString::leftJustified(width);}
int QString_wrapper::length()const{
//tag=1000

//tag=1004
return ::QString::length();}
int QString_wrapper::localeAwareCompare(const QString & s)const{
//tag=1000

//tag=1004
return ::QString::localeAwareCompare(s);}
int QString_wrapper::localeAwareCompare(const QString & s1,const QString & s2){
//tag=1000

//tag=1004
return ::QString::localeAwareCompare(s1,s2);}
QString QString_wrapper::mid(int position,int n)const{
//tag=1000

//tag=1004
return ::QString::mid(position,n);}
QString QString_wrapper::number(int arg__1,int base){
//tag=1000

//tag=1004
return ::QString::number(arg__1,base);}
QString QString_wrapper::number(long arg__1,int base){
//tag=1000

//tag=1004
return ::QString::number(arg__1,base);}
QString QString_wrapper::number(qint64 arg__1,int base){
//tag=1000

//tag=1004
return ::QString::number(arg__1,base);}
QString & QString_wrapper::prepend(const QString & s){
//tag=1000

//tag=1004
return ::QString::prepend(s);}
void QString_wrapper::push_back(const QString & s){
//tag=1000

//tag=1004
::QString::push_back(s);}
void QString_wrapper::push_front(const QString & s){
//tag=1000

//tag=1004
::QString::push_front(s);}
QString & QString_wrapper::remove(const QString & s){
//tag=1000

//tag=1004
return ::QString::remove(s);}
QString & QString_wrapper::remove(int i,int len){
//tag=1000

//tag=1004
return ::QString::remove(i,len);}
QString QString_wrapper::repeated(int times)const{
//tag=1000

//tag=1004
return ::QString::repeated(times);}
QString & QString_wrapper::replace(const QString & before,const QString & after){
//tag=1000

//tag=1004
return ::QString::replace(before,after);}
QString & QString_wrapper::replace(int i,int len,const QString & after){
//tag=1000

//tag=1004
return ::QString::replace(i,len,after);}
void QString_wrapper::reserve(int size){
//tag=1000

//tag=1004
::QString::reserve(size);}
void QString_wrapper::resize(int size){
//tag=1000

//tag=1004
::QString::resize(size);}
QString QString_wrapper::right(int n)const{
//tag=1000

//tag=1004
return ::QString::right(n);}
QString QString_wrapper::rightJustified(int width)const{
//tag=1000

//tag=1004
return ::QString::rightJustified(width);}
QString QString_wrapper::section(const QString & in_sep,int start,int end)const{
//tag=1000

//tag=1004
return ::QString::section(in_sep,start,end);}
QString & QString_wrapper::setNum(int arg__1,int base){
//tag=1000

//tag=1004
return ::QString::setNum(arg__1,base);}
QString & QString_wrapper::setNum(long arg__1,int base){
//tag=1000

//tag=1004
return ::QString::setNum(arg__1,base);}
QString & QString_wrapper::setNum(qint64 arg__1,int base){
//tag=1000

//tag=1004
return ::QString::setNum(arg__1,base);}
QString & QString_wrapper::setNum(short arg__1,int base){
//tag=1000

//tag=1004
return ::QString::setNum(arg__1,base);}
void QString_wrapper::shrink_to_fit(){
//tag=1000

//tag=1004
::QString::shrink_to_fit();}
QString QString_wrapper::simplified(){
//tag=1000

//tag=1004
return ::QString::simplified();}
int QString_wrapper::size()const{
//tag=1000

//tag=1004
return ::QString::size();}
void QString_wrapper::squeeze(){
//tag=1000

//tag=1004
::QString::squeeze();}
bool QString_wrapper::startsWith(const QString & s)const{
//tag=1000

//tag=1004
return ::QString::startsWith(s);}
QString QString_wrapper::toCaseFolded(){
//tag=1000

//tag=1004
return ::QString::toCaseFolded();}
QString QString_wrapper::toHtmlEscaped()const{
//tag=1000

//tag=1004
return ::QString::toHtmlEscaped();}
QByteArray QString_wrapper::toLatin1(){
//tag=1000

//tag=1004
return ::QString::toLatin1();}
QByteArray QString_wrapper::toLocal8Bit(){
//tag=1000

//tag=1004
return ::QString::toLocal8Bit();}
QString QString_wrapper::toLower(){
//tag=1000

//tag=1004
return ::QString::toLower();}
QString QString_wrapper::toUpper(){
//tag=1000

//tag=1004
return ::QString::toUpper();}
QByteArray QString_wrapper::toUtf8(){
//tag=1000

//tag=1004
return ::QString::toUtf8();}
QString QString_wrapper::trimmed(){
//tag=1000

//tag=1004
return ::QString::trimmed();}
void QString_wrapper::truncate(int pos){
//tag=1000

//tag=1004
::QString::truncate(pos);}

//tag=1005
QString_wrapper::~QString_wrapper() {}

}
//tag=1013
static QString* fromPtr(void *ptr)
{return reinterpret_cast<QString*>(ptr);}
//tag=1014
static KDDockWidgetsBindings_wrappersNS::QString_wrapper* fromWrapperPtr(void *ptr)
{return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QString_wrapper*>(ptr);}extern "C" {

//tag=1049
 void c_QString_Finalizer(void *, void *cppObj, void *){delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QString_wrapper *>(cppObj);}void * c_QString__constructor()
{

//tag=1056
auto ptr = new KDDockWidgetsBindings_wrappersNS::QString_wrapper();return reinterpret_cast<void*>(ptr);}

//tag=1050
//append(const QString & s)
void* c_QString__append_QString(void *thisObj,const char *s_){const auto s = QString::fromUtf8(s_);return 
//tag=1010

//tag=1070
&fromPtr(thisObj)->append(s);}

//tag=1050
//arg(const QString & a, int fieldWidth) const
void* c_QString__arg_QString_int(void *thisObj,const char *a_,int fieldWidth){const auto a = QString::fromUtf8(a_);return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->arg(a,fieldWidth)};}

//tag=1050
//arg(const QString & a1, const QString & a2) const
void* c_QString__arg_QString_QString(void *thisObj,const char *a1_,const char *a2_){const auto a1 = QString::fromUtf8(a1_);const auto a2 = QString::fromUtf8(a2_);return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->arg(a1,a2)};}

//tag=1050
//arg(const QString & a1, const QString & a2, const QString & a3) const
void* c_QString__arg_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_){const auto a1 = QString::fromUtf8(a1_);const auto a2 = QString::fromUtf8(a2_);const auto a3 = QString::fromUtf8(a3_);return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->arg(a1,a2,a3)};}

//tag=1050
//arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4) const
void* c_QString__arg_QString_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_,const char *a4_){const auto a1 = QString::fromUtf8(a1_);const auto a2 = QString::fromUtf8(a2_);const auto a3 = QString::fromUtf8(a3_);const auto a4 = QString::fromUtf8(a4_);return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->arg(a1,a2,a3,a4)};}

//tag=1050
//arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5) const
void* c_QString__arg_QString_QString_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_,const char *a4_,const char *a5_){const auto a1 = QString::fromUtf8(a1_);const auto a2 = QString::fromUtf8(a2_);const auto a3 = QString::fromUtf8(a3_);const auto a4 = QString::fromUtf8(a4_);const auto a5 = QString::fromUtf8(a5_);return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->arg(a1,a2,a3,a4,a5)};}

//tag=1050
//arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6) const
void* c_QString__arg_QString_QString_QString_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_,const char *a4_,const char *a5_,const char *a6_){const auto a1 = QString::fromUtf8(a1_);const auto a2 = QString::fromUtf8(a2_);const auto a3 = QString::fromUtf8(a3_);const auto a4 = QString::fromUtf8(a4_);const auto a5 = QString::fromUtf8(a5_);const auto a6 = QString::fromUtf8(a6_);return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->arg(a1,a2,a3,a4,a5,a6)};}

//tag=1050
//arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6, const QString & a7) const
void* c_QString__arg_QString_QString_QString_QString_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_,const char *a4_,const char *a5_,const char *a6_,const char *a7_){const auto a1 = QString::fromUtf8(a1_);const auto a2 = QString::fromUtf8(a2_);const auto a3 = QString::fromUtf8(a3_);const auto a4 = QString::fromUtf8(a4_);const auto a5 = QString::fromUtf8(a5_);const auto a6 = QString::fromUtf8(a6_);const auto a7 = QString::fromUtf8(a7_);return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->arg(a1,a2,a3,a4,a5,a6,a7)};}

//tag=1050
//arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6, const QString & a7, const QString & a8) const
void* c_QString__arg_QString_QString_QString_QString_QString_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_,const char *a4_,const char *a5_,const char *a6_,const char *a7_,const char *a8_){const auto a1 = QString::fromUtf8(a1_);const auto a2 = QString::fromUtf8(a2_);const auto a3 = QString::fromUtf8(a3_);const auto a4 = QString::fromUtf8(a4_);const auto a5 = QString::fromUtf8(a5_);const auto a6 = QString::fromUtf8(a6_);const auto a7 = QString::fromUtf8(a7_);const auto a8 = QString::fromUtf8(a8_);return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->arg(a1,a2,a3,a4,a5,a6,a7,a8)};}

//tag=1050
//arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6, const QString & a7, const QString & a8, const QString & a9) const
void* c_QString__arg_QString_QString_QString_QString_QString_QString_QString_QString_QString(void *thisObj,const char *a1_,const char *a2_,const char *a3_,const char *a4_,const char *a5_,const char *a6_,const char *a7_,const char *a8_,const char *a9_){const auto a1 = QString::fromUtf8(a1_);const auto a2 = QString::fromUtf8(a2_);const auto a3 = QString::fromUtf8(a3_);const auto a4 = QString::fromUtf8(a4_);const auto a5 = QString::fromUtf8(a5_);const auto a6 = QString::fromUtf8(a6_);const auto a7 = QString::fromUtf8(a7_);const auto a8 = QString::fromUtf8(a8_);const auto a9 = QString::fromUtf8(a9_);return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->arg(a1,a2,a3,a4,a5,a6,a7,a8,a9)};}

//tag=1050
//arg(int a, int fieldWidth, int base) const
void* c_QString__arg_int_int_int(void *thisObj,int a,int fieldWidth,int base){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->arg(a,fieldWidth,base)};}

//tag=1050
//arg(long a, int fieldwidth, int base) const
void* c_QString__arg_long_int_int(void *thisObj,long a,int fieldwidth,int base){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->arg(a,fieldwidth,base)};}

//tag=1050
//arg(qint64 a, int fieldwidth, int base) const
void* c_QString__arg_qint64_int_int(void *thisObj,qint64 a,int fieldwidth,int base){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->arg(a,fieldwidth,base)};}

//tag=1050
//arg(short a, int fieldWidth, int base) const
void* c_QString__arg_short_int_int(void *thisObj,short a,int fieldWidth,int base){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->arg(a,fieldWidth,base)};}

//tag=1050
//asprintf(const char * format)
void* c_static_QString__asprintf_char(const char * format){return 
//tag=1068

//tag=1072
new Dartagnan::ValueWrapper<QString>{KDDockWidgetsBindings_wrappersNS::QString_wrapper::asprintf(format)};}

//tag=1050
//capacity() const
int c_QString__capacity(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->capacity();}

//tag=1050
//chop(int n)
void c_QString__chop_int(void *thisObj,int n){
//tag=1010
fromPtr(thisObj)->chop(n);}

//tag=1050
//chopped(int n) const
void* c_QString__chopped_int(void *thisObj,int n){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->chopped(n)};}

//tag=1050
//clear()
void c_QString__clear(void *thisObj){
//tag=1010
fromPtr(thisObj)->clear();}

//tag=1050
//compare(const QString & s) const
int c_QString__compare_QString(void *thisObj,const char *s_){const auto s = QString::fromUtf8(s_);return 
//tag=1010
fromPtr(thisObj)->compare(s);}

//tag=1050
//compare(const QString & s1, const QString & s2)
int c_static_QString__compare_QString_QString(const char *s1_,const char *s2_){const auto s1 = QString::fromUtf8(s1_);const auto s2 = QString::fromUtf8(s2_);return 
//tag=1068
KDDockWidgetsBindings_wrappersNS::QString_wrapper::compare(s1,s2);}

//tag=1050
//contains(const QString & s) const
bool c_QString__contains_QString(void *thisObj,const char *s_){const auto s = QString::fromUtf8(s_);return 
//tag=1010
fromPtr(thisObj)->contains(s);}

//tag=1050
//count() const
int c_QString__count(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->count();}

//tag=1050
//count(const QString & s) const
int c_QString__count_QString(void *thisObj,const char *s_){const auto s = QString::fromUtf8(s_);return 
//tag=1010
fromPtr(thisObj)->count(s);}

//tag=1050
//detach()
void c_QString__detach(void *thisObj){
//tag=1010
fromPtr(thisObj)->detach();}

//tag=1050
//endsWith(const QString & s) const
bool c_QString__endsWith_QString(void *thisObj,const char *s_){const auto s = QString::fromUtf8(s_);return 
//tag=1010
fromPtr(thisObj)->endsWith(s);}

//tag=1050
//fromLatin1(const QByteArray & str)
void* c_static_QString__fromLatin1_QByteArray(void* str_){auto &str = *reinterpret_cast<QByteArray *>(str_);return 
//tag=1068

//tag=1072
new Dartagnan::ValueWrapper<QString>{KDDockWidgetsBindings_wrappersNS::QString_wrapper::fromLatin1(str)};}

//tag=1050
//fromLatin1(const char * str, int size)
void* c_static_QString__fromLatin1_char_int(const char * str,int size){return 
//tag=1068

//tag=1072
new Dartagnan::ValueWrapper<QString>{KDDockWidgetsBindings_wrappersNS::QString_wrapper::fromLatin1(str,size)};}

//tag=1050
//fromLocal8Bit(const QByteArray & str)
void* c_static_QString__fromLocal8Bit_QByteArray(void* str_){auto &str = *reinterpret_cast<QByteArray *>(str_);return 
//tag=1068

//tag=1072
new Dartagnan::ValueWrapper<QString>{KDDockWidgetsBindings_wrappersNS::QString_wrapper::fromLocal8Bit(str)};}

//tag=1050
//fromLocal8Bit(const char * str, int size)
void* c_static_QString__fromLocal8Bit_char_int(const char * str,int size){return 
//tag=1068

//tag=1072
new Dartagnan::ValueWrapper<QString>{KDDockWidgetsBindings_wrappersNS::QString_wrapper::fromLocal8Bit(str,size)};}

//tag=1050
//fromUtf8(const QByteArray & str)
void* c_static_QString__fromUtf8_QByteArray(void* str_){auto &str = *reinterpret_cast<QByteArray *>(str_);return 
//tag=1068

//tag=1072
new Dartagnan::ValueWrapper<QString>{KDDockWidgetsBindings_wrappersNS::QString_wrapper::fromUtf8(str)};}

//tag=1050
//fromUtf8(const char * str, int size)
void* c_static_QString__fromUtf8_char_int(const char * str,int size){return 
//tag=1068

//tag=1072
new Dartagnan::ValueWrapper<QString>{KDDockWidgetsBindings_wrappersNS::QString_wrapper::fromUtf8(str,size)};}

//tag=1050
//indexOf(const QString & s, int from) const
int c_QString__indexOf_QString_int(void *thisObj,const char *s_,int from){const auto s = QString::fromUtf8(s_);return 
//tag=1010
fromPtr(thisObj)->indexOf(s,from);}

//tag=1050
//insert(int i, const QString & s)
void* c_QString__insert_int_QString(void *thisObj,int i,const char *s_){const auto s = QString::fromUtf8(s_);return 
//tag=1010

//tag=1070
&fromPtr(thisObj)->insert(i,s);}

//tag=1050
//isDetached() const
bool c_QString__isDetached(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->isDetached();}

//tag=1050
//isEmpty() const
bool c_QString__isEmpty(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->isEmpty();}

//tag=1050
//isLower() const
bool c_QString__isLower(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->isLower();}

//tag=1050
//isNull() const
bool c_QString__isNull(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->isNull();}

//tag=1050
//isRightToLeft() const
bool c_QString__isRightToLeft(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->isRightToLeft();}

//tag=1050
//isSharedWith(const QString & other) const
bool c_QString__isSharedWith_QString(void *thisObj,const char *other_){const auto other = QString::fromUtf8(other_);return 
//tag=1010
fromPtr(thisObj)->isSharedWith(other);}

//tag=1050
//isSimpleText() const
bool c_QString__isSimpleText(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->isSimpleText();}

//tag=1050
//isUpper() const
bool c_QString__isUpper(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->isUpper();}

//tag=1050
//isValidUtf16() const
bool c_QString__isValidUtf16(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->isValidUtf16();}

//tag=1050
//lastIndexOf(const QString & s, int from) const
int c_QString__lastIndexOf_QString_int(void *thisObj,const char *s_,int from){const auto s = QString::fromUtf8(s_);return 
//tag=1010
fromPtr(thisObj)->lastIndexOf(s,from);}

//tag=1050
//left(int n) const
void* c_QString__left_int(void *thisObj,int n){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->left(n)};}

//tag=1050
//leftJustified(int width) const
void* c_QString__leftJustified_int(void *thisObj,int width){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->leftJustified(width)};}

//tag=1050
//length() const
int c_QString__length(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->length();}

//tag=1050
//localeAwareCompare(const QString & s) const
int c_QString__localeAwareCompare_QString(void *thisObj,const char *s_){const auto s = QString::fromUtf8(s_);return 
//tag=1010
fromPtr(thisObj)->localeAwareCompare(s);}

//tag=1050
//localeAwareCompare(const QString & s1, const QString & s2)
int c_static_QString__localeAwareCompare_QString_QString(const char *s1_,const char *s2_){const auto s1 = QString::fromUtf8(s1_);const auto s2 = QString::fromUtf8(s2_);return 
//tag=1068
KDDockWidgetsBindings_wrappersNS::QString_wrapper::localeAwareCompare(s1,s2);}

//tag=1050
//mid(int position, int n) const
void* c_QString__mid_int_int(void *thisObj,int position,int n){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->mid(position,n)};}

//tag=1050
//number(int arg__1, int base)
void* c_static_QString__number_int_int(int arg__1,int base){return 
//tag=1068

//tag=1072
new Dartagnan::ValueWrapper<QString>{KDDockWidgetsBindings_wrappersNS::QString_wrapper::number(arg__1,base)};}

//tag=1050
//number(long arg__1, int base)
void* c_static_QString__number_long_int(long arg__1,int base){return 
//tag=1068

//tag=1072
new Dartagnan::ValueWrapper<QString>{KDDockWidgetsBindings_wrappersNS::QString_wrapper::number(arg__1,base)};}

//tag=1050
//number(qint64 arg__1, int base)
void* c_static_QString__number_qint64_int(qint64 arg__1,int base){return 
//tag=1068

//tag=1072
new Dartagnan::ValueWrapper<QString>{KDDockWidgetsBindings_wrappersNS::QString_wrapper::number(arg__1,base)};}

//tag=1050
//prepend(const QString & s)
void* c_QString__prepend_QString(void *thisObj,const char *s_){const auto s = QString::fromUtf8(s_);return 
//tag=1010

//tag=1070
&fromPtr(thisObj)->prepend(s);}

//tag=1050
//push_back(const QString & s)
void c_QString__push_back_QString(void *thisObj,const char *s_){const auto s = QString::fromUtf8(s_);
//tag=1010
fromPtr(thisObj)->push_back(s);}

//tag=1050
//push_front(const QString & s)
void c_QString__push_front_QString(void *thisObj,const char *s_){const auto s = QString::fromUtf8(s_);
//tag=1010
fromPtr(thisObj)->push_front(s);}

//tag=1050
//remove(const QString & s)
void* c_QString__remove_QString(void *thisObj,const char *s_){const auto s = QString::fromUtf8(s_);return 
//tag=1010

//tag=1070
&fromPtr(thisObj)->remove(s);}

//tag=1050
//remove(int i, int len)
void* c_QString__remove_int_int(void *thisObj,int i,int len){return 
//tag=1010

//tag=1070
&fromPtr(thisObj)->remove(i,len);}

//tag=1050
//repeated(int times) const
void* c_QString__repeated_int(void *thisObj,int times){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->repeated(times)};}

//tag=1050
//replace(const QString & before, const QString & after)
void* c_QString__replace_QString_QString(void *thisObj,const char *before_,const char *after_){const auto before = QString::fromUtf8(before_);const auto after = QString::fromUtf8(after_);return 
//tag=1010

//tag=1070
&fromPtr(thisObj)->replace(before,after);}

//tag=1050
//replace(int i, int len, const QString & after)
void* c_QString__replace_int_int_QString(void *thisObj,int i,int len,const char *after_){const auto after = QString::fromUtf8(after_);return 
//tag=1010

//tag=1070
&fromPtr(thisObj)->replace(i,len,after);}

//tag=1050
//reserve(int size)
void c_QString__reserve_int(void *thisObj,int size){
//tag=1010
fromPtr(thisObj)->reserve(size);}

//tag=1050
//resize(int size)
void c_QString__resize_int(void *thisObj,int size){
//tag=1010
fromPtr(thisObj)->resize(size);}

//tag=1050
//right(int n) const
void* c_QString__right_int(void *thisObj,int n){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->right(n)};}

//tag=1050
//rightJustified(int width) const
void* c_QString__rightJustified_int(void *thisObj,int width){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->rightJustified(width)};}

//tag=1050
//section(const QString & in_sep, int start, int end) const
void* c_QString__section_QString_int_int(void *thisObj,const char *in_sep_,int start,int end){const auto in_sep = QString::fromUtf8(in_sep_);return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->section(in_sep,start,end)};}

//tag=1050
//setNum(int arg__1, int base)
void* c_QString__setNum_int_int(void *thisObj,int arg__1,int base){return 
//tag=1010

//tag=1070
&fromPtr(thisObj)->setNum(arg__1,base);}

//tag=1050
//setNum(long arg__1, int base)
void* c_QString__setNum_long_int(void *thisObj,long arg__1,int base){return 
//tag=1010

//tag=1070
&fromPtr(thisObj)->setNum(arg__1,base);}

//tag=1050
//setNum(qint64 arg__1, int base)
void* c_QString__setNum_qint64_int(void *thisObj,qint64 arg__1,int base){return 
//tag=1010

//tag=1070
&fromPtr(thisObj)->setNum(arg__1,base);}

//tag=1050
//setNum(short arg__1, int base)
void* c_QString__setNum_short_int(void *thisObj,short arg__1,int base){return 
//tag=1010

//tag=1070
&fromPtr(thisObj)->setNum(arg__1,base);}

//tag=1050
//shrink_to_fit()
void c_QString__shrink_to_fit(void *thisObj){
//tag=1010
fromPtr(thisObj)->shrink_to_fit();}

//tag=1050
//simplified()
void* c_QString__simplified(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->simplified()};}

//tag=1050
//size() const
int c_QString__size(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->size();}

//tag=1050
//squeeze()
void c_QString__squeeze(void *thisObj){
//tag=1010
fromPtr(thisObj)->squeeze();}

//tag=1050
//startsWith(const QString & s) const
bool c_QString__startsWith_QString(void *thisObj,const char *s_){const auto s = QString::fromUtf8(s_);return 
//tag=1010
fromPtr(thisObj)->startsWith(s);}

//tag=1050
//toCaseFolded()
void* c_QString__toCaseFolded(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->toCaseFolded()};}

//tag=1050
//toHtmlEscaped() const
void* c_QString__toHtmlEscaped(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->toHtmlEscaped()};}

//tag=1050
//toLatin1()
void* c_QString__toLatin1(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr(thisObj)->toLatin1()};}

//tag=1050
//toLocal8Bit()
void* c_QString__toLocal8Bit(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr(thisObj)->toLocal8Bit()};}

//tag=1050
//toLower()
void* c_QString__toLower(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->toLower()};}

//tag=1050
//toUpper()
void* c_QString__toUpper(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->toUpper()};}

//tag=1050
//toUtf8()
void* c_QString__toUtf8(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QByteArray>{fromPtr(thisObj)->toUtf8()};}

//tag=1050
//trimmed()
void* c_QString__trimmed(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QString>{fromPtr(thisObj)->trimmed()};}

//tag=1050
//truncate(int pos)
void c_QString__truncate_int(void *thisObj,int pos){
//tag=1010
fromPtr(thisObj)->truncate(pos);}
void c_QString__destructor(void *thisObj)
{

//tag=1055
delete fromPtr(thisObj);}
}
