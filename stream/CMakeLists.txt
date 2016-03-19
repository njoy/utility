if(${verbose_traversal})
  message(STATUS "Entered stream subdirectory")
endif(${verbose_traversal})

list(APPEND utility_src 
  "${CMAKE_CURRENT_SOURCE_DIR}/src/getBool.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/getLine.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/getEnergy.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/getInteger.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/getIntInRange.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/getIntWithLBound.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/getRealNumber.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/getRealWithLBound.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/getStringArg.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/getTemperature.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/readString.cpp"
)

list(APPEND testLabels stream)
if (${local_testing})
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif (${local_testing})

set(utility_src "${utility_src}" PARENT_SCOPE)
set(utility_src_headers "${utility_src_headers}" PARENT_SCOPE)
set(utility_bin_headers "${utility_bin_headers}" PARENT_SCOPE)

if(${verbose_traversal})
  message(STATUS "Exiting stream subdirectory")
endif(${verbose_traversal})
