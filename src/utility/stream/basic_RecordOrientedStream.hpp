#include "utility/stream/basic_RecordOriented_streambuf.hpp"

template < template< typename, typename > class Base,
	   typename Char_t, typename Traits = std::char_traits< Char_t > >
class basic_RecordOrientedStream : public Base< Char_t, Traits > {

  using streambuf = basic_RecordOriented_streambuf< InputTag, Char_t, Traits >;

  std::basic_string< Char_t, Traits > buffer = "";
  long lineNumber;
  
  basic_RecordOrientedStream
  ( Base< Char_t, Traits >& base, const long lineNumber ) :
    Base< Char_t, Traits >( streambuf( *(base.rdbuf()),
				       this->buffer,
				       this->lineNumber ) ),
    lineNumber( lineNumber ){}

#include "utility/stream/basic_RecordOrientedStream/src/ctor.hpp"
#include "utility/stream/basic_RecordOrientedStream/src/dtor.hpp"
#include "utility/stream/basic_RecordOrientedStream/src/assignment.hpp"
};
