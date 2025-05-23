#!/bin/bash

# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sérgio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.

set -e

SCRIPT_PATH=$(dirname "$(readlink -f "$0")")

cd "$SCRIPT_PATH"
docker build -t kddw-qt6-asan -f Dockerfile_qtasan .

CONTAINER_ID=$(docker run -d -it kddw-qt6-asan bash)
echo "Container started with ID: $CONTAINER_ID"

echo "exporting..."
docker export -o mycontainer.tar "$CONTAINER_ID"

echo "importing..."
IMPORTED_IMAGE=$(docker import mycontainer.tar)

echo "tagging.. $IMPORTED_IMAGE"
docker tag "$IMPORTED_IMAGE" iamsergio/kddw-qt6-asan

echo "pushing..."
docker push iamsergio/kddw-qt6-asan

echo "killing..."
docker kill "$CONTAINER_ID"
rm mycontainer.tar
