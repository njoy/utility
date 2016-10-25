add_executable( string.test
                isInteger.test.cpp
                isRealNumber.test.cpp
                split.test.cpp
                string.test.cpp
                toDouble.test.cpp
                trim.test.cpp
                unzip.test.cpp )
set( test_flags ${utility_compiler_flags} )
separate_arguments( test_flags )
foreach( flag IN LISTS test_flags )
    target_compile_options( string.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( string.test PROPERTIES LINK_FLAGS "${utility_compiler_flags}" )
target_link_libraries( string.test PUBLIC utility )
add_test( NAME string COMMAND string.test ) 
