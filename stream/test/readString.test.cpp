#include <sstream>

#include "catch.hpp"

#include "utility.hpp"

using namespace utility::stream;

SCENARIO( "readString returns the proper string read from the stream" ){
  GIVEN( "A stream from which a string can be read" ){
    std::stringstream streamer;
    std::string read;

    WHEN( "reading a simple stream" ){
      streamer << "1234567";
      THEN( "the correct string will be read" ){
        read = readString( streamer, 4 );
        REQUIRE( "1234" == read );
      }
    }

    WHEN( "the stream is too short" ){
      streamer << "123";
      THEN( "an exception is thrown"){
        REQUIRE_THROWS( readString( streamer, 4 ) );
      }
    }

    WHEN( "the stream has spaces" ){
      streamer << "123 456";
      THEN( "the stream is read (including the spaces)" ){
        read = readString( streamer, 7 );
        REQUIRE( "123 456" == read );
       }
    }

    WHEN( "the stream has zero length" ){
      streamer << "";
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( readString( streamer, 1 ) );
      }
    }
  } // GIVEN
} // SCENARIO

SCENARIO( "readString with delimiter reads the proper string from the stream" ){
  GIVEN( "A stream from which a string can be read" ){
    std::stringstream streamer;
    std::string read;

    WHEN( "reading a simple stream with no delimiter" ){
      streamer << "1234567";
      THEN( "the correct string will be read" ){
        read = readString( streamer, 4, ' ' );
        REQUIRE( "1234" == read );
      }
    }

    WHEN( "the stream is too short (and no delimiter)" ){
      streamer << "123";
      THEN( "an exception is thrown"){
        REQUIRE_THROWS( readString( streamer, 4, ' ' ) );
      }
    }

    WHEN( "the stream has a space and a space delimiter" ){
      streamer << "123 456";
      THEN( "the stream is read (including the spaces)" ){
        read = readString( streamer, 7, ' ' );
        REQUIRE( "123" == read );
      }
    }

    WHEN( "the stream has a space and a ';' delimiter" ){
      streamer << "123 4;56";
      THEN( "the stream is read (including the spaces)" ){
        read = readString( streamer, 7, ';' );
        REQUIRE( "123 4" == read );
      }
    }

    WHEN( "the stream has leading delimiters" ){
      streamer << "   123 456  ";
      THEN( "the leading elimiters should be ignored" ){
        read = readString( streamer, 7, ' ' );
        REQUIRE( "123" == read );
      }
    }

    WHEN( "the stream has zero length" ){
      streamer << "";
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( readString( streamer, 1, ' ' ) );
      }
    }
  } // GIVEN
} // SCENARIO

