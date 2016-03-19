#include <sstream>

#include "catch.hpp"

#include "utility/stream.hpp"
#include "utility/realNumberStringCollection.hpp"

namespace rnsc = utility::realNumberStringCollection;

extern int testNumber;

SCENARIO("getRealNumber returns the proper value from streams with valid real number strings",
         "[utility],[stream]"){

  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  const std::string name("testReal");
  bool found;
  std::istringstream buffer;
  double residual;
  double referenceReal;

  GIVEN("streams with valid real number strings"){
    WHEN("passed to getRealNumber"){
      THEN("returns the correct real value"){
        for ( auto rnp : rnsc::valid ){
          for (auto rns : rnp.second ){
            buffer.clear();
            buffer.str(rns);
            residual = std::abs(rnp.first - utility::stream::getRealNumber(buffer, name));
            REQUIRE(residual < 0.000001);
            buffer.clear();
            buffer.seekg(0);
            found = false;
            residual = std::abs(rnp.first - utility::stream::getRealNumber(buffer, name, found));
            REQUIRE(residual < 0.000001);
            REQUIRE(true == found);
          }
        }
      }
    }
  }
}

SCENARIO("getRealNumber throws for streams with invalid real number strings",
         "[utility],[stream]"){

  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";

  const std::string name("testReal");
  std::istringstream buffer;
  bool found;

  GIVEN("streams with illegal character"){
    WHEN("passed to getRealNumber"){
      THEN("throws"){
        for ( const std::string& guts : rnsc::invalid ){
	  buffer.clear();
	  buffer.str(guts);
          REQUIRE_THROWS(utility::stream::getRealNumber(buffer, name));
	  buffer.clear();
	  buffer.seekg(0);
          REQUIRE_THROWS(utility::stream::getRealNumber(buffer, name, found));
        }
      }
    }
  }
}

SCENARIO("mandatory getRealNumber throws for streams with badbit",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";

  const std::string name("testReal");
  GIVEN("empty stream"){
    std::istringstream buffer;
    WHEN("passed to getReal"){
      THEN("will throw"){
	REQUIRE_THROWS(utility::stream::getRealNumber(buffer, name));
      }
    }
  }
}

SCENARIO("optional getRealNumber sets found flag to false for streams with badbit",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  const std::string name("testReal");
  bool found = true;
  GIVEN("empty stream"){
    std::istringstream buffer;
    WHEN("passed to getReal"){
      THEN("will set found flag to false"){
	REQUIRE_NOTHROW(utility::stream::getRealNumber(buffer, name, found));
	REQUIRE(found == false);
      }
    }
  }
}
