/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <DropArea.h>
#include <qstring.h>
#include <View.h>
#include <qlist.h>
#include <Group.h>
#include <Item_p.h>
#include <core/DropIndicatorOverlay.h>
#include <DockWidget.h>
#include <KDDockWidgets.h>
#include <qsize.h>
#include <qpoint.h>
#include <FloatingWindow.h>
#include <MainWindow.h>

namespace KDDockWidgetsBindings_wrappersNS {
class DropArea_wrapper : public ::KDDockWidgets::Core::DropArea
{
public:
    ~DropArea_wrapper();
    DropArea_wrapper(KDDockWidgets::Core::View *parent, QFlags<KDDockWidgets::MainWindowOption> options, bool isMDIWrapper = false);
    void addDockWidget(KDDockWidgets::Core::DockWidget *dw, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget *relativeTo, KDDockWidgets::InitialOption initialOption = {});
    void addMultiSplitter(KDDockWidgets::Core::DropArea *splitter, KDDockWidgets::Location location, KDDockWidgets::Core::Group *relativeTo = nullptr, KDDockWidgets::InitialOption option = KDDockWidgets::DefaultSizeMode::Fair);
    void addWidget(KDDockWidgets::Core::View *widget, KDDockWidgets::Location location, KDDockWidgets::Core::Group *relativeTo = nullptr, KDDockWidgets::InitialOption option = KDDockWidgets::DefaultSizeMode::Fair);
    Core::Item *centralFrame() const;
    bool containsDockWidget(KDDockWidgets::Core::DockWidget *arg__1) const;
    static KDDockWidgets::Core::Group *createCentralFrame(QFlags<KDDockWidgets::MainWindowOption> options);
    KDDockWidgets::DropLocation currentDropLocation() const;
    KDDockWidgets::Core::DropIndicatorOverlay *dropIndicatorOverlay() const;
    QList<KDDockWidgets::Core::Group *> groups() const;
    bool hasSingleFloatingFrame() const;
    bool hasSingleFrame() const;
    bool isMDIWrapper() const;
    void layoutEqually();
    void layoutParentContainerEqually(KDDockWidgets::Core::DockWidget *arg__1);
    KDDockWidgets::Core::DockWidget *mdiDockWidgetWrapper() const;
    void removeHover();
    virtual void setParentView_impl(KDDockWidgets::Core::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::Core::View *parent);
    static QString tr(const char *s, const char *c, int n);
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::Core::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::Core::DropArea::DropArea(KDDockWidgets::Core::View * parent, QFlags<KDDockWidgets::MainWindowOption> options, bool isMDIWrapper)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__DropArea__constructor_View_MainWindowOptions_bool(void *parent_, int options_, bool isMDIWrapper);
// KDDockWidgets::Core::DropArea::addDockWidget(KDDockWidgets::Core::DockWidget * dw, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget * relativeTo, KDDockWidgets::InitialOption initialOption)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__addDockWidget_DockWidget_Location_DockWidget_InitialOption(void *thisObj, void *dw_, int location, void *relativeTo_, void *initialOption_);
// KDDockWidgets::Core::DropArea::addMultiSplitter(KDDockWidgets::Core::DropArea * splitter, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo, KDDockWidgets::InitialOption option)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__addMultiSplitter_DropArea_Location_Group_InitialOption(void *thisObj, void *splitter_, int location, void *relativeTo_, void *option_);
// KDDockWidgets::Core::DropArea::addWidget(KDDockWidgets::Core::View * widget, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo, KDDockWidgets::InitialOption option)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__addWidget_View_Location_Group_InitialOption(void *thisObj, void *widget_, int location, void *relativeTo_, void *option_);
// KDDockWidgets::Core::DropArea::centralFrame() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__DropArea__centralFrame(void *thisObj);
// KDDockWidgets::Core::DropArea::containsDockWidget(KDDockWidgets::Core::DockWidget * arg__1) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__DropArea__containsDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::DropArea::createCentralFrame(QFlags<KDDockWidgets::MainWindowOption> options)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Controllers__DropArea__createCentralFrame_MainWindowOptions(int options_);
// KDDockWidgets::Core::DropArea::currentDropLocation() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__DropArea__currentDropLocation(void *thisObj);
// KDDockWidgets::Core::DropArea::dropIndicatorOverlay() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__DropArea__dropIndicatorOverlay(void *thisObj);
// KDDockWidgets::Core::DropArea::groups() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__DropArea__groups(void *thisObj);
// KDDockWidgets::Core::DropArea::hasSingleFloatingFrame() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__DropArea__hasSingleFloatingFrame(void *thisObj);
// KDDockWidgets::Core::DropArea::hasSingleFrame() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__DropArea__hasSingleFrame(void *thisObj);
// KDDockWidgets::Core::DropArea::isMDIWrapper() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__DropArea__isMDIWrapper(void *thisObj);
// KDDockWidgets::Core::DropArea::layoutEqually()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__layoutEqually(void *thisObj);
// KDDockWidgets::Core::DropArea::layoutParentContainerEqually(KDDockWidgets::Core::DockWidget * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__layoutParentContainerEqually_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::DropArea::mdiDockWidgetWrapper() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__DropArea__mdiDockWidgetWrapper(void *thisObj);
// KDDockWidgets::Core::DropArea::removeHover()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__removeHover(void *thisObj);
// KDDockWidgets::Core::DropArea::setParentView_impl(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::DropArea::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Controllers__DropArea__tr_char_char_int(const char *s, const char *c, int n);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea_Finalizer(void *, void *cppObj, void *);
}
