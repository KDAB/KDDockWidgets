/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
class QSize_wrapper : public ::QSize
{
public:
    ~QSize_wrapper();
    QSize_wrapper();
    QSize_wrapper(int w, int h);
    QSize boundedTo(const QSize &arg__1) const;
    QSize expandedTo(const QSize &arg__1) const;
    int height() const;
    bool isEmpty() const;
    bool isNull() const;
    bool isValid() const;
    void setHeight(int h);
    void setWidth(int w);
    void transpose();
    QSize transposed() const;
    int width() const;
};
}
extern "C" {
// QSize::QSize()
KDDockWidgetsBindings_EXPORT void *c_QSize__constructor();
// QSize::QSize(int w, int h)
KDDockWidgetsBindings_EXPORT void *c_QSize__constructor_int_int(int w, int h);
// QSize::boundedTo(const QSize & arg__1) const
KDDockWidgetsBindings_EXPORT void *c_QSize__boundedTo_QSize(void *thisObj, void *arg__1_);
// QSize::expandedTo(const QSize & arg__1) const
KDDockWidgetsBindings_EXPORT void *c_QSize__expandedTo_QSize(void *thisObj, void *arg__1_);
// QSize::height() const
KDDockWidgetsBindings_EXPORT int c_QSize__height(void *thisObj);
// QSize::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QSize__isEmpty(void *thisObj);
// QSize::isNull() const
KDDockWidgetsBindings_EXPORT bool c_QSize__isNull(void *thisObj);
// QSize::isValid() const
KDDockWidgetsBindings_EXPORT bool c_QSize__isValid(void *thisObj);
// QSize::setHeight(int h)
KDDockWidgetsBindings_EXPORT void c_QSize__setHeight_int(void *thisObj, int h);
// QSize::setWidth(int w)
KDDockWidgetsBindings_EXPORT void c_QSize__setWidth_int(void *thisObj, int w);
// QSize::transpose()
KDDockWidgetsBindings_EXPORT void c_QSize__transpose(void *thisObj);
// QSize::transposed() const
KDDockWidgetsBindings_EXPORT void *c_QSize__transposed(void *thisObj);
// QSize::width() const
KDDockWidgetsBindings_EXPORT int c_QSize__width(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QSize__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QSize_Finalizer(void *, void *cppObj, void *);
}
