#include <vector>
#include <sstream>

#include "catch.hpp"

#include "utility.hpp"
#include "utility/realNumberStringCollection.hpp"

namespace rnsc = njoy::utility::realNumberStringCollection;

using namespace njoy::utility::string;

SCENARIO( "toDouble returns the correct value form valid real number strings" ){
  double residual;
  GIVEN("a collection of real number strings"){
    WHEN("passed to toDouble"){
      THEN("returns the correct value"){
        for ( auto rnp : rnsc::valid ){
          for ( auto rns : rnp.second ){
            residual = rnp.first - toDouble(rns);
            REQUIRE( residual < 0.00001 );
          }
        }
      }
    }
  }
}

