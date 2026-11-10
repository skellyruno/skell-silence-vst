#!/usr/bin/env bash
set -euo pipefail
here="$(cd "$(dirname "$0")" && pwd)"
compiler="${CXX:-c++}"
"$compiler" -std=c++17 -Wall -Wextra -pedantic -O2 "$here/test_dsp.cpp" -o "$here/.test_dsp"
"$here/.test_dsp"
"$compiler" -std=c++17 -Wall -Wextra -pedantic -O2 "$here/test_regression.cpp" -o "$here/.test_regression"
"$here/.test_regression"
rm -f "$here/.test_dsp" "$here/.test_regression"
