#define CATCH_CONFIG_RUNNER

// other includes
#include "catch.hpp"

// what we're testing
#include "utility/ID.hpp"

int testNumber = 0;

namespace {

  // test variable
  std::string str("myId");
  std::string validstr("validId");

  // dummy test class and validation function
  class Dummy {};
}

// override validateID function for the Dummy class
namespace utility {

  template <> bool validateID<Dummy>(const std::string& id) noexcept {

    if (id != validstr) {

      return false;
    }
    return true;
  }
}

int main( int argc, const char* argv[] )
{
  LOG(INFO) << "";
  LOG(INFO) << " ID Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "ID Tests Complete!";
  return result;
}

SCENARIO("ID construction ", "[utility], [ID]"){

  GIVEN("an identifier string"){

    WHEN("constructing a valid string ID with the default validateString") {

      THEN("the constructor should not throw") {

        LOG(INFO) << "Test " << ++testNumber 
                  << ": [construction] No Errors Expected";
        REQUIRE_NOTHROW( utility::ID<double> id(str) );
      }
    }

    WHEN("constructing a valid string ID with an override validateString") {

      THEN("the constructor should not throw with a valid string") {

        LOG(INFO) << "Test " << ++testNumber 
                  << ": [construction] No Errors Expected";
        REQUIRE_NOTHROW( utility::ID<Dummy> id(validstr) );
      }
    }

    WHEN("constructing a valid string ID with an override validateString") {

      THEN("the constructor should throw with a invalid string") {

        LOG(INFO) << "Test " << ++testNumber 
                  << ": [construction] No Errors Expected";
        REQUIRE_THROWS( utility::ID<Dummy> id(str) );
      }
    }
  }

  GIVEN("a valid string id"){

    utility::ID<double> id(str);
    WHEN("using the getString() function") {

      THEN("returns the identifier string") {

        LOG(INFO) << "Test " << ++testNumber 
                  << ": [construction] No Errors Expected";
        REQUIRE( str == id.getString() );
      }
    }
  }
}

SCENARIO("ID operators ", "[utility], [ID]"){

  GIVEN("two valid string id objects"){

    utility::ID<double> a("a");
    utility::ID<double> b("b");
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

SCENARIO("ID out stream ", "[utility], [ID]"){

  GIVEN("a valid string id"){

    utility::ID<double> id(str);
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

