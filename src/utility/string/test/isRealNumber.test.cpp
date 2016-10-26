#include "catch.hpp"

#include "utility.hpp"
#include "utility/realNumberStringCollection.hpp"

namespace rnsc = njoy::utility::realNumberStringCollection;

using namespace njoy::utility::string;

SCENARIO( "isRealNumber will return true for valid real number strings" ){
  GIVEN( "a collection of valid real number strings" ){
    WHEN( "each element is passed to isRealNumber" ){
      THEN( "returns true" ){
        for ( auto rnp : rnsc::valid ){
          for ( auto rns : rnp.second ){
            REQUIRE( isRealNumber(rns) );
          }
        }
      }
    }
    WHEN( "the collection is passed to isRealNumber" ){
      THEN( "returns true" ){
        for( auto rnp : rnsc::valid ){
          std::vector< std::string > second = rnp.second;
          REQUIRE( isRealNumber( second.begin(), second.end() ) );
          REQUIRE( isRealNumber( second ) );
        }
      }
    }
  } // GIVEN
} // SCENARIO

SCENARIO( "isRealNumber will return false for invalid real number strings" ){
  GIVEN( "a collection of invalid real number strings" ){
    WHEN( "each element is passed to isRealNumber" ){
      THEN( "returns false" ){
        for ( const std::string& s : rnsc::invalid ){
          REQUIRE( not njoy::utility::string::isRealNumber(s) );
        }
      }
    }
    WHEN( "the collection is passed to isRealNumber" ){
      THEN( "returns true" ){
        std::vector< std::string > invalid = rnsc::invalid;
        REQUIRE( not isRealNumber( invalid.begin(), invalid.end() ) );
        REQUIRE( not isRealNumber( invalid ) );
      }
    }
  } // GIVEN
} // SCENARIO
