#include "catch.hpp"

#include "utility/realNumberStringCollection.hpp"
#include "utility/string.hpp"

namespace rnsc = utility::realNumberStringCollection;

extern int testNumber;

SCENARIO("isRealNumber will return true for valid real number strings",
	 "[utility],[string]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";
  GIVEN("a collection of valid real number strings"){
    WHEN("each elemt is passed to isRealNumber"){
      THEN("returns true"){
        for (auto rnp : rnsc::valid){
          for (auto rns : rnp.second){
            REQUIRE(true == utility::string::isRealNumber(rns));
          }
        }
      }
    }
    WHEN( "the collection is passed to isRealNumber" ){
      THEN( "returns true" ){
        for( auto rnp : rnsc::valid ){
          std::vector<std::string> second = rnp.second;
          REQUIRE( utility::string::isRealNumber(second.begin(), second.end()));
          REQUIRE( utility::string::isRealNumber(second));
        }
      }
    }
  } // GIVEN
} // SCENARIO

SCENARIO("isRealNumber will return false for invalid real number strings",
	 "[utility],[string]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";
  GIVEN("a collection of invalid real number strings"){
    WHEN("each element is passed to isRealNumber"){
      THEN("returns false"){
        for ( const std::string& s : rnsc::invalid ){
          REQUIRE(false == utility::string::isRealNumber(s));
        }
      }
    }
    WHEN( "the collection is passed to isRealNumber" ){
      THEN( "returns true" ){
        std::vector<std::string> invalid = rnsc::invalid;
        REQUIRE( not utility::string::isRealNumber(
                invalid.begin(), invalid.end()) );
        REQUIRE( not utility::string::isRealNumber( invalid ) );
      }
    }
  } // GIVEN
} // SCENARIO
