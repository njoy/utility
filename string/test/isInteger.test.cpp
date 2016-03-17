#include <vector>

#include "catch.hpp"

#include "utility/string.hpp"

extern int testNumber;

SCENARIO("isInteger will return true for valid integer strings",
	 "[utility],[string]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";
  
  GIVEN("implicitly postive integer string"){
    const std::string integer("123456");
    WHEN("passed to isInteger"){
      THEN("returns true"){
	REQUIRE(true == utility::string::isInteger(integer));
      }
    }
  }

  GIVEN("explicitly postive integer string"){
    const std::string integer("+123456");
    WHEN("passed to isInteger"){
      THEN("returns true"){
	REQUIRE(true == utility::string::isInteger(integer));
      }
    }
  }

  GIVEN("explicitly negative integer string"){
    const std::string integer("-123456");
    WHEN("passed to isInteger"){
      THEN("returns true"){
	REQUIRE(true == utility::string::isInteger(integer));
      }
    }
  }

  GIVEN( "a vector of strings represnting valid integers" ){
    std::vector<std::string> integers{ "123456", "+123456", "-123456" };

    WHEN( "passed to isInteger" ){
      THEN( "returns true" ){
        REQUIRE( utility::string::isInteger( integers.begin(), integers.end()));
        REQUIRE( utility::string::isInteger( integers ) );
      }
    }
  } // GIVEN vector of invalid integers

}

SCENARIO("isInteger will return false for invalid integer strings",
	 "[utility],[string]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  /* Fortran doesn't recognize scientific notation in the context of integer 
   * inputs 
   */
  GIVEN("integer string in enigineers notation"){ 
    const std::string integer("10E6");
    WHEN("passed to isInteger"){
      THEN("returns false"){
	REQUIRE(false == utility::string::isInteger(integer));
      }
    }
  }

  /* Fortran doesn't recognize integer values in decimal notation */
  GIVEN("integer value with trailing zeros"){ 
    const std::string integer("1.0");
    WHEN("passed to isInteger"){
      THEN("returns false"){
	REQUIRE(false == utility::string::isInteger(integer));
      }
    }
  }

  GIVEN("integer value with decimal point"){ 
    const std::string integer("1.");
    WHEN("passed to isInteger"){
      THEN("returns false"){
	REQUIRE(false == utility::string::isInteger(integer));
      }
    }
  }

  /* C and C++ will truncate at the first nonconforming character when reading 
   * numeric values, e.g.
   * 10a -> 10
   * This is undesirable, and should result in failure.
   */
  GIVEN("integer value with decimal point"){ 
    const std::string noninteger("10a");
    WHEN("passed to isInteger"){
      THEN("returns false"){
	REQUIRE(false == utility::string::isInteger(noninteger));
      }
    }
  }

  GIVEN( "a vector of strings represnting invalid integers" ){
    std::vector<std::string> integers{ "10E6", "1.0", "1.", "10a" };

    WHEN( "passed to isInteger" ){
      THEN( "returns true" ){
        REQUIRE( not 
          utility::string::isInteger( integers.begin(), integers.end() ) );
        REQUIRE( not utility::string::isInteger( integers ) );
      }
    }
  } // GIVEN vector of invalid integers

}
