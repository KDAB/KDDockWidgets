/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Platform_wrapper.h"


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
Platform_wrapper::Platform_wrapper() : ::KDDockWidgets::Platform() {}
QString Platform_wrapper::applicationName()const{
//tag=1000
if (m_applicationNameCallback) {
//tag=1001
const void* thisPtr = this;
return *m_applicationNameCallback(const_cast<void *>(thisPtr));} else {
//tag=1015
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}}
//tag=1009
QString Platform_wrapper::applicationName_nocallback()const{
//tag=1003

//tag=1007
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}
KDDockWidgets::ViewFactory * Platform_wrapper::createDefaultViewFactory(){
//tag=1000
if (m_createDefaultViewFactoryCallback) {
//tag=1001
const void* thisPtr = this;
return m_createDefaultViewFactoryCallback(const_cast<void *>(thisPtr));} else {
//tag=1015
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}}
//tag=1009
KDDockWidgets::ViewFactory * Platform_wrapper::createDefaultViewFactory_nocallback(){
//tag=1003

//tag=1007
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}
bool Platform_wrapper::hasActivePopup()const{
//tag=1000
if (m_hasActivePopupCallback) {
//tag=1001
const void* thisPtr = this;
return m_hasActivePopupCallback(const_cast<void *>(thisPtr));} else {
//tag=1002
return ::KDDockWidgets::Platform::hasActivePopup();}}
//tag=1009
bool Platform_wrapper::hasActivePopup_nocallback()const{
//tag=1003
return ::KDDockWidgets::Platform::hasActivePopup();}
bool Platform_wrapper::inDisallowedDragView(QPoint globalPos)const{
//tag=1000
if (m_inDisallowedDragViewCallback) {
//tag=1001
const void* thisPtr = this;
return m_inDisallowedDragViewCallback(const_cast<void *>(thisPtr),globalPos);} else {
//tag=1015
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}}
//tag=1009
bool Platform_wrapper::inDisallowedDragView_nocallback(QPoint globalPos)const{
//tag=1003

//tag=1007
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}
KDDockWidgets::Platform * Platform_wrapper::instance(){
//tag=1000

//tag=1004
return ::KDDockWidgets::Platform::instance();}
bool Platform_wrapper::isLeftMouseButtonPressed()const{
//tag=1000
if (m_isLeftMouseButtonPressedCallback) {
//tag=1001
const void* thisPtr = this;
return m_isLeftMouseButtonPressedCallback(const_cast<void *>(thisPtr));} else {
//tag=1015
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}}
//tag=1009
bool Platform_wrapper::isLeftMouseButtonPressed_nocallback()const{
//tag=1003

//tag=1007
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}
bool Platform_wrapper::isProcessingAppQuitEvent()const{
//tag=1000
if (m_isProcessingAppQuitEventCallback) {
//tag=1001
const void* thisPtr = this;
return m_isProcessingAppQuitEventCallback(const_cast<void *>(thisPtr));} else {
//tag=1015
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}}
//tag=1009
bool Platform_wrapper::isProcessingAppQuitEvent_nocallback()const{
//tag=1003

//tag=1007
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}
bool Platform_wrapper::isQtQuick()const{
//tag=1000

//tag=1004
return ::KDDockWidgets::Platform::isQtQuick();}
bool Platform_wrapper::isQtWidgets()const{
//tag=1000

//tag=1004
return ::KDDockWidgets::Platform::isQtWidgets();}
const char * Platform_wrapper::name()const{
//tag=1000
if (m_nameCallback) {
//tag=1001
const void* thisPtr = this;
return m_nameCallback(const_cast<void *>(thisPtr));} else {
//tag=1015
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}}
//tag=1009
const char * Platform_wrapper::name_nocallback()const{
//tag=1003

//tag=1007
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}
QString Platform_wrapper::organizationName()const{
//tag=1000
if (m_organizationNameCallback) {
//tag=1001
const void* thisPtr = this;
return *m_organizationNameCallback(const_cast<void *>(thisPtr));} else {
//tag=1015
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}}
//tag=1009
QString Platform_wrapper::organizationName_nocallback()const{
//tag=1003

//tag=1007
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}
void Platform_wrapper::restoreMouseCursor(){
//tag=1000
if (m_restoreMouseCursorCallback) {
//tag=1001
const void* thisPtr = this;
m_restoreMouseCursorCallback(const_cast<void *>(thisPtr));} else {
//tag=1015
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return;}}
//tag=1009
void Platform_wrapper::restoreMouseCursor_nocallback(){
//tag=1003

//tag=1007
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return;}
int Platform_wrapper::screenNumberFor(KDDockWidgets::View * arg__1)const{
//tag=1000
if (m_screenNumberForCallback) {
//tag=1001
const void* thisPtr = this;
return m_screenNumberForCallback(const_cast<void *>(thisPtr),arg__1);} else {
//tag=1015
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}}
//tag=1009
int Platform_wrapper::screenNumberFor_nocallback(KDDockWidgets::View * arg__1)const{
//tag=1003

//tag=1007
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}
QSize Platform_wrapper::screenSizeFor(KDDockWidgets::View * arg__1)const{
//tag=1000
if (m_screenSizeForCallback) {
//tag=1001
const void* thisPtr = this;
return *m_screenSizeForCallback(const_cast<void *>(thisPtr),arg__1);} else {
//tag=1015
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}}
//tag=1009
QSize Platform_wrapper::screenSizeFor_nocallback(KDDockWidgets::View * arg__1)const{
//tag=1003

//tag=1007
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}
int Platform_wrapper::startDragDistance()const{
//tag=1000

//tag=1004
return ::KDDockWidgets::Platform::startDragDistance();}
int Platform_wrapper::startDragDistance_impl()const{
//tag=1000
if (m_startDragDistance_implCallback) {
//tag=1001
const void* thisPtr = this;
return m_startDragDistance_implCallback(const_cast<void *>(thisPtr));} else {
//tag=1002
return ::KDDockWidgets::Platform::startDragDistance_impl();}}
//tag=1009
int Platform_wrapper::startDragDistance_impl_nocallback()const{
//tag=1003
return ::KDDockWidgets::Platform::startDragDistance_impl();}
void Platform_wrapper::ungrabMouse(){
//tag=1000
if (m_ungrabMouseCallback) {
//tag=1001
const void* thisPtr = this;
m_ungrabMouseCallback(const_cast<void *>(thisPtr));} else {
//tag=1015
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return;}}
//tag=1009
void Platform_wrapper::ungrabMouse_nocallback(){
//tag=1003

//tag=1007
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return;}
bool Platform_wrapper::usesFallbackMouseGrabber()const{
//tag=1000
if (m_usesFallbackMouseGrabberCallback) {
//tag=1001
const void* thisPtr = this;
return m_usesFallbackMouseGrabberCallback(const_cast<void *>(thisPtr));} else {
//tag=1015
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}}
//tag=1009
bool Platform_wrapper::usesFallbackMouseGrabber_nocallback()const{
//tag=1003

//tag=1007
qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
return {};}

