
add_executable( utility.string.test
                split.test.cpp
                isInteger.test.cpp
                trim.test.cpp
                unzip.test.cpp
                string.test.cpp
                toDouble.test.cpp
                isRealNumber.test.cpp )
target_compile_options( utility.string.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${utility_appended_flags} )
target_link_libraries( utility.string.test PUBLIC utility ) 
add_test( NAME utility.string COMMAND utility.string.test )