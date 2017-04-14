#!/bin/bash
set -x

if [ "$TRAVIS_OS_NAME" = "linux" ]; then
    sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3.8 90 \
         --slave /usr/bin/clang++ clang++ /usr/bin/clang++-3.8
    sudo update-alternatives --config clang
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 90 \
	 --slave /usr/bin/g++ g++ /usr/bin/g++-6 \
	 --slave /usr/bin/gcov gcov /usr/bin/gcov-6 \
	 --slave /usr/bin/gcc-ar ar /usr/bin/gcc-ar-6 \
	 --slave /usr/bin/gcc-nm nm /usr/bin/gcc-nm-6 \
	 --slave /usr/bin/gcc-ranlib ranlib /usr/bin/gcc-ranlib-6
    sudo update-alternatives --config gcc
  if [ "$CXX" = "clang++" ]; then
    export PATH=/usr/bin:$PATH
    export CUSTOM=("-D link_time_optimization=OFF")
  else
    export CUSTOM=('-D CMAKE_AR=/usr/bin/gcc-ar' '-D CMAKE_NM=/usr/bin/gcc-nm' '-D CMAKE_RANLIB=/usr/bin/gcc-ranlib' '-D link_time_optimization=ON')
  fi;
fi

if [ "$build_type" = "coverage" ]; then
  export build_type=DEBUG
  export coverage=true
  export NOPE="$NOPE -D coverage=ON"
else
  export coverage=false
fi;  

./metaconfigure/fetch_subprojects.py
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=$build_type \
      -D static_libraries=$static_libraries \
      -D utility_appended_flags="$appended_flags" \
      ${CUSTOM[@]} ..
make VERBOSE=1 -j2
export COMPILATION_FAILURE=$?
if [ $COMPILATION_FAILURE -ne 0 ];
then
  exit 1
fi

ctest --output-on-failure -j2
export TEST_FAILURE=$?
if [ $TEST_FAILURE -ne 0 ];
then
    exit 1
fi

if $coverage; then
  pip install --user cpp-coveralls
  echo "loading coverage information"
  coveralls  --exclude-pattern "/usr/include/.*|.*/CMakeFiles/.*|.*subprojects.*|.*dependencies.*|.*test\.cpp" --root ".." --build-root "." --gcov-options '\-lp'
fi
