#include <string>
#include <type_traits>

#include "catch.hpp"

#include "utility.hpp"

extern int testNumber;

SCENARIO("clean alias works correctly",
	 "[utility]"){
  bool test;
  test = std::is_same< int, utility::clean< int > >::value;
  REQUIRE( test );
  test = std::is_same< int, utility::clean< const int > >::value;
  REQUIRE( test );
  test = std::is_same< int, utility::clean< int& > >::value;
  REQUIRE( test );
  test = std::is_same< int, utility::clean< const int& > >::value;
  REQUIRE( test );
}
