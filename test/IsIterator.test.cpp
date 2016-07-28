#include <string>
#include <type_traits>

#include "catch.hpp"

#include "utility.hpp"

extern int testNumber;

SCENARIO("IsIterator alias works correctly",
	 "[utility]"){
  bool test;
  LOG(INFO) << "Test " << ++testNumber << ":[IsIterator] No Errors Expected";
  test = utility::IsIterator< std::string >::value;
  REQUIRE( not test );
  LOG(INFO) << "Test " << ++testNumber << ":[IsIterator] No Errors Expected";
  test = utility::IsIterator< std::string::iterator >::value;
  REQUIRE( test );
  LOG(INFO) << "Test " << ++testNumber << ":[IsIterator] No Errors Expected";
  test = utility::IsIterator< std::string* >::value;
  REQUIRE( test );
  LOG(INFO) << "Test " << ++testNumber << ":[IsIterator] No Errors Expected";
  test = utility::IsIterator< int >::value;
  REQUIRE( not test );
}
