if(${verbose_traversal})
  message(STATUS "Entered ID directory")
endif(${verbose_traversal})

if(NOT(EXISTS "${utility_HEADER_DIR}/ID/src"))
  file(MAKE_DIRECTORY "${utility_HEADER_DIR}/ID/src")
endif(NOT(EXISTS "${utility_HEADER_DIR}/ID/src"))

set(headers "")
list(APPEND headers
  "src/ID"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${utility_HEADER_DIR}/ID/${header}.hpp"
    COPYONLY
    )
  list(APPEND utility_src_headers
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    )
  list(APPEND utility_bin_headers
    "${utility_HEADER_DIR}/ID/${header}.hpp"
    )
endforeach(header)

if (${local_testing})
  list(APPEND testLabels ID)
  add_subdirectory(test)
endif (${local_testing})

list(APPEND utility_src
  )
set(utility_src "${utility_src}" PARENT_SCOPE)
set(utility_src_headers "${utility_src_headers}" PARENT_SCOPE)
set(utility_bin_headers "${utility_bin_headers}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting ID directory")
endif(${verbose_traversal})
