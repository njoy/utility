/** @brief File stream buffer using C's FILE*.
 */
template< class Char_t, class Traits = std::char_traits< Char_t > >
class FILE_streambuf : public std::basic_streambuf< Char_t, Traits > {
  FILE* filePtr;
  const std::size_t putBack;
  std::vector< char > buffer;

public:
  FILE_streambuf( FILE* filePtr,
		  std::size_t bufferSize = 256,
		  std::size_t putBack = 8 ) :
    filePtr( filePtr ),
    putBack( std::max( putBack, std::size_t(1) ) ),
    buffer( std::max( bufferSize, putBack) + putBack){
    char* end = &( this->buffer.front() ) + this->buffer.size();
    this->setg( end, end, end );
  }

  FILE_streambuf( const FILE_streambuf& ) = delete;
  FILE_streambuf( FILE_streambuf&& ) = default;
  FILE_streambuf& operator= ( const FILE_streambuf& ) = delete;
  FILE_streambuf& operator= ( FILE_streambuf&& ) = default;
  virtual ~FILE_streambuf(){
    fclose( this->filePtr );
  }
  
private:
  typename Traits::int_type underflow(){
    if ( this->gptr() < this->egptr() ){
      return Traits::to_int_type( *( this->gptr() ) );
    }
    char* base = &( this->buffer.front() );
    char* start = base;

    if ( this->eback() == base ){
      std::memmove( base, this->egptr() - this->putBack, this->putBack );
      start += this->putBack;
    }
    std::size_t nConsumedCharacters =
      std::fread( start, 1, this->buffer.size() - (start - base), filePtr );
    if ( not nConsumedCharacters ){ return Traits::eof(); }

    this->setg( base, start, start + nConsumedCharacters);
    return Traits::to_int_type( *(this->gptr() ) );
  }
};

