/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <LayoutSaver.h>
#include <qstring.h>
#include <qbytearray.h>

namespace KDDockWidgetsBindings_wrappersNS {
class LayoutSaver_wrapper : public ::KDDockWidgets::LayoutSaver
{
public:
    ~LayoutSaver_wrapper();
    LayoutSaver_wrapper();
    bool restoreFromFile(const QString &jsonFilename);
    static bool restoreInProgress();
    bool restoreLayout(const QByteArray &arg__1);
    bool saveToFile(const QString &jsonFilename);
    QByteArray serializeLayout() const;
};
}
extern "C" {
// KDDockWidgets::LayoutSaver::LayoutSaver()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__LayoutSaver__constructor();
// KDDockWidgets::LayoutSaver::restoreFromFile(const QString & jsonFilename)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__LayoutSaver__restoreFromFile_QString(void *thisObj, const char *jsonFilename_);
// KDDockWidgets::LayoutSaver::restoreInProgress()
KDDockWidgetsBindings_EXPORT bool c_static_KDDockWidgets__LayoutSaver__restoreInProgress();
// KDDockWidgets::LayoutSaver::restoreLayout(const QByteArray & arg__1)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__LayoutSaver__restoreLayout_QByteArray(void *thisObj, void *arg__1_);
// KDDockWidgets::LayoutSaver::saveToFile(const QString & jsonFilename)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__LayoutSaver__saveToFile_QString(void *thisObj, const char *jsonFilename_);
// KDDockWidgets::LayoutSaver::serializeLayout() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__LayoutSaver__serializeLayout(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__LayoutSaver__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__LayoutSaver_Finalizer(void *, void *cppObj, void *);
}
