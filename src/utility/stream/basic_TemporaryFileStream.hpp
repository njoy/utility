template < class Char_t, class Traits = std::char_traits< Char_t > >
class basic_TemporaryFileStream : public std::basic_ostream< Char_t, Traits > {

  std::string filepath;

private:
#include "utility/stream/basic_TemporaryFileStream/src/path.hpp"
#include "utility/stream/basic_TemporaryFileStream/src/file.hpp"

public:
#include "utility/stream/basic_TemporaryFileStream/src/ctor.hpp"
#include "utility/stream/basic_TemporaryFileStream/src/dtor.hpp"
#include "utility/stream/basic_TemporaryFileStream/src/assignment.hpp"
  
  const std::string& filename(){ return this->filepath; }

};


