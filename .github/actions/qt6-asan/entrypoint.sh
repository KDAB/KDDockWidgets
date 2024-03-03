# SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

cd /github/workspace/
cmake --preset=ci-dev-asan-qt6 && cd build-ci-dev-asan-qt6/ && ninja && ctest -j12
