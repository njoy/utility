########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )
project( utility LANGUAGES CXX )


########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

option( utility_unit_tests
    "Compile the utility unit tests and integrate with ctest" ON
    )
option( strict_compile
    "Treat all warnings as errors." ON
    )

# Compile flags
set( common_flags "-Wall" "-Wextra" "-Wpedantic" )
set( strict_flags "-Werror" )
set( release_flags "-O3" )
set( debug_flags "-O0" "-g" )


########################################################################
# Dependencies
########################################################################

set( REPOSITORIES "release"
    CACHE STRING
    "Options for where to fetch repositories: develop, release, local"
    )

if( REPOSITORIES STREQUAL "develop" )
    include( cmake/develop_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "release" )
    include( cmake/release_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "local" )
    include( cmake/local_dependencies.cmake )

endif()


########################################################################
# Project targets
########################################################################

add_library( utility 
    src/utility/stream/src/getBool.cpp
    src/utility/stream/src/getEnergy.cpp
    src/utility/stream/src/getIntInRange.cpp
    src/utility/stream/src/getIntWithLBound.cpp
    src/utility/stream/src/getInteger.cpp
    src/utility/stream/src/getLine.cpp
    src/utility/stream/src/getRealNumber.cpp
    src/utility/stream/src/getRealWithLBound.cpp
    src/utility/stream/src/getStringArg.cpp
    src/utility/stream/src/getTemperature.cpp
    src/utility/stream/src/readString.cpp
    src/utility/string/src/split.cpp
    src/utility/string/src/toDouble.cpp
    src/utility/string/src/trim.cpp
    )
target_include_directories( utility PUBLIC src/ )
target_link_libraries( utility
    PUBLIC catch-adapter
    PUBLIC header-utilities
    )
target_compile_options( utility PRIVATE
    ${common_flags}
    $<$<BOOL:${strict_compile}>:${strict_flags}>
    $<$<CONFIG:DEBUG>:${debug_flags}>
    $<$<CONFIG:RELEASE>:${release_flags}>
    )


#######################################################################
# Top-level Only
#######################################################################

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )

    # unit testing
    if( utility_unit_tests )
        include( cmake/unit_testing.cmake )
    endif()

endif()
