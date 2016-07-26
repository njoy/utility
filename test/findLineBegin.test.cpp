#include "catch.hpp"

#include "utility.hpp"

extern int testNumber;

SCENARIO("findLineBegin functions correctly",
	 "[utility]"){
  GIVEN("a string with an multiple lines"){
    LOG(INFO) << "Test " << ++testNumber
              << ":[findLineBegin] No Errors Expected";
    std::string solution = "hello world";
    auto str = std::string("012345\n") + solution;
    auto positionIterator = std::next( str.begin(), 10 );
   
    std::string trial
      ( utility::findLineBegin( positionIterator ), str.end() );
    REQUIRE(solution == trial);
  }
}
