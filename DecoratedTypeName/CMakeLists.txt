if(${verbose_traversal})
  message(STATUS "Entered DecoratedTypeName directory")
endif(${verbose_traversal})

if (${local_testing})
  list(APPEND testLabels DecoratedTypeName)
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif (${local_testing})

set(utility_src "${utility_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting DecoratedTypeName directory")
endif(${verbose_traversal})
