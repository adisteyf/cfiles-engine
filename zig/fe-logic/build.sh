#! /bin/bash

pushd zig/fe-logic
  zig build-obj -O ReleaseSmall src/main.zig -fPIE
  rm ../../build/fe-logic.o
  mv main.o ../../build/fe-logic.o
popd

