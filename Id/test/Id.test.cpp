#define CATCH_CONFIG_RUNNER

// other includes
#include "catch.hpp"

// what we're testing
#include "utility/Id.hpp"

int testNumber = 0;

namespace {

  // test variable
  std::string str("myId");
  std::string validstr("validId");

  // dummy test class and validation function
  class Dummy {};
}

// override validateId function for the Dummy class
namespace utility {

  template <> bool validateId<Dummy>(const std::string& id) noexcept {

    if (id != validstr) {

      return false;
    }
    return true;
  }
}

int main( int argc, const char* argv[] )
{
  LOG(INFO) << "";
  LOG(INFO) << " Id Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "Id Tests Complete!";
  return result;
}

SCENARIO("Id construction ", "[utility], [Id]"){

  GIVEN("an identifier string"){

    WHEN("constructing a valid string Id with the default validateString") {

      THEN("the constructor should not throw") {

        LOG(INFO) << "Test " << ++testNumber 
                  << ": [construction] No Errors Expected";
        REQUIRE_NOTHROW( utility::Id<double> id(str) );
      }
    }

    WHEN("constructing a valid string Id with an override validateString") {

      THEN("the constructor should not throw with a valid string") {

        LOG(INFO) << "Test " << ++testNumber 
                  << ": [construction] No Errors Expected";
        REQUIRE_NOTHROW( utility::Id<Dummy> id(validstr) );
      }
    }

    WHEN("constructing a valid string Id with an override validateString") {

      THEN("the constructor should throw with a invalid string") {

        LOG(INFO) << "Test " << ++testNumber 
                  << ": [construction] No Errors Expected";
        REQUIRE_THROWS( utility::Id<Dummy> id("myId") );
      }
    }
  }

  GIVEN("a valid string id"){

    utility::Id<double> id(str);
    WHEN("using the getString() function") {

      THEN("returns the identifier string") {

        LOG(INFO) << "Test " << ++testNumber 
                  << ": [construction] No Errors Expected";
        REQUIRE( str == id.getString() );
      }
    }
  }
}

SCENARIO("Id operators ", "[utility], [Id]"){

  GIVEN("two valid string id objects"){

    utility::Id<double> a("a");
    utility::Id<double> b("b");
    WHEN("comparing the identifier objects") {

      THEN("the comparison operators function correctly") {

        LOG(INFO) << "Test " << ++testNumber 
                  << ": [comparison a and a] No Errors Expected";
        REQUIRE( (a < a) == false );
        REQUIRE( (a <= a) == true );
        REQUIRE( (a > a) == false );
        REQUIRE( (a >= a) == true );
        REQUIRE( (a == a) == true );
        REQUIRE( (a != a) == false );

        LOG(INFO) << "Test " << ++testNumber 
                  << ": [comparison a and b] No Errors Expected";
        REQUIRE( (a < b) == true );
        REQUIRE( (a <= b) == true );
        REQUIRE( (a > b) == false );
        REQUIRE( (a >= b) == false );
        REQUIRE( (a == b) == false );
        REQUIRE( (a != b) == true );

        LOG(INFO) << "Test " << ++testNumber 
                  << ": [comparison b and a] No Errors Expected";
        REQUIRE( (b < a) == false );
        REQUIRE( (b <= a) == false );
        REQUIRE( (b > a) == true );
        REQUIRE( (b >= a) == true );
        REQUIRE( (b == a) == false );
        REQUIRE( (b != a) == true );
      }
    }
  }
}

SCENARIO("Id out stream ", "[utility], [Id]"){

  GIVEN("a valid string id"){

    utility::Id<double> id(str);
    WHEN("using the << output stream operator") {

      THEN("writes the identifier string to the stream") {

        std::ostringstream out;
        out << id;

        LOG(INFO) << "Test " << ++testNumber 
                  << ": [streaming] No Errors Expected";
        REQUIRE( str == id.getString() );
      }
    }
  }
}

