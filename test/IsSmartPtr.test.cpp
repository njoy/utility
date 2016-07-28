#include <string>
#include <type_traits>

#include "catch.hpp"

#include "utility.hpp"

extern int testNumber;

SCENARIO("IsSmartPtr alias works correctly",
	 "[utility]"){
  bool test;
  LOG(INFO) << "Test " << ++testNumber << ":[IsSmartPtr] No Errors Expected";
  test = utility::IsSmartPtr< int >::value;
  REQUIRE( not test );
  LOG(INFO) << "Test " << ++testNumber << ":[IsSmartPtr] No Errors Expected";
  test = utility::IsSmartPtr< int* >::value;
  REQUIRE( not test );
  LOG(INFO) << "Test " << ++testNumber << ":[IsSmartPtr] No Errors Expected";
  test = utility::IsSmartPtr< std::shared_ptr<int> >::value;
  REQUIRE( test );
  LOG(INFO) << "Test " << ++testNumber << ":[IsSmartPtr] No Errors Expected";
  test = utility::IsSmartPtr< std::unique_ptr<int> >::value;
  REQUIRE( test );
}
