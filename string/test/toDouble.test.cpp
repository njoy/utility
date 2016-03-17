#include <vector>
#include <sstream>

#include "catch.hpp"

#include "utility/realNumberStringCollection.hpp"
#include "utility/string.hpp"

namespace rnsc = utility::realNumberStringCollection;

extern int testNumber;

SCENARIO("toDouble returns the correct value form valid real number strings",
         "[utility],[string]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";
  double residual;
  GIVEN("a collection of real number strings"){
    WHEN("passed to toDouble"){
      THEN("returns the correct value"){
        for (auto rnp : rnsc::valid){
          for (auto rns : rnp.second){
            residual = rnp.first - utility::string::toDouble(rns);
            REQUIRE(residual < 0.00001);
          }
        }
      }
    }
  }
}

