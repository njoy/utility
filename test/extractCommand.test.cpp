#include "catch.hpp"

#include "utility.hpp"

extern int testNumber;

SCENARIO("extractCommand will extract commands preceding Fortran EOL",
	 "[utility]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  GIVEN("a string with a Fortran EOL character"){
    const std::string reference(" 10 20 30 ");
    const std::string card = reference + "/ inline comment";
    WHEN("passed to the extractCommand function"){
      std::string command;
      REQUIRE_NOTHROW(command = utility::extractCommand(card));
      THEN("the return value will only contain the substring preceing the EOL character"){
	REQUIRE(reference == command);
      }
    }
  }
  
  GIVEN("a string with a Fortran EOL character in inline comment"){
    const std::string reference(" 10 20 30 ");
    const std::string card = reference + "/ inline / comment";
    WHEN("passed to the extractCommand function"){
      std::string command;
      REQUIRE_NOTHROW(command = utility::extractCommand(card));
      THEN("the return value will only contain the substring preceeding the first EOL character"){
	REQUIRE(reference == command);
      }
    }
  }
  
}

SCENARIO("extractCommand will not throw for line without Fortran EOL",
	 "[utility]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  GIVEN("a string without a Fortran EOL character"){
    const std::string reference(" 10 20 30 ");
    const std::string card = reference;
    WHEN("passed to the extractCommand function"){
      std::string command;
      REQUIRE_NOTHROW(command = utility::extractCommand(card));
      THEN("the return value will be a copy of the input"){
	REQUIRE(reference == command);
      }
    }
  }
}

SCENARIO("extractCommand will ignore Fortran EOL characters in string arguments",
	 "[utility]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  GIVEN("a string with a Fortran EOL character in double quotes and no inline comment"){
    const std::string reference(" 10 20 30 \"string/argument\"");
    const std::string card = reference;
    WHEN("passed to the extractCommand function"){
      std::string command;
      REQUIRE_NOTHROW(command = utility::extractCommand(card));
      THEN("the return value will be a copy of the input"){
	REQUIRE(reference == command);
      }
    }
  }

  GIVEN("a string with a Fortran EOL character in double quotes and also inline comment"){
    const std::string reference(" 10 20 30 \"string/argument\" ");
    const std::string card = reference + "/ inline comment";
    WHEN("passed to the extractCommand function"){
      std::string command;
      REQUIRE_NOTHROW(command = utility::extractCommand(card));
      THEN("the return value will only contain the substring preceing the first unquoted EOL character"){
	REQUIRE(reference == command);
      }
    }
  }

  GIVEN("a string with a Fortran EOL character in single quotes and no inline comment"){
    const std::string reference(" 10 20 30 \'string/argument\'");
    const std::string card = reference;
    WHEN("passed to the extractCommand function"){
      std::string command;
      REQUIRE_NOTHROW(command = utility::extractCommand(card));
      THEN("the return value will be a copy of the input"){
	REQUIRE(reference == command);
      }
    }
  }

  GIVEN("a string with a Fortran EOL character in single quotes and also inline comment"){
    const std::string reference(" 10 20 30 \'string/argument\' ");
    const std::string card = reference + "/ inline comment";
    WHEN("passed to the extractCommand function"){
      std::string command;
      REQUIRE_NOTHROW(command = utility::extractCommand(card));
      THEN("the return value will only contain the substring preceing the first unquoted EOL character"){
	REQUIRE(reference == command);
      }
    }
  }

  GIVEN("a string with a single quote character in double quotes string"){
    const std::string reference(" 10 20 30 \"string argument\'s value\"");
    const std::string card = reference + "/ inline comment"; 
    WHEN("passed to the extractCommand function"){
      std::string command;
      REQUIRE_NOTHROW(command = utility::extractCommand(card));
      THEN("the return value will only contain the substring preceing the first unquoted EOL character"){
	REQUIRE(reference == command);
      }
    }
  }

  GIVEN("a string with a double quote character in single quotes string"){
    const std::string reference(" 10 20 30 \'string \"arguments\"\'");
    const std::string card = reference + "/ inline comment"; 
    WHEN("passed to the extractCommand function"){
      std::string command;
      REQUIRE_NOTHROW(command = utility::extractCommand(card));
      THEN("the return value will only contain the substring preceing the first unquoted EOL character"){
	REQUIRE(reference == command);
      }
    }
  }

}

SCENARIO("extractCommand will throw for unmatched quotations when EOL character present",
	 "[utility]"){
  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";

  GIVEN("a string with unmatched double quote with EOL character"){
    const std::string reference(" 10 20 30 \"open string arg with EOL character /");
    const std::string card = reference;
    WHEN("passed to the extractCommand function"){
      std::string command;
      THEN("extractCommand will throw"){
	REQUIRE_THROWS(command = utility::extractCommand(card));
      }
    }
  }

  GIVEN("a string with unmatched single quote with EOL character"){
    const std::string reference(" 10 20 30 \'open string arg with EOL character /");
    const std::string card = reference;
    WHEN("passed to the extractCommand function"){
      std::string command;
      THEN("extractCommand will throw"){
	REQUIRE_THROWS(command = utility::extractCommand(card));
      }
    }
  }

  GIVEN("a string with mismatched quotes with EOL character"){
    const std::string reference(" 10 20 30 \"mismatched string arg with EOL character / \'");
    const std::string card = reference;
    WHEN("passed to the extractCommand function"){
      std::string command;
      THEN("extractCommand will throw"){
	REQUIRE_THROWS(command = utility::extractCommand(card));
      }
    }
  }

}

