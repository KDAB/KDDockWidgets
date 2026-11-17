#!/usr/bin/env bash

# SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

# Runs a command inside a nested mutter Wayland compositor.
#
# Usage: scripts/run_under_mutter.sh <command> [args...]
# Example: scripts/run_under_mutter.sh build-release/bin/qtwidgets_dockwidgets --wayland-toplevel-drag
#
# Set MUTTER to use a mutter other than the one in PATH, for example a self-built one:
#   MUTTER=/path/to/mutter/build/src/mutter scripts/run_under_mutter.sh ...
# Note that --devkit (mutter >= 49) needs mutter-devkit installed in mutter's libexecdir.

set -e

MUTTER=${MUTTER:-mutter}

if ! command -v "$MUTTER" >/dev/null 2>&1; then
  echo "error: mutter not found: $MUTTER" >&2
  exit 1
fi

if [ $# -eq 0 ]; then
  echo "usage: $0 <command> [args...]" >&2
  exit 1
fi

# "mutter 48.1" -> 48
MUTTER_MAJOR=$("$MUTTER" --version | head -n1 | sed -E 's/^mutter ([0-9]+).*/\1/')
if ! [[ "$MUTTER_MAJOR" =~ ^[0-9]+$ ]]; then
  echo "error: could not parse mutter version: $("$MUTTER" --version | head -n1)" >&2
  exit 1
fi

if [ -z "$XDG_RUNTIME_DIR" ]; then
  # Keep it short, wayland socket paths are limited to 108 bytes
  XDG_RUNTIME_DIR=$(mktemp -d /tmp/xdg-XXXXXX)
  chmod 700 "$XDG_RUNTIME_DIR"
  export XDG_RUNTIME_DIR
  trap 'rm -rf "$XDG_RUNTIME_DIR"' EXIT
fi

if [ "$MUTTER_MAJOR" -le 48 ]; then
  dbus-run-session "$MUTTER" --wayland --nested --no-x11 --wayland-display=wayland-mutter -- "$@"
else
  MUTTER_DEBUG_DUMMY_MODE_SPECS=1920x1080 dbus-run-session "$MUTTER" --wayland --devkit --wayland-display=wayland-mutter -- "$@"
fi
