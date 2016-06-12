if(${verbose_traversal})
  message(STATUS "Entered TypeSwitch directory")
endif(${verbose_traversal})

if (${local_testing})
  list(APPEND testLabels TypeSwitch)
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif (${local_testing})

set(utility_src "${utility_src}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting TypeSwitch directory")
endif(${verbose_traversal})