//tag=1005
Platform_wrapper::~Platform_wrapper() {}

}
//tag=1013
static KDDockWidgets::Platform* fromPtr(void *ptr)
{return reinterpret_cast<KDDockWidgets::Platform*>(ptr);}
//tag=1014
static KDDockWidgetsBindings_wrappersNS::Platform_wrapper* fromWrapperPtr(void *ptr)
{return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(ptr);}extern "C" {

//tag=1049
 void c_KDDockWidgets__Platform_Finalizer(void *, void *cppObj, void *){delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(cppObj);}void * c_KDDockWidgets__Platform__constructor()
{

//tag=1056
auto ptr = new KDDockWidgetsBindings_wrappersNS::Platform_wrapper();return reinterpret_cast<void*>(ptr);}

//tag=1050
//applicationName() const
void* c_KDDockWidgets__Platform__applicationName(void *thisObj){return 
//tag=1016

//tag=1072
new Dartagnan::ValueWrapper<QString>{[&]{auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->applicationName_nocallback();} else {    return targetPtr->applicationName();}}()};}

//tag=1050
//createDefaultViewFactory()
void* c_KDDockWidgets__Platform__createDefaultViewFactory(void *thisObj){return 
//tag=1016
[&]{auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createDefaultViewFactory_nocallback();} else {    return targetPtr->createDefaultViewFactory();}}();}

//tag=1050
//hasActivePopup() const
bool c_KDDockWidgets__Platform__hasActivePopup(void *thisObj){return 
//tag=1016
[&]{auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hasActivePopup_nocallback();} else {    return targetPtr->hasActivePopup();}}();}

//tag=1050
//inDisallowedDragView(QPoint globalPos) const
bool c_KDDockWidgets__Platform__inDisallowedDragView_QPoint(void *thisObj,void* globalPos_){auto &globalPos = *reinterpret_cast<QPoint *>(globalPos_);return 
//tag=1016
[&]{auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->inDisallowedDragView_nocallback(globalPos);} else {    return targetPtr->inDisallowedDragView(globalPos);}}();}

//tag=1050
//instance()
void* c_static_KDDockWidgets__Platform__instance(){return 
//tag=1068
KDDockWidgetsBindings_wrappersNS::Platform_wrapper::instance();}

//tag=1050
//isLeftMouseButtonPressed() const
bool c_KDDockWidgets__Platform__isLeftMouseButtonPressed(void *thisObj){return 
//tag=1016
[&]{auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isLeftMouseButtonPressed_nocallback();} else {    return targetPtr->isLeftMouseButtonPressed();}}();}

