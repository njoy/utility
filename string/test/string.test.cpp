#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "utility/string.hpp"

int testNumber = 0;

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "Utility/String Function Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "Utility/String Function Tests Complete!";
  return result;
}
