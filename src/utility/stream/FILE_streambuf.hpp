template< class Char_t, class Traits = std::char_traits< Char_t > >
class FILE_streambuf : public std::basic_streambuf< Char_t, Traits > {
public:
#include "utility/stream/FILE_streambuf/src/ctor.hpp"
#include "utility/stream/FILE_streambuf/src/dtor.hpp"

  FILE* filePtr;
  const std::size_t putBack;
  std::vector< char > buffer;

#include "utility/stream/FILE_streambuf/src/overflow.hpp"

private:
#include "utility/stream/FILE_streambuf/src/flush.hpp"
#include "utility/stream/FILE_streambuf/src/underflow.hpp"
    
  typename Traits::int_type sync(){ return this->flush() ? 0 : -1; }
};
