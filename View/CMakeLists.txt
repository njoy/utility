if(${verbose_traversal})
  message(STATUS "Entered View directory")
endif(${verbose_traversal})

set(header_only_subdirs "")
list(APPEND header_only_subdirs
  "Range"
  )
list(APPEND subdirs
  ${header_only_subdirs}
  )
  
foreach (subdir ${header_only_subdirs})
  if(NOT(EXISTS "${utility_HEADER_DIR}/View/${subdir}"))
    file(MAKE_DIRECTORY "${utility_HEADER_DIR}/View/${subdir}")
  endif(NOT(EXISTS "${utility_HEADER_DIR}/View/${subdir}"))
endforeach (subdir)

set(headers "")
list(APPEND headers
  ${subdirs}
  "iterator"
  "const_iterator"
  "reverse_iterator"
  "const_reverse_iterator"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${utility_HEADER_DIR}/View/${header}.hpp"
    COPYONLY
    )
endforeach(header)

foreach (subdir ${subdirs})
  add_subdirectory( ${subdir} )
endforeach (subdir)

if (${local_testing})
  list(APPEND testLabels View)
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif (${local_testing})

set(utility_src "${utility_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting View directory")
endif(${verbose_traversal})
