#!/bin/bash

# SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

# Runs the tests of a clang coverage build (see the dev-cov preset) and generates a report.
#
# Usage: tests/coverage.sh [build-dir] [extra ctest args]
#
# Outputs, inside the build dir:
#   coverage/summary.txt   - per-file summary
#   coverage/html/         - annotated sources
#   coverage/coverage.lcov - for uploading to a coverage service
#
# Set LLVM_SUFFIX (e.g. -20) to use versioned llvm tools.

set -e

BUILD_DIR=$(realpath "${1:-build-dev-cov}")
shift || true

if [ "$(uname)" = "Darwin" ]; then
  LLVM_PROFDATA="xcrun llvm-profdata"
  LLVM_COV="xcrun llvm-cov"
else
  LLVM_PROFDATA="llvm-profdata${LLVM_SUFFIX}"
  LLVM_COV="llvm-cov${LLVM_SUFFIX}"
fi

OUT_DIR="$BUILD_DIR/coverage"
PROFRAW_DIR="$OUT_DIR/profraw"
PROFDATA="$OUT_DIR/kddw.profdata"

rm -rf "$OUT_DIR"
mkdir -p "$PROFRAW_DIR"

# %p: one file per process, as tests run in parallel. %m: per-module merging.
TESTS_STATUS=0
LLVM_PROFILE_FILE="$PROFRAW_DIR/%p-%m.profraw" ctest --test-dir "$BUILD_DIR" --output-on-failure "$@" || TESTS_STATUS=$?

$LLVM_PROFDATA merge -sparse "$PROFRAW_DIR"/*.profraw -o "$PROFDATA"

# The library holds most of the coverage mappings, but inline and template code is also
# instantiated in the tests, so pass them too.
LIBRARY=$(find "$BUILD_DIR/lib" -type f \( -name 'libkddockwidgets*.so*' -o -name 'libkddockwidgets*.dylib' \) | head -n 1)
OBJECTS=()
for test in "$BUILD_DIR"/bin/tst_*; do
  [ -f "$test" ] && [ -x "$test" ] && OBJECTS+=(-object "$test")
done

COV_ARGS=(
  "$LIBRARY" "${OBJECTS[@]}"
  -instr-profile="$PROFDATA"
  -ignore-filename-regex='(/tests/|/examples/|/3rdparty/|/build-[^/]*/|/usr/|/Qt/|\.framework/|/DragControllerWayland_p\.cpp|/DebugWindow\.|/ObjectViewer\.|/DebugWidgetViewer_p\.h)'
)

$LLVM_COV report "${COV_ARGS[@]}" | tee "$OUT_DIR/summary.txt"
$LLVM_COV show "${COV_ARGS[@]}" -format=html -show-instantiations=false -output-dir="$OUT_DIR/html"
$LLVM_COV export "${COV_ARGS[@]}" -format=lcov >"$OUT_DIR/coverage.lcov"

echo "HTML report: $OUT_DIR/html/index.html"

exit $TESTS_STATUS
