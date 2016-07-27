#include <string>
#include <type_traits>

#include "catch.hpp"

#include "utility.hpp"

extern int testNumber;

SCENARIO("IsIterator alias works correctly",
	 "[utility]"){
  bool test;
  test = utility::IsIterator< std::string >::value;
  REQUIRE( not test );
  test = utility::IsIterator< std::string::iterator >::value;
  REQUIRE( test );
  test = utility::IsIterator< std::string* >::value;
  REQUIRE( test );
  test = utility::IsIterator< int >::value;
  REQUIRE( not test );
}
