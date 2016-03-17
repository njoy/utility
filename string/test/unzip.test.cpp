
#include <vector>
#include <string>

#include "catch.hpp"

#include "utility/string.hpp"

extern int testNumber;

SCENARIO("unzip will correctly split a string of numbers into N vectors"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";
  GIVEN( "A string of integer values" ){
    std::string iValues = " 0   1   2   3   4   5   6   7   8   9 \n " \
                          " 10  11  12  13  14  15  16  17  18  19 ";

    THEN( "unzip<int, int> will return two vectors" ){
      std::tuple< std::vector<int>, 
                  std::vector<int> > nTuple;
      REQUIRE_NOTHROW(
        (nTuple = utility::string::unzip<int, int>::parse(iValues, 10)) );

      AND_THEN( "The contents of the vectors are correct" ){

        std::vector<int> even = std::get<0>(nTuple);
        std::vector<int> odd  = std::get<1>(nTuple);

        REQUIRE( (std::vector<int>{0,2,4,6,8,10,12,14,16,18}) == even );
        REQUIRE( (std::vector<int>{1,3,5,7,9,11,13,15,17,19}) == odd );
      }
    } 
    THEN( "unzip<int, int, int, int> will return four vectors" ){
      std::tuple< std::vector<int>,
                  std::vector<int>,
                  std::vector<int>,
                  std::vector<int> > nTuple;
      REQUIRE_NOTHROW( (nTuple = 
         utility::string::unzip<int, int, int, int>::parse(iValues, 5)) );

      AND_THEN( "The contents of the vectors are correct" ){

        std::vector<int> v0 = std::get<0>(nTuple);
        std::vector<int> v1 = std::get<1>(nTuple);
        std::vector<int> v2 = std::get<2>(nTuple);
        std::vector<int> v3 = std::get<3>(nTuple);

        REQUIRE( (std::vector<int>{0,4,8 ,12,16}) == v0 );
        REQUIRE( (std::vector<int>{1,5,9 ,13,17}) == v1 );
        REQUIRE( (std::vector<int>{2,6,10,14,18}) == v2 );
        REQUIRE( (std::vector<int>{3,7,11,15,19}) == v3 );
      }
    } 
  } // GIVEN <int>

  GIVEN( "A string of double values" ){
    std::string iValues = "0.0 1.1 2.2 3.3 4.4 5.5 6.6 7.7 8.8 9.9 10.10 11.11";

    THEN( "unzip<double, double> will return two vectors" ){
      std::tuple< std::vector<double>,
                  std::vector<double> > nTuple;

      REQUIRE_NOTHROW(
        (nTuple = utility::string::unzip<double, double>::parse(iValues, 6) ) );

      AND_THEN( "The contents of the vectors are correct" ){

        std::vector<double> v0 = std::get<0>(nTuple);
        std::vector<double> v1 = std::get<1>(nTuple);

        REQUIRE( (std::vector<double>{0.0, 2.2, 4.4, 6.6, 8.8, 10.10} == v0) );
        REQUIRE( (std::vector<double>{1.1, 3.3, 5.5, 7.7, 9.9, 11.11} == v1) );
      }
    }
    THEN( "unzip<double, double, double> will return three vectors" ){
      std::tuple< std::vector<double>,
                  std::vector<double>,
                  std::vector<double> > nTuple;

      REQUIRE_NOTHROW( (nTuple = 
          utility::string::unzip<double, double, double>::parse(iValues, 4) ) );

      AND_THEN( "The contents of the vectors are correct" ){

        std::vector<double> v0 = std::get<0>(nTuple);
        std::vector<double> v1 = std::get<1>(nTuple);
        std::vector<double> v2 = std::get<2>(nTuple);

        REQUIRE( (std::vector<double>{0.0, 3.3, 6.6, 9.9 }  == v0) );
        REQUIRE( (std::vector<double>{1.1, 4.4, 7.7, 10.10} == v1) );
        REQUIRE( (std::vector<double>{2.2, 5.5, 8.8, 11.11} == v2) );
      }
    }
  } // GIVEN <double>
  
  GIVEN( "A string of mixed integer and double values" ){

    std::string iValues = "0 0.0 1 1.1 2 2.2 3 3.3 4 4.4 5 5.5";

    THEN( "unzip<int,double> will return two vectors" ){
      std::tuple< std::vector<int>,
                  std::vector<double> > nTuple;

      REQUIRE_NOTHROW( 
        (nTuple = utility::string::unzip<int, double>::parse(iValues, 5) ) );

      AND_THEN( "The contents of the vectors are correct" ){

        std::vector<int> vint     = std::get<0>(nTuple);
        std::vector<double> vdoub = std::get<1>(nTuple);

        REQUIRE( (std::vector<int>{0,1,2,3,4}              == vint) );
        REQUIRE( (std::vector<double>{0.0,1.1,2.2,3.3,4.4} == vdoub) );
      }

    }
    THEN( "unzip<int, double, int, double> will return four vectors" ){
      std::tuple< std::vector<int>,
                  std::vector<double>,
                  std::vector<int>,
                  std::vector<double> > nTuple;

      REQUIRE_NOTHROW( (nTuple = 
        utility::string::unzip<int, double, int, double>::parse(iValues, 3) ) );

      AND_THEN( "The contents of the vectors are correct" ){

        std::vector<int> v0    = std::get<0>(nTuple);
        std::vector<double> v1 = std::get<1>(nTuple);
        std::vector<int> v2    = std::get<2>(nTuple);
        std::vector<double> v3 = std::get<3>(nTuple);

        REQUIRE( (std::vector<int>{0,2,4}          == v0) );
        REQUIRE( (std::vector<double>{0.0,2.2,4.4} == v1) );
        REQUIRE( (std::vector<int>{1,3,5}          == v2) );
        REQUIRE( (std::vector<double>{1.1,3.3,5.5} == v3) );
      }
    }
  } // GIVEN <int, double>
  GIVEN( "A string of strings" ){
    std::string iValues = "zero one two three four five six seven eight nine";

    THEN( "unzip<std::string, std::string> will return two vectors" ){
      std::tuple< std::vector<std::string>,
                  std::vector<std::string> > nTuple;

      REQUIRE_NOTHROW( (nTuple = 
        utility::string::unzip<std::string, std::string>::parse(iValues,5) ) );

      AND_THEN( "The contents of the vectors are correct" ){

        std::vector<std::string> even = std::get<0>(nTuple);
        std::vector<std::string> odd  = std::get<1>(nTuple);

        REQUIRE( (std::vector<std::string>{
          "zero","two","four","six","eight"} == even) );
        REQUIRE( (std::vector<std::string>{
          "one","three","five","seven","nine"} == odd) );
      }
    }

  } // GIVEN <string>
} // SCENARIO

SCENARIO( "unzip will (correctly) throw exceptions" ){
  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";
  GIVEN( "A string of values that is too short" ){
    std::string iValues = " 0   1   2   3   4   5   6   7   8   9";

    std::tuple< std::vector<int>, std::vector<int> > nTuple;

    THEN( "unzip will throw an exception when asking for too many numbers" ){
      REQUIRE_THROWS(
        (nTuple = utility::string::unzip<int, int>::parse(iValues, 11)) );

    }
  } // GIVEN
} // SCENARIO
