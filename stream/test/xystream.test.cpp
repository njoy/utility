// other includes
#include "catch.hpp"

// what we're testing
#include "utility/stream.hpp"

extern int testNumber;

// enum class to test the various functions
enum class TestEnum {

  VALUE1,
  VALUE2
};

// maps used for testing
const std::map<std::string,TestEnum> ENUMMAP
  = { { "value1", TestEnum::VALUE1 } ,
      { "value2", TestEnum::VALUE2 } };
const std::map<TestEnum,std::string> STRINGMAP
  = { { TestEnum::VALUE1, "value1" } ,
      { TestEnum::VALUE2, "value2" } };
const std::map<TestEnum,std::string> STRINGMAPEXCEPTION
  = { { TestEnum::VALUE1, "value1" } };

// ostream operator for the test enumerator (nice test output)
std::ostream& operator<<(std::ostream& out, const TestEnum& value) {

  return utility::stream::writeValue(out, value, STRINGMAP);
}

SCENARIO("Test readValue ", "[utility/stream], [X,Y stream]") {

  GIVEN("an input stream, an enum class and associated strings"){

    std::istringstream in("value1 value2 this should fail");
    WHEN("reading values from the stream") {

      TestEnum value1, value2;
      std::string string;

      utility::stream::readValue(in, value1, ENUMMAP);
      utility::stream::readValue(in, value2, ENUMMAP);
      THEN("the enum values are found") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [readValue] No Errors Expected";
        REQUIRE( TestEnum::VALUE1 == value1 );
        REQUIRE( TestEnum::VALUE2 == value2 );
      }

      utility::stream::readValue(in, value1, ENUMMAP);
      THEN("the stream goes into fail and the value is unchanged") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [readValue] No Errors Expected";
        REQUIRE( TestEnum::VALUE1 == value1 );
        REQUIRE( true == in.fail() );
      }

      in.clear();
      std::getline(in, string);
      THEN("the remaining stream should be \" this should fail\"") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [readValue] No Errors Expected";
        REQUIRE( " this should fail" == string );
      }
    }
  }
}

SCENARIO("Test writeValue ", "[utility/stream], [X,Y stream]") {

  GIVEN("an output stream, an enum class and associated strings"){

    std::ostringstream out;
    WHEN("writing values from the stream") {

      utility::stream::writeValue(out, TestEnum::VALUE1, STRINGMAP);
      out << " ";
      utility::stream::writeValue(out, TestEnum::VALUE2, STRINGMAP);
      THEN("the enum values are written to the stream") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [readValue] No Errors Expected";
        REQUIRE( out.str() == "value1 value2" );
      }

      out << " not modified";
      utility::stream::writeValue(out, TestEnum::VALUE2, STRINGMAPEXCEPTION);
      THEN("the stream goes into fail and the value is unchanged") {

        LOG(INFO) << "Test " << ++testNumber
                  << ": [readValue] No Errors Expected";
        REQUIRE( out.str() == "value1 value2 not modified" );
      }
    }
  }
}

