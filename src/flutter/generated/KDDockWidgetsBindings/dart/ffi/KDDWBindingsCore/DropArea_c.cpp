/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "DropArea_c.h"


#include <iostream>

#include <cassert>


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
namespace KDDWBindingsCore {
DropArea_wrapper::DropArea_wrapper(KDDockWidgets::Core::View *parent, QFlags<KDDockWidgets::MainWindowOption> options, bool isMDIWrapper)
    : ::KDDockWidgets::Core::DropArea(parent, options, isMDIWrapper)
{
}
void DropArea_wrapper::addDockWidget(KDDockWidgets::Core::DockWidget *dw, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget *relativeTo, KDDockWidgets::InitialOption initialOption)
{
    ::KDDockWidgets::Core::DropArea::addDockWidget(dw, location, relativeTo, initialOption);
}
void DropArea_wrapper::addMultiSplitter(KDDockWidgets::Core::DropArea *splitter, KDDockWidgets::Location location, KDDockWidgets::Core::Group *relativeTo, KDDockWidgets::InitialOption option)
{
    ::KDDockWidgets::Core::DropArea::addMultiSplitter(splitter, location, relativeTo, option);
}
void DropArea_wrapper::addWidget(KDDockWidgets::Core::View *widget, KDDockWidgets::Location location, KDDockWidgets::Core::Group *relativeTo, KDDockWidgets::InitialOption option)
{
    ::KDDockWidgets::Core::DropArea::addWidget(widget, location, relativeTo, option);
}
KDDockWidgets::Size DropArea_wrapper::availableSize() const
{
    return ::KDDockWidgets::Core::DropArea::availableSize();
}
KDDockWidgets::Core::Item *DropArea_wrapper::centralFrame() const
{
    return ::KDDockWidgets::Core::DropArea::centralFrame();
}
KDDockWidgets::Core::Group *DropArea_wrapper::centralGroup() const
{
    return ::KDDockWidgets::Core::DropArea::centralGroup();
}
bool DropArea_wrapper::containsDockWidget(KDDockWidgets::Core::DockWidget *arg__1) const
{
    return ::KDDockWidgets::Core::DropArea::containsDockWidget(arg__1);
}
KDDockWidgets::Core::Group *DropArea_wrapper::createCentralFrame(QFlags<KDDockWidgets::MainWindowOption> options)
{
    return ::KDDockWidgets::Core::DropArea::createCentralFrame(options);
}
KDDockWidgets::DropLocation DropArea_wrapper::currentDropLocation() const
{
    return ::KDDockWidgets::Core::DropArea::currentDropLocation();
}
bool DropArea_wrapper::drop(KDDockWidgets::Core::View *droppedwindow, KDDockWidgets::Location location, KDDockWidgets::Core::Group *relativeTo)
{
    return ::KDDockWidgets::Core::DropArea::drop(droppedwindow, location, relativeTo);
}
KDDockWidgets::Core::DropIndicatorOverlay *DropArea_wrapper::dropIndicatorOverlay() const
{
    return ::KDDockWidgets::Core::DropArea::dropIndicatorOverlay();
}
KDDockWidgets::Core::Group *DropArea_wrapper::groupContainingPos(KDDockWidgets::Point globalPos) const
{
    return ::KDDockWidgets::Core::DropArea::groupContainingPos(globalPos);
}
bool DropArea_wrapper::hasSingleFloatingFrame() const
{
    return ::KDDockWidgets::Core::DropArea::hasSingleFloatingFrame();
}
bool DropArea_wrapper::hasSingleFrame() const
{
    return ::KDDockWidgets::Core::DropArea::hasSingleFrame();
}
bool DropArea_wrapper::isMDIWrapper() const
{
    return ::KDDockWidgets::Core::DropArea::isMDIWrapper();
}
void DropArea_wrapper::layoutEqually()
{
    ::KDDockWidgets::Core::DropArea::layoutEqually();
}
void DropArea_wrapper::layoutParentContainerEqually(KDDockWidgets::Core::DockWidget *arg__1)
{
    ::KDDockWidgets::Core::DropArea::layoutParentContainerEqually(arg__1);
}
KDDockWidgets::Core::DockWidget *DropArea_wrapper::mdiDockWidgetWrapper() const
{
    return ::KDDockWidgets::Core::DropArea::mdiDockWidgetWrapper();
}
void DropArea_wrapper::removeHover()
{
    ::KDDockWidgets::Core::DropArea::removeHover();
}
void DropArea_wrapper::setParentView_impl(KDDockWidgets::Core::View *parent)
{
    if (m_setParentView_implCallback) {
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Core::DropArea::setParentView_impl(parent);
    }
}
void DropArea_wrapper::setParentView_impl_nocallback(KDDockWidgets::Core::View *parent)
{
    ::KDDockWidgets::Core::DropArea::setParentView_impl(parent);
}
void DropArea_wrapper::updateFloatingActions()
{
    ::KDDockWidgets::Core::DropArea::updateFloatingActions();
}
bool DropArea_wrapper::validateInputs(KDDockWidgets::Core::View *widget, KDDockWidgets::Location location, const KDDockWidgets::Core::Group *relativeToFrame, KDDockWidgets::InitialOption option) const
{
    return ::KDDockWidgets::Core::DropArea::validateInputs(widget, location, relativeToFrame, option);
}
DropArea_wrapper::~DropArea_wrapper()
{
}

}
}
static KDDockWidgets::Core::DropArea *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Core::DropArea *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::KDDWBindingsCore::DropArea_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsCore::DropArea_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Core__DropArea_Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsCore::DropArea_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Core__DropArea__constructor_View_MainWindowOptions_bool(void *parent_, int options_, bool isMDIWrapper)
{
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    auto options = static_cast<QFlags<KDDockWidgets::MainWindowOption>>(options_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::KDDWBindingsCore::DropArea_wrapper(parent, options, isMDIWrapper);
    return reinterpret_cast<void *>(ptr);
}
// addDockWidget(KDDockWidgets::Core::DockWidget * dw, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget * relativeTo, KDDockWidgets::InitialOption initialOption)
void c_KDDockWidgets__Core__DropArea__addDockWidget_DockWidget_Location_DockWidget_InitialOption(void *thisObj, void *dw_, int location, void *relativeTo_, void *initialOption_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Core::DockWidget *>(dw_);
    auto relativeTo = reinterpret_cast<KDDockWidgets::Core::DockWidget *>(relativeTo_);
    assert(initialOption_);
    auto &initialOption = *reinterpret_cast<KDDockWidgets::InitialOption *>(initialOption_);
    fromPtr(thisObj)->addDockWidget(dw, static_cast<KDDockWidgets::Location>(location), relativeTo, initialOption);
}
// addMultiSplitter(KDDockWidgets::Core::DropArea * splitter, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo, KDDockWidgets::InitialOption option)
void c_KDDockWidgets__Core__DropArea__addMultiSplitter_DropArea_Location_Group_InitialOption(void *thisObj, void *splitter_, int location, void *relativeTo_, void *option_)
{
    auto splitter = reinterpret_cast<KDDockWidgets::Core::DropArea *>(splitter_);
    auto relativeTo = reinterpret_cast<KDDockWidgets::Core::Group *>(relativeTo_);
    assert(option_);
    auto &option = *reinterpret_cast<KDDockWidgets::InitialOption *>(option_);
    fromPtr(thisObj)->addMultiSplitter(splitter, static_cast<KDDockWidgets::Location>(location), relativeTo, option);
}
// addWidget(KDDockWidgets::Core::View * widget, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo, KDDockWidgets::InitialOption option)
void c_KDDockWidgets__Core__DropArea__addWidget_View_Location_Group_InitialOption(void *thisObj, void *widget_, int location, void *relativeTo_, void *option_)
{
    auto widget = reinterpret_cast<KDDockWidgets::Core::View *>(widget_);
    auto relativeTo = reinterpret_cast<KDDockWidgets::Core::Group *>(relativeTo_);
    assert(option_);
    auto &option = *reinterpret_cast<KDDockWidgets::InitialOption *>(option_);
    fromPtr(thisObj)->addWidget(widget, static_cast<KDDockWidgets::Location>(location), relativeTo, option);
}
// availableSize() const
void *c_KDDockWidgets__Core__DropArea__availableSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Size> { fromPtr(thisObj)->availableSize() };
}
// centralFrame() const
void *c_KDDockWidgets__Core__DropArea__centralFrame(void *thisObj)
{
    return fromPtr(thisObj)->centralFrame();
}
// centralGroup() const
void *c_KDDockWidgets__Core__DropArea__centralGroup(void *thisObj)
{
    return fromPtr(thisObj)->centralGroup();
}
// containsDockWidget(KDDockWidgets::Core::DockWidget * arg__1) const
bool c_KDDockWidgets__Core__DropArea__containsDockWidget_DockWidget(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Core::DockWidget *>(arg__1_);
    return fromPtr(thisObj)->containsDockWidget(arg__1);
}
// createCentralFrame(QFlags<KDDockWidgets::MainWindowOption> options)
void *c_static_KDDockWidgets__Core__DropArea__createCentralFrame_MainWindowOptions(int options_)
{
    auto options = static_cast<QFlags<KDDockWidgets::MainWindowOption>>(options_);
    return KDDockWidgetsBindings_wrappersNS::KDDWBindingsCore::DropArea_wrapper::createCentralFrame(options);
}
// currentDropLocation() const
int c_KDDockWidgets__Core__DropArea__currentDropLocation(void *thisObj)
{
    return int(fromPtr(thisObj)->currentDropLocation());
}
// drop(KDDockWidgets::Core::View * droppedwindow, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo)
bool c_KDDockWidgets__Core__DropArea__drop_View_Location_Group(void *thisObj, void *droppedwindow_, int location, void *relativeTo_)
{
    auto droppedwindow = reinterpret_cast<KDDockWidgets::Core::View *>(droppedwindow_);
    auto relativeTo = reinterpret_cast<KDDockWidgets::Core::Group *>(relativeTo_);
    return fromPtr(thisObj)->drop(droppedwindow, static_cast<KDDockWidgets::Location>(location), relativeTo);
}
// dropIndicatorOverlay() const
void *c_KDDockWidgets__Core__DropArea__dropIndicatorOverlay(void *thisObj)
{
    return fromPtr(thisObj)->dropIndicatorOverlay();
}
// groupContainingPos(KDDockWidgets::Point globalPos) const
void *c_KDDockWidgets__Core__DropArea__groupContainingPos_Point(void *thisObj, void *globalPos_)
{
    assert(globalPos_);
    auto &globalPos = *reinterpret_cast<KDDockWidgets::Point *>(globalPos_);
    return fromPtr(thisObj)->groupContainingPos(globalPos);
}
// hasSingleFloatingFrame() const
bool c_KDDockWidgets__Core__DropArea__hasSingleFloatingFrame(void *thisObj)
{
    return fromPtr(thisObj)->hasSingleFloatingFrame();
}
// hasSingleFrame() const
bool c_KDDockWidgets__Core__DropArea__hasSingleFrame(void *thisObj)
{
    return fromPtr(thisObj)->hasSingleFrame();
}
// isMDIWrapper() const
bool c_KDDockWidgets__Core__DropArea__isMDIWrapper(void *thisObj)
{
    return fromPtr(thisObj)->isMDIWrapper();
}
// layoutEqually()
void c_KDDockWidgets__Core__DropArea__layoutEqually(void *thisObj)
{
    fromPtr(thisObj)->layoutEqually();
}
// layoutParentContainerEqually(KDDockWidgets::Core::DockWidget * arg__1)
void c_KDDockWidgets__Core__DropArea__layoutParentContainerEqually_DockWidget(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Core::DockWidget *>(arg__1_);
    fromPtr(thisObj)->layoutParentContainerEqually(arg__1);
}
// mdiDockWidgetWrapper() const
void *c_KDDockWidgets__Core__DropArea__mdiDockWidgetWrapper(void *thisObj)
{
    return fromPtr(thisObj)->mdiDockWidgetWrapper();
}
// removeHover()
void c_KDDockWidgets__Core__DropArea__removeHover(void *thisObj)
{
    fromPtr(thisObj)->removeHover();
}
// setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__DropArea__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}
// updateFloatingActions()
void c_KDDockWidgets__Core__DropArea__updateFloatingActions(void *thisObj)
{
    fromPtr(thisObj)->updateFloatingActions();
}
// validateInputs(KDDockWidgets::Core::View * widget, KDDockWidgets::Location location, const KDDockWidgets::Core::Group * relativeToFrame, KDDockWidgets::InitialOption option) const
bool c_KDDockWidgets__Core__DropArea__validateInputs_View_Location_Group_InitialOption(void *thisObj, void *widget_, int location, void *relativeToFrame_, void *option_)
{
    auto widget = reinterpret_cast<KDDockWidgets::Core::View *>(widget_);
    auto relativeToFrame = reinterpret_cast<KDDockWidgets::Core::Group *>(relativeToFrame_);
    assert(option_);
    auto &option = *reinterpret_cast<KDDockWidgets::InitialOption *>(option_);
    return fromPtr(thisObj)->validateInputs(widget, static_cast<KDDockWidgets::Location>(location), relativeToFrame, option);
}
void c_KDDockWidgets__Core__DropArea__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Core__DropArea__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 332:
        wrapper->m_setParentView_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsCore::DropArea_wrapper::Callback_setParentView_impl>(callback);
        break;
    }
}
}
