#include <vector>

#include "catch.hpp"

#include "utility.hpp"

const std::vector< std::string > ws = { "\t  \n", " ", "\t" };
const std::vector< std::string > c = { "a", "abc", "a,c" };

using namespace njoy::utility::string;

SCENARIO( "Default split will ignore leading trailing whitespace blobs" ){
  std::string trial("   ");
  for ( std::string::size_type i = 0; i < c.size(); ++i ){
    trial += c[i];
    trial += ws[i];
  }
  GIVEN( "whitespace delimited substrings in a argument string" ){
    WHEN( "passed to split" ){
      THEN( "the substrings are recovered" ){ 
        REQUIRE( c == split(trial) );
      }
    }
  }
}

SCENARIO( "split on arbitrary characters" ){
  std::string trial("");
  for (std::string::size_type i = 0; i < c.size() - 1; ++i){
    trial += c[i];
    trial += ";";
  }
  trial += c.back();
  GIVEN("\'xyz\' delimited substrings in a argument string"){
    WHEN("passed to split"){
      THEN("the substrings are recovered"){        
        REQUIRE(c == njoy::utility::string::split(trial, std::string(";")));
      }
    }
  }
}

SCENARIO(
  "splitting on arbitrary substrings can produce "
  "empty string entries in resulting list" ){
  std::string trial("");
  for (std::string::size_type i = 0; i < c.size(); ++i){
    trial += c[i];
    trial += ";";
  }
  auto cp = c;
  cp.push_back("");
  GIVEN("semicolon delimited substrings in a argument string"){
    WHEN("passed to split"){
      THEN("the substrings are recovered"){        
        REQUIRE(cp == njoy::utility::string::split(trial, std::string(";")));
      }
    }
  }
}


