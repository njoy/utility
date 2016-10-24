#include <sstream>

#include "catch.hpp"

#include "utility.hpp"
#include "utility/realNumberStringCollection.hpp"

namespace rnsc = utility::realNumberStringCollection;

using namespace utility::stream;

SCENARIO( "getEnergy returns the proper value"
	  " from streams with energy strings" ){

  const std::string name( "testEnergy" );
  bool found;
  std::istringstream buffer;
  double residual;

  GIVEN( "streams with postive value energy string" ){
    WHEN( "passed to getEnergy" ){
      THEN( "returns the correct energy" ){
        for ( auto rnp : rnsc::valid ){
          if ( rnp.first >= 0 ){
            for ( auto rns : rnp.second ){
              buffer.clear();
              buffer.str(rns);
              residual = std::abs( rnp.first - getEnergy( buffer, name ) );
              REQUIRE(residual < 0.000001);
              buffer.clear();
              buffer.seekg(0);
              found = false;
              residual = std::abs( rnp.first - getEnergy( buffer,found, name ) );          
              REQUIRE( residual < 0.000001 );
              REQUIRE( true == found );
            }
          }
        }
      }
    }
  }
}

SCENARIO( "getEnergy throws for streams with invalid energy strings" ){

  const std::string name("testEnergy");
  std::istringstream buffer;
  bool found;

  GIVEN( "streams with negative real number" ){
    WHEN( "passed to getEnergy" ){
      THEN( "throws" ){
        for ( auto rnp : rnsc::valid ){
          if ( rnp.first < 0 ){
            for ( auto rns : rnp.second ){
              buffer.clear();
              buffer.str( rns );
              REQUIRE_THROWS( getEnergy(buffer, name) );
              buffer.clear();
              buffer.seekg(0);
              REQUIRE_THROWS( getEnergy(buffer, found, name ) );
            }
          }
        }
      }
    }
  }

  GIVEN( "streams with illegal character" ){
    WHEN( "passed to getEnergy" ){
      THEN( "throws" ){
        for ( const std::string& guts : rnsc::invalid ){
	  buffer.clear();
	  buffer.str(guts);
          REQUIRE_THROWS( getEnergy( buffer, name ) );
	  buffer.clear();
	  buffer.seekg(0);
          REQUIRE_THROWS( getEnergy( buffer, found, name ) );
        }
      }
    }
  }
}

SCENARIO( "mandatory getEnergy throws for streams with badbit" ){
  const std::string name( "testEnergy" );
  GIVEN( "empty stream" ){
    std::istringstream buffer;
    WHEN( "passed to getEnergy" ){
      THEN( "will throw" ){
	REQUIRE_THROWS( getEnergy( buffer, name ) );
      }
    }
  }
}

SCENARIO( "optional getEnergy sets found flag to"
	  " false for streams with badbit" ){
  const std::string name("testEnergy");
  bool found = true;
  GIVEN( "empty stream" ){
    std::istringstream buffer;
    WHEN( "passed to getEnergy" ){
      THEN( "will set found flag to false" ){
	REQUIRE_NOTHROW( getEnergy( buffer, found, name ) );
	REQUIRE( found == false );
      }
    }
  }
}
