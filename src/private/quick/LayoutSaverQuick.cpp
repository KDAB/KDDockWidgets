/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "LayoutSaver.h"

// TODO: Temporary, until LayoutSaver.cpp is ported to QtQuick

using namespace KDDockWidgets;

LayoutSaver::LayoutSaver() : d(nullptr) {}
LayoutSaver::~LayoutSaver() {}

bool LayoutSaver::saveToDisk() { return false; }
bool LayoutSaver::restoreFromDisk() { return false; }

bool LayoutSaver::restoreInProgress() { return false; }
