#define CATCH_CONFIG_RUNNER

// other includes
#include "catch.hpp"

// what we're testing
#include "utility/Id.hpp"

// dummy test class and validation function
class Dummy {};
namespace utility {

  // specialised validateId function for the Dummy class
  template <> bool validateId<Dummy>(const std::string& id) {

    if (id != "validId") {

      return false;
    }
    return true;
  }
}

int testNumber = 0;

int main( int argc, const char* argv[] )
{
  LOG(INFO) << "";
  LOG(INFO) << " View Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "View Tests Complete!";
  return result;
}


/*
BOOST_AUTO_TEST_CASE(testSetFunctions) {

  // create new id
  utility::Id<double> id("myId");

  // test values
  BOOST_CHECK_EQUAL(id.getString(), "myId");

  // set string
  id.setString("myNewId");

  // test values
  BOOST_CHECK_EQUAL(id.getString(), "myNewId");
}

BOOST_AUTO_TEST_CASE(testOperators) {

  // create new id
  utility::Id<double> id1("a");
  utility::Id<double> id2("b");

  // test values
  BOOST_CHECK_EQUAL(id1 <  id1, false);
  BOOST_CHECK_EQUAL(id1 == id1, true);
  BOOST_CHECK_EQUAL(id1 != id1, false);
  BOOST_CHECK_EQUAL(id1 <  id2, true);
  BOOST_CHECK_EQUAL(id1 == id2, false);
  BOOST_CHECK_EQUAL(id1 != id2, true);
  BOOST_CHECK_EQUAL(id2 <  id1, false);
  BOOST_CHECK_EQUAL(id2 == id1, false);
  BOOST_CHECK_EQUAL(id2 != id1, true);
}

BOOST_AUTO_TEST_CASE(testInStream) {

  // input stream and SectionId
  std::istringstream in("validId this should fail");
  utility::Id<Dummy> id;

  // read from the stream
  in >> id;

  // test stream state
  BOOST_CHECK(!in.fail());
  BOOST_CHECK(!in.eof());

  // test values
  BOOST_CHECK_EQUAL(id.getString(), "validId");

  // read from the stream (should fail)
  in >> id;

  // test stream state
  BOOST_CHECK(in.fail());

  // clear the stream and read the remainder
  in.clear();
  std::string temp;

  // test the remainder
  std::getline(in, temp);
  BOOST_CHECK_EQUAL(temp, " this should fail");

  // test values (identifier should be unchanged)
  BOOST_CHECK_EQUAL(id.getString(), "validId");
}

BOOST_AUTO_TEST_CASE(testOutStream) {

  // output stream and id
  std::ostringstream out;
  utility::Id<double> id("myId");

  // write to the stream
  out << id;

  // test values
  BOOST_CHECK_EQUAL(out.str(), "myId");
}

BOOST_AUTO_TEST_CASE(testExceptions) {

  // create an identifier
  utility::Id<Dummy> id("validId");

  // test constructor exceptions
  BOOST_REQUIRE_THROW(utility::Id<Dummy>("notValidId"), std::invalid_argument);

  // test set function exceptions
  BOOST_REQUIRE_THROW(id.setString("notValidId"), std::invalid_argument);
  BOOST_CHECK_EQUAL(id.getString(), "validId");
}*/

SCENARIO("Id construction ", "[utility], [Id]"){

  GIVEN("A string based Id"){

    WHEN("Constructing a valid string Id") {
      THEN("the constructor should not throw") {
        LOG(INFO) << "Test " << ++testNumber 
                  << ": [construction] No Errors Expected";
        REQUIRE_NOTHROW( utility::Id<double>("myId") );
      }
    }

    utility::Id<double> id("myId");
    WHEN("When the string is a valid Id") {
      THEN("the getString() returns the identifier string") {
        LOG(INFO) << "Test " << ++testNumber 
                  << ": [construction] No Errors Expected";
        REQUIRE( "myId" == id.getString() );
      }
    }
  }
}

