#include <fstream>

#include "catch.hpp"
#include "utility.hpp"

using namespace njoy::utility::stream;

SCENARIO("Encountered segfault when cleaning up moved input record oriented"
         "stream composing a type-erased ifstream"){
  {
    iRecordOrientedStream stream( iRecordOrientedStream
  				  ( std::ifstream("./helloWord.txt") ) );
  }
}
