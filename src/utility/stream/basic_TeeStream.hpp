#include "utility/stream/basic_Tee_streambuf.hpp"

template< template< typename, typename > class Base >
struct Tee;

template<>
struct Tee< std::basic_istream > {
  template< typename Char_t, typename Traits >
  using streambuf = basic_Tee_streambuf< InputTag, Char_t, Traits >;
};

template<>
struct Tee< std::basic_ostream > {
  template< typename Char_t, typename Traits >
  using streambuf = basic_Tee_streambuf< OutputTag, Char_t, Traits >;
};
  
template < template< typename, typename > class Base,
	   typename Char_t, typename Traits = std::char_traits< Char_t > >
class basic_TeeStream : public Base< Char_t, Traits > {    
public:

  using streambuf = typename Tee< Base >::template streambuf< Char_t, Traits >;

  basic_TeeStream( Base< Char_t, Traits >& base,
		   std::basic_ostream< Char_t, Traits >& fork ) 
    try :
      Base< Char_t, Traits >
	( std::make_unique< streambuf >
	  ( base.rdbuf(), fork.rdbuf() ).release() ){}
    catch( std::exception& e ){
      Log::info( "Error while constructing basic_TeeStream" );
      throw e;
    }
  
#include "utility/stream/basic_TeeStream/src/ctor.hpp"
#include "utility/stream/basic_TeeStream/src/dtor.hpp"
#include "utility/stream/basic_TeeStream/src/assignment.hpp"

};
