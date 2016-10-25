#!/bin/bash

mkdir build
cd build
cmake -D build_type=$build_type \
      -D static_libraries=$static_libraries \
      -D appended_flags="$appended_flags" \
      -D no_link_time_optimization=TRUE ..
make -j2
export COMPILATION_FAILURE=$?
ctest --output-on-failure -j2
export TEST_FAILURE=$?
if [ $COMPILATION_FAILURE -ne 0 ] || [ $TEST_FAILURE -ne 0 ];
then
    exit 1
else
    exit 0
fi
