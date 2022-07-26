/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <ViewFactory_flutter.h>
#include <qstring.h>
#include <View.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1017
class ViewFactory_flutter_wrapper : public ::KDDockWidgets::ViewFactory_flutter
{
public:
    ~ViewFactory_flutter_wrapper();
    // tag=1041
    ViewFactory_flutter_wrapper();
    // tag=1041
    virtual KDDockWidgets::View *createRubberBand(KDDockWidgets::View *parent) const;
    // tag=1008
    virtual KDDockWidgets::View *createRubberBand_nocallback(KDDockWidgets::View *parent) const;
    // tag=1041
    static QString tr(const char *s, const char *c, int n);
    // tag=1042
    typedef KDDockWidgets::View *(*Callback_createRubberBand)(void *, KDDockWidgets::View *parent);
    Callback_createRubberBand m_createRubberBandCallback = nullptr;
};
}
extern "C" {

// tag=1067
//  KDDockWidgets::ViewFactory_flutter::ViewFactory_flutter()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory_flutter__constructor();

// tag=1067
//  KDDockWidgets::ViewFactory_flutter::createRubberBand(KDDockWidgets::View * parent) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory_flutter__createRubberBand_View(void *thisObj, void *parent_);

// tag=1067
//  KDDockWidgets::ViewFactory_flutter::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__ViewFactory_flutter__tr_char_char_int(const char *s, const char *c, int n);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__ViewFactory_flutter__destructor(void *thisObj);

// tag=1046
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__ViewFactory_flutter__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__ViewFactory_flutter_Finalizer(void *, void *cppObj, void *);
}
