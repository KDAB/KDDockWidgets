#!/bin/bash

# SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

# Launches the argument with CDB, prints backtrace of exit
# Used to debug weird crashes in CI where process simply exits

"/C/Program Files (x86)/Windows Kits/10/Debuggers/x64/cdb.exe" -G -cfr cdb_debug_commands.txt "$*"
