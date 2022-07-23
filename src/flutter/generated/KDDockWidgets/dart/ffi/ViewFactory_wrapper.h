/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgets_exports.h"
#include <ViewFactory.h>
#include <qstring.h>
#include <View.h>
#include <qlist.h>
#include <qbytearray.h>
#include <qobject.h>

namespace KDDockWidgets_wrappersNS {
// tag=1017
class ViewFactory_wrapper : public ::KDDockWidgets::ViewFactory
{
public:
    ~ViewFactory_wrapper();
    // tag=1041
    ViewFactory_wrapper();
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
//  KDDockWidgets::ViewFactory::ViewFactory()
KDDockWidgets_EXPORT void *c_KDDockWidgets__ViewFactory__constructor();

// tag=1067
//  KDDockWidgets::ViewFactory::createRubberBand(KDDockWidgets::View * parent) const
KDDockWidgets_EXPORT void *c_KDDockWidgets__ViewFactory__createRubberBand_View(void *thisObj, void *parent_);

// tag=1067
//  KDDockWidgets::ViewFactory::tr(const char * s, const char * c, int n)
KDDockWidgets_EXPORT void *c_static_KDDockWidgets__ViewFactory__tr_char_char_int(const char *s, const char *c, int n);

// tag=1066
KDDockWidgets_EXPORT void c_KDDockWidgets__ViewFactory__destructor(void *thisObj);

// tag=1046
KDDockWidgets_EXPORT void c_KDDockWidgets__ViewFactory__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgets_EXPORT void c_KDDockWidgets__ViewFactory_Finalizer(void *, void *cppObj, void *);
}
