private:
template< typename DerivedStream >
basic_RecordOrientedStream( std::unique_ptr< DerivedStream >&& core, const long lineNumber ) :
  Stream( new Streambuf
          ( *(core->rdbuf()), this->buffer, this->lineNumber ) ),
  core( std::move( core ) ), lineNumber( lineNumber ){
}

public:
template< typename DerivedStream >
basic_RecordOrientedStream( DerivedStream&& core, const long lineNumber = 1 ) :
  basic_RecordOrientedStream( std::make_unique< DerivedStream >
			      ( std::move( core ) ), lineNumber ){}

basic_RecordOrientedStream
( Stream& core, const long lineNumber = 1 ) :
  basic_RecordOrientedStream( std::make_unique< Stream >( core.rdbuf() ),
			      lineNumber ){}

basic_RecordOrientedStream( const basic_RecordOrientedStream& ) = delete;

basic_RecordOrientedStream( basic_RecordOrientedStream&& other ) :
  Stream( new Streambuf
          ( *(other.core->rdbuf()), this->buffer, this->lineNumber ) ) {
  this->core = std::move(other.core);
  this->buffer = std::move(other.buffer);
  this->lineNumber = other.lineNumber;
}
