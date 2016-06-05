#define CATCH_CONFIG_RUNNER

#include <type_traits>

#include "catch.hpp"

#include "utility/TypeSwitch.hpp"

int testNumber = 0;

int main( int argc, const char* argv[] )
{
  LOG(INFO) << "";
  LOG(INFO) << " TypeSwitch Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "TypeSwitch Tests Complete!";
  return result;
}

SCENARIO("the TypeSwitch class evaluates the type correctly",
	 "[utility], [TypeSwitch]"){
  GIVEN( "a pair of typenames" ){
    WHEN( "chosen based on a compile-time conditional" ){
      THEN( "the TypeSwitch type alias refers to the correct typename" ){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [TypeSwitch] No Errors Expected";
        auto is_same = std::is_same
                       < int,
                         utility::TypeSwitch< int, void,
                                              ( 1 == 1 ) >::type >::value;
        REQUIRE( true == is_same );

        LOG(INFO) << "Test " << ++testNumber
                  << ": [TypeSwitch] No Errors Expected";
        auto is_not_same =
          not std::is_same
              < int, utility::TypeSwitch< int, void,
                                          ( 1 == 0 ) >::type >::value;

        REQUIRE( true == is_not_same );

        LOG(INFO) << "Test " << ++testNumber
                  << ": [TypeSwitch] No Errors Expected";
        is_same = std::is_same
                  < void, utility::TypeSwitch< int, void,
                                               ( 1 == 0 ) >::type >::value;
        REQUIRE( true == is_same );


        LOG(INFO) << "Test " << ++testNumber
                  << ": [TypeSwitch] No Errors Expected";is_not_same =
          not std::is_same
              < void, utility::TypeSwitch< int, void,
                                          ( 1 == 1 ) >::type >::value;

        REQUIRE( true == is_not_same );

      }
    }
  }
}
