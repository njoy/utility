#include <sstream>

#include "catch.hpp"

#include "utility/stream.hpp"
#include "utility/realNumberStringCollection.hpp"

namespace rnsc = utility::realNumberStringCollection;

extern int testNumber;

SCENARIO("getEnergy returns the proper value from streams with energy strings",
         "[utility],[stream]"){

  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  const std::string name("testEnergy");
  bool found;
  std::istringstream buffer;
  double residual;

  GIVEN("streams with postive value energy string"){
    WHEN("passed to getEnergy"){
      THEN("returns the correct energy"){
        for ( auto rnp : rnsc::valid ){
          if (rnp.first >= 0){
            for (auto rns : rnp.second){
              buffer.clear();
              buffer.str(rns);
              residual = std::abs(rnp.first - utility::stream::getEnergy(buffer, name));
              REQUIRE(residual < 0.000001);
              buffer.clear();
              buffer.seekg(0);
              found = false;
              residual = std::abs(rnp.first - utility::stream::getEnergy(buffer,found, name));          
              REQUIRE(residual < 0.000001);
              REQUIRE(true == found);
            }
          }
        }
      }
    }
  }
}

SCENARIO("getEnergy throws for streams with invalid energy strings",
         "[utility],[stream]"){

  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";

  const std::string name("testEnergy");
  std::istringstream buffer;
  bool found;

  GIVEN("streams with negative real number"){
    WHEN("passed to getEnergy"){
      THEN("throws"){
        for ( auto rnp : rnsc::valid ){
          if (rnp.first < 0){
            for (auto rns : rnp.second){
              buffer.clear();
              buffer.str(rns);
              REQUIRE_THROWS(utility::stream::getEnergy(buffer, name));
              buffer.clear();
              buffer.seekg(0);
              REQUIRE_THROWS(utility::stream::getEnergy(buffer, found, name));
            }
          }
        }
      }
    }
  }

  GIVEN("streams with illegal character"){
    WHEN("passed to getEnergy"){
      THEN("throws"){
        for ( const std::string& guts : rnsc::invalid ){
	  buffer.clear();
	  buffer.str(guts);
          REQUIRE_THROWS(utility::stream::getEnergy(buffer, name));
	  buffer.clear();
	  buffer.seekg(0);
          REQUIRE_THROWS(utility::stream::getEnergy(buffer, found, name));
        }
      }
    }
  }

}

SCENARIO("mandatory getEnergy throws for streams with badbit",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";

  const std::string name("testEnergy");
  GIVEN("empty stream"){
    std::istringstream buffer;
    WHEN("passed to getEnergy"){
      THEN("will throw"){
	REQUIRE_THROWS(utility::stream::getEnergy(buffer, name));
      }
    }
  }
}

SCENARIO("optional getEnergy sets found flag to false for streams with badbit",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  const std::string name("testEnergy");
  bool found = true;
  GIVEN("empty stream"){
    std::istringstream buffer;
    WHEN("passed to getEnergy"){
      THEN("will set found flag to false"){
	REQUIRE_NOTHROW(utility::stream::getEnergy(buffer, found, name));
	REQUIRE(found == false);
      }
    }
  }
}
