#######################################################################
# Setup
#######################################################################

message( STATUS "Adding utility unit testing" )
enable_testing()


#######################################################################
# Unit testing directories
#######################################################################

add_subdirectory( src/utility/stream/basic_FILE_streambuf/test )
add_subdirectory( src/utility/stream/basic_RecordOrientedStream/test )
add_subdirectory( src/utility/stream/basic_TeeStream/test )
add_subdirectory( src/utility/stream/basic_TemporaryFileStream/test )
add_subdirectory( src/utility/stream/test )
add_subdirectory( src/utility/string/test )
