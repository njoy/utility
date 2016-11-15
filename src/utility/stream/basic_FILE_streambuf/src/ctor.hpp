basic_FILE_streambuf( FILE* filePtr,
    std::size_t bufferSize = 256,
    std::size_t putBack = 8 ) :
  filePtr( filePtr ),
  putBack( std::max( putBack, std::size_t(1) ) ),
  buffer( std::max( bufferSize, putBack ) + putBack ){
  std::fflush( this->filePtr );
  std::setbuf( this->filePtr, nullptr );
  char* begin = &( this->buffer.front() );
  char* end = begin + this->buffer.size();
  this->setg( end, end, end );
  this->setp( begin, --end );
  *end = 0;
}

basic_FILE_streambuf( const basic_FILE_streambuf& ) = delete;
basic_FILE_streambuf( basic_FILE_streambuf&& ) = default;
basic_FILE_streambuf& operator= ( const basic_FILE_streambuf& ) = delete;
basic_FILE_streambuf& operator= ( basic_FILE_streambuf&& ) = default;


