/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#ifdef __cplusplus

#include <KDDockWidgets.h>
extern "C" {
#else
#define DOCKS_EXPORT
#endif

DOCKS_EXPORT void on_flutter_droparea_widget_resized(void *host, int width, int height);
DOCKS_EXPORT void on_separator_mouse_button_event(void *separator, int pressed);
DOCKS_EXPORT void on_separator_mouse_move_event(void *separator, float x, float y);
DOCKS_EXPORT void *create_host();
DOCKS_EXPORT void delete_host(void *host);
DOCKS_EXPORT void *create_guest(void *host, void (*callback)(void *guest, int x, int y, int width, int height, int is_visible));
DOCKS_EXPORT void delete_guest(void *host);
DOCKS_EXPORT void insert_item(void *host, void *guest, int location);
DOCKS_EXPORT void insert_item_relative_to(void *host, void *guest, void *relativeToGuest, int location);
DOCKS_EXPORT void remove_guest(void *host, void *guest);

/// Separators are created and destroyed by KDDW
DOCKS_EXPORT void set_separator_added_callback(void *host, void (*callback)(void *host, void *separator, int isVertical));
DOCKS_EXPORT void set_separator_removed_callback(void *host, void (*callback)(void *host, void *separator));
DOCKS_EXPORT void set_separator_changed_callback(void *separator, void (*callback)(void *separator, int x, int y, int width, int height));

#ifdef __cplusplus
}
#endif
