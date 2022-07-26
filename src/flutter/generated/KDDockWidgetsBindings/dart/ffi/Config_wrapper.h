/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <Config.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1043
class Config_wrapper : public ::KDDockWidgets::Config
{
public:
    ~Config_wrapper();
    // tag=1041
    QSize absoluteWidgetMaxSize() const;
    // tag=1041
    QSize absoluteWidgetMinSize() const;
    // tag=1041
    qreal draggedWindowOpacity() const;
    // tag=1041
    bool dropIndicatorsInhibited() const;
    // tag=1041
    int mdiPopupThreshold() const;
    // tag=1041
    static KDDockWidgets::Config &self();
    // tag=1041
    int separatorThickness() const;
    // tag=1041
    void setAbsoluteWidgetMaxSize(QSize size);
    // tag=1041
    void setAbsoluteWidgetMinSize(QSize size);
    // tag=1041
    void setDraggedWindowOpacity(qreal opacity);
    // tag=1041
    void setDropIndicatorsInhibited(bool inhibit) const;
    // tag=1041
    void setMDIPopupThreshold(int arg__1);
    // tag=1041
    void setSeparatorThickness(int value);
    // tag=1041
    void setStartDragDistance(int arg__1);
    // tag=1041
    int startDragDistance() const;
};
}
extern "C" {

// tag=1067
//  KDDockWidgets::Config::absoluteWidgetMaxSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Config__absoluteWidgetMaxSize(void *thisObj);

// tag=1067
//  KDDockWidgets::Config::absoluteWidgetMinSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Config__absoluteWidgetMinSize(void *thisObj);

// tag=1067
//  KDDockWidgets::Config::draggedWindowOpacity() const
KDDockWidgetsBindings_EXPORT qreal c_KDDockWidgets__Config__draggedWindowOpacity(void *thisObj);

// tag=1067
//  KDDockWidgets::Config::dropIndicatorsInhibited() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Config__dropIndicatorsInhibited(void *thisObj);

// tag=1067
//  KDDockWidgets::Config::mdiPopupThreshold() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Config__mdiPopupThreshold(void *thisObj);

// tag=1067
//  KDDockWidgets::Config::self()
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Config__self();

// tag=1067
//  KDDockWidgets::Config::separatorThickness() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Config__separatorThickness(void *thisObj);

// tag=1067
//  KDDockWidgets::Config::setAbsoluteWidgetMaxSize(QSize size)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config__setAbsoluteWidgetMaxSize_QSize(void *thisObj, void *size_);

// tag=1067
//  KDDockWidgets::Config::setAbsoluteWidgetMinSize(QSize size)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config__setAbsoluteWidgetMinSize_QSize(void *thisObj, void *size_);

// tag=1067
//  KDDockWidgets::Config::setDraggedWindowOpacity(qreal opacity)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config__setDraggedWindowOpacity_qreal(void *thisObj, qreal opacity);

// tag=1067
//  KDDockWidgets::Config::setDropIndicatorsInhibited(bool inhibit) const
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config__setDropIndicatorsInhibited_bool(void *thisObj, bool inhibit);

// tag=1067
//  KDDockWidgets::Config::setMDIPopupThreshold(int arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config__setMDIPopupThreshold_int(void *thisObj, int arg__1);

// tag=1067
//  KDDockWidgets::Config::setSeparatorThickness(int value)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config__setSeparatorThickness_int(void *thisObj, int value);

// tag=1067
//  KDDockWidgets::Config::setStartDragDistance(int arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config__setStartDragDistance_int(void *thisObj, int arg__1);

// tag=1067
//  KDDockWidgets::Config::startDragDistance() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Config__startDragDistance(void *thisObj);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config__destructor(void *thisObj);

// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config_Finalizer(void *, void *cppObj, void *);
}
