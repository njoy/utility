
cmake_minimum_required( VERSION 3.2 )
set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Supported configuration types" FORCE )
        
project( utility LANGUAGES CXX )
get_directory_property( is_subproject PARENT_DIRECTORY )
include( CMakeDependentOption REQUIRED )

set( utility_AppleClang_minimum_version 8.0 )
set( utility_GNU_minimum_version 6.2 )
set( utility_Clang_minimum_version 3.8 )

if( utility_${CMAKE_CXX_COMPILER_ID}_minimum_version )
    if( CMAKE_CXX_COMPILER_VERSION AND
        CMAKE_CXX_COMPILER_VERSION VERSION_LESS
        ${utility_${CMAKE_CXX_COMPILER_ID}_minimum_version} )
        message( FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} version must be greater than ${utility_${CMAKE_CXX_COMPILER_ID}_minimum_version}" )
    endif()
endif()

# general properties
option( utility_strict "Compile time warnings are converted to errors" ON )

# binary instrumentation
option( coverage "Enable binary instrumentation to collect test coverage information in the DEBUG configuration" )
option( profile_generate "Enable binary instrumentation to generation execution profiles in the RELEASE configuration which may be used to guide later optimization" )

# additional optimizations
option( link_time_optimization "Enable link time optimization in the RELEASE configuration" )
option( profile_use "In the RELEASE configuration, leverage previously generated execution profile to inform optimization decisions" )
option( nonportable_optimization "Enable optimizations which compromise portability of resulting binary in the RELEASE configuration" )

