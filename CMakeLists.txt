cmake_minimum_required( VERSION 3.2 )

set(projectName "utility")
set(projectVersion "1.0.0")

if(NOT DEFINED commonCMakeScripts_path)
  set(commonCMakeScripts_path "${CMAKE_SOURCE_DIR}/commonCMakeScripts")
endif(NOT DEFINED commonCMakeScripts_path)

include(subprojects.cmake)
include(${commonCMakeScripts_path}/base.cmake)
include(${commonCMakeScripts_path}/doxygen.cmake)

if(NOT(EXISTS "${utility_HEADER_DIR}/stream"))
  file(MAKE_DIRECTORY "${utility_HEADER_DIR}/stream")
  file(MAKE_DIRECTORY "${utility_HEADER_DIR}/string")
  file(MAKE_DIRECTORY "${utility_HEADER_DIR}/View")
  file(MAKE_DIRECTORY "${utility_HEADER_DIR}/DecoratedTypeName")
endif(NOT(EXISTS "${utility_HEADER_DIR}/stream"))

list(APPEND utility_src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/extractCommand.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utility.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/verifyString.cpp
  )

set(headers "")
list(APPEND headers
  "ID.hpp"
  "View.hpp"
  "DecoratedTypeName.hpp"
  "realNumberStringCollection.hpp"
  "string.hpp"
  "stream.hpp"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.in"
    "${utility_HEADER_DIR}/${header}"
    COPYONLY
    )
endforeach(header)

list(APPEND testLabels utility)

add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/stream" )
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/string" )
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/ID" )
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/View" )
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/DecoratedTypeName" )

if (${local_testing})
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif (${local_testing})

include(${commonCMakeScripts_path}/assemble.cmake)
include(${commonCMakeScripts_path}/terminus.cmake)
