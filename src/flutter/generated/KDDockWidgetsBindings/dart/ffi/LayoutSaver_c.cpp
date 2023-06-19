/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "LayoutSaver_c.h"


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
LayoutSaver_wrapper::LayoutSaver_wrapper()
    : ::KDDockWidgets::LayoutSaver()
{
}
bool LayoutSaver_wrapper::restoreFromFile(const QString &jsonFilename)
{
    return ::KDDockWidgets::LayoutSaver::restoreFromFile(jsonFilename);
}
bool LayoutSaver_wrapper::restoreInProgress()
{
    return ::KDDockWidgets::LayoutSaver::restoreInProgress();
}
bool LayoutSaver_wrapper::restoreLayout(const QByteArray &arg__1)
{
    return ::KDDockWidgets::LayoutSaver::restoreLayout(arg__1);
}
bool LayoutSaver_wrapper::saveToFile(const QString &jsonFilename)
{
    return ::KDDockWidgets::LayoutSaver::saveToFile(jsonFilename);
}
QByteArray LayoutSaver_wrapper::serializeLayout() const
{
    return ::KDDockWidgets::LayoutSaver::serializeLayout();
}
LayoutSaver_wrapper::~LayoutSaver_wrapper()
{
}

}
static KDDockWidgets::LayoutSaver *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::LayoutSaver *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::LayoutSaver_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::LayoutSaver_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__LayoutSaver_Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::LayoutSaver_wrapper *>(cppObj);
}
void *c_KDDockWidgets__LayoutSaver__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::LayoutSaver_wrapper();
    return reinterpret_cast<void *>(ptr);
}
// restoreFromFile(const QString & jsonFilename)
bool c_KDDockWidgets__LayoutSaver__restoreFromFile_QString(void *thisObj, const char *jsonFilename_)
{
    const auto jsonFilename = QString::fromUtf8(jsonFilename_);
    return fromPtr(thisObj)->restoreFromFile(jsonFilename);
}
// restoreInProgress()
bool c_static_KDDockWidgets__LayoutSaver__restoreInProgress()
{
    return KDDockWidgetsBindings_wrappersNS::LayoutSaver_wrapper::restoreInProgress();
}
// restoreLayout(const QByteArray & arg__1)
bool c_KDDockWidgets__LayoutSaver__restoreLayout_QByteArray(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<QByteArray *>(arg__1_);
    return fromPtr(thisObj)->restoreLayout(arg__1);
}
// saveToFile(const QString & jsonFilename)
bool c_KDDockWidgets__LayoutSaver__saveToFile_QString(void *thisObj, const char *jsonFilename_)
{
    const auto jsonFilename = QString::fromUtf8(jsonFilename_);
    return fromPtr(thisObj)->saveToFile(jsonFilename);
}
// serializeLayout() const
void *c_KDDockWidgets__LayoutSaver__serializeLayout(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QByteArray> { fromPtr(thisObj)->serializeLayout() };
}
void c_KDDockWidgets__LayoutSaver__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
}