# libraries and linking
option( static "Statically link component and environment libraries" OFF )
if ( static AND ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin" ) )
    message( FATAL_ERROR "Static binaries not supported on OSX" )
endif()

CMAKE_DEPENDENT_OPTION( static_libraries "Statically link component libraries" OFF "NOT static" ON )
CMAKE_DEPENDENT_OPTION( static_utility "Statically link the utility component library" OFF "NOT static;NOT static_libraries" ON ) 

option( unit_tests "Compile the utility unit tests and integrate with ctest" ON ) 

if ( profile_generate AND profile_use )
    message( FATAL_ERROR "Cannot both generate and use execution profile in the same configuration" )
endif()

if ( profile_generate )
    file( MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/profiling" )
endif()

set( utility_AppleClang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( utility_AppleClang_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( utility_AppleClang_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( utility_AppleClang_Darwin_strict_flags "-Werror" )
set( utility_AppleClang_Darwin_coverage_flags "--coverage" )
set( utility_AppleClang_Darwin_subproject_flags  )
set( utility_AppleClang_Darwin_base_project_flags  )
set( utility_AppleClang_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_AppleClang_Darwin_link_time_optimization_flags "-flto" )
set( utility_AppleClang_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_AppleClang_Darwin_nonportable_optimization_flags "-march=native" )
set( utility_AppleClang_Darwin_static_flags "-static" )
set( utility_GNU_MinGW_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( utility_GNU_MinGW_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( utility_GNU_MinGW_RELEASE_flags "-O3" "-DNDEBUG" )
set( utility_GNU_MinGW_strict_flags "-Werror" )
set( utility_GNU_MinGW_coverage_flags "--coverage" )
set( utility_GNU_MinGW_subproject_flags  )
set( utility_GNU_MinGW_base_project_flags  )
set( utility_GNU_MinGW_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_GNU_MinGW_link_time_optimization_flags "-flto" )
set( utility_GNU_MinGW_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_GNU_MinGW_nonportable_optimization_flags "-march=native" )
set( utility_GNU_MinGW_static_flags "-static" )
set( utility_GNU_Linux_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( utility_GNU_Linux_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( utility_GNU_Linux_RELEASE_flags "-O3" "-DNDEBUG" )
set( utility_GNU_Linux_strict_flags "-Werror" )
set( utility_GNU_Linux_coverage_flags "--coverage" )
set( utility_GNU_Linux_subproject_flags  )
set( utility_GNU_Linux_base_project_flags  )
set( utility_GNU_Linux_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_GNU_Linux_link_time_optimization_flags "-flto" )
set( utility_GNU_Linux_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_GNU_Linux_nonportable_optimization_flags "-march=native" )
set( utility_GNU_Linux_static_flags "-static" )
set( utility_GNU_Windows_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( utility_GNU_Windows_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( utility_GNU_Windows_RELEASE_flags "-O3" "-DNDEBUG" )
set( utility_GNU_Windows_strict_flags "-Werror" )
set( utility_GNU_Windows_coverage_flags "--coverage" )
set( utility_GNU_Windows_subproject_flags  )
set( utility_GNU_Windows_base_project_flags  )
set( utility_GNU_Windows_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_GNU_Windows_link_time_optimization_flags "-flto" )
set( utility_GNU_Windows_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_GNU_Windows_nonportable_optimization_flags "-march=native" )
set( utility_GNU_Windows_static_flags "-static" )
set( utility_GNU_Darwin_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( utility_GNU_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( utility_GNU_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( utility_GNU_Darwin_strict_flags "-Werror" )
set( utility_GNU_Darwin_coverage_flags "--coverage" )
set( utility_GNU_Darwin_subproject_flags  )
set( utility_GNU_Darwin_base_project_flags  )
set( utility_GNU_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_GNU_Darwin_link_time_optimization_flags "-flto" )
set( utility_GNU_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_GNU_Darwin_nonportable_optimization_flags "-march=native" )
set( utility_GNU_Darwin_static_flags "-static" )
set( utility_GNU_CYGWIN_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=gnu++17" )
set( utility_GNU_CYGWIN_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( utility_GNU_CYGWIN_RELEASE_flags "-O3" "-DNDEBUG" )
set( utility_GNU_CYGWIN_strict_flags "-Werror" )
set( utility_GNU_CYGWIN_coverage_flags "--coverage" )
set( utility_GNU_CYGWIN_subproject_flags  )
set( utility_GNU_CYGWIN_base_project_flags  )
set( utility_GNU_CYGWIN_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_GNU_CYGWIN_link_time_optimization_flags "-flto" )
set( utility_GNU_CYGWIN_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_GNU_CYGWIN_nonportable_optimization_flags "-march=native" )
set( utility_GNU_CYGWIN_static_flags "-static" )
set( utility_Clang_MinGW_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( utility_Clang_MinGW_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( utility_Clang_MinGW_RELEASE_flags "-O3" "-DNDEBUG" )
set( utility_Clang_MinGW_strict_flags "-Werror" )
set( utility_Clang_MinGW_coverage_flags "--coverage" )
set( utility_Clang_MinGW_subproject_flags  )
set( utility_Clang_MinGW_base_project_flags  )
set( utility_Clang_MinGW_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_Clang_MinGW_link_time_optimization_flags "-flto" )
set( utility_Clang_MinGW_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_Clang_MinGW_nonportable_optimization_flags "-march=native" )
set( utility_Clang_MinGW_static_flags "-static" )
set( utility_Clang_Linux_common_flags "-stdlib=libstdc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( utility_Clang_Linux_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( utility_Clang_Linux_RELEASE_flags "-O3" "-DNDEBUG" )
set( utility_Clang_Linux_strict_flags "-Werror" )
set( utility_Clang_Linux_coverage_flags "--coverage" )
set( utility_Clang_Linux_subproject_flags  )
set( utility_Clang_Linux_base_project_flags  )
set( utility_Clang_Linux_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_Clang_Linux_link_time_optimization_flags "-flto" )
set( utility_Clang_Linux_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_Clang_Linux_nonportable_optimization_flags "-march=native" )
set( utility_Clang_Linux_static_flags "-static" )
set( utility_Clang_Windows_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( utility_Clang_Windows_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( utility_Clang_Windows_RELEASE_flags "-O3" "-DNDEBUG" )
set( utility_Clang_Windows_strict_flags "-Werror" )
set( utility_Clang_Windows_coverage_flags "--coverage" )
set( utility_Clang_Windows_subproject_flags  )
set( utility_Clang_Windows_base_project_flags  )
set( utility_Clang_Windows_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_Clang_Windows_link_time_optimization_flags "-flto" )
set( utility_Clang_Windows_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_Clang_Windows_nonportable_optimization_flags "-march=native" )
set( utility_Clang_Windows_static_flags "-static" )
set( utility_Clang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( utility_Clang_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( utility_Clang_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( utility_Clang_Darwin_strict_flags "-Werror" )
set( utility_Clang_Darwin_coverage_flags "--coverage" )
set( utility_Clang_Darwin_subproject_flags  )
set( utility_Clang_Darwin_base_project_flags  )
set( utility_Clang_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_Clang_Darwin_link_time_optimization_flags "-flto" )
set( utility_Clang_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_Clang_Darwin_nonportable_optimization_flags "-march=native" )
set( utility_Clang_Darwin_static_flags "-static" )
set( utility_Clang_CYGWIN_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=gnu++17" )
set( utility_Clang_CYGWIN_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( utility_Clang_CYGWIN_RELEASE_flags "-O3" "-DNDEBUG" )
set( utility_Clang_CYGWIN_strict_flags "-Werror" )
set( utility_Clang_CYGWIN_coverage_flags "--coverage" )
set( utility_Clang_CYGWIN_subproject_flags  )
set( utility_Clang_CYGWIN_base_project_flags  )
set( utility_Clang_CYGWIN_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_Clang_CYGWIN_link_time_optimization_flags "-flto" )
set( utility_Clang_CYGWIN_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( utility_Clang_CYGWIN_nonportable_optimization_flags "-march=native" )
set( utility_Clang_CYGWIN_static_flags "-static" )

if ( static_utility )
    set( utility_library_linkage STATIC )
else ()
    set( utility_library_linkage SHARED )
endif ()

set( CMAKE_SKIP_BUILD_RPATH FALSE )
set( CMAKE_BUILD_WITH_INSTALL_RPATH FALSE )
if ( CMAKE_SYSTEM_NAME STREQUAL "Darwin" )
    set( rpath_prefix "@loader_path" )
else()
    set( rpath_prefix "\\$ORIGIN" )
endif()
list( INSERT 0 CMAKE_INSTALL_RPATH "${rpath_prefix}/../lib" )
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )
get_directory_property( is_subproject PARENT_DIRECTORY )

add_library( utility ${utility_library_linkage}
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/realNumberStringCollection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/string.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_Tee_streambuf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_TeeStream.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_FILE_streambuf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_TemporaryFileStream.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_RecordOrientedStream.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_RecordOriented_streambuf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_FILE_streambuf/src/overflow.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_FILE_streambuf/src/underflow.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_FILE_streambuf/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_FILE_streambuf/src/flush.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_FILE_streambuf/src/dtor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_TeeStream/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_TeeStream/src/dtor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_TeeStream/src/assignment.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_TemporaryFileStream/src/file.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_TemporaryFileStream/src/path.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_TemporaryFileStream/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_TemporaryFileStream/src/dtor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_TemporaryFileStream/src/assignment.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_RecordOrientedStream/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_RecordOrientedStream/src/dtor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/basic_RecordOrientedStream/src/assignment.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/string/unzip.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/src/getRealWithLBound.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/src/getRealNumber.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/src/readString.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/src/getLine.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/src/getInteger.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/src/getBool.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/src/getTemperature.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/src/getIntInRange.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/src/getEnergy.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/src/getStringArg.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/stream/src/getIntWithLBound.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/string/src/split.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/string/src/toDouble.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/string/src/trim.cpp" )

target_include_directories( utility PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/src src/ )

set( PREFIX utility_${CMAKE_CXX_COMPILER_ID}_${CMAKE_SYSTEM_NAME} )

target_compile_options( utility PRIVATE 
${${PREFIX}_common_flags}
$<$<BOOL:${utility_strict}>:${${PREFIX}_strict_flags}>
$<$<BOOL:${static}>:${${PREFIX}_static_flags}>
$<$<BOOL:${is_subproject}>:${${PREFIX}_subproject_flags}>
$<$<NOT:$<BOOL:${is_subproject}>>:${${PREFIX}_base_project_flags}>
$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags} 
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags} 
$<$<BOOL:${profile_generate}>:${${PREFIX}_profile_generate_flags}> 
$<$<BOOL:${profile_use}>:${${PREFIX}_profile_use_flags}> 
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}> 
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>
${CXX_appended_flags} ${utility_appended_flags} )

target_link_libraries( utility PUBLIC "$<$<AND:$<CONFIG:RELEASE>,$<BOOL:${link_time_optimization}>>:${${PREFIX}_RELEASE_flags};${${PREFIX}_link_time_optimization_flags}$<$<BOOL:${profile_generate}>:${${PREFIX}_profile_generate_flags};>$<$<BOOL:${profile_use}>:${${PREFIX}_profile_use_flags};>$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags};>>$<$<CONFIG:DEBUG>:$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags};>>$<$<BOOL:CXX_appended_flags>:${CXX_appended_flags};>$<$<BOOL:utility_appended_flags>:${utility_appended_flags};>" )

target_link_libraries( utility PUBLIC catch-adapter PUBLIC header-utilities )

install( DIRECTORY src// DESTINATION include
         FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                          GROUP_READ
                          WORLD_READ
         DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE
                               GROUP_READ
                               WORLD_READ
         FILES_MATCHING REGEX ".*\.h[+][+]$|.*\.hxx$|.*\.hpp$|.*\.hh$|.*\.h$"  )

                    INCLUDE(CPack)
                    
