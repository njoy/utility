#include <sstream>

#include "catch.hpp"

#include "utility/stream.hpp"
#include "utility/realNumberStringCollection.hpp"

namespace rnsc = utility::realNumberStringCollection;

extern int testNumber;

SCENARIO("getTemperature returns the proper value from streams with energy strings",
         "[utility],[stream]"){

  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  const std::string name("testTemperature");
  bool found;
  std::istringstream buffer;

  GIVEN("streams with postive value temperature string"){
    WHEN("passed to getTemperature with a name argument"){
      THEN("returns the correct temperature"){
	double residual;
        for ( auto rnp : rnsc::valid){
          if (!(rnp.first < 0)){
            for ( auto rns : rnp.second){
              buffer.clear();
              buffer.str(rns);
              residual = std::abs(rnp.first - utility::stream::getTemperature(buffer, name));
              REQUIRE(residual < 0.000001);
              buffer.clear();
              buffer.seekg(0);
              found = false;
              residual = std::abs(rnp.first - utility::stream::getTemperature(buffer,found, name));          
              REQUIRE(residual < 0.000001);
              REQUIRE(true == found);
            }
          }
        }
      }
    }

    WHEN("passed to getTemperature without a name argument"){
      THEN("returns the correct temperature"){
	double residual;
        for ( auto rnp : rnsc::valid){
          if (!(rnp.first < 0)){
            for ( auto rns : rnp.second){
              buffer.clear();
              buffer.str(rns);
              residual = std::abs(rnp.first - utility::stream::getTemperature(buffer));
              REQUIRE(residual < 0.000001);
              buffer.clear();
              buffer.seekg(0);
              found = false;
              residual = std::abs(rnp.first - utility::stream::getTemperature(buffer, found));          
              REQUIRE(residual < 0.000001);
              REQUIRE(true == found);
            }
          }
        }
      }
    }
  }
}

SCENARIO("getTemperature throws for streams with invalid temperature strings",
         "[utility],[stream]"){

  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";

  const std::string name("testTemperature");
  std::istringstream buffer;
  bool found;

  GIVEN("streams with negative real number"){

    WHEN("passed to getTemperature with a name argument"){
      THEN("throws"){
        for ( auto rnp : rnsc::valid){
          if (rnp.first < 0){
            for ( auto rns : rnp.second){
              buffer.clear();
              buffer.str(rns);
              REQUIRE_THROWS(utility::stream::getTemperature(buffer, name));
              buffer.clear();
              buffer.seekg(0);
              REQUIRE_THROWS(utility::stream::getTemperature(buffer, found, name));
            }
          }
        }
      }
    }

    WHEN("passed to getTemperature without name argument"){
      THEN("throws"){
        for ( auto rnp : rnsc::valid){
          if (rnp.first < 0){
            for ( auto rns : rnp.second){
              buffer.clear();
              buffer.str(rns);
              REQUIRE_THROWS(utility::stream::getTemperature(buffer));
              buffer.clear();
              buffer.seekg(0);
              REQUIRE_THROWS(utility::stream::getTemperature(buffer, found));
            }
          }
        }
      }
    }
  }

  GIVEN("streams with illegal character"){
    WHEN("passed to getTemperature with a name argument"){
      THEN("throws"){
        for ( const std::string& guts : rnsc::invalid ){
	  buffer.clear();
	  buffer.str(guts);
          REQUIRE_THROWS(utility::stream::getTemperature(buffer, name));
	  buffer.clear();
	  buffer.seekg(0);
          REQUIRE_THROWS(utility::stream::getTemperature(buffer, found, name));
        }
      }
    }

    WHEN("passed to getTemperature without a name argument"){
      THEN("throws"){
        for ( const std::string& guts : rnsc::invalid ){
	  buffer.clear();
	  buffer.str(guts);
          REQUIRE_THROWS(utility::stream::getTemperature(buffer));
	  buffer.clear();
	  buffer.seekg(0);
          REQUIRE_THROWS(utility::stream::getTemperature(buffer, found));
        }
      }
    }

  }

}

SCENARIO("mandatory getTemperature throws for streams with badbit",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";

  const std::string name("testTemperature");
  GIVEN("empty stream"){
    std::istringstream buffer;

    WHEN("passed to getTemperature with a name argument"){
      THEN("will throw"){
	REQUIRE_THROWS(utility::stream::getTemperature(buffer, name));
      }
    }

    WHEN("passed to getTemperature without a name argument"){
      THEN("will throw"){
	REQUIRE_THROWS(utility::stream::getTemperature(buffer));
      }
    }

  }
}

SCENARIO("optional getTemperature sets found flag to false for streams with badbit",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  const std::string name("testTemperature");
  bool found = true;
  GIVEN("empty stream"){
    std::istringstream buffer;

    WHEN("passed to getTemperature with name argument"){
      THEN("will set found flag to false"){
	REQUIRE_NOTHROW(utility::stream::getTemperature(buffer, found, name));
	REQUIRE(found == false);
      }
    }

    WHEN("passed to getTemperature without name argument"){
      THEN("will set found flag to false"){
	REQUIRE_NOTHROW(utility::stream::getTemperature(buffer, found));
	REQUIRE(found == false);
      }
    }

  }
}
