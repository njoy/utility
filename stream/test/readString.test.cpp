
#include <sstream>

#include "catch.hpp"
#include "easylogging++.h"

#include "utility/stream.hpp"

extern int testNumber;

SCENARIO( "readString returns the proper string read from the stream",
	 "[utility],[stream],[readString]"){

  GIVEN( "A stream from which a string can be read" ){
    std::stringstream streamer;
    std::string read;

    WHEN( "reading a simple stream" ){
      LOG(INFO) << "Test " << ++testNumber <<
        ": [readString] No Errors Expected";
      streamer << "1234567";
      THEN( "the correct string will be read" ){
        read = utility::stream::readString(streamer, 4);
        REQUIRE("1234" == read );
      }
    }

    WHEN( "the stream is too short" ){
      LOG(INFO) << "Test " << ++testNumber <<
        ": [readString] Errors Expected";
      streamer << "123";
      THEN( "an exception is thrown"){
        REQUIRE_THROWS( utility::stream::readString(streamer, 4) );
      }
    }

    WHEN( "the stream has spaces" ){
      LOG(INFO) << "Test " << ++testNumber <<
        ": [readString] No Errors Expected";
      streamer << "123 456";
      THEN( "the stream is read (including the spaces)" ){
        read = utility::stream::readString(streamer, 7);
        REQUIRE( "123 456" == read );
       }
    }

    WHEN( "the stream has zero length" ){
      LOG(INFO) << "Test " << ++testNumber <<
        ": [readString] Errors Expected";
      streamer << "";
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( utility::stream::readString(streamer, 1) );
      }
    }
  } // GIVEN


} // SCENARIO
SCENARIO( "readString with delimiter reads the proper string from the stream",
	 "[utility],[stream],[readString]"){

  GIVEN( "A stream from which a string can be read" ){
    std::stringstream streamer;
    std::string read;

    WHEN( "reading a simple stream with no delimiter" ){
      LOG(INFO) << "Test " << ++testNumber <<
        ": [readString] No Errors Expected";
      streamer << "1234567";
      THEN( "the correct string will be read" ){
        read = utility::stream::readString(streamer, 4,  ' ');
        REQUIRE("1234" == read );
      }
    }

    WHEN( "the stream is too short (and no delimiter)" ){
      LOG(INFO) << "Test " << ++testNumber <<
        ": [readString] No Errors Expected";
      streamer << "123";
      THEN( "an exception is thrown"){
        REQUIRE_THROWS( utility::stream::readString(streamer, 4,  ' ') );
      }
    }

    WHEN( "the stream has a space and a space delimiter" ){
      LOG(INFO) << "Test " << ++testNumber <<
        ": [readString] No Errors Expected";
      streamer << "123 456";
      THEN( "the stream is read (including the spaces)" ){
        read = utility::stream::readString(streamer, 7,  ' ');
        REQUIRE( "123" == read );
       }
    }

    WHEN( "the stream has a space and a ';' delimiter" ){
      LOG(INFO) << "Test " << ++testNumber <<
        ": [readString] No Errors Expected";
      streamer << "123 4;56";
      THEN( "the stream is read (including the spaces)" ){
        read = utility::stream::readString(streamer, 7, ';');
        REQUIRE( "123 4" == read );
       }
    }

    WHEN( "the stream has leading delimiters" ){
      LOG(INFO) << "Test " << ++testNumber <<
        ": [readString] No Errors Expected";
      streamer << "   123 456  ";
      THEN( "the leading elimiters should be ignored" ){
        read = utility::stream::readString(streamer, 7, ' ');
        REQUIRE( "123" == read );
      }
    }

    WHEN( "the stream has zero length" ){
      LOG(INFO) << "Test " << ++testNumber <<
        ": [readString] Errors Expected";
      streamer << "";
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( utility::stream::readString(streamer, 1,  ' ') );
      }
    }
  } // GIVEN

} // SCENARIO

