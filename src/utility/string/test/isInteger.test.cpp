#include <vector>

#include "catch.hpp"

#include "utility.hpp"

using namespace utility::string;

SCENARIO( "isInteger will return true for valid integer strings" ){
  GIVEN( "implicitly postive integer string" ){
    const std::string integer( "123456" );
    WHEN( "passed to isInteger" ){
      THEN( "returns true" ){
	REQUIRE( isInteger(integer) );
      }
    }
  }

  GIVEN( "explicitly postive integer string" ){
    const std::string integer( "+123456" );
    WHEN( "passed to isInteger" ){
      THEN( "returns true" ){
	REQUIRE( isInteger(integer) );
      }
    }
  }

  GIVEN( "explicitly negative integer string" ){
    const std::string integer( "-123456" );
    WHEN( "passed to isInteger" ){
      THEN( "returns true" ){
	REQUIRE( isInteger(integer) );
      }
    }
  }

  GIVEN( "a vector of strings represnting valid integers" ){
    std::vector< std::string > integers{ "123456", "+123456", "-123456" };

    WHEN( "passed to isInteger" ){
      THEN( "returns true" ){
        REQUIRE( isInteger( integers.begin(), integers.end() ) );
        REQUIRE( isInteger( integers ) );
      }
    }
  } // GIVEN vector of invalid integers

}

SCENARIO( "isInteger will return false for invalid integer strings" ){
  /* Fortran doesn't recognize scientific notation in the context of integer 
   * inputs 
   */
  GIVEN( "integer string in enigineers notation" ){ 
    const std::string integer( "10E6" );
    WHEN( "passed to isInteger" ){
      THEN( "returns false" ){
	REQUIRE( not isInteger(integer) );
      }
    }
  }

  /* Fortran doesn't recognize integer values in decimal notation */
  GIVEN( "integer value with trailing zeros" ){ 
    const std::string integer( "1.0" );
    WHEN( "passed to isInteger" ){
      THEN( "returns false" ){
	REQUIRE( not utility::string::isInteger(integer) );
      }
    }
  }

  GIVEN( "integer value with decimal point" ){ 
    const std::string integer( "1." );
    WHEN( "passed to isInteger" ){
      THEN( "returns false" ){
	REQUIRE( not isInteger(integer) );
      }
    }
  }

  /* C and C++ will truncate at the first nonconforming character when reading 
   * numeric values, e.g.
   * 10a -> 10
   * This is undesirable, and should result in failure.
   */
  GIVEN( "integer value with decimal point" ){ 
    const std::string noninteger( "10a" );
    WHEN( "passed to isInteger" ){
      THEN( "returns false" ){
	REQUIRE( not isInteger(noninteger) );
      }
    }
  }

  GIVEN( "a vector of strings represnting invalid integers" ){
    std::vector< std::string > integers{ "10E6", "1.0", "1.", "10a" };

    WHEN( "passed to isInteger" ){
      THEN( "returns true" ){
        REQUIRE( not isInteger( integers.begin(), integers.end() ) );
        REQUIRE( not isInteger( integers ) );
      }
    }
  } // GIVEN vector of invalid integers

}
