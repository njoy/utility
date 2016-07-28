#include <string>
#include <type_traits>

#include "catch.hpp"

#include "utility.hpp"

extern int testNumber;

SCENARIO("IsUniquePtr alias works correctly",
	 "[utility]"){
  bool test;
  LOG(INFO) << "Test " << ++testNumber << ":[IsUniquePtr] No Errors Expected";
  test = utility::IsUniquePtr< int >::value;
  REQUIRE( not test );
  LOG(INFO) << "Test " << ++testNumber << ":[IsUniquePtr] No Errors Expected";
  test = utility::IsUniquePtr< int* >::value;
  REQUIRE( not test );
  LOG(INFO) << "Test " << ++testNumber << ":[IsUniquePtr] No Errors Expected";
  test = utility::IsUniquePtr< std::shared_ptr<int> >::value;
  REQUIRE( not test );
  LOG(INFO) << "Test " << ++testNumber << ":[IsUniquePtr] No Errors Expected";
  test = utility::IsUniquePtr< std::unique_ptr<int> >::value;
  REQUIRE( test );
}
