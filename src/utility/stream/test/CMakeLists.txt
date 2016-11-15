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
set( test_flags ${utility_compiler_flags} )
separate_arguments( test_flags_list UNIX_COMMAND "${test_flags}" )
foreach( flag IN LISTS test_flags_list )
    target_compile_options( utility.stream.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( utility.stream.test PROPERTIES LINK_FLAGS "${test_flags}" )
target_link_libraries( utility.stream.test PUBLIC utility )
add_test( NAME utility.stream COMMAND utility.stream.test ) 
