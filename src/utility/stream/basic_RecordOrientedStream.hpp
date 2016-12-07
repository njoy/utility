#include "utility/stream/basic_RecordOriented_streambuf.hpp"

template < template< typename, typename > class BaseStream,
	   typename Char_t, typename Traits = std::char_traits< Char_t > >
class basic_RecordOrientedStream : public BaseStream< Char_t, Traits > {
public:
  /* convenience typedef */
  using Streambuf = basic_RecordOriented_streambuf< InputTag, Char_t, Traits >;
  using Stream = BaseStream< Char_t, Traits >;
  
  /* fields */
  std::unique_ptr<Stream> core;
  std::basic_string< Char_t, Traits > buffer = "";
  long lineNumber = 1;

#include "utility/stream/basic_RecordOrientedStream/src/ctor.hpp"
#include "utility/stream/basic_RecordOrientedStream/src/dtor.hpp"
#include "utility/stream/basic_RecordOrientedStream/src/assignment.hpp"
};
