
add_executable( utility.stream.test
                getBool.test.cpp
                getEnergy.test.cpp
                getInteger.test.cpp
                getIntInRange.test.cpp
                getIntWithLBound.test.cpp
                getLine.test.cpp
                getRealNumber.test.cpp
                getRealWithLBound.test.cpp
                getStringArg.test.cpp
                getTemperature.test.cpp
                readString.test.cpp
                stream.test.cpp )
target_compile_options( utility.stream.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${utility_appended_flags} )
target_link_libraries( utility.stream.test PUBLIC utility ) 
add_test( NAME utility.stream COMMAND utility.stream.test )