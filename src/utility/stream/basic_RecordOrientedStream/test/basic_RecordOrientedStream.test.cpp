#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "utility.hpp"

using namespace njoy::utility::stream;

std::string phrase1("123456");
std::string phrase2("7890123");
std::string line1Text( phrase1 + " " + phrase2 );
std::string line2Text("ABCDEFG--098765");
std::string line3Text("Lorem ipsum dolor sit amet");

SCENARIO( "Creating a record-oriented stream for writing",
          "[TemporaryFileStream]"){
  WHEN( "creating a record-oriented stream" ){
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

    REQUIRE( 'a' == ros.get() );
    ros.unget(); 
    REQUIRE( 'a' == ros.get() );
    ros.unget();
    ros.unget(); /* fails to cross into previous line */
    REQUIRE( not ros.good() );
    ros.clear();
    REQUIRE( ros.good() );
    
    REQUIRE( 'a' == ros.get() );
    REQUIRE( 'b' == ros.get() );
    REQUIRE( 'c' == ros.get() );
    REQUIRE( std::char_traits<char>::eof() == ros.get() );
    REQUIRE( std::char_traits<char>::eof() == ros.get() );
  }

  WHEN( "assigning one stream to another" ){
    std::istringstream iss( line1Text );
    iRecordOrientedStream ros( std::move(iss) );

    std::istringstream iss2( "abc2" );
    ros = iRecordOrientedStream( std::move( iss2 ) );
    REQUIRE( ros.buffer == "" );
    std::string garbage;
    ros >> garbage;
    REQUIRE( garbage == "abc2" );
    REQUIRE( ros.buffer == "abc2" );
  }
} // SCENARIO
