FILE_streambuf( FILE* filePtr,
    std::size_t bufferSize = 256,
    std::size_t putBack = 8 ) :
  filePtr( filePtr ),
  putBack( std::max( putBack, std::size_t(1) ) ),
  buffer( std::max( bufferSize, putBack) + putBack){
  std::fflush( this->filePtr );
  std::setbuf( this->filePtr, nullptr );
  char* begin = &( this->buffer.front() );
  char* end = begin + this->buffer.size();
  this->setg( end, end, end );
  this->setp( begin, --end );
  *end = 0;
}

FILE_streambuf( const FILE_streambuf& ) = delete;
FILE_streambuf( FILE_streambuf&& ) = default;
FILE_streambuf& operator= ( const FILE_streambuf& ) = delete;
FILE_streambuf& operator= ( FILE_streambuf&& ) = default;


