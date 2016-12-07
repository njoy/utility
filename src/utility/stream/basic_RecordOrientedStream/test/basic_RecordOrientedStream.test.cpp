#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "utility.hpp"

using namespace njoy::utility::stream;

SCENARIO( "Creating a record-oriented stream for writing",
          "[TemporaryFileStream]"){
  WHEN( "creating a record-oriented stream" ){
    std::string phrase1("123456");
    std::string phrase2("7890123");
    std::string line1Text( phrase1 + " " + phrase2 );
    std::string line2Text("ABCDEFG--098765");
    std::string line3Text("Lorem ipsum dolor sit amet");

    std::istringstream iss( line1Text
			    + '\n' + line2Text
			    + '\n' + line3Text
			    + '\n' + "abc" );
    iRecordOrientedStream ros( std::move(iss) );
    
    int integerSink;
    std::string stringSink;
    ros >> integerSink;
    REQUIRE( ros.buffer == phrase1 );
    ros >> integerSink;
    REQUIRE( ros.buffer == line1Text );
    REQUIRE( ros.lineNumber == 1 );
    ros >> stringSink;
    REQUIRE( ros.lineNumber == 2 );
    REQUIRE( ros.buffer == line2Text );
    ros.get();
    REQUIRE( ros.buffer == line2Text );
    ros.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
    REQUIRE( ros.buffer == line3Text );
    char c = ros.get();
    REQUIRE( 'a' == c );
    ros.unget();
    ros.unget();
    ros.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
    ros.unget();
    ros.unget();
    ros.get();
    REQUIRE( std::char_traits<char>::eof() == ros.get() );
  }
} // SCENARIO
