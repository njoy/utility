#include <string>
#include <type_traits>

#include "catch.hpp"

#include "utility.hpp"

extern int testNumber;

SCENARIO("IsSharedPtr alias works correctly",
	 "[utility]"){
  bool test;
  LOG(INFO) << "Test " << ++testNumber << ":[IsSharedPtr] No Errors Expected";
  test = utility::IsSharedPtr< int >::value;
  REQUIRE( not test );
  LOG(INFO) << "Test " << ++testNumber << ":[IsSharedPtr] No Errors Expected";
  test = utility::IsSharedPtr< int* >::value;
  REQUIRE( not test );
  LOG(INFO) << "Test " << ++testNumber << ":[IsSharedPtr] No Errors Expected";
  test = utility::IsSharedPtr< std::shared_ptr<int> >::value;
  REQUIRE( test );
  LOG(INFO) << "Test " << ++testNumber << ":[IsSharedPtr] No Errors Expected";
  test = utility::IsSharedPtr< std::unique_ptr<int> >::value;
  REQUIRE( not test );
}
