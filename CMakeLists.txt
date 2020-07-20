########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )
project( utility LANGUAGES CXX )


########################################################################
# Dependencies
########################################################################

include( cmake/utility_dependencies.cmake )


########################################################################
# Project targets
########################################################################

add_library( utility
    src/utility.hpp
    src/utility/realNumberStringCollection.hpp
    src/utility/stream.hpp
    src/utility/string.hpp
    src/utility/stream/basic_Tee_streambuf.hpp
    src/utility/stream/basic_TeeStream.hpp
    src/utility/stream/basic_FILE_streambuf.hpp
    src/utility/stream/basic_TemporaryFileStream.hpp
    src/utility/stream/basic_RecordOrientedStream.hpp
    src/utility/stream/basic_RecordOriented_streambuf.hpp
    src/utility/stream/basic_FILE_streambuf/src/overflow.hpp
    src/utility/stream/basic_FILE_streambuf/src/underflow.hpp
    src/utility/stream/basic_FILE_streambuf/src/ctor.hpp
    src/utility/stream/basic_FILE_streambuf/src/flush.hpp
    src/utility/stream/basic_FILE_streambuf/src/dtor.hpp
    src/utility/stream/basic_TeeStream/src/ctor.hpp
    src/utility/stream/basic_TeeStream/src/dtor.hpp
    src/utility/stream/basic_TeeStream/src/assignment.hpp
    src/utility/stream/basic_TemporaryFileStream/src/file.hpp
    src/utility/stream/basic_TemporaryFileStream/src/path.hpp
    src/utility/stream/basic_TemporaryFileStream/src/ctor.hpp
    src/utility/stream/basic_TemporaryFileStream/src/dtor.hpp
    src/utility/stream/basic_TemporaryFileStream/src/assignment.hpp
    src/utility/stream/basic_RecordOrientedStream/src/ctor.hpp
    src/utility/stream/basic_RecordOrientedStream/src/dtor.hpp
    src/utility/stream/basic_RecordOrientedStream/src/assignment.hpp
    src/utility/string/unzip.hpp
    src/utility/stream/src/getRealWithLBound.cpp
    src/utility/stream/src/getRealNumber.cpp
    src/utility/stream/src/readString.cpp
    src/utility/stream/src/getLine.cpp
    src/utility/stream/src/getInteger.cpp
    src/utility/stream/src/getBool.cpp
    src/utility/stream/src/getTemperature.cpp
    src/utility/stream/src/getIntInRange.cpp
    src/utility/stream/src/getEnergy.cpp
    src/utility/stream/src/getStringArg.cpp
    src/utility/stream/src/getIntWithLBound.cpp
    src/utility/string/src/split.cpp
    src/utility/string/src/toDouble.cpp
    src/utility/string/src/trim.cpp
    )
target_include_directories( utility PUBLIC src/ )
target_link_libraries( utility
    PUBLIC catch-adapter
    PUBLIC header-utilities
    )
