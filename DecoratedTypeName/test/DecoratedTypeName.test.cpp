#define CATCH_CONFIG_RUNNER

#include <type_traits>

#include "catch.hpp"

#include "utility/DecoratedTypeName.hpp"

int testNumber = 0;

int main( int argc, const char* argv[] )
{
  LOG(INFO) << "";
  LOG(INFO) << " DecoratedTypeName Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "DecoratedTypeName Tests Complete!";
  return result;
}

template< typename base >
struct decoratorA{};

template< typename base >
struct decoratorB{};

template< typename base >
struct decoratorC{};


SCENARIO("the DecoratedTypeName class evaluates the type correctly",
	 "[utility], [DecoratedTypeName]"){
  GIVEN( "a series of templates" ){
    WHEN( "applied to an int" ){
      THEN( "the DecoratedTypeName value correctly predicts the type generated"
            " by the compiler" ){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [DecoratedTypeName] No Errors Expected";
        auto is_same = std::is_same
                       < decoratorA<int>,
                         utility::DecoratedTypeName
                         < int, decoratorA >::value >::value;
        REQUIRE( true == is_same );

        LOG(INFO) << "Test " << ++testNumber
                  << ": [DecoratedTypeName] No Errors Expected";
        is_same = std::is_same
                  < decoratorA< decoratorB< int > >,
                    utility::DecoratedTypeName
                    < int, decoratorA, decoratorB >::value >::value;
        REQUIRE( true == is_same );

                LOG(INFO) << "Test " << ++testNumber
                  << ": [DecoratedTypeName] No Errors Expected";
        is_same = std::is_same
                  < decoratorA< decoratorB< decoratorC< int > > >,
                    utility::DecoratedTypeName
                    < int, decoratorA, decoratorB, decoratorC >::value >::value;
        REQUIRE( true == is_same );
      }
    }
  }
}
