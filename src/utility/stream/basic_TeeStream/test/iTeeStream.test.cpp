#define CATCH_CONFIG_MAIN

#include <sstream>

#include "catch.hpp"

#include "utility.hpp"

using namespace njoy::utility::stream;

SCENARIO( "TeeStream and Tee_streambuf" ){
  std::string reference = "abcdefg--123456";
  std::string loremIpsum =
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit."
    " Cras tincidunt pretium nulla, eget ullamcorper risus euismod ut."
    " Donec rhoncus ultricies interdum."
    " Ut ut dui eget ipsum egestas eleifend."
    " Phasellus ut est nibh."
    " Duis et iaculis mi."
    " Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos."
    " Mauris in luctus ex, id iaculis arcu. Donec in tincidunt elit."
    " Curabitur odio velit, vehicula vitae leo vitae, tempus elementum nunc."
    " Nulla in convallis urna."
    " Duis sem risus, pharetra vitae efficitur a, tincidunt vitae nisl."
    " Phasellus vel odio sit amet ipsum mattis suscipit."
    " In pellentesque nisl elit, nec placerat tellus elementum nec."
    " Cras vulputate tempor rhoncus."
    " In vulputate eros nec justo placerat venenatis."
    " Donec non felis quis nisl dictum sodales."
    " Vestibulum eu rhoncus arcu, at luctus risus."
    " Aliquam non nibh venenatis, sodales libero cursus, semper neque."
    " Etiam dapibus nisi lectus, quis aliquam mi volutpat in."
    " Duis vestibulum metus consectetur nisi dapibus, ac tincidunt volutpat.";
  
  auto iss = std::istringstream( reference + ' ' + loremIpsum );
  std::ostringstream oss;
  std::string sink;
  {
    iTeeStream its(iss, oss);
    its >> sink;
  }
  REQUIRE( reference == sink );
  REQUIRE( reference + ' ' == oss.str() );
  {
    iTeeStream its(iss, oss);
    std::getline( its, sink );
    its.unget();
    its.get();
  }
  REQUIRE( loremIpsum == sink );
  REQUIRE( reference + ' ' + loremIpsum == oss.str() );
  {
    using iTee_streambuf = basic_Tee_streambuf< InputTag, char >;
    REQUIRE_THROWS( iTee_streambuf( iss.rdbuf(), nullptr ) );
    REQUIRE_THROWS( iTee_streambuf( nullptr, oss.rdbuf() ) );
    //REQUIRE_THROWS( iTeeStream( iss, os ) );
  }  
} // SCENARIO
