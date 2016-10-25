#include <sstream>

#include "catch.hpp"

#include "utility.hpp"

using namespace njoy::utility::stream;

SCENARIO( "getLine can extract lines of text" ){

  GIVEN( "a stream with a single line" ){
    const std::string card( "this is a card" );
    std::istringstream buffer( card );
    WHEN( "passed to getLine once" ){
      THEN( "will not throw" ){
	std::string returnCard;
	REQUIRE_NOTHROW( returnCard = getLine( buffer ) );
	REQUIRE( card == returnCard );
      }
    }
  }

  GIVEN( "a stream with a multiple lines" ){
    const std::string card1( "this is card1" );
    const std::string card2( "this is card2" );
    const std::string card3( "this is card3" );
    std::istringstream buffer( card1 + '\n' + card2 + '\n' + card3 );
    WHEN( "passed to getLine multiple times" ){
      THEN( "will not throw" ){
	std::string returnCard;
	REQUIRE_NOTHROW( returnCard = getLine( buffer ) );
	REQUIRE( card1 == returnCard );
	REQUIRE_NOTHROW( returnCard = getLine( buffer ) );
	REQUIRE( card2 == returnCard );
	REQUIRE_NOTHROW( returnCard = getLine( buffer ) );
	REQUIRE( card3 == returnCard );
      }
    }
  }
}

SCENARIO( "getLine will throw when called"
	  " on stream state bit on stream is bad" ){
  
  GIVEN( "a stream with a no lines" ){
    std::istringstream buffer;
    WHEN( "passed to getLine" ){
      THEN( "will throw" ){
	std::string returnCard;
	REQUIRE_THROWS( returnCard = getLine( buffer ) );
      }
    }
  }

  GIVEN( "a stream with a single line" ){
    const std::string card( "this is a card" );
    std::istringstream buffer( card );
    WHEN( "passed to getLine twice" ){
      THEN( "will throw" ){
	std::string returnCard;
	REQUIRE_NOTHROW( returnCard = getLine( buffer ) );
	REQUIRE( card == returnCard );
	REQUIRE_THROWS( returnCard = njoy::utility::stream::getLine( buffer ) );
      }
    }
  }

  GIVEN( "a stream with a n lines" ){
    const std::string card1( "this is card1" );
    const std::string card2( "this is card2" );
    const std::string card3( "this is card3" );
    std::istringstream buffer( card1 + '\n' + card2 + '\n' + card3 );
    WHEN( "passed to getLine n+1 times" ){
      THEN( "will throw" ){
	std::string returnCard;
	REQUIRE_NOTHROW( returnCard = getLine( buffer ) );
	REQUIRE( card1 == returnCard );
	REQUIRE_NOTHROW( returnCard = getLine( buffer ) );
	REQUIRE( card2 == returnCard );
	REQUIRE_NOTHROW( returnCard = getLine( buffer ) );
	REQUIRE( card3 == returnCard );
	REQUIRE_THROWS( returnCard = getLine( buffer ) );
      }
    }
  }
}
