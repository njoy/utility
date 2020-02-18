
add_executable( utility.stream.basic_RecordOrientedStream.test
                fstreamRegression.test.cpp
                basic_RecordOrientedStream.test.cpp )
target_compile_options( utility.stream.basic_RecordOrientedStream.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${utility_appended_flags} )
target_link_libraries( utility.stream.basic_RecordOrientedStream.test PUBLIC utility ) 
file( GLOB resources "resources/*" )
foreach( resource ${resources})
    file( COPY "${resource}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )
endforeach()
add_test( NAME utility.stream.basic_RecordOrientedStream COMMAND utility.stream.basic_RecordOrientedStream.test )