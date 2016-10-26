#!/bin/bash

if [ "$TRAVIS_OS_NAME" = "linux" ]; then
  if [ "$CXX" = "clang++" ]; then
    sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3.8 90 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-3.8
    export appended_flags=$appended_flags"-stdlib=libstdc++"
    export PATH=/usr/bin:$PATH
    export CUSTOM='-D no_link_time_optimization=TRUE'
    sudo update-alternatives --config clang
  else
    ln -s /usr/bin/gcc-ar-6 ar
    ln -s /usr/bin/gcc-ranlib-6 ranlib
    ln -s /usr/bin/gcc-nm-6 nm
    export PATH=$(pwd):$PATH
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 90 --slave /usr/bin/g++ g++ /usr/bin/g++-6 --slave /usr/bin/gcov gcov /usr/bin/gcov-6
    sudo update-alternatives --config gcc
  fi;
fi

mkdir build
cd build
cmake -D build_type=$build_type \
      -D static_libraries=$static_libraries \
      -D appended_flags="$appended_flags" \
      $CUSTOM ..
make -j2
export COMPILATION_FAILURE=$?
ctest --output-on-failure -j2
export TEST_FAILURE=$?
if [ "$build_type" = "coverage" ]
then
    pip install --user cpp-coveralls
    echo "loading coverage information"
    coveralls  --exclude-pattern "/usr/include/.*|.*/CMakeFiles/.*|.*subprojects.*|.*dependencies.*|.*test\.cpp" --root ".." --build-root "." --gcov-options '\-lp'
fi
if [ $COMPILATION_FAILURE -ne 0 ] || [ $TEST_FAILURE -ne 0 ];
then
    exit 1
else
    exit 0
fi
