add_executable( stream.test
                FILE_streambuf.test.cpp
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
                stream.test.cpp
                TemporaryFileStream.test.cpp )
set( test_flags ${utility_compiler_flags} )
separate_arguments( test_flags_list UNIX_COMMAND "${test_flags}" )
foreach( flag IN LISTS test_flags_list )
    target_compile_options( stream.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( stream.test PROPERTIES LINK_FLAGS "${test_flags}" )
target_link_libraries( stream.test PUBLIC utility )
add_test( NAME stream COMMAND stream.test ) 