//tag=1050
//isProcessingAppQuitEvent() const
bool c_KDDockWidgets__Platform__isProcessingAppQuitEvent(void *thisObj){return 
//tag=1016
[&]{auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isProcessingAppQuitEvent_nocallback();} else {    return targetPtr->isProcessingAppQuitEvent();}}();}

//tag=1050
//isQtQuick() const
bool c_KDDockWidgets__Platform__isQtQuick(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->isQtQuick();}

//tag=1050
//isQtWidgets() const
bool c_KDDockWidgets__Platform__isQtWidgets(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->isQtWidgets();}

//tag=1050
//name() const
const char * c_KDDockWidgets__Platform__name(void *thisObj){return 
//tag=1016
[&]{auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->name_nocallback();} else {    return targetPtr->name();}}();}

//tag=1050
//organizationName() const
void* c_KDDockWidgets__Platform__organizationName(void *thisObj){return 
//tag=1016

//tag=1072
new Dartagnan::ValueWrapper<QString>{[&]{auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->organizationName_nocallback();} else {    return targetPtr->organizationName();}}()};}

//tag=1050
//restoreMouseCursor()
void c_KDDockWidgets__Platform__restoreMouseCursor(void *thisObj){
//tag=1016
[&]{auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->restoreMouseCursor_nocallback();} else {    return targetPtr->restoreMouseCursor();}}();}

//tag=1050
//screenNumberFor(KDDockWidgets::View * arg__1) const
int c_KDDockWidgets__Platform__screenNumberFor_View(void *thisObj,void* arg__1_){auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);return 
//tag=1016
[&]{auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->screenNumberFor_nocallback(arg__1);} else {    return targetPtr->screenNumberFor(arg__1);}}();}

//tag=1050
//screenSizeFor(KDDockWidgets::View * arg__1) const
void* c_KDDockWidgets__Platform__screenSizeFor_View(void *thisObj,void* arg__1_){auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);return 
//tag=1016

//tag=1072
new Dartagnan::ValueWrapper<QSize>{[&]{auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->screenSizeFor_nocallback(arg__1);} else {    return targetPtr->screenSizeFor(arg__1);}}()};}

//tag=1050
//startDragDistance() const
int c_KDDockWidgets__Platform__startDragDistance(void *thisObj){return 
//tag=1010
fromPtr(thisObj)->startDragDistance();}

//tag=1050
//startDragDistance_impl() const
int c_KDDockWidgets__Platform__startDragDistance_impl(void *thisObj){return 
//tag=1011

//tag=1074
fromWrapperPtr(thisObj)->startDragDistance_impl_nocallback();}

//tag=1050
//ungrabMouse()
void c_KDDockWidgets__Platform__ungrabMouse(void *thisObj){
//tag=1016
[&]{auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->ungrabMouse_nocallback();} else {    return targetPtr->ungrabMouse();}}();}

//tag=1050
//usesFallbackMouseGrabber() const
bool c_KDDockWidgets__Platform__usesFallbackMouseGrabber(void *thisObj){return 
//tag=1016
[&]{auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->usesFallbackMouseGrabber_nocallback();} else {    return targetPtr->usesFallbackMouseGrabber();}}();}
void c_KDDockWidgets__Platform__destructor(void *thisObj)
{

//tag=1055
delete fromPtr(thisObj);}
void c_KDDockWidgets__Platform__registerVirtualMethodCallback(void *ptr, void *callback, int methodId){
//tag=1048
auto wrapper = fromWrapperPtr(ptr);
switch (methodId) {
case 680:
wrapper->m_applicationNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_applicationName>(callback);break;case 681:
wrapper->m_createDefaultViewFactoryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_createDefaultViewFactory>(callback);break;case 682:
wrapper->m_hasActivePopupCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_hasActivePopup>(callback);break;case 683:
wrapper->m_inDisallowedDragViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_inDisallowedDragView>(callback);break;case 685:
wrapper->m_isLeftMouseButtonPressedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_isLeftMouseButtonPressed>(callback);break;case 686:
wrapper->m_isProcessingAppQuitEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_isProcessingAppQuitEvent>(callback);break;case 689:
wrapper->m_nameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_name>(callback);break;case 690:
wrapper->m_organizationNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_organizationName>(callback);break;case 691:
wrapper->m_restoreMouseCursorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_restoreMouseCursor>(callback);break;case 692:
wrapper->m_screenNumberForCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_screenNumberFor>(callback);break;case 693:
wrapper->m_screenSizeForCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_screenSizeFor>(callback);break;case 695:
wrapper->m_startDragDistance_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_startDragDistance_impl>(callback);break;case 696:
wrapper->m_ungrabMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_ungrabMouse>(callback);break;case 697:
wrapper->m_usesFallbackMouseGrabberCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_usesFallbackMouseGrabber>(callback);break;}
}}
