#include "catch.hpp"

#include "header-utilities.hpp"

std::stringstream ss;

SCENARIO("echoErroneousLine"){
  Log::add_sink(ss);
  std::string buffer("the error is here -> \n pretty cool huh?");
  auto begin = buffer.begin();
  auto it = std::next( begin, 20 );
  auto end = buffer.end();
  auto lineNumber = 10l;

  utility::echoErroneousLine( begin, it, end, lineNumber );

  std::string referenceMessage =
    "Error while parsing line 10\n"
    "\n"
    "the error is here -> \n"
    "~~~~~~~~~~~~~~~~~~~~^\n";

  REQUIRE( referenceMessage == ss.str() );
}
