add_executable( utility.string.test
                isInteger.test.cpp
                isRealNumber.test.cpp
                split.test.cpp
                string.test.cpp
                toDouble.test.cpp
                trim.test.cpp
                unzip.test.cpp )
set( test_flags ${utility_compiler_flags} )
separate_arguments( test_flags_list UNIX_COMMAND "${test_flags}" )
foreach( flag IN LISTS test_flags_list )
    target_compile_options( utility.string.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( utility.string.test PROPERTIES LINK_FLAGS "${test_flags}" )
target_link_libraries( utility.string.test PUBLIC utility )
add_test( NAME utility.string COMMAND utility.string.test ) 
