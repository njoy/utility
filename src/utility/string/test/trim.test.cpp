#include <vector>
#include <sstream>

#include "catch.hpp"

#include "utility.hpp"

using namespace utility::string;

SCENARIO( "the trim function works correctly" ){
  std::vector< std::string > noEmbedded =
    {"   trim", "trim   ", "   trim   ",  "trim"};
  std::vector< std::string > embedded =
    {" trim trim ", "trim trim", "  trim trim", "trim trim   "};
  GIVEN( "a collection of strings to be trimmed" ){
    WHEN( "passed to the trim function" ){
      THEN( "returns only leading and trailing whitespace will be removed" ){
        for ( auto& untrimmedString : noEmbedded ){
          REQUIRE( "trim" == trim( untrimmedString ) );
        }
        for ( auto& untrimmedString : embedded ){
          REQUIRE( "trim trim" == trim( untrimmedString ) );
        }
      }
    }
  }
}
