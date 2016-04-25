if(${verbose_traversal})
  message(STATUS "Entered Id directory")
endif(${verbose_traversal})

set(header_only_subdirs "")
list(APPEND header_only_subdirs
  )
list(APPEND subdirs
  ${header_only_subdirs}
  )
  
foreach (subdir ${header_only_subdirs})
  if(NOT(EXISTS "${utility_HEADER_DIR}/Id/${subdir}"))
    file(MAKE_DIRECTORY "${utility_HEADER_DIR}/Id/${subdir}")
  endif(NOT(EXISTS "${utility_HEADER_DIR}/Id/${subdir}"))
endforeach (subdir)

set(headers "")
list(APPEND headers
  ${subdirs}
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${utility_HEADER_DIR}/Id/${header}.hpp"
    COPYONLY
    )
endforeach(header)

foreach (subdir ${subdirs})
  add_subdirectory( ${subdir} )
endforeach (subdir)

if (${local_testing})
  list(APPEND testLabels Id)
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif (${local_testing})

set(utility_src "${utility_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting Id directory")
endif(${verbose_traversal})
