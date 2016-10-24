#include <sstream>

#include "catch.hpp"

#include "utility.hpp"

using namespace utility::stream;

SCENARIO( "manditory getBool returns the proper"
	  " value from streams with valid bools" ){

  const std::string name("testBool");

  GIVEN( "a stream with \'1\' as the next whitespace delimited character" ){
    std::istringstream buffer("  1  ");
    WHEN( "passed to getBool" ){
      THEN( "returns true" ){
	REQUIRE( true == getBool( buffer, name ) );
      }
    }
  }

  GIVEN( "a stream with \'0\' as the next whitespace delimited character" ){
    std::istringstream buffer("  0  ");
    WHEN( "passed to getBool" ){
      THEN( "returns false" ){
	REQUIRE( false == getBool( buffer, name ) );
      }
    }
  }

  GIVEN( "an empty stream" ){
    std::istringstream buffer("    ");
    WHEN( "passed to getBool" ){
      THEN( "throws" ){
	REQUIRE_THROWS( getBool( buffer, name ) );
      }
    }
  }
}

SCENARIO( "optional getBool returns the proper"
	  " value from streams with valid bools" ){
  bool found;
  const std::string name("testBool");

  GIVEN( "a stream with \'1\' as the next whitespace delimited character" ){
    std::istringstream buffer("  1  ");
    WHEN( "passed to getBool" ){
      THEN( "returns true" ){
	REQUIRE(true == utility::stream::getBool(buffer, name, found));
	REQUIRE(found == true);
      }
    }
  }

  GIVEN( "a stream with \'0\' as the next whitespace delimited character" ){
    std::istringstream buffer("  0  ");
    WHEN( "passed to getBool" ){
      THEN( "returns false" ){
	REQUIRE( false == getBool( buffer, name, found ) );
	REQUIRE( found == true );
      }
    }
  }


  GIVEN( "an empty stream" ){
    std::istringstream buffer("    ");
    WHEN( "passed to getBool" ){
      THEN( "does not throw and **found** is set to false" ){
	REQUIRE_NOTHROW( getBool( buffer, name, found ) );
	REQUIRE( false == found );
      }
    }
  }
}

SCENARIO( "getBool throws when passed stream with invalid bool string" ){

  const std::string name("testBool");
  bool found;

  GIVEN( "a stream with int < 0 as the next whitespace delimited character" ){
    std::istringstream buffer("  -1  ");
    WHEN( "passed to manditory getBool" ){
      THEN( "throws" ){
	REQUIRE_THROWS( getBool( buffer, name ) );
      }
    }
  }

  GIVEN( "a stream with int < 0 as the next whitespace delimited character" ){
    std::istringstream buffer("  -1  ");
    WHEN( "passed to optional getBool" ){
      THEN( "throws" ){
	REQUIRE_THROWS( getBool( buffer, name, found ) );
      }
    }
  }

  GIVEN( "a stream with int > 1 as the next whitespace delimited character" ){
    std::istringstream buffer("  2  ");
    WHEN( "passed to manditory getBool" ){
      THEN( "throws" ){
	REQUIRE_THROWS( getBool( buffer, name ) );
      }
    }
  }

  GIVEN( "a stream with int > 1 as the next whitespace delimited character" ){
    std::istringstream buffer("  2  ");
    WHEN( "passed to optional getBool" ){
      THEN( "throws" ){
	REQUIRE_THROWS( getBool( buffer, name, found ) );
      }
    }
  }

  GIVEN( "a stream with real number in (0,1) as the next"
	 " whitespace delimited character" ){
    std::istringstream buffer("  0.33  ");
    WHEN( "passed to manditory getBool" ){
      THEN( "throws" ){
	REQUIRE_THROWS( getBool( buffer, name ) );
      }
    }
  }

  GIVEN( "a stream with realnumber in (0,1) as the next"
	 " whitespace delimited character" ){
    std::istringstream buffer("  0.33  ");
    WHEN( "passed to optional getBool" ){
      THEN( "throws" ){
	REQUIRE_THROWS( getBool( buffer, name, found ) );
      }
    }
  }

  GIVEN( "a stream with illegal characters as the next"
	 " whitespace delimited character" ){
    std::istringstream buffer("  1t  ");
    WHEN( "passed to manditory getBool" ){
      THEN( "throws" ){
	REQUIRE_THROWS( getBool( buffer, name ) );
      }
    }
  }

  GIVEN( "a stream with illegal characters as the next"
	 " whitespace delimited character" ){
    std::istringstream buffer("  1t  ");
    WHEN( "passed to optional getBool" ){
      THEN( "throws" ){
	REQUIRE_THROWS( getBool( buffer, name, found ) );
      }
    }
  }
}
