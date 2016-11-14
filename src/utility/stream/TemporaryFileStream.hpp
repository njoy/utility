template < class Char_t, class Traits = std::char_traits< Char_t > >
class TemporaryFileStream : public std::basic_ostream< Char_t, Traits > {
public:
  TemporaryFileStream( int n = 100)
    try : TemporaryFileStream( file(n) ) {}
    catch ( std::exception& e ){
      /* Log error */
      throw e;
    }

#include "utility/stream/TemporaryFileStream/src/dtor.hpp"

  const std::string filename;

private:
#include "utility/stream/TemporaryFileStream/src/path.hpp"
#include "utility/stream/TemporaryFileStream/src/file.hpp"


  TemporaryFileStream( std::pair<std::string, FILE_streambuf<Char_t>*> pair ) :
    std::basic_ostream< Char_t, Traits >( pair.second ),
    filename( pair.first ){}

};


