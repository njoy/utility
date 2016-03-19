#include <vector>
#include <sstream>

#include "catch.hpp"

#include "utility/stream.hpp"

extern int testNumber;

SCENARIO("getInteger returns the proper value from streams with integer strings",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  const std::string name("testInteger");
  std::vector<std::string> bufferQueue;
  bufferQueue.emplace_back(" 123 ");
  bufferQueue.emplace_back(" +123 ");
  bufferQueue.emplace_back(" -123 ");
  bufferQueue.emplace_back(" 0123 ");
  std::istringstream buffer;
  bool found;

  GIVEN("stream with integer values"){
    WHEN("passed to getInteger"){
      THEN("the correct integer value is returned"){
	for( std::string& guts : bufferQueue ){
	  buffer.clear();
	  buffer.str(guts);
	  REQUIRE(std::stoi(guts) == utility::stream::getInteger(buffer, name));
	  buffer.clear();
	  buffer.seekg(0);
	  found = false;
	  REQUIRE(std::stoi(guts) == utility::stream::getInteger(buffer, name, found));
	  REQUIRE(true == found);
	}
      }
    }
  }

}

SCENARIO("getInteger throws for streams with non-integer strings",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";

  const std::string name("testInteger");
  std::vector<std::string> bufferQueue;
  bufferQueue.emplace_back(" 123. ");
  bufferQueue.emplace_back(" +123.0 ");
  bufferQueue.emplace_back(" -123E2 ");
  bufferQueue.emplace_back(" string ");
  std::istringstream buffer;
  bool found;

  GIVEN("stream with non-integer values"){
    WHEN("passed to getInteger"){
      THEN("will throw"){
	for( std::string& guts : bufferQueue ){
	  buffer.clear();
	  buffer.str(guts);
	  REQUIRE_THROWS(utility::stream::getInteger(buffer, name));
	  buffer.clear();
	  buffer.seekg(0);
	  REQUIRE_THROWS(utility::stream::getInteger(buffer, name, found));
	}
      }
    }
  }

}

SCENARIO("mandatory getInteger throws for streams with badbit",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";

  const std::string name("testInteger");
  GIVEN("empty stream"){
    std::istringstream buffer;
    WHEN("passed to getInteger"){
      THEN("will throw"){
	REQUIRE_THROWS(utility::stream::getInteger(buffer, name));
      }
    }
  }
}

SCENARIO("optional getInteger sets found flag to false for streams with badbit",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  const std::string name("testInteger");
  bool found = true;
  GIVEN("empty stream"){
    std::istringstream buffer;
    WHEN("passed to getInteger"){
      THEN("will set found flag to false"){
	REQUIRE_NOTHROW(utility::stream::getInteger(buffer, name, found));
	REQUIRE(found == false);
      }
    }
  }
}
