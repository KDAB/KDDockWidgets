/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Config_wrapper.h"


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
QSize Config_wrapper::absoluteWidgetMaxSize() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Config::absoluteWidgetMaxSize();
}
QSize Config_wrapper::absoluteWidgetMinSize() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Config::absoluteWidgetMinSize();
}
qreal Config_wrapper::draggedWindowOpacity() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Config::draggedWindowOpacity();
}
bool Config_wrapper::dropIndicatorsInhibited() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Config::dropIndicatorsInhibited();
}
int Config_wrapper::mdiPopupThreshold() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Config::mdiPopupThreshold();
}
KDDockWidgets::Config &Config_wrapper::self()
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Config::self();
}
int Config_wrapper::separatorThickness() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Config::separatorThickness();
}
void Config_wrapper::setAbsoluteWidgetMaxSize(QSize size)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Config::setAbsoluteWidgetMaxSize(size);
}
void Config_wrapper::setAbsoluteWidgetMinSize(QSize size)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Config::setAbsoluteWidgetMinSize(size);
}
void Config_wrapper::setDraggedWindowOpacity(qreal opacity)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Config::setDraggedWindowOpacity(opacity);
}
void Config_wrapper::setDropIndicatorsInhibited(bool inhibit) const
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Config::setDropIndicatorsInhibited(inhibit);
}
void Config_wrapper::setMDIPopupThreshold(int arg__1)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Config::setMDIPopupThreshold(arg__1);
}
void Config_wrapper::setSeparatorThickness(int value)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Config::setSeparatorThickness(value);
}
void Config_wrapper::setStartDragDistance(int arg__1)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Config::setStartDragDistance(arg__1);
}
int Config_wrapper::startDragDistance() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Config::startDragDistance();
}

// tag=1005
Config_wrapper::~Config_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::Config *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Config *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::Config_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Config_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__Config_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Config_wrapper *>(cppObj);
}
// tag=1050
// absoluteWidgetMaxSize() const
void *c_KDDockWidgets__Config__absoluteWidgetMaxSize(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->absoluteWidgetMaxSize() };
}

// tag=1050
// absoluteWidgetMinSize() const
void *c_KDDockWidgets__Config__absoluteWidgetMinSize(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->absoluteWidgetMinSize() };
}

// tag=1050
// draggedWindowOpacity() const
qreal c_KDDockWidgets__Config__draggedWindowOpacity(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->draggedWindowOpacity();
}

// tag=1050
// dropIndicatorsInhibited() const
bool c_KDDockWidgets__Config__dropIndicatorsInhibited(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->dropIndicatorsInhibited();
}

// tag=1050
// mdiPopupThreshold() const
int c_KDDockWidgets__Config__mdiPopupThreshold(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->mdiPopupThreshold();
}

// tag=1050
// self()
void *c_static_KDDockWidgets__Config__self()
{
    return
        // tag=1068

        // tag=1070
        &KDDockWidgetsBindings_wrappersNS::Config_wrapper::self();
}

// tag=1050
// separatorThickness() const
int c_KDDockWidgets__Config__separatorThickness(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->separatorThickness();
}

// tag=1050
// setAbsoluteWidgetMaxSize(QSize size)
void c_KDDockWidgets__Config__setAbsoluteWidgetMaxSize_QSize(void *thisObj, void *size_)
{
    auto &size = *reinterpret_cast<QSize *>(size_);
    // tag=1010
    fromPtr(thisObj)->setAbsoluteWidgetMaxSize(size);
}

// tag=1050
// setAbsoluteWidgetMinSize(QSize size)
void c_KDDockWidgets__Config__setAbsoluteWidgetMinSize_QSize(void *thisObj, void *size_)
{
    auto &size = *reinterpret_cast<QSize *>(size_);
    // tag=1010
    fromPtr(thisObj)->setAbsoluteWidgetMinSize(size);
}

// tag=1050
// setDraggedWindowOpacity(qreal opacity)
void c_KDDockWidgets__Config__setDraggedWindowOpacity_qreal(void *thisObj, qreal opacity)
{
    // tag=1010
    fromPtr(thisObj)->setDraggedWindowOpacity(opacity);
}

// tag=1050
// setDropIndicatorsInhibited(bool inhibit) const
void c_KDDockWidgets__Config__setDropIndicatorsInhibited_bool(void *thisObj, bool inhibit)
{
    // tag=1010
    fromPtr(thisObj)->setDropIndicatorsInhibited(inhibit);
}

// tag=1050
// setMDIPopupThreshold(int arg__1)
void c_KDDockWidgets__Config__setMDIPopupThreshold_int(void *thisObj, int arg__1)
{
    // tag=1010
    fromPtr(thisObj)->setMDIPopupThreshold(arg__1);
}

// tag=1050
// setSeparatorThickness(int value)
void c_KDDockWidgets__Config__setSeparatorThickness_int(void *thisObj, int value)
{
    // tag=1010
    fromPtr(thisObj)->setSeparatorThickness(value);
}

// tag=1050
// setStartDragDistance(int arg__1)
void c_KDDockWidgets__Config__setStartDragDistance_int(void *thisObj, int arg__1)
{
    // tag=1010
    fromPtr(thisObj)->setStartDragDistance(arg__1);
}

// tag=1050
// startDragDistance() const
int c_KDDockWidgets__Config__startDragDistance(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->startDragDistance();
}
void c_KDDockWidgets__Config__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
}
