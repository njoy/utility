#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "easylogging++.h"

//INITIALIZE_EASYLOGGINGPP
//SHARE_EASYLOGGINGPP(el::Helpers::storage());

int testNumber = 0;

int main( int argc, char* const argv[] )
{
  LOG(INFO) << "";
  LOG(INFO) << "Utility Function Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "Utility Function Tests Complete!";
  return result;
}
