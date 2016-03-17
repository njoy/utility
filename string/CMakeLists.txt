if(${verbose_traversal})
  message(STATUS "Entered string subdirectory")
endif(${verbose_traversal})

list(APPEND utility_src 
  "${CMAKE_CURRENT_SOURCE_DIR}/src/split.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/toDouble.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/trim.cpp"
  )

list(APPEND "${utility_src_headers}"
  "${CMAKE_CURRENT_SOURCE_DIR}/unzip.hpp.in"
  )

configure_file( 
  "${CMAKE_CURRENT_SOURCE_DIR}/unzip.hpp.in"
  "${utility_HEADER_DIR}/string/unzip.hpp"
  COPYONLY
  )

list(APPEND "${utility_bin_headers}"
  "${CMAKE_CURRENT_SOURCE_DIR}/string/unzip.hpp"
  )

list(APPEND testLabels string)
if (${local_testing})
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif (${local_testing})

set(utility_src "${utility_src}" PARENT_SCOPE)
set(utility_src_headers "${utility_src_headers}" PARENT_SCOPE)
set(utility_bin_headers "${utility_bin_headers}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting string subdirectory")
endif(${verbose_traversal})
