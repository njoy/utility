if(${verbose_traversal})
  message(STATUS "Entered Range directory")
endif(${verbose_traversal})

set(headers "")
list(APPEND headers
  "IteratorRange"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${utility_HEADER_DIR}/View/Range/${header}.hpp"
    COPYONLY
    )
  list(APPEND utility_src_headers
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    )
  list(APPEND utility_bin_headers
    "${utility_HEADER_DIR}/View/Range/${header}.hpp"
    )
endforeach(header)

# add_subdirectory( ${subdir} )

set(utility_src "${utility_src}" PARENT_SCOPE)
set(utility_src_headers "${utility_src_headers}" PARENT_SCOPE)
set(utility_bin_headers "${utility_bin_headers}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting Range directory")
endif(${verbose_traversal})
