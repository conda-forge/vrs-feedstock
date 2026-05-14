#!/bin/bash

set -euxo pipefail

test -f "${PREFIX}/bin/vrsplayer"
test -f "${PREFIX}/bin/vrs"

cmake tests \
  ${CMAKE_ARGS:-} \
  -G Ninja \
  -B tests/build \
  -DCMAKE_BUILD_TYPE=Release

cmake --build tests/build --parallel

./tests/build/vrs_consumer_test
test -s my_record_file.vrs
