#define CATCH_CONFIG_MAIN

#include <cstdio>

#include "catch.hpp"

#include "utility.hpp"

using namespace njoy::utility::stream;

SCENARIO( "Creating a temporary file for writing",
          "[TemporaryFileStream]"){
  WHEN( "creating a temporary file" ){
    std::string filename;
    std::string arbText{"abcdefg--123456\nABCDEFG--098765"};

    THEN( "we can write to the temporary file" ){
      {
        TemporaryFileStream tfs;

        tfs << arbText;
        tfs.flush();
        filename = tfs.filename();

        AND_THEN( "the contents of the file can be verified." ){
          REQUIRE( arbText == njoy::utility::slurpFileToMemory(filename) );
        }
      }
      AND_THEN( "the temporary file is deleted upon destruction." ){

        FILE* testfile = fopen( filename.c_str(), "wx" );

        REQUIRE( testfile != NULL );
      }

    }
  } // WHEN

  WHEN( "testing ability to throw exceptions" ){
    REQUIRE_THROWS( TemporaryFileStream tfs(0) );
  }
} // SCENARIO
