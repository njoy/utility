#include <vector>
#include <sstream>

#include "catch.hpp"

#include "utility/stream.hpp"

extern int testNumber;

SCENARIO("getIntWithLBound's left bound is inclusive",
         "[utility],[stream]"){

  int returnInteger;
  const int tooLow = 1;
  const int leftBound = 5;
  const int higher = 7;
  const std::string name("testInteger");

  GIVEN("a stream with an integer greater than the left bound"){
    LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";
    std::istringstream buffer(std::to_string(higher));
    WHEN("passed to getIntWithLBound"){
      THEN("the correct integer value will be returned"){
	REQUIRE_NOTHROW(returnInteger = utility::stream::getIntWithLBound(buffer, name, leftBound));
	REQUIRE(higher == returnInteger);
      }
    }
  }

  GIVEN("a stream with an integer equal to the left bound"){
    LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";
    std::istringstream buffer(std::to_string(leftBound));
    WHEN("passed to getIntWithLBound"){
      THEN("the correct integer value will be returned"){
	REQUIRE_NOTHROW(returnInteger = utility::stream::getIntWithLBound(buffer, name, leftBound));
	REQUIRE(leftBound == returnInteger);
      }
    }
  }

  GIVEN("a stream with an integer less than the left bound"){
    LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";
    std::istringstream buffer(std::to_string(tooLow));
    WHEN("passed to getIntWithLBound"){
      THEN("will throw"){
	REQUIRE_THROWS(returnInteger = utility::stream::getIntWithLBound(buffer, name, leftBound));
      }
    }
  }

}

/* repetition of the getInteger tests */
SCENARIO("getIntWithLBound returns the proper value from streams with integer strings",
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
    WHEN("passed to getIntWithLBound"){
      THEN("the correct integer value is returned"){
	for( std::string& guts : bufferQueue ){
	  buffer.clear();
	  buffer.str(guts);
	  REQUIRE(std::stoi(guts) == utility::stream::getIntWithLBound(buffer, name, -125));
	  buffer.clear();
	  buffer.seekg(0);
	  found = false;
	  REQUIRE(std::stoi(guts) == utility::stream::getIntWithLBound(buffer, name, -125, found));
	  REQUIRE(true == found);
	}
      }
    }
  }

}

SCENARIO("getIntWithLBound throws for streams with non-integer strings",
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
    WHEN("passed to getIntWithLBound"){
      THEN("will throw"){
	for( std::string& guts : bufferQueue ){
	  buffer.clear();
	  buffer.str(guts);
	  REQUIRE_THROWS(utility::stream::getIntWithLBound(buffer, name, -125));
	  buffer.clear();
	  buffer.seekg(0);
	  REQUIRE_THROWS(utility::stream::getIntWithLBound(buffer, name, -125, found));
	}
      }
    }
  }

}

SCENARIO("mandatory getIntWithLBound throws for streams with badbit",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";

  const std::string name("testInteger");
  GIVEN("empty stream"){
    std::istringstream buffer;
    WHEN("passed to getIntWithLBound"){
      THEN("will throw"){
	REQUIRE_THROWS(utility::stream::getIntWithLBound(buffer, name, -125));
      }
    }
  }
}

SCENARIO("optional getIntWithLBound sets found flag to false for streams with badbit",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  const std::string name("testInteger");
  bool found = true;
  GIVEN("empty stream"){
    std::istringstream buffer;
    WHEN("passed to getIntWithLBound"){
      THEN("will set found flag to false"){
	REQUIRE_NOTHROW(utility::stream::getIntWithLBound(buffer, name, -125, found));
	REQUIRE(found == false);
      }
    }
  }
}
