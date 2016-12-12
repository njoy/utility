basic_RecordOrientedStream&
operator=( const basic_RecordOrientedStream& ) = delete;

basic_RecordOrientedStream&
operator=( basic_RecordOrientedStream&& other ){
  if ( this->rdbuf() ){ delete this->rdbuf(); }

  this->rdbuf() = other.rdbuf();
  this->buffer = std::move(other.buffer);
  this->lineNumber = other.lineNumber;
  other.rdbuf( nullptr );
}
