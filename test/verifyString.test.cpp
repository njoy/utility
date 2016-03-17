/* external project */
#include "catch.hpp"
#include "easylogging++.h"
/* local header */
#include "utility.hpp"

extern int testNumber;

SCENARIO("verifyString evaluates to true when passed a quote delimited string with a number of characters fewer then or equal to the length argument",
	 "[utility]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  GIVEN("a double quote delimited string with fewer characters than the length argument"){
    const std::string validString("\"this is a valid string\"");
    WHEN("passed to verifyString"){
      THEN("returns true"){
	REQUIRE( true == utility::verifyString(validString, 23) );
      }
    }
  }

  GIVEN("a double quote delimited string length argument number of characters"){
    const std::string validString("\"this is a valid string\"");
    WHEN("passed to verifyString"){
      THEN("returns true"){
	REQUIRE( true == utility::verifyString(validString, 22) );
      }
    }
  }

  GIVEN("a single quote delimited string with fewer characters than the length argument"){
    const std::string validString("\'this is a valid string\'");
    WHEN("passed to verifyString"){
      THEN("returns true"){
	REQUIRE( true == utility::verifyString(validString, 23) );
      }
    }
  }

  GIVEN("a single quote delimited string length argument number of characters"){
    const std::string validString("\'this is a valid string\'");
    WHEN("passed to verifyString"){
      THEN("returns true"){
	REQUIRE( true == utility::verifyString(validString, 22) );
      }
    }
  }

}

SCENARIO("verifyString will distinguish between quote types",
	 "[utility]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  GIVEN("a double quote delimited string with a single quote character embedded"){
    const std::string validString("\"this is a \'valid string\"");
    WHEN("passed to verifyString"){
      THEN("returns true"){
	REQUIRE( true == utility::verifyString(validString, 99) );
      }
    }
  }

  GIVEN("a double quote delimited string with two single quote character embedded"){
    const std::string validString("\"this is a \'valid\' string\"");
    WHEN("passed to verifyString"){
      THEN("returns true"){
	REQUIRE( true == utility::verifyString(validString, 99) );
      }
    }
  }

  GIVEN("a single quote delimited string with a double quote character embedded"){
    const std::string validString("\'this is a \"valid string\'");
    WHEN("passed to verifyString"){
      THEN("returns true"){
	REQUIRE( true == utility::verifyString(validString, 99) );
      }
    }
  }

  GIVEN("a single quote delimited string with two double quote character embedded"){
    const std::string validString("\'this is a \"valid\" string\'");
    WHEN("passed to verifyString"){
      THEN("returns true"){
	REQUIRE( true == utility::verifyString(validString, 99) );
      }
    }
  }

}

SCENARIO("verifyString will return true for empty strings",
	 "[utility]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";
  GIVEN("an empty string"){
    const std::string validString("\'\'");
    WHEN("passed to verifyString"){
      THEN("returns true"){
	REQUIRE( true == utility::verifyString(validString, 99) );
      }
    }
  }
}

SCENARIO("verifyString will return false for invalid strings",
	 "[utility]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  GIVEN("a string without quote delimiters"){
    const std::string invalidString("hello world");
    WHEN("passed to verifyString"){
      THEN("returns false"){
	REQUIRE( false == utility::verifyString(invalidString, 99) );
      }
    }
  }

  GIVEN("a string with only one string delimiter"){
    const std::string invalidString("\"hello world");
    WHEN("passed to verifyString"){
      THEN("returns false"){
	REQUIRE( false == utility::verifyString(invalidString, 99) );
      }
    }
  }

  GIVEN("a string with too many characters"){
    const std::string invalidString("\"13 characters\"");
    WHEN("passed to verifyString"){
      THEN("returns false"){
	REQUIRE( false == utility::verifyString(invalidString, 12) );
      }
    }
  }

}
