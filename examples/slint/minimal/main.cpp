/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "main_ui.h"

int main(int argc, char **argv)
{
    auto hello_world = HelloWorld::create();
    hello_world->set_my_label("Hello from C++");
    hello_world->run();
    return 0;
}
