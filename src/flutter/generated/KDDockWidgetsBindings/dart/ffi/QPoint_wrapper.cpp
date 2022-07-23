/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "QPoint_wrapper.h"


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
QPoint_wrapper::QPoint_wrapper() : ::QPoint() {}

//tag=1006
QPoint_wrapper::QPoint_wrapper(int xpos,int ypos) : ::QPoint(xpos,ypos) {}
int QPoint_wrapper::dotProduct(const QPoint & p1,const QPoint & p2){
//tag=1000

//tag=1004
return ::QPoint::dotProduct(p1,p2);}
bool QPoint_wrapper::isNull()const{
//tag=1000

//tag=1004
return ::QPoint::isNull();}
int QPoint_wrapper::manhattanLength()const{
//tag=1000

//tag=1004
return ::QPoint::manhattanLength();}
void QPoint_wrapper::setX(int x){
//tag=1000

//tag=1004
::QPoint::setX(x);}
void QPoint_wrapper::setY(int y){
//tag=1000

//tag=1004
::QPoint::setY(y);}
QPoint QPoint_wrapper::transposed()const{
//tag=1000

//tag=1004
return ::QPoint::transposed();}
int QPoint_wrapper::x()const{
//tag=1000

//tag=1004
return ::QPoint::x();}
int QPoint_wrapper::y()const{
//tag=1000

//tag=1004
return ::QPoint::y();}

//tag=1005
QPoint_wrapper::~QPoint_wrapper() {}

}
//tag=1013
static QPoint* fromPtr(void *ptr)
{return reinterpret_cast<QPoint*>(ptr);}
//tag=1014
static KDDockWidgetsBindings_wrappersNS::QPoint_wrapper* fromWrapperPtr(void *ptr)
{return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QPoint_wrapper*>(ptr);}extern "C" {

//tag=1049
 void c_QPoint_Finalizer(void *, void *cppObj, void *){delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QPoint_wrapper *>(cppObj);}void * c_QPoint__constructor()
{

//tag=1056
auto ptr = new KDDockWidgetsBindings_wrappersNS::QPoint_wrapper();return reinterpret_cast<void*>(ptr);}
void * c_QPoint__constructor_int_int(int xpos,int ypos)
{

//tag=1056
auto ptr = new KDDockWidgetsBindings_wrappersNS::QPoint_wrapper(xpos,ypos);return reinterpret_cast<void*>(ptr);}

//tag=1050
//dotProduct(const QPoint & p1, const QPoint & p2)
int c_static_QPoint__dotProduct_QPoint_QPoint(void* p1_,void* p2_){auto &p1 = *reinterpret_cast<QPoint *>(p1_);auto &p2 = *reinterpret_cast<QPoint *>(p2_);return 
//tag=1068
KDDockWidgetsBindings_wrappersNS::QPoint_wrapper::dotProduct(p1,p2);}

//tag=1050
//isNull() const
bool c_QPoint__isNull(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->isNull();}

//tag=1050
//manhattanLength() const
int c_QPoint__manhattanLength(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->manhattanLength();}

//tag=1050
//setX(int x)
void c_QPoint__setX_int(void *thisObj,int x){
//tag=1010
fromPtr(thisObj)->setX(x);}

//tag=1050
//setY(int y)
void c_QPoint__setY_int(void *thisObj,int y){
//tag=1010
fromPtr(thisObj)->setY(y);}

//tag=1050
//transposed() const
void* c_QPoint__transposed(void *thisObj){return 
//tag=1010

//tag=1072
new Dartagnan::ValueWrapper<QPoint>{fromPtr(thisObj)->transposed()};}

//tag=1050
//x() const
int c_QPoint__x(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->x();}

//tag=1050
//y() const
int c_QPoint__y(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->y();}
void c_QPoint__destructor(void *thisObj)
{

//tag=1055
delete fromPtr(thisObj);}
}
