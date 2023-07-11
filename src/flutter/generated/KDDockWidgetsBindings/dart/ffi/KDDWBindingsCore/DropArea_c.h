/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "kddockwidgets_export.h"
#include "core/DropArea.h"
#include <core/View.h>
#include <Item_p.h>
#include <core/DropIndicatorOverlay.h>
#include <core/DockWidget.h>
#include <KDDockWidgets.h>
#include <core/Group.h>
#include <geometry_helpers_p.h>
#include "core/MainWindow.h"
#include <FloatingWindow.h>

namespace KDDockWidgetsBindings_wrappersNS {
namespace KDDWBindingsCore {
class DropArea_wrapper : public ::KDDockWidgets::Core::DropArea
{
public:
    ~DropArea_wrapper();
    DropArea_wrapper(KDDockWidgets::Core::View *parent, QFlags<KDDockWidgets::MainWindowOption> options, bool isMDIWrapper = false);
    void addDockWidget(KDDockWidgets::Core::DockWidget *dw, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget *relativeTo, KDDockWidgets::InitialOption initialOption = {});
    void addMultiSplitter(KDDockWidgets::Core::DropArea *splitter, KDDockWidgets::Location location, KDDockWidgets::Core::Group *relativeTo = nullptr, KDDockWidgets::InitialOption option = KDDockWidgets::DefaultSizeMode::Fair);
    void addWidget(KDDockWidgets::Core::View *widget, KDDockWidgets::Location location, KDDockWidgets::Core::Group *relativeTo = nullptr, KDDockWidgets::InitialOption option = KDDockWidgets::DefaultSizeMode::Fair);
    KDDockWidgets::Size availableSize() const;
    KDDockWidgets::Core::Item *centralFrame() const;
    KDDockWidgets::Core::Group *centralGroup() const;
    bool containsDockWidget(KDDockWidgets::Core::DockWidget *arg__1) const;
    static KDDockWidgets::Core::Group *createCentralFrame(QFlags<KDDockWidgets::MainWindowOption> options);
    KDDockWidgets::DropLocation currentDropLocation() const;
    bool drop(KDDockWidgets::Core::View *droppedwindow, KDDockWidgets::Location location, KDDockWidgets::Core::Group *relativeTo);
    KDDockWidgets::Core::DropIndicatorOverlay *dropIndicatorOverlay() const;
    KDDockWidgets::Core::Group *groupContainingPos(KDDockWidgets::Point globalPos) const;
    bool hasSingleFloatingFrame() const;
    bool hasSingleFrame() const;
    bool isMDIWrapper() const;
    void layoutEqually();
    void layoutParentContainerEqually(KDDockWidgets::Core::DockWidget *arg__1);
    KDDockWidgets::Core::DockWidget *mdiDockWidgetWrapper() const;
    void removeHover();
    virtual void setParentView_impl(KDDockWidgets::Core::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::Core::View *parent);
    void updateFloatingActions();
    bool validateInputs(KDDockWidgets::Core::View *widget, KDDockWidgets::Location location, const KDDockWidgets::Core::Group *relativeToFrame, KDDockWidgets::InitialOption option) const;
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::Core::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
};
}
}
extern "C" {
// KDDockWidgets::Core::DropArea::DropArea(KDDockWidgets::Core::View * parent, QFlags<KDDockWidgets::MainWindowOption> options, bool isMDIWrapper)
DOCKS_EXPORT void *c_KDDockWidgets__Core__DropArea__constructor_View_MainWindowOptions_bool(void *parent_, int options_, bool isMDIWrapper);
// KDDockWidgets::Core::DropArea::addDockWidget(KDDockWidgets::Core::DockWidget * dw, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget * relativeTo, KDDockWidgets::InitialOption initialOption)
DOCKS_EXPORT void c_KDDockWidgets__Core__DropArea__addDockWidget_DockWidget_Location_DockWidget_InitialOption(void *thisObj, void *dw_, int location, void *relativeTo_, void *initialOption_);
// KDDockWidgets::Core::DropArea::addMultiSplitter(KDDockWidgets::Core::DropArea * splitter, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo, KDDockWidgets::InitialOption option)
DOCKS_EXPORT void c_KDDockWidgets__Core__DropArea__addMultiSplitter_DropArea_Location_Group_InitialOption(void *thisObj, void *splitter_, int location, void *relativeTo_, void *option_);
// KDDockWidgets::Core::DropArea::addWidget(KDDockWidgets::Core::View * widget, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo, KDDockWidgets::InitialOption option)
DOCKS_EXPORT void c_KDDockWidgets__Core__DropArea__addWidget_View_Location_Group_InitialOption(void *thisObj, void *widget_, int location, void *relativeTo_, void *option_);
// KDDockWidgets::Core::DropArea::availableSize() const
DOCKS_EXPORT void *c_KDDockWidgets__Core__DropArea__availableSize(void *thisObj);
// KDDockWidgets::Core::DropArea::centralFrame() const
DOCKS_EXPORT void *c_KDDockWidgets__Core__DropArea__centralFrame(void *thisObj);
// KDDockWidgets::Core::DropArea::centralGroup() const
DOCKS_EXPORT void *c_KDDockWidgets__Core__DropArea__centralGroup(void *thisObj);
// KDDockWidgets::Core::DropArea::containsDockWidget(KDDockWidgets::Core::DockWidget * arg__1) const
DOCKS_EXPORT bool c_KDDockWidgets__Core__DropArea__containsDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::DropArea::createCentralFrame(QFlags<KDDockWidgets::MainWindowOption> options)
DOCKS_EXPORT void *c_static_KDDockWidgets__Core__DropArea__createCentralFrame_MainWindowOptions(int options_);
// KDDockWidgets::Core::DropArea::currentDropLocation() const
DOCKS_EXPORT int c_KDDockWidgets__Core__DropArea__currentDropLocation(void *thisObj);
// KDDockWidgets::Core::DropArea::drop(KDDockWidgets::Core::View * droppedwindow, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo)
DOCKS_EXPORT bool c_KDDockWidgets__Core__DropArea__drop_View_Location_Group(void *thisObj, void *droppedwindow_, int location, void *relativeTo_);
// KDDockWidgets::Core::DropArea::dropIndicatorOverlay() const
DOCKS_EXPORT void *c_KDDockWidgets__Core__DropArea__dropIndicatorOverlay(void *thisObj);
// KDDockWidgets::Core::DropArea::groupContainingPos(KDDockWidgets::Point globalPos) const
DOCKS_EXPORT void *c_KDDockWidgets__Core__DropArea__groupContainingPos_Point(void *thisObj, void *globalPos_);
// KDDockWidgets::Core::DropArea::hasSingleFloatingFrame() const
DOCKS_EXPORT bool c_KDDockWidgets__Core__DropArea__hasSingleFloatingFrame(void *thisObj);
// KDDockWidgets::Core::DropArea::hasSingleFrame() const
DOCKS_EXPORT bool c_KDDockWidgets__Core__DropArea__hasSingleFrame(void *thisObj);
// KDDockWidgets::Core::DropArea::isMDIWrapper() const
DOCKS_EXPORT bool c_KDDockWidgets__Core__DropArea__isMDIWrapper(void *thisObj);
// KDDockWidgets::Core::DropArea::layoutEqually()
DOCKS_EXPORT void c_KDDockWidgets__Core__DropArea__layoutEqually(void *thisObj);
// KDDockWidgets::Core::DropArea::layoutParentContainerEqually(KDDockWidgets::Core::DockWidget * arg__1)
DOCKS_EXPORT void c_KDDockWidgets__Core__DropArea__layoutParentContainerEqually_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::DropArea::mdiDockWidgetWrapper() const
DOCKS_EXPORT void *c_KDDockWidgets__Core__DropArea__mdiDockWidgetWrapper(void *thisObj);
// KDDockWidgets::Core::DropArea::removeHover()
DOCKS_EXPORT void c_KDDockWidgets__Core__DropArea__removeHover(void *thisObj);
// KDDockWidgets::Core::DropArea::setParentView_impl(KDDockWidgets::Core::View * parent)
DOCKS_EXPORT void c_KDDockWidgets__Core__DropArea__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::DropArea::updateFloatingActions()
DOCKS_EXPORT void c_KDDockWidgets__Core__DropArea__updateFloatingActions(void *thisObj);
// KDDockWidgets::Core::DropArea::validateInputs(KDDockWidgets::Core::View * widget, KDDockWidgets::Location location, const KDDockWidgets::Core::Group * relativeToFrame, KDDockWidgets::InitialOption option) const
DOCKS_EXPORT bool c_KDDockWidgets__Core__DropArea__validateInputs_View_Location_Group_InitialOption(void *thisObj, void *widget_, int location, void *relativeToFrame_, void *option_);
DOCKS_EXPORT void c_KDDockWidgets__Core__DropArea__destructor(void *thisObj);
DOCKS_EXPORT void c_KDDockWidgets__Core__DropArea__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
DOCKS_EXPORT void c_KDDockWidgets__Core__DropArea_Finalizer(void *cppObj);
}
