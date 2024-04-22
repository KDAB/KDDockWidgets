#!/bin/sh

# SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

# Creates a GitHub PR that upgrades dependencies in pubspec.yml
# called by flutter-pub-update.yml

if [ -n "$(git status --porcelain)" ]; then
  git add .
  git commit -m "flutter: run pub upgrade"
  git checkout -B flutter/pub-"$(git log -1 --pretty=format:"%H")"
  git push --set-upstream origin "$(git branch --show-current)"
  gh pr create --base main --title "flutter: run pub upgrade" --body "Automatically created via GH action."
fi
