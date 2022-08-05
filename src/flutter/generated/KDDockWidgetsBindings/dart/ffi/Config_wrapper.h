/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <Config.h>
#include <ViewFactory.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
class Config_wrapper : public ::KDDockWidgets::Config
{
public:
    ~Config_wrapper();
    QSize absoluteWidgetMaxSize() const;
    QSize absoluteWidgetMinSize() const;
    qreal draggedWindowOpacity() const;
    bool dropIndicatorsInhibited() const;
    int mdiPopupThreshold() const;
    static KDDockWidgets::Config &self();
    int separatorThickness() const;
    void setAbsoluteWidgetMaxSize(QSize size);
    void setAbsoluteWidgetMinSize(QSize size);
    void setDraggedWindowOpacity(qreal opacity);
    void setDropIndicatorsInhibited(bool inhibit) const;
    void setMDIPopupThreshold(int arg__1);
    void setSeparatorThickness(int value);
    void setStartDragDistance(int arg__1);
    void setViewFactory(KDDockWidgets::ViewFactory *arg__1);
    int startDragDistance() const;
    KDDockWidgets::ViewFactory *viewFactory() const;
};
}
extern "C" {
// KDDockWidgets::Config::absoluteWidgetMaxSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Config__absoluteWidgetMaxSize(void *thisObj);
// KDDockWidgets::Config::absoluteWidgetMinSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Config__absoluteWidgetMinSize(void *thisObj);
// KDDockWidgets::Config::draggedWindowOpacity() const
KDDockWidgetsBindings_EXPORT qreal c_KDDockWidgets__Config__draggedWindowOpacity(void *thisObj);
// KDDockWidgets::Config::dropIndicatorsInhibited() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Config__dropIndicatorsInhibited(void *thisObj);
// KDDockWidgets::Config::mdiPopupThreshold() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Config__mdiPopupThreshold(void *thisObj);
// KDDockWidgets::Config::self()
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Config__self();
// KDDockWidgets::Config::separatorThickness() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Config__separatorThickness(void *thisObj);
// KDDockWidgets::Config::setAbsoluteWidgetMaxSize(QSize size)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Config__setAbsoluteWidgetMaxSize_QSize(void *thisObj, void *size_);
// KDDockWidgets::Config::setAbsoluteWidgetMinSize(QSize size)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Config__setAbsoluteWidgetMinSize_QSize(void *thisObj, void *size_);
// KDDockWidgets::Config::setDraggedWindowOpacity(qreal opacity)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Config__setDraggedWindowOpacity_qreal(void *thisObj, qreal opacity);
// KDDockWidgets::Config::setDropIndicatorsInhibited(bool inhibit) const
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Config__setDropIndicatorsInhibited_bool(void *thisObj, bool inhibit);
// KDDockWidgets::Config::setMDIPopupThreshold(int arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config__setMDIPopupThreshold_int(void *thisObj,
                                                                                    int arg__1);
// KDDockWidgets::Config::setSeparatorThickness(int value)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config__setSeparatorThickness_int(void *thisObj,
                                                                                     int value);
// KDDockWidgets::Config::setStartDragDistance(int arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config__setStartDragDistance_int(void *thisObj,
                                                                                    int arg__1);
// KDDockWidgets::Config::setViewFactory(KDDockWidgets::ViewFactory * arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Config__setViewFactory_ViewFactory(void *thisObj, void *arg__1_);
// KDDockWidgets::Config::startDragDistance() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Config__startDragDistance(void *thisObj);
// KDDockWidgets::Config::viewFactory() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Config__viewFactory(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Config_Finalizer(void *, void *cppObj, void *);
}
