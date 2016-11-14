#define CATCH_CONFIG_MAIN

#include <cstdio>
#include <ostream>

#include "catch.hpp"

#include "utility.hpp"

using namespace njoy::utility::stream;

SCENARIO( "Using the FILE_streambuf to write to a file", 
         "[FILE_streambuf]"){
  GIVEN( "A file pointer and an arbitrary string to write to a file" ){
    std::string filename{"foo.txt"};
    std::string arbText{"abcdefg--123456\nABCDEFG--098765"};

    WHEN( "Using the FILE_streambuf to write a file" ){
      FILE* filePtr = fopen(filename.c_str(), "w");
      THEN( "the FILE_streambuf can be created and text can be written to it" ){
        {
          FILE_streambuf<char> fsb(filePtr, 5);
          std::ostream ostm(&fsb);
          ostm << arbText;
          ostm.flush();
        }
        AND_THEN( "the contents of the file can be verified." ){
          REQUIRE( arbText == njoy::utility::slurpFileToMemory("foo.txt") );
        }
      }
  }

    WHEN( "Using the FILE_streambuf to read in a file" ){
      FILE* filePtr = fopen(filename.c_str(), "r");
      FILE_streambuf<char> fsb(filePtr);
      std::istream is( &fsb );

      std::string text;
      std::string totalText{""};
      is >> text;
      totalText += text;
      totalText += "\n";
      is >> text;
      totalText += text;

      REQUIRE( arbText == totalText );

      std::remove(filename.c_str());
    }
  }   // GIVEN

}   // SCENARIO
