#include <sstream>

#include "catch.hpp"

#include "utility.hpp"
#include "utility/realNumberStringCollection.hpp"

namespace rnsc = njoy::utility::realNumberStringCollection;
using namespace njoy::utility::stream;

SCENARIO( "getRealWithLBound returns the proper value"
	  " from streams with valid real number strings >= bound" ){

  const std::string name("testReal");
  const double lBound = 0.0;
  bool found;
  std::istringstream buffer;
  double residual;

  GIVEN( "streams with valid real number strings with value >= bound" ){
    WHEN( "passed to getRealWithLBound" ){
      THEN( "returns the correct energy" ){
        for ( auto rnp : rnsc::valid ){
          if ( rnp.first >= lBound ){
            for ( auto rns : rnp.second ){
              buffer.clear();
              buffer.str( rns );
              residual =
		std::abs( rnp.first
			  - getRealWithLBound( buffer, name, lBound ) );
              REQUIRE( residual < 0.000001 );
              buffer.clear();
              buffer.seekg(0);
              found = false;
              residual =
		std::abs( rnp.first
			  - getRealWithLBound( buffer, name, lBound, found ) ); 
              REQUIRE( residual < 0.000001 );
              REQUIRE( found );
            }
          }
        }
      }
    }
  }
}

SCENARIO( "getRealWithLBound throws for streams"
	  " with valid real number strings < bound" ){

  const std::string name( "testReal" );
  const double lBound = 0.0;
  bool found;
  std::istringstream buffer;

  GIVEN( "streams with valid real number strings with value < bound" ){
    WHEN( "passed to getRealWithLBound" ){
      THEN( "throws" ){
        for ( auto rnp : rnsc::valid ){
          if ( rnp.first < lBound ){
            for ( auto rns : rnp.second ){
              buffer.clear();
              buffer.str(rns);
              REQUIRE_THROWS( getRealWithLBound( buffer, name, lBound ) );
              buffer.clear();
              buffer.seekg(0);
              REQUIRE_THROWS( getRealWithLBound( buffer, name, lBound, found ) );         
            }
          }
        }
      }
    }
  }
}

SCENARIO( "getRealWithLBound throws for streams"
	  " with invalid real number strings" ){

  const std::string name( "testReal" );
  const double lBound = 0.0;
  std::istringstream buffer;
  bool found;

  GIVEN( "streams with illegal character" ){
    WHEN( "passed to getRealWithLBound" ){
      THEN( "throws" ){
        for ( const std::string& guts : rnsc::invalid ){
	  buffer.clear();
	  buffer.str( guts );
          REQUIRE_THROWS( getRealWithLBound( buffer, name, lBound ) );
	  buffer.clear();
	  buffer.seekg(0);
          REQUIRE_THROWS( getRealWithLBound( buffer, name, lBound, found ) );
        }
      }
    }
  }
}

SCENARIO( "mandatory getRealWithLBound throws for streams with badbit" ){

  const std::string name( "testReal" );
  const double lBound = 0.0;
  GIVEN( "empty stream" ){
    std::istringstream buffer;
    WHEN( "passed to getReal" ){
      THEN( "will throw" ){
	REQUIRE_THROWS( getRealWithLBound( buffer, name, lBound ) );
      }
    }
  }
}

SCENARIO( "optional getRealWithLBound sets found"
	  " flag to false for streams with badbit" ){

  const std::string name( "testReal" );
  bool found = true;
  const double lBound = 0.0;
  GIVEN( "empty stream" ){
    std::istringstream buffer;
    WHEN( "passed to getReal" ){
      THEN( "will set found flag to false" ){
	REQUIRE_NOTHROW( getRealWithLBound( buffer, name, lBound, found ) );
	REQUIRE( not found );
      }
    }
  }
}
