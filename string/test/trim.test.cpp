#include <vector>
#include <sstream>

#include "catch.hpp"

#include "utility/string.hpp"

extern int testNumber;

SCENARIO("the trim function works correctly",
         "[utility],[string],[trim]"){
  std::vector<std::string> noEmbedded =
    {"   trim", "trim   ", "   trim   ",  "trim"};
  std::vector<std::string> embedded =
    {" trim trim ", "trim trim", "  trim trim", "trim trim   "};
  GIVEN("a collection of strings to be trimmed"){
    WHEN("passed to the trim function"){
      THEN("returns only leading and trailing whitespace will be removed"){
        LOG(INFO) << "Test " << ++testNumber << ":[trim] No Errors Expected";
        for ( auto& untrimmedString : noEmbedded ){
          REQUIRE( "trim" == utility::string::trim( untrimmedString ) );
        }
        LOG(INFO) << "Test " << ++testNumber << ":[trim] No Errors Expected";
        for ( auto& untrimmedString : embedded ){
          REQUIRE( "trim trim" == utility::string::trim( untrimmedString ) );
        }
      }
    }
  }
}

