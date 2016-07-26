#include "catch.hpp"

#include "utility.hpp"

extern int testNumber;

SCENARIO("echoErroneousLine functions correctly",
	 "[utility]"){
  GIVEN("a string with an error"){
    std::string referenceString1("this is an integer: 123a5");
    WHEN("there is no newline present"){
      LOG(INFO) << "Test " << ++testNumber
                << ":[echoErroneousLine] Errors Expected";
      auto begin = referenceString1.begin();
      auto it = std::next( begin, 23 );
      auto end = referenceString1.end();
      auto lineNumber = 10l;

      utility::echoErroneousLine( begin, it, end, lineNumber );
    }
    std::string referenceString2 = referenceString1 + "\n this shouldn't print";
    WHEN("there is a newline present"){
      LOG(INFO) << "Test " << ++testNumber
                << ":[echoErroneousLine] Errors Expected";
      auto begin = referenceString2.begin();
      auto it = std::next( begin, 23 );
      auto end = referenceString2.end();
      auto lineNumber = 10l;

      utility::echoErroneousLine( begin, it, end, lineNumber ); 
    }
  }
}
