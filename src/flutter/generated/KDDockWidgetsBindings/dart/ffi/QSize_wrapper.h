/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1043
class QSize_wrapper : public ::QSize
{
public:
    ~QSize_wrapper();
    // tag=1041
    QSize_wrapper();
    // tag=1041
    QSize_wrapper(int w, int h);
    // tag=1041
    QSize boundedTo(const QSize &arg__1) const;
    // tag=1041
    QSize expandedTo(const QSize &arg__1) const;
    // tag=1041
    int height() const;
    // tag=1041
    bool isEmpty() const;
    // tag=1041
    bool isNull() const;
    // tag=1041
    bool isValid() const;
    // tag=1041
    void setHeight(int h);
    // tag=1041
    void setWidth(int w);
    // tag=1041
    void transpose();
    // tag=1041
    QSize transposed() const;
    // tag=1041
    int width() const;
};
}
extern "C" {

// tag=1067
//  QSize::QSize()
KDDockWidgetsBindings_EXPORT void *c_QSize__constructor();

// tag=1067
//  QSize::QSize(int w, int h)
KDDockWidgetsBindings_EXPORT void *c_QSize__constructor_int_int(int w, int h);

// tag=1067
//  QSize::boundedTo(const QSize & arg__1) const
KDDockWidgetsBindings_EXPORT void *c_QSize__boundedTo_QSize(void *thisObj, void *arg__1_);

// tag=1067
//  QSize::expandedTo(const QSize & arg__1) const
KDDockWidgetsBindings_EXPORT void *c_QSize__expandedTo_QSize(void *thisObj, void *arg__1_);

// tag=1067
//  QSize::height() const
KDDockWidgetsBindings_EXPORT int c_QSize__height(void *thisObj);

// tag=1067
//  QSize::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QSize__isEmpty(void *thisObj);

// tag=1067
//  QSize::isNull() const
KDDockWidgetsBindings_EXPORT bool c_QSize__isNull(void *thisObj);

// tag=1067
//  QSize::isValid() const
KDDockWidgetsBindings_EXPORT bool c_QSize__isValid(void *thisObj);

// tag=1067
//  QSize::setHeight(int h)
KDDockWidgetsBindings_EXPORT void c_QSize__setHeight_int(void *thisObj, int h);

// tag=1067
//  QSize::setWidth(int w)
KDDockWidgetsBindings_EXPORT void c_QSize__setWidth_int(void *thisObj, int w);

// tag=1067
//  QSize::transpose()
KDDockWidgetsBindings_EXPORT void c_QSize__transpose(void *thisObj);

// tag=1067
//  QSize::transposed() const
KDDockWidgetsBindings_EXPORT void *c_QSize__transposed(void *thisObj);

// tag=1067
//  QSize::width() const
KDDockWidgetsBindings_EXPORT int c_QSize__width(void *thisObj);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_QSize__destructor(void *thisObj);

// tag=1047
KDDockWidgetsBindings_EXPORT void c_QSize_Finalizer(void *, void *cppObj, void *);
}
