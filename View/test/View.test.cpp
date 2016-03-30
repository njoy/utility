#define CATCH_CONFIG_RUNNER

#include <numeric>
#include <vector>

#include "catch.hpp"

#include "utility/View.hpp"

int testNumber = 0;

int main( int argc, const char* argv[] )
{
  LOG(INFO) << "";
  LOG(INFO) << " View Tests";
  LOG(INFO) << "======================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "View Tests Complete!";
  return result;
}

SCENARIO("the View class can be instantiated",
	 "[utility], [View]"){
  GIVEN("a vector of integers"){
    std::vector<int> vi = {0,1,2,3,4,5};
    WHEN("the container is used in its entirety to construct a view"){
      utility::View<int> view( vi.begin(), vi.end() );
      THEN("the View will function with range iteration"){
        int viewSum = 0;
        LOG(INFO) << "Test " << ++testNumber
                  << ": [range-based iteration] No Errors Expected";
        for (auto element : view ){ viewSum += element; }
        int referenceSum = std::accumulate(vi.begin(), vi.end(), 0);
        REQUIRE( referenceSum == viewSum);
      }
      
      THEN("the bracket operator works"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [operator[]] No Errors Expected";
        for (unsigned long i = 0; i < vi.size(); ++i){
          REQUIRE(vi[i] == view[i]);  
        }
      }

      THEN("the 'at' method works"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [at] No Errors Expected";
        for (unsigned long i = 0; i < vi.size(); ++i){
          REQUIRE(vi.at(i) == view.at(i));  
        }
        LOG(INFO) << "Test " << ++testNumber
                  << ": [at] Errors Expected";
        REQUIRE_THROWS(view.at(6));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [at] Errors Expected";
        REQUIRE_THROWS(view.at(-1));        
      }

      THEN("the 'back' method works "){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [back] No Errors Expected";
        REQUIRE(vi.back() == view.back());
      }

      THEN("the 'front' method works "){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [front] No Errors Expected";
        REQUIRE(vi.front() == view.front());
      }

      THEN("the 'size' method works "){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [size] No Errors Expected";
        REQUIRE(vi.size() == view.size());
      }
    }
    
    WHEN("a segment of a container is used to construct a view"){
      const long l = 4;
      utility::View<int> view( vi.begin(), vi.begin() + l );
      THEN("the View will function with range iteration"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [range-based iteration] No Errors Expected";
        int viewSum = 0;
        for (auto element : view ){ viewSum += element; }
        int referenceSum = std::accumulate(vi.begin(), vi.begin() + l, 0);
        REQUIRE(referenceSum == viewSum); 
      }
      
      THEN("the bracket operator works"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [operator[]] No Errors Expected";
        for (int i = 0; i < l ; ++i){
          REQUIRE(vi[i] == view[i]);  
        }
      }

      THEN("the 'at' method works"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [at] No Errors Expected";
        for (int i = 0; i < l ; ++i){
          REQUIRE(vi.at(i) == view.at(i));  
        }
        LOG(INFO) << "Test " << ++testNumber
                  << ": [at] Errors Expected";
        REQUIRE_THROWS(view.at(l));
        LOG(INFO) << "Test " << ++testNumber
                  << ": [at] Errors Expected";
        REQUIRE_THROWS(view.at(-1));        
      }

      THEN("the 'back' method works "){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [back] No Errors Expected";
        REQUIRE(vi[l-1] == view.back());
      }

      THEN("the 'front' method works "){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [front] No Errors Expected";
        REQUIRE(vi.front() == view.front());
      }

      THEN("the 'size' method works "){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [size] No Errors Expected";
        REQUIRE(l == view.size());
      }
    }
  }
  
  GIVEN("Views for comparison"){
    std::vector<int> a = {0,1,2,3,4};
    std::vector<int> b = {0,1,2,3,5};
    utility::View<int> v0(a.begin(), a.end());
    utility::View<int> v1(b.begin(), b.end());
    utility::View<int> v2(a.begin(), a.end()-1);
    utility::View<int> v3(b.begin(), b.end()-1);
    WHEN("passed to comparison operators"){
      THEN("comparisons will evaluate correctly"){
        LOG(INFO) << "Test " << ++testNumber
                  << ": [operator==] No Errors Expected";
        REQUIRE(true == (v0 == v0));
        REQUIRE(false == (v0 == v1));
        REQUIRE(true == (v3 == v2));
        REQUIRE(false == (v3 == v0));
        REQUIRE(false == (v3 == v1));
        
        LOG(INFO) << "Test " << ++testNumber
                  << ": [operator!=] No Errors Expected";
        REQUIRE(false == (v0 != v0));
        REQUIRE(true == (v0 != v1));
        REQUIRE(true == (v3 != v0));
        REQUIRE(false == (v3 != v2));
        REQUIRE(true == (v3 != v1));        

        LOG(INFO) << "Test " << ++testNumber
                  << ": [operator<] No Errors Expected";
        REQUIRE(true == (v0 < v1));
        REQUIRE(false == (v1 < v0));
        REQUIRE(true == (v3 < v0));

        LOG(INFO) << "Test " << ++testNumber
                  << ": [operator>] No Errors Expected";
        REQUIRE(true == (v1 > v0));
        REQUIRE(false == (v0 > v1));
        REQUIRE(false == (v3 > v0));

        LOG(INFO) << "Test " << ++testNumber
                  << ": [operator<=] No Errors Expected";
        REQUIRE(true == (v0 <= v1));
        REQUIRE(false == (v1 <= v0));
        REQUIRE(true == (v3 <= v0));
        
        LOG(INFO) << "Test " << ++testNumber
                  << ": [operator>=] No Errors Expected";
        REQUIRE(true == (v1 >= v0));
        REQUIRE(false == (v0 >= v1));
        REQUIRE(false == (v3 >= v0));
      }
    }
  }
}
