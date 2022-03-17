#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

for arg in "$@"; do
  echo "Testing ${arg}" && diff -q                                                        \
                                                                                          \
  <(                                                                                      \
    clang++ -I"./eigen" -std=c++17 -DVERSION_NC -DNDEBUG -O3 -S -o- "${arg}"              \
      -DEIGEN_PLAINOBJECTBASE_PLUGIN=\""${SCRIPT_DIR}"/../EigenPlainobjectbasePlugin.h\"  \
      -DEIGEN_VECTORWISEOP_PLUGIN=\""${SCRIPT_DIR}"/../EigenVectorwiseopPlugin.h\"        \
      -DEIGEN_MATRIXBASE_PLUGIN=\""${SCRIPT_DIR}"/../EigenMatrixbasePlugin.h\"            \
      -DEIGEN_ARRAYBASE_PLUGIN=\""${SCRIPT_DIR}"/../EigenArraybasePlugin.h\"              \
      -DEIGEN_DENSEBASE_PLUGIN=\""${SCRIPT_DIR}"/../EigenDensebasePlugin.h\"              \
      -DEIGEN_FUNCTORS_PLUGIN=\""${SCRIPT_DIR}"/../EigenFunctorsPlugin.h\"                \
                                                                                          \
      | sed -e '1,/begin-asm/d' | sed -e '1,/end-asm/!d' | awk NF=1 || kill $$            \
  )                                                                                       \
                                                                                          \
  <(                                                                                      \
    clang++ -I"./eigen" -std=c++17 -DNDEBUG -O3 -S -o- "${arg}"                           \
      -DEIGEN_PLAINOBJECTBASE_PLUGIN=\""${SCRIPT_DIR}"/../EigenPlainobjectbasePlugin.h\"  \
      -DEIGEN_VECTORWISEOP_PLUGIN=\""${SCRIPT_DIR}"/../EigenVectorwiseopPlugin.h\"        \
      -DEIGEN_MATRIXBASE_PLUGIN=\""${SCRIPT_DIR}"/../EigenMatrixbasePlugin.h\"            \
      -DEIGEN_ARRAYBASE_PLUGIN=\""${SCRIPT_DIR}"/../EigenArraybasePlugin.h\"              \
      -DEIGEN_DENSEBASE_PLUGIN=\""${SCRIPT_DIR}"/../EigenDensebasePlugin.h\"              \
      -DEIGEN_FUNCTORS_PLUGIN=\""${SCRIPT_DIR}"/../EigenFunctorsPlugin.h\"                \
                                                                                          \
      | sed -e '1,/begin-asm/d' | sed -e '1,/end-asm/!d' | awk NF=1 || kill $$            \
  ) || exit 1
done
