#include "catch.hpp"

#include "utility.hpp"

using namespace njoy::utility::stream;

SCENARIO( "getIntInRange's left bound is inclusive" ){

  int returnInteger;
  const int tooLow = 1;
  const int leftBound = 5;
  const int rightBound = 10;
  const int intermediate = 7;
  const std::string name("testInteger");

  GIVEN( "a stream with an integer greater than the left bound" ){
    std::istringstream buffer( std::to_string( intermediate ) );
    WHEN( "passed to getIntInRange" ){
      THEN( "the correct integer value will be returned" ){
	REQUIRE_NOTHROW( returnInteger =
			 getIntInRange( buffer, name, leftBound, rightBound ) );
	REQUIRE( intermediate == returnInteger );
      }
    }
  }

  GIVEN( "a stream with an integer equal to the left bound" ){
    std::istringstream buffer( std::to_string( leftBound ) );
    WHEN( "passed to getIntInRange" ){
      THEN( "the correct integer value will be returned" ){
	REQUIRE_NOTHROW( returnInteger =
			 getIntInRange( buffer, name, leftBound, rightBound ) );
	REQUIRE( leftBound == returnInteger );
      }
    }
  }

  GIVEN( "a stream with an integer less than the left bound" ){
    std::istringstream buffer( std::to_string( tooLow ) );
    WHEN( "passed to getIntInRange" ){
      THEN( "will throw" ){
	REQUIRE_THROWS( returnInteger =
			getIntInRange( buffer, name, leftBound, rightBound ) );
      }
    }
  }
}

SCENARIO( "getIntInRange's right bound is exclusive" ){

  int returnInteger;
  const int tooHigh = 15;
  const int leftBound = 5;
  const int rightBound = 10;
  const int intermediate = 7;
  const std::string name( "testInteger" );

  GIVEN( "a stream with an integer greater than the right bound" ){
    std::istringstream buffer( std::to_string( tooHigh ) );
    WHEN( "passed to getIntInRange" ){
      THEN( "will throw" ){
	REQUIRE_THROWS( returnInteger =
			getIntInRange( buffer, name, leftBound, rightBound ) );
      }
    }
  }

  GIVEN( "a stream with an integer equal to the right bound" ){
    std::istringstream buffer( std::to_string( rightBound ) );
    WHEN( "passed to getIntInRange" ){
      THEN( "will throw" ){
	REQUIRE_THROWS( returnInteger =
			getIntInRange( buffer, name, leftBound, rightBound ) );
      }
    }
  }

  GIVEN( "a stream with an integer less than the right bound" ){
    std::istringstream buffer(std::to_string(intermediate));
    WHEN( "passed to getIntInRange" ){
      THEN( "the correct integer value will be returned" ){
	REQUIRE_NOTHROW( returnInteger =
			 getIntInRange( buffer, name, leftBound, rightBound ) );
	REQUIRE( intermediate == returnInteger );
      }
    }
  }

}

/* repetition of the getInteger tests */
SCENARIO( "getIntInRange returns the proper value"
	  " from streams with integer strings" ){

  const std::string name("testInteger");
  std::vector<std::string> bufferQueue;
  bufferQueue.emplace_back(" 123 ");
  bufferQueue.emplace_back(" +123 ");
  bufferQueue.emplace_back(" -123 ");
  bufferQueue.emplace_back(" 0123 ");
  std::istringstream buffer;
  bool found;

  GIVEN( "stream with integer values" ){
    WHEN( "passed to getIntInRange" ){
      THEN( "the correct integer value is returned" ){
	for( std::string& guts : bufferQueue ){
	  buffer.clear();
	  buffer.str( guts );
	  REQUIRE( std::stoi( guts ) ==
		   getIntInRange( buffer, name, -125, 125 ) );
	  buffer.clear();
	  buffer.seekg(0);
	  found = false;
	  REQUIRE( std::stoi( guts ) ==
		   getIntInRange( buffer, name, -125, 125, found ) );
	  REQUIRE( found );
	}
      }
    }
  }

}

SCENARIO( "getIntInRange throws for streams with non-integer strings" ){

  const std::string name("testInteger");
  std::vector<std::string> bufferQueue;
  bufferQueue.emplace_back(" 123. ");
  bufferQueue.emplace_back(" +123.0 ");
  bufferQueue.emplace_back(" -123E2 ");
  bufferQueue.emplace_back(" string ");
  std::istringstream buffer;
  bool found;

  GIVEN( "stream with non-integer values" ){
    WHEN( "passed to getIntInRange" ){
      THEN( "will throw" ){
	for( std::string& guts : bufferQueue ){
	  buffer.clear();
	  buffer.str( guts );
	  REQUIRE_THROWS( getIntInRange( buffer, name, -125, 125 ) );
	  buffer.clear();
	  buffer.seekg(0);
	  REQUIRE_THROWS( getIntInRange( buffer, name, -125, 125, found ) );
	}
      }
    }
  }
}

SCENARIO( "mandatory getIntInRange throws for streams with badbit" ){

  const std::string name("testInteger");
  GIVEN( "empty stream" ){
    std::istringstream buffer;
    WHEN( "passed to getIntInRange" ){
      THEN( "will throw" ){
	REQUIRE_THROWS( getIntInRange( buffer, name, -125, 125 ) );
      }
    }
  }
}

SCENARIO( "optional getIntInRange sets found flag to"
	  " false for streams with badbit" ){

  const std::string name("testInteger");
  bool found = true;
  GIVEN( "empty stream" ){
    std::istringstream buffer;
    WHEN( "passed to getIntInRange" ){
      THEN( "will set found flag to false" ){
	REQUIRE_NOTHROW( getIntInRange( buffer, name, -125, 125, found ) );
	REQUIRE( not found );
      }
    }
  }
}
