#include <string>
#include <type_traits>

#include "catch.hpp"

#include "utility.hpp"

extern int testNumber;

SCENARIO("IsContainer alias works correctly",
	 "[utility]"){
  bool test;
  test = utility::IsContainer< std::string >::value;
  REQUIRE( test );
  test = utility::IsContainer< std::string::iterator >::value;
  REQUIRE( not test );
  test = utility::IsContainer< int >::value;
  REQUIRE( not test );
}
