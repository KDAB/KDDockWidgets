/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_MULTISPLITTER_EXPORT_H
#define KD_MULTISPLITTER_EXPORT_H

#include <QtCore/QtGlobal>

#if defined(BUILDING_MULTISPLITTER_LIBRARY)
#  define MULTISPLITTER_EXPORT Q_DECL_EXPORT
#else
#  define MULTISPLITTER_EXPORT Q_DECL_IMPORT
#endif

#endif
