basic_RecordOrientedStream( const basic_RecordOrientedStream& ) = delete;
basic_RecordOrientedStream( basic_RecordOrientedStream&& other ){
  this->rdbuf() = other.rdbuf();
  this->buffer = std::move(other.buffer);
  this->lineNumber = other.lineNumber;
  other.rdbuf( nullptr );
}
