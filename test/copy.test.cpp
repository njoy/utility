#include <string>
#include <vector>

#include "catch.hpp"

#include "utility.hpp"

extern int testNumber;

SCENARIO("copy functions correctly",
	 "[utility]"){
  GIVEN("a string, vector of ints, and a double"){
    std::string referenceString(" 10 20 30 ");
    std::vector<int> referenceVector =  {10, 20, 30};
    double referenceDouble = 1020.30;
    WHEN("passed to the copy function"){
      THEN("the copy returns an independent copy of the object"){
        LOG(INFO) << "Test " << ++testNumber << ":[copy] No Errors Expected";
        auto trialString = utility::copy( referenceString );
        REQUIRE( referenceString == trialString );
        LOG(INFO) << "Test " << ++testNumber << ":[copy] No Errors Expected";
        trialString[0] = 'a';
        REQUIRE( referenceString != trialString );
        LOG(INFO) << "Test " << ++testNumber << ":[copy] No Errors Expected";
        auto trialVector = utility::copy( referenceVector );
        REQUIRE( referenceVector == trialVector );
        LOG(INFO) << "Test " << ++testNumber << ":[copy] No Errors Expected";
        trialVector[0] = 0;
        REQUIRE( referenceVector != trialVector );
        LOG(INFO) << "Test " << ++testNumber << ":[copy] No Errors Expected";
        auto trialDouble = utility::copy( referenceDouble );
	REQUIRE( referenceDouble == trialDouble );
        LOG(INFO) << "Test " << ++testNumber << ":[copy] No Errors Expected";
        trialDouble = 0;
        REQUIRE( referenceDouble != trialDouble );
      }
    }
  }
}
