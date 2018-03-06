basic_RecordOrientedStream&
operator=( const basic_RecordOrientedStream& ) = delete;

basic_RecordOrientedStream&
operator=( basic_RecordOrientedStream&& other ){
  if ( this->rdbuf() ){ delete this->rdbuf(); }
  this->core = std::move(other.core);
  this->buffer = std::move(other.buffer);
  this->lineNumber = other.lineNumber;
  this->rdbuf( new Streambuf( *(this->core->rdbuf()),
                              this->buffer, this->lineNumber ) );

  return *this;
}
